section.begin
   Name = EventInternetShellJoinCustomRoom
   Code : struct.begin
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
      [*] = ;         var elmInputboxText : Integer = GetGUIElementIndexByNameParent('internetjoincustom.password.text', _gui_GetLayerI());
      [*] = ;         var inputpassword : String = GetGUIElementText(elmInputboxText);
      [*] = ;         var bAvailable : Boolean = False;
      [*] = ;
      [*] = ;         if (inputpassword<>'') then
      [*] = ;         begin
      [*] = ;            if (StrLength(inputpassword)>cMaxPasswordLength) then
      [*] = ;            _gui_ShowQuestionDialog('menu|137', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;            if (not _inet_IsPasswordValid(inputpassword)) then
      [*] = ;               _gui_ShowQuestionDialog('menu|133', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;               bAvailable := True;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            bAvailable := True;
      [*] = ;
      [*] = ;         var bRoomFound : Boolean = False;
      [*] = ;         if (bAvailable) then
      [*] = ;         begin
      [*] = ;            var pSessions : Integer = _misc_ParserGetOrCreateByKey('sessions',true);
      [*] = ;
      [*] = ;            LanPublicServerSessionsToParser(pSessions);
      [*] = ;            var i : Integer;
      [*] = ;            for i:=0 to ParserGetCountByHandle(pSessions)-1 do
      [*] = ;            begin
      [*] = ;               var p : Integer = ParserSelectByHandleByIndex(pSessions, i);
      [*] = ;               var masterID : Integer = ParserGetIntValueByKeyByHandle(p, 'Master');
      [*] = ;               if (masterID=gIntRegister_InetSelectedPlayerID) then
      [*] = ;               begin
      [*] = ;                  bRoomFound := True;
      [*] = ;                  var bCustom : Boolean = False;
      [*] = ;                  var password : String = '';
      [*] = ;                  var enName : String;
      [*] = ;                  var enPoints, enAllowPointsDif, enHeroClass1, enHeroClass2, enAllowedHeroClasses, enAllowedTerrains : Integer;
      [*] = ;                  var myName : String;
      [*] = ;                  var myPoints, myAllowPointsDif, myHeroClass1, myHeroClass2, myAllowedHeroClasses, myAllowedTerrains : Integer;
      [*] = ;
      [*] = ;                  if ParserGetIntValueByKeyByHandle(p, 'MaxPlayers')>ParserGetIntValueByKeyByHandle(p, 'Clients') then
      [*] = ;                  begin
      [*] = ;                     var gameName : String = ParserGetValueByKeyByHandle(p, 'GameName');
      [*] = ;                     _inet_GetInetGameParamsMy(myName, myPoints, myAllowPointsDif, myHeroClass1, myHeroClass2, myAllowedHeroClasses, myAllowedTerrains);
      [*] = ;                     _inet_GetInetGameParamsByGameName(gameName, enName, enPoints, enAllowPointsDif, enHeroClass1, enHeroClass2, enAllowedHeroClasses, enAllowedTerrains, bCustom, password);
      [*] = ;                     if (inputpassword=password) then
      [*] = ;                     begin
      [*] = ;                        LanTerminateGame();
      [*] = ;                        _lan_timer_Arm(gc_lt_server_answer,gc_gui_FadeTime0_4,false);
      [*] = ;                        LanJoinGame({password}'', IntToStr(gIntRegister_InetSelectedPlayerID), False); // leave password empty to make join work.
      [*] = ;                        _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('internetjoincustom', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     _gui_ShowQuestionDialog('menu|137', cEventState, 0, '', 0, False, True)
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (not bRoomFound) then
      [*] = ;            begin
      [*] = ;               _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('internetjoincustom', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;               ExecuteState('ShowInternetShell');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('internetjoincustom', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

