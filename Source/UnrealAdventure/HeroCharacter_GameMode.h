// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HeroCharacter_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALADVENTURE_API AHeroCharacter_GameMode : public AGameMode
{
	GENERATED_BODY()

		AHeroCharacter_GameMode();

	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> PlayerFuel;

	float Spawn_Z = 500.0f;
	
	UPROPERTY(EditAnywhere)
		float Spawn_X_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Max;

	void SpawnFuel();
};
