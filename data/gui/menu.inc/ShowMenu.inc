section.begin
   Name = ShowMenu
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\SHOWMENU';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;const cTemplateName = 'list_menu';
      [*] = ;const cHeaderTextOffset = $17;
      [*] = ;const cHeaderStripe = $16;
      [*] = ;const cScreenOffset = $15;
      [*] = ;const cTexHeaderStripe = 'element.strip.322';
      [*] = ;
      [*] = ;var whd,qhd : Integer;
      [*] = ;var ret_str : String;
      [*] = ;var if_handle : Integer;
      [*] = ;var window_d : TInterfaceElementData;
      [*] = ;
      [*] = ;qhd := _gui_GetWindow(cQuickAccessMenuWindowName);
      [*] = ;if not GetGUIElementVisible(qhd) then
      [*] = ;begin
      [*] = ;   var text : String;
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;   var ehd : Integer;
      [*] = ;
      [*] = ;   _qaccess_GetTopMenuCommands(4,ret_str);
      [*] = ;   StringRegister0 := cQuickAccessMenuWindowName;
      [*] = ;   StringRegister1 := 'EventMenu';
      [*] = ;   StringRegister2 := 'VVK.MainMenuCommands';
      [*] = ;   StringRegister3 := ret_str;
      [*] = ;   IntRegister0 := $f00;
      [*] = ;   GUIExecuteState('ShowListMenu');
      [*] = ;   qhd := IntRegister0;
      [*] = ;
      [*] = ;   if_handle := _gui_GetInterfaceWindowHandle(cTemplateName);
      [*] = ;   text := GetLocaleTableListItemByID('menu', 'quick_access_header');
      [*] = ;
      [*] = ;   _gui_GetInterfaceElement(if_handle,cHeaderStripe,window_d);
      [*] = ;   _sys_FillRect(tmp_pos,0,GetGUITextureHeight(cTexHeaderStripe) div (-2),0,0);
      [*] = ;   ehd := _gui_CreateImage_VVK('qa_text',qhd,cTexHeaderStripe,window_d.align,tmp_pos);
      [*] = ;   _sys_FillRect(tmp_pos,0,_gui_ie_GetOffsetY(if_handle,cHeaderTextOffset,cHeaderStripe,false),0,0);
      [*] = ;   _gui_CreateText_VVK('',ehd,text,gc_gui_align_parent_mt,tmp_pos,gc_gui_align_middle,window_d.font_handle,window_d.color);
      [*] = ;
      [*] = ;   _gui_GetInterfaceElement(if_handle,cScreenOffset,window_d);
      [*] = ;   SetGUIElementPositionX(qhd,GetViewerWidth()-(GetGUIElementWidth(qhd)+window_d.p.size.w));
      [*] = ;   SetGUIElementPositionY(qhd,GetViewerHeight()-(GetGUIElementHeight(qhd)+window_d.p.size.h));
      [*] = ;
      [*] = ;   //_gui_GetInterfaceElement(if_handle,cHeaderTextOffset,window_d);
      [*] = ;   //_gui_CreateText_VVK('qa_text',qhd,'menu|quick_access_header',gc_gui_align_parent_lt,window_d.p,gc_gui_align_middle,window_d.font_handle,window_d.color);
      [*] = ;end;
      [*] = ;
      [*] = ;whd := _gui_GetWindow('main_menu');
      [*] = ;if not GetGUIElementVisible(whd) then
      [*] = ;begin
      [*] = ;   GUIExecuteState('ShowMainMenu');
      [*] = ;   if not GetGUIElementVisible(_gui_GetWindow(cBaseAdsWindowName)) then
      [*] = ;      GUIExecuteState('VVK.BannerWindowShow');
      [*] = ;   //whd := IntRegister0;
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('ShowHeader');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;//IntRegister0 := whd;
   struct.end
section.end

