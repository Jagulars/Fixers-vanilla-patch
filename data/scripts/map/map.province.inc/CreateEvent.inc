section.begin
   Name = CreateEvent
   UsedFileName = 
   Code : struct.begin
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var sum : Float = 0;
      [*] = ;var curSum : Float = 0;
      [*] = ;var rand : Float;
      [*] = ;
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(provPlHandle);
      [*] = ;var pEventTimers : Integer = ParserSelectByHandleByKey(pPlParser, 'EventTimers');
      [*] = ;
      [*] = ;var pEvents : Integer = gPrototypeData.events.handle;
      [*] = ;
      [*] = ;IntRegister0 := 12;
      [*] = ;ExecuteState('GetRitualBonus');
      [*] = ;var rit : Integer = IntRegister1;
      [*] = ;
      [*] = ;function IsLocked(eventID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pEventTimers)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pEventTimer : Integer = ParserSelectByHandleByIndex(pEventTimers, i);
      [*] = ;      var id : Integer = ParserGetIntValueByKeyByHandle(pEventTimer, 'EventID');
      [*] = ;      var timer : Integer = ParserGetIntValueByKeyByHandle(pEventTimer, 'Timer');
      [*] = ;
      [*] = ;      if (id = eventID) and (timer >= 0) then
      [*] = ;      begin
      [*] = ;         Result := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_rand_ClearRoll;
      [*] = ;var count : Integer = 0;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pEvents)-1 do
      [*] = ;begin
      [*] = ;   var pEvent : Integer = ParserSelectByHandleByIndex(pEvents, i);
      [*] = ;   var eventID : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'EventID');
      [*] = ;   //var freq : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'Possibility');
      [*] = ;
      [*] = ;   IntRegister0 := eventID;
      [*] = ;   IntRegister1 := rit;
      [*] = ;   ExecuteState('GetEventPoss');
      [*] = ;   var freq : Integer = IntRegister2;
      [*] = ;
      [*] = ;   if freq > 0 then
      [*] = ;   begin
      [*] = ;      {IntRegister0 := eventID;
      [*] = ;      ExecuteState('CheckEventConditions');
      [*] = ;      var canOccur : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;      if (not IsLocked(eventID)) and canOccur then}
      [*] = ;      if not IsLocked(eventID) then
      [*] = ;      begin
      [*] = ;         gArrRollerN[count] := eventID;
      [*] = ;         gArrRollerP[count] := freq;
      [*] = ;         count := count + 1;
      [*] = ;
      [*] = ;         sum := sum + freq;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gScenario.enabled) then
      [*] = ;begin
      [*] = ;   pEvents := gPrototypeData.scenarioevents.handle;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pEvents)-1 do
      [*] = ;   begin
      [*] = ;      var pEvent : Integer = ParserSelectByHandleByIndex(pEvents, i);
      [*] = ;      var eventID : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'EventID');
      [*] = ;      //var freq : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'Possibility');
      [*] = ;
      [*] = ;      IntRegister0 := eventID;
      [*] = ;      IntRegister1 := rit;
      [*] = ;      ExecuteState('GetEventPoss');
      [*] = ;      var freq : Integer = IntRegister2;
      [*] = ;
      [*] = ;      if freq > 0 then
      [*] = ;      begin
      [*] = ;         if not IsLocked(eventID) then
      [*] = ;         begin
      [*] = ;            gArrRollerN[count] := eventID;
      [*] = ;            gArrRollerP[count] := freq;
      [*] = ;            count := count + 1;
      [*] = ;
      [*] = ;            sum := sum + freq;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var eventID : Integer = _rand_Roll(false);
      [*] = ;
      [*] = ;IntRegister0 := eventID;
      [*] = ;ExecuteState('CreateEventByID');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

