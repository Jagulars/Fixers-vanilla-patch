section.begin
   Name = ShardEdges
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\SHARDEDGES';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'astral_edge';
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
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   type TPoint = class
      [*] = ;   x, z : Float;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   type TPattern = class
      [*] = ;   name : String;
      [*] = ;   level : Integer;
      [*] = ;   a, b, y : Float = 0;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var countOfMinusPatterns : Integer = 4;
      [*] = ;   var countOfPlusPatterns : Integer = 5;
      [*] = ;   var countOfLinePatterns : Integer = 2;
      [*] = ;   var countOfEndPatterns : Integer = 3;
      [*] = ;   var patternArray : array[0..13] of TPattern; //countOfMinusPatterns+countOfPlusPatterns+countOfLinePatterns+countOfEndPatterns
      [*] = ;   
      [*] = ;   var mapHeight : Integer = GetMapHeight();
      [*] = ;   var mapWidth : Integer = GetMapWidth();
      [*] = ;
      [*] = ;   var m : Integer;
      [*] = ;   var enum : Integer = 0;
      [*] = ;   for m:=0 to countOfMinusPatterns-1 do
      [*] = ;   begin
      [*] = ;      patternArray[enum].level := -1;
      [*] = ;      case m of
      [*] = ;         0 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-minus-1b';
      [*] = ;            patternArray[enum].a := 5;
      [*] = ;            patternArray[enum].b := 4;
      [*] = ;            patternArray[enum].y := 1;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-minus-2b';
      [*] = ;            patternArray[enum].a := 5;
      [*] = ;            patternArray[enum].b := 4;
      [*] = ;            patternArray[enum].y := 1;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-minus-3';
      [*] = ;            patternArray[enum].a := 6;
      [*] = ;            patternArray[enum].b := 6;
      [*] = ;            patternArray[enum].y := 1;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-minus-4a';
      [*] = ;            patternArray[enum].a := 6;
      [*] = ;            patternArray[enum].b := 6;
      [*] = ;            patternArray[enum].y := 1;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            Log('Error! DoCreateShardEdgesWithPatterns');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      enum := enum+1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   for m:=0 to countOfPlusPatterns-1 do
      [*] = ;   begin
      [*] = ;      patternArray[enum].level := 1;
      [*] = ;      case m of
      [*] = ;         0 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-plus-1';
      [*] = ;            patternArray[enum].a := 6;
      [*] = ;            patternArray[enum].b := 6;
      [*] = ;            patternArray[enum].y := -4;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-plus-2a';
      [*] = ;            patternArray[enum].a := 3;
      [*] = ;            patternArray[enum].b := 3;
      [*] = ;            patternArray[enum].y := -4;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-plus-3';
      [*] = ;            patternArray[enum].a := 4;
      [*] = ;            patternArray[enum].b := 5;
      [*] = ;            patternArray[enum].y := -4;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-plus-4';
      [*] = ;            patternArray[enum].a := 6;
      [*] = ;            patternArray[enum].b := 6;
      [*] = ;            patternArray[enum].y := -4;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-plus-5';
      [*] = ;            patternArray[enum].a := 5;
      [*] = ;            patternArray[enum].b := 4;
      [*] = ;            patternArray[enum].y := -4;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            Log('Error! DoCreateShardEdgesWithPatterns');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      enum := enum+1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   for m:=0 to countOfLinePatterns-1 do
      [*] = ;   begin
      [*] = ;      patternArray[enum].level := 0;
      [*] = ;      case m of
      [*] = ;         0 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-line-1b';
      [*] = ;            patternArray[enum].a := 5;
      [*] = ;            patternArray[enum].b := 4;
      [*] = ;            patternArray[enum].y := -3;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-line-2';
      [*] = ;            patternArray[enum].a := 4;
      [*] = ;            patternArray[enum].b := 5;
      [*] = ;            patternArray[enum].y := -4;//-3
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            Log('Error! DoCreateShardEdgesWithPatterns');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      enum := enum+1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   for m:=0 to countOfEndPatterns-1 do
      [*] = ;   begin
      [*] = ;      patternArray[enum].level := 0;
      [*] = ;      case m of
      [*] = ;         0 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-line-1b';
      [*] = ;            patternArray[enum].a := 5;
      [*] = ;            patternArray[enum].b := 4;
      [*] = ;            patternArray[enum].y := -3;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-line-2';
      [*] = ;            patternArray[enum].a := 4;
      [*] = ;            patternArray[enum].b := 5;
      [*] = ;            patternArray[enum].y := -4;//-3
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            patternArray[enum].name := 'map-edge-line-3a';
      [*] = ;            patternArray[enum].a := 2;
      [*] = ;            patternArray[enum].b := 1;
      [*] = ;            patternArray[enum].y := -4;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            Log('Error! DoCreateShardEdgesWithPatterns');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      enum := enum+1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var curVisualID : Integer = 0;
      [*] = ;   // world rule
      [*] = ;   //if (gGame.gametype=gc_GameTypeCampaign) then
      [*] = ;   //begin
      [*] = ;   //   case gShards[gCampaign.activeShard].terrain of
      [*] = ;   //      6 : curVisualID := 2;
      [*] = ;   //      7 : curVisualID := 3;
      [*] = ;   //   end;
      [*] = ;   //end
      [*] = ;   //else
      [*] = ;   if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;   curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;   
      [*] = ;   if (curVisualID=3) then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:= 0 to 13 do
      [*] = ;      patternArray[i].name := patternArray[i].name+'-dark';
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var posX, posY, posZ : Float;
      [*] = ;   const blockLineSizeX : Float = 0;
      [*] = ;   const blockLineSizeZ : Float = -3;
      [*] = ;   const blockLineAngle : Float = 0;
      [*] = ;   const blockInSizeX : Float = 0; //4
      [*] = ;   const blockInSizeZ : Float = 0; //3
      [*] = ;   const blockInAngle : Float = 90;
      [*] = ;   const blockOutSizeX : Float = 4;
      [*] = ;   const blockOutSizeZ : Float = 3;
      [*] = ;   const blockOutAngle : Float = -90;
      [*] = ;   
      [*] = ;   if (uPlHandle=0) then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;   
      [*] = ;   var step, stepX, stepZ : Integer = 0;
      [*] = ;   var alphaStep : Integer = 6;
      [*] = ;   
      [*] = ;   var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;   var HexCount : Integer = ParserGetCountByHandle(pStratHexCells);
      [*] = ;   
      [*] = ;   function CalcMapMinMax(var minX, maxX, minY, maxY : Float) : Integer;
      [*] = ;   begin
      [*] = ;      var mapSize : Integer = round(sqrt(HexCount));
      [*] = ;      if (mapSize<=0) then
      [*] = ;      mapSize := 6;
      [*] = ;      minX := -mapWidth div 2+8;
      [*] = ;      minY := -mapHeight div 2+8;
      [*] = ;      maxX := minX+round(((mapSize+0.5)*gc_StratHexSize*sqrt(3))/3)*3+6*3; //������ ���� ������� 3��. ������� � ���������� �����, ��� �� ����������� ����� = 3. ������ 6*3, ���� ������� ������, ������ �������� waterplane'�
      [*] = ;      maxY := minY+round(((mapSize*gc_StratHexSize*1.5))/3)*3+6*3;
      [*] = ;      Result := mapSize;
      [*] = ;   end;
      [*] = ;   var minX, maxX, minY, maxY : Float;
      [*] = ;   CalcMapMinMax(minX, maxX, minY, maxY);
      [*] = ;   
      [*] = ;   procedure DoCreateCorner(x, z, angle : Float);
      [*] = ;   begin
      [*] = ;      var posY : Float = GetHeightData(Floor(x), Floor(z));
      [*] = ;      var xAlpha, zAlpha : Float;
      [*] = ;      //var scale : Float = 1.33;
      [*] = ;      var patternName : String;
      [*] = ;      patternName := 'map-edge-corner-1a';
      [*] = ;   
      [*] = ;      case angle of
      [*] = ;         0 : begin
      [*] = ;            x:=x-2;
      [*] = ;            z:=z+2;
      [*] = ;            xAlpha := x-3;
      [*] = ;            zAlpha := z;
      [*] = ;         end;
      [*] = ;         90 : begin
      [*] = ;            x:=x-3;
      [*] = ;            z:=z-2;
      [*] = ;            xAlpha := x-2;
      [*] = ;            zAlpha := z;
      [*] = ;         end;
      [*] = ;         180 : begin
      [*] = ;            x:=x+1;
      [*] = ;            z:=z-3;
      [*] = ;            xAlpha := x-4;
      [*] = ;            zAlpha := z+7;
      [*] = ;         end;
      [*] = ;         270 : begin
      [*] = ;            x:=x+2;
      [*] = ;            z:=z+1;
      [*] = ;            xAlpha := x-7;
      [*] = ;            zAlpha := z-7;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      //var goHandle : Integer;
      [*] = ;      var convertedAngle : Float = angle / 180 * pi;
      [*] = ;      StandPatternAdv(uPlHandle, patternName, x, z, convertedAngle, true, false, 'map-edge-corner.'+IntToStr(Floor(angle)), '', 0);
      [*] = ;   
      [*] = ;      // world rule Deadland
      [*] = ;      if (curVisualID=3) then
      [*] = ;      begin
      [*] = ;         var grHandle : Integer = GetGRHandleByPlayerHandleByIndex(uPlHandle, GetPlayerCountOfGroupsByHandle(uPlHandle)-1);
      [*] = ;         if (grHandle<>0) then
      [*] = ;         begin
      [*] = ;            var goIndex : Integer;
      [*] = ;            for goIndex:=GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, goIndex);
      [*] = ;               var goMat : String = GetGameObjectMaterialNameByHandle(goHnd);
      [*] = ;               if SameText(goMat, 'shard_edge') then
      [*] = ;               SetGameObjectMaterialNameByHandle(goHnd, 'shard_edge_dark');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      if (angle=90) or (angle=0) then
      [*] = ;      StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', xAlpha, zAlpha, 0, false, false, '', '', 0);
      [*] = ;      //goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, baseName, x, posY, z);
      [*] = ;      //SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;      //GameObjectRollByHandle(goHandle, angle);
      [*] = ;   
      [*] = ;      //StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', xAlpha-2, zAlpha-2, 0, false, false, '', '', 0);
      [*] = ;      //StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', xAlpha-2, zAlpha+2, 0, false, false, '', '', 0);
      [*] = ;      //StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', xAlpha+2, zAlpha-2, 0, false, false, '', '', 0);
      [*] = ;      //StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', xAlpha+2, zAlpha+2, 0, false, false, '', '', 0);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure DoCreateAlphaBorders(x1, y1, x2, y2 : Float);
      [*] = ;   begin
      [*] = ;      var lpixel : Integer;
      [*] = ;      var lMaxAxisLength : Float;
      [*] = ;      var lRatio : Float;
      [*] = ;      var patternName : String = '';
      [*] = ;   
      [*] = ;      var x, y, t : Float;
      [*] = ;      t := alphaStep;
      [*] = ;      if (abs(x1-x2))>(abs(y1-y2)) then
      [*] = ;      lMaxAxisLength := abs(x1-x2)
      [*] = ;      else
      [*] = ;      lMaxAxisLength := abs(y1-y2);
      [*] = ;      for lpixel:=0 to lMaxAxisLength do
      [*] = ;      begin
      [*] = ;         t := t + 1;
      [*] = ;         if (t>=alphaStep) and (lpixel<=lMaxAxisLength) then
      [*] = ;         begin
      [*] = ;            lRatio := lpixel / lMaxAxisLength;
      [*] = ;            x := x1 + (x2 - x1) * lRatio;
      [*] = ;            y := y1 + (y2 - y1) * lRatio;
      [*] = ;   
      [*] = ;            x := Trunc(x);
      [*] = ;            y := Trunc(y);
      [*] = ;   
      [*] = ;            var dir : Integer;
      [*] = ;            if (x2>x1) then
      [*] = ;            dir := 6
      [*] = ;            else
      [*] = ;            if (x1>x2) then
      [*] = ;            dir := 4
      [*] = ;            else
      [*] = ;            if (y2>y1) then
      [*] = ;            dir := 2
      [*] = ;            else
      [*] = ;            if (y1>y2) then
      [*] = ;            dir := 8;
      [*] = ;   
      [*] = ;            var j : Integer;
      [*] = ;            var px, py : Float;
      [*] = ;            case dir of
      [*] = ;               8 : begin
      [*] = ;                  //px := -(mapWidth div 2)-2;
      [*] = ;                  //py := y;
      [*] = ;                  //StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', px, py, 0, false, false, '', '', 0);
      [*] = ;                  for j:=0 to 3-1 do
      [*] = ;                  begin
      [*] = ;                     px := x-17-(j-1)*8;
      [*] = ;                     py := y;
      [*] = ;                     StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', px, py, 0, false, false, '', '', 0);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               6 : begin
      [*] = ;                  for j:=0 to 3-1 do
      [*] = ;                  begin
      [*] = ;                     px := x;
      [*] = ;                     py := y-17-(j-1)*8;
      [*] = ;                     StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', px, py, 0, false, false, '', '', 0);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               2 : begin
      [*] = ;                  for j:=0 to 6-1 do
      [*] = ;                  begin
      [*] = ;                     px := x+9+j*8;
      [*] = ;                     py := y;
      [*] = ;                     StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', px, py, 0, false, false, '', '', 0);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               4 : begin
      [*] = ;                  for j:=0 to 3-1 do
      [*] = ;                  begin
      [*] = ;                     px := x;
      [*] = ;                     py := y+9+j*8;
      [*] = ;                     StandPatternAdv(uPlHandle, 'map-edge-alpha-9x9', px, py, 0, false, false, '', '', 0);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;   
      [*] = ;            t := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var pointArray : array[0..255] of TPoint;
      [*] = ;   var pointArrayCount : Integer = 4;
      [*] = ;   pointArray[0].x := minX+2;
      [*] = ;   pointArray[0].z := minY;
      [*] = ;   pointArray[1].x := maxX;
      [*] = ;   pointArray[1].z := minY;
      [*] = ;   
      [*] = ;   pointArray[2].x := maxX-1;
      [*] = ;   pointArray[2].z := minY+2;
      [*] = ;   pointArray[3].x := maxX-1;
      [*] = ;   pointArray[3].z := maxY;
      [*] = ;   
      [*] = ;   pointArray[4].x := maxX-3;
      [*] = ;   pointArray[4].z := maxY-1;
      [*] = ;   pointArray[5].x := minX;
      [*] = ;   pointArray[5].z := maxY-1;
      [*] = ;   
      [*] = ;   pointArray[6].x := minX;
      [*] = ;   pointArray[6].z := maxY-2;
      [*] = ;   pointArray[7].x := minX;
      [*] = ;   pointArray[7].z := minY;
      [*] = ;   
      [*] = ;   function DoLineByPatterns(x1, y1, x2, y2 : Float; step : Integer; var prevX, prevZ, prevDir : Float) : Float;
      [*] = ;   begin
      [*] = ;      var lpixel : Integer;
      [*] = ;      var lMaxAxisLength : Float;
      [*] = ;      var lRatio : Float;
      [*] = ;      var curLevel : Integer = 0;
      [*] = ;   
      [*] = ;      var x, y, t : Float;
      [*] = ;      t := step;
      [*] = ;      if (abs(x1-x2))>(abs(y1-y2)) then
      [*] = ;      lMaxAxisLength := abs(x1-x2)
      [*] = ;      else
      [*] = ;      lMaxAxisLength := abs(y1-y2);
      [*] = ;      for lpixel:=0 to lMaxAxisLength do
      [*] = ;      begin
      [*] = ;         t := t + 1;
      [*] = ;         if (t>=step) and (lpixel<=(lMaxAxisLength)) then//and (lpixel<(lMaxAxisLength-13)) then
      [*] = ;         begin
      [*] = ;            lRatio := lpixel / lMaxAxisLength;
      [*] = ;            x := x1 + (x2 - x1) * lRatio;
      [*] = ;            y := y1 + (y2 - y1) * lRatio;
      [*] = ;   
      [*] = ;            var baseName : String;
      [*] = ;            var angle : Float = 0;
      [*] = ;            //var scale : Float = 1.33;
      [*] = ;   
      [*] = ;            if ((x1<>x2) and (y1=y2)) or ((x1=x2) and (y1<>y2)) then
      [*] = ;            begin
      [*] = ;               var xOffset : Float = 0;
      [*] = ;               var zOffset : Float = 0;
      [*] = ;               var patternEnum : Integer = -1;
      [*] = ;   
      [*] = ;               if (lpixel>=(lMaxAxisLength-(15))) then //SetupEnd
      [*] = ;               begin
      [*] = ;                  //lpixel:=round(lMaxAxisLength);
      [*] = ;                  var distLeft : Integer = round(lMaxAxisLength-lpixel)-3;//Round(VectorDistance(prevX, 0, prevZ, x2, 0, y2)-8);
      [*] = ;                  //log('distLeft='+IntToStr(distLeft));
      [*] = ;   
      [*] = ;                  var j : Integer;
      [*] = ;                  var maxWidth : Integer = 0;
      [*] = ;                  for j:=0 to countOfEndPatterns-1 do
      [*] = ;                  begin
      [*] = ;                     var tmpEnum : Integer = j+countOfPlusPatterns+countOfMinusPatterns+countOfLinePatterns;
      [*] = ;                     if (distLeft>=(patternArray[tmpEnum].a+patternArray[tmpEnum].b)) and ((maxWidth<patternArray[tmpEnum].a+patternArray[tmpEnum].b) or ((maxWidth=patternArray[tmpEnum].a+patternArray[tmpEnum].b) and (Random<0.5))) then
      [*] = ;                     begin
      [*] = ;                        patternEnum := tmpEnum;
      [*] = ;                        maxWidth := round(patternArray[tmpEnum].a+patternArray[tmpEnum].b);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (lpixel>(lMaxAxisLength-(28))) then
      [*] = ;               begin
      [*] = ;                  if (curLevel>0) then
      [*] = ;                  patternEnum := Floor(Random*countOfMinusPatterns)
      [*] = ;                  else
      [*] = ;                  if (curLevel<0) then
      [*] = ;                  patternEnum := Floor(countOfMinusPatterns+Random*(countOfPlusPatterns))
      [*] = ;                  else
      [*] = ;                  patternEnum := Floor(countOfMinusPatterns+countOfPlusPatterns+Random*(countOfLinePatterns))
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (curLevel>0) then
      [*] = ;                  begin
      [*] = ;                     if (Random<1.65) then
      [*] = ;                     patternEnum := Floor(Random*countOfMinusPatterns)
      [*] = ;                     else
      [*] = ;                     patternEnum := Floor(countOfMinusPatterns+countOfPlusPatterns+Random*(countOfLinePatterns))
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (curLevel<0) then
      [*] = ;                  begin
      [*] = ;                     if (Random<1.65) then
      [*] = ;                     patternEnum := Floor(countOfMinusPatterns+Random*(countOfPlusPatterns))
      [*] = ;                     else
      [*] = ;                     patternEnum := Floor(countOfMinusPatterns+countOfPlusPatterns+Random*(countOfLinePatterns))
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     patternEnum := Floor(Random*(countOfMinusPatterns+countOfPlusPatterns+countOfLinePatterns))
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;   
      [*] = ;               if (patternEnum>-1) then
      [*] = ;               begin
      [*] = ;                  var patternName : String = patternArray[patternEnum].name;
      [*] = ;                  var patternLevel : Integer = patternArray[patternEnum].level;
      [*] = ;                  var patternA : Float = patternArray[patternEnum].a;
      [*] = ;                  var patternB : Float = patternArray[patternEnum].b;
      [*] = ;                  var patternY : Float = patternArray[patternEnum].y;
      [*] = ;                  curLevel := curLevel+patternLevel;
      [*] = ;   
      [*] = ;                  if (x2>x1) then
      [*] = ;                  begin
      [*] = ;                     angle := 90;
      [*] = ;                     prevDir := 6;
      [*] = ;                     xOffset := patternB;
      [*] = ;                     zOffset := 5*curLevel+patternY;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (x1>x2) then
      [*] = ;                  begin
      [*] = ;                     angle := 270;
      [*] = ;                     prevDir := 4;
      [*] = ;                     xOffset := -patternB;
      [*] = ;                     zOffset := -5*curLevel-patternY;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (y2>y1) then
      [*] = ;                  begin
      [*] = ;                     angle := 180;
      [*] = ;                     prevDir := 2;
      [*] = ;                     xOffset := -5*curLevel-patternY;
      [*] = ;                     zOffset := patternB;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (y1>y2) then
      [*] = ;                  begin
      [*] = ;                     angle := 0;
      [*] = ;                     prevDir := 8;
      [*] = ;                     xOffset := 5*curLevel+patternY;
      [*] = ;                     zOffset := -patternB;//-patternY;//-4
      [*] = ;                  end;
      [*] = ;   
      [*] = ;                  step:=round(patternA+patternB);
      [*] = ;   
      [*] = ;                  x := x+xOffset;
      [*] = ;                  y := y+zOffset;
      [*] = ;                  prevX := x;
      [*] = ;                  prevZ := y;
      [*] = ;   
      [*] = ;                  angle := angle / 180 * pi;
      [*] = ;                  var grIndex : Integer = GetPlayerCountOfGroupsByHandle(uPlHandle);
      [*] = ;                  StandPatternAdv(uPlHandle, patternName, x, y, angle, true, false, 'map-edge.'+IntToStr(grIndex), '', 0);
      [*] = ;   
      [*] = ;                  // world rule Deadland
      [*] = ;                  if (curVisualID=3) then
      [*] = ;                  begin
      [*] = ;                     var grHandle : Integer = GetGRHandleByPlayerHandleByIndex(uPlHandle, GetPlayerCountOfGroupsByHandle(uPlHandle)-1);
      [*] = ;                     if (grHandle<>0) then
      [*] = ;                     begin
      [*] = ;                        var goIndex : Integer;
      [*] = ;                        for goIndex:=GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;                        begin
      [*] = ;                           var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, goIndex);
      [*] = ;                           var goMat : String = GetGameObjectMaterialNameByHandle(goHnd);
      [*] = ;                           if SameText(goMat, 'shard_edge') then
      [*] = ;                           SetGameObjectMaterialNameByHandle(goHnd, 'shard_edge_dark');
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  //var height : Float = GetHeightData(Floor(x), Floor(y));
      [*] = ;                  //var grHandle : Integer = GetGRHandleByPlayerHandleByIndex(uPlHandle, GetPlayerCountOfGroupsByHandle(uPlHandle)-1);
      [*] = ;                  //if (grHandle<>0) then
      [*] = ;                  //begin
      [*] = ;                  //   var goIndex : Integer;
      [*] = ;                  //   for goIndex:=GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;                  //   begin
      [*] = ;                  //      var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, goIndex);
      [*] = ;                  //      var xOff, zOff : Float = 0;
      [*] = ;                  //      //��� �������� ��������, ��� ���������� ����� �������. �� ����, �� ��� ��� ��� ������� ����
      [*] = ;                  //      case prevDir of
      [*] = ;                  //         6 : begin
      [*] = ;                  //            xOff := 1;
      [*] = ;                  //            zOff := 0;
      [*] = ;                  //         end;
      [*] = ;                  //         2 : begin
      [*] = ;                  //            xOff := 1;
      [*] = ;                  //            zOff := 1;
      [*] = ;                  //         end;
      [*] = ;                  //         4 : begin
      [*] = ;                  //            xOff := 0;
      [*] = ;                  //            zOff := 0;
      [*] = ;                  //         end;
      [*] = ;                  //         8 : begin
      [*] = ;                  //            xOff := 0;
      [*] = ;                  //            zOff := 0;
      [*] = ;                  //         end;
      [*] = ;                  //      end;
      [*] = ;   
      [*] = ;                  //      var px : Float = GetGameObjectPositionXByHandle(goHnd)+xOff;
      [*] = ;                  //      var pz : Float = GetGameObjectPositionZByHandle(goHnd)+zOff;
      [*] = ;                  //      var py : Float = GetGameObjectPositionYByHandle(goHnd);
      [*] = ;                  //      if (StrPos('edge', GetGameObjectBaseNameByHandle(goHnd))=0) then
      [*] = ;                  //      begin
      [*] = ;                  //         py := py+height;
      [*] = ;                  //      end;
      [*] = ;                  //      SetGameObjectPositionByHandle(goHnd, px, py, pz);
      [*] = ;                  //   end;
      [*] = ;                  //end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            t := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      Result := lMaxAxisLength;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var i : Integer;
      [*] = ;   var prevX : Float = -mapWidth div 2;
      [*] = ;   var prevZ : Float = -mapHeight div 2;
      [*] = ;   var prevDir : Float = 0; // Directions from numpad 63214789
      [*] = ;   var x, z : Float;
      [*] = ;   
      [*] = ;   i := 0;
      [*] = ;   DoCreateAlphaBorders(pointArray[i].x-25, pointArray[i].z, pointArray[i+1].x+25, pointArray[i+1].z);
      [*] = ;   i := i+2;
      [*] = ;   DoCreateAlphaBorders(pointArray[i].x, pointArray[i].z-25, pointArray[i+1].x, pointArray[i+1].z+25);
      [*] = ;   i := i+2;
      [*] = ;   DoCreateAlphaBorders(pointArray[i].x+25, pointArray[i].z, pointArray[i+1].x-25, pointArray[i+1].z);
      [*] = ;   i := i+2;
      [*] = ;   DoCreateAlphaBorders(pointArray[i].x-12, pointArray[i].z+25, pointArray[i+1].x-12, pointArray[i+1].z-25);
      [*] = ;   
      [*] = ;   i := 0;
      [*] = ;   DoCreateAlphaBorders(pointArray[i].x-25, pointArray[i].z, pointArray[i+1].x+25, pointArray[i+1].z);
      [*] = ;   i := i+2;
      [*] = ;   DoCreateAlphaBorders(pointArray[i].x, pointArray[i].z-25, pointArray[i+1].x, pointArray[i+1].z+25);
      [*] = ;   i := i+2;
      [*] = ;   DoCreateAlphaBorders(pointArray[i].x+25, pointArray[i].z, pointArray[i+1].x-25, pointArray[i+1].z);
      [*] = ;   i := i+2;
      [*] = ;   DoCreateAlphaBorders(pointArray[i].x, pointArray[i].z+25, pointArray[i+1].x, pointArray[i+1].z-25);
      [*] = ;   
      [*] = ;   i := 0;
      [*] = ;   DoLineByPatterns(pointArray[i].x, pointArray[i].z, pointArray[i+1].x, pointArray[i+1].z, 0, prevX, prevZ, prevDir);
      [*] = ;   i := i+2;
      [*] = ;   DoLineByPatterns(pointArray[i].x, pointArray[i].z, pointArray[i+1].x, pointArray[i+1].z, 0, prevX, prevZ, prevDir);
      [*] = ;   i := i+2;
      [*] = ;   DoLineByPatterns(pointArray[i].x, pointArray[i].z, pointArray[i+1].x, pointArray[i+1].z, 0, prevX, prevZ, prevDir);
      [*] = ;   i := i+2;
      [*] = ;   DoLineByPatterns(pointArray[i].x, pointArray[i].z, pointArray[i+1].x, pointArray[i+1].z, 0, prevX, prevZ, prevDir);
      [*] = ;   
      [*] = ;   //Turn all edges for test
      [*] = ;   //var goIndex : Integer;
      [*] = ;   //for goIndex := GetPlayerGameObjectsCountByHandle(uPlHandle)-1 downto 0 do
      [*] = ;   //begin
      [*] = ;   //   goHandle := GetGameObjectHandleByIndex(goIndex, uPlHandle);
      [*] = ;   //   if (GetGameObjectBaseNameByHandle(goHandle)='shard_edge1') then
      [*] = ;   //   begin
      [*] = ;   //      GameObjectTurnByHandle(goHandle, 0);
      [*] = ;   //   end;
      [*] = ;   //end;
      [*] = ;   DoCreateCorner(minX, minY, 90);
      [*] = ;   DoCreateCorner(maxX, minY, 180);
      [*] = ;   DoCreateCorner(maxX, maxY, 270);
      [*] = ;   DoCreateCorner(minX, maxY, 0);
      [*] = ;   
      [*] = ;   //Clear 1 tiles at left side and top side. fixes 1 green tile at corners
      [*] = ;   var nullTileIndex : Integer = MapGetTileIndexByTileBlock('alpha_null_2');//67;
      [*] = ;   for i:= -(mapHeight div 2) to (mapHeight div 2) do
      [*] = ;   begin
      [*] = ;      PaintTerrain(-(mapWidth div 2), i, nullTileIndex, 0, 0, false, 6, 0, 1, true, true);
      [*] = ;   end;
      [*] = ;   for i:= -(mapWidth div 2) to (mapWidth div 2) do
      [*] = ;   begin
      [*] = ;      PaintTerrain(i, mapHeight div 2, nullTileIndex, 0, 0, false, 6, 0, 1, true, true);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if (not (gMapEditor.enabled and gBoolRegister_EditorFastGeneration)) then
      [*] = ;   begin
      [*] = ;      MapGeneratorSmoothTiles;
      [*] = ;      MapGeneratorSmoothTiles;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
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

