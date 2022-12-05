section.begin
   Name = SellItem
   Description : struct.begin
      [*] = IntRegister0 - item ID
      [*] = IntRegister1 - item durability
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var itemID : Integer = IntRegister0;
      [*] = ;var itemDur : Integer = IntRegister1;
      [*] = ;// TODO: maybe shop is needed here?
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;IntRegister0 := itemID;
      [*] = ;IntRegister1 := itemDur;
      [*] = ;ExecuteState('GetSellItemPrice');
      [*] = ;var gold : Integer = IntRegister2;
      [*] = ;var gem : Integer = IntRegister3;
      [*] = ;
      [*] = ;plGold := plGold + gold;
      [*] = ;plGem := plGem + gem;
      [*] = ;
      [*] = ;SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;plGold := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gold);
      [*] = ;
      [*] = ;plGem := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + gem);
      [*] = ;
      [*] = ;if _stats_IsEligible(myPlHandle) then 
      [*] = ;begin
      [*] = ;   _stats_SimpleUpdate('Gold', 'ItemsSold', gold);
      [*] = ;   _stats_SimpleUpdate('Gem', 'ItemsSold', gem);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
