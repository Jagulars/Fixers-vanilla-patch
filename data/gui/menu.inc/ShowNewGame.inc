section.begin
   Name = ShowNewGame
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\SHOWNEWGAME';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
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
      [*] = ;const cEventState = 'EventNewGame';
      [*] = ;
      [*] = ;function CreateIntPortraitSlider(SliderID : String; value, parentElement : Integer; hAlign, vAlign : String; posX, posY : Integer; eventState, hint : String; cycle : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var sliderWidth : Integer = 106;
      [*] = ;   var elmSliderHandle : Integer = _gui_CreateImage('slider', parentElement, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX, posY, sliderWidth, 45, 0);
      [*] = ;   SetGUIElementStringTag(elmSliderHandle, sliderID);
      [*] = ;   var portrait : String = 'astral.players.icon.small.'+IntToStr(value);
      [*] = ;   var elmSliderPortrait : Integer = _gui_CreateImage('portraitSlider', elmSliderHandle, portrait, 'halParentLeft', 'valParentTop', 10, -23, 0, 0, 0);
      [*] = ;   SetGUIAllowEvents(elmSliderPortrait, True, False, False);
      [*] = ;   SetGUIElementHint(elmSliderPortrait, hint);
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', elmSliderHandle, 'gamepanel03.constructor.portrait.frame', 'halParentLeft', 'valParentTop', -50, -49, 0, 0, 0);
      [*] = ;   var elmBtnArrowLeftHandle : Integer = _gui_CreateButton('arrowSliderLeft', elmSliderHandle, '', 'gamepanel01.btn.arrow.left', 'halParentLeft', 'valParentTop', -6-34, -5-55, 0, 0, eventState, '', 0);
      [*] = ;   var elmBtnArrowRightHandle : Integer = _gui_CreateButton('arrowSliderRight', elmSliderHandle, '', 'gamepanel01.btn.arrow.right', 'halParentLeft', 'valParentTop', -6+sliderWidth-31+29, -5-55, 0, 0, eventState, '', 0);
      [*] = ;   Result := elmSliderHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;var sameGameVersion : Boolean = true;
      [*] = ;
      [*] = ;function AcceptEnabled(bMaster,bInet,bHotSeat : Boolean; var pno : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := true;
      [*] = ;   pno := 1;
      [*] = ;   if (bInet) or (bHotSeat) then
      [*] = ;   begin
      [*] = ;      var p : Integer = 0;
      [*] = ;      var i,empty_id : Integer;
      [*] = ;      var myModVersion : String = gc_DataModName + '_' + gc_DataModVersion;
      [*] = ;
      [*] = ;      empty_id := 0;
      [*] = ;      for i := 1 to (gMapSettings.players+2-1) do
      [*] = ;      begin
      [*] = ;         if (gMapSettings.arrplayers[i].control=1) then 
      [*] = ;         begin
      [*] = ;            pno := pno + 1;
      [*] = ;            if (bInet) then
      [*] = ;            begin
      [*] = ;               var playerLanID : Integer = gLanShardGame.arrlanplayers[i].lanid;
      [*] = ;               if (playerLanID<>0) then
      [*] = ;               begin
      [*] = ;                  p := p + 1;
      [*] = ;                     
      [*] = ;                  if sameGameVersion then
      [*] = ;                     sameGameVersion := _inet_IsSameVersionByID(playerLanID, myModVersion);
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  empty_id := empty_id + 1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               p := p + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if _log then _Log_gui('Human players: '+IntToStr(p+1)+'/'+IntToStr(pno));
      [*] = ;      if (p=0) or ((bInet) and ((p > (gc_MaxLanMapHumanPlayers-1)) or (empty_id <> 0))) or (not bMaster) or (not sameGameVersion) then
      [*] = ;         Result := false;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var bHotseat : Boolean = ((gGame.gameType=gc_GameTypeHotseat) and (gGame.gametype <> gc_GameTypeLanShard));
      [*] = ;var bInet : Boolean = (gGame.gametype=gc_GameTypeLanShard);
      [*] = ;var fontHandle, fontHandleH : String;
      [*] = ;var fontHandleS : String;
      [*] = ;var offsetY768 : Integer = 0;
      [*] = ;var elmSliderHandle, intValue,elmHandle : Integer;
      [*] = ;var text : String;
      [*] = ;var bMaster : Boolean = (not bInet) or bHotSeat or ((bInet) and (GetLanMode()>=2));
      [*] = ;var bVisible : Boolean = False;
      [*] = ;var no_ai_button : Boolean;
      [*] = ;var elmParentHandle : Integer = _gui_GetWindow('NewGame');
      [*] = ;var i,elmListBoxHandle,wr_no : Integer;
      [*] = ;var wr_array : array [0..gc_max_worldrules] of Integer;
      [*] = ;var pPlayers : Integer = gPrototypeData.players.handle;
      [*] = ;var playerCount : Integer = gMapSettings.players+2;
      [*] = ;var j,avatar,id,sign,color1,color2,pno,cpno,enum: Integer;
      [*] = ;var playerName,material,hint,sliderID : String;
      [*] = ;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle); // HeaderL
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text', gc_gui_fontsize_largest,'',fontHandleH); // HeaderL
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandleS);
      [*] = ;
      [*] = ;if (gGame.gametype=gc_GameTypeLanShard) and (not IsLanPublicServerMode()) then
      [*] = ;   ErrorLogI('gLanShardGame conflict IsLanPublicServerMode');
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;if (elmParentHandle<>0) and GetGUIElementVisible(elmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;if (_gui_RootWindowGetBaseScaleY()<>1) then
      [*] = ;   offsetY768 := -17;
      [*] = ;elmParentHandle := _gui_CreateLargeWindow(0, 'NewGame', 'halParentMiddle', 'valParentMiddle', 0, offsetY768, 1218, 816, true);
      [*] = ;_gui_RootWindowAddExt(elmParentHandle,cRootWindowModal,0,cRootWindowAttrScaleByY,cEventState);
      [*] = ;
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.9);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 1);
      [*] = ;elmHandle := GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;if (elmHandle<>0) then
      [*] = ;begin
      [*] = ;   SetGUIElementMaterial(elmHandle, 'element.header.strip.629');
      [*] = ;   SetGUIElementAllPositionRect(elmHandle, 0, -53, 629, 90);
      [*] = ;   _gui_CreateText('', elmHandle, 'menu|21', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandleH, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentTop', 341-3, 581+5, 0, 0, 0);
      [*] = ;elmHandle := _gui_CreateButton('menu_newcustomgame_btnAccept', elmHandle, '', 'mainpanel.btn.accept', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.1', cBtnAcceptTag);
      [*] = ;if (not AcceptEnabled(bMaster,bInet,bHotseat,pno)) then
      [*] = ;begin
      [*] = ;   SetGUIElementEnabled(elmHandle, False);
      [*] = ;   if not sameGameVersion then
      [*] = ;      SetGUIElementHint(elmHandle, 'menu|multiplayer_version_reminder');
      [*] = ;end;
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentTop', 341+423-3, 581+5, 0, 0, 0);
      [*] = ;_gui_CreateButton('menu_newcustomgame_btnCancel', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'gui|211', cBtnCancelTag);
      [*] = ;
      [*] = ;
      [*] = ;// world creation settings
      [*] = ;elmHandle := _gui_CreateButton('Settings', elmParentHandle, '', 'common.btn', 'halParentLeft', 'valParentTop', 512-16, 510, 0, 0, cEventState, '', cGeneratorSettingsBtnTag);
      [*] = ;_gui_CreateText('', elmHandle, 'gui|356', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;if (gMapSettings.random) then
      [*] = ;begin
      [*] = ;   SetGUIElementHint(elmHandle, 'gui|230');
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.35);
      [*] = ;   SetGUIAllowEvents(elmHandle, False, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;// gameplay settings
      [*] = ;elmHandle := _gui_CreateButton('btnGameplaySettings', elmParentHandle, '', 'common.btn', 'halParentLeft', 'valParentTop', 512-16, 510+(GetGUIElementHeight(elmHandle)-4), 0, 0, cEventState, '', cGameplayBtnTag);
      [*] = ;_gui_CreateText('', elmHandle, 'menu|89', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;// randomize button
      [*] = ;{elmHandle := _gui_CreateButton('Random', elmParentHandle, '', 'common.btn', 'halParentLeft', 'valParentTop', 512-16, 600, 0, 0, cEventState, '', cGeneratorRandomBtnTag);
      [*] = ;_gui_CreateText('', elmHandle, 'gui|230', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;if not bMaster then
      [*] = ;   SetGUIAllowEvents(elmHandle, False, False, False);}
      [*] = ;elmHandle := _gui_CreateCheckBox('Random', elmParentHandle, gMapSettings.random, 'gui|230', 'halParentLeft', 'valParentTop', 516, 510+(GetGUIElementHeight(elmHandle)-4)*2+10, cEventState, '', cGeneratorRandomBtnTag);
      [*] = ;if (not bMaster) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.35);
      [*] = ;   SetGUIAllowEvents(elmHandle, False, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// Bottom background
      [*] = ;var yOff : Integer = -30+24-4-20;
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'gamepanel03.bottom.background.3', 'halParentMiddle', 'valParentMiddle', 0, -40+yOff div 2, 0, 0, 0);
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;SetGUIElementUserColor(elmHandle, 1, 1, 1, 0.75);
      [*] = ;
      [*] = ;if (_gui_RootWindowGetBaseScaleY()<>1) then
      [*] = ;   yOff := yOff-66;
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentLeft', 'valParentTop', 264+31-46, 470+yOff, 0, 0, 0);
      [*] = ;_gui_CreateText('', elmHandle, 'menu|24', 'halParentLeft', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentLeft', 'valParentTop', 264+31-46+243*2, 470+yOff, 0, 0, 0);
      [*] = ;_gui_CreateText('', elmHandle, 'menu|25', 'halParentLeft', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentLeft', 'valParentTop', 264+31-46+243*1, 470+yOff, 0, 0, 0);
      [*] = ;_gui_CreateText('', elmHandle, 'gui|682', 'halParentLeft', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;
      [*] = ;wr_no := 0;
      [*] = ;for i:=0 to gPrototypeData.worldrules.number-1 do
      [*] = ;begin
      [*] = ;   j := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.worldrules.handle, i), 'WorldRuleID');
      [*] = ;   if (j>=0) then
      [*] = ;   begin
      [*] = ;      wr_array[wr_no] := i;
      [*] = ;      wr_no := wr_no + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// Players
      [*] = ;cpno := 0;
      [*] = ;enum := 0;
      [*] = ;no_ai_button := true;
      [*] = ;for i:=0 to 4 do
      [*] = ;begin
      [*] = ;   for j:=0 to 4 do
      [*] = ;   begin
      [*] = ;      if (j>0) and (j<4) and (i>0) and (i<4) then
      [*] = ;         continue;
      [*] = ;
      [*] = ;      var bActive : Boolean = enum<=(playerCount-1);
      [*] = ;      var posX : Integer = 4+(242)*j;
      [*] = ;      var posY : Integer = 33+156*i;
      [*] = ;      var elmPlayerHandle : Integer = _gui_CreateImage('player', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX, posY, 230, 146, enum);
      [*] = ;
      [*] = ;      elmHandle := _gui_CreateImage('', elmPlayerHandle, 'element.strip.240', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;      if (bActive) then
      [*] = ;      begin
      [*] = ;         if (bInet) then
      [*] = ;         begin
      [*] = ;            if (gMapSettings.arrplayers[enum].control=1) then
      [*] = ;            begin
      [*] = ;               if (gLanShardGame.arrlanplayers[enum].lanid<>0) then
      [*] = ;                  playerName := gLanShardGame.arrlanplayers[enum].profile.name
      [*] = ;               else
      [*] = ;                  playerName := 'gui|766';
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (gMapSettings.arrplayers[enum].id=0) then
      [*] = ;                  playerName := 'gui|230'
      [*] = ;               else
      [*] = ;                  playerName := 'players|'+IntToStr(gMapSettings.arrplayers[enum].id);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (enum=0) then
      [*] = ;               playerName := gProfile.name
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (bHotseat) and (gMapSettings.arrplayers[enum].control=1) then
      [*] = ;                  playerName := gArrHotseatProfiles[enum].name
      [*] = ;               else
      [*] = ;                  if (gMapSettings.arrplayers[enum].id=0) then
      [*] = ;                     playerName := 'gui|230'
      [*] = ;                  else
      [*] = ;                     playerName := 'players|'+IntToStr(gMapSettings.arrplayers[enum].id);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         _gui_CreateText('', elmHandle, playerName, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;         if (bInet) then
      [*] = ;            avatar := gLanShardGame.arrlanplayers[enum].profile.avatar
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (enum=0) then
      [*] = ;               avatar := gProfile.avatar
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (bHotseat) and (gMapSettings.arrplayers[enum].control=1) then
      [*] = ;                  avatar := gArrHotseatProfiles[enum].avatar
      [*] = ;               else
      [*] = ;                  avatar := 0;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (enum=0) or ((bHotseat) and (gMapSettings.arrplayers[enum].control=1)) or ((bInet) and (gMapSettings.arrplayers[enum].control=1) and (gLanShardGame.arrlanplayers[enum].lanid<>0)) then
      [*] = ;         begin
      [*] = ;            var elmSliderPortrait : Integer = _gui_CreateImage('portraitSlider', elmPlayerHandle, 'astral.players.icon.small.'+IntToStr(avatar), 'halParentLeft', 'valParentTop', 75+10, 57-23, 0, 0, 0);
      [*] = ;            _gui_CreateImage('', elmPlayerHandle, 'gamepanel03.constructor.portrait.frame', 'halParentLeft', 'valParentTop', 75-50, 57-49, 0, 0, 0);
      [*] = ;            SetGUIAllowEvents(elmSliderPortrait, True, False, False);
      [*] = ;            SetGUIElementHint(elmSliderPortrait, 'menu|41');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            sliderID := 'playerid.'+IntToStr(enum);
      [*] = ;            id := gMapSettings.arrplayers[enum].id;
      [*] = ;
      [*] = ;            if (bInet) and (gMapSettings.arrplayers[enum].control=1) then
      [*] = ;               id := 0;
      [*] = ;            if (id>0) then
      [*] = ;               hint := GetLocaleTableListItemByID('players', IntToStr(id)) + ' - ' + GetLocaleTableListItemByID('players', IntToStr(id)+'.hint')
      [*] = ;            else
      [*] = ;               hint := 'menu|40';
      [*] = ;            elmSliderHandle := CreateIntPortraitSlider(sliderID, id, elmPlayerHandle, 'halParentLeft', 'valParentTop', 75, 57, cEventState, hint, True);
      [*] = ;            if (gMapSettings.arrplayers[enum].control=1) and (gLanShardGame.arrlanplayers[enum].lanid=0) then
      [*] = ;               SetGUIElementUserBlend(elmSliderHandle, 0.25);
      [*] = ;            if (not bMaster) or ((bInet) and (gMapSettings.arrplayers[enum].control=1)) then
      [*] = ;            begin
      [*] = ;               SetGUIElementVisible(GetGUIElementIndexByNameParent('arrowSliderLeft', elmSliderHandle), False);
      [*] = ;               SetGUIElementVisible(GetGUIElementIndexByNameParent('arrowSliderRight', elmSliderHandle), False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (not ((i=0) and (j=0))) and ((bHotseat) or ((bInet) and (bMaster))) then
      [*] = ;         begin
      [*] = ;            if (gMapSettings.arrplayers[enum].control=0) then begin
      [*] = ;               if ((enum < (gc_MaxLanMapHumanPlayers)) and no_ai_button) or (not bInet) then
      [*] = ;               begin
      [*] = ;                  _gui_CreateButton('', elmPlayerHandle, '', 'map.mainpanel.btn.statistics', 'halParentLeft', 'valParentTop', 133, 30, 41, 41, cEventState, 'gui|763', cBtnSwitchControlModeToHuman);
      [*] = ;                  no_ai_button := false;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               cpno := cpno+1;
      [*] = ;               if (bInet) and (gLanShardGame.arrlanplayers[enum].lanid<>0) then
      [*] = ;                  _gui_CreateButton('', elmPlayerHandle, '', 'interface.circle.destroy', 'halParentLeft', 'valParentTop', 133, 30, 38, 38, cEventState, 'gui|765', cBtnKickPlayer)
      [*] = ;               else
      [*] = ;               if enum > 1 then
      [*] = ;                  _gui_CreateButton('', elmPlayerHandle, '', 'map.mainpanel.btn.nexthero', 'halParentLeft', 'valParentTop', 133, 30, 41, 41, cEventState, 'gui|762', cBtnSwitchControlModeToAI);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if (bHotseat) and (gMapSettings.arrplayers[enum].control=1) then
      [*] = ;               _gui_CreateButton('', elmPlayerHandle, '', 'gamepanel01.herorecruit.list.btn.heroinfo', 'halParentLeft', 'valParentTop', 69, 30, 41, 41, cEventState, 'gui|764', cBtnSetupPlayerProfile);
      [*] = ;         end;
      [*] = ;
      [*] = ;         id := ParserSelectByHandleByIndex(pPlayers, gMapSettings.arrplayers[enum].id);
      [*] = ;         if (enum=0) then
      [*] = ;         begin
      [*] = ;            if (bInet) then
      [*] = ;            begin
      [*] = ;               sign := gLanShardGame.arrlanplayers[enum].profile.sign;
      [*] = ;               color1 := gLanShardGame.arrlanplayers[enum].profile.color1;
      [*] = ;               color2 := gLanShardGame.arrlanplayers[enum].profile.color2;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               sign := gProfile.sign;
      [*] = ;               color1 := gProfile.color1;
      [*] = ;               color2 := gProfile.color2;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (bInet) and (gMapSettings.arrplayers[enum].control=1) then
      [*] = ;         begin
      [*] = ;            if (gLanShardGame.arrlanplayers[enum].lanid<>0) then
      [*] = ;            begin
      [*] = ;               sign := gLanShardGame.arrlanplayers[enum].profile.sign;
      [*] = ;               color1 := gLanShardGame.arrlanplayers[enum].profile.color1;
      [*] = ;               color2 := gLanShardGame.arrlanplayers[enum].profile.color2;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               sign := -1;
      [*] = ;               color1 := -1;
      [*] = ;               color2 := -1;
      [*] = ;            end
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (bHotseat) and (gMapSettings.arrplayers[enum].control=1) then
      [*] = ;         begin
      [*] = ;            sign := gArrHotseatProfiles[enum].sign;
      [*] = ;            color1 := gArrHotseatProfiles[enum].color1;
      [*] = ;            color2 := gArrHotseatProfiles[enum].color2;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (gMapSettings.arrplayers[enum].id=0) then
      [*] = ;            begin
      [*] = ;               sign := -1;
      [*] = ;               color1 := -1;
      [*] = ;               color2 := -1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               sign := ParserGetIntValueByKeyByHandle(id, 'Herb');
      [*] = ;               color1 := ParserGetIntValueByKeyByHandle(id, 'Color1');
      [*] = ;               color2 := ParserGetIntValueByKeyByHandle(id, 'Color2');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         elmHandle := _gui_CreateHerb('', elmPlayerHandle, sign, color1, color2, 'halParentLeft', 'valParentTop', 12, 42);
      [*] = ;         if (bInet) and (gMapSettings.arrplayers[enum].control=1) and (gLanShardGame.arrlanplayers[enum].lanid=0) then
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;         elmHandle := _gui_CreateHerb('', elmPlayerHandle, sign, color1, color2, 'halParentLeft', 'valParentTop', 12+162, 42);
      [*] = ;         if (bInet) and (gMapSettings.arrplayers[enum].control=1) and (gLanShardGame.arrlanplayers[enum].lanid=0) then
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;
      [*] = ;         if (enum=0) then
      [*] = ;            hint := GetLocaleTableListItemByID('gui', '218')+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('menu', '36')
      [*] = ;         else
      [*] = ;            hint := GetLocaleTableListItemByID('gui', '218')+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('menu', '37');
      [*] = ;         sliderID := 'playerdiff.'+IntToStr(enum);
      [*] = ;         elmSliderHandle := _gui_CreateIntSlider(sliderID, elmPlayerHandle, 'halParentLeft', 'valParentTop', 8, 111, 228, cEventState, hint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         intValue := gMapSettings.arrplayers[enum].advdiff.basediff;
      [*] = ;         text := 'difficulty|'+IntToStr(intValue);
      [*] = ;         if (gMapSettings.arrplayers[enum].advdiff.custom) and (not bInet) and (not bHotSeat) and (enum=0) then
      [*] = ;            text := 'gui|767';
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, intValue, 7, text, false);
      [*] = ;         if (not bMaster) then
      [*] = ;         begin
      [*] = ;            SetGUIElementEnabled(GetGUIElementIndexByNameParent('arrowSliderLeft', elmSliderHandle), False);
      [*] = ;            SetGUIElementEnabled(GetGUIElementIndexByNameParent('arrowSliderRight', elmSliderHandle), False);
      [*] = ;         end;
      [*] = ;         if (not bInet) and (not bHotSeat) and (enum=0) then
      [*] = ;            _gui_CreateButton('btnCustomDifficulty', elmSliderHandle, '', 'tempshell.journal', 'halParentRight', 'valParentMiddle', -66+8, -4, 27, 27, cEventState, 'gui|806', cBtnCustomDifficultyTag);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.35);
      [*] = ;
      [*] = ;         material := 'gamepanel03.constructor.portrait.frame.gray';
      [*] = ;         _gui_CreateImage('', elmPlayerHandle, material, 'halParentLeft', 'valParentTop', 25, 8, 0, 0, 0);
      [*] = ;
      [*] = ;         material := 'gamepanel03.shield.gray';
      [*] = ;         _gui_CreateImage('', elmPlayerHandle, material, 'halParentLeft', 'valParentTop', 12, 42, 0, 0, 0);
      [*] = ;         _gui_CreateImage('', elmPlayerHandle, material, 'halParentLeft', 'valParentTop', 12+162, 42, 0, 0, 0);
      [*] = ;
      [*] = ;         var sliderWidth : Integer = 240-14;
      [*] = ;         elmSliderHandle := _gui_CreateImage('slider', elmPlayerHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 7, 111, sliderWidth, 45, 0);
      [*] = ;         _gui_CreateImage('', elmSliderHandle, 'common.slider.left.end', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;         _gui_CreateImage('', elmSliderHandle, 'common.slider.right.end', 'halParentLeft', 'valParentTop', sliderWidth-GetGUITextureWidth('common.slider.right.end'), 0, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateScrollLayer(elmSliderHandle, 'common.slider.middle', 'halParentLeft', 'valParentTop', GetGUITextureWidth('common.slider.left.end'), 0, sliderWidth-GetGUITextureWidth('common.slider.left.end')-GetGUITextureWidth('common.slider.right.end'), 0);
      [*] = ;         SetGUIElementUserBlend(GetGUIElementIndexByNameParent('material', elmHandle), 0.1);
      [*] = ;         if (not bActive) then
      [*] = ;            SetGUIElementUserBlend(elmPlayerHandle, 0.1);
      [*] = ;      end;
      [*] = ;      enum := enum+1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;        
      [*] = ;
      [*] = ;intValue := gMapSettings.size;
      [*] = ;
      [*] = ;var hexes : String = IntToStr(6 + intValue * 2);
      [*] = ;hint := hexes+' x '+hexes;
      [*] = ;text := 'shard|'+IntToStr(intValue);
      [*] = ;
      [*] = ;elmSliderHandle := _gui_CreateIntSlider('size', elmParentHandle, 'halParentMiddle', 'valParentTop', -244, 503+yOff, 180, cEventState, hint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, intValue, gc_MapSizeOptions, text, false);
      [*] = ;elmHandle := GetGUIElementIndexByNameParent('arrowSliderLeft', elmSliderHandle);
      [*] = ;if GetGUIElementEnabled(elmHandle) then
      [*] = ;   SetGUIElementEnabled(elmHandle, bMaster);
      [*] = ;elmHandle := GetGUIElementIndexByNameParent('arrowSliderRight', elmSliderHandle);
      [*] = ;if GetGUIElementEnabled(elmHandle) then
      [*] = ;   SetGUIElementEnabled(elmHandle, bMaster);
      [*] = ;
      [*] = ;intValue := gMapSettings.players;
      [*] = ;
      [*] = ;elmSliderHandle := _gui_CreateIntSlider('players', elmParentHandle, 'halParentMiddle', 'valParentTop', 244, 503+yOff, 180, cEventState, '', 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;text := IntToStr(intValue+2);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, intValue, gc_MaxMapPlayers-1, text, false);
      [*] = ;elmHandle := GetGUIElementIndexByNameParent('arrowSliderLeft', elmSliderHandle);
      [*] = ;if GetGUIElementEnabled(elmHandle) then
      [*] = ;   SetGUIElementEnabled(elmHandle , bMaster);
      [*] = ;elmHandle := GetGUIElementIndexByNameParent('arrowSliderRight', elmSliderHandle);
      [*] = ;if GetGUIElementEnabled(elmHandle) then
      [*] = ;   SetGUIElementEnabled(elmHandle , bMaster);
      [*] = ;
      [*] = ;intValue := gMapSettings.worldrule;
      [*] = ;if gMapSettings.random then
      [*] = ;begin
      [*] = ;   hint := '';
      [*] = ;   text := 'gui|230';
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   hint := 'worldrule|'+IntToStr(intValue)+'.description';
      [*] = ;   text := 'worldrule|'+IntToStr(wr_array[intValue]);
      [*] = ;end;
      [*] = ;elmSliderHandle := _gui_CreateIntSlider('worldrule', elmParentHandle, 'halParentMiddle', 'valParentTop', 0, 503+yOff, 280, cEventState, hint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, intValue, wr_no, text, false);
      [*] = ;elmHandle := GetGUIElementIndexByNameParent('arrowSliderLeft', elmSliderHandle);
      [*] = ;if GetGUIElementEnabled(elmHandle) then
      [*] = ;   SetGUIElementEnabled(elmHandle, bMaster and (not gMapSettings.random));
      [*] = ;elmHandle := GetGUIElementIndexByNameParent('arrowSliderRight', elmSliderHandle);
      [*] = ;if GetGUIElementEnabled(elmHandle) then
      [*] = ;   SetGUIElementEnabled(elmHandle, bMaster and (not gMapSettings.random));
      [*] = ;
      [*] = ;{elmHandle := _gui_CreateCheckBox('fog', elmParentHandle, gProfile.fog, 'gui|680', 'halParentLeft', 'valParentTop', 320-46+4-22, 524+26-26, cEventState, '', 0);
      [*] = ;if (not bMaster) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.35);
      [*] = ;   SetGUIAllowEvents(elmHandle, False, False, False);
      [*] = ;end;
      [*] = ;elmHandle := _gui_CreateCheckBox('diplomacy', elmParentHandle, gProfile.diplomacy, 'gui|681', 'halParentLeft', 'valParentTop', 320-46+4-22, 524+26-6, cEventState, '', 0);
      [*] = ;if (not bMaster) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.35);
      [*] = ;   SetGUIAllowEvents(elmHandle, False, False, False);
      [*] = ;end;}
      [*] = ;
      [*] = ;if (_log) and (gGame.gametype=gc_GameTypeLanShard) then
      [*] = ;begin
      [*] = ;   var pTmp : Integer;
      [*] = ;
      [*] = ;   pTmp := _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;   LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(),pTmp);
      [*] = ;   _Log_gui('Savegame: '+ParserGetValueByKeyByHandle(pTmp,'MapName'));
      [*] = ;end;
      [*] = ;
      [*] = ;if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;   _gui_CreateAstralChatButton(elmParentHandle, -970, 200);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

