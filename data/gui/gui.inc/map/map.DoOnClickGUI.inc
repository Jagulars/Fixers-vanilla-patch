section.begin
   Name = map.DoOnClickGUI
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.DOONCLICKGUI';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;
      [*] = ;procedure SetSelection(province_p : Integer);
      [*] = ;begin
      [*] = ;   gIntRegister_MapSelectedHex := province_p;
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UpdateHeroHUDSelectionState(goHnd : Integer; state : Boolean);
      [*] = ;begin
      [*] = ;   var frame : String;
      [*] = ;   var hudHnd : Integer = GetGUIGroupHUDCollectionItemByGameObject(_gui_GetLayer(cHUDStrategyHeroLayer), goHnd);
      [*] = ;   var elmHnd : Integer = GetGUIElementIndexByNameParent('map_radialhero_portrait_dummy.map_radialhero_portrait_image.map_radialhero_frame', hudHnd);
      [*] = ;
      [*] = ;   if (state) then frame := 'map.heroselection.yellowcircle'
      [*] = ;   else frame := 'map.heroselection.browncircle';
      [*] = ;   SetGUIElementMaterial(elmHnd, frame);
      [*] = ;   SetGUIElementVisible(GetGUIElementIndexByNameParent('map_radialhero_frame_selection', hudHnd), state);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetHexParserByProvinceRadialBtnHandle(elmHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var dummyUID : Integer = GetGameObjectUniqueIdByHandle(GetGUIElementTag(GetGUIElementParentByIndex(elmHandle)));
      [*] = ;
      [*] = ;   IntRegister0 := dummyUID;
      [*] = ;   StateMachineExecuteState(GetMapInitMachineHandle, 'GetProvinceParserByUID', 0);
      [*] = ;   Result := IntRegister1;
      [*] = ;
      [*] = ;   if (Result=0) then ErrorLog('map.DoOnClickGUI : gIntRegister_MapSelectedHex = 0');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure updateShopSortMode();
      [*] = ;begin
      [*] = ;   //reset shop scroller
      [*] = ;   var elmScrollLayer : Integer = _gui_GetWindow('map_shoppanel.map_shoppanel_bg.map_shoppanel_items.scroll_layer');
      [*] = ;   if (elmScrollLayer<>0) then
      [*] = ;   begin
      [*] = ;      var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;      if (elmVScroll<>0) then SetGUIScrollBarPosition(elmVScroll, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if gIntRegister_GUICurCastleMode <> 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 3;
      [*] = ;      GUIExecuteState('map.CreateCastleBuildWindow')
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gIntRegister_GUICurHeroMode := gc_HeroPanelInventory;
      [*] = ;      GUIExecuteState('map.CreateHeroWindow');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String =  GetGUIElementNameByIndex(elmHandle);
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var key : String = GetValueByName('Key');
      [*] = ;var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;
      [*] = ;if (not SameText(key, 'LButton')) then exit;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;case tag of
      [*] = ;   0 : begin
      [*] = ;      if (elmName='mesbuildinner') then
      [*] = ;      begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         gProfile.mesbuildinner := bChecked;
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (elmName='mesbuildouter') then
      [*] = ;      begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;         gProfile.mesbuildouter := bChecked;
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var elmSliderHandle : Integer;
      [*] = ;         if (gIntRegister_GUIScrollSliderHandle<>0) then
      [*] = ;            elmSliderHandle := gIntRegister_GUIScrollSliderHandle
      [*] = ;         else
      [*] = ;            elmSliderHandle := GetGUIElementParentByIndex(elmHandle);
      [*] = ;         var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;
      [*] = ;         if (elmName='btnSlider') or (elmName='lineSlider') then
      [*] = ;         begin
      [*] = ;            if (status='geMouseDown') then
      [*] = ;            begin
      [*] = ;               gIntRegister_GUIScrollSliderHandle := elmSliderHandle;
      [*] = ;
      [*] = ;               var mX, my : Integer;
      [*] = ;               var x2, y2 : Integer;
      [*] = ;               GetGUICurrentMouseCoord(mX, mY);
      [*] = ;               GUIInvalidateParentPositions(elmHandle);
      [*] = ;               GetGUIElementAlignPosition(elmHandle, x2, y2);
      [*] = ;               SetIntValueByName('SliderElementDragX', mX-x2);
      [*] = ;               SetIntValueByName('SliderElementDragY', mY-y2);
      [*] = ;               GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (gIntRegister_GUIScrollSliderHandle<>0) or ((GetValueByName('Press')='d') and (elmName='lineSlider')) then
      [*] = ;         begin
      [*] = ;            SetIntValueByName('SliderElementDragX', 14);
      [*] = ;            var value : Float = _gui_ModifySliderValueByMouseCoord(elmSliderHandle);
      [*] = ;
      [*] = ;            case sliderID of
      [*] = ;               'mesbuildgold' : begin
      [*] = ;                  gProfile.mesbuildgold := value;
      [*] = ;                  _gui_SetSliderText(elmSliderHandle, IntToStr(Round(value * 100))+'% %style(Symbols)%0%style(default)%');
      [*] = ;               end;
      [*] = ;               'mesbuildgem' : begin
      [*] = ;                  gProfile.mesbuildgem := value;
      [*] = ;                  _gui_SetSliderText(elmSliderHandle, IntToStr(Round(value * 100))+'% %style(Symbols)%1%style(default)%');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_gui_mainpanel_btnMenu : _cmd_Post('mapshowmenu','','1');
      [*] = ;   gc_gui_mainpanel_btnSettingsMenu : _cmd_Post('mapshowsettings','','');
      [*] = ;   gc_gui_mainpanel_btnEndTurn : _cmd_Post('mapnextturn','','');
      [*] = ;   gc_gui_mainpanel_btnCastle : _cmd_Post('mapgotocastle','','');
      [*] = ;   gc_gui_mainpanel_btnMap : _cmd_Post('mapgotomap','','');
      [*] = ;   gc_gui_mainpanel_btnDiplomacy : _cmd_Post('mapdiplomacy','','');
      [*] = ;   gc_gui_mainpanel_btnProvinceList, gc_gui_castlepanel_tabs_btnProvinceList : _cmd_Post('mapprovincelist','','');
      [*] = ;   gc_gui_mainpanel_btnStatistics, gc_gui_mainpanel_btnResourceHint : _cmd_Post('mapstatistics','','');
      [*] = ;   gc_gui_mainpanel_btnRitual : _cmd_Post('maprituals','','');
      [*] = ;   gc_gui_mainpanel_btnNextHero : _cmd_Post('mapnexthero','','');
      [*] = ;   gc_gui_mainpanel_btnAlchemy : _cmd_Post('mapalchemy','','');
      [*] = ;   gc_gui_castlepanel_tabs_btnBuild : _cmd_Post('castlebuild','','');
      [*] = ;   gc_gui_castlepanel_tabs_btnHero : _cmd_Post('castleheroes','','');
      [*] = ;   gc_gui_castlepanel_tabs_btnGarrison : _cmd_Post('castlegarrison','','');
      [*] = ;   gc_gui_castlepanel_tabs_btnInventory : _cmd_Post('castletreasury','','');
      [*] = ;   gc_gui_castlepanel_tabs_btnMagic : _cmd_Post('castlelibrary','','');
      [*] = ;   gc_gui_heropanel_btnCloseWindow: _cmd_Post('heroclosepanels','','');
      [*] = ;   gc_gui_heropanel_btnAstralAccept: _cmd_Post('heroclosepanels','1','');
      [*] = ;   gc_gui_garrisonpanel_btnCloseWindow: _cmd_Post('provinceclosegarrisonpanel','','');
      [*] = ;   gc_gui_heropanel_btnCloseWindowAccept : _cmd_Post('heroclosepanels','','1');
      [*] = ;   gc_gui_heropanel_btnSquad : _cmd_Post('herosquadpanel','','');
      [*] = ;   gc_gui_heropanel_btnInventory : _cmd_Post('heroinventorypanel','','');
      [*] = ;   gc_gui_heropanel_btnSpellbook : _cmd_Post('herospellbookpanel','','');
      [*] = ;   gc_gui_heropanel_btnHeroInfo : _cmd_Post('heroinfopanel','','');
      [*] = ;   gc_gui_heropanel_btnDismissHero : _cmd_Post('herodismisspanel','',GetGUIElementStringTag(elmHandle));
      [*] = ;   gc_gui_radialprovince_btnBuild :
      [*] = ;   begin
      [*] = ;      SetSelection(GetHexParserByProvinceRadialBtnHandle(elmHandle));
      [*] = ;      _cmd_Post('provincebuild','','');
      [*] = ;   end;
      [*] = ;   gc_gui_radialprovince_btnSite :
      [*] = ;   begin
      [*] = ;      SetSelection(GetHexParserByProvinceRadialBtnHandle(elmHandle));
      [*] = ;      _cmd_Post('provincesiteslist','2','');
      [*] = ;   end;
      [*] = ;   gc_gui_radialprovince_btnGuard :
      [*] = ;   begin
      [*] = ;      SetSelection(GetHexParserByProvinceRadialBtnHandle(elmHandle));
      [*] = ;      _cmd_Post('provincehireguard','','');
      [*] = ;   end;
      [*] = ;   gc_gui_radialprovince_btnGarrison :
      [*] = ;   begin
      [*] = ;      SetSelection(GetHexParserByProvinceRadialBtnHandle(elmHandle));
      [*] = ;      _cmd_Post('provincegarrison','','');
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnSortAll :
      [*] = ;   begin
      [*] = ;      gIntRegister_GUIShopSortMode := 0;
      [*] = ;      updateShopSortMode();
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnSortMagic :
      [*] = ;   begin
      [*] = ;      if (gIntRegister_GUIShopSortMode=1) then
      [*] = ;         gIntRegister_GUIShopSortMode := 0
      [*] = ;      else
      [*] = ;         gIntRegister_GUIShopSortMode := 1;
      [*] = ;      updateShopSortMode();
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnSortWeapon :
      [*] = ;   begin
      [*] = ;      if (gIntRegister_GUIShopSortMode=2) then
      [*] = ;         gIntRegister_GUIShopSortMode := 0
      [*] = ;      else
      [*] = ;         gIntRegister_GUIShopSortMode := 2;
      [*] = ;      updateShopSortMode();
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnSortArmor :
      [*] = ;   begin
      [*] = ;      if (gIntRegister_GUIShopSortMode=3) then
      [*] = ;         gIntRegister_GUIShopSortMode := 0
      [*] = ;      else
      [*] = ;         gIntRegister_GUIShopSortMode := 3;
      [*] = ;      updateShopSortMode();
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnSortJewels :
      [*] = ;   begin
      [*] = ;      if (gIntRegister_GUIShopSortMode=4) then
      [*] = ;         gIntRegister_GUIShopSortMode := 0
      [*] = ;      else
      [*] = ;         gIntRegister_GUIShopSortMode := 4;
      [*] = ;      updateShopSortMode();
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnSortScrolls :
      [*] = ;   begin
      [*] = ;      if (gIntRegister_GUIShopSortMode=5) then
      [*] = ;         gIntRegister_GUIShopSortMode := 0
      [*] = ;      else
      [*] = ;         gIntRegister_GUIShopSortMode := 5;
      [*] = ;      updateShopSortMode();
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnSortFlags :
      [*] = ;   begin
      [*] = ;      if (gIntRegister_GUIShopSortMode=6) then
      [*] = ;         gIntRegister_GUIShopSortMode := 0
      [*] = ;      else
      [*] = ;         gIntRegister_GUIShopSortMode := 6;
      [*] = ;      updateShopSortMode();
      [*] = ;   end;
      [*] = ;   gc_gui_heropanel_btnChoosePrevHero, gc_gui_heropanel_btnChooseNextHero :
      [*] = ;   begin
      [*] = ;      var stringTag : String = GetGUIElementStringTag(elmHandle);
      [*] = ;      if (IsDelimiterCharExists(stringTag, gc_gui_DelimiterChar)) then
      [*] = ;      begin
      [*] = ;         var delimiterStringCount : Integer = GetDelimiterStringCount(stringTag, gc_gui_DelimiterChar, gc_gui_QuoteChar);
      [*] = ;         if (delimiterStringCount>=2) then
      [*] = ;         begin
      [*] = ;            var newHeroUID : Integer = StrToInt(GetDelimiterStringByIndex(stringTag, gc_gui_DelimiterChar, gc_gui_QuoteChar, 0));
      [*] = ;            var side : Integer = StrToInt(GetDelimiterStringByIndex(stringTag, gc_gui_DelimiterChar, gc_gui_QuoteChar, 1));
      [*] = ;            if (side=0) then
      [*] = ;               gIntRegister_GUIActiveHeroUID1 := newHeroUID
      [*] = ;            else
      [*] = ;               gIntRegister_GUIActiveHeroUID2 := newHeroUID;
      [*] = ;
      [*] = ;            if (gIntRegister_MapSelectedUID<>0) and (gIntRegister_MapSelectedUID<>gIntRegister_GUIActiveHeroUID1) then
      [*] = ;            begin
      [*] = ;               UpdateHeroHUDSelectionState(GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID), false); //unselect prev unit
      [*] = ;               gIntRegister_MapSelectedUID := gIntRegister_GUIActiveHeroUID1;
      [*] = ;               var goHnd : Integer = GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;               UpdateHeroHUDSelectionState(goHnd, true);
      [*] = ;               GameObjectExecuteStateByHandle(goHnd, 'Select');
      [*] = ;               GUIExecuteState('map.DrawGroupDataViewer');
      [*] = ;               gIntRegister_GUIDrawPathUID := gIntRegister_MapSelectedUID;
      [*] = ;               GUIExecuteState('map.DrawPath');
      [*] = ;               _map_RefreshProvincesHUDs();
      [*] = ;
      [*] = ;               IntRegister0 := 0; //DummyUID - if 0, then get activeHero current UID
      [*] = ;               IntRegister1 := gIntRegister_MapSelectedUID; //setActiveHeroUID - if 0, then choose first picked hero
      [*] = ;               IntRegister2 := 0; //goUIDEndPointReached
      [*] = ;               GUIExecuteState('map.CreateHeroMultiHUD');
      [*] = ;            end;
      [*] = ;
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnRepair :
      [*] = ;   begin
      [*] = ;      gBoolRegister_RepairItemMode := not gBoolRegister_RepairItemMode;
      [*] = ;
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;      begin
      [*] = ;         GUIExecuteState('map.CreateHeroWindow');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_HeroPanelInventory;
      [*] = ;         GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;      end;
      [*] = ;      GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   end;
      [*] = ;   gc_gui_shoppanel_btnRepairAll :
      [*] = ;   begin
      [*] = ;      if (gIntRegister_GUIActiveHeroUID1<>0) then
      [*] = ;         goHandle := GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;      IntRegister0 := gIntRegister_MapCurrentShop;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'RepairInvItems');
      [*] = ;
      [*] = ;      GUIExecuteState('map.CreateHeroWindow');
      [*] = ;      _gui_PlaySound('interface', 'repair_all');
      [*] = ;   end;
      [*] = ;   gc_gui_recruithero_btnRecruit :
      [*] = ;   begin
      [*] = ;      IntRegister0 := StrToInt(GetGUIElementStringTag(elmHandle));
      [*] = ;      GUIExecuteState('vvk.map.ConfirmRecruitHeroWindow');
      [*] = ;   end;
      [*] = ;   gc_gui_question_btnCheckBoxMesLoafers :
      [*] = ;   begin
      [*] = ;      var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;      gProfile.mesloafers := bChecked;
      [*] = ;      SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

