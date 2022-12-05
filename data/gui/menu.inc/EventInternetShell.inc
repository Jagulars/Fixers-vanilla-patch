section.begin
   Name = EventInternetShell
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\EVENTINTERNETSHELL';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var sStatus  : String = GetValueByName('Status');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;
      [*] = ;const cBtnMain = 101;
      [*] = ;const cBtnPrepare = 102;
      [*] = ;const cBtnStartBattle = 103;
      [*] = ;const cBtnStartBattleApprove = 104;
      [*] = ;const cBtnProfile = 105;
      [*] = ;const cBtnHotSeatPreparePlayer1 = 106;
      [*] = ;const cBtnHotSeatPreparePlayer2 = 107;
      [*] = ;const cBtnHotSeatStartBattle = 108;
      [*] = ;const cBtnExpandProfileTag = 109;
      [*] = ;const cBtnExitToMainMenu = 110;
      [*] = ;const cBtnPointsModeClassic = 111;
      [*] = ;const cBtnPointsModeProgressive = 112;
      [*] = ;const cBtnCreatePrivateBattle = 113;
      [*] = ;const cBtnJoinBattle = 114;
      [*] = ;const cBtnShardGames = 115;
      [*] = ;const cBtnCreateShardGame = 116;
      [*] = ;const cBtnJoinShardGame = 117;
      [*] = ;const cBtnLoadShardGame = 118;
      [*] = ;const cBtnMode1 = 201;
      [*] = ;const cBtnMode2 = 202;
      [*] = ;const cBtnMode3 = 203;
      [*] = ;const cBtnMode4 = 204;
      [*] = ;const cBtnHeroList = 210;
      [*] = ;const cListBoxPlayers = 30;
      [*] = ;const cListBoxPointsDifference = 50;
      [*] = ;const cListBoxGames = 60;
      [*] = ;const cBtnCancelJoin = 301;
      [*] = ;const cBtnCancelCreate = 302;
      [*] = ;const cBtnCancelPlaySearch = 303;
      [*] = ;const cBtnSetDefaultTag = 120;
      [*] = ;const cRatingAllowHeroesFlagsBaseTag = 400;
      [*] = ;const cRatingAllowTerrainFlagsBaseTag = 420;
      [*] = ;const cCheckBoxTagEmailNotify = 500;
      [*] = ;const cCheckBoxTagConflictNeedsMe = 501;
      [*] = ;const cCheckBoxTagTurnStarted = 502;
      [*] = ;const cCheckBoxTagAllowAINeutrals = 503;
      [*] = ;const cCheckBoxTagAllowAIHuman = 504;
      [*] = ;
      [*] = ;var fontHandle2 : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;
      [*] = ;procedure StartHotSeatBattle();
      [*] = ;begin
      [*] = ;   _prof_SaveStructToUserProfileParser('gHotSeatPlayer1');
      [*] = ;   _prof_SaveStructToUserProfileParser('gHotSeatPlayer2');
      [*] = ;   GUIExecuteState('DoInetBattle');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetupHeroGenerator(var hero : TInetHero; randkey0, randkey1 : Integer);
      [*] = ;begin
      [*] = ;   hero.randkey0 := randkey0;
      [*] = ;   hero.randkey1 := randkey1;
      [*] = ;   hero.lanid := 0;
      [*] = ;   hero.allowedterrains := 63;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UpdateJoinButtonState(bState, sameVersion : Boolean);
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = _gui_GetWindow('internetshell.rightpanel.players.btnjoin');
      [*] = ;   if (elmHandle<>0) then
      [*] = ;   begin
      [*] = ;      SetGUIElementEnabled(elmHandle, bState);
      [*] = ;      var hint : String = GetLocaleTableListItemByID('menu', '212.ext');
      [*] = ;      if (not sameVersion) then
      [*] = ;         hint := GetLocaleTableListItemByID('menu', 'multiplayer_version_reminder')
      [*] = ;      else
      [*] = ;      if (not bState) then
      [*] = ;         hint := hint+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('menu', '213');
      [*] = ;      SetGUIElementHint(elmHandle, hint);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
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
      [*] = ;function CheckPossibilityToStartBattle() : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   if (gInetBattle.hero[gInetBattle.curhero].class1 = 0) then
      [*] = ;   begin
      [*] = ;      gIntRegister_InetWindowMode := 2;
      [*] = ;      gIntRegister_InetHeroMode := 5;
      [*] = ;      ExecuteState('ShowInternetShell');
      [*] = ;      _gui_ShowQuestionDialog('menu|175', '', 0, '', 0, False, True);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var heroScore : Integer = _inet_CalcHeroPrice(gInetBattle.hero[gInetBattle.curhero]);
      [*] = ;      var maxScore : Integer = gInetBattle.points;
      [*] = ;      if (heroScore<(300*0.75)) then
      [*] = ;      begin
      [*] = ;         gIntRegister_InetWindowMode := 2;
      [*] = ;         ExecuteState('ShowInternetShell');
      [*] = ;         _gui_ShowQuestionDialog('menu|176', '', 0, '', 0, False, True);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (heroScore>maxScore) then
      [*] = ;      begin
      [*] = ;         _gui_ShowQuestionDialog('menu|177', '', 0, '', 0, False, True);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (not _inet_CheckAllowHeroesReqs) then
      [*] = ;      begin
      [*] = ;         gIntRegister_InetWindowMode := 1;
      [*] = ;         ExecuteState('ShowInternetShell');
      [*] = ;         _gui_ShowQuestionDialog('menu|178', '', 0, '', 0, False, True);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (not _inet_CheckAllowTerrainReqs) then
      [*] = ;      begin
      [*] = ;         gIntRegister_InetWindowMode := 1;
      [*] = ;         ExecuteState('ShowInternetShell');
      [*] = ;         _gui_ShowQuestionDialog('menu|179', '', 0, '', 0, False, True);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      Result := True;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateLeftSide(elmParentHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := 4;
      [*] = ;   IntRegister1 := elmParentHandle;
      [*] = ;   GUIExecuteState('vvk.LanUpdateGUIElements');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure StartBattle(joinMasterID : Integer);
      [*] = ;begin
      [*] = ;   _prof_SaveStructToUserProfileParser('gInetBattle');
      [*] = ;
      [*] = ;   if (GetLanMode()>0) then
      [*] = ;   begin
      [*] = ;      LanTerminateGame();
      [*] = ;      GUIExecuteState('ShowInternetShell')
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var pSessions : Integer = _misc_ParserGetOrCreateByKey('sessions',true);
      [*] = ;      var join_id : Integer = 0;
      [*] = ;      var i : Integer;
      [*] = ;      var k : Integer;
      [*] = ;      var pointDiffNeeded : Integer = 0;
      [*] = ;      var bOpenJoinCustomRoom : Boolean = False;
      [*] = ;
      [*] = ;      LanPublicServerSessionsToParser(pSessions);
      [*] = ;
      [*] = ;      ArrayClear();
      [*] = ;      for [MAIN]k := 0 to 1 do
      [*] = ;      begin
      [*] = ;         for i := 0 to ParserGetCountByHandle(pSessions)-1 do
      [*] = ;         begin
      [*] = ;            var p : Integer = ParserSelectByHandleByIndex(pSessions, i);
      [*] = ;            var masterID : Integer = ParserGetIntValueByKeyByHandle(p, 'Master');
      [*] = ;            var bCustom : Boolean = False;
      [*] = ;            var password : String = '';
      [*] = ;            var myName : String;
      [*] = ;            var myPoints, myAllowPointsDif, myHeroClass1, myHeroClass2, myAllowedHeroClasses, myAllowedTerrains : Integer;
      [*] = ;            var enName : String;
      [*] = ;            var enPoints, enAllowPointsDif, enHeroClass1, enHeroClass2, enAllowedHeroClasses, enAllowedTerrains : Integer;
      [*] = ;
      [*] = ;            if ParserGetIntValueByKeyByHandle(p, 'MaxPlayers') > ParserGetIntValueByKeyByHandle(p, 'Clients') then
      [*] = ;            begin
      [*] = ;               var gameName : String = ParserGetValueByKeyByHandle(p, 'GameName');
      [*] = ;               _inet_GetInetGameParamsMy(myName, myPoints, myAllowPointsDif, myHeroClass1, myHeroClass2, myAllowedHeroClasses, myAllowedTerrains);
      [*] = ;               _inet_GetInetGameParamsByGameName(gameName, enName, enPoints, enAllowPointsDif, enHeroClass1, enHeroClass2, enAllowedHeroClasses, enAllowedTerrains, bCustom, password);
      [*] = ;
      [*] = ;               if (joinMasterID=0) then
      [*] = ;               begin
      [*] = ;                  if (not bCustom) and (password='') then
      [*] = ;                  begin
      [*] = ;                     var bAllowed : Boolean = False;
      [*] = ;                     
      [*] = ;                     var realPointDiff : Integer = Round(Abs(enPoints-myPoints));
      [*] = ;                     var myPercDiff, enPercDiff : Integer;
      [*] = ;                     case myAllowPointsDif of
      [*] = ;                        0 : enPercDiff := 5;
      [*] = ;                        1 : enPercDiff := 15;
      [*] = ;                        2 : enPercDiff := 30;
      [*] = ;                     end;
      [*] = ;                     case enAllowPointsDif of
      [*] = ;                        0 : myPercDiff := 5;
      [*] = ;                        1 : myPercDiff := 15;
      [*] = ;                        2 : myPercDiff := 30;
      [*] = ;                     end;
      [*] = ;                     var enPointsMin : Integer = round(enPoints-(enPoints * enPercDiff / 100));
      [*] = ;                     var enPointsMax : Integer = round(enPoints+(enPoints * enPercDiff / 100));
      [*] = ;                     var myPointsMin : Integer = round(myPoints-(myPoints * myPercDiff / 100));
      [*] = ;                     var myPointsMax : Integer = round(myPoints+(myPoints * myPercDiff / 100));
      [*] = ;                     
      [*] = ;                     if (myPoints>=enPointsMin) and (myPoints<=enPointsMax) and (enPoints>=myPointsMin) and (enPoints<=myPointsMax) then
      [*] = ;                     begin
      [*] = ;                        bAllowed := True;
      [*] = ;
      [*] = ;                        if (myHeroClass2 > 0) then
      [*] = ;                        begin
      [*] = ;                           var myClassInd : Integer = (myHeroClass1-1) * 4 + myHeroClass2-1;
      [*] = ;                           if ((myClassInd and enAllowedHeroClasses) = 0) then
      [*] = ;                              bAllowed := false;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        if (enHeroClass2 > 0) then
      [*] = ;                        begin
      [*] = ;                           var enClassInd : Integer = (enHeroClass1-1) * 4 + enHeroClass2-1;
      [*] = ;                           if ((enClassInd and myAllowedHeroClasses) = 0) then
      [*] = ;                              bAllowed := false;
      [*] = ;                        end;
      [*] = ;                        
      [*] = ;                        if (bAllowed) then
      [*] = ;                        begin
      [*] = ;                           if (k=0) then
      [*] = ;                              ArrayPushValue(realPointDiff)
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              if (realPointDiff=pointDiffNeeded) then
      [*] = ;                              begin
      [*] = ;                                 join_id := masterID;
      [*] = ;                                 gLanGameRoom := gameName;
      [*] = ;                                 break(MAIN);
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               //if (joinMasterID<>0) then
      [*] = ;               if (joinMasterID=masterID) then
      [*] = ;               begin
      [*] = ;                  join_id := joinMasterID;
      [*] = ;                  if (password<>'') then
      [*] = ;                  begin
      [*] = ;                     bOpenJoinCustomRoom := True;
      [*] = ;                     break(MAIN);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     gLanGameRoom := gameName;
      [*] = ;                     break(MAIN);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (k=0) then
      [*] = ;         begin
      [*] = ;            ArraySort(False);
      [*] = ;            pointDiffNeeded := ArrayPopValue();
      [*] = ;            ArrayClear();
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      LanTerminateGame();
      [*] = ;      //gGame.gametype := gc_GameTypeLanBattle;
      [*] = ;      if (bOpenJoinCustomRoom) then
      [*] = ;         GUIExecuteState('ShowInternetShellJoinCustomRoom')
      [*] = ;      else
      [*] = ;      if (join_id=0) then
      [*] = ;         CreateRoom(False, '')
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _lan_timer_Arm(gc_lt_server_answer,gc_gui_FadeTime0_4,false);
      [*] = ;         LanJoinGame('', IntToStr(join_id), False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure JoinShardRoom(joinMasterID : Integer);
      [*] = ;begin
      [*] = ;   if (GetLanMode()>0) then
      [*] = ;   begin
      [*] = ;      LanTerminateGame();
      [*] = ;      GUIExecuteState('ShowInternetShell');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var pSessions : Integer = _misc_ParserGetOrCreateByKey('sessions',true);
      [*] = ;      var lockedRoom : Boolean = False;
      [*] = ;      var i,p,join_id : Integer;
      [*] = ;      var mapname,password : String;
      [*] = ;
      [*] = ;      LanPublicServerSessionsToParser(pSessions);
      [*] = ;      join_id := 0;
      [*] = ;
      [*] = ;      for i:=0 to ParserGetCountByHandle(pSessions)-1 do
      [*] = ;      begin
      [*] = ;         p := ParserSelectByHandleByIndex(pSessions, i);
      [*] = ;         mapname := ParserGetValueByKeyByHandle(p, 'MapName');
      [*] = ;         if ParserGetIntValueByKeyByHandle(p, 'Master') = joinMasterID then
      [*] = ;         begin
      [*] = ;            if _inet_IsSaveGameMapName(mapname) then
      [*] = ;            begin
      [*] = ;               StringRegister0 := mapname;
      [*] = ;               IntRegister0 := 3;
      [*] = ;               IntRegister1 := LanMyInfoID();
      [*] = ;               GUIExecuteState('vvk.LanUpdateGUIElements');
      [*] = ;               if IntRegister0 > 0 then
      [*] = ;                  join_id := joinMasterID;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if ParserGetIntValueByKeyByHandle(p, 'MaxPlayers') > ParserGetIntValueByKeyByHandle(p, 'Clients') then
      [*] = ;               begin
      [*] = ;                  _inet_GetInetShardPasswordByMapName(mapname, password);
      [*] = ;                  join_id := joinMasterID;
      [*] = ;                  if (password<>'') then
      [*] = ;                     lockedRoom := True;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      LanTerminateGame();
      [*] = ;      if (lockedRoom) then
      [*] = ;         GUIExecuteState('ShowInternetShellJoinShardCustomRoom')
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (join_id<>0) then
      [*] = ;         begin
      [*] = ;            _lan_timer_Arm(gc_lt_server_answer,gc_gui_FadeTime0_4,false);
      [*] = ;            LanJoinGame('', IntToStr(join_id), False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (sStatus='select') then
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;   case tag of
      [*] = ;      cListBoxGames : begin
      [*] = ;         var ind : Integer = GetGUIListBoxItemIndex(elmHandle);
      [*] = ;         if (ind>=0) then
      [*] = ;         begin
      [*] = ;            var pSession : Integer = _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;            LanPublicServerGetSessionInfoToParserByIndex(ind, pSession);
      [*] = ;            var mapname : String = ParserGetValueByKeyByHandle(pSession, 'MapName');
      [*] = ;
      [*] = ;            var myModVersion : String = gc_DataModName + '_' + gc_DataModVersion;
      [*] = ;            var sameGameVersion : Boolean = _inet_IsSameVersionByID(ParserGetIntValueByKeyByHandle(pSession, 'Master'), myModVersion);
      [*] = ;
      [*] = ;            gIntRegister_InetSelectedGameID := GetGUIListBoxItemTag(elmHandle, ind);
      [*] = ;            if _log then _log_valuesL('SEL_ID',gIntRegister_InetSelectedGameID,0,0,0,0,0);
      [*] = ;            UpdateJoinButtonState(((gIntRegister_InetSelectedGameID>-1) and sameGameVersion), sameGameVersion);
      [*] = ;            
      [*] = ;            if _inet_IsSaveGameMapName(mapname) then
      [*] = ;            begin
      [*] = ;               StringRegister0 := mapname;
      [*] = ;               IntRegister0 := 3;
      [*] = ;               IntRegister1 := LanMyInfoID();
      [*] = ;               GUIExecuteState('vvk.LanUpdateGUIElements');
      [*] = ;               if IntRegister0 = 0 then
      [*] = ;                  UpdateJoinButtonState(False, sameGameVersion);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var clients : Integer = ParserGetIntValueByKeyByHandle(pSession, 'Clients');
      [*] = ;               var players : Integer = _inet_GetInetShardMaxPlayersByMapName(mapName);
      [*] = ;               if (clients>=players) then
      [*] = ;                  UpdateJoinButtonState(False, sameGameVersion);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cListBoxPlayers : begin
      [*] = ;         _inet_PlayerSelected(elmHandle, true, true);
      [*] = ;      end;
      [*] = ;      cListBoxPointsDifference : begin
      [*] = ;         var ind : Integer = GetGUIListBoxItemIndex(elmHandle);
      [*] = ;         if (ind>=0) then
      [*] = ;         begin
      [*] = ;            gInetShell.allowpointsdif := ind;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   GUIExecuteState('DoResetDragElement');
      [*] = ;   if (tag>=cBtnMode1) and (tag<=cBtnMode4) then
      [*] = ;   begin
      [*] = ;      gIntRegister_InetSelectedPlayerID := 0;
      [*] = ;      gIntRegister_InetHeroMode := tag-200;
      [*] = ;      GUIExecuteState('ShowInternetShell');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (tag>=cRatingAllowHeroesFlagsBaseTag) and (tag<cRatingAllowTerrainFlagsBaseTag) then
      [*] = ;   begin
      [*] = ;      var ind : Integer = tag-cRatingAllowHeroesFlagsBaseTag;
      [*] = ;      var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;      var checkFlagNumber : Integer = _misc_GetBitFlagByIndex(ind);
      [*] = ;      
      [*] = ;      if bChecked then 
      [*] = ;         gInetShell.allowedheroclasses := gInetShell.allowedheroclasses + checkFlagNumber
      [*] = ;      else
      [*] = ;         gInetShell.allowedheroclasses := gInetShell.allowedheroclasses - checkFlagNumber;
      [*] = ;      
      [*] = ;      SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;
      [*] = ;      var elmHeroesReqText : Integer = GetGUIElementIndexByNameParent('internetshell.leftpanel.leftside.allowheroes.reqs', _gui_GetLayerI);
      [*] = ;      if (elmHeroesReqText<>0) and (_inet_CheckAllowHeroesReqs()) then
      [*] = ;         SetGUIElementVisible(elmHeroesReqText, False)
      [*] = ;      else
      [*] = ;         SetGUIElementVisible(elmHeroesReqText, True);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (tag>=cRatingAllowTerrainFlagsBaseTag) and (tag<cRatingAllowTerrainFlagsBaseTag+gc_TerrainChoiceCount) then
      [*] = ;   begin
      [*] = ;      var ind : Integer = tag-cRatingAllowTerrainFlagsBaseTag;
      [*] = ;      var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;      var checkFlagNumber : Integer = _misc_GetBitFlagByIndex(ind);
      [*] = ;      
      [*] = ;      if bChecked then 
      [*] = ;         gInetShell.allowedterrains := gInetShell.allowedterrains + checkFlagNumber
      [*] = ;      else
      [*] = ;         gInetShell.allowedterrains := gInetShell.allowedterrains - checkFlagNumber;
      [*] = ;      
      [*] = ;      SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;
      [*] = ;      var elmTerrainReqText : Integer = GetGUIElementIndexByNameParent('internetshell.leftpanel.leftside.allowterrain.reqs', _gui_GetLayerI);
      [*] = ;      if (elmTerrainReqText<>0) and (_inet_CheckAllowTerrainReqs()) then
      [*] = ;         SetGUIElementVisible(elmTerrainReqText, False)
      [*] = ;      else
      [*] = ;         SetGUIElementVisible(elmTerrainReqText, True);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   case tag of
      [*] = ;      cCheckBoxTagEmailNotify : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;      cCheckBoxTagConflictNeedsMe : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;      cCheckBoxTagTurnStarted : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;      cCheckBoxTagAllowAINeutrals : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;      cCheckBoxTagAllowAIHuman : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;      cBtnCancelJoin : begin
      [*] = ;         LanTerminateGame();
      [*] = ;      end;
      [*] = ;      cBtnCancelCreate : begin
      [*] = ;         LanTerminateGame();
      [*] = ;      end;
      [*] = ;      cBtnCancelPlaySearch : begin
      [*] = ;         LanTerminateGame();
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;         _inet_UpdateShardGamesList('internetshell.leftpanel.shardgames.list');
      [*] = ;         _inet_UpdateClientsList('internetshell.rightpanel.players.list', 0);
      [*] = ;      end;
      [*] = ;      cBtnStartBattleApprove : begin
      [*] = ;         StartBattle(0);
      [*] = ;      end;
      [*] = ;      cBtnCreateShardGame : begin
      [*] = ;         GUIExecuteState('ShowInternetShellCreateShardCustomRoom');
      [*] = ;      end;
      [*] = ;      cBtnJoinShardGame : begin
      [*] = ;         if gIntRegister_InetSelectedGameID > -1 then
      [*] = ;         begin
      [*] = ;            var pSession : Integer = _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;            LanPublicServerGetSessionInfoToParserByIndex(gIntRegister_InetSelectedGameID, pSession);
      [*] = ;            var masterID : Integer = ParserGetIntValueByKeyByHandle(pSession, 'Master');
      [*] = ;            gIntRegister_InetSelectedPlayerID := masterID;
      [*] = ;            JoinShardRoom(masterID);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnLoadShardGame : begin
      [*] = ;         _prof_SyncCustomsFolderExt(gc_GameTypeFlagInternet,0,1);
      [*] = ;         SetIntValueByName('loadMapMode', 2);
      [*] = ;         SetBoolValueByName('bActiveSave', False);
      [*] = ;         SetBoolValueByName('bLoadMapSkipApproval', True);
      [*] = ;         GUIExecuteState('ShowLoadMap');
      [*] = ;      end;
      [*] = ;      cBtnCreatePrivateBattle : begin
      [*] = ;         if (CheckPossibilityToStartBattle()) then
      [*] = ;            GUIExecuteState('ShowInternetShellCreateCustomRoom');
      [*] = ;      end;
      [*] = ;      cBtnJoinBattle : begin
      [*] = ;         if (CheckPossibilityToStartBattle()) then
      [*] = ;            StartBattle(gIntRegister_InetSelectedPlayerID);
      [*] = ;      end;
      [*] = ;      cBtnStartBattle : begin
      [*] = ;         if (CheckPossibilityToStartBattle()) then
      [*] = ;            StartBattle(0);
      [*] = ;      end;
      [*] = ;      cBtnHotSeatStartBattle : begin
      [*] = ;         if (gHotSeatPlayer1.hero[gHotSeatPlayer1.curhero].class1=0) then
      [*] = ;         begin
      [*] = ;            gIntRegister_HotSeatActivePlayer := 0;
      [*] = ;            gIntRegister_InetWindowMode := 2;
      [*] = ;            gIntRegister_InetHeroMode := 5;
      [*] = ;            GUIExecuteState('ShowInternetShell');
      [*] = ;            _gui_ShowQuestionDialog('menu|175', '', 0, '', 0, False, True);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (gHotSeatPlayer2.hero[gHotSeatPlayer2.curhero].class1=0) then
      [*] = ;         begin
      [*] = ;            gIntRegister_HotSeatActivePlayer := 1;
      [*] = ;            gIntRegister_InetWindowMode := 2;
      [*] = ;            gIntRegister_InetHeroMode := 5;
      [*] = ;            GUIExecuteState('ShowInternetShell');
      [*] = ;            _gui_ShowQuestionDialog('menu|175', '', 0, '', 0, False, True);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (_inet_CalcHeroPrice(gHotSeatPlayer1.hero[gHotSeatPlayer1.curhero])>gc_hotseat_maxpoints) or (_inet_CalcHeroPrice(gHotSeatPlayer2.hero[gHotSeatPlayer2.curhero])>gc_hotseat_maxpoints) then
      [*] = ;            begin
      [*] = ;               _gui_ShowQuestionDialog('menu|177', '', 0, '', 0, False, True);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var randKey0, randKey1 : Integer;
      [*] = ;               GenerateMapRandKey(randKey0, randKey1);
      [*] = ;
      [*] = ;               _inet_AssignHero(gHotSeatPlayer1.hero[gHotSeatPlayer1.curhero], gLanHeroServer);
      [*] = ;               _inet_AssignHero(gHotSeatPlayer2.hero[gHotSeatPlayer2.curhero], gLanHeroClient);
      [*] = ;               SetupHeroGenerator(gLanHeroServer, randKey0, randKey1);
      [*] = ;               SetupHeroGenerator(gLanHeroClient, randKey0, randKey1);
      [*] = ;
      [*] = ;               StartHotSeatBattle();
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnExpandProfileTag : begin
      [*] = ;         var bChecked : Boolean = GetGUIElementChecked(elmHandle);
      [*] = ;         SetGUIElementChecked(elmHandle, not bChecked);
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;      cBtnExitToMainMenu, gc_gui_hotkey_btnEscape : begin
	  [*] = ;         if not gProfile.serverautoconnect then
	  [*] = ;         begin
      [*] = ;            LanShutdown();
	  [*] = ;            LanPublicServerLeave();
	  [*] = ;         end;
	  [*] = ;         
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('internetshell'),gc_gui_FadeTime0_4);
	  [*] = ;         
      [*] = ;         //_gui_DelayExecuteStateOneInstance('ShowMenu', gc_gui_FadeTime0_4);
      [*] = ;         if (gBoolRegister_IsHotSeat) then
      [*] = ;         begin
      [*] = ;            _prof_SaveStructToUserProfileParser('gHotSeatPlayer1');
      [*] = ;            _prof_SaveStructToUserProfileParser('gHotSeatPlayer2');
      [*] = ;            gBoolRegister_IsHotSeat := False;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if gGame.gametype = gc_GameTypeLanBattle then
      [*] = ;               _prof_SaveStructToUserProfileParser('gInetBattle');
      [*] = ;         end;
      [*] = ;         gGame.gametype := gc_GameTypeNone;
	  [*] = ;         
	  [*] = ;         if gProfile.serverautoconnect then
      [*] = ;         begin
      [*] = ;            _inet_UpdateNetworkProfileInfo(false, true);
      [*] = ;            LanPublicServerRegister();
      [*] = ;            LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;            
      [*] = ;            if not _inet_AstralChatModal then
      [*] = ;            begin
      [*] = ;               IntRegister0 := gIntRegister_AstralChatMode;
      [*] = ;               GUIExecuteState('ShowAstralChat');
      [*] = ;            end;
      [*] = ;         end;
	  [*] = ;         
      [*] = ;         GUIExecuteState('ShowMultiplayer');
      [*] = ;      end;
      [*] = ;      cBtnHeroList : begin
      [*] = ;         gIntRegister_InetHeroMode := 5;
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;      cBtnMain : begin
      [*] = ;         gIntRegister_InetSelectedPlayerID := 0;
      [*] = ;         gIntRegister_InetWindowMode := 1;
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;      cBtnPrepare : begin
      [*] = ;         gIntRegister_InetWindowMode := 2;
      [*] = ;         if (gInetBattle.hero[gInetBattle.curhero].class1=0) then
      [*] = ;            gIntRegister_InetHeroMode := 5;
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;      cBtnShardGames : begin
      [*] = ;         gIntRegister_InetWindowMode := 3;
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;      cBtnSetDefaultTag : begin
      [*] = ;         _inet_ShellAllowSetDefault(gInetShell);
      [*] = ;         var elmLeftPanel : Integer = _gui_GetWindow('internetshell.leftpanel');
      [*] = ;         CreateLeftSide(elmLeftPanel);
      [*] = ;
      [*] = ;         var elmHeroesReqText : Integer = _gui_GetWindow('internetshell.leftpanel.leftside.allowheroes.reqs');
      [*] = ;         if (elmHeroesReqText<>0) and (_inet_CheckAllowHeroesReqs()) then
      [*] = ;            SetGUIElementVisible(elmHeroesReqText, False)
      [*] = ;         else
      [*] = ;            SetGUIElementVisible(elmHeroesReqText, True);
      [*] = ;
      [*] = ;         var elmTerrainReqText : Integer = _gui_GetWindow('internetshell.leftpanel.leftside.allowterrain.reqs');
      [*] = ;         if (elmTerrainReqText<>0) and (_inet_CheckAllowTerrainReqs()) then
      [*] = ;            SetGUIElementVisible(elmTerrainReqText, False)
      [*] = ;         else
      [*] = ;            SetGUIElementVisible(elmTerrainReqText, True);
      [*] = ;      end;
      [*] = ;      cBtnHotSeatPreparePlayer1 : begin
      [*] = ;         gIntRegister_HotSeatActivePlayer := 0;
      [*] = ;         if (gHotSeatPlayer1.hero[gHotSeatPlayer1.curhero].class1=0) and (gIntRegister_InetHeroMode<>5) then
      [*] = ;            gIntRegister_InetHeroMode := 5;
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;      cBtnHotSeatPreparePlayer2 : begin
      [*] = ;         gIntRegister_HotSeatActivePlayer := 1;
      [*] = ;         if (gHotSeatPlayer2.hero[gHotSeatPlayer2.curhero].class1=0) and (gIntRegister_InetHeroMode<>5) then
      [*] = ;            gIntRegister_InetHeroMode := 5;
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;      cBtnPointsModeClassic : begin
      [*] = ;         gIntRegister_InetPointsMode := 0;
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;      cBtnPointsModeProgressive : begin
      [*] = ;         gIntRegister_InetPointsMode := 1;
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

