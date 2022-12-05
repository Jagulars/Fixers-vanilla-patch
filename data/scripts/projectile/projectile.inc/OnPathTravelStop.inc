section.begin
   Name = OnPathTravelStop
   Code : struct.begin
      [*] = ;var _log_name : String = 'PROJECTILE\PROJECTILE.INC\ONPATHTRAVELSTOP';
      [*] = ;var _log_trace : Integer = $800001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myHnd : Integer = GetGameObjectMyHandle();
      [*] = ;
      [*] = ;var ownerUID : Integer = GetIntValueByIndex(gc_stack_projectile_iOwner);
      [*] = ;var ownerGOHnd : Integer = GetGameObjectHandleByUniqueId(ownerUID);
      [*] = ;
      [*] = ;var tUID : Integer = GetIntValueByIndex(gc_stack_projectile_iTarget);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Shooter: '+GetGameObjectCustomNameByHandle(ownerGOHnd)+',Target: '+GetGameObjectCustomNameByHandle(tGOHandle)+']',_log_trace);
      [*] = ;
      [*] = ;if (ownerGOHnd<>0) then
      [*] = ;begin
      [*] = ;   var arrows : Integer = GetGameObjectIntValueIndByHandle(ownerGOHnd, gc_stack_unit_iArrowsCount);
      [*] = ;   if arrows > 0 then
      [*] = ;      SetGameObjectIntValueIndByHandle(ownerGOHnd, gc_stack_unit_iArrowsCount, arrows-1);
      [*] = ;
      [*] = ;   var shotCount : Integer = GetGameObjectIntValueIndByHandle(ownerGOHnd, gc_stack_unit_iShotCount);
      [*] = ;
      [*] = ;   if (arrows = 1) and (shotCount = 0) then // all shots have now hit
      [*] = ;      SetGameObjectIntValueIndByHandle(ownerGOHnd, gc_stack_unit_iTargetUID, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;if tGOHandle <> 0 then
      [*] = ;begin
      [*] = ;   _gv_SetBattleLock(-1,_log_name);
      [*] = ;   GameObjectExecuteStateByHandle(tGOHandle, 'DeathAnimReady');
      [*] = ;
      [*] = ;   var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;   if tCurLife > 0 then
      [*] = ;   begin
      [*] = ;      var pTarParser : Integer = ParserSelectGameObject(tGOHandle);
      [*] = ;      var bUID : Integer = ParserGetIntValueByKeyByHandle(pTarParser, 'BerserkUID');
      [*] = ;
      [*] = ;      if ((ownerUID > 0) and (bUID = ownerUID)) or ((ownerUID = 0) and (bUID = -1)) then
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'PlayBerserkAnimation');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var pTarParser : Integer = ParserSelectGameObject(tGOHandle);
      [*] = ;      var bUID : Integer = ParserGetIntValueByKeyByHandle(pTarParser, 'BerserkUID');
      [*] = ;      if bUID <> 0 then
      [*] = ;         ParserSetIntValueByKeyByHandle(pTarParser, 'BerserkUID', 0);
      [*] = ;      
      [*] = ;      if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 0;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'CheckDeathAnimation');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      _unit_CreateFlyTexts(tGOHandle, ownerUID);
      [*] = ;      _unit_ModifyVisualParams(tGOHandle, ownerUID);
      [*] = ;
      [*] = ;      if _unit_CheckAbility(ownerGOHnd, gc_ability_fire_ammo) > 0 then
      [*] = ;      begin
      [*] = ;         _gui_PlaySound('spells','spell65');
      [*] = ;         var tGridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;         var tGridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;         _unit_ApplyNeighbourVisuals(ownerGOHnd, tGridX, tGridY, 1, true);
      [*] = ;         _unit_ApplyNeighbourVisuals(ownerGOHnd, tGridX, tGridY, 1, false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ExecuteState('CreateBoom');
      [*] = ;end;
      [*] = ;
      [*] = ;SetIntValueByIndex(gc_stack_projectile_iTarget, 0);
      [*] = ;
      [*] = ;var endState : String;
      [*] = ;if gc_RecycleProjectiles then
      [*] = ;   endState := 'Recycle'
      [*] = ;else
      [*] = ;   endState := 'Destroy';
      [*] = ;
      [*] = ;if (_fx_FindFXHandleByID(myHnd, true, 2)<>0) then
      [*] = ;begin
      [*] = ;   GameObjectMyDelayExecuteState(endState, 5); // allow the trail to finish
      [*] = ;   _fx_GetOrCreateFXByID(myHnd, 'fxspiderfirefinish', 0, 0, 0, 0, 0, 2);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (_fx_FindFXHandleByID(myHnd, true, 7)<>0) then
      [*] = ;   begin
      [*] = ;      GameObjectMyDelayExecuteState(endState, 5); // allow the trail to finish
      [*] = ;      _fx_GetOrCreateFXByID(myHnd, 'fxstonetrailfinish', 0, 0, 0, 0, 0, 7);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      GameObjectMyDelayExecuteState(endState, 1); // non-delayed destruction will cause access violation error
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

