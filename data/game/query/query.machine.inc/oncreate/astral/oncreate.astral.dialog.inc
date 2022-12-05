section.begin
   Name = oncreate.astral.dialog
   Description : struct.begin
      [*] = ;OUT: StringRegister0 - next query
      [*] = ;OUT: BoolRegister0 - close current query
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'ONCREATE\ASTRAL\ONCREATE.ASTRAL.DIALOG';
      [*] = ;var _log_trace : Integer = $80001;
      [*] = ;var queryHandle : Integer = _query_GetExecutedHandle;
      [*] = ;var queryID : String = QueryMachineQueryGetID(queryHandle);
      [*] = ;var queryStyle : Integer = StrToInt(QueryMachineQueryGetStyle(queryHandle));
      [*] = ;var resultsHandle : Integer = QueryMachineQueryGetResults(queryHandle);
      [*] = ;var countResults : Integer= QueryMachineResultsCount(resultsHandle);
      [*] = ;var next_query : String;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var visCnt : Integer;
      [*] = ;
      [*] = ;var plIndex : Integer = gIntRegister_CurrentCampPlayer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if queryStyle = 5 then
      [*] = ;begin
      [*] = ;   var curPage : Integer = GetIntValueByName('CurrentQuestionPage');
      [*] = ;   var startInd : Integer = 4*curPage;
      [*] = ;   var endInd : Integer = startInd+4;
      [*] = ;   for i := 0 to countResults-3 do
      [*] = ;   begin
      [*] = ;      var res : Integer = QueryMachineResultsGetByIndex(resultsHandle, i);
      [*] = ;      var trigger : Integer = QueryMachineResultGetTagInteger(res);
      [*] = ;      if gCampaign.arrDialogs[trigger] = 1 then
      [*] = ;      begin
      [*] = ;         visCnt := visCnt+1;
      [*] = ;
      [*] = ;         if (visCnt > startInd) and (visCnt <= endInd) then
      [*] = ;         QueryMachineResultSetVisible(res, true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if visCnt <= endInd then
      [*] = ;   begin
      [*] = ;      var resultAnotherQuestions : Integer = QueryMachineResultsGetByIndex(resultsHandle, countResults-2);
      [*] = ;      var nextQuery : String = QueryMachineResultGetNextQuery(resultAnotherQuestions);
      [*] = ;      QueryMachineResultSetVisible(resultAnotherQuestions, false);
      [*] = ;      if (curPage > 0) then
      [*] = ;      begin
      [*] = ;         var backResultID : String = 'astral.back';
      [*] = ;         var newResultHandle : Integer = QueryMachineResultsInsert(resultsHandle, countResults-1);
      [*] = ;         QueryMachineResultSetID(newResultHandle, backResultID);
      [*] = ;         QueryMachineResultSetTable(newResultHandle, 'gui');
      [*] = ;         QueryMachineResultSetKey(newResultHandle, '555');
      [*] = ;         QueryMachineResultSetEnable(newResultHandle, true);
      [*] = ;         QueryMachineResultSetVisible(newResultHandle, true);
      [*] = ;         QueryMachineResultSetNextQuery(newResultHandle, nextQuery);
      [*] = ;         SetIntValueByName('CurrentQuestionPage', GetIntValueByName('CurrentQuestionPage')-1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var eventID : Integer = StrToInt(queryID);
      [*] = ;var mult : Integer = 0;
      [*] = ;var pEvents : Integer = gPrototypeData.campEvents.handle;
      [*] = ;var pEvent : Integer = ParserSelectByHandleByIndex(pEvents, eventID - gc_query_CampEventMinIndex);
      [*] = ;
      [*] = ;var newQueryID : Integer = -1;
      [*] = ;var closeQuery : Boolean = false;
      [*] = ;
      [*] = ;if pEvent <> 0 then
      [*] = ;begin
      [*] = ;   var karma : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'Karma');
      [*] = ;   gCampaign.arrCampPlayers[0].karma := gCampaign.arrCampPlayers[0].karma + karma;
      [*] = ;
      [*] = ;   var pEffectList : Integer = ParserSelectByHandleByKey(pEvent, 'EffectList');
      [*] = ;
      [*] = ;   for j := 0 to ParserGetCountByHandle(pEffectList)-1 do
      [*] = ;   begin
      [*] = ;      var pEffect : Integer = ParserSelectByHandleByIndex(pEffectList, j);
      [*] = ;      var effectIndex : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Power');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param1');
      [*] = ;      var param2 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param2');
      [*] = ;
      [*] = ;      case effectIndex of
      [*] = ;         1 : begin
      [*] = ;            var plIndex : Integer = param2;
      [*] = ;
      [*] = ;            var energy : Integer = gCampaign.arrCampPlayers[plIndex].energy;
      [*] = ;            var work : Integer = power+_rand_Random(param1);
      [*] = ;            gIntRegister_AstralEnergy := Round(Abs(work));
      [*] = ;            gCampaign.arrCampPlayers[plIndex].energy := energy + work;
      [*] = ;            gBoolRegister_GUIUpdateInterfacePanel := true;
      [*] = ;            if j = 0 then
      [*] = ;            mult := work;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            if param1 = 0 then
      [*] = ;            begin
      [*] = ;               var att : Integer = gCampaign.arrCampPlayers[plIndex].arrAttitude[param2];
      [*] = ;               gCampaign.arrCampPlayers[plIndex].arrAttitude[param2] := att + power;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var att : Integer = gCampaign.arrCampPlayers[param1].arrAttitude[param2];
      [*] = ;               gCampaign.arrCampPlayers[param1].arrAttitude[param2] := att + power;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            if (param2 = 0) or (gCampaign.arrDialogs[param2] > 0) then
      [*] = ;            gCampaign.arrDialogs[power] := param1;
      [*] = ;         end;
      [*] = ;         5 : begin
      [*] = ;            var work : Integer = power + _rand_Random(param1);
      [*] = ;            if work > 0 then
      [*] = ;            gCampaign.arrCampPlayers[param2].energyBonus := gCampaign.arrCampPlayers[param2].energyBonus + work
      [*] = ;            else
      [*] = ;            gCampaign.arrCampPlayers[param2].energyPenalty := gCampaign.arrCampPlayers[param2].energyPenalty + work;
      [*] = ;
      [*] = ;            if j = 0 then
      [*] = ;            mult := work;
      [*] = ;         end;
      [*] = ;         7 : begin
      [*] = ;            gCampaign.arrCampPlayers[param2].karma := gCampaign.arrCampPlayers[param2].karma + power + _rand_Random(param1);
      [*] = ;         end;
      [*] = ;         12 : begin
      [*] = ;            gCampaign.arrCampPlayers[power].treaty := param1;
      [*] = ;         end;
      [*] = ;         13 : begin
      [*] = ;            var f : Boolean = false;
      [*] = ;            for i := 0 to gc_MaxCampaignQuest-1 do
      [*] = ;            begin
      [*] = ;               if gCampaign.arrQuests[i].questIndex = power then
      [*] = ;               begin
      [*] = ;                  gCampaign.arrQuests[i].status := param1;
      [*] = ;                  f := true;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if not f then
      [*] = ;            begin
      [*] = ;               for i := 0 to gc_MaxCampaignQuest-1 do
      [*] = ;               if gCampaign.arrQuests[i].questIndex = 0 then
      [*] = ;               begin
      [*] = ;                  gCampaign.arrQuests[i].questIndex := power;
      [*] = ;                  gCampaign.arrQuests[i].status := param1;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         14 : begin
      [*] = ;            gIntRegister_CampAttackPlayer := 0;
      [*] = ;            gIntRegister_CampDefendPlayer := gIntRegister_CurrentCampPlayer;
      [*] = ;         end;
      [*] = ;         15 : begin
      [*] = ;            gCampaign.arrItems[power] := gCampaign.arrItems[power] + param1;
      [*] = ;
      [*] = ;            if param2 > 0 then
      [*] = ;            gCampaign.arrItems[power] := gCampaign.arrItems[power] + gCampaign.arrItems[param2];
      [*] = ;         end;
      [*] = ;         17 : begin
      [*] = ;            if gCampaign.arrEvents[0] > 0 then
      [*] = ;            begin
      [*] = ;               for i := gc_MaxCampaignEvent-2 downto 0 do
      [*] = ;               gCampaign.arrEvents[i+1] := gCampaign.arrEvents[i];
      [*] = ;            end;
      [*] = ;
      [*] = ;            gCampaign.arrEvents[0] := power;
      [*] = ;         end;
      [*] = ;         18 : begin
      [*] = ;            IntRegister0 := power;
      [*] = ;            MapExecuteState('astral.BanishPlayer');
      [*] = ;         end;
      [*] = ;         19 : begin
      [*] = ;            if gCampaign.arrCampPlayers[param1].inGame then
      [*] = ;            begin
      [*] = ;               newQueryID := power;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         21 : begin
      [*] = ;            gIntRegister_CampAttackPlayer := power;
      [*] = ;            gIntRegister_CampDefendPlayer := 0;
      [*] = ;            closeQuery := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;         22 : begin
      [*] = ;            var energyLose : Integer = gCampaign.arrCampPlayers[0].energyLose;
      [*] = ;            var work : Integer = power + _rand_Random(param1);
      [*] = ;            gCampaign.arrCampPlayers[0].energyLose := energyLose + work;
      [*] = ;
      [*] = ;            gIntRegister_AstralEnergy := Round(Abs(work));
      [*] = ;         end;
      [*] = ;         23 : begin
      [*] = ;            gCampaign.arrJournals[power] := param1;
      [*] = ;            // TODO: blink journal GUI element if param1 > 0
      [*] = ;         end;
      [*] = ;         24 : begin
      [*] = ;            gCampaign.timeBonus := gCampaign.timeBonus + power;
      [*] = ;         end;
      [*] = ;         25 : begin
      [*] = ;            gCampaign.arrCampPlayers[0].mapScore := gCampaign.arrCampPlayers[0].mapScore + power;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (newQueryID < 0) and (not closeQuery) then
      [*] = ;   begin
      [*] = ;      for j := 0 to ParserGetCountByHandle(pEffectList)-1 do
      [*] = ;      begin
      [*] = ;         var pEffect : Integer = ParserSelectByHandleByIndex(pEffectList, j);
      [*] = ;         var effectIndex : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;         var power : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Power');
      [*] = ;         var param1 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param1');
      [*] = ;         var param2 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param2');
      [*] = ;
      [*] = ;         case effectIndex of
      [*] = ;            9 : begin
      [*] = ;               if _camp_player_GetAttitude(gCampaign.arrCampPlayers[power]) < param1 then
      [*] = ;               newQueryID := param2;
      [*] = ;            end;
      [*] = ;            10 : begin
      [*] = ;               if gCampaign.arrDialogs[power] > 0 then
      [*] = ;               begin
      [*] = ;                  if param1 > 0 then
      [*] = ;                  newQueryID := param1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if param2 > 0 then
      [*] = ;                  newQueryID := param2;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            11 : begin
      [*] = ;               if (param1 > 0) and (_rand_Random(100) > param2) then
      [*] = ;               newQueryID := param1
      [*] = ;               else
      [*] = ;               newQueryID := power;
      [*] = ;            end;
      [*] = ;            26 : begin
      [*] = ;               if gCampaign.arrCampPlayers[0].mapScore >= power then
      [*] = ;               begin
      [*] = ;                  if param1 > 0 then
      [*] = ;                  newQueryID := param1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if param2 > 0 then
      [*] = ;                  newQueryID := param2;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            20 : begin
      [*] = ;               IntRegister0 := power;
      [*] = ;               MapExecuteState('astral.FinishCampaign');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if newQueryID >= 0 then
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if newQueryID < 0 then
      [*] = ;      begin
      [*] = ;         for j := 0 to ParserGetCountByHandle(pEffectList)-1 do
      [*] = ;         begin
      [*] = ;            var pEffect : Integer = ParserSelectByHandleByIndex(pEffectList, j);
      [*] = ;            var effectIndex : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;
      [*] = ;            if effectIndex = 16 then
      [*] = ;            begin
      [*] = ;               if (gCampaign.arrItems[0] >= 2) and (_misc_CalcEffect(pEffect, 0, 0) > 0) then
      [*] = ;               gBoolRegister_ShowAdvice := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if newQueryID >= 0 then
      [*] = ;begin
      [*] = ;   next_query := IntToStr(newQueryID);
      [*] = ;   closeQuery := true;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   next_query := '';
      [*] = ;   //var value : Integer;
      [*] = ;   //if (gCampaign.arrItems[0] > 0) and (value > 0) then
      [*] = ;   //gBoolRegister_ShowAdvice := true;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;if gIntRegister_CurGameMode = gc_GameModeAstral then
      [*] = ;   MapExecuteState('astral.IsEndGame');
      [*] = ;
      [*] = ;BoolRegister0 := closeQuery;
      [*] = ;StringRegister0 := next_query;
   struct.end
section.end

