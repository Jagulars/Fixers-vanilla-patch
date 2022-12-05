section.begin
   Name = InitNewGame
   Description[*] = ;
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\INITNEWGAME';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;gMapSettings.players := gProfile.custommapplayers;
      [*] = ;gMapSettings.size := gProfile.custommapsize;
      [*] = ;gMapSettings.worldrule := gProfile.custommapworldrule;
      [*] = ;_prof_MapGeneratorProfileLoad(gMapSettings);
      [*] = ;   
      [*] = ;var bMultiplayer : Boolean = (gGame.gameType = gc_GameTypeHotseat) or (gGame.gametype = gc_GameTypeLanShard);
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;begin
      [*] = ;   gMapSettings.arrplayers[i].id := 0;
      [*] = ;   if bMultiplayer and i < 2 then
      [*] = ;   gMapSettings.arrplayers[i].control := 1
      [*] = ;   else
      [*] = ;   gMapSettings.arrplayers[i].control := 0;
      [*] = ;   gMapSettings.arrplayers[i].advdiff.custom := False;
      [*] = ;   _map_SetGameCustomDifficultyOptionsDefault(gMapSettings.arrplayers[i].advdiff, False, gProfile.advdiff.basediff);
      [*] = ;end;
      [*] = ;
      [*] = ;var bCustomDiff : Boolean = gProfile.advdiff.custom and (not bMultiplayer);
      [*] = ;if bCustomDiff then
      [*] = ;begin
      [*] = ;   gMapSettings.arrplayers[0].advdiff.custom := True;
      [*] = ;   _misc_AssignDifficulty(gProfile.advdiff, gMapSettings.arrplayers[0].advdiff);
      [*] = ;end;
      [*] = ;
      [*] = ;gMapSettings.allowedheroes := gProfile.allowedheroes;
      [*] = ;gMapSettings.fog := gProfile.fog;
      [*] = ;gMapSettings.diplomacy := gProfile.diplomacy;
      [*] = ;gMapSettings.quickgame := gProfile.quickgame;
      [*] = ;gMapSettings.sandbox := gProfile.sandbox and ((gGame.gameType = gc_GameTypeCustom) or (gGame.gameType = gc_GameTypeHotseat));
      [*] = ;gMapSettings.genesismode := gProfile.genesismode;
      [*] = ;gMapSettings.improvedai := gProfile.improvedai and (gGame.gameType = gc_GameTypeLanShard);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

