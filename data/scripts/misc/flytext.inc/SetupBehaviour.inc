section.begin
   Name = SetupBehaviour
   Code : struct.begin
      [*] = ;var _log_name : String = 'MISC\FLYTEXT.INC\SETUPBEHAVIOUR';
      [*] = ;var _log_trace : Integer = $800001;
      [*] = ;
      [*] = ;procedure SetupBehaviour(goHandle : Integer);
      [*] = ;begin
      [*] = ;   var posX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;   var posY : Float = GetGameObjectPositionYByHandle(goHandle);
      [*] = ;   var posZ : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;   var i : Integer;
      [*] = ;   var stepY, stepZ, stepDY, stepDZ, speed : Float = 0;
      [*] = ;   var speedMod : Float = _fx_GetFlyTextSpeedMod();
      [*] = ;   var sStep : Float = 0.36 * speedMod;
      [*] = ;   var sSpeed : Float = 3.6 * speedMod;
      [*] = ;   var count : Integer = Round(40 / speedMod);
      [*] = ;   var behHnd : Integer = BehaviourCreate(goHandle, 'TXMoveRotateWaveBehaviour', true, false);
      [*] = ;
      [*] = ;   stepY := ParserGetFloatValueByKeyByHandle(ParserSelectByHandleByIndex(_map_GetHexCells(),gc_battle_GridSize), 'CenterY');
      [*] = ;   if stepY > posZ then
      [*] = ;   begin
      [*] = ;      stepY := posY;
      [*] = ;      stepDY := 0;
      [*] = ;      stepZ := posZ+sStep;
      [*] = ;      stepDZ := sStep;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      stepY := posY+sStep;
      [*] = ;      stepDY := sStep;
      [*] = ;      stepZ := posZ;
      [*] = ;      stepDZ := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'OffsetTime', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'ClearPaths', '');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathPosition', 'mppUse');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'AddPath', '');
      [*] = ;
      [*] = ;   for i:=0 to count-1 do
      [*] = ;   begin
      [*] = ;      speed := sSpeed;
      [*] = ;      stepY := stepY+stepDY;
      [*] = ;      stepZ := stepZ+stepDZ;
      [*] = ;      SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,'+IntToStr(i)+']', posX);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,'+IntToStr(i)+']', stepY);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,'+IntToStr(i)+']', stepZ);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,'+IntToStr(i)+']', speed);
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsPathSplineMode[0]', 'lsmBezierSpline'); // lsmLines, lsmCubicSpline, lsmBezierSpline, lsmNURBSCurve, lsmSegments
      [*] = ;
      [*] = ;   SetBehaviourIntProperty(behHnd, 'ActivePathIndex', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsLooped[0]', false);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'StartPathTravel', '');
      [*] = ;   
      [*] = ;   //if gc_RecycleFlyTexts then
      [*] = ;   //   SetBehaviourStringProperty(behHnd, 'OnStatePathTravelStop', 'Recycle') // for some reason never triggers
      [*] = ;   //else
      [*] = ;      SetBehaviourStringProperty(behHnd, 'OnStatePathTravelStop', 'Destroy');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;
      [*] = ;SetupBehaviour(GetGameObjectMyHandle());
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

