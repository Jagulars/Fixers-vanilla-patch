section.begin
   Name = ShowListMenu
   UsedFileName =
   Description : struct.begin
      [*] = ;StringRegister0 - menu window name
      [*] = ;StringRegister1 - event name
      [*] = ;StringRegister2 - commands name
      [*] = ;StringRegister3 - string array of commands:
      [*] = ;  if first char is '#' then it is command name, else it is attribute name
      [*] = ;IntRegister0 - & 0xff - root window mode (0-default), &0x100 - if not 1 then show tooltips
      [*] = ; & 0x200 - do not show header
      [*] = ; & 0x400 - treat n/a as disabled
      [*] = ; & 0x800 - use cTopOffset for first button position
      [*] = ;Returns:
      [*] = ;   IntRegister0 - resulting window handle
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;const cShowButtonTips = $100; // set to $100 to disable button tips
      [*] = ;const cMaxItems = 20;
      [*] = ;const cTemplateName = 'list_menu';
      [*] = ;const cDragon = $1e;
      [*] = ;const cButton = $1d;
      [*] = ;const cButtonText = $1c;
      [*] = ;const cButtonDY = $1b;
      [*] = ;const cGameHeader = $1a;
      [*] = ;const cHeaderWindowOffset = $19;
      [*] = ;const cScreenEdgesOffset = $18;
      [*] = ;// 13-17 reserved for quick access menu
      [*] = ;const cTopOffset = $12;
      [*] = ;
      [*] = ;var windowName : String = StringRegister0;
      [*] = ;var eventName : String = StringRegister1;
      [*] = ;var cmdName : String = StringRegister2;
      [*] = ;var tags_str : String = StringRegister3;
      [*] = ;var root_mode : Integer = (IntRegister0 and $ff);
      [*] = ;var show_tips : Integer =  (IntRegister0 and $100);
      [*] = ;var hide_header : Integer =  (IntRegister0 and $200);
      [*] = ;var na_as_disabled: Integer =  (IntRegister0 and $400);
      [*] = ;var top_offset: Integer =  (IntRegister0 and $800);
      [*] = ;var temp_str,temp_str2,temp_str3,cmd,ret_str : String;
      [*] = ;var whd,ehd,windowHandle,h,no,i,bn : Integer;
      [*] = ;var if_handle : Integer;
      [*] = ;var elem_d,elem2_d,text_d,window_d : TInterfaceElementData;
      [*] = ;var pos : TRectangle;
      [*] = ;var btn_tag : array [0..cMaxItems] of Integer;
      [*] = ;var btn_attr : array [0..cMaxItems] of Integer;
      [*] = ;var btn_text : array [0..cMaxItems] of String;
      [*] = ;var btn_hotkeys : array [0..cMaxItems] of String;
      [*] = ;
      [*] = ;if root_mode = 0 then
      [*] = ;   root_mode := cRootWindowActive;
      [*] = ;
      [*] = ;if_handle := _gui_GetInterfaceWindowHandle(cTemplateName);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,window_d);
      [*] = ;
      [*] = ;windowHandle := _gui_GetWindow(windowName);
      [*] = ;if windowHandle <> 0 then
      [*] = ;   RemoveGUIElement(windowHandle);
      [*] = ;
      [*] = ;bn := _sa_GetNum(tags_str);
      [*] = ;no := 0;
      [*] = ;cmd := 'menumainbutton';
      [*] = ;
      [*] = ;windowHandle := _cmd_RegisterStateForDummy('temp_menu_window',cmdName,'',root_mode,0);
      [*] = ;
      [*] = ;if _log then Log('STR: '+tags_str+', NO:'+IntToStr(bn));
      [*] = ;for i := 0 to bn-1 do
      [*] = ;begin
      [*] = ;   if no >= cMaxItems then
      [*] = ;      break;
      [*] = ;
      [*] = ;   _sa_Get(tags_str,i,temp_str);
      [*] = ;   if SubStr(temp_str,1,1) = '#' then
      [*] = ;   begin
      [*] = ;      if _log then Log('LM: '+cmd);
      [*] = ;      cmd := SubStr(temp_str,2,StrLength(temp_str)-1);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      h := _cmd_CheckExtNF(cmd,temp_str,'',ret_str);
      [*] = ;      if (h <> 0) or (na_as_disabled <> 0) then
      [*] = ;      begin
      [*] = ;         btn_tag[no] := _sa_GetAsInt(ret_str,0);
      [*] = ;         btn_attr[no] := _sa_GetAsInt(ret_str,1);
      [*] = ;         if (h = 2) or (h=0) then
      [*] = ;            btn_attr[no] := btn_attr[no] or $80;
      [*] = ;         _sa_Get(ret_str,2,btn_text[no]);
      [*] = ;         if show_tips = cShowButtonTips then
      [*] = ;            _cmd_GetHotKey(cmd,temp_str,btn_hotkeys[no])
      [*] = ;         else
      [*] = ;            btn_hotkeys[no] := '';
      [*] = ;         if _log then Log('TAG: '+IntToStr(btn_tag[no])+', ATTR: '+IntToStr(btn_attr[no])+', TXT: '+btn_text[no]);
      [*] = ;         no := no + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;RemoveGUIElement(windowHandle);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cButton,elem_d);
      [*] = ;if top_offset > 0 then
      [*] = ;begin
      [*] = ;   _gui_GetInterfaceElement(if_handle,cTopOffset,elem2_d);
      [*] = ;   top_offset := elem2_d.p.size.h;
      [*] = ;end
      [*] = ;else
      [*] = ;   top_offset := elem_d.p_raw.pos.y;
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cButtonDY,elem2_d);
      [*] = ;_gui_GetInterfaceElement(if_handle,cButtonText,text_d);
      [*] = ;text_d.p.pos.x := text_d.p_raw.pos.x-elem_d.p_raw.pos.x;
      [*] = ;text_d.p.pos.y := text_d.p_raw.pos.y-elem_d.p_raw.pos.y;
      [*] = ;
      [*] = ;h := top_offset+(window_d.p.size.h-(elem_d.p_raw.pos.y+elem_d.p.size.h))+no*(elem_d.p.size.h+elem2_d.p.size.h)-elem2_d.p.size.h;
      [*] = ;
      [*] = ;_sys_FillRect(pos,0,0,elem_d.p.size.w+(elem_d.p_raw.pos.x*2),h);
      [*] = ;windowHandle := _gui_CreateScalableWindow_VVK(windowName,_gui_GetLayerI(),gc_gui_align_parent_lt,pos,'common_window');
      [*] = ;_gui_SetScaleableWindowBkgBlend(windowHandle,0.65);
      [*] = ;SetGUIAllowEvents(windowHandle, True, False, False);
      [*] = ;
      [*] = ;_sys_FillRect(pos,0,top_offset,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   if btn_hotkeys[i] <> '' then
      [*] = ;      temp_str := GetLocaleTableListItemByID('menu', 'hotkeys')+' ('+btn_hotkeys[i]+')'
      [*] = ;   else
      [*] = ;      temp_str := '';
      [*] = ;   whd := _gui_CreateButton_VVK('button_'+IntToStr(i),windowHandle,'','common.btn',gc_gui_align_parent_mt,pos,eventName,temp_str,btn_tag[i]);
      [*] = ;   SetGUIElementUserBlend(whd,0.7);
      [*] = ;
      [*] = ;   if btn_text[i] = '' then
      [*] = ;      temp_str := 'menu|'+IntToStr(btn_tag[i] and $7fff)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if StrExists(btn_text[i],'#') then
      [*] = ;      begin
      [*] = ;         _sa_Get_D(btn_text[i],0,$23,temp_str2);
      [*] = ;         _sa_Get_D(btn_text[i],1,$23,temp_str3);
      [*] = ;         temp_str := temp_str2;
      [*] = ;         _sa_Add(temp_str,temp_str3);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         temp_str := btn_text[i];
      [*] = ;   end;
      [*] = ;   ehd := _gui_CreateText_VVK('text',whd,temp_str,gc_gui_align_parent_lt,text_d.p,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;   if ((btn_attr[i] and $80) <> 0) then
      [*] = ;   begin
      [*] = ;      SetGUIElementEnabled(whd,False);
      [*] = ;      SetGUIElementColor(ehd,0.5,0.5,0.5,1);
      [*] = ;   end;
      [*] = ;   if ((btn_attr[i] and 1) <> 0) then
      [*] = ;   begin
      [*] = ;      SetGUIElementVisibleProperties(whd, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementVisibleProperties(whd, 'UpProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementVisibleProperties(whd, 'HoverProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   pos.pos.y := pos.pos.y + (elem_d.p.size.h+elem2_d.p.size.h);
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cHeaderWindowOffset,elem_d);
      [*] = ;_gui_GetInterfaceElement(if_handle,cScreenEdgesOffset,elem2_d);
      [*] = ;
      [*] = ;whd := _gui_GetWindow(cListMenuHeaderWindowName);
      [*] = ;if (whd = 0) and (hide_header = 0) then
      [*] = ;begin
      [*] = ;   GUIExecuteState('ShowHeader');
      [*] = ;   whd := IntRegister0;
      [*] = ;end;
      [*] = ;//i := _gui_GetWindow(cBaseAdsWindowName);
      [*] = ;//if i <> 0 then
      [*] = ;//   pos.pos.x := (GetViewerWidth()-GetGUIElementWidth(windowHandle)-elem2_d.p.size.w)
      [*] = ;//else
      [*] = ;   pos.pos.x := (GetViewerWidth()-GetGUIElementWidth(windowHandle)) div 2;
      [*] = ;
      [*] = ;if whd = 0 then
      [*] = ;   h := ((GetViewerHeight()-GetGUIElementHeight(windowHandle)) div 2)
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementPositionX(whd,(pos.pos.x+(GetGUIElementWidth(windowHandle) div 2))-(GetGUIElementWidth(whd) div 2));
      [*] = ;   h := GetGUIElementPositionY(whd)+GetGUIElementHeight(whd) - elem_d.p.size.h;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _log_Values('H|HDR_Y|HDR_DY|DY|WDY',h,GetGUIElementPositionY(whd),GetGUIElementHeight(whd),elem_d.p.size.h,GetGUIElementHeight(windowHandle),0);
      [*] = ;
      [*] = ;SetGUIElementPosition(windowHandle,pos.pos.x,h);
      [*] = ;
      [*] = ;_gui_RootWindowAdd(windowHandle,root_mode);
      [*] = ;if whd <> 0 then
      [*] = ;   _gui_RootWindowAddExt(whd,root_mode,0,cRootWindowAttrModalNoBlack,'');
      [*] = ;
      [*] = ;SetGUIElementPressState(windowHandle, eventName);
      [*] = ;_gui_FadeWindow_VVK(windowHandle,gc_gui_FadeTime0_4,0);
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;if root_mode = cRootWindowModal then
      [*] = ;   temp_str := '1'
      [*] = ;else
      [*] = ;   temp_str := '';
      [*] = ;_cmd_RegisterWindowState(windowHandle,cmdName,temp_str);
      [*] = ;IntRegister0 := windowHandle;
   struct.end
section.end

