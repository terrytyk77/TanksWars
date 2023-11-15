// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TankCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TANKWARS_API ATankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/** Returns CameraBoom sub-object */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera sub-object */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/** Camera boom positioning the camera on top of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;
	/** Camera that follows the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Components", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;
	/** The distance from the camera to the focus point */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta=(AllowPrivateAccess="true"))
	float CameraArmLength = 1000.0f;
};