section.begin
   Name = map.SetQueryRegisters
   Code : struct.begin
      [*] = ;var myPlHandle : Integer;
      [*] = ;var myHeroHandle : Integer;
      [*] = ;var myArmyHandle : Integer;
      [*] = ;var enPlHandle : Integer;
      [*] = ;var enHeroHandle : Integer;
      [*] = ;var enArmyHandle : Integer;
      [*] = ;
      [*] = ;var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;
      [*] = ;if GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer) = gIntRegister_MapMyPlayerIndex then
      [*] = ;begin
      [*] = ;   myPlHandle := gIntRegister_BattleAttackPlayer;
      [*] = ;   myHeroHandle := gIntRegister_BattleAttackHeroHandle;
      [*] = ;   myArmyHandle := gIntRegister_BattleAttackArmy;
      [*] = ;   enPlHandle := gIntRegister_BattleDefendPlayer;
      [*] = ;   enHeroHandle := gIntRegister_BattleDefendHeroHandle;
      [*] = ;   enArmyHandle := gIntRegister_BattleDefendArmy;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   myPlHandle := gIntRegister_BattleDefendPlayer;
      [*] = ;   myHeroHandle := gIntRegister_BattleDefendHeroHandle;
      [*] = ;   myArmyHandle := gIntRegister_BattleDefendArmy;
      [*] = ;   enPlHandle := gIntRegister_BattleAttackPlayer;
      [*] = ;   enHeroHandle := gIntRegister_BattleAttackHeroHandle;
      [*] = ;   enArmyHandle := gIntRegister_BattleAttackArmy;
      [*] = ;end;
      [*] = ;
      [*] = ;var pMyHeroParser : Integer = ParserSelectGameObject(myHeroHandle);
      [*] = ;var pEnHeroParser : Integer = ParserSelectGameObject(enHeroHandle);
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(enPlHandle, 'GetName');
      [*] = ;gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;_hero_GetName(myHeroHandle, gStringRegister_MyHeroName);
      [*] = ;_hero_GetName(enHeroHandle, gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;var pEnUnits : Integer = ParserSelectByHandleByKey(enArmyHandle, 'Units');
      [*] = ;
      [*] = ;IntRegister0 := pEnUnits;
      [*] = ;ExecuteState('map.GetArmyUnitsCount');
      [*] = ;var enArmyCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := pEnUnits;
      [*] = ;ExecuteState('map.GetArmyUnitsList');
      [*] = ;var enArmyList : String = StringRegister0;
      [*] = ;
      [*] = ;if enHeroHandle <> 0 then
      [*] = ;begin
      [*] = ;   gIntRegister_EnemyHeroArmyCount := enArmyCount;
      [*] = ;   gStringRegister_EnemyHeroArmyList := enArmyList;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if enArmyHandle = ParserSelectByHandleByKey(pProvince, 'Guard') then
      [*] = ;   begin
      [*] = ;      gIntRegister_GuardEnemyCount := enArmyCount;
      [*] = ;      gStringRegister_GuardEnemyList := enArmyList;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gIntRegister_DefenderEnemyCount := enArmyCount;
      [*] = ;      gStringRegister_DefenderEnemyList := enArmyList;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

