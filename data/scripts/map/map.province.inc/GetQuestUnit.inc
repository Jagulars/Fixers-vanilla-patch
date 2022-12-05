section.begin
   Name = GetQuestUnit
   Description : struct.begin
      [*] = ;IntRegister0 - unit rank
      [*] = ;OUT: IntRegister1 - quest unit ID
   struct.end
   Code : struct.begin
      [*] = ;var rank : Integer = IntRegister0;
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;var pUnits : Integer = gPrototypeData.units.handle;
      [*] = ;var pProvNeighbours : Integer = ParserSelectByHandleByKey(pProvince, 'Neighbours');
      [*] = ;var i, pUnit, unitID : Integer;
      [*] = ;
      [*] = ;_rand_ClearRoll();
      [*] = ;gArrRollerN[0] := 1;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pUnits)-1 downto 1 do
      [*] = ;begin
      [*] = ;   pUnit := ParserSelectByHandleByIndex(pUnits,i);
      [*] = ;   unitID := ParserGetIntValueByKeyByHandle(pUnit, 'UnitID');
      [*] = ;   if (ParserGetIntValueByKeyByHandle(pUnit, 'Rank') = rank) and _map_IsQuestUnitEnabled(unitID) then
      [*] = ;      gArrRollerN[i] := i
      [*] = ;   else
      [*] = ;      gArrRollerN[i] := -1*i;
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('FillMonsters');
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pProvNeighbours)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pProvNeighbour : Integer = ParserSelectByHandleByIndex(pProvNeighbours, i);
      [*] = ;   var index : Integer = ParserGetIntValueByKeyByHandle(pProvNeighbour, 'Index');
      [*] = ;   var pNProvince : Integer = ParserSelectByHandleByIndex(pProvinces, index);
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pNProvince, 'DummyUID');
      [*] = ;
      [*] = ;   if dummyUID > 0 then
      [*] = ;   begin
      [*] = ;      var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'FillMonsters');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister1 := _rand_Roll_VVK(true);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

