#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommonStructsActor.generated.h"

UCLASS()
class VISUALIZE_API ACommonStructsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACommonStructsActor();
};

// USTRUCT()
// struct FDataSettings {
// 	GENERATED_BODY()

// 	UPROPERTY()
// 	FString loginEmail;
// 	UPROPERTY()
// 	FString loginPassword;
// 	UPROPERTY()
// 	FString projectUName;
// 	UPROPERTY()
// 	FString urlWebsocket;
// 	UPROPERTY()
// 	int performanceQualityLevel;
// 	UPROPERTY()
// 	FString projectPath;
// 	UPROPERTY()
// 	TMap<FString, FString> jsonFiles;

// 	FDataSettings() {};
// 	FDataSettings(FString loginEmail_, FString loginPassword_, FString projectUName_,
// 		FString urlWebsocket_, int performanceQualityLevel_,
// 		FString projectPath_, TMap<FString, FString> jsonFiles_) {
// 		loginEmail = loginEmail_;
// 		loginPassword = loginPassword_;
// 		projectUName = projectUName_;
// 		urlWebsocket = urlWebsocket_;
// 		performanceQualityLevel = performanceQualityLevel_;
// 		projectPath = projectPath_;
// 		jsonFiles = jsonFiles_;
// 	};
// };

USTRUCT()
struct FSocketData {
	GENERATED_BODY()

	UPROPERTY()
	FString Route;
	UPROPERTY()
	TMap<FString, FString> Data;
	UPROPERTY()
	TMap<FString, FString> Auth;
};
