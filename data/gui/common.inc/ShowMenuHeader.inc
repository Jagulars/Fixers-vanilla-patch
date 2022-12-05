section.begin
   Name = ShowMenuHeader
   Description : struct.begin
      [*] = ;IntRegister0 - mode (0 - show nothing, 1-show dragon only, 2 - show gamelogo and dragon)
      [*] = ;RETURNS:
      [*] = ;   IntRegister0 - window header
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;const cTemplateName = 'list_menu';
      [*] = ;const cDragon = $1e;
      [*] = ;const cGameHeader = $1a;
      [*] = ;const cHeaderWindowOffset = $19;
      [*] = ;
      [*] = ;const cGameLogo = 'logo';
      [*] = ;
      [*] = ;var windowHandle,y : Integer;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var if_handle : Integer;
      [*] = ;var elem_d,elem2_d : TInterfaceElementData;
      [*] = ;var pos : TRectangle;
      [*] = ;var temp_str : String;
      [*] = ;
      [*] = ;windowHandle := _gui_GetWindow(cListMenuHeaderWindowName);
      [*] = ;var bExists : Boolean = windowHandle <> 0;
      [*] = ;//if windowHandle <> 0 then
      [*] = ;//   _gui_RootWindowRemoveWithFade(windowHandle,0);
      [*] = ;
      [*] = ;if_handle := _gui_GetInterfaceWindowHandle(cTemplateName);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cGameHeader,elem_d);
      [*] = ;var viewerHeight : Integer = GetViewerHeight();
      [*] = ;y := viewerHeight div 3;
      [*] = ;
      [*] = ;if (mode <> 0) then
      [*] = ;begin
      [*] = ;   if (not bExists) then
      [*] = ;   begin
      [*] = ;      _sys_FillRect(pos,0,0,GetViewerWidth,viewerHeight);
      [*] = ;      windowHandle := _gui_CreateImage_VVK(cListMenuHeaderWindowName,_gui_GetLayerI(),gc_gui_material_blank_0,gc_gui_align_parent_lt,pos);
      [*] = ;      SetGUIAllowEvents(windowHandle, False, False, False);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;   windowHandle := 0;
      [*] = ;
      [*] = ;case mode of
      [*] = ;   2 : begin
      [*] = ;      SetGUIElementAllPositionRect(windowHandle,0,y-elem_d.p.size.h,GetViewerWidth,elem_d.p.size.h);
      [*] = ;      temp_str := cGameLogo+'.'+GetLocaleTableListItemByID('menu','lang_id');
      [*] = ;      if GetGUITextureWidth(temp_str) = 0 then
      [*] = ;         temp_str := cGameLogo+'.en';
      [*] = ;      
      [*] = ;      _sys_FillRect(pos,0,0,0,0);
      [*] = ;      var logo : Integer = GetGUIElementIndexByNameParent('logo', windowHandle);
      [*] = ;      if (logo = 0) then
      [*] = ;         logo := _gui_CreateImage_VVK('logo',windowHandle,temp_str,gc_gui_align_parent_mt,pos);
      [*] = ;      
      [*] = ;      temp_str := 'common.window.header.dragon';
      [*] = ;      _gui_GetInterfaceElement(if_handle,cDragon,elem2_d);
      [*] = ;      var endY : Integer = elem2_d.p_raw.pos.y-elem_d.p_raw.pos.y;
      [*] = ;      
      [*] = ;      _sys_FillRect(pos,0,endY,0,0);
      [*] = ;      var dragon : Integer = GetGUIElementIndexByNameParent('dragon', windowHandle);
      [*] = ;      if (dragon = 0) then
      [*] = ;         dragon := _gui_CreateImage_VVK('dragon',windowHandle,temp_str,gc_gui_align_parent_mt,pos);
      [*] = ;      
      [*] = ;      SetGUIElementAllPositionRect(windowHandle,0,y-elem_d.p.size.h,GetViewerWidth,pos.pos.y+GetGUITextureHeight(temp_str));
      [*] = ;      //temp_str := 'misc.snapshot';
      [*] = ;      //if LoadImageToMaterial('.\data\archer.bmp', temp_str) then
      [*] = ;      //begin
      [*] = ;      //   _log_gui('Material from texture created.');
      [*] = ;      //   _sys_FillRect(pos,((-1*GetViewerWidth()+GetGUITextureWidth(temp_str)) div 2),0,0,0);
      [*] = ;      //   _gui_CreateImage_VVK('',windowHandle,temp_str,gc_gui_align_parent_lt,pos);
      [*] = ;      //end
      [*] = ;      //else
      [*] = ;      //  _log_gui('Material from texture creation failed.');
      [*] = ;      
      [*] = ;      // entrance animation
      [*] = ;      var startTime : Float = GetGameTime;
      [*] = ;      if (not bExists) and (gGame.gameType = gc_GameTypeNone) and (startTime < 3) then
      [*] = ;      begin
      [*] = ;         var startY : Integer = 200;
      [*] = ;         var transitionTime : Float = 1.5;
      [*] = ;         SetGUIElementPositionY(logo, startY);
      [*] = ;         var startScale : Float = 1.5;
      [*] = ;         SetGUIElementScale(logo, startScale, startScale);
      [*] = ;         SetGUIElementStringTag(logo, IntToStr(startY)+'|'+'0'+'|'+FloatToStr(startTime)+'|'+FloatToStr(transitionTime));
      [*] = ;      
      [*] = ;         transitionTime := 1.5;
      [*] = ;         startY := viewerHeight-y;
      [*] = ;         SetGUIElementPositionY(dragon, startY);
      [*] = ;         SetGUIElementStringTag(dragon, IntToStr(startY)+'|'+IntToStr(endY)+'|'+FloatToStr(startTime)+'|'+FloatToStr(transitionTime));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   1 : begin
      [*] = ;      temp_str := 'common.window.header.dragon';
      [*] = ;      SetGUIElementAllPositionRect(windowHandle,0,y-GetGUITextureHeight(temp_str),GetGUITextureWidth(temp_str),GetGUITextureHeight(temp_str));
      [*] = ;      _gui_GetInterfaceElement(if_handle,cDragon,elem2_d);
      [*] = ;      _sys_FillRect(pos,0,0,0,0);
      [*] = ;      if _log then _log_Values('HY|DY|Y',elem_d.p_raw.pos.y,elem2_d.p_raw.pos.y,pos.pos.y,0,0,0);
      [*] = ;      var dragon : Integer = _gui_CreateImage_VVK('dragon',windowHandle,temp_str,gc_gui_align_parent_mt,pos);
      [*] = ;      SetGUIElementStringTag(dragon, '');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not bExists) then
      [*] = ;   _gui_FadeWindow_VVK(windowHandle,gc_gui_FadeTime1_25,0);
      [*] = ;IntRegister0 := windowHandle;
      [*] = ;
      [*] = ;{const cWindowName = 'main_menu_header';
      [*] = ;const cVersionHeader = 1;
      [*] = ;const cVersionHeaderText = $13;
      [*] = ;const cGameName = $1e;
      [*] = ;const cDragon = $1d;
      [*] = ;
      [*] = ;var if_handle : Integer = _gui_GetInterfaceWindowHandle(cWindowName);
      [*] = ;var window_d : TInterfaceElementData;
      [*] = ;var elem_d : TInterfaceElementData;
      [*] = ;var elem_handle : Integer;
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,window_d);
      [*] = ;var top : Integer = _gui_GetLayerI();
      [*] = ;
      [*] = ;var windowHandle : Integer = GetGUIElementIndexByNameParent(cWindowName,top);
      [*] = ;var windowHandleTop : Integer;
      [*] = ;if windowHandle = 0 then
      [*] = ;begin
      [*] = ;   windowHandle := AddNewElementByClassNameParent(cWindowName, 'TOSWImageGuiControl', 0, top);
      [*] = ;   SetGUIElementMaterial(windowHandle, gc_gui_material_blank_0);
      [*] = ;   SetGUIAllowEvents(windowHandle, False, False, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   RemoveGUIChildren(windowHandle);
      [*] = ;end;
      [*] = ;SetGUIElementAlign(windowHandle, window_d.align.h, window_d.align.v);
      [*] = ;SetGUIElementAllPositionRect(windowHandle, 0, 0, window_d.p.size.w, window_d.p.size.h);
      [*] = ;
      [*] = ;// hack to override strange _gui_FadeElement behavior
      [*] = ;windowHandleTop := windowHandle;
      [*] = ;windowHandle := AddNewElementByClassNameParent(cWindowName+'_ghost', 'TOSWImageGuiControl', 0, windowHandle);
      [*] = ;SetGUIElementMaterial(windowHandle, gc_gui_material_blank_0);
      [*] = ;SetGUIAllowEvents(windowHandle, False, False, False);
      [*] = ;SetGUIElementAlign(windowHandle, 'halParentLeft', 'valParentTop');
      [*] = ;SetGUIElementAllPositionRect(windowHandle, 0, 0, window_d.p.size.w, window_d.p.size.h);
      [*] = ;
      [*] = ;if _gui_GetInterfaceElement(if_handle,cDragon,elem_d) then
      [*] = ;  _gui_CreateImage('dragon', windowHandle, 'common.window.header.dragon', elem_d.align.h, elem_d.align.v, elem_d.p.pos.x, elem_d.p.pos.y, 0, 0, 0);
      [*] = ;
      [*] = ;if _gui_GetInterfaceElement(if_handle,cGameName,elem_d) then
      [*] = ;begin
      [*] = ;   elem_handle := _gui_CreateImage('logo', windowHandle, 'logo.en', elem_d.align.h, elem_d.align.v, elem_d.p.pos.x, elem_d.p.pos.y, elem_d.p.size.w, 0, 0);
      [*] = ;   SetGUIElementUserBlend(elem_handle, 0.75);
      [*] = ;end;
      [*] = ;}
      [*] = ;{if _gui_GetInterfaceElement(if_handle,cVersionHeader,elem_d) then
      [*] = ;begin
      [*] = ;   elem_handle := _gui_CreateImage('logo_strip', windowHandle, 'element.strip.341', elem_d.align.h, elem_d.align.v, elem_d.p.pos.x, elem_d.p.pos.y, elem_d.p.size.w, 0, 0);
      [*] = ;   SetGUIElementUserBlend(elem_handle, 0.9);
      [*] = ;end;
      [*] = ;
      [*] = ;if _gui_GetInterfaceElement(if_handle,cVersionHeaderText,elem_d) then
      [*] = ;   _gui_CreateText_VVK('logo_text' , windowHandle, 'Technical Beta', elem_d.align, elem_d.p, gc_gui_align_middle, elem_d.font_handle, elem_d.color);}
      [*] = ;{
      [*] = ;_gui_FadeWindow_VVK(windowHandle,gc_gui_FadeTime0_4,0);
      [*] = ;
      [*] = ;IntRegister0 := windowHandleTop;}
   struct.end
section.end

