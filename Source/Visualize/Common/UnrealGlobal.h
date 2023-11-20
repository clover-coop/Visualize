#pragma once

#include <mutex>

#include "../StructsActors/DataStructsActor.h"
// #include "../CanvasTextWidget.h"
// #include "../GlobalActor.h"
// #include "../SocketActor.h"

class UnrealGlobal {

private:
	static UnrealGlobal *pinstance_;
	static std::mutex mutex_;

	UWorld* World;
	// TMap<FString, bool> _initeds = {};

public:
	UnrealGlobal();
	~UnrealGlobal();

	// Singletons should not be cloneable or assignable.
	UnrealGlobal(UnrealGlobal &other) = delete;
	void operator=(const UnrealGlobal &) = delete;

	FDataSettings* _settings = nullptr;
	// ASocketActor* SocketActor = nullptr;
	// AGlobalActor* _globalActor = nullptr;
	// UCanvasTextWidget* _canvasTextWidget = nullptr;
	TMap<FString, AActor*> _actors;

	static UnrealGlobal *GetInstance();
	// void SetWidgets(UCanvasTextWidget* canvasTextWidget);
	void Init(UWorld*);
	// void InitAll(UWorld*, TArray<FString> skipKeys = {});
	bool InitSettings();
	// FDataSettings* GetSettings();
	// void InitCommon(UWorld*);
	// void InitWeb(UWorld*);
	void InitMeshes();
	// void SetInited(FString key);
	// bool IsIniteds(TArray<FString>);
	// void GetSocket(UWorld*);
	// void SocketOffRoutes(TArray<FString> socketKeys);
	FDataSettings* Settings();
	void CleanUp(TArray<FString> skipKeys = {});
	void SetWorld(UWorld*);
	UWorld* GetWorld();
	float GetScale();
	static FVector Scale(FVector);
	void SetActorFolder(AActor* actor, FString path = "Spawned");
	void ClearAllSpawned();
	void ClearActorsByFolder(FString folderPath);
	void ClearActorsByNamePrefix(FString namePrefix);
	void RemoveAttachedActors(AActor* actor);
	AActor* GetActorByName(FString name, TSubclassOf<AActor> ActorClass, bool save = false, bool matchStartsWith = false);
	static std::tuple<FDataSettings*, bool> LoadSettings(FString fileName = "settings.json");
};
