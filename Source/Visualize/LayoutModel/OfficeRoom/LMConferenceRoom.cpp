#include "LMConferenceRoom.h"

#include "../LayoutModelBase.h"
#include "../LMRoomPlants.h"
#include "../LMTableChairs.h"
#include "../../Common/DataConvert.h"
#include "../../Common/Lodash.h"
#include "../../Common/MathPolygon.h"
#include "../../Common/MathVector.h"
#include "../../Landscape/VerticesEdit.h"
#include "../../Layout/LayoutPlace.h"
#include "../../Layout/LayoutPolyLine.h"
#include "../../Mesh/LoadContent.h"
#include "../../Modeling/ModelBase.h"
#include "../../Modeling/Furniture/ModelTable.h"
#include "../../Mesh/DynamicMaterial.h"
#include "../../Mesh/LoadContent.h"
#include "../../StructsActors/ModelingStructsActor.h"
#include "../../StructsActors/BuildingStructsActor.h"

LMConferenceRoom::LMConferenceRoom() {
}

LMConferenceRoom::~LMConferenceRoom() {
}

TMap<FString, FPolygon> LMConferenceRoom::Create(FVector size, FModelParams modelParams,
	FModelCreateParams createParamsIn) {
	FVector rotation = FVector(0,0,0), location = FVector(0,0,0), scale = FVector(1,1,1);
	FString uName, type, pairsString, scaleString;
	TArray<FVector> vertices;
	TMap<FString, FPolygon> polygons = {};

	// uName = Lodash::GetInstanceId("Room");
	// pairsString = "meshRule=roomCube&mat=wood&bottomMat=marbleTile&scale=" + DataConvert::VectorToString(size) +
	// 	ModelBase::AddRotationString(createParamsIn.rotation);
	// vertices = { createParamsIn.offset };
	// vertices = ModelBase::Vertices(vertices, createParamsIn);
	// polygons.Add(uName, FPolygon(uName, uName, vertices, FVector(0,0,0), "room", "point", pairsString));

	FWallPlants plantParams;
	plantParams.pairsStringPlants = "meshes=brackenFern,solidFern,cinnamonFern&placeOffsetAverage=0.3";
	plantParams.walls = { "left", "back", "front" };
	LMRoomPlants::WallPlants(size, modelParams, createParamsIn, plantParams);

	uName = Lodash::GetInstanceId("tv");
	location = FVector(0, size.Y / -2 + 1, 1.5);
	scale = FVector(2.5,2.5,2.5);
	pairsString = "mesh=wallTV&scale=" + DataConvert::VectorToString(scale) +
		ModelBase::AddRotationString(createParamsIn.rotation, FVector(0,0,90));
	vertices = { location + createParamsIn.offset };
	vertices = ModelBase::Vertices(vertices, createParamsIn);
	polygons.Add(uName, FPolygon(uName, uName, vertices, FVector(0,0,0), "room", "point", pairsString));

	// scale = FVector(size.X / 2, size.Y / 2, -1);
	scale = FVector(2.5 + 1 * 2, 5.5 + 1 * 2, 1);
	FTableChairs tableParams;
	tableParams.meshesByTags["table"] = { "conferenceTable" };
	tableParams.meshesByTags["chair"] = { "officeChair" };
	LMTableChairs::TableWithChairs(scale, modelParams, createParamsIn, tableParams);

	VerticesEdit* verticesEdit = VerticesEdit::GetInstance();
	verticesEdit->AddAndSave(polygons);
	return polygons;
}
