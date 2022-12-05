section.begin
   Name = AddUnitToParser
   Description : struct.begin
      [*] = ;IntRegister0 - parser handle
      [*] = ;IntRegister1 - unit ID
      [*] = ;IntRegister2 - unit experience
      [*] = ;IntRegister3 - hero UID
      [*] = ;OUT: IntRegister4 - unit parser
   struct.end
   Code : struct.begin
      [*] = ;var parser : Integer = IntRegister0;
      [*] = ;var unitID : Integer = IntRegister1;
      [*] = ;var unitExp : Integer = IntRegister2;
      [*] = ;var heroUID : Integer = IntRegister3;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;var name : String = ParserGetValueByKeyByHandle(pUnit, 'Name');
      [*] = ;
      [*] = ;IntRegister0 := parser;
      [*] = ;ExecuteState('GetFreePosInArmy');
      [*] = ;var battleX : Integer = IntRegister1;
      [*] = ;var battleY : Integer = IntRegister2;
      [*] = ;
      [*] = ;var pParserUnit : Integer = ParserAddChildByIndex(parser, '*');
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'UnitID', unitID);
      [*] = ;ParserSetValueByKeyByHandle(pParserUnit, 'Name', name);
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'BattleX', battleX);
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'BattleY', battleY);
      [*] = ;
      [*] = ;IntRegister0 := unitID;
      [*] = ;IntRegister1 := unitExp;
      [*] = ;ExecuteState('GetUnitLevelByExp');
      [*] = ;var level : Integer = IntRegister2;
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'Level', 0);
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'Exp', unitExp);
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'HeroUID', heroUID);
      [*] = ;if heroUID <> 0 then
      [*] = ;   ParserSetBoolValueByKeyByHandle(pParserUnit, 'IsHero', true);
      [*] = ;
      [*] = ;ParserAddChildByIndex(pParserUnit, 'Upgrades');
      [*] = ;ParserAddChildByIndex(pParserUnit, 'Medals');
      [*] = ;ParserAddChildByIndex(pParserUnit, 'Skills');
      [*] = ;
      [*] = ;IntRegister0 := pParserUnit;
      [*] = ;ExecuteState('MakeUnitStartUpgrades');
      [*] = ;
      [*] = ;for i := 1 to level do
      [*] = ;begin
      [*] = ;   IntRegister0 := pParserUnit;
      [*] = ;   ExecuteState('UnitLevelUpByParser');
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := pParserUnit;
      [*] = ;IntRegister1 := parser;
      [*] = ;IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;ExecuteState('GetUnitPropertyByParser');
      [*] = ;var curLife : Integer = IntRegister3;
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'CurLife', curLife);
      [*] = ;ParserSetFloatValueByKeyByHandle(pParserUnit, 'FCurLife', curLife);
      [*] = ;ParserSetFloatValueByKeyByHandle(pParserUnit, 'LifeRatio', 1);
      [*] = ;
      [*] = ;IntRegister0 := pParserUnit;
      [*] = ;IntRegister1 := parser;
      [*] = ;IntRegister2 := gc_battle_unit_iMaxMoral;
      [*] = ;ExecuteState('GetUnitPropertyByParser');
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'CurMoral', IntRegister3);
      [*] = ;ParserSetIntValueByKeyByHandle(pParserUnit, 'MoralMod', 0);
      [*] = ;
      [*] = ;IntRegister4 := pParserUnit;
   struct.end
section.end

