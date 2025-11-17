// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponentBase.h"
#include "DataAssets/CharacterCustomize.h"
#include "DataAssets/Items/ArmorItemInfo.h"
#include "Characters/SCCharacterBase.h"
#include "Engine/SkinnedAssetCommon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Items/Equipments/Weapons/SCWeaponBase.h"
#include "Items/Equipments/SCEquippableBase.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "SCDebugHelper.h"
#include "SCTypes/SCStructTypes.h"
#include "DataAssets/Items/WeaponItemInfo.h"
#include "AnimInstances/SCAnimInstanceBase.h"
#include "AbilitySystem/Data/StartupDataBase.h"
#include "Components/Inventory/InventoryComponent.h"
#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SCAbilitySystemLibrary.h"
#include "GameplayCueFunctionLibrary.h"
#include "SCFunctionLibrary.h"

UPawnCombatComponentBase::UPawnCombatComponentBase()
{
	SetIsReplicatedByDefault(true);

}

void UPawnCombatComponentBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_AutonomousProxy || GetOwnerRole() == ROLE_SimulatedProxy)
	{
		OnRep_EquippedArmors();
	}

}

void UPawnCombatComponentBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPawnCombatComponentBase, CurrentEquippedWeaponTag);
	DOREPLIFETIME(UPawnCombatComponentBase, EquippedWeapons);
	DOREPLIFETIME(UPawnCombatComponentBase, EquippedArmors);

}

void UPawnCombatComponentBase::CheckOwnerCharacter()
{
	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<ASCCharacterBase>(GetOwner());
	}
	check(OwnerCharacter);
}

//Armor
void UPawnCombatComponentBase::Server_EquipArmor(UArmorItemInfo* ArmorInfo)
{
	if (!ArmorInfo) return;
	CheckOwnerCharacter();

	FEquippedArmorEntry Entry;
	Entry.EquipSocket = ArmorInfo->EquipSocket;
	Entry.ArmorMesh = ArmorInfo->ArmorMesh;
	

	int32 Idx = EquippedArmors.Items.IndexOfByPredicate([&] (const FEquippedArmorEntry & E)
	{
		return E.EquipSocket == Entry.EquipSocket;
	});

	if (Idx != INDEX_NONE)
	{
		EquippedArmors.Items[Idx] = Entry;
		EquippedArmors.MarkItemDirty(EquippedArmors.Items[Idx]);
	}
	else
	{
		EquippedArmors.Items.Add(Entry);
		EquippedArmors.MarkItemDirty(EquippedArmors.Items.Last());
	}

	EquipArmor(ArmorInfo);

}

void UPawnCombatComponentBase::EquipArmor(UArmorItemInfo* ArmorInfo)
{
	CheckOwnerCharacter();
	if (USkeletalMesh* ArmorMesh = ArmorInfo->ArmorMesh.LoadSynchronous())
	{
		if (USkeletalMeshComponent* EquippedMesh = OwnerCharacter->GetMeshByTag(ArmorInfo->EquipSocket))
		{
			EquippedMesh->SetSkeletalMeshAsset(ArmorMesh);

			for (const FSkeletalMaterial& Material : ArmorMesh->GetMaterials())
			{
				if (OwnerCharacter->GetCharacterCustomizeData()->MaterialMap.Contains(Material.MaterialSlotName))
				{
					EquippedMesh->SetMaterialByName(Material.MaterialSlotName, OwnerCharacter->GetCharacterCustomizeData()->MaterialMap.FindRef(Material.MaterialSlotName));
				}
				else
				{
					EquippedMesh->SetMaterialByName(Material.MaterialSlotName, Material.MaterialInterface);

				}
			}
		}
	}
}

void UPawnCombatComponentBase::OnRep_EquippedArmors()
{

	CheckOwnerCharacter();
	UpdateEquippedArmors();

}

