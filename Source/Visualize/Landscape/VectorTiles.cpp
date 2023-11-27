#include "VectorTiles.h"
#include "JsonObjectConverter.h"

#include "../Common/Lodash.h"
#include "../Common/Socket.h"
#include "../Common/UnrealGlobal.h"
#include "../Draw/DrawVertices.h"
// #include "./VerticesEdit.h"

VectorTiles* VectorTiles::pinstance_{nullptr};
std::mutex VectorTiles::mutex_;

VectorTiles::VectorTiles() {
}

VectorTiles::~VectorTiles() {
}

VectorTiles *VectorTiles::GetInstance() {
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr) {
		pinstance_ = new VectorTiles();
	}
	return pinstance_;
}

void VectorTiles::Init() {
	if (!_inited) {
		_inited = true;
		this->InitSocketOn();
	}
}

void VectorTiles::InitSocketOn() {
	Socket* socket = Socket::GetInstance();

	// this->DestroySocket();
	FString prefix = "VectorTiles";
	socket->On(prefix, "get-vector-tiles", [this](FString DataString) {
		FDataGetVectorTiles* Data = new FDataGetVectorTiles();
		if (!FJsonObjectConverter::JsonObjectStringToUStruct(DataString, Data, 0, 0)) {
			UE_LOG(LogTemp, Error, TEXT("VectorTiles.On get-vector-tiles json parse error"));
		} else {
			if (Data->valid > 0) {
				// // Add 1 height offset otherwise roads are below ground.
				// float heightOffset = 10.0f;
				// DrawVertices::LoadPolygons(Data->polygons, true, true, heightOffset);
				DrawVertices::LoadPolygons(Data->polygons);
			}
		}
	});
}

// void VectorTiles::Destroy() {
// 	this->DestroySocket();
// }

// void VectorTiles::DestroySocket() {
// 	UnrealGlobal* unrealGlobal = UnrealGlobal::GetInstance();
//     unrealGlobal->SocketOffRoutes(_socketKeys);
// 	_socketKeys.Empty();
// }

void VectorTiles::GetTiles(float lng, float lat, float xMeters, float yMeters) {
	Init();
	Socket* socket = Socket::GetInstance();
    // UnrealGlobal* unrealGlobal = UnrealGlobal::GetInstance();
	// VerticesEdit* verticesEdit = VerticesEdit::GetInstance();
	// verticesEdit->DestroyItems();
	TMap<FString, FString> Data = {
		{ "lng", Lodash::ToFixed(lng, 6) },
        { "lat", Lodash::ToFixed(lat, 6) },
        { "xMeters", Lodash::ToFixed(xMeters, 0) },
        { "yMeters", Lodash::ToFixed(yMeters, 0) },
	};
	socket->Emit("get-vector-tiles", Data);
}