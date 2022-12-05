section.begin
   Name = GetProperty
   Description : struct.begin
      [*] = ;IntRegister0 - property index
      [*] = ;OUT: IntRegister1 - result
   struct.end
   Code : struct.begin
      [*] = ;var prIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;
      [*] = ;var myIndex : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iIndex);
      [*] = ;var myLevel : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLevel);
      [*] = ;var myHealth : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iHealth);
      [*] = ;var pMyUnits : Integer = ParserSelectGameObject(myHandle);
      [*] = ;pMyUnits := ParserSelectByHandleByKey(pMyUnits, 'Units');
      [*] = ;
      [*] = ;var curUID : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;var curDummyHandle : Integer = GetGameObjectHandleByUniqueId(curUID);
      [*] = ;
      [*] = ;var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, myIndex);
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var cDummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(cDummyUID);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var value : Integer = 0;
      [*] = ;
      [*] = ;var pMyUnit : Integer = ParserSelectByHandleByIndex(pMyUnits, 0);
      [*] = ;var abilityID : Integer = -1;
      [*] = ;var prNewIndex : Integer = -1;
      [*] = ;
      [*] = ;case prIndex of
      [*] = ;   gc_map_hero_iLeaderProperty : begin
      [*] = ;      value := GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLeader);
      [*] = ;   end;
      [*] = ;   gc_map_hero_iHealthProperty : begin
      [*] = ;      value := GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iHealth);
      [*] = ;   end;
      [*] = ;   gc_map_hero_iMagicProperty : begin
      [*] = ;      value := GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iMagic);
      [*] = ;   end;
      [*] = ;
      [*] = ;   gc_map_hero_iInitiative : begin
      [*] = ;      abilityID := 999;
      [*] = ;   end;
      [*] = ;   gc_map_hero_iSiege : begin
      [*] = ;      if (gGame.gameType = gc_GameTypeHotseatBattle) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;         value := 0
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := pMyUnits;
      [*] = ;         IntRegister1 := myHandle;
      [*] = ;         MapExecuteState('map.GetSiegePowerByParser');
      [*] = ;         value := IntRegister2;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_map_hero_iMobility : begin
      [*] = ;      if (gGame.gameType = gc_GameTypeHotseatBattle) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;         value := 0
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         value := 1000;
      [*] = ;
      [*] = ;         for i := 0 to ParserGetCountByHandle(pMyUnits)-1 do
      [*] = ;         begin
      [*] = ;            var pMyUnit : Integer = ParserSelectByHandleByIndex(pMyUnits, i);
      [*] = ;
      [*] = ;            IntRegister0 := pMyUnit;
      [*] = ;            IntRegister1 := pMyUnits;
      [*] = ;            IntRegister2 := gc_battle_unit_iSpeed;
      [*] = ;            MapExecuteState('GetUnitPropertyByParser');
      [*] = ;            if IntRegister3 < value then
      [*] = ;               value := IntRegister3;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if value < 1 then
      [*] = ;            value := 1;
      [*] = ;
      [*] = ;         abilityID := 998;
      [*] = ;
      [*] = ;         if (gIntRegister_CurGameMode = gc_GameModeStrategy) or (gIntRegister_CurGameMode = gc_GameModeTactics) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 37; // mobility bonus from castle
      [*] = ;            GameObjectExecuteStateByHandle(cDummyHandle, 'CheckInnerBuildAbility');
      [*] = ;            value := value + IntRegister1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         value := value + GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iMoveBonus);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   gc_map_hero_iLife : prNewIndex := gc_battle_unit_iMaxLife;
      [*] = ;   gc_map_hero_iStamina : prNewIndex := gc_battle_unit_iMaxStamina;
      [*] = ;   gc_map_hero_iMoral : prNewIndex := gc_battle_unit_iCurMoral;
      [*] = ;   gc_map_hero_iAttack : prNewIndex := gc_battle_unit_iAttack;
      [*] = ;   gc_map_hero_iCounterAttack : prNewIndex := gc_battle_unit_iCounterAttack;
      [*] = ;   gc_map_hero_iDefence : prNewIndex := gc_battle_unit_iDefence;
      [*] = ;   gc_map_hero_iRangedDefence : prNewIndex := gc_battle_unit_iRangedDefence;
      [*] = ;   gc_map_hero_iResist : prNewIndex := gc_battle_unit_iResist;
      [*] = ;   gc_map_hero_iSpeed : prNewIndex := gc_battle_unit_iSpeed;
      [*] = ;   gc_map_hero_iRangedAttack : prNewIndex := gc_battle_unit_iRangedAttack;
      [*] = ;   gc_map_hero_iShootingRange : prNewIndex := gc_battle_unit_iShootingRange;
      [*] = ;   gc_map_hero_iAmmo : prNewIndex := gc_battle_unit_iMaxAmmo;
      [*] = ;end;
      [*] = ;
      [*] = ;if abilityID >= 0 then //for initiative and mobility
      [*] = ;begin
      [*] = ;   IntRegister0 := abilityID;
      [*] = ;   ExecuteState('CheckAbility');
      [*] = ;   value := value + IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;if prNewIndex >= 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := pMyUnit;
      [*] = ;   IntRegister1 := pMyUnits;
      [*] = ;   IntRegister2 := prNewIndex;
      [*] = ;   MapExecuteState('GetUnitPropertyByParser');
      [*] = ;   value := IntRegister3;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister1 := value;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

