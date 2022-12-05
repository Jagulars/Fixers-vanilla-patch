section.begin
   Name = map.SaveQueryRegisters
   Description[*] = ;IntRegister0 - parser
   Code : struct.begin
      [*] = ;var pParser : Integer = IntRegister0;
      [*] = ;
      [*] = ;procedure ConvertUnitNames(var nameList : String);
      [*] = ;begin
      [*] = ;   var oldNameList : String = nameList;
      [*] = ;   nameList := '';
      [*] = ;   while StrLength(oldNameList) > 0 do
      [*] = ;   begin
      [*] = ;      var name : String = '';
      [*] = ;      if StrPos(',', oldNameList) > 0 then //if there is a comma in the string
      [*] = ;      begin
      [*] = ;         var pos : Integer = StrPos(',', oldNameList); //get the position of the first comma in the string
      [*] = ;         var len : Integer = StrLength(oldNameList); 
      [*] = ;         name := SubStr(oldNameList, 0, pos-1); // get the string before the comma (pos)
      [*] = ;         oldNameList := SubStr(oldNameList, pos+2, len-pos-1);  // get the string starting after the comma and whitespace (pos + 2 = start point of extraction; len-pos-1 = length of extraction)
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         name := oldNameList;
      [*] = ;         oldNameList := '';
      [*] = ;      end;
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      for i := 1 to gPrototypeData.units.number-1 do
      [*] = ;      begin
      [*] = ;         var tmpName : String = GetLocaleTableListItemByID('unit', IntToStr(i));
      [*] = ;         if SameText(name, tmpName) then
      [*] = ;         begin
      [*] = ;            if nameList <> '' then
      [*] = ;            nameList := nameList + ', ';
      [*] = ;            nameList := nameList + IntToStr(i);
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_DefenderEnemyCount', gIntRegister_DefenderEnemyCount);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_GuardEnemyCount', gIntRegister_GuardEnemyCount);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_TurnsOnHeroRevive', gIntRegister_TurnsOnHeroRevive);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_GoldCost', gIntRegister_GoldCost);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_GemCost', gIntRegister_GemCost);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_EnemyHeroArmyCount', gIntRegister_EnemyHeroArmyCount);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_SiegeTurnsLeft', gIntRegister_SiegeTurnsLeft);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_EffectValue', gIntRegister_EffectValue);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_SiteName', gStringRegister_SiteName);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_ExploreValue', gIntRegister_ExploreValue);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_AbilityPower', gIntRegister_AbilityPower);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_GoldReward', gIntRegister_GoldReward);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_GemReward', gIntRegister_GemReward);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_TreasureGoldReward', gIntRegister_TreasureGoldReward);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_TreasureGemReward', gIntRegister_TreasureGemReward);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_HeroLevel', gIntRegister_HeroLevel);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_HeroClass', gStringRegister_HeroClass);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_BattleEffectValue', gIntRegister_BattleEffectValue);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_SpellName', gStringRegister_SpellName);
      [*] = ;ParserSetBoolValueByKeyByHandle(pParser, 'gBoolRegister_ShowAdvice', gBoolRegister_ShowAdvice);
      [*] = ;ParserSetBoolValueByKeyByHandle(pParser, 'gBoolRegister_ShowPlayerHint', gBoolRegister_ShowPlayerHint);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_AttackerHeroClass', gStringRegister_AttackerHeroClass);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_DefenderHeroClass', gStringRegister_DefenderHeroClass);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_CampaignQueryID', gStringRegister_CampaignQueryID);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_ShardName', gStringRegister_ShardName);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_RulerTitle', gStringRegister_RulerTitle);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_NumYears', gIntRegister_NumYears);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_StrYears', gStringRegister_StrYears);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_RecordPlace', gIntRegister_RecordPlace);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_AstralEnergy', gIntRegister_AstralEnergy);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_QuestValue', gStringRegister_QuestValue);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_UnitName', gStringRegister_UnitName);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_UnitCount', gIntRegister_UnitCount);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_MoodDummyUID', gIntRegister_MoodDummyUID);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_BuildName', gStringRegister_BuildName);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_TerrainName', gStringRegister_TerrainName);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_ResourceName', gStringRegister_ResourceName);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_GuardianArtifactPercent', gIntRegister_GuardianArtifactPercent);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_DiplomacyTurnLeft', gIntRegister_DiplomacyTurnLeft);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_QueryPlayerIndex', gIntRegister_QueryPlayerIndex);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_QueryPlayerIndex1', gIntRegister_QueryPlayerIndex1);
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'gIntRegister_VirtualBattleResult', gIntRegister_VirtualBattleResult);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;      var params : String = '';
      [*] = ;      _sa_AddAsInt(params, i);
      [*] = ;      _sa_AddAsInt(params, j);
      [*] = ;
      [*] = ;      var name : String;
      [*] = ;      _hero_GetName(goHandle, name);
      [*] = ;      if SameText(name, gStringRegister_MyHeroName) then
      [*] = ;      ParserSetValueByKeyByHandle(pParser, 'gStringRegister_MyHeroName', params);
      [*] = ;
      [*] = ;      if SameText(name, gStringRegister_EnemyHeroName) then
      [*] = ;      ParserSetValueByKeyByHandle(pParser, 'gStringRegister_EnemyHeroName', params);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to gStratHexCells.number-1 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, i);
      [*] = ;   IntRegister0 := pProvince;
      [*] = ;   ExecuteState('map.GetProvinceName');
      [*] = ;   var provName : String = StringRegister0;
      [*] = ;
      [*] = ;   if SameText(provName, gStringRegister_ProvinceName) then
      [*] = ;   begin
      [*] = ;      var value : String = IntToStr(i);
      [*] = ;      ParserSetValueByKeyByHandle(pParser, 'gStringRegister_ProvinceName', value);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetName');
      [*] = ;   var plName : String = StringRegister0;
      [*] = ;   var value : String = IntToStr(i);
      [*] = ;
      [*] = ;   if SameText(plName, gStringRegister_EnemyPlayerName) then
      [*] = ;   ParserSetValueByKeyByHandle(pParser, 'gStringRegister_EnemyPlayerName', value);
      [*] = ;
      [*] = ;   if SameText(plName, gStringRegister_EnemyPlayerNameDiplomacy) then
      [*] = ;   ParserSetValueByKeyByHandle(pParser, 'gStringRegister_EnemyPlayerNameDiplomacy', value);
      [*] = ;end;
      [*] = ;
      [*] = ;ConvertUnitNames(gStringRegister_DefenderEnemyList);
      [*] = ;ConvertUnitNames(gStringRegister_GuardEnemyList);
      [*] = ;ConvertUnitNames(gStringRegister_EnemyHeroArmyList);
      [*] = ;
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_DefenderEnemyList', gStringRegister_DefenderEnemyList);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_GuardEnemyList', gStringRegister_GuardEnemyList);
      [*] = ;ParserSetValueByKeyByHandle(pParser, 'gStringRegister_EnemyHeroArmyList', gStringRegister_EnemyHeroArmyList);
   struct.end
section.end

