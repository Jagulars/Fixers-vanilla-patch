section.begin
   Name = EatCorpse
   Description : struct.begin
      [*] = ;IntRegister0 - target UID
   struct.end
   Code : struct.begin
      [*] = ;var sendParser : Boolean = BoolRegister0;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\EATCORPSE';
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var curX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var curY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;IntRegister0 := curX;
      [*] = ;IntRegister1 := curY;
      [*] = ;PlayerExecuteStateByHandle(enPlHandle, 'GetDeadUnitInHex');
      [*] = ;var goHandle : Integer = IntRegister2;
      [*] = ;
      [*] = ;if goHandle = 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := curX;
      [*] = ;   IntRegister1 := curY;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'GetDeadUnitInHex');
      [*] = ;   goHandle := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;var goUID : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_ability_flesh_eater;
      [*] = ;   ExecuteState('CheckAbility');
      [*] = ;   var addLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iCurLife;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var curLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var lifeBonus : Integer = addLife div 2 + _rand_Random(addLife div 2 + 1);
      [*] = ;   if lifeBonus > maxLife - curLife then
      [*] = ;      lifeBonus := maxLife - curLife;
      [*] = ;
      [*] = ;   curLife := curLife + lifeBonus;
      [*] = ;
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iCurLife, curLife);
      [*] = ;   _unit_GUIUpdateUnitHUD(myGOHandle);
      [*] = ;   ExecuteState('ActionDone');
      [*] = ;
      [*] = ;   //GameObjectDestroyByHandle(goHandle);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX, -1);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY, -1);
      [*] = ;   SetGameObjectVisibleByHandle(goHandle, false);
      [*] = ;
      [*] = ;   var remainsUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iRemainsUID);
      [*] = ;   var remainsHnd : Integer = GetGameObjectHandleByUniqueId(remainsUID);
      [*] = ;   if (remainsHnd <> 0) then
      [*] = ;   begin
      [*] = ;      if gc_RecycleBattleField then
      [*] = ;         _obj_Recycle(remainsHnd)
      [*] = ;      else
      [*] = ;         AddObjectToDestroyList(remainsHnd);
      [*] = ;   end;
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iRemainsUID, 0);
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      if GetGameObjectMyTrackPointMovementMode = 'mmNone' then
      [*] = ;      begin
      [*] = ;         _unit_ModifyAnimIntervalFactor(myGOHandle, gc_battle_unit_attackspeedmod);
      [*] = ;         GameObjectMySwitchToTreeAnimationCyclesDefault('cannibalize');
      [*] = ;         _unit_PlaySound(myGOHandle, 'units', 'cannibalize');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;         ParserSetValueByKeyByHandle(pMyParser, 'DefferedAnimation', 'cannibalize');
      [*] = ;         ParserSetBoolValueByKeyByHandle(pMyParser, 'AnimRotate', false);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pElmLog : Integer = _log_battle_AddNewElement();
      [*] = ;      ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 8);
      [*] = ;
      [*] = ;      var pSrcUnit : Integer = ParserSelectByHandleByKey(pElmLog, 'SrcUnit');
      [*] = ;      ParserSetIntValueByKeyByHandle(pSrcUnit, 'UID', myUID);
      [*] = ;
      [*] = ;      var pChangedParams : Integer = ParserGetIntValueByKeyByHandle(pSrcUnit, 'ChangedParams');
      [*] = ;      var pChangedParam : Integer = _log_battle_AddChangedParamToParser(pChangedParams);
      [*] = ;      ParserSetIntValueByKeyByHandle(pChangedParam, 'ParamID', 1);
      [*] = ;      ParserSetIntValueByKeyByHandle(pChangedParam, 'Value', lifeBonus);
      [*] = ;
      [*] = ;      _log_battle_Show();
      [*] = ;
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_flesh_eater, 0);
      [*] = ;
      [*] = ;      var stFrame, endFrame : Integer;
      [*] = ;      var exist : Boolean = GetGameObjectFrameAnimationDataByHandle(myGOHandle, 'cannibalize', stFrame, endFrame);
      [*] = ;      if exist then
      [*] = ;         _gv_SetBattleLock(1,_log_name)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ErrorLogI(_log_name+' '+GetGameObjectMyCustomName()+' has no animation cannibalize!');
      [*] = ;         ExecuteState('Idle');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if sendParser then
      [*] = ;      _inet_CreateOrderParser(myUID, -1, -1, gc_inet_actiontype_activateability, 0, gc_ability_flesh_eater, goUID, 0, lanOrderRandKey0, lanOrderRandKey1,'EatCorpse');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

