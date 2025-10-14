#pragma once

UENUM()
enum class ESCConfirmType : uint8
{
	YES,
	NO
};
UENUM()
enum class ESCValidType : uint8
{
	Valid,
	InValid
};
UENUM(BlueprintType)
enum class EGameState : uint8
{
	Playing,
	InGameMenu,
	Building
};

UENUM(BlueprintType)
enum class EMenuType : uint8
{
	Map,
	Inventory,
	Crafting
};


UENUM(BlueprintType)
enum class ESCSuccessType : uint8
{
	Successful,
	Failed
};

UENUM(BlueprintType)
enum class ECraftingType : uint8
{
	Player,
	CraftingBench,
	AdvancedCraftingBench
};

UENUM(BlueprintType)
enum class EContentType : uint8
{
	Empty,
	ConsumableItem,
	BuildableItem,
	Armor,
	Weapon,
	Resource,
	Skill
};
UENUM(BlueprintType)
enum class EContainerType : uint8
{
	Inventory,
	QuickSlot,
	Storage,
	Equipable,
};

UENUM(BlueprintType)
enum class EBuildableType : uint8
{
	Foundation,
	Wall,
	Ceil,
	Roof,
	Stair,
	Ramp,
	Door,
	Window,
	Torch,
};
