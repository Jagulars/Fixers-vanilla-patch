section.begin
   Name = map.CreateProvinceList
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;const cDataMask = $fff;
      [*] = ;const cDataMax = $7ff;
      [*] = ;const cDataShift = 18;
      [*] = ;const cScrollShift = 12;
      [*] = ;const cScrollMask = $3f;
      [*] = ;const cIndexMask = $fff;
      [*] = ;
      [*] = ;function GetProvinceProperty(pidx : Integer; property_id : Integer ) : Integer ;
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle,pidx);
      [*] = ;   var cidx : Integer;
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'GetCastleParser');
      [*] = ;   cidx := ParserGetIntValueByKeyByHandle( IntRegister0, 'Index');
      [*] = ;
      [*] = ;   if ((property_id=0) or (property_id=9)) and (pidx=cidx) then
      [*] = ;   begin
      [*] = ;      if (property_id=0) then
      [*] = ;         Result := 0
      [*] = ;      else
      [*] = ;         Result := cDataMask;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;      var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;      case property_id of
      [*] = ;         0 : begin // sortValueName := 'CastleDist';
      [*] = ;            Result := ParserGetIntValueByKeyByHandle(pProvince, 'CastleDist')+1;
      [*] = ;         end;
      [*] = ;         1 : begin // sortValueName := 'GoldIncome';
      [*] = ;            IntRegister0 := 1;
      [*] = ;            IntRegister1 := -1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHnd, 'GetGoldAndGemIncomeExt');
      [*] = ;            Result := IntRegister0+cDataMax;
      [*] = ;         end;
      [*] = ;         2 : begin // sortValueName := 'GemIncome';
      [*] = ;            IntRegister0 := 2;
      [*] = ;            IntRegister1 := -1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHnd, 'GetGoldAndGemIncomeExt');
      [*] = ;            Result := IntRegister1+cDataMax;
      [*] = ;         end;
      [*] = ;         3 : begin // sortValueName := 'Population';
      [*] = ;            Result := ParserGetIntValueByKeyByHandle(pProvince, 'Population') + cDataMax;
      [*] = ;         end;
      [*] = ;         4 : begin // sortValueName := 'Mood';
      [*] = ;            GameObjectExecuteStateByHandle(dummyHnd, 'GetMood');
      [*] = ;            Result := IntRegister0+cDataMax;
      [*] = ;         end;
      [*] = ;         5 : begin // sortValueName := 'Unrest';
      [*] = ;            GameObjectExecuteStateByHandle(dummyHnd, 'GetOwnerUnrest');
      [*] = ;            Result := IntRegister0+cDataMax;
      [*] = ;         end;
      [*] = ;         6 : begin // sortValueName := 'Explored';
      [*] = ;            Result := ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;         end;
      [*] = ;         7 : begin // sortValueName := 'ProvinceRace';
      [*] = ;            Result := ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;         end;
      [*] = ;         8 : begin // sortValueName := 'SiteCount';
      [*] = ;            var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;            var siteCount : Integer = 0;
      [*] = ;            var j,explored : Integer;
      [*] = ;
      [*] = ;            explored := ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;
      [*] = ;            for j:=0 to ParserGetCountByHandle(pProvSites)-1 do
      [*] = ;            begin
      [*] = ;               var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;               var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;               var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;               if (siteID>0) and (siteExplore<=explored) then
      [*] = ;                  siteCount := siteCount+1;
      [*] = ;            end;
      [*] = ;            Result := siteCount;
      [*] = ;         end;
      [*] = ;         9 : begin // sortValueName := 'OuterBuildCount';
      [*] = ;            var pProvOuterBuildings : Integer =  ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;            var outerBuildCount : Integer = 0;
      [*] = ;            var j : Integer;
      [*] = ;
      [*] = ;            for j:=0 to ParserGetCountByHandle(pProvOuterBuildings)-1 do
      [*] = ;            begin
      [*] = ;               var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, j);
      [*] = ;               var buildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;               if (buildID<>0) then
      [*] = ;                  outerBuildCount := outerBuildCount+1;
      [*] = ;            end;
      [*] = ;            Result := outerBuildCount;
      [*] = ;         end;
      [*] = ;         else Result := 0;
      [*] = ;      end;
      [*] = ;      if Result < 0 then
      [*] = ;         Result := 0;
      [*] = ;      if Result > cDataMask then
      [*] = ;         Result := cDataMask;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateSortedList(sort_mode : Integer; sort_order : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pList : Integer = _misc_ParserGetOrCreateByKey('map_cpl_tmpSortProvinceList',false);
      [*] = ;   var pHexCells : Integer = gStratHexCells.handle;
      [*] = ;   var p,i,pr,s,idx : Integer;
      [*] = ;
      [*] = ;   if _log then _log_values('SortMode|SortOrder|No',sort_mode,sort_order,ParserGetCountByHandle(pList),0,0,0);
      [*] = ;   ArrayClear();
      [*] = ;   if (ParserGetCountByHandle(pList)=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;      begin
      [*] = ;         if SameText(ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pHexCells, i), 'Player'), GetPlayerNameInterfaceIO()) then
      [*] = ;            ArrayPushValue(((GetProvinceProperty(i,sort_mode) shl cDataShift) or i));
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      for i:=0 to ParserGetCountByHandle(pList)-1 do
      [*] = ;      begin
      [*] = ;         p := ParserSelectByHandleByIndex(pList, i);
      [*] = ;         idx := ParserGetIntValueByKeyByHandle(p, 'Index');
      [*] = ;         s := ParserGetIntValueByKeyByHandle(p, 'Scroll');
      [*] = ;         if s < 0 then s := 0;
      [*] = ;         if s > cScrollMask then s := cScrollMask;
      [*] = ;         pr := GetProvinceProperty(idx,sort_mode);
      [*] = ;         if _log then _log_values('Idx|Property|Scroll',idx,pr,s,0,0,0);
      [*] = ;         ArrayPushValue(((pr shl cDataShift) or (s shl cScrollShift) or idx));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (sort_mode=0) or (sort_mode=7) then
      [*] = ;      sort_order := sort_order xor 1;
      [*] = ;
      [*] = ;   ArraySort((sort_order=0));
      [*] = ;
      [*] = ;   pList := _misc_ParserGetOrCreateByKey('map_cpl_tmpSortProvinceList',true);
      [*] = ;
      [*] = ;   if _log then _log_gui('Sort done.');
      [*] = ;   for i:=0 to ArrayGetCount()-1 do
      [*] = ;   begin
      [*] = ;      p := ParserAddChildByIndex(pList, '*');
      [*] = ;      pr := ArrayGetValueByIndex(i);
      [*] = ;      if _log then _log_values('Idx|Property|Scroll',pr and cIndexMask,pr shr cDataShift,(pr shr cScrollShift) and cScrollMask,0,0,0);
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'Index', pr and cIndexMask);
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'Scroll', (pr shr cScrollShift) and cScrollMask);
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := pList;
      [*] = ;end;
      [*] = ;
      [*] = ;const cEventState = 'map.EventProvinceList';
      [*] = ;
      [*] = ;var sortOrder : Integer = gIntRegister_GUIProvinceListSortOrder;
      [*] = ;var sortMode : Integer = gIntRegister_GUIProvinceListSortMode;
      [*] = ;var statMode : Integer = gIntRegister_GUIProvinceListStatMode;
      [*] = ;
      [*] = ;var fontHandleT, fontHandleH2, fontHandleN : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandleT);
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_large,'',fontHandleH2);
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Numbers',gc_gui_fontsize_default,'',fontHandleN);
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = _gui_GetWindow('provincelist');
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True
      [*] = ;else
      [*] = ;   _misc_ParserGetOrCreateByKey('map_cpl_tmpSortProvinceList',true);
      [*] = ;var elmScrollLayer : Integer = _gui_GetWindow('provincelist.background.provincelist_scrollLayer.scroll_layer');
      [*] = ;var lastScrollPos : Float = 0;
      [*] = ;if (elmScrollLayer<>0) then
      [*] = ;begin
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;   if (elmVScroll<>0) then
      [*] = ;      lastScrollPos := GetGUIScrollBarPosition(elmVScroll);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElementExt('provincelist', _gui_GetLayerI(), 'halMiddle', 'valMiddle', 0, 0, 0, 0, 0);
      [*] = ;_gui_RootWindowAddExt(elmParentHandle,cRootWindowModal,0,cRootWindowAttrScaleByY,cEventState);
      [*] = ;_cmd_RegisterWindowState(elmParentHandle,'map.ProvinceListCommands','map.EventProvinceList|VVK.ModalCommandsBlock');
      [*] = ;
      [*] = ;var elmBackgroundHandle : Integer = _gui_CreateImage('background', elmParentHandle, 'gamepanel03.provincelist.background', 'halMiddle', 'valMiddle', 0, 0, 0, 0, 0);
      [*] = ;var elmHandle : Integer;
      [*] = ;
      [*] = ;const cBtnSortOrder0 = 220;
      [*] = ;const cBtnSortOrder1 = 221;
      [*] = ;const cBtnSortMode0 = 200;
      [*] = ;const cBtnSortMode1 = 201;
      [*] = ;const cBtnSortMode2 = 202;
      [*] = ;const cBtnSortMode3 = 203;
      [*] = ;const cBtnSortMode4 = 204;
      [*] = ;const cBtnSortMode5 = 205;
      [*] = ;const cBtnSortMode6 = 206;
      [*] = ;const cBtnSortMode7 = 207;
      [*] = ;const cBtnSortMode8 = 208;
      [*] = ;const cBtnSortMode9 = 209;
      [*] = ;const cBtnStatMode0 = 240;
      [*] = ;const cBtnStatMode1 = 241;
      [*] = ;
      [*] = ;const cBaseProvIndex = 1000;
      [*] = ;const cBtnArrowLeftBaseTag = 2000;
      [*] = ;const cBtnArrowRightBaseTag = 3000;
      [*] = ;
      [*] = ;// Sort Up/Down
      [*] = ;var xOff : Integer = 52;
      [*] = ;var posX : Integer = 69;
      [*] = ;var posY : Integer = 10;
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('', elmBackgroundHandle, '', 'gamepanel03.btn.sort.down', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, 'gui|544', cBtnSortOrder0);
      [*] = ;if (sortOrder=0) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;   elmBtnHandle := _gui_CreateButton('', elmBackgroundHandle, '', 'gamepanel03.btn.sort.up', 'halParentLeft', 'valParentTop', posX+xOff, posY, 0, 0, cEventState, 'gui|545', cBtnSortOrder1);
      [*] = ;if (sortOrder=1) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;// Sort part1 - по удалению от замка / по доходу золота / по доходу кристалов / по населению / по настроению
      [*] = ;posX := 230;
      [*] = ;elmBtnHandle := _gui_CreateButton('sort1', elmBackgroundHandle, '', 'gamepanel03.btn.sort.castledistance', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, 'gui|534|0|0|0|provincelistsortmode|1', cBtnSortMode0);
      [*] = ;if (sortMode=0) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('sort2', elmBackgroundHandle, '', 'gamepanel03.btn.sort.goldincome', 'halParentLeft', 'valParentTop', posX+1*xOff, posY, 0, 0, cEventState, 'gui|535|0|0|0|provincelistsortmode|2', cBtnSortMode1);
      [*] = ;if (sortMode=1) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('sort3', elmBackgroundHandle, '', 'gamepanel03.btn.sort.gemincome', 'halParentLeft', 'valParentTop', posX+2*xOff, posY, 0, 0, cEventState, 'gui|536|0|0|0|provincelistsortmode|3', cBtnSortMode2);
      [*] = ;if (sortMode=2) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('sort4', elmBackgroundHandle, '', 'gamepanel03.btn.sort.population', 'halParentLeft', 'valParentTop', posX+3*xOff, posY, 0, 0, cEventState, 'gui|537|0|0|0|provincelistsortmode|4', cBtnSortMode3);
      [*] = ;if (sortMode=3) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('sort5', elmBackgroundHandle, '', 'gamepanel03.btn.sort.mood', 'halParentLeft', 'valParentTop', posX+4*xOff, posY, 0, 0, cEventState, 'gui|538|0|0|0|provincelistsortmode|5', cBtnSortMode4);
      [*] = ;if (sortMode=4) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;// Sort part2 - по недовольству / по исследованности / по расе / по особым местам / по количеству построек
      [*] = ;posX := 756;
      [*] = ;elmBtnHandle := _gui_CreateButton('sort6', elmBackgroundHandle, '', 'gamepanel03.btn.sort.unrest', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, 'gui|539|MT|0|0|provincelistsortmode|6', cBtnSortMode5);
      [*] = ;if (sortMode=5) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('sort7', elmBackgroundHandle, '', 'gamepanel03.btn.sort.explore', 'halParentLeft', 'valParentTop', posX+1*xOff, posY, 0, 0, cEventState, 'gui|540|MT|0|0|provincelistsortmode|7', cBtnSortMode6);
      [*] = ;if (sortMode=6) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('sort8', elmBackgroundHandle, '', 'gamepanel03.btn.sort.race', 'halParentLeft', 'valParentTop', posX+2*xOff, posY, 0, 0, cEventState, 'gui|541|MT|0|0|provincelistsortmode|8', cBtnSortMode7);
      [*] = ;if (sortMode=7) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('sort9', elmBackgroundHandle, '', 'gamepanel03.btn.sort.site', 'halParentLeft', 'valParentTop', posX+3*xOff, posY, 0, 0, cEventState, 'gui|542|MT|0|0|provincelistsortmode|9', cBtnSortMode8);
      [*] = ;if (sortMode=8) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('sort0', elmBackgroundHandle, '', 'gamepanel03.btn.sort.outerbuildings', 'halParentLeft', 'valParentTop', posX+4*xOff, posY, 0, 0, cEventState, 'gui|543|MT|0|0|provincelistsortmode|0', cBtnSortMode9);
      [*] = ;if (sortMode=9) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;// Режим просмотра статистики / режим просмотра особых мест
      [*] = ;posX := 1075;
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmBackgroundHandle, '', 'gamepanel03.btn.mode.statistics', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, 'gui|546', cBtnStatMode0);
      [*] = ;if (statMode=0) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmBackgroundHandle, '', 'gamepanel03.btn.mode.sitelist', 'halParentLeft', 'valParentTop', posX+1*xOff, posY, 0, 0, cEventState, 'gui|547', cBtnStatMode1);
      [*] = ;if (statMode=1) then SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;// List
      [*] = ;// Scroll layer
      [*] = ;var minCount : Integer = 9; // for 768 height, do dynamic height. (GetViewerHeight-166) div 85;
      [*] = ;var elmTmpLayer : Integer = _gui_CreateImage('provincelist_scrollLayer', elmBackgroundHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 51, 72, 1, 1, 0);
      [*] = ;var scrollLayerWidth : Integer = 1104;
      [*] = ;var scrollLayerHeight : Integer = 87*minCount;
      [*] = ;
      [*] = ;var height : Integer = 0;
      [*] = ;var elmGuiLayer : Integer = AddNewElementByClassNameParent('scroll_layer', 'TXGuiLayer', 0, elmTmpLayer);
      [*] = ;SetGUIElementAlign(elmGuiLayer, 'halParentLeft', 'valParentTop');
      [*] = ;SetGUIElementAllPositionRect(elmGuiLayer, 0, 0, scrollLayerWidth, scrollLayerHeight);
      [*] = ;SetGUIElementMaterial(elmGuiLayer, gc_gui_material_blank_0);
      [*] = ;var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;SetGUIElementAlign(elmVScroll, 'halParentRight', 'valParentTop');
      [*] = ;SetGUIElementMaterialOffset(elmVScroll, 2, 0);
      [*] = ;SetGUIElementAllPositionRect(elmVScroll, -5, 0, 32, round(scrollLayerHeight));
      [*] = ;SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;SetGUIAllowEvents(elmGuiLayer, True, False, False);
      [*] = ;      
      [*] = ;var bDisplayDetails : Boolean = not _map_CheckGenesisMode(gc_GM_ProvinceDetails);
      [*] = ;
      [*] = ;var ind : Integer = 0;
      [*] = ;var i,j,p,scroll : Integer;
      [*] = ;var pList : Integer = CreateSortedList(sortMode,sortOrder);
      [*] = ;var provIndex,pProvince : Integer;
      [*] = ;var text : String;
      [*] = ;
      [*] = ;for i:=0 to ParserGetCountByHandle(pList)-1 do
      [*] = ;begin
      [*] = ;   p := ParserSelectByHandleByIndex(pList,i);
      [*] = ;   scroll := ParserGetIntValueByKeyByHandle(p, 'Scroll');
      [*] = ;   provIndex := ParserGetIntValueByKeyByHandle(p, 'Index');
      [*] = ;   pProvince := ParserSelectByHandleByIndex(gStratHexCells.handle, provIndex);
      [*] = ;
      [*] = ;   var castle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   var posX : Integer = 0;
      [*] = ;   var posY : Integer = ind*87;
      [*] = ;   var elmItemListHandle : Integer = _gui_CreateImage('', elmGuiLayer, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX, posY, 1104, 72, 0);
      [*] = ;
      [*] = ;   var moodPrefix : String = '';
      [*] = ;   var mood, unrest, defenderID, pProvDefender : Integer = 0;
      [*] = ;   var iProvinceMarkCount, ProvinceLevel : Integer;
      [*] = ;   var sProvinceMarkType : String;
      [*] = ;   var wallBuildID : Integer = 0;
      [*] = ;   var wallBuildIcon : Integer = 0;
      [*] = ;   var siteCount : Integer = 0;
      [*] = ;   var explored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;   if (statMode=0) then
      [*] = ;   begin
      [*] = ;      if (castle) then
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.extendedroundblackdummy', 'halParentLeft', 'valParentTop', 670, 5, 0, 0, 0)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         for j:=0 to 2 do
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.roundblackdummy', 'halParentLeft', 'valParentTop', 670+j*64, 5, 0, 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.6);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      for j:=0 to 1 do
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.roundblackdummy', 'halParentLeft', 'valParentTop', 348+j*64, 5, 0, 0, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.6);
      [*] = ;      end;
      [*] = ;      for j:=0 to 2 do
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.roundblackdummy', 'halParentLeft', 'valParentTop', 859+j*64, 5, 0, 0, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.6);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // Race
      [*] = ;      var provinceRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;      var racePrefix : String = '';
      [*] = ;      case provinceRace of
      [*] = ;         1 : racePrefix := 'human';
      [*] = ;         2 : racePrefix := 'elf';
      [*] = ;         3 : racePrefix := 'dwarf';
      [*] = ;         4 : racePrefix := 'goblin';
      [*] = ;         5 : racePrefix := 'orc';
      [*] = ;         6 : racePrefix := 'halfling';
      [*] = ;         7 : racePrefix := 'centaur';
      [*] = ;         8 : racePrefix := 'lizardman';
      [*] = ;      end;
      [*] = ;      var elmName : String = 'map_infopanel_race_'+racePrefix;
      [*] = ;      elmHandle := _gui_CreateImage(elmName, elmItemListHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', 406, 5, 0, 0, 0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;      // Resource (Пока не показывать)
      [*] = ;      var resource : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;      var resourcePrefix : String = '';
      [*] = ;      case resource of
      [*] = ;         1 : resourcePrefix := 'iron';
      [*] = ;         2 : resourcePrefix := 'wood';
      [*] = ;         3 : resourcePrefix := 'horses';
      [*] = ;         4 : resourcePrefix := 'mandragora';
      [*] = ;         5 : resourcePrefix := 'arcanite';
      [*] = ;         6 : resourcePrefix := 'marble';
      [*] = ;         7 : resourcePrefix := 'mithril';
      [*] = ;         8 : resourcePrefix := 'diony';
      [*] = ;         9 : resourcePrefix := 'blacklotus';
      [*] = ;      end;
      [*] = ;      var resExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ResourceExplore');
      [*] = ;      if (resource>0) and (explored>=resExplore) then
      [*] = ;      begin
      [*] = ;         //elmHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmItemListHandle, 'map.resource.'+resourcePrefix, 'halParentLeft', 'valParentTop', gIntRegister_dbgX, gIntRegister_dbgY, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmItemListHandle, 'map.resource.'+IntToStr(resource)+'.61x61', 'halParentLeft', 'valParentTop', 350, 7, 0, 0, 0);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         //var elmBtnHandle : Integer = _gui_CreateButton('map_infopanel_resource_'+resourcePrefix, elmHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'ShowInfoWindow', '', 0);
      [*] = ;         //SetGUIElementStringTag(elmBtnHandle, 'Resource.'+IntToStr(Resource));
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'map.resource.2.61x61', 'halParentLeft', 'valParentTop', 350, 7, 0, 0, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.15);
      [*] = ;         SetGUIElementHint(elmHandle, 'gui|26');
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // Mood, unrest
      [*] = ;      GameObjectExecuteStateByHandle(dummyHnd, 'GetMood');
      [*] = ;      mood := IntRegister0;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHnd, 'GetOwnerUnrest');
      [*] = ;      unrest := IntRegister0;
      [*] = ;
      [*] = ;      if (mood<-5) then
      [*] = ;         moodPrefix := '.1'
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (mood>3) then
      [*] = ;            moodPrefix := '.9'
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            case mood of
      [*] = ;               -5 : moodPrefix := '.1';
      [*] = ;               -4 : moodPrefix := '.2';
      [*] = ;               -3 : moodPrefix := '.3';
      [*] = ;               -2 : moodPrefix := '.4';
      [*] = ;               -1 : moodPrefix := '.5';
      [*] = ;               0 : moodPrefix := '.6';
      [*] = ;               1 : moodPrefix := '.7';
      [*] = ;               2 : moodPrefix := '.8';
      [*] = ;               3 : moodPrefix := '.9';
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (unrest>gc_MaxUnrest) then
      [*] = ;      begin
      [*] = ;         ErrorLog('Unrest>gc_MaxUnrest see gui.aix Unrest = '+IntToStr(unrest));
      [*] = ;         unrest := gc_MaxUnrest;
      [*] = ;      end;
      [*] = ;      var meterValue : Integer = Floor(117*unrest/gc_MaxUnrest);
      [*] = ;      elmHandle := _gui_CreateImage('map_infopanel_uprising_progress', elmItemListHandle, 'map.infopanel.uprising.meter', 'halParentLeft', 'valParentTop', 513, 13, meterValue, 12, 0);
      [*] = ;      if (meterValue=0) then
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0);
      [*] = ;      elmHandle := _gui_CreateImage('map_infopanel_uprising_meter', elmItemListHandle, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 513, 13, 119, 14, 0);
      [*] = ;      if bDisplayDetails then
      [*] = ;         _gui_ft_AttachHint_I1(elmHandle,'VVK.map.HintProvDetailsCallback',dummyUID)
      [*] = ;      else
      [*] = ;         SetGUIElementHint(elmHandle, GetLocaleTableListItemByID('tooltip','map_infopanel_uprising_meter'));
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;      // Province level
      [*] = ;      ProvinceLevel := ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;      sProvinceMarkType := 'map.infopanel.growth.mark';
      [*] = ;      if (ProvinceLevel<=2) then
      [*] = ;         sProvinceMarkType := 'map.infopanel.growth.mark.red';
      [*] = ;
      [*] = ;      case ProvinceLevel of
      [*] = ;         1 : begin
      [*] = ;            iProvinceMarkCount := 2; //Red mark
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            iProvinceMarkCount := 1; //Red mark
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            iProvinceMarkCount := 1;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            iProvinceMarkCount := 2;
      [*] = ;         end;
      [*] = ;         5 : begin
      [*] = ;            iProvinceMarkCount := 3;
      [*] = ;         end;
      [*] = ;         6 : begin
      [*] = ;            iProvinceMarkCount := 4;
      [*] = ;         end;
      [*] = ;         7 : begin
      [*] = ;            iProvinceMarkCount := 5;
      [*] = ;         end;
      [*] = ;         8 : begin
      [*] = ;            iProvinceMarkCount := 6;
      [*] = ;         end;
      [*] = ;         9 : begin
      [*] = ;            iProvinceMarkCount := 7;
      [*] = ;         end;
      [*] = ;         10 : begin
      [*] = ;            iProvinceMarkCount := 8;
      [*] = ;         end;
      [*] = ;         11 : begin
      [*] = ;            iProvinceMarkCount := 9;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            iProvinceMarkCount := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var population : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Population');
      [*] = ;      var pProvinceLevels : Integer = gPrototypeData.provinceLevels.handle;
      [*] = ;      var pProvinceLevel : Integer = ParserSelectByHandleByIndex(pProvinceLevels, ProvinceLevel);
      [*] = ;      var maxPopulation : Integer = ParserGetIntValueByKeyByHandle(pProvinceLevel, 'MaxPopulation');
      [*] = ;      var minPopulation : Integer;
      [*] = ;      var hint : String;
      [*] = ;      if (provinceLevel>0) then
      [*] = ;      begin
      [*] = ;         var pPrevProvinceLevel : Integer = ParserSelectByHandleByIndex(pProvinceLevels, ProvinceLevel-1);
      [*] = ;         minPopulation := ParserGetIntValueByKeyByHandle(pPrevProvinceLevel, 'MaxPopulation');
      [*] = ;      end
      [*] = ;      else
      [*] = ;         minPopulation := 0;
      [*] = ;      meterValue := Floor(159*(population-minPopulation)/(maxPopulation-minPopulation));
      [*] = ;      if (meterValue>159) then
      [*] = ;         meterValue := 159;
      [*] = ;      elmHandle := _gui_CreateImage('map_infopanel_growth_progress', elmItemListHandle, 'map.infopanel.growth.meter', 'halParentLeft', 'valParentTop', 492, 44, meterValue, 12, 0);
      [*] = ;      if (meterValue=0) then
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0);
      [*] = ;      elmHandle := _gui_CreateImage('map_infopanel_growth_meter', elmHandle, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', -2, -1, 159+4, 14, 0);
      [*] = ;      if bDisplayDetails then
      [*] = ;      begin
      [*] = ;         hint := IntToStr(dummyUID)+',||512|tooltip|map_infopanel_mood.ext';
      [*] = ;         _gui_ft_AttachHint(elmHandle,'VVK.map.HintProvDetailsCallback',hint);  //mood
      [*] = ;      end
      [*] = ;      else
      [*] = ;         SetGUIElementHint(elmHandle, GetLocaleTableListItemByID('tooltip','map_infopanel_growth_meter'));
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;      // Outer-buildings
      [*] = ;      if (not castle) then
      [*] = ;      begin
      [*] = ;         var pProvOuterBuildings : Integer =  ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;         var tmpInd : Integer = 0;
      [*] = ;         for j:=0 to ParserGetCountByHandle(pProvOuterBuildings)-1 do
      [*] = ;         begin
      [*] = ;            var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, j);
      [*] = ;            var buildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;            if (buildID<>0) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := buildID;
      [*] = ;               MapExecuteState('GetOuterBuildParserByID');
      [*] = ;               var pOuterBuilding : Integer = IntRegister1;
      [*] = ;               var buildIcon : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Icon');
      [*] = ;               var wall : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Wall');
      [*] = ;               if (wall>0) then
      [*] = ;               begin
      [*] = ;                  wallBuildID := buildID;
      [*] = ;                  wallBuildIcon := buildIcon;
      [*] = ;               end;
      [*] = ;               elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.building.'+IntToStr(buildIcon), 'halParentLeft', 'valParentTop', 674+floor(tmpInd*63.5), 8, 53, 53, 0);
      [*] = ;               SetGUIElementHint(elmHandle, 'outer_build|'+IntToStr(buildID));
      [*] = ;               SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;               tmpInd := tmpInd+1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.building.'+IntToStr(2), 'halParentLeft', 'valParentTop', 674+tmpInd*63, 8, 53, 53, 0);
      [*] = ;               SetGUIElementUserBlend(elmHandle, 0.1);
      [*] = ;               SetGUIElementHint(elmHandle, 'gui|531');
      [*] = ;               SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;               tmpInd := tmpInd+1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // Страж
      [*] = ;      pProvDefender := ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;      defenderID := ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;      if (defenderID>0) then
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.defender.'+IntToStr(defenderID), 'halParentLeft', 'valParentTop', 869-7, 10-2, 0, 0, 0);
      [*] = ;         _gui_CreateFrameBorder('', elmHandle, 'halParentLeft', 'valParentTop', 0, 0, 56, 56);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;         SetGUIElementHint(elmHandle, 'defender|'+IntToStr(defenderID));
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.template.defender', 'halParentLeft', 'valParentTop', 869, 13, 46, 46, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.2);
      [*] = ;         SetGUIElementHint(elmHandle, 'gui|532');
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // Укрепление
      [*] = ;      if (castle) then
      [*] = ;      begin
      [*] = ;         wallBuildIcon := 206;
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.building.'+IntToStr(wallBuildIcon), 'halParentLeft', 'valParentTop', 927, 8, 53, 53, 0);
      [*] = ;         SetGUIElementHint(elmHandle, 'gui|117');
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (wallBuildID>0) and (wallBuildIcon>0) then
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.building.'+IntToStr(wallBuildIcon), 'halParentLeft', 'valParentTop', 927, 8, 53, 53, 0);
      [*] = ;            SetGUIElementHint(elmHandle, 'gui|117');
      [*] = ;            SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.building.'+IntToStr(47), 'halParentLeft', 'valParentTop', 927, 8, 53, 53, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.125);
      [*] = ;            SetGUIElementHint(elmHandle, 'gui|38');
      [*] = ;            SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // Особые места
      [*] = ;      var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;      var firstSiteID : Integer = 0;
      [*] = ;      for j:=0 to ParserGetCountByHandle(pProvSites)-1 do
      [*] = ;      begin
      [*] = ;         var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;         var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;         var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;         //var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;         //var guardID : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'GuardID');
      [*] = ;         //var pSites : Integer = gPrototypeData.sites.handle;
      [*] = ;         //var pSite : Integer = ParserSelectByHandleByIndex(pSites, siteID);
      [*] = ;         //var canEnter : Boolean = ParserGetBoolValueByKeyByHandle(pSite, 'CanEnter');
      [*] = ;
      [*] = ;         if (siteID>0) and (siteExplore<=explored) then
      [*] = ;         begin
      [*] = ;            if (firstSiteID=0) then
      [*] = ;               firstSiteID := siteID;
      [*] = ;            siteCount := siteCount+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (firstSiteID<>0) then
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.site.'+IntToStr(firstSiteID), 'halParentLeft', 'valParentTop', 927+64, 8, 53, 53, 0);
      [*] = ;         SetGUIElementHint(elmHandle, 'gui|533');
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.template.site', 'halParentLeft', 'valParentTop', 927+64, 8, 53, 53, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.125);
      [*] = ;         SetGUIElementHint(elmHandle, 'gui|533');
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      // Особые места
      [*] = ;      elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.shortcover', 'halParentLeft', 'valParentTop', -3, 2, 0, 0, 0);
      [*] = ;      elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.gotoprovince.decor', 'halParentLeft', 'valParentTop', 1037, 0, 0, 0, 0);
      [*] = ;      var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;      var count : Integer = ParserGetCountByHandle(pProvSites);
      [*] = ;      const cMaxSiteCount = 10;
      [*] = ;      if (count>cMaxSiteCount) then
      [*] = ;         count := cMaxSiteCount;
      [*] = ;      var indTmp : Integer = 0;
      [*] = ;      for j:=0 to cMaxSiteCount-1 do
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.template.site', 'halParentLeft', 'valParentTop', 362+31+j*(69-6), 8+1, 53, 53, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.125);
      [*] = ;         SetGUIElementHint(elmHandle, 'gui|533');
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var siteCount : Integer = 0;
      [*] = ;      var startInd : Integer = scroll;
      [*] = ;      var endInd : Integer = cMaxSiteCount+scroll;
      [*] = ;      var visualIndex : Integer = 0;
      [*] = ;      for j:=0 to ParserGetCountByHandle(pProvSites)-1 do
      [*] = ;      begin
      [*] = ;         var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;         var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;         var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;         var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;         var guardType : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'GuardType');
      [*] = ;         var guardID : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'GuardID');
      [*] = ;         var pSites : Integer = gPrototypeData.sites.handle;
      [*] = ;         var pSite : Integer = ParserSelectByHandleByIndex(pSites, siteID);
      [*] = ;         var canEnter : Boolean = ParserGetBoolValueByKeyByHandle(pSite, 'CanEnter');
      [*] = ;         {var bResource : Boolean = False;
      [*] = ;         var pSiteAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;         var k : Integer;
      [*] = ;         for k:=0 to ParserGetCountByHandle(pSiteAbilities)-1 do
      [*] = ;         begin
      [*] = ;            var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, k);
      [*] = ;            var abilityID : Integer =  ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;            if (abilityID=1) then
      [*] = ;            begin
      [*] = ;               bResource := True;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;}
      [*] = ;
      [*] = ;         if (siteID>0) and (siteExplore<=explored) {and ((bResource) or (not ((guardID=0) and (not canEnter))))} then
      [*] = ;         begin
      [*] = ;            if (visualIndex<cMaxSiteCount) then
      [*] = ;            begin
      [*] = ;               if (indTmp>=startInd) and (indTmp<endInd) then
      [*] = ;               begin
      [*] = ;                  elmHandle := _gui_CreateImage('', elmItemListHandle, 'icon.site.'+IntToStr(siteID), 'halParentLeft', 'valParentTop', 362+31+(visualIndex)*(69-6), 8+1, 53, 53, 0);
      [*] = ;                  var hint : String;
      [*] = ;                  if (guardType<>0) then
      [*] = ;                  begin
      [*] = ;                     hint := GetLocaleTableListItemByID('site', IntToStr(siteID));
      [*] = ;                     hint := hint+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '25')+':'+gc_gui_BreakLine+GetLocaleTableListItemByID('guard_type', IntToStr(guardType))
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     hint := GetLocaleTableListItemByID('site1', IntToStr(siteID));
      [*] = ;                     hint := hint+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('site1', IntToStr(siteID)+'.description');
      [*] = ;                     //hint := hint+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '532');
      [*] = ;                  end;
      [*] = ;                  SetGUIElementHint(elmHandle, hint);
      [*] = ;                  SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;                  visualIndex := visualIndex+1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            indTmp := indTmp+1;
      [*] = ;            siteCount := siteCount+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      var elmBtnArrowLeftHandle : Integer = _gui_CreateButton('arrowLeft', elmItemListHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', 320+33, 12+1, 0, 0, cEventState, '', cBtnArrowLeftBaseTag+i);
      [*] = ;      if (scroll<=0) then
      [*] = ;      begin
      [*] = ;         SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.4);
      [*] = ;         SetGUIElementEnabled(elmBtnArrowLeftHandle, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.8);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var elmBtnArrowRightHandle : Integer = _gui_CreateButton('arrowRight', elmItemListHandle, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', 980+28, 12+1, 0, 0, cEventState, '', cBtnArrowRightBaseTag+i);
      [*] = ;      if ((siteCount-scroll)<=cMaxSiteCount) then
      [*] = ;      begin
      [*] = ;         SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.4);
      [*] = ;         SetGUIElementEnabled(elmBtnArrowRightHandle, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.8);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (statMode=0) then
      [*] = ;   begin
      [*] = ;      if (castle) then
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.longcover.castle', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0)
      [*] = ;      else
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.longcover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      //elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.round.frame.79x69', 'halParentLeft', 'valParentTop', 355+j*69, 2, 0, 0, 0);
      [*] = ;      const cMaxSiteCount = 10;
      [*] = ;      for j:=(cMaxSiteCount-1) downto 0 do
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.round', 'halParentLeft', 'valParentTop', 355+31+j*(69-6), 2+1, 0, 0, 0);
      [*] = ;         if (j<(cMaxSiteCount-1)) then
      [*] = ;            elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.round.decor', 'halParentLeft', 'valParentTop', 355+31+j*(69-6)+53, 2+1+6, 0, 0, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Province name
      [*] = ;   IntRegister0 := pProvince;
      [*] = ;   MapExecuteState('map.GetProvinceName');
      [*] = ;   elmHandle := _gui_CreateText('map_infopanel_province_name', elmItemListHandle, StringRegister0, 'halParentLeft', 'valParentTop', 174-100, 7, 200, 32, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;   // Gold and gem income
      [*] = ;   begin
      [*] = ;      var gold,gem : Integer;
      [*] = ;      var gold_f,gem_f : Float;
      [*] = ;      var gs,ms : String;
      [*] = ;
      [*] = ;      IntRegister0 := 7;
      [*] = ;      IntRegister1 := -1;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHnd, 'GetGoldAndGemIncomeExt');
      [*] = ;      gold := IntRegister0;
      [*] = ;      gem := IntRegister1;
      [*] = ;      gold_f := FloatRegister0;
      [*] = ;      gem_f := FloatRegister1;
      [*] = ;      gs := StringRegister0;
      [*] = ;      ms := StringRegister1;
      [*] = ;
      [*] = ;      if (gold>0) then
      [*] = ;         text := '+'+IntToStr(gold)
      [*] = ;      else
      [*] = ;         text := '';
      [*] = ;      elmHandle := _gui_CreateText('_map_infopanel_province_gold_income', elmItemListHandle, text, 'halParentLeft', 'valParentTop', 64, 36, 40, 32, 'halLeft', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;      IntRegister0 := 0;
      [*] = ;      FloatRegister0 := gold_f;
      [*] = ;      StringRegister0 := gs;
      [*] = ;      GUIExecuteState('vvk.map.CreateProvinceIncomeTooltip');
      [*] = ;      SetGUIElementHint(elmHandle, StringRegister0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;      if (gem>0) then
      [*] = ;         text := '+'+IntToStr(gem)
      [*] = ;      else
      [*] = ;         text := '';
      [*] = ;      elmHandle := _gui_CreateText('_map_infopanel_province_gem_income', elmItemListHandle, text, 'halParentLeft', 'valParentTop', 64+223, 36, 40, 32, 'halLeft', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;      IntRegister0 := 1;
      [*] = ;      FloatRegister0 := gem_f;
      [*] = ;      StringRegister0 := ms;
      [*] = ;      GUIExecuteState('vvk.map.CreateProvinceIncomeTooltip');
      [*] = ;      SetGUIElementHint(elmHandle, StringRegister0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Explore %
      [*] = ;   // Terrain type
      [*] = ;   var terrainType : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType');
      [*] = ;   var terrainTypePrefix : String = '';
      [*] = ;   case terrainType of
      [*] = ;      gc_PlainTerrainType    : terrainTypePrefix := 'plain';
      [*] = ;      gc_ForestTerrainType   : terrainTypePrefix := 'forest';
      [*] = ;      gc_HillTerrainType     : terrainTypePrefix := 'hill';
      [*] = ;      gc_SwampTerrainType    : terrainTypePrefix := 'swamp';
      [*] = ;      gc_DesertTerrainType   : terrainTypePrefix := 'desert';
      [*] = ;      gc_DeadLandTerrainType : terrainTypePrefix := 'deadland';
      [*] = ;   end;
      [*] = ;   var hint : String;
      [*] = ;   var elmName : String = 'map_infopanel_terraintype_'+terrainTypePrefix;
      [*] = ;   text := GetLocaleTableListItemByID('tooltip', elmName);
      [*] = ;   var w, h : Integer;
      [*] = ;   var tmpFontSize : String = fontHandleT;
      [*] = ;   var textExplored : String = ' '+IntToStr(explored)+'%';
      [*] = ;   GetGUIElementFontTextFormatRect(tmpFontSize, textExplored, w, h);
      [*] = ;   var fColorR, fColorG, fColorB : Float;
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHnd, 'GetGrow');
      [*] = ;   var provGrow : Integer = IntRegister0;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHnd, 'GetLevel');
      [*] = ;   var oldLevel : Integer = IntRegister0;
      [*] = ;   IntRegister0 := oldLevel;
      [*] = ;   MapExecuteState('GetProvLevelParserByID');
      [*] = ;   var pProvLevel : Integer = IntRegister1;
      [*] = ;   var levelExplored : Integer = ParserGetIntValueByKeyByHandle(pProvLevel, 'Explored');
      [*] = ;   var bRooms : Boolean = False;
      [*] = ;   if (oldLevel<gc_MaxProvinceLevel) then
      [*] = ;   begin
      [*] = ;      if (explored>=levelExplored) or (provGrow<=0) then
      [*] = ;         bRooms := True;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (bRooms) or (explored>=100) then
      [*] = ;   begin
      [*] = ;      fColorR := gc_gui_fontcolor_NormalR;
      [*] = ;      fColorG := gc_gui_fontcolor_NormalG;
      [*] = ;      fColorB := gc_gui_fontcolor_NormalB;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      fColorR := gc_gui_fontcolor_RedR;
      [*] = ;      fColorG := gc_gui_fontcolor_RedG;
      [*] = ;      fColorB := gc_gui_fontcolor_RedB;
      [*] = ;   end;
      [*] = ;   GetGUIElementFontTextFormatRect(tmpFontSize, text, w, h);
      [*] = ;   elmHandle := _gui_CreateText(elmName, elmItemListHandle, text, 'halParentLeft', 'valParentTop', 170-(w div 2)-30, 37, w+30, 32, 'halMiddle', 'valMiddle', tmpFontSize, fColorR, fColorG, fColorB, 1);
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;   elmHandle := _gui_CreateText('map_infopanel_province_explored', elmItemListHandle, textExplored, 'halParentLeft', 'valParentTop', GetGUIElementPositionX(elmHandle)+(GetGUIElementWidth(elmHandle)), 37, 44, 32, 'halLeft', 'valMiddle', tmpFontSize, fColorR, fColorG, fColorB, 1);
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;   if (statMode=0) then
      [*] = ;   begin
      [*] = ;      elmHandle := _gui_CreateImage('map_infopanel_mood', elmItemListHandle, 'map.infopanel.mood' + moodPrefix, 'halParentLeft', 'valParentTop', 489, 8, 22, 22, 0);
      [*] = ;      var moodInd : Integer = 0;
      [*] = ;      if (mood<-5) then
      [*] = ;         moodInd := 75
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (mood>3) then
      [*] = ;            moodInd := 83
      [*] = ;         else
      [*] = ;            moodInd := 80+mood;
      [*] = ;      end;
      [*] = ;      hint := IntToStr(dummyUID)+',gui|'+IntToStr(moodInd)+'|512|tooltip|map_infopanel_mood.ext';
      [*] = ;      _gui_ft_AttachHint(elmHandle,'VVK.map.HintProvMoodCallback',hint); // mood
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;      if (mood=0) then
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.325);
      [*] = ;
      [*] = ;      if ((Unrest/gc_MaxUnrest)<0.8) or (mood>=0) then
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('map_infopanel_uprising_no', elmItemListHandle, 'map.infopanel.uprising', 'halParentLeft', 'valParentTop', 489+143, 8, 22, 22, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.4);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         elmHandle := _gui_CreateImage('map_infopanel_uprising', elmItemListHandle, 'map.infopanel.uprising', 'halParentLeft', 'valParentTop', 489+143, 8, 22, 22, 0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;      _gui_ft_AttachHint_I1(elmHandle,'VVK.map.HintProvMoodCallback',dummyUID);
      [*] = ;
      [*] = ;      if (iProvinceMarkCount>0) then
      [*] = ;      begin
      [*] = ;         const cProvinceMarkOffset = 7;
      [*] = ;         var elmProvinceLevelHandle : Integer = _gui_CreateDummy('map_infopanel_provincelevel', elmItemListHandle, 'halParentLeft', 'valParentTop', 583-(iProvinceMarkCount * round(cProvinceMarkOffset/2)), 46, 0, 0, 0);
      [*] = ;         var markInd : Integer = 0;
      [*] = ;         for markInd := 0 to iProvinceMarkCount-1 do
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('map_infopanel_mark_'+IntToStr(ProvinceLevel), elmProvinceLevelHandle, sProvinceMarkType, 'halParentRightWidth', 'valParentBottomHeight', 0 + markInd * cProvinceMarkOffset, 0, 14, 21, 0);
      [*] = ;            SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (mood>0) and (unrest>0) then
      [*] = ;         elmHandle := _gui_CreateImage('map_infopanel_uprising_direction_down', elmItemListHandle, 'map.infopanel.uprising.down', 'halParentLeft', 'valParentTop', 545, 0, 66, 15, 0)
      [*] = ;      else
      [*] = ;         if (mood<0) then
      [*] = ;            elmHandle := _gui_CreateImage('map_infopanel_uprising_direction_up', elmItemListHandle, 'map.infopanel.uprising.up', 'halParentLeft', 'valParentTop', 545, 0, 66, 15, 0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;      // Страж (проценты)
      [*] = ;      if (defenderID>0) then
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.covernumbers', 'halParentLeft', 'valParentTop', 856, 47, 0, 0, 0);
      [*] = ;         IntRegister0 := pProvDefender;
      [*] = ;         MapExecuteState('map.GetDefenderArmyLifePercent');
      [*] = ;         elmHandle := _gui_CreateText('', elmItemListHandle, IntToStr(IntRegister1)+'%', 'halParentLeft', 'valParentTop', 872, 54, 41, 19, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // Укрепление (проценты)
      [*] = ;      var wallHP : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Fort');
      [*] = ;      GameObjectExecuteStateByHandle(dummyHnd, 'GetMaxFortValue');
      [*] = ;      var maxWallHP : Integer = IntRegister0;
      [*] = ;      var castleWallPercent : Integer = round(100*WallHP/maxWallHP);
      [*] = ;      if (castle) then
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.covernumbers', 'halParentLeft', 'valParentTop', 856+63, 47, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateText('', elmItemListHandle, IntToStr(castleWallPercent)+'%', 'halParentLeft', 'valParentTop', 872+63, 54, 41, 19, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (wallBuildID>0) and (wallBuildIcon>0) then
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.covernumbers', 'halParentLeft', 'valParentTop', 856+63, 47, 0, 0, 0);
      [*] = ;            elmHandle := _gui_CreateText('', elmItemListHandle, IntToStr(castleWallPercent)+'%', 'halParentLeft', 'valParentTop', 872+63, 54, 41, 19, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // Количество сайтов
      [*] = ;      if (siteCount>0) then
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmItemListHandle, 'gamepanel03.provincelist.covernumbers', 'halParentLeft', 'valParentTop', 856+2*63, 47, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateText('', elmItemListHandle, IntToStr(siteCount), 'halParentLeft', 'valParentTop', 872+2*63, 54, 41, 19, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Кнопка перейти к провинции
      [*] = ;   var tag : Integer = cBaseProvIndex+provIndex;
      [*] = ;   elmBtnHandle := _gui_CreateButton('', elmItemListHandle, '', 'gamepanel03.btn.gotoprovince', 'halParentLeft', 'valParentTop', 1053, 10, 0, 0, cEventState, 'gui|550', tag);
      [*] = ;
      [*] = ;   ind := ind+1;
      [*] = ;end;
      [*] = ;SetGUIScrollEnabled(elmGuiLayer, (ind-1)>=minCount);
      [*] = ;// scroll height cutter
      [*] = ;//height := (ind)*87-16;
      [*] = ;//SetGUIElementHeight(elmGuiLayer, height+1);
      [*] = ;
      [*] = ;height := round((ind)*87);
      [*] = ;SetGUIElementHeight(elmGuiLayer, height);
      [*] = ;
      [*] = ;// restore scroller position
      [*] = ;//elmScrollLayer := GetGUIElementIndexByNameParent('provincelist.background.provincelist_scrollLayer.scroll_layer', _gui_GetLayerI());
      [*] = ;//elmVScroll := GetGUIElementVScroll(elmScrollLayer);
      [*] = ;SetGUIScrollBarPosition(elmVScroll, lastScrollPos);
      [*] = ;
      [*] = ;const cBtnClose = 101;
      [*] = ;elmHandle := _gui_CreateImage('', elmBackgroundHandle, 'gamepanel03.close.btn.placer', 'halParentMiddle', 'valParentBottomHeight', 0, -2, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmHandle, '', 'map.heropanel.btn.closewindow', 'halParentLeft', 'valParentTop', 86, 2, 0, 0, cEventState, 'menu|47', cBtnClose);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;//ParserFreeByHandle(pSortHexCells); // 'tmp'
      [*] = ;//ParserFreeByHandle(pTmpArray);
   struct.end
section.end

