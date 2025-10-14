// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCTypes/SCStructTypes.h"
#include "ItemActor.generated.h"

class USphereComponent;
class ASCPlayerCharacter;

UCLASS()
class PROJECTSC_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:		
	AItemActor();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void SetItemInfo(const FSCItemStructure& InItemInfo);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ItemMesh;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server,Reliable)
	void ServerPickupItem(ASCPlayerCharacter* PlayerCharacter);


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> PickupRange;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	FSCItemStructure ItemInfo;

	bool bPickUp = false;

};
