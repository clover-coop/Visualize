#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EditorActor.generated.h"

UCLASS()
class VISUALIZE_API AEditorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEditorActor();

	UFUNCTION(CallInEditor)
	void GetTiles();
	UFUNCTION(CallInEditor)
	void Clear();

protected:
	virtual void BeginPlay() override;

// public:	
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;

};
