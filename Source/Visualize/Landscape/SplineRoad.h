#pragma once

#include <mutex>
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "Engine/StaticMeshActor.h"

#include "../StructsActors/BuildingStructsActor.h"

class SplineRoad {

private:
	static SplineRoad *pinstance_;
	static std::mutex mutex_;

	UWorld* World;

	TMap<FString, TMap<FString, FPolygon>> _RoadsByType = {};
	AStaticMeshActor* _roadsActor = nullptr;
	TMap<FString, AActor*> _RoadsActors = {};

public:
	SplineRoad();
	~SplineRoad();

	// Singletons should not be cloneable or assignable.
	SplineRoad(SplineRoad &other) = delete;
	void operator=(const SplineRoad &) = delete;

	static SplineRoad *GetInstance();
	void SetWorld(UWorld*);
	void Init();
	void DestroyRoads();
	void CleanUp();

	void AddRoads(TMap<FString, FPolygon> roads);
	void DrawRoads();
};
