section.begin
   Name = ProceedQueries
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked()) and (gIntRegister_MapTurnIteration = 12) and (myPlIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\PROCEEDQUERIES';
      [*] = ;   var _log_trace : Integer = $40001;
      [*] = ;   var myParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;   var pQueries : Integer = ParserSelectByHandleByKey(myParser, 'Queries');
      [*] = ;   var queryID : String = '';
      [*] = ;   var pQuery : Integer = 0;
      [*] = ;   var i, pCheckQuery : Integer;
      [*] = ;
      [*] = ;   _gv_traceState(_log_name,_log_trace);
      [*] = ;   if SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      while (queryID = '') and (ParserGetCountByHandle(pQueries) > 0) do
      [*] = ;      begin
      [*] = ;         pQuery := ParserSelectByHandleByIndex(pQueries, 0);
      [*] = ;         queryID := ParserGetValueByKeyByHandle(pQuery, 'QueryID');
      [*] = ;         if queryID = '' then
      [*] = ;            ParserFreeByHandle(pQuery)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            for i := 0 to ParserGetCountByHandle(pQueries)-1 do
      [*] = ;            begin
      [*] = ;               pCheckQuery := ParserSelectByHandleByIndex(pQueries, i);
      [*] = ;               if ParserGetBoolValueByKeyByHandle(pCheckQuery, 'Priority') then
      [*] = ;               begin
      [*] = ;                  pQuery := pCheckQuery;
      [*] = ;                  queryID := ParserGetValueByKeyByHandle(pCheckQuery, 'QueryID');
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            var heroUID : Integer = ParserGetIntValueByKeyByHandle(pQuery, 'HeroUID');
      [*] = ;            var plIndex : Integer = _pars_ParserGetIntValueExt(pQuery, 'PlayerIndex');
      [*] = ;            var plIndex1 : Integer = _pars_ParserGetIntValueExt(pQuery, 'PlayerIndex1');
      [*] = ;            var playersList : String = ParserGetValueByKeyByHandle(pQuery, 'gStringRegister_PlayersList');
      [*] = ;            var diplomacy : Boolean = ParserGetBoolValueByKeyByHandle(pQuery, 'Diplomacy');
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;            var plHandle1 : Integer = GetPlayerHandleByIndex(plIndex1);
      [*] = ;
      [*] = ;            if heroUID > 0 then
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;               gIntRegister_DeadHeroHandle := goHandle;
      [*] = ;
      [*] = ;               _hero_GetName(goHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'GetResurrectPrice');
      [*] = ;               gIntRegister_GoldCost := IntRegister0;
      [*] = ;               gIntRegister_GemCost := IntRegister1;
      [*] = ;
      [*] = ;               if (gGame.gameType = 2) and gProfile.mesTutor and (gTutorial.deliver = 0) then
      [*] = ;                  gTutorial.deliver := 1;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if plIndex >= 0 then
      [*] = ;            begin
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'GetName');
      [*] = ;               gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;               gIntRegister_QueryPlayerIndex := plIndex;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if plIndex1 >= 0 then
      [*] = ;            begin
      [*] = ;               PlayerExecuteStateByHandle(plHandle1, 'GetName');
      [*] = ;               gStringRegister_EnemyPlayerNameDiplomacy := StringRegister0;
      [*] = ;               gIntRegister_QueryPlayerIndex1 := plIndex1;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if playersList <> '' then
      [*] = ;               gStringRegister_PlayersList := playersList;
      [*] = ;
      [*] = ;            //if diplomacy then
      [*] = ;            //   gArrDiplomacy[myPlIndex][plIndex].lanAnswer := (not diplAnswer); // if no answer received for my proposal
      [*] = ;
      [*] = ;            if diplomacy {and (not diplAnswer)} then
      [*] = ;            begin
      [*] = ;               var valid : Boolean = true;
      [*] = ;               gIntRegister_QueryDiplomacyPlayerID := plIndex; // used in DrawDiplomacyOfferCover
      [*] = ;               if (plIndex >= 0) and ParserGetBoolValueByKeyByHandle(pQuery, 'Informative') then
      [*] = ;                  gIntRegister_QueryDiplomacyPlayerID := gIntRegister_QueryDiplomacyPlayerID + $10; // to reverse tables for an answer to the proposal
      [*] = ;               
      [*] = ;               // this check is now done in CheckMessage.inc, so the player will get a proper refusal.
      [*] = ;               {if gArrDiplomacy[plIndex][myPlIndex].message.treaty = gc_TreatyUnion then
      [*] = ;               begin
      [*] = ;                  ExecuteState('GetUnionCount');
      [*] = ;                  var myUnion : Integer = IntRegister0;
      [*] = ;
      [*] = ;                  PlayerExecuteStateByHandle(plHandle, 'GetUnionCount');
      [*] = ;                  var plUnion : Integer = IntRegister0;
      [*] = ;
      [*] = ;                  if (myUnion > 0) or (plUnion > 0) then
      [*] = ;                     valid := false;
      [*] = ;               end;}
      [*] = ;               
      [*] = ;               //if (gArrDiplomacy[myPlIndex][plIndex].treaty = gc_TreatyPeace) and (gArrDiplomacy[plIndex][myPlIndex].message.treaty = gc_TreatyPeace) then // don't show peace offer if already at peace (possible if another party of a union war already proposed peace and it was signed)
      [*] = ;               //   valid := false;
      [*] = ;
      [*] = ;               if StrToInt(queryID) = gc_gui_query_diplAskPeaceFromUnion then
      [*] = ;               begin
      [*] = ;                  gIntRegister_QueryDiplomacyPlayerID := -1;
      [*] = ;                  //if gArrDiplomacy[myPlIndex][plIndex].treaty <> gc_TreatyUnion then
      [*] = ;                  if (gArrDiplomacy[myPlIndex][plIndex].message.treaty = gc_TreatyPeace) or (gArrDiplomacy[myPlIndex][plIndex1].message.treaty = gc_TreatyPeace) then // in case getting a peace offer from an ally of this player before answering this query, and sending a peace offer
      [*] = ;                     valid := false;
      [*] = ;               end;
      [*] = ;               
      [*] = ;
      [*] = ;               if not valid then
      [*] = ;               begin
      [*] = ;                  queryID := '';
      [*] = ;                  _diplomacy_ClearMessage(gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;                  ParserFreeByHandle(pQuery);
      [*] = ;                  gIntRegister_QueryDiplomacyPlayerID := -1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      {else
      [*] = ;      begin
      [*] = ;         for i := 0 to gGame.map.players-1 do
      [*] = ;         if i <> myIndex then
      [*] = ;         begin
      [*] = ;            if gArrDiplomacy[i][myIndex].message.text <> '' then
      [*] = ;            begin
      [*] = ;               queryID := gArrDiplomacy[i][myIndex].message.text;
      [*] = ;               gIntRegister_QueryPlayerIndex := i;
      [*] = ;               gStringRegister_EnemyPlayerName := GetPlayerNameByIndex(i);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;}
      [*] = ;   end
      [*] = ;   else
      [*] = ;      ParserClearByHandle(pQueries);
      [*] = ;
      [*] = ;   if (queryID <> '') and (queryID <> '0') then
      [*] = ;   begin
      [*] = ;      ParserFreeByHandle(pQuery);
      [*] = ;
      [*] = ;      StringRegister0 := queryID;
      [*] = ;      GUIExecuteState('map.RequestQueryWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gIntRegister_QueryPlayerIndex := -1;
      [*] = ;      gIntRegister_QueryPlayerIndex1 := -1;
      [*] = ;      // switch to next iteration state
      [*] = ;      gIntRegister_MapCurHeroIndex := 0;
      [*] = ;      gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;   end;
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
   struct.end
section.end

