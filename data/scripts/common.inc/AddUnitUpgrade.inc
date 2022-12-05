section.begin
   Name = AddUnitUpgrade
   Description : struct.begin
      [*] = ;IntRegister0 - unit parser
      [*] = ;IntRegister1 - upgrade ID
   struct.end
   Code : struct.begin
      [*] = ;var pUnitParser : Integer = IntRegister0;
      [*] = ;var upgradeID : Integer = IntRegister1;
      [*] = ;
      [*] = ;var pUnitUpgrade : Integer = ParserSelectByHandleByIndex(gPrototypeData.unitupgrades.handle, upgradeID);
      [*] = ;var pUpgUpgrades : Integer = ParserSelectByHandleByKey(pUnitUpgrade, 'Upgrades');
      [*] = ;var pUpgUpgrade0 : Integer = ParserSelectByHandleByIndex(pUpgUpgrades, 0);
      [*] = ;var abilityID : Integer = ParserGetIntValueByKeyByHandle(pUpgUpgrade0, 'AbilityID');
      [*] = ;
      [*] = ;var oldUnitID : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'UnitID');
      [*] = ;var oldLevel : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'Level');
      [*] = ;
      [*] = ;var pMadeUpgrades : Integer = ParserSelectByHandleByKey(pUnitParser, 'Upgrades');
      [*] = ;
      [*] = ;if abilityID = gc_ability_unit_type_change then
      [*] = ;begin
      [*] = ;   var unitID : Integer = ParserGetIntValueByKeyByHandle(pUpgUpgrade0, 'Quantity');
      [*] = ;   var exp : Integer = (ParserGetIntValueByKeyByHandle(pUnitParser, 'Exp') div 2);
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'UnitID', unitID);
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'Exp', exp);
      [*] = ;
      [*] = ;   IntRegister0 := unitID;
      [*] = ;   IntRegister1 := exp;
      [*] = ;   ExecuteState('GetUnitLevelByExp');
      [*] = ;   var level : Integer = IntRegister2;
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'Level', level);
      [*] = ;
      [*] = ;   var i, j : Integer;
      [*] = ;   for i := 0 to oldLevel-level-1 do
      [*] = ;   begin
      [*] = ;      var upgCount : Integer = ParserGetCountByHandle(pMadeUpgrades);
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(pMadeUpgrades, upgCount-1));
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pOldUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, oldUnitID);
      [*] = ;   var pOldStartUpgrades : Integer = ParserSelectByHandleByKey(pOldUnit, 'StartUpgrades');
      [*] = ;   var oldCount : Integer = ParserGetCountByHandle(pOldStartUpgrades);
      [*] = ;   for i := oldCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMadeUpgrade : Integer = ParserSelectByHandleByIndex(pMadeUpgrades, i);
      [*] = ;      ParserFreeByHandle(pMadeUpgrade);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pNewUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;   var pNewStartUpgrades : Integer = ParserSelectByHandleByKey(pNewUnit, 'StartUpgrades');
      [*] = ;   for i := ParserGetCountByHandle(pNewStartUpgrades) downto 0 do
      [*] = ;   begin
      [*] = ;      var pNewStartUpgrade : Integer = ParserSelectByHandleByIndex(pNewStartUpgrades, i);
      [*] = ;      var upgID : Integer = ParserGetIntValueByKeyByHandle(pNewStartUpgrade, 'UpgradeID');
      [*] = ;      if upgID > 0 then
      [*] = ;      begin
      [*] = ;         var pMadeUpgrade : Integer = ParserAddChildByIndex(pMadeUpgrades, '*');
      [*] = ;         for j := ParserGetCountByHandle(pMadeUpgrades)-1 downto 1 do
      [*] = ;         begin
      [*] = ;            var pMadeUpgrade : Integer = ParserSelectByHandleByIndex(pMadeUpgrades, j);
      [*] = ;            var pPrevUpgrade : Integer = ParserSelectByHandleByIndex(pMadeUpgrades, j-1);
      [*] = ;            var id : Integer = ParserGetIntValueByKeyByHandle(pPrevUpgrade, 'UpgradeID');
      [*] = ;            ParserSetIntValueByKeyByHandle(pMadeUpgrade, 'UpgradeID', id);
      [*] = ;         end;
      [*] = ;         pMadeUpgrade := ParserSelectByHandleByIndex(pMadeUpgrades, 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pMadeUpgrade, 'UpgradeID', upgID);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister0 := pUnitParser;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;   ExecuteState('GetUnitPropertyByParser');
      [*] = ;   var oldMaxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;   if pMadeUpgrades = 0 then
      [*] = ;      pMadeUpgrades := ParserAddChildByIndex(pUnitParser, 'Upgrades');
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pMadeUpgrades, '*'), 'UpgradeID', upgradeID);
      [*] = ;
      [*] = ;   IntRegister0 := pUnitParser;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;   ExecuteState('GetUnitPropertyByParser');
      [*] = ;   var newMaxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;   var level : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'Level');
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'Level', level + 1);
      [*] = ;
      [*] = ;   var curLife : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'CurLife');
      [*] = ;   curLife := curLife + newMaxLife - oldMaxLife;
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'CurLife', curLife);
      [*] = ;
      [*] = ;   var fCurLife : Float = ParserGetFloatValueByKeyByHandle(pUnitParser, 'FCurLife');
      [*] = ;   fCurLife := fCurLife + newMaxLife - oldMaxLife;
      [*] = ;   ParserSetFloatValueByKeyByHandle(pUnitParser, 'FCurLife', fCurLife);
      [*] = ;
      [*] = ;   ParserSetFloatValueByKeyByHandle(pUnitParser, 'LifeRatio', curLife / newMaxLife);
      [*] = ;end;
   struct.end
section.end

