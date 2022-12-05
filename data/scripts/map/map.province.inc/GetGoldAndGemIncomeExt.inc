section.begin
   Name = GetGoldAndGemIncomeExt
   Description : struct.begin
      [*] = ;   IntRegister0 - bit flags mode
      [*] = ;      &1 - get gold total income
      [*] = ;      &2 - get gems total income
      [*] = ;      &4 - get income with stats
      [*] = ;   IntRegister1 - player handle for owner override or -1 for default
      [*] = ;RET: IntRegister0 - gold income
      [*] = ;     IntRegister1 - gem income
      [*] = ;     FloatRegister0 - gold income (float)
      [*] = ;     FloatRegister1 - gem income (float)
      [*] = ;     StringRegister0 - gold string array with stats (if mode&4 != 0) - fixed numbers x10:
      [*] = ;       [base_income]*perc1, outer_build,inner_build,sites,rituals,defender,
      [*] = ;       [+level_income_perc,*race_income_perc,+mood_increase_5perc]=perc1, exploration_decrease,outer_and_def_perc_increase,site_perc_increase,unit_level_decrease
      [*] = ;     StringRegister1 - gem string array with stats (if mode&4 != 0) - fixed numbers x10:
      [*] = ;       [base_income]*perc1, outer_build,inner_build,sites,rituals,defender,
      [*] = ;       [+level_income_perc,*race_income_perc,+mood_increase_div20]=perc1, exploration_decrease,outer_and_def_perc_increase
   struct.end
   Code : struct.begin
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var plHandle : Integer = IntRegister1;
      [*] = ;var g_mood_no,g_perc_start,i,j : Integer;
      [*] = ;var m_mood_no,m_perc_start : Integer;
      [*] = ;var gold,gem : Float;
      [*] = ;var g_stats : array [0..20] of Float;
      [*] = ;var g_no : Integer = 0;
      [*] = ;var m_stats : array [0..20] of Float;
      [*] = ;var m_no : Integer = 0;
      [*] = ;var stats_str_g : String;
      [*] = ;var stats_str_m : String;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;if _console_GetIntVar('DebugUseLegacyIncome') > 0 then
      [*] = ;begin
      [*] = ;   var gems,gold : Integer;
      [*] = ;
      [*] = ;   if((mode and 1) <> 0) then
      [*] = ;   begin
      [*] = ;      ExecuteState('GetGoldIncome');
      [*] = ;      gold := IntRegister0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      gold := 0;
      [*] = ;
      [*] = ;   if((mode and 2) <> 0) then
      [*] = ;   begin
      [*] = ;      ExecuteState('GetGemIncome');
      [*] = ;      gem := IntRegister0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      gem := 0;
      [*] = ;
      [*] = ;   FloatRegister0 := gold;
      [*] = ;   FloatRegister1 := gem;
      [*] = ;   IntRegister0 := Floor(gold);
      [*] = ;   IntRegister1 := Floor(gem);
      [*] = ;   StringRegister0 := '';
      [*] = ;   StringRegister1 := '';
      [*] = ;   SwitchTo('Nothing');
      [*] = ;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('IsPlayable');
      [*] = ;if BoolRegister0 then
      [*] = ;begin
      [*] = ;   var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;   var cDummyHandle : Integer = 0;
      [*] = ;   var pCastle : Integer = 0;
      [*] = ;   var pidx,perc_g,perc_m,check_gold,check_gem,mood : Integer;
      [*] = ;   var terType,resID,pDefender,pProvRace : Integer;
      [*] = ;   var pMyInnerBuildings : Integer;
      [*] = ;   var isResOpen : Boolean;
      [*] = ;   var provRaceID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;   var coastal : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Coast');
      [*] = ;   var provExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;   var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;   var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;
      [*] = ;   if ((mode and 4) = 0) then _log := false;
      [*] = ;   if((mode and 1) <> 0) then check_gold := 1 else check_gold := 0;
      [*] = ;   if((mode and 2) <> 0) then check_gem := 1 else check_gem := 0;
      [*] = ;   if plHandle = -1 then
      [*] = ;      plHandle := GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player'));
      [*] = ;   if plHandle <> 0 then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;      pCastle := IntRegister0;
      [*] = ;      cDummyHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID'));
      [*] = ;      pMyInnerBuildings := ParserSelectByHandleByKey(pCastle, 'InnerBuildings');
      [*] = ;   end
      [*] = ;   else
      [*] = ;      pMyInnerBuildings := 0;
      [*] = ;
      [*] = ;   IntRegister0 := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByKey(pProvince, 'Defender'), 'DefenderID');
      [*] = ;   MapExecuteState('GetDefenderParserByID');
      [*] = ;   pDefender := IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := provRaceID;
      [*] = ;   MapExecuteState('GetRaceParserByID');
      [*] = ;   pProvRace := IntRegister1;
      [*] = ;
      [*] = ;   if check_gold > 0 then
      [*] = ;   begin
      [*] = ;      terType := ParserGetIntValueByKeyByHandle(pProvince 'TerrainType');
      [*] = ;      resID := ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;      if (ParserGetBoolValueByKeyByHandle(pProvince, 'ResourceGuarded')) or (ParserGetIntValueByKeyByHandle(pProvince, 'ResourceExplore') > provExplore) then
      [*] = ;         isResOpen := false
      [*] = ;      else
      [*] = ;         isResOpen := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      isResOpen := false;
      [*] = ;
      [*] = ;   if check_gold > 0 then
      [*] = ;   begin
      [*] = ;      g_stats[g_no] := ParserGetIntValueByKeyByHandle(pProvince,'GoldInc');
      [*] = ;      if g_stats[g_no] <= 0 then
      [*] = ;         g_stats[g_no] := 1;
      [*] = ;      g_no := g_no + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if check_gem > 0 then
      [*] = ;   begin
      [*] = ;      m_stats[m_no] := ParserGetIntValueByKeyByHandle(pProvince,'GemInc');
      [*] = ;      if m_stats[m_no] <= 0 then
      [*] = ;         m_stats[m_no] := 1;
      [*] = ;      m_no := m_no + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _Log_map('Province index: '+ParserGetValueByKeyByHandle(pProvince,'Index'));
      [*] = ;   g_mood_no := g_no;
      [*] = ;   m_mood_no := m_no;
      [*] = ;
      [*] = ;   // outer buildings
      [*] = ;   gold := 0;
      [*] = ;   gem := 0;
      [*] = ;   perc_g := 0;
      [*] = ;   perc_m := 0;
      [*] = ;   for i := ParserGetCountByHandle(pProvOuterBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, i);
      [*] = ;      var outerBuildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;      if (outerBuildID<>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := outerBuildID;
      [*] = ;         MapExecuteState('GetOuterBuildParserByID');
      [*] = ;         var pOuterBuild : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if check_gold > 0 then
      [*] = ;         begin
      [*] = ;            gold := gold + ParserGetIntValueByKeyByHandle(pOuterBuild, 'GoldAdd');
      [*] = ;            perc_g := perc_g + ParserGetIntValueByKeyByHandle(pOuterBuild, 'GoldPerc');
      [*] = ;            // building abilities
      [*] = ;            var pBuildAbilities : Integer = ParserSelectByHandleByKey(pOuterBuild, 'Abilities');
      [*] = ;            for j := ParserGetCountByHandle(pBuildAbilities)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, j);
      [*] = ;               var abilID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;
      [*] = ;               if abilID = 6 then
      [*] = ;               begin
      [*] = ;                  var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;                  var param2 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;                  IntRegister0 := param2;
      [*] = ;                  if cDummyHandle <> 0 then
      [*] = ;                  begin
      [*] = ;                     GameObjectExecuteStateByHandle(cDummyHandle, 'CheckInnerBuilding');
      [*] = ;                     if BoolRegister0 then
      [*] = ;                        gold := gold + param1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // resource bonuses
      [*] = ;            if isResOpen then
      [*] = ;            begin
      [*] = ;               var pResBonuses : Integer = ParserSelectByHandleByKey(pOuterBuild, 'ResourceBonuses');
      [*] = ;               for j := ParserGetCountByHandle(pResBonuses)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pResBonus : Integer = ParserSelectByHandleByIndex(pResBonuses, j);
      [*] = ;
      [*] = ;                  if ParserGetIntValueByKeyByHandle(pResBonus, 'ResourceID') = resID then
      [*] = ;                  begin
      [*] = ;                     gold := gold + ParserGetIntValueByKeyByHandle(pResBonus, 'Bonus');
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if check_gem > 0 then
      [*] = ;         begin
      [*] = ;            gem := gem + ParserGetIntValueByKeyByHandle(pOuterBuild, 'GemAdd');
      [*] = ;            perc_m := perc_m + ParserGetIntValueByKeyByHandle(pOuterBuild, 'GemPerc');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   g_stats[g_no] := gold; g_no := g_no + 1;
      [*] = ;   m_stats[m_no] := gem; m_no := m_no + 1;
      [*] = ;
      [*] = ;   // inner buildings
      [*] = ;   gold := 0;
      [*] = ;   gem := 0;
      [*] = ;   if pMyInnerBuildings <> 0 then
      [*] = ;   begin
      [*] = ;      for i := ParserGetCountByHandle(pMyInnerBuildings)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pMyInnerBuildings, i), 'BuildingID');
      [*] = ;         MapExecuteState('GetInnerBuildParserByID');
      [*] = ;         var pBuildAbilities : Integer = ParserSelectByHandleByKey( IntRegister1, 'Abilities');
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pBuildAbilities)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, j);
      [*] = ;            var abilID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;            var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;
      [*] = ;            if check_gold > 0 then
      [*] = ;            begin
      [*] = ;               if (abilID = 14) then
      [*] = ;               begin
      [*] = ;                  if (param1 = 0) or (param1 = terType) or ((param1 = 8) and (coastal > 0)) then
      [*] = ;                     gold := gold + ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;               end;
      [*] = ;               if (abilID = 49) and (provRaceID = param1) then
      [*] = ;                  gold := gold + ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;               if (abilID = 9) and (resID = param1) and (isResOpen) then
      [*] = ;                  gold := gold + ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;            end;
      [*] = ;            if check_gem > 0 then
      [*] = ;            begin
      [*] = ;               if (abilID = 55) and (provRaceID = param1) then
      [*] = ;                  gem := gem + ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   g_stats[g_no] := gold; g_no := g_no + 1;
      [*] = ;   m_stats[m_no] := gem; m_no := m_no + 1;
      [*] = ;
      [*] = ;   // sites
      [*] = ;   IntRegister0 := 2;
      [*] = ;   ExecuteState('CheckSiteAbility');
      [*] = ;   g_stats[g_no] := IntRegister1; g_no := g_no + 1;
      [*] = ;   m_stats[m_no] := IntRegister2; m_no := m_no + 1;
      [*] = ;
      [*] = ;   // rutuals
      [*] = ;   IntRegister0 := 6;
      [*] = ;   ExecuteState('GetRitualBonus');
      [*] = ;   g_stats[g_no] := IntRegister1; g_no := g_no + 1;
      [*] = ;   m_stats[m_no] := IntRegister2; m_no := m_no + 1;
      [*] = ;
      [*] = ;   // defender
      [*] = ;   var pDefAbilities : Integer = ParserSelectByHandleByKey(pDefender, 'Abilities');
      [*] = ;   gold := 0;
      [*] = ;   gem := 0;
      [*] = ;   for i := ParserGetCountByHandle(pDefAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pDefAbility : Integer = ParserSelectByHandleByIndex(pDefAbilities, i);
      [*] = ;      var abilID : Integer = ParserGetIntValueByKeyByHandle(pDefAbility, 'AbilityID');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pDefAbility, 'Param1');
      [*] = ;
      [*] = ;      if (check_gold > 0) and (abilID = 7) and (param1 = resID) then
      [*] = ;         gold := gold + ParserGetIntValueByKeyByHandle(pDefAbility, 'Param2');
      [*] = ;
      [*] = ;      if abilID = 1 then
      [*] = ;      begin
      [*] = ;         perc_g := perc_g + param1;
      [*] = ;         perc_m := perc_m + ParserGetIntValueByKeyByHandle(pDefAbility, 'Param2');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   g_stats[g_no] := gold; g_no := g_no + 1;
      [*] = ;   m_stats[m_no] := gem; m_no := m_no + 1;
      [*] = ;
      [*] = ;   g_perc_start := g_no;
      [*] = ;   m_perc_start := m_no;
      [*] = ;   gold := 0;
      [*] = ;   gem := 0;
      [*] = ;   if check_gold > 0 then
      [*] = ;   begin
      [*] = ;      for i := 0 to g_mood_no-1 do
      [*] = ;         gold := gold + g_stats[i];
      [*] = ;   end;
      [*] = ;   if check_gem > 0 then
      [*] = ;   begin
      [*] = ;      for i := 0 to m_mood_no-1 do
      [*] = ;         gem := gem + m_stats[i];
      [*] = ;   end;
      [*] = ;   if _log then _Log_map('   Base gold: '+FloatToStr(gold));
      [*] = ;   if _log then _Log_map('   Base gem: '+FloatToStr(gem));
      [*] = ;
      [*] = ;   ExecuteState('GetLevel');
      [*] = ;   MapExecuteState('GetProvLevelParserByID');
      [*] = ;   i := ParserGetIntValueByKeyByHandle(IntRegister1, 'Income');
      [*] = ;   if check_gold > 0 then
      [*] = ;   begin
      [*] = ;      g_stats[g_no] := i;
      [*] = ;      g_no := g_no + 1;
      [*] = ;      gold := gold + (gold * i / 100);
      [*] = ;      if _log then _Log_map('   Extra gold with level: '+FloatToStr(gold));
      [*] = ;      g_stats[g_no] := ParserGetIntValueByKeyByHandle(pProvRace, 'GoldIncome');
      [*] = ;      g_no := g_no + 1;
      [*] = ;      gold := (gold * (g_stats[g_no-1]) / 100);
      [*] = ;      if _log then _Log_map('   Gold after race: '+FloatToStr(gold));
      [*] = ;   end;
      [*] = ;   if check_gem > 0 then
      [*] = ;   begin
      [*] = ;      m_stats[m_no] := i;
      [*] = ;      m_no := m_no + 1;
      [*] = ;      gem := gem + (gem * i / 100);
      [*] = ;      if _log then _Log_map('   Extra gem with level: '+FloatToStr(gem));
      [*] = ;      m_stats[m_no] := ParserGetIntValueByKeyByHandle(pProvRace, 'GemIncome');
      [*] = ;      m_no := m_no + 1;
      [*] = ;      gem := (gem * (m_stats[m_no-1]) / 100);
      [*] = ;      if _log then _Log_map('   Gem after race: '+FloatToStr(gem));
      [*] = ;   end;
      [*] = ;
      [*] = ;   // mood
      [*] = ;   ExecuteState('GetMood');
      [*] = ;   mood := IntRegister0;
      [*] = ;   if check_gold > 0 then
      [*] = ;   begin
      [*] = ;      g_stats[g_no] := mood * 5;
      [*] = ;      g_no := g_no + 1;
      [*] = ;      gold := gold + (gold * g_stats[g_no-1] / 100);
      [*] = ;      if _log then _Log_map('   Gold after mood: '+FloatToStr(gold));
      [*] = ;      // exploration
      [*] = ;      g_stats[g_no] := (gold * (100 - provExplore) / 500);
      [*] = ;      g_no := g_no + 1;
      [*] = ;      if provExplore = 100 then
      [*] = ;         g_stats[g_no-1] := g_stats[g_no-1] - 2;
      [*] = ;      gold := gold - g_stats[g_no-1];
      [*] = ;      if _log then _Log_map('   Gold after explore: '+FloatToStr(gold));
      [*] = ;
      [*] = ;      g_stats[g_no] := perc_g; g_no := g_no + 1;
      [*] = ;      for i := g_mood_no to g_perc_start-1 do
      [*] = ;         gold := gold + g_stats[i];
      [*] = ;
      [*] = ;      if _log then _Log_map('   Gold after build,sites, etc: '+FloatToStr(gold));
      [*] = ;      gold := gold + (gold * perc_g / 100);
      [*] = ;      if _log then _Log_map('   Gold after perc modifiers: '+FloatToStr(gold));
      [*] = ;
      [*] = ;      IntRegister0 := 6;
      [*] = ;      ExecuteState('CheckSiteAbility');
      [*] = ;      g_stats[g_no] := IntRegister1; g_no := g_no + 1;
      [*] = ;      gold := gold + (gold * IntRegister1 / 100);
      [*] = ;      if _log then _Log_map('   Gold after site perc modifiers: '+FloatToStr(gold));
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_plunderer;
      [*] = ;      ExecuteState('GetUnitsSkill');
      [*] = ;      g_stats[g_no] := IntRegister1; g_no := g_no + 1;
      [*] = ;      gold := gold - (gold * IntRegister1 / 100);
      [*] = ;      if _log then _Log_map('   Gold after plunder perc: '+FloatToStr(gold));
      [*] = ;
      [*] = ;      stats_str_g := '';
      [*] = ;      if ((mode and 4) <> 0) then
      [*] = ;      begin
      [*] = ;         for i := 0 to g_no-1 do
      [*] = ;            _sa_AddAsInt(stats_str_g,Floor(g_stats[i]*10));
      [*] = ;      end;
      [*] = ;      if gold < 0 then
      [*] = ;         gold := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if check_gem > 0 then
      [*] = ;   begin
      [*] = ;      m_stats[m_no] := ((mood * 5) / 100);
      [*] = ;      m_no := m_no + 1;
      [*] = ;      gem := gem + m_stats[m_no-1];
      [*] = ;      // exploration
      [*] = ;      m_stats[m_no] := (gem * (100 - provExplore) / 500);
      [*] = ;      m_no := m_no + 1;
      [*] = ;      gem := gem - m_stats[m_no-1];
      [*] = ;
      [*] = ;      m_stats[m_no] := perc_m; m_no := m_no + 1;
      [*] = ;      for i := m_mood_no to m_perc_start-1 do
      [*] = ;         gem := gem + m_stats[i];
      [*] = ;
      [*] = ;      gem := gem + (gem * perc_m / 100);
      [*] = ;
      [*] = ;      stats_str_m := '';
      [*] = ;      if ((mode and 4) <> 0) then
      [*] = ;      begin
      [*] = ;         for i := 0 to m_no-1 do
      [*] = ;            _sa_AddAsInt(stats_str_m,Floor(m_stats[i]*10));
      [*] = ;      end;
      [*] = ;      if gem < 0 then
      [*] = ;         gem := 0;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   gold := 0;
      [*] = ;   gem := 0;
      [*] = ;   stats_str_g := '';
      [*] = ;   stats_str_m := '';
      [*] = ;end;
      [*] = ;
      [*] = ;FloatRegister0 := gold;
      [*] = ;FloatRegister1 := gem;
      [*] = ;IntRegister0 := Floor(gold);
      [*] = ;IntRegister1 := Floor(gem);
      [*] = ;StringRegister0 := stats_str_g;
      [*] = ;StringRegister1 := stats_str_m;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

