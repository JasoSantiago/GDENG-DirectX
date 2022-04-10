// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FIleLoader.generated.h"

/**
 * 
 */
UCLASS()
class FINALS2_API UFIleLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "Finals")
		static void loadFile(FString path, TArray<FString>&OutNames, TArray<int>&OutType, TArray<FVector>&OutPosition, TArray<FVector>& OutScale, TArray<FRotator>& OutRotation, TArray<bool>&OutRigidBody);
		UFUNCTION(BlueprintCallable, Category = "Finals")
		static void saveFile(TArray<AActor*> actors,TArray<bool> rb, FString filePath);
};
