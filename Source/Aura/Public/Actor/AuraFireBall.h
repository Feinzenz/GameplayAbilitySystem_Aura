// Copyright Vinzenz Landl

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraProjectile.h"
#include "AuraFireBall.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraFireBall : public AAuraProjectile
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void StartOutgoingTimeline();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> ReturnActor;
	
	UPROPERTY(BlueprintReadWrite)
	FDamageEffectParams ExplosionDamageParams;
protected:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnHit() override;
	
	UFUNCTION(BlueprintCallable)
	void EmptyIgnoreList();
 
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> IgnoreList;
};
