section.begin
   Name = AdvCompareArmiesStrength
   Description : struct.begin
      [*] = ;IntRegister0 - attack province parser
      [*] = ;IntRegister1 - attack site index
      [*] = ;BoolRegister0 - check hero death
      [*] = ;BoolRegister1 - setup battle registers
      [*] = ;OUT: IntRegister2 - comparison result
      [*] = ;OUT: BoolRegister2 - is hero died
   struct.end
   Code : struct.begin
      [*] = ;var checkDeath : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;IntRegister2 := IntRegister1;
      [*] = ;if IntRegister1 = -1 then
      [*] = ;   IntRegister1 := gc_UnitTaskMove
      [*] = ;else
      [*] = ;   IntRegister1 := gc_UnitTaskExplore;
      [*] = ;BoolRegister0 := BoolRegister1;
      [*] = ;ExecuteState('StartVirtualBattle');
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;if bImprovedAI and (gIntRegister_MapCurPlayerIndex = GetPlayerIndexByHandle(myPlHandle)) and SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC') then
      [*] = ;begin
      [*] = ;   var myPlProfile : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;   var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, myPlProfile);
      [*] = ;   var profReckless : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Reckless');
      [*] = ;   gIntRegister_VirtualBattleResult := Max(0, gIntRegister_VirtualBattleResult + profReckless);
      [*] = ;end;
      [*] = ;
      [*] = ;if checkDeath and gBoolRegister_VirtualBattleHeroDied then
      [*] = ;begin
      [*] = ;   ExecuteState('CanResurrect');
      [*] = ;   if not BoolRegister0 then
      [*] = ;      gIntRegister_VirtualBattleResult := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister2 := gIntRegister_VirtualBattleResult;
      [*] = ;BoolRegister2 := gBoolRegister_VirtualBattleHeroDied;
      [*] = ;
      [*] = ;gIntRegister_VirtualBattleResult := 0;
      [*] = ;gBoolRegister_VirtualBattleHeroDied := false;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

