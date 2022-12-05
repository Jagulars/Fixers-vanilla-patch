section.begin
   Name = EventInternetShellCreateCustomRoom
   Code : struct.begin
      [*] = ;function CreateRoom(bCustom : Boolean; password : String) : Boolean;
      [*] = ;begin
      [*] = ;   const cMaxPlayers = 2;
      [*] = ;   var gameName : String;
      [*] = ;
      [*] = ;   _lan_timer_Arm(gc_lt_server_answer,gc_gui_FadeTime0_4,false);
      [*] = ;
      [*] = ;   _inet_MakeInetGameParamsString(gameName, bCustom, password);
      [*] = ;   _inet_UpdateNetworkProfileInfo(true,true);
      [*] = ;   LanPublicServerRegister();
      [*] = ;   LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;
      [*] = ;   LanCreateGame(password, gameName, '', cMaxPlayers);
      [*] = ;   LanClSetMyTeam(0);
      [*] = ;   LanSrvSetBattleFieldMode(0);
      [*] = ;   LanSrvSetFogOfWarMode(True);
      [*] = ;end;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String =  GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;const cEventState = 'EventInternetShellCreateCustomRoom';
      [*] = ;const cBtnAcceptTag = 101;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;const cMaxPasswordLength = 16;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var elmInputboxText : Integer = GetGUIElementIndexByNameParent('internetcreatecustom.password.text', _gui_GetLayerI());
      [*] = ;         var password : String = GetGUIElementText(elmInputboxText);
      [*] = ;         var bAvailable : Boolean = False;
      [*] = ;
      [*] = ;         if (password<>'') then
      [*] = ;         begin
      [*] = ;            if (StrLength(password)>cMaxPasswordLength) then
      [*] = ;            _gui_ShowQuestionDialog('menu|137', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;            if (not _inet_IsPasswordValid(password)) then
      [*] = ;               _gui_ShowQuestionDialog('menu|133', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;               bAvailable := True;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         bAvailable := True;
      [*] = ;
      [*] = ;         if (bAvailable) then
      [*] = ;         begin
      [*] = ;            LanTerminateGame;
      [*] = ;            CreateRoom(True, password);
      [*] = ;            _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('internetcreatecustom', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('internetcreatecustom', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

