section.begin
   Name = EventInternetShellCreateShardCustomRoom
   Code : struct.begin
      [*] = ;function CreateShardRoom(gameName, password : String) : Boolean;
      [*] = ;begin
      [*] = ;   var mapName : String;
      [*] = ;
      [*] = ;   _lan_timer_Arm(gc_lt_server_answer,gc_gui_FadeTime0_4,false);
      [*] = ;
      [*] = ;   _inet_MakeInetShardMapParamsString(mapName, password);
      [*] = ;
      [*] = ;   _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;   LanPublicServerRegister();
      [*] = ;   LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;
      [*] = ;   //gGame.gametype := gc_GameTypeLanShard;
      [*] = ;   //LanCreateGame(password, gameName, mapName, gc_MaxCustomMapPlayer);
      [*] = ;   LanCreateGame(password, gameName, mapName, gc_MaxLanMapHumanPlayers);
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
      [*] = ;const cEventState = 'EventInternetShellCreateShardCustomRoom';
      [*] = ;const cBtnAcceptTag = 101;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;const cMaxPasswordLength = 16;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var elmInputboxText : Integer = _gui_GetWindow('internetcreateshardcustom.gamename.text');
      [*] = ;         var gamename : String = GetGUIElementText(elmInputboxText);
      [*] = ;         elmInputboxText := _gui_GetWindow('internetcreateshardcustom.password.text');
      [*] = ;         var password : String = GetGUIElementText(elmInputboxText);
      [*] = ;         var bAvailable : Boolean = False;
      [*] = ;
      [*] = ;         if (gamename='') then
      [*] = ;            _gui_ShowQuestionDialog('gui|805', cEventState, 0, '', 0, False, True)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (password<>'') then
      [*] = ;            begin
      [*] = ;               if (StrLength(password)>cMaxPasswordLength) then
      [*] = ;                  _gui_ShowQuestionDialog('menu|137', cEventState, 0, '', 0, False, True)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (not _inet_IsPasswordValid(password)) then
      [*] = ;                     _gui_ShowQuestionDialog('menu|133', cEventState, 0, '', 0, False, True)
      [*] = ;                  else
      [*] = ;                     bAvailable := True;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               bAvailable := True;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (bAvailable) then
      [*] = ;         begin
      [*] = ;            GUIExecuteState('InitNewGame');
      [*] = ;            
      [*] = ;            var i : Integer;
      [*] = ;            var myInfoID : Integer = LanMyInfoID();
      [*] = ;            for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;            begin
      [*] = ;               gMapSettings.arrplayers[i].id := 0;
      [*] = ;               _map_SetGameCustomDifficultyOptionsDefault(gMapSettings.arrplayers[i].advdiff, False, 3);
      [*] = ;               if (i < 2) then gMapSettings.arrplayers[i].control := 1
      [*] = ;               else gMapSettings.arrplayers[i].control := 0;
      [*] = ;               gLanShardGame.arrlanplayers[i].lanid := 0;
      [*] = ;               _inet_ClearHotseatProfile(gLanShardGame.arrlanplayers[i].profile);
      [*] = ;            end;
      [*] = ;            // setup master
      [*] = ;            gLanShardGame.masterid := myInfoID;
      [*] = ;            gMapSettings.arrplayers[0].id := 0;
      [*] = ;            _map_SetGameCustomDifficultyOptionsDefault(gMapSettings.arrplayers[0].advdiff, False, gProfile.advdiff.basediff);
      [*] = ;            gMapSettings.arrplayers[0].control := 1;
      [*] = ;            gLanShardGame.arrlanplayers[0].lanid := myInfoID;
      [*] = ;            gLanShardGame.arrlanplayers[0].profile.name := gInetProfile.name;
      [*] = ;            gLanShardGame.arrlanplayers[0].profile.land := gInetProfile.land;
      [*] = ;            gLanShardGame.arrlanplayers[0].profile.avatar := gInetProfile.avatar;
      [*] = ;            gLanShardGame.arrlanplayers[0].profile.sign := gInetProfile.sign;
      [*] = ;            gLanShardGame.arrlanplayers[0].profile.color1 := gInetProfile.color1;
      [*] = ;            gLanShardGame.arrlanplayers[0].profile.color2 := gInetProfile.color2;
      [*] = ;            gLanShardGame.arrlanplayers[0].profile.name := gInetProfile.name;
      [*] = ;
      [*] = ;            LanTerminateGame();
      [*] = ;            CreateShardRoom(gamename, password);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('internetcreateshardcustom', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

