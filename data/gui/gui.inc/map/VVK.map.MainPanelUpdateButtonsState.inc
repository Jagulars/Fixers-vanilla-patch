section.begin
   Name = VVK.map.MainPanelUpdateButtonsState
   Description : struct.begin
      [*] = ;IntRegister0 - parent window handle, if zero then IntRegister1 is a button tag to check,
      [*] = ;in this case BoolRegister0 will be true if button is available
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure GetButtonBaseTextureName(name : String;var base_name : String);
      [*] = ;begin
      [*] = ;   var i,no : Integer;
      [*] = ;   var temp_str : String;
      [*] = ;
      [*] = ;   no := _sa_GetNum_D(name,$2e);
      [*] = ;   base_name := '';
      [*] = ;   for i := 0 to no-2 do
      [*] = ;   begin
      [*] = ;      _sa_Get_D(name,i,$2e,temp_str);
      [*] = ;      _sa_Add_D(base_name,temp_str,'.');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function UpdateCastleButtonProperties(ca : Integer; ehd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var active,ca1 : Integer;
      [*] = ;   var temp_str : String;
      [*] = ;
      [*] = ;   ca1 := ca;
      [*] = ;   active := ((ca and $200) shr 9);
      [*] = ;   if active <> 0 then
      [*] = ;      ca := 2;
      [*] = ;
      [*] = ;   if ehd <> 0 then
      [*] = ;   begin
      [*] = ;      GetButtonBaseTextureName(GetGUIElementMaterial(ehd),temp_str);
      [*] = ;
      [*] = ;      //if _log then _log_Gui('Name: '+GetGUIElementNameByIndex(ehd)+', Button: '+temp_str+', Tex: '+GetGUIElementMaterial(ehd)+', CA: '+IntToStr(ca1));
      [*] = ;      if active <> 0 then
      [*] = ;         temp_str := temp_str+'.pressed'
      [*] = ;      else
      [*] = ;         temp_str := temp_str+'.disabled';
      [*] = ;      SetGUIElementVisibleProperties(ehd, 'DisableProperty',temp_str,0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := (ca and $ff);
      [*] = ;end;
      [*] = ;
      [*] = ;// 0 - wrong tag, 1 - show, 2 - hide
      [*] = ;function IsAccepted(ehd : Integer; tag : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var e_accepted, visible : Boolean;
      [*] = ;   var ca,active : Integer;
      [*] = ;   var temp_str : String;
      [*] = ;
      [*] = ;   e_accepted := true;
      [*] = ;   visible := true;
      [*] = ;
      [*] = ;   ca := -1;
      [*] = ;   case tag of
      [*] = ;      gc_gui_mainpanel_btnMenu: begin
      [*] = ;         ca := _cmd_Check('mapshowmenu','','1');
      [*] = ;         if ehd <> 0 then
      [*] = ;         begin
      [*] = ;            if _cmd_Check('mapgotocastle','','') <> 0 then
      [*] = ;               SetGUIElementHint(ehd,'gui|96|MT|0|0|mapshowmenu')
      [*] = ;            else
      [*] = ;               SetGUIElementHint(ehd,'gui|96')
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_gui_mainpanel_btnSettingsMenu: begin
      [*] = ;         ca := _cmd_Check('mapshowsettings','','1');
      [*] = ;      end;
      [*] = ;      gc_gui_mainpanel_btnCastle, gc_gui_mainpanel_btnMap: begin
      [*] = ;         ca := _cmd_Check('mapgotocastle','','');
      [*] = ;         if ehd <> 0 then
      [*] = ;         begin
      [*] = ;            if ca <> 0 then
      [*] = ;            begin
      [*] = ;               _gui_ReskinButton_VVK(ehd,'map.mainpanel.btn.tocastle',False);
      [*] = ;               SetGUIElementTag(ehd,gc_gui_mainpanel_btnCastle);
      [*] = ;               SetGUIElementHint(ehd,'gui|97|MT|0|0|mapgotocastle');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               _gui_ReskinButton_VVK(ehd,'map.mainpanel.btn.tomap',False);
      [*] = ;               SetGUIElementTag(ehd,gc_gui_mainpanel_btnMap);
      [*] = ;               SetGUIElementHint(ehd,'gui|736|MT|0|0|mapgotomap');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if ca = 0 then ca := _cmd_Check('mapgotomap','','');
      [*] = ;      end;
      [*] = ;      gc_gui_mainpanel_btnRitual: begin
      [*] = ;         ca := _cmd_Check('maprituals','','1');
      [*] = ;         if ca <> 0 then
      [*] = ;         begin
      [*] = ;            if ehd <> 0 then
      [*] = ;            begin
      [*] = ;               if gBoolRegister_BtnRitualBlink and (gIntRegister_GUICurHeroMode = -1) then
      [*] = ;                  _gui_CreateBlinkElement('btnRitual', ehd, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;
      [*] = ;               if ((ca and $ff) = 1) and ((ca and $100) <> 0) then
      [*] = ;                  _gui_ReskinButton_VVK(ehd,'btn.ritual.marked',False)
      [*] = ;               else
      [*] = ;                  _gui_ReskinButton_VVK(ehd,'map.mainpanel.btn.ritual',False);
      [*] = ;
      [*] = ;               if ((ca and $ff) <> 1) then
      [*] = ;                  SetGUIElementHint(ehd, 'gui|637|MT|0|0|maprituals')
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if ((ca and $100) <> 0) then
      [*] = ;                  begin
      [*] = ;                     var temp_str,temp_str2 : String;
      [*] = ;
      [*] = ;                     temp_str := GetLocaleTableListItemByID('gui', '95')+' ('+GetLocaleTableListItemByID('message', '9.description')+')';
      [*] = ;                     _cmd_GetHotKey('maprituals','',temp_str2);
      [*] = ;                     if temp_str2 <> '' then
      [*] = ;                        temp_str := temp_str + ' ('+StrToUpperCase(temp_str2)+')';
      [*] = ;                     SetGUIElementHint(ehd,temp_str);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     SetGUIElementHint(ehd, 'gui|95|MT|0|0|maprituals');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            ca := ca and $ff;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_gui_mainpanel_btnAlchemy: begin
      [*] = ;         ca := _cmd_CheckNF('mapalchemy','','');
      [*] = ;         if (ehd <> 0) then
      [*] = ;         begin
      [*] = ;            if (ca = 1) then
      [*] = ;               SetGUIElementVisible(ehd, True)
      [*] = ;            else
      [*] = ;               SetGUIElementVisible(ehd, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_gui_castlepanel_tabs_btnMagic: begin
      [*] = ;         active := _cmd_Check('castlelibrary','','1');
      [*] = ;         ca := UpdateCastleButtonProperties(active,ehd);
      [*] = ;         if (ca <> 0) and (ehd <> 0) then
      [*] = ;         begin
      [*] = ;            if (ca = 1) or ((active and $100) <> 0) then
      [*] = ;               SetGUIElementHint(ehd, 'gui|562|MT|0|0|castlelibrary')
      [*] = ;            else
      [*] = ;               SetGUIElementHint(ehd, 'gui|638|MT|0|0|castlelibrary');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_gui_mainpanel_btnDiplomacy: ca := _cmd_Check('mapdiplomacy','','');
      [*] = ;      gc_gui_mainpanel_btnProvinceList: ca := _cmd_Check('mapprovincelist','','');
      [*] = ;      gc_gui_mainpanel_btnStatistics: ca := _cmd_Check('mapstatistics','','');
      [*] = ;      gc_gui_heropanel_btnDismissHero: ca := _cmd_Check('herodismiss','','');
      [*] = ;      gc_gui_heropanel_btnHeroInfo: ca := _cmd_Check('heroinfo','','');
      [*] = ;      gc_gui_heropanel_btnInventory: ca := _cmd_Check('heroinventory','','');
      [*] = ;      gc_gui_heropanel_btnSquad: ca := _cmd_Check('herosquad','','');
      [*] = ;      gc_gui_heropanel_btnSpellbook: ca := _cmd_Check('herospellbook','','');
      [*] = ;      gc_gui_mainpanel_btnNextHero: begin
      [*] = ;         if gBoolRegister_BtnNextHeroBlink and (gIntRegister_GUICurHeroMode = -1) and (ehd <> 0) then
      [*] = ;            _gui_CreateBlinkElement('btnNextHero', ehd, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;         ca := _cmd_Check('mapnexthero','','');
      [*] = ;      end;
      [*] = ;      gc_gui_castlepanel_tabs_btnHero: begin
      [*] = ;         ca := _cmd_Check('castleheroes','','1');
      [*] = ;         ca := UpdateCastleButtonProperties(ca,ehd);
      [*] = ;      end;
      [*] = ;      gc_gui_castlepanel_tabs_btnGarrison: begin
      [*] = ;         ca := _cmd_Check('castlegarrison','','1');
      [*] = ;         ca := UpdateCastleButtonProperties(ca,ehd);
      [*] = ;      end;
      [*] = ;      gc_gui_castlepanel_tabs_btnBuild: begin
      [*] = ;         ca := _cmd_Check('castlebuild','','1');
      [*] = ;         if ca <> 0 then
      [*] = ;         begin
      [*] = ;            if ehd <> 0 then
      [*] = ;            begin
      [*] = ;               if gBoolRegister_BtnCastleBuildBlink and (gIntRegister_GUICurHeroMode = -1) then
      [*] = ;                  _gui_CreateBlinkElement('btnCastleBuild', ehd, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;               if ((ca and $ff) = 1) and ((ca and $100) <> 0) then
      [*] = ;                  _gui_ReskinButton_VVK(ehd,'radialprovince.btn.build.marked',False)
      [*] = ;               else
      [*] = ;                  _gui_ReskinButton_VVK(ehd,'map.mainpanel.btn.build',False);
      [*] = ;
      [*] = ;               if ((ca and $ff) <> 1) then
      [*] = ;                  SetGUIElementHint(ehd, 'gui|558|0|0|0|castlebuild')
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if ((ca and $100) <> 0) then
      [*] = ;                     SetGUIElementHint(ehd, 'message|2|256|0|0|castlebuild')
      [*] = ;                  else
      [*] = ;                     SetGUIElementHint(ehd,'gui|558|0|0|0|castlebuild');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         ca := UpdateCastleButtonProperties(ca,ehd);
      [*] = ;      end;
      [*] = ;      gc_gui_castlepanel_tabs_btnInventory: begin
      [*] = ;         ca := _cmd_Check('castletreasury','','1');
      [*] = ;         ca := UpdateCastleButtonProperties(ca,ehd);
      [*] = ;      end;
      [*] = ;      gc_gui_mainpanel_btnEndTurn: ca := _cmd_Check('mapnextturn','','');
      [*] = ;      else begin
      [*] = ;         if (tag >= gc_gui_mainpanel_btnPopupFirst) and (tag <= gc_gui_mainpanel_btnPopupLast) then
      [*] = ;         begin
      [*] = ;            if ehd <> 0 then
      [*] = ;            begin
      [*] = ;               var tag_str,tmp_str : String;
      [*] = ;               var no : Integer;
      [*] = ;
      [*] = ;               tmp_str := GetGUIElementStringTag(ehd);
      [*] = ;               StringRegister0 := tmp_str;
      [*] = ;               GUIExecuteState('VVK.map.MainPanelGetPopupButtons');
      [*] = ;
      [*] = ;               no := _sa_GetAsInt(StringRegister1,0);
      [*] = ;               _sa_Get(StringRegister0,no*5+1,tmp_str);
      [*] = ;               _gui_ReskinButton_VVK(ehd,tmp_str,False);
      [*] = ;
      [*] = ;               if (not BoolRegister0) then
      [*] = ;               begin
      [*] = ;                  visible := false;
      [*] = ;                  SetGUIElementEnabled(ehd,false);
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  SetGUIElementEnabled(ehd,true);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            e_accepted := False;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ca <> -1 then
      [*] = ;   begin
      [*] = ;      ca := ca and $ff;
      [*] = ;      if ca = 0 then
      [*] = ;         e_accepted := false
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ca = 2 then
      [*] = ;            visible := false;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if e_accepted then
      [*] = ;   begin
      [*] = ;      if visible then
      [*] = ;         Result := 1
      [*] = ;      else
      [*] = ;         Result := 2;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;var windowHandle,k,ehd,tag,elmTag : Integer;
      [*] = ;
      [*] = ;windowHandle := IntRegister0;
      [*] = ;
      [*] = ;if _log then _log_Values('Children_No',GetGUIElementChildrenCount(windowHandle),0,0,0,0,0);
      [*] = ;
      [*] = ;if windowHandle = 0 then
      [*] = ;begin
      [*] = ;   tag := IsAccepted(0,IntRegister1);
      [*] = ;   if tag = 1 then
      [*] = ;      BoolRegister0 := true
      [*] = ;   else
      [*] = ;      BoolRegister0 := false;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   for k := 0 to GetGUIElementChildrenCount(windowHandle)-1 do
      [*] = ;   begin
      [*] = ;      ehd := GetGUIElementChildrenByIndex(windowHandle,k);
      [*] = ;      elmTag := GetGUIElementTag(ehd);
      [*] = ;      tag := IsAccepted(ehd, elmTag);
      [*] = ;      if tag <> 0 then
      [*] = ;      begin
      [*] = ;         if tag = 1 then
      [*] = ;         begin
      [*] = ;            SetGUIElementEnabled(ehd,true);
      [*] = ;            case elmTag of
      [*] = ;               gc_gui_mainpanel_btnCastle : begin
      [*] = ;                  if gIntRegister_GUICurHeroMode = -1 then
      [*] = ;                  begin
      [*] = ;                     if gBoolRegister_BtnCastleBlink and (gIntRegister_GUICurCastleMode = 0) and (gIntRegister_GUICurHeroMode = -1) then
      [*] = ;                     begin
      [*] = ;                        var elmBlink : Integer = _gui_CreateBlinkElement('btnCastle', ehd, 'gamepanel01.btn.endturn.highlight', false, 0, 0, 0, 0);
      [*] = ;                        var width : Integer = GetGUIElementWidth(elmBlink);
      [*] = ;                        var posX : Integer = GetGUIElementPositionX(elmBlink);
      [*] = ;
      [*] = ;                        SetGUIElementWidth(elmBlink, -width);
      [*] = ;                        SetGUIElementPositionX(elmBlink, posX + width);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_gui_mainpanel_btnMap : begin
      [*] = ;                  if gBoolRegister_BtnCastleCloseBlink and (gIntRegister_GUICurHeroMode = -1) then
      [*] = ;                  begin
      [*] = ;                     var elmBlink : Integer = _gui_CreateBlinkElement('btnCastleClose', ehd, 'gamepanel01.btn.endturn.highlight', false, 0, 0, 0, 0);
      [*] = ;                     var width : Integer = GetGUIElementWidth(elmBlink);
      [*] = ;                     var posX : Integer = GetGUIElementPositionX(elmBlink);
      [*] = ;
      [*] = ;                     SetGUIElementWidth(elmBlink, -width);
      [*] = ;                     SetGUIElementPositionX(elmBlink, posX + width);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_gui_mainpanel_btnStatistics : begin
      [*] = ;                  if gBoolRegister_BtnStatisticsBlink and (gIntRegister_GUICurHeroMode = -1) then
      [*] = ;                     _gui_CreateBlinkElement('btnStatistics', ehd, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;               end;
      [*] = ;               gc_gui_mainpanel_btnEndTurn : begin
      [*] = ;                  if gBoolRegister_BtnEndTurnBlink and (gIntRegister_GUICurHeroMode = -1) then
      [*] = ;                     _gui_CreateBlinkElement('btnEndTurn', ehd, 'gamepanel01.btn.endturn.highlight', false, 0, 0, 0, 0);
      [*] = ;               end;
      [*] = ;               gc_gui_mainpanel_btnDiplomacy : begin
      [*] = ;                  if gBoolRegister_BtnDiplomacyBlink and (gIntRegister_GUICurHeroMode = -1) then
      [*] = ;                     _gui_CreateBlinkElement('btnDiplomacy', ehd, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0)
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var plIndex : Integer;
      [*] = ;                     var myPlIndex : Integer = GetPlayerIndexByHandle(GetPlayerHandleInterfaceIO);
      [*] = ;                     for plIndex := 0 to gGame.map.players-1 do
      [*] = ;                     begin
      [*] = ;                        if plIndex <> myPlIndex then
      [*] = ;                        begin
      [*] = ;                           if (gArrDiplomacy[plIndex][myPlIndex].displayPriority > 0) then
      [*] = ;                           begin
      [*] = ;                              _gui_CreateBlinkElement('btnDiplomacy', ehd, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;                              gBoolRegister_BtnDiplomacyBlink := true;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_gui_mainpanel_btnAlchemy: GUIElementBringToFront(ehd);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            SetGUIElementEnabled(ehd,false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

