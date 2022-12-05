section.begin
   Name = ConflictRetreat
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;BoolRegister0 := false;
      [*] = ;ExecuteState('RetreatGuard');
      [*] = ;_misc_RemoveConflictHero(myUID);
      [*] = ;
      [*] = ;if myUID = gIntRegister_ConflictHeroUID2 then
      [*] = ;begin
      [*] = ;   var confHero1 : Integer = GetGameObjectHandleByUniqueId(gIntRegister_ConflictHeroUID1);
      [*] = ;   var confPlayer1 : Integer = GetGameObjectPlayerHandleByHandle(confHero1);
      [*] = ;   GameObjectExecuteStateByHandle(confHero1, 'ReturnBeforeAttack');
      [*] = ;  
      [*] = ;   if SameText(GetPlayerControlModeByHandle(confPlayer1), 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      StringRegister0 := IntToStr(gc_gui_query_heroSimultaneousAttackRetreat);
      [*] = ;      BoolRegister0 := true;
      [*] = ;      PlayerExecuteStateByHandle(confPlayer1, 'CheckRequestQuery');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;gIntRegister_ConflictHeroUID1 := 0;
      [*] = ;gIntRegister_ConflictHeroUID2 := 0;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

