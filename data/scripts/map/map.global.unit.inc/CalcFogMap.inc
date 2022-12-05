section.begin
   Name = CalcFogMap
   Code : struct.begin
      [*] = ;if (gGame.gameType = gc_GameTypeLanBattle) or (gGame.gameType = gc_GameTypeHotseatBattle) then
      [*] = ;exit;
      [*] = ;
      [*] = ;var plHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;var sIndex : String = IntToStr(plIndex);
      [*] = ;var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;procedure Swim(pProvince, port : Integer);
      [*] = ;begin
      [*] = ;   if port >= 0 then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      var pProvNeighbours : Integer = ParserSelectByHandleByKey(pProvince, 'Neighbours');
      [*] = ;      for i := 0 to ParserGetCountByHandle(pProvNeighbours)-1 do
      [*] = ;      begin
      [*] = ;         var pProvNeighbour : Integer = ParserSelectByHandleByIndex(pProvNeighbours, i);
      [*] = ;         var ind : Integer = ParserGetIntValueByKeyByHandle(pProvNeighbour, 'Index');
      [*] = ;         var pNProvince : Integer = ParserSelectByHandleByIndex(pProvinces, ind);
      [*] = ;         var nTerType : Integer = ParserGetIntValueByKeyByHandle(pNProvince, 'TerrainType');
      [*] = ;
      [*] = ;         if (pNProvince <> 0) then
      [*] = ;         begin
      [*] = ;            var pProvFog : Integer = ParserSelectByHandleByKey(pNProvince, 'Fog');
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvFog, sIndex, 0);
      [*] = ;
      [*] = ;            if (nTerType = gc_WaterTerrainType) then
      [*] = ;            Swim(pNProvince, port-1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if plHandle = 0 then
      [*] = ;exit;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var pProvFog : Integer = ParserSelectByHandleByKey(pProvince, 'Fog');
      [*] = ;   var fog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, plIndex);
      [*] = ;
      [*] = ;   if fog < 2 then
      [*] = ;   begin
      [*] = ;      var pProvFog : Integer = ParserSelectByHandleByKey(pProvince, 'Fog');
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvFog, sIndex, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// setup fog around player's provinces
      [*] = ;for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var lastPlayer : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'LastPlayer');
      [*] = ;   var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   IntRegister0 := pProvince;
      [*] = ;   ExecuteState('CanPassProvince');
      [*] = ;   var canPass : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   var isNeutral : Boolean = _misc_IsProvinceNeutral(pProvince);
      [*] = ;
      [*] = ;   var visible : Boolean;
      [*] = ;   if gTutorial.map then
      [*] = ;   visible := SameText(plName, provPlName) and (lastPlayer = plIndex)
      [*] = ;   else
      [*] = ;   visible := SameText(plName, provPlName) or (isNeutral and (lastPlayer = plIndex));
      [*] = ;
      [*] = ;   //if canPass then
      [*] = ;   //if lastPlayer = plIndex then
      [*] = ;   if visible then
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      ExecuteState('SetNeighboursFog');
      [*] = ;
      [*] = ;      if (dummyHandle<>0) then // i got crashes in map generator cause of this
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetPort');
      [*] = ;         var port : Integer = IntRegister0;
      [*] = ;         if port > 0 then
      [*] = ;         Swim(pProvince, port);
      [*] = ;
      [*] = ;         IntRegister0 := 11;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CheckOuterBuildAbility');
      [*] = ;         var incRadius : Boolean = (IntRegister1 > 0);
      [*] = ;
      [*] = ;         if not incRadius then
      [*] = ;         begin
      [*] = ;            var pProvDefender : Integer = ParserAddChildByIndex(pProvince, 'Defender');
      [*] = ;            var defenderID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;
      [*] = ;            IntRegister0 := defenderID;
      [*] = ;            IntRegister1 := 5;
      [*] = ;            MapExecuteState('CheckDefenderAbility');
      [*] = ;            incRadius := (IntRegister2 > 0);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if incRadius then
      [*] = ;         begin
      [*] = ;            var pProvNeighbours : Integer = ParserSelectByHandleByKey(pProvince, 'Neighbours');
      [*] = ;            for j := 0 to ParserGetCountByHandle(pProvNeighbours)-1 do
      [*] = ;            begin
      [*] = ;               var pProvNeighbour : Integer = ParserSelectByHandleByIndex(pProvNeighbours, j);
      [*] = ;               var ind : Integer = ParserGetIntValueByKeyByHandle(pProvNeighbour, 'Index');
      [*] = ;               var pNProvince : Integer = ParserSelectByHandleByIndex(pProvinces, ind);
      [*] = ;
      [*] = ;               IntRegister0 := pNProvince;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               ExecuteState('SetNeighboursFog');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      ErrorLog('CalcFogMap : dummyHandle=0, when in old code, we try to execute state for dummyHandle');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// setup fog around heroes
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;   begin
      [*] = ;      var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;      IntRegister0 := curUID;
      [*] = ;      MapExecuteState('GetProvinceParserByUID');
      [*] = ;      var pProvince : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      ExecuteState('SetNeighboursFog');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;MapExecuteState('map.FogHideObjects');
      [*] = ;
      [*] = ;gBoolRegister_GUIUpdateMapHexGrid := true;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

