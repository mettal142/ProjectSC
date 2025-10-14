// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
struct FSCGameplayTags
{
public:
	static const FSCGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();


	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_StaminaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxStamina;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look;
	FGameplayTag InputTag_MainAction;
	FGameplayTag InputTag_SubAction;
	FGameplayTag InputTag_DodgeRoll;
	FGameplayTag InputTag_Block;
	FGameplayTag InputTag_Interaction_1;
	FGameplayTag InputTag_Interaction_2;
	FGameplayTag InputTag_Interaction_3;
	FGameplayTag InputTag_Wheel_Up;
	FGameplayTag InputTag_Wheel_Down;
	FGameplayTag InputTag_Wheel_Click;

	FGameplayTag InputTag_QuickSlot_1;
	FGameplayTag InputTag_QuickSlot_2;
	FGameplayTag InputTag_QuickSlot_3;
	FGameplayTag InputTag_QuickSlot_4;
	FGameplayTag InputTag_QuickSlot_5;
	FGameplayTag InputTag_QuickSlot_6;
	FGameplayTag InputTag_QuickSlot_7;
	FGameplayTag InputTag_QuickSlot_8;
	FGameplayTag InputTag_QuickSlot_9;
	FGameplayTag InputTag_QuickSlot_0;

	FGameplayTag InputTag_UI_Inventory;
	FGameplayTag InputTag_UI_Crafting;
	
	FGameplayTag Event_Montage_AttackEnd;
	FGameplayTag Event_MeleeHit;



	FGameplayTag Shared_Ability_UseItem;
	FGameplayTag Shared_Ability_Equip_Weapon;
	FGameplayTag Shared_Ability_Unequip_Weapon;
	FGameplayTag Shared_Ability_Equip_Armor;
	FGameplayTag Shared_Ability_Unequip_Armor;
	FGameplayTag Shared_Ability_MeleeHit;


	FGameplayTag Player_Ability_LightAttack;
	FGameplayTag Player_Ability_HeavyAttack;
	FGameplayTag Player_Ability_HitPose;
	FGameplayTag Player_Ability_Roll;
	FGameplayTag Player_Ability_Block;
	FGameplayTag Player_Ability_TargetLock;
	FGameplayTag Player_Ability_Equip_Weapon;
	FGameplayTag Player_Ability_Build;

	FGameplayTag Player_Montage_1H_Sword_LightAttack_01;
	FGameplayTag Player_Montage_1H_Sword_LightAttack_02;
	FGameplayTag Player_Montage_1H_Sword_LightAttack_03;


	FGameplayTag Enemy_Ability_LightAttack;



	FGameplayTag Shared_State_Dead;
	FGameplayTag Shared_State_ComboCount;

	
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	FGameplayTag Effects_HitReact;

	FGameplayTag EquippableSocket_Head;
	FGameplayTag EquippableSocket_Helmet;
	FGameplayTag EquippableSocket_Tabard;
	FGameplayTag EquippableSocket_Belt;
	FGameplayTag EquippableSocket_Boots;
	FGameplayTag EquippableSocket_Bracers;
	FGameplayTag EquippableSocket_Cape;
	FGameplayTag EquippableSocket_Chest;
	FGameplayTag EquippableSocket_Feet;
	FGameplayTag EquippableSocket_Ears;
	FGameplayTag EquippableSocket_Hair;
	FGameplayTag EquippableSocket_Hands;
	FGameplayTag EquippableSocket_Legs;
	FGameplayTag EquippableSocket_Skirt;
	FGameplayTag EquippableSocket_Brows;
	FGameplayTag EquippableSocket_Beard;
	FGameplayTag EquippableSocket_RightHand;
	FGameplayTag EquippableSocket_LeftHand;
	
	
	FGameplayTag Item_Equippable_Armor;
	FGameplayTag Item_Equippable_Weapon_1H_Sword;
	FGameplayTag Item_Equippable_Weapon_1H_Axe;
	FGameplayTag Item_Equippable_Weapon_1H_PickAxe;
	FGameplayTag Item_Equippable_Weapon_2H_Sword;
	FGameplayTag Item_Equippable_Weapon_2H_Axe;
	FGameplayTag Item_Equippable_Weapon_2H_PickAxe;

	FGameplayTag Item_Resource;
	FGameplayTag Item_Consumable;
	FGameplayTag Item_Buildablel;

	FGameplayTag GameplayCue_Sound_Hit_Wood;
	FGameplayTag GameplayCue_Sound_Hit_Stone;
	FGameplayTag GameplayCue_Sound_Hit_Monster;
	FGameplayTag GameplayCue_Sound_Block;

	FGameplayTag GameplayCue_Effect_Hit_Wood;
	FGameplayTag GameplayCue_Effect_Hit_Stone;
	FGameplayTag GameplayCue_Effect_Hit_Monster;
	FGameplayTag GameplayCue_Effect_Block;


	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

private:
	static FSCGameplayTags GameplayTags;
};