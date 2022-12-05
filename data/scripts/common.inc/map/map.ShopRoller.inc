section.begin
   Name = map.ShopRoller
   Description : struct.begin
      [*] = ;IntRegister0 - items type
      [*] = ;IntRegister1 - shop level
      [*] = ;IntRegister2 - rarity
      [*] = ;BoolRegister0 - equal
      [*] = ;OUT: IntRegister3 - items count
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var itemType : Integer = IntRegister0;
      [*] = ;var shopLevel : Integer = IntRegister1;
      [*] = ;var rarity : Integer = IntRegister2;
      [*] = ;var equal : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\MAP\MAP.SHOPROLLER';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name+'['+ IntToStr(shopLevel)+','+ IntToStr(itemType)+']',_log_trace);
      [*] = ;
      [*] = ;var pExtItems : Integer = gPrototypeData.extItems.handle;
      [*] = ;
      [*] = ;_rand_ClearRoll();
      [*] = ;var count : Integer = 0;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pExtItems)-1 do
      [*] = ;begin
      [*] = ;   var pExtItem : Integer = ParserSelectByHandleByIndex(pExtItems, i);
      [*] = ;   var iType : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'ItemType');
      [*] = ;   var iSlot : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'ItemSlot');
      [*] = ;   var iShopLevel : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'ShopLevel');
      [*] = ;   var iDurability : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'Durability');
      [*] = ;   var iRarity : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'Rarity');
      [*] = ;
      [*] = ;   var bAdd : Boolean = false;
      [*] = ;
      [*] = ;   if (iShopLevel <= shopLevel) then
      [*] = ;   begin
      [*] = ;      case itemType of
      [*] = ;         3, 4, 5, 7, 8, 10, 11, 12, 13 :
      [*] = ;         begin
      [*] = ;            if iType = itemType then
      [*] = ;               bAdd := true;
      [*] = ;         end;
      [*] = ;         6 :
      [*] = ;         // belts
      [*] = ;         begin
      [*] = ;            if (iType = itemType) or (iSlot = 5) then
      [*] = ;               bAdd := true;
      [*] = ;         end;
      [*] = ;         1, 2, 9 :
      [*] = ;         // weapon and shields
      [*] = ;         begin
      [*] = ;            if (iType = 1) or (iType = 2) or (iType = 9) then
      [*] = ;               bAdd := true;
      [*] = ;         end;
      [*] = ;         -1 :
      [*] = ;         // clothes
      [*] = ;         begin
      [*] = ;            if (iType = 0) and ((iSlot = 3) or (iSlot = 4) or (iSlot = 6) or (iSlot = 7) or (iSlot = 8) or ((iSlot = 10) and (iDurability > 0))) then
      [*] = ;               bAdd := true;
      [*] = ;         end;
      [*] = ;         // finery
      [*] = ;         -2 :
      [*] = ;         begin
      [*] = ;            if (iType = 0) and ((iSlot = 9) or (iSlot = 11) or ((iSlot = 10) and (iDurability = 0))) then
      [*] = ;               bAdd := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if i >= gPrototypeData.items.number then
      [*] = ;      begin
      [*] = ;         if ParserGetIntValueByKeyByHandle(pExtItem, 'ItemID') <= 0 then
      [*] = ;            bAdd := false
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var pItemAbility0 : Integer = ParserSelectByHandleByIndex(ParserSelectByHandleByKey(pExtItem, 'Abilities'), 0);
      [*] = ;            if ParserGetIntValueByKeyByHandle(pItemAbility0, 'Power') = 0 then
      [*] = ;               bAdd := false;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if bAdd and (iRarity >= rarity) and ((iShopLevel = shopLevel) or (not equal)) and _map_IsItemEnabled(i) then
      [*] = ;      begin
      [*] = ;         gArrRollerN[count] := i;
      [*] = ;         gArrRollerP[count] := 8 - iRarity;
      [*] = ;         count := count + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+ IntToStr(count)+']',$1000000 or _log_trace);
      [*] = ;IntRegister3 := count;
   struct.end
section.end

