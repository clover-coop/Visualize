#pragma once

#include <mutex>
#include "Engine/StaticMeshActor.h"

#include "../StructsActors/DataStructsActor.h"

class LoadContent {
private:
	static LoadContent *pinstance_;
	static std::mutex mutex_;

	TMap<FString, FContentMeshModel> _meshModels = {};
	TMap<FString, FString> _materialPaths = {};
	TMap<FString, FString> _texturePaths = {};

public:
	LoadContent();
	~LoadContent();

	// Singletons should not be cloneable or assignable.
	LoadContent(LoadContent &other) = delete;
	void operator=(const LoadContent &) = delete;
	static LoadContent *GetInstance();

	void CleanUp();

	std::tuple<FDataContentMesh, bool> LoadFile(FString fileName);
	void LoadMeshes(FString defaultMeshPath = "/Script/Engine.StaticMesh'/Game/Modeling/Primitives/Cube.Cube'");
	TArray<FString> GetMeshNamesByTypes(TArray<FString> types);
	TArray<FString> GetMeshNamesByTags(TArray<FString> tags);
	std::tuple<bool, TMap<FString, TArray<FString>>> FillMeshesByTags(TMap<FString, TArray<FString>> meshesByTags,
		TArray<FString> required = { "[all]" });
	FString Material(FString key);
	FString Texture(FString key);
	FString Mesh(FString key);
	FString MeshScale(FVector scale, FString meshKey = "", TArray<FString> axes = { "x", "y", "z" });
	FVector GetMeshSize(FString meshKey);
	FVector MeshRotation(FString meshKey);
};