void UPawnCombatComponentBase::UpdateEquippedArmors()
{
	for (const FEquippedArmorEntry& Entry : EquippedArmors.Items)
	{
		if (USkeletalMesh* ArmorMesh = Entry.ArmorMesh.LoadSynchronous())
		{
			if (USkeletalMeshComponent* EquippedMesh = OwnerCharacter->GetMeshByTag(Entry.EquipSocket))
			{

				EquippedMesh->SetSkeletalMeshAsset(ArmorMesh);

				for (const FSkeletalMaterial& Material : ArmorMesh->GetMaterials())
				{
					if (OwnerCharacter->GetCharacterCustomizeData()->MaterialMap.Contains(Material.MaterialSlotName))
					{
						EquippedMesh->SetMaterialByName(Material.MaterialSlotName, OwnerCharacter->GetCharacterCustomizeData()->MaterialMap.FindRef(Material.MaterialSlotName));
					}
					else
					{
						EquippedMesh->SetMaterialByName(Material.MaterialSlotName, Material.MaterialInterface);

					}
				}
			}


		}
	}
}

bool FEquippedArmorArray::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
{
	return FFastArraySerializer::FastArrayDeltaSerialize<FEquippedArmorEntry, FEquippedArmorArray>(Items, DeltaParams, *this);
}


//Weapon
ASCWeaponBase* UPawnCombatComponentBase::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	for (const FEquippedWeaponEntry& Entry : EquippedWeapons.Items)
	{
		if (Entry.EquipSocket == InWeaponTagToGet)
		{
			return Entry.Weapon;
		}
	}
	return nullptr;
}

ASCWeaponBase* UPawnCombatComponentBase::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterCarriedWeaponByTag(FSCGameplayTags::Get().EquippableSocket_RightHand);
}

//Equip
void UPawnCombatComponentBase::RegisterSpawnedWeapon(ASCWeaponBase* InWeaponToRegister,const FGameplayTag WeaponTag, bool bRegisterAsEquippedWeapon)
{
	check(InWeaponToRegister);

	FEquippedWeaponEntry NewEntry;
	NewEntry.EquipSocket = WeaponTag;
	NewEntry.Weapon = InWeaponToRegister;
	EquippedWeapons.Items.Add(NewEntry);
	EquippedWeapons.MarkItemDirty(NewEntry);

	if (bRegisterAsEquippedWeapon && WeaponTag == FSCGameplayTags::Get().EquippableSocket_RightHand)
	{
		CurrentEquippedWeaponTag = WeaponTag;
		ServerSetCurrentEquippedWeaponTag(WeaponTag);
	}
	
}

void UPawnCombatComponentBase::SpawnAndEquipWeapon_Implementation(UWeaponItemInfo* WeaponInfo, FGuid Guid)
{		
	if (TSubclassOf<ASCWeaponBase> WeaponClass = WeaponInfo->PlayerWeaponClass.LoadSynchronous())
	{
		ASCWeaponBase* SpawndWeapon = GetWorld()->SpawnActor<ASCWeaponBase>(WeaponClass, FTransform(), FActorSpawnParameters());

		FEquippedWeaponEntry Entry;
		Entry.EquipSocket = WeaponInfo->EquipSocket;
		Entry.Weapon = SpawndWeapon;
		Entry.WeaponInfo = WeaponInfo;
		int32 Idx = EquippedWeapons.Items.IndexOfByPredicate([&](const FEquippedWeaponEntry& E)
		{
			return E.EquipSocket == Entry.EquipSocket;
		});

		if (Idx != INDEX_NONE)
		{
			EquippedWeapons.Items[Idx] = Entry;
			EquippedWeapons.MarkItemDirty(EquippedWeapons.Items[Idx]);
		}
		else
		{
			EquippedWeapons.Items.Add(Entry);
			EquippedWeapons.MarkItemDirty(EquippedWeapons.Items.Last());
		}

		CheckOwnerCharacter();

		FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, true);
		SpawndWeapon->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentRule, WeaponInfo->SocketToEquip);
		SpawndWeapon->WeaponGuid = Guid;
		RegisterSpawnedWeapon(SpawndWeapon, WeaponInfo->EquipSocket, true);
		if (!WeaponInfo->LightAttackMontages.IsEmpty())
		{
			OwnerCharacter->SetLightAttackMontages(WeaponInfo->LightAttackMontages);
		}

		if (!WeaponInfo->HeavyAttackMontages.IsEmpty())
		{
			OwnerCharacter->SetHeavyAttackMontages(WeaponInfo->HeavyAttackMontages);
		}

		TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
		Cast<USCAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent())->GrantWeaponAbilities(WeaponInfo->DefaultWeaponAbilities,1, GrantedAbilities);
		SpawndWeapon->AssignGrantedAbilitySpecHandles(GrantedAbilities);
		SpawndWeapon->OnEquipWeapon();
		SpawndWeapon->OwnerCharacter = OwnerCharacter;
		if (WeaponInfo->WeaponAnimLayerToLink != nullptr)
		{
			if (WeaponInfo->WeaponAnimLayerToLink.LoadSynchronous())
			{
				MulticastSetWeaponAnimLayer(WeaponInfo->WeaponAnimLayerToLink.Get());
			}

		}
	}
}

