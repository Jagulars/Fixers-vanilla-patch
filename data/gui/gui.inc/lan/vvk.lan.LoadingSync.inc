section.begin
   Name = vvk.lan.LoadingSync
   Description : struct.begin
      [*] = ;IntRegister0 - mode
      [*] = ;IntRegister1 - timer id
      [*] = ;   0 - start sync process
      [*] = ;      BoolRegister0 - true if should call do_progress
      [*] = ;   1 - sync ready received
      [*] = ;      IntRegister2 - message source lan id
      [*] = ;   2 - sync release received
      [*] = ;   3 - get sync status
      [*] = ;      IntRegister0 - status, see gc_lan_timer_status_ constants
      [*] = ;   4 - idle cycle
      [*] = ;   5 - reset to undefined state
      [*] = ;      BoolRegister0 - true if should call do_progress
      [*] = ;   6 - sync revoke received
      [*] = ;      IntRegister2 - message source lan id
      [*] = ;      BoolRegister0 - true if should call do_progress
      [*] = ;   7 - change state received
      [*] = ;      IntRegister2 - message source lan id
      [*] = ;      BoolRegister0 - true if lan_id is ready false if lan_id is revoked
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\LAN\VVK.LAN.LOADINGSYNC';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cReadyPingDelta = 2.0;
      [*] = ;
      [*] = ;function GetHumanPlayersNumber() : Integer;
      [*] = ;begin
      [*] = ;   var i,n,plHandle : Integer;
      [*] = ;   var cMode : String;
      [*] = ;
      [*] = ;   n := 0;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      plHandle := GetPlayerHandleByIndex(i);
      [*] = ;      cMode := GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;      if SameText(cMode, 'cmPlayer') and _plr_IsInGame(plHandle) then
      [*] = ;         n := n + 1;
      [*] = ;   end;
      [*] = ;   if _log then _log_valuesL('HUMAN_PLAYERS',n,0,0,0,0,0);
      [*] = ;
      [*] = ;   Result := n;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckLanTimer(tidx : Integer);
      [*] = ;begin
      [*] = ;   if ((gArr_LanTimers[tidx].flags and 2) <> 0) and (not gBoolRegister_LanMapTurnPassed) then // should not block interface unless turn is passed
      [*] = ;   begin
      [*] = ;      if (gArr_LanTimers[tidx].timer < 0) then
      [*] = ;         gArr_LanTimers[tidx].timer := 0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var whd : Integer;
      [*] = ;
      [*] = ;      if (gArr_LanTimers[tidx].timer<>0) then
      [*] = ;         whd := _gui_GetWindow('LanDialog_'+IntToStr(tidx));
      [*] = ;
      [*] = ;      if (gArr_LanTimers[tidx].timer>0) then
      [*] = ;      begin
      [*] = ;         var cbd : Float;
      [*] = ;
      [*] = ;         if gArr_LanTimers[tidx].cancel_delay > 0 then
      [*] = ;            cbd := gArr_LanTimers[tidx].cancel_delay
      [*] = ;         else
      [*] = ;            cbd := 1000000;
      [*] = ;
      [*] = ;         if (whd<>0) and (GetCurrentTime()>(gArr_LanTimers[tidx].timer+cbd)) then // can cancel after required time has passed.
      [*] = ;         begin
      [*] = ;            var bhd : Integer = GetGUIElementIndexByNameParent('btnCancelFrame',whd);
      [*] = ;
      [*] = ;            if (bhd<>0) and (not GetGUIElementVisible(bhd)) then
      [*] = ;            begin
      [*] = ;               SetGUIElementVisible(bhd, True);
      [*] = ;               SetGUIElementFadingTimes(bhd, gc_gui_FadeTime0_2, 0);
      [*] = ;               SetGUIElementFadeInEnabled(bhd, True);
      [*] = ;               SetGUIElementFadeStart(bhd, True);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (GetCurrentTime()>gArr_LanTimers[tidx].timer) and (whd=0) then
      [*] = ;            begin
      [*] = ;               var qhd : Integer = _gui_ShowQuestionDialogWithFade(gArr_LanTimers[tidx].text, '', 0, gArr_LanTimers[tidx].event_state, gArr_LanTimers[tidx].event_tag, False, True, $f, 'LanDialog_'+IntToStr(tidx));
      [*] = ;
      [*] = ;               if ((gArr_LanTimers[tidx].flags and 4) <> 0) then
      [*] = ;                  _gui_CreateAstralChatButton(qhd, -54, -15);
      [*] = ;               
      [*] = ;               if _log then _log_lan(_log_name+' ['+IntToStr(tidx)+'] : Waiting for event...');
      [*] = ;               if gArr_LanTimers[tidx].event_command <> '' then
      [*] = ;                  _cmd_RegisterWindowState(qhd, gArr_LanTimers[tidx].event_state, 'showmenulantimer');
      [*] = ;               qhd := GetGUIElementIndexByNameParent('btnCancelFrame', qhd);
      [*] = ;               if (qhd<>0) then
      [*] = ;                  SetGUIElementVisible(qhd, False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (gArr_LanTimers[tidx].timer < 0) then
      [*] = ;         begin
      [*] = ;            if (whd<>0) then
      [*] = ;               _gui_RootWindowRemoveWithFade(whd,0);
      [*] = ;            gArr_LanTimers[tidx].timer := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function Status(timer_id : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var f : Float = GetFloatValueByName('LAN_SyncTimer_'+IntToStr(timer_id));
      [*] = ;
      [*] = ;   if f = 0 then
      [*] = ;      Result := gc_lan_timer_status_notactive
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if f > 0 then
      [*] = ;         Result := gc_lan_timer_status_released
      [*] = ;      else
      [*] = ;         Result := gc_lan_timer_status_armed;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Start(timer_id : Integer; do_progress : Boolean);
      [*] = ;begin
      [*] = ;   var tnm : String = 'LAN_SyncTimer_'+IntToStr(timer_id);
      [*] = ;
      [*] = ;   Assert((GetFloatValueByName(tnm) = 0),'[LAN] Recursive sync: '+IntToStr(timer_id));
      [*] = ;   if _log then _log_lan('Sync started with timer id '+tnm+', '+gArr_LanTimers[timer_id].text);
      [*] = ;   if GetLanMode() > 1 then
      [*] = ;   begin
      [*] = ;      var p : Integer;
      [*] = ;
      [*] = ;      p := _misc_ParserGetOrCreateByKey(tnm,true);
      [*] = ;      ParserSetIntValueByKeyByHandle(p,'TotalHumanPlayers',-1*GetHumanPlayersNumber());
      [*] = ;   end;
      [*] = ;   SetFloatValueByName(tnm,-1);
      [*] = ;   _lan_timer_Arm(timer_id,0,do_progress);
      [*] = ;end;
      [*] = ;
      [*] = ;function Ready(timer_id,lan_id : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var tnm : String = 'LAN_SyncTimer_'+IntToStr(timer_id);
      [*] = ;
      [*] = ;   _lan_stimer_ChangeState(timer_id,lan_id,1);
      [*] = ;   if (GetLanMode() > 1) and (GetFloatValueByName(tnm) < 0) then
      [*] = ;   begin
      [*] = ;      var p : Integer = _misc_ParserGetOrCreateByKey(tnm,false);
      [*] = ;      var cs : String = 'Client_'+IntToStr(lan_id);
      [*] = ;
      [*] = ;      if _log and (ParserGetIntValueByKeyByHandle(p,cs) = 0) then _log_valuesL('Timer|Ready_received_from',timer_id,lan_id,0,0,0,0);
      [*] = ;      ParserSetValueByKeyByHandle(p,cs,cs);
      [*] = ;   end;
      [*] = ;   Result := Status(timer_id);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Release(timer_id : Integer);
      [*] = ;begin
      [*] = ;   var tnm : String = 'LAN_SyncTimer_'+IntToStr(timer_id);
      [*] = ;
      [*] = ;   if _log then _log_valuesL('RELEASE_Timer_ID',timer_id,0,0,0,0,0);
      [*] = ;   SetFloatValueByName(tnm,1);
      [*] = ;   if GetLanMode() > 1 then
      [*] = ;      _misc_ParserGetOrCreateByKey(tnm,true);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Idle(timer_id : Integer);
      [*] = ;begin
      [*] = ;   if ((gArr_LanTimers[timer_id].flags and 1) <> 0) and (GetLanMode() > 0) then // synced timer
      [*] = ;   begin
      [*] = ;      var tnm : String = 'LAN_SyncTimer_'+IntToStr(timer_id);
      [*] = ;      var t : float = GetFloatValueByName(tnm);
      [*] = ;
      [*] = ;      if (t <> 0) and (abs(t) <= GetCurrentTime()) then
      [*] = ;      begin
      [*] = ;         var p : Integer = _misc_ParserGetOrCreateByKey('lan_loadsync_ready',true);
      [*] = ;
      [*] = ;         if t < 0 then
      [*] = ;            SetFloatValueByName(tnm,-1*(GetCurrentTime()+cReadyPingDelta))
      [*] = ;         else
      [*] = ;            SetFloatValueByName(tnm,GetCurrentTime()+cReadyPingDelta);
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(p,'LanID',LanMyInfoID());
      [*] = ;         ParserSetIntValueByKeyByHandle(p,'TimerID',timer_id);
      [*] = ;         _lan_LanSendParserToServer(gc_LAN_SHARD_SYNC_READY, p);
      [*] = ;         if GetLanMode() > 1 then
      [*] = ;         begin
      [*] = ;            var pt : Integer = _misc_ParserGetOrCreateByKey(tnm,false);
      [*] = ;            var total_no : Integer;
      [*] = ;
      [*] = ;            total_no := -1*ParserGetIntValueByKeyByHandle(pt,'TotalHumanPlayers');
      [*] = ;            //total_no := GetHumanPlayersNumber();
      [*] = ;            if _log then _log_valuesL('Timer_ID|Synced_players|Total',timer_id,ParserGetCountByHandle(pt)-1,total_no,0,0,0);
      [*] = ;            if (ParserGetCountByHandle(pt) >= (total_no+1)) then // we have them all
      [*] = ;            begin
      [*] = ;               var i,n,c,lan_id : Integer;
      [*] = ;               var nm : String;
      [*] = ;
      [*] = ;               n := 0;
      [*] = ;               for i := 0 to ParserGetCountByHandle(pt)-1 do
      [*] = ;               begin
      [*] = ;                  nm := ParserGetValueByIndexByHandle(pt,i);
      [*] = ;                  if StrLength(nm) > 4 then
      [*] = ;                  begin
      [*] = ;                     lan_id := StrToInt(SubStr(nm,8,StrLength(nm)-7));  // Client_
      [*] = ;                     if lan_id <> 0 then
      [*] = ;                        n := n + 1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if n >= total_no then
      [*] = ;                  _inet_LanSendParserExt(gc_LAN_SHARD_SYNC_RELEASE, p);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   CheckLanTimer(timer_id);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Reset(timer_id : Integer; do_progress : Boolean);
      [*] = ;begin
      [*] = ;   var tnm : String = 'LAN_SyncTimer_'+IntToStr(timer_id);
      [*] = ;
      [*] = ;   if _log and (GetFloatValueByName(tnm) <= 0) then _log_lan('Warning. Timer with ID '+IntToStr(timer_id)+' was reset while not ready.');
      [*] = ;   SetFloatValueByName(tnm,0);
      [*] = ;   _lan_timer_Reset(timer_id,do_progress,'GUI.INC\LAN\VVK.LAN.LOADINGSYNC [Reset]');
      [*] = ;end;
      [*] = ;
      [*] = ;function Revoke(timer_id,lan_id : Integer; do_progress : Boolean) : Integer; // not ready anymore
      [*] = ;begin
      [*] = ;   var tnm : String = 'LAN_SyncTimer_'+IntToStr(timer_id);
      [*] = ;
      [*] = ;   _lan_stimer_ChangeState(timer_id,lan_id,0);
      [*] = ;   if lan_id = LanMyInfoID() then
      [*] = ;   begin
      [*] = ;      SetFloatValueByName(tnm,0);
      [*] = ;      _lan_timer_Reset(timer_id,do_progress,'GUI.INC\LAN\VVK.LAN.LOADINGSYNC [Revoke]');
      [*] = ;   end;
      [*] = ;   if (GetLanMode() > 1) then
      [*] = ;   begin
      [*] = ;      var p : Integer = _misc_ParserGetOrCreateByKey(tnm,false);
      [*] = ;      var cs : String = 'Client_'+IntToStr(lan_id);
      [*] = ;
      [*] = ;      if _log and (ParserGetIntValueByKeyByHandle(p,cs) = 0) then _log_valuesL('Timer|Revoke_received_from',timer_id,lan_id,0,0,0,0);
      [*] = ;      ParserSetValueByKeyByHandle(p,cs,'Client_0');
      [*] = ;   end;
      [*] = ;   Result := Status(timer_id);
      [*] = ;end;
      [*] = ;
      [*] = ;function StateChanged(timer_id,lan_id : Integer; ready : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   //_lan_stimer_ChangeState(timer_id,lan_id,0);
      [*] = ;end;
      [*] = ;
      [*] = ;function dumpLogInfo(mode,tid,arg2 : Integer; do_progress : Boolean; time : Float; org_state : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 1;
      [*] = ;   case mode of
      [*] = ;      3,4,7 : Result := 0;
      [*] = ;      0 : _log_gui(_log_name+'[START. TID:'+IntToStr(tid)+', P:'+BoolToStr(do_progress)+']');
      [*] = ;      5 : _log_gui(_log_name+'[RESET_S. TID:'+IntToStr(tid)+', P:'+BoolToStr(do_progress)+']');
      [*] = ;      6 : _log_gui(_log_name+'[REVOKE. TID:'+IntToStr(tid)+', LANID:'+IntToStr(arg2)+', P:'+BoolToStr(do_progress)+']');
      [*] = ;      $10 : _log_gui(_log_name+'[RESET. TID:'+IntToStr(tid)+', P:'+BoolToStr(do_progress)+', State: '+org_state+']');
      [*] = ;      $11 : _log_gui(_log_name+'[ARM. TID:'+IntToStr(tid)+', P:'+BoolToStr(do_progress)+', T:'+FloatToStr(time)+']');
      [*] = ;      1 : _log_gui(_log_name+'[READY. TID:'+IntToStr(tid)+', LANID:'+IntToStr(arg2)+']');
      [*] = ;      else _log_gui(_log_name+'[MODE:'+IntToStr(mode)+', TID:'+IntToStr(tid)+']');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var tid : Integer = IntRegister1;
      [*] = ;var lan_id : Integer = IntRegister2;
      [*] = ;var do_progress : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;case mode of
      [*] = ;   0 : Start(tid,do_progress);
      [*] = ;   1 : Ready( tid, lan_id);
      [*] = ;   2 : Release(tid);
      [*] = ;   3 : tid := Status(tid);
      [*] = ;   4 : Idle(tid);
      [*] = ;   5 : Reset(tid,do_progress);
      [*] = ;   6 : Revoke(tid,lan_id,do_progress);
      [*] = ;   7 : StateChanged(tid,lan_id,do_progress);
      [*] = ;   else begin
      [*] = ;      if _log and (mode > $ff) then
      [*] = ;         tid := dumpLogInfo(mode and $ff,tid,lan_id,do_progress,FloatRegister0,StringRegister0)
      [*] = ;      else
      [*] = ;         tid := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := tid;
   struct.end
section.end

