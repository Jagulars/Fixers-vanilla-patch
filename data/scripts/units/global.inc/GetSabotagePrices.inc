section.begin
   Name = GetSabotagePrices
   Description : struct.begin
      [*] = ;OUT: IntRegister0 - false alarm price
      [*] = ;OUT: IntRegister1 - poisoned water price
      [*] = ;OUT: IntRegister2 - panic price
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;ExecuteState('GetHeroHandle');
      [*] = ;var heroHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var arPrices : array [0..2] of Integer;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to 2 do
      [*] = ;   arPrices[i] := -1; // -1 = not available, 0 = free of charge
      [*] = ;
      [*] = ;if heroHandle = 0 then
      [*] = ;  exit;
      [*] = ;
      [*] = ;var bBattleMode : Boolean = (gGame.gameType = gc_GameTypeLanBattle) or (gGame.gameType = gc_GameTypeHotseatBattle);
      [*] = ;var heroUID : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID);
      [*] = ;var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;if (mapHeroHandle = 0) then
      [*] = ;  exit;
      [*] = ;
      [*] = ;IntRegister0 := 24;
      [*] = ;GameObjectExecuteStateByHandle(mapHeroHandle, 'GetSkillLevel');
      [*] = ;var skill24 : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_sabotage;
      [*] = ;GameObjectExecuteStateByHandle(mapHeroHandle, 'CheckAbility');
      [*] = ;var abil981 : Integer = IntRegister1;
      [*] = ;
      [*] = ;if (skill24 > 1) or (abil981 > 0) then
      [*] = ;begin
      [*] = ;   if abil981 > 0 then
      [*] = ;     skill24 := skill24 + 1;
      [*] = ;
      [*] = ;   ExecuteState('GetEnemyPlHandle');
      [*] = ;   var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;      var level : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLevel);
      [*] = ;
      [*] = ;      if _unit_CheckAbility(goHandle, gc_ability_tireless) = 0 then
      [*] = ;        arPrices[0] := arPrices[0] + level;
      [*] = ;
      [*] = ;      if (skill24 > 2) and (_unit_CheckAbility(goHandle, gc_ability_poison_immunity) = 0) then
      [*] = ;        arPrices[1] := arPrices[1] + level;
      [*] = ;
      [*] = ;      if (skill24 > 3) and (_unit_CheckAbility(goHandle, gc_ability_fearless) = 0) then
      [*] = ;        arPrices[2] := arPrices[2] + level;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if arPrices[0] >= 0 then
      [*] = ;   begin
      [*] = ;      arPrices[0] := arPrices[0] + 1;
      [*] = ;      if bBattleMode then
      [*] = ;         arPrices[0] := 0
      [*] = ;      else
      [*] = ;         arPrices[0] := 15 + arPrices[0] * 4;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if arPrices[1] >= 0 then
      [*] = ;   begin
      [*] = ;      arPrices[1] := arPrices[1] + 1;
      [*] = ;      if bBattleMode then
      [*] = ;         arPrices[1] := 0
      [*] = ;      else
      [*] = ;         arPrices[1] := 20 + arPrices[1] * 5;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if arPrices[2] >= 0 then
      [*] = ;   begin
      [*] = ;      arPrices[2] := arPrices[2] + 1;
      [*] = ;      if bBattleMode then
      [*] = ;         arPrices[2] := 0
      [*] = ;      else
      [*] = ;         arPrices[2] := 30 + arPrices[2] * 6;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if skill24 >= 5 then
      [*] = ;   begin
      [*] = ;      for i := 0 to 2 do
      [*] = ;      if arPrices[i] > 1 then
      [*] = ;        arPrices[i] := arPrices[i] div 2;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := arPrices[0];
      [*] = ;IntRegister1 := arPrices[1];
      [*] = ;IntRegister2 := arPrices[2];
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
