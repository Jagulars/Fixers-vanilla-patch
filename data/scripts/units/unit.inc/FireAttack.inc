section.begin
   Name = FireAttack
   Code : struct.begin
      [*] = ;var sendParser : Boolean = BoolRegister0;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\FIREATTACK';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;const cEpsilonAngle = 10;
      [*] = ;
      [*] = ;var tUID : Integer = GetIntValueByIndex(gc_stack_unit_iTargetUID);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;var tStealthMode : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bStealthMode);
      [*] = ;
      [*] = ;if not tStealthMode then
      [*] = ;begin
      [*] = ;   var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;   var myCustomName : String = GetGameObjectMyCustomName();
      [*] = ;   var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;   var myIsHero : Boolean = GetBoolValueByIndex(gc_stack_unit_bIsHero);
      [*] = ;   var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;   var actAbility : Integer = GetIntValueByIndex(gc_stack_unit_iActiveAbility);
      [*] = ;   var tCustomName : String = GetGameObjectCustomNameByHandle(tGOHandle);
      [*] = ;   var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;
      [*] = ;   _gv_traceState(_log_name+'['+myCustomName+']',_log_trace);
      [*] = ;
      [*] = ;   GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;   // Fly text data
      [*] = ;   //var oldMyLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;   var oldMyStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;   //var oldMyMoral : Integer = GetIntValueByIndex(gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;   var ammo : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurAmmo);
      [*] = ;   var i : Integer;
      [*] = ;   var shotCount : Integer = 1;
      [*] = ;
      [*] = ;   if (actAbility = gc_ability_double_shot) and (ammo > 1) then
      [*] = ;   begin
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_double_shot, 0);
      [*] = ;      shotCount := shotCount + 1;
      [*] = ;   end;
      [*] = ;   if not gBoolRegister_BattleSimulate then
      [*] = ;   begin
      [*] = ;      var myGridX : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;      var myGridY : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;      var tGridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;      var tGridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iFacing, _map_GetFacing(_map_GetBattleHex(myGridX, myGridY), _map_GetBattleHex(tGridX, tGridY)));
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to shotCount-1 do
      [*] = ;   begin
      [*] = ;      if GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife) > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := myUID;
      [*] = ;         IntRegister1 := tUID;
      [*] = ;         MapExecuteState('bat.DoProjectileDamage');
      [*] = ;         ammo := ammo - 1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         shotCount := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iCurAmmo, ammo);
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iShotCount, shotCount);
      [*] = ;
      [*] = ;      ExecuteState('VisualFireAttack');
      [*] = ;      _gv_SetBattleLock(shotCount,_log_name);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // change stamina
      [*] = ;   var movePoints : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints);
      [*] = ;   IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var speed : Integer = IntRegister1;
      [*] = ;   var stamina : Integer = 0;
      [*] = ;
      [*] = ;   if (movePoints < speed) and (_unit_CheckAbility(myGOHandle, gc_ability_second_breath) = 0) then
      [*] = ;      stamina := -2
      [*] = ;   else
      [*] = ;      stamina := -1;
      [*] = ;
      [*] = ;   // world rule
      [*] = ;   if _worldrule_GetWorldRuleAbilityExistByID(21) then
      [*] = ;   begin
      [*] = ;      if gBoolRegister_BattleIsAttackerAction then
      [*] = ;         stamina := stamina + _worldrule_GetWorldRuleAbilityParam1(21)
      [*] = ;      else
      [*] = ;         stamina := stamina + _worldrule_GetWorldRuleAbilityParam2(21);
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := stamina;
      [*] = ;   ExecuteState('ChangeStamina');
      [*] = ;
      [*] = ;   // check for additional shot ability
      [*] = ;   if (actAbility = gc_ability_double_shot) and (movePoints > 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_ability_double_shot;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      IntRegister0 := -1 * IntRegister1;
      [*] = ;      ExecuteState('ChangeStamina');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (movePoints > 0) and (_unit_CheckAbility(myGOHandle, gc_ability_swiftness) > 0) and (_unit_CheckAbility(myGOHandle, gc_ability_cantmove) = 0) then
      [*] = ;   begin
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bActionTaken, true);
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bCanMelee, false);
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bCanShoot, false);
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bCanCast, false);
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iActiveAbility, 0);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ExecuteState('ActionDone');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if GetBoolValueByIndex(gc_stack_unit_bStealthMode) then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := false;
      [*] = ;      ExecuteState('SwitchStealthModeFlag');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      var pElmLog : Integer = _log_battle_AddNewElement();
      [*] = ;      ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 3);
      [*] = ;      var pSrcUnit : Integer = ParserSelectByHandleByKey(pElmLog, 'SrcUnit');
      [*] = ;      ParserSetIntValueByKeyByHandle(pSrcUnit, 'UID', myUID);
      [*] = ;      var pChangedParams : Integer = ParserSelectByHandleByKey(pSrcUnit, 'ChangedParams');
      [*] = ;
      [*] = ;      var newMyStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;      var deltaMyStamina : Integer = newMyStamina-oldMyStamina;
      [*] = ;
      [*] = ;      if (deltaMyStamina<>0) then
      [*] = ;      begin
      [*] = ;         _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryParam,gc_battle_unit_iCurStamina, deltaMyStamina);
      [*] = ;
      [*] = ;         var pChangedParam : Integer = _log_battle_AddChangedParamToParser(pChangedParams);
      [*] = ;         ParserSetIntValueByKeyByHandle(pChangedParam, 'ParamID', 2);
      [*] = ;         ParserSetIntValueByKeyByHandle(pChangedParam, 'Value', deltaMyStamina);
      [*] = ;
      [*] = ;         _unit_GUIUpdateUnitHUD(myGOHandle);
      [*] = ;      end;
      [*] = ;      _log_battle_Show();
      [*] = ;   end;
      [*] = ;
      [*] = ;   if sendParser then
      [*] = ;      _inet_CreateOrderParser(myUID, -1, -1, gc_inet_actiontype_fireattack, 0, 0, tUID, 0, lanOrderRandKey0, lanOrderRandKey1, 'FireAttack');
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
   struct.end
section.end

