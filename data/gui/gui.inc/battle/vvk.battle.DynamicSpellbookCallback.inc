section.begin
   Name = vvk.battle.DynamicSpellbookCallback
   UsedFileName =
   Description : struct.begin
      [*] = ;For details please see VVK.DynamicWindowBuildingCallback
      [*] = ;Object ID string: uid of selected unit
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;const cIconFrame = 'icon.frame.item';
      [*] = ;
      [*] = ;const cNameTextOffset = $1d;
      [*] = ;const cSpellIcon = $1c;   // pos,size
      [*] = ;const cSpellName = $1b;         // font,color,pos,size
      [*] = ;const cSpellPrice = $1a;        // font,color,pos,size
      [*] = ;const cSpellCooldown = $19;     // font,color,pos,size
      [*] = ;const cSpellBorderOffsets = $18;// size-1 (!)
      [*] = ;
      [*] = ;const cFirstDisplayableField = $e;
      [*] = ;const cUnitStats = $e;
      [*] = ;const cSpellsLegend = $d;
      [*] = ;const cSpellsList = $c;         // pos
      [*] = ;const cName = $b;
      [*] = ;const cLastDisplayableField = $b;
      [*] = ;
      [*] = ;var e_x,e_dx,e_dy,e_y,total_dx,space_dx,space_dy,extra_dy_offset : Integer;
      [*] = ;var windowHandle,if_handle : Integer;
      [*] = ;//filled in fillstartup
      [*] = ;var spells_p,obj_uid,obj_handle : Integer;
      [*] = ;// filled in serialize
      [*] = ;var total_x,total_y,real_uid,real_handle : Integer;
      [*] = ;var ctxt0,ctxt1 : String;
      [*] = ;// saved in s0 on init
      [*] = ;var pl_handle,is_hero,hero_resurrected,pl_gems: Integer;
      [*] = ;//filled in processelement
      [*] = ;var elem_d,elem2_d : TInterfaceElementData;
      [*] = ;
      [*] = ;function ProcessTextString(text : String;use_elem_width : Boolean;do_draw : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;   var temp_str : String;
      [*] = ;   var w,h,ehd : Integer;
      [*] = ;
      [*] = ;   _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;   _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;   e_x := tmp_pos.pos.x;
      [*] = ;   if do_draw then
      [*] = ;      temp_str := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,total_dx)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if use_elem_width then
      [*] = ;         temp_str := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,elem_d.p.size.w)
      [*] = ;      else
      [*] = ;         temp_str := text;
      [*] = ;   end;
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
      [*] = ;function GetSpellDuration(p_spell : Integer) : Integer; // $10000-momentary,$10000+cr_id-summon cr id
      [*] = ;begin
      [*] = ;   var p,p1,i,d,d1,a_id,c : Integer;
      [*] = ;   var spell_id : Integer = ParserGetIntValueByKeyByHandle(p_spell,'SpellID');;
      [*] = ;
      [*] = ;   d := -1;
      [*] = ;   c := 0;
      [*] = ;   p := ParserSelectByHandleByKey(p_spell,'Effects');
      [*] = ;   if p <> 0 then
      [*] = ;   begin
      [*] = ;      for i := 0 to ParserGetCountByHandle(p)-1 do
      [*] = ;      begin
      [*] = ;         p1 := ParserSelectByHandleByIndex(p,i);
      [*] = ;         a_id := ParserGetIntValueByKeyByHandle(p1,'AbilityID');
      [*] = ;         d1 := ParserGetIntValueByKeyByHandle(p1,'Duration');
      [*] = ;         case a_id of
      [*] = ;            47 : d1 := 2; // web hack
      [*] = ;            71 : d1 := 0; // life drain
      [*] = ;            72 : d1 := 0; // white magic
      [*] = ;            73 : if spell_id = 52 then d1 := 1; // word of power
      [*] = ;         end;
      [*] = ;         d := max(d,d1);
      [*] = ;         if a_id > 1000 then
      [*] = ;            c := a_id-1000;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if d < 0 then
      [*] = ;      Result := $10000+c
      [*] = ;   else
      [*] = ;      Result := d;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetBorderFlags(x,y,no,dx : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var flags,dy,rx : Integer;
      [*] = ;
      [*] = ;   flags := $1ce;
      [*] = ;   dy := (no+dx-1) div dx;
      [*] = ;   rx := no mod dx;
      [*] = ;   if rx=0 then rx := dx+1;
      [*] = ;
      [*] = ;   if (x=(dx-1)) then
      [*] = ;      flags := flags and ($1ff xor $42);
      [*] = ;   if (y=(dy-1)) and (x>=(rx-1))then
      [*] = ;      flags := flags and ($1ff xor $40);
      [*] = ;   if (y=(dy-1)) or ((y=(dy-2)) and (x>=rx)) then
      [*] = ;      flags := flags and ($1ff xor $8c);
      [*] = ;
      [*] = ;   Result := flags;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsDisplayableField(i : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if (i >= cLastDisplayableField) and (i <= cFirstDisplayableField) then
      [*] = ;   begin
      [*] = ;      Result := true;
      [*] = ;      case i of
      [*] = ;         cSpellsList: begin
      [*] = ;            if ParserGetCountByHandle(spells_p) = 0 then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillStartupVariables(object_id : String);
      [*] = ;begin
      [*] = ;   obj_uid := _sa_GetAsInt(object_id,0);
      [*] = ;   obj_handle := GetGameObjectHandleByUniqueId(obj_uid);
      [*] = ;   spells_p := ParserSelectByHandleByKey(ParserSelectGameObject(obj_handle),'Spells');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetupInitial(template_id: Integer; var s0 : String; var s1 : String);
      [*] = ;begin
      [*] = ;   var uid,handle : Integer;
      [*] = ;
      [*] = ;   hero_resurrected := 0;
      [*] = ;   is_hero := 0;
      [*] = ;   if GetGameObjectBoolValueIndByHandle(obj_handle, gc_stack_unit_bIsHero) then
      [*] = ;      is_hero := 1;
      [*] = ;
      [*] = ;   //if is_hero = 0 then
      [*] = ;   //begin
      [*] = ;   //   // check if this is resurrected unit
      [*] = ;   //   uid := GetGameObjectIntValueIndByHandle(obj_handle,gc_stack_unit_iTrueFormUID);
      [*] = ;   //   handle := GetGameObjectHandleByUniqueId(uid);
      [*] = ;   //
      [*] = ;   //   if handle <> 0 then
      [*] = ;   //   begin
      [*] = ;   //      if GetGameObjectBoolValueIndByHandle(handle,gc_stack_unit_bIsHero) then
      [*] = ;   //      begin
      [*] = ;   //         is_hero := 1;
      [*] = ;   //         hero_resurrected := uid;
      [*] = ;   //         obj_handle := handle;
      [*] = ;   //      end;
      [*] = ;   //   end;
      [*] = ;   //end;
      [*] = ;
      [*] = ;   uid := GetGameObjectIntValueIndByHandle(obj_handle,gc_stack_unit_iHeroUID);
      [*] = ;   handle := GetGameObjectHandleByUniqueId(uid);
      [*] = ;   pl_handle := GetGameObjectPlayerHandleByHandle(handle);
      [*] = ;   pl_gems := GetPlayerIntValueIndByHandle(pl_handle,gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;   s0 := '';
      [*] = ;   _sa_AddAsInt(s0,is_hero);
      [*] = ;   _sa_AddAsInt(s0,hero_resurrected);
      [*] = ;   _sa_AddAsInt(s0,pl_handle);
      [*] = ;   _sa_AddAsInt(s0,pl_gems);
      [*] = ;
      [*] = ;   s1 := '';
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UnserializeData(s0 : String;v : String);
      [*] = ;begin
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
      [*] = ;
      [*] = ;   is_hero := _sa_GetAsInt(s0,0);
      [*] = ;   hero_resurrected := _sa_GetAsInt(s0,1);
      [*] = ;   pl_handle := _sa_GetAsInt(s0,2);
      [*] = ;   pl_gems := _sa_GetAsInt(s0,3);
      [*] = ;   real_uid := obj_uid;
      [*] = ;   real_handle := obj_handle;
      [*] = ;   if hero_resurrected <> 0 then
      [*] = ;   begin
      [*] = ;      obj_uid := hero_resurrected;
      [*] = ;      obj_handle := GetGameObjectHandleByUniqueId(obj_uid);
      [*] = ;      spells_p := ParserSelectByHandleByKey(ParserSelectGameObject(obj_handle),'Spells');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ProcessElement(elem_id, if_handle: Integer;do_draw : Boolean);
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
      [*] = ;         text := GetLocaleTableListItemByID('gui', '123');
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
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
      [*] = ;               ehd := _gui_CreateText_VVK('',ehd,text,gc_gui_align_parent_mt,tmp_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if do_draw then
      [*] = ;               text := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,total_dx);
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle,text,w,h);
      [*] = ;
      [*] = ;            e_dx := Max(w,tmp_pos.size.w);
      [*] = ;            tmp_pos.size.w := e_dx;
      [*] = ;            if do_draw then
      [*] = ;            begin
      [*] = ;               tmp_pos.size.h := h;
      [*] = ;               ehd := _gui_CreateText_VVK('name',windowHandle,text,elem_d.align,tmp_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;               e_dy := h;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cSpellsList: begin
      [*] = ;         var n_dx,no,i,j,whd,ehd,duration,x,y,count,rhd,start_x,font_h,n,s_no,cx,cy : Integer;
      [*] = ;         var spells_available,avail : Boolean;
      [*] = ;         var r_v : array [0..$10] of Integer;
      [*] = ;         var r_vp : array [0..$10] of Integer;
      [*] = ;         var r_id : array [0..$10] of Integer;
      [*] = ;         var r_x : array [0..$10] of Integer;
      [*] = ;         var r_dx : array [0..$10] of Integer;
      [*] = ;         var avail_idx : array [0..$40] of Integer;
      [*] = ;         var avail_no : array [0..$40] of Integer;
      [*] = ;         var spell : array [0..$40] of Integer;
      [*] = ;         var spell_p : array [0..$40] of Integer;
      [*] = ;         var id : array [0..$40] of Integer;
      [*] = ;         var spells_no : array [0..$40] of Integer;
      [*] = ;         var names : array [0..$40] of String;
      [*] = ;         var text_d,price_d : TInterfaceElementData;
      [*] = ;         var tmp_pos2 : TRectangle;
      [*] = ;         var c : TColorRGBA;
      [*] = ;
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,1,1);
      [*] = ;         _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;
      [*] = ;         _gui_GetInterfaceElement(if_handle,cSpellName,text_d);
      [*] = ;         text_d.p.pos.x := text_d.p_raw.pos.x - elem_d.p_raw.pos.x;
      [*] = ;         text_d.p.pos.y := text_d.p_raw.pos.y - elem_d.p_raw.pos.y;
      [*] = ;
      [*] = ;         _gui_GetInterfaceElement(if_handle,cSpellPrice,price_d);
      [*] = ;
      [*] = ;         spells_available := GetGameObjectBoolValueIndByHandle(obj_handle, gc_stack_unit_bCanAct) and GetGameObjectBoolValueIndByHandle(obj_handle, gc_stack_unit_bCanCast);
      [*] = ;
      [*] = ;         no := 0;
      [*] = ;         for i := 0 to ParserGetCountByHandle(spells_p)-1 do
      [*] = ;         begin
      [*] = ;            spell[no] := ParserSelectByHandleByIndex(spells_p,i);
      [*] = ;            id[no] := ParserGetIntValueByKeyByHandle(spell[no], 'SpellID');
      [*] = ;            for j := 0 to no-1 do
      [*] = ;            begin
      [*] = ;               if id[j] = id[no] then
      [*] = ;               begin
      [*] = ;                  spells_no[j] := spells_no[j] + 1;
      [*] = ;                  if not ParserGetBoolValueByKeyByHandle(spell[no],'Used') then
      [*] = ;                  begin
      [*] = ;                     avail_idx[j] := i;
      [*] = ;                     avail_no[j] := avail_no[j] + 1;
      [*] = ;                  end;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if j = no then
      [*] = ;            begin
      [*] = ;               IntRegister0 := id[no];
      [*] = ;               MapExecuteState('GetSpellParserByID');
      [*] = ;               spell_p[no] := IntRegister1;
      [*] = ;               spells_no[j] := 1;
      [*] = ;               if not ParserGetBoolValueByKeyByHandle(spell[no],'Used') then
      [*] = ;               begin
      [*] = ;                  avail_idx[no] := i;
      [*] = ;                  avail_no[no] := 1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  avail_idx[no] := -1;
      [*] = ;                  avail_no[no] := 0;
      [*] = ;               end;
      [*] = ;               no := no + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         s_no := no;
      [*] = ;
      [*] = ;         temp_str := '%style(Symbols)%'+'M'+'%style(default)% 00  ';
      [*] = ;         GetGUIElementFontTextFormatRect(price_d.font_handle,temp_str,w,h);
      [*] = ;         start_x := w*3;
      [*] = ;         for i := 0 to s_no-1 do
      [*] = ;         begin
      [*] = ;            names[i] := GetLocaleTableListItemByID('spell', IntToStr(id[i]));
      [*] = ;            if avail_no[i] <> 1 then names[i] := names[i] + ' ('+IntToStr(avail_no[i])+')';
      [*] = ;            GetGUIElementFontTextFormatRect(text_d.font_handle,names[i],w,h);
      [*] = ;            if w > start_x then start_x := w;
      [*] = ;         end;
      [*] = ;         w := text_d.p.size.w-start_x;
      [*] = ;         elem_d.p.size.w := text_d.p.pos.x+(text_d.p.size.w-w)+(elem_d.p.size.w-(text_d.p.pos.x+text_d.p.size.w));
      [*] = ;         text_d.p.size.w := text_d.p.size.w - w;
      [*] = ;         if do_draw then w := min(total_dx,s_no*elem_d.p.size.w)
      [*] = ;         else w := s_no*elem_d.p.size.w;
      [*] = ;
      [*] = ;         _gui_FormatTableByRatio(w div elem_d.p.size.w,s_no,elem_d.p.size.w,elem_d.p.size.h,4/2,true,e_dx,e_dy);
      [*] = ;         e_dy := e_dy*elem_d.p.size.h;
      [*] = ;         n_dx := e_dx;
      [*] = ;         e_dx := e_dx*elem_d.p.size.w;
      [*] = ;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            no := 0;
      [*] = ;            if is_hero <> 0 then
      [*] = ;            begin
      [*] = ;               r_vp[no] := GetGameObjectIntValueIndByHandle(obj_handle,gc_stack_unit_iCurStamina); no := no + 1;
      [*] = ;               r_vp[no] := pl_gems; no := no + 1;
      [*] = ;               r_vp[no] := GetGameObjectIntValueIndByHandle(obj_handle,gc_stack_unit_iCurLife); no := no + 1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               r_vp[no] := GetGameObjectIntValueIndByHandle(obj_handle,gc_stack_unit_iCurAmmo); no := no + 1;
      [*] = ;            end;
      [*] = ;
      [*] = ;            ehd := _gui_CreateImage_VVK('list',windowHandle,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;
      [*] = ;            _gui_GetInterfaceElement(if_handle,cSpellIcon,elem2_d);
      [*] = ;            elem2_d.p.pos.x := elem2_d.p_raw.pos.x - elem_d.p_raw.pos.x;
      [*] = ;            elem2_d.p.pos.y := elem2_d.p_raw.pos.y - elem_d.p_raw.pos.y;
      [*] = ;            cx := (GetGUITextureWidth(cIconFrame)-elem2_d.p.size.w) div 2;
      [*] = ;            cy := (GetGUITextureHeight(cIconFrame)-elem2_d.p.size.h) div 2;
      [*] = ;
      [*] = ;            price_d.p.pos.x := price_d.p_raw.pos.x - elem_d.p_raw.pos.x;
      [*] = ;            price_d.p.pos.y := price_d.p_raw.pos.y - elem_d.p_raw.pos.y;
      [*] = ;
      [*] = ;            _gui_GetInterfaceWindowColor(if_handle,7,c);
      [*] = ;            SetGUIElementStringTag(ehd,FormatColorToHex4(text_d.color.a,text_d.color.r,text_d.color.g,text_d.color.b)+'|'+FormatColorToHex4(c.a,c.r,c.g,c.b));
      [*] = ;
      [*] = ;            _sys_FillRect(tmp_pos,0,0,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;
      [*] = ;            if _log then _log_values('NDX|W|H',n_dx,elem_d.p.size.w,elem_d.p.size.h,0,0,0);
      [*] = ;            x := 0;
      [*] = ;            y := 0;
      [*] = ;            for i := 0 to s_no-1 do
      [*] = ;            begin
      [*] = ;               duration := GetSpellDuration(spell_p[i]);
      [*] = ;               avail := spells_available;
      [*] = ;
      [*] = ;               if is_hero <> 0 then
      [*] = ;               begin
      [*] = ;                  r_v[0] := ParserGetIntValueByKeyByHandle(spell_p[i], 'StamCost');
      [*] = ;                  r_v[1] := ParserGetIntValueByKeyByHandle(spell_p[i], 'Cost');
      [*] = ;                  r_v[2] := ParserGetIntValueByKeyByHandle(spell_p[i], 'LifeCost');
      [*] = ;                  r_v[3] := 0;
      [*] = ;
      [*] = ;                  // world rule
      [*] = ;                  if (_worldrule_GetWorldRuleAbilityExistByID(8)) then
      [*] = ;                     r_v[1] := _misc_RoundUp((r_v[1]*_worldrule_GetWorldRuleAbilityParam1(8))/100);
      [*] = ;
      [*] = ;                  IntRegister0 := 983;
      [*] = ;                  GameObjectExecuteStateByHandle(obj_handle, 'CheckAbility');
      [*] = ;                  r_v[1] := (r_v[1] * (100 - IntRegister1)) div 100;
      [*] = ;                  if avail_no[i] <= 0 then avail := false;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  r_v[0] := ParserGetIntValueByKeyByHandle(spell[i], 'Ammo');
      [*] = ;                  r_v[1] := 0;
      [*] = ;               end;
      [*] = ;
      [*] = ;               for j := 0 to (no)-1 do
      [*] = ;               begin
      [*] = ;                  if (r_v[j] > 0) and (r_vp[j] < r_v[j]) then
      [*] = ;                  begin
      [*] = ;                     avail := false;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if avail then j := 1 else j := 0;
      [*] = ;               //_log_Values('A|ST|GEM|LIFE',j,r_v[0],r_v[1],r_v[2],0,0);
      [*] = ;
      [*] = ;               j := (i shl $10) or (id[i] and $ffff);
      [*] = ;               _sys_FillRect(tmp_pos2,tmp_pos.pos.x,tmp_pos.pos.y,tmp_pos.size.w,tmp_pos.size.h);
      [*] = ;               whd := _gui_CreateButton_VVK('highlight_button_'+IntToStr(j),ehd,'',gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos,'','',gc_gui_castle_spells_btnBaseTag+avail_idx[i]);
      [*] = ;               if avail then
      [*] = ;               begin
      [*] = ;                  temp_str2 := 'battle.EventSpellBookWindow';
      [*] = ;                  SetGUIElementVisibleProperties(whd,'HoverProperty',gc_gui_material_blank_0, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementVisibleProperties(whd,'DownProperty',gc_gui_material_blank_0,  0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  temp_str2 := '';
      [*] = ;                  SetGUIElementVisibleProperties(whd,'HoverProperty',gc_gui_material_blank_0, 0, 0, 0, 0,  1, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementVisibleProperties(whd,'DownProperty',gc_gui_material_blank_0,  0, 0, 0, 0,  1, 0.5, 0.5, 0.5, 1);
      [*] = ;               end;
      [*] = ;               if is_hero <> 0 then j := r_v[1] else j := r_v[0];
      [*] = ;               _gui_ft_AttachHint_I4_S2(whd,'VVK.FTooltipSpell',id[i],is_hero,j,cFT_SpellTypeBook,temp_str2,'4');
      [*] = ;
      [*] = ;               if avail then SetGUIElementStringTag(whd,IntToStr(j))
      [*] = ;               else SetGUIElementStringTag(whd,IntToStr(-1*j));
      [*] = ;
      [*] = ;               rhd := whd;
      [*] = ;
      [*] = ;               _sys_FillRect(tmp_pos2,0,0,tmp_pos.size.w,tmp_pos.size.h);
      [*] = ;               _gui_CreateScalableWindowExt_VVK('',rhd,gc_gui_align_parent_lt,tmp_pos2,'wooden_window',GetBorderFlags(x,y,s_no,n_dx));
      [*] = ;
      [*] = ;               start_x := 0;
      [*] = ;               n := 0;
      [*] = ;               temp_str := '';
      [*] = ;               for j := 0 to no-1 do
      [*] = ;               begin
      [*] = ;                  if r_v[j] <> 0 then
      [*] = ;                  begin
      [*] = ;                     case j of
      [*] = ;                        0 : if (is_hero = 0) then temp_str2 := '[' else temp_str2 := 'Q';
      [*] = ;                        1 : temp_str2 := '1';
      [*] = ;                        2 : temp_str2 := 'P';
      [*] = ;                     end;
      [*] = ;                     temp_str2 := '%color(ignore)%%style(Symbols)%'+temp_str2+'%style(default)%%color(default)% '+IntToStr(r_v[j]);
      [*] = ;                     if r_v[j+1] <> 0 then
      [*] = ;                        temp_str2 := temp_str2 + '   ';
      [*] = ;                     temp_str := temp_str+temp_str2;
      [*] = ;                     if is_hero = 0 then
      [*] = ;                        r_id[n] := $100
      [*] = ;                     else
      [*] = ;                        r_id[n] := j;
      [*] = ;                     r_x[n] := start_x;
      [*] = ;                     GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str2,w,font_h);
      [*] = ;                     r_dx[n] := w;
      [*] = ;                     start_x := start_x + w;
      [*] = ;                     n := n + 1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               // to do - calculate REAL duration
      [*] = ;               temp_str := temp_str + gc_gui_BreakLine;
      [*] = ;               if (duration > 0) and (duration < $10000) then
      [*] = ;               begin
      [*] = ;                  temp_str := temp_str + '%color(ignore)%%style(Symbols)%'+'M'+'%style(default)%%color(extrainfo)% '+IntToStr(duration);
      [*] = ;               end;
      [*] = ;
      [*] = ;               GetGUIElementFontTextFormatRect(price_d.font_handle,temp_str,w,h);
      [*] = ;               _sys_FillRect(tmp_pos2,price_d.p.pos.x,price_d.p.pos.y,w,price_d.p.size.h);
      [*] = ;               whd := _gui_DWCreateText(if_handle,'',rhd,temp_str,gc_gui_align_parent_lt,tmp_pos2,gc_gui_align_lm,price_d.font_handle,price_d.color);
      [*] = ;               if not avail then SetGUIElementUserBlend(whd,0.8);
      [*] = ;
      [*] = ;               for j := 0 to n-1 do
      [*] = ;               begin
      [*] = ;                  _sys_FillRect(tmp_pos2,r_x[j],0,r_dx[j],font_h);
      [*] = ;                  case r_id[j] of
      [*] = ;                     0 : temp_str := 'ability|11';
      [*] = ;                     1 : temp_str := 'gui|190';
      [*] = ;                     2 : temp_str := 'ability|1';
      [*] = ;                     $100 : temp_str := 'ability|10';
      [*] = ;                  end;
      [*] = ;                  //h := _gui_CreateImage_VVK('',whd,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos2);
      [*] = ;                  //SetGUIElementHint(h,temp_str);
      [*] = ;                  //SetGUIAllowEvents(h, True, False, False);
      [*] = ;               end;
      [*] = ;
      [*] = ;               _sys_FillRect(tmp_pos2,elem2_d.p.pos.x-cx,elem2_d.p.pos.y-cy,0,0);
      [*] = ;               whd :=_gui_CreateImage_VVK('',rhd,cIconFrame,gc_gui_align_parent_lt,tmp_pos2);
      [*] = ;               _sys_FillRect(tmp_pos2,0,0,elem2_d.p.size.w,elem2_d.p.size.h);
      [*] = ;               whd := _gui_CreateImage_VVK('',whd,'icon.spell.'+IntToStr(id[i]),gc_gui_align_parent_m,tmp_pos2);
      [*] = ;               if not avail then SetGUIElementUserBlend(whd,0.3);
      [*] = ;
      [*] = ;               _sys_FillRect(tmp_pos2,text_d.p.pos.x,text_d.p.pos.y,text_d.p.size.w,text_d.p.size.h);
      [*] = ;               whd := _gui_CreateText_VVK('name',rhd,names[i],gc_gui_align_parent_lt,tmp_pos2,gc_gui_align_lm,text_d.font_handle,text_d.color);
      [*] = ;               if not avail then SetGUIElementUserBlend(whd,0.6);
      [*] = ;
      [*] = ;               x := x + 1;
      [*] = ;               tmp_pos.pos.x := tmp_pos.pos.x + tmp_pos.size.w;
      [*] = ;               if x >= n_dx then
      [*] = ;               begin
      [*] = ;                  x := 0;
      [*] = ;                  y := y + 1;
      [*] = ;                  tmp_pos.pos.x := 0;
      [*] = ;                  tmp_pos.pos.y := tmp_pos.pos.y + tmp_pos.size.h;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cSpellsLegend: begin
      [*] = ;         i := _cmd_Check('battlecastspell','','1');
      [*] = ;         if ((i and $ff) <> 1) then
      [*] = ;            i := 1
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if ((i and $100) = 0) then
      [*] = ;               i := 0
      [*] = ;            else
      [*] = ;               i := 2;
      [*] = ;         end;
      [*] = ;         temp_str := GetLocaleTableListItemByID('spell', 'window_legend_'+IntToStr(i));
      [*] = ;         ProcessTextString(temp_str,true,do_draw);
      [*] = ;      end;
      [*] = ;      cUnitStats : begin
      [*] = ;         const h0 = '%color(ignore)%%style(Symbols)%';
      [*] = ;         const h1 = '%color(default)%%style(default)%';
      [*] = ;
      [*] = ;         var r_x : array [0..$10] of Integer;
      [*] = ;         var r_dx : array [0..$10] of Integer;
      [*] = ;         var r_hint : array [0..$10] of String;
      [*] = ;         var temp_str2 : String;
      [*] = ;         var start_x,ehd,w,h : Integer;
      [*] = ;
      [*] = ;         start_x := 0;
      [*] = ;         if is_hero <> 0 then
      [*] = ;         begin
      [*] = ;            temp_str2 := h0+'Q'+h1+' '+IntToStr(GetGameObjectIntValueIndByHandle(obj_handle,gc_stack_unit_iCurStamina))+'    ';
      [*] = ;            temp_str := temp_str2;
      [*] = ;            if do_draw then
      [*] = ;            begin
      [*] = ;               GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str2,w,h);
      [*] = ;               r_x[0] := start_x; r_dx[0] := w; start_x := start_x + w; r_hint[0] := 'ability|11';
      [*] = ;            end;
      [*] = ;
      [*] = ;            temp_str2:= h0+'1'+h1+' '+IntToStr(pl_gems)+'    ';
      [*] = ;            temp_str := temp_str+temp_str2;
      [*] = ;            if do_draw then
      [*] = ;            begin
      [*] = ;               GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str2,w,h);
      [*] = ;               r_x[1] := start_x; r_dx[1] := w; start_x := start_x + w; r_hint[1] := 'gui|190';
      [*] = ;            end;
      [*] = ;
      [*] = ;            temp_str2 := h0+'P'+h1+' '+IntToStr(GetGameObjectIntValueIndByHandle(obj_handle,gc_stack_unit_iCurLife));
      [*] = ;            temp_str := temp_str+temp_str2;
      [*] = ;            if do_draw then
      [*] = ;            begin
      [*] = ;               GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str2,w,h);
      [*] = ;               r_x[2] := start_x; r_dx[2] := w; start_x := start_x + w; r_hint[2] := 'ability|1';
      [*] = ;               r_hint[3] := '';
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            temp_str := h0+'['+h1+' '+IntToStr(GetGameObjectIntValueIndByHandle(obj_handle,gc_stack_unit_iCurAmmo));
      [*] = ;            if do_draw then
      [*] = ;            begin
      [*] = ;               GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;               r_x[0] := start_x; r_dx[0] := w; start_x := start_x + w; r_hint[0] := 'ability|10';
      [*] = ;               r_hint[1] := '';
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         temp_str := gc_gui_BreakLine+temp_str;
      [*] = ;         ehd := ProcessTextString(temp_str,true,do_draw);
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            var tmp_pos : TRectangle;
      [*] = ;
      [*] = ;            start_x := 0;
      [*] = ;            while r_hint[start_x] <> '' do
      [*] = ;            begin
      [*] = ;               _sys_FillRect(tmp_pos,r_x[start_x],h,r_dx[start_x],h);
      [*] = ;               w := _gui_CreateImage_VVK('',ehd,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;               SetGUIElementHint(w,r_hint[start_x]);
      [*] = ;               SetGUIAllowEvents(w, True, False, False);
      [*] = ;               start_x := start_x + 1;
      [*] = ;            end;
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
      [*] = ;      SetupInitial(if_handle,s0,s1);
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
      [*] = ;      ProcessElement(field_id,if_handle,false);
      [*] = ;      //if _log then _log_Values('SIZE_ID|X|DX|TOTAL_DX',field_id,e_x,e_dx,0,0,0);
      [*] = ;      IntRegister0 := e_dx;
      [*] = ;      IntRegister1 := e_x;
      [*] = ;   end;
      [*] = ;   cDW_CallbackDisplay: begin
      [*] = ;      UnserializeData(StringRegister1,StringRegister4);
      [*] = ;      field_id := IntRegister2;
      [*] = ;      windowHandle := IntRegister3;
      [*] = ;      ProcessElement(field_id,if_handle,true);
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

