section.begin
   Name = Death
   Description : struct.begin
      [*] = ;IntRegister0 - killer UID
   struct.end
   Code : struct.begin
      [*] = ;var killUID : Integer = IntRegister0;
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
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName;
      [*] = ;var myBaseName : String = GetGameObjectMyBaseName;
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
      [*] = ;   ErrorLogI(_log_name+' Battle: hero death.');
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
      [*] = ;var myGridX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myGridY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;var myInd : Integer = gc_battle_GridSize * myGridY + myGridX;
      [*] = ;var myTNHandle : Integer = GetTrackNodeHandleByIndex(myInd);
      [*] = ;var pMyHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, myInd);
      [*] = ;
      [*] = ;
      [*] = ;var explode : Integer = _unit_CheckAbility(myGOHandle, gc_ability_death_explosion);
      [*] = ;
      [*] = ;for i := GetTrackNodeNeighboursCountByHandle(myTNHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var tnHandle : Integer = GetTrackNodeNeighbourHandleByHandleByIndex(myTNHandle, i);
      [*] = ;   var ind : Integer = GetTrackNodeIndexByHandle(tnHandle);
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;   var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;
      [*] = ;   if uid <> 0 then
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
      [*] = ;         BoolRegister0 := false;
      [*] = ;         IntRegister0 := hit;
      [*] = ;         IntRegister1 := 1;
      [*] = ;         IntRegister2 := myUID;
      [*] = ;         GameObjectExecuteStateByHandle(nGOHandle, 'TakeDamage');
      [*] = ;         isDead := BoolRegister1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var moralChange : Integer = 0;
      [*] = ;
      [*] = ;      if plHandle = myPlHandle then
      [*] = ;      begin
      [*] = ;         moralChange := -1;
      [*] = ;         // world rule
      [*] = ;         if _worldrule_GetWorldRuleAbilityExistByID(15) then
      [*] = ;            moralChange := moralChange+_worldrule_GetWorldRuleAbilityParam1(15);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if uid <> killUID then
      [*] = ;            moralChange := 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if moralChange <> 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := moralChange;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'ChangeMoral');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;         _unit_SetupStatsTextData(nGOHandle, myUID, oldLife, oldStamina, oldMoral);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// After Death
      [*] = ;
      [*] = ;if not GetBoolValueByIndex(gc_stack_unit_bStatic) then
      [*] = ;begin
      [*] = ;   var pUnit : Integer = _unit_GetUnitParserByID(GetIntValueByIndex(gc_stack_unit_iUnitID));
      [*] = ;   var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;   var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   var chIndex : Integer = -1;
      [*] = ;   var bReincarnate : Boolean = false;
      [*] = ;   var bDarkPact : Boolean = false;
      [*] = ;   var bRaiseZombie : Boolean = false;
      [*] = ;
      [*] = ;   var newGOHandle : Integer = myGOHandle;
      [*] = ;
      [*] = ;   var killGOHandle : Integer = GetGameObjectHandleByUniqueId(killUID);
      [*] = ;
      [*] = ;   var pMyEffects : Integer = ParserSelectByHandleByKey(pMyParser, 'Effects');
      [*] = ;   for i := ParserGetCountByHandle(pMyEffects)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMyEffect : Integer = ParserSelectByHandleByIndex(pMyEffects, i);
      [*] = ;      var abilityID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'AbilityID');
      [*] = ;
      [*] = ;      case abilityID of
      [*] = ;         gc_ability_change_side : chIndex := ParserGetIntValueByKeyByHandle(pMyEffect, 'Power');
      [*] = ;         gc_ability_reincarnation : bReincarnate := true;
      [*] = ;         gc_ability_dark_pact : bDarkPact := true;
      [*] = ;         gc_ability_phantom_form : begin
      [*] = ;            var tfHandle : Integer = GetGameObjectHandleByUniqueId(GetIntValueByIndex(gc_stack_unit_iTrueFormUID));
      [*] = ;            if tfHandle <> 0 then
      [*] = ;               newGOHandle := tfHandle;
      [*] = ;         end;
      [*] = ;         gc_ability_zombie : bRaiseZombie := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      ParserFreeByHandle(pMyEffect);
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyHexCell, 'UID', 0);
      [*] = ;   SetBoolValueByIndex(gc_stack_unit_bStealthMode, false);
      [*] = ;
      [*] = ;   if chIndex >= 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := chIndex;
      [*] = ;      ExecuteState('ChangeSide');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if bReincarnate then
      [*] = ;   begin
      [*] = ;      //GameObjectExecuteStateByHandle(newGOHandle, 'Resurrect');
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iCurLife, _unit_GetProperty(newGOHandle, gc_battle_unit_iMaxLife));
      [*] = ;      SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iFear, 0);
      [*] = ;      SetGameObjectPlayableObjectByHandle(newGOHandle, true);
      [*] = ;      if chIndex >= 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := chIndex;
      [*] = ;         GameObjectExecuteStateByHandle(newGOHandle, 'ChangeSide');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if bDarkPact then
      [*] = ;   begin
      [*] = ;      var pUnit : Integer = _unit_GetUnitParserByID(GetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iUnitID));
      [*] = ;      var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;
      [*] = ;      var dUnitID : Integer = 0;
      [*] = ;      case rank of
      [*] = ;         1 : dUnitID := 21;
      [*] = ;         2 : dUnitID := 37;
      [*] = ;         3 : dUnitID := 56;
      [*] = ;         4 : dUnitID := 65;
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := dUnitID;
      [*] = ;      IntRegister1 := myGridX;
      [*] = ;      IntRegister2 := myGridY;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'AddUnit');
      [*] = ;      var dGOHandle : Integer = IntRegister3;
      [*] = ;      var dUID : Integer = GetGameObjectUniqueIdByHandle(dGOHandle);
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(dGOHandle, 'CalcAbilities');
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iLastX, myGridX);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iLastY, myGridY);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iCurrentX, myGridX);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iCurrentY, myGridY);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMyHexCell, 'UID', dUID);
      [*] = ;
      [*] = ;      var maxLife : Integer = _unit_GetProperty(dGOHandle, gc_battle_unit_iMaxLife);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iCurLife, maxLife);
      [*] = ;      var maxAmmo : Integer = _unit_GetProperty(dGOHandle, gc_battle_unit_iMaxAmmo);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iCurAmmo, maxAmmo);
      [*] = ;      var maxStamina : Integer = _unit_GetProperty(dGOHandle, gc_battle_unit_iMaxStamina);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iCurStamina, maxStamina);
      [*] = ;      var maxMoral : Integer = _unit_GetProperty(dGOHandle, gc_battle_unit_iMaxMoral);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iCurMoral, maxMoral);
      [*] = ;
      [*] = ;      var armyIndex : Integer = GetIntValueByIndex(gc_stack_unit_iArmyIndex);
      [*] = ;      var batX : Integer = GetIntValueByIndex(gc_stack_unit_iBattleX);
      [*] = ;      var batY : Integer = GetIntValueByIndex(gc_stack_unit_iBattleY);
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iFear, 0);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iArmyIndex, armyIndex);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iBattleX, batX);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iBattleY, batY);
      [*] = ;
      [*] = ;      if chIndex >= 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := chIndex;
      [*] = ;         GameObjectExecuteStateByHandle(dGOHandle, 'ChangeSide');
      [*] = ;      end;
      [*] = ;
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iCurrentX, -1);
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iCurrentY, -1);
      [*] = ;
      [*] = ;      if not gBoolRegister_BattleSimulate then
      [*] = ;      begin
      [*] = ;         var remainsUID : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iRemainsUID);
      [*] = ;         var remainsHnd : Integer = GetGameObjectHandleByUniqueId(remainsUID);
      [*] = ;         if (remainsHnd <> 0) then
      [*] = ;            AddObjectToDestroyList(remainsHnd);
      [*] = ;         SetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iRemainsUID, 0);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if bRaiseZombie then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 20;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := myGridX;
      [*] = ;      IntRegister3 := myGridY;
      [*] = ;      PlayerExecuteStateByHandle(enPlHandle, 'SummonUnit');
      [*] = ;      _fx_CreateFlyText_VVK( IntRegister4, gc_flytext_CategoryAbility, gc_ability_zombie, 0);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if GetBoolValueByIndex(gc_stack_unit_bRaiseCorpse) then
      [*] = ;   begin
      [*] = ;      if killGOHandle <> 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;         GameObjectExecuteStateByHandle(killGOHandle, 'RaiseCorpse');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (_unit_CheckAbility(killGOHandle, gc_ability_oviposition) > 0) and (ParserGetIntValueByKeyByHandle(pMyHexCell, 'Layer') = 0) and ((unitType = 1) or (unitType = 5)) then
      [*] = ;   begin
      [*] = ;      var pAbility : Integer;
      [*] = ;      // spider egg ability
      [*] = ;      IntRegister0 := gc_ability_oviposition;
      [*] = ;      MapExecuteState('GetAbilityParserByID');
      [*] = ;      pAbility := IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := ParserGetIntValueByKeyByHandle(pAbility, 'UnitID');
      [*] = ;      if IntRegister0 > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister1 := 0;
      [*] = ;         IntRegister2 := myGridX;
      [*] = ;         IntRegister3 := myGridY;
      [*] = ;         PlayerExecuteStateByHandle(enPlHandle, 'SummonUnit');
      [*] = ;         var goHandle : Integer = IntRegister4;
      [*] = ;
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bSummoned, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bStatic, true);
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iTransformTimer, ParserGetIntValueByKeyByHandle(pAbility, 'UnitTransformTimer'));
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iTransformUnitID, ParserGetIntValueByKeyByHandle(pAbility, 'UnitTransformID'));
      [*] = ;         _fx_CreateFlyText_VVK(goHandle, gc_flytext_CategoryAbility, gc_ability_oviposition, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var remainsHnd : Integer = GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iRemainsUID));
      [*] = ;      if (remainsHnd <> 0) then
      [*] = ;         AddObjectToDestroyList(remainsHnd);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   // trample
      [*] = ;   if (_unit_CheckAbility(killGOHandle, gc_ability_trumpling) > 0) and (_unit_CheckAbility(myGOHandle, gc_ability_flying) = 0) and (_unit_CheckAbility(killGOHandle, gc_ability_cantmove) = 0) then
      [*] = ;   begin
      [*] = ;      var goGridX : Integer = GetGameObjectIntValueIndByHandle(killGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;      var goGridY : Integer = GetGameObjectIntValueIndByHandle(killGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;      var goInd : Integer = gc_battle_GridSize * goGridY + goGridX;
      [*] = ;
      [*] = ;      var pGOHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.Handle, goInd);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOHexCell, 'UID', 0);
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pMyHexCell, 'UID', killUID);
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(killGOHandle, gc_stack_unit_iCurrentX, myGridX);
      [*] = ;      SetGameObjectIntValueIndByHandle(killGOHandle, gc_stack_unit_iCurrentY, myGridY);
      [*] = ;
      [*] = ;      if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;      begin
      [*] = ;         var x, y, z : Float;
      [*] = ;         GetTrackNodePositionByIndex(myInd, x, y, z);
      [*] = ;
      [*] = ;         GameObjectTrackPointClearByHandle(killGOHandle);
      [*] = ;         GameObjectTrackPointAddByHandle(killGOHandle, x, 0, z);
      [*] = ;         SetGameObjectTrackPointCurrentPointIndexByHandle(killGOHandle, 0);
      [*] = ;
      [*] = ;         var killAnim : String = GetGameObjectAnimationCycleNameByHandle(killGOHandle);
      [*] = ;
      [*] = ;         if SameText(killAnim, 'idle') then
      [*] = ;            GameObjectExecuteStateByHandle(killGOHandle, 'Move');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := myGridX;
      [*] = ;         IntRegister1 := myGridY;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         GameObjectExecuteStateByHandle(killGOHandle, 'Replace');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ExecuteState('IsFullDestroy');
      [*] = ;      if BoolRegister0 then
      [*] = ;      begin
      [*] = ;         SetIntValueByIndex(gc_stack_unit_iCurrentX, -1);
      [*] = ;         SetIntValueByIndex(gc_stack_unit_iCurrentY, -1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if GetBoolValueByIndex(gc_stack_unit_bIsHero) and (not bReincarnate) then
      [*] = ;   begin
      [*] = ;      for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;         if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CalcAbilities');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyHexCell, 'UID', 0);
      [*] = ;   if GetIntValueByIndex(gc_stack_unit_iTransformTimer) = 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := GetIntValueByIndex(gc_stack_unit_iTransformUnitID);
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := myGridX;
      [*] = ;      IntRegister3 := myGridY;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'SummonUnit');
      [*] = ;      _fx_CreateFlyText_VVK( IntRegister4, gc_flytext_CategoryAbility, gc_ability_transformed, 0);
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

