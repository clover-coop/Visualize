#pragma once

#include "../StructsActors/BuildingStructsActor.h"

class BuildingRoad {
public:
	BuildingRoad();
	~BuildingRoad();

	static TMap<FString, FPolygon> BetweenSpaces(TArray<TArray<FVector>> spacesVertices,
		float verticesBuffer);
};
