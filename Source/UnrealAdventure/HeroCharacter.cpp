// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "Particles/ParticleEmitter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 1.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bDead = false;
	Burning = 100.0f;
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHeroCharacter::OnBeingOverlap);

	if(Hero_Fuel_Widget_Class != nullptr)
	{
		Hero_Fuel_Widget = CreateWidget(GetWorld(), Hero_Fuel_Widget_Class);
		Hero_Fuel_Widget->AddToViewport();
	}
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Burning -= DeltaTime * Burning_Treshold;

	if(Burning <= 0)
	{
		if(!bDead)
		{
			bDead = true;
			
			GetMesh()->SetSimulatePhysics(true);
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &AHeroCharacter::RestartScene, 3.0f, false);
			
		}
	}
}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHeroCharacter::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AHeroCharacter::StopRunning);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AHeroCharacter::Dashing);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHeroCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
}

void AHeroCharacter::MoveForward(float Axis)
{
	if(!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void AHeroCharacter::MoveRight(float Axis)
{
	if(!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void AHeroCharacter::StartRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	Burning_Treshold = 10.0f;
}

void AHeroCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	Burning_Treshold = 3.0f;
}

void AHeroCharacter::Dashing()
{
	Burning -= 5.0f;
	const FVector ForwardDirection = this->GetActorRotation().Vector();
	LaunchCharacter(ForwardDirection * DashDistance, true, true);
	if(DashMontage)
	{
		PlayAnimMontage(DashMontage, 1, NAME_None);
	}
}

void AHeroCharacter::OnBeingOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(OtherActor->ActorHasTag("Fuel"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Fueled!"))
		
		Burning += 10.0f;

		if(Burning > 100.0f)
			Burning = 100.0f;
		
		OtherActor->Destroy();
	}
	
}

void AHeroCharacter::RestartScene()
{
	
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	
}



