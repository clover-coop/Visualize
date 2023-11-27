#pragma once

#include "../StructsActors/BuildingStructsActor.h"
#include "../StructsActors/DataStructsActor.h"

class DrawVertices {
public:
	DrawVertices();
	~DrawVertices();

	static void LoadPolygons(TArray<FPolygonSimplified> polygonsSimplified, bool destroyAll = true,
		bool addHeight = true, float addHeightOffset = 0.0f);
	static void DrawPolygon(FPolygon polygon);
	static void LoadVertices(TArray<FString> skipTypes = {});
};
