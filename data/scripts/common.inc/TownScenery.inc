section.begin
   Name = TownScenery
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\TOWNSCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'townPattern';
      [*] = ;const cRaceName = 'nature';
      [*] = ;const cCMode = 'cmNone';
      [*] = ;
      [*] = ;var uPlHandle : Integer = GetPlayerHandleByName(cPlayerName);
      [*] = ;
      [*] = ;var sTrace : String = _log_name+'[Run Flags: '+IntToStr(runFlags);
      [*] = ;if (runFlags and 1) > 0 then sTrace := sTrace + ', '+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle));
      [*] = ;sTrace := sTrace +']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace,_log_trace);
      [*] = ;      
      [*] = ;const cTownRadius = 30;
      [*] = ;      
      [*] = ;//const cHeight = 4.4;
      [*] = ;      
      [*] = ;const cWaveBaseName = 'wave1';
      [*] = ;const cWaveRaceName = 'misc';
      [*] = ;const cShoreStep = 1.2;
      [*] = ;const cShoreStepRandom = 0.3;
      [*] = ;const cShoreWaveOffset = 1.7;
      [*] = ;const cShoreWaveOffsetRandom = 0.3;
      [*] = ;const cWaveSpawnRadius = {1}0;
      [*] = ;const cWaveCount = 4;
      [*] = ;   
      [*] = ;var pTownQuarters : Integer = gPrototypeData.townQuarters.handle;
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if uPlHandle = 0 then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;   
      [*] = ;   var globalPosX : Float = gFloatRegister_TownPositionX;
      [*] = ;   var globalPosZ : Float = gFloatRegister_TownPositionY;
      [*] = ;   var i, j : Integer;
      [*] = ;
      [*] = ;   {procedure ClearObjectsInRadius(posX, posZ, radius : Float);
      [*] = ;   begin
      [*] = ;      const cNatureRaceTag = 30;
      [*] = ;      //const cTownPatternPlName = 'townPattern';
      [*] = ;      const cPatternPlName = 'Pattern';
      [*] = ;      const cBldRaceName = 'buildings';
      [*] = ;      //var plHnd : Integer = GetPlayerHandleByName(cTownPatternPlName);
      [*] = ;      var plHnd : Integer = GetPlayerHandleByName(cPatternPlName);
      [*] = ;      GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, cNatureRaceTag, 0, false, false, false, false, false, false);
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to GetGameObjectListCount-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         
      [*] = ;         if (not GetGameObjectPlayableObjectByHandle(goHnd)) and (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;         GameObjectDestroyByHandle(goHnd);
      [*] = ;      end;
      [*] = ;      
      [*] = ;      const cBuildingsRaceTag = 10;
      [*] = ;      GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, cBuildingsRaceTag, 0, false, false, false, false, false, false);
      [*] = ;      for j:=0 to GetGameObjectListCount-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         
      [*] = ;         if (not GetGameObjectPlayableObjectByHandle(goHnd)) and (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;         GameObjectDestroyByHandle(goHnd);
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;   
      [*] = ;   procedure RotateRelativePosition(goHandle : Integer; cPosX, cPosZ, angle : Float);
      [*] = ;   begin
      [*] = ;      var posX, posY, posZ : Float;
      [*] = ;      posX := GetGameObjectPositionXByHandle(goHandle);
      [*] = ;      posY := GetGameObjectPositionYByHandle(goHandle);
      [*] = ;      posZ := GetGameObjectPositionZByHandle(goHandle);
      [*] = ;      
      [*] = ;      var dirX : Float = posX-cPosX;
      [*] = ;      var dirY : Float = 0;
      [*] = ;      var dirZ : Float = posZ-cPosZ;
      [*] = ;      VectorRotateY(dirX, dirY, dirZ, angle);
      [*] = ;      
      [*] = ;      var dPosX, dPosY, dPosZ : Float;
      [*] = ;      dPosX := cPosX + dirX;
      [*] = ;      dPosY := 0;
      [*] = ;      dPosZ := cPosZ + dirZ;
      [*] = ;      
      [*] = ;      SetGameObjectPositionByHandle(goHandle, dPosX, dPosY, dPosZ);
      [*] = ;      GameObjectRollByHandle(goHandle, -angle);
      [*] = ;      GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure ScaleRelativePosition(goHandle : Integer; cPosX, cPosZ, scale : Float);
      [*] = ;   begin
      [*] = ;      var posX, posY, posZ : Float;
      [*] = ;      posX := GetGameObjectPositionXByHandle(goHandle);
      [*] = ;      posY := GetGameObjectPositionYByHandle(goHandle);
      [*] = ;      posZ := GetGameObjectPositionZByHandle(goHandle);
      [*] = ;      
      [*] = ;      var ScaleX, ScaleY, ScaleZ, ScaleMod : float;
      [*] = ;      ScaleX := GetGameObjectScaleXByHandle(goHandle);
      [*] = ;      ScaleY := GetGameObjectScaleYByHandle(goHandle);
      [*] = ;      ScaleZ := GetGameObjectScaleZByHandle(goHandle);
      [*] = ;      
      [*] = ;      SetGameObjectScaleByHandle(goHandle, ScaleX * scale, ScaleY * scale, ScaleZ * scale);
      [*] = ;      SetGameObjectTrackPointMoveStepByHandle(goHandle, GetGameObjectTrackPointMoveStepByHandle(goHandle) * scale);
      [*] = ;      
      [*] = ;      var dPosX, dPosY, dPosZ : Float;
      [*] = ;      dPosX := cPosX + (posX-cPosX)*scale;
      [*] = ;      dPosY := 0;
      [*] = ;      dPosZ := cPosZ + (posZ-cPosZ)*scale;
      [*] = ;      
      [*] = ;      SetGameObjectPositionByHandle(goHandle, dPosX, dPosY, dPosZ);
      [*] = ;      GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure DoCreateSwampFireBugs(uPlHandle : Integer; posX, posZ : Float);
      [*] = ;   begin
      [*] = ;      var aPosX, aPosZ : array [0..7] of Float;
      [*] = ;      aPosX[0] := -11.8;
      [*] = ;      aPosZ[0] := 11.5;
      [*] = ;      
      [*] = ;      aPosX[1] := -11.0;
      [*] = ;      aPosZ[1] := 15.6;
      [*] = ;      
      [*] = ;      aPosX[2] := -8.3;
      [*] = ;      aPosZ[2] := 19.7;
      [*] = ;      
      [*] = ;      aPosX[3] := -4.9;
      [*] = ;      aPosZ[3] := 17.3;
      [*] = ;      
      [*] = ;      aPosX[4] := -1.7;
      [*] = ;      aPosZ[4] := 16.3;
      [*] = ;      
      [*] = ;      aPosX[5] := -5.8;
      [*] = ;      aPosZ[5] := 16.6;
      [*] = ;      
      [*] = ;      aPosX[6] := -7.5;
      [*] = ;      aPosZ[6] := 14.3;
      [*] = ;      
      [*] = ;      aPosX[7] := -10.8;
      [*] = ;      aPosZ[7] := 16.6;
      [*] = ;      
      [*] = ;      var goHnd : Integer = CreatePlayerGameObjectHandleByHandle(uPlHandle, 'misc', 'townfirebug', aPosX[0]+posX, 0, aPosZ[0]+posZ);
      [*] = ;      
      [*] = ;      var tCount : Integer = 8;
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to tCount-1 do
      [*] = ;      GameObjectTrackPointAddByHandle(goHnd, aPosX[j]+posX, RayCastHeight(aPosX[j]+posX, aPosZ[j]+posZ), aPosZ[j]+posZ);
      [*] = ;      
      [*] = ;      SetGameObjectTrackPointMoveStepIntervalByHandle(goHnd, 150);
      [*] = ;      SetGameObjectTrackPointTurnStepIntervalByHandle(goHnd, 2);
      [*] = ;      SetGameObjectTrackPointCurrentPointIndexByHandle(goHnd, 0);
      [*] = ;      SetGameObjectTrackPointMovementModeByHandle(goHnd, 'mmDoTrackListLoop');
      [*] = ;      
      [*] = ;      goHnd := CreatePlayerGameObjectHandleByHandle(uPlHandle, 'misc', 'townfirebug', aPosX[0]+posX, 0, aPosZ[0]+posZ);
      [*] = ;      tCount := 8;
      [*] = ;      for j:=0 to tCount-1 do
      [*] = ;      GameObjectTrackPointAddByHandle(goHnd, aPosX[j]+posX, RayCastHeight(aPosX[j]+posX, aPosZ[j]+posZ), aPosZ[j]+posZ);
      [*] = ;      
      [*] = ;      SetGameObjectTrackPointMoveStepIntervalByHandle(goHnd, 100);
      [*] = ;      SetGameObjectTrackPointTurnStepIntervalByHandle(goHnd, 2);
      [*] = ;      SetGameObjectTrackPointCurrentPointIndexByHandle(goHnd, 4);
      [*] = ;      SetGameObjectTrackPointMovementModeByHandle(goHnd, 'mmDoTrackListLoop');
      [*] = ;   end;
      [*] = ;   
      [*] = ;   StandPattern(uPlHandle, 'town-big-42', globalPosX-6, globalPosZ, 0); // 'town-big-38'
      [*] = ;   
      [*] = ;   //WaterFieldsClear;
      [*] = ;   //WaterFieldAdd(gc_WaterNameTown, globalPosX+11.845, globalPosZ-15.270, globalPosX+24.695, globalPosZ+2.483, 3.8);
      [*] = ;   
      [*] = ;   var px1, py1, px2, py2 : Float;
      [*] = ;   px1 := globalPosX+11.845;
      [*] = ;   py1 := globalPosZ-15.270;
      [*] = ;   px2 := globalPosX+24.695;
      [*] = ;   py2 := globalPosZ+2.483;
      [*] = ;   
      [*] = ;   var count : Integer = 15;
      [*] = ;   for i:=0 to count do
      [*] = ;   begin
      [*] = ;      var dX, dY : Float = 0;
      [*] = ;      case i of
      [*] = ;         0..3 : begin
      [*] = ;            dX := 0;
      [*] = ;            dY := 0;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            dX := -2;
      [*] = ;            dY := 0;
      [*] = ;         end;
      [*] = ;         5 : begin
      [*] = ;            dX := -20;
      [*] = ;            dY := -1;
      [*] = ;         end;
      [*] = ;         6 : begin
      [*] = ;            dX := -20;
      [*] = ;            dY := 0;
      [*] = ;         end;
      [*] = ;         7 : begin
      [*] = ;            dX := -20;
      [*] = ;            dY := -7;
      [*] = ;         end;
      [*] = ;         8 : begin
      [*] = ;            dX := -24;
      [*] = ;            dY := -8;
      [*] = ;         end;
      [*] = ;         9 : begin
      [*] = ;            dX := -24;
      [*] = ;            dY := -8;
      [*] = ;         end;
      [*] = ;         10: begin
      [*] = ;            dX := -24;
      [*] = ;            dY := -9;
      [*] = ;         end;
      [*] = ;         11 : begin
      [*] = ;            dX := -24;
      [*] = ;            dY := -10;
      [*] = ;         end;
      [*] = ;         12..15 : begin
      [*] = ;            dX := -24;
      [*] = ;            dY := -11;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            dX := 0;
      [*] = ;            dY := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      WaterFieldAdd(gc_WaterNameTown, px1+i*2, py1+dx, px1+i*2+2, py2+dy, 3.8);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure SetupTownWaves();
      [*] = ;   begin
      [*] = ;      var plName : String;
      [*] = ;      var goHandle, goIndex : Integer;
      [*] = ;      
      [*] = ;      //var plHandle : Integer;
      [*] = ;      //for i := 0 to GetCountOfPlayers-1 do
      [*] = ;      //begin
      [*] = ;      //   plHandle := GetPlayerHandleByIndex(i);
      [*] = ;      //   plName := GetPlayerNameByHandle(plHandle);
      [*] = ;      //   if SameText(plName, cPlayerName) then
      [*] = ;      //   begin
      [*] = ;      //      for goIndex := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      //      begin
      [*] = ;      //         goHandle := GetGameObjectHandleByIndex(goIndex, plHandle);
      [*] = ;      //         var posX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;      //         var posY : Float = GetGameObjectPositionYByHandle(goHandle);
      [*] = ;      //         var posZ : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;      //         if (GetGameObjectBaseNameByHandle(goHandle)=cWaveBaseName) then
      [*] = ;      //         begin
      [*] = ;      //            GameObjectDestroyByHandle(goHandle);
      [*] = ;      //         end;
      [*] = ;      //      end;
      [*] = ;      //   end;
      [*] = ;      //end;
      [*] = ;      
      [*] = ;      procedure PlaceWaves(xv1, zv1, xv2, zv2, midX, midZ : Float);
      [*] = ;      begin
      [*] = ;         // middle point pos
      [*] = ;         var x : Float = midX;//105;//125;
      [*] = ;         var z : Float = midZ;//61;//44;
      [*] = ;         
      [*] = ;         var dx : Float = xv2 - xv1;
      [*] = ;         var dy : Float = 0;
      [*] = ;         var dz : Float = zv2 - zv1;
      [*] = ;         VectorNormalize(dx, dy, dz);
      [*] = ;         
      [*] = ;         var dist : Float = Sqrt(Sqr(xv2 - xv1) + Sqr(zv2 - zv1));
      [*] = ;         
      [*] = ;         var k : Integer;
      [*] = ;         for k := 0 to Floor(dist / cShoreStep) do
      [*] = ;         begin
      [*] = ;            var xv : Float = xv1 + k * dx * (cShoreStep + Random*cShoreStepRandom);
      [*] = ;            var zv : Float = zv1 + k * dz * (cShoreStep + Random*cShoreStepRandom);
      [*] = ;            
      [*] = ;            // direction to the center of water hex
      [*] = ;            var dirCenterX : Float = xv - x;
      [*] = ;            var dirCenterY : Float = 0;
      [*] = ;            var dirCenterZ : Float = zv - z;
      [*] = ;            // direction perpendicular to edge
      [*] = ;            var dirX, dirY, dirZ : Float;
      [*] = ;            dirX := dx;
      [*] = ;            dirY := 0;
      [*] = ;            dirZ := dz;
      [*] = ;            VectorRotateY(dirX, dirY, dirZ, -90);
      [*] = ;            VectorNormalize(dirX, dirY, dirZ);
      [*] = ;            
      [*] = ;            var bHex : Boolean = false;
      [*] = ;            var bVertex : Boolean = false;
      [*] = ;            
      [*] = ;            var terX : Float = xv;
      [*] = ;            var terZ : Float = zv;
      [*] = ;            var waterY : Float;
      [*] = ;            bVertex := GetWaterExt(terX, terZ, waterY);
      [*] = ;            
      [*] = ;            while bVertex and (terX > -GetMapWidth div 2) and (terX < GetMapWidth div 2) and
      [*] = ;            (terZ > -GetMapHeight div 2) and (terZ < GetMapHeight div 2) do
      [*] = ;            begin
      [*] = ;               terX := terX + dirX;
      [*] = ;               terZ := terZ + dirZ;
      [*] = ;               bVertex := GetWaterExt(terX, terZ, waterY);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            var waterX : Float = xv;
      [*] = ;            var waterZ : Float = zv;
      [*] = ;            bVertex := GetWaterExt(waterX, waterZ, waterY);
      [*] = ;            
      [*] = ;            while (not bVertex) and (waterX > -GetMapWidth div 2) and (waterX < GetMapWidth div 2) and
      [*] = ;            (waterZ > -GetMapHeight div 2) and (waterZ < GetMapHeight div 2) do
      [*] = ;            begin
      [*] = ;               waterX := waterX - dirX;
      [*] = ;               waterZ := waterZ - dirZ;
      [*] = ;               bVertex := GetWaterExt(waterX, waterZ, waterY);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if (terX > -GetMapWidth div 2) and (terX < GetMapWidth div 2) and
      [*] = ;            (terZ > -GetMapHeight div 2) and (terZ < GetMapHeight div 2) and
      [*] = ;            (waterX > -GetMapWidth div 2) and (waterX < GetMapWidth div 2) and
      [*] = ;            (waterZ > -GetMapHeight div 2) and (waterZ < GetMapHeight div 2) then
      [*] = ;            begin
      [*] = ;               dirX := terX - waterX;
      [*] = ;               dirY := 0;
      [*] = ;               dirZ := terZ - waterZ;
      [*] = ;               VectorNormalize(dirX, dirY, dirZ);
      [*] = ;               
      [*] = ;               var chooseRandomObject : Float = Random;
      [*] = ;               var objBaseName : String = '';
      [*] = ;               var yOffset : Float = 0;
      [*] = ;               
      [*] = ;               _map_GetShorePosition(terX, terZ, waterX, waterZ);
      [*] = ;               var waterHeight : Float;
      [*] = ;               
      [*] = ;               var g : Integer;
      [*] = ;               for g := 0 to cWaveCount-1 do
      [*] = ;               begin
      [*] = ;                  var posX : Float = waterX - dirX * (cShoreWaveOffset + Random*cShoreWaveOffsetRandom);
      [*] = ;                  var posZ : Float = waterZ - dirZ * (cShoreWaveOffset + Random*cShoreWaveOffsetRandom);
      [*] = ;                  GetWaterExt(posX, posZ, waterHeight);
      [*] = ;                  //var rayCast : Float = RayCastHeight(posX, posZ);
      [*] = ;                  
      [*] = ;                  var waveX : Float = posX - (Random - 0.5) * cWaveSpawnRadius;
      [*] = ;                  var waveZ : Float = posZ - (Random - 0.5) * cWaveSpawnRadius;
      [*] = ;                  var waveY : Float = waterHeight-0.185+random*0.01;
      [*] = ;                  
      [*] = ;                  var goHandle : Integer = CreatePlayerGameObjectHandle(cPlayerName, cWaveRaceName, cWaveBaseName, waveX, waveY, waveZ);
      [*] = ;                  SetGameObjectCurrentFrameByHandle(goHandle, _rand_Random(200));
      [*] = ;                  SetGameObjectCurrentFrameByHandle(goHandle, 140 + g*floor({440}200/(cWaveCount)));
      [*] = ;                  SetGameObjectIntervalFactorByHandle(goHandle, 0.85);
      [*] = ;                  
      [*] = ;                  var upX, upY, upZ : Float;
      [*] = ;                  var dirX0, dirY0, dirZ0 : Float;
      [*] = ;                  
      [*] = ;                  GetGameObjectOrientationByHandle(goHandle, upX, upY, upZ, dirX0, dirY0, dirZ0);
      [*] = ;                  SetGameObjectOrientationByHandle(goHandle, dirX, dirY, dirZ, dirX0, dirY0, dirZ0);
      [*] = ;                  var scaleX, scaleY, scaleZ : Float;
      [*] = ;                  var modScale : Float = 2;
      [*] = ;                  scaleX := GetGameObjectScaleXByHandle(goHandle) * modScale;
      [*] = ;                  scaleY := GetGameObjectScaleYByHandle(goHandle) * modScale;
      [*] = ;                  scaleZ := GetGameObjectScaleZByHandle(goHandle) * modScale;
      [*] = ;                  SetGameObjectScaleByHandle(goHandle, scaleX, scaleY, scaleZ);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      type TPoint = class
      [*] = ;         x, z : Float;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      var pointArray : array[0..255] of TPoint;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to 32 do
      [*] = ;      begin
      [*] = ;         pointArray[i].x := 0;
      [*] = ;         pointArray[i].z := 0;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      pointArray[0].x := 20.827995300;
      [*] = ;      pointArray[0].z := -14.030323029;
      [*] = ;      pointArray[1].x := 18.742752075;
      [*] = ;      pointArray[1].z := -13.186805725;
      [*] = ;      pointArray[2].x := 17.898941040;
      [*] = ;      pointArray[2].z := -11.262775421;
      [*] = ;      pointArray[3].x := 15.825965881;
      [*] = ;      pointArray[3].z := -10.449398041;
      [*] = ;      pointArray[4].x := 14.783195496;
      [*] = ;      pointArray[4].z := -8.556415558;
      [*] = ;      pointArray[5].x := 15.191314697;
      [*] = ;      pointArray[5].z := -5.811004639;
      [*] = ;      pointArray[6].x := 16.381233215;
      [*] = ;      pointArray[6].z := -4.645446777;
      [*] = ;      pointArray[7].x := 17.349708557;
      [*] = ;      pointArray[7].z := -3.888916016;
      [*] = ;      pointArray[8].x := 18.008766174;
      [*] = ;      pointArray[8].z := -1.989418030;
      [*] = ;      pointArray[9].x := 18.046882629;
      [*] = ;      pointArray[9].z := -0.526191711;
      [*] = ;      pointArray[10].x := 19.010055542;
      [*] = ;      pointArray[10].z := 0.614265442;
      [*] = ;      pointArray[11].x := 20.204353333;
      [*] = ;      pointArray[11].z := 0.894355774;
      [*] = ;      pointArray[12].x := 21.604568481;
      [*] = ;      pointArray[12].z := 0.561714172;
      [*] = ;      pointArray[13].x := 23.615432739;
      [*] = ;      pointArray[13].z := 1.523643494;
      [*] = ;      pointArray[14].x := 24.299949646;
      [*] = ;      pointArray[14].z := 1.641494751;
      [*] = ;      pointArray[15].x := 25.751976013;
      [*] = ;      pointArray[15].z := 0.544326782;
      [*] = ;      pointArray[16].x := 25.911804199;
      [*] = ;      pointArray[16].z := -2.790924072;
      [*] = ;      pointArray[17].x := 26.5;
      [*] = ;      pointArray[17].z := -5;
      [*] = ;      
      [*] = ;      // line posXY1, posXY2
      [*] = ;      for i:=0 to 32-1 do
      [*] = ;      begin
      [*] = ;         if (pointArray[i].x=0) or (pointArray[i].z=0) or (pointArray[i+1].x=0) or (pointArray[i+1].z=0) then
      [*] = ;         break;
      [*] = ;         var xv1 : Float = globalPosX+pointArray[i].x;
      [*] = ;         var zv1 : Float = globalPosZ+pointArray[i].z;
      [*] = ;         var xv2 : Float = globalPosX+pointArray[i+1].x;
      [*] = ;         var zv2 : Float = globalPosZ+pointArray[i+1].z;
      [*] = ;   
      [*] = ;         var midX : Float = globalPosX+22;
      [*] = ;         var midY : Float = globalPosZ-8;
      [*] = ;         PlaceWaves(xv1, zv1, xv2, zv2, midX, midY);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   SetupTownWaves();
      [*] = ;   
      [*] = ;   for i := 0 to ParserGetCountByHandle(pTownQuarters)-1 do
      [*] = ;   begin
      [*] = ;      var pTownQuarter : Integer = ParserSelectByHandleByIndex(pTownQuarters, i);
      [*] = ;      var quarterPosX : Float = ParserGetFloatValueByKeyByHandle(pTownQuarter, 'QuarterPosX');
      [*] = ;      var quarterPosZ : Float = ParserGetFloatValueByKeyByHandle(pTownQuarter, 'QuarterPosZ');
      [*] = ;      var quarterRotation : Float = ParserGetFloatValueByKeyByHandle(pTownQuarter, 'QuarterRotation');
      [*] = ;      var quarterScale : Float = ParserGetFloatValueByKeyByHandle(pTownQuarter, 'QuarterScale');
      [*] = ;      var quarterDebug : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarter, 'Debug');
      [*] = ;      var quarterEnabled : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarter, 'Enabled');
      [*] = ;      var maxDynamicCount : Integer = ParserGetIntValueByKeyByHandle(pTownQuarter, 'MaxDynamicCount');
      [*] = ;      var pTownQuarterBuildings : Integer = ParserSelectByHandleByKey(pTownQuarter, 'Buildings');
      [*] = ;      var pTownQuarterPlaces : Integer = ParserSelectByHandleByKey(pTownQuarter, 'Places');
      [*] = ;      var pTownQuarterPatterns : Integer = ParserSelectByHandleByKey(pTownQuarter, 'Patterns');
      [*] = ;      var pTownQuarterMiscObjects : Integer = ParserSelectByHandleByKey(pTownQuarter, 'MiscObjects');
      [*] = ;      
      [*] = ;      quarterPosX := globalPosX + quarterPosX;
      [*] = ;      quarterPosZ := globalPosZ + quarterPosZ;
      [*] = ;      
      [*] = ;      if (quarterEnabled) then
      [*] = ;      begin
      [*] = ;         if (quarterDebug) then
      [*] = ;         begin
      [*] = ;            quarterPosX := quarterPosX {+ dbgX*0.25};
      [*] = ;            quarterPosZ := quarterPosZ {+ dbgY*0.25};
      [*] = ;            quarterRotation := quarterRotation {+ dbgZ*2.5};
      [*] = ;            log('quarterPosX = ' + FloatToStr(quarterPosX) + ' quarterPosZ = ' + FloatToStr(quarterPosZ) + ' quarterRotation = ' + FloatToStr(quarterRotation));
      [*] = ;         end;
      [*] = ;         
      [*] = ;         //MiscObjects
      [*] = ;         if (pTownQuarterMiscObjects<>0) then
      [*] = ;         begin
      [*] = ;            var j : Integer;
      [*] = ;            for j := 0 to ParserGetCountByHandle(pTownQuarterMiscObjects)-1 do
      [*] = ;            begin
      [*] = ;               var pTownQuarterMiscObject : Integer = ParserSelectByHandleByIndex(pTownQuarterMiscObjects, j);
      [*] = ;               var miscObjectBaseName : String = ParserGetValueByKeyByHandle(pTownQuarterMiscObject, 'BaseName');
      [*] = ;               var miscObjectRaceName : String = ParserGetValueByKeyByHandle(pTownQuarterMiscObject, 'RaceName');
      [*] = ;               var miscObjectPosX : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterMiscObject, 'PosX');
      [*] = ;               var miscObjectPosZ : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterMiscObject, 'PosZ');
      [*] = ;               var miscObjectRotate : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterMiscObject, 'Rotate');
      [*] = ;               var miscObjectScale : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterMiscObject, 'Scale');
      [*] = ;               var miscObjectDebug : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarterMiscObject, 'Debug');
      [*] = ;               var miscObjectBuild : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarterMiscObject, 'Build');
      [*] = ;               
      [*] = ;               miscObjectPosX := miscObjectPosX + quarterPosX;
      [*] = ;               miscObjectPosZ := miscObjectPosZ + quarterPosZ;
      [*] = ;               if (miscObjectDebug) then
      [*] = ;               begin
      [*] = ;                  miscObjectPosX := miscObjectPosX {+ dbgX*0.25};
      [*] = ;                  miscObjectPosZ := miscObjectPosZ {+ dbgY*0.25};
      [*] = ;                  miscObjectRotate := miscObjectRotate {+ dbgZ*2};
      [*] = ;                  log('miscObjectPosX = ' + FloatToStr(miscObjectPosX) + ' miscObjectPosZ = ' + FloatToStr(miscObjectPosZ) + ' miscObjectRotate = ' + FloatToStr(miscObjectRotate));
      [*] = ;               end;
      [*] = ;               
      [*] = ;               miscObjectPosX := miscObjectPosX + globalPosX;
      [*] = ;               var posY : Float = 0;
      [*] = ;               miscObjectPosZ := miscObjectPosZ + globalPosZ;
      [*] = ;               
      [*] = ;               if (miscObjectBuild) and (miscObjectScale<>0) and (miscObjectRaceName<>'') and (miscObjectBaseName<>'') then
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = CreatePlayerGameObjectHandle(cPlayerName, miscObjectRaceName, miscObjectBaseName, miscObjectPosX, posY, miscObjectPosZ);
      [*] = ;                  SetGameObjectRollAngleByHandle(goHandle, miscObjectRotate);
      [*] = ;                  SetGameObjectScaleByHandle(goHandle, miscObjectScale*GetGameObjectScaleXByHandle(goHandle), miscObjectScale*GetGameObjectScaleYByHandle(goHandle), miscObjectScale*GetGameObjectScaleZByHandle(goHandle));
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         //Patterns
      [*] = ;         if (pTownQuarterPatterns<>0) then
      [*] = ;         begin
      [*] = ;            var j : Integer;
      [*] = ;            for j := 0 to ParserGetCountByHandle(pTownQuarterPatterns)-1 do
      [*] = ;            begin
      [*] = ;               var pTownQuarterPattern : Integer = ParserSelectByHandleByIndex(pTownQuarterPatterns, j);
      [*] = ;               var patternName : String = ParserGetValueByKeyByHandle(pTownQuarterPattern, 'PatternName');
      [*] = ;               var patternPosX : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterPattern, 'PosX');
      [*] = ;               var patternPosZ : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterPattern, 'PosZ');
      [*] = ;               var patternScale : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterPattern, 'Scale');
      [*] = ;               var patternRotate : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterPattern, 'Rotate');
      [*] = ;               var patternDebug : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarterPattern, 'Debug');
      [*] = ;               var patternSmartScale : Float = ParserGetFloatValueByKeyByHandle(pTownQuarterPattern, 'PatternSmartScale');
      [*] = ;               var patternStandPattern : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarterPattern, 'StandPattern');
      [*] = ;               
      [*] = ;               if (patternStandPattern) then
      [*] = ;               begin
      [*] = ;                  patternRotate := patternRotate / 180 * pi;
      [*] = ;                  
      [*] = ;                  patternPosX := patternPosX + quarterPosX;
      [*] = ;                  patternPosZ := patternPosZ + quarterPosZ;
      [*] = ;                  if (patternDebug) then
      [*] = ;                  begin
      [*] = ;                     patternPosX := patternPosX{ + dbgX};
      [*] = ;                     patternPosZ := patternPosZ{ + dbgY};
      [*] = ;                     log('patternPosX = ' + FloatToStr(patternPosX-globalPosX) + ' patternPosZ = ' + FloatToStr(patternPosZ-globalPosZ));
      [*] = ;                  end;
      [*] = ;                  
      [*] = ;                  {patternPosX := patternPosX + globalPosX;
      [*] = ;                  patternPosZ := patternPosZ + globalPosZ;}
      [*] = ;                  
      [*] = ;                  if (patternName<>'') and (patternScale>0) then
      [*] = ;                  StandPatternAdv(uPlHandle, patternName, patternPosX, patternPosZ, patternRotate, True, False, 'town.pat.'+IntToStr(GetPlayerCountOfGroupsByHandle(uPlHandle)), '', 0);
      [*] = ;                  
      [*] = ;                  if (patternScale<>0) then
      [*] = ;                  begin
      [*] = ;                     var grHandle : Integer = GetGRHandleByPlayerHandleByIndex(uPlHandle, GetPlayerCountOfGroupsByHandle(uPlHandle)-1);
      [*] = ;                     if (grHandle<>0) then
      [*] = ;                     begin
      [*] = ;                        var goIndex : Integer;
      [*] = ;                        for goIndex:=GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;                        begin
      [*] = ;                           var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, goIndex);
      [*] = ;                           var ScaleX, ScaleY, ScaleZ, ScaleMod : float;
      [*] = ;                           ScaleX := GetGameObjectScaleXByHandle(goHnd);
      [*] = ;                           ScaleY := GetGameObjectScaleYByHandle(goHnd);
      [*] = ;                           ScaleZ := GetGameObjectScaleZByHandle(goHnd);
      [*] = ;                           ScaleMod := patternScale;//1.1
      [*] = ;                           
      [*] = ;                           SetGameObjectScaleByHandle(goHnd, ScaleX * ScaleMod, ScaleY * ScaleMod, ScaleZ * ScaleMod);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  
      [*] = ;                  if (patternSmartScale<>0) then
      [*] = ;                  begin
      [*] = ;                     var grHandle : Integer = GetGRHandleByPlayerHandleByIndex(uPlHandle, GetPlayerCountOfGroupsByHandle(uPlHandle)-1);
      [*] = ;                     if (grHandle<>0) then
      [*] = ;                     begin
      [*] = ;                        var cPosX, cPosY, cPosZ : Float = 0;
      [*] = ;                        var count : Integer = 0;
      [*] = ;                        
      [*] = ;                        var goIndex : Integer;
      [*] = ;                        for goIndex:=GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;                        begin
      [*] = ;                           var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, goIndex);
      [*] = ;                           
      [*] = ;                           count := count+1;
      [*] = ;                           cPosX := cPosX + GetGameObjectPositionXByHandle(goHnd);
      [*] = ;                           cPosY := cPosY + GetGameObjectPositionYByHandle(goHnd);
      [*] = ;                           cPosZ := cPosZ + GetGameObjectPositionZByHandle(goHnd);
      [*] = ;                        end;
      [*] = ;                        
      [*] = ;                        cPosX := cPosX/count;
      [*] = ;                        cPosY := cPosY/count;
      [*] = ;                        cPosZ := cPosZ/count;
      [*] = ;                        
      [*] = ;                        for goIndex:=GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;                        begin
      [*] = ;                           var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, goIndex);
      [*] = ;                           var posX, posY, posZ : Float;
      [*] = ;                           posX := GetGameObjectPositionXByHandle(goHnd);
      [*] = ;                           posY := GetGameObjectPositionYByHandle(goHnd);
      [*] = ;                           posZ := GetGameObjectPositionZByHandle(goHnd);
      [*] = ;                           
      [*] = ;                           var ScaleX, ScaleY, ScaleZ, ScaleMod : float;
      [*] = ;                           ScaleX := GetGameObjectScaleXByHandle(goHnd);
      [*] = ;                           ScaleY := GetGameObjectScaleYByHandle(goHnd);
      [*] = ;                           ScaleZ := GetGameObjectScaleZByHandle(goHnd);
      [*] = ;                           ScaleMod := patternSmartScale;//1.1
      [*] = ;                           
      [*] = ;                           var dPosX, dPosY, dPosZ : Float;
      [*] = ;                           dPosX := cPosX + (posX-cPosX)*ScaleMod;
      [*] = ;                           dPosY := cPosY + (posY-cPosY)*ScaleMod;
      [*] = ;                           dPosZ := cPosZ + (posZ-cPosZ)*ScaleMod;
      [*] = ;                           
      [*] = ;                           SetGameObjectPositionByHandle(goHnd, dPosX, dPosY, dPosZ);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   DoCreateSwampFireBugs(uPlHandle, globalPosX, globalPosZ);
      [*] = ;   
      [*] = ;   ExecuteState('map.DoUpdateCastleClouds');
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;   begin
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
      [*] = ;      ClearPlayerGameObjectsByHandle(GetPlayerHandleByName('townClouds'));
      [*] = ;      _map_ClearWaterFieldsByName(gc_WaterNameTown);
      [*] = ;      _map_ClearDecalsInArea(gFloatRegister_TownPositionX, gFloatRegister_TownPositionY, cTownRadius, 'map.road');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (runFlags and 1) > 0 then Clear();
      [*] = ;if (runFlags and 2) > 0 then Create();
      [*] = ;
      [*] = ;sTrace := _log_name;
      [*] = ;if (runFlags and 2) > 0 then sTrace := sTrace + '['+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle))+']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace, $1000000 or _log_trace);
   struct.end
section.end

