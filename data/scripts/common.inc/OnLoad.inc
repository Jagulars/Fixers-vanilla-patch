section.begin
   Name = OnLoad
   Code : struct.begin
      [*] = ;Log('OnLoad');
      [*] = ;//if (gIntRegister_CurGameMode = gc_GameModeStrategy) or (gIntRegister_CurGameMode = gc_GameModeTactics) then
      [*] = ;//begin
      [*] = ;   _map_GetStratHexCells();
      [*] = ;   _map_GetHexCells();
      [*] = ;   _stats_GetStatistics(gGame.gameType);
      [*] = ;
      [*] = ;   gBoolRegister_WriteToGrid := false;
      [*] = ;   gBoolRegister_Loading := true;
      [*] = ;   gBoolRegister_GUIStartup := true;
      [*] = ;//end;
   struct.end
section.end
