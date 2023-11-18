// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/TankHUD.h"

#include "UI/Scoreboard.h"

// Sets default values
ATankHUD::ATankHUD()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATankHUD::BeginPlay()
{
	Super::BeginPlay();

	// Load score board and hide it
	if(ScoreboardWidgetClass)
	{
		ScoreboardWidget = CreateWidget<UScoreboard>(GetOwningPlayerController(), ScoreboardWidgetClass);
		ScoreboardWidget->AddToViewport();
	}
}

// Called every frame
void ATankHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankHUD::ToggleScoreboardVisibility(const TArray<TObjectPtr<APlayerState>>& PlayerArray) const
{
	if(!ScoreboardWidget)
		return;

	if (ScoreboardWidget->GetVisibility() == ESlateVisibility::HitTestInvisible)
	{
		ScoreboardWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		ScoreboardWidget->InitScoreBoard(PlayerArray);
		ScoreboardWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

