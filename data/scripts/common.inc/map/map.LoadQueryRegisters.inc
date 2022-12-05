section.begin
   Name = map.LoadQueryRegisters
   Description[*] = ;IntRegister0 - parser
   Code : struct.begin
      [*] = ;var pParser : Integer = IntRegister0;
      [*] = ;
      [*] = ;procedure ConvertHeroName(var heroName : String);
      [*] = ;begin
      [*] = ;   var value : String = heroName;
      [*] = ;   var plInd : Integer = _sa_GetAsInt(value, 0);
      [*] = ;   var goInd : Integer = _sa_GetAsInt(value, 1);
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(goInd, plHandle);
      [*] = ;   _hero_GetName(goHandle, heroName);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ConvertUnitIndices(var nameIndices : String);
      [*] = ;begin
      [*] = ;   var oldNameIndices : String = nameIndices;
      [*] = ;   nameIndices := '';
      [*] = ;   while StrLength(oldNameIndices) > 0 do
      [*] = ;   begin
      [*] = ;      var ind : Integer = 0;
      [*] = ;      if StrPos(',', oldNameIndices) > 0 then
      [*] = ;      begin
      [*] = ;         var pos : Integer = StrPos(',', oldNameIndices);
      [*] = ;         var len : Integer = StrLength(oldNameIndices);
      [*] = ;         var indStr : String = SubStr(oldNameIndices, 0, pos-1);
      [*] = ;         ind := StrToInt(indStr);
      [*] = ;         oldNameIndices := SubStr(oldNameIndices, pos+2, len-pos-1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var indStr : String = oldNameIndices;
      [*] = ;         ind := StrToInt(indStr);
      [*] = ;         oldNameIndices := '';
      [*] = ;      end;
      [*] = ;      
      [*] = ;      var unitName : String = GetLocaleTableListItemByID('unit', IntToStr(ind));
      [*] = ;      if nameIndices <> '' then
      [*] = ;      nameIndices := nameIndices + ', ';
      [*] = ;      nameIndices := nameIndices + unitName;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;gStringRegister_MyHeroName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_MyHeroName');
      [*] = ;gStringRegister_ProvinceName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_ProvinceName');
      [*] = ;gIntRegister_DefenderEnemyCount := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_DefenderEnemyCount');
      [*] = ;gStringRegister_DefenderEnemyList := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_DefenderEnemyList');
      [*] = ;gIntRegister_GuardEnemyCount := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_GuardEnemyCount');
      [*] = ;gStringRegister_GuardEnemyList := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_GuardEnemyList');
      [*] = ;gIntRegister_TurnsOnHeroRevive := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_TurnsOnHeroRevive');
      [*] = ;gIntRegister_GoldCost := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_GoldCost');
      [*] = ;gIntRegister_GemCost := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_GemCost');
      [*] = ;gStringRegister_EnemyPlayerName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_EnemyPlayerName');
      [*] = ;gStringRegister_EnemyPlayerNameDiplomacy := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_EnemyPlayerNameDiplomacy');
      [*] = ;gStringRegister_EnemyHeroName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_EnemyHeroName');
      [*] = ;gIntRegister_EnemyHeroArmyCount := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_EnemyHeroArmyCount');
      [*] = ;gStringRegister_EnemyHeroArmyList := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_EnemyHeroArmyList');
      [*] = ;gIntRegister_SiegeTurnsLeft := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_SiegeTurnsLeft');
      [*] = ;gIntRegister_EffectValue := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_EffectValue');
      [*] = ;gStringRegister_SiteName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_SiteName');
      [*] = ;gIntRegister_ExploreValue := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_ExploreValue');
      [*] = ;gIntRegister_AbilityPower := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_AbilityPower');
      [*] = ;gIntRegister_GoldReward := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_GoldReward');
      [*] = ;gIntRegister_GemReward := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_GemReward');
      [*] = ;gIntRegister_TreasureGoldReward := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_TreasureGoldReward');
      [*] = ;gIntRegister_TreasureGemReward := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_TreasureGemReward');
      [*] = ;gIntRegister_HeroLevel := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_HeroLevel');
      [*] = ;gStringRegister_HeroClass := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_HeroClass');
      [*] = ;gIntRegister_BattleEffectValue := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_BattleEffectValue');
      [*] = ;gStringRegister_SpellName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_SpellName');
      [*] = ;gBoolRegister_ShowAdvice := ParserGetBoolValueByKeyByHandle(pParser, 'gBoolRegister_ShowAdvice');
      [*] = ;gBoolRegister_ShowPlayerHint := ParserGetBoolValueByKeyByHandle(pParser, 'gBoolRegister_ShowPlayerHint');
      [*] = ;gStringRegister_AttackerHeroClass := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_AttackerHeroClass');
      [*] = ;gStringRegister_DefenderHeroClass := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_DefenderHeroClass');
      [*] = ;gStringRegister_CampaignQueryID := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_CampaignQueryID');
      [*] = ;gStringRegister_ShardName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_ShardName');
      [*] = ;gStringRegister_RulerTitle := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_RulerTitle');
      [*] = ;gIntRegister_NumYears := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_NumYears');
      [*] = ;gStringRegister_StrYears := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_StrYears');
      [*] = ;gIntRegister_RecordPlace := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_RecordPlace');
      [*] = ;gIntRegister_AstralEnergy := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_AstralEnergy');
      [*] = ;gStringRegister_QuestValue := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_QuestValue');
      [*] = ;gStringRegister_UnitName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_UnitName');
      [*] = ;gIntRegister_UnitCount := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_UnitCount');
      [*] = ;gIntRegister_MoodDummyUID := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_MoodDummyUID');
      [*] = ;gStringRegister_BuildName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_BuildName');
      [*] = ;gStringRegister_TerrainName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_TerrainName');
      [*] = ;gStringRegister_ResourceName := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_ResourceName');
      [*] = ;gIntRegister_GuardianArtifactPercent := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_GuardianArtifactPercent');
      [*] = ;gIntRegister_DiplomacyTurnLeft := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_DiplomacyTurnLeft');
      [*] = ;gIntRegister_QueryPlayerIndex := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_QueryPlayerIndex');
      [*] = ;gIntRegister_QueryPlayerIndex1 := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_QueryPlayerIndex1');
      [*] = ;gIntRegister_VirtualBattleResult := ParserGetIntValueByKeyByHandle(pParser, 'gIntRegister_VirtualBattleResult');
      [*] = ;
      [*] = ;ConvertHeroName(gStringRegister_MyHeroName);
      [*] = ;ConvertHeroName(gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;var provIndex : Integer = StrToInt(gStringRegister_ProvinceName);
      [*] = ;var pProvince : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, provIndex);
      [*] = ;IntRegister0 := pProvince;
      [*] = ;ExecuteState('map.GetProvinceName');
      [*] = ;gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;var plIndex : Integer = StrToInt(gStringRegister_EnemyPlayerName);
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetName');
      [*] = ;gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;plIndex := StrToInt(gStringRegister_EnemyPlayerNameDiplomacy);
      [*] = ;plHandle := GetPlayerHandleByIndex(plIndex);
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetName');
      [*] = ;gStringRegister_EnemyPlayerNameDiplomacy := StringRegister0;
      [*] = ;
      [*] = ;gStringRegister_DefenderEnemyList := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_DefenderEnemyList');
      [*] = ;gStringRegister_GuardEnemyList := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_GuardEnemyList');
      [*] = ;gStringRegister_EnemyHeroArmyList := ParserGetValueByKeyByHandle(pParser, 'gStringRegister_EnemyHeroArmyList');
      [*] = ;
      [*] = ;ConvertUnitIndices(gStringRegister_DefenderEnemyList);
      [*] = ;ConvertUnitIndices(gStringRegister_GuardEnemyList);
      [*] = ;ConvertUnitIndices(gStringRegister_EnemyHeroArmyList);
   struct.end
section.end

