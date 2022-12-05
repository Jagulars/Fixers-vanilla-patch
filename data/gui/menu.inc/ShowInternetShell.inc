section.begin
   Name = ShowInternetShell
   Description : struct.begin
      [*] = ;none
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\SHOWINTERNETSHELL';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;
      [*] = ;const cEventState = 'EventInternetShell';
      [*] = ;const cEventStateChat = 'EvLanShellChat';
      [*] = ;const cResetDragElementState = 'DoResetDragElement';
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
      [*] = ;//const cBtnPointsModeClassic = 111;
      [*] = ;//const cBtnPointsModeProgressive = 112;
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
      [*] = ;const cListBoxChat = 40;
      [*] = ;//const cListBoxPointsDifference = 50;
      [*] = ;const cListBoxGames = 60;
      [*] = ;//const cBtnSetDefaultTag = 120;
      [*] = ;//const cRatingAllowHeroesFlagsBaseTag = 400;
      [*] = ;//const cRatingAllowTerrainFlagsBaseTag = 420;
      [*] = ;const cCheckBoxTagEmailNotify = 500;
      [*] = ;const cCheckBoxTagConflictNeedsMe = 501;
      [*] = ;const cCheckBoxTagTurnStarted = 502;
      [*] = ;const cCheckBoxTagAllowAINeutrals = 503;
      [*] = ;const cCheckBoxTagAllowAIHuman = 504;
      [*] = ;
      [*] = ;const cBorderFrameSize = 16;
      [*] = ;const cPlayersListWidth = 244;
      [*] = ;const cPanelHeight = 576;
      [*] = ;
      [*] = ;const cStyleDefault = '%color(default)%';
      [*] = ;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var avatar : String;
      [*] = ;var leftPanelWidth : Integer;
      [*] = ;var rightPanelWidth, rowHeight : Integer;
      [*] = ;var cStyleWhite : String;
      [*] = ;var fontHandle1, fontHandle, fontHandle2, fontHandle3, fontHandle4, fontHandle5, fontHandleInput : String;
      [*] = ;var level, exp, expPrevLevel, expNextLevel, expNeeded, points, gamesStarted, gamesPlayed, gamesWin, rank, karma : Integer;
      [*] = ;
      [*] = ;var prevInputText : String = GetGUIElementText(_gui_GetWindow('internetshell.rightpanel.chat.chatinput.text'));
      [*] = ;var profileMessage : String;
      [*] = ;var expandedProfile : Boolean = GetGUIElementChecked(_gui_GetWindow('internetshell.rightpanel.profile.expand_button'));
      [*] = ;if expandedProfile then
      [*] = ;begin
      [*] = ;   profileMessage := GetGUIElementText(_gui_GetWindow('internetshell.rightpanel.profile.textlayer.message'));
      [*] = ;   if (profileMessage = '') and (gIntRegister_InetSelectedPlayerID > 0) then
      [*] = ;   begin
      [*] = ;      if gIntRegister_InetSelectedPlayerID = LanMyInfoID then
      [*] = ;      begin
      [*] = ;         if gProfile.profilemessage <> '' then
      [*] = ;            profileMessage := gProfile.profilemessage
      [*] = ;         else
      [*] = ;            profileMessage := 'menu|profile_message';
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var pClient : Integer = _misc_ParserGetOrCreateByKey('client_info', True);
      [*] = ;         LanPublicServerGetClientInfoToParserByClientID(gIntRegister_InetSelectedPlayerID, pClient);
      [*] = ;         _gui_GetDelimiterValueByIndex(ParserGetValueByKeyByHandle(pClient, 'Info'), 10, profileMessage)
      [*] = ;      end;
      [*] = ;      profileMessage := StrReplace(profileMessage, '_', ' ');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UpdateListBoxScrollerPos(elmHandle : Integer);
      [*] = ;begin
      [*] = ;   IntRegister0 := 2;
      [*] = ;   IntRegister1 := elmHandle;
      [*] = ;   GUIExecuteState('vvk.LanUpdateGUIElements');
      [*] = ;end;
      [*] = ;
      [*] = ;function ClampToIntStep(value, step : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var count : Integer;
      [*] = ;   count := round(value/step);
      [*] = ;   Result := count*step;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetRulerKarmaID(const karma : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var rulerKarmaID : Integer = 0;
      [*] = ;   var j : Integer;
      [*] = ;   for j:=0 to gPrototypeData.rulerNicks.number-1 do
      [*] = ;   begin
      [*] = ;      var pRulerNick : Integer = ParserSelectByHandleByIndex(gPrototypeData.rulerNicks.handle, j);
      [*] = ;      var min : Integer = ParserGetIntValueByKeyByHandle(pRulerNick, 'Min');
      [*] = ;      var max : Integer = ParserGetIntValueByKeyByHandle(pRulerNick, 'Max');
      [*] = ;      if (karma>=min) and (karma<max) then
      [*] = ;      begin
      [*] = ;         rulerKarmaID := ParserGetIntValueByKeyByHandle(pRulerNick, 'RulerNickID');
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := rulerKarmaID;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateProfileInfo(elmParentHandle: Integer) : Integer;
      [*] = ;begin
      [*] = ;   var dropDownProfileWidth : Integer = rightPanelWidth-cBorderFrameSize*2-cPlayersListWidth;
      [*] = ;   var dropDownProfileHeight : Integer = rowHeight;
      [*] = ;   
      [*] = ;   if expandedProfile then
      [*] = ;   begin
      [*] = ;      const cBreakLineChar = 13; 
      [*] = ;      profileMessage := GetGUIWrappedTextFormatByFont(fontHandle, profileMessage, dropDownProfileWidth-8);
      [*] = ;      profileMessage := StrReplace(profileMessage, ' ', '_');
      [*] = ;      var lines : Integer = GetDelimiterStringCount(profileMessage, cBreakLineChar, gc_gui_QuoteChar);
      [*] = ;      profileMessage := StrReplace(profileMessage, '_', ' ');
      [*] = ;      var messageHeight : Integer = lines * GetGUIElementFontHeight(fontHandle);
      [*] = ;      var air : Integer = lines * rowHeight - messageHeight;
      [*] = ;      dropDownProfileHeight := rowHeight * 2 + messageHeight - air div rowHeight;
      [*] = ;      dropDownProfileHeight := min(dropDownProfileHeight, cPanelHeight-cBorderFrameSize*3-4);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   // profile info block
      [*] = ;   const cAvatarMarginL = 0;
      [*] = ;   const cAvatarMarginT = 0;
      [*] = ;   const cAvatarSizeX = 416 div 4;
      [*] = ;   const cAvatarSizeY = 480 div 4;
      [*] = ;
      [*] = ;   const cBorderFrameHeight = cAvatarSizeY;
      [*] = ;   const cTextMarginL = 6;
      [*] = ;   const cTextMarginT = 0;
      [*] = ;
      [*] = ;   // avatar
      [*] = ;   var elmProfileAvatarInfo : Integer = _gui_CreateFrameBorder('', elmParentHandle, 'halParentLeft', 'valParentTop', cBorderFrameSize, cBorderFrameSize, cAvatarSizeX, cAvatarSizeY);
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('avatar', elmProfileAvatarInfo, avatar, 'halParentLeft', 'valParentTop', cAvatarMarginL, cAvatarMarginT, cAvatarSizeX, cAvatarSizeY, 0);
      [*] = ;
      [*] = ;   // info
      [*] = ;   var elmProfileInfo : Integer = _gui_CreateFrameBorder('', elmParentHandle, 'halParentLeft', 'valParentTop', cBorderFrameSize+cAvatarSizeX+cBorderFrameSize, cBorderFrameSize, rightPanelWidth-cBorderFrameSize*3-cAvatarSizeX, cBorderFrameHeight);
      [*] = ;
      [*] = ;   // name
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmProfileInfo, cStyleWhite+gProfile.name, 'halParentLeft', 'valParentTop', cTextMarginL, cTextMarginT, rightPanelWidth-cBorderFrameSize*2-cTextMarginL*2, GetGUIElementFontHeight(fontHandle5), 'halLeft', 'valMiddle', fontHandle5, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   // herb
      [*] = ;   const cHerbX = 5;
      [*] = ;   const cHerbY = 3;
      [*] = ;   _gui_CreateHerb('', elmProfileInfo, gProfile.sign, gProfile.color1, gProfile.color2, 'halParentLeft', 'valParentBottomHeight', cHerbX, cHerbY);
      [*] = ;   _gui_CreateHerb('', elmProfileInfo, gProfile.sign, gProfile.color1, gProfile.color2, 'halParentRightWidth', 'valParentBottomHeight', -cHerbX, cHerbY);
      [*] = ;
      [*] = ;   // game win
      [*] = ;   var text : String = GetLocaleTableListItemByID('menu', '158')+': '+cStyleWhite+IntToStr(gamesWin);
      [*] = ;   elmTextHandle := _gui_CreateText('', elmProfileInfo, text, 'halParentLeft', 'valParentTop', 0, cTextMarginT, GetGUIElementWidth(elmProfileInfo)-cTextMarginL, GetGUIElementFontHeight(fontHandle5), 'halRight', 'valTop', fontHandle5, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   // exp meter
      [*] = ;   const cExpMeterMarginL = 0;
      [*] = ;   const cExpMeterMarginT = 31;
      [*] = ;   const cExpMeterSizeY = 22;
      [*] = ;   var expMeterSizeX : Integer = GetGUIElementWidth(elmProfileInfo)-cExpMeterMarginL*2;
      [*] = ;
      [*] = ;   var expMeterHandle : Integer = _gui_CreateImage('expmeter', elmProfileInfo, 'shell.exp.back', 'halParentMiddle', 'valParentTop', cExpMeterMarginL, cExpMeterMarginT, 0, 0, 0);
      [*] = ;
      [*] = ;   var meterWidth : Integer = round(((exp-expPrevLevel)/expNeeded)*expMeterSizeX);
      [*] = ;   meterWidth := round(Clamp(meterWidth, 0, expMeterSizeX));
      [*] = ;   if (meterWidth>1) then
      [*] = ;   begin
      [*] = ;      //elmHandle := _gui_CreateImage('expmeter', expMeterHandle, 'shell.exp.progress', 'halParentLeft', 'valParentMiddle', 0, 0, meterWidth, cExpMeterSizeY, 0);
      [*] = ;      elmHandle := _gui_CreateTileScaleImage('expmeter', expMeterHandle, 'shell.exp.progress.highlight', 'halParentLeft', 'valParentMiddle', 0, 0, meterWidth, 0, 0);
      [*] = ;      elmHandle := _gui_CreateTileScaleImage('expmeter', expMeterHandle, 'shell.exp.progress', 'halParentLeft', 'valParentMiddle', 0, 0, meterWidth-1, 0, 0);
      [*] = ;   end;
      [*] = ;   elmHandle := _gui_CreateImage('expmeter', expMeterHandle, 'shell.exp.cover', 'halParentMiddle', 'valParentMiddle', 0, 0, 0, 0, 0);
      [*] = ;
      [*] = ;   text := GetLocaleTableListItemByID('menu', '159')+': %style(bold)%'+cStyleWhite+IntToStr(exp-expPrevLevel)+' / '+IntToStr(expNeeded);
      [*] = ;   elmTextHandle := _gui_CreateText('', expMeterHandle, text, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(expMeterHandle), GetGUIElementHeight(expMeterHandle), 'halMiddle', 'valMiddle', fontHandle1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   // karma
      [*] = ;   var rulerTitleID : Integer = rank;//GetRulerTitleIDByLevel(level);
      [*] = ;   var rulerKarmaID : Integer = GetRulerKarmaID(karma);
      [*] = ;   if (rulerKarmaID<>0) then
      [*] = ;   begin
      [*] = ;      text := GetLocaleTableListItemByID('ruler_title', IntToStr(rulerTitleID))+', '+GetLocaleTableListItemByID('ruler_nick', IntToStr(rulerKarmaID));
      [*] = ;      //elmTextHandle := _gui_CreateText('', expMeterHandle, text, 'halParentLeft', 'valParentBottom', 0, cLevelMarginT, GetGUIElementWidth(expMeterHandle), h, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   const cStyle0 = '%style(default)%'+cStyleDefault;
      [*] = ;   var cStyle1 : String = '%style(bold)%'+cStyleWhite;
      [*] = ;   const statMarginT = 0;
      [*] = ;   text := GetLocaleTableListItemByID('menu', '160')+': '+cStyle1+IntToStr(level)+cStyle0;
      [*] = ;   //text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('unit', IntToStr(rank));
      [*] = ;   var rulertitle : String = GetLocaleTableListItemByID('ruler_title', IntToStr(rulerTitleID));
      [*] = ;   if (rulertitle<>'') and (rulertitle<>' ') then
      [*] = ;   text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('menu', '161')+': '+cStyle1+rulertitle+cStyle0;
      [*] = ;   var rulernick : String = GetLocaleTableListItemByID('ruler_nick', IntToStr(rulerKarmaID));
      [*] = ;   if (rulernick<>'') and (rulernick<>' ') then
      [*] = ;   text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('menu', '162')+': '+cStyle1+rulernick;
      [*] = ;   elmTextHandle := _gui_CreateText('', elmProfileInfo, text, 'halParentLeft', 'valParentTop', cExpMeterMarginL, cExpMeterMarginT+cExpMeterSizeY, GetGUIElementWidth(expMeterHandle), GetGUIElementHeight(elmProfileInfo)-(cExpMeterMarginT+cExpMeterSizeY), 'halMiddle', 'valMiddle', fontHandle1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   
      [*] = ;   // select profile info bar
      [*] = ;   var elmProfileSelectBar : Integer = _gui_CreateFrameBorder('profile', elmParentHandle, 'halParentLeft', 'valParentTop', cBorderFrameSize, GetGUIElementHeight(elmProfileInfo)+cBorderFrameSize*2, dropDownProfileWidth, dropDownProfileHeight);
      [*] = ;   // expand profile button
      [*] = ;   var elmShowProfileBtn : Integer = _gui_CreateCheckBox('expand_button', elmProfileSelectBar, false, 'menu|172', 'halParentLeft', 'valParentTop', 0, 0, cEventState, '', cBtnExpandProfileTag);
      [*] = ;   var xOff : Integer = 0;
      [*] = ;   var yOff : Integer = 2;
      [*] = ;   var txOff : Integer = 24;
      [*] = ;   var tyOff : Integer = -1;
      [*] = ;   SetGUIElementVisibleProperties(elmShowProfileBtn, 'UpProperty', 'common.checkbox.normal', xOff, yOff, txOff, tyOff, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmShowProfileBtn, 'HoverProperty', 'common.checkbox.hover', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmShowProfileBtn, 'DownProperty', 'common.checkbox.pressed', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmShowProfileBtn, 'DisableProperty', 'common.checkbox.disabled', xOff, yOff, txOff, tyOff, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmShowProfileBtn, 'CheckOnProperty', 'common.checkbox.checkon', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   if gIntRegister_InetSelectedPlayerID > 0 then
      [*] = ;   begin
      [*] = ;      SetGUIElementEnabled(elmShowProfileBtn, true);
      [*] = ;      SetGUIElementUserBlend(elmShowProfileBtn, 1.0);
      [*] = ;      if expandedProfile then
      [*] = ;      begin
      [*] = ;         SetGUIElementChecked(elmShowProfileBtn, true);
      [*] = ;         var elmTextHandle : Integer = _gui_CreateText('version', elmProfileSelectBar, '', 'halParentMiddle', 'valParentTop', 0, rowHeight, dropDownProfileWidth, GetGUIElementFontHeight(fontHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;            
      [*] = ;         var elmGuiLayer : Integer = AddNewElementByClassNameParent('textLayer', 'TXGuiLayer', 0, elmProfileSelectBar);
      [*] = ;         SetGUIElementAlign(elmGuiLayer, 'halParentLeft', 'valParentTop');
      [*] = ;         SetGUIElementAllPositionRect(elmGuiLayer, 0, rowHeight*2, dropDownProfileWidth, dropDownProfileHeight - rowHeight*2);
      [*] = ;         SetGUIElementMaterial(elmGuiLayer, 'misc.blank.black.alpha.0');
      [*] = ;         var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;         SetGUIElementAlign(elmVScroll, 'halParentLeft', 'valParentTop');
      [*] = ;         SetGUIElementMaterialOffset(elmVScroll, 0, 0);
      [*] = ;         SetGUIElementAllPositionRect(elmVScroll, 0, 0, dropDownProfileWidth-8, dropDownProfileHeight - rowHeight*2);
      [*] = ;         SetGUIScrollEnabled(elmGuiLayer, True);
      [*] = ;         elmTextHandle := _gui_CreateText('message', elmGuiLayer, profileMessage, 'halParentLeft', 'valParentTop', 0, 0, dropDownProfileWidth-8, dropDownProfileHeight - rowHeight*2, 'halLeft', 'valTop', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      SetGUIElementEnabled(elmShowProfileBtn, false);
      [*] = ;      SetGUIElementUserBlend(elmShowProfileBtn, 0.4);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // mute button
      [*] = ;   const cBtnMuteTag = 105;
      [*] = ;   var elmMuteButton : Integer;
      [*] = ;   var posX : Integer = -188;
      [*] = ;   xOff := 164;
      [*] = ;   txOff := 24;
      [*] = ;   elmMuteButton := _gui_CreateCheckBox('mute', elmProfileSelectBar, false, 'menu|88', 'halParentRight', 'valParentTop', posX, 0, 'EventAstralChat', '', cBtnMuteTag);
      [*] = ;   SetGUIElementTextAlign(elmMuteButton, 'halRight', 'valMiddle', 0, 0);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'UpProperty', 'common.checkbox.normal', xOff, yOff, txOff, tyOff, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'HoverProperty', 'common.checkbox.hover', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'DownProperty', 'common.checkbox.pressed', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'DisableProperty', 'common.checkbox.disabled', xOff, yOff, txOff, tyOff, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'CheckOnProperty', 'common.checkbox.checkon', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementEnabled(elmMuteButton, false);
      [*] = ;   SetGUIElementUserBlend(elmMuteButton, 0.4);
      [*] = ;   
      [*] = ;   Result := elmProfileInfo;
      [*] = ;end;
      [*] = ;
      [*] = ;function UpdateChat(elmParentHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pChat : Integer = _misc_ParserGetOrCreateByKey('shell.commonchat',false);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pChat)-1 do
      [*] = ;   begin
      [*] = ;      var pChatMsg : Integer = ParserSelectByHandleByIndex(pChat, i);
      [*] = ;      var msg : String = ParserGetValueByKeyByHandle(pChatMsg, 'm');
      [*] = ;      var idFrom : Integer = ParserGetIntValueByKeyByHandle(pChatMsg, 'f');
      [*] = ;      var idTo : Integer = ParserGetIntValueByKeyByHandle(pChatMsg, 't');
      [*] = ;      _inet_ShowChatMessage(elmParentHandle, msg, false, idTo, idFrom);
      [*] = ;   end;
      [*] = ;   SetGUIListBoxItemIndexSilent(elmParentHandle, GetGUIListBoxItemsCount(elmParentHandle)-1);
      [*] = ;
      [*] = ;   UpdateListBoxScrollerPos(elmParentHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateChat(elmParentHandle, elmProfileInfo : Integer) : Integer;
      [*] = ;begin
      [*] = ;   const cChatTextMarginL = 5;
      [*] = ;   const cChatTextMarginB = -32;
      [*] = ;   const cScrollOffset = -7;
      [*] = ;   var r_pos : TRectangle;
      [*] = ;   var chatFontHandle : String = fontHandle2;
      [*] = ;   var chatLineHeight : Integer = GetGUIElementFontHeight(chatFontHandle);
      [*] = ;   var profileBarHeight : Integer = GetGUIElementHeight(_gui_GetWindow('internetshell.rightpanel.profile'));
      [*] = ;   var chatMarginT : Integer = cBorderFrameSize*2+GetGUIElementHeight(elmProfileInfo)+4 + profileBarHeight;
      [*] = ;   var chatWidth : Integer = rightPanelWidth-cBorderFrameSize*2-cPlayersListWidth;
      [*] = ;   var chatHeight : Integer = round((cPanelHeight-(GetGUIElementHeight(elmProfileInfo)))-cBorderFrameSize*3-4) - profileBarHeight;
      [*] = ;   chatHeight := ClampToIntStep(chatHeight, chatLineHeight);
      [*] = ;   var elmChat : Integer = _gui_CreateFrameBorder('chat', elmParentHandle, 'halParentLeft', 'valParentTop', cBorderFrameSize, chatMarginT, chatWidth, chatHeight+cChatTextMarginB);
      [*] = ;
      [*] = ;   // Scroll layer and save file list
      [*] = ;   var chatTextWidth : Integer = GetGUIElementWidth(elmChat)-cChatTextMarginL*2;
      [*] = ;   var elmChatHistory : Integer = AddNewElementByClassNameParent('history', 'TXGuiListBox', cListBoxChat, elmChat);
      [*] = ;
      [*] = ;   const cChatHistoryScrollMarginR = 7;
      [*] = ;   SetGUIElementPressState(elmChatHistory, cEventStateChat);
      [*] = ;   SetGUIElementFont(elmChatHistory, chatFontHandle);
      [*] = ;   SetGUIElementColor(elmChatHistory, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementAlign(elmChatHistory, 'halParentLeft', 'valParentTop');
      [*] = ;   SetGUIElementAllPositionRect(elmChatHistory, 0, 0, GetGUIElementWidth(elmChat)-cChatHistoryScrollMarginR, GetGUIElementHeight(elmChat));
      [*] = ;   SetGUIElementMaterial(elmChatHistory,  gc_gui_material_blank_0{'common.slider.middle'});
      [*] = ;   SetGUIListBoxSelectedMaterialName(elmChatHistory, gc_gui_material_blank_0{'gamepanel03.combobox.line.selected'});
      [*] = ;
      [*] = ;   SetGUIElementTextAlign(elmChatHistory, 'halLeft', 'valTop', 5, -5);
      [*] = ;   SetGUIListBoxRowHeight(elmChatHistory, GetGUIElementFontHeight(chatFontHandle)+4);
      [*] = ;   SetGUIListBoxVisibleRows(elmChatHistory, -1);
      [*] = ;   SetGUIListBoxItemIndexSilent(elmChatHistory, -1);
      [*] = ;   SetGUIListBoxMouseTrack(elmChatHistory, 2);
      [*] = ;   SetGUIListBoxMouseTrackMaterialName(elmChatHistory, gc_gui_material_blank_0{'gamepanel03.combobox.line.hover'});
      [*] = ;   SetGUIListBoxMouseTrackFontColor(elmChatHistory, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;
      [*] = ;   // - setup scroller
      [*] = ;   var elmScroll : Integer = GetGUIListBoxScrollerHandle(elmChatHistory);
      [*] = ;   SetGUIElementMaterialOffset(elmScroll, -5, 0);
      [*] = ;   SetGUIElementAllPositionRect(elmScroll, 22, 5, 18, GetGUIElementHeight(elmChatHistory)-5*2);
      [*] = ;   SetGUIElementMaterial(elmScroll, 'map.dialog.scroller.tile');
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 0, 'map.dialog.scroller.up', True);
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 1, 'map.dialog.scroller.slider', True);
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 2, 'map.dialog.scroller.down', True);
      [*] = ;
      [*] = ;   var inputWidth : Integer = chatTextWidth+73+cPlayersListWidth;
      [*] = ;   const cMaxLength = 1024;
      [*] = ;   const cInputBoxMarginL = cPlayersListWidth div 2;
      [*] = ;   const cInputBoxMarginT = -2;
      [*] = ;   _sys_FillRect(r_pos,cInputBoxMarginL, GetGUIElementHeight(elmChat)+cInputBoxMarginT, inputWidth,0);
      [*] = ;   var inputField : Integer = _gui_CreateInputControl_VVK('chatinput',elmChat,'', gc_gui_align_parent_mt,false,r_pos,cMaxLength, cEventState, '');
      [*] = ;   if prevInputText <> '' then
      [*] = ;      SetGUIElementText(inputField, prevInputText);
      [*] = ;   UpdateChat(_gui_GetWindow('internetshell.rightpanel.chat.history'));
      [*] = ;
      [*] = ;   Result := elmChat;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreatePlayers(elmParentHandle, elmProfileInfo : Integer) : Integer;
      [*] = ;begin
      [*] = ;   const cPlayersTextMarginL = 5;
      [*] = ;   const cPlayersTextMarginB = -32;
      [*] = ;   const cScrollOffset = -7;
      [*] = ;   const cBtnOffsetY = 44;
      [*] = ;
      [*] = ;   var playersFontHandle : String = fontHandle2;
      [*] = ;   var playersLineHeight : Integer = GetGUIElementFontHeight(playersFontHandle);
      [*] = ;   var playersMarginT : Integer = cBorderFrameSize*2+GetGUIElementHeight(elmProfileInfo);
      [*] = ;   var playersWidth : Integer = cPlayersListWidth-cBorderFrameSize;
      [*] = ;
      [*] = ;   var b_no,maxPageCount : Integer;
      [*] = ;   var playersHeight : Integer = round((cPanelHeight-(GetGUIElementHeight(elmProfileInfo)))-cBorderFrameSize*3-4);
      [*] = ;
      [*] = ;   if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;      maxPageCount := 9
      [*] = ;   else
      [*] = ;      maxPageCount := 11;
      [*] = ;   playersHeight := ClampToIntStep(playersHeight, playersLineHeight);
      [*] = ;
      [*] = ;   var chatWidth : Integer = rightPanelWidth-cBorderFrameSize*2-cPlayersListWidth;
      [*] = ;   var elmPlayers : Integer = _gui_CreateFrameBorder('players', elmParentHandle, 'halParentLeft', 'valParentTop', cBorderFrameSize*2+(chatWidth), playersMarginT, playersWidth, playersHeight+cPlayersTextMarginB);
      [*] = ;   var playersListTextWidth : Integer = GetGUIElementWidth(elmPlayers)-cPlayersTextMarginL*2;
      [*] = ;   var elmPlayersList : Integer = AddNewElementByClassNameParent('list', 'TXGuiListBox', cListBoxPlayers, elmPlayers);
      [*] = ;
      [*] = ;   AddGUIListBoxTabProperty(elmPlayersList, 1, 1, 1, 1, 23, 'tsImage'); // Client state
      [*] = ;   AddGUIListBoxTabProperty(elmPlayersList, 1, 1, 1, 1, 149, 'tsText'); // Client list
      [*] = ;   AddGUIListBoxTabProperty(elmPlayersList, 1, 1, 1, 1, 0, 'tsText'); // Client list
      [*] = ;
      [*] = ;   const cPlayersListScrollMarginR = 7;
      [*] = ;   SetGUIElementPressState(elmPlayersList, cEventState);
      [*] = ;   SetGUIElementFont(elmPlayersList, playersFontHandle);
      [*] = ;   SetGUIElementColor(elmPlayersList, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementAlign(elmPlayersList, 'halParentLeft', 'valParentTop');
      [*] = ;   //SetGUIElementAllPositionRect(elmPlayersList, 0, 0, GetGUIElementWidth(elmPlayers)-cPlayersListScrollMarginR, GetGUIElementHeight(elmPlayers)-100);
      [*] = ;   SetGUIElementMaterial(elmPlayersList,  gc_gui_material_blank_0{'common.slider.middle'});
      [*] = ;   SetGUIListBoxSelectedMaterialName(elmPlayersList, {gc_gui_material_blank_0}'gamepanel03.combobox.line.selected');
      [*] = ;
      [*] = ;   SetGUIElementTextAlign(elmPlayersList, 'halLeft', 'valTop', 2, -5);
      [*] = ;   SetGUIListBoxRowHeight(elmPlayersList, GetGUIElementFontHeight(GetGUIElementFont(elmPlayersList))+4);
      [*] = ;   SetGUIElementAllPositionRect(elmPlayersList, 0, 0, GetGUIElementWidth(elmPlayers)-cPlayersListScrollMarginR, GetGUIListBoxRowHeight(elmPlayersList)*maxPageCount);
      [*] = ;   SetGUIListBoxVisibleRows(elmPlayersList, maxPageCount);
      [*] = ;   SetGUIListBoxItemIndexSilent(elmPlayersList, -1);
      [*] = ;   SetGUIListBoxMouseTrack(elmPlayersList, 3);
      [*] = ;   SetGUIListBoxMouseTrackMaterialName(elmPlayersList, gc_gui_material_blank_0{'gamepanel03.combobox.line.hover'});
      [*] = ;   SetGUIListBoxMouseTrackFontColor(elmPlayersList, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;
      [*] = ;   SetGUIElementCursorByName(elmPlayersList, 'crHand');
      [*] = ;
      [*] = ;   // - setup scroller
      [*] = ;   var elmScroll : Integer = GetGUIListBoxScrollerHandle(elmPlayersList);
      [*] = ;   SetGUIElementMaterialOffset(elmScroll, -5, 0);
      [*] = ;   SetGUIElementAllPositionRect(elmScroll, 15+cPlayersListScrollMarginR, 5, 18, 20{GetGUIListBoxRowHeight(elmPlayersList)*(maxPageCount-2)}-5*2);
      [*] = ;   SetGUIElementMaterial(elmScroll, 'map.dialog.scroller.tile');
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 0, 'map.dialog.scroller.up', True);
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 1, 'map.dialog.scroller.slider', True);
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 2, 'map.dialog.scroller.down', True);
      [*] = ;
      [*] = ;   if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;      b_no := 3
      [*] = ;   else
      [*] = ;      b_no := 2;
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('btncreate', elmPlayers, '', 'common.btn', 'halParentMiddle', 'valParentBottomHeight', 0, -1*(cBtnOffsetY*(b_no-1)+4), 0, 0, cEventState, 'menu|211.ext', 0);
      [*] = ;   if gGame.gametype <> gc_GameTypeLanShard then
      [*] = ;      SetGUIElementTag(elmBtnHandle,cBtnCreatePrivateBattle)
      [*] = ;   else
      [*] = ;      SetGUIElementTag(elmBtnHandle,cBtnCreateShardGame);
      [*] = ;   SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementUserBlend(elmBtnHandle, 0.8);
      [*] = ;   _gui_CreateText('', elmBtnHandle, 'menu|211', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;   if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;   begin
      [*] = ;      elmBtnHandle := _gui_CreateButton('btnload', elmPlayers, '', 'common.btn', 'halParentMiddle', 'valParentBottomHeight', 0, -1*(cBtnOffsetY*(b_no-2)+4), 0, 0, cEventState, '', cBtnLoadShardGame);
      [*] = ;      SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementUserBlend(elmBtnHandle, 0.8);
      [*] = ;      _gui_CreateText('', elmBtnHandle, 'menu|227', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      if ((_misc_GetLoadContinueFlags($40) and $40) = 0) then
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var bEnabled : Boolean = False;
      [*] = ;   if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;   begin
      [*] = ;      var elmGamesList,ind : Integer;
      [*] = ;
      [*] = ;      elmGamesList := _gui_GetWindow('internetshell.leftpanel.shardgames.list');
      [*] = ;      if elmGamesList <> 0 then
      [*] = ;         ind := GetGUIListBoxItemIndex(elmGamesList)
      [*] = ;      else
      [*] = ;         ind := -1;
      [*] = ;      if (ind>=0) then
      [*] = ;      begin
      [*] = ;         var itemValue : String = GetGUIListBoxItemValue(elmGamesList, ind);
      [*] = ;         var gamestate : String = '';
      [*] = ;         if (GetDelimiterStringCount(itemValue, 9, gc_gui_QuoteChar)>1) then
      [*] = ;            gamestate := GetDelimiterStringByIndex(itemValue, 9, gc_gui_QuoteChar, 0);
      [*] = ;         if ((gamestate='ready') or (gamestate='progress')) then
      [*] = ;           bEnabled := True;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var ind : Integer = GetGUIListBoxItemIndex(elmPlayersList);
      [*] = ;
      [*] = ;      if (ind>=0) then
      [*] = ;      begin
      [*] = ;         var itemValue : String = GetGUIListBoxItemValue(elmPlayersList, ind);
      [*] = ;         var gamestate : String = '';
      [*] = ;         if (GetDelimiterStringCount(itemValue, 9, gc_gui_QuoteChar)>1) then
      [*] = ;            gamestate := GetDelimiterStringByIndex(itemValue, 9, gc_gui_QuoteChar, 0);
      [*] = ;         if (gIntRegister_InetSelectedPlayerID<>0) and ((gamestate='shell.session') or (gamestate='shell.session.lock') or (gamestate='shell.session.unlock')) then
      [*] = ;            bEnabled := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //var elmHandle : Integer = _gui_GetWindow('internetshell.rightpanel.players.btnjoin');
      [*] = ;   var hint : String = GetLocaleTableListItemByID('menu', '212.ext');
      [*] = ;   if (not bEnabled) then
      [*] = ;      hint := hint+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('menu', '213');
      [*] = ;
      [*] = ;   elmBtnHandle := _gui_CreateButton('btnjoin', elmPlayers, '', 'common.btn', 'halParentMiddle', 'valParentBottomHeight', 0, -4, 0, 0, cEventState, hint, 0);
      [*] = ;   if gGame.gametype <> gc_GameTypeLanShard then
      [*] = ;      SetGUIElementTag(elmBtnHandle,cBtnJoinBattle)
      [*] = ;   else
      [*] = ;      SetGUIElementTag(elmBtnHandle,cBtnJoinShardGame);
      [*] = ;   SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementUserBlend(elmBtnHandle, 0.8);
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, bEnabled);
      [*] = ;   _gui_CreateText('', elmBtnHandle, 'menu|212', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;   const cShellClientsList = 'internetshell.rightpanel.players.list';
      [*] = ;   _inet_UpdateClientsList(cShellClientsList, 0);
      [*] = ;
      [*] = ;   Result := elmPlayers;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateLeftSide(elmParentHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := 4;
      [*] = ;   IntRegister1 := elmParentHandle;
      [*] = ;   GUIExecuteState('vvk.LanUpdateGUIElements');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UpdateShardGamesList(elmName : String);
      [*] = ;begin
      [*] = ;   IntRegister0 := 1;
      [*] = ;   StringRegister0 := elmName;
      [*] = ;   GUIExecuteState('vvk.LanUpdateGUIElements');
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateShardGames(elmParentHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   // get values
      [*] = ;   var elmShardGames : Integer = GetGUIElementIndexByNameParent('shardgames', elmParentHandle);
      [*] = ;   if (elmShardGames<>0) then
      [*] = ;      RemoveGUIElement(elmShardGames);
      [*] = ;   //elmShardGames := _gui_CreateImage('shardgames', elmParentHandle, gc_gui_material_blank_0, 'halParentMiddle', 'valParentTop', 0, 16+33, GetGUIElementWidth(elmParentHandle)-32, GetGUIElementHeight(elmParentHandle), 0);
      [*] = ;   elmShardGames := _gui_CreateImage('shardgames', elmParentHandle, gc_gui_material_blank_0, 'halParentMiddle', 'valParentTop', -8, 0, GetGUIElementWidth(elmParentHandle)-32-16, GetGUIElementHeight(elmParentHandle), 0);
      [*] = ;   const cStripMarginT = 26;
      [*] = ;   const cStripTextMarginT = 6;
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', elmShardGames, 'element.strip.341', 'halParentMiddle', 'valParentTop', 8, cStripMarginT, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('' , elmHandle, 'gui|797', 'halParentLeft', 'valParentTop', 0, cStripTextMarginT, GetGUIElementWidth(elmHandle), 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   var elmGamesList : Integer = AddNewElementByClassNameParent('list', 'TXGuiListBox', cListBoxGames, elmShardGames);
      [*] = ;   var listWidth : Integer = GetGUIElementWidth(elmShardGames);
      [*] = ;   const cWidthKoefGameName = 0.35;
      [*] = ;   const cWidthKoefGameMaster = 0.2;
      [*] = ;   const cWidthKoefPlayersCount = 0.125;
      [*] = ;   const cWidthKoefPlayersOnline = 0.125;
      [*] = ;   const cWidthKoefPlayersStatus = 1-(cWidthKoefGameName+cWidthKoefGameMaster+cWidthKoefPlayersCount+cWidthKoefPlayersOnline);
      [*] = ;   AddGUIListBoxTabProperty(elmGamesList, 1, 1, 1, 1, 0, 'tsImage');
      [*] = ;   AddGUIListBoxTabProperty(elmGamesList, 1, 1, 1, 1, round(listWidth*cWidthKoefGameName), 'tsText'); // game name
      [*] = ;   AddGUIListBoxTabProperty(elmGamesList, 1, 1, 1, 1, round(listWidth*cWidthKoefGameMaster), 'tsText'); // game master
      [*] = ;   AddGUIListBoxTabProperty(elmGamesList, 1, 1, 1, 1, round(listWidth*cWidthKoefPlayersCount), 'tsText'); // players count
      [*] = ;   //AddGUIListBoxTabProperty(elmGamesList, 1, 1, 1, 1, round(listWidth*0.1), 'tsText'); // game turn
      [*] = ;   //AddGUIListBoxTabProperty(elmGamesList, 1, 1, 1, 1, round(listWidth*cWidthKoefPlayersOnline), 'tsText'); // online
      [*] = ;   AddGUIListBoxTabProperty(elmGamesList, 1, 1, 1, 1, 0, 'tsText'); // status
      [*] = ;
      [*] = ;   const cGamesListScrollMarginR = 0;
      [*] = ;   var gamesFontHandle : String = fontHandle2;
      [*] = ;   const maxPageCount = 12;
      [*] = ;
      [*] = ;   SetGUIElementPressState(elmGamesList, cEventState);
      [*] = ;   SetGUIElementFont(elmGamesList, gamesFontHandle);
      [*] = ;   SetGUIElementColor(elmGamesList, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementAlign(elmGamesList, 'halParentLeft', 'valParentTop');
      [*] = ;   //SetGUIElementAllPositionRect(elmPlayersList, 0, 0, GetGUIElementWidth(elmPlayers)-cPlayersListScrollMarginR, GetGUIElementHeight(elmPlayers)-100);
      [*] = ;   SetGUIElementMaterial(elmGamesList,  gc_gui_material_blank_0{'common.slider.middle'});
      [*] = ;   SetGUIListBoxSelectedMaterialName(elmGamesList, {gc_gui_material_blank_0}'gamepanel03.combobox.line.selected');
      [*] = ;   //SetGUIListBoxSelectedMaterialName(elmGamesList, gc_gui_material_blank_0);
      [*] = ;
      [*] = ;   SetGUIElementTextAlign(elmGamesList, 'halLeft', 'valMiddle', 4, -5);
      [*] = ;   SetGUIListBoxRowHeight(elmGamesList, GetGUIElementFontHeight(GetGUIElementFont(elmGamesList))+4+8);
      [*] = ;   SetGUIElementAllPositionRect(elmGamesList, 0, 115, GetGUIElementWidth(elmShardGames)-cGamesListScrollMarginR, GetGUIListBoxRowHeight(elmGamesList)*maxPageCount);
      [*] = ;   SetGUIListBoxVisibleRows(elmGamesList, maxPageCount);
      [*] = ;   SetGUIListBoxItemIndexSilent(elmGamesList, -1);
      [*] = ;   SetGUIListBoxMouseTrack(elmGamesList, 1);
      [*] = ;   SetGUIListBoxMouseTrackMaterialName(elmGamesList, gc_gui_material_blank_0{'gamepanel03.combobox.line.hover'});
      [*] = ;   SetGUIListBoxMouseTrackFontColor(elmGamesList, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;
      [*] = ;   SetGUIElementCursorByName(elmGamesList, 'crHand');
      [*] = ;
      [*] = ;   // - setup scroller
      [*] = ;   var elmScroll : Integer = GetGUIListBoxScrollerHandle(elmGamesList);
      [*] = ;   SetGUIElementMaterialOffset(elmScroll, -5, 0);
      [*] = ;   SetGUIElementAllPositionRect(elmScroll, 15+cGamesListScrollMarginR+16, 5, 18, GetGUIElementHeight(elmGamesList)-5*2);
      [*] = ;   SetGUIElementMaterial(elmScroll, 'map.dialog.scroller.tile');
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 0, 'map.dialog.scroller.up', True);
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 1, 'map.dialog.scroller.slider', True);
      [*] = ;   SetGUIScrollButtonSource(elmScroll, 2, 'map.dialog.scroller.down', True);
      [*] = ;
      [*] = ;   var elmFrame : Integer = 0;
      [*] = ;   var elmFrameTitle : Integer = _gui_CreateFrameBorderExt('', elmShardGames, 'halParentLeft', 'valParentTop', 1, 74, GetGUIElementWidth(elmShardGames)-2, 38+6, False);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to maxPageCount-1 do
      [*] = ;   begin
      [*] = ;      elmFrame := _gui_CreateFrameBorderExt('', elmFrameTitle, 'halParentLeft', 'valParentTop', 0, 46+2+i*(GetGUIElementFontHeight(GetGUIElementFont(elmGamesList))+4+8), GetGUIElementWidth(elmShardGames)-2, GetGUIElementFontHeight(GetGUIElementFont(elmGamesList))+4+8-4, False);
      [*] = ;      //var elmLineHandle : Integer = _gui_CreateImage('', elmGamesList, 'gamepanel03.loadgame.table.line', 'halParentLeft', 'valParentTop', 0, i*(28)+1, 0, 0, 0);
      [*] = ;      //if (i<neededCount-1) then
      [*] = ;      //elmHandle := _gui_CreateImage('', elmLineHandle, 'gamepanel03.loadgame.table.border.middle', 'halParentLeft', 'valParentTop', 0, 22, 0, 0, 0);
      [*] = ;   end;
      [*] = ;   _gui_CreateText('', elmFrameTitle, 'Game name', 'halParentLeft', 'valParentTop', 2, 0, round(listWidth*cWidthKoefGameName), GetGUIElementHeight(elmFrameTitle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   var elmFrameDelimiter : Integer = _gui_CreateFrameBorderExt('', elmShardGames, 'halParentLeft', 'valParentTop', round(listWidth*cWidthKoefGameName)-4, GetGUIElementPositionY(elmFrameTitle), 0, GetGUIElementHeight(elmFrameTitle)+maxPageCount*(GetGUIElementHeight(elmFrame))+4*maxPageCount, False);
      [*] = ;   _gui_CreateText('', elmFrameTitle, 'Master', 'halParentLeft', 'valParentTop', 4+GetGUIElementPositionX(elmFrameDelimiter), 0, round(listWidth*cWidthKoefGameName), GetGUIElementHeight(elmFrameTitle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   elmFrameDelimiter := _gui_CreateFrameBorderExt('', elmShardGames, 'halParentLeft', 'valParentTop', GetGUIElementPositionX(elmFrameDelimiter)+round(listWidth*cWidthKoefGameMaster), GetGUIElementPositionY(elmFrameTitle), 0, GetGUIElementHeight(elmFrameTitle)+maxPageCount*(GetGUIElementHeight(elmFrame))+4*maxPageCount, False);
      [*] = ;   _gui_CreateText('', elmFrameTitle, 'Players', 'halParentLeft', 'valParentTop', 4+GetGUIElementPositionX(elmFrameDelimiter), 0, round(listWidth*cWidthKoefGameName), GetGUIElementHeight(elmFrameTitle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   //elmFrameDelimiter := _gui_CreateFrameBorderExt('', elmShardGames, 'halParentLeft', 'valParentTop', GetGUIElementPositionX(elmFrameDelimiter)+round(listWidth*cWidthKoefPlayersCount), GetGUIElementPositionY(elmFrameTitle), 0, GetGUIElementHeight(elmFrameTitle)+maxPageCount*(GetGUIElementHeight(elmFrame))+4*maxPageCount, False);
      [*] = ;   //_gui_CreateText('', elmFrameTitle, 'Online', 'halParentLeft', 'valParentTop', 4+GetGUIElementPositionX(elmFrameDelimiter), 0, round(listWidth*cWidthKoefGameName), GetGUIElementHeight(elmFrameTitle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   elmFrameDelimiter := _gui_CreateFrameBorderExt('', elmShardGames, 'halParentLeft', 'valParentTop', GetGUIElementPositionX(elmFrameDelimiter)+round(listWidth*cWidthKoefPlayersOnline), GetGUIElementPositionY(elmFrameTitle), 0, GetGUIElementHeight(elmFrameTitle)+maxPageCount*(GetGUIElementHeight(elmFrame))+4*maxPageCount, False);
      [*] = ;   _gui_CreateText('', elmFrameTitle, 'Status', 'halParentLeft', 'valParentTop', 6+GetGUIElementPositionX(elmFrameDelimiter), 0, round(listWidth*cWidthKoefGameName), GetGUIElementHeight(elmFrameTitle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   //_gui_CreateFrameBorderExt('', elmShardGames, 'halParentLeft', 'valParentTop', GetGUIElementPositionX(elmFrameDelimiter)+round(listWidth*cWidthKoefPlayersOnline), GetGUIElementPositionY(elmFrameTitle), 0, GetGUIElementHeight(elmFrameTitle)+maxPageCount*(GetGUIElementHeight(elmFrame))+40+8, False);
      [*] = ;
      [*] = ;   const cShellShardGamesList = 'internetshell.leftpanel.shardgames.list';
      [*] = ;   UpdateShardGamesList(cShellShardGamesList);
      [*] = ;
      [*] = ;   // sync parser, log my actions (hero parsers+stack, my province parsers (player inner buildings in castle parser), playerstack)
      [*] = ;   // sync parser, conflict battles, first player send (hero parsers+stacks to server), server send to second player.
      [*] = ;
      [*] = ;   {const cBtnOffsetY = 44;
      [*] = ;   var ind : Integer = LanPublicServerGetSessionIndexByClientID(LanMyInfoID());
      [*] = ;   var bEnabled : Boolean = (ind<0);
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('btncreate', elmShardGames, '', 'common.btn', 'halParentMiddle', 'valParentBottomHeight', -GetGUITextureWidth('common.btn.normal') div 2, -4, 0, 0, cEventState, 'menu|211.ext', cBtnCreateShardGame);
      [*] = ;   SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementUserBlend(elmBtnHandle, 0.8);
      [*] = ;   _gui_CreateText('', elmBtnHandle, 'menu|211', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   //SetGUIElementEnabled(elmBtnHandle, bEnabled);
      [*] = ;
      [*] = ;   bEnabled := False;
      [*] = ;   ind := GetGUIListBoxItemIndex(elmGamesList);
      [*] = ;   if (ind>=0) then
      [*] = ;   begin
      [*] = ;      var itemValue : String = GetGUIListBoxItemValue(elmGamesList, ind);
      [*] = ;      var gamestate : String = '';
      [*] = ;      if (GetDelimiterStringCount(itemValue, 9, gc_gui_QuoteChar)>1) then
      [*] = ;      gamestate := GetDelimiterStringByIndex(itemValue, 9, gc_gui_QuoteChar, 0);
      [*] = ;      if (gIntRegister_InetSelectedGameID<>0) and ((gamestate='ready') or (gamestate='progress')) then
      [*] = ;        bEnabled := True;
      [*] = ;   end;
      [*] = ;
      [*] = ;   elmHandle := _gui_GetWindow('internetshell.leftpanel.shardgames.btnjoin');
      [*] = ;   var hint : String = GetLocaleTableListItemByID('menu', '212.ext');
      [*] = ;   if (not bEnabled) then
      [*] = ;      hint := hint+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('menu', '213');
      [*] = ;   //SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;
      [*] = ;   elmBtnHandle := _gui_CreateButton('btnjoin', elmShardGames, '', 'common.btn', 'halParentMiddle', 'valParentBottomHeight', GetGUITextureWidth('common.btn.normal') div 2, -4, 0, 0, cEventState, hint, cBtnJoinShardGame);
      [*] = ;   SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementUserBlend(elmBtnHandle, 0.8);
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, bEnabled);
      [*] = ;   _gui_CreateText('', elmBtnHandle, 'menu|212', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);}
      [*] = ;
      [*] = ;   {var tmp : Integer = 104+maxPageCount*(GetGUIElementFontHeight(GetGUIElementFont(elmGamesList)));
      [*] = ;   tmp := tmp+74;
      [*] = ;   elmHandle := _gui_CreateImage('', elmShardGames, 'element.strip.341', 'halParentMiddle', 'valParentTop', 8, cStripMarginT+tmp, 0, 0, 0);
      [*] = ;   elmTextHandle := _gui_CreateText('' , elmHandle, cTextMyShardGames, 'halParentLeft', 'valParentTop', 0, cStripTextMarginT, GetGUIElementWidth(elmHandle), 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);}
      [*] = ;
      [*] = ;   Result := elmShardGames;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateStripHeader(elmParentHandle : Integer; hero : TInetHero; mode, side : Integer) : Integer;
      [*] = ;begin
      [*] = ;   const cStripMarginB = -509;
      [*] = ;   var text : String;
      [*] = ;   case side of
      [*] = ;      0 : begin
      [*] = ;         case mode of
      [*] = ;            1 : text := GetLocaleTableListItemByID('gui', '589');
      [*] = ;            2 : text := GetLocaleTableListItemByID('gui', '613');
      [*] = ;            3 : text := GetLocaleTableListItemByID('gui', '606');
      [*] = ;            //5 : text := GetLocaleTableListItemByID('gui', '47');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      1 : begin
      [*] = ;         case mode of
      [*] = ;            1 : text := GetLocaleTableListItemByID('gui', '104');
      [*] = ;            2 : text := GetLocaleTableListItemByID('menu', '183');
      [*] = ;            //3 : text := GetLocaleTableListItemByID('gui', '606');
      [*] = ;            5 : begin
      [*] = ;               if (hero.level=10) and (hero.class2=0) then
      [*] = ;               text := GetLocaleTableListItemByID('gui', '674')
      [*] = ;               else
      [*] = ;               text := 'menu|184';//GetLocaleTableListItemByID('gui', '602');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var posX : Integer = 56;
      [*] = ;   var posY : Integer = 6;
      [*] = ;   if (text<>'') then
      [*] = ;   begin
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, 'element.strip.341' 'halParentMiddle', 'valParentBottomHeight', 0, cStripMarginB, 0, 0, 0);
      [*] = ;      var elmTextHandle : Integer = _gui_CreateText('' , elmHandle, text, 'halParentLeft', 'valParentTop', posX, posY, 240, 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateHeroTabs(elmParentHandle : Integer; hero : TInetHero; mode : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var posX : Integer = 46;
      [*] = ;   var posY : Integer = 2;
      [*] = ;
      [*] = ;   var elmTabsHandle : Integer = _gui_CreateImage('', elmParentHandle, 'shell.tabshero.3btn.background', 'halParentMiddle', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;   posX := 46;
      [*] = ;   posY := 11;
      [*] = ;
      [*] = ;   var bNoCurHero : Boolean = (hero.class1=0);
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('heropanel_tabs_squad', elmTabsHandle, '', 'map.radialhero.btn.garrison', 'halParentLeft', 'valParentTop', posX, posY, 49, 49, cEventState, 'menu|202', cBtnMode1);
      [*] = ;   if (mode=1) or (gBoolRegister_InetStartBattle) or (bNoCurHero) then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;   var elmHandle : Integer;
      [*] = ;   if (mode=1) then
      [*] = ;   elmHandle := _gui_CreateImage('', elmTabsHandle, 'map.castle.tabs.btn.garrison.checkon', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;
      [*] = ;   elmBtnHandle := _gui_CreateButton('heropanel_tabs_inventory', elmTabsHandle, '', 'map.radialhero.btn.treasury', 'halParentLeft', 'valParentTop', posX+54, posY, 49, 49, cEventState, 'menu|204', cBtnMode2);
      [*] = ;   if (mode=2) or (gBoolRegister_InetStartBattle) or (bNoCurHero) then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;   if (mode=2) then
      [*] = ;   elmHandle := _gui_CreateImage('', elmTabsHandle, 'map.castle.tabs.btn.treasury.checkon', 'halParentLeft', 'valParentTop', posX+54, posY, 0, 0, 0);
      [*] = ;
      [*] = ;   elmBtnHandle := _gui_CreateButton('heropanel_tabs_spellbook', elmTabsHandle, '', 'map.radialhero.btn.magic', 'halParentLeft', 'valParentTop', posX+107, posY, 49, 49, cEventState, 'menu|203', cBtnMode3);
      [*] = ;   if (mode=3) or (gBoolRegister_InetStartBattle) or (bNoCurHero) then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;   if (mode=3) then
      [*] = ;   elmHandle := _gui_CreateImage('', elmTabsHandle, 'map.castle.tabs.btn.library.checkon', 'halParentLeft', 'valParentTop', posX+107, posY, 0, 0, 0);
      [*] = ;
      [*] = ;   elmHandle := _gui_CreateImage('', elmTabsHandle, 'shell.tabshero.1btn.background', 'halParentLeft', 'valParentBottomHeight', 20-GetGUITextureWidth('shell.tabshero.1btn.background'), 0, 0, 0, 0);
      [*] = ;   elmBtnHandle := _gui_CreateButton('', elmTabsHandle, '', 'map.mainpanel.btn.nexthero', 'halParentLeft', 'valParentTop', -77, 27-17, 0, 0, cEventState, '', cBtnHeroList);
      [*] = ;   if (mode=5) or (gBoolRegister_InetStartBattle) then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;   if (mode=5) then
      [*] = ;   elmHandle := _gui_CreateImage('', elmTabsHandle, 'map.mainpanel.btn.nexthero.pressed', 'halParentLeft', 'valParentTop', -77, 27-17, 0, 0, 0);
      [*] = ;   SetGUIElementHint(elmBtnHandle, 'menu|201');
      [*] = ;   if (gBoolRegister_InetStartBattle) then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;
      [*] = ;   Result := elmTabsHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;function SetHeroMode(hero : TInetHero;_elmLeftPanel,_elmRightPanel,_heroMode : Integer;_lastShopScrollPos : Float) : Boolean;
      [*] = ;begin
      [*] = ;   if (gIntRegister_InetWindowMode=2) then
      [*] = ;   begin
      [*] = ;      var elmStripHeaderLeft : Integer = CreateStripHeader(_elmLeftPanel, hero, _heroMode, 0);
      [*] = ;      var elmStripHeaderRight : Integer = CreateStripHeader(_elmRightPanel, hero, _heroMode, 1);
      [*] = ;      var elmHeroTabs : Integer = CreateHeroTabs(_elmLeftPanel, hero, _heroMode);
      [*] = ;      // Troops
      [*] = ;      // mode 0 - none, 1 - army, 2 - inventory, 3 - spells, 4 - hero info, 5 - hero recuit
      [*] = ;      case _heroMode of
      [*] = ;         1 : begin
      [*] = ;            const cSquadMarginL = 110;
      [*] = ;            const cSquadMarginB = 93;
      [*] = ;            var elmSquad : Integer = _gui_CreateImage('squad', _elmLeftPanel, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', cSquadMarginL, 0, GetGUIElementWidth(_elmLeftPanel)-cSquadMarginL*1, GetGUIElementHeight(_elmLeftPanel)-cSquadMarginB, 0);
      [*] = ;            IntRegister0 := elmSquad;
      [*] = ;            GUIExecuteState('ShowCustomHeroSquad');
      [*] = ;
      [*] = ;            const cSquadRecruitMarginL = 33;
      [*] = ;            const cSquadRecruitMarginB = 93;
      [*] = ;            var elmSquadRecruit : Integer = _gui_CreateImage('squad_recruit', _elmRightPanel, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', cSquadRecruitMarginL, 0, GetGUIElementWidth(_elmRightPanel)-cSquadRecruitMarginL*1, GetGUIElementHeight(_elmRightPanel)-cSquadRecruitMarginB, 0);
      [*] = ;            var rank : Integer = gIntRegister_InetRecruitRankMode;
      [*] = ;            IntRegister0 := elmSquadRecruit;
      [*] = ;            IntRegister1 := rank;
      [*] = ;            GUIExecuteState('ShowCustomHeroSquadRecruit');
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            const cInventoryMarginL = 110;
      [*] = ;            const cInventoryMarginB = 93;
      [*] = ;            var elmInventory : Integer = _gui_CreateImage('inventory', _elmLeftPanel, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', cInventoryMarginL, 0, GetGUIElementWidth(_elmLeftPanel)-cInventoryMarginL*1, GetGUIElementHeight(_elmLeftPanel)-cInventoryMarginB, 0);
      [*] = ;            IntRegister0 := elmInventory;
      [*] = ;            GUIExecuteState('ShowCustomHeroInventory');
      [*] = ;
      [*] = ;            const cShopMarginL = 33+29;
      [*] = ;            const cShopMarginB = 93;
      [*] = ;            var elmShop : Integer = _gui_CreateImage('shop', _elmRightPanel, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', cShopMarginL, 0, GetGUIElementWidth(_elmRightPanel)-cShopMarginL*1, GetGUIElementHeight(_elmRightPanel)-cShopMarginB, 0);
      [*] = ;            var rank : Integer = gIntRegister_InetShopRankMode;
      [*] = ;            IntRegister0 := elmShop;
      [*] = ;            IntRegister1 := rank;
      [*] = ;            FloatRegister0 := _lastShopScrollPos;
      [*] = ;            GUIExecuteState('ShowCustomHeroShop');
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            const cSpellbookMarginL = 110;
      [*] = ;            const cSpellbookMarginB = 93;
      [*] = ;            var elmSpellbook : Integer = _gui_CreateImage('spellbook', _elmLeftPanel, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', cSpellbookMarginL, 0, GetGUIElementWidth(_elmLeftPanel)-cSpellbookMarginL*1, GetGUIElementHeight(_elmLeftPanel)-cSpellbookMarginB, 0);
      [*] = ;            IntRegister0 := elmSpellbook;
      [*] = ;            GUIExecuteState('ShowCustomHeroSpellbook');
      [*] = ;
      [*] = ;            const cLibraryMarginL = 33-6;
      [*] = ;            const cLibraryMarginB = 93;
      [*] = ;            var elmLibrary : Integer = _gui_CreateImage('library', _elmRightPanel, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', cLibraryMarginL, 0, GetGUIElementWidth(_elmRightPanel)-cLibraryMarginL*1, GetGUIElementHeight(_elmRightPanel)-cLibraryMarginB, 0);
      [*] = ;            var rank : Integer = gIntRegister_InetLibraryRankMode;
      [*] = ;            IntRegister0 := elmLibrary;
      [*] = ;            IntRegister1 := rank;
      [*] = ;            GUIExecuteState('ShowCustomHeroLibrary');
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            // hero info
      [*] = ;         end;
      [*] = ;         5 : begin
      [*] = ;            //
      [*] = ;            const cHeroRecruitMarginL = 0;
      [*] = ;            const cHeroRecruitMarginB = 93;
      [*] = ;            var elmHeroRecruit : Integer = _gui_CreateImage('herorecruit', _elmLeftPanel, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', cHeroRecruitMarginL, 0, GetGUIElementWidth(_elmLeftPanel)-cHeroRecruitMarginL*1, GetGUIElementHeight(_elmLeftPanel)-cHeroRecruitMarginB, 0);
      [*] = ;            IntRegister0 := elmHeroRecruit;
      [*] = ;            GUIExecuteState('ShowCustomHeroHeroRecruit');
      [*] = ;
      [*] = ;            if (hero.class1>0) then
      [*] = ;            begin
      [*] = ;               const cHeroUpgradeMarginL = 0;
      [*] = ;               const cHeroUpgradeMarginB = 93;
      [*] = ;               var elmHeroUpgrade : Integer = _gui_CreateImage('heroupgrade', _elmRightPanel, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', cHeroUpgradeMarginL, 0, GetGUIElementWidth(_elmRightPanel)-cHeroUpgradeMarginL*1, GetGUIElementHeight(_elmRightPanel)-cHeroUpgradeMarginB, 0);
      [*] = ;               IntRegister0 := elmHeroUpgrade;
      [*] = ;               GUIExecuteState('ShowCustomHeroHeroUpgrade');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// main code starts here
      [*] = ;const cMarginBottom = 0.07;
      [*] = ;const cWindowFrameSize = 16;
      [*] = ;const cMinLeftPanelWidth = 583+cWindowFrameSize;
      [*] = ;const cMinRightPanelWidth = 583+cWindowFrameSize;
      [*] = ;const cMiddleSpace = 0.018;
      [*] = ;const cInfoMarginBottom = -110;
      [*] = ;const cInfoWidth = 264;
      [*] = ;const cInfoHeight = 200;
      [*] = ;const cTabsHeight = 58;
      [*] = ;const cTabsBtnMarginT = -2;
      [*] = ;const cBtnCount = 5;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var viewWidth : Integer = GetViewerWidth();
      [*] = ;var viewHeight : Integer = GetViewerHeight();
      [*] = ;var elmInfoPanel : Integer = 0;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;// input data
      [*] = ;var myInfo : String = LanPublicServerProfInfo;
      [*] = ;const cMaxLevel = 40;
      [*] = ;
      [*] = ;if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;begin
      [*] = ;   gamesStarted := _sa_GetAsInt(myInfo, 12);
      [*] = ;   gamesPlayed := _sa_GetAsInt(myInfo, 14);
      [*] = ;   gamesWin := _sa_GetAsInt(myInfo, 16);
      [*] = ;   exp := _sa_GetAsInt(myInfo, 18);
      [*] = ;
      [*] = ;   level := 1;
      [*] = ;   for i:=1 to cMaxLevel do
      [*] = ;   begin
      [*] = ;      expNextLevel := 40*i*i+360*i;
      [*] = ;      if (expNextLevel>exp) then
      [*] = ;      begin
      [*] = ;         level := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   expPrevLevel := 40*(level-1)*(level-1)+360*(level-1);
      [*] = ;   if (expPrevLevel<0) then expPrevLevel := 0;
      [*] = ;   expNeeded := expNextLevel-expPrevLevel;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   gamesStarted := _sa_GetAsInt(myInfo, 11);
      [*] = ;   gamesPlayed := _sa_GetAsInt(myInfo, 13);
      [*] = ;   gamesWin := _sa_GetAsInt(myInfo, 15);
      [*] = ;   exp := _sa_GetAsInt(myInfo, 17);
      [*] = ;   var averageUnits : Integer = _sa_GetAsInt(myInfo, 19);
      [*] = ;
      [*] = ;   level := 1;
      [*] = ;   //exp := gamesPlayed*75+gamesWin*50;
      [*] = ;   for i:=1 to cMaxLevel do
      [*] = ;   begin
      [*] = ;      expNextLevel := 40*i*i+360*i;
      [*] = ;      if (expNextLevel>exp) then
      [*] = ;      begin
      [*] = ;         level := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   expPrevLevel := 40*(level-1)*(level-1)+360*(level-1);
      [*] = ;   if (expPrevLevel<0) then expPrevLevel := 0;
      [*] = ;   expNeeded := expNextLevel-expPrevLevel;
      [*] = ;   if (gIntRegister_InetPointsMode=0) then
      [*] = ;      gInetBattle.points := gc_lan_maxpoints
      [*] = ;   else
      [*] = ;      gInetBattle.points := gc_lan_startpoints + 150 * (level-1) + 50 * Max(0, level-11) + 50 * Max(0, level-21) + 100 * Max(0, level-31);
      [*] = ;end;
      [*] = ;rank := floor(((i/cMaxLevel)*gPrototypeData.rulerTitles.number));
      [*] = ;karma := 0;
      [*] = ;
      [*] = ;if _log then _log_values('GAME_MODE|HERO_MODE|WINDOW_MODE',gGame.gametype,gIntRegister_InetHeroMode,gIntRegister_InetWindowMode,0,0,0);
      [*] = ;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_smallest,'',fontHandle1);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle); 
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandle3);
      [*] = ;_gui_GetFont(gc_gui_fontsection_astral,'Text',gc_gui_fontsize_largest,'',fontHandle5);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Input',gc_gui_fontsize_default,'',fontHandleInput);
      [*] = ;
      [*] = ;rowHeight := (GetGUIElementFontHeight(fontHandle2)+4);
      [*] = ;var cMarginTop : Float = (1-(cPanelHeight/viewHeight))*0.5;
      [*] = ;var cLeftPanel : Float = 0.373;
      [*] = ;if ((round(cLeftPanel*viewWidth)-cWindowFrameSize*2)<cMinLeftPanelWidth) then
      [*] = ;   cLeftPanel := (cMinLeftPanelWidth+cWindowFrameSize*2)/viewWidth;
      [*] = ;var cRightPanel : Float = cLeftPanel*0.875;
      [*] = ;if ((round(cRightPanel*viewWidth)-cWindowFrameSize*3)<cMinRightPanelWidth) then
      [*] = ;   cRightPanel := (cMinRightPanelWidth+cWindowFrameSize*3)/viewWidth;
      [*] = ;var cSideSpace : Float = (1-cLeftPanel-cRightPanel)/2;
      [*] = ;if (cSideSpace<0) then cSideSpace := 0;
      [*] = ;if (cLeftPanel+cRightPanel>1) then cRightPanel := 1-cLeftPanel;
      [*] = ;
      [*] = ;leftPanelWidth := 599;
      [*] = ;rightPanelWidth := 599;
      [*] = ;
      [*] = ;var middleSpaceWidth : Integer = round(cMiddleSpace*viewWidth)+cWindowFrameSize*2;
      [*] = ;var sideSpaceWidth : Integer = round(cSideSpace*viewWidth);
      [*] = ;sideSpaceWidth := (GetViewerWidth-(leftPanelWidth+middleSpaceWidth+rightPanelWidth+cWindowFrameSize*2)) div 2;
      [*] = ;var panelMarginTop : Integer = round(cMarginTop*viewHeight);
      [*] = ;var panelMarginBottom : Integer = round(cMarginBottom*viewHeight);
      [*] = ;
      [*] = ;var leftPanelPosX : Integer = sideSpaceWidth+cWindowFrameSize;
      [*] = ;var rightPanelPosX : Integer = sideSpaceWidth+leftPanelWidth+middleSpaceWidth+cWindowFrameSize;
      [*] = ;//var panelHeight : Integer = GetViewerHeight-panelMarginTop-panelMarginBottom-cWindowFrameSize;
      [*] = ;//var panelHeight : Integer = cPanelHeight;
      [*] = ;
      [*] = ;var heroMode : Integer = gIntRegister_InetHeroMode;
      [*] = ;
      [*] = ;avatar := 'astral.dialog.portrait.'+IntToStr(gProfile.avatar-1);
      [*] = ;cStyleWhite := '%color('+FormatColorToHex3(gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB)+')%';
      [*] = ;
      [*] = ;_misc_FadeMenu('main_menu',1);
      [*] = ;
      [*] = ;var prevElmParentHandle : Integer = _gui_GetWindow('internetshell');
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;var elmShopScrollLayer : Integer = _gui_GetWindow('internetshell.rightpanel.shop.scroll_layer');
      [*] = ;var lastShopScrollPos : Float = 0;
      [*] = ;if (elmShopScrollLayer<>0) then
      [*] = ;begin
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmShopScrollLayer);
      [*] = ;   if (elmVScroll<>0) then
      [*] = ;      lastShopScrollPos := GetGUIScrollBarPosition(elmVScroll);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('internetshell' _gui_GetLayerI(), 'halLeft', 'valTop', 0, 0, GetViewerWidth(), GetViewerHeight(), 0);
      [*] = ;
      [*] = ;if gGame.gametype <> gc_GameTypeLanShard then
      [*] = ;begin
      [*] = ;   elmInfoPanel := _gui_CreateLargeWindow(elmParentHandle, 'infopanel', 'halParentMiddle', 'valParentBottomHeight', 0, -cInfoMarginBottom, cInfoWidth, cInfoHeight, false);
      [*] = ;   SetGUIElementPressState(GetGUIElementIndexByNameParent('background.eventlayer', elmInfoPanel), cResetDragElementState);
      [*] = ;   SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmInfoPanel), 0.8);
      [*] = ;   SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmInfoPanel), 0.85);
      [*] = ;   SetGUIElementVisible(GetGUIElementIndexByNameParent('header', elmInfoPanel), False);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmLeftPanel : Integer = _gui_CreateLargeWindow(elmParentHandle, 'leftpanel', 'halParentLeft', 'valParentTop', leftPanelPosX, panelMarginTop, leftPanelWidth, cPanelHeight, false);
      [*] = ;SetGUIElementPressState(GetGUIElementIndexByNameParent('background.eventlayer', elmLeftPanel), cResetDragElementState);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmLeftPanel), 0.8);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmLeftPanel), 0.85);
      [*] = ;SetGUIElementVisible(GetGUIElementIndexByNameParent('header', elmLeftPanel), False);
      [*] = ;
      [*] = ;var elmRightPanel : Integer = _gui_CreateLargeWindow(elmParentHandle, 'rightpanel', 'halParentLeft', 'valParentTop', rightPanelPosX, panelMarginTop, rightPanelWidth, cPanelHeight, false);
      [*] = ;SetGUIElementPressState(GetGUIElementIndexByNameParent('background.eventlayer', elmRightPanel), cResetDragElementState);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmRightPanel), 0.8);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmRightPanel), 0.85);
      [*] = ;SetGUIElementVisible(GetGUIElementIndexByNameParent('header', elmRightPanel), False);
      [*] = ; 
      [*] = ;procedure UpdateSelectedPlayer(elmPlayers : Integer);
      [*] = ;begin
      [*] = ;   var elmPlayersList : Integer = GetGUIElementIndexByNameParent('list', elmPlayers);
      [*] = ;   SetGUIListBoxItemIndex(elmPlayersList, GetGUIListBoxItemIndexOfTag(elmPlayersList, gIntRegister_InetSelectedPlayerID));
      [*] = ;   _inet_PlayerSelected(elmPlayersList, false, false);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmPlayers : Integer;
      [*] = ;if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;begin
      [*] = ;   var elmProfileInfo : Integer = CreateProfileInfo(elmRightPanel);
      [*] = ;   CreateShardGames(elmLeftPanel);
      [*] = ;   elmPlayers := CreatePlayers(elmRightPanel, elmProfileInfo);
      [*] = ;   CreateChat(elmRightPanel, elmProfileInfo);
      [*] = ;   gIntRegister_InetWindowMode := 3;
      [*] = ;   if gIntRegister_InetSelectedPlayerID > 0 then
      [*] = ;      UpdateSelectedPlayer(elmPlayers);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if gIntRegister_InetWindowMode = 3 then
      [*] = ;      gIntRegister_InetWindowMode := 1;
      [*] = ;   if (gIntRegister_InetWindowMode=1) then
      [*] = ;   begin
      [*] = ;      var elmProfileInfo : Integer = CreateProfileInfo(elmRightPanel);
      [*] = ;      elmPlayers := CreatePlayers(elmRightPanel, elmProfileInfo);
      [*] = ;      CreateChat(elmRightPanel, elmProfileInfo);
      [*] = ;      CreateLeftSide(elmLeftPanel);
      [*] = ;      if gIntRegister_InetSelectedPlayerID > 0 then
      [*] = ;         UpdateSelectedPlayer(elmPlayers);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ; 
      [*] = ; 
      [*] = ;// LEFT PANEL
      [*] = ;var elmTabs : Integer = _gui_CreateImage('tabs', elmParentHandle, gc_gui_material_blank_0+'asd', 'halParentMiddle', 'valParentTop', 0, 0, 0, GetGUITextureHeight('shell.buttonstab'), 0);
      [*] = ;var elmHandle : Integer = _gui_CreateImage('background', elmTabs, 'shell.buttonstab', 'halParentMiddle', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;SetGUIElementUserColor(elmHandle, 0.8, 0.8, 0.8, 0.85);
      [*] = ;
      [*] = ;var cTabsBtnMarginL : Integer = 226;
      [*] = ;
      [*] = ;if (gBoolRegister_IsHotSeat) then
      [*] = ;begin
      [*] = ;   for i:=0 to cBtnCount-1 do
      [*] = ;   begin
      [*] = ;      var tag : Integer = 0;
      [*] = ;      var text : String = '';
      [*] = ;      var enabled : Boolean = True;
      [*] = ;      var checked : Boolean = False;
      [*] = ;      case i of
      [*] = ;         0 : begin
      [*] = ;            text := ' ';
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            text := 'menu|199';
      [*] = ;            tag := cBtnHotSeatPreparePlayer1;
      [*] = ;            if (gIntRegister_HotSeatActivePlayer=0) then
      [*] = ;               checked := true;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            text := 'menu|200';
      [*] = ;            tag := cBtnHotSeatPreparePlayer2;
      [*] = ;            if (gIntRegister_HotSeatActivePlayer=1) then
      [*] = ;               checked := true;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            text := 'menu|173';
      [*] = ;            tag := cBtnExitToMainMenu;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (text <> '') then
      [*] = ;      begin
      [*] = ;         if (text = ' ') then
      [*] = ;         begin
      [*] = ;            var elmHandle : Integer = _gui_CreateImage('', elmTabs, 'shell.button.place' 'halParentMiddle', 'valParentMiddle', round((i-cBtnCount*0.5+0.5)*cTabsBtnMarginL), cTabsBtnMarginT, 0, 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.9);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var elmHandle : Integer = _gui_CreateButton('', elmTabs, '', 'common.btn', 'halParentMiddle', 'valParentMiddle', round((i-cBtnCount*0.5+0.5)*cTabsBtnMarginL), cTabsBtnMarginT, 0, 0, cEventState, '', tag);
      [*] = ;            SetGUIElementVisibleProperties(elmHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.8);
      [*] = ;            SetGUIElementEnabled(elmHandle, enabled);
      [*] = ;            SetGUIElementChecked(elmHandle, checked);
      [*] = ;            _gui_CreateText('', elmHandle, text, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   for i:=0 to cBtnCount-1 do
      [*] = ;   begin
      [*] = ;      var tag : Integer = 0;
      [*] = ;      var text : String = '';
      [*] = ;      var enabled : Boolean = True;
      [*] = ;      var checked : Boolean = False;
      [*] = ;      case i of
      [*] = ;         0 : begin
      [*] = ;            {text := 'gui|797';
      [*] = ;            tag := cBtnShardGames;
      [*] = ;            if (gIntRegister_InetWindowMode=3) then
      [*] = ;               checked := true;}
      [*] = ;            if gGame.gametype <> gc_GameTypeLanShard then
      [*] = ;            begin
      [*] = ;               text := 'gui|798';
      [*] = ;               tag := cBtnMain;
      [*] = ;               if (gIntRegister_InetWindowMode=1) then
      [*] = ;                  checked := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            {text := 'menu|170';
      [*] = ;            tag := cBtnMain;
      [*] = ;            if (gIntRegister_InetWindowMode=1) or (gIntRegister_InetWindowMode=2) then
      [*] = ;               checked := true;}
      [*] = ;            if gGame.gametype <> gc_GameTypeLanShard then
      [*] = ;            begin
      [*] = ;               text := 'menu|171';
      [*] = ;               tag := cBtnPrepare;
      [*] = ;               if (gIntRegister_InetWindowMode=2) then
      [*] = ;                  checked := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;            begin
      [*] = ;               text := 'menu|173';
      [*] = ;               tag := cBtnExitToMainMenu;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            if gGame.gametype <> gc_GameTypeLanShard then
      [*] = ;            begin
      [*] = ;               text := 'menu|173';
      [*] = ;               tag := cBtnExitToMainMenu;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if text <> '' then
      [*] = ;      begin
      [*] = ;         var elmHandle : Integer = _gui_CreateButton('', elmTabs, '', 'common.btn', 'halParentMiddle', 'valParentMiddle', round((i-cBtnCount*0.5+0.5)*cTabsBtnMarginL), cTabsBtnMarginT, 0, 0, cEventState, '', tag);
      [*] = ;         SetGUIElementVisibleProperties(elmHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.8);
      [*] = ;         SetGUIElementEnabled(elmHandle, enabled);
      [*] = ;         SetGUIElementChecked(elmHandle, checked);
      [*] = ;         _gui_CreateText('', elmHandle, text, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gGame.gametype <> gc_GameTypeLanShard then
      [*] = ;begin
      [*] = ;   var hint : String = 'menu|174';
      [*] = ;   var tag : Integer;
      [*] = ;
      [*] = ;   if (not gBoolRegister_IsHotSeat) then
      [*] = ;      tag := cBtnStartBattle
      [*] = ;   else
      [*] = ;      tag := cBtnHotSeatStartBattle;
      [*] = ;   elmHandle := _gui_CreateButton('', elmTabs, '', 'shell.startbutton', 'halParentMiddle', 'valParentMiddle', 0, cTabsBtnMarginT+14, 0, 0, cEventState, hint, tag);
      [*] = ;
      [*] = ;   var heroScore : Integer;
      [*] = ;   var maxScore : Integer;
      [*] = ;   if (gBoolRegister_IsHotSeat) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_HotSeatActivePlayer=0) then
      [*] = ;      begin
      [*] = ;         SetHeroMode(gHotSeatPlayer1.hero[gHotSeatPlayer1.curhero],elmLeftPanel,elmRightPanel,heroMode,lastShopScrollPos);
      [*] = ;         heroScore := _inet_CalcHeroPrice(gHotSeatPlayer1.hero[gHotSeatPlayer1.curhero]);
      [*] = ;         maxScore := gc_hotseat_maxpoints;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         SetHeroMode(gHotSeatPlayer2.hero[gHotSeatPlayer2.curhero],elmLeftPanel,elmRightPanel,heroMode,lastShopScrollPos);
      [*] = ;         heroScore := _inet_CalcHeroPrice(gHotSeatPlayer2.hero[gHotSeatPlayer2.curhero]);
      [*] = ;         maxScore := gc_hotseat_maxpoints;
      [*] = ;      end
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      SetHeroMode(gInetBattle.hero[gInetBattle.curhero],elmLeftPanel,elmRightPanel,heroMode,lastShopScrollPos);
      [*] = ;      heroScore := _inet_CalcHeroPrice(gInetBattle.hero[gInetBattle.curhero]);
      [*] = ;      maxScore := gInetBattle.points;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // score panel
      [*] = ;   if elmInfoPanel <> 0 then
      [*] = ;   begin
      [*] = ;      var text : String;
      [*] = ;      if (heroScore<=maxScore) then
      [*] = ;         text := GetLocaleTableListItemByID('menu', '154')+': '+cStyleWhite+IntToStr(heroScore)+cStyleDefault+' '+GetLocaleTableListItemByID('menu', '155')+' '+IntToStr(maxScore)
      [*] = ;      else
      [*] = ;         text := GetLocaleTableListItemByID('menu', '154')+': '+'%color(attention)%'+IntToStr(heroScore)+cStyleDefault+' '+GetLocaleTableListItemByID('menu', '155')+' '+IntToStr(maxScore);
      [*] = ;      _gui_CreateText('', elmInfoPanel, text, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmInfoPanel), GetGUIElementHeight(elmInfoPanel)+cInfoMarginBottom, 'halMiddle', 'valMiddle', fontHandle5, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gGame.gametype = gc_GameTypeLanShard then
      [*] = ;   _inet_RefreshLoadGameProgress(0);
      [*] = ;
      [*] = ;
      [*] = ;// FOOTER
      [*] = ;_gui_RootWindowAddM(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle,cEventState);
      [*] = ;_cmd_RegisterWindowState(elmParentHandle,'VVK.InternetShellCommands',cEventStateChat);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeWindow_VVK(elmParentHandle,gc_gui_FadeTime0_2,0);
      [*] = ;
      [*] = ;// FADE QUESTION WINDOW IF EXISTS
      [*] = ;_gui_FadeWindow_VVK(_gui_GetWindow(cQuestionDialogWindowName),gc_gui_FadeTime0_2,2);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister0 := elmParentHandle;
   struct.end
section.end

