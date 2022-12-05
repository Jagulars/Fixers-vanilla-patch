section.begin
   Name = vvk.LanUpdateGUIElements
   Description : struct.begin
      [*] = ;IntRegister0 - mode
      [*] = ;   [0] - update clients list
      [*] = ;      IntRegister1 - client id to exclude
      [*] = ;      StringRegister0 - list elemant name
      [*] = ;   [1] - update shard games list
      [*] = ;      StringRegister0 - list elemant name
      [*] = ;   [2] - update listbox scroller pos
      [*] = ;      IntRegister1 - scroller element handle
      [*] = ;   [3] - check if save is valid and exists for client
      [*] = ;      IntRegister1 - client lan id
      [*] = ;      StringRegister0 - save map name
      [*] = ;      RET: IntRegister0 > 0 - valid and it is number of players
      [*] = ;   [4] - create left panel in battle mode
      [*] = ;      IntRegister1 - parent handle
      [*] = ;      RET: IntRegister0 - left side window handle
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;var _fake_clients : Integer = 0;
      [*] = ;
      [*] = ;const cEventState = 'EventInternetShell';
      [*] = ;const cBtnPointsModeClassic = 111;
      [*] = ;const cBtnPointsModeProgressive = 112;
      [*] = ;const cListBoxPointsDifference = 50;
      [*] = ;const cRatingAllowHeroesFlagsBaseTag = 400;
      [*] = ;const cRatingAllowTerrainFlagsBaseTag = 420;
      [*] = ;const cBtnSetDefaultTag = 120;
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
      [*] = ;procedure GetShardGamesListString(pSession : Integer; var _sline : String);
      [*] = ;begin
      [*] = ;   var pClient : Integer = _misc_ParserGetOrCreateByKey('client_info',true);
      [*] = ;   var gamename : String = ParserGetValueByKeyByHandle(pSession, 'GameName');
      [*] = ;   var mapname : String = ParserGetValueByKeyByHandle(pSession, 'MapName');
      [*] = ;   var gamemaster,sline : String;
      [*] = ;
      [*] = ;   LanPublicServerGetClientInfoToParserByClientID(ParserGetIntValueByKeyByHandle(pSession, 'Master'), pClient);
      [*] = ;   gamemaster := ParserGetValueByKeyByHandle(pClient, 'Nick');
      [*] = ;
      [*] = ;   if _inet_IsSaveGameMapName(mapname) then
      [*] = ;   begin
      [*] = ;      var p_no : Integer = _inet_IsSaveValidForClient(LanMyInfoID(),mapname);
      [*] = ;      if p_no > 0 then
      [*] = ;      begin
      [*] = ;         sline := '""'+#9;
      [*] = ;         sline := sline+gamename+#9;
      [*] = ;         sline := sline+gamemaster+#9;
      [*] = ;         sline := sline+IntToStr(p_no)+#9;
      [*] = ;         sline := sline+'Save'+#9;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         sline := '';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var clientplayers : Integer = ParserGetIntValueByKeyByHandle(pSession, 'Clients');
      [*] = ;      //var password: String;
      [*] = ;      //var bPassword : Boolean = (password<>'');
      [*] = ;      //var onlineplayers : Integer = ParserGetIntValueByKeyByHandle(pSession, 'Clients');
      [*] = ;      //var aiplayers : Integer = maxplayers-humanslots;
      [*] = ;
      [*] = ;      var maxPlayers : Integer = _inet_GetInetShardMaxPlayersByMapName(mapName);
      [*] = ;      var humanSlots : Integer = _inet_GetInetShardHumanSlotsByMapName(mapName);
      [*] = ;      var players : Integer = clientplayers+(maxplayers-humanSlots)-1;
      [*] = ;
      [*] = ;      sline := '""'+#9;
      [*] = ;      sline := sline+gamename+#9;
      [*] = ;      sline := sline+gamemaster+#9;
      [*] = ;      sline := sline+IntToStr(players)+'/'+IntToStr(maxplayers)+#9;
      [*] = ;      //sline := sline+IntToStr(turn)+#9;
      [*] = ;      //sline := sline+IntToStr(onlineplayers)+'/'+IntToStr(clientplayers)+#9;
      [*] = ;      sline := sline+'New'+#9;
      [*] = ;   end;
      [*] = ;   if _log then _log_lan('SLINE: '+sline);
      [*] = ;   _sline := sline;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UpdateShardGamesList(elmName : String);
      [*] = ;begin
      [*] = ;   const maxPageCount = 6;
      [*] = ;
      [*] = ;   var elmHandle : Integer = _gui_GetWindow(elmName);
      [*] = ;   var itemIndex : Integer = GetGUIListBoxItemIndex(elmHandle);
      [*] = ;   var topIndex  : Integer = GetGUIListBoxTopIndex(elmHandle);
      [*] = ;   var pickedIndex : Integer = -1;
      [*] = ;   var pSessions : Integer = _misc_ParserGetOrCreateByKey('sessions',true);
      [*] = ;   var i,ind,pClient,masterid,pSession,count,elmScroll,height : Integer;
      [*] = ;   var game,clientInfo : String;
      [*] = ;
      [*] = ;   GUIListBoxClearSilent(elmHandle);
      [*] = ;   //GUIListBoxAddItem(elmHandle, '""'+#9+'DUMMY', -1);
      [*] = ;   LanPublicServerSessionsToParser(pSessions);
      [*] = ;
      [*] = ;   ind := 0;
      [*] = ;   pClient := _misc_ParserGetOrCreateByKey('client_info',true);
      [*] = ;   for i:=0 to ParserGetCountByHandle(pSessions)-1 do
      [*] = ;   begin
      [*] = ;      pSession := ParserSelectByHandleByIndex(pSessions, i);
      [*] = ;      masterid := ParserGetIntValueByKeyByHandle(pSession, 'Master');
      [*] = ;      ParserClearByHandle(pClient);
      [*] = ;      LanPublicServerGetClientInfoToParserByClientID(masterid, pClient);
      [*] = ;      clientInfo := ParserGetValueByKeyByHandle(pClient, 'Info');
      [*] = ;      if (_sa_GetAsInt(clientInfo,5)=0) then // only shard room
      [*] = ;      begin
      [*] = ;         game := '';
      [*] = ;         GetShardGamesListString(pSession, game);
      [*] = ;         if game <> '' then
      [*] = ;         begin
      [*] = ;            GUIListBoxAddItem(elmHandle, game, i);
      [*] = ;            if gIntRegister_InetSelectedGameID=i then
      [*] = ;               pickedIndex := ind;
      [*] = ;            ind := ind+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   SetGUIListBoxItemIndexSilent(elmHandle, pickedIndex);
      [*] = ;   count := GetGUIListBoxItemsCount(elmHandle);
      [*] = ;   //if _log then _log_valuesL('VALID_ITEMS|TOTAL',ind,count,0,0,0,0);
      [*] = ;
      [*] = ;   if topIndex>=count then
      [*] = ;      topIndex := count-1;
      [*] = ;
      [*] = ;   if topIndex >= 0 then
      [*] = ;      SetGUIListBoxTopIndex(elmHandle, topIndex)
      [*] = ;   else
      [*] = ;      SetGUIListBoxTopIndex(elmHandle, 0);
      [*] = ;
      [*] = ;   if (count>maxPageCount) then
      [*] = ;       count := maxPageCount;
      [*] = ;
      [*] = ;   if count > 0 then
      [*] = ;   begin
      [*] = ;      SetGUIElementAllPositionRect(elmHandle, GetGUIElementPositionX(elmHandle), GetGUIElementPositionY(elmHandle), GetGUIElementWidth(elmHandle), GetGUIListBoxRowHeight(elmHandle)*count);
      [*] = ;      SetGUIElementLogicHeight(elmHandle, GetGUIListBoxRowHeight(elmHandle)*count);
      [*] = ;
      [*] = ;      elmScroll := GetGUIListBoxScrollerHandle(elmHandle);
      [*] = ;      height := GetGUIElementHeight(elmScroll);
      [*] = ;      SetGUIElementHeight(elmScroll, height);
      [*] = ;      SetGUIElementLogicHeight(elmScroll, height);
      [*] = ;
      [*] = ;      UpdateListBoxScrollerPos(elmHandle);
      [*] = ;   end;
      [*] = ;   if _log then _log_valuesL('VALID_ITEMS|TOTAL',ind,GetGUIListBoxItemsCount(elmHandle),0,0,0,0);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateLeftSide(elmParentHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   //var fontHandle1, fontHandle2, fontHandle3, fontHandle4, fontHandle5, fontHandleInput : String;
      [*] = ;   var fontHandle2 : String;
      [*] = ;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;
      [*] = ;   var elmLeftSide : Integer = GetGUIElementIndexByNameParent('leftside', elmParentHandle);
      [*] = ;   if (elmLeftSide<>0) then
      [*] = ;      RemoveGUIElement(elmLeftSide);
      [*] = ;   elmLeftSide := _gui_CreateImage('leftside', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmParentHandle), GetGUIElementHeight(elmParentHandle), 0);
      [*] = ;   const cStripMarginT = 26;
      [*] = ;   const cStripTextMarginT = 6;
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('rating', elmLeftSide, 'element.strip.341', 'halParentMiddle', 'valParentTop', 0, cStripMarginT, 0, 0, 0);
      [*] = ;   _gui_CreateText('' , elmHandle, 'menu|163', 'halParentLeft', 'valParentTop', 0, cStripTextMarginT, GetGUIElementWidth(elmHandle), 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   const cSettingsMarginL = -150;
      [*] = ;   const cPointsModeMarginL = 140;
      [*] = ;
      [*] = ;   const cPointsModeMarginT = cStripMarginT+52;
      [*] = ;   var elmPointsModeHandle : Integer = _gui_CreateImage('pointsmode', elmLeftSide, 'element.strip.240', 'halParentMiddle', 'valParentTop', cPointsModeMarginL, cPointsModeMarginT, 0, 0, 0);
      [*] = ;   _gui_CreateText('' , elmPointsModeHandle, 'menu|207', 'halParentLeft', 'valParentTop', 0, cStripTextMarginT, 240, 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   const cBtnStripOffsetY = 40;
      [*] = ;   const cBtnOffsetY = 44;
      [*] = ;   elmHandle := _gui_CreateButton('', elmPointsModeHandle, '', 'common.btn', 'halParentMiddle', 'valParentTop', 0, cBtnStripOffsetY, 0, 0, cEventState, 'menu|208.hint', cBtnPointsModeClassic);
      [*] = ;   SetGUIElementVisibleProperties(elmHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.8);
      [*] = ;   SetGUIElementChecked(elmHandle, gIntRegister_InetPointsMode=0);
      [*] = ;   _gui_CreateText('', elmHandle, 'menu|208', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;   elmHandle := _gui_CreateButton('', elmPointsModeHandle, '', 'common.btn', 'halParentMiddle', 'valParentTop', 0, cBtnStripOffsetY+cBtnOffsetY, 0, 0, cEventState, 'menu|209.hint', cBtnPointsModeProgressive);
      [*] = ;   SetGUIElementVisibleProperties(elmHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.8);
      [*] = ;   SetGUIElementChecked(elmHandle, gIntRegister_InetPointsMode=1);
      [*] = ;   _gui_CreateText('', elmHandle, 'menu|209', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;   var elmRatingSettingsHandle : Integer = _gui_CreateImage('rating', elmLeftSide, gc_gui_material_blank_0, 'halParentMiddle', 'valParentTop', cSettingsMarginL, cStripMarginT, 0, 0, 0);
      [*] = ;   var elmListBoxHandle : Integer = _gui_CreateListBox('pointsdifference', elmRatingSettingsHandle, 3, 0{-30}, 62, cEventState);
      [*] = ;   SetGUIElementTag(elmListBoxHandle, cListBoxPointsDifference);
      [*] = ;   SetGUIElementAlign(elmListBoxHandle, 'halParentMiddle', 'valParentTop');
      [*] = ;   _gui_CreateText('header', elmListBoxHandle, 'menu|164', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   GUIListBoxAddItem(elmListBoxHandle, '5%', 0);
      [*] = ;   GUIListBoxAddItem(elmListBoxHandle, '15%', 1);
      [*] = ;   GUIListBoxAddItem(elmListBoxHandle, '30%', 2);
      [*] = ;   SetGUIListBoxItemIndexSilent(elmListBoxHandle, gInetShell.allowpointsdif);
      [*] = ;
      [*] = ;   var allowHeroesMarginT : Integer = 138;
      [*] = ;   var elmAllowHeroesHandle : Integer = _gui_CreateImage('allowheroes', elmLeftSide, 'element.strip.240', 'halParentMiddle', 'valParentTop', cSettingsMarginL, allowHeroesMarginT, 0, 0, 0);
      [*] = ;   _gui_CreateText('' , elmAllowHeroesHandle, 'menu|165', 'halParentLeft', 'valParentTop', 0, cStripTextMarginT, 240, 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   var i, checkFlagNumber, posIndex, posX, posY, tag : Integer;
      [*] = ;   var bChecked : Boolean;
      [*] = ;   var allowedClasses : Integer = gInetShell.allowedheroclasses;
      [*] = ;   var hint, name : String = '';
      [*] = ;   for i := 0 to gc_HeroClassChoiceCount-1 do
      [*] = ;   begin
      [*] = ;      checkFlagNumber := _misc_GetBitFlagByIndex(i);
      [*] = ;      bChecked := ((checkFlagNumber and allowedClasses) > 0);
      [*] = ;      
      [*] = ;      name := 'hero_class|'+IntToStr(i+5);
      [*] = ;      hint := 'hero_class|'+IntToStr(i+5)+'.description';
      [*] = ;      posIndex := i;
      [*] = ;      if i mod 4 - i div 4 = 0 then // adjust so that pure class is always first
      [*] = ;         posIndex := posIndex - i div 4
      [*] = ;      else if i mod 4 <= i div 4 then
      [*] = ;         posIndex := posIndex + 1;
      [*] = ;      posX := 31;
      [*] = ;      posY := 40+20*posIndex;
      [*] = ;      tag := cRatingAllowHeroesFlagsBaseTag+i;
      [*] = ;      _gui_CreateCheckBox('', elmAllowHeroesHandle, bChecked, name, 'halParentLeft', 'valParentTop', posX, posY, cEventState, hint, tag);
      [*] = ;   end;
      [*] = ;   var reqsMarginT : Integer = 42+gc_HeroClassChoiceCount*20;
      [*] = ;   elmHandle := _gui_CreateText('reqs' , elmAllowHeroesHandle, 'menu|166', 'halParentLeft', 'valParentTop', 0, reqsMarginT, GetGUIElementWidth(elmAllowHeroesHandle), 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   if (_inet_CheckAllowHeroesReqs) then
      [*] = ;      SetGUIElementVisible(elmHandle, False);
      [*] = ;
      [*] = ;   var allowTerrainMarginT : Integer = allowHeroesMarginT+195;
      [*] = ;   var elmAllowTerrainHandle : Integer = _gui_CreateImage('allowterrain', elmLeftSide, 'element.strip.240', 'halParentMiddle', 'valParentTop', cPointsModeMarginL, allowTerrainMarginT, 0, 0, 0);
      [*] = ;   _gui_CreateText('' , elmAllowTerrainHandle, 'menu|169', 'halParentLeft', 'valParentTop', 0, cStripTextMarginT, 240, 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   for i:=0 to gc_TerrainChoiceCount-1 do
      [*] = ;   begin
      [*] = ;      var checkFlagNumber : Integer = _misc_GetBitFlagByIndex(i);
      [*] = ;      var bChecked : Boolean = ((gInetShell.allowedterrains and checkFlagNumber) > 0);
      [*] = ;      var hint, name : String = '';
      [*] = ;      var tag : Integer = cRatingAllowTerrainFlagsBaseTag+i;
      [*] = ;      case i of
      [*] = ;         0, 1, 2, 3 : name := 'gui|'+IntToStr(335+i);
      [*] = ;         4 : name := 'gui|'+IntToStr(568);
      [*] = ;         5 : name := 'gui|'+IntToStr(569);
      [*] = ;      end;
      [*] = ;      
      [*] = ;      var posX : Integer = 31;
      [*] = ;      var posY : Integer = 43+20*i;
      [*] = ;      _gui_CreateCheckBox('', elmAllowTerrainHandle, bChecked, name, 'halParentLeft', 'valParentTop', posX, posY, cEventState, hint, tag);
      [*] = ;   end;
      [*] = ;   reqsMarginT := 42+gc_TerrainChoiceCount*20;
      [*] = ;   elmHandle := _gui_CreateText('reqs' , elmAllowTerrainHandle, 'menu|167', 'halParentLeft', 'valParentTop', 0, reqsMarginT, GetGUIElementWidth(elmAllowHeroesHandle), 25, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   if (_inet_CheckAllowTerrainReqs) then
      [*] = ;      SetGUIElementVisible(elmHandle, False);
      [*] = ;
      [*] = ;   elmHandle := _gui_CreateImage('', elmLeftSide, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 0, -32, 0, 0, 0);
      [*] = ;   _gui_CreateButton('btnSetDefault', elmHandle, '', 'map.castle.tabs.btn.provincelist', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'gui|355', cBtnSetDefaultTag);
      [*] = ;
      [*] = ;   Result := elmLeftSide;
      [*] = ;end;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;
      [*] = ;case mode of
      [*] = ;   0 : _inet_UpdateClientsList( StringRegister0, IntRegister1 );
      [*] = ;   1 : UpdateShardGamesList( StringRegister0 );
      [*] = ;   2 : UpdateListBoxScrollerPos( IntRegister1 );
      [*] = ;   3 : IntRegister0 := _inet_IsSaveValidForClient( IntRegister1, StringRegister0 );
      [*] = ;   4 : IntRegister0 := CreateLeftSide( IntRegister1 );
      [*] = ;end;
   struct.end
section.end

