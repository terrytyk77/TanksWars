// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TankHUD.generated.h"

class UScoreboard;

UCLASS()
class TANKWARS_API ATankHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATankHUD();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void ToggleScoreboardVisibility(const TArray<TObjectPtr<APlayerState>>& PlayerArray) const;

	FORCEINLINE UScoreboard* GetScoreboardWidget() const { return ScoreboardWidget; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	UScoreboard* ScoreboardWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UScoreboard> ScoreboardWidgetClass;
};
