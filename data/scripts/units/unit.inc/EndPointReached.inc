section.begin
   Name = EndPointReached
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\ENDPOINTREACHED';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;const cEpsilonAngle = 10;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;_unit_CreateFlyTexts(myGOHandle, myUID);
      [*] = ;_unit_ModifyVisualParams(myGOHandle, myUID);
      [*] = ;_fx_StartFlyText_VVK(0);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyBaseName()+', UID: '+IntToStr(myUID)+', TargetUID: '+IntToStr(GetIntValueByIndex(gc_stack_unit_iTargetUID))+']',_log_trace);
      [*] = ;
      [*] = ;_gv_SetBattleLock(-1,_log_name);
      [*] = ;
      [*] = ;var animName : String = ParserGetValueByKeyByHandle(pMyParser, 'DefferedAnimation');
      [*] = ;if animName <> '' then
      [*] = ;begin
      [*] = ;   var rotate : Boolean = ParserGetBoolValueByKeyByHandle(pMyParser, 'AnimRotate');
      [*] = ;   var animX : Float = ParserGetFloatValueByKeyByHandle(pMyParser, 'AnimTargetX');
      [*] = ;   var animY : Float = ParserGetFloatValueByKeyByHandle(pMyParser, 'AnimTargetY');
      [*] = ;
      [*] = ;   if rotate then
      [*] = ;   begin
      [*] = ;      var dirX : Float = GetGameObjectMyTransformedVirtualDirectionX;
      [*] = ;      var dirY : Float = GetGameObjectMyTransformedVirtualDirectionY;
      [*] = ;      var dirZ : Float = GetGameObjectMyTransformedVirtualDirectionZ;
      [*] = ;
      [*] = ;      var dirX1 : Float = animX - GetGameObjectMyPositionX;
      [*] = ;      var dirY1 : Float = 0;
      [*] = ;      var dirZ1 : Float = animY - GetGameObjectMyPositionZ;
      [*] = ;
      [*] = ;      var angle : Float = VectorAngle(dirX, dirY, dirZ, dirX1, dirY1, dirZ1);
      [*] = ;
      [*] = ;      if angle > cEpsilonAngle then
      [*] = ;      begin
      [*] = ;         SetGameObjectMyRotatingTargetCoords(animX, 0, animY);
      [*] = ;         SetGameObjectMyTrackPointAnimationNames('', '');
      [*] = ;
      [*] = ;         var tpts : Float = ParserGetFloatValueByKeyByHandle(pMyParser, 'TPTurnStep');
      [*] = ;         SetGameObjectMyTrackPointTurnStep(tpts*angle/60*_misc_CalcBattleSpeedModified(gc_battle_unit_turnspeedmod));
      [*] = ;         SetGameObjectMyTargetRotatingMode('trmToTargetCoordinates');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _unit_ModifyAnimIntervalFactor(myGOHandle, gc_battle_unit_attackspeedmod);
      [*] = ;   GameObjectMySwitchToTreeAnimationCyclesDefault(animName);
      [*] = ;
      [*] = ;   ParserSetValueByKeyByHandle(pMyParser, 'DefferedAnimation', '');
      [*] = ;   ParserSetBoolValueByKeyByHandle(pMyParser, 'AnimRotate', false);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pMyParser, 'AnimTargetX', 0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pMyParser, 'AnimTargetY', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;var stFrame, endFrame : Integer;
      [*] = ;var exist : Boolean = GetGameObjectFrameAnimationDataByHandle(myGOHandle, 'down', stFrame, endFrame);
      [*] = ;if (exist) then
      [*] = ;   GameObjectSwitchToFBAnimationCyclesBlendByHandle(myGOHandle, 'down', false, false, 4, 8);
      [*] = ;
      [*] = ;var aType : Integer = GetIntValueByIndex(gc_stack_unit_iActionType);
      [*] = ;
      [*] = ;//if aType = 2 then
      [*] = ;begin
      [*] = ;   BoolRegister0 := false;
      [*] = ;   ExecuteState('CheckTargetAction');
      [*] = ;end;
      [*] = ;
      [*] = ;if (aType <= 1) and (GetIntValueByIndex(gc_stack_unit_iTargetUID) > 0) then
      [*] = ;begin
      [*] = ;   BoolRegister0 := false;
      [*] = ;   ExecuteState('CheckAttackAnimation');
      [*] = ;end;
      [*] = ;
      [*] = ;{if _misc_IsLanBattle() then
      [*] = ;begin
      [*] = ;   _inet_ExecuteLanSyncParser();
      [*] = ;   _inet_ExecuteUnitLanSyncParser(myGOHandle);
      [*] = ;end;}
      [*] = ;
      [*] = ;SetIntValueByIndex(gc_stack_unit_iLastX, GetIntValueByIndex(gc_stack_unit_iCurrentX));
      [*] = ;SetIntValueByIndex(gc_stack_unit_iLastY, GetIntValueByIndex(gc_stack_unit_iCurrentY));
      [*] = ;
      [*] = ;_fx_HideEnvironmentAroundTacticalUnit(myGOHandle);
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   //_unit_PlaySoundLoop(myGOHandle, 'units', 'walk', gc_SoundLoopTagWalk, False);
      [*] = ;   //var baseName : String = GetGameObjectMyBaseName();
      [*] = ;   _unit_PlaySoundLoop(myGOHandle, 'units', 'walk', gc_SoundLoopTagWalk, False);
      [*] = ;   if (exist) then
      [*] = ;      _unit_PlaySound(myGOHandle, 'units', 'down');
      [*] = ;end;
      [*] = ;
      [*] = ;//IntRegister0 := GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;//MapExecuteState('bat.KillDeadUnits');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

