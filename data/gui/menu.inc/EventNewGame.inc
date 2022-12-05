section.begin
   Name = EventNewGame
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\EVENTNEWGAME';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure SaveSettingsToProfile();
      [*] = ;begin
      [*] = ;   gProfile.custommapplayers := gMapSettings.players;
      [*] = ;   gProfile.custommapsize := gMapSettings.size;
      [*] = ;   gProfile.custommapworldrule := gMapSettings.worldrule;
      [*] = ;   if not gMapSettings.random then
      [*] = ;      _prof_MapGeneratorProfileSave(gMapSettings);
      [*] = ;   
      [*] = ;   if (gGame.gameType <> gc_GameTypeHotseat) and (gGame.gametype <> gc_GameTypeLanShard) then
      [*] = ;      gProfile.advdiff.custom := gMapSettings.arrplayers[0].advdiff.custom;
      [*] = ;   
      [*] = ;   gProfile.allowedheroes := gMapSettings.allowedheroes;
      [*] = ;   gProfile.fog := gMapSettings.fog;
      [*] = ;   gProfile.diplomacy := gMapSettings.diplomacy;
      [*] = ;   gProfile.quickgame := gMapSettings.quickgame;
      [*] = ;   if (gGame.gameType = gc_GameTypeCustom) or (gGame.gameType = gc_GameTypeHotseat) then
      [*] = ;      gProfile.sandbox := gMapSettings.sandbox;
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;      gProfile.improvedai := gMapSettings.improvedai;
      [*] = ;   gProfile.genesismode := gMapSettings.genesismode;
      [*] = ;   
	  [*] = ;   _prof_SaveUserProfile();
      [*] = ;   UserSaveProfile();
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoInetShardGame(randKey0, randKey1 : Integer);
      [*] = ;begin
      [*] = ;   var pLanGame,pTmp : Integer;
      [*] = ;   var mapname : String;
      [*] = ;
      [*] = ;   pTmp := _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;   LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(),pTmp);
      [*] = ;   mapname := ParserGetValueByKeyByHandle(pTmp,'MapName');
      [*] = ;   if _log then _log_lan('LAN MAP NAME: '+mapname);
      [*] = ;
      [*] = ;   pLanGame := _misc_ParserGetOrCreateByKey('eng_langame', True);
      [*] = ;   if _inet_IsSaveGameMapName(mapname) then
      [*] = ;      ParserSetValueByKeyByHandle(pLanGame, 'SaveGame', mapname)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ParserSetIntValueByKeyByHandle(pLanGame, 'randkey0', randKey0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pLanGame, 'randkey1', randKey1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   _lan_LanSendParser(gc_LAN_START, pLanGame);
      [*] = ;   LanLockServer();
      [*] = ;   IntRegister0 := pLanGame;
      [*] = ;   GUIExecuteState('DoInetShardGame');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RearrangeHumanSlots(new_idx : Integer);
      [*] = ;begin
      [*] = ;   if (IsLanPublicServerMode()) and (GetLanMode()>=2) then
      [*] = ;   begin
      [*] = ;      var i,cno : Integer;
      [*] = ;
      [*] = ;      cno := 0;
      [*] = ;      for i := 1 to gc_MaxCustomMapPlayer-1 do
      [*] = ;      begin
      [*] = ;         if gMapSettings.arrplayers[i].control <> 0 then
      [*] = ;         begin
      [*] = ;            cno := cno + 1;
      [*] = ;            if (cno > (gc_MaxLanMapHumanPlayers-1)) then
      [*] = ;            begin
      [*] = ;               if (gLanShardGame.arrlanplayers[i].lanid <> 0) then LanKillClient(gLanShardGame.arrlanplayers[i].lanid);
      [*] = ;               gLanShardGame.arrlanplayers[i].lanid := 0;
      [*] = ;               gMapSettings.arrplayers[i].control := 0;
      [*] = ;               _inet_ClearHotseatProfile(gLanShardGame.arrlanplayers[i].profile);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure LanUpdateShardRoomInfo();
      [*] = ;begin
      [*] = ;   if (IsLanPublicServerMode()) and (GetLanMode()>=2) then
      [*] = ;   begin
      [*] = ;      var pSession : Integer = _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;      var mapname : String;
      [*] = ;
      [*] = ;      LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(), pSession);
      [*] = ;      mapname := ParserGetValueByKeyByHandle(pSession, 'MapName');
      [*] = ;      if not _inet_IsSaveGameMapName(mapname) then
      [*] = ;      begin
      [*] = ;         // verify human players
      [*] = ;         var cno : Integer = 0;
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;         begin
      [*] = ;            if gMapSettings.arrplayers[i].control <> 0 then
      [*] = ;               cno := cno + 1;
      [*] = ;            if (cno > gc_MaxLanMapHumanPlayers) then
      [*] = ;            begin
      [*] = ;               if i > 1 then gMapSettings.arrplayers[i].control := 0;
      [*] = ;               gLanShardGame.arrlanplayers[i].lanid := 0;
      [*] = ;               _inet_ClearHotseatProfile(gLanShardGame.arrlanplayers[i].profile);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         var password : String;
      [*] = ;         _inet_GetInetShardPasswordByMapName(mapname, password);
      [*] = ;         _inet_MakeInetShardMapParamsString(mapname, password);
      [*] = ;         LanSrvSetMapFile(mapname);
      [*] = ;
      [*] = ;         _inet_SendShardGameSettings();
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure MakeRandomGame();
      [*] = ;begin
      [*] = ;   var humanPlayers,minSize,plrAmount,mapSize : Integer;
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   mapSize := gMapSettings.size;
      [*] = ;   plrAmount := gMapSettings.players + 2; // Displayed players show two more than gMapSettings.players.
      [*] = ;   {humanPlayers := 1;
      [*] = ;   for i:=1 to gc_MaxCustomMapPlayer-1 do
      [*] = ;   begin
      [*] = ;      if gMapSettings.arrplayers[i].control <> 0 then
      [*] = ;         humanPlayers := humanPlayers + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   plrAmount := Round(RandomExt()*(gc_MaxCustomMapPlayer-(minSize+1)))+minSize;
      [*] = ;   minSize := humanPlayers;
      [*] = ;   if minSize < 2 then minSize := 2;
      [*] = ;   plrAmount := Round(RandomExt()*(gc_MaxCustomMapPlayer-(minSize+1)))+minSize;
      [*] = ;   _rand_ClearRoll();
      [*] = ;   minSize := 0;
      [*] = ;   if plrAmount > 15 then
      [*] = ;      minSize := 7
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if plrAmount > 13 then
      [*] = ;         minSize := 6
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if plrAmount > 10 then
      [*] = ;            minSize := 5
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if plrAmount > 7 then
      [*] = ;               minSize := 4
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if plrAmount > 4 then
      [*] = ;                  minSize := 3
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if plrAmount > 2 then
      [*] = ;                     minSize := 2;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   mapSize := 7;
      [*] = ;   if plrAmount < 5 then
      [*] = ;      mapSize := 2
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if plrAmount < 7 then
      [*] = ;         mapSize := 3
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if plrAmount < 9 then
      [*] = ;            mapSize := 4
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if plrAmount < 11 then
      [*] = ;               mapSize := 5
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if plrAmount < 13 then
      [*] = ;                  mapSize := 6;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to 7 do
      [*] = ;   begin
      [*] = ;      gArrRollerN[i] := i+1;
      [*] = ;      if (i >= minSize) and (i <= mapSize) then
      [*] = ;         gArrRollerP[i] := 10
      [*] = ;      else
      [*] = ;         gArrRollerP[i] := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   mapSize := _rand_Roll(false)-1;
      [*] = ;
      [*] = ;   if _log then _Log_values('PLAYERS|MINSIZE|MAPSIZE|HUMANS',plrAmount,minSize,mapSize,humanPlayers,0,0);
      [*] = ;
      [*] = ;   _rand_ClearRoll();
      [*] = ;   for i := 0 to 15 do
      [*] = ;   begin
      [*] = ;      gArrRollerN[i] := i+2;
      [*] = ;      gArrRollerP[i] := 10;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := humanPlayers to plrAmount-1 do
      [*] = ;   begin
      [*] = ;      gMapSettings.arrplayers[i].id := _rand_Roll(true)-1;
      [*] = ;      gMapSettings.arrplayers[i].advdiff.custom := false;
      [*] = ;      gMapSettings.arrplayers[i].advdiff.basediff := Round(RandomExt()*5)+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   gProfile.diplomacy := false;
      [*] = ;   gProfile.fog := false;
      [*] = ;   if (Round(RandomExt()*100) > 33) then
      [*] = ;   begin
      [*] = ;      gProfile.fog := true;
      [*] = ;      if (Round(RandomExt()*100) > 50) then
      [*] = ;         gProfile.diplomacy := true;
      [*] = ;   end;}
      [*] = ;
      [*] = ;   _rand_ClearRoll();
      [*] = ;   var worldrule, k : Integer;
      [*] = ;   k := 0;
      [*] = ;   for i:=0 to gPrototypeData.worldrules.number-1 do
      [*] = ;   begin
      [*] = ;      worldrule := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.worldrules.handle, i), 'WorldRuleID');
      [*] = ;      if (worldrule>=0) and ((worldrule <> 9) or ((plrAmount = 4) and (mapSize = 2))) then // Guarded World possible only when there are four players and average-sized map. Displayed players show two more than gMapSettings.players.
      [*] = ;      begin
      [*] = ;         gArrRollerN[k] := worldrule+1;
      [*] = ;         gArrRollerP[k] := 10;
      [*] = ;         k := k + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gMapSettings.worldrule := _rand_Roll(false)-1;
      [*] = ;   
      [*] = ;   var islandChance : Integer = (10 + mapSize * 10 div 2); // low chance of island map when small map, because it just transforms the perimeter to water, making it cramped.
      [*] = ;   if RandomExt * 100 < islandChance then
      [*] = ;      gMapSettings.typ := 1
      [*] = ;   else
      [*] = ;      gMapSettings.typ := 0;
      [*] = ;   
      [*] = ;   gMapSettings.wastelands := (RandomExt());
      [*] = ;   gMapSettings.population := (RandomExt());
      [*] = ;   gMapSettings.isles := (RandomExt());
      [*] = ;   gMapSettings.forest := (RandomExt());
      [*] = ;   gMapSettings.neutrals := (RandomExt());
      [*] = ;   gMapSettings.dissolve := (RandomExt());
      [*] = ;   gMapSettings.hill := (RandomExt());
      [*] = ;   gMapSettings.resource := (RandomExt());
      [*] = ;   gMapSettings.water := (RandomExt());
      [*] = ;   gMapSettings.swamp := (RandomExt());
      [*] = ;   gMapSettings.site := (RandomExt());
      [*] = ;
      [*] = ;   //gMapSettings.size := mapSize;
      [*] = ;   //gMapSettings.players := plrAmount-2;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsPlayerIDUnique(id : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to gMapSettings.players+1 do
      [*] = ;   begin
      [*] = ;      if (id=gMapSettings.arrplayers[i].id) then
      [*] = ;      begin
      [*] = ;         Result := False;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function FindNextFreePlayerID(curValue : Integer; bForward, bAllowZero : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var minValue : Integer;
      [*] = ;   if (bAllowZero) then
      [*] = ;      minValue := 0
      [*] = ;   else
      [*] = ;      minValue := 1;
      [*] = ;
      [*] = ;   if (bForward) then
      [*] = ;   begin
      [*] = ;      Result := -1;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=(curValue+1) to 16 do
      [*] = ;      begin
      [*] = ;         if (IsPlayerIDUnique(i)) then
      [*] = ;         begin
      [*] = ;            Result := i;
      [*] = ;            break;
      [*] = ;         end
      [*] = ;      end;
      [*] = ;      if (Result=-1) then
      [*] = ;      begin
      [*] = ;         var j : Integer;
      [*] = ;         for j:=minValue to (curValue-1) do
      [*] = ;         begin
      [*] = ;            if (j=0) or (IsPlayerIDUnique(j)) then
      [*] = ;            begin
      [*] = ;               Result := j;
      [*] = ;               break;
      [*] = ;            end
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   //if (not bForward) then
      [*] = ;   begin
      [*] = ;      Result := -1;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=(curValue-1) downto minValue do
      [*] = ;      begin
      [*] = ;         if (i=0) or (IsPlayerIDUnique(i)) then
      [*] = ;         begin
      [*] = ;            Result := i;
      [*] = ;            break;
      [*] = ;         end
      [*] = ;      end;
      [*] = ;      if (Result=-1) then
      [*] = ;      begin
      [*] = ;         var j : Integer;
      [*] = ;         for j:=16 downto (curValue+1) do
      [*] = ;         begin
      [*] = ;            if (IsPlayerIDUnique(j)) then
      [*] = ;            begin
      [*] = ;               Result := j;
      [*] = ;               break;
      [*] = ;            end
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (Result=-1) then
      [*] = ;      ErrorLogI(_log_name+' FindNextFreePlayerID : not found');
      [*] = ;end;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;const cBtnAcceptTag = 101;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;const cGeneratorSettingsBtnTag = 103;
      [*] = ;const cGeneratorRandomBtnTag = 104;
      [*] = ;const cGameplayBtnTag = 105;
      [*] = ;const cBtnSwitchControlModeToHuman = 110;
      [*] = ;const cBtnSwitchControlModeToAI = 111;
      [*] = ;const cBtnKickPlayer = 113;
      [*] = ;const cBtnSetupPlayerProfile = 112;
      [*] = ;const cBtnCustomDifficultyTag = 114;
      [*] = ;
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String = '';
      [*] = ;if (elmHandle<>0) and (IsElementByHandle(elmHandle)) then
      [*] = ;   elmName := GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;{if (sPress='c') and ((elmName='fog') or (elmName='diplomacy')) then
      [*] = ;begin
      [*] = ;   case elmName of
      [*] = ;      'fog' : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         gProfile.fog := bChecked;
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;
      [*] = ;         if (not bChecked) then
      [*] = ;         begin
      [*] = ;            gProfile.diplomacy := bChecked;
      [*] = ;            SetGUIElementChecked(_gui_GetWindow('NewGame.diplomacy'), bChecked);
      [*] = ;         end;
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;      end;
      [*] = ;      'diplomacy' : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         gProfile.diplomacy := bChecked;
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;
      [*] = ;         if (bChecked) then
      [*] = ;         begin
      [*] = ;            gProfile.fog := bChecked;
      [*] = ;            SetGUIElementChecked(_gui_GetWindow('NewGame.fog'), bChecked);
      [*] = ;         end;
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (elmName='worldrule') then
      [*] = ;begin
      [*] = ;   var elmListBoxHandle : Integer = _gui_GetWindow('NewGame.worldrule');
      [*] = ;   var i : Integer = GetGUIListBoxItemTag(elmListBoxHandle, GetGUIListBoxItemIndex(elmListBoxHandle));
      [*] = ;   gMapSettings.worldrule := i;
      [*] = ;   if (i=9) then // Guarded world
      [*] = ;   begin
      [*] = ;      gMapSettings.size := 2;
      [*] = ;      gMapSettings.players := 2;
      [*] = ;      GUIExecuteState('ShowNewGame');
      [*] = ;   end;
      [*] = ;   LanUpdateShardRoomInfo();
      [*] = ;end
      [*] = ;else}
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if _log then _Log_gui('EventNewGame');
      [*] = ;   if (elmName='arrowSliderLeft') or (elmName='arrowSliderRight') then
      [*] = ;   begin
      [*] = ;      var elmSliderHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;
      [*] = ;      if StrExists(sliderID, 'playerid.') then
      [*] = ;      begin
      [*] = ;         var index : Integer = StrToInt(StrReplace(sliderID, 'playerid.', ''));
      [*] = ;         var value : Integer = gMapSettings.arrplayers[index].id;
      [*] = ;         if (elmName='arrowSliderLeft') then
      [*] = ;            value := FindNextFreePlayerID(value, false, true)
      [*] = ;         else
      [*] = ;            value := FindNextFreePlayerID(value, true, true);
      [*] = ;         var maxValue : Integer = gc_MaxCustomMapPlayer;
      [*] = ;         if (value>maxValue) then value := 0;
      [*] = ;         if (value<0) then value := maxValue;
      [*] = ;         gMapSettings.arrplayers[index].id := value;
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;         GUIExecuteState('ShowNewGame');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if StrExists(sliderID, 'playerdiff.') then
      [*] = ;      begin
      [*] = ;         var index : Integer = StrToInt(StrReplace(sliderID, 'playerdiff.', ''));
      [*] = ;         var value : Integer = gMapSettings.arrplayers[index].advdiff.basediff;
      [*] = ;         if (index=0) and (gProfileTmp.advdiff.custom) then
      [*] = ;            gProfileTmp.advdiff.custom := false
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var maxValue : Integer = 6;
      [*] = ;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;               value := value-1
      [*] = ;            else
      [*] = ;               value := value+1;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;         end;
      [*] = ;         var text : String = 'difficulty|'+IntToStr(value);
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, value, 7, text, false);
      [*] = ;         gMapSettings.arrplayers[index].advdiff.basediff := value;
      [*] = ;         gMapSettings.arrplayers[index].advdiff.custom := false;
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (sliderID='size') then
      [*] = ;      begin
      [*] = ;         var maxValue : Integer = 7;
      [*] = ;         var value : Integer = gMapSettings.size;
      [*] = ;         if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;         else
      [*] = ;            value := value+1;
      [*] = ;         if (value>maxValue) then value := 0;
      [*] = ;         if (value<0) then value := maxValue;
      [*] = ;         var text : String = 'shard|'+IntToStr(value);
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, value, 8, text, false);
      [*] = ;         gMapSettings.size := value;
      [*] = ;         if (gMapSettings.worldrule=9) then
      [*] = ;            gMapSettings.worldrule := 0;
      [*] = ;
      [*] = ;         if (elmName='arrowSliderLeft') then
      [*] = ;         begin
      [*] = ;            var curPlCount : Integer = gMapSettings.players;
      [*] = ;            case value of
      [*] = ;               0 : begin
      [*] = ;                  if (curPlCount>0) then
      [*] = ;                     curPlCount := 0;
      [*] = ;               end;
      [*] = ;               1 : begin
      [*] = ;                  if (curPlCount>1) then
      [*] = ;                     curPlCount := 1;
      [*] = ;               end;
      [*] = ;               2 : begin
      [*] = ;                  if (curPlCount>3) then
      [*] = ;                     curPlCount := 3;
      [*] = ;               end;
      [*] = ;               3 : begin
      [*] = ;                  if (curPlCount>6) then
      [*] = ;                     curPlCount := 6;
      [*] = ;               end;
      [*] = ;               4 : begin
      [*] = ;                  if (curPlCount>9) then
      [*] = ;                     curPlCount := 9;
      [*] = ;               end;
      [*] = ;               5 : begin
      [*] = ;                  if (curPlCount>12) then
      [*] = ;                     curPlCount := 12;
      [*] = ;               end;
      [*] = ;               6 : begin
      [*] = ;                  if (curPlCount>14) then
      [*] = ;                     curPlCount := 14;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gMapSettings.players := curPlCount;
      [*] = ;         end;
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;         GUIExecuteState('ShowNewGame');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (sliderID='players') then
      [*] = ;      begin
      [*] = ;         var value : Integer = gMapSettings.players;
      [*] = ;         if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;         else
      [*] = ;            value := value+1;
      [*] = ;         var maxValue : Integer = gc_MaxCustomMapPlayer-2;
      [*] = ;         if (value>maxValue) then value := 0;
      [*] = ;         if (value<0) then value := maxValue;
      [*] = ;
      [*] = ;         if (elmName='arrowSliderRight') and (not IsPlayerIDUnique(gMapSettings.arrplayers[value+1].id)) then
      [*] = ;            gMapSettings.arrplayers[value+1].id := 0;
      [*] = ;
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, value, 15, IntToStr(value+2), false);
      [*] = ;         gMapSettings.players := value;
      [*] = ;         if (gMapSettings.worldrule=9) then
      [*] = ;            gMapSettings.worldrule := 0; //reset world rule if changes are made for guarded world
      [*] = ;
      [*] = ;         if (elmName='arrowSliderRight') then
      [*] = ;         begin
      [*] = ;            var curSize : Integer = gMapSettings.size;
      [*] = ;            case value of
      [*] = ;               13..14 : begin
      [*] = ;                  if (curSize<6) then
      [*] = ;                     curSize := 6;
      [*] = ;               end;
      [*] = ;               10..12 : begin
      [*] = ;                  if (curSize<5) then
      [*] = ;                     curSize := 5;
      [*] = ;               end;
      [*] = ;               7..9 : begin
      [*] = ;                  if (curSize<4) then
      [*] = ;                     curSize := 4;
      [*] = ;               end;
      [*] = ;               4..6 : begin
      [*] = ;                  if (curSize<3) then
      [*] = ;                     curSize := 3;
      [*] = ;               end;
      [*] = ;               2,3 : begin
      [*] = ;                  if (curSize<2) then
      [*] = ;                     curSize := 2;
      [*] = ;               end;
      [*] = ;               1 : begin
      [*] = ;                  if (curSize<1) then
      [*] = ;                     curSize := 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gMapSettings.size := curSize;
      [*] = ;         end;
      [*] = ;         //_gui_DelayExecuteStateOneInstance('ShowNewGame', 0.01);
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;         GUIExecuteState('ShowNewGame');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (sliderID='worldrule') then
      [*] = ;      begin
      [*] = ;         var wr_no, j, i : Integer = 0;
      [*] = ;         for i:=0 to gPrototypeData.worldrules.number-1 do
      [*] = ;         begin
      [*] = ;            j := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.worldrules.handle, i), 'WorldRuleID');
      [*] = ;            if (j>=0) then
      [*] = ;            begin
      [*] = ;               wr_no := wr_no + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         var value : Integer = gMapSettings.worldrule;
      [*] = ;         if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;         else
      [*] = ;            value := value+1;
      [*] = ;         var maxValue : Integer = wr_no;
      [*] = ;         if (value>maxValue) then value := 0;
      [*] = ;         if (value<0) then value := maxValue;
      [*] = ;
      [*] = ;
      [*] = ;         var text : String = 'worldrule|'+IntToStr(value);
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, value, maxValue, text, false);
      [*] = ;         gMapSettings.worldrule := value;
      [*] = ;         if (gMapSettings.worldrule=9) then
      [*] = ;         begin
      [*] = ;            gMapSettings.size := 2;
      [*] = ;            gMapSettings.players := 2;
      [*] = ;         end;
      [*] = ;
      [*] = ;         //_gui_DelayExecuteStateOneInstance('ShowNewGame', 0.01);
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;         GUIExecuteState('ShowNewGame');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   case tag of
      [*] = ;      cBtnCustomDifficultyTag : begin
      [*] = ;         _misc_AssignGlobalVars('gProfile', 'gProfileTmp');
      [*] = ;         if (not gMapSettings.arrplayers[0].advdiff.custom) then
      [*] = ;            _map_SetGameCustomDifficultyOptionsDefault(gMapSettings.arrplayers[0].advdiff, False, gMapSettings.arrplayers[0].advdiff.basediff);
      [*] = ;         BoolRegister0 := True;
      [*] = ;         GUIExecuteState('ShowCustomDifficulty');
      [*] = ;      end;
      [*] = ;      cBtnKickPlayer : begin
      [*] = ;         var elmParentHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;         var index : Integer = GetGUIElementTag(elmParentHandle);
      [*] = ;         LanKillClient(gLanShardGame.arrlanplayers[index].lanid);
      [*] = ;         gLanShardGame.arrlanplayers[index].lanid := 0;
      [*] = ;         _inet_ClearHotseatProfile(gLanShardGame.arrlanplayers[index].profile);
      [*] = ;         GUIExecuteState('ShowNewGame');
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;      end;
      [*] = ;      cBtnSetupPlayerProfile : begin
      [*] = ;         var elmParentHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;         var index : Integer = GetGUIElementTag(elmParentHandle);
      [*] = ;         gIntRegister_ShardHotSeatActivePlayer := index;
      [*] = ;         _inet_AssignHotseatProfile(gArrHotseatProfiles[gIntRegister_ShardHotSeatActivePlayer], gHotseatProfileTmp);
      [*] = ;         GUIExecuteState('ShowHotseatProfile');
      [*] = ;      end;
      [*] = ;      cBtnSwitchControlModeToHuman : begin
      [*] = ;         var elmParentHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;         var index : Integer = GetGUIElementTag(elmParentHandle);
      [*] = ;         gMapSettings.arrplayers[index].control := 1;
      [*] = ;         RearrangeHumanSlots(index);
      [*] = ;         GUIExecuteState('ShowNewGame');
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;      end;
      [*] = ;      cBtnSwitchControlModeToAI : begin
      [*] = ;         var elmParentHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;         var index : Integer = GetGUIElementTag(elmParentHandle);
      [*] = ;         gMapSettings.arrplayers[index].control := 0;
      [*] = ;         GUIExecuteState('ShowNewGame');
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;      end;
      [*] = ;      cBtnAcceptTag : begin
      [*] = ;         const cMapName = 'global.map';
      [*] = ;         var zoneName : String = 'Default';
      [*] = ;         const cPresetName = 'Default';
      [*] = ;
      [*] = ;         gIntRegister_CurGameMode := gc_GameModeStrategy;
      [*] = ;
      [*] = ;         var randKey0, randKey1 : Integer;
      [*] = ;         if (gMapEditor.enabled) then
      [*] = ;         begin
      [*] = ;            _editor_LoadMapDataFromFile('gMapEditor');
      [*] = ;            randKey0 := gMapEditor.randkey0;
      [*] = ;            randKey1 := gMapEditor.randkey1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            GenerateMapRandKey(randKey0, randKey1);
      [*] = ;         if _log then _log_gui('randKey0 = '+IntToStr(randKey0)+', randKey1 = '+IntToStr(randKey1));
      [*] = ;         SetRandomExtKey64(randKey0, randKey1);
      [*] = ;         SetMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;         SetGlobalMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;
      [*] = ;         GetRandomExtKey64(gMapEditor.randkey0, gMapEditor.randkey1); // Store randkey to future map editor regen map
      [*] = ;
      [*] = ;         var iSeed : Integer = randKey1 mod gc_MaxSeedValue;
      [*] = ;
      [*] = ;         var mapSize : Integer = 32;
      [*] = ;         var i : Integer;
      [*] = ;         var iMapSize : Integer = gMapSettings.size*2+6;
      [*] = ;
      [*] = ;         if (gMapEditor.enabled) then
      [*] = ;            iMapSize := gMapEditor.map.x;
      [*] = ;
      [*] = ;         const HEX_WIDTH = 10.575;
      [*] = ;         var shardWidth : Float = HEX_WIDTH*(iMapSize+2);
      [*] = ;         var shardHeight : Float = shardWidth*0.885;
      [*] = ;         var MapWidth : Integer = 40+130+Round(shardWidth);
      [*] = ;         while (MapWidth>mapSize) do
      [*] = ;            mapSize := mapSize+32;
      [*] = ;
      [*] = ;         MapWidth := mapSize;
      [*] = ;         mapSize := 32;
      [*] = ;         var MapHeight : Integer = 40+90+Round(shardHeight);
      [*] = ;         while (MapHeight>mapSize) do
      [*] = ;            mapSize := mapSize+32;
      [*] = ;         MapHeight := mapSize;
      [*] = ;
      [*] = ;         var bHotseat : Boolean = (gGame.gameType=gc_GameTypeHotseat);
      [*] = ;         var bInet : Boolean = (gGame.gametype=gc_GameTypeLanShard);
      [*] = ;         if (bInet) and (bHotseat) then
      [*] = ;            bHotseat := False;
      [*] = ;         if (bHotseat) or (bInet) then
      [*] = ;         begin
      [*] = ;            for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;               gMapSettings.arrplayers[i].advdiff.custom := False;
      [*] = ;         end;
      [*] = ;         for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;         begin
      [*] = ;            if (not gMapSettings.arrplayers[i].advdiff.custom) then
      [*] = ;               _map_SetGameCustomDifficultyOptionsDefault(gMapSettings.arrplayers[i].advdiff, False, gMapSettings.arrplayers[i].advdiff.basediff);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (GetLanMode()>=2) then
      [*] = ;         begin
      [*] = ;            SaveSettingsToProfile();
      [*] = ;            DoInetShardGame(randKey0, randKey1);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if gGame.gameType <> gc_GameTypeLanShard then
      [*] = ;               SaveSettingsToProfile();
      [*] = ;            
      [*] = ;            _misc_CreateStratMapParser(iSeed);
      [*] = ;
      [*] = ;            // world rule - need after CreateStratMapParser, cause it setup gGame.worldrule
      [*] = ;            if _worldrule_GetWorldRuleVisualExistByID(3) then
      [*] = ;            begin
      [*] = ;               case _worldrule_GetWorldRuleVisualParams(3, 1) of
      [*] = ;                  1 : zoneName := 'Crystals';
      [*] = ;                  2 : zoneName := 'Desert';
      [*] = ;                  3 : zoneName := 'Deadland';
      [*] = ;                  4 : zoneName := 'Autumn';
      [*] = ;                  5 : zoneName := 'Vulcan';
      [*] = ;                  6 : zoneName := 'Ice';
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            StateMachineClearVariables(GetMapInitMachineHandle());
      [*] = ;            gTutorial.map := false;
      [*] = ;            GenerateMapNeededExtBorder(cMapName, zoneName, cPresetName, MapWidth, MapHeight, 5, randKey0, randKey1, 0, 0, 0, '', '', '', '', '', '', '.\data\gui\gui.cfg', ''{'GUIInitialize'}, 'Ingame1', '', 'MakeStratHexGrid', false);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         if (gGame.gametype=gc_GameTypeLanShard) then
      [*] = ;         begin
      [*] = ;            LanTerminateGame();
      [*] = ;            GUIExecuteState('ShowInternetShell');
      [*] = ;            _inet_UpdateShardGamesList('internetshell.leftpanel.shardgames.list');
      [*] = ;            _inet_UpdateClientsList('internetshell.rightpanel.players.list', 0);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gGame.gametype := gc_GameTypeNone;
      [*] = ;         end;
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('NewGame'),gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;      cGeneratorSettingsBtnTag : begin
      [*] = ;         _misc_AssignGlobalVars('gMapSettings', 'gMapSettingsTmp');
      [*] = ;         GUIExecuteState('ShowMapGeneratorSettings');
      [*] = ;      end;
      [*] = ;      cGeneratorRandomBtnTag : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         gMapSettings.random := bChecked;
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;         
      [*] = ;         MakeRandomGame();
      [*] = ;         GUIExecuteState('ShowNewGame');
      [*] = ;         LanUpdateShardRoomInfo();
      [*] = ;      end;
      [*] = ;      cGameplayBtnTag : begin
      [*] = ;         _misc_AssignGlobalVars('gMapSettings', 'gMapSettingsTmp');
      [*] = ;         StringRegister0 := 'Gameplay Settings';
      [*] = ;         GUIExecuteState('CreateWindowFromParser');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

