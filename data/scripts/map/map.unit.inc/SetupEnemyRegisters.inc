section.begin
   Name = SetupEnemyRegisters
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;_hero_GetName(myGOHandle, gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetName');
      [*] = ;gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;var pMyUnits : Integer = ParserSelectByHandleByKey(pMyParser, 'Units');
      [*] = ;IntRegister0 := pMyUnits;
      [*] = ;MapExecuteState('map.GetArmyUnitsCount');
      [*] = ;gIntRegister_EnemyHeroArmyCount := IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := pMyUnits;
      [*] = ;MapExecuteState('map.GetArmyUnitsList');
      [*] = ;gStringRegister_EnemyHeroArmyList := StringRegister0;
      [*] = ;
      [*] = ;var tUID : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;var pProvince : Integer = _misc_GetProvinceParserByUID(tUID);
      [*] = ;IntRegister0 := pProvince;
      [*] = ;MapExecuteState('map.GetProvinceName');
      [*] = ;gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

