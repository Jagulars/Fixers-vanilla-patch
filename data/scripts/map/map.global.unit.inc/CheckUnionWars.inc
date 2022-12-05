section.begin
   Name = CheckUnionWars
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myCMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;var pMyQueries : Integer = ParserSelectByHandleByKey(pMyParser, 'Queries');
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;if i <> myPlIndex then
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   if _plr_IsInGame(plHandle) then
      [*] = ;   begin
      [*] = ;      // check if playerIndex i is my ally. I will declare war on his enemies.
      [*] = ;      if gArrDiplomacy[myPlIndex][i].treaty = gc_TreatyUnion then
      [*] = ;      begin
      [*] = ;         for j := 0 to gGame.map.players-1 do
      [*] = ;         if (j <> myPlIndex) and (j <> i) then
      [*] = ;         begin
      [*] = ;            var plTmpHandle : Integer = GetPlayerHandleByIndex(j);
      [*] = ;            var tr1 : Integer = gArrDiplomacy[myPlIndex][j].treaty;
      [*] = ;            var tr2 : Integer = gArrDiplomacy[i][j].treaty;
      [*] = ;            if _plr_IsInGame(plTmpHandle) and (gArrDiplomacy[myPlIndex][j].treaty = gc_TreatyPeace) and (gArrDiplomacy[i][j].treaty = gc_TreatyWar) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := j;
      [*] = ;               ExecuteState('DeclareWar');
      [*] = ;
      [*] = ;               if SameText(myCMode, 'cmPlayer') and (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;               begin
      [*] = ;                  var pQuery : Integer = ParserAddChildByIndex(pMyQueries, '*');
      [*] = ;                  ParserSetValueByKeyByHandle(pQuery, 'QueryID', IntToStr(gc_gui_query_diplDeclareWarFromUnion));
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', i);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', j);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // check if playerIndex i is my enemy. Then their allies will declare war on me.
      [*] = ;      if gArrDiplomacy[myPlIndex][i].treaty = gc_TreatyWar then
      [*] = ;      begin
      [*] = ;         for j := 0 to gGame.map.players-1 do
      [*] = ;         if (j <> myPlIndex) and (j <> i) then
      [*] = ;         begin
      [*] = ;            var plTmpHandle : Integer = GetPlayerHandleByIndex(j);
      [*] = ;            if _plr_IsInGame(plTmpHandle) and (gArrDiplomacy[myPlIndex][j].treaty = gc_TreatyPeace) and (gArrDiplomacy[i][j].treaty = gc_TreatyUnion) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := myPlIndex;
      [*] = ;               PlayerExecuteStateByHandle(plTmpHandle, 'DeclareWar');
      [*] = ;
      [*] = ;               if SameText(myCMode, 'cmPlayer') and (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;               begin
      [*] = ;                  var pQuery : Integer = ParserAddChildByIndex(pMyQueries, '*');
      [*] = ;                  ParserSetValueByKeyByHandle(pQuery, 'QueryID', IntToStr(gc_gui_query_diplGetWarFromUnion));
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', i);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', j);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

