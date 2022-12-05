section.begin
   Name = VVK.MenuCommands
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
   struct.end
   Code : struct.begin
      [*] = ;procedure FadeMenu(hdr : Integer);
      [*] = ;begin
      [*] = ;   _misc_FadeMenu('main_menu',hdr);
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var cmd : String = StringRegister0;
      [*] = ;var cmd_attr : String = StringRegister1;
      [*] = ;var reg_attr : String = StringRegister2;
      [*] = ;var user_attr : String = StringRegister3;
      [*] = ;var res,tag,tag_attr,i : Integer;
      [*] = ;var ret_str, lng_str: String;
      [*] = ;
      [*] = ;res := 0;
      [*] = ;ret_str := '';
      [*] = ;tag := 0;
      [*] = ;tag_attr := 0;
      [*] = ;lng_str := '';
      [*] = ;
      [*] = ;case cmd of
      [*] = ;   'menuaction' : begin
      [*] = ;      if mode = 0 then
      [*] = ;         _qaccess_ElementSelected(cmd_attr);
      [*] = ;      res := 1;
      [*] = ;      case cmd_attr of
      [*] = ;         'campaignnew' : begin
      [*] = ;            tag := $20000+42;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               if (user_attr <> '') or ((_misc_GetLoadContinueFlags(8) and 8) = 0) then
      [*] = ;               begin
      [*] = ;                  MapExecuteState('astral.InitCampaign');
      [*] = ;                  MapExecuteState('astral.GenerateTutorialMap');
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  _gui_ShowQuestionDialog('menu|38', '#menucampaignbutton|new|1', 0, '', 0, false, false);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'campaignload' : begin
      [*] = ;            tag := $20000+39;
      [*] = ;            if ((_misc_GetLoadContinueFlags(4) and 4) = 0) then
      [*] = ;               res := 2;
      [*] = ;
      [*] = ;            if (mode = 0) and (res <> 2) then
      [*] = ;            begin
      [*] = ;               _misc_FadeMenuExt('main_menu',4);
      [*] = ;               _prof_SyncCustomsFolderExt(gc_GameTypeFlagCampaign,0,-1);
      [*] = ;               SetIntValueByName('loadMapMode', 0);
      [*] = ;               SetBoolValueByName('bActiveSave', False);
      [*] = ;               SetBoolValueByName('bLoadMapSkipApproval', True);
      [*] = ;               GUIExecuteState('ShowLoadMap');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'campaigncont' : begin
      [*] = ;            tag := $20000+16;
      [*] = ;            lng_str := 'menu#16.campaign';
      [*] = ;            if ((_misc_GetLoadContinueFlags(8) and 8) = 0) then
      [*] = ;               res := 2;
      [*] = ;
      [*] = ;            if (mode = 0) and (res <> 2) then
      [*] = ;            begin
      [*] = ;               gGame.gametype := gc_GameTypeCampaign;
      [*] = ;               StringRegister0 := 'guiDoRunContinueCampaignTimer';
      [*] = ;               FloatRegister0 := gc_gui_FadeTime0_6;
      [*] = ;               GUIExecuteState('FadeIn');
      [*] = ;               FadeMenu(1);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'customnew' : begin
      [*] = ;            tag := $20000+21;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               gGame.gameType := gc_GameTypeCustom;
      [*] = ;               //_map_MapGeneratorDefault(gMapSettings, True);
      [*] = ;               //_misc_AssignDifficulty(gProfile.advdiff, gMapSettings.arrplayers[0].advdiff);
      [*] = ;               GUIExecuteState('InitNewGame');
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowNewGame', gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'customload' : begin
      [*] = ;            tag := $20000+13;
      [*] = ;            if ((_misc_GetLoadContinueFlags(1) and 1) = 0) then
      [*] = ;               res := 2;
      [*] = ;
      [*] = ;            if (mode = 0) and (res <> 2) then
      [*] = ;            begin
      [*] = ;               _misc_FadeMenuExt('main_menu',4);
      [*] = ;               _prof_SyncCustomsFolder(gc_GameTypeFlagSingle);
      [*] = ;               SetIntValueByName('loadMapMode', 1);
      [*] = ;               SetBoolValueByName('bActiveSave', False);
      [*] = ;               SetBoolValueByName('bLoadMapSkipApproval', True);
      [*] = ;               GUIExecuteState('ShowLoadMap');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'customcont' : begin
      [*] = ;            tag := $20000+17;
      [*] = ;            lng_str := 'menu#16.shard';
      [*] = ;            if ((_misc_GetLoadContinueFlags(2) and 2) = 0) then
      [*] = ;               res := 2;
      [*] = ;
      [*] = ;            if (mode = 0) and (res <> 2) then
      [*] = ;            begin
      [*] = ;               gGame.gametype := gc_GameTypeCustom;
      [*] = ;               StringRegister0 := 'guiDoRunContinueCustomTimer';
      [*] = ;               FloatRegister0 := gc_gui_FadeTime0_6;
      [*] = ;               GUIExecuteState('FadeIn');
      [*] = ;               FadeMenu(1);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'lanbattle', 'lanshard' : begin
      [*] = ;            if cmd_attr = 'lanshard' then
      [*] = ;               tag := $20000+224
      [*] = ;            else
      [*] = ;               tag := $20000+156;
      [*] = ;            
      [*] = ;            if gConnectIPCount > 0 then
      [*] = ;            begin
      [*] = ;               if mode = 0 then
      [*] = ;               begin
      [*] = ;                  _log_lan('Entering lobby: '+cmd_attr);
      [*] = ;                  
      [*] = ;                  gBoolRegister_IsHotSeat := False;
      [*] = ;                  
      [*] = ;                  if cmd_attr = 'lanshard' then
      [*] = ;                  begin
      [*] = ;                     gGame.gametype := gc_GameTypeLanShard;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     _inet_UpdateAllHeroes(gInetBattle);
      [*] = ;                     gIntRegister_InetWindowMode := 1;
      [*] = ;                     gIntRegister_InetHeroMode := 5;
      [*] = ;                     gGame.gametype := gc_GameTypeLanBattle;
      [*] = ;                  end;
      [*] = ;                  
      [*] = ;                  if not IsLanPublicServerMode then // if not yet connected to server
      [*] = ;                  begin
      [*] = ;                     gConnectIPIndex := 0;
      [*] = ;                     GUIExecuteState('DoLanConnect');
      [*] = ;                  end
      [*] = ;                  else // already connected, simply enter lobby
      [*] = ;                  begin
      [*] = ;                     const cShellClientsList = 'internetshell.rightpanel.players.list';
      [*] = ;                     const cShellShardGamesList = 'internetshell.leftpanel.shardgames.list';
      [*] = ;                     
      [*] = ;                     _gui_FadeWindow_VVK(_gui_GetWindow('internetshell'), 0, 1); // astral chat must be removed before entering lobby or everything will disappear when creating a room
      [*] = ;                        
      [*] = ;                     _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;                     LanPublicServerRegister();
      [*] = ;                     LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;                     
      [*] = ;                     GUIExecuteState('ShowInternetShell');
      [*] = ;                     if gGame.gametype <> gc_GameTypeLanShard then
      [*] = ;                        _gui_ShowQuestionDialog('menu|multiplayer_version_reminder', '',0,'', 0,false,true)
      [*] = ;                     else
      [*] = ;                        _gui_ShowQuestionDialog('gui|network_disclaimer2', '',0,'', 0,false,true);
      [*] = ;
      [*] = ;                     _inet_UpdateShardGamesList(cShellShardGamesList);
      [*] = ;                     _inet_UpdateClientsList(cShellClientsList,0);
      [*] = ;
      [*] = ;                     _inet_RefreshLoadGameProgress(0);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               res := $102;
      [*] = ;         end;
      [*] = ;         'hotseatbattle' : begin
      [*] = ;            tag := $20000+157;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               _inet_UpdateAllHeroes(gHotSeatPlayer1);
      [*] = ;               _inet_UpdateAllHeroes(gHotSeatPlayer2);
      [*] = ;               
      [*] = ;               gBoolRegister_IsHotSeat := True;
      [*] = ;               gIntRegister_InetWindowMode := 2;
      [*] = ;               gIntRegister_InetHeroMode := 5;
      [*] = ;               gIntRegister_HotSeatActivePlayer := 0;
      [*] = ;               gGame.gameType := gc_GameTypeHotseatBattle;
      [*] = ;               GUIExecuteState('ShowInternetShell');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'hotseatshard' : begin
      [*] = ;            tag := $20000+223;
      [*] = ;            if (mode = 0) then
      [*] = ;            begin
      [*] = ;               gGame.gameType := gc_GameTypeHotseat;
      [*] = ;               GUIExecuteState('InitNewGame');
      [*] = ;               //_map_MapGeneratorDefault(gMapSettings, True);
      [*] = ;               _inet_InitRandomHotseatProfiles();
      [*] = ;               //_misc_AssignDifficulty(gProfile.advdiff, gMapSettings.arrplayers[0].advdiff);
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowNewGame', gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'hotseatload' : begin
      [*] = ;            tag := $20000+226;
      [*] = ;            if ((_misc_GetLoadContinueFlags($10) and $10) = 0) then
      [*] = ;               res := 2;
      [*] = ;
      [*] = ;            if (mode = 0) and (res <> 2) then
      [*] = ;            begin
      [*] = ;               _prof_SyncCustomsFolder(0);
      [*] = ;               SetIntValueByName('loadMapMode', 1);
      [*] = ;               SetBoolValueByName('bActiveSave', False);
      [*] = ;               SetBoolValueByName('bLoadMapSkipApproval', True);
      [*] = ;               GUIExecuteState('ShowLoadMap');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'lanprofile' : begin
      [*] = ;            tag := $20000+225;
      [*] = ;            if gConnectIPCount > 0 then
      [*] = ;            begin
      [*] = ;               if mode = 0 then
      [*] = ;               begin
      [*] = ;                  //var a : Integer = _sa_GetAsInt(user_attr,_sa_GetNum(user_attr)-1);
      [*] = ;                  //if a > $ff then
      [*] = ;                  //begin
      [*] = ;                     //if a = $100 then
      [*] = ;                     //begin
      [*] = ;                        StringRegister0 := user_attr;
      [*] = ;                        GUIExecuteState('VVK.SetupLanProfile');
      [*] = ;                    // end
      [*] = ;                    // else
      [*] = ;                    // begin
      [*] = ;                     //   if not _misc_IsMenuVisible('main_menu') then
      [*] = ;                      //     GUIExecuteState('ShowMultiplayer');
      [*] = ;                   //  end;
      [*] = ;                  //end;
      [*] = ;                  //else
      [*] = ;                  //   _gui_ShowQuestionDialogWithFade('gui|network_disclaimer', '#menuaction|lanprofile|'+user_attr+'|256',0, '#menuaction|lanprofile|'+user_attr+'|257', 0,false,false,$f,'networkwaiver_dialog');
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               res := $102;
      [*] = ;         end;
      [*] = ;         'multiplayer' : begin
      [*] = ;            tag := $20000+4;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               FadeMenu(0);
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowMultiplayer',gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'windowdesigner' : begin
      [*] = ;            tag := $20000+237;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               _misc_FadeMenu('main_menu',1);
      [*] = ;               BoolRegister0 := True;
      [*] = ;               GUIExecuteState('WindowDesigner');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'mainmenu' : begin
      [*] = ;            tag := $20000+11;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               _misc_FadeMenu('main_menu',0);
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowMenu', gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         else res := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   '.menulanevent' : begin
      [*] = ;      res := 1;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;      begin
      [*] = ;         if cmd_attr = 'cancel' then
      [*] = ;         begin
      [*] = ;            LanPublicServerLeave();
      [*] = ;            LanTerminateGame();
      [*] = ;            LanShutdown();
      [*] = ;            _cmd_Post('menuaction','multiplayer','');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            GUIExecuteState('LanEventDefault');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'copy', 'paste' : begin // unused
      [*] = ;      res := 0;
      [*] = ;      {var elmHandle : Integer = GetGUIFocusedElementHandle();
      [*] = ;      if elmHandle = 0 then
      [*] = ;         res := 0
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         res := 1;
      [*] = ;         if (mode = 0) then
      [*] = ;         begin
      [*] = ;            if cmd = 'copy' then
      [*] = ;               gStr_Clipboard := GetGUIElementText(elmHandle)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;            Log('extpaste '+IntToStr(_gui_GetWindow('Window Designer.External Text Paste')));
      [*] = ;            Log('extpaste chcked '+BoolToStr(GetGUIElementChecked(_gui_GetWindow('Window Designer.External Text Paste'))));
      [*] = ;            if not GetGUIElementChecked(_gui_GetWindow('Window Designer.External Text Paste')) then
      [*] = ;               SetGUIElementText(elmHandle, gStr_Clipboard);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;}
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
      [*] = ;IntRegister2 := res;
      [*] = ;StringRegister0 := ret_str;
   struct.end
section.end
