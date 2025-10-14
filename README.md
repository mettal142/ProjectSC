# ProjectSC(Survival Craft)
---
+ 엔진 버전 : Unreal Engine 5.4
+ 에디터 : Visual Studio 2022
+ 개발 규모 : 1인 개발
+ 개발 기간 : 2025.06 ~ 개발 진행중

데모 동영상
---
>YouTube

[![이미지 텍스트](https://github.com/mettal142/ProjectSC/blob/main/Images/main.png)](https://youtu.be/X-r0QMzDt_k)
 + 이미지 클릭 시 영상 재생

---
Character
---
+ Character StartUp Data
  
  ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/5.png)
  + Player Startup Ability Sets: InputTag 대비 실행할 Gameplay Ability
  + Default Anim Layer to Link: 기본 Animation Layer
  + Attack Montage: 기본공격 Montage
  + Activate on Given Abilities: 부여된 직후 바로 실행될 단발성 Gameplay Ability
  + Reactive Abilities: 캐릭터에 부여된 어빌리티
  + Startup Gameplay Effects: 캐릭터의 기본 Gameplay Effects
 
 
+ Character Customize

  + Character Customize Data Asset
  ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/10.png)

 
   + 변경된 캐릭터의 외형
  ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/9.png)

   + 변경된 Enemy의 외형
  ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/8.png)

---
Components
---

+ InventoryComponent: 캐릭터의 인벤토리 관련 컴포넌트
  + Itema Add/Remove/Transfer: 아이템 추가 삭제 및 이동기능
  + Craft Item: Recipe에 따라 새로운 아이템 생성기능
  + Use Item: 아이템 종류에 따른 어빌리티 사용
+ QuickSlotComponent: 캐릭터의 퀵슬릇 관련 컴포넌트
  + Transfer Contents: 인벤토리 및 스킬(추가 계정)을 퀵슬릇에 배치
  + Use Slot Ability: 퀵슬릇에 배치된 요소에 따라 적절한 어빌리티 사용
+ BuildingComponent: 구조물을 배치하는 컴포넌트
  + PreViewActor(Client): Preview Mesh 추가 및 이동, 회전
  + Place Structure(Server): Preview Mesh의 위치에 해당 구조물을 배치
+ CombatComponent: 캐릭터의 전투 관련 컴포넌트
  + Equip Weapon(Server): 무기 장착기능
  + Equip Armor(Server): 방어구 장착기능
  + Melee Attack: 근접공격 탐지 로직


---
Ability System
---
+ Gameplay Abilities
  + UseItem: 소비 아이템의 게임플레이 이펙트를 캐릭터에게 부여해주는 어빌리티
     ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/18.gif)
  + Player Evade: 회피 어빌리티
   ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/17.gif)
  + Player Attack: 플레이어의 공격 어빌리티
   ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/15.gif)
  + Enemy Attack: Enemy(무기장착 X)의 공격 어빌리티
   ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/16.gif)
+ Gameplay Effects
  + Primary Attributes: 캐릭터의 기본 스탯 어트리뷰트를 부여하는 게임플레이 이펙트(추가 예정)
  + Secondary Abilities: Primary Attribute에 따라 달라지는 어트리뷰트를 부여하는 게임플레이 이펙트
  + Vital Abilities: 현재 체력, 마나, 스태미나를 부여하는 게임플레이 이펙트
  + Health/Stamina/Mana Regen: 주기적으로 Vital Attribute를 회복시켜주는 게임플레이 이펙트
  + Useable Item Effect: 소비 아이템에 부여된 게임플레이 이펙트 (현제는 Health Potion)
  + Combo Stack: 콤보공격의 스택을 관리하는 게임플레이 이펙트(1초마다 리셋)
  + Damage: 캐릭터가 받는 데미지 관련 게임플레이 이펙트


---
Items
---
+ SlotPrimaryDataAsset: 퀵슬릇에 올릴 수 있는 컨텐츠의 Primary Data Asset(Item, Skill)
> SlotPrimaryDataBase.h


    class PROJECTSC_API USlotPrimaryDataBase : public UPrimaryDataAsset
    {
    	GENERATED_BODY()
    	
    public:
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
    	int ID = 0;
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
    	UTexture2D* Icon;
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
    	FText Name;
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
    	FText Description;
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
    	FGameplayTag AbilityTag;
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseProperties")
    	EContentType ContentType;
    };

     
+ Data Tables
  + Item Table: 게임에 들어가는 모든 아이템 테이블
  ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/21.png)
  + Recipe Table: 아이템을 제작하기 위한 레시피 테이블
  ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/23.png)
  + Drop Table: 아이템을 획득하기 위한 드랍 테이블
  ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/22.png)
  + Buildable Table: 배치 가능한 구조물 테이블
  ![스크린샷 2024-03-25 233612](https://github.com/mettal142/ProjectSC/blob/main/Images/24.png)
  
+ Data Types
   + Resource: 제작에 필요한 기타 아이템(ID: 100000 ~ 199999)
   + Usable: 사용할 수 있는 소비 아이템(ID: 200000 ~ 299999)
   + Armor: 장착할 수 있는 방어구 아이템(ID: 300000 ~ 399999)
   + Weapon: 장착할 수 있는 무기 아이템(ID: 400000 ~ 499999)
   + Buildables: 배치할 수 있는 건축 아이템(ID: 500000 ~ 599999)
   + Skill: 전투 및 보조 역할의 스킬(ID: 600000 ~ 699999) -> 추가예정
   + Recipe: 제작을 위한 레시피(ID: 700000 ~ 799999)
---
Multiplay System
---
>YouTube

[![이미지 텍스트](https://github.com/mettal142/ProjectSC/blob/main/Images/20.png)](https://youtu.be/3JuylUJiWrs)
 + 이미지 클릭 시 영상 재생
