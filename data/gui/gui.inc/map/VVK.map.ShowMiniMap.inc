section.begin
   Name = VVK.map.ShowMiniMap
   Description : struct.begin
      [*] = ;Displays minimap window using predefined material
      [*] = ;IntRegister0 - window mode
      [*] = ;   0  - full size window
      [*] = ;   1  - minimized window
      [*] = ;   -1 - remove window
      [*] = ;RET:
      [*] = ;   IntRegister0 - window handle
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\VVK.MAP.SHOWMINIMAP';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cMapHeader = $1c;
      [*] = ;const cMapElement = $1b;
      [*] = ;const cMapRTOffset = $1a;
      [*] = ;const cMapHeaderText = $1;
      [*] = ;const cButtonXOffset = 70;
      [*] = ;
      [*] = ;const cEventState = 'VVK.map.EventShowMiniMap';
      [*] = ;
      [*] = ;function DisplayMapButton(windowHandle,x,y,tag : Integer;button_name,hint,wnd_name : String) : Integer;
      [*] = ;begin
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;   var t2 : String = button_name+'.normal';
      [*] = ;
      [*] = ;   if GetGUITextureWidth('map.hideminimap.background') <> 0 then
      [*] = ;   begin
      [*] = ;      var t1 : String = 'map.hideminimap.background';
      [*] = ;
      [*] = ;      _sys_FillRect(tmp_pos,x-(GetGUITextureWidth(t2)+((GetGUITextureWidth(t1)-GetGUITextureWidth(t2)) div 2)),y-((GetGUITextureHeight(t1)-GetGUITextureHeight(t2)) div 2),0,0);
      [*] = ;      Result := _gui_CreateImage_VVK(wnd_name,windowHandle,t1,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;      _sys_FillRect(tmp_pos,0,0,0,0);
      [*] = ;      _gui_CreateButton_VVK('minmax',Result,'',button_name,gc_gui_align_parent_m,tmp_pos,cEventState,hint,tag);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      _sys_FillRect(tmp_pos,x-GetGUITextureWidth(t2),y,0,0);
      [*] = ;      Result := _gui_CreateButton_VVK(wnd_name,windowHandle,'',button_name,gc_gui_align_parent_lt,tmp_pos,cEventState,hint,tag);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetMiniMapPosByIndex(p,idx : Integer;var _x : Integer;var _y : Integer);
      [*] = ;begin
      [*] = ;   IntRegister0 := 0;
      [*] = ;   IntRegister1 := p;
      [*] = ;   IntRegister2 := idx;
      [*] = ;   MapExecuteState('map.vvk.MiniMapHelper');
      [*] = ;   _x := IntRegister0;
      [*] = ;   _y := IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;var if_handle : Integer;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var windowHandle : Integer;
      [*] = ;var window_d,elem_d,elem1_d : TInterfaceElementData;
      [*] = ;var i,mm_dy,mm_dx,minimap_p,whd,idx,no,dx,dy,wnd_dx : Integer;
      [*] = ;var scale_f : Float;
      [*] = ;var tmp_pos : TRectangle;
      [*] = ;
      [*] = ;windowHandle := _gui_GetWindow(cMapMiniMapWindowName);
      [*] = ;if windowHandle <> 0 then
      [*] = ;begin
      [*] = ;   _gui_RootWindowRemoveWithFade(windowHandle,0);
      [*] = ;   if mode = -1 then
      [*] = ;      exit;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;windowHandle := 0;
      [*] = ;if_handle := _gui_GetInterfaceWindowHandle(cMapMiniMapWindowName);
      [*] = ;
      [*] = ;if (mode = 1) then
      [*] = ;begin
      [*] = ;   _gui_GetInterfaceElement(if_handle,cMapRTOffset,elem_d);
      [*] = ;   windowHandle := DisplayMapButton(_gui_GetLayerI(),cButtonXOffset{GetViewerWidth()-elem_d.p.size.w},elem_d.p.size.h,$100,'map.showminimap','gui|minimapmin.hint',cMapMiniMapWindowName);
      [*] = ;   SetGUIElementStringTag(windowHandle,'min');
      [*] = ;   SetGUIElementUserBlend(windowHandle, 0.8);
      [*] = ;   _gui_RootWindowAddExt(windowHandle,cRootWindowCP,0,0,'');
      [*] = ;   _gui_FadeWindow_VVK(windowHandle,0,0);
      [*] = ;   _gv_traceState(_log_name+'[Minimized '+IntToStr(tmp_pos.pos.x)+','+IntToStr(tmp_pos.pos.y)+']',$1000000 or _log_trace);
      [*] = ;   IntRegister0 := windowHandle;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;minimap_p := _misc_ParserGetOrCreateByKey('MiniMapDimensionsParser', False);
      [*] = ;if ParserGetIntValueByKeyByHandle(minimap_p,'DX') = 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := 0;
      [*] = ;   MapExecuteState('map.vvk.GenerateMiniMap');
      [*] = ;   minimap_p := _misc_ParserGetOrCreateByKey('MiniMapDimensionsParser', False);
      [*] = ;end;
      [*] = ;mm_dx := ParserGetIntValueByKeyByHandle(minimap_p,'DX');
      [*] = ;mm_dy := ParserGetIntValueByKeyByHandle(minimap_p,'DY');
      [*] = ;if (mm_dy > (GetViewerHeight() div 2)) then
      [*] = ;   scale_f := (GetViewerHeight() div 2) / mm_dy
      [*] = ;else
      [*] = ;   scale_f := 1.0;
      [*] = ;if _log then _Log_gui('SCALE: '+FloatToStr(scale_f));
      [*] = ;_gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,window_d);
      [*] = ;_gui_GetInterfaceElement(if_handle,cMapElement,elem_d);
      [*] = ;_gui_GetInterfaceElement(if_handle,cMapRTOffset,elem1_d);
      [*] = ;_sys_FillRect(tmp_pos,0,elem1_d.p.size.h,window_d.p.size.w-elem_d.p.size.w+floor(mm_dx*scale_f),window_d.p.size.h-elem_d.p.size.h+floor(mm_dy*scale_f));
      [*] = ;tmp_pos.pos.x := cButtonXOffset;//GetViewerWidth()-(tmp_pos.size.w+elem1_d.p.size.w);
      [*] = ;windowHandle := _gui_CreateScalableWindow_VVK(cMapMiniMapWindowName,_gui_GetLayerI(),gc_gui_align_parent_lt,tmp_pos,'common_window');
      [*] = ;wnd_dx := tmp_pos.size.w;
      [*] = ;//_gui_SetScaleableWindowBkgBlend(windowHandle,0.9);
      [*] = ;SetGUIAllowEvents(windowHandle, True, False, False);
      [*] = ;SetGUIElementStringTag(windowHandle,'max|'+IntToStr(mm_dx)+'|'+IntToStr(mm_dy)+'|'+FloatToStr(scale_f));
      [*] = ;_sys_FillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,floor(mm_dx*scale_f),floor(mm_dy*scale_f));
      [*] = ;whd := _gui_CreateButton_VVK('minimap',windowHandle,'','misc.minimap',gc_gui_align_parent_lt,tmp_pos,cEventState, '', $102);
      [*] = ;// castles
      [*] = ;dx := GetGUITextureWidth('minimap.castleicon');
      [*] = ;dy := GetGUITextureHeight('minimap.castleicon');
      [*] = ;if scale_f <> 1.0 then
      [*] = ;begin
      [*] = ;   dx := floor(dx*scale_f);
      [*] = ;   dy := floor(dy*scale_f);
      [*] = ;end;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   idx := ParserGetIntValueByKeyByHandle(minimap_p,'Castle'+IntToStr(i));
      [*] = ;   if idx <> -1 then
      [*] = ;   begin
      [*] = ;      GetMiniMapPosByIndex(minimap_p,idx,mm_dx,mm_dy);
      [*] = ;      _sys_FillRect(tmp_pos,floor(mm_dx*scale_f)-dx,floor(mm_dy*scale_f)-(dy div 2),dx,dy);
      [*] = ;      _gui_CreateImage_VVK('',whd,'minimap.castleicon',gc_gui_align_parent_lt,tmp_pos);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;// heroes
      [*] = ;dx := GetGUITextureWidth('minimap.heroicon');
      [*] = ;dy := GetGUITextureHeight('minimap.heroicon');
      [*] = ;if scale_f <> 1.0 then
      [*] = ;begin
      [*] = ;   dx := floor(dx*scale_f);
      [*] = ;   dy := floor(dy*scale_f);
      [*] = ;end;
      [*] = ;no := ParserGetIntValueByKeyByHandle(minimap_p,'HeroesTotal');
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   idx := ParserGetIntValueByKeyByHandle(minimap_p,'Hero'+IntToStr(i));
      [*] = ;   if idx <> -1 then
      [*] = ;   begin
      [*] = ;      GetMiniMapPosByIndex(minimap_p,idx,mm_dx,mm_dy);
      [*] = ;      _sys_FillRect(tmp_pos,floor(mm_dx*scale_f),floor(mm_dy*scale_f)-(dy div 2),dx,dy);
      [*] = ;      _gui_CreateImage_VVK('',whd,'minimap.heroicon',gc_gui_align_parent_lt,tmp_pos);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;// pointer
      [*] = ;dx := GetGUITextureWidth('minimap.pointerpos');
      [*] = ;dy := GetGUITextureHeight('minimap.pointerpos');
      [*] = ;if scale_f <> 1.0 then
      [*] = ;begin
      [*] = ;   dx := floor(dx*scale_f);
      [*] = ;   dy := floor(dy*scale_f);
      [*] = ;end;
      [*] = ;_sys_FillRect(tmp_pos,-2000,-2000,dx,dy);
      [*] = ;_gui_CreateImage_VVK('pointer',whd,'minimap.pointerpos',gc_gui_align_parent_lt,tmp_pos);
      [*] = ;
      [*] = ;if _gui_GetInterfaceElement(if_handle,cMapHeader,elem_d) then
      [*] = ;begin
      [*] = ;   _gui_CreateImage_VVK('',windowHandle,'element.header.strip.620',elem_d.align,elem_d.p);
      [*] = ;   _gui_GetInterfaceElement(if_handle,cMapHeaderText,elem_d);
      [*] = ;   _gui_CreateButton_VVK('',windowHandle,'',gc_gui_material_blank_0,elem_d.align,elem_d.p,cEventState,'gui|minimapheader.hint',$101);
      [*] = ;   _gui_CreateText_VVK('',windowHandle,'gui|minimapheader',elem_d.align,elem_d.p,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;end
      [*] = ;else
      [*] = ;   DisplayMapButton(windowHandle,0,0,$101,'map.hideminimap','gui|minimapheader.hint','');
      [*] = ;
      [*] = ;_gui_RootWindowAddExt(windowHandle,cRootWindowCP,0,0,'');
      [*] = ;_gui_FadeWindow_VVK(windowHandle,0,0);
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;IntRegister0 := windowHandle;
   struct.end
section.end

