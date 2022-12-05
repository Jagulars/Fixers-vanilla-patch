section.begin
   Name = CalcUnitAbility
   Code : struct.begin
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;var pGOParser : Integer = IntRegister1;
      [*] = ;var heroHandle : Integer = IntRegister2;
      [*] = ;var abilityID : Integer = IntRegister3;
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;   pGOParser := ParserSelectGameObject(goHandle);
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;var pGOUpgrades : Integer = ParserSelectByHandleByKey(pGOParser, 'Upgrades');
      [*] = ;if (pGOUpgrades=0) then
      [*] = ;   pGOUpgrades := ParserSelectByHandleByKey(pGOParser, 'StartUpgrades');
      [*] = ;var pGOMedals : Integer = ParserSelectByHandleByKey(pGOParser, 'Medals');
      [*] = ;var pGOAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'Abilities');
      [*] = ;var pGOHeroAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'HeroAbilities');
      [*] = ;var pGOSpellAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'SpellAbilities');
      [*] = ;
      [*] = ;var unitID : Integer;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   unitID := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;
      [*] = ;   var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;   {PlayerExecuteStateByHandle(plHandle, 'GetHeroHandle');
      [*] = ;   var batHeroHandle : Integer = IntRegister0;}
      [*] = ;   var batHeroHandle : Integer = _unit_GetHeroHandle(plHandle);
      [*] = ;   var curLife : Integer = GetGameObjectIntValueIndByHandle(batHeroHandle, gc_stack_unit_iCurLife);
      [*] = ;   if curLife = 0 then
      [*] = ;      heroHandle := 0;
      [*] = ;end
      [*] = ;else
      [*] = ;   unitID := ParserGetIntValueByKeyByHandle(pGOParser, 'UnitID');
      [*] = ;
      [*] = ;var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;function GetAbilityParserByID(abilityID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   if abilityID < 900 then
      [*] = ;      Result := ParserSelectByHandleByIndex(pGOAbilities, abilityID)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if abilityID < 1000 then
      [*] = ;         Result := ParserSelectByHandleByIndex(pGOHeroAbilities, abilityID - 900)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if abilityID > 2000 then
      [*] = ;            Result := ParserSelectByHandleByIndex(pGOSpellAbilities, abilityID - 2000);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckUnitAbility(cGOHandle, cGOParser, cHeroHandle, cAbilityID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := cGOHandle;
      [*] = ;   IntRegister1 := cGOParser;
      [*] = ;   IntRegister2 := cHeroHandle;
      [*] = ;   IntRegister3 := cAbilityID;
      [*] = ;   ExecuteState('CheckUnitAbility');
      [*] = ;   Result := IntRegister4;
      [*] = ;end;
      [*] = ;
      [*] = ;if abilityID = 0 then
      [*] = ;begin
      [*] = ;   for i := ParserGetCountByHandle(pGOAbilities)-1 downto 0 do
      [*] = ;      ParserSetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGOAbilities, i), 'Value', 0);
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pGOHeroAbilities)-1 downto 0 do
      [*] = ;      ParserSetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGOHeroAbilities, i), 'Value', 0);
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pGOSpellAbilities)-1 downto 0 do
      [*] = ;      ParserSetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGOSpellAbilities, i), 'Value', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;var abilValue : Integer = 0;
      [*] = ;
      [*] = ;// check in upgrades
      [*] = ;for [MAIN]i := ParserGetCountByHandle(pGOUpgrades)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pGOUpgrade : Integer = ParserSelectByHandleByIndex(pGOUpgrades, i);
      [*] = ;   var upgradeID : Integer = ParserGetIntValueByKeyByHandle(pGOUpgrade, 'UpgradeID');
      [*] = ;   
      [*] = ;   var pUpgrade : Integer = _unit_GetUpgradeParserByID(upgradeID);
      [*] = ;
      [*] = ;   var pUpgAbilities : Integer = ParserSelectByHandleByKey(pUpgrade, 'Upgrades');
      [*] = ;   for j := ParserGetCountByHandle(pUpgAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pUpgAbility : Integer = ParserSelectByHandleByIndex(pUpgAbilities, j);
      [*] = ;      var id : Integer = ParserGetIntValueByKeyByHandle(pUpgAbility, 'AbilityID');
      [*] = ;      var quantity : Integer = ParserGetIntValueByKeyByHandle(pUpgAbility, 'Quantity');
      [*] = ;
      [*] = ;      if (abilityID = 0) then
      [*] = ;      begin
      [*] = ;         var pGOAbility : Integer = GetAbilityParserByID(id);
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pGOAbility, 'Value');
      [*] = ;         value := value + quantity;
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOAbility, 'Value', value);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if id = abilityID then
      [*] = ;            abilValue := abilValue + quantity;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// check in medals
      [*] = ;for [MAIN]i := ParserGetCountByHandle(pGOMedals)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pGOMedal : Integer = ParserSelectByHandleByIndex(pGOMedals, i);
      [*] = ;   var medalID : Integer = ParserGetIntValueByKeyByHandle(pGOMedal, 'MedalID');
      [*] = ;
      [*] = ;   IntRegister0 := medalID;
      [*] = ;   ExecuteState('GetMedalParserByID');
      [*] = ;   var pMedal : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var pMedalAbilities : Integer = ParserSelectByHandleByKey(pMedal, 'Upgrades');
      [*] = ;   for j := ParserGetCountByHandle(pMedalAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMedalAbility : Integer = ParserSelectByHandleByIndex(pMedalAbilities, j);
      [*] = ;      var id : Integer = ParserGetIntValueByKeyByHandle(pMedalAbility, 'AbilityID');
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pMedalAbility, 'Power');
      [*] = ;
      [*] = ;      if abilityID = 0 then
      [*] = ;      begin
      [*] = ;         var pMyAbility : Integer = GetAbilityParserByID(id);
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pMyAbility, 'Value');
      [*] = ;         value := value + power;
      [*] = ;         ParserSetIntValueByKeyByHandle(pMyAbility, 'Value', value);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if id = abilityID then
      [*] = ;            abilValue := abilValue + power;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := goHandle;
      [*] = ;IntRegister1 := pGOParser;
      [*] = ;IntRegister2 := heroHandle;
      [*] = ;IntRegister3 := abilityID;
      [*] = ;ExecuteState('CalcUnitHeroBonus');
      [*] = ;if abilityID > 0 then
      [*] = ;   abilValue := abilValue + IntRegister4;
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   var pGOAbility : Integer = ParserSelectByHandleByIndex(pGOAbilities, gc_ability_parry);
      [*] = ;   if ParserGetIntValueByKeyByHandle(pGOAbility, 'Value') > 0 then
      [*] = ;      SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bParry, true);
      [*] = ;
      [*] = ;   //IntRegister0 := 97;
      [*] = ;   //GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;   //if IntRegister1 > 0 then
      [*] = ;   if (_unit_CheckAbility(goHandle, gc_ability_reincarnated)>0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_spell_reincarnation;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetEffectParserBySpellID');
      [*] = ;      if IntRegister1 = 0 then
      [*] = ;      begin
      [*] = ;         var pGOEffect : Integer = _unit_AddEffect(goHandle, gc_ability_reincarnation, 1, 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentSpellID', gc_spell_reincarnation);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister4 := abilValue;
   struct.end
section.end

