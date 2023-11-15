// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;	
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(FName("Click"), EInputEvent::IE_Released, this, &ATankPlayerController::MoveToMouseLocation);
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
