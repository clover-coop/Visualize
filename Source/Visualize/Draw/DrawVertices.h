#pragma once

#include "../StructsActors/BuildingStructsActor.h"
#include "../StructsActors/DataStructsActor.h"

class DrawVertices {
public:
	DrawVertices();
	~DrawVertices();

	static void LoadPolygons(TArray<FPolygonSimplified> polygonsSimplified, bool destroyAll = true);
	static void DrawPolygon(FPolygon polygon);
	static void LoadVertices(TArray<FString> skipTypes = {});
};
