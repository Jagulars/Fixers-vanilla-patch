section.begin
   Name = VVK.BannerWindowShow
   UsedFileName =
   Description : struct.begin
      [*] = ;Returns:
      [*] = ;   IntRegister0 - resulting window handle
   struct.end
   Code : struct.begin
      [*] = ;const MAX_BANNERS = $10;
      [*] = ;const BANNERS_FOLDER = '.\data\resources\banners\';
      [*] = ;const FALLBACK_BANNERS_FOLDER = '.\banners\';
      [*] = ;const BANNERS_FILE = 'ingame_banners.cfg';
      [*] = ;const URL_FILE = 'ingame_banners_url.cfg';
      [*] = ;
      [*] = ;const cGoButton = $1e;
      [*] = ;const cNextButton = $1d;
      [*] = ;const cPrevButton = $1c;
      [*] = ;const cTopOffset = $1b;
      [*] = ;
      [*] = ;type BannerData = class
      [*] = ;   full_nm : String;
      [*] = ;   delay : Integer;
      [*] = ;   action_type : Integer;
      [*] = ;   action_idx : Integer;
      [*] = ;   w : Integer;
      [*] = ;   h : Integer;
      [*] = ;   action : String;
      [*] = ;end;
      [*] = ;
      [*] = ;var _log_name : String = 'MENU.INC\VVK.BANNERWINDOWSHOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure GetProfilesRootPath(var dst_path : String);
      [*] = ;begin
      [*] = ;   var temp_str : String;
      [*] = ;
      [*] = ;   _misc_GetGameDataRootPath(temp_str);
      [*] = ;   dst_path := temp_str+'banners\';
      [*] = ;end;
      [*] = ;
      [*] = ;var banners : array [0..MAX_BANNERS] of BannerData;
      [*] = ;var sizes : array [0..$10] of Integer;
      [*] = ;var sizes_w : array [0..$10] of Integer;
      [*] = ;var sizes_h : array [0..$10] of Integer;
      [*] = ;var banners_no,i,j,windowHandle,whd,pData,pElems,pBanner,sizes_no,banner_idx,if_handle : Integer;
      [*] = ;var temp_str : String;
      [*] = ;var pos : TRectangle;
      [*] = ;var elem_d : TInterfaceElementData;
      [*] = ;var banners_path : String;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;windowHandle := _gui_GetWindow(cBaseAdsWindowName);
      [*] = ;var bExists : Boolean = windowHandle <> 0;
      [*] = ;if windowHandle <> 0 then
      [*] = ;   _gui_RootWindowRemoveWithFade(windowHandle,0);
      [*] = ;
      [*] = ;
      [*] = ;//windowHandle := 0;
      [*] = ;banners_path := BANNERS_FOLDER;
      [*] = ;if not IsFileExists(banners_path+BANNERS_FILE) then
      [*] = ;   banners_path := FALLBACK_BANNERS_FOLDER;
      [*] = ;if _log then _log_gui('Steam: '+BoolToStr(IsSteamAPPLoaded()));
      [*] = ;var bFileExists : Boolean = IsFileExists(banners_path+BANNERS_FILE);
      [*] = ;if _log then _log_gui('File path: '+banners_path+BANNERS_FILE+' exists: '+BoolToStr(bFileExists));
      [*] = ;if (not bFileExists) or (not IsSteamAPPLoaded()) then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   IntRegister0 := 0;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;pData  := _misc_ParserGetOrCreateByKey('banners_cfg',true);
      [*] = ;ParserLoadFromFile(banners_path+BANNERS_FILE);
      [*] = ;
      [*] = ;sizes[0] := $20000;
      [*] = ;sizes_w[0] := 900;
      [*] = ;sizes_h[0] := 300;
      [*] = ;sizes_no := 0;
      [*] = ;pElems := ParserSelectByHandleByKey(pData, 'BannerSizes');
      [*] = ;for i := 0 to (ParserGetCountByHandle(pElems) div 3)-1 do
      [*] = ;begin
      [*] = ;   sizes[sizes_no] := ParserGetIntValueByIndexByHandle(pElems,i*3);
      [*] = ;   sizes_w[sizes_no] := ParserGetIntValueByIndexByHandle(pElems,i*3+1);
      [*] = ;   sizes_h[sizes_no] := ParserGetIntValueByIndexByHandle(pElems,i*3+2);
      [*] = ;   sizes_no := sizes_no + 1;
      [*] = ;   if sizes[sizes_no-1] >= GetViewerWidth() then
      [*] = ;     break;
      [*] = ;end;
      [*] = ;sizes[sizes_no] := $20000;
      [*] = ;sizes_w[sizes_no] := 900;
      [*] = ;sizes_h[sizes_no] := 300;
      [*] = ;
      [*] = ;for i := 0 to (sizes_no)-1 do
      [*] = ;begin
      [*] = ;   if GetViewerWidth() <= sizes[i] then
      [*] = ;      break;
      [*] = ;end;
      [*] = ;banner_idx := i;
      [*] = ;
      [*] = ;if _log then _log_values('BIDX|DX|DY|SDX|NO|SZNO',banner_idx,sizes_w[banner_idx],sizes_h[banner_idx],GetViewerWidth(),ParserGetCountByHandle(pElems),sizes_no);
      [*] = ;banners_no := 0;
      [*] = ;pElems := ParserSelectByHandleByKey(pData, 'Banners');
      [*] = ;for i := 0 to (ParserGetCountByHandle(pElems))-1 do
      [*] = ;begin
      [*] = ;   pBanner := ParserSelectByHandleByIndex(pElems, i);
      [*] = ;   temp_str := ParserGetValueByKeyByHandle(pBanner,'FileName');
      [*] = ;   for j := banner_idx downto 0 do
      [*] = ;   begin
      [*] = ;      banners[banners_no].full_nm := banners_path+temp_str+'_'+IntToStr(j)+'.bmp';
      [*] = ;      if IsFileExists(banners[banners_no].full_nm) then
      [*] = ;         break;
      [*] = ;   end;
      [*] = ;   if IsFileExists(banners[banners_no].full_nm) then
      [*] = ;   begin
      [*] = ;      banners[banners_no].w := sizes_w[banner_idx];
      [*] = ;      banners[banners_no].h := sizes_h[banner_idx];
      [*] = ;      banners[banners_no].delay := ParserGetIntValueByKeyByHandle(pBanner,'Delay');
      [*] = ;      case StrToLowerCase(ParserGetValueByKeyByHandle(pBanner,'ActionType')) of
      [*] = ;         'url2' : banners[banners_no].action_type := 1;
      [*] = ;         else banners[banners_no].action_type := 0;
      [*] = ;      end;
      [*] = ;      banners[banners_no].action := ParserGetValueByKeyByHandle(pBanner,'ActionData');
      [*] = ;      _misc_StripQuotationMarks(banners[banners_no].action); // for some reason, they used quotation marks here.
      [*] = ;      banners[banners_no].action_idx := i;
      [*] = ;      banners_no := banners_no + 1;
      [*] = ;      if banners_no >= MAX_BANNERS then break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;_misc_ParserGetOrCreateByKey('banners_cfg',true);
      [*] = ;
      [*] = ;if banners_no = 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := 0;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var prof_path : String;
      [*] = ;GetProfilesRootPath(prof_path);
      [*] = ;var sActionData : String = '';
      [*] = ;for i := 0 to (banners_no)-1 do
      [*] = ;begin
      [*] = ;   if banners[i].action_type = 0 then
      [*] = ;   begin
      [*] = ;      if sActionData <> '' then
      [*] = ;      sActionData := sActionData + gc_gui_BreakLine;
      [*] = ;      sActionData := sActionData + banners[i].action;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;_misc_WriteStringToFile(prof_path+URL_FILE, sActionData);
      [*] = ;
      [*] = ;if_handle := _gui_GetInterfaceWindowHandle('banners_window');
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cTopOffset,elem_d);
      [*] = ;_sys_FillRect(pos,0,elem_d.p.size.h,1,1);
      [*] = ;windowHandle := _gui_CreateImage_VVK(cBaseAdsWindowName,_gui_GetLayerI(),gc_gui_material_blank_0,gc_gui_align_parent_lt,pos);
      [*] = ;//whd := _gui_GetWindow('main_menu');
      [*] = ;//if whd <> 0 then
      [*] = ;//   whd := GetViewerWidth()-GetGUIElementWidth(whd)
      [*] = ;//else
      [*] = ;   whd := GetViewerWidth() div 4;
      [*] = ;i := GetViewerHeight();
      [*] = ;//if ((banners[0].h+elem_d.p.size.h) > GetViewerHeight()) then
      [*] = ;   i := (GetViewerHeight() - banners[0].h) div 2;
      [*] = ;//else
      [*] = ;//   i := elem_d.p.size.h;
      [*] = ;SetGUIElementAllPositionRect(windowHandle,0,i,whd,GetViewerHeight());
      [*] = ;if _log then _log_values('Y|DX',elem_d.p.size.h,whd,0,0,0,0);
      [*] = ;
      [*] = ;_sys_FillRect(pos,0,0,banners[0].w,banners[0].h);
      [*] = ;_gui_CreateButton_VVK('banner_goto',windowHandle,'',gc_gui_material_blank_0,gc_gui_align_parent_lt,pos,'VVK.BannerWindowEvent','',$1010);
      [*] = ;_sys_FillRect(pos,0,0,0,0);
      [*] = ;for i := 0 to (banners_no)-1 do
      [*] = ;begin
      [*] = ;   temp_str := 'banner_'+IntToStr(i);
      [*] = ;   LoadImageToMaterial(banners[i].full_nm,temp_str);
      [*] = ;   _sys_FillRect(pos,0,0,banners[i].w,banners[i].h);
      [*] = ;   whd := _gui_CreateImage_VVK(temp_str,windowHandle,temp_str,gc_gui_align_parent_lt,pos);
      [*] = ;   SetGUIElementTag(whd,$1000);
      [*] = ;   temp_str := '';
      [*] = ;   _sa_AddAsInt(temp_str,banners[i].delay);
      [*] = ;   _sa_AddAsInt(temp_str,banners[i].action_idx);
      [*] = ;   _sa_AddAsInt(temp_str,banners[i].action_type);
      [*] = ;   _sa_Add(temp_str,banners[i].action);
      [*] = ;   SetGUIElementStringTag(whd,temp_str);
      [*] = ;   SetGUIElementVisible(whd,false);
      [*] = ;end;
      [*] = ;
      [*] = ;_sys_FillRect(pos,0,0,0,0);
      [*] = ;if banners_no > 1 then
      [*] = ;begin
      [*] = ;   whd := _gui_CreateButton_VVK('button_prev',windowHandle,'','common.scroller.left',gc_gui_align_parent_lt,pos,'VVK.BannerWindowEvent','',$1001);
      [*] = ;   SetGUIElementStringTag(whd,IntToStr(_gui_ie_GetOffsetX(if_handle,-1,cPrevButton,false)));
      [*] = ;   whd := _gui_CreateButton_VVK('button_next',windowHandle,'','common.scroller.right',gc_gui_align_parent_lt,pos,'VVK.BannerWindowEvent','',$1002);
      [*] = ;   _gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,elem_d);
      [*] = ;   SetGUIElementStringTag(whd,IntToStr(_gui_ie_GetOffsetX(if_handle,-1,cNextButton,true)));
      [*] = ;end;
      [*] = ;_gui_GetInterfaceElement(if_handle,cGoButton,elem_d);
      [*] = ;whd := _gui_CreateTextButton_VVK('button_goto',windowHandle,'','castle.hero.recruit.window.btn.recruit',gc_gui_align_parent_lt,elem_d.p,'VVK.BannerWindowEvent','',$1000,'menu|banner_go',gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;SetGUIElementStringTag(whd,IntToStr(_gui_ie_GetOffsetY(if_handle,-1,cGoButton,true)));
      [*] = ;
      [*] = ;SetGUIElementTag(windowHandle,banners_no);
      [*] = ;temp_str := '';
      [*] = ;_sa_AddAsInt(temp_str,-1);
      [*] = ;_sa_AddAsFloat(temp_str,GetGameTime()+3);
      [*] = ;SetGUIElementStringTag(windowHandle,temp_str);
      [*] = ;_gui_RootWindowAddA(windowHandle);
      [*] = ;_cmd_RegisterWindowState(windowHandle,'VVK.BannerWindowCommands','');
      [*] = ;var fadeTime : Float;
      [*] = ;if not bExists then
      [*] = ;   fadeTime := 2.0
      [*] = ;else
      [*] = ;   fadeTime := gc_gui_FadeTime0_4;
      [*] = ;_gui_FadeWindow_VVK(windowHandle,fadeTime,0);
      [*] = ;_cmd_Post('.menushowbanner','',IntToStr($ffff));
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;IntRegister0 := windowHandle;
   struct.end
section.end

