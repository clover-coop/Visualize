#pragma once

#include <mutex>
#include "IWebSocket.h"

#include "../StructsActors/CommonStructsActor.h"

class Socket {
private:
	static Socket *pinstance_;
	static std::mutex mutex_;

    TSharedPtr<IWebSocket> _webSocket;
    bool _inited = false;
	TMap<FString, std::function<void(FString)>> _listenersOn;
	FString _rawMessageJoiner = "";

public:
	Socket();
	~Socket();

	// Singletons should not be cloneable or assignable.
	Socket(Socket &other) = delete;
	void operator=(const Socket &) = delete;

	static Socket *GetInstance();

	void Close();
	bool IsConnected();
	void Emit(FString, TMap<FString, FString>);
	FString On(FString, FString, std::function<void(FString)>);
	void Off(FString);
	void InitSocket(bool closeSocket = false);
	void Destroy();

protected:
	void Init();
	void HandleMessage(FString);
	TMap<FString, FString> GetAuth();
};
