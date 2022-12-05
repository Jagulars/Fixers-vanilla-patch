section.begin
   Name = map.DoFogOfWar
   UsedFileName =
   Code : struct.begin
      [*] = ;const cFowPlayerName = 'plFogofwar';
      [*] = ;const cFowControlMode = 'cmPlayer'; // must be cmPlayer, or fogofwar will not progress outside camera
      [*] = ;const cFowRaceName = 'misc';
      [*] = ;const cFowCloudBaseName = 'fowcloud';
      [*] = ;const cFowCloudManagerName = 'fowclouds';
      [*] = ;const cFowCloudSourceName = 'fowcloud'; // fowcloud1, fowcloud2, fowcloud3, fowcloud4, fowcloud5
      [*] = ;const cFowShadowBaseName = 'fowshadow';
      [*] = ;
      [*] = ;function MaxValue(const a, b : Float) : Float;
      [*] = ;begin
      [*] = ;   if (a>b) then
      [*] = ;      Result := a
      [*] = ;   else
      [*] = ;      Result := b;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetHexCellPosition(const hexCell : Integer; var posX : Float; var posY : Float; var posZ : Float);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var mx, mz : Float = 0;
      [*] = ;   var ax, az : array [0..5] of Float;
      [*] = ;   var verts : Integer = ParserSelectByHandleByKey(hexCell, 'Vertices');
      [*] = ;   for i:=0 to 5 do
      [*] = ;   begin
      [*] = ;      var vert : Integer = ParserSelectByHandleByIndex(verts, i);
      [*] = ;      var x : Float = ParserGetFloatValueByKeyByHandle(vert, 'X');
      [*] = ;      var z : Float = ParserGetFloatValueByKeyByHandle(vert, 'Y');
      [*] = ;      ax[i] := x;
      [*] = ;      az[i] := z;
      [*] = ;      mx := mx + x;
      [*] = ;      mz := mz + z;
      [*] = ;   end;
      [*] = ;   mx := mz/6;
      [*] = ;   mz := mz/6;
      [*] = ;   var minX, maxX : Float = mx;
      [*] = ;   var minZ, maxZ : Float = mz;
      [*] = ;   for i:=0 to 5 do
      [*] = ;   begin
      [*] = ;      if ax[i]<minX then minX := ax[i];
      [*] = ;      if ax[i]>maxX then maxX := ax[i];
      [*] = ;      if az[i]<minZ then minZ := az[i];
      [*] = ;      if az[i]>maxZ then maxZ := az[i];
      [*] = ;   end;
      [*] = ;   var hexWidth : Float = maxX - minX;
      [*] = ;   var hexHeight : Float = maxZ - minZ;
      [*] = ;   var hexRad : Float = MaxValue(hexWidth, hexHeight);
      [*] = ;   posX := mx;
      [*] = ;   posZ := mz;
      [*] = ;   posY := GetMapMaxHeight(Round(posX), Round(posZ), hexRad) + 0;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetGameObjectHandleByBaseName(plHnd : Integer; baseName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetPlayerGameObjectsCountByHandle(plHnd)-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectHandleByIndex(i, plHnd);
      [*] = ;      if (SameText(GetGameObjectBaseNameByHandle(goHnd), baseName)) then
      [*] = ;      begin
      [*] = ;         Result := goHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UpdateFogOfWar;
      [*] = ;begin
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cFowPlayerName);
      [*] = ;   if (plHnd=0) then
      [*] = ;   plHnd := CreatePlayer(cFowPlayerName, cFowRaceName, cFowControlMode);
      [*] = ;   var hexCells : Integer = gStratHexCells.handle;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(hexCells)-1 do
      [*] = ;   begin
      [*] = ;      var hexCell : Integer = ParserSelectByHandleByIndex(hexCells, i);
      [*] = ;      var fowUID : Integer = ParserGetIntValueByKeyByHandle(hexCell, 'fowuid');
      [*] = ;      var fowHnd : Integer = GetGameObjectHandleByUniqueId(fowUID);
      [*] = ;      gIntRegister_fowcloud_province := hexCell;
      [*] = ;      if (fowHnd=0) then
      [*] = ;      begin
      [*] = ;         var posX, posY, posZ : Float = 0;
      [*] = ;         GetHexCellPosition(hexCell, posX, posY, posZ);
      [*] = ;         fowHnd := CreatePlayerGameObjectHandleByHandle(plHnd, cFowRaceName, cFowCloudBaseName, posX, posY, posZ);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      GameObjectExecuteStateByHandle(fowHnd, 'OnUpdate');
      [*] = ;   end;
      [*] = ;   gIntRegister_fowcloud_province := 0;
      [*] = ;
      [*] = ;   ExecuteState('map.DoCreateMapShadow');
      [*] = ;   ExecuteState('map.DoCreateBattleShadow');
      [*] = ;   ExecuteState('map.DoCreateCastleShadow');
      [*] = ;
      [*] = ;   if (gIntRegister_GUICurCastleMode<>0) then
      [*] = ;   begin
      [*] = ;      ExecuteState('map.DoHideMapShadow');
      [*] = ;      ExecuteState('map.DoHideBattleShadow');
      [*] = ;      ExecuteState('map.DoShowCastleShadow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   case gIntRegister_CurGameMode of
      [*] = ;      // map
      [*] = ;      1 : begin
      [*] = ;         ExecuteState('map.DoShowMapShadow');
      [*] = ;         ExecuteState('map.DoHideBattleShadow');
      [*] = ;         ExecuteState('map.DoHideCastleShadow');
      [*] = ;      end;
      [*] = ;      // battle
      [*] = ;      2 : begin
      [*] = ;         ExecuteState('map.DoHideMapShadow');
      [*] = ;         ExecuteState('map.DoShowBattleShadow');
      [*] = ;         ExecuteState('map.DoHideCastleShadow');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gGame.gameType <> gc_GameTypeLanBattle) and (gGame.gameType <> gc_GameTypeHotseatBattle) then
      [*] = ;begin
      [*] = ;   ExecuteState('map.CalcFogMap');
      [*] = ;   UpdateFogOfWar();
      [*] = ;end;
   struct.end
section.end

