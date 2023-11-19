#include "LayoutModelBase.h"

#include "../Common/Lodash.h"
#include "../Common/UnrealGlobal.h"
#include "../Mesh/LoadContent.h"
#include "../Modeling/ModelBase.h"
#include "../StructsActors/ModelingStructsActor.h"
#include "OfficeRoom/LMLobby.h"
#include "LMParkingLot.h"

LayoutModelBase* LayoutModelBase::pinstance_{nullptr};
std::mutex LayoutModelBase::mutex_;

LayoutModelBase::LayoutModelBase() {
}

LayoutModelBase::~LayoutModelBase() {
}

LayoutModelBase *LayoutModelBase::GetInstance() {
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr) {
		pinstance_ = new LayoutModelBase();
	}
	return pinstance_;
}

void LayoutModelBase::SetWorld(UWorld* World1) {
	World = World1;
}

UWorld* LayoutModelBase::GetWorld() {
	return World;
}

void LayoutModelBase::DestroyActors() {
	ModelBase* modelBase = ModelBase::GetInstance();
	modelBase->DestroyActors();
}

void LayoutModelBase::CleanUp() {
	DestroyActors();
}

void LayoutModelBase::SetInputs(FLayoutModelBaseParams layoutParams) {
	_layoutParams = layoutParams;
}

std::tuple<FLayoutModelBaseParams, FModelParams> LayoutModelBase::GetInputs(FString defaultName, FVector defaultSize) {
	FLayoutModelBaseParams layoutParams = _layoutParams;
	if (layoutParams.name.Len() < 1) {
		layoutParams.name = defaultName;
	}
	layoutParams.name = Lodash::GetInstanceId(layoutParams.name + "_");

	float minSize = 0.01;
	if (layoutParams.size.X < minSize || layoutParams.size.X > -1 * minSize) {
		layoutParams.size.X = defaultSize.X;
	}
	if (layoutParams.size.Y < minSize || layoutParams.size.Y > -1 * minSize) {
		layoutParams.size.Y = defaultSize.Y;
	}
	if (layoutParams.size.Z < minSize || layoutParams.size.Z > -1 * minSize) {
		layoutParams.size.Z = defaultSize.Z;
	}

	FModelParams modelParams;
	if (layoutParams.materialKey.Len() > 0) {
		LoadContent* loadContent = LoadContent::GetInstance();
		modelParams.materialPath = loadContent->Material(layoutParams.materialKey);
	}

	return { layoutParams, modelParams };
}

void LayoutModelBase::Create() {
	if (_layoutParams.pairsString.Len() > 0) {
		_layoutParams.pairs = Lodash::PairsStringToObject(_layoutParams.pairsString);
	}

	UE_LOG(LogTemp, Display, TEXT("subCategory %s"), *_layoutParams.subCategory);

	if (_layoutParams.subCategory == "lobby") {
		LMLobby::CreateFromInputs();
	}
	else if (_layoutParams.subCategory == "parking")
	{
		LMParkingLot::CreateFromInputs();
	}
}
