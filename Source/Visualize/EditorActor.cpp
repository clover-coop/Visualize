#include "EditorActor.h"

#include "Common/Socket.h"
#include "Common/UnrealGlobal.h"
#include "Landscape/VectorTiles.h"

AEditorActor::AEditorActor()
{
}

void AEditorActor::BeginPlay()
{
	Super::BeginPlay();
	// GetTiles();
}

void AEditorActor::GetTiles() {
	UE_LOG(LogTemp, Display, TEXT("AEditorActor::GetTiles"));
	UnrealGlobal* unrealGlobal = UnrealGlobal::GetInstance();
	unrealGlobal->Init(GetWorld());
	// this->Login();
	VectorTiles* vectorTiles = VectorTiles::GetInstance();
	float lng = -122.033802;
	float lat = 37.977362;
	vectorTiles->GetTiles(lng, lat, 125, 125);
}

void AEditorActor::Clear() {
	UnrealGlobal* unrealGlobal = UnrealGlobal::GetInstance();
	unrealGlobal->SetWorld(GetWorld());
	unrealGlobal->CleanUp();
}
