// Fill out your copyright notice in the Description page of Project Settings.


#include "SCGameplayTags.h"
#include "GameplayTagsManager.h"

FSCGameplayTags FSCGameplayTags::GameplayTags;

void FSCGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Attributes
	 */
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("Amount of Health regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("Amount of Mana regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_StaminaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.StaminaRegeneration"),FString("Amount of Stamina regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("Maximum amount of Health obtainable"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("Maximum amount of Mana obtainable"));
	GameplayTags.Attributes_Secondary_MaxStamina= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Stamina"),FString("Maximum amount of Mana obtainable"));
	
	/*
	 * Input Tag
	 */
	GameplayTags.InputTag_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Move"), FString("Input Tag for Move"));
	GameplayTags.InputTag_Look = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Look"), FString("Input Tag for Look"));
	GameplayTags.InputTag_MainAction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.MainAction"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_SubAction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SubAction"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_DodgeRoll = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.DodgeRoll"), FString("Input Tag for DodgeRoll"));
	GameplayTags.InputTag_SwitchTarget = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SwitchTarget"), FString("Input Tag for SwitchTarget"));
	GameplayTags.InputTag_Interaction_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Interaction.1"), FString("Input Tag for Interaction 1"));
	GameplayTags.InputTag_Interaction_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Interaction.2"), FString("Input Tag for Interaction 2"));
	GameplayTags.InputTag_Interaction_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Interaction.3"), FString("Input Tag for Interaction 3"));
	GameplayTags.InputTag_Wheel_Up = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Wheel.Up"), FString("Input Tag for InputTag Wheel Up"));
	GameplayTags.InputTag_Wheel_Down = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Wheel.Down"), FString("Input Tag for InputTag Wheel Down"));
	GameplayTags.InputTag_Wheel_Click = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Wheel.Click"), FString("Input Tag for InputTag Wheel Click"));
	

	GameplayTags.InputTag_Hold = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Hold"), FString("Holding Input Tag"));
	GameplayTags.InputTag_Hold_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Hold.Block"), FString("Holding Input Tag for Block"));
	GameplayTags.InputTag_Hold_Interaction_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Hold.Interaction.1"), FString("Holding Input Tag for Interaction 1"));
	GameplayTags.InputTag_Hold_Interaction_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Hold.Interaction.2"), FString("Holding Input Tag for Interaction 2"));
	GameplayTags.InputTag_Hold_Interaction_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Hold.Interaction.3"), FString("Holding Input Tag for Interaction 3"));
	GameplayTags.InputTag_Hold_MainAction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Hold.MainAction"), FString("Holding Input Tag for MainAction"));
	GameplayTags.InputTag_Hold_SubAction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Hold.SubAction"), FString("Holding Input Tag for SubAction"));
	
	GameplayTags.InputTag_Toggle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Toggle"), FString("Holding Input Tag for Toggle"));
	GameplayTags.InputTag_Toggle_TargetLock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Toggle.TargetLock"), FString("Holding Input Tag for TargetLock"));
	
	
	
	
	GameplayTags.InputTag_QuickSlot_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.1"), FString("Input Tag for QuickSlot1"));
	GameplayTags.InputTag_QuickSlot_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.2"), FString("Input Tag for QuickSlot2"));
	GameplayTags.InputTag_QuickSlot_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.3"), FString("Input Tag for QuickSlot3"));
	GameplayTags.InputTag_QuickSlot_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.4"), FString("Input Tag for QuickSlot4"));
	GameplayTags.InputTag_QuickSlot_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.5"), FString("Input Tag for QuickSlot5"));
	GameplayTags.InputTag_QuickSlot_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.6"), FString("Input Tag for QuickSlot6"));
	GameplayTags.InputTag_QuickSlot_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.7"), FString("Input Tag for QuickSlot7"));
	GameplayTags.InputTag_QuickSlot_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.8"), FString("Input Tag for QuickSlot8"));
	GameplayTags.InputTag_QuickSlot_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.9"), FString("Input Tag for QuickSlot9"));
	GameplayTags.InputTag_QuickSlot_0 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.QuickSlot.0"), FString("Input Tag for QuickSlot0"));
	
	GameplayTags.InputTag_UI_Inventory = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.UI.Inventory"), FString("Input Tag for Toggle Inventory"));
	GameplayTags.InputTag_UI_Crafting = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.UI.Crafting"), FString("Input Tag for Toggle Crafting"));
	
	/*
	* Event
	*/
	GameplayTags.Event_Montage_AttackStart= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.AttackStart"), FString("Attack Start Tag"));
	GameplayTags.Event_Montage_AttackEnd = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.AttackEnd"), FString("Attack End Tag"));
	GameplayTags.Event_MeleeHit = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.MeleeHit"), FString("Melee Hit Tag"));
	GameplayTags.Event_SuccessfulBlock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.SuccessBlocking"), FString("Melee Hit Tag"));
	GameplayTags.Event_SwitchTarget_Left = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.SwitchTarget.Left"), FString("Event SwitchTarget Left Tag"));
	GameplayTags.Event_SwitchTarget_Right = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.SwitchTarget.Right"), FString("Event SwitchTarget Right Tag"));
	GameplayTags.Event_Parried = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Parried"), FString("Event Parried Tag"));
	
	/*
	* Shared Ability
	*/
	GameplayTags.Shared_Ability_UseItem = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.Ability.UseItem"), FString("Ability Tag for UseItem"));
	GameplayTags.Shared_Ability_Equip_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.Ability.Equip.Weapon"), FString("Ability Tag for Equip Weapon"));
	GameplayTags.Shared_Ability_Unequip_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.Ability.Unequip.Weapon"), FString("Ability Tag for Unequip Weapon"));
	GameplayTags.Shared_Ability_Equip_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.Ability.Equip.Armor"), FString("Ability Tag for Equip Armor"));
	GameplayTags.Shared_Ability_Unequip_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.Ability.Unequip.Armor"), FString("Ability Tag for Unequip Armor"));
	GameplayTags.Shared_Ability_MeleeHit = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.Ability.MeleeHit"), FString("Ability Tag for Shared Ability MeleeHit"));
	GameplayTags.Shared_Ability_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.Ability.Block"), FString("Ability Tag for Block"));
	GameplayTags.Shared_Ability_Parry = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.Ability.Parry"), FString("Ability Tag for Parry"));


	/*
	* Player Ability
	*/
	GameplayTags.Player_Ability_LightAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Ability.LightAttack"), FString("Ability Tag for Right Mouse Button"));
	GameplayTags.Player_Ability_HeavyAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Ability.HeavyAttack"), FString("Ability Tag for Right Mouse Button"));
	GameplayTags.Player_Ability_HitPose = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Ability.HitPose"), FString("Ability Tag for Right Mouse Button"));
	GameplayTags.Player_Ability_Roll = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Ability.Roll"), FString("Ability Tag for Right Mouse Button"));
	GameplayTags.Player_Ability_TargetLock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Ability.TargetLock"), FString("Ability Tag for Right Mouse Button"));
	
	GameplayTags.Player_Ability_Build = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Ability.Build"), FString("Ability Tag for Build"));
	
	/*
	* Enemy Ability
	*/
	GameplayTags.Enemy_Ability_LightAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Enemy.Ability.LightAttack"), FString("Ability Tag for Enemy LightAttack Ability"));
	
	/*
	* States
	*/
	GameplayTags.Player_State_Lock = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.State.Lock"), FString("Status Tag for Lock"));
	GameplayTags.Player_State_Evade = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.State.Evade"), FString("Status Tag for Evade"));

	GameplayTags.Shared_State_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.State.Block"), FString("Status Tag for Block"));
	GameplayTags.Shared_State_ComboCount = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.State.ComboCount"), FString("Ability Tag for Combo Count"));
	GameplayTags.Shared_State_Dead = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Shared.State.Dead"), FString("Ability Tag for Dead"));

	/*
	* Damage Types
	*/
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));

	/*
	* Effects
	*/
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Tag Granted when hit reacting"));

	/*
	 * Equip Socket
	 */
	GameplayTags.EquippableSocket_Head = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Head"), FString("Head Socket"));
	GameplayTags.EquippableSocket_Helmet = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Helmet"), FString("Helmet Socket"));
	GameplayTags.EquippableSocket_Tabard = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Tabard"), FString("Tabard Socket"));
	GameplayTags.EquippableSocket_Belt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Belt"), FString("Belt Socket"));
	GameplayTags.EquippableSocket_Boots = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Boots"), FString("Boots Socket"));
	GameplayTags.EquippableSocket_Bracers = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Bracers"), FString("Bracers Socket"));
	GameplayTags.EquippableSocket_Cape = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Cape"), FString("Cape Socket"));
	GameplayTags.EquippableSocket_Chest = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Chest"), FString("Chest Socket"));
	GameplayTags.EquippableSocket_Feet = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Feet"), FString("Feet Socket"));
	GameplayTags.EquippableSocket_Ears = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Ears"), FString("Ears Socket"));
	GameplayTags.EquippableSocket_Hair = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Hair"), FString("Hair Socket"));
	GameplayTags.EquippableSocket_Hands = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Hands"), FString("Hands Socket"));
	GameplayTags.EquippableSocket_Legs = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Legs"), FString("Legs Socket"));
	GameplayTags.EquippableSocket_Skirt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Skirt"), FString("Skirt Socket"));
	GameplayTags.EquippableSocket_Brows = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Brows"), FString("Brows Socket"));
	GameplayTags.EquippableSocket_Beard = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.Beard"), FString("Beard Socket"));
	GameplayTags.EquippableSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.RightHand"), FString("RightHandWeapon Socket"));
	GameplayTags.EquippableSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippableSocket.LeftHand"), FString("LeftHandWeapon Socket"));
	
	
	
	/*
	 * Item Type
	 */
	GameplayTags.Item_Equippable_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Equippable.Armor"), FString("Armor"));
	GameplayTags.Item_Equippable_Weapon_1H_Sword = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Equippable.Weapon.1H.Sword"), FString("1H Sword"));
	GameplayTags.Item_Equippable_Weapon_1H_Axe = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Equippable.Weapon.1H.Axe"), FString("1H Axe"));
	GameplayTags.Item_Equippable_Weapon_1H_PickAxe = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Equippable.Weapon.1H.PickAxe"), FString("1H PickAxe"));

	GameplayTags.Item_Equippable_Weapon_2H_Sword = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Equippable.Weapon.2H.Sword"), FString("2H Sword"));
	GameplayTags.Item_Equippable_Weapon_2H_Axe = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Equippable.Weapon.2H.Axe"), FString("2H Axe"));
	GameplayTags.Item_Equippable_Weapon_2H_PickAxe = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Equippable.Weapon.2H.PickAxe"), FString("2H PickAxe"));
		
	GameplayTags.Item_Resource = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Resource"), FString("Resource"));
	GameplayTags.Item_Consumable = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Consumable"), FString("Consumable"));
	GameplayTags.Item_Buildablel = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Buildablel"), FString("Buildable"));
	
	
	/*
	 * Gameplay Cue
	 */
	GameplayTags.GameplayCue_Sound_Hit_Wood = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Sound.Hit.Wood"), FString("GameplayCue Sound Hit Wood"));
	GameplayTags.GameplayCue_Sound_Hit_Stone = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Sound.Hit.Stone"), FString("GameplayCue Sound Hit Stone"));
	GameplayTags.GameplayCue_Sound_Hit_Monster = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Sound.Hit.Monster"), FString("GameplayCue Sound Hit Monster"));
	GameplayTags.GameplayCue_Sound_Hit_Shield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Sound.Hit.Shield"), FString("GameplayCue Sound ShieldAttack"));
	GameplayTags.GameplayCue_Sound_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Sound.Block"), FString("GameplayCue Sound Block"));
	
	GameplayTags.GameplayCue_Effect_Hit_Wood = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Effect.Hit.Wood"), FString("GameplayCue Effect Block"));
	GameplayTags.GameplayCue_Effect_Hit_Stone = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Effect.Hit.Stone"), FString("GameplayCue Effect Block"));
	GameplayTags.GameplayCue_Effect_Hit_Monster = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Effect.Hit.Monster"), FString("GameplayCue Effect Block"));
	GameplayTags.GameplayCue_Effect_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.Effect.Block"), FString("GameplayCue Effect Block"));




}
