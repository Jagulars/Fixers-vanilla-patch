section.begin
   Name = VVK.ExitMenuCommands
   UsedFileName =
   Description : struct.begin
      [*] = ;IntRegister0 - execution mode (0-execute, 1-return status)
      [*] = ;IntRegister1 - command id
      [*] = ;IntRegister3 - (!) window handle to which this one attached
      [*] = ;StringRegister0 - command name
      [*] = ;StringRegister1 - command parameters (from cfg file)
      [*] = ;StringRegister2 - state parameters (passed in RegisterWindowState)
      [*] = ;StringRegister3 - extra state parameters (passed in PostCommand)
      [*] = ;RETURNS:
      [*] = ;   IntRegister2 - (&0xff: 1 - command available, stop execution, 2 - command unavailable, stop execution, 0 - not supported, continue execution)
      [*] = ;                  high 24 bits are for user defined check availability attributes!
      [*] = ;   StringRegister0 - string array
      [*] = ;      int: element tag
      [*] = ;      int: button extra status (1 - show as checked)
      [*] = ;      str: text reource section and name split by # sign, or empty string if old scheme (menu#(tag&0x7fff)) should be used
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\VVK.EXITMENUCOMMANDS';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;const cBtnSurrenderApprove = 201;
      [*] = ;const cBtnExitApprove = 202;
      [*] = ;const cBtnExitToMainMenuApprove = 203;
      [*] = ;
      [*] = ;procedure FadeMenu(hdr : Integer);
      [*] = ;begin
      [*] = ;   _misc_FadeMenu('ingame_exitmenu',hdr);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CloseQueryWindow();
      [*] = ;begin
      [*] = ;   SetValueByName('queryID', '');
      [*] = ;   QueryMachineCustomQueriesClear();
      [*] = ;   GUIExecuteState('ToolQueryWindow');
      [*] = ;end;
      [*] = ;
      [*] = ;{procedure LeaveLanSession();
      [*] = ;begin
      [*] = ;   var gf : Integer = _misc_GetGameFlags();
      [*] = ;
      [*] = ;   if ((gf and (gc_GameTypeFlagSingle or gc_GameTypeFlagInternet)) = gc_GameTypeFlagInternet) then
      [*] = ;   begin
      [*] = ;      if ((gf and gc_GameTypeFlagBattle) <> 0) then
      [*] = ;      begin
      [*] = ;         if (LanMyInfoID() = gIntRegsiter_LanBatServerID) then
      [*] = ;         begin
      [*] = ;            LanSrvSetClientScore(LanMyInfoID, -1);
      [*] = ;            LanSrvSetClientScore(_inet_GetLanEnemyID, 1);
      [*] = ;            _lan_LanSendParserToEnemy( gc_LAN_CLIENTWIN, _pars_ParserEmpty)
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _lan_LanSendParserToEnemy( gc_LAN_CLIENTSURRENDER, _pars_ParserEmpty);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var cmd : String = StringRegister0;
      [*] = ;var cmd_attr : String = StringRegister1;
      [*] = ;var reg_attr : String = StringRegister2;
      [*] = ;var user_attr : String = StringRegister3;
      [*] = ;var res,tag,tag_attr,i : Integer;
      [*] = ;var ret_str,lng_str: String;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;res := 1;
      [*] = ;ret_str := '';
      [*] = ;tag := 0;
      [*] = ;tag_attr := 0;
      [*] = ;lng_str := '';
      [*] = ;
      [*] = ;if ((mode = 0) and (not _misc_IsMenuVisible('ingame_exitmenu')) and (user_attr = '')) or ((_cmd_GetAttributes(cmd) and gc_gui_command_attr_system) <> 0) or (SubStr(cmd,1,5) = 'debug') then
      [*] = ;begin
      [*] = ;   IntRegister2 := 0;
      [*] = ;   StringRegister0 := '';
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;case cmd of
      [*] = ;   'menuexitbutton' : begin
      [*] = ;      case cmd_attr of
      [*] = ;         'continue': begin
      [*] = ;            tag := $20000+30;
      [*] = ;            lng_str := 'menu#16';
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               var whd : Integer;
      [*] = ;
      [*] = ;               whd := _gui_GetWindow('ingame_exitmenu');
      [*] = ;               if whd <> 0 then
      [*] = ;                  whd := StrToInt(GetGUIElementStringTag(whd))
      [*] = ;               else
      [*] = ;                  whd := 1;
      [*] = ;               if whd > 0 then
      [*] = ;               begin
      [*] = ;                  FadeMenu(0);
      [*] = ;                  _gui_DelayExecuteStateOneInstance('ShowMenu',gc_gui_FadeTime0_2);
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  FadeMenu(1);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'surrender': begin
      [*] = ;            tag := $20000+20;
      [*] = ;            i := _cmd_Check('menuisactionpossible','',cmd_attr);
      [*] = ;            if ((i and $ff) <> 1) then
      [*] = ;            begin
      [*] = ;               if ((i and $100) <> 0) then res := 0
      [*] = ;               else res := 2;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (mode = 0) and (res = 1) then
      [*] = ;            begin
      [*] = ;               if user_attr <> '' then
      [*] = ;               begin
      [*] = ;                  if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;                  begin
      [*] = ;                     const cBattleResultDelay = 2;
      [*] = ;
      [*] = ;                     MapExecuteState('bat.LoseBattle');
      [*] = ;                     SetFloatValueByName('guiBattleResultWindowDelay', GetGameTime()-cBattleResultDelay-1);
      [*] = ;                     gBoolRegister_GUIBattleResultWindow := True;
      [*] = ;
      [*] = ;                     if (IsLanGame()) and (LanMyInfoID = gIntRegsiter_LanBatClientID) then
      [*] = ;                     begin
      [*] = ;                        _lan_LanSendParserToEnemy( gc_LAN_CLIENTSURRENDER, _pars_ParserEmpty());
      [*] = ;                        LanSrvSetClientScore(LanMyInfoID(), -1);
      [*] = ;                        LanSrvSetClientScore(_inet_GetLanEnemyID(), 1);
      [*] = ;                        LanPublicServerCloseSession();
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if (gGame.gameType <> gc_GameTypeLanShard) then
      [*] = ;                     begin
      [*] = ;                        i := _gui_GetWindow('queryWindow');
      [*] = ;                        if (i<>0) and GetGUIElementVisible(i) then
      [*] = ;                        begin
      [*] = ;                           CloseQueryWindow();
      [*] = ;                           _gv_SetMapLock(-1,_log_name);
      [*] = ;                        end;
      [*] = ;                        BoolRegister0 := true;
      [*] = ;                        PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'PlayerLose');
      [*] = ;                        FadeMenu(1);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        var p : Integer = ParserSelectPlayer(GetPlayerHandleInterfaceIO());
      [*] = ;
      [*] = ;                        ParserSetIntValueByKeyByHandle(p, 'Surrender', 1);
      [*] = ;                        FadeMenu(1);
      [*] = ;                        _cmd_Post('mapnextturn','','1');
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (gIntRegister_CurGameMode=gc_GameModeTactics) then i := 1194
      [*] = ;                  else i := 1163;
      [*] = ;                  _gui_ShowQuestionDialogWithFade('map.event|'+IntToStr(i), '#menuexitbutton|surrender|1', 0, '', 0, False, False,5,'');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'tomain', 'todesktop': begin
      [*] = ;            if cmd_attr = 'tomain' then
      [*] = ;               tag := $20000+107
      [*] = ;            else
      [*] = ;               tag := $20000+108;
      [*] = ;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               if user_attr <> '' then
      [*] = ;               begin
      [*] = ;                  var g_flags : Integer;
      [*] = ;
      [*] = ;                  _misc_FadeMenuExt('ingame_menu',$10f);
      [*] = ;                  _misc_FadeMenuExt('ingame_exitmenu',$10f);
      [*] = ;                  if (_cmd_CheckNF('menuisactionpossible','','save') = 1) and ((_misc_GetGameFlags() and gc_GameTypeFlagSingle) <> 0) and (gIntRegister_CurGameMode <> gc_GameModeTactics) then
      [*] = ;                  begin
      [*] = ;                     StringRegister0 := 'continue';
      [*] = ;                     BoolRegister0 := False;
      [*] = ;                     IntRegister0 := 0;
      [*] = ;                     MapExecuteState('SaveMap');
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if GetLanMode > 0 then
      [*] = ;                  begin
      [*] = ;                     if cmd_attr = 'tomain' then
      [*] = ;                        IntRegister0 := gc_gui_ModeSwitchToLanMenu
      [*] = ;                     else
      [*] = ;                        IntRegister0 := gc_gui_ModeExitLanGame;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if cmd_attr = 'tomain' then
      [*] = ;                        IntRegister0 := gc_gui_ModeSwitchToMainMenu
      [*] = ;                     else
      [*] = ;                        IntRegister0 := gc_gui_ModeExitGame;
      [*] = ;                  end;
      [*] = ;                  FloatRegister0 := gc_gui_FadeTime0_6;
      [*] = ;                  StringRegister0 := '';
      [*] = ;                  GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (gIntRegister_CurGameMode=gc_GameModeTactics) or ((_misc_GetGameFlags() and gc_GameTypeFlagSingle) = 0) then
      [*] = ;                  begin
      [*] = ;                     if cmd_attr = 'tomain' then i := 111
      [*] = ;                     else i := 109;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if cmd_attr = 'tomain' then i := 112
      [*] = ;                     else i := 113;
      [*] = ;                  end;
      [*] = ;                  _gui_ShowQuestionDialogWithFade('menu|'+IntToStr(i), '#menuexitbutton|'+cmd_attr+'|1', 0, '', 0, False, False,5,'');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         else begin
      [*] = ;            res := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   else begin
      [*] = ;      res := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (res <> 0) and (tag <> 0) then
      [*] = ;begin
      [*] = ;   _sa_AddAsInt(ret_str,tag);
      [*] = ;   _sa_AddAsInt(ret_str,tag_attr);
      [*] = ;   _sa_Add(ret_str,lng_str);
      [*] = ;end;
      [*] = ;
      [*] = ;if (reg_attr <> '') and (res = 0) and (not StrExists(cmd,'mbdown')) and (not StrExists(cmd,'mbup')) then
      [*] = ;   res := 2;
      [*] = ;
      [*] = ;IntRegister2 := res;
      [*] = ;StringRegister0 := ret_str;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

