section.begin
   Name = vvk.map.DynamicWindowRitualCallback
   UsedFileName =
   Description : struct.begin
      [*] = ;For details please see VVK.DynamicWindowBuildingCallback
      [*] = ;Object ID string: ritual_id,res1,res2,parent object(hero) uid or (cFT_ItemHero)
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;var _test_display : Boolean = false;
      [*] = ;
      [*] = ;const cNameTextOffset = $1d;
      [*] = ;const cIconImage = $1c;
      [*] = ;//const cEffectsText = $1b;
      [*] = ;//const cEffectsHeaderOffset = $1a;
      [*] = ;
      [*] = ;const cFirstDisplayableField = $16;
      [*] = ;const cKarma = $16;                  // karma
      [*] = ;const cHelpIcon = $15;               // help icon
      [*] = ;const cTarget = $14;                 // target
      [*] = ;const cDC = $13;                     // duration,cooldown
      [*] = ;const cDescription = $12;
      [*] = ;const cFullPrice = $11;
      [*] = ;const cCurrentPrice = $10;
      [*] = ;const cRes1 = $f;
      [*] = ;const cRes2 = $e;
      [*] = ;const cIcon = $d;
      [*] = ;const cDCT = $c;                     // duration,cooldown,target
      [*] = ;const cName = $b;
      [*] = ;const cLastDisplayableField = $b;
      [*] = ;
      [*] = ;var e_x,e_dx,e_dy,e_y,total_dx,space_dx,space_dy,extra_dy_offset : Integer;
      [*] = ;var windowHandle,if_handle : Integer;
      [*] = ;// filled in serialize
      [*] = ;var total_x,total_y : Integer;
      [*] = ;var ctxt0,ctxt1 : String;
      [*] = ;// saved in s0 on init
      [*] = ;var ritual_id,hero_mode,hero_uid : Integer;
      [*] = ;// calculated in unserialize
      [*] = ;var hero_handle,pl_handle,p_ritual: Integer;
      [*] = ;//filled in processelement
      [*] = ;var elem_d,elem2_d : TInterfaceElementData;
      [*] = ;
      [*] = ;function GetRitualValue(v_name : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserGetIntValueByKeyByHandle(p_ritual,v_name);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetRitualValueB(v_name : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := ParserGetBoolValueByKeyByHandle(p_ritual,v_name);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetFullPrice(var res_str: String) : Boolean;
      [*] = ;begin
      [*] = ;   var c,n : Integer;
      [*] = ;   var s,temp_str : String;
      [*] = ;
      [*] = ;   s := '';
      [*] = ;   n := 0;
      [*] = ;   c := GetRitualValue('GoldCost');
      [*] = ;   if c <> 0 then
      [*] = ;   begin
      [*] = ;      _sa_AddAsInt(s,$10000);
      [*] = ;      _sa_AddAsInt(s,c);
      [*] = ;      n := n + 1;
      [*] = ;   end;
      [*] = ;   c := GetRitualValue('GemCost');
      [*] = ;   if c <> 0 then
      [*] = ;   begin
      [*] = ;      _sa_AddAsInt(s,$10001);
      [*] = ;      _sa_AddAsInt(s,c);
      [*] = ;      n := n + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   c := _gui_ft_GetResourcesCount(ParserSelectByHandleByKey(p_ritual, 'Resources'),temp_str);
      [*] = ;   if c > 0 then
      [*] = ;   begin
      [*] = ;      s := s + '|'+temp_str;
      [*] = ;      n := n + c;
      [*] = ;   end;
      [*] = ;   res_str := s;
      [*] = ;   if n = 0 then Result := false
      [*] = ;   else Result := true;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsDisplayableField(i : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var p : Integer;
      [*] = ;
      [*] = ;   if (i >= cLastDisplayableField) and (i <= cFirstDisplayableField) then
      [*] = ;   begin
      [*] = ;      Result := true;
      [*] = ;      if (i = cKarma) and (GetRitualValue('Karma') = 0) then
      [*] = ;         Result := false;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillStartupVariables(object_id : String);
      [*] = ;begin
      [*] = ;   ritual_id := _sa_GetAsInt(object_id,0);
      [*] = ;   //res1 := _sa_GetAsInt(object_id,1);
      [*] = ;   //res2 := _sa_GetAsInt(object_id,2);
      [*] = ;   hero_mode := _sa_GetAsInt(object_id,3);
      [*] = ;   if hero_mode > 0 then
      [*] = ;   begin
      [*] = ;      hero_uid := hero_mode;
      [*] = ;      hero_mode := cFT_ItemHeroDefault;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if hero_mode=cFT_ItemHeroGlobalUID1 then
      [*] = ;      begin
      [*] = ;         hero_uid := gIntRegister_GUIActiveHeroUID1;
      [*] = ;         hero_mode := cFT_ItemHeroDefault;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         hero_uid := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetupInitial(var s0 : String; var s1 : String);
      [*] = ;begin
      [*] = ;   hero_handle := GetGameObjectHandleByUniqueId(hero_uid);
      [*] = ;   pl_handle := GetGameObjectPlayerHandleByHandle(hero_handle);
      [*] = ;   if pl_handle = 0 then
      [*] = ;      pl_handle := GetPlayerHandleInterfaceIO();
      [*] = ;   p_ritual := ParserSelectByHandleByIndex(gPrototypeData.rituals.handle,ritual_id);
      [*] = ;
      [*] = ;   s0 := '';
      [*] = ;   _sa_AddAsInt(s0,hero_handle);
      [*] = ;   _sa_AddAsInt(s0,pl_handle);
      [*] = ;   _sa_AddAsInt(s0,p_ritual);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UnserializeData(s0 : String;v : String);
      [*] = ;begin
      [*] = ;   hero_handle := _sa_GetAsInt(s0,0);
      [*] = ;   pl_handle := _sa_GetAsInt(s0,1);
      [*] = ;   p_ritual := _sa_GetAsInt(s0,2);
      [*] = ;
      [*] = ;   e_x := 0;
      [*] = ;   e_dx := 0;
      [*] = ;   e_dy := 0;
      [*] = ;   e_y := 0;
      [*] = ;   total_dx := _sa_GetAsInt(v,2);
      [*] = ;   space_dx := _sa_GetAsInt(v,3);
      [*] = ;   space_dy := _sa_GetAsInt(v,4);
      [*] = ;   extra_dy_offset := _sa_GetAsInt(v,5);
      [*] = ;   total_x := _sa_GetAsInt(v,0);
      [*] = ;   total_y := _sa_GetAsInt(v,1);
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessTextString(text : String;do_draw : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var stackable : Boolean;
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;   var temp_str : String;
      [*] = ;   var w,h,ehd : Integer;
      [*] = ;
      [*] = ;   _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;   stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;   e_x := tmp_pos.pos.x;
      [*] = ;   //if do_draw then
      [*] = ;   //   temp_str := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,elem_d.p.size.w)
      [*] = ;   //else
      [*] = ;      temp_str := text;
      [*] = ;   GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;
      [*] = ;   e_dx := w; //Max(w,tmp_pos.size.w);
      [*] = ;   tmp_pos.size.w := e_dx;
      [*] = ;   if do_draw then
      [*] = ;   begin
      [*] = ;      tmp_pos.size.h := h;
      [*] = ;      ehd := _gui_DWCreateText(if_handle,'',windowHandle,temp_str,elem_d.align,tmp_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;      e_dy := h;
      [*] = ;      e_y := tmp_pos.pos.y;
      [*] = ;      Result := ehd;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ProcessElement(elem_id: Integer;do_draw : Boolean);
      [*] = ;begin
      [*] = ;   var i,j,k,ehd,p,pa,no,xhd,idx : Integer;
      [*] = ;   var stackable : Boolean;
      [*] = ;   var w,h : Integer;
      [*] = ;   var temp_str,hint_tag,icon_name,hint,temp_str2 : String;
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;
      [*] = ;   _gui_DWGetElement(elem_id,if_handle,elem_d);
      [*] = ;
      [*] = ;   case elem_id of
      [*] = ;      cName : begin
      [*] = ;         const cTexHeaderStripe = 'map.generic.window.header';
      [*] = ;
      [*] = ;         var text : String;
      [*] = ;
      [*] = ;         text := GetLocaleTableListItemByID('ritual', IntToStr(ritual_id));
      [*] = ;
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;         _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;
      [*] = ;         if _gui_GetInterfaceElement(if_handle,cNameTextOffset,elem2_d) then
      [*] = ;         begin
      [*] = ;            e_dx := GetGUITextureWidth(cTexHeaderStripe);
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle,text,w,h);
      [*] = ;            e_dx := max(w,e_dx);
      [*] = ;            if do_draw then
      [*] = ;            begin
      [*] = ;               tmp_pos.size.w := 0;
      [*] = ;               tmp_pos.size.h := 0;
      [*] = ;               ehd := _gui_CreateImage_VVK('name',windowHandle,cTexHeaderStripe,elem_d.align,tmp_pos);
      [*] = ;               e_dy := GetGUITextureHeight(cTexHeaderStripe);
      [*] = ;               _sys_FillRect(tmp_pos,0,elem2_d.p_raw.pos.y-elem_d.p_raw.pos.y,e_dx,0);
      [*] = ;               ehd := _gui_DWCreateText(if_handle,'',ehd,text,gc_gui_align_parent_mt,tmp_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            pa := ParserSelectByHandleByIndex(gPrototypeData.rituals.handle, ritual_id);
      [*] = ;            var rarity : Integer = ParserGetIntValueByKeyByHandle(pa, 'ItemRarity');
      [*] = ;            case rarity of 
      [*] = ;               2 : begin
      [*] = ;                  elem_d.color.r := gc_gui_fontcolor_Rarity2R;
      [*] = ;                  elem_d.color.g := gc_gui_fontcolor_Rarity2G;
      [*] = ;                  elem_d.color.b := gc_gui_fontcolor_Rarity2B;
      [*] = ;               end;
      [*] = ;               3 : begin
      [*] = ;                  elem_d.color.r := gc_gui_fontcolor_Rarity3R;
      [*] = ;                  elem_d.color.g := gc_gui_fontcolor_Rarity3G;
      [*] = ;                  elem_d.color.b := gc_gui_fontcolor_Rarity2B;
      [*] = ;               end;
      [*] = ;               4 : begin
      [*] = ;                  elem_d.color.r := gc_gui_fontcolor_Rarity4R;
      [*] = ;                  elem_d.color.g := gc_gui_fontcolor_Rarity4G;
      [*] = ;                  elem_d.color.b := gc_gui_fontcolor_Rarity4B;
      [*] = ;               end;
      [*] = ;               5 : begin
      [*] = ;                  elem_d.color.r := gc_gui_fontcolor_Rarity5R;
      [*] = ;                  elem_d.color.g := gc_gui_fontcolor_Rarity5G;
      [*] = ;                  elem_d.color.b := gc_gui_fontcolor_Rarity5B;
      [*] = ;               end;
      [*] = ;               6 : begin
      [*] = ;                  elem_d.color.r := gc_gui_fontcolor_Rarity6R;
      [*] = ;                  elem_d.color.g := gc_gui_fontcolor_Rarity6G;
      [*] = ;                  elem_d.color.b := gc_gui_fontcolor_Rarity6B;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if do_draw then
      [*] = ;               text := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,total_dx);
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle,text,w,h);
      [*] = ;
      [*] = ;            if do_draw then
      [*] = ;               e_dx := total_dx
      [*] = ;            else
      [*] = ;               e_dx := Min(w,tmp_pos.size.w);
      [*] = ;            tmp_pos.size.w := e_dx;
      [*] = ;            if do_draw then
      [*] = ;            begin
      [*] = ;               tmp_pos.size.h := h;
      [*] = ;               ehd := _gui_DWCreateText(if_handle,'name',windowHandle,text,elem_d.align,tmp_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;               e_dy := h;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cDescription : begin
      [*] = ;         var scroll_canvas_size : TElementSize;
      [*] = ;
      [*] = ;         temp_str := GetLocaleTableListItemByID('ritual', IntToStr(ritual_id)+'.description');
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         if not do_draw then
      [*] = ;            e_dx := w
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            i := total_dx;
      [*] = ;            if w > i then
      [*] = ;            begin
      [*] = ;               var ts2 : String;
      [*] = ;
      [*] = ;               ts2 := temp_str;
      [*] = ;               temp_str := GetGUIWrappedTextFormatByFont(elem_d.font_handle,ts2,i);
      [*] = ;               GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;               if h >= elem_d.p.size.h then // have to make room for scroller
      [*] = ;               begin
      [*] = ;                  temp_str := GetGUIWrappedTextFormatByFont(elem_d.font_handle,ts2,i-_gui_GetVScrollerWidth('map.dialog'));
      [*] = ;                  GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            scroll_canvas_size.w := w;
      [*] = ;            scroll_canvas_size.h := h;
      [*] = ;
      [*] = ;            tmp_pos.size.w := w;
      [*] = ;            tmp_pos.size.h := min(h,elem_d.p.size.h);
      [*] = ;
      [*] = ;            e_dx := w;
      [*] = ;            e_y := tmp_pos.pos.y;
      [*] = ;            e_dy := tmp_pos.size.h;
      [*] = ;
      [*] = ;            ehd := _gui_CreateScrollableCanvas_VVK('ritual_descr_scroll',windowHandle,elem_d.align,tmp_pos,scroll_canvas_size,'map.dialog',true);
      [*] = ;            e_dx := GetGUIElementWidth(ehd);
      [*] = ;            SetGUIAllowEvents(ehd, True, False, False);
      [*] = ;            _sys_FillRect(tmp_pos,0,0,w,h);
      [*] = ;            _gui_DWCreateText(if_handle,'',ehd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lt,elem_d.font_handle,elem_d.color);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cDCT, cDC, cTarget: begin // duration,cooldown,target
      [*] = ;         var a_color : String;
      [*] = ;         var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;         temp_str := '';
      [*] = ;         if elem_id <> cTarget then
      [*] = ;         begin
      [*] = ;            i := GetRitualValue('Time');
      [*] = ;            if i <> 0 then
      [*] = ;               temp_str := temp_str+GetLocaleTableListItemByID('gui', '86')+': '+IntToStr(i);
      [*] = ;            IntRegister0 := ritual_id;
      [*] = ;            PlayerExecuteStateByHandle(plHandle,'GetRitualCooldown');
      [*] = ;            i := IntRegister1;
      [*] = ;            if i <> 0 then
      [*] = ;            begin
      [*] = ;               if temp_str <> '' then
      [*] = ;               begin
      [*] = ;                  if elem_id = cDCT then temp_str := temp_str + gc_gui_BreakLine
      [*] = ;                  else temp_str := temp_str + '    ';
      [*] = ;               end;
      [*] = ;               temp_str := temp_str+GetLocaleTableListItemByID('gui', 'ritual_cooldown')+': '+IntToStr(i);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if elem_id <> cDC then
      [*] = ;         begin
      [*] = ;            i := 0;
      [*] = ;            if GetRitualValueB('OnHero') then
      [*] = ;               i := 2
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if GetRitualValueB('OnAlly') then
      [*] = ;                  i := 1;
      [*] = ;            end;
      [*] = ;            case i of
      [*] = ;               1 : a_color := 'info';
      [*] = ;               2 : a_color := 'warning';
      [*] = ;               else a_color := 'attention';
      [*] = ;            end;
      [*] = ;            if temp_str <> '' then temp_str := temp_str + gc_gui_BreakLine;
      [*] = ;            temp_str := temp_str + '%color('+a_color+')%'+GetLocaleTableListItemByID('gui', 'ritual_applied_to_'+IntToStr(i))+'%color(default)%';
      [*] = ;         end;
      [*] = ;         ProcessTextString(temp_str,do_draw);
      [*] = ;      end;
      [*] = ;      cIcon : begin
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;         e_dx := tmp_pos.size.w;
      [*] = ;         e_dy := tmp_pos.size.h;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            var tmp_pos2 : TRectangle;
      [*] = ;
      [*] = ;            _sys_FillRect(tmp_pos2,tmp_pos.pos.x,tmp_pos.pos.y,e_dx,e_dy);
      [*] = ;            ehd := _gui_CreateImage_VVK('',windowHandle,gc_gui_material_blank_0,elem_d.align,tmp_pos2);
      [*] = ;
      [*] = ;            temp_str := 'icon.ritual.'+IntToStr(ritual_id);
      [*] = ;            _gui_GetInterfaceElement(if_handle,cIconImage,elem2_d);
      [*] = ;            _sys_FillRect(tmp_pos2,_gui_ie_GetOffsetX(if_handle,cIconImage,cIcon,false),_gui_ie_GetOffsetY(if_handle,cIconImage,cIcon,false),elem2_d.p.size.w,elem2_d.p.size.h);
      [*] = ;            _gui_CreateImage_VVK('',ehd,temp_str,elem2_d.align,tmp_pos2);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cCurrentPrice: begin
      [*] = ;         var no,whd,ehd,start_x : Integer;
      [*] = ;         var r_v : array [0..$10] of Integer;
      [*] = ;         var r_vp : array [0..$10] of Integer;
      [*] = ;         var r_x : array [0..$10] of Integer;
      [*] = ;         var r_dx : array [0..$10] of Integer;
      [*] = ;         var r_id : array [0..$10] of Integer;
      [*] = ;         var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;         r_vp[0] := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         r_vp[1] := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         IntRegister0 := ritual_id;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetRitualPrice');
      [*] = ;         r_v[0] := IntRegister1;
      [*] = ;         r_v[1] := IntRegister2;
      [*] = ;         r_v[2] := 0;
      [*] = ;
      [*] = ;         no := 0;
      [*] = ;         temp_str := '%color(extrainfo)%'+GetLocaleTableListItemByID('gui', 'ritual_price')+': %color(default)%';
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;         start_x := w;
      [*] = ;         for i := 0 to 1 do
      [*] = ;         begin
      [*] = ;            if r_v[i] <> 0 then
      [*] = ;            begin
      [*] = ;               case i of
      [*] = ;                  0 : if r_v[i] >= r_vp[i] then temp_str2 := '4' else temp_str2 := '0';
      [*] = ;                  1 : if r_v[i] >= r_vp[i] then temp_str2 := '5' else temp_str2 := '1';
      [*] = ;               end;
      [*] = ;               temp_str2 := '%color(ignore)%%style(Symbols)%'+temp_str2+'%style(default)%%color(default)% '+IntToStr(r_v[i]);
      [*] = ;               if r_v[i+1] <> 0 then
      [*] = ;                  temp_str2 := temp_str2 + '   ';
      [*] = ;               temp_str := temp_str+temp_str2;
      [*] = ;               if do_draw then
      [*] = ;               begin
      [*] = ;                  r_id[no] := i;
      [*] = ;                  r_x[no] := start_x;
      [*] = ;                  GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str2,w,h);
      [*] = ;                  r_dx[no] := w;
      [*] = ;                  start_x := start_x + w;
      [*] = ;                  no := no + 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         ehd := ProcessTextString(temp_str,do_draw);
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            for i := 0 to no-1 do
      [*] = ;            begin
      [*] = ;               _sys_FillRect(tmp_pos,r_x[i],0,r_dx[i],h);
      [*] = ;               whd := _gui_CreateImage_VVK('',ehd,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;               SetGUIElementHint(whd,'gui|'+IntToStr(189+r_id[i]));
      [*] = ;               SetGUIAllowEvents(whd, True, False, False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cFullPrice: begin
      [*] = ;         var no,id,whd,ehd,start_x : Integer;
      [*] = ;         var ret_boxes,temp_str2 : String;
      [*] = ;
      [*] = ;         GetFullPrice(temp_str2);
      [*] = ;         temp_str := '%color(extrainfo)%'+GetLocaleTableListItemByID('gui', 'ritual_base_price')+': %color(default)%';
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,start_x,h);
      [*] = ;         h := _gui_ft_FormatResourcesData(temp_str2,elem_d.font_handle,'',temp_str2,ret_boxes,do_draw);
      [*] = ;         temp_str := temp_str + temp_str2;
      [*] = ;         ehd := ProcessTextString(temp_str,do_draw);
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            no := _sa_GetNum(ret_boxes) div 3;
      [*] = ;            for i := 0 to no-1 do
      [*] = ;            begin
      [*] = ;               id := _sa_GetAsInt(ret_boxes,i*3);
      [*] = ;               _sys_FillRect(tmp_pos,start_x+_sa_GetAsInt(ret_boxes,i*3+1),0,_sa_GetAsInt(ret_boxes,i*3+2),h);
      [*] = ;               case id of
      [*] = ;                  $10000 : temp_str := 'gui|189';
      [*] = ;                  $10001 : temp_str := 'gui|190';
      [*] = ;                  else _gui_ft_CreateHint_I3(temp_str,'VVK.FTooltipResource',id-1,cFT_ResSkipAccess,0);
      [*] = ;               end;
      [*] = ;               whd := _gui_CreateImage_VVK('',ehd,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;               SetGUIElementHint(whd,temp_str);
      [*] = ;               SetGUIAllowEvents(whd, True, False, False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cHelpIcon : begin
      [*] = ;         const icon_name = 'map.innerbuild.window.icon.hint.normal';
      [*] = ;
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,GetGUITextureWidth(icon_name),GetGUITextureHeight(icon_name));
      [*] = ;         _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_dx := tmp_pos.size.w;
      [*] = ;         e_dy := tmp_pos.size.h;
      [*] = ;         if do_draw then tmp_pos.pos.x := tmp_pos.pos.x+total_dx-e_dx;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;         e_x := tmp_pos.pos.y;
      [*] = ;         if do_draw then
      [*] = ;            _gui_CreateImage_VVK('',windowHandle,icon_name,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;      end;
      [*] = ;      cKarma : begin
      [*] = ;         i := GetRitualValue('Karma');
      [*] = ;         if i <> 0 then
      [*] = ;         begin
      [*] = ;            if i < 0 then
      [*] = ;               temp_str := gc_gui_KarmaBadChar + ' %color(attention)%' + IntToStr(i)
      [*] = ;            else
      [*] = ;               temp_str := gc_gui_KarmaChar + ' %color(info)%+' + IntToStr(i);
      [*] = ;
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;
      [*] = ;            _sys_FillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,0);
      [*] = ;            _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;            e_x := tmp_pos.pos.x;
      [*] = ;            if do_draw then
      [*] = ;            begin
      [*] = ;               tmp_pos.pos.x := total_dx+total_x-(w+elem_d.p.size.w+((total_dx) div 2));
      [*] = ;               e_dx := 1;
      [*] = ;               e_dy := h;
      [*] = ;               e_y := tmp_pos.pos.y;
      [*] = ;
      [*] = ;               tmp_pos.size.w := w;
      [*] = ;               tmp_pos.size.h := h;
      [*] = ;               ehd := _gui_CreateText_VVK('',windowHandle,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lm,elem_d.font_handle,elem_d.color);
      [*] = ;               SetGUIElementHint(ehd,'inner_build_abilities|'+IntToStr(gc_inner_build_karma));
      [*] = ;               SetGUIAllowEvents(ehd,True, False, False);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               e_dx := 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var field_id : Integer;
      [*] = ;
      [*] = ;if_handle := IntRegister1;
      [*] = ;FillStartupVariables(StringRegister0);
      [*] = ;case mode of
      [*] = ;   cDW_CallbackSetup : begin
      [*] = ;      var s0,s1 : String;
      [*] = ;
      [*] = ;      SetupInitial(s0,s1);
      [*] = ;      StringRegister0 := s0;
      [*] = ;      StringRegister1 := s1;
      [*] = ;   end;
      [*] = ;   cDW_CallbackIsDisplayable: begin
      [*] = ;      UnserializeData(StringRegister1,StringRegister4);
      [*] = ;      BoolRegister0 := IsDisplayableField(IntRegister2);
      [*] = ;   end;
      [*] = ;   cDW_CallbackGetWidth: begin
      [*] = ;      UnserializeData(StringRegister1,StringRegister4);
      [*] = ;      field_id := IntRegister2;
      [*] = ;      windowHandle := 0;
      [*] = ;      ProcessElement(field_id,false);
      [*] = ;      //if _log then _log_Values('SIZE_ID|X|DX|TOTAL_DX',field_id,e_x,e_dx,0,0,0);
      [*] = ;      IntRegister0 := e_dx;
      [*] = ;      IntRegister1 := e_x;
      [*] = ;   end;
      [*] = ;   cDW_CallbackDisplay: begin
      [*] = ;      UnserializeData(StringRegister1,StringRegister4);
      [*] = ;      field_id := IntRegister2;
      [*] = ;      windowHandle := IntRegister3;
      [*] = ;      ProcessElement(field_id,true);
      [*] = ;      //if _log then _log_Values('DRAW_ID|DX|Y|DY|TOTAL_DX|TOTAL_Y',field_id,e_dx,e_y,e_dy,total_dx,total_y);
      [*] = ;      IntRegister0 := e_dx;
      [*] = ;      IntRegister1 := e_y;
      [*] = ;      IntRegister2 := e_dy;
      [*] = ;   end;
      [*] = ;   cDW_CallbackShutdown: begin
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

