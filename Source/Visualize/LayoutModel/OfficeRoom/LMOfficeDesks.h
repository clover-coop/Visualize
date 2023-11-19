#pragma once

#include "../../StructsActors/BuildingStructsActor.h"
#include "../../Modeling/ModelBase.h"

class LMOfficeDesks {
public:
	LMOfficeDesks();
	~LMOfficeDesks();

	static TMap<FString, FPolygon> Desks(FVector size, FModelParams modelParams = FModelParams(),
		FModelCreateParams createParamsIn = FModelCreateParams());
};
