// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CircleObjectSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL1_API UCircleObjectSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCircleObjectSpawner();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CircleSpawner")
	float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CircleSpawner")
	int ItemNumber;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CircleSpawner")
	TSubclassOf<AActor> ToSpawn;

private:
	UPROPERTY(EditANywhere, Category = "CircleSpawner")
	FVector Center;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Spawn();
};
