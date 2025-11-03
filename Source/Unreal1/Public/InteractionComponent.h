// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL1_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();


	//** Trace Interaction Distance
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FPS_Character")
	float DistanceInteraction = 1500.f;

	//** Radius Interaction Distance
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FPS_Character")
	float RadiusInteraction = 400.f;

	//** Objects types
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FPS_Character")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesToInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FPS_Character_Debug")
	bool bDebugInteraction = false;

	//** Character Name
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FPS_Character_Debug")
	FString CharacterName = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FPS_Character_Debug")
	float RadiusDetectInteractable = 200.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//** ActorToIgnore
	UPROPERTY(EditAnywhere, Category = "FPS_Character")
	TArray<AActor*> ActorsToIgnore;

	//** ActorToIgnore
	UPROPERTY(EditAnywhere, Category = "FPS_Character_Debug")
	TArray<AActor*> ActorsFound;

	UPROPERTY(EditAnywhere, Category = "FPS_Character_Debug")
	AActor* ClosestActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Interaction Trace Objects
	UFUNCTION(BlueprintCallable, Category = "FPS_Character")
	TArray<AActor*> InteractionTraceObjects(const float Distance, const float Radius);

		
};
