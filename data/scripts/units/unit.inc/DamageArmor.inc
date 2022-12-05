section.begin
   Name = DamageArmor
   Description : struct.begin
      [*] = ;IntRegister0 - damage
      [*] = ;IntRegister1 - attackerUID
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var damage : Integer = IntRegister0;
      [*] = ;var aUID : Integer = IntRegister1;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var isHero : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bIsHero);
      [*] = ;var do_exit : Boolean;
      [*] = ;
      [*] = ;if (not isHero) or (_unit_CheckAbility(myGOHandle, gc_ability_item_maintenance) >= 100) then
      [*] = ;begin
      [*] = ;   SwitchTo('Nothing');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var uid : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iHeroUID);
      [*] = ;var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;var pHeroParser : Integer = ParserSelectGameObject(mapHeroHandle);
      [*] = ;var pDoll : Integer = ParserSelectByHandleByKey(pHeroParser, 'Doll');
      [*] = ;
      [*] = ;var freq : array [0..gc_HeroDollSlotsCount-1] of Integer;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;for i := 0 to gc_HeroDollSlotsCount-1 do
      [*] = ;   freq[i] := 0;
      [*] = ;
      [*] = ;for i := 0 to gc_HeroDollSlotsCount-1 do
      [*] = ;begin
      [*] = ;   var pDollSlot : Integer = ParserSelectByHandleByIndex(pDoll, i);
      [*] = ;   var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemSlot');
      [*] = ;   var itemID : Integer = ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemID');
      [*] = ;   var itemDur : Integer = ParserGetIntValueByKeyByHandle(pDollSlot, 'Durability');
      [*] = ;
      [*] = ;   if (itemID > 0) and (itemDur >0) then
      [*] = ;   begin
      [*] = ;      case itemSlot of
      [*] = ;         2 : freq[i] := 50;
      [*] = ;         3 : freq[i] := 50;
      [*] = ;         4 : freq[i] := 30;
      [*] = ;         5 : freq[i] := 10;
      [*] = ;         6 : freq[i] := 20;
      [*] = ;         7 : freq[i] := 30;
      [*] = ;         8 : freq[i] := 30;
      [*] = ;         10: freq[i] := 10;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var sum : Integer = 0;
      [*] = ;for i := 0 to gc_HeroDollSlotsCount-1 do
      [*] = ;   sum := sum + freq[i];
      [*] = ;
      [*] = ;var destroyed : Boolean = false;
      [*] = ;
      [*] = ;// making damage to armor
      [*] = ;do_exit := false;
      [*] = ;for i := 0 to damage-1 do
      [*] = ;begin
      [*] = ;   if (sum = 0) then
      [*] = ;   begin
      [*] = ;      do_exit := true;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var r : Float = sum * RandomExt;
      [*] = ;   var curSum : Integer = 0;
      [*] = ;
      [*] = ;   for j := 0 to gc_HeroDollSlotsCount-1 do
      [*] = ;   begin
      [*] = ;      curSum := curSum + freq[j];
      [*] = ;      if curSum >= r then
      [*] = ;         break;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pDollSlot : Integer = ParserSelectByHandleByIndex(pDoll, j);
      [*] = ;   var itemDur : Integer = ParserGetIntValueByKeyByHandle(pDollSlot, 'Durability');
      [*] = ;   itemDur := itemDur - 1;
      [*] = ;
      [*] = ;   // world rule
      [*] = ;   if _worldrule_GetWorldRuleAbilityExistByID(17) then
      [*] = ;   begin
      [*] = ;      var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(17);
      [*] = ;      if (param1>itemDur) then
      [*] = ;         param1 := itemDur;
      [*] = ;      itemDur := itemDur-param1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if itemDur = 0 then
      [*] = ;   begin
      [*] = ;      sum := sum - freq[j];
      [*] = ;      freq[j] := 0;
      [*] = ;
      [*] = ;      destroyed := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //_log_map('Damage Armor: Item ID '+IntToStr(ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemID'))+', Durability set as '+IntToStr(itemDur));
      [*] = ;   ParserSetIntValueByKeyByHandle(pDollSlot, 'Durability', itemDur);
      [*] = ;end;
      [*] = ;
      [*] = ;if (not do_exit) and destroyed then
      [*] = ;begin
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := mapHeroHandle;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      MapExecuteState('CalcUnitInvAbility');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if GetGameObjectMyPlayableObject() then
      [*] = ;      _unit_SetupFlyText(myGOHandle, aUID, gc_flytext_CategoryParam, gc_battle_unit_iDefence, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

