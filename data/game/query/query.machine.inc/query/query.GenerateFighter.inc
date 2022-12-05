section.begin
   Name = query.GenerateFighter
   UsedFileName =
   Code : struct.begin
      [*] = ;var plHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, plHandle);
      [*] = ;var wins : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iArenaWinCount);
      [*] = ;
      [*] = ;var resultHandle : Integer = _query_GetExecutedHandle();
      [*] = ;
      [*] = ;if QueryMachineIsResultHandle(resultHandle) then
      [*] = ;begin
      [*] = ;   var resultID : String = QueryMachineResultGetID(resultHandle);
      [*] = ;
      [*] = ;   if (IsDelimiterCharExists(resultID, gc_gui_DotChar)) then
      [*] = ;   begin
      [*] = ;      var strCount : Integer = GetDelimiterStringCount(resultID, gc_gui_DotChar, gc_gui_QuoteChar);
      [*] = ;      if (strCount>=2) then
      [*] = ;      begin
      [*] = ;         var resIndex : Integer = StrToInt(GetDelimiterStringByIndex(resultID, gc_gui_DotChar, gc_gui_QuoteChar, 1));
      [*] = ;
      [*] = ;         gIntRegister_ArenaLeague := resIndex;
      [*] = ;
      [*] = ;         if (resIndex = 3) and (wins = 9) then
      [*] = ;         begin
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'GenerateOrca');
      [*] = ;            QueryMachineResultSetNextQuery(resultHandle, IntToStr(gc_gui_query_heroArenaOrcaBattle));
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var level : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;            var newLevel : Integer = level;
      [*] = ;
      [*] = ;            case gIntRegister_ArenaLeague of
      [*] = ;               1 : newLevel := newLevel - _rand_Random(level div 5) - level div 5;
      [*] = ;               2 : newLevel := newLevel + 2 - _rand_Random(3);
      [*] = ;               3 : newLevel := newLevel + 3 + _rand_Random(3);
      [*] = ;            end;
      [*] = ;
      [*] = ;            if newLevel > 30 then
      [*] = ;               newLevel := 30;
      [*] = ;
      [*] = ;            IntRegister0 := newLevel;
      [*] = ;            IntRegister1 := gIntRegister_ArenaLeague;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'GenerateFighter');
      [*] = ;            var heroHandle : Integer = GetGameObjectHandleByUniqueId( IntRegister2 );
      [*] = ;            _hero_GetName(heroHandle, gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(heroHandle, 'GetClass');
      [*] = ;            gStringRegister_DefenderHeroClass := GetLocaleTableListItemByID('hero_class', IntToStr( IntRegister0 ));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

