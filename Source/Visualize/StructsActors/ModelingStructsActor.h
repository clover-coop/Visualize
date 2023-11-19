#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModelingStructsActor.generated.h"

UCLASS()
class VISUALIZE_API AModelingStructsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AModelingStructsActor();
};

UENUM()
enum ModelingCategory {
	ANIMAL,
	ARCHITECTURE,
	ELECTRONICS,
	FOOD,
	FURNITURE,
	PLANTS,
	// SPORTS,
	TOOLS,
	VEHICLE
};

UENUM()
enum ModelingSubCategoryAnimal {
	DOG
};

UENUM()
enum ModelingSubCategoryArchitecture {
	ELEVATOR,
	FENCE,
	SOLAR_PANEL,
	STAIRS,
	STREETLIGHT,
	TRASH_CAN
};

UENUM()
enum ModelingSubCategoryElectronics {
	CELL_PHONE,
	COMPUTER,
	// KEYBOARD,
	LAPTOP,
	MONITOR,
	// MOUSE,
	TV
};

UENUM()
enum ModelingSubCategoryFood {
	CUP,
	WATER_BOTTLE
};

UENUM()
enum ModelingSubCategoryFurniture {
	BED,
	BENCH,
	BOOK,
	CABINET,
	CHAIR,
	COUCH,
	DESK,
	DOOR,
	LIGHT,
	MIRROR,
	PILLOW,
	PLANTER_BOX,
	STAND,
	TABLE,
	WINDOW
};

UENUM()
enum ModelingSubCategoryPlants {
	BUSH,
	LEAVES,
	TREE
};

// UENUM()
// enum ModelingSubCategorySports {
// };

UENUM()
enum ModelingSubCategoryTools {
	PEN
};

UENUM()
enum ModelingSubCategoryVehicle
{
	CAR,
	EV_CHARGER,
	TRAIN,
	SOLAR_CHARGING_STATION
};

USTRUCT()
struct FModelingBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ModelingCategory> category;

	// Conditional hide sub category
	UPROPERTY()
	FString subCategory;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::ANIMAL", EditConditionHides))
	TEnumAsByte<ModelingSubCategoryAnimal> subCategoryAnimal;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::ARCHITECTURE", EditConditionHides))
	TEnumAsByte<ModelingSubCategoryArchitecture> subCategoryArchitecture;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::ELECTRONICS", EditConditionHides))
	TEnumAsByte<ModelingSubCategoryElectronics> subCategoryElectronics;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::FOOD", EditConditionHides))
	TEnumAsByte<ModelingSubCategoryFood> subCategoryFood;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::FURNITURE", EditConditionHides))
	TEnumAsByte<ModelingSubCategoryFurniture> subCategoryFurniture;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::PLANTS", EditConditionHides))
	TEnumAsByte<ModelingSubCategoryPlants> subCategoryPlants;
	// UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::SPORTS", EditConditionHides))
	// TEnumAsByte<ModelingSubCategorySports> subCategorySports;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::TOOLS", EditConditionHides))
	TEnumAsByte<ModelingSubCategoryTools> subCategoryTools;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "category == ModelingCategory::VEHICLE", EditConditionHides))
	TEnumAsByte<ModelingSubCategoryVehicle> subCategoryVehicle;

	UPROPERTY(EditAnywhere)
	FString name;
	UPROPERTY(EditAnywhere)
	FVector size;
	UPROPERTY(EditAnywhere)
	FString pairsString;
	UPROPERTY()
	TMap<FString, FString> pairs = {};
	UPROPERTY(EditAnywhere)
	FString materialKey = "";

	// FModelingBase() {};
};

UENUM()
enum ProceduralModelCategory {
	CUBE,
	CYLINDER,
	PRISM
};

USTRUCT()
struct FProceduralModelBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ProceduralModelCategory> category;
	UPROPERTY(EditAnywhere)
	FString name;
	UPROPERTY(EditAnywhere)
	FVector size;
	// UPROPERTY(EditAnywhere)
	// FVector vertices;
	UPROPERTY(EditAnywhere)
	int32 sidesSegmentCount;
	UPROPERTY(EditAnywhere)
	float topOffsetWidth;
	UPROPERTY(EditAnywhere)
	bool closeTop; // Closes the top face of the prism
	UPROPERTY(EditAnywhere)
	bool closeBottom; // Closes the bottom face of the prism
	UPROPERTY(EditAnywhere)
	FString pairsString;
	UPROPERTY()
	TMap<FString, FString> pairs = {};
	UPROPERTY(EditAnywhere)
	FString materialKey = "";
};

USTRUCT()
struct FLayoutModelBaseParams {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	// homeRoom, officeRoom, homeBuilding, officeBuilding, parkingLot, transitBuilding
	FString category;
	UPROPERTY(EditAnywhere)
	// homeBuilding:
	// homeRoom: bathroom, bedroom, closet, diningRoom, familyRoom, gameRoom, kitchen
	// officeBuilding:
	// officeRoom: conferenceRoom, desksRoom, cafeteria, lobby, serverRoom
	// parkingLot: outdoorParking, parkingGarage
	// transitBuilding: trainStation
	FString subCategory;
	UPROPERTY()
	FString name;
	UPROPERTY(EditAnywhere)
	FVector size;
	UPROPERTY(EditAnywhere)
	FString pairsString;
	UPROPERTY()
	TMap<FString, FString> pairs = {};
	UPROPERTY(EditAnywhere)
	FString materialKey = "";
};
