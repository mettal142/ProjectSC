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
+ BuildingComponent
+ CombatComponent


---
Ability System
---
+ Gameplay Abilities
+ Gameplay Effects


---
Items
---
+ SlotPrimaryDataAsset
+ Item Types
   + Weapon
   + Armor
   + Usable
   + Resource
   + Buildables
+ 데이터테이블
  
---
Multiplay System
---
+ 멀티플레이 영상
