#include "GrabberComponent.h"
#include "Engine/World.h"
#include "Kismet/Gameplaystatics.h"

UGrabberComponent::UGrabberComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PhysicsHandler = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("GrabberPhysicsHandler"));
}

void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPrimitiveComponent* GrabbedComponent = PhysicsHandler->GetGrabbedComponent();
	if (GrabbedComponent != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandler->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabberComponent::Grab()
{
	FHitResult HitResult;
	if (GetGrabbableInReach(HitResult))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetMobility(EComponentMobility::Movable);
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();

		PhysicsHandler->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

		if (GrabSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, GrabSound, GetComponentLocation());
		}
	}
}

void UGrabberComponent::Release()
{
	UPrimitiveComponent* GrabbedComponent = PhysicsHandler->GetGrabbedComponent();
	if (GrabbedComponent != nullptr)
	{
		GrabbedComponent->WakeAllRigidBodies();
		PhysicsHandler->ReleaseComponent();

		if (ReleaseSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ReleaseSound, GetComponentLocation());
		}
	}
}

void UGrabberComponent::Throw()
{
	UPrimitiveComponent* GrabbedComponent = PhysicsHandler->GetGrabbedComponent();
	if (GrabbedComponent != nullptr)
	{
		GrabbedComponent->WakeAllRigidBodies();
		PhysicsHandler->ReleaseComponent();
		GrabbedComponent->AddImpulse(GetComponentLocation() + GetForwardVector() * LaunchForce);

		if (LaunchSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetComponentLocation());
		}
	}
}

bool UGrabberComponent::GetGrabbableInReach(FHitResult& outHitResult) const
{
	FVector StartLocation = GetComponentLocation();;
	FVector EndLocation = StartLocation + GetForwardVector() * MaxGrabDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(outHitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, Sphere);
}

