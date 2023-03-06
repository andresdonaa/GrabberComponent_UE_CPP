#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"

class USoundBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRABBERUECPP_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UGrabberComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Throw();

private:
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;

private:
	UPROPERTY(EditAnywhere, Category = "Grabber Configuration")
	float MaxGrabDistance = 400;

	UPROPERTY(EditAnywhere, Category = "Grabber Configuration")
	float GrabRadius = 100;

	UPROPERTY(EditAnywhere, Category = "Grabber Configuration")
	float HoldDistance = 200;

	UPROPERTY(EditAnywhere, Category = "Grabber Configuration")
	float LaunchForce = 300000;

	UPROPERTY(EditAnywhere, Category = "Grabber Configuration")
	USoundBase* GrabSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Grabber Configuration")
	USoundBase* ReleaseSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Grabber Configuration")
	USoundBase* LaunchSound = nullptr;

	UPhysicsHandleComponent* PhysicsHandler = nullptr;
};
