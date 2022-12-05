section.begin
   Name = lan.DoCreate
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;if (not _misc_IsLanBattle()) then
      [*] = ;   exit;
      [*] = ;
      [*] = ;//gStrRegister_ConsoleLog := '';
      [*] = ;
      [*] = ;//if (gBoolRegister_BattlePlaceMode) and (gIntRegister_InetLanTurn<>-1) then
      [*] = ;//gIntRegister_InetLanTurn := -2;
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeLanBattle) and (gIntRegister_CurGameMode <> gc_GameModeTactics) then
      [*] = ;begin
      [*] = ;   ErrorLogI('map.SwitchToBattle call from lan.DoCreate');
      [*] = ;   GUIExecuteState('map.SwitchToBattle');
      [*] = ;end;
      [*] = ;
      [*] = ;case gGame.gameType of
      [*] = ;   gc_GameTypeLanBattle : begin
      [*] = ;      if not IsLanReady() then
      [*] = ;      begin
      [*] = ;         if _log then _Log_lan(IntToStr(LanMyInfoIP())+' : '+IntToStr(LanMyInfoID)+' lan.DoCreate');
      [*] = ;         //_lan_timer_Arm(gc_lt_loading,0,false); this relocated to vvk.lan.onprogressgui because all timers are reset there
      [*] = ;         LanDoReady();
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_GameTypeLanShard : begin
      [*] = ;      if _log then _log_valuesL('BATTLELOADED_AS|MY_ID',GetLanMode(),LanMyInfoID(),0,0,0,0);
      [*] = ;      if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;      begin
      [*] = ;         var p : Integer = _misc_ParserGetOrCreateByKey('lan_docreate_startbattle',true);
      [*] = ;         _lan_timer_Arm(gc_lt_loading,0,false);
      [*] = ;         _inet_LanSendBattleParser(gc_LAN_SHARD_BATTLELOADED,p);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

