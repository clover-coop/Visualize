#pragma once

#include "../../StructsActors/BuildingStructsActor.h"
#include "../../Modeling/ModelBase.h"

class LMServerRoom {
public:
	LMServerRoom();
	~LMServerRoom();

	static TMap<FString, FPolygon> Create(FVector size, FModelParams modelParams = FModelParams(),
		FModelCreateParams createParamsIn = FModelCreateParams());
};
