section.begin
   Name = CalcUnitInvAbility
   Description : struct.begin
      [*] = ;IntRegister0 - game object handle
      [*] = ;IntRegister1 - game object parser
      [*] = ;IntRegister2 - ability ID
      [*] = ;OUT: IntRegister3 - ability value
   struct.end
   Code : struct.begin
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;var pGOParser : Integer = IntRegister1;
      [*] = ;var heroHandle : Integer = IntRegister2;
      [*] = ;var abilityID : Integer = IntRegister3;
      [*] = ;
      [*] = ;var plHandle : Integer = GetGameObjectPlayerHandleByHandle(heroHandle);
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
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;var pGOAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'Abilities');
      [*] = ;var pGOHeroAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'HeroAbilities');
      [*] = ;var pGOSpellAbilities : Integer = ParserSelectByHandleByKey(pGOParser, 'SpellAbilities');
      [*] = ;
      [*] = ;var heroParser : Integer = ParserSelectGameObject(heroHandle);
      [*] = ;var pHeroInventory : Integer = ParserSelectByHandleByKey(heroParser, 'Doll');
      [*] = ;
      [*] = ;var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;var pItems : Integer = gPrototypeData.items.handle;
      [*] = ;
      [*] = ;function CheckHeroItem(goHnd, cItemID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   var pGOParser : Integer = ParserSelectGameObject(goHnd);
      [*] = ;   var pGODoll : Integer = ParserSelectByHandleByKey(pGOParser, 'Doll');
      [*] = ;
      [*] = ;   for i:=0 to gc_HeroDollSlotsCount-1 do
      [*] = ;   begin
      [*] = ;      var pHeroItem : Integer = ParserSelectByHandleByIndex(pGODoll, i);
      [*] = ;      var id : Integer = ParserGetIntValueByKeyByHandle(pHeroItem, 'ItemID');
      [*] = ;      var dur : Integer = ParserGetIntValueByKeyByHandle(pHeroItem, 'Durability');
      [*] = ;      var picked : Boolean = ParserGetBoolValueByKeyByHandle(pHeroItem, 'Picked');
      [*] = ;
      [*] = ;      if (not picked) and (id = cItemID) and (dur <> 0) then
      [*] = ;      begin
      [*] = ;         Result := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetAbilityParserByID(cAbilityID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   if cAbilityID < 900 then
      [*] = ;   Result := ParserSelectByHandleByIndex(pGOAbilities, cAbilityID)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if cAbilityID < 1000 then
      [*] = ;      Result := ParserSelectByHandleByIndex(pGOHeroAbilities, cAbilityID - 900)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if cAbilityID > 2000 then
      [*] = ;         Result := ParserSelectByHandleByIndex(pGOSpellAbilities, cAbilityID - 2000);
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
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOAbility, 'Inventory', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pGOHeroAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGOHeroAbility : Integer = ParserSelectByHandleByIndex(pGOHeroAbilities, i);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOHeroAbility, 'Inventory', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pGOSpellAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGOSpellAbility : Integer = ParserSelectByHandleByIndex(pGOSpellAbilities, i);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOSpellAbility, 'Inventory', 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var abilValue : Integer = 0;
      [*] = ;var ammo : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Ammo');
      [*] = ;
      [*] = ;//ArrayClear;
      [*] = ;
      [*] = ;for i := 0 to gc_HeroDollSlotsCount-1 do
      [*] = ;begin
      [*] = ;   var pHeroItem : Integer = ParserSelectByHandleByIndex(pHeroInventory, i);
      [*] = ;   var itemID : Integer = ParserGetIntValueByKeyByHandle(pHeroItem, 'ItemID');
      [*] = ;   var itemDur : Integer = ParserGetIntValueByKeyByHandle(pHeroItem, 'Durability');
      [*] = ;   var picked : Boolean = ParserGetBoolValueByKeyByHandle(pHeroItem, 'Picked');
      [*] = ;
      [*] = ;   if (itemID > 0) and (itemDur <> 0) and (not picked) then
      [*] = ;   begin
      [*] = ;      var pItem : Integer = ParserSelectByHandleByIndex(pItems, itemID);
      [*] = ;      var pItemAbilities : Integer = ParserSelectByHandleByKey(pItem, 'Abilities');
      [*] = ;
      [*] = ;      for j := ParserGetCountByHandle(pItemAbilities)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pItemAbility : Integer = ParserSelectByHandleByIndex(pItemAbilities, j);
      [*] = ;         var abilID : Integer = ParserGetIntValueByKeyByHandle(pItemAbility, 'AbilityID');
      [*] = ;         var heroOnly : Boolean = ParserGetBoolValueByKeyByHandle(pItemAbility, 'HeroOnly');
      [*] = ;
      [*] = ;         if ((abilityID = 0) or (abilityID = abilID)) and (isHero or (not heroOnly)) then
      [*] = ;         begin
      [*] = ;            var addBonus : Boolean = true;
      [*] = ;            if (abilID = gc_ability_shoot_range) or (abilID = gc_ability_ammo) then // melee weapon (healing staff) should grant range/ammo only when there is no functional ranged weapon.
      [*] = ;            begin
      [*] = ;               if ParserGetIntValueByKeyByHandle(pHeroItem, 'ItemSlot') = 1 then // melee weapon slot
      [*] = ;               begin
      [*] = ;                  IntRegister0 := 12; // ranged weapon slot
      [*] = ;                  GameObjectExecuteStateByHandle(heroHandle, 'GetSlotIndexByItemSlot');
      [*] = ;                  if IntRegister1 >= 0 then
      [*] = ;                  begin
      [*] = ;                     var pRangedSlot : Integer = ParserSelectByHandleByIndex(pHeroInventory, IntRegister1);
      [*] = ;                     var itemID : Integer = ParserGetIntValueByKeyByHandle(pRangedSlot, 'ItemID');
      [*] = ;                     var itemDur : Integer = ParserGetIntValueByKeyByHandle(pRangedSlot, 'Durability');
      [*] = ;                     if (itemID > 0) and (itemDur > 0) then
      [*] = ;                        continue;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if abilID = gc_ability_ammo then
      [*] = ;            begin
      [*] = ;               var abil24 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, gc_ability_healing);
      [*] = ;               var abil28 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, gc_ability_magic_shot);
      [*] = ;               addBonus := (ammo > 1) and (abil24 = 0) and (abil28 = 0)
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if abilID = gc_ability_morale then
      [*] = ;            begin
      [*] = ;               var abil19 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, gc_ability_fearless);
      [*] = ;               addBonus := (abil19 = 0);
      [*] = ;            end;
      [*] = ;
      [*] = ;            addBonus := addBonus or isHero;
      [*] = ;
      [*] = ;            if addBonus then
      [*] = ;            begin
      [*] = ;               var power : Integer = ParserGetIntValueByKeyByHandle(pItemAbility, 'Power');
      [*] = ;               if abilityID = 0 then
      [*] = ;               begin
      [*] = ;                  var pGOAbility : Integer = GetAbilityParserByID(abilID);
      [*] = ;                  var value : Integer = ParserGetIntValueByKeyByHandle(pGOAbility, 'Inventory');
      [*] = ;                  value := value + power;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pGOAbility, 'Inventory', value);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               abilValue := abilValue + power;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // check hero inventory sets
      [*] = ;      var itemSetID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemSetID');
      [*] = ;      var exist : Boolean = False;
      [*] = ;      if (itemSetID>0) then
      [*] = ;      begin
      [*] = ;         for j:=0 to i-1 do
      [*] = ;         begin
      [*] = ;            var pTmpHeroItem : Integer = ParserSelectByHandleByIndex(pHeroInventory, j);
      [*] = ;            var tmpItemID : Integer = ParserGetIntValueByKeyByHandle(pTmpHeroItem, 'ItemID');
      [*] = ;            var tmpItemDur : Integer = ParserGetIntValueByKeyByHandle(pTmpHeroItem, 'Durability');
      [*] = ;            var tmpPicked : Boolean = ParserGetBoolValueByKeyByHandle(pTmpHeroItem, 'Picked');
      [*] = ;
      [*] = ;            if (tmpItemID > 0) and (tmpItemDur <> 0) and (not tmpPicked) then
      [*] = ;            begin
      [*] = ;               var pTmpItem : Integer = ParserSelectByHandleByIndex(pItems, tmpItemID);
      [*] = ;               var tmpItemSetID : Integer = ParserGetIntValueByKeyByHandle(pTmpItem, 'ItemSetID');
      [*] = ;               if (itemSetID=tmpItemSetID) then
      [*] = ;               exist := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (itemSetID > 0) and (not exist){(ArrayGetIndexByValue(itemSetID) = -1)} then
      [*] = ;      begin
      [*] = ;         //ArrayPushValue(itemSetID);
      [*] = ;         var pItemSet : Integer = ParserSelectByHandleByIndex(gPrototypeData.itemsets.handle, itemSetID);
      [*] = ;         var pSetItems : Integer = ParserSelectByHandleByKey(pItemSet, 'Items');
      [*] = ;
      [*] = ;         var setCount : Integer = 0;
      [*] = ;         for j := ParserGetCountByHandle(pSetItems)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSetItem : Integer = ParserSelectByHandleByIndex(pSetItems, j);
      [*] = ;            var id : Integer = ParserGetIntValueByKeyByHandle(pSetItem, 'ItemID');
      [*] = ;
      [*] = ;            if (heroHandle<>0) then
      [*] = ;            begin
      [*] = ;               if CheckHeroItem(heroHandle, id) then
      [*] = ;               setCount := setCount + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if setCount > 0 then
      [*] = ;         begin
      [*] = ;            if (setCount >= 4) and (plHandle <> 0) then
      [*] = ;            SetPlayerBoolValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_bSet, True);
      [*] = ;
      [*] = ;            var pSetBonuses : Integer = ParserSelectByHandleByKey(pItemSet, 'Bonuses');
      [*] = ;            for j := ParserGetCountByHandle(pSetBonuses)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pSetBonus : Integer = ParserSelectByHandleByIndex(pSetBonuses, j);
      [*] = ;               var count : Integer = ParserGetIntValueByKeyByHandle(pSetBonus, 'ItemsCount');
      [*] = ;
      [*] = ;               if setCount >= count then
      [*] = ;               begin
      [*] = ;                  var pBonusList : Integer = ParserSelectByHandleByKey(pSetBonus, 'BonusList');
      [*] = ;                  for k := ParserGetCountByHandle(pBonusList)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var pBonusItem : Integer = ParserSelectByHandleByIndex(pBonusList, k);
      [*] = ;                     var abilID : Integer = ParserGetIntValueByKeyByHandle(pBonusItem, 'AbilityID');
      [*] = ;                     var heroOnly : Boolean = ParserGetBoolValueByKeyByHandle(pBonusItem, 'HeroOnly');
      [*] = ;
      [*] = ;                     if ((abilityID = 0) or (abilityID = abilID)) and (isHero or (not heroOnly)) then
      [*] = ;                     begin
      [*] = ;                        var addBonus : Boolean = true;
      [*] = ;                        if abilID = gc_ability_ammo then
      [*] = ;                        begin
      [*] = ;                           var abil24 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, gc_ability_healing);
      [*] = ;                           var abil28 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, gc_ability_magic_shot);
      [*] = ;                           addBonus := (ammo > 1) and (abil24 = 0) and (abil28 = 0)
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        if abilID = gc_ability_morale then
      [*] = ;                        begin
      [*] = ;                           var abil19 : Integer = CheckUnitAbility(goHandle, pGOParser, heroHandle, gc_ability_fearless);
      [*] = ;                           addBonus := (abil19 = 0);
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        if addBonus then
      [*] = ;                        begin
      [*] = ;                           var power : Integer = ParserGetIntValueByKeyByHandle(pBonusItem, 'Power');
      [*] = ;                           if abilityID = 0 then
      [*] = ;                           begin
      [*] = ;                              var pGOAbility : Integer = GetAbilityParserByID(abilID);
      [*] = ;                              var value : Integer = ParserGetIntValueByKeyByHandle(pGOAbility, 'Inventory');
      [*] = ;                              value := value + power;
      [*] = ;                              ParserSetIntValueByKeyByHandle(pGOAbility, 'Inventory', value);
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           abilValue := abilValue + power;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister4 := abilValue;
   struct.end
section.end

