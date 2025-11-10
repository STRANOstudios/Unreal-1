// Fill out your copyright notice in the Description page of Project Settings.


#include "UWaypointMovementComponent.h"

// Sets default values for this component's properties
UUWaypointMovementComponent::UUWaypointMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUWaypointMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		if (USceneComponent* RC = Owner->GetRootComponent())
		{
			StartPosition = RC->GetRelativeTransform();
			RootComp = RC;
		}
	}

	if (Waypoints.Num() == 0)
	{
		SetComponentTickEnabled(false);
		return;
	}

	if (CurrentIndex < 0 || CurrentIndex >= Waypoints.Num())
	{
		CurrentIndex = 0;
	}

	// convert waypoint from global to relative
}


// Called every frame
void UUWaypointMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!RootComp || Waypoints.Num() == 0 || DesiredDuration <= 0.f)
	{
		return;
	}

	ElapsedTime += DeltaTime;
	PercentageComplete = FMath::Clamp(ElapsedTime / DesiredDuration, 0.f, 1.f);

	const FTransform& Start = StartPosition;
	const FTransform& Target = Waypoints[CurrentIndex];

	const FTransform NewTf = Lerp(Start, Target, PercentageComplete);
	RootComp->SetRelativeTransform(NewTf);

	if (PercentageComplete < 1.f)
	{
		return;
	}

	StartPosition = Target;
	ElapsedTime = 0.f;
	PercentageComplete = 0.f;

	++CurrentIndex;
	if (CurrentIndex >= Waypoints.Num())
	{
		CurrentIndex = 0; // loop
	}
}

float UUWaypointMovementComponent::PercentageClamped(float A, float B)
{
	if (B <= 0.f)
	{
		return 1.f;
	}
	return FMath::Clamp(A / B, 0.f, 1.f);
}

FTransform UUWaypointMovementComponent::Lerp(const FTransform& From, const FTransform& To, float Alpha)
{
	const FVector Loc = FMath::Lerp(From.GetLocation(), To.GetLocation(), Alpha);
	const FVector Scale = FMath::Lerp(From.GetScale3D(), To.GetScale3D(), Alpha);
	const FQuat   Rot = FQuat::Slerp(From.GetRotation(), To.GetRotation(), Alpha).GetNormalized();
	return FTransform(Rot, Loc, Scale);
}

#pragma region Draw Debug

void UUWaypointMovementComponent::OnRegister()
{
	Super::OnRegister();
#if WITH_EDITOR
	DrawEditorGizmos();
#endif
}

#if WITH_EDITOR
void UUWaypointMovementComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	DrawEditorGizmos();
}
#endif

void UUWaypointMovementComponent::DrawEditorGizmos() const
{
//	UWorld* World = GetWorld();
//	if (!World) return;
//
//#if WITH_EDITOR
//	if (World->WorldType != EWorldType::Editor) return; // solo in editor, non in PIE
//#endif
//
//	// Pulisci i vecchi disegni persistenti di questo world
//	FlushPersistentDebugLines(World);
//
//	// Se i Waypoint sono RELATIVI al Root, trasformali in world
//	const USceneComponent* Root = GetOwner() ? GetOwner()->GetRootComponent() : nullptr;
//	const FTransform RootTf = Root ? Root->GetComponentTransform() : FTransform::Identity;
//
//	for (int32 i = 0; i < Waypoints.Num(); ++i)
//	{
//		const FTransform WpTfWorld = RootTf * Waypoints[i];
//		const FVector P = WpTfWorld.GetLocation();
//
//		DrawDebugSphere(World, P, 25.f, 12, FColor::Yellow,
//			/*bPersistentLines=*/true, /*LifeTime=*/0.f, /*DepthPriority=*/0, /*Thickness=*/1.5f);
//
//		if (i + 1 < Waypoints.Num())
//		{
//			const FVector Q = (RootTf * Waypoints[i + 1]).GetLocation();
//			DrawDebugLine(World, P, Q, FColor::Green,
//				/*bPersistentLines=*/true, /*LifeTime=*/0.f, /*DepthPriority=*/0, /*Thickness=*/2.f);
//		}
//	}
}

#pragma endregion