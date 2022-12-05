section.begin
   Name = AIPlaceDefender
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlName : String = GetCurrentPlayerName;
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var cDummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(cDummyUID);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;BoolRegister0 := true;
      [*] = ;GameObjectExecuteStateByHandle(cDummyHandle, 'AITryDefender');
      [*] = ;var plCanHire : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanHire);
      [*] = ;
      [*] = ;if plCanHire > 0 then
      [*] = ;begin
      [*] = ;   var count : Integer = 2 + Floor(3 * RandomExt);
      [*] = ;   for [MAIN]i := 0 to count-1 do
      [*] = ;   begin
      [*] = ;      for j := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, j);
      [*] = ;         var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;
      [*] = ;         if SameText(myPlName, provPlName) then
      [*] = ;         begin
      [*] = ;            var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;            var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;            var pDefUnits : Integer = ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;            var isDefender : Boolean = (ParserGetCountByHandle(pDefUnits) > 0);
      [*] = ;
      [*] = ;            StringRegister0 := myPlName;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'IsEnemyNeighbour');
      [*] = ;            var enNeighbour : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            case i of
      [*] = ;               3 :
      [*] = ;               begin
      [*] = ;                  BoolRegister0 := false;
      [*] = ;                  GameObjectExecuteStateByHandle(dummyHandle, 'AITryDefender');
      [*] = ;               end;
      [*] = ;               2 :
      [*] = ;               begin
      [*] = ;                  if not isDefender then
      [*] = ;                  begin
      [*] = ;                     BoolRegister0 := false;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'AITryDefender');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               1 :
      [*] = ;               begin
      [*] = ;                  if enNeighbour then
      [*] = ;                  begin
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'AITryDefender');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (not isDefender) and (enNeighbour) then
      [*] = ;                  begin
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'AITryDefender');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            var plCanHire : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanHire);
      [*] = ;            if plCanHire <= 0 then
      [*] = ;            break(MAIN);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

