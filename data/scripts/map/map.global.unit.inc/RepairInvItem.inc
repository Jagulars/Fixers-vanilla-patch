section.begin
   Name = RepairInvItem
   Description : struct.begin
      [*] = ;IntRegister0 - pItemSlot
      [*] = ;IntRegister1 - hero handle
      [*] = ;IntRegister2 - shop parser
   struct.end
   Code : struct.begin
      [*] = ;var pItemSlot : Integer = IntRegister0;
      [*] = ;var goHandle : Integer = IntRegister1;
      [*] = ;var pProvShop : Integer = IntRegister2;
      [*] = ;
      [*] = ;var itemID : Integer = ParserGetIntValueByKeyByHandle(pItemSlot, 'ItemID');
      [*] = ;if (itemID > 0) and (_pars_ParserGetIntValueExt(pItemSlot, 'ReservedPlayer') < 0) then // ensure that the durability of reserved items is not changed so it doesn't mess up the transaction.
      [*] = ;begin
      [*] = ;   var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   
      [*] = ;   IntRegister0 := itemID;
      [*] = ;   MapExecuteState('GetItemParserByID');
      [*] = ;   var maxDur : Integer = ParserGetIntValueByKeyByHandle( IntRegister1, 'Durability');
      [*] = ;
      [*] = ;   IntRegister0 := itemID;
      [*] = ;   IntRegister1 := ParserGetIntValueByKeyByHandle(pItemSlot, 'Durability');
      [*] = ;   IntRegister2 := goHandle;
      [*] = ;   IntRegister3 := pProvShop;
      [*] = ;   ExecuteState('GetItemRepPrice');
      [*] = ;   plGold := plGold - IntRegister4;
      [*] = ;   plGem := plGem - IntRegister5;
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pItemSlot, 'Durability', maxDur);
      [*] = ;
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
