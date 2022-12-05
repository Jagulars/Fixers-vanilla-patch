section.begin
   Name = WaterScenery
   UsedFileName = 
   Description : struct.begin
      [*] = ;No Clear method exists here because it would be difficult to eliminate just the water scenery without touching anything else because it's all same pattern-player. 
      [*] = ;Clear method for the whole pattern-player exists in TerrainScenery.inc
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\WATERSCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cWavesPlName = 'plWaves';
      [*] = ;const cWavesPlRace = 'misc';
      [*] = ;const cWavesPlCMode = 'cmNone';
      [*] = ;
      [*] = ;const cPatternPlName = 'pattern';
      [*] = ;const cPatternPlRace = 'nature';
      [*] = ;const cPatternPlCMode = 'cmNone';
      [*] = ;
      [*] = ;var wavesPlHandle : Integer = _plr_GetOrCreatePlayer(cWavesPlName, cWavesPlRace, cWavesPlCMode, False);
      [*] = ;var patPlHandle : Integer = _plr_GetOrCreatePlayer(cPatternPlName, cPatternPlRace, cPatternPlCMode, False);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+cWavesPlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(wavesPlHandle))+', '+cPatternPlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(patPlHandle))+']', _log_trace);
      [*] = ;
      [*] = ;const cWaveBaseName = 'wave1';
      [*] = ;
      [*] = ;const cWaveCount = 4; //3
      [*] = ;const cShoreStep = 1.2;
      [*] = ;const cShoreStepRandom = 0.3;
      [*] = ;const cShoreOffset = 0; //1.2
      [*] = ;const cShoreOffsetRandom = 0.2;
      [*] = ;const cShoreWaveOffset = 1.7;
      [*] = ;const cShoreWaveOffsetRandom = 0.3;
      [*] = ;const cShoreObjectFreqFactor = 0.25;
      [*] = ;const cWaveSpawnRadius = 0; //1
      [*] = ;
      [*] = ;const cIceShoreStep = 2.9;
      [*] = ;const cIceShoreStepRandom = 0.1;
      [*] = ;const cIceWaveCount = 1; //3
      [*] = ;const cIceShoreOffset = 1; //1.2
      [*] = ;const cIceShoreOffsetRandom = 0.0;
      [*] = ;const cIceShoreWaveOffset = 1.25;
      [*] = ;const cIceShoreWaveOffsetRandom = 0.1;
      [*] = ;const cIceWaveSpawnRadius = 0; //1
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   var mapHeight : Integer = GetMapHeight();
      [*] = ;   var mapWidth : Integer = GetMapWidth();
      [*] = ;
      [*] = ;   var i, j, k, g, pStratHexCell, pNeighbourHex, terrainType, pVertice, vertInd, vertInd2 : Integer;
      [*] = ;   var xv, zv, xv1, zv1, xv2, zv2, dx, dy, dz, dirX, dirY, dirZ, terX, terZ, waterX, waterZ, posX, posZ : Float;
      [*] = ;   var grEnum : Integer = 0;
      [*] = ;   var modScale : Float = 0.1;
      [*] = ;
      [*] = ;   var shardVisualID : Integer = 0;
      [*] = ;   if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;      shardVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;      
      [*] = ;   _obj_CleanPruner();
      [*] = ;
      [*] = ;   var graphicsLevel : Integer = gProfile.shardscenery;
      [*] = ;   var pPruner : Integer = _obj_GetPrunerByStateName('ShardScenery', 'TerrainScenery');
      [*] = ;   var pPlayer : Integer = _obj_GetPlayerPruner(pPruner, cWavesPlName);
      [*] = ;   var pObjects : Integer = ParserSelectByHandleByKey(pPlayer, 'Objects');
      [*] = ;
      [*] = ;   var bIce : Boolean = (shardVisualID = gc_ShardVisualIce);
      [*] = ;
      [*] = ;   var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;   var pGridVertices : Integer = gGridVertices.handle;
      [*] = ;      
      [*] = ;      
      [*] = ;   procedure GetRandomObjectStyle(var objectStyleOut : Integer; const os1 : Integer; const rnd1 : Float; const os2 : Integer; const rnd2 : Float; const os3 : Integer; const rnd3 : Float; const os4 : Integer; const rnd4 : Float; const os5 : Integer; const rnd5 : Float);
      [*] = ;   begin
      [*] = ;      var i, ind, os : Integer;
      [*] = ;      var sum : Float = 0;
      [*] = ;   
      [*] = ;      var rnd : array[0..4] of Float;
      [*] = ;      rnd[0] := rnd1;
      [*] = ;      rnd[1] := rnd2;
      [*] = ;      rnd[2] := rnd3;
      [*] = ;      rnd[3] := rnd4;
      [*] = ;      rnd[4] := rnd4;
      [*] = ;   
      [*] = ;      sum := rnd1 + rnd2 + rnd3 + rnd4 + rnd5;
      [*] = ;   
      [*] = ;      var rand : Float = Random * sum;
      [*] = ;      var curSum : Float = 0;
      [*] = ;   
      [*] = ;      for i := 0 to 5-1 do
      [*] = ;      begin
      [*] = ;         curSum := curSum + rnd[i];
      [*] = ;   
      [*] = ;         if curSum >= rand then
      [*] = ;         begin
      [*] = ;            ind := i+1;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      case ind of
      [*] = ;         1 : os := os1;
      [*] = ;         2 : os := os2;
      [*] = ;         3 : os := os3;
      [*] = ;         4 : os := os4;
      [*] = ;         5 : os := os5;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      objectStyleOut := os;
      [*] = ;      //log('objectStyleOut = ' + IntToStr(objectStyleOut));
      [*] = ;   end;
      [*] = ;
      [*] = ;   {for i := 0 to ParserGetCountByHandle(pStratHexCells)-1 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      terrainType := ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;      if terrainType = gc_WaterTerrainType then
      [*] = ;      begin
      [*] = ;         var x : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;         var z : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;
      [*] = ;         for k := 0 to 1 do
      [*] = ;         begin
      [*] = ;            var layerPatternName : String;
      [*] = ;            if Random < (4/11) then
      [*] = ;               layerPatternName := 'map-holmgroup-layer-' + IntToStr(1 + Floor(Random * 4))
      [*] = ;            else
      [*] = ;               layerPatternName := 'map-water-layer-' + IntToStr(1 + Floor(Random * 7));
      [*] = ;            var randX : Float = (0.5-Random)*10;
      [*] = ;            var randZ : Float = (0.5-Random)*10;
      [*] = ;            StandPattern(patPlHandle, layerPatternName, x+randX, z+randZ, Floor(Random * 4)*90);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;   
      [*] = ;   for [MAIN]i := 0 to ParserGetCountByHandle(pStratHexCells)-1 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;
      [*] = ;      if ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType') = gc_WaterTerrainType then
      [*] = ;      begin
      [*] = ;         var pVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;         var centerX : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;         var centerZ : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;
      [*] = ;         var putObjectCounter : Integer = 0;
      [*] = ;         var putObjectStyle   : Integer = 0;
      [*] = ;
      [*] = ;         //TODO : Check if it work
      [*] = ;         //HACK : Ask faust, it there info in parser
      [*] = ;         {var isLake : Boolean = false;
      [*] = ;         var waterCount : Integer = 0;
      [*] = ;         for j := 0 to 5 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := j;
      [*] = ;            ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;            var pNextHexCell : Integer = IntRegister2;
      [*] = ;            var nextTerrainType : Integer = ParserGetIntValueByKeyByHandle(pNextHexCell, 'TerrainType');
      [*] = ;            if nextTerrainType = gc_WaterTerrainType then
      [*] = ;            begin
      [*] = ;               waterCount := waterCount + 1;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if waterCount = 0 then
      [*] = ;         isLake := true;}
      [*] = ;
      [*] = ;         for vertInd := 0 to 5 do
      [*] = ;         begin
      [*] = ;            pVertice := ParserSelectByHandleByIndex(pVertices, vertInd);
      [*] = ;            //var vIndex : Integer = _map_GetVertexIndex(i, vertInd);
      [*] = ;            //var pGridVertice : Integer = ParserSelectByHandleByIndex(pGridVertices, vIndex);
      [*] = ;
      [*] = ;            xv1 := ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;            zv1 := ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;            vertInd2 := (vertInd+1) mod 6;
      [*] = ;            pNeighbourHex := _map_GetNeighbourByVertices(pStratHexCell, vertInd, vertInd2);
      [*] = ;
      [*] = ;            if (ParserGetIntValueByKeyByHandle(pNeighbourHex, 'TerrainType') <> gc_WaterTerrainType) then
      [*] = ;            begin
      [*] = ;               pNeighbourHex := _map_GetNeighbourByVertices(pStratHexCell, vertInd, (vertInd+5) mod 6);
      [*] = ;               var bLeftWater : Boolean = ParserGetIntValueByKeyByHandle(pNeighbourHex, 'TerrainType') = gc_WaterTerrainType;
      [*] = ;               pNeighbourHex := _map_GetNeighbourByVertices(pStratHexCell, vertInd2, (vertInd2+1) mod 6);
      [*] = ;               var bRightWater : Boolean = ParserGetIntValueByKeyByHandle(pNeighbourHex, 'TerrainType') = gc_WaterTerrainType;
      [*] = ;               
      [*] = ;               pVertice := ParserSelectByHandleByIndex(pVertices, vertInd2); // get the other vertex
      [*] = ;               xv2 := ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;               zv2 := ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;               // get vector between vertices
      [*] = ;               dx := xv2 - xv1;
      [*] = ;               dy := 0;
      [*] = ;               dz := zv2 - zv1;
      [*] = ;               VectorNormalize(dx, dy, dz);
      [*] = ;
      [*] = ;               //var dist : Float = Sqrt(Sqr(xv2 - xv1) + Sqr(zv2 - zv1));
      [*] = ;               var dist : Float = VectorDistance(xv1, 0, zv1, xv2, 0, zv2); // distance between vertices
      [*] = ;               var shorePoints : Integer = Floor(dist / cShoreStep) + 1;
      [*] = ;
      [*] = ;               for k := 0 to shorePoints do
      [*] = ;               begin
      [*] = ;                  // get slightly random coords between vertices
      [*] = ;                  if k = 0 then
      [*] = ;                  begin
      [*] = ;                     xv := xv1 + dx * Random*cShoreStepRandom;
      [*] = ;                     zv := zv1 + dz * Random*cShoreStepRandom;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if k = shorePoints then
      [*] = ;                  begin
      [*] = ;                     xv := xv2 - dx * Random*cShoreStepRandom;
      [*] = ;                     zv := zv2 - dz * Random*cShoreStepRandom;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     xv := xv1 + k * dx * (cShoreStep + Random*cShoreStepRandom);
      [*] = ;                     zv := zv1 + k * dz * (cShoreStep + Random*cShoreStepRandom);
      [*] = ;                  end;
      [*] = ;                  
      [*] = ;          
      [*] = ;                  if ((k < shorePoints div 2) and (not bLeftWater)) or ((k >= shorePoints div 2) and (not bRightWater)) then // when shoreline continues within this hex, waves direction from the center of the hex
      [*] = ;                  begin
      [*] = ;                     // get direction towards the center of water hex
      [*] = ;                     dirX := xv - centerX;
      [*] = ;                     dirY := 0;
      [*] = ;                     dirZ := zv - centerZ;
      [*] = ;                  end
      [*] = ;                  else // waves perpendicular to the border when shoreline continues past the vertex
      [*] = ;                  begin
      [*] = ;                     // get direction perpendicular to vertex edge
      [*] = ;                     dirX := dx;
      [*] = ;                     dirY := 0;
      [*] = ;                     dirZ := dz;
      [*] = ;                     VectorRotateY(dirX, dirY, dirZ, 90);
      [*] = ;                  end;
      [*] = ;                  VectorNormalize(dirX, dirY, dirZ);
      [*] = ;
      [*] = ;                  // find the shoreline
      [*] = ;                  terX := xv;
      [*] = ;                  terZ := zv;
      [*] = ;                  var bCoordWater : Boolean = _map_IsTerrainType(terX, terZ, gc_WaterTerrainType);
      [*] = ;
      [*] = ;                  while bCoordWater and (terX > -mapWidth div 2) and (terX < mapWidth div 2) and
      [*] = ;                  (terZ > -mapHeight div 2) and (terZ < mapHeight div 2) do
      [*] = ;                  begin
      [*] = ;                     terX := terX + dirX;
      [*] = ;                     terZ := terZ + dirZ;
      [*] = ;                     bCoordWater := _map_IsTerrainType(terX, terZ, gc_WaterTerrainType);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  waterX := xv;
      [*] = ;                  waterZ := zv;
      [*] = ;                  bCoordWater := _map_IsTerrainType(waterX, waterZ, gc_WaterTerrainType);
      [*] = ;
      [*] = ;                  while (not bCoordWater) and (waterX > -mapWidth div 2) and (waterX < mapWidth div 2) and
      [*] = ;                  (waterZ > -mapHeight div 2) and (waterZ < mapHeight div 2) do
      [*] = ;                  begin
      [*] = ;                     waterX := waterX - dirX;
      [*] = ;                     waterZ := waterZ - dirZ;
      [*] = ;                     bCoordWater := _map_IsTerrainType(waterX, waterZ, gc_WaterTerrainType);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (terX > -mapWidth div 2) and (terX < mapWidth div 2) and
      [*] = ;                  (terZ > -mapHeight div 2) and (terZ < mapHeight div 2) and
      [*] = ;                  (waterX > -mapWidth div 2) and (waterX < mapWidth div 2) and
      [*] = ;                  (waterZ > -mapHeight div 2) and (waterZ < mapHeight div 2) then
      [*] = ;                  begin
      [*] = ;                     dirX := terX - waterX;
      [*] = ;                     dirY := 0;
      [*] = ;                     dirZ := terZ - waterZ;
      [*] = ;                     VectorNormalize(dirX, dirY, dirZ);
      [*] = ;
      [*] = ;                     var chooseRandomObject : Float = Random;
      [*] = ;                     var objBaseName : String = '';
      [*] = ;                     var yOffset : Float = 0;
      [*] = ;
      [*] = ;                     modScale := 1;
      [*] = ;
      [*] = ;                     if (putObjectCounter = 0) and (not bIce) then
      [*] = ;                     begin
      [*] = ;                        putObjectStyle := 0;
      [*] = ;                        GetRandomObjectStyle(putObjectStyle, 1, 6, 2, 3, 0, 0, 0, 0, 0, 0);
      [*] = ;                        case putObjectStyle of
      [*] = ;                           1 : begin
      [*] = ;                              if Random < 0.10 then
      [*] = ;                              putObjectCounter := 4 + Floor(Random * 4);
      [*] = ;                           end;
      [*] = ;                           2: begin
      [*] = ;                              if Random < 0.10 then
      [*] = ;                              putObjectCounter := 6 + Floor(Random * 5);
      [*] = ;                           end;
      [*] = ;                           3: begin
      [*] = ;                              if Random < 0.14 then
      [*] = ;                              putObjectCounter := 10 + Floor(Random * 10);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if (putObjectCounter <> 0) then
      [*] = ;                     begin
      [*] = ;                        case putObjectStyle of
      [*] = ;                           1 : begin // Lily
      [*] = ;                              if Random < 0.85 then
      [*] = ;                              begin
      [*] = ;                                 if chooseRandomObject < 0.30 then
      [*] = ;                                 objBaseName := 'lily1'
      [*] = ;                                 else
      [*] = ;                                 if chooseRandomObject < 0.60 then
      [*] = ;                                 objBaseName := 'lily2'
      [*] = ;                                 else
      [*] = ;                                 if chooseRandomObject < 0.73 then
      [*] = ;                                 objBaseName := 'lily3'
      [*] = ;                                 else
      [*] = ;                                 if chooseRandomObject < 0.86 then
      [*] = ;                                 objBaseName := 'lily5'
      [*] = ;                                 else
      [*] = ;                                 if chooseRandomObject < 1.00 then
      [*] = ;                                 objBaseName := 'lily4';
      [*] = ;
      [*] = ;                                 modScale := 1.7;
      [*] = ;                                 yOffset := yOffset + 0.1;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                           2 : begin // Reed
      [*] = ;                              if Random < 0.9 then
      [*] = ;                              begin
      [*] = ;                                 begin
      [*] = ;                                    objBaseName := 'reed';
      [*] = ;                                    modScale := 1.4;
      [*] = ;                                    yOffset := yOffset - 0.05;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                           3 : begin // Stones
      [*] = ;                              if Random < 0.85 then
      [*] = ;                              begin
      [*] = ;                                 if chooseRandomObject < 0.80 then
      [*] = ;                                 begin
      [*] = ;                                    objBaseName := 'stones';
      [*] = ;                                    modScale := 1.1;
      [*] = ;                                 end
      [*] = ;                                 else
      [*] = ;                                 if chooseRandomObject < 1.00 then
      [*] = ;                                 objBaseName := 'boulder';
      [*] = ;
      [*] = ;                                 modScale := 1;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if Random < 0.02 then
      [*] = ;                     begin
      [*] = ;                        objBaseName := 'boat';
      [*] = ;                        modScale := 1.5;
      [*] = ;                        yOffset := -0.2;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     if Random < 0.000075 then
      [*] = ;                     begin
      [*] = ;                        objBaseName := 'stones';
      [*] = ;                        yOffset := -0.1;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     var posX, posZ : Float;
      [*] = ;                     var rayCast : Float = 0;
      [*] = ;                     _map_GetShorePosition(terX, terZ, waterX, waterZ);
      [*] = ;                     if (putObjectStyle = 3) and (objBaseName<>'boat') then
      [*] = ;                     begin
      [*] = ;                        posX := waterX - dirX * (1 + (Random-1)*1.7);
      [*] = ;                        posZ := waterZ - dirZ * (1 + (Random-1)*1.7);
      [*] = ;                        rayCast := RayCastHeight(posX, posZ);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        posX := waterX - dirX * (cShoreOffset + Random*cShoreOffsetRandom);
      [*] = ;                        posZ := waterZ - dirZ * (cShoreOffset + Random*cShoreOffsetRandom);
      [*] = ;                        rayCast := RayCastHeight(posX, posZ);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     var waterHeight : Float;
      [*] = ;                     GetWaterExt(posX, posZ, waterHeight);
      [*] = ;                     yOffset := yOffset + waterHeight;
      [*] = ;
      [*] = ;                     if (objBaseName<>'') and (putObjectCounter>0) then
      [*] = ;                     begin
      [*] = ;                        var posX1 : Float;
      [*] = ;                        var posZ1 : Float;
      [*] = ;                        var putCount : Integer = 1;
      [*] = ;                        if (putObjectStyle = 3) and (objBaseName<>'boat') then
      [*] = ;                        putCount := 2;
      [*] = ;
      [*] = ;                        if putObjectCounter < putCount then putCount := putObjectCounter;
      [*] = ;                        var m : Integer;
      [*] = ;
      [*] = ;                        for m := 0 to putCount-1 do
      [*] = ;                        begin
      [*] = ;                           if (putObjectStyle = 3) and (objBaseName<>'boat') then
      [*] = ;                           begin
      [*] = ;                              var rad : Float = Random * 1.5;
      [*] = ;                              var angle : Float = Random * 2 * pi;
      [*] = ;                              var dirX1 : Float = rad * sin(angle);
      [*] = ;                              var dirY1 : Float = 0;
      [*] = ;                              var dirZ1 : Float = rad * cos(angle);
      [*] = ;                              posX1 := posX + dirX1;
      [*] = ;                              posZ1 := posZ + dirZ1;
      [*] = ;                              rayCast := RayCastHeight(posX1, posZ1);
      [*] = ;                              yOffset := rayCast + Random * 0.1;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              posX1 := posX;
      [*] = ;                              posZ1 := posZ;
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           var goHandle : Integer = CreatePlayerGameObjectHandleByHandle(patPlHandle, cPatternPlRace, objBaseName, posX1, yOffset, posZ1);
      [*] = ;
      [*] = ;                           putObjectCounter := putObjectCounter - 1;
      [*] = ;                           SetGameObjectAutoOffsetByHandle(goHandle, false);
      [*] = ;                           SetGameObjectPositionByHandle(goHandle, posX1, yOffset, posZ1);
      [*] = ;                           var scaleX, scaleY, scaleZ : Float;
      [*] = ;                           scaleX := GetGameObjectScaleXByHandle(goHandle) * modScale;
      [*] = ;                           scaleY := GetGameObjectScaleYByHandle(goHandle) * modScale;
      [*] = ;                           scaleZ := GetGameObjectScaleZByHandle(goHandle) * modScale;
      [*] = ;                           SetGameObjectScaleByHandle(goHandle, scaleX, scaleY, scaleZ);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if (bIce) then // ice
      [*] = ;                     begin
      [*] = ;                        for g := 0 to cIceWaveCount-1 do
      [*] = ;                        begin
      [*] = ;                           var posX : Float = waterX - dirX * (cIceShoreWaveOffset + Random*cIceShoreWaveOffsetRandom);
      [*] = ;                           var posZ : Float = waterZ - dirZ * (cIceShoreWaveOffset + Random*cIceShoreWaveOffsetRandom);
      [*] = ;                           GetWaterExt(posX, posZ, waterHeight);
      [*] = ;
      [*] = ;                           var waveX : Float = posX - (Random - 0.5) * cIceWaveSpawnRadius;
      [*] = ;                           var waveZ : Float = posZ - (Random - 0.5) * cIceWaveSpawnRadius;
      [*] = ;                           var waveY : Float = waterHeight+0.03+Random * 0.05 - 0.35;
      [*] = ;
      [*] = ;                           //var goHandle : Integer = CreatePlayerGameObjectHandle(cWavesPlName, cWavesPlRace, 'wave1_ice', waveX, waveY, waveZ);
      [*] = ;
      [*] = ;                           //var upX, upY, upZ : Float;
      [*] = ;                           //var dirX0, dirY0, dirZ0 : Float;
      [*] = ;
      [*] = ;                           //GetGameObjectOrientationByHandle(goHandle, upX, upY, upZ, dirX0, dirY0, dirZ0);
      [*] = ;                           //SetGameObjectOrientationByHandle(goHandle, dirX, dirY, dirZ, dirX0, dirY0, dirZ0);
      [*] = ;                           //var scaleX, scaleY, scaleZ : Float;
      [*] = ;                           //modScale := 3.5;
      [*] = ;                           //scaleX := GetGameObjectScaleXByHandle(goHandle) * modScale;
      [*] = ;                           //scaleY := GetGameObjectScaleYByHandle(goHandle) * modScale;
      [*] = ;                           //scaleZ := GetGameObjectScaleZByHandle(goHandle) * modScale;
      [*] = ;                           ////SetGameObjectScaleByHandle(goHandle, scaleX, scaleY, scaleZ);
      [*] = ;                           //SetGameObjectScaleByHandle(goHandle, 0, 0, 0); // to properly display water.
      [*] = ;
      [*] = ;                           if (Random<0.2) then
      [*] = ;                           begin
      [*] = ;                              var angle : Float = VectorAngle(dirX, dirY, dirZ, 1, 0, 0);
      [*] = ;                              begin
      [*] = ;                                 angle := -(angle-150) / 180 * pi;
      [*] = ;                                 //StandPatternWithAngle(patPlHandle, 'map-hex-ice-reefs-2', posX, posZ, angle-2.25, 0, 360);
      [*] = ;                                 //StandPattern(patPlHandle, 'map-hex-ice-reefs-1', waveX, waveZ, angle);
      [*] = ;                                 var pname : String;
      [*] = ;                                 case Floor(Random*3) of
      [*] = ;                                    0 : pname := 'map-hex-ice-reefs-1';
      [*] = ;                                    1 : pname := 'map-hex-ice-reefs-3';
      [*] = ;                                    2 : pname := 'map-hex-ice-reefs-4';
      [*] = ;                                 end;
      [*] = ;                                 StandPatternAdv(patPlHandle, pname, posX, posZ, angle, true, false, 'ice'+IntToStr(grEnum), '', 0);
      [*] = ;                                 grEnum := grEnum+1;
      [*] = ;                                 var grHandle : Integer = GetGRHandleByPlayerHandleByIndex(patPlHandle, GetPlayerCountOfGroupsByHandle(patPlHandle)-1);
      [*] = ;                                 if (grHandle<>0) then
      [*] = ;                                 begin
      [*] = ;                                    var goIndex : Integer;
      [*] = ;                                    for goIndex:=GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;                                    begin
      [*] = ;                                       var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, goIndex);
      [*] = ;                                       var pX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;                                       var pY : Float = GetGameObjectPositionYByHandle(goHnd);
      [*] = ;                                       var pZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;                                       SetGameObjectPositionByHandle(goHnd, pX, pY+waterHeight-0.5+(Random*0.3), pZ);
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     for g := 0 to cWaveCount-1 do
      [*] = ;                     begin
      [*] = ;                        if not _obj_CheckPruning(pObjects, cWaveBaseName, graphicsLevel) then
      [*] = ;                        begin
      [*] = ;                           posX := waterX - dirX * (cShoreWaveOffset + Random*cShoreWaveOffsetRandom);
      [*] = ;                           posZ := waterZ - dirZ * (cShoreWaveOffset + Random*cShoreWaveOffsetRandom);
      [*] = ;                           GetWaterExt(posX, posZ, waterHeight);
      [*] = ;
      [*] = ;                           var waveX : Float = posX - (Random - 0.5) * cWaveSpawnRadius;
      [*] = ;                           var waveZ : Float = posZ - (Random - 0.5) * cWaveSpawnRadius;
      [*] = ;                           var waveY : Float = waterHeight+0.03+Random * 0.05 - 0.19;
      [*] = ;
      [*] = ;                           var goHandle : Integer = CreatePlayerGameObjectHandle(cWavesPlName, cWavesPlRace, cWaveBaseName, waveX, waveY, waveZ);
      [*] = ;                           SetGameObjectCurrentFrameByHandle(goHandle, Floor(Random * 200));
      [*] = ;                           SetGameObjectCurrentFrameByHandle(goHandle, 140 + g*Floor(200/(cWaveCount)));
      [*] = ;                           
      [*] = ;                           var upX, upY, upZ : Float;
      [*] = ;                           var dirX0, dirY0, dirZ0 : Float;
      [*] = ;
      [*] = ;                           GetGameObjectOrientationByHandle(goHandle, upX, upY, upZ, dirX0, dirY0, dirZ0);
      [*] = ;                           SetGameObjectOrientationByHandle(goHandle, dirX, dirY, dirZ, dirX0, dirY0, dirZ0);
      [*] = ;                           var scaleX, scaleY, scaleZ : Float;
      [*] = ;                           modScale := 2;
      [*] = ;                           scaleX := GetGameObjectScaleXByHandle(goHandle) * modScale;
      [*] = ;                           scaleY := GetGameObjectScaleYByHandle(goHandle) * modScale;
      [*] = ;                           scaleZ := GetGameObjectScaleZByHandle(goHandle) * modScale;
      [*] = ;                           SetGameObjectScaleByHandle(goHandle, scaleX, scaleY, scaleZ);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;Create();
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+cWavesPlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(wavesPlHandle))+', '+cPatternPlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(patPlHandle))+']', $1000000 or _log_trace);
   struct.end
section.end