//Unequip
void UPawnCombatComponentBase::UnequipAndDestroyWeapon_Implementation(const FGameplayTag& EquippedSocket)
{
	CheckOwnerCharacter();
	ASCWeaponBase* CurrentEquippedWeapon = GetCharacterCarriedWeaponByTag(EquippedSocket);
	CurrentEquippedWeapon->OnUnequipWeapon();

	const int32 Idx = EquippedWeapons.Items.IndexOfByPredicate([&](const FEquippedWeaponEntry& E) 
	{
		return E.EquipSocket == EquippedSocket;
	});

	if (Idx == INDEX_NONE) return;

	EquippedWeapons.MarkItemDirty(EquippedWeapons.Items[Idx]);
	
	if (EquippedWeapons.Items[Idx].Weapon)
	{
		TArray<FGameplayAbilitySpecHandle> GrantedAbilities = EquippedWeapons.Items[Idx].Weapon->GetGrantedAbilitySpecHandles();
		Cast<USCAbilitySystemComponent>(OwnerCharacter->GetAbilitySystemComponent())->RemoveGrantedPlayerWeaponAbilities(GrantedAbilities);
		EquippedWeapons.Items[Idx].Weapon->Destroy();
	}

	EquippedWeapons.Items.RemoveAt(Idx);


	if (UStartupDataBase* CharacterStartupData = OwnerCharacter->GetCharacterStartupData().LoadSynchronous())
	{
		if (CharacterStartupData->DefaultAnimLayerToLink.LoadSynchronous())
		{
			MulticastSetWeaponAnimLayer(CharacterStartupData->DefaultAnimLayerToLink.Get());

		}
		OwnerCharacter->SetLightAttackMontages(CharacterStartupData->LightAttackMontages);
		OwnerCharacter->SetHeavyAttackMontages(CharacterStartupData->HeavyAttackMontages);
	}	
}


void UPawnCombatComponentBase::ServerSetCurrentEquippedWeaponTag_Implementation(FGameplayTag NewTag)
{
	CurrentEquippedWeaponTag = NewTag;
}

void UPawnCombatComponentBase::MulticastSetWeaponAnimLayer_Implementation(TSubclassOf<USCAnimInstanceBase> AnimLayer)
{
	CheckOwnerCharacter();
	OwnerCharacter->GetMesh()->LinkAnimClassLayers(AnimLayer);
	
}

bool FEquippedWeaponArray::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
{
	return FFastArraySerializer::FastArrayDeltaSerialize<FEquippedWeaponEntry, FEquippedWeaponArray>(Items, DeltaParams, *this);
}

//Attack
void UPawnCombatComponentBase::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		ASCWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
		check(WeaponToToggle);
		CheckOwnerCharacter();
		OverlappedActors.Empty();
		OverlappedActors.AddUnique(OwnerCharacter);


		if (bShouldEnable)
		{
			GetWorld()->GetTimerManager().SetTimer(WeaponTraceTimer, this, &ThisClass::MeleeAttackTrace, 0.01f, true);

		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(WeaponTraceTimer);
			OverlappedActors.Empty();

		}
	}

}

