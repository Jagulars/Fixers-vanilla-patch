section.begin
   Name = InitAstralChat
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\INITASTRALCHAT';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if IsLanPublicServerMode then
      [*] = ;begin
      [*] = ;   _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;   LanPublicServerRegister();
      [*] = ;   LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;end;
      [*] = ;
      [*] = ;var mainMenuModal : Boolean = false;
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeNone then
      [*] = ;begin
      [*] = ;   if (_inet_GetAstralChatWidth < 450) then
      [*] = ;      mainMenuModal := true;
      [*] = ;end;
      [*] = ;
      [*] = ;if mainMenuModal then
      [*] = ;   IntRegister0 := 1
      [*] = ;else
      [*] = ;if (gIntRegister_CurGameMode = gc_GameModeTactics) then
      [*] = ;   IntRegister0 := 3 // always minimize in battle
      [*] = ;else
      [*] = ;   IntRegister0 := gIntRegister_AstralChatMode;
      [*] = ;GUIExecuteState('ShowAstralChat');
      [*] = ;
      [*] = ;if (not IsLanPublicServerMode) and gProfile.serverautoconnect and (gGame.gameType = gc_GameTypeNone) and (not mainMenuModal) then
      [*] = ;begin
      [*] = ;   gConnectIPIndex := 0;
      [*] = ;   _gui_DelayExecuteStateOneInstance('DoLanConnect', gc_gui_FadeTime0_2); // for some reason has to be delayed a bit or it wont work on game startup.
      [*] = ;   //GUIExecuteState('DoLanConnect');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

