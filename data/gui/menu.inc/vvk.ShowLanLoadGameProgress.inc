section.begin
   Name = vvk.ShowLanLoadGameProgress
   Description : struct.begin
      [*] = ;StringRegister0 - header text
      [*] = ;StringRegister1 - list of player ids
      [*] = ;RET: IntRegister0 - window handle
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\VVK.SHOWLANLOADGAMEPROGRESS';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cWindowTemplateName = 'lan_load_game_progress';
      [*] = ;const cHeaderTexName = 'map.generic.window.header';
      [*] = ;const cBadgeHeaderTexName = 'element.strip.240';
      [*] = ;
      [*] = ;const cIcon = $1e;
      [*] = ;const cOKCancelButton = $1d;
      [*] = ;const cPlayerBadgeSpacers = $1c;
      [*] = ;const cHeader = $1b;
      [*] = ;const cWindowSpacers = $1a;
      [*] = ;
      [*] = ;const cPlayerIcon = $18;
      [*] = ;const cPlayerNameStrip = $17;
      [*] = ;const cPlayerCOA = $16;
      [*] = ;const cPlayerBadge = $8;
      [*] = ;
      [*] = ;const cHeaderTextOffs = $2;
      [*] = ;const cMinWindowWidth = $1;
      [*] = ;
      [*] = ;const cBtnOKTag = 101;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;const cBtnRefreshTag = 103;
      [*] = ;const cEventState = 'VVK.EventLanLoadGameProgress';
      [*] = ;
      [*] = ;var header : String = StringRegister0;
      [*] = ;var players: String = StringRegister1;
      [*] = ;var windowHandle : Integer;
      [*] = ;var if_handle : Integer = _gui_GetInterfaceWindowHandle(cWindowTemplateName);
      [*] = ;var window_d,badge_d,text_d,elem_d : TInterfaceElementData;
      [*] = ;var whd,bhd,wdx,i,dx,dy,x,y,total_no : Integer;
      [*] = ;var spacer,w_spacer : TElementSize;
      [*] = ;var icon_pos,name_pos,coa_pos : TelementPos;
      [*] = ;var info,tex : String;
      [*] = ;var txt_pos : TRectangle;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,window_d);
      [*] = ;_gui_GetInterfaceElement(if_handle,cPlayerBadge,badge_d);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cPlayerBadgeSpacers,elem_d);
      [*] = ;spacer.w := elem_d.p.size.w;
      [*] = ;spacer.h := elem_d.p.size.h;
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cWindowSpacers,elem_d);
      [*] = ;w_spacer.w := elem_d.p.size.w;
      [*] = ;w_spacer.h := elem_d.p.size.h;
      [*] = ;
      [*] = ;total_no := _sa_GetNum(players);
      [*] = ;
      [*] = ;dx := window_d.p.size.w div (badge_d.p.size.w+spacer.w);
      [*] = ;dy := (total_no+dx-1) div dx;
      [*] = ;
      [*] = ;if total_no < dx then
      [*] = ;begin
      [*] = ;   _gui_GetInterfaceElement(if_handle,cMinWindowWidth,elem_d);
      [*] = ;
      [*] = ;   i := elem_d.p.size.w div (badge_d.p.size.w+spacer.w);
      [*] = ;   if i > total_no then
      [*] = ;      w_spacer.w := w_spacer.w+((elem_d.p.size.w-((badge_d.p.size.w+spacer.w)*total_no-spacer.w)) div 2);
      [*] = ;
      [*] = ;   dx := total_no;
      [*] = ;end;
      [*] = ;if _log then _log_values('DX|SPACER_W|BDX',dx,w_spacer.w,badge_d.p.size.w,0,0,0);
      [*] = ;wdx := dx*(badge_d.p.size.w+spacer.w)-spacer.w+w_spacer.w*2;
      [*] = ;
      [*] = ;_lan_timer_Reset(gc_lt_server_answer,false,'MENU.INC\VVK.SHOWLANLOADGAMEPROGRESS');
      [*] = ;
      [*] = ;windowHandle := _gui_GetWindow(cLanLoadGameSyncName);
      [*] = ;if windowHandle <> 0 then
      [*] = ;   RemoveGUIChildren(windowHandle);
      [*] = ;
      [*] = ;_sys_FillRect(txt_pos,0,0,wdx,dy*(badge_d.p.size.h+spacer.h)-spacer.h+w_spacer.h*2);
      [*] = ;windowHandle := _gui_CreateScalableWindow_VVK(cLanLoadGameSyncName,_gui_GetLayerI(),gc_gui_align_parent_m,txt_pos,'common_window');
      [*] = ;SetGUIElementStringTag(windowHandle,IntToStr(total_no));
      [*] = ;
      [*] = ;if header <> '' then
      [*] = ;begin
      [*] = ;   _gui_GetInterfaceElement(if_handle,cHeader,elem_d);
      [*] = ;   _gui_GetInterfaceElement(if_handle,cHeaderTextOffs,text_d);
      [*] = ;
      [*] = ;   _sys_FillRect(txt_pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;   whd := _gui_CreateImage_VVK('header',windowHandle,cHeaderTexName,elem_d.align,txt_pos);
      [*] = ;   _sys_FillRect(txt_pos,0,text_d.p_raw.pos.y-elem_d.p_raw.pos.y,0,0);
      [*] = ;   _gui_CreateText_VVK('',whd,header,gc_gui_align_parent_mt,txt_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;end;
      [*] = ;
      [*] = ;x := 0;
      [*] = ;y := 0;
      [*] = ;if _log then _log_gui('LanLoadProgress players: '+players);
      [*] = ;for i := 0 to total_no-1 do
      [*] = ;begin
      [*] = ;   _sys_FillRect(txt_pos,w_spacer.w+(spacer.w+badge_d.p.size.w)*x,w_spacer.h+(spacer.h+badge_d.p.size.h)*y,badge_d.p.size.w,badge_d.p.size.h);
      [*] = ;   whd := _gui_CreateImage_VVK('badge_'+IntToStr(i),windowHandle,gc_gui_material_blank_0,gc_gui_align_parent_lt,txt_pos);
      [*] = ;   SetGUIElementTag(whd,_sa_GetAsInt(players,i));
      [*] = ;
      [*] = ;   x := x + 1;
      [*] = ;   if x >= dx then
      [*] = ;   begin
      [*] = ;      x := 0;
      [*] = ;      y := y + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;tex := 'mainpanel.btnplace.with.frame';
      [*] = ;_gui_GetInterfaceElement(if_handle,cOKCancelButton,elem_d);
      [*] = ;if GetLanMode() > 1 then
      [*] = ;begin
      [*] = ;   _sys_FillRect(txt_pos,0,-1*(window_d.p.size.h-elem_d.p_raw.pos.y),wdx shr 1,GetGUITextureHeight(tex));
      [*] = ;   bhd := _gui_CreateImage_VVK('accept_placeholder',windowHandle,gc_gui_material_blank_0,gc_gui_align_parent_lb,txt_pos);
      [*] = ;   _sys_FillRect(txt_pos,0,0,0,0);
      [*] = ;   whd := _gui_CreateImage_VVK('frame',bhd,tex,gc_gui_align_parent_m,txt_pos);
      [*] = ;   whd := _gui_CreateButton_VVK('button',whd,'','map.radialhero.btn.move.accept',gc_gui_align_parent_m,txt_pos,cEventState,'map.event|28.1',cBtnOKTag);
      [*] = ;   SetGUIElementEnabled(whd,false);
      [*] = ;   _sys_FillRect(txt_pos,wdx div 2,-1*(window_d.p.size.h-elem_d.p_raw.pos.y),wdx shr 1,GetGUITextureHeight(tex));
      [*] = ;end
      [*] = ;else
      [*] = ;   _sys_FillRect(txt_pos,0,-1*(window_d.p.size.h-elem_d.p_raw.pos.y),wdx,GetGUITextureHeight(tex));
      [*] = ;
      [*] = ;bhd := _gui_CreateImage_VVK('cancel_placeholder',windowHandle,gc_gui_material_blank_0,gc_gui_align_parent_lb,txt_pos);
      [*] = ;_sys_FillRect(txt_pos,0,0,0,0);
      [*] = ;whd := _gui_CreateImage_VVK('frame',bhd,tex,gc_gui_align_parent_m,txt_pos);
      [*] = ;whd := _gui_CreateButton_VVK('button',whd,'','map.radialhero.btn.move.cancel',gc_gui_align_parent_m,txt_pos,cEventState,'menu|47',cBtnCancelTag);
      [*] = ;
      [*] = ;SetGUIElementPressState(windowHandle,cEventState);
      [*] = ;_gui_RootWindowAddM(windowHandle);
      [*] = ;
      [*] = ;SetValueByName('Press','c');
      [*] = ;SetIntValueByName('Tag',cBtnRefreshTag);
      [*] = ;SetIntValueByName('ElementHandle',windowHandle);
      [*] = ;SetIntValueByName('DisconnectedClientID',0);
      [*] = ;GUIExecuteState('VVK.EventLanLoadGameProgress');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister0 := windowHandle;
   struct.end
section.end

