#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "./BuildingStructsActor.h"

#include "DataStructsActor.generated.h"

UCLASS()
class VISUALIZE_API ADataStructsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADataStructsActor();

public:	
	// virtual void Tick(float DeltaTime) override;

	static FDataProjectJsonSimplified ProjectToSimplified(FDataProjectJson data);
	static FDataProjectJson ProjectFromSimplified(FDataProjectJsonSimplified dataSimplified);

};

USTRUCT()
struct FDataSettings {
	GENERATED_BODY()

	UPROPERTY()
	FString loginEmail;
	UPROPERTY()
	FString loginPassword;
	UPROPERTY()
	FString projectUName;
	UPROPERTY()
	FString urlWebsocket;
	UPROPERTY()
	int performanceQualityLevel;
	UPROPERTY()
	FString projectPath;
	UPROPERTY()
	TMap<FString, FString> jsonFiles;

	FDataSettings() {};
	FDataSettings(FString loginEmail_, FString loginPassword_, FString projectUName_,
		FString urlWebsocket_, int performanceQualityLevel_,
		FString projectPath_, TMap<FString, FString> jsonFiles_) {
		loginEmail = loginEmail_;
		loginPassword = loginPassword_;
		projectUName = projectUName_;
		urlWebsocket = urlWebsocket_;
		performanceQualityLevel = performanceQualityLevel_;
		projectPath = projectPath_;
		jsonFiles = jsonFiles_;
	};
};

USTRUCT()
struct FDataLogin {
	GENERATED_BODY()

	UPROPERTY()
	int valid;
	UPROPERTY()
	FString msg;
	UPROPERTY()
	TMap<FString, FString> user;
	UPROPERTY()
	TMap<FString, FString> user_preferences;
    // public UserCurrentStateClass user_current_state = new UserCurrentStateClass() {};
    // public List<ProjectClass> projects = new List<ProjectClass>() {};
    // public List<UserProjectClass> userProjects = new List<UserProjectClass>() {};

	// FDataLogin(int valid = 0, FString msg = "",  TMap<FString, FString> Auth = {}) {}
};

USTRUCT()
struct FDataProject {
	GENERATED_BODY()

	UPROPERTY()
	int valid;
	UPROPERTY()
	FString msg;
	UPROPERTY()
	TArray<FLand> lands;
};

USTRUCT()
struct FDataGetVectorTiles {
	GENERATED_BODY()

	UPROPERTY()
	int valid;
	UPROPERTY()
	FString msg;
	UPROPERTY()
	TArray<FPolygonSimplified> polygons;
	UPROPERTY()
	int currentTile;
	UPROPERTY()
	int totalTiles;
};

USTRUCT()
struct FDataProjectJsonSimplified {
	GENERATED_BODY()

	UPROPERTY()
	TMap<FString, FPolygonSimplified> polygons;

	FDataProjectJsonSimplified() {};
	FDataProjectJsonSimplified(TMap<FString, FPolygonSimplified> polygons_) {
		polygons = polygons_;
	};
};

USTRUCT()
struct FDataProjectJson {
	GENERATED_BODY()

	UPROPERTY()
	TMap<FString, FPolygon> polygons;

	FDataProjectJson() {};
	FDataProjectJson(TMap<FString, FPolygon> polygons_) {
		polygons = polygons_;
	};
};

// USTRUCT()
// struct FDataPlot {
// 	GENERATED_BODY()

// 	UPROPERTY()
// 	TMap<FString, FPlot> plots;

// 	FDataPlot() {};
// 	FDataPlot(TMap<FString, FPlot> plots_) {
// 		plots = plots_;
// 	};
// }

USTRUCT()
struct FContentMeshModel {
	GENERATED_BODY()

	UPROPERTY()
	FString size = "";
	UPROPERTY()
	FString type = "";
	UPROPERTY()
	FString path = "";
	UPROPERTY()
	FString materialPath = "";
	UPROPERTY()
	FString rotation = "0,0,0";
	UPROPERTY()
	FString tags = "";
	// UPROPERTY()
	// FString offset = "";

	FContentMeshModel() {};
	FContentMeshModel(FString size_, FString type_, FString path_,
		FString materialPath_ = "", FString rotation_ = "0,0,0", FString tags_ = "") {
		size = size_;
		type = type_;
		path = path_;
		materialPath = materialPath_;
		rotation = rotation_;
		tags = tags_;
		// Ensure delimiter at end for searching.
		if (tags.Len() > 1 && !(tags.RightChop((tags.Len() - 1)) == ",")) {
			tags += ",";
		}
	};
};

USTRUCT()
struct FDataContentMesh {
	GENERATED_BODY()

	UPROPERTY()
	TMap<FString, FContentMeshModel> models;
	UPROPERTY()
	TMap<FString, FString> materials;
	UPROPERTY()
	TMap<FString, FString> textures;

	FDataContentMesh() {};
	FDataContentMesh(TMap<FString, FContentMeshModel> models_, TMap<FString, FString> materials_,
		TMap<FString, FString> textures_) {
		models = models_;
		materials = materials_;
		textures = textures_;
	};
};
