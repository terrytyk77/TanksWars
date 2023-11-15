// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
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
	
	const FVector NewDestination = MouseHitResult.Location;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *NewDestination.ToString())

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NewDestination);
}
