section.begin
   Name = Death
   Description : struct.begin
      [*] = ;IntRegister0 - killer UID
   struct.end
   Code : struct.begin
      [*] = ;var kUID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\DEATH';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;//if not gBoolRegister_BattleSimulate then
      [*] = ;//Log('Death execute for ' + GetGameObjectMyCustomName);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var isHero : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bIsHero);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;//var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName()+',UID:'+IntToStr(myUID)+']',_log_trace);
      [*] = ;if gBoolRegister_QuickBattle or gBoolRegister_BattleSimulate then
      [*] = ;   SetGameObjectMyPlayableObject(false);
      [*] = ;
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurLife, 0);
      [*] = ;
      [*] = ;if (myUID=gIntRegister_SelectedUID) then
      [*] = ;   gBoolRegister_GUIBattleSelectNextUnit := True;
      [*] = ;
      [*] = ;var grHandle : Integer = GetGameObjectMyGrHandle();
      [*] = ;if grHandle <> 0 then
      [*] = ;   GroupRemoveGameObjectByHandle(grHandle, myGOHandle);
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetSelectedGroupHandle');
      [*] = ;grHandle := IntRegister0;
      [*] = ;if grHandle <> 0 then
      [*] = ;   GroupRemoveGameObjectByHandle(grHandle, myGOHandle);
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;// damage armor and weapon for hero
      [*] = ;if isHero and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   _log_obj(_log_name+' Battle: hero death.');
      [*] = ;
      [*] = ;   IntRegister0 := 5;
      [*] = ;   IntRegister1 := myUID;
      [*] = ;   ExecuteState('DamageArmor');
      [*] = ;   IntRegister0 := 5;
      [*] = ;   IntRegister1 := 1;
      [*] = ;   ExecuteState('DamageWeapon');
      [*] = ;   IntRegister0 := 5;
      [*] = ;   IntRegister1 := 2;
      [*] = ;   ExecuteState('DamageWeapon');
      [*] = ;end;
      [*] = ;
      [*] = ;// change neighbours moral
      [*] = ;var myX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;var myInd : Integer = gc_battle_GridSize * myY + myX;
      [*] = ;var myTNHandle : Integer = GetTrackNodeHandleByIndex(myInd);
      [*] = ;var explode : Integer = _unit_CheckAbility(myGOHandle, gc_ability_death_explosion);
      [*] = ;
      [*] = ;for i := GetTrackNodeNeighboursCountByHandle(myTNHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var tnHandle : Integer = GetTrackNodeNeighbourHandleByHandleByIndex(myTNHandle, i);
      [*] = ;   var ind : Integer = GetTrackNodeIndexByHandle(tnHandle);
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;   var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;
      [*] = ;   if uid > 0 then
      [*] = ;   begin
      [*] = ;      var nGOHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;      var plHandle : Integer = GetGameObjectPlayerHandleByHandle(nGOHandle);
      [*] = ;
      [*] = ;      var oldLife : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iCurLife);
      [*] = ;      var oldStamina : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;      var oldMoral : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;      var isDead : Boolean = false;
      [*] = ;      
      [*] = ;      if (explode > 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := explode;
      [*] = ;         IntRegister1 := _unit_GetProperty(nGOHandle, gc_battle_unit_iResist);
      [*] = ;         BoolRegister0 := true;
      [*] = ;         MapExecuteState('bat.GetHit');
      [*] = ;         var hit : Integer = IntRegister2;
      [*] = ;
      [*] = ;         if hit > oldLife then
      [*] = ;            hit := oldLife;
      [*] = ;
      [*] = ;         IntRegister0 := hit;
      [*] = ;         IntRegister1 := 1;
      [*] = ;         IntRegister2 := myUID;
      [*] = ;         GameObjectExecuteStateByHandle(nGOHandle, 'TakeDamage');
      [*] = ;         isDead := BoolRegister0;
      [*] = ;
      [*] = ;         var deathAnimReady : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iDeathAnimReady) + 1;
      [*] = ;         SetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iDeathAnimReady, deathAnimReady);
      [*] = ;      end;
      [*] = ;      
      [*] = ;
      [*] = ;      if not isDead then //if doesn't die from explosion
      [*] = ;      begin
      [*] = ;         var moralChange : Integer = 0;
      [*] = ;
      [*] = ;         if plHandle = myPlHandle then
      [*] = ;         begin
      [*] = ;            moralChange := -1;
      [*] = ;            // world rule
      [*] = ;            if _worldrule_GetWorldRuleAbilityExistByID(15) then
      [*] = ;            moralChange := moralChange+_worldrule_GetWorldRuleAbilityParam1(15);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if uid <> kUID then // killer morale gain is done in DoAttack.inc
      [*] = ;               moralChange := 1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if moralChange <> 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := moralChange;
      [*] = ;            GameObjectExecuteStateByHandle(nGOHandle, 'ChangeMoral');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;      begin
      [*] = ;         var triggerUID : Integer;
      [*] = ;         if kUID <> 0 then
      [*] = ;         triggerUID := kUID
      [*] = ;         else
      [*] = ;         triggerUID := myUID;
      [*] = ;      
      [*] = ;         _unit_SetupStatsTextData(nGOHandle, triggerUID, oldLife, oldStamina, oldMoral);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_QuickBattle or gBoolRegister_BattleSimulate then
      [*] = ;   ExecuteState('AfterDeath');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

