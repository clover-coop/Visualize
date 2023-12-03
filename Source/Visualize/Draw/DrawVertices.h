#pragma once

#include "../StructsActors/BuildingStructsActor.h"
#include "../StructsActors/DataStructsActor.h"

class DrawVertices {
public:
	DrawVertices();
	~DrawVertices();

	static void LoadPolygons(TArray<FPolygonSimplified> polygonsSimplified, bool destroyAll = false,
		bool addHeight = true, float addHeightOffset = 0.0f);
	static void DrawPolygon(FPolygon polygon);
	// static void DrawAllPolygons();
	static void LoadVertices(TArray<FString> skipTypes = {});
};
