section.begin
   Name = VisualFireAttack
   Code : struct.begin
      [*] = ;const cEpsilonAngle = 10;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;var tUID : Integer = GetIntValueByIndex(gc_stack_unit_iTargetUID);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;
      [*] = ;var dirX : Float = GetGameObjectMyTransformedVirtualDirectionX;
      [*] = ;var dirY : Float = GetGameObjectMyTransformedVirtualDirectionY;
      [*] = ;var dirZ : Float = GetGameObjectMyTransformedVirtualDirectionZ;
      [*] = ;
      [*] = ;var dirX1 : Float = GetGameObjectPositionXByHandle(tGOHandle) - GetGameObjectMyPositionX;
      [*] = ;var dirY1 : Float = GetGameObjectPositionYByHandle(tGOHandle) - GetGameObjectMyPositionY;
      [*] = ;var dirZ1 : Float = GetGameObjectPositionZByHandle(tGOHandle) - GetGameObjectMyPositionZ;
      [*] = ;
      [*] = ;var angle : Float = VectorAngle(dirX, dirY, dirZ, dirX1, dirY1, dirZ1);
      [*] = ;
      [*] = ;if angle > cEpsilonAngle then
      [*] = ;begin
      [*] = ;   SetGameObjectMyRotatingTargetCoords(GetGameObjectPositionXByHandle(tGOHandle), GetGameObjectPositionYByHandle(tGOHandle), GetGameObjectPositionZByHandle(tGOHandle));
      [*] = ;   SetGameObjectMyTrackPointAnimationNames('', '');
      [*] = ;
      [*] = ;   var tpts : Float = ParserGetFloatValueByKeyByHandle(pMyParser, 'TPTurnStep');
      [*] = ;   SetGameObjectMyTrackPointTurnStep(tpts*angle/60*_misc_CalcBattleSpeedModified(gc_battle_unit_turnspeedmod));
      [*] = ;   SetGameObjectMyTargetRotatingMode('trmToTargetCoordinates');
      [*] = ;end;
      [*] = ;
      [*] = ;_unit_ModifyAnimIntervalFactor(myGOHandle, gc_battle_unit_attackspeedmod);
      [*] = ;if SameText(GetGameObjectMyAnimationCycleName, 'shot') then
      [*] = ;GameObjectMySwitchToTreeAnimationCyclesDefault('idle');
      [*] = ;GameObjectMySwitchToTreeAnimationCyclesDefault('shot');
      [*] = ;_unit_PlaySound(myGOHandle, 'units', 'shot');
      [*] = ;
      [*] = ;var stFrame, endFrame : Integer;
      [*] = ;if not GetGameObjectFrameAnimationDataByHandle(myGOHandle, 'shot', stFrame, endFrame) then
      [*] = ;begin
      [*] = ;   ErrorLogI(GetGameObjectMyCustomName()+' has no animation shot!');
      [*] = ;   ExecuteState('Idle');
      [*] = ;end;
      [*] = ;
      [*] = ;var FrameShift : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iShotFrame);
      [*] = ;var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myGOHandle);
      [*] = ;var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myGOHandle);
      [*] = ;var DelayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor);
      [*] = ;GameObjectMyDelayExecuteState('CreateProjectile', DelayTime);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

