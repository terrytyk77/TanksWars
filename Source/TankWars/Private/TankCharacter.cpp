// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCharacter.h"

#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATankCharacter::ATankCharacter()
	: CameraArmLength(1000.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
    ACharacter::SetReplicateMovement(true);
	
	// Create a camera boom (For more detailed camera control if needed)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraArmLength;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false; // Don't move the camera if player is under an object (ex: trees)
	CameraBoom->bInheritYaw = false; // Lock the camera to not turn with the player rotation

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach camera to the end of boom
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to the arm

	// Don't rotate when the controller rotates. 
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator{ 0.f, 540.f, 0.f };
}

void ATankCharacter::Fire_Implementation()
{
	if(const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName(FName("Muzzle")))
	{
		const FTransform SocketTransform = MuzzleSocket->GetSocketTransform(GetMesh());
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		
		if(UWorld* World = GetWorld())
		{
			World->SpawnActor<AProjectile>(
				ProjectileClass,
				SocketTransform.GetLocation(),
				SocketTransform.GetRotation().GetForwardVector().ToOrientationRotator(),
				SpawnParameters);
		}
	}
}

// Called when the game starts or when spawned
void ATankCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
