section.begin
   Name = DoInertiaFall
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'MISC\BUILD.INC\DOINERTIAFALL';
      [*] = ;var _log_trace : Integer = $800000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;procedure SetupBehaviour(goHandle : Integer);
      [*] = ;begin
      [*] = ;   GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;   SetGameObjectAutoOffsetByHandle(goHandle, false);
      [*] = ;   var posX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;   var posY : Float = GetGameObjectPositionYByHandle(goHandle);
      [*] = ;   var posZ : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;
      [*] = ;   var behHnd : Integer = BehaviourCreate(goHandle, 'TXMoveRotateWaveBehaviour', true, false);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'OffsetTime', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'ClearPaths', '');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathPosition', 'mppUse');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'AddPath', '');
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   var step, speed : Float = 0;
      [*] = ;   var sStep : Float = 0.002*(1+Random*0.6);
      [*] = ;   var sSpeed : Float = 0.04{*(0.9+Random*0.2)};
      [*] = ;   var count : Integer = 20;
      [*] = ;   for i:=0 to count-1 do
      [*] = ;   begin
      [*] = ;      step := sStep*pow(1.65, i);
      [*] = ;      speed := sSpeed*pow(1.45, i);
      [*] = ;      if (i=(count-1)) then
      [*] = ;      step := 8;
      [*] = ;      SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,'+IntToStr(i)+']', posX);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,'+IntToStr(i)+']', posY-step);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,'+IntToStr(i)+']', posZ);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,'+IntToStr(i)+']', speed);
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsPathSplineMode[0]', 'lsmBezierSpline'); // lsmLines, lsmCubicSpline, lsmBezierSpline, lsmNURBSCurve, lsmSegments
      [*] = ;
      [*] = ;   SetBehaviourIntProperty(behHnd, 'ActivePathIndex', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsLooped[0]', false);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'StartPathTravel', '');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure InertiaDownObjectsInRadius(posX, posZ, radius : Float);
      [*] = ;begin
      [*] = ;   const cNatureRaceTag = 30;
      [*] = ;   const cBuildingsRaceTag = 10;
      [*] = ;   const cTownPatternPlName = 'townPattern';
      [*] = ;   const cTownQuarterPlName = 'townQuarter';
      [*] = ;   //const cPatternPlName = 'Pattern';
      [*] = ;   const cBldRaceName = 'buildings';
      [*] = ;   const speed : Float = -5.0;
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cTownPatternPlName);
      [*] = ;   //var plHnd : Integer = GetPlayerHandleByName(cPatternPlName);
      [*] = ;   GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, cNatureRaceTag, 0, false, false, false, false, false, false);
      [*] = ;   var j : Integer;
      [*] = ;   for j:=0 to GetGameObjectListCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;      var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;      var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;
      [*] = ;      if (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) and (not StrExists(GetGameObjectBaseNameByHandle(goHnd), 'hill')) then
      [*] = ;      begin
      [*] = ;         //var behHnd : Integer = GetBehaviourByClassName(goHnd, 'TXMoveRotateWaveBehaviour');
      [*] = ;         //if (behHnd<>0) then
      [*] = ;         AddObjectToDestroyList(goHnd);
      [*] = ;         //else
      [*] = ;         //SetupBehaviour(goHnd);//SetupInertiaBehaviour(goHnd, speed);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, cBuildingsRaceTag, 0, false, false, false, false, false, false);
      [*] = ;   for j:=0 to GetGameObjectListCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;      var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;      var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;
      [*] = ;      if (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;      begin
      [*] = ;         //var behHnd : Integer = GetBehaviourByClassName(goHnd, 'TXMoveRotateWaveBehaviour');
      [*] = ;         //if (behHnd<>0) then
      [*] = ;         AddObjectToDestroyList(goHnd);
      [*] = ;         //else
      [*] = ;         //SetupBehaviour(goHnd);//SetupInertiaBehaviour(goHnd, speed);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var clearObjectsX : Float = GetFloatValueByName('clearObjectsX');
      [*] = ;var clearObjectsZ : Float = GetFloatValueByName('clearObjectsZ');
      [*] = ;var clearObjectsRadius : Float = GetFloatValueByName('clearObjectsRadius');
      [*] = ;InertiaDownObjectsInRadius(clearObjectsX, clearObjectsZ, clearObjectsRadius);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
