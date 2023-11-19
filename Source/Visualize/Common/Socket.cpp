#include "Socket.h"
#include "WebSocketsModule.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Containers/UnrealString.h"
#include <string>

#include "./UnrealGlobal.h"

Socket* Socket::pinstance_{nullptr};
std::mutex Socket::mutex_;

Socket::Socket() {
}

Socket::~Socket() {
}

Socket *Socket::GetInstance() {
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr) {
		pinstance_ = new Socket();
	}
	return pinstance_;
}

void Socket::Init() {
    if (!_inited || (!_connecting && !IsConnected())) {
        _inited = true;
        UnrealGlobal* unrealGlobal = UnrealGlobal::GetInstance();
        unrealGlobal->InitSettings();
        InitSocket();
        // unrealGlobal->GetSocket(GetWorld());
        // unrealGlobal->SetInited("socket");
    }
}

void Socket::InitSocket(bool closeSocket) {
    _connecting = true;
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
		FModuleManager::Get().LoadModule("WebSockets");
	}

	if (closeSocket) {
		this->Destroy();
	}

	UnrealGlobal* unrealGlobal = UnrealGlobal::GetInstance();
	FString Url = unrealGlobal->_settings->urlWebsocket;
	_webSocket = FWebSocketsModule::Get().CreateWebSocket(Url);

	_webSocket->OnConnected().AddLambda([this]() {
        _connecting = false;
		UE_LOG(LogTemp, Display, TEXT("Websocket connected"));
	});
	_webSocket->OnConnectionError().AddLambda([](const FString& Error) {
		UE_LOG(LogTemp, Error, TEXT("Websocket error %s"), *Error);
	});
	_webSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) {
		UE_LOG(LogTemp, Warning, TEXT("Websocket closed %s"), *Reason);
	});
	_webSocket->OnMessage().AddLambda([this](const FString& MessageString) {
		// UE_LOG(LogTemp, Display, TEXT("Websocket OnMessage %s"), *MessageString);
		this->HandleMessage(MessageString);
	});
	_webSocket->OnRawMessage().AddLambda([this](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) {
		uint8* line = (uint8*)Data;
		FString ValidString = "";
		for (int ii = 0; ii < Size; ii++) {
			if (line[ii] >= 0 && line[ii] < 128) {
				ValidString += char(line[ii]);
			}
		}
		// UE_LOG(LogTemp, Display, TEXT("Websocket OnRawMessage %s %d"), *ValidString, BytesRemaining);
		// TODO - this assumes messages are all from the same source.. What if another message comes in between frames??
		if (BytesRemaining > 0) {
			_rawMessageJoiner += ValidString;
		} else {
			if (_rawMessageJoiner.Len() > 0) {
				ValidString = _rawMessageJoiner + ValidString;
			}
			// UE_LOG(LogTemp, Display, TEXT("Websocket OnRawMessage %d %s"), ValidString.Len(), *ValidString);
			this->HandleMessage(ValidString);
			// Reset for next time.
			_rawMessageJoiner = "";
		}
	});
	_webSocket->OnMessageSent().AddLambda([](const FString& MessageString) {
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Websocket sent message" + MessageString);
	});
	_webSocket->Connect();
}

void Socket::Destroy() {
	_listenersOn.Empty();
	this->Close();
}

void Socket::Close() {
	if (_webSocket && _webSocket->IsConnected()) {
		_webSocket->Close();
	}
}

bool Socket::IsConnected() {
    // Init();
	return _webSocket && _webSocket->IsConnected();
}

TMap<FString, FString> Socket::GetAuth() {
	TMap<FString, FString> Auth = {
		{ "user_id", "" },
		{ "session_id", "" }
	};
	return Auth;
}

void Socket::Emit(FString Route, TMap<FString, FString> Data) {
    Init();
	FString JsonString;
	FSocketData SendObj;
	SendObj.Route = Route;
	SendObj.Data = Data;
	SendObj.Auth = GetAuth();
	if (!FJsonObjectConverter::UStructToJsonObjectString(SendObj, JsonString, 0, 0)) {
		UE_LOG(LogTemp, Error, TEXT("SocketActor.Emit JsonString error %s"), *Route);
	} else {
		// TODO - ensure socket is open
		UE_LOG(LogTemp, Display, TEXT("SocketActor.Emit Route %s"), *Route);
		_webSocket->Send(JsonString);
	}
}

FString Socket::On(FString RouteKeyPrefix, FString Route, std::function<void(FString)> Callback) {
    Init();
	FString RouteKey = RouteKeyPrefix + Route;
	this->Off(RouteKey);
	if (!_listenersOn.Contains(RouteKey)) {
		_listenersOn.Add(Route, Callback);
	} else {
		UE_LOG(LogTemp, Error, TEXT("SocketActor.On route already exists - need to update to TArray to support multiple listeners per route!"));
	}
	return RouteKey;
}

void Socket::Off(FString RouteKey) {
    Init();
	if (_listenersOn.Contains(RouteKey)) {
		_listenersOn.Remove(RouteKey);
	}
}

void Socket::HandleMessage(FString Message) {
	// Find route.
	FString Word = "\"route\": \"";
	int IndexWord = Message.Find(Word);
	int Start = (IndexWord + Word.Len());
	// Could be long messages (4 million+ len, so need 32 to 64 bit; 16bit only goes to 65k)
	uint64 IndexEnd = Message.Find("\",", ESearchCase::CaseSensitive, ESearchDir::FromStart, Start);
	uint64 SliceLen = IndexEnd - Start;
	FString Route = Message.Mid(Start, SliceLen);

	// Get data
	Word = "\"data\": ";
	IndexWord = Message.Find(Word);
	Start = (IndexWord + Word.Len());
	IndexEnd = Message.Find(", \"auth\":", ESearchCase::CaseSensitive, ESearchDir::FromStart, Start);
	SliceLen = IndexEnd - Start;
	FString DataString = Message.Mid(Start, SliceLen);
	if (_listenersOn.Contains(Route)) {
		_listenersOn[Route](DataString);
	}
}
