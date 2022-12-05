section.begin
   Name = ProceedEncounter
   Description : struct.begin
      [*] = ;IntRegister0 - encounter ID to proceed
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\PROCEEDENCOUNTER';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;procedure ProcessAIQuerySelection(encounterID,provHandle,provParser,queryHandle : Integer);
      [*] = ;begin
      [*] = ;   var resHandle : Integer;
      [*] = ;   var t : Integer;
      [*] = ;   var queryID : String;
      [*] = ;
      [*] = ;   // always choose first query result
      [*] = ;   while queryHandle <> 0 do
      [*] = ;   begin
      [*] = ;      resHandle := QueryMachineQueryGetResults(queryHandle);
      [*] = ;      if QueryMachineResultsCount(resHandle) > 0 then
      [*] = ;      begin
      [*] = ;         queryHandle := QueryMachineResultsGetByIndex(resHandle,0);
      [*] = ;         QueryMachineResultDoSelectExecute(queryHandle);
      [*] = ;         queryID := QueryMachineResultGetNextQuery(queryHandle);
      [*] = ;         if queryID = '' then
      [*] = ;         begin
      [*] = ;            IntRegister0 := encounterID;
      [*] = ;            MapExecuteState('GetEncounterParserByID');
      [*] = ;            t := ParserGetIntValueByKeyByHandle(IntRegister1,'GuardType');
      [*] = ;            if t > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := t;
      [*] = ;               ExecuteState('SetupEncGuard');
      [*] = ;
      [*] = ;               IntRegister0 := provParser;
      [*] = ;               ExecuteState('CheckAttackMode');
      [*] = ;            end;
      [*] = ;
      [*] = ;            if gIntRegister_EncounterResult > -3 then
      [*] = ;            begin
      [*] = ;               case gIntRegister_EncounterResult of
      [*] = ;                  0 : begin // retreat guard
      [*] = ;                     BoolRegister0 := false;
      [*] = ;                     ExecuteState('RetreatGuard');
      [*] = ;                     gIntRegister_EncounterResult := -3;
      [*] = ;                  end;
      [*] = ;                  -1 : begin // TODO: attack guard of your own province (ai not supported !!!)
      [*] = ;                  end;
      [*] = ;                  -2 : begin // diplomatic province capture
      [*] = ;                     IntRegister0 := GetGameObjectPlayerHandleByHandle(GetGameObjectMyHandle());
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     GameObjectExecuteStateByHandle(provHandle, 'CaptureProvince');
      [*] = ;                     SetGameObjectIntValueIndByHandle(GetGameObjectMyHandle(), gc_map_GOStack_MapUnit_iTask, gc_UnitTaskRest);
      [*] = ;                     SetGameObjectIntValueIndByHandle(GetGameObjectMyHandle(), gc_map_GOStack_MapUnit_iActionType, 0);
      [*] = ;                     IntRegister0 := GetGameObjectMyHandle();
      [*] = ;                     GUIExecuteState('map.GUIUpdateHeroHUD');
      [*] = ;                  end
      [*] = ;                  else begin
      [*] = ;                     if gIntRegister_EncounterResult > 0 then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := GetGameObjectPlayerHandleByHandle(GetGameObjectMyHandle());
      [*] = ;                        IntRegister1 := gIntRegister_EncounterResult;
      [*] = ;                        GameObjectExecuteStateByHandle(provHandle, 'DiplCaptureProvince');
      [*] = ;
      [*] = ;                        SetGameObjectIntValueIndByHandle(GetGameObjectMyHandle(), gc_map_GOStack_MapUnit_iTask, gc_UnitTaskRest);
      [*] = ;                        SetGameObjectIntValueIndByHandle(GetGameObjectMyHandle(), gc_map_GOStack_MapUnit_iActionType, 0);
      [*] = ;                        IntRegister0 := GetGameObjectMyHandle();
      [*] = ;                        GUIExecuteState('map.GUIUpdateHeroHUD');
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;            end;
      [*] = ;            queryHandle := 0;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            queryHandle := QueryMachineCustomQueryCreate(queryID);
      [*] = ;            QueryMachineQueryDoCreateExecute(queryHandle);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;          queryHandle := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   gIntRegister_CurQueryHandle := 0;
      [*] = ;   _gv_SetMapLock($10000,_log_name);
      [*] = ;end;
      [*] = ;
      [*] = ;var encounterID : Integer = IntRegister0;
      [*] = ;var queryID : String = IntToStr(encounterID);
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName;
      [*] = ;var curUID : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;var pCurProvince : Integer = _misc_GetProvinceParserByUID(curUID);
      [*] = ;
      [*] = ;var pEncounter : Integer = ParserSelectByHandleByIndex(gPrototypeData.encounters.handle, encounterID - gc_query_EncounterMinIndex);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(encounterID)+']',_log_trace);
      [*] = ;var queryHandle : Integer = QueryMachineCustomQueryCreate(queryID);
      [*] = ;gIntRegister_CurQueryHandle := queryHandle;
      [*] = ;gIntRegister_CurrentEncounterID := encounterID;
      [*] = ;gIntRegister_AfterBattleEncounterID := 0;
      [*] = ;
      [*] = ;var qCount : Integer = QueryMachineCustomQueriesCount;
      [*] = ;
      [*] = ;QueryMachineQueryDoCreateExecute(queryHandle);
      [*] = ;//QueryMachineQueryDoParserExecute(queryHandle);
      [*] = ;var newQueryID : String = StringRegister0;
      [*] = ;var openHeroWindow : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;if openHeroWindow and (newQueryID <> queryID) then
      [*] = ;begin
      [*] = ;   var pMachineParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle);
      [*] = ;   var pQueries : Integer = ParserSelectByHandleByKey(pMachineParser, 'Queries');
      [*] = ;   var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;   ParserSetValueByKeyByHandle(pQuery, 'QueryID', newQueryID);
      [*] = ;   ParserSetIntValueByKeyByHandle(pQuery, 'HeroUID', myUID);
      [*] = ;
      [*] = ;   SetGUIValue('QueryID', '');
      [*] = ;   GUIExecuteState('ToolQueryWindow');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if newQueryID <> queryID then
      [*] = ;   begin
      [*] = ;      var id : Integer = StrToInt(newQueryID);
      [*] = ;
      [*] = ;      if (id > gc_query_EncounterMinIndex) and (id <= gc_query_EncounterMaxIndex) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := StrToInt(newQueryID);
      [*] = ;         ExecuteState('ProceedEncounter');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (id > gc_query_EventMinIndex) and (id <= gc_query_EventMaxIndex) then
      [*] = ;         begin
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(curUID);
      [*] = ;            gIntRegister_CurProvinceIndex := GetGameObjectIndexByHandle(dummyHandle);
      [*] = ;
      [*] = ;            IntRegister0 := id;
      [*] = ;            //IntRegister1 := 0;
      [*] = ;            //BoolRegister0 := false;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'ProceedEvent');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if myPlIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if myPlIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;      begin
      [*] = ;         var resHandle : Integer = QueryMachineQueryGetResults(queryHandle);
      [*] = ;         var resCount : Integer = QueryMachineResultsCount(resHandle);
      [*] = ;
      [*] = ;         var guardTypeID : Integer = ParserGetIntValueByKeyByHandle(pEncounter, 'GuardType');
      [*] = ;         if guardTypeID > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := guardTypeID;
      [*] = ;            ExecuteState('SetupEncGuard');
      [*] = ;
      [*] = ;            IntRegister0 := gIntRegister_BattleDefendArmy;
      [*] = ;            IntRegister1 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;            ExecuteState('SetupBattleRegisters');
      [*] = ;         end;
      [*] = ;
      [*] = ;         if resCount > 0 then
      [*] = ;         begin
      [*] = ;            _gui_ProgressCalculations(_log_name+' Encounter ' + queryID + ' appeared');
      [*] = ;            var queryID : String = QueryMachineQueryGetID(queryHandle);
      [*] = ;            SetGUIValue('QueryID', queryID);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            SetGUIValue('QueryID', '');
      [*] = ;            gIntRegister_MapActiveHeroHandle := 0;
      [*] = ;
      [*] = ;            var guardTypeID : Integer = ParserGetIntValueByKeyByHandle(pEncounter, 'GuardType');
      [*] = ;            if guardTypeID > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pCurProvince;
      [*] = ;               ExecuteState('CheckAttackMode');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (not gBoolRegister_MapProceedBattle) and (not openHeroWindow) then
      [*] = ;               _gv_SetMapLock($10000,_log_name);
      [*] = ;         end;
      [*] = ;
      [*] = ;         GUIExecuteState('ToolQueryWindow');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ProcessAIQuerySelection(encounterID,GetGameObjectHandleByUniqueId(curUID),pCurProvince,queryHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+newQueryID+','+BoolToStr(openHeroWindow)+']',$1000000 or _log_trace);
   struct.end
section.end

