section.begin
   Name = StringReplaceParams
   Description : struct.begin
      [*] = ;StringRegister0 - string to modify
      [*] = ;OUT: StringRegister1 - modified string
   struct.end
   Code : struct.begin
      [*] = ;var provMoodInd : Integer = $10000;
      [*] = ;var nextLevelTurns : Integer = $10000;
      [*] = ;var rebelTurns : Integer = $10000;
      [*] = ;
      [*] = ;procedure CalculateMoodVariables();
      [*] = ;begin
      [*] = ;   if (gIntRegister_CurGameMode=gc_GameModeStrategy) and (provMoodInd = $10000) then
      [*] = ;   begin
      [*] = ;      var dummyUID : Integer = gIntRegister_MoodDummyUID;
      [*] = ;
      [*] = ;      provMoodInd := 75;
      [*] = ;
      [*] = ;      if dummyUID>0 then
      [*] = ;      begin
      [*] = ;         var provMood : Integer;
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;         provMood := IntRegister0;
      [*] = ;         if (provMood<-5) then
      [*] = ;            provMoodInd := 75
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (provMood>3) then
      [*] = ;               provMoodInd := 83
      [*] = ;            else
      [*] = ;               provMoodInd := 80+provMood;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CalculateLevelVariables();
      [*] = ;begin
      [*] = ;   if (gIntRegister_CurGameMode=gc_GameModeStrategy) and (nextLevelTurns = $10000) then
      [*] = ;   begin
      [*] = ;      var dummyUID : Integer = gIntRegister_MoodDummyUID;
      [*] = ;
      [*] = ;      nextLevelTurns := 0;
      [*] = ;
      [*] = ;      if dummyUID>0 then
      [*] = ;      begin
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;         IntRegister0 := dummyUID;
      [*] = ;         ExecuteState('GetProvinceParserByUID');
      [*] = ;         var pProvince : Integer = IntRegister1;
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CalcNextLevelTurns');
      [*] = ;         nextLevelTurns := IntRegister0;
      [*] = ;
      [*] = ;         if ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel') = gc_MaxProvinceLevel then
      [*] = ;            nextLevelTurns := 0;
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CalcRebelTurns');
      [*] = ;         rebelTurns := IntRegister0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CalculateRebelVariables();
      [*] = ;begin
      [*] = ;   if (gIntRegister_CurGameMode=gc_GameModeStrategy) and (rebelTurns = $10000) then
      [*] = ;   begin
      [*] = ;      var dummyUID : Integer = gIntRegister_MoodDummyUID;
      [*] = ;
      [*] = ;      rebelTurns := 0;
      [*] = ;
      [*] = ;      if dummyUID>0 then
      [*] = ;      begin
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CalcRebelTurns');
      [*] = ;         rebelTurns := IntRegister0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var str : String = StringRegister0;
      [*] = ;var reg_ex : Boolean;
      [*] = ;var _log_name : String = 'COMMON.INC\STRINGREPLACEPARAMS';
      [*] = ;var _log_trace : Integer = $20000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;reg_ex := RegExprExec(gIntRegister_StringReplaceRegExHandle,str);
      [*] = ;if not reg_ex then
      [*] = ;begin
      [*] = ;   //_log_map(_log_name+' skipping line without tokens.');
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   StringRegister1 := str;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_CurGameMode = gc_GameModeStrategy) or (gIntRegister_CurGameMode = gc_GameModeTactics) then
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var plGoldInc : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;   var plGemInc : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;   var myPlName : String;
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetName');
      [*] = ;   myPlName := StringRegister0;
      [*] = ;
      [*] = ;   if StrExists(str,'%hero_name%') then
      [*] = ;   begin
      [*] = ;      var color : String = '%color(warning)%';
      [*] = ;      if _gui_GetWindow('map_heropanel.map_heropanel_leftside.map_heropanel_btn_astralaccept') <> 0 then
      [*] = ;         color := '%color(default)%';
      [*] = ;      
      [*] = ;      str := StrReplace(str, '%hero_name%', color + gStringRegister_MyHeroName+'%color(default)%');
      [*] = ;   end;
      [*] = ;
      [*] = ;   str := StrReplace(str, '%prov_name%', {'%color(info)%'}'%color(warning)%'+gStringRegister_ProvinceName+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%defender_enemy_count%', {'%color(attention)%'}'%color(warning)%'+IntToStr(gIntRegister_DefenderEnemyCount)+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%defender_enemy_list%', '%color(warning)%'+gStringRegister_DefenderEnemyList+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%guard_enemy_count%', {'%color(attention)%'}'%color(warning)%'+IntToStr(gIntRegister_GuardEnemyCount)+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%guard_enemy_list%', '%color(warning)%'+gStringRegister_GuardEnemyList+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%turns_to_hero_revive%', IntToStr(gIntRegister_TurnsOnHeroRevive));
      [*] = ;   str := StrReplace(str, '%gold_cost%', IntToStr(gIntRegister_GoldCost));
      [*] = ;   str := StrReplace(str, '%gem_cost%', IntToStr(gIntRegister_GemCost));
      [*] = ;   str := StrReplace(str, '%enemy_player_name%', {'%color(info)%'}'%color(warning)%'+gStringRegister_EnemyPlayerName+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%enemy_player_name_nc%', gStringRegister_EnemyPlayerName);
      [*] = ;   str := StrReplace(str, '%enemy_hero_name%', {'%color(info)%'}'%color(warning)%'+gStringRegister_EnemyHeroName+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%enemy_hero_army_count%', {'%color(attention)%'}'%color(warning)%'+IntToStr(gIntRegister_EnemyHeroArmyCount)+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%enemy_hero_army_list%', '%color(warning)%'+gStringRegister_EnemyHeroArmyList+'%color(default)%');
      [*] = ;   str := StrReplace(str, '%siege_turns_left%', IntToStr(gIntRegister_SiegeTurnsLeft));
      [*] = ;   str := StrReplace(str, '%site_name%', gStringRegister_SiteName);
      [*] = ;   str := StrReplace(str, '%record_place%', IntToStr(gIntRegister_RecordPlace));
      [*] = ;   str := StrReplace(str, '%battle_turns_left%', 'TODO'{IntToStr(gIntRegister_)});
      [*] = ;   str := StrReplace(str, '%attacker_hero_class%', gStringRegister_AttackerHeroClass);
      [*] = ;   str := StrReplace(str, '%defender_hero_class%', gStringRegister_DefenderHeroClass);
      [*] = ;   str := StrReplace(str, '%diplomacy_turns_left%', IntToStr(gIntRegister_DiplomacyTurnLeft));
      [*] = ;   str := StrReplace(str, '%false_alarm_price%', IntToStr(gIntRegister_FalseAlarmPrice));
      [*] = ;   str := StrReplace(str, '%poisoned_water_price%', IntToStr(gIntRegister_PoisonedWaterPrice));
      [*] = ;   str := StrReplace(str, '%panic_price%', IntToStr(gIntRegister_PanicPrice));
      [*] = ;   str := StrReplace(str, '%player_gold%', IntToStr(plGold));
      [*] = ;   str := StrReplace(str, '%player_gem%', IntToStr(plGem));
      [*] = ;   str := StrReplace(str, '%player_gold_income%', IntToStr(plGoldInc));
      [*] = ;   str := StrReplace(str, '%player_gem_income%', IntToStr(plGemInc));
      [*] = ;   str := StrReplace(str, '%quest_value%', gStringRegister_QuestValue);
      [*] = ;   str := StrReplace(str, '%build_name%', gStringRegister_BuildName);
      [*] = ;   str := StrReplace(str, '%terrain_name%', gStringRegister_TerrainName);
      [*] = ;   str := StrReplace(str, '%player_name%', myPlName);
      [*] = ;   str := StrReplace(str, '%players_list%', gStringRegister_PlayersList);
      [*] = ;
      [*] = ;   if StrExists(str,'%province_mood%') then
      [*] = ;   begin
      [*] = ;      CalculateMoodVariables();
      [*] = ;      str := StrReplace(str, '%province_mood%', GetLocaleTableListItemByID('gui', IntToStr(provMoodInd)));
      [*] = ;   end;
      [*] = ;   if StrExists(str,'%province_nextlevel_turns%') then
      [*] = ;   begin
      [*] = ;      CalculateLevelVariables();
      [*] = ;      if nextLevelTurns > 0 then
      [*] = ;         str := StrReplace(str, '%province_nextlevel_turns%', IntToStr(nextLevelTurns))
      [*] = ;      else
      [*] = ;         str := StrReplace(str, '%province_nextlevel_turns%', '-');
      [*] = ;   end;
      [*] = ;   if StrExists(str,'%province_uprising_turns%') then
      [*] = ;   begin
      [*] = ;      CalculateRebelVariables();
      [*] = ;      if rebelTurns > 0 then
      [*] = ;         str := StrReplace(str, '%province_uprising_turns%', IntToStr(rebelTurns))
      [*] = ;      else
      [*] = ;         str := StrReplace(str, '%province_uprising_turns%', '-');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   str := StrReplace(str, '%enemy_player_name%', gStringRegister_EnemyPlayerName);
      [*] = ;   str := StrReplace(str, '%player_name%', gProfile.name);
      [*] = ;end;
      [*] = ;
      [*] = ;str := StrReplace(str, '%explore_value%', IntToStr(gIntRegister_ExploreValue));
      [*] = ;str := StrReplace(str, '%ability_power%', IntToStr(gIntRegister_AbilityPower));
      [*] = ;str := StrReplace(str, '%battle_effect_value%', IntToStr(gIntRegister_BattleEffectValue));
      [*] = ;str := StrReplace(str, '%hero_class%', gStringRegister_HeroClass);
      [*] = ;str := StrReplace(str, '%hero_level%', IntToStr(gIntRegister_HeroLevel));
      [*] = ;str := StrReplace(str, '%effect_value%', IntToStr(gIntRegister_EffectValue));
      [*] = ;str := StrReplace(str, '%shard_name%', gStringRegister_ShardName);
      [*] = ;str := StrReplace(str, '%guardian_artifact_percent%', IntToStr(gIntRegister_GuardianArtifactPercent));
      [*] = ;str := StrReplace(str, '%ruler_title%', gStringRegister_RulerTitle);
      [*] = ;str := StrReplace(str, '%num_years%', IntToStr(gIntRegister_NumYears));
      [*] = ;str := StrReplace(str, '%str_years%', gStringRegister_StrYears);
      [*] = ;str := StrReplace(str, '%unit_name%', gStringRegister_UnitName);
      [*] = ;str := StrReplace(str, '%unit_num%', IntToStr(gIntRegister_UnitCount));
      [*] = ;str := StrReplace(str, '%resource_name%', gStringRegister_ResourceName);
      [*] = ;str := StrReplace(str, '%energy_cost%', IntToStr(gIntRegister_AstralEnergy));
      [*] = ;str := StrReplace(str, '%spell_name%', gStringRegister_SpellName);
      [*] = ;str := StrReplace(str, '%enemy_player_name_2%', {'%color(info)%'}'%color(warning)%'+gStringRegister_EnemyPlayerNameDiplomacy+'%color(default)%'); // todo gStringRegister_EnemyPlayerNameDiplomacy
      [*] = ;str := StrReplace(str, '%gold_reward%', IntToStr(gIntRegister_GoldReward));
      [*] = ;str := StrReplace(str, '%gem_reward%', IntToStr(gIntRegister_GemReward));
      [*] = ;str := StrReplace(str, '%skill_name%', gStringRegister_SkillName);
      [*] = ;str := StrReplace(str, '%astral_energy%', IntToStr(gIntRegister_AstralEnergy));
      [*] = ;if StrExists(str,'%game_version%') then
      [*] = ;begin
      [*] = ;   var gameVersion : String;
      [*] = ;   _misc_GetBuildVersionExt(gameVersion);
      [*] = ;   gameVersion := StrReplace(gameVersion, '_', ' ');
      [*] = ;   str := StrReplace(str, '%game_version%', gameVersion);
      [*] = ;end;
      [*] = ;str := StrReplace(str, '%data_file%', gc_DataModFile);
      [*] = ;str := StrReplace(str, '%%minimum_allowed_classes%%', IntToStr(gc_MinAllowedHeroClasses));
      [*] = ;
      [*] = ;str := StrReplace(str, '$', '%color(ignore)%'+gc_gui_GoldIconChar+'%color(restore)%');
      [*] = ;str := StrReplace(str, '&', '%color(ignore)%'+gc_gui_GemIconChar+'%color(restore)%');
      [*] = ;str := StrReplace(str, '~', '%');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;StringRegister1 := str;
   struct.end
section.end

