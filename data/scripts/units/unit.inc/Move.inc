section.begin
   Name = Move
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\MOVE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;procedure SetupBehaviourFlight(goHandle : Integer; startX, startY, startZ, endX, endY, endZ, speed, parabolaFactor, parabolaH, maxHeight, lowSpeed, lowParabolaFactor : Float);
      [*] = ;begin
      [*] = ;   var pathLenght : Float = VectorDistance(startX, startY, startZ, endX, endY, endZ);
      [*] = ;   if (pathLenght<(gc_HexSize*Sqrt(3)+0.5)) then
      [*] = ;   begin
      [*] = ;      speed := lowSpeed; //speed*0.85;
      [*] = ;      parabolaFactor := lowParabolaFactor; //parabolaFactor*0.1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var behHnd : Integer = BehaviourCreateWithKey(goHandle, 'TXMoveRotateWaveBehaviour', 'flight', false);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'OffsetTime', 0);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosX', 'wscNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosY', 'wscNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosZ', 'wscNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'ClearPaths', '');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathPosition', 'mppUse');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathScale', 'mpsNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathRotate', 'mprNone');
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'AddPath', '');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,0]', startX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,0]', startY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,0]', startZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,0]', speed);
      [*] = ;
      [*] = ;   var addHeight : Float = pathLenght*parabolaFactor;
      [*] = ;   if (addHeight>maxHeight) then
      [*] = ;   addHeight := maxHeight;
      [*] = ;
      [*] = ;   var dirX : Float = endX-startX;
      [*] = ;   var dirY : Float = 0;
      [*] = ;   var dirZ : Float = endZ-startZ;
      [*] = ;   VectorNormalize(dirX, dirY, dirZ);
      [*] = ;
      [*] = ;   var midX1 : Float = (startX+dirX*pathLenght*parabolaH);
      [*] = ;   var midY1 : Float = (startY+endY)/2 + addHeight;
      [*] = ;   var midZ1 : Float = (startZ+dirZ*pathLenght*parabolaH);
      [*] = ;
      [*] = ;   var midX2 : Float = (endX-dirX*pathLenght*parabolaH);
      [*] = ;   var midY2 : Float = (startY+endY)/2 + addHeight;
      [*] = ;   var midZ2 : Float = (endZ-dirZ*pathLenght*parabolaH);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,1]', midX1);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,1]', midY1);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,1]', midZ1);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,1]', speed);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,2]', midX2);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,2]', midY2);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,2]', midZ2);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,2]', speed);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,3]', endX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,3]', endY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,3]', endZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,3]', speed*0.02);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'OnStatePathTravelStop', '');
      [*] = ;
      [*] = ;   SetBehaviourIntProperty(behHnd, 'ActivePathIndex', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsLooped[0]', false);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;   //SetBehaviourFloatProperty(behHnd, 'StartTime[0]', GetCurrentTime-(Random*estimateTime));
      [*] = ;   SetBehaviourStringProperty(behHnd, 'StartPathTravel', '');
      [*] = ;   var estimateTime : Float = GetBehaviourFloatProperty(behHnd, 'EstimateTime[0]');
      [*] = ;   //SetBehaviourBoolProperty(behHnd, 'PathsShowPath[0]', True);
      [*] = ;end;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;
      [*] = ;if (not gBoolRegister_BattlePlaceMode) then
      [*] = ;   ExecuteState('DoPathStaminaCharge');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var moveType : Integer = _unit_GetMoveType(myGOHandle);
      [*] = ;
      [*] = ;if (moveType>0) then
      [*] = ;begin
      [*] = ;   var ownerGOHnd : Integer = GetGameObjectHandleByUniqueId(GetIntValueByIndex(gc_stack_projectile_iOwner));
      [*] = ;   var startX, startY, startZ : Float;
      [*] = ;   startX := GetGameObjectMyPositionX;
      [*] = ;   startY := GetGameObjectMyPositionY;
      [*] = ;   startZ := GetGameObjectMyPositionZ;
      [*] = ;   var endX, endY, endZ : Float;
      [*] = ;   var tpCount : Integer = GetGameObjectTrackPointCountByHandle(myGOHandle);
      [*] = ;   GetGameObjectTrackPointCoordsByIndexByHandle(myGOHandle, tpCount-1, endX, endY, endZ);
      [*] = ;   endY := RayCastHeight(endX, endZ);
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=tpCount-2 downto 0 do
      [*] = ;   begin
      [*] = ;      GameObjectTrackPointDeleteByHandle(myGOHandle, i);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var speed : Float = 10;
      [*] = ;   var projX, proj, projZ, parabola, parabolaH, maxHeight : Float = 0;
      [*] = ;
      [*] = ;   var baseName : String = GetGameObjectBaseNameByHandle(myGOHandle);
      [*] = ;   GameObjectSwitchToAnimationCyclesBlendByHandle(myGOHandle, 'walk', false, false, 4, 8);
      [*] = ;   var stFrame, endFrame : Integer;
      [*] = ;   var exist : Boolean = GetGameObjectFrameAnimationDataByHandle(myGOHandle, 'up', stFrame, endFrame);
      [*] = ;   if (exist) then
      [*] = ;   GameObjectSwitchToFBAnimationCyclesBlendByHandle(myGOHandle, 'up', false, false, 8, 12);
      [*] = ;
      [*] = ;   var pMy : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;   var speedfactor, lowSpeed, lowParabolaFactor : Float = 1;
      [*] = ;
      [*] = ;   if (pMy<>0) then
      [*] = ;   begin
      [*] = ;      var tpms : Float = ParserGetFloatValueByKeyByHandle(pMy, 'TPMoveStep');
      [*] = ;      var tpts : Float = ParserGetFloatValueByKeyByHandle(pMy, 'TPTurnStep');
      [*] = ;      var waif : Float = ParserGetFloatValueByKeyByHandle(pMy, 'WalkAnimIntervalFactor');
      [*] = ;
      [*] = ;      var speedBoost : Float;
      [*] = ;      if (gFloatRegister_UnitMoveSpeedBoost=0) then
      [*] = ;      speedBoost := 1
      [*] = ;      else
      [*] = ;      speedBoost := gFloatRegister_UnitMoveSpeedBoost;
      [*] = ;
      [*] = ;      IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;      ExecuteState('GetProperty');
      [*] = ;      var speed : Integer = IntRegister1;
      [*] = ;      var unitID : Integer = GetIntValueByIndex(gc_stack_unit_iUnitID);
      [*] = ;      var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;      var baseSpeed : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Speed');
      [*] = ;      var effectSpeedBoost : Float = 1;
      [*] = ;      if (baseSpeed<>0) then
      [*] = ;      begin
      [*] = ;         effectSpeedBoost := speed/baseSpeed;
      [*] = ;         if (effectSpeedBoost>2) then
      [*] = ;         effectSpeedBoost := 2
      [*] = ;         else
      [*] = ;         if (effectSpeedBoost<0.5) then
      [*] = ;         effectSpeedBoost := 0.5;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var battlespeed : Float = _misc_GetBattleSpeed();
      [*] = ;      speedfactor := speedBoost*gFloatRegister_UnitMoveSpeedBoost*effectSpeedBoost*(gc_battle_speed_min+(battlespeed*(gc_battle_speed_max-gc_battle_speed_min)));
      [*] = ;      if battlespeed=1 then speedfactor:=gc_battle_speed_absolute_max;
      [*] = ;      tpms := tpms*speedfactor;
      [*] = ;      tpts := tpts*speedfactor;
      [*] = ;      waif := waif*speedfactor;
      [*] = ;
      [*] = ;      SetGameObjectMyTrackPointMoveStep(tpms/2);
      [*] = ;      SetGameObjectMyTrackPointMoveStepInterval(100); // for flight only, to get better accuracy
      [*] = ;      SetGameObjectMyTrackPointTurnStep(tpts);
      [*] = ;      SetGameObjectIntervalFactorByHandle(myGOHandle, waif);
      [*] = ;   end;
      [*] = ;
      [*] = ;   case baseName of
      [*] = ;      'pegasus' : begin
      [*] = ;         speed := 6;
      [*] = ;         parabola := 1.3;
      [*] = ;         maxHeight := 4;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'griffin' : begin
      [*] = ;         speed := 5.5;
      [*] = ;         parabola := 0.4;
      [*] = ;         maxHeight := 6;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'fairy' : begin
      [*] = ;         speed := 5;
      [*] = ;         parabola := 0.3;
      [*] = ;         maxHeight := 3.5;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'succubus' : begin
      [*] = ;         speed := 5;
      [*] = ;         parabola := 0.3;
      [*] = ;         maxHeight := 3.5;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'dragon', 'dragonfire', 'dragonstorm', 'dragonunholy' : begin
      [*] = ;         speed := 8;
      [*] = ;         parabola := 0.5;
      [*] = ;         maxHeight := 3;
      [*] = ;         lowSpeed := 0.675;
      [*] = ;         lowParabolaFactor := 0.3;
      [*] = ;      end;
      [*] = ;      'chimera' : begin
      [*] = ;         speed := 8;
      [*] = ;         parabola := 0.5;
      [*] = ;         maxHeight := 3;
      [*] = ;         lowSpeed := 0.675;
      [*] = ;         lowParabolaFactor := 0.3;
      [*] = ;      end;
      [*] = ;      'gargoyle', 'gargoylecrystal', 'gargoyleobsidian' : begin
      [*] = ;         speed := 5;
      [*] = ;         parabola := 0.5;
      [*] = ;         maxHeight := 5;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'ghost' : begin
      [*] = ;         speed := 5;
      [*] = ;         parabola := 0.4;
      [*] = ;         maxHeight := 4;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'harpy' : begin
      [*] = ;         speed := 5;
      [*] = ;         parabola := 0.4;
      [*] = ;         maxHeight := 4;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'imp' : begin
      [*] = ;         speed := 5;
      [*] = ;         parabola := 0.5;
      [*] = ;         maxHeight := 5;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'manticore' : begin
      [*] = ;         speed := 6;
      [*] = ;         parabola := 0.2;
      [*] = ;         maxHeight := 6;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'phoenix' : begin
      [*] = ;         speed := 6;
      [*] = ;         parabola := 0.5;
      [*] = ;         maxHeight := 4;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.25;
      [*] = ;      end;
      [*] = ;      'vampire' : begin
      [*] = ;         speed := 7;
      [*] = ;         parabola := 0.5;
      [*] = ;         maxHeight := 5;
      [*] = ;         lowSpeed := 0.7;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      'daemon', 'daemonice' : begin
      [*] = ;         speed := 5;
      [*] = ;         parabola := 0.5;
      [*] = ;         maxHeight := 5;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ErrorLogI(_log_name+' Move, unknown fly unit settings');
      [*] = ;         speed := 5;
      [*] = ;         parabola := 0.5;
      [*] = ;         maxHeight := 5;
      [*] = ;         lowSpeed := 0.85;
      [*] = ;         lowParabolaFactor := 0.1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //endY := endY+targetH;
      [*] = ;
      [*] = ;   speed := speed*speedfactor;
      [*] = ;   lowSpeed := speed*lowSpeed;
      [*] = ;   const cParabolaH = 0.25; //do not set value lower then 0.25 or unit will flight backward first. (cause of spline normalize)
      [*] = ;
      [*] = ;   SetupBehaviourFlight(myGOHandle, startX, startY, startZ, endX, endY, endZ, speed, parabola, cParabolaH, maxHeight, lowSpeed, lowParabolaFactor);
      [*] = ;   SetGameObjectEpsilonDistanceByHandle(myGOHandle, 0.04);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   GameObjectMySwitchToTreeAnimationCycles('walk', false, false, false, false);
      [*] = ;
      [*] = ;   var pMy : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;   var tpms : Float = ParserGetFloatValueByKeyByHandle(pMy, 'TPMoveStep');
      [*] = ;   var tpts : Float = ParserGetFloatValueByKeyByHandle(pMy, 'TPTurnStep');
      [*] = ;   var waif : Float = ParserGetFloatValueByKeyByHandle(pMy, 'WalkAnimIntervalFactor');
      [*] = ;   var speedBoost : Float;
      [*] = ;   if (gFloatRegister_UnitMoveSpeedBoost=0) then
      [*] = ;      speedBoost := 1
      [*] = ;   else
      [*] = ;      speedBoost := gFloatRegister_UnitMoveSpeedBoost;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var speed : Integer = IntRegister1;
      [*] = ;   var unitID : Integer = GetIntValueByIndex(gc_stack_unit_iUnitID);
      [*] = ;   var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;   var baseSpeed : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Speed');
      [*] = ;   var effectSpeedBoost : Float = 1;
      [*] = ;   if (baseSpeed<>0) then
      [*] = ;   begin
      [*] = ;      effectSpeedBoost := speed/baseSpeed;
      [*] = ;      if (effectSpeedBoost>2) then
      [*] = ;         effectSpeedBoost := 2
      [*] = ;      else
      [*] = ;         if (effectSpeedBoost<0.5) then
      [*] = ;            effectSpeedBoost := 0.5;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var battlespeed : Float = _misc_GetBattleSpeed();
      [*] = ;   var speedfactor : Float = speedBoost*gFloatRegister_UnitMoveSpeedBoost*effectSpeedBoost*(gc_battle_speed_min+(battlespeed*(gc_battle_speed_max-gc_battle_speed_min)));
      [*] = ;   if battlespeed=1 then
      [*] = ;      speedfactor:=gc_battle_speed_absolute_max;
      [*] = ;   tpms := tpms*speedfactor;
      [*] = ;   tpts := tpts*speedfactor;
      [*] = ;   waif := waif*speedfactor;
      [*] = ;
      [*] = ;   SetGameObjectMyTrackPointMoveStep(tpms);
      [*] = ;   SetGameObjectMyTrackPointTurnStep(tpts);
      [*] = ;   SetGameObjectIntervalFactorByHandle(myGOHandle, waif);
      [*] = ;end;
      [*] = ;
      [*] = ;//_unit_PlaySoundLoop(myGOHandle, 'units', 'walk', gc_SoundLoopTagWalk, True);
      [*] = ;var baseName : String = GetGameObjectMyBaseName();
      [*] = ;case baseName of
      [*] = ;   'dragon', 'griffin', 'manticore', 'pegasus', 'phoenix', 'vampire', 'dragonfire', 'dragonstorm', 'dragonunholy' : begin
      [*] = ;      _unit_PlaySound(myGOHandle, 'units', 'up');
      [*] = ;      _unit_PlaySoundLoop(myGOHandle, 'units', 'walk', gc_SoundLoopTagWalk, True);
      [*] = ;   end;
      [*] = ;   else
      [*] = ;   begin
	  [*] = ;      _unit_PlaySoundLoop(myGOHandle, 'units', 'walk', gc_SoundLoopTagWalk, True);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;//_unit_PlaySoundLoop(myGOHandle, 'units', 'idle', gc_SoundLoopTagIdle, False);
      [*] = ;_gv_SetBattleLock(1,_log_name);
      [*] = ;
      [*] = ;_fx_ShowEnvironmentAroundTacticalUnit(GetGameObjectMyHandle);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

