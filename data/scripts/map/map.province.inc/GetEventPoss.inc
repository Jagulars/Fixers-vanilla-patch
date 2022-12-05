section.begin
   Name = GetEventPoss
   Description : struct.begin
      [*] = ;IntRegister0 - event ID
      [*] = ;OUT: IntRegister1 - event possibility
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var eventID : Integer = IntRegister0;
      [*] = ;var ritualObstruction : Integer = IntRegister1;
      [*] = ;var pEvents, pEvent : Integer;
      [*] = ;if (eventID>=gc_query_ScenarioEventMinIndex) then
      [*] = ;begin
      [*] = ;   pEvents := gPrototypeData.scenarioevents.handle;
      [*] = ;   pEvent := ParserSelectByHandleByIndex(pEvents, eventID-gc_query_ScenarioEventMinIndex);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   pEvents := gPrototypeData.events.handle;
      [*] = ;   pEvent := ParserSelectByHandleByIndex(pEvents, eventID);
      [*] = ;end;
      [*] = ;var eventType : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'Type');
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;var pProvince : Integer = GetIntValueByIndex(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;
      [*] = ;var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;var plKarma : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var poss : Integer = 0;
      [*] = ;
      [*] = ;var attacker : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'Attacker');
      [*] = ;
      [*] = ;if (attacker = 0) or (ritualObstruction = 0) then
      [*] = ;begin
      [*] = ;   IntRegister0 := eventID;
      [*] = ;   ExecuteState('CheckEventConditions');
      [*] = ;   var canOccur : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   if canOccur then
      [*] = ;   begin
      [*] = ;      poss := ParserGetIntValueByKeyByHandle(pEvent, 'Possibility');
      [*] = ;
      [*] = ;      // check neighbours event possibility
      [*] = ;      var pProvNeighbours : Integer = ParserSelectByHandleByKey(pProvince, 'Neighbours');
      [*] = ;      for i := ParserGetCountByHandle(pProvNeighbours)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvNeighbour : Integer = ParserSelectByHandleByIndex(pProvNeighbours, i);
      [*] = ;         var index : Integer = ParserGetIntValueByKeyByHandle(pProvNeighbour, 'Index');
      [*] = ;         var pNProvince : Integer = ParserSelectByHandleByIndex(pProvinces, index);
      [*] = ;         var provType : Integer = ParserGetIntValueByKeyByHandle(pNProvince, 'ProvinceType');
      [*] = ;         var nProvPlName : String = ParserGetValueByKeyByHandle(pNProvince, 'Player');
      [*] = ;         var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provincetypes.handle, provType);
      [*] = ;         var pProvEvents : Integer = ParserSelectByHandleByKey(pProvinceType, 'Events');
      [*] = ;
      [*] = ;         if nProvPlName = '' then
      [*] = ;         begin
      [*] = ;            for j := ParserGetCountByHandle(pProvEvents)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pProvEvent : Integer = ParserSelectByHandleByIndex(pProvEvents, j);
      [*] = ;               var id : Integer = ParserGetIntValueByKeyByHandle(pProvEvent, 'EventID');
      [*] = ;
      [*] = ;               if id = eventID then
      [*] = ;               begin
      [*] = ;                  poss := poss + ParserGetIntValueByKeyByHandle(pProvEvent, 'Possibility');
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // check sites possibility
      [*] = ;      IntRegister0 := 4;
      [*] = ;      IntRegister1 := eventID;
      [*] = ;      ExecuteState('CheckSiteAbilityByParam1');
      [*] = ;      poss := poss + IntRegister2;
      [*] = ;
      [*] = ;      // world rule
      [*] = ;      if (_worldrule_GetWorldRuleEventsExist()) then
      [*] = ;      begin
      [*] = ;         if (_worldrule_GetWorldRuleEventExistByID(eventID)) then
      [*] = ;            poss := _worldrule_GetWorldRuleEventPossibilityByID(eventID); // Абсолютное число (не в проценте)
      [*] = ;      end;
      [*] = ;
      [*] = ;      if poss > 0 then
      [*] = ;      begin
      [*] = ;         // check outer buildings
      [*] = ;         if isCastle then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 45;
      [*] = ;            IntRegister1 := eventID;
      [*] = ;            ExecuteState('CheckInnerBuildAbilityByParam1');
      [*] = ;            poss := poss + (poss * IntRegister2) div 100;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := 7;
      [*] = ;            IntRegister1 := eventID;
      [*] = ;            ExecuteState('CheckOuterBuildAbilityByParam1');
      [*] = ;            poss := poss + (poss * IntRegister2) div 100;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if plHandle <> 0 then
      [*] = ;         begin
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;            var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle( IntRegister0 , 'DummyUID'));
      [*] = ;            if cDummyHandle <> 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 38; // oracle decrease bad event increase good
      [*] = ;               GameObjectExecuteStateByHandle(cDummyHandle, 'CheckInnerBuildAbility');
      [*] = ;               if ((plKarma + IntRegister1) * eventType > 0) or ((plKarma + IntRegister1 = 0) and (eventType = 0)) then
      [*] = ;                  poss := poss + Round(poss * Abs(plKarma + IntRegister1)) div 100;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if poss < 1 then
      [*] = ;            poss := 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister2 := poss;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

