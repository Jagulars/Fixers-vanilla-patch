section.begin
   Name = CalcUnitHeroBonus
   Code : struct.begin
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;var pGOParser : Integer = IntRegister1;
      [*] = ;var heroHandle : Integer = IntRegister2;
      [*] = ;var abilityID : Integer = IntRegister3;
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;pGOParser := ParserSelectGameObject(goHandle);
      [*] = ;
      [*] = ;var isHero : Boolean;
      [*] = ;var unitID : Integer;
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   isHero := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bIsHero);
      [*] = ;   unitID := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;   
      [*] = ;   var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetHeroHandle');
      [*] = ;   var batHeroHandle : Integer = IntRegister0;
      [*] = ;   var curLife : Integer = GetGameObjectIntValueIndByHandle(batHeroHandle, gc_stack_unit_iCurLife);
      [*] = ;   if curLife = 0 then
      [*] = ;   heroHandle := 0;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   isHero := ParserGetBoolValueByKeyByHandle(pGOParser, 'IsHero');
      [*] = ;   unitID := ParserGetIntValueByKeyByHandle(pGOParser, 'UnitID');
      [*] = ;end;
      [*] = ;var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;var pGOAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'Abilities');
      [*] = ;var pGOHeroAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'HeroAbilities');
      [*] = ;var pGOSpellAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'SpellAbilities');
      [*] = ;
      [*] = ;var heroParser : Integer = ParserSelectGameObject(heroHandle);
      [*] = ;var pHeroSkills : Integer = ParserSelectByHandleByKey(heroParser, 'Skills');
      [*] = ;
      [*] = ;var heroClass1 : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;var heroClass2 : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iClassInd2);
      [*] = ;var level : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;
      [*] = ;function GetAbilityParserByID(abilityID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   if abilityID < 900 then
      [*] = ;   Result := ParserSelectByHandleByIndex(pGOAbilities, abilityID)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if abilityID < 1000 then
      [*] = ;      Result := ParserSelectByHandleByIndex(pGOHeroAbilities, abilityID - 900)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if abilityID > 2000 then
      [*] = ;         Result := ParserSelectByHandleByIndex(pGOSpellAbilities, abilityID - 2000);
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
      [*] = ;   begin
      [*] = ;      var pGOAbility : Integer = ParserSelectByHandleByIndex(pGOAbilities, i);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOAbility, 'Hero', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOAbility, 'Squad', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOAbility, 'Inventory', 0);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   for i := ParserGetCountByHandle(pGOHeroAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGOHeroAbility : Integer = ParserSelectByHandleByIndex(pGOHeroAbilities, i);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOHeroAbility, 'Hero', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOHeroAbility, 'Squad', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOHeroAbility, 'Inventory', 0);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   for i := ParserGetCountByHandle(pGOSpellAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGOSpellAbility : Integer = ParserSelectByHandleByIndex(pGOSpellAbilities, i);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOSpellAbility, 'Hero', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOSpellAbility, 'Squad', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOSpellAbility, 'Inventory', 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var abilValue : Integer = 0;
      [*] = ;var ammo : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Ammo');
      [*] = ;
      [*] = ;// check hero skills
      [*] = ;// check class talents
      [*] = ;IntRegister0 := heroClass1;
      [*] = ;IntRegister1 := heroClass2;
      [*] = ;ExecuteState('GetExtHeroClassParserByIndices');
      [*] = ;var pHeroClass1 : Integer = IntRegister2;
      [*] = ;var pHeroClass2 : Integer = IntRegister3;
      [*] = ;
      [*] = ;var pClassAbilities : Integer = ParserSelectByHandleByKey(pHeroClass1, 'Abilities');
      [*] = ;for i := ParserGetCountByHandle(pClassAbilities)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pClassAbility : Integer =  ParserSelectByHandleByIndex(pClassAbilities, i);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pClassAbility, 'AbilityID');
      [*] = ;   var power : Integer = ParserGetIntValueByKeyByHandle(pClassAbility, 'Power');
      [*] = ;   var heroOnly : Boolean = ParserGetBoolValueByKeyByHandle(pClassAbility, 'HeroOnly');
      [*] = ;   
      [*] = ;   if (not heroOnly) or isHero then
      [*] = ;   begin
      [*] = ;      if abilityID = 0 then
      [*] = ;      begin
      [*] = ;         var pMyAbility : Integer = GetAbilityParserByID(abilID);
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pMyAbility, 'Hero');
      [*] = ;         value := value + power;
      [*] = ;         ParserSetIntValueByKeyByHandle(pMyAbility, 'Hero', value);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if abilID = abilityID then
      [*] = ;         abilValue := abilValue + power;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if level >= 20 then
      [*] = ;begin
      [*] = ;   pClassAbilities := ParserSelectByHandleByKey(pHeroClass2, 'Abilities');
      [*] = ;   for i := ParserGetCountByHandle(pClassAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pClassAbility : Integer =  ParserSelectByHandleByIndex(pClassAbilities, i);
      [*] = ;      var abilID : Integer = ParserGetIntValueByKeyByHandle(pClassAbility, 'AbilityID');
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pClassAbility, 'Power');
      [*] = ;      var heroOnly : Boolean = ParserGetBoolValueByKeyByHandle(pClassAbility, 'HeroOnly');
      [*] = ;      
      [*] = ;      if (not heroOnly) or isHero then
      [*] = ;      begin
      [*] = ;         if abilityID = 0 then
      [*] = ;         begin
      [*] = ;            var pMyAbility : Integer = GetAbilityParserByID(abilID);
      [*] = ;            var value : Integer = ParserGetIntValueByKeyByHandle(pMyAbility, 'Hero');
      [*] = ;            value := value + power;
      [*] = ;            ParserSetIntValueByKeyByHandle(pMyAbility, 'Hero', value);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if abilID = abilityID then
      [*] = ;            abilValue := abilValue + power;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pHeroSkills)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pHeroSkill : Integer = ParserSelectByHandleByIndex(pHeroSkills, i);
      [*] = ;   var skillID : Integer = ParserGetIntValueByKeyByHandle(pHeroSkill, 'SkillID');
      [*] = ;   var skillLevel : Integer = ParserGetIntValueByKeyByHandle(pHeroSkill, 'Level');
      [*] = ;   
      [*] = ;   var pSkill : Integer = ParserSelectByHandleByIndex(gPrototypeData.skills.handle, skillID);
      [*] = ;   var pSquadUpgrades : Integer = ParserSelectByHandleByKey(pSkill, 'SquadUpgrades');
      [*] = ;   var pHeroUpgrades : Integer = ParserSelectByHandleByKey(pSkill, 'HeroUpgrades');
      [*] = ;   
      [*] = ;   for j := 0 to skillLevel-1 do
      [*] = ;   begin
      [*] = ;      var pSkillLevel : Integer = ParserSelectByHandleByIndex(pSquadUpgrades, j);
      [*] = ;      var pUpgradeList : Integer = ParserSelectByHandleByKey(pSkillLevel, 'UpgradeList');
      [*] = ;      
      [*] = ;      for k := ParserGetCountByHandle(pUpgradeList)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pUpgrade : Integer = ParserSelectByHandleByIndex(pUpgradeList, k);
      [*] = ;         var id : Integer = ParserGetIntValueByKeyByHandle(pUpgrade, 'AbilityID');
      [*] = ;         var power : Integer = ParserGetIntValueByKeyByHandle(pUpgrade, 'Power');
      [*] = ;         
      [*] = ;         if (abilityID > 0) and (id <> abilityID) then
      [*] = ;         continue;
      [*] = ;         
      [*] = ;         var addBonus : Boolean = true;
      [*] = ;         
      [*] = ;         if id = 10 then
      [*] = ;         begin
      [*] = ;            var abil24 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, 24);
      [*] = ;            var abil28 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, 28);
      [*] = ;            addBonus := (ammo > 1) and (abil24 = 0) and (abil28 = 0);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if id = 12 then
      [*] = ;         begin
      [*] = ;            var abil19 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, 19);
      [*] = ;            addBonus := (abil19 = 0);
      [*] = ;         end;
      [*] = ;         
      [*] = ;         if addBonus then
      [*] = ;         begin
      [*] = ;            if abilityID = 0 then
      [*] = ;            begin
      [*] = ;               var pMyAbility : Integer = GetAbilityParserByID(id);
      [*] = ;               var value : Integer = ParserGetIntValueByKeyByHandle(pMyAbility, 'Squad');
      [*] = ;               value := value + power;
      [*] = ;               ParserSetIntValueByKeyByHandle(pMyAbility, 'Squad', value);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if id = abilityID then
      [*] = ;               abilValue := abilValue + power;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if isHero then
      [*] = ;      begin
      [*] = ;         var pSkillLevel : Integer = ParserSelectByHandleByIndex(pHeroUpgrades, j);
      [*] = ;         var pUpgradeList : Integer = ParserSelectByHandleByKey(pSkillLevel, 'UpgradeList');
      [*] = ;         
      [*] = ;         for k := ParserGetCountByHandle(pUpgradeList)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pUpgrade : Integer = ParserSelectByHandleByIndex(pUpgradeList, k);
      [*] = ;            var id : Integer = ParserGetIntValueByKeyByHandle(pUpgrade, 'AbilityID');
      [*] = ;            var power : Integer = ParserGetIntValueByKeyByHandle(pUpgrade, 'Power');
      [*] = ;            
      [*] = ;            if abilityID = 0 then
      [*] = ;            begin
      [*] = ;               var pMyAbility : Integer = GetAbilityParserByID(id);
      [*] = ;               var value : Integer = ParserGetIntValueByKeyByHandle(pMyAbility, 'Hero');
      [*] = ;               value := value + power;
      [*] = ;               ParserSetIntValueByKeyByHandle(pMyAbility, 'Hero', value);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if id = abilityID then
      [*] = ;               abilValue := abilValue + power;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := goHandle;
      [*] = ;IntRegister1 := pGOParser;
      [*] = ;IntRegister2 := heroHandle;
      [*] = ;IntRegister3 := abilityID;
      [*] = ;ExecuteState('CalcUnitInvAbility');
      [*] = ;if abilityID > 0 then
      [*] = ;abilValue := abilValue + IntRegister4;
      [*] = ;
      [*] = ;IntRegister4 := abilValue;
   struct.end
section.end

