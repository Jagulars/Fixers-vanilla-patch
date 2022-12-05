section.begin
   Name = VVK.DynamicWindowItemCallback
   UsedFileName =
   Description : struct.begin
      [*] = ;For details please see VVK.DynamicWindowBuildingCallback
      [*] = ;Object ID string: item_id,price_mode(cFT_ItemPrice),durability,parent object(hero) uid or (cFT_ItemHero)
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;var _test_display : Boolean = false;
      [*] = ;
      [*] = ;const cTexDelimiter = 'tooltip_text_delimiter';
      [*] = ;
      [*] = ;const cNameTextOffset = $1d;
      [*] = ;const cIconImage = $1c;
      [*] = ;const cAbilityText = $1b;
      [*] = ;const cAbilityHeaderOffset = $1a;
      [*] = ;const cSetHeaderText = $19;
      [*] = ;
      [*] = ;const cFirstDisplayableField = $16;
      [*] = ;const cDescription = $16;
      [*] = ;const cHelpIcon = $15;               // help icon
      [*] = ;const cRes_0x14 = $14;
      [*] = ;const cSetAbilities = $13;
      [*] = ;const cPriceFull = $12;
      [*] = ;const cPriceInfo = $11;
      [*] = ;const cSetInfo = $10;
      [*] = ;const cStatsText = $f;
      [*] = ;const cAbilities = $e;
      [*] = ;const cIcon = $d;
      [*] = ;const cCPD = $c; // class/place/durability block
      [*] = ;const cName = $b;
      [*] = ;const cLastDisplayableField = $b;
      [*] = ;
      [*] = ;var e_x,e_dx,e_dy,e_y,total_dx,space_dx,space_dy,extra_dy_offset : Integer;
      [*] = ;var if_handle,windowHandle : Integer;
      [*] = ;// filled in serialize
      [*] = ;var total_x,total_y : Integer;
      [*] = ;var ctxt0,ctxt1 : String;
      [*] = ;// saved in s0 on init
      [*] = ;var item_id,price_mode,durability,hero_uid,hero_mode : Integer;
      [*] = ;// calculated in unserialize
      [*] = ;var hero_handle,pl_handle,p_item : Integer;
      [*] = ;//filled in processelement
      [*] = ;var elem_d,elem2_d : TInterfaceElementData;
      [*] = ;
      [*] = ;function CreateESButton(ehd : Integer;pos : TRectangle;elem2_d : TInterfaceElementData;value : Integer;hint,icon_name : String;value_type : Integer; draw_button : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var whd,xhd,w,h : Integer;
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;
      [*] = ;   _sys_FillRect(tmp_pos,0,0,pos.size.w,pos.size.h);
      [*] = ;   xhd := _gui_CreateImage_VVK('',ehd,icon_name,gc_gui_align_parent_lt,pos);
      [*] = ;   if not draw_button then
      [*] = ;   begin
      [*] = ;     SetGUIAllowEvents(xhd, True, False, False);
      [*] = ;     SetGUIElementHint(xhd,hint);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      whd := _gui_CreateButton_VVK('',xhd,'','heropanel.icon.52x52.slot.cover',gc_gui_align_parent_lt,tmp_pos,'',hint,0);
      [*] = ;
      [*] = ;   case value_type of
      [*] = ;      1 : value_type := 1;
      [*] = ;      3 : begin
      [*] = ;         if value > 0 then _gui_CreateImage_VVK('',xhd,'building_show_2',gc_gui_align_parent_lt,tmp_pos);
      [*] = ;      end;
      [*] = ;      else begin
      [*] = ;         var temp_str : String;
      [*] = ;
      [*] = ;         if value_type = 2 then
      [*] = ;            temp_str := IntToStr(value)+'%'
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if value > 0 then
      [*] = ;               temp_str := '+'+IntToStr(value)
      [*] = ;            else
      [*] = ;               temp_str := IntToStr(value)
      [*] = ;         end;
      [*] = ;         GetGUIElementFontTextFormatRect(elem2_d.font_handle,temp_str,w,h);
      [*] = ;         _sys_FillRect(tmp_pos,pos.size.w-(w+2+1),pos.size.h-(h+2+1),w+2,h+2);
      [*] = ;         whd  := _gui_CreateImage_VVK('',xhd,'pixel.0.0.0',gc_gui_align_parent_lt,tmp_pos);
      [*] = ;         _gui_CreateText_VVK('',xhd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lt,elem2_d.font_handle,elem2_d.color);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := xhd;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsDisplayableField(i : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if (i >= cLastDisplayableField) and (i <= cFirstDisplayableField) then
      [*] = ;   begin
      [*] = ;      Result := true;
      [*] = ;      case i of
      [*] = ;         cSetInfo, cSetAbilities : begin
      [*] = ;            if ParserGetIntValueByKeyByHandle(p_item, 'ItemSetID') <= 0 then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;         cPriceInfo : begin
      [*] = ;            if price_mode = cFT_ItemPriceHide then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;         cCPD : begin
      [*] = ;            var p,id : Integer;
      [*] = ;
      [*] = ;            p := ParserSelectByHandleByKey(p_item, 'Abilities');
      [*] = ;
      [*] = ;            id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(p,0),'AbilityID');
      [*] = ;            if id = gc_ability_summon then
      [*] = ;               Result := False;
      [*] = ;         end;
      [*] = ;         cAbilities, cStatsText : begin
      [*] = ;            if ParserSelectByHandleByKey(p_item, 'Abilities') = 0 then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;         cRes_0x14 : Result := false;
      [*] = ;         cDescription : begin
      [*] = ;            if GetLocaleTableListItemByID('item', IntToStr(item_id)+'.description') = '' then
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
      [*] = ;   item_id := _sa_GetAsInt(object_id,0);
      [*] = ;   price_mode := _sa_GetAsInt(object_id,1);
      [*] = ;   durability := _sa_GetAsInt(object_id,2);
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
      [*] = ;procedure SetupInitial(template_id: Integer; var s0 : String; var s1 : String);
      [*] = ;begin
      [*] = ;   hero_handle := GetGameObjectHandleByUniqueId(hero_uid);
      [*] = ;   pl_handle := GetGameObjectPlayerHandleByHandle(hero_handle);
      [*] = ;   if pl_handle = 0 then
      [*] = ;      pl_handle := GetPlayerHandleInterfaceIO();
      [*] = ;   p_item := ParserSelectByHandleByIndex(gPrototypeData.extItems.handle,item_id);
      [*] = ;
      [*] = ;   s0 := '';
      [*] = ;   _sa_AddAsInt(s0,hero_handle);
      [*] = ;   _sa_AddAsInt(s0,pl_handle);
      [*] = ;   _sa_AddAsInt(s0,p_item);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UnserializeData(s0 : String;v : String);
      [*] = ;begin
      [*] = ;   hero_handle := _sa_GetAsInt(s0,0);
      [*] = ;   pl_handle := _sa_GetAsInt(s0,1);
      [*] = ;   p_item := _sa_GetAsInt(s0,2);
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
      [*] = ;function GetItemValue(v_name : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserGetIntValueByKeyByHandle(p_item, v_name);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetFullPrice(var res_str: String) : Boolean;
      [*] = ;begin
      [*] = ;   var c,n : Integer;
      [*] = ;   var s,temp_str : String;
      [*] = ;
      [*] = ;   s := '';
      [*] = ;   n := 0;
      [*] = ;   c := GetItemValue('GoldCost');
      [*] = ;   if c <> 0 then
      [*] = ;   begin
      [*] = ;      _sa_AddAsInt(s,$10000);
      [*] = ;      _sa_AddAsInt(s,c);
      [*] = ;      n := n + 1;
      [*] = ;   end;
      [*] = ;   c := GetItemValue('GemCost');
      [*] = ;   if c <> 0 then
      [*] = ;   begin
      [*] = ;      _sa_AddAsInt(s,$10001);
      [*] = ;      _sa_AddAsInt(s,c);
      [*] = ;      n := n + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   c := _gui_ft_GetResourcesCount(ParserSelectByHandleByKey(p_item, 'Resources'),temp_str);
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
      [*] = ;procedure GetItemExtraName(var en : String);
      [*] = ;begin
      [*] = ;   var temp_str : String = '';
      [*] = ;   var pa : Integer;
      [*] = ;
      [*] = ;   pa := ParserSelectByHandleByKey(p_item, 'Abilities');
      [*] = ;   if pa <> 0 then
      [*] = ;   begin
      [*] = ;      pa := ParserSelectByHandleByIndex(pa, 0);
      [*] = ;      if pa <> 0 then
      [*] = ;      begin
      [*] = ;         pa := ParserGetIntValueByKeyByHandle(pa, 'Power');
      [*] = ;
      [*] = ;         case GetItemValue('ItemType') of
      [*] = ;            gc_itemtype_spell : temp_str := 'spell';
      [*] = ;            gc_itemtype_contract : temp_str := 'defender';
      [*] = ;            gc_itemtype_scheme : temp_str := 'outer_build';
      [*] = ;            gc_itemtype_ritual : temp_str := 'ritual';
      [*] = ;            gc_itemtype_innerscheme : temp_str := 'inner_build';
      [*] = ;         end;
      [*] = ;         if temp_str <> '' then
      [*] = ;            temp_str := GetLocaleTableListItemByID(temp_str, IntToStr(pa));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   en := temp_str;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsItemExists(id : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var i,cid : Integer;
      [*] = ;
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   if hero_mode < 0 then
      [*] = ;   begin
      [*] = ;      for i:=0 to gc_HeroDollSlotsCount-1 do
      [*] = ;      begin
      [*] = ;         case hero_mode of
      [*] = ;            cFT_ItemHeroHotSeat1 : cid := gHotSeatPlayer1.hero[gHotSeatPlayer1.curhero].arritems[i];
      [*] = ;            cFT_ItemHeroHotSeat2 : cid := gHotSeatPlayer2.hero[gHotSeatPlayer2.curhero].arritems[i];
      [*] = ;            cFT_ItemHeroMultiplayer : cid := gInetBattle.hero[gInetBattle.curhero].arritems[i];
      [*] = ;            cFT_ItemHeroMapEditor : cid := gEditorCustomPlayerTemporary.hero[gEditorCustomPlayerTemporary.curhero].arritems[i];
      [*] = ;            else cid := 0;
      [*] = ;         end;
      [*] = ;         if (cid=id) and (i <> gIntRegister_InetPickedItemSlot) then
      [*] = ;         begin
      [*] = ;            Result := True;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (hero_handle<>0) then
      [*] = ;      begin
      [*] = ;         var p,pa : Integer;
      [*] = ;
      [*] = ;         p := ParserSelectByHandleByKey(ParserSelectGameObject(hero_handle),'Doll');
      [*] = ;         for i:=0 to gc_HeroDollSlotsCount-1 do
      [*] = ;         begin
      [*] = ;            pa := ParserSelectByHandleByIndex(p,i);
      [*] = ;            if (not ParserGetBoolValueByKeyByHandle(pa,'Picked')) and (id = ParserGetIntValueByKeyByHandle(pa,'ItemID')) and (ParserGetIntValueByKeyByHandle(pa,'Durability') <> 0) then
      [*] = ;            begin
      [*] = ;               Result := true;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessTextWithHeader(text_hdr,text : String;do_draw: Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var tmp_pos,tmp_pos2 : TRectangle;
      [*] = ;   var temp_str,hdr : String;
      [*] = ;   var w,h,hdr_w,hdr_h : Integer;
      [*] = ;
      [*] = ;   _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;   _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;   e_x := tmp_pos.pos.x;
      [*] = ;
      [*] = ;   if text_hdr <> '' then
      [*] = ;   begin
      [*] = ;      if do_draw then temp_str := GetGUIWrappedTextFormatByFont(elem2_d.font_handle,text_hdr,total_dx)
      [*] = ;      else temp_str := text_hdr;
      [*] = ;      GetGUIElementFontTextFormatRect(elem2_d.font_handle,temp_str,w,h);
      [*] = ;      hdr := temp_str;
      [*] = ;      hdr_w := w;
      [*] = ;      hdr_h := h;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      hdr_w := 0;
      [*] = ;      hdr_h := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if do_draw then temp_str := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,total_dx)
      [*] = ;   else temp_str := text;
      [*] = ;   GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;
      [*] = ;   e_dx := Max(w,hdr_w); //Max(w,hdr_w,tmp_pos.size.w);
      [*] = ;   if do_draw then
      [*] = ;   begin
      [*] = ;      var ehd : Integer;
      [*] = ;
      [*] = ;      e_dy := h+hdr_h;
      [*] = ;      e_y := tmp_pos.pos.y;
      [*] = ;      tmp_pos.size.w := e_dx;
      [*] = ;      tmp_pos.size.h := e_dy;
      [*] = ;
      [*] = ;      if hdr_h > 0 then
      [*] = ;      begin
      [*] = ;         ehd := _gui_CreateImage_VVK('',windowHandle,gc_gui_material_blank_0,elem_d.align,tmp_pos);
      [*] = ;         _sys_FillRect(tmp_pos2,0,0,0,0);
      [*] = ;         if hdr_w < w then tmp_pos2.pos.x := ((w-hdr_w) div 2);
      [*] = ;         _gui_DWCreateText(if_handle,'header',ehd,hdr,elem_d.align,tmp_pos2,gc_gui_align_middle,elem2_d.font_handle,elem_d.color);
      [*] = ;         tmp_pos2.pos.y := hdr_h;
      [*] = ;         if hdr_w > w then tmp_pos2.pos.x := ((hdr_w-w) div 2)
      [*] = ;         else tmp_pos2.pos.x := 0;
      [*] = ;         _gui_DWCreateText(if_handle,'text',ehd,temp_str,elem_d.align,tmp_pos2,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ehd := _gui_DWCreateText(if_handle,'',windowHandle,temp_str,elem_d.align,tmp_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;      Result := ehd;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessTextString(text : String;do_draw : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   Result := ProcessTextWithHeader('',text,do_draw);
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
      [*] = ;         var rarity : Integer;
      [*] = ;
      [*] = ;         GetItemExtraName(text);
      [*] = ;         if text = '' then
      [*] = ;         begin
      [*] = ;            text := GetLocaleTableListItemByID('item', IntToStr(item_id));
      [*] = ;            rarity := GetItemValue('Rarity');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            pa := ParserSelectByHandleByKey(p_item, 'Abilities');
      [*] = ;            if pa <> 0 then
      [*] = ;            begin
      [*] = ;               pa := ParserSelectByHandleByIndex(pa, 0);
      [*] = ;               if pa <> 0 then
      [*] = ;                  pa := ParserGetIntValueByKeyByHandle(pa, 'Power');
      [*] = ;            end;
      [*] = ;            
      [*] = ;            case GetItemValue('ItemType') of
      [*] = ;               gc_itemtype_spell : begin
      [*] = ;                  pa := ParserSelectByHandleByIndex(gPrototypeData.spells.handle, pa);
      [*] = ;                  rarity := ParserGetIntValueByKeyByHandle(pa, 'Level') div 2 + 1;
      [*] = ;               end;
      [*] = ;               gc_itemtype_contract : begin
      [*] = ;                  pa := ParserSelectByHandleByIndex(gPrototypeData.defenders.handle, pa);
      [*] = ;                  var pAbilities : Integer = ParserSelectByHandleByKey(pa, 'Abilities');
      [*] = ;                  for j := ParserGetCountByHandle(pAbilities)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     p := ParserSelectByHandleByIndex(pAbilities, j);
      [*] = ;                     if ParserGetIntValueByKeyByHandle(p, 'AbilityID') = 10 then
      [*] = ;                     begin
      [*] = ;                        rarity := ParserGetIntValueByKeyByHandle(p, 'Param2');
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_itemtype_scheme : begin
      [*] = ;                  pa := ParserSelectByHandleByIndex(gPrototypeData.outerBuildings.handle, pa);
      [*] = ;                  var pAbilities : Integer = ParserSelectByHandleByKey(pa, 'Abilities');
      [*] = ;                  for j := ParserGetCountByHandle(pAbilities)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     p := ParserSelectByHandleByIndex(pAbilities, j);
      [*] = ;                     if ParserGetIntValueByKeyByHandle(p, 'AbilityID') = 8 then
      [*] = ;                     begin
      [*] = ;                        rarity := ParserGetIntValueByKeyByHandle(p, 'Param2');
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_itemtype_ritual : begin
      [*] = ;                  pa := ParserSelectByHandleByIndex(gPrototypeData.rituals.handle, pa);
      [*] = ;                  rarity := ParserGetIntValueByKeyByHandle(pa, 'ItemRarity');
      [*] = ;               end;
      [*] = ;               else
      [*] = ;                  rarity := 0;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
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
      [*] = ;            {case rarity of 
      [*] = ;                2 : elem_d.color := gc_gui_fontcolor_Rarity2;
      [*] = ;                3 : elem_d.color := gc_gui_fontcolor_Rarity3;
      [*] = ;                4 : elem_d.color := gc_gui_fontcolor_Rarity4;
      [*] = ;                5 : elem_d.color := gc_gui_fontcolor_Rarity5;
      [*] = ;                6 : elem_d.color := gc_gui_fontcolor_Rarity6;
      [*] = ;            end;}
      [*] = ;            if do_draw then
      [*] = ;               text := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,total_dx);
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle,text,w,h);
      [*] = ;
      [*] = ;            if _gui_GetInterfaceElement(if_handle,cIcon,elem2_d) then
      [*] = ;               w := w + elem2_d.p.size.w*2;
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
      [*] = ;      cCPD : begin
      [*] = ;         i := GetItemValue('ItemType');
      [*] = ;         temp_str := GetLocaleTableListItemByID('item_type', IntToStr(i));
      [*] = ;         if (i >= 0) and (i < gc_itemtype_spell) then // hack!
      [*] = ;         begin
      [*] = ;            if hero_handle <> 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := item_id;
      [*] = ;               GameObjectExecuteStateByHandle(hero_handle, 'CanUseItem');
      [*] = ;               if (not BoolRegister0) then
      [*] = ;               begin
      [*] = ;                  temp_str := '%color(attention)%'+temp_str+'%color(default)%';
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         GetItemExtraName(temp_str2);
      [*] = ;         if temp_str2 <> '' then
      [*] = ;            temp_str := temp_str+', '+temp_str2;
      [*] = ;
      [*] = ;         temp_str2 := GetLocaleTableListItemByID('item_slot', IntToStr(GetItemValue('ItemSlot')));
      [*] = ;         temp_str2 := temp_str+', '+temp_str2;
      [*] = ;
      [*] = ;         i := GetItemValue('Durability');
      [*] = ;
      [*] = ;         if i <> -1 then
      [*] = ;         begin
      [*] = ;            temp_str := GetLocaleTableListItemByID('gui', '622')+': ';
      [*] = ;            if durability = -1 then
      [*] = ;               temp_str := temp_str + IntToStr(i)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               // the actual durability is increased at the start of battle when the hero has item maintenance skill, but visually show the normal durability.
      [*] = ;               if (gIntRegister_CurGameMode = gc_GameModeTactics) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := gc_ability_item_maintenance;
      [*] = ;                  GameObjectExecuteStateByHandle(hero_handle, 'CheckAbility');
      [*] = ;                  if IntRegister1 > 0 then
      [*] = ;                     durability := Floor(durability / (100 / (100-IntRegister1)));
      [*] = ;               end;
      [*] = ;               
      [*] = ;               if (durability>i) then
      [*] = ;                  durability := i;
      [*] = ;
      [*] = ;               if (price_mode <> cFT_ItemPriceBuy) and (i > 1) then
      [*] = ;               begin
      [*] = ;                  if durability = 0 then
      [*] = ;                     temp_str := temp_str + '%color(attention)%'
      [*] = ;                  else
      [*] = ;                  if (durability < (i div 2)) then
      [*] = ;                     temp_str := temp_str + '%color(warning)%';
      [*] = ;                  temp_str := temp_str + IntToStr(durability) + '%color(default)%/';
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (i < 2) then
      [*] = ;                  temp_str := temp_str + '1/1'
      [*] = ;               else
      [*] = ;                  temp_str := temp_str + IntToStr(i);
      [*] = ;            end;
      [*] = ;            temp_str2 := temp_str2+gc_gui_BreakLine+temp_str;
      [*] = ;         end;
      [*] = ;
      [*] = ;         ProcessTextString(temp_str2,do_draw);
      [*] = ;      end;
      [*] = ;      cStatsText : begin
      [*] = ;         const cIPS = 3;
      [*] = ;
      [*] = ;         var id,p,pa,pia,i_type : Integer;
      [*] = ;         var ability_color,value : String;
      [*] = ;
      [*] = ;         i_type := GetItemValue('ItemType');
      [*] = ;         pa := ParserSelectByHandleByKey(p_item, 'Abilities');
      [*] = ;         temp_str2 := '';
      [*] = ;         for i:=0 to ParserGetCountByHandle(pa)-1 do
      [*] = ;         begin
      [*] = ;            pia := ParserSelectByHandleByIndex(pa,i);
      [*] = ;            id := ParserGetIntValueByKeyByHandle(pia,'AbilityID');
      [*] = ;            IntRegister0 := id;
      [*] = ;            MapExecuteState('GetAbilityParserByID');
      [*] = ;            p := IntRegister1;
      [*] = ;            j := ParserGetIntValueByKeyByHandle(pia, 'Power');
      [*] = ;            case ParserGetIntValueByKeyByHandle(p,'Effect') of
      [*] = ;               -1 : ability_color := 'attention';
      [*] = ;               0 :  ability_color := 'warning';
      [*] = ;               1 : begin
      [*] = ;                  if (j<0) then
      [*] = ;                     ability_color := 'attention'
      [*] = ;                  else
      [*] = ;                     ability_color := 'info';
      [*] = ;               end;
      [*] = ;               else
      [*] = ;                  ability_color := '';
      [*] = ;            end;
      [*] = ;            temp_str := '';
      [*] = ;            if ability_color <> '' then
      [*] = ;               temp_str := temp_str+'%color('+ability_color+')%';
      [*] = ;            temp_str := temp_str+GetLocaleTableListItemByID('ability',IntToStr(ParserGetIntValueByKeyByHandle(p,'Index')));
      [*] = ;
      [*] = ;            value := '';
      [*] = ;            if (id = gc_ability_summon) then
      [*] = ;               temp_str := temp_str+': '+GetLocaleTableListItemByID('unit', IntToStr(j))
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (ParserGetIntValueByKeyByHandle(p,'Numeric') > 0) then
      [*] = ;               begin
      [*] = ;                  value := IntToStr(j);
      [*] = ;                  if (j>0) then
      [*] = ;                     value := '+'+value;
      [*] = ;                  if (ParserGetIntValueByKeyByHandle(p,'Percent')>0) then
      [*] = ;                     value := value+'%';
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if value <> '' then
      [*] = ;               temp_str := temp_str+' '+value;
      [*] = ;
      [*] = ;            if (i_type < gc_itemtype_spell) and (not ParserGetBoolValueByKeyByHandle(pia,'HeroOnly')) then  // hack!
      [*] = ;               temp_str := temp_str + ' (' + GetLocaleTableListItemByID('gui', '621') +')';
      [*] = ;
      [*] = ;            if ability_color <> '' then
      [*] = ;               temp_str := temp_str + '%color(default)%';
      [*] = ;
      [*] = ;            if temp_str <> '' then
      [*] = ;               _sa_Add(temp_str2,'"'+temp_str+'"');
      [*] = ;         end;
      [*] = ;
      [*] = ;         if do_draw then w := total_dx
      [*] = ;         else w := $10000;
      [*] = ;         _gui_DWFormatTextByItems(temp_str2,'',cIPS,w,elem_d.font_handle,temp_str);
      [*] = ;         if temp_str <> '' then
      [*] = ;            ProcessTextString(temp_str,do_draw);
      [*] = ;      end;
      [*] = ;      cSetAbilities : begin
      [*] = ;         var id,pa,s_id : Integer;
      [*] = ;         var ability_color,temp_str2,set_color : String;
      [*] = ;         var c : TColorRGBA;
      [*] = ;         var no,pb,pl,pi,count,pid,idx : Integer;
      [*] = ;
      [*] = ;         _gui_GetInterfaceElement(if_handle,cSetHeaderText,elem2_d);
      [*] = ;         _gui_GetInterfaceWindowColor(if_handle,4,c);
      [*] = ;         set_color := SubStr(FormatColorToHex4(c.a,c.r,c.g,c.b),3,6);
      [*] = ;
      [*] = ;         id := ParserGetIntValueByKeyByHandle(p_item, 'ItemSetID');
      [*] = ;         IntRegister0 := id;
      [*] = ;         MapExecuteState('GetItemSetParserByID');
      [*] = ;         p := IntRegister1;
      [*] = ;
      [*] = ;         if do_draw then w := total_dx
      [*] = ;         else w := $10000;
      [*] = ;
      [*] = ;         no := 0;
      [*] = ;         pa := ParserSelectByHandleByKey(p, 'Items');
      [*] = ;         for i:=0 to ParserGetCountByHandle(pa)-1 do
      [*] = ;         begin
      [*] = ;            s_id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pa,i),'ItemID');
      [*] = ;            if IsItemExists(s_id) then
      [*] = ;               no := no+1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         pa := ParserSelectByHandleByKey(p,'Bonuses');
      [*] = ;         temp_str2 := '';
      [*] = ;         for i:=0 to ParserGetCountByHandle(pa)-1 do
      [*] = ;         begin
      [*] = ;            pb := ParserSelectByHandleByIndex(pa,i);
      [*] = ;            count := ParserGetIntValueByKeyByHandle(pb,'ItemsCount');
      [*] = ;            pl := ParserSelectByHandleByKey(pb,'BonusList');
      [*] = ;            for j:=0 to ParserGetCountByHandle(pl)-1 do
      [*] = ;            begin
      [*] = ;               pi := ParserSelectByHandleByIndex(pl,j);
      [*] = ;               id := ParserGetIntValueByKeyByHandle(pi,'AbilityID');
      [*] = ;               IntRegister0 := id;
      [*] = ;               MapExecuteState('GetAbilityParserByID');
      [*] = ;               pid := IntRegister1;
      [*] = ;               idx := ParserGetIntValueByKeyByHandle(pid,'Index');
      [*] = ;               if no >= count then
      [*] = ;                  ability_color := 'warning'
      [*] = ;               else
      [*] = ;                  ability_color := set_color;
      [*] = ;               temp_str := '%color('+ability_color+')%'+'('+IntToStr(count)+') '+GetLocaleTableListItemByID('ability',IntToStr(idx));
      [*] = ;
      [*] = ;               idx := ParserGetIntValueByKeyByHandle(pi, 'Power');
      [*] = ;               if ParserGetIntValueByKeyByHandle(pid,'Numeric') > 0 then
      [*] = ;               begin
      [*] = ;                  ability_color := IntToStr(idx);
      [*] = ;                  if idx>0 then
      [*] = ;                     ability_color := '+'+ability_color;
      [*] = ;                  if ParserGetIntValueByKeyByHandle(pid,'Percent') > 0 then
      [*] = ;                     ability_color := ability_color+'%';
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  ability_color := '';
      [*] = ;               
      [*] = ;               var wholeParty : String = '';
      [*] = ;               if (not ParserGetBoolValueByKeyByHandle(pi,'HeroOnly')) then
      [*] = ;                  wholeParty := ' (' + GetLocaleTableListItemByID('gui', '621') +')';
      [*] = ;               
      [*] = ;               if ability_color <> '' then
      [*] = ;                  temp_str := temp_str+' '+ability_color+wholeParty+'%color(default)%';
      [*] = ;               
      [*] = ;               _sa_Add(temp_str2,'"'+temp_str+'"');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         _gui_DWFormatTextByItems(temp_str2,'',3,w,elem_d.font_handle,temp_str);
      [*] = ;         if temp_str <> '' then
      [*] = ;            ProcessTextWithHeader(GetLocaleTableListItemByID('gui','72'),temp_str,do_draw);
      [*] = ;      end;
      [*] = ;      cPriceInfo : begin
      [*] = ;         var gold,gem,i_gold,i_gem,i_durability : Integer;
      [*] = ;
      [*] = ;         i_gold := GetItemValue('GoldCost');
      [*] = ;         i_gem := GetItemValue('GemCost');
      [*] = ;         i_durability := GetItemValue('Durability');
      [*] = ;         gold := 0;
      [*] = ;         gem := 0;
      [*] = ;         temp_str := '';
      [*] = ;
      [*] = ;         temp_str := '';
      [*] = ;         if (price_mode<>cFT_ItemPriceBuy) and (gBoolRegister_RepairItemMode) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := item_id;
      [*] = ;            IntRegister1 := durability;
      [*] = ;            IntRegister2 := hero_handle;
      [*] = ;            IntRegister3 := gIntRegister_MapCurrentShop;
      [*] = ;            PlayerExecuteStateByHandle(pl_handle,'GetItemRepPrice');
      [*] = ;
      [*] = ;            gold := IntRegister4;
      [*] = ;            gem := IntRegister5;
      [*] = ;
      [*] = ;            if (durability>=i_durability) then
      [*] = ;               temp_str := temp_str+GetLocaleTableListItemByID('gui', '15')
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               temp_str := temp_str+GetLocaleTableListItemByID('gui', '14') + ': ';
      [*] = ;
      [*] = ;               if gold <> 0 then
      [*] = ;               begin
      [*] = ;                  temp_str := temp_str+'%color(ignore)%'+gc_gui_GoldIconChar+'%color(warning)%'+IntToStr(gold);
      [*] = ;                  if gem <> 0 then temp_str := temp_str+'  ';
      [*] = ;               end;
      [*] = ;               if gem <> 0 then
      [*] = ;                  temp_str := temp_str+'%color(ignore)%'+gc_gui_GemIconChar+'%color(warning)%'+IntToStr(gem);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            case price_mode of
      [*] = ;               cFT_ItemPriceBase : begin
      [*] = ;                  gold := i_gold;
      [*] = ;                  gem := i_gem;
      [*] = ;                  temp_str := temp_str+GetLocaleTableListItemByID('gui', '12');
      [*] = ;               end;
      [*] = ;               cFT_ItemPriceBuy : begin
      [*] = ;                  IntRegister0 := item_id;
      [*] = ;                  IntRegister1 := hero_handle;
      [*] = ;                  IntRegister2 := gIntRegister_MapCurrentShop;
      [*] = ;                  PlayerExecuteStateByHandle(pl_handle, 'GetItemPrice');
      [*] = ;                  gold := IntRegister3;
      [*] = ;                  gem := IntRegister4;
      [*] = ;                  temp_str := temp_str+GetLocaleTableListItemByID('gui', '13');
      [*] = ;               end;
      [*] = ;               cFT_ItemPriceSell : begin
      [*] = ;                  IntRegister0 := item_id;
      [*] = ;                  IntRegister1 := durability;
      [*] = ;                  PlayerExecuteStateByHandle(pl_handle, 'GetSellItemPrice');
      [*] = ;                  gold := IntRegister2;
      [*] = ;                  gem := IntRegister3;
      [*] = ;                  temp_str := temp_str+GetLocaleTableListItemByID('gui', '675');
      [*] = ;               end;
      [*] = ;               cFT_ItemPricePoints : begin
      [*] = ;                  gold := _inet_GetItemPrice(item_id);
      [*] = ;                  temp_str := temp_str+GetLocaleTableListItemByID('menu', '197');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if price_mode=cFT_ItemPricePoints then
      [*] = ;               temp_str := temp_str+': %color(warning)%'+IntToStr(gold)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (gold>0) or (gem>0) then
      [*] = ;               begin
      [*] = ;                  var plGold : Integer = GetPlayerIntValueIndByHandle(pl_handle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;                  var plGem : Integer = GetPlayerIntValueIndByHandle(pl_handle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;                  temp_str := temp_str + ': ';
      [*] = ;                  if gold <> 0 then
      [*] = ;                  begin
      [*] = ;                     if (price_mode=cFT_ItemPriceBuy) and (plGold<gold) then
      [*] = ;                        temp_str := temp_str+'%color(ignore)%'+gc_gui_GoldIconStrokedChar+'%color(warning)%'+IntToStr(gold)
      [*] = ;                     else
      [*] = ;                        temp_str := temp_str+'%color(ignore)%'+gc_gui_GoldIconChar+'%color(warning)%'+IntToStr(gold);
      [*] = ;                     if gem <> 0 then
      [*] = ;                        temp_str := temp_str+'  ';
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if gem <> 0 then
      [*] = ;                  begin
      [*] = ;                     if (price_mode=cFT_ItemPriceBuy) and (plGem<gem) then
      [*] = ;                        temp_str := temp_str+'%color(ignore)%'+gc_gui_GemIconStrokedChar+'%color(warning)%'+IntToStr(gem)
      [*] = ;                     else
      [*] = ;                        temp_str := temp_str+'%color(ignore)%'+gc_gui_GemIconChar+'%color(warning)%'+IntToStr(gem);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  temp_str := '';
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if temp_str <> '' then
      [*] = ;         begin
      [*] = ;            ProcessTextString(temp_str,do_draw);
      [*] = ;            if (not do_draw) and _gui_GetInterfaceElement(if_handle,cIcon,elem2_d) then
      [*] = ;               e_dx := e_dx + elem2_d.p.size.w*2;
      [*] = ;         end;
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
      [*] = ;            _misc_GetItemIconNameExt(item_id,temp_str);
      [*] = ;            _gui_GetInterfaceElement(if_handle,cIconImage,elem2_d);
      [*] = ;            _sys_FillRect(tmp_pos2,_gui_ie_GetOffsetX(if_handle,cIconImage,cIcon,false),_gui_ie_GetOffsetY(if_handle,cIconImage,cIcon,false),elem2_d.p.size.w,elem2_d.p.size.h);
      [*] = ;            _gui_CreateImage_VVK('',ehd,temp_str,elem2_d.align,tmp_pos2);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cAbilities, cSetInfo: begin
      [*] = ;         var id,p,pa,pia,i_type,offs_y,s_id : Integer;
      [*] = ;         var blend : Float;
      [*] = ;
      [*] = ;         if elem_id = cSetInfo then
      [*] = ;         begin
      [*] = ;            id := ParserGetIntValueByKeyByHandle(p_item, 'ItemSetID');
      [*] = ;            IntRegister0 := id;
      [*] = ;            MapExecuteState('GetItemSetParserByID');
      [*] = ;            p := IntRegister1;
      [*] = ;            pa := ParserSelectByHandleByKey(p, 'Items');
      [*] = ;            i_type := gc_itemtype_setinfo;
      [*] = ;            no := ParserGetCountByHandle(pa)-1;
      [*] = ;            temp_str := GetLocaleTableListItemByID('item_set',IntToStr(id))
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            i_type := GetItemValue('ItemType');
      [*] = ;            pa := ParserSelectByHandleByKey(p_item, 'Abilities');
      [*] = ;            no := ParserGetCountByHandle(pa);
      [*] = ;            if no=1 then
      [*] = ;               temp_str := GetLocaleTableListItemByID('gui', 'ability')
      [*] = ;            else
      [*] = ;               temp_str := GetLocaleTableListItemByID('gui', 'ability_plural');
      [*] = ;         end;
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;
      [*] = ;         _gui_GetInterfaceElement(if_handle,cAbilityHeaderOffset,elem2_d);
      [*] = ;         offs_y := elem2_d.p.size.h;
      [*] = ;         _gui_GetInterfaceElement(if_handle,cAbilityText,elem2_d);
      [*] = ;
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,1,1);
      [*] = ;         _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;         if not do_draw then
      [*] = ;         begin
      [*] = ;            e_dx := elem_d.p.size.w*no;
      [*] = ;            if ((_gui_RootWindowGetBaseScaleY() < 1.0) ) then
      [*] = ;               e_dx := (e_dx * 3) div 4;
      [*] = ;            e_dx := max(e_dx,w);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var offs_x,pwr,value_type,i_no : Integer;
      [*] = ;
      [*] = ;            ehd := _gui_CreateImage_VVK('',windowHandle,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;            e_dx := (total_dx+elem_d.p.size.w-1) div elem_d.p.size.w;
      [*] = ;            e_dx := e_dx*elem_d.p.size.w;
      [*] = ;            if ((elem_d.p.size.w*no) > total_dx) or ((_gui_RootWindowGetBaseScaleY() < 1.0) ) then
      [*] = ;            begin
      [*] = ;               elem_d.p.size.w := (elem_d.p.size.w * 3) div 4;
      [*] = ;               elem_d.p.size.h := (elem_d.p.size.h * 3) div 4;
      [*] = ;               e_dx := (total_dx+elem_d.p.size.w-1) div elem_d.p.size.w;
      [*] = ;               e_dx := e_dx*elem_d.p.size.w;
      [*] = ;            end;
      [*] = ;            if (elem_d.p.size.w*no) < w then
      [*] = ;               offs_x := (w-(elem_d.p.size.w*no)) div 2
      [*] = ;            else
      [*] = ;               offs_x := 0;
      [*] = ;            _sys_FillRect(tmp_pos,offs_x,h+offs_y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;            e_dy := tmp_pos.pos.y;
      [*] = ;
      [*] = ;            if elem_id = cSetInfo then i_no := no + 1
      [*] = ;            else i_no := no;
      [*] = ;
      [*] = ;            for i := 0 to i_no-1 do
      [*] = ;            begin
      [*] = ;               blend := 1.0;
      [*] = ;               if elem_id = cSetInfo then
      [*] = ;               begin
      [*] = ;                  s_id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pa,i),'ItemID');
      [*] = ;                  if s_id = item_id then
      [*] = ;                     blend := 0
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if not IsItemExists(s_id) then
      [*] = ;                     begin
      [*] = ;                        //blend := 0.6;
      [*] = ;                        pwr := 0;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                        pwr := 1;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  pia := ParserSelectByHandleByIndex(pa,i);
      [*] = ;                  id := ParserGetIntValueByKeyByHandle(pia,'AbilityID');
      [*] = ;
      [*] = ;                  IntRegister0 := id;
      [*] = ;                  StateMachineExecuteState(GetMapInitMachineHandle(), 'GetAbilityParserByID', 0);
      [*] = ;                  p := IntRegister1;
      [*] = ;
      [*] = ;                  pwr := ParserGetIntValueByKeyByHandle(pia, 'Power');;
      [*] = ;                  idx := ParserGetIntValueByKeyByHandle(p, 'Index');
      [*] = ;               end;
      [*] = ;
      [*] = ;               if blend > 0 then
      [*] = ;               begin
      [*] = ;                  case i_type of
      [*] = ;                     gc_itemtype_spell : begin
      [*] = ;                        icon_name := 'icon.spell.'+IntToStr(pwr);
      [*] = ;                        _gui_ft_CreateHint_I4_S2(hint_tag,'VVK.FTooltipSpell',pwr,$20000,$20000,cFT_SpellTypeDefault,'0','0');
      [*] = ;                        value_type := 1;
      [*] = ;                     end;
      [*] = ;                     gc_itemtype_ritual: begin
      [*] = ;                        icon_name := 'icon.ritual.'+IntToStr(pwr);
      [*] = ;                        _gui_ft_CreateHint_I3(hint_tag,'VVK.HintASERCallback',cFT_ASER_Ritual,pwr,pwr);
      [*] = ;                        value_type := 1;
      [*] = ;                     end;
      [*] = ;                     gc_itemtype_setinfo: begin
      [*] = ;                        _misc_GetItemIconNameExt(s_id,icon_name);
      [*] = ;                        _gui_ft_CreateHint_I3(hint_tag,'VVK.HintASERCallback',cFT_ASER_SetItem,s_id,s_id);
      [*] = ;                        value_type := 3;
      [*] = ;                     end;
      [*] = ;                     else begin
      [*] = ;                        icon_name := 'icon.ability.'+IntToStr(idx);
      [*] = ;
      [*] = ;                        if id=gc_ability_summon then
      [*] = ;                           _gui_ft_CreateHint_I6(hint_tag,'VVK.FTooltipUnit',cFT_UnitTemplate,pwr,1,0,1,1)
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           _gui_ft_CreateHint_I4(hint_tag,'VVK.HintASERCallback',cFT_ASER_Ability,id,idx,pwr);
      [*] = ;                           if (not ParserGetBoolValueByKeyByHandle(pia,'HeroOnly')) then
      [*] = ;                              _sa_AddAsInt(hint_tag,1)
      [*] = ;                           else
      [*] = ;                              _sa_AddAsInt(hint_tag,0);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if elem_id <> cSetInfo then
      [*] = ;                  begin
      [*] = ;                     if ParserGetIntValueByKeyByHandle(p, 'Numeric') <= 0 then
      [*] = ;                        value_type := 1
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if ParserGetIntValueByKeyByHandle(p,'Percent') > 0 then
      [*] = ;                           value_type := 2
      [*] = ;                        else
      [*] = ;                           value_type := 0;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  xhd := CreateESButton(ehd,tmp_pos,elem2_d,pwr,hint_tag,icon_name,value_type,(id=gc_ability_summon));
      [*] = ;                  if blend <> 1.0 then
      [*] = ;                     SetGUIElementUserBlend(xhd,blend);
      [*] = ;                  tmp_pos.pos.x := tmp_pos.pos.x+elem_d.p.size.w;
      [*] = ;                  if ((tmp_pos.pos.x+elem_d.p.size.w) > e_dx) and (i <> (i_no-1)) then
      [*] = ;                  begin
      [*] = ;                     tmp_pos.pos.x := offs_x;
      [*] = ;                     tmp_pos.pos.y := tmp_pos.pos.y+elem_d.p.size.h;
      [*] = ;                     e_dy := e_dy+elem_d.p.size.h;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if ((elem_d.p.size.w*no) < e_dx) then
      [*] = ;               e_dx := max(w,elem_d.p.size.w*no);
      [*] = ;            _sys_FillRect(tmp_pos,0,0,e_dx,h);
      [*] = ;            xhd := _gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;            e_dy := e_dy+elem_d.p.size.h;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cPriceFull: begin
      [*] = ;         var no,id,whd,ehd,start_x : Integer;
      [*] = ;         var ret_boxes,temp_str2 : String;
      [*] = ;
      [*] = ;         GetFullPrice(temp_str2);
      [*] = ;         temp_str := GetLocaleTableListItemByID('gui', 'ritual_base_price')+': ';
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,start_x,h);
      [*] = ;         h := _gui_ft_FormatResourcesData(temp_str2,elem_d.font_handle,'warning',temp_str2,ret_boxes,do_draw);
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
      [*] = ;         //const icon_name = 'map.innerbuild.window.icon.hint.normal';
      [*] = ;         const icon_name = 'mouse.right.btn.icon.11x13';
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
      [*] = ;      cDescription : begin
      [*] = ;         var scroll_canvas_size : TElementSize;
      [*] = ;         //_log_gui('Description');
      [*] = ;         temp_str := GetLocaleTableListItemByID('item', IntToStr(item_id)+'.description');
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
      [*] = ;            ehd := _gui_CreateScrollableCanvas_VVK('item_descr_scroll',windowHandle,elem_d.align,tmp_pos,scroll_canvas_size,'map.dialog',true);
      [*] = ;            e_dx := GetGUIElementWidth(ehd);
      [*] = ;            SetGUIAllowEvents(ehd, True, False, False);
      [*] = ;            _sys_FillRect(tmp_pos,0,0,w,h);
      [*] = ;            _gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lt,elem_d.font_handle,elem_d.color);
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

