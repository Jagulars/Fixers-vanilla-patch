section.begin
   Name = UpdateTrackNodes
   Code : struct.begin
      [*] = ;var goHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var i, j : Integer;
      [*] = ;var moveType : Integer = _unit_GetMoveType(goHandle);
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;var goUID : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;var pZones : Integer = gBattleData.zoneList.handle;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;begin
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;   var tnHandle : Integer = GetTrackNodeHandleByIndex(i); // track nodes in list have same indices as in parser
      [*] = ;   SetTrackNodeEnabledByHandle(tnHandle, true);
      [*] = ;
      [*] = ;   // check for another unit in cell
      [*] = ;   var UID : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;   if (UID <> goUID) and (UID <> 0) then
      [*] = ;   begin
      [*] = ;      if moveType = 0 then
      [*] = ;      begin
      [*] = ;         //var goHandle : Integer = GetGameObjectHandleByUniqueId(UID);
      [*] = ;         //var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;         SetTrackNodeEnabledByHandle(tnHandle, false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // check for barriers
      [*] = ;   var layer : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Layer');
      [*] = ;   if layer = 1 then
      [*] = ;   begin
      [*] = ;      if moveType < 2 then
      [*] = ;         SetTrackNodeEnabledByHandle(tnHandle, false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // update dist factor
      [*] = ;   var tType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Type');
      [*] = ;
      [*] = ;   IntRegister0 := tType;
      [*] = ;   MapExecuteState('bat.GetTerrainType'); // ret: sr0 - terrain type
      [*] = ;   ExecuteState('IsTerrainTypeAvailable');
      [*] = ;
      [*] = ;   if (BoolRegister0) or (moveType <> 0) then
      [*] = ;      SetTrackNodeDistFactorByHandle(tnHandle,1)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := tType;
      [*] = ;      MapExecuteState('GetBFObjectParserByID');
      [*] = ;      SetTrackNodeDistFactorByHandle(tnHandle, ParserGetIntValueByKeyByHandle( IntRegister1, 'MoveCost'));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

