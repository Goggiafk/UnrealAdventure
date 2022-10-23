// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Blueprint/UserWidget.h"

#include "HeroCharacter.generated.h"

UCLASS()
class UNREALADVENTURE_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	UPROPERTY(EditAnywhere)
	UAnimMontage* DashMontage;

	bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Burning;

	UPROPERTY(EditAnywhere)
		float Burning_Treshold = 3.0f;

	UFUNCTION()
		void OnBeingOverlap(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, Category = "UI_HUD")
		TSubclassOf<UUserWidget> Hero_Fuel_Widget_Class;
	UUserWidget* Hero_Fuel_Widget;

	void RestartScene();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartRunning();
	void StopRunning();
	float WalkSpeed = 600.0f;
	float RunSpeed = 1000.0f;

	void Dashing();
	float DashDistance = 3000.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
