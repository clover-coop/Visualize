#pragma once

#include "../../StructsActors/BuildingStructsActor.h"
#include "../../Modeling/ModelBase.h"

class LMCafeteria {
public:
	LMCafeteria();
	~LMCafeteria();

	static TMap<FString, FPolygon> Create(FVector size, FModelParams modelParams = FModelParams(),
		FModelCreateParams createParamsIn = FModelCreateParams());
};
