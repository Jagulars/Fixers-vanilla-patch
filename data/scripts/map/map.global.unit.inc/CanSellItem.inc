section.begin
   Name = CanSellItem
   Description : struct.begin
      [*] = IntRegister0 - item ID
      [*] = OUT: BoolRegister0 - can player sell item
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var itemID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;IntRegister0 := itemID;
      [*] = ;StateMachineExecuteState(initMachine, 'GetItemParserByID', 0);
      [*] = ;var pItem : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := itemID;
      [*] = ;IntRegister1 := 84;
      [*] = ;StateMachineExecuteState(initMachine, 'CheckItemAbility', 0);
      [*] = ;var value : Integer = IntRegister2;
      [*] = ;
      [*] = ;if value > 0 then
      [*] = ;begin
      [*] = ;   BoolRegister0 := false;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var pShopItems : Integer = ParserSelectByHandleByKey(pCastle, 'Items');
      [*] = ;for i := ParserGetCountByHandle(pShopItems)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pShopItem : Integer = ParserSelectByHandleByIndex(pShopItems, i);
      [*] = ;   var itID : Integer = ParserGetIntValueByKeyByHandle(pShopItem, 'ItemID');
      [*] = ;
      [*] = ;   if itID = itemID then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := true;
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := itemID;
      [*] = ;      BoolRegister0 := true;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'TryItem');
      [*] = ;      if IntRegister1 > -1 then
      [*] = ;      begin
      [*] = ;         BoolRegister0 := false;
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var itemRarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;      if itemRarity  > 1 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'TryItem');
      [*] = ;         if IntRegister1 > -1 then
      [*] = ;         begin
      [*] = ;            BoolRegister0 := false;
      [*] = ;            exit;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := true;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
