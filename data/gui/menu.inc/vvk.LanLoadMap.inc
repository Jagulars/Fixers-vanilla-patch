section.begin
   Name = vvk.LanLoadMap
   Description : struct.begin
      [*] = ;StringRegister0 - save filename
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var fnm : String = StringRegister0;
      [*] = ;var map_name,game_name,players : String;
      [*] = ;var game_uid : Integer;
      [*] = ;
      [*] = ;_lan_timer_Arm(gc_lt_server_answer,gc_gui_FadeTime0_4,false);
      [*] = ;
      [*] = ;game_uid := _prof_GetLanPlayersFromSaveFilename(players,fnm);
      [*] = ;_prof_ConvertSaveFilename(game_name,fnm,true);
      [*] = ;_prof_SyncCustomsFolderExt(gc_GameTypeFlagInternet,game_uid,1);
      [*] = ;
      [*] = ;_inet_MakeInetShardMapParamsForSave(map_name,fnm,game_uid,players);
      [*] = ;
      [*] = ;_inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;LanPublicServerRegister();
      [*] = ;LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;
      [*] = ;LanCreateGame('', game_name, map_name, gc_MaxCustomMapPlayer);
      [*] = ;LanClSetMyTeam(0);
      [*] = ;LanSrvSetBattleFieldMode(0);
      [*] = ;LanSrvSetFogOfWarMode(True);
      [*] = ;
   struct.end
section.end
