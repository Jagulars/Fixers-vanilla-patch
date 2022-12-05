section.begin
   Name = DoLanConnect
   Code : struct.begin
      [*] = ;if gProfile.netemail = '' or gProfile.netkey = '' then
      [*] = ;begin
      [*] = ;   var s : String = '';
      [*] = ;
      [*] = ;   if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;      s := 'menuaction|lanshard'
      [*] = ;   else if gGame.gametype = gc_GameTypeLanBattle then
      [*] = ;      s := 'menuaction|lanbattle';
      [*] = ;
      [*] = ;   _cmd_Post('menuaction','lanprofile',s);
      [*] = ;end
      [*] = ;else
      [*] = ;if not IsLanPublicServerMode then
      [*] = ;begin
      [*] = ;   var port : Integer;
      [*] = ;   var ip : String;
      [*] = ;
      [*] = ;   if _inet_GetConnectionIP(ip, port) then
      [*] = ;   begin
      [*] = ;      _Log_lan('Try connection : ' + ip + '['+IntToStr(port)+']');
      [*] = ;
      [*] = ;      //LanShutdown();
      [*] = ;      //_gui_ShowQuestionDialog('Waiting for leShellGetAuth...', '', 0, 'EvLanConnect', 10, False, True); //LAN.SHELL.CONNECTING
      [*] = ;      _lan_timer_Arm(gc_lt_connect,gc_gui_FadeTime0_4,false);
      [*] = ;
      [*] = ;      LanPublicServerEnter(ip,port);
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end