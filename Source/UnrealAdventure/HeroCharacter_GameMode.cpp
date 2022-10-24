// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter_GameMode.h"
#include "GameFramework/Actor.h"

AHeroCharacter_GameMode::AHeroCharacter_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHeroCharacter_GameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnFuel();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AHeroCharacter_GameMode::SpawnFuel, FMath::RandRange(2, 5), true);
}

void AHeroCharacter_GameMode::StartPlay()
{
	Super::StartPlay();
	SpawnFuel();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AHeroCharacter_GameMode::SpawnFuel, FMath::RandRange(2, 5), true);
}

void AHeroCharacter_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHeroCharacter_GameMode::SpawnFuel()
{
	
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("spawned"));
	
	GetWorld()->SpawnActor(PlayerFuel, &SpawnPosition, &SpawnRotation);
}
