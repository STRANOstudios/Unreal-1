// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UWaypointMovementComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class UNREAL1_API UUWaypointMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUWaypointMovementComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Waypoint_Component", meta = (MakeEditWidget = true))
	TArray<FTransform> Waypoints;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Waypoint_Component")
	float DesiredDuration;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Waypoint|Runtime")
	FTransform StartPosition;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Waypoint|Runtime")
	float ElapsedTime;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Waypoint|Runtime")
	float PercentageComplete;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Waypoint|Runtime")
	int CurrentIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoint", meta = (UseComponentPicker, AllowedClasses = "SceneComponent"))
	USceneComponent* RootComp = nullptr;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Waypoint") 
	float PercentageClamped(float From, float To);

	UFUNCTION(BlueprintCallable, Category = "Waypoint") 
	FTransform Lerp(const FTransform& transformStart, const FTransform& transformEnd, float alpha);

	virtual void OnRegister() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void DrawEditorGizmos() const;
};
