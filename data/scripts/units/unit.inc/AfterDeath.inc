section.begin
   Name = AfterDeath
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\AFTERDEATH';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyEffects : Integer = ParserSelectByHandleByKey(pMyParser, 'Effects');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName()+',UID:'+IntToStr(myUID)+']',_log_trace);
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;var bRaiseCorpse : Boolean = GetBoolValueByIndex(gc_stack_unit_bRaiseCorpse);
      [*] = ;var gridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;var gridY : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;var layer : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Layer');
      [*] = ;
      [*] = ;var killUID : Integer = GetIntValueByIndex(gc_stack_unit_iKillerUID);
      [*] = ;var static : Boolean = GetBoolValueByIndex(gc_stack_unit_bStatic);
      [*] = ;var killGOHandle : Integer = GetGameObjectHandleByUniqueId(killUID);
      [*] = ;
      [*] = ;if not static then
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
      [*] = ;   if (_unit_CheckAbility(myGOHandle, gc_ability_death_explosion) > 0) and (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      _gui_PlaySound('spells','spell49');
      [*] = ;       if _obj_EnabledByFlag(gc_ObjectFlagBattleFX) then
      [*] = ;          _fx_CreateFX(myGOHandle, 'fx_blast_shot', 0, 0, 0, 0, 0);
      [*] = ;      _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_death_explosion, 0);
      [*] = ;      _unit_ApplyNeighbourVisuals(myGOHandle, gridX, gridY, 2, true);
      [*] = ;      _unit_ApplyNeighbourVisuals(myGOHandle, gridX, gridY, 2, false);
      [*] = ;   end;
      [*] = ;
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
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'UID', 0);
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
      [*] = ;      GameObjectExecuteStateByHandle(newGOHandle, 'Resurrect');
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iCurLife, _unit_GetProperty(newGOHandle, gc_battle_unit_iMaxLife));
      [*] = ;      _unit_GUIUpdateUnitHUD(newGOHandle);
      [*] = ;      SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iFear, 0);
      [*] = ;      SetGameObjectPlayableObjectByHandle(newGOHandle, true);
      [*] = ;      if chIndex >= 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := chIndex;
      [*] = ;         GameObjectExecuteStateByHandle(newGOHandle, 'ChangeSide');
      [*] = ;      end;
      [*] = ;   
      [*] = ;      if (not gBoolRegister_BattleSimulate) and (not gBoolRegister_QuickBattle) and _obj_EnabledByFlag(gc_ObjectFlagBattleFX) then
      [*] = ;      begin
      [*] = ;         var reincarnateFX : String;
      [*] = ;         if GetGameObjectMyIntValueInd(gc_stack_unit_iUnitID) = 70 then // phoenix
      [*] = ;            reincarnateFX := 'fx_impact_burn'
      [*] = ;         else
      [*] = ;            reincarnateFX := 'fxray';
      [*] = ;         
      [*] = ;         _fx_CreateFX(newGOHandle, reincarnateFX, 0, 0, 0, 0, 0);
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
      [*] = ;      IntRegister1 := gridX;
      [*] = ;      IntRegister2 := gridY;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'AddUnit');
      [*] = ;      var dGOHandle : Integer = IntRegister3;
      [*] = ;      var dUID : Integer = GetGameObjectUniqueIdByHandle(dGOHandle);
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(dGOHandle, 'CalcAbilities');
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iLastX, gridX);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iLastY, gridY);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iCurrentX, gridX);
      [*] = ;      SetGameObjectIntValueIndByHandle(dGOHandle, gc_stack_unit_iCurrentY, gridY);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'UID', dUID);
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
      [*] = ;      _unit_GUIUpdateUnitHUD(dGOHandle);
      [*] = ;
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iCurrentX, -1);
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iCurrentY, -1);
      [*] = ;
      [*] = ;      if not gBoolRegister_BattleSimulate then
      [*] = ;      begin
      [*] = ;         var remainsUID : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iRemainsUID);
      [*] = ;         var remainsHnd : Integer = GetGameObjectHandleByUniqueId(remainsUID);
      [*] = ;         if (remainsHnd <> 0) then
      [*] = ;         begin
      [*] = ;            if gc_RecycleBattleField then
      [*] = ;               _obj_Recycle(remainsHnd)
      [*] = ;            else
      [*] = ;               AddObjectToDestroyList(remainsHnd);
      [*] = ;         end;
      [*] = ;         
      [*] = ;         SetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iRemainsUID, 0);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if bRaiseZombie then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 20;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := gridX;
      [*] = ;      IntRegister3 := gridY;
      [*] = ;      PlayerExecuteStateByHandle(enPlHandle, 'SummonUnit');
      [*] = ;      _unit_SetupFlyText(IntRegister4, myUID, gc_flytext_CategoryAbility, gc_ability_zombie, 0);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if bRaiseCorpse then
      [*] = ;   begin
      [*] = ;      if killGOHandle <> 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;         GameObjectExecuteStateByHandle(killGOHandle, 'RaiseCorpse');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (_unit_CheckAbility(killGOHandle, gc_ability_oviposition) > 0) and (layer = 0) and ((unitType = 1) or (unitType = 5)) then
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
      [*] = ;         IntRegister2 := gridX;
      [*] = ;         IntRegister3 := gridY;
      [*] = ;         PlayerExecuteStateByHandle(enPlHandle, 'SummonUnit');
      [*] = ;         var goHandle : Integer = IntRegister4;
      [*] = ;
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bSummoned, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanMelee, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanShoot, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanCast, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bStatic, true);
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iTransformTimer, ParserGetIntValueByKeyByHandle(pAbility, 'UnitTransformTimer'));
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iTransformUnitID, ParserGetIntValueByKeyByHandle(pAbility, 'UnitTransformID'));
      [*] = ;         _unit_SetupFlyText(goHandle, myUID, gc_flytext_CategoryAbility, gc_ability_oviposition, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var remainsHnd : Integer = GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iRemainsUID));
      [*] = ;      if (remainsHnd <> 0) then
      [*] = ;      begin
      [*] = ;         if gc_RecycleBattleField then
      [*] = ;            _obj_Recycle(remainsHnd)
      [*] = ;         else
      [*] = ;            AddObjectToDestroyList(remainsHnd);
      [*] = ;      end;
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
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'UID', killUID);
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(killGOHandle, gc_stack_unit_iCurrentX, gridX);
      [*] = ;      SetGameObjectIntValueIndByHandle(killGOHandle, gc_stack_unit_iCurrentY, gridY);
      [*] = ;
      [*] = ;      if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;      begin
      [*] = ;         var x, y, z : Float;
      [*] = ;         GetTrackNodePositionByIndex(ind, x, y, z);
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
      [*] = ;         IntRegister0 := gridX;
      [*] = ;         IntRegister1 := gridY;
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
      [*] = ;   var isHero : Boolean = GetBoolValueByIndex(gc_stack_unit_bIsHero);
      [*] = ;   if isHero and (not bReincarnate) then
      [*] = ;   begin
      [*] = ;      for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;         if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CalcAbilities');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // check
      [*] = ;   if not GetGameObjectPlayableObjectByHandle(newGOHandle) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := myPlHandle;
      [*] = ;      MapExecuteState('bat.CheckEndBattle');
      [*] = ;      //_Log_Map('CheckEndBattle '+BoolToStr(BoolRegister0));
      [*] = ;      //_Log_Map('gBoolRegister_BattleSimulate '+BoolToStr(gBoolRegister_BattleSimulate));
      [*] = ;      //_Log_Map('gBoolRegister_IsHumanPlayer '+BoolToStr(gBoolRegister_IsHumanPlayer));
      [*] = ;      if BoolRegister0 and (not gBoolRegister_BattleSimulate) and gBoolRegister_IsHumanPlayer then
      [*] = ;         MapExecuteState('bat.DoFinishBattle');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'UID', 0);
      [*] = ;   if GetIntValueByIndex(gc_stack_unit_iTransformTimer) = 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := GetIntValueByIndex(gc_stack_unit_iTransformUnitID);
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := gridX;
      [*] = ;      IntRegister3 := gridY;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'SummonUnit');
      [*] = ;      _unit_SetupFlyText(IntRegister4, myUID, gc_flytext_CategoryAbility, gc_ability_transformed, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('ApplyAllVisualParams');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

