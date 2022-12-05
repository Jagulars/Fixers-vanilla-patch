section.begin
   Name = ShowAstralChat
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI\COMMON.INC\SHOWASTRALCHAT';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;const cSizeShowProfileBar = 6;
      [*] = ;const cPlayersBottomThreshold = 450; // width
      [*] = ;const cSizeShowPlayersOnBottom = 6; 
      [*] = ;const cWindowFrameSize = 16;
      [*] = ;const cBorderFrameSize = 16;
      [*] = ;const cPanelHeight = 88;
      [*] = ;const cListBoxPlayers = 30;
      [*] = ;const cListBoxChat = 40;
      [*] = ;const cEventStateChat = 'EvLanShellChat';
      [*] = ;const cEventState = 'EventAstralChat';
      [*] = ;const cMarginBottom = 0.07;
      [*] = ;var viewWidth : Integer = GetViewerWidth();
      [*] = ;var viewHeight : Integer = GetViewerHeight();
      [*] = ;
      [*] = ;var chatPanelWidth : Integer;
      [*] = ;if (gGame.gametype = gc_GameTypeNone) and (mode <> 2) then // reduce the width of window in main menu unless modal (when too small resolution)
      [*] = ;   chatPanelWidth := _inet_GetAstralChatWidth()
      [*] = ;else
      [*] = ;   chatPanelWidth := 600;
      [*] = ;
      [*] = ;var playersListWidth : Integer = 244;//188;
      [*] = ;var playersListBottom : Integer = 0;
      [*] = ;
      [*] = ;var chatSize : Integer = gProfile.astralchatsize;
      [*] = ;if (gGame.gametype = gc_GameTypeNone) then
      [*] = ;begin
      [*] = ;   if (chatSize >= 18) and (viewHeight <= 800) then
      [*] = ;      chatSize := 14
      [*] = ;   else
      [*] = ;   if (chatSize >= 20) and (viewHeight <= 1000) then
      [*] = ;      chatSize := 18;
      [*] = ;end;
      [*] = ;
      [*] = ;{if (chatPanelWidth < cPlayersBottomThreshold) and (gGame.gametype = gc_GameTypeNone) then // move players list to bottom if main menu screen is not large enough. Not functional
      [*] = ;begin
      [*] = ;   playersListWidth := 0;
      [*] = ;   if chatSize >= cSizeShowPlayersOnBottom then
      [*] = ;   begin
      [*] = ;      playersListBottom := chatSize div 2;
      [*] = ;      playersListWidth := chatPanelWidth - cBorderFrameSize;
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;var cMarginTop : Float = 0.05;//cPanelHeight/viewHeight;//(1-(cPanelHeight/viewHeight))*0.5;
      [*] = ;var panelMarginTop : Integer = round(cMarginTop*viewHeight);
      [*] = ;var panelMarginBottom : Integer = round(cMarginBottom*viewHeight);
      [*] = ;var chatPanelPosX : Integer = viewWidth - chatPanelWidth - cBorderFrameSize - cWindowFrameSize;
      [*] = ;const cButtonX = -80;
      [*] = ;const cButtony = -20;
      [*] = ;const cBtnCloseTag = 101;
      [*] = ;const cBtnShrinkTag = 102;
      [*] = ;const cBtnExpandTag = 103;
      [*] = ;const cBtnOpenTag = 104;
      [*] = ;const cBtnMuteTag = 105;
      [*] = ;const cBtnExpandProfileTag = 106;
      [*] = ;
      [*] = ;var prevMode : Integer = gIntRegister_AstralChatMode;
      [*] = ;gIntRegister_AstralChatMode := 0;
      [*] = ;if (mode = 1) or (mode = 3) or (not IsLanPublicServerMode) then
      [*] = ;begin
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;   var posX : Integer = viewWidth - 129;
      [*] = ;   var posY : Integer = panelMarginTop - 38; 
      [*] = ;   _sys_FillRect(tmp_pos,posX,posY,0,0);
      [*] = ;   var elmOpenButton : Integer = _gui_CreateImage_VVK('open_chat_button',_gui_GetLayerI(),'map.hideminimap.background',gc_gui_align_parent_lt,tmp_pos);
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('btnOpen', elmOpenButton, '', 'gamepanel03.btn.sort.down', 'halParentMiddle', 'valParentMiddle', 0, 0, 0, 0, cEventState, 'menu|astral_chat', cBtnOpenTag);
      [*] = ;   SetGUIElementUserBlend(elmOpenButton, 0.8);
      [*] = ;   
      [*] = ;   if (mode = 1) and (not ((GetLanMode = 0) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle)))) then // not lobby
      [*] = ;      gIntRegister_AstralChatMode := 1
      [*] = ;   else if (mode = 3) then // forced minimization, preserve previous mode
      [*] = ;      gIntRegister_AstralChatMode := prevMode;
      [*] = ;   
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;//else
      [*] = ;//   SetGUIElementUserBlend(GetGUIElementIndexByNameParent('open_chat_button',_gui_GetLayerI()), 0.1);
      [*] = ;   //_gui_FadeElement(GetGUIElementIndexByNameParent('open_chat_button',_gui_GetLayerI()), gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;
      [*] = ;var fontHandle, fontHandle2, fontHandle5, cStyleWhite : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;_gui_GetFont(gc_gui_fontsection_astral,'Text',gc_gui_fontsize_largest,'',fontHandle5);
      [*] = ;cStyleWhite := '%color('+FormatColorToHex3(gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB)+')%';
      [*] = ;const cStyleDefault = '%color(default)%';
      [*] = ;var avatar : String = 'astral.dialog.portrait.'+IntToStr(gProfile.avatar-1);
      [*] = ;var rowHeight : Integer = (GetGUIElementFontHeight(fontHandle2)+4);
      [*] = ;            
      [*] = ;var chatHeight : Integer = chatSize * rowHeight + 6;
      [*] = ;var elmProfileHeight : Integer = 0;
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = _gui_GetWindow('internetshell');
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;var prevInputText : String = GetGUIElementText(_gui_GetWindow('internetshell.rightpanel.chat.chatinput.text'));
      [*] = ;
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
      [*] = ;   var count : Integer = GetGUIListBoxItemsCount(elmHandle);
      [*] = ;   var topIndex  : Integer = GetGUIListBoxTopIndex(elmHandle);
      [*] = ;   var elmScrollHandle : Integer = GetGUIListBoxScrollerHandle(elmHandle);
      [*] = ;   var rowheight : Integer = GetGUIListBoxRowHeight(elmHandle);
      [*] = ;   var step : Float = ((GetGUIElementHeight(elmHandle)-rowheight)/rowheight);
      [*] = ;   SetGUIScrollBarPosition(elmScrollHandle, (topIndex/(count-step)));
      [*] = ;end;
      [*] = ;
      [*] = ;function CreatePlayers(elmParentHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   const cPlayersTextMarginL = 5;
      [*] = ;   const cPlayersTextMarginB = -32;
      [*] = ;   const cScrollOffset = -7;
      [*] = ;   const cBtnOffsetY = 44;
      [*] = ;
      [*] = ;   var playersFontHandle : String = fontHandle2;
      [*] = ;   var playersLineHeight : Integer = GetGUIElementFontHeight(playersFontHandle);
      [*] = ;   var playersMarginT : Integer = cBorderFrameSize*2;
      [*] = ;   var playersWidth : Integer = playersListWidth-cBorderFrameSize;
      [*] = ;
      [*] = ;   //var b_no : Integer;
      [*] = ;   //var playersHeight : Integer = round((cPanelHeight-elmProfileHeight)-cBorderFrameSize*3-4);
      [*] = ;   var playersHeight : Integer = chatHeight;//chatSize * (GetGUIElementFontHeight(fontHandle2)+4) + 6; // use chat line heights
      [*] = ;   if playersListBottom > 0 then
      [*] = ;   begin
      [*] = ;      playersMarginT := playersMarginT + chatHeight div 2 + 6;
      [*] = ;      playersHeight := playersHeight div 2;// - 8;
      [*] = ;      chatHeight := chatHeight div 2 + 3;
      [*] = ;   end;
      [*] = ;   {if elmProfileHeight > 0 then
      [*] = ;   begin
      [*] = ;      playersMarginT := playersMarginT + 4;
      [*] = ;      playersHeight := playersHeight - rowHeight;
      [*] = ;   end;}
      [*] = ;
      [*] = ;   //playersHeight := ClampToIntStep(playersHeight, playersLineHeight);
      [*] = ;   var maxVisibleCount : Integer = playersHeight div (playersLineHeight+4);
      [*] = ;
      [*] = ;   var chatWidth : Integer = chatPanelWidth-cBorderFrameSize*2-playersListWidth;
      [*] = ;   var elmPlayers : Integer = _gui_CreateFrameBorder('players', elmParentHandle, 'halParentLeft', 'valParentTop', cBorderFrameSize*2+(chatWidth), playersMarginT, playersWidth, playersHeight{+cPlayersTextMarginB});
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
      [*] = ;   SetGUIElementAllPositionRect(elmPlayersList, 0, 0, GetGUIElementWidth(elmPlayers)-cPlayersListScrollMarginR, GetGUIListBoxRowHeight(elmPlayersList)*maxVisibleCount);
      [*] = ;   SetGUIListBoxVisibleRows(elmPlayersList, maxVisibleCount);
      [*] = ;   SetGUIListBoxItemIndexSilent(elmPlayersList, -1);
      [*] = ;   SetGUIListBoxMouseTrack(elmPlayersList, 3);
      [*] = ;   SetGUIListBoxMouseTrackMaterialName(elmPlayersList, gc_gui_material_blank_0{'gamepanel03.combobox.line.hover'});
      [*] = ;   SetGUIListBoxMouseTrackFontColor(elmPlayersList, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;
      [*] = ;   SetGUIElementCursorByName(elmPlayersList, 'crHand');
      [*] = ;
      [*] = ;   // - setup scroller
      [*] = ;   if (chatSize > 2) and ((playersListBottom = 0) or (chatSize > cSizeShowPlayersOnBottom)) then
      [*] = ;   begin
      [*] = ;      var elmScroll : Integer = GetGUIListBoxScrollerHandle(elmPlayersList);
      [*] = ;      SetGUIElementMaterialOffset(elmScroll, -5, 0);
      [*] = ;      SetGUIElementAllPositionRect(elmScroll, 15+cPlayersListScrollMarginR, 5, 18, 20{GetGUIListBoxRowHeight(elmPlayersList)*(maxVisibleCount-2)}-5*2);
      [*] = ;      SetGUIElementMaterial(elmScroll, 'map.dialog.scroller.tile');
      [*] = ;      SetGUIScrollButtonSource(elmScroll, 0, 'map.dialog.scroller.up', True);
      [*] = ;      SetGUIScrollButtonSource(elmScroll, 1, 'map.dialog.scroller.slider', True);
      [*] = ;      SetGUIScrollButtonSource(elmScroll, 2, 'map.dialog.scroller.down', True);
      [*] = ;   end;
      [*] = ;
      [*] = ;   const cShellClientsList = 'internetshell.rightpanel.players.list';
      [*] = ;   var exclude_id : Integer = 0;//LanMyInfoID();
      [*] = ;   //if mode = 2 then
      [*] = ;   //  exclude_id := 0;
      [*] = ;   _inet_UpdateClientsList(cShellClientsList, exclude_id);
      [*] = ;
      [*] = ;   {if gGame.gametype = gc_GameTypeLanShard then
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
      [*] = ;      var elmGamesList,ind: Integer;
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
      [*] = ;   }
      [*] = ;   Result := elmPlayers;
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
      [*] = ;function CreateChat(elmParentHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   const cChatTextMarginL = 5;
      [*] = ;   const cChatTextMarginB = -32;
      [*] = ;   const cScrollOffset = -7;
      [*] = ;   var r_pos : TRectangle;
      [*] = ;   var chatFontHandle : String = fontHandle2;
      [*] = ;   var chatLineHeight : Integer = GetGUIElementFontHeight(chatFontHandle);
      [*] = ;   var chatMarginT : Integer = cBorderFrameSize*2 + elmProfileHeight;
      [*] = ;   var chatWidth : Integer = chatPanelWidth-cBorderFrameSize*2;
      [*] = ;   
      [*] = ;   if playersListBottom = 0 then
      [*] = ;      chatWidth := chatWidth - playersListWidth;
      [*] = ;   
      [*] = ;   if elmProfileHeight > 0 then
      [*] = ;   begin
      [*] = ;      chatMarginT := chatMarginT + 4;
      [*] = ;      if playersListBottom = 0 then
      [*] = ;         chatHeight := chatHeight - elmProfileHeight;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   //var chatHeight : Integer = round((cPanelHeight-elmProfileHeight)-cBorderFrameSize*3-4);
      [*] = ;   //chatHeight := ClampToIntStep(chatHeight, chatLineHeight);
      [*] = ;   var elmChat : Integer = _gui_CreateFrameBorder('chat', elmParentHandle, 'halParentLeft', 'valParentTop', cBorderFrameSize, chatMarginT, chatWidth, chatHeight{+cChatTextMarginB});
      [*] = ;
      [*] = ;   // Scroll layer and save file list
      [*] = ;   var chatTextWidth : Integer = GetGUIElementWidth(elmChat)-cChatTextMarginL*2;
      [*] = ;   var elmChatHistory : Integer = AddNewElementByClassNameParent('history', 'TXGuiListBox', cListBoxChat, elmChat);
      [*] = ;
      [*] = ;   const cChatHistoryScrollMarginR = 7;
      [*] = ;   SetGUIElementPressState(elmChatHistory, cEventState);
      [*] = ;   SetGUIElementFont(elmChatHistory, chatFontHandle);
      [*] = ;   SetGUIElementColor(elmChatHistory, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementAlign(elmChatHistory, 'halParentLeft', 'valParentTop');
      [*] = ;   SetGUIElementAllPositionRect(elmChatHistory, 0, 0, GetGUIElementWidth(elmChat)-cChatHistoryScrollMarginR, GetGUIElementHeight(elmChat));
      [*] = ;   SetGUIElementMaterial(elmChatHistory,  gc_gui_material_blank_0{'common.slider.middle'});
      [*] = ;   SetGUIListBoxSelectedMaterialName(elmChatHistory, gc_gui_material_blank_0{'gamepanel03.combobox.line.selected'});
      [*] = ;
      [*] = ;   SetGUIElementTextAlign(elmChatHistory, 'halLeft', 'valTop', 5, -5);
      [*] = ;   SetGUIListBoxRowHeight(elmChatHistory, rowHeight);
      [*] = ;   SetGUIListBoxVisibleRows(elmChatHistory, -1);
      [*] = ;   SetGUIListBoxItemIndexSilent(elmChatHistory, -1);
      [*] = ;   SetGUIListBoxMouseTrack(elmChatHistory, 2);
      [*] = ;   SetGUIListBoxMouseTrackMaterialName(elmChatHistory, gc_gui_material_blank_0{'gamepanel03.combobox.line.hover'});
      [*] = ;   SetGUIListBoxMouseTrackFontColor(elmChatHistory, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;
      [*] = ;   // - setup scroller
      [*] = ;   if (chatSize - elmProfileHeight div rowHeight > 2) then
      [*] = ;   begin
      [*] = ;      var elmScroll : Integer = GetGUIListBoxScrollerHandle(elmChatHistory);
      [*] = ;      SetGUIElementMaterialOffset(elmScroll, -5, 0);
      [*] = ;      SetGUIElementAllPositionRect(elmScroll, 22, 5, 18, GetGUIElementHeight(elmChatHistory)-5*2);
      [*] = ;      SetGUIElementMaterial(elmScroll, 'map.dialog.scroller.tile');
      [*] = ;      SetGUIScrollButtonSource(elmScroll, 0, 'map.dialog.scroller.up', True);
      [*] = ;      SetGUIScrollButtonSource(elmScroll, 1, 'map.dialog.scroller.slider', True);
      [*] = ;      SetGUIScrollButtonSource(elmScroll, 2, 'map.dialog.scroller.down', True);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var inputWidth : Integer = chatTextWidth+73;
      [*] = ;   if playersListBottom = 0 then
      [*] = ;      inputWidth := inputWidth + playersListWidth;
      [*] = ;   var inputMarginT : Integer = GetGUIElementHeight(elmChat)-2;
      [*] = ;   if playersListBottom > 0 then
      [*] = ;   begin
      [*] = ;      inputMarginT := inputMarginT + chatHeight - rowHeight;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   const cMaxLength = 1024;
      [*] = ;   var inputBoxMarginL : Integer = playersListWidth div 2;
      [*] = ;   if playersListBottom > 0 then
      [*] = ;      inputBoxMarginL := 0;
      [*] = ;   _sys_FillRect(r_pos, inputBoxMarginL, inputMarginT, inputWidth, 0);
      [*] = ;   var inputField : Integer = _gui_CreateInputControl_VVK('chatinput',elmChat,'', gc_gui_align_parent_mt,false,r_pos,cMaxLength, cEventStateChat, '');
      [*] = ;   
      [*] = ;   if prevInputText <> '' then
      [*] = ;      SetGUIElementText(inputField, prevInputText);
      [*] = ;   
      [*] = ;   UpdateChat(_gui_GetWindow('internetshell.rightpanel.chat.history'));
      [*] = ;
      [*] = ;   Result := elmChat;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateProfileInfo(elmParentHandle: Integer) : Integer;
      [*] = ;begin
      [*] = ;   var profileWidth : Integer = chatPanelWidth-cBorderFrameSize*2;
      [*] = ;   var profileHeight : Integer = rowHeight;
      [*] = ;   if playersListBottom = 0 then
      [*] = ;      profileWidth := profileWidth - playersListWidth;
      [*] = ;   
      [*] = ;   
      [*] = ;   if expandedProfile then
      [*] = ;   begin
      [*] = ;      const cBreakLineChar = 13; 
      [*] = ;      profileMessage := GetGUIWrappedTextFormatByFont(fontHandle, profileMessage, profileWidth-8);
      [*] = ;      profileMessage := StrReplace(profileMessage, ' ', '_');
      [*] = ;      var lines : Integer = GetDelimiterStringCount(profileMessage, cBreakLineChar, gc_gui_QuoteChar);
      [*] = ;      profileMessage := StrReplace(profileMessage, '_', ' ');
      [*] = ;      var messageHeight : Integer = lines * GetGUIElementFontHeight(fontHandle);
      [*] = ;      
      [*] = ;      var air : Integer = lines * rowHeight - messageHeight;
      [*] = ;      profileHeight := rowHeight * 2 + messageHeight - air div rowHeight;
      [*] = ;      if chatSize * rowHeight < profileHeight then
      [*] = ;         profileHeight := chatSize * rowHeight;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   // profile info block
      [*] = ;   {const cAvatarMarginL = 0;
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
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('avatar', elmProfileAvatarInfo, avatar, 'halParentLeft', 'valParentTop', cAvatarMarginL, cAvatarMarginT, cAvatarSizeX, cAvatarSizeY, 0);}
      [*] = ;
      [*] = ;   var elmProfileInfo : Integer = _gui_CreateFrameBorder('profile', elmParentHandle, 'halParentLeft', 'valParentTop', cBorderFrameSize, cBorderFrameSize*2, profileWidth, profileHeight);
      [*] = ;   elmProfileHeight := GetGUIElementHeight(elmProfileInfo);
      [*] = ;
      [*] = ;   // expand profile button
      [*] = ;   var elmShowProfileBtn : Integer = _gui_CreateCheckBox('expand_button', elmProfileInfo, false, 'menu|172', 'halParentLeft', 'valParentTop', 0, 0, cEventState, '', cBtnExpandProfileTag);
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
      [*] = ;         var elmTextHandle : Integer = _gui_CreateText('version', elmProfileInfo, '', 'halParentMiddle', 'valParentTop', 0, rowHeight, profileWidth, GetGUIElementFontHeight(fontHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;            
      [*] = ;         var elmGuiLayer : Integer = AddNewElementByClassNameParent('textLayer', 'TXGuiLayer', 0, elmProfileInfo);
      [*] = ;         SetGUIElementAlign(elmGuiLayer, 'halParentLeft', 'valParentTop');
      [*] = ;         SetGUIElementAllPositionRect(elmGuiLayer, 0, rowHeight*2, profileWidth, profileHeight - rowHeight*2);
      [*] = ;         SetGUIElementMaterial(elmGuiLayer, 'misc.blank.black.alpha.0');
      [*] = ;         var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;         SetGUIElementAlign(elmVScroll, 'halParentLeft', 'valParentTop');
      [*] = ;         SetGUIElementMaterialOffset(elmVScroll, 0, 0);
      [*] = ;         SetGUIElementAllPositionRect(elmVScroll, 0, 0, profileWidth-8, profileHeight - rowHeight*2);
      [*] = ;         SetGUIScrollEnabled(elmGuiLayer, True);
      [*] = ;         elmTextHandle := _gui_CreateText('message', elmGuiLayer, profileMessage, 'halParentLeft', 'valParentTop', 0, 0, profileWidth-8, profileHeight - rowHeight*2, 'halLeft', 'valTop', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      SetGUIElementEnabled(elmShowProfileBtn, false);
      [*] = ;      SetGUIElementUserBlend(elmShowProfileBtn, 0.4);
      [*] = ;   end;
      [*] = ;      
      [*] = ;   // mute button
      [*] = ;   var elmMuteButton : Integer;
      [*] = ;   var posX : Integer = -188;
      [*] = ;   xOff := 164;
      [*] = ;   txOff := 24;
      [*] = ;   elmMuteButton := _gui_CreateCheckBox('mute', elmProfileInfo, false, 'menu|88', 'halParentRight', 'valParentTop', posX, 0, cEventState, '', cBtnMuteTag);
      [*] = ;   SetGUIElementTextAlign(elmMuteButton, 'halRight', 'valMiddle', 0, 0);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'UpProperty', 'common.checkbox.normal', xOff, yOff, txOff, tyOff, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'HoverProperty', 'common.checkbox.hover', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'DownProperty', 'common.checkbox.pressed', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'DisableProperty', 'common.checkbox.disabled', xOff, yOff, txOff, tyOff, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmMuteButton, 'CheckOnProperty', 'common.checkbox.checkon', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementEnabled(elmMuteButton, false);
      [*] = ;   SetGUIElementUserBlend(elmMuteButton, 0.4);
      [*] = ;   
      [*] = ;   // name
      [*] = ;   //var elmTextHandle : Integer = _gui_CreateText('name', elmProfileInfo, ''{cStyleWhite+gProfile.name}, 'halParentMiddle', 'valParentMiddle', 0, 0, profileWidth-GetGUIElementWidth(elmShowProfileBtn)-GetGUIElementWidth(elmMuteButton), GetGUIElementFontHeight(fontHandle5), 'halLeft', 'valMiddle', fontHandle5, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   
      [*] = ;   // herb
      [*] = ;   {const cHerbX = 5;
      [*] = ;   const cHerbY = 3;
      [*] = ;   _gui_CreateHerb('', elmProfileInfo, gProfile.sign, gProfile.color1, gProfile.color2, 'halParentLeft', 'valParentBottomHeight', cHerbX, cHerbY);
      [*] = ;   _gui_CreateHerb('', elmProfileInfo, gProfile.sign, gProfile.color1, gProfile.color2, 'halParentRightWidth', 'valParentBottomHeight', -cHerbX, cHerbY);}
      [*] = ;
      [*] = ;   // game win
      [*] = ;   //var text : String = GetLocaleTableListItemByID('menu', '158')+': '+cStyleWhite+IntToStr(gamesWin);
      [*] = ;   //elmTextHandle := _gui_CreateText('', elmProfileInfo, text, 'halParentLeft', 'valParentTop', 0, cTextMarginT, GetGUIElementWidth(elmProfileInfo)-cTextMarginL, GetGUIElementFontHeight(fontHandle5), 'halRight', 'valTop', fontHandle5, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   // exp meter
      [*] = ;   {const cExpMeterMarginL = 0;
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
      [*] = ;   elmTextHandle := _gui_CreateText('', expMeterHandle, text, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(expMeterHandle), GetGUIElementHeight(expMeterHandle), 'halMiddle', 'valMiddle', fontHandle1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);}
      [*] = ;
      [*] = ;   // karma
      [*] = ;   {var rulerTitleID : Integer = rank;//GetRulerTitleIDByLevel(level);
      [*] = ;   var rulerKarmaID : Integer = GetRulerKarmaID(karma);
      [*] = ;   if (rulerKarmaID<>0) then
      [*] = ;   begin
      [*] = ;      text := GetLocaleTableListItemByID('ruler_title', IntToStr(rulerTitleID))+', '+GetLocaleTableListItemByID('ruler_nick', IntToStr(rulerKarmaID));
      [*] = ;      //elmTextHandle := _gui_CreateText('', expMeterHandle, text, 'halParentLeft', 'valParentBottom', 0, cLevelMarginT, GetGUIElementWidth(expMeterHandle), h, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   end;}
      [*] = ;
      [*] = ;   {const cStyle0 = '%style(default)%'+cStyleDefault;
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
      [*] = ;   elmTextHandle := _gui_CreateText('', elmProfileInfo, text, 'halParentLeft', 'valParentTop', cExpMeterMarginL, cExpMeterMarginT+cExpMeterSizeY, GetGUIElementWidth(expMeterHandle), GetGUIElementHeight(elmProfileInfo)-(cExpMeterMarginT+cExpMeterSizeY), 'halMiddle', 'valMiddle', fontHandle1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);}
      [*] = ;
      [*] = ;   Result := elmProfileInfo;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('internetshell' _gui_GetLayerI(), 'halLeft', 'valTop', 0, 0, viewWidth, viewHeight, 0);
      [*] = ;var elmChatPanel : Integer;
      [*] = ;if chatSize > 5 then
      [*] = ;   elmChatPanel :=_gui_CreateLargeWindow(elmParentHandle, 'rightpanel', 'halParentLeft', 'valParentTop', chatPanelPosX, panelMarginTop, chatPanelWidth, cPanelHeight+chatHeight, false)
      [*] = ;else
      [*] = ;   elmChatPanel :=_gui_CreateSmallWindow(elmParentHandle, 'rightpanel', 'halParentLeft', 'valParentTop', chatPanelPosX, panelMarginTop, chatPanelWidth, cPanelHeight+chatHeight, false);
      [*] = ;     
      [*] = ;
      [*] = ;SetGUIElementPressState(GetGUIElementIndexByNameParent('background.eventlayer', elmChatPanel), cEventState);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmChatPanel), gProfile.chatopacity);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmChatPanel), gProfile.chatopacity);
      [*] = ;SetGUIElementVisible(GetGUIElementIndexByNameParent('header', elmChatPanel), False);
      [*] = ; 
      [*] = ;var chatPanelHeader : Integer = _gui_CreateImage('', elmChatPanel, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, -cBorderFrameSize, 0, 0, 0);
      [*] = ;if (gProfile.chatopacity > 0.4) and ((chatPanelWidth >= 600) or (gGame.gametype <> gc_GameTypeNone)) then // no header with reduced width panel.
      [*] = ;   SetGUIElementUserBlend(chatPanelHeader, 1)
      [*] = ;else
      [*] = ;   SetGUIElementUserBlend(chatPanelHeader, 0);
      [*] = ;_gui_CreateText('' , chatPanelHeader, 'menu|astral_chat', 'halParentLeft', 'valParentTop', 0, 2, 240, 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ; 
      [*] = ;var elmPlayers, elmProfileInfo : Integer = 0;
      [*] = ;if (playersListWidth > 0) then
      [*] = ;   elmPlayers := CreatePlayers(elmChatPanel);
      [*] = ; 
      [*] = ;if (chatSize >= cSizeShowProfileBar) and ((chatPanelWidth >= cPlayersBottomThreshold) or (chatSize >= cSizeShowPlayersOnBottom)) then
      [*] = ;   elmProfileInfo := CreateProfileInfo(elmChatPanel);
      [*] = ; 
      [*] = ;CreateChat(elmChatPanel);
      [*] = ; 
      [*] = ;if gIntRegister_InetSelectedPlayerID > 0 then
      [*] = ;begin
      [*] = ;   var elmPlayersList : Integer = GetGUIElementIndexByNameParent('list', elmPlayers);
      [*] = ;   SetGUIListBoxItemIndex(elmPlayersList, GetGUIListBoxItemIndexOfTag(elmPlayersList, gIntRegister_InetSelectedPlayerID));
      [*] = ;   _inet_PlayerSelected(elmPlayersList, false, false);
      [*] = ;end;
      [*] = ;
      [*] = ;// Close button
      [*] = ;var posX : Integer = cButtonX;
      [*] = ;var posY : Integer = cButtonY;
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('btnClose', elmChatPanel, '', 'map.hideminimap', 'halParentRight', 'valParentTop', posX, posY, 0, 0, cEventState, 'menu|47', cBtnCloseTag);
      [*] = ; 
      [*] = ;// Scale buttons
      [*] = ;posX := posX - 50;
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmChatPanel, '', 'gamepanel03.btn.sort.up', 'halParentRight', 'valParentTop', posX, posY, 0, 0, cEventState, '', cBtnShrinkTag);
      [*] = ;posX := posX - 50;
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmChatPanel, '', 'gamepanel03.btn.sort.down', 'halParentRight', 'valParentTop', posX, posY, 0, 0, cEventState, '', cBtnExpandTag);
      [*] = ;
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;//_gui_RootWindowAddExt(elmParentHandle,cRootWindowModal,0,1,'');
      [*] = ;if mode = 2 then
      [*] = ;begin
      [*] = ;   _gui_RootWindowAdd(elmParentHandle, cRootWindowModal);
      [*] = ;   _cmd_RegisterWindowState(elmParentHandle,'VVK.InternetShellCommands',cEventStateChat);
      [*] = ;end;
      [*] = ;SetGUIElementPressState(elmParentHandle,cEventState);
      [*] = ;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

