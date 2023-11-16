// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "NiagaraFunctionLibrary.h"
#include "TankCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;	
}

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(FName("Click"), EInputEvent::IE_Released, this, &ThisClass::MoveToMouseLocation);
	InputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ThisClass::Fire);
}

void ATankPlayerController::MoveToMouseLocation()
{
	FHitResult MouseHitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, MouseHitResult);
	
	if(MouseHitResult.bBlockingHit)
	{
		const FVector LocationToMoveTo = MouseHitResult.Location;
		// Move the character to the new location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, LocationToMoveTo);
		// Spawn mouse move-to particle effect
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, LocationToMoveTo);
	}
}

void ATankPlayerController::Fire()
{
	if(APawn* PlayerPawn = GetPawn())
	{
		if(ATankCharacter* TankCharacter = Cast<ATankCharacter>(PlayerPawn))
		{
			TankCharacter->Fire();
		}
	}
}
