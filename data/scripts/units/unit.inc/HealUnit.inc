section.begin
   Name = HealUnit
   Description : struct.begin
      [*] = ;IntRegister0 - game object handle
   struct.end
   Code : struct.begin
      [*] = ;var sendParser : Boolean = BoolRegister0;
      [*] = ;var tGOHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\HEALUNIT';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var tUID : Integer = GetGameObjectUniqueIdByHandle(tGOHandle);
      [*] = ;
      [*] = ;const cEpsilonAngle = 10;
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;var autoBattle : Boolean = GetPlayerBoolValueIndByHandle(myPlHandle, gc_battle_PLStack_bAutoBattle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myHandle);
      [*] = ;
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;
      [*] = ;var pElmLog : Integer = 0;
      [*] = ;var pSrcUnit : Integer = 0;
      [*] = ;var pDestUnit : Integer = 0;
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iCurAmmo;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var curAmmo : Integer = IntRegister1;
      [*] = ;
      [*] = ;if curAmmo > 0 then
      [*] = ;begin
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      if GetGameObjectMyTrackPointMovementMode = 'mmNone' then
      [*] = ;      begin
      [*] = ;         if (myHandle <> tGOHandle) then
      [*] = ;         begin
      [*] = ;            var dirX : Float = GetGameObjectMyTransformedVirtualDirectionX;
      [*] = ;            var dirY : Float = GetGameObjectMyTransformedVirtualDirectionY;
      [*] = ;            var dirZ : Float = GetGameObjectMyTransformedVirtualDirectionZ;
      [*] = ;
      [*] = ;            var dirX1 : Float = GetGameObjectPositionXByHandle(tGOHandle) - GetGameObjectMyPositionX;
      [*] = ;            var dirY1 : Float = GetGameObjectPositionYByHandle(tGOHandle) - GetGameObjectMyPositionY;
      [*] = ;            var dirZ1 : Float = GetGameObjectPositionZByHandle(tGOHandle) - GetGameObjectMyPositionZ;
      [*] = ;
      [*] = ;            var angle : Float = VectorAngle(dirX, dirY, dirZ, dirX1, dirY1, dirZ1);
      [*] = ;
      [*] = ;            if angle > cEpsilonAngle then
      [*] = ;            begin
      [*] = ;               SetGameObjectMyRotatingTargetCoords(GetGameObjectPositionXByHandle(tGOHandle), GetGameObjectPositionYByHandle(tGOHandle), GetGameObjectPositionZByHandle(tGOHandle));
      [*] = ;               SetGameObjectMyTrackPointAnimationNames('', '');
      [*] = ;
      [*] = ;               var tpts : Float = ParserGetFloatValueByKeyByHandle(pMyParser, 'TPTurnStep');
      [*] = ;               SetGameObjectMyTrackPointTurnStep(tpts*angle/60*_misc_CalcBattleSpeedModified(gc_battle_unit_turnspeedmod));
      [*] = ;               SetGameObjectMyTargetRotatingMode('trmToTargetCoordinates');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         _unit_ModifyAnimIntervalFactor(myHandle, gc_battle_unit_attackspeedmod);
      [*] = ;         GameObjectMySwitchToTreeAnimationCyclesDefault('heal');
      [*] = ;         _unit_PlaySound(myHandle, 'units', 'heal');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var tarX : Float = GetGameObjectPositionXByHandle(tGOHandle);
      [*] = ;         var tarZ : Float = GetGameObjectPositionZByHandle(tGOHandle);
      [*] = ;
      [*] = ;         ParserSetValueByKeyByHandle(pMyParser, 'DefferedAnimation', 'heal');
      [*] = ;         ParserSetBoolValueByKeyByHandle(pMyParser, 'AnimRotate', true);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pMyParser, 'AnimTargetX', tarX);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pMyParser, 'AnimTargetY', tarZ);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var stFrame, endFrame : Integer;
      [*] = ;      var exist : Boolean = GetGameObjectFrameAnimationDataByHandle(myHandle, 'heal', stFrame, endFrame);
      [*] = ;      if exist then
      [*] = ;         _gv_SetBattleLock(1,_log_name)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ErrorLogI(_log_name+' '+GetGameObjectMyCustomName() + ' has no animation heal!');
      [*] = ;         ExecuteState('Idle');
      [*] = ;      end;
      [*] = ;
      [*] = ;      pElmLog := _log_battle_AddNewElement;
      [*] = ;      ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 5);
      [*] = ;
      [*] = ;      pSrcUnit := ParserSelectByHandleByKey(pElmLog, 'SrcUnit');
      [*] = ;      ParserSetIntValueByKeyByHandle(pSrcUnit, 'UID', myUID);
      [*] = ;
      [*] = ;      var pDestUnits : Integer = ParserSelectByHandleByKey(pElmLog, 'DestUnits');
      [*] = ;      pDestUnit := _log_battle_AddUnitInfoToParser(pDestUnits);
      [*] = ;      ParserSetIntValueByKeyByHandle(pDestUnit, 'UID', tUID);
      [*] = ;   end;
      [*] = ;
      [*] = ;   //IntRegister0 := gc_battle_unit_iShootingRange;
      [*] = ;   //ExecuteState('GetProperty');
      [*] = ;   //var shootingRange : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var myX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;   var myY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;   var goX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;   var goY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;   var pHexCell : Integer = _map_GetBattleHex(goX, goY);
      [*] = ;
      [*] = ;   if (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      var pMyHex : Integer = _map_GetBattleHex(myX, myY);
      [*] = ;      if pMyHex <> pHexCell then
      [*] = ;         SetIntValueByIndex(gc_stack_unit_iFacing, _map_GetFacing(pMyHex, pHexCell));
      [*] = ;   end;
      [*] = ;
      [*] = ;   //IntRegister0 := goX;
      [*] = ;   //IntRegister1 := goY;
      [*] = ;   //StateMachineExecuteState(initMachine, 'bat.GetHexByCoords', 0);
      [*] = ;   //var pHexCell : Integer = IntRegister2;
      [*] = ;
      [*] = ;   //if ((goX = myX) and (goY = myY)) or (ParserGetIntValueByKeyByHandle(pHexCell, 'Shoot') > 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_battle_unit_iCurLife;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'GetProperty');
      [*] = ;      var goLife : Integer = IntRegister1;
      [*] = ;      var oldLife : Integer = goLife;
      [*] = ;
      [*] = ;      IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'GetProperty');
      [*] = ;      var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;      if goLife < maxLife then
      [*] = ;      begin
      [*] = ;         // check heal ability
      [*] = ;         var abil24 : Integer = _unit_CheckAbility(myHandle, gc_ability_healing);
      [*] = ;         var abil132 : Integer = _unit_CheckAbility(myHandle, gc_ability_repair);
      [*] = ;
      [*] = ;         var healHP : Integer;
      [*] = ;         if abil24 > 0 then
      [*] = ;            healHP := abil24
      [*] = ;         else
      [*] = ;            healHP := abil132;
      [*] = ;
      [*] = ;         if not gBoolRegister_BattleSimulate then
      [*] = ;            healHP := healHP + 1 - Floor(RandomExt * 3);
      [*] = ;
      [*] = ;         if healHP + goLife > maxLife then
      [*] = ;            healHP := maxLife - goLife;
      [*] = ;
      [*] = ;         goLife := goLife + healHP;
      [*] = ;         SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife, goLife);
      [*] = ;
      [*] = ;         curAmmo := curAmmo - 1;
      [*] = ;         SetGameObjectMyIntValueInd(gc_stack_unit_iCurAmmo, curAmmo);
      [*] = ;
      [*] = ;         var healed : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iDamageHealed);
      [*] = ;         SetGameObjectMyIntValueInd(gc_stack_unit_iDamageHealed, healed + healHP);
      [*] = ;
      [*] = ;         if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;         begin
      [*] = ;            _fx_CreateFlyText_VVK(tGOHandle, gc_flytext_CategoryParam, gc_battle_unit_iCurLife, healHP);
      [*] = ;
      [*] = ;            var pChangedParams : Integer = ParserSelectByHandleByKey(pDestUnit, 'ChangedParams');
      [*] = ;            var pChangedParam : Integer = _log_battle_AddChangedParamToParser(pChangedParams);
      [*] = ;            ParserSetIntValueByKeyByHandle(pChangedParam, 'ParamID', 1);
      [*] = ;            ParserSetIntValueByKeyByHandle(pChangedParam, 'Value', healHP);
      [*] = ;
      [*] = ;            _log_battle_Show();
      [*] = ;
      [*] = ;            if (GetGameObjectMyIntValueInd(gc_stack_unit_iUnitID) <> 8) and _obj_EnabledByFlag(gc_ObjectFlagBattleFX) then // no ray of light with Healer
      [*] = ;               _fx_GetOrCreateFXByID(tGOHandle, 'fxray', 0, 0, 0, 0, 0, 4);
      [*] = ;
      [*] = ;            _unit_GUIUpdateUnitHUD(tGOHandle);
      [*] = ;         end;
      [*] = ;
      [*] = ;         IntRegister0 := -1;
      [*] = ;         ExecuteState('ChangeStamina');
      [*] = ;         ExecuteState('ActionDone');
      [*] = ;
      [*] = ;         if sendParser then
      [*] = ;            _inet_CreateOrderParser(myUID, -1, -1, gc_inet_actiontype_heal, 0, 0, tUID, 0, lanOrderRandKey0, lanOrderRandKey1,'HealUnit');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

