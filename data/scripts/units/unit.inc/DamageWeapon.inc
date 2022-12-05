section.begin
   Name = DamageWeapon
   Description : struct.begin
      [*] = ;IntRegister0 - damage
      [*] = ;IntRegister1 - mode: 1 - melee attack, 2 - range attack
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var damage : Integer = IntRegister0;
      [*] = ;var mode : Integer = IntRegister1;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var isHero : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;if not isHero then
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
      [*] = ;function DoDamageToItemSlot(itemSlot, cDamage : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   IntRegister0 := itemSlot; // weapon item type
      [*] = ;   GameObjectExecuteStateByHandle(mapHeroHandle, 'GetSlotIndexByItemSlot');
      [*] = ;   var dollSlot : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var pDollSlot : Integer = ParserSelectByHandleByIndex(pDoll, dollSlot);
      [*] = ;   var itemID : Integer = ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemID');
      [*] = ;   var itemDur : Integer = ParserGetIntValueByKeyByHandle(pDollSlot, 'Durability');
      [*] = ;
      [*] = ;   if (itemID > 0) and (itemDur > 0) and ((_unit_CheckAbility(myGOHandle, gc_ability_item_maintenance) < 100) or (itemSlot = 13)) then
      [*] = ;   begin
      [*] = ;      itemDur := itemDur - cDamage;
      [*] = ;
      [*] = ;      // world rule
      [*] = ;      if (itemSlot<>13) and (_worldrule_GetWorldRuleAbilityExistByID(17)) then // don't add rust world damage to arrows
      [*] = ;      begin
      [*] = ;         var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(17);
      [*] = ;         if (param1>itemDur) then
      [*] = ;            param1 := itemDur;
      [*] = ;         itemDur := itemDur-param1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if itemDur < 0 then
      [*] = ;         itemDur := 0;
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pDollSlot, 'Durability', itemDur);
      [*] = ;
      [*] = ;      if itemDur = 0 then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;            IntRegister1 := 0;
      [*] = ;            IntRegister2 := mapHeroHandle;
      [*] = ;            IntRegister3 := 0;
      [*] = ;            MapExecuteState('CalcUnitInvAbility');
      [*] = ;         end;
      [*] = ;
      [*] = ;         Result := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var destroyed : Boolean = false;
      [*] = ;case mode of
      [*] = ;   1 : begin
      [*] = ;      destroyed := DoDamageToItemSlot(1, damage); // weapon
      [*] = ;      if destroyed and GetGameObjectMyPlayableObject() then
      [*] = ;         _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryParam, gc_battle_unit_iAttack, 0);
      [*] = ;   end;
      [*] = ;   2 : begin
      [*] = ;      var f1 : Boolean = DoDamageToItemSlot(12, damage); // bow
      [*] = ;      var f2 : Boolean = DoDamageToItemSlot(13, damage); // arrows
      [*] = ;      if (f1 or f2) and GetGameObjectMyPlayableObject() then
      [*] = ;         _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryParam, gc_battle_unit_iAttack, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

