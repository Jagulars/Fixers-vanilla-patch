section.begin
   Name = map.InitGrid
   Code : struct.begin
      [*] = ;var i, j : Integer;
      [*] = ;var tnHandle : Integer;
      [*] = ;var tnHandle1 : Integer;
      [*] = ;var tnHandle2 : Integer;
      [*] = ;
      [*] = ;function GetTrackNodeHandleByIndices(const gridX, gridY : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var posX, posY : Float;
      [*] = ;   _map_GetGridCoordDefault(gridX, gridY, posX, posY);
      [*] = ;   Result := GetTrackNodeHandleByPosition(posX, 0, posY);
      [*] = ;end;
      [*] = ;
      [*] = ;gFloatRegister_MapGridXCoord := -(GetMapWidth div 2) + gc_StratHexSize * (2.75 - Sqrt(3) / 2) + 10;// 2.25
      [*] = ;gFloatRegister_MapGridYCoord := -(GetMapHeight div 2) + gc_StratHexSize * 2.0 + 9;// 1.5
      [*] = ;
      [*] = ;SetActiveTrackNodeList(0);
      [*] = ;ClearTrackNodeList('');
      [*] = ;
      [*] = ;var gWidth : Integer = gGame.map.x;
      [*] = ;var gHeight : Integer = gGame.map.y;
      [*] = ;var nodeCount : Integer = gWidth * gHeight;
      [*] = ;
      [*] = ;// load hexagons
      [*] = ;var x : Integer = 0;
      [*] = ;var y : Integer = 0;
      [*] = ;
      [*] = ;for y := 0 to gHeight-1 do
      [*] = ;begin
      [*] = ;   for x := 0 to gWidth-1 do
      [*] = ;   begin
      [*] = ;      var posX, posY : Float;
      [*] = ;      _map_GetGridCoordDefault(x, y, posX, posY);
      [*] = ;
      [*] = ;      tnHandle := AddTrackNode('', posX, 0, posY, 0);
      [*] = ;      SetTrackNodeNameByHandle(tnHandle, 'TrackNode.' + IntToStr(x) + '.' + IntToStr(y));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// connect track nodes
      [*] = ;for i := 0 to nodeCount do
      [*] = ;begin
      [*] = ;   for j := 0 to nodeCount do
      [*] = ;   begin
      [*] = ;      tnHandle := GetTrackNodeHandleByIndices(i, j);
      [*] = ;
      [*] = ;      tnHandle1 := GetTrackNodeHandleByIndices(i, j-1);
      [*] = ;      if tnHandle1 <> 0 then
      [*] = ;         ConnectTrackNodesByHandle(tnHandle, tnHandle1);
      [*] = ;
      [*] = ;      tnHandle1 := GetTrackNodeHandleByIndices(i, j+1);
      [*] = ;      if tnHandle1 <> 0 then
      [*] = ;         ConnectTrackNodesByHandle(tnHandle, tnHandle1);
      [*] = ;
      [*] = ;      tnHandle1 := GetTrackNodeHandleByIndices(i-1, j);
      [*] = ;      if tnHandle1 <> 0 then
      [*] = ;         ConnectTrackNodesByHandle(tnHandle, tnHandle1);
      [*] = ;
      [*] = ;      tnHandle1 := GetTrackNodeHandleByIndices(i+1, j);
      [*] = ;      if tnHandle1 <> 0 then
      [*] = ;         ConnectTrackNodesByHandle(tnHandle, tnHandle1);
      [*] = ;
      [*] = ;      if (i mod 2 = 1) then
      [*] = ;      begin
      [*] = ;         tnHandle1 := GetTrackNodeHandleByIndices(i-1, j+1);
      [*] = ;         if tnHandle1 <> 0 then
      [*] = ;            ConnectTrackNodesByHandle(tnHandle, tnHandle1);
      [*] = ;
      [*] = ;         tnHandle1 := GetTrackNodeHandleByIndices(i+1, j+1);
      [*] = ;         if tnHandle1 <> 0 then
      [*] = ;            ConnectTrackNodesByHandle(tnHandle, tnHandle1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         tnHandle1 := GetTrackNodeHandleByIndices(i-1, j-1);
      [*] = ;         if tnHandle1 <> 0 then
      [*] = ;            ConnectTrackNodesByHandle(tnHandle, tnHandle1);
      [*] = ;
      [*] = ;         tnHandle1 := GetTrackNodeHandleByIndices(i+1, j-1);
      [*] = ;         if tnHandle1 <> 0 then
      [*] = ;            ConnectTrackNodesByHandle(tnHandle, tnHandle1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ReflectTrackNodeConnections();
   struct.end
section.end

