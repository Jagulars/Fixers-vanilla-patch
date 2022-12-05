section.begin
   Name = GetArenaReward
   Description : struct.begin
      [*] = IntRegister0 - hero handle
      [*] = OUT: IntRegister1  - arena gold reward
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var enHeroHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var enLevel : Integer = GetGameObjectIntValueIndByHandle(enHeroHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;var league : Integer = gIntRegister_ArenaLeague;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;
      [*] = ;var gold : Integer = 50 + _rand_Random(50) + league * 20 + _rand_Random(league * 20) + enLevel * (20 + league * 7);
      [*] = ;
      [*] = ;IntRegister0 := 985;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;var abil985 : Integer = IntRegister1;
      [*] = ;
      [*] = ;gold := gold + (gold * abil985) div 100;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold + gold);
      [*] = ;
      [*] = ;//plGold := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;//SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gold);
      [*] = ;if _stats_IsEligible(myPlHandle) then _stats_SimpleUpdate('Gold', 'ArenaBattleProfit', gold);
      [*] = ;
      [*] = ;IntRegister1 := gold;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