void UPawnCombatComponentBase::MeleeAttackTrace()
{
	ASCWeaponBase* EquippedWeapon = GetCharacterCurrentEquippedWeapon();
	if (PrevBoxLocation.IsZero())
	{
		PrevBoxLocation = EquippedWeapon->GetWeaponCollisionBox()->GetComponentLocation();
		return;
	}
	TArray<FHitResult> HitResults;

	FCollisionQueryParams CQP;		
	CQP.AddIgnoredActors(OverlappedActors);
	
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		PrevBoxLocation,
		EquippedWeapon->GetWeaponCollisionBox()->GetComponentLocation(),
		EquippedWeapon->GetWeaponCollisionBox()->GetComponentQuat(),
		ECC_Visibility,
		FCollisionShape::MakeBox(EquippedWeapon->GetWeaponCollisionBox()->GetScaledBoxExtent()),
		CQP

	);
	//DrawDebugLine(
	//	GetWorld(),
	//	PrevBoxLocation,
	//	EquippedWeapon->GetWeaponCollisionBox()->GetComponentLocation(),
	//	FColor::Red,
	//	false,
	//	2
	//);
	if (bHit)
	{
		for (const FHitResult& HitResalt : HitResults)
		{
			//if (OverlappedActors.Contains(HitResalt.GetActor())) continue;
			//Debug::Print(HitResalt.GetActor()->GetName());			
			//DrawDebugSphere(GetWorld(), HitResalt.ImpactPoint, 15, 1, FColor::White, false, 3, 0, 1);
			if (UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResalt.GetActor()))				
			{
				FGameplayEventData Data;
				Data.Instigator = OwnerCharacter;
				Data.Target = HitResalt.GetActor();

				FGameplayAbilityTargetDataHandle TargetDataHandle;
				TargetDataHandle.Add(new FGameplayAbilityTargetData_SingleTargetHit(HitResalt));
				Data.TargetData = TargetDataHandle;

				const bool bIsTargetBlocking = USCFunctionLibrary::DoesActorHaveTag(HitResalt.GetActor(), FSCGameplayTags::Get().Shared_State_Block);
				bool bIsValidBlock = false;
				if (bIsTargetBlocking)
				{
					bIsValidBlock = USCFunctionLibrary::IsValidBlock(OwnerCharacter, HitResalt.GetActor());
				}
				if (bIsValidBlock)
				{
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitResalt.GetActor(), FSCGameplayTags::Get().Event_SuccessfulBlock, Data);
				}
				else
				{
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerCharacter, FSCGameplayTags::Get().Event_MeleeHit, Data);
					UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(HitResalt.GetActor(), FSCGameplayTags::Get().GameplayCue_Sound_Hit_Monster, FGameplayCueParameters());
				}
			}
			OverlappedActors.AddUnique(HitResalt.GetActor());

		}
	}
	PrevBoxLocation = EquippedWeapon->GetWeaponCollisionBox()->GetComponentLocation();

}

void UPawnCombatComponentBase::Parry()
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter))
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FSCGameplayTags::Get().Shared_Ability_Parry);
		ASC->TryActivateAbilitiesByTag(TagContainer);
	}

}
void UPawnCombatComponentBase::OnParried()
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter))
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(FSCGameplayTags::Get().Event_Parried);
		ASC->TryActivateAbilitiesByTag(TagContainer);
	}

}

void UPawnCombatComponentBase::MeleeAttackTraceWithRange(const FVector& Attacklocation, float Radius)
{
	CheckOwnerCharacter();
	bool bHit;
	TArray<AActor*> OverlappingActors;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.AddUnique(OwnerCharacter);

	USCAbilitySystemLibrary::GetLiveCharactersWithinRadius(this, OverlappingActors, IgnoreActors, Radius, Attacklocation);
	//DrawDebugSphere(GetWorld(), Attacklocation, Radius, 12, FColor::Red, false, 3);
	for (AActor* OverlappingActor : OverlappingActors)
	{
		bHit = true;
		if (UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OverlappingActor))
		{
			FGameplayEventData Data;
			Data.Instigator = OwnerCharacter;
			Data.Target = OverlappingActor;

			const bool bIsTargetBlocking = USCFunctionLibrary::DoesActorHaveTag(OverlappingActor, FSCGameplayTags::Get().Shared_State_Block);
			bool bIsValidBlock = false;
			if (bIsTargetBlocking)
			{
				bIsValidBlock = USCFunctionLibrary::IsValidBlock(OwnerCharacter, OverlappingActor);
			}
			if (bIsValidBlock)
			{
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OverlappingActor, FSCGameplayTags::Get().Event_SuccessfulBlock, Data);
			}
			else
			{
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerCharacter, FSCGameplayTags::Get().Event_MeleeHit, Data);
				UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(OverlappingActor, FSCGameplayTags::Get().GameplayCue_Sound_Hit_Monster, FGameplayCueParameters());
			}
		}
	}

}

