section.begin
   Name = VVK.DynamicWindowUnitCallback
   UsedFileName =
   Description : struct.begin
      [*] = ;For details please see VVK.DynamicWindowBuildingCallback
      [*] = ;Object ID - see FTooltipUnit
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;var _test_no : Integer = 12;
      [*] = ;var _test_display : Boolean = false;
      [*] = ;var _visible_stats_table : Integer = 0;
      [*] = ;
      [*] = ;const cUnitIconsOffset = 8;
      [*] = ;
      [*] = ;const cMedalOffset = $1d;
      [*] = ;const cPriceOffset = $1c;
      [*] = ;const cAbilityText = $1b;
      [*] = ;const cAbilityHeaderOffset = $1a;
      [*] = ;const cNameTextOffset = $19;
      [*] = ;
      [*] = ;const cFirstDisplayableField = $16;
      [*] = ;
      [*] = ;const cAlign = $16;
      [*] = ;const cDescription = $15;
      [*] = ;const cEffects = $14;
      [*] = ;const cAbilities = $13;
      [*] = ;const cUpkeepPrice = $12;
      [*] = ;const cStats = $11;
      [*] = ;const cHeroStats = $10;
      [*] = ;const cMedals = $f;
      [*] = ;const cLevel = $e;
      [*] = ;const cExpBar = $d;
      [*] = ;const cIcon = $c; // new format - with hire price and rank display (cIconRank)
      [*] = ;const cName = $b;
      [*] = ;// 0xa is reserved
      [*] = ;const cHeroPrice = $9;
      [*] = ;
      [*] = ;const cLastDisplayableField = $9;
      [*] = ;
      [*] = ;const cMaxResources = 6; // max resource types required for unit
      [*] = ;
      [*] = ;var e_x,e_dx,e_dy,e_y,total_dx,space_dx,space_dy,extra_dy_offset : Integer;
      [*] = ;var windowHandle : Integer;
      [*] = ;// filled in serialize
      [*] = ;var total_x,total_y : Integer;
      [*] = ;var ctxt0,ctxt1,hero_price : String;
      [*] = ;// filled in GetArguments
      [*] = ;var mode,army_p,unit_p,unit_uid,is_hero,unit_id : Integer; // if is_hero or unit_id is -1 then its status will be updated in setupinitial
      [*] = ;// saved in s0 on init
      [*] = ;var unit_handle,is_summoned,hero_handle : Integer;
      [*] = ;// calculated in unserialize
      [*] = ;var hero_parser : Integer;
      [*] = ;
      [*] = ;procedure GetHeroProperty(idx : Integer; var _res : String);
      [*] = ;begin
      [*] = ;   var res : String;
      [*] = ;
      [*] = ;   res := '0';
      [*] = ;   if (is_hero > 0) then
      [*] = ;   begin
      [*] = ;      if (mode = cFT_HeroTemplate) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;
      [*] = ;         case idx of
      [*] = ;            gc_map_hero_iLeaderProperty : i := 0;
      [*] = ;            gc_map_hero_iHealthProperty : i := 1;
      [*] = ;            gc_map_hero_iMagicProperty : i := 2;
      [*] = ;            gc_map_hero_iInitiative : i := 3;
      [*] = ;            gc_map_hero_iSiege : i := 4;
      [*] = ;            gc_map_hero_iMobility : i := 5;
      [*] = ;            else i := 6;
      [*] = ;         end;
      [*] = ;         if unit_p <> 0 then
      [*] = ;            _sa_Get(ParserGetValueByKeyByHandle(unit_p,'GoldPayment'),i,res);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (hero_handle <> 0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := idx;
      [*] = ;            IntRegister1 := 0;
      [*] = ;            GameObjectExecuteStateByHandle(hero_handle, 'GetProperty');
      [*] = ;            res :=IntToStr(IntRegister1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _res := res;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetUnitProperty(idx : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := $1000000;
      [*] = ;   if (is_hero > 0) and (mode = cFT_UnitMapHero) then // convert battle indexes to hero map indexes
      [*] = ;   begin
      [*] = ;      case idx of
      [*] = ;         gc_battle_unit_iMaxLife : idx := gc_map_hero_iLife;
      [*] = ;         gc_battle_unit_iCurLife : Result := GetGameObjectIntValueIndByHandle(hero_handle, gc_map_GOStack_MapUnit_iCurHP);
      [*] = ;         gc_battle_unit_iMaxStamina : idx := gc_map_hero_iStamina;
      [*] = ;         gc_battle_unit_iCurMoral : idx := gc_map_hero_iMoral;
      [*] = ;         gc_battle_unit_iSpeed : idx := gc_map_hero_iSpeed;
      [*] = ;         gc_battle_unit_iAttack : idx := gc_map_hero_iAttack;
      [*] = ;         gc_battle_unit_iCounterAttack : idx := gc_map_hero_iCounterAttack;
      [*] = ;         gc_battle_unit_iDefence : idx := gc_map_hero_iDefence;
      [*] = ;         gc_battle_unit_iRangedDefence : idx := gc_map_hero_iRangedDefence;
      [*] = ;         gc_battle_unit_iResist : idx := gc_map_hero_iResist;
      [*] = ;         gc_battle_unit_iRangedAttack : idx := gc_map_hero_iRangedAttack;
      [*] = ;         gc_battle_unit_iShootingRange : idx := gc_map_hero_iShootingRange;
      [*] = ;         gc_battle_unit_iMaxAmmo : idx := gc_map_hero_iAmmo;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if Result = $1000000 then
      [*] = ;   begin
      [*] = ;      if (unit_handle <> 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := idx;
      [*] = ;         IntRegister1 := 0;
      [*] = ;         GameObjectExecuteStateByHandle(unit_handle, 'GetProperty');
      [*] = ;         Result := IntRegister1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := unit_p;
      [*] = ;         IntRegister1 := army_p;
      [*] = ;         IntRegister2 := idx;
      [*] = ;         IntRegister3 := 0;
      [*] = ;         MapExecuteState('GetUnitPropertyByParser');
      [*] = ;         Result := IntRegister3;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetExperience() : Integer;
      [*] = ;begin
      [*] = ;   var ce : Integer;
      [*] = ;
      [*] = ;   if unit_handle <> 0 then
      [*] = ;   begin
      [*] = ;      if mode = cFT_UnitBattle then
      [*] = ;         ce := GetGameObjectIntValueIndByHandle(unit_handle, gc_stack_unit_iExperience)
      [*] = ;      else
      [*] = ;         ce := GetGameObjectIntValueIndByHandle(unit_handle, gc_map_GOStack_MapUnit_iExp);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (mode <> cFT_UnitTemplate) and (mode <> cFT_HeroTemplate) then
      [*] = ;         ce := ParserGetIntValueByKeyByHandle(unit_p,'Exp')
      [*] = ;      else
      [*] = ;         ce := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := ce;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetLevel() : Integer;
      [*] = ;begin
      [*] = ;   if unit_handle <> 0 then
      [*] = ;   begin
      [*] = ;      if mode = cFT_UnitBattle then
      [*] = ;         Result := GetGameObjectIntValueIndByHandle(unit_handle, gc_stack_unit_iLevel)
      [*] = ;      else
      [*] = ;         Result := GetGameObjectIntValueIndByHandle(unit_handle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := ParserGetIntValueByKeyByHandle(unit_p, 'Level');
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateESButton(ehd : Integer;pos : TRectangle;elem2_d : TInterfaceElementData;value : Integer;hint,icon_name : String) : Integer;
      [*] = ;begin
      [*] = ;   var whd,xhd,w,h : Integer;
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;
      [*] = ;   _sys_FillRect(tmp_pos,0,0,pos.size.w,pos.size.h);
      [*] = ;   xhd := _gui_CreateImage_VVK('',ehd,icon_name,gc_gui_align_parent_lt,pos);
      [*] = ;   SetGUIAllowEvents(xhd, True, False, False);
      [*] = ;   SetGUIElementHint(xhd,hint);
      [*] = ;   //whd := _gui_CreateButton_VVK('',xhd,'','heropanel.icon.52x52.slot.cover',gc_gui_align_parent_lt,tmp_pos,'',temp_str,0);
      [*] = ;   if ((value and $10000) = 0) then
      [*] = ;   begin
      [*] = ;      var temp_str : String;
      [*] = ;
      [*] = ;      temp_str := IntToStr(value);
      [*] = ;      GetGUIElementFontTextFormatRect(elem2_d.font_handle,temp_str,w,h);
      [*] = ;      _sys_FillRect(tmp_pos,pos.size.w-(w+2+1),pos.size.h-(h+2+1),w+2,h+2);
      [*] = ;      whd  := _gui_CreateImage_VVK('',xhd,'pixel.0.0.0',gc_gui_align_parent_lt,tmp_pos);
      [*] = ;      _gui_CreateText_VVK('',xhd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lt,elem2_d.font_handle,elem2_d.color);
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
      [*] = ;         cUpkeepPrice : begin
      [*] = ;            if (is_hero <> 0) then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;         cHeroPrice : begin
      [*] = ;            if (hero_price = '') then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;         cHeroStats: begin
      [*] = ;            if (is_hero = 0) then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;         cMedals : begin
      [*] = ;            var p : Integer;
      [*] = ;
      [*] = ;            if unit_handle <> 0 then
      [*] = ;               p := ParserSelectGameObject(unit_handle)
      [*] = ;            else
      [*] = ;               p := unit_p;
      [*] = ;
      [*] = ;            p := ParserSelectByHandleByKey(p,'Medals');
      [*] = ;            if (ParserGetCountByHandle(p) = 0) and (not _test_display) then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;         cLevel : begin
      [*] = ;            var l : Integer;
      [*] = ;
      [*] = ;            if unit_handle <> 0 then
      [*] = ;               l := GetGameObjectIntValueIndByHandle(unit_handle, gc_stack_unit_iLevel)
      [*] = ;            else
      [*] = ;               l := ParserGetIntValueByKeyByHandle(unit_p, 'Level');
      [*] = ;
      [*] = ;            if l=0 then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;         cExpBar : begin
      [*] = ;            if GetExperience()=0 then
      [*] = ;               Result := false;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetupInitial(template_id: Integer; var s0 : String; var s1 : String);
      [*] = ;begin
      [*] = ;   hero_handle := 0;
      [*] = ;   is_summoned := 0;
      [*] = ;   case mode of
      [*] = ;      cFT_UnitTemplate : begin
      [*] = ;         unit_handle := 0;
      [*] = ;      end;
      [*] = ;      cFT_UnitMapArmy : begin
      [*] = ;         if unit_id = -1 then
      [*] = ;            unit_id := ParserGetIntValueByKeyByHandle(unit_p, 'UnitID');
      [*] = ;         unit_handle := 0;
      [*] = ;      end;
      [*] = ;      cFT_UnitMapHero : begin
      [*] = ;         is_hero := 1;
      [*] = ;         unit_handle := GetGameObjectHandleByUniqueId(unit_uid);
      [*] = ;         if unit_id = -1 then
      [*] = ;            unit_id := GetGameObjectIntValueIndByHandle(unit_handle, gc_stack_unit_iUnitID);
      [*] = ;         hero_handle := unit_handle;
      [*] = ;      end;
      [*] = ;      cFT_UnitBattle : begin
      [*] = ;         var uid : Integer;
      [*] = ;
      [*] = ;         unit_handle := GetGameObjectHandleByUniqueId(unit_uid);
      [*] = ;         if unit_id = -1 then
      [*] = ;            unit_id := GetGameObjectIntValueIndByHandle(unit_handle, gc_stack_unit_iUnitID);
      [*] = ;         if GetGameObjectBoolValueIndByHandle(unit_handle, gc_stack_unit_bSummoned) then
      [*] = ;            is_summoned := 1
      [*] = ;         else
      [*] = ;            is_summoned := 0;
      [*] = ;         if is_hero=-1 then
      [*] = ;         begin
      [*] = ;            if GetGameObjectBoolValueIndByHandle(unit_handle, gc_stack_unit_bIsHero) then
      [*] = ;               is_hero := 1
      [*] = ;            else
      [*] = ;               is_hero := 0;
      [*] = ;         end;
      [*] = ;
      [*] = ;         uid := GetGameObjectIntValueIndByHandle(unit_handle,gc_stack_unit_iHeroUID);
      [*] = ;         if (uid<>0) then
      [*] = ;            hero_handle := GetGameObjectHandleByUniqueId(uid);
      [*] = ;      end;
      [*] = ;      cFT_HeroTemplate : begin
      [*] = ;         is_hero := 1;
      [*] = ;         hero_handle := 0;
      [*] = ;         unit_handle := 0;
      [*] = ;      end;
      [*] = ;      cFT_UnitAstralHero : begin
      [*] = ;         is_hero := 0;
      [*] = ;         hero_handle := 0;
      [*] = ;         unit_handle := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   s0 := '';
      [*] = ;   _sa_AddAsInt(s0,unit_id);
      [*] = ;   _sa_AddAsInt(s0,is_hero);
      [*] = ;   _sa_AddAsInt(s0,is_summoned);
      [*] = ;   _sa_AddAsInt(s0,unit_handle);
      [*] = ;   _sa_AddAsInt(s0,hero_handle);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UnserializeData(s0 : String;v : String);
      [*] = ;begin
      [*] = ;   unit_id := _sa_GetAsInt(s0,0);
      [*] = ;   is_hero := _sa_GetAsInt(s0,1);
      [*] = ;   is_summoned := _sa_GetAsInt(s0,2);
      [*] = ;   unit_handle := _sa_GetAsInt(s0,3);
      [*] = ;   hero_handle := _sa_GetAsInt(s0,4);
      [*] = ;   if hero_handle <> 0 then
      [*] = ;      hero_parser := ParserSelectGameObject(hero_handle)
      [*] = ;   else
      [*] = ;      hero_parser := 0;
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
      [*] = ;procedure ProcessElement(elem_id, if_handle: Integer;do_draw : Boolean);
      [*] = ;begin
      [*] = ;   var elem_d,elem2_d : TInterfaceElementData;
      [*] = ;   var i,j,k,ehd,p,pa,no,xhd,idx : Integer;
      [*] = ;   var stackable : Boolean;
      [*] = ;   var w,h : Integer;
      [*] = ;   var temp_str,hint_tag,icon_name,hint : String;
      [*] = ;   var tmp_pos : TRectangle;
      [*] = ;   var abil : array [0..$100] of Integer;
      [*] = ;   var txt : array [0..$20] of String;
      [*] = ;
      [*] = ;   _gui_DWGetElement(elem_id,if_handle,elem_d);
      [*] = ;
      [*] = ;   case elem_id of
      [*] = ;      cName : begin
      [*] = ;         const cTexHeaderStripe = 'map.generic.window.header';
      [*] = ;
      [*] = ;         var text : String;
      [*] = ;
      [*] = ;         if (is_hero <> 0) then
      [*] = ;         begin
      [*] = ;            if hero_handle <> 0 then
      [*] = ;               _hero_GetName(hero_handle,text)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if mode = cFT_HeroTemplate then
      [*] = ;                  text := GetLocaleTableListItemByID('hero_class', IntToStr(unit_id-39))
      [*] = ;               else
      [*] = ;                  text := '???';
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            text := GetLocaleTableListItemByID('unit', IntToStr(unit_id));
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
      [*] = ;      cAlign : begin
      [*] = ;         var text : String;
      [*] = ;         var if_handle_c,hero_class : Integer;
      [*] = ;         var text_c : TColorRGBA;
      [*] = ;
      [*] = ;         if_handle_c := _gui_GetInterfaceWindowHandle('unit_details_colors');
      [*] = ;         if (is_hero <> 0) then
      [*] = ;         begin
      [*] = ;            if hero_handle <> 0 then
      [*] = ;            begin
      [*] = ;               GameObjectExecuteStateByHandle(hero_handle, 'GetClass');
      [*] = ;               hero_class := IntRegister0;
      [*] = ;               text := GetLocaleTableListItemByID('hero_class',IntToStr(hero_class));
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if mode = cFT_HeroTemplate then
      [*] = ;                  text := GetLocaleTableListItemByID('gui','hireunit.approx')
      [*] = ;               else
      [*] = ;                  text := '????';
      [*] = ;            end;
      [*] = ;            _gui_GetInterfaceWindowColor(if_handle_c,3,text_c);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            i := ParserGetIntValueByKeyByHandle(_unit_GetUnitParserByID(unit_id), 'Karma');
      [*] = ;            if i > 0 then
      [*] = ;               _gui_GetInterfaceWindowColor(if_handle_c,2,text_c)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if i < 0 then
      [*] = ;                  _gui_GetInterfaceWindowColor(if_handle_c,0,text_c)
      [*] = ;               else
      [*] = ;                  _gui_GetInterfaceWindowColor(if_handle_c,1,text_c);
      [*] = ;            end;
      [*] = ;            text := GetLocaleTableListItemByID('gui', IntToStr(300+3+i));
      [*] = ;         end;
      [*] = ;
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         if do_draw then
      [*] = ;            text := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,total_dx);
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,text,w,h);
      [*] = ;
      [*] = ;         e_dx := Max(w,tmp_pos.size.w);
      [*] = ;         tmp_pos.size.w := e_dx;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            tmp_pos.size.h := h;
      [*] = ;            ehd := _gui_CreateText_VVK('align',windowHandle,text,elem_d.align,tmp_pos,gc_gui_align_middle,elem_d.font_handle,text_c);
      [*] = ;            if is_hero <> 0 then
      [*] = ;            begin
      [*] = ;               var tmp_pos2 : TRectangle;
      [*] = ;
      [*] = ;               _sys_FillRect(tmp_pos2,0,0,GetGUIElementWidth(ehd),GetGUIElementHeight(ehd));
      [*] = ;               ehd := _gui_CreateButton_VVK('',ehd,''gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos2,'','',0);
      [*] = ;               _gui_ft_AttachHint_I2(ehd,'VVK.HintHeroClassCallback',hero_class,GetGameObjectUniqueIdByHandle(hero_handle));
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               SetGUIAllowEvents(ehd, True, False, False);
      [*] = ;               SetGUIElementHint(ehd,'hint|7|256');
      [*] = ;            end;
      [*] = ;            e_dy := h;
      [*] = ;            e_y := tmp_pos.pos.y;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cDescription : begin
      [*] = ;         var scroll_canvas_size : TElementSize;
      [*] = ;
      [*] = ;         if mode = cFT_HeroTemplate then
      [*] = ;            temp_str := GetLocaleTableListItemByID('gui', 'hireunit.'+IntToStr(unit_id-39))
      [*] = ;         else
      [*] = ;            temp_str := GetLocaleTableListItemByID('unit', IntToStr(unit_id)+'.description');
      [*] = ;         if _test_display then
      [*] = ;            temp_str := temp_str + gc_gui_BreakLine + temp_str + gc_gui_BreakLine + temp_str + gc_gui_BreakLine + temp_str;
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
      [*] = ;            ehd := _gui_CreateScrollableCanvas_VVK('unit_descr_scroll',windowHandle,elem_d.align,tmp_pos,scroll_canvas_size,'map.dialog',true);
      [*] = ;            e_dx := GetGUIElementWidth(ehd);
      [*] = ;            SetGUIAllowEvents(ehd, True, False, False);
      [*] = ;            _sys_FillRect(tmp_pos,0,0,w,h);
      [*] = ;            _gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lt,elem_d.font_handle,elem_d.color);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cEffects, cAbilities : begin
      [*] = ;         if _test_display then
      [*] = ;         begin
      [*] = ;            if elem_id = cAbilities then
      [*] = ;            begin
      [*] = ;               for i := 0 to _test_no-1 do
      [*] = ;                  abil[i] := i+13;
      [*] = ;               no := _test_no;
      [*] = ;            end;
      [*] = ;            no := _test_no;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            no := 0;
      [*] = ;            if elem_id = cEffects then
      [*] = ;            begin
      [*] = ;               if unit_handle <> 0 then
      [*] = ;                  p := ParserSelectGameObject(unit_handle)
      [*] = ;               else
      [*] = ;                  p := unit_p;
      [*] = ;
      [*] = ;               p := ParserSelectByHandleByKey(p,'Effects');
      [*] = ;
      [*] = ;               for i := 0 to ParserGetCountByHandle(p)-1 do
      [*] = ;               begin
      [*] = ;                  pa := ParserSelectByHandleByIndex(p,i);
      [*] = ;                  if (ParserGetBoolValueByKeyByHandle(pa, 'Visible')) and ((ParserGetIntValueByKeyByHandle(pa,'ParentUpgradeID') > 0) or (ParserGetIntValueByKeyByHandle(pa, 'ParentSpellID') > 0)) then
      [*] = ;                  begin
      [*] = ;                     abil[no] := pa;
      [*] = ;                     no := no+1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if is_summoned <> 0 then
      [*] = ;               begin
      [*] = ;                  abil[0] := gc_ability_summoned;
      [*] = ;                  no := 1;
      [*] = ;               end;
      [*] = ;
      [*] = ;               for i := 0 to ParserGetCountByHandle(gPrototypeData.abilities.handle)-1 do
      [*] = ;               begin
      [*] = ;                  pa := ParserSelectByHandleByIndex(gPrototypeData.abilities.handle,i);
      [*] = ;                  j := ParserGetIntValueByKeyByHandle(pa, 'AbilityID');
      [*] = ;
      [*] = ;                  if (ParserGetBoolValueByKeyByHandle(pa, 'Visible')) and (j <> gc_ability_summoned) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := j;
      [*] = ;                     StateMachineExecuteState(GetMapInitMachineHandle(), 'GetAbilityParserByID', 0);
      [*] = ;                     pa := IntRegister1;
      [*] = ;
      [*] = ;                     if unit_handle <> 0 then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := j;
      [*] = ;                        GameObjectExecuteStateByHandle(unit_handle, 'CheckAbility');
      [*] = ;                        k := IntRegister1;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := 0;
      [*] = ;                        IntRegister1 := unit_p;
      [*] = ;                        IntRegister2 := hero_handle;
      [*] = ;                        IntRegister3 := j;
      [*] = ;                        MapExecuteState('CheckUnitAbility');
      [*] = ;                        k := IntRegister4;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if k > 0 then
      [*] = ;                     begin
      [*] = ;                        abil[no] := j;
      [*] = ;                        no := no+1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if no > 0 then
      [*] = ;         begin
      [*] = ;            var offs_y : Integer;
      [*] = ;
      [*] = ;            _gui_GetInterfaceElement(if_handle,cAbilityHeaderOffset,elem2_d);
      [*] = ;            offs_y := elem2_d.p.size.h;
      [*] = ;            _gui_GetInterfaceElement(if_handle,cAbilityText,elem2_d);
      [*] = ;
      [*] = ;            if elem_id = cEffects then
      [*] = ;               temp_str := GetLocaleTableListItemByID('gui', '85')
      [*] = ;            else
      [*] = ;               temp_str := GetLocaleTableListItemByID('gui', '84');
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;
      [*] = ;            _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,1,1);
      [*] = ;            stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;            e_x := tmp_pos.pos.x;
      [*] = ;            e_y := tmp_pos.pos.y;
      [*] = ;            if not do_draw then
      [*] = ;            begin
      [*] = ;               e_dx := elem_d.p.size.w*no;
      [*] = ;               if _gui_RootWindowGetBaseScaleY() < 1.0 then
      [*] = ;                  e_dx := (e_dx * 3) div 4;
      [*] = ;               e_dx := max(e_dx,w);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var offs_x : Integer;
      [*] = ;
      [*] = ;               ehd := _gui_CreateImage_VVK('',windowHandle,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;               e_dx := (total_dx+elem_d.p.size.w-1) div elem_d.p.size.w;
      [*] = ;               e_dx := e_dx*elem_d.p.size.w;
      [*] = ;               if ((elem_d.p.size.w*no) > total_dx) or (_gui_RootWindowGetBaseScaleY() < 1.0) then
      [*] = ;               begin
      [*] = ;                  elem_d.p.size.w := (elem_d.p.size.w * 3) div 4;
      [*] = ;                  elem_d.p.size.h := (elem_d.p.size.h * 3) div 4;
      [*] = ;                  e_dx := (total_dx+elem_d.p.size.w-1) div elem_d.p.size.w;
      [*] = ;                  e_dx := e_dx*elem_d.p.size.w;
      [*] = ;               end;
      [*] = ;               if (elem_d.p.size.w*no) < w then
      [*] = ;                  offs_x := (w-(elem_d.p.size.w*no)) div 2
      [*] = ;               else
      [*] = ;                  offs_x := 0;
      [*] = ;               _sys_FillRect(tmp_pos,offs_x,h+offs_y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;               e_dy := tmp_pos.size.h;
      [*] = ;               for i := 0 to no-1 do
      [*] = ;               begin
      [*] = ;                  if elem_id = cEffects then
      [*] = ;                  begin
      [*] = ;                     if _test_display then
      [*] = ;                     begin
      [*] = ;                        var ht : Integer;
      [*] = ;
      [*] = ;                        IntRegister0 := i+1;
      [*] = ;                        MapExecuteState('GetEffectParserByID');
      [*] = ;                        pa := IntRegister1;
      [*] = ;                        k := ParserGetIntValueByKeyByHandle(pa, 'AbilityID');
      [*] = ;                        if k <> 0 then
      [*] = ;                        begin
      [*] = ;                           icon_name := 'icon.skill.' + IntToStr(i+1);
      [*] = ;                           ht := cFT_ASER_Effect;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           k := ParserGetIntValueByKeyByHandle(pa, 'SpellID');
      [*] = ;                           icon_name := 'icon.spell.' + IntToStr(i+1);
      [*] = ;                           ht := cFT_ASER_EffectSpell;
      [*] = ;                        end;
      [*] = ;                        _gui_ft_CreateHint_I5(hint_tag,'VVK.HintASERCallback',ht,i+1,k,i+2,i mod 2);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        pa := abil[i];
      [*] = ;                        IntRegister0 := pa;
      [*] = ;                        MapExecuteState('bat.GetEffectIDByParser');
      [*] = ;                        idx := IntRegister1;
      [*] = ;
      [*] = ;                        k := ParserGetIntValueByKeyByHandle(pa, 'ParentUpgradeID');
      [*] = ;                        if k > 0 then
      [*] = ;                        begin
      [*] = ;                           icon_name := 'icon.skill.' + IntToStr(k);
      [*] = ;                           _gui_ft_CreateHint_I4(hint_tag,'VVK.HintASERCallback',cFT_ASER_Effect,idx,k,ParserGetIntValueByKeyByHandle(pa, 'Power'));
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           k := ParserGetIntValueByKeyByHandle(pa, 'ParentSpellID');
      [*] = ;                           icon_name := 'icon.spell.' + IntToStr(k);
      [*] = ;                           _gui_ft_CreateHint_I4(hint_tag,'VVK.HintASERCallback',cFT_ASER_EffectSpell,idx,k,0);
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        k := ParserGetIntValueByKeyByHandle(pa, 'Duration');
      [*] = ;                        _sa_AddAsInt(hint_tag,k);
      [*] = ;                     end;
      [*] = ;                     if k <= 0 then
      [*] = ;                        k := $10000;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := abil[i];
      [*] = ;                     StateMachineExecuteState(GetMapInitMachineHandle(), 'GetAbilityParserByID', 0);
      [*] = ;                     pa := IntRegister1;
      [*] = ;
      [*] = ;                     if _test_display then
      [*] = ;                     begin
      [*] = ;                        if ((i and 1) <> 0) then
      [*] = ;                           k := 14
      [*] = ;                        else
      [*] = ;                           k := 0;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if unit_handle <> 0 then
      [*] = ;                        begin
      [*] = ;                           IntRegister0 := abil[i];
      [*] = ;                           GameObjectExecuteStateByHandle(unit_handle, 'CheckAbility');
      [*] = ;                           k := IntRegister1;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           IntRegister0 := 0;
      [*] = ;                           IntRegister1 := unit_p;
      [*] = ;                           IntRegister2 := hero_handle;
      [*] = ;                           IntRegister3 := abil[i];
      [*] = ;                           MapExecuteState('CheckUnitAbility');
      [*] = ;                           k := IntRegister4;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     idx := ParserGetIntValueByKeyByHandle(pa, 'Index');
      [*] = ;                     icon_name := 'icon.ability.'+IntToStr(idx);
      [*] = ;                     _gui_ft_CreateHint_I5(hint_tag,'VVK.HintASERCallback',cFT_ASER_Ability,abil[i],idx,k,0);
      [*] = ;                     if ParserGetIntValueByKeyByHandle(pa, 'Numeric') <= 0 then
      [*] = ;                        k := k or $10000;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  xhd := CreateESButton(ehd,tmp_pos,elem2_d,k,hint_tag,icon_name);
      [*] = ;                  tmp_pos.pos.x := tmp_pos.pos.x+elem_d.p.size.w;
      [*] = ;                  if ((tmp_pos.pos.x+elem_d.p.size.w) > e_dx) and (i <> (no-1)) then
      [*] = ;                  begin
      [*] = ;                     tmp_pos.pos.x := offs_x;
      [*] = ;                     tmp_pos.pos.y := tmp_pos.pos.y+elem_d.p.size.h;
      [*] = ;                     e_dy := e_dy+elem_d.p.size.h;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if ((elem_d.p.size.w*no) < e_dx) then
      [*] = ;                  e_dx := max(w,elem_d.p.size.w*no);
      [*] = ;               _sys_FillRect(tmp_pos,0,0,e_dx,h);
      [*] = ;               xhd := _gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;               e_dy := e_dy+elem_d.p.size.h;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cUpkeepPrice,cHeroPrice : begin
      [*] = ;         var pt,hh,hw,offs_y : Integer;
      [*] = ;         var g_p : array [0..$10] of Integer;
      [*] = ;         var dx : array [0..$10] of Integer;
      [*] = ;         var dy : array [0..$10] of Integer;
      [*] = ;         var str : array [0..$10] of String;
      [*] = ;         var tex_str : array [0..$10] of String;
      [*] = ;         var tex_dx : array [0..$10] of Integer;
      [*] = ;         var tmp_pos2 : TRectangle;
      [*] = ;         var hdr_str : String;
      [*] = ;
      [*] = ;         _gui_GetInterfaceElement(if_handle,cAbilityHeaderOffset,elem2_d);
      [*] = ;
      [*] = ;         if elem_id = cUpkeepPrice then
      [*] = ;            hdr_str := GetLocaleTableListItemByID('gui', 'unit_upkeep')
      [*] = ;         else
      [*] = ;            hdr_str := GetLocaleTableListItemByID('gui', 'hero_cost');
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,hdr_str,hw,hh);
      [*] = ;         offs_y := elem2_d.p.size.h+hh;
      [*] = ;
      [*] = ;         pt := _unit_GetUnitParserByID(unit_id);
      [*] = ;         if (unit_p = 0) then
      [*] = ;            p := pt
      [*] = ;         else
      [*] = ;            p := unit_p;
      [*] = ;
      [*] = ;         if elem_id = cUpkeepPrice then
      [*] = ;         begin
      [*] = ;            IntRegister0 := p;
      [*] = ;            IntRegister1 := hero_handle;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            MapExecuteState('GetUnitPaymentByParser');
      [*] = ;            g_p[0] := IntRegister2;
      [*] = ;            g_p[1] := IntRegister3;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            g_p[0] := _sa_GetAsInt(hero_price,0);
      [*] = ;            g_p[1] := _sa_GetAsInt(hero_price,1);
      [*] = ;         end;
      [*] = ;
      [*] = ;         tex_str[0] := 'map.infopanel.gold';
      [*] = ;         tex_str[1] := 'map.infopanel.crystals';
      [*] = ;
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;
      [*] = ;         for i:=0 to 1 do
      [*] = ;         begin
      [*] = ;            dx[i] := GetGUITextureWidth(tex_str[i]);
      [*] = ;            dy[i] := GetGUITextureHeight(tex_str[i]);
      [*] = ;            tex_dx[i] := dx[i];
      [*] = ;            if (g_p[i]<>0) then
      [*] = ;            begin
      [*] = ;               str[i] := IntToStr(g_p[i]);
      [*] = ;               GetGUIElementFontTextFormatRect(elem_d.font_handle,str[i],w,h);
      [*] = ;               dx[i] := dx[i]+w;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               str[i] := '';
      [*] = ;         end;
      [*] = ;
      [*] = ;         if elem_d.scalable <> 0 then
      [*] = ;         begin
      [*] = ;            e_dx := max(dx[0],dx[1]);
      [*] = ;            e_dy := dy[0]+dy[1];
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            e_dx := dx[0]+dx[1]+space_dx;
      [*] = ;            e_dy := max(dy[0],dy[1]);
      [*] = ;         end;
      [*] = ;         e_dx := max(hw,e_dx);
      [*] = ;         e_dy := e_dy+offs_y;
      [*] = ;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            _gui_GetInterfaceElement(if_handle,cPriceOffset,elem2_d);
      [*] = ;
      [*] = ;            tmp_pos.size.w := e_dx;
      [*] = ;            tmp_pos.size.h := e_dy;
      [*] = ;            ehd := _gui_CreateImage_VVK('',windowHandle,gc_gui_material_blank_0,elem_d.align,tmp_pos);
      [*] = ;            tmp_pos.pos.x := 0;
      [*] = ;            tmp_pos.pos.y := offs_y;
      [*] = ;            for i:=0 to 1 do
      [*] = ;            begin
      [*] = ;               if (g_p[i]=0) then
      [*] = ;                  continue;
      [*] = ;
      [*] = ;               if elem_d.scalable <> 0 then
      [*] = ;                  tmp_pos.size.w := e_dx
      [*] = ;               else
      [*] = ;                  tmp_pos.size.w := dx[i];
      [*] = ;               tmp_pos.size.h := dy[i];
      [*] = ;               temp_str := GetLocaleTableListItemByID('gui',IntToStr(712+i));
      [*] = ;               j := _gui_CreateButton_VVK('',ehd,''gc_gui_material_blank_0,elem_d.align,tmp_pos,'',temp_str,0);
      [*] = ;               SetGUIElementEnabled(j,false);
      [*] = ;               SetGUIElementVisibleProperties(j,'DisabledProperty',gc_gui_material_blank_0, 0, 0, 0, 0, 1, 1, 1, 1, 1);
      [*] = ;               if elem_d.scalable <> 0 then
      [*] = ;                  _sys_FillRect(tmp_pos2,tmp_pos.pos.x,tmp_pos.pos.y,0,0)
      [*] = ;               else
      [*] = ;                  _sys_FillRect(tmp_pos2,tmp_pos.pos.x,tmp_pos.pos.y+((e_dy-dy[i]) div 2),0,0);
      [*] = ;               j:=_gui_CreateImage_VVK('',ehd,tex_str[i],gc_gui_align_parent_lt,tmp_pos2);
      [*] = ;               if (g_p[i]=0) then
      [*] = ;                  SetGUIElementUserBlend(j,0.35);
      [*] = ;               j := tmp_pos2.pos.x;
      [*] = ;               tmp_pos2.pos.x := tmp_pos2.pos.x+tex_dx[i];
      [*] = ;               tmp_pos2.size.h := dy[i];
      [*] = ;               _gui_CreateText_VVK('',ehd,str[i],gc_gui_align_parent_lt,tmp_pos2,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;               _sys_FillRect(tmp_pos2,j-(elem2_d.p.size.w div 2),tmp_pos2.pos.y+dy[i]-(elem2_d.p.size.h div 1),elem2_d.p.size.w,elem2_d.p.size.h);
      [*] = ;               j:=_gui_CreateImage_VVK('',ehd,'astral.beforebattle.curenergy.sign',gc_gui_align_parent_lt,tmp_pos2);
      [*] = ;               if (g_p[i]=0) then
      [*] = ;                  SetGUIElementUserBlend(j,0.5);
      [*] = ;
      [*] = ;               if elem_d.scalable <> 0 then
      [*] = ;                  tmp_pos.pos.y := tmp_pos.pos.y+dy[i]
      [*] = ;               else
      [*] = ;                  tmp_pos.pos.x := tmp_pos.pos.x+dx[i]+space_dx;
      [*] = ;            end;
      [*] = ;            _sys_FillRect(tmp_pos2,0,0,e_dx,hh);
      [*] = ;            _gui_CreateText_VVK('',ehd,hdr_str,gc_gui_align_parent_lt,tmp_pos2,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cStats,cHeroStats : begin
      [*] = ;         var stats_str,a_str : String;
      [*] = ;         var max_w,sym_w,rows_no,w3,a_idx : Integer;
      [*] = ;         var tmp_pos2 : TRectangle;
      [*] = ;         var table_style : Integer;
      [*] = ;
      [*] = ;         if _visible_stats_table <> 0 then
      [*] = ;            table_style := gc_gui_TableStyleBorder
      [*] = ;         else
      [*] = ;            table_style := gc_gui_TableStyleOpaque;
      [*] = ;
      [*] = ;         if elem_id=cStats then
      [*] = ;            stats_str := 'PQRSTUVWXYZ['
      [*] = ;         else
      [*] = ;            stats_str := '8;9<:=';
      [*] = ;         j := StrLength(stats_str);
      [*] = ;         max_w := 0;
      [*] = ;         for i := 0 to j-1 do
      [*] = ;         begin
      [*] = ;            temp_str := SubStr(stats_str,i+1,1);
      [*] = ;            case temp_str of
      [*] = ;               'P': begin
      [*] = ;                  if _test_display then txt[i] := '1999/2000'
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iMaxLife));
      [*] = ;                     if (mode <> cFT_UnitTemplate) and (mode <> cFT_HeroTemplate) then txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iCurLife))+'/'+txt[i];
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               'Q': begin   // stamina
      [*] = ;                  txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iMaxStamina));
      [*] = ;                  if mode = cFT_UnitBattle then txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iCurStamina)) +'/'+txt[i];
      [*] = ;               end;
      [*] = ;               'R': txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iCurMoral));
      [*] = ;               'S': begin
      [*] = ;                  txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iSpeed));
      [*] = ;                  if mode = cFT_UnitBattle then txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iMovePoints)) +'/'+txt[i];
      [*] = ;               end;
      [*] = ;               'T': txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iAttack));
      [*] = ;               'U': txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iCounterAttack));
      [*] = ;               'V': txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iDefence));
      [*] = ;               'W': txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iRangedDefence));
      [*] = ;               'X': txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iResist));
      [*] = ;               'Y': txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iRangedAttack));
      [*] = ;               'Z': txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iShootingRange));
      [*] = ;               '[': begin   // ammo
      [*] = ;                  txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iMaxAmmo));
      [*] = ;                  if mode = cFT_UnitBattle then txt[i] := IntToStr(GetUnitProperty(gc_battle_unit_iCurAmmo)) +'/'+txt[i];
      [*] = ;               end;
      [*] = ;               '8': GetHeroProperty(gc_map_hero_iLeaderProperty,txt[i]);
      [*] = ;               '9': GetHeroProperty(gc_map_hero_iHealthProperty,txt[i]);
      [*] = ;               ':': GetHeroProperty(gc_map_hero_iMagicProperty,txt[i]);
      [*] = ;               '<': GetHeroProperty(gc_map_hero_iInitiative,txt[i]);
      [*] = ;               ';': GetHeroProperty(gc_map_hero_iSiege,txt[i]);
      [*] = ;               '=': begin
      [*] = ;                  GetHeroProperty(gc_map_hero_iMobility,txt[i]);
      [*] = ;                  if hero_handle <> 0 then
      [*] = ;                  begin
      [*] = ;                     var curProvUID : Integer = GetGameObjectIntValueIndByHandle(hero_handle,gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;                     var pCurProvince : Integer = _misc_GetProvinceParserByUID(curProvUID);
      [*] = ;                     var stable : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'Stable');
      [*] = ;
      [*] = ;                     if stable > 0 then
      [*] = ;                        txt[i] := txt[i] + '+' + IntToStr(stable);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               else txt[i] := '';
      [*] = ;            end;
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle,txt[i],w,h);
      [*] = ;            max_w := max(max_w,w);
      [*] = ;         end;
      [*] = ;         temp_str := '%style(Symbols)%P';
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;         sym_w := w;
      [*] = ;         if elem_id = cStats then
      [*] = ;            no := 3 // !!!
      [*] = ;         else
      [*] = ;            no := 2;
      [*] = ;         rows_no := j div no;
      [*] = ;         i := _gui_TableGetFrameWidth(table_style);
      [*] = ;         e_dx := (i*2+w+max_w)*no+i;
      [*] = ;         //if _visible_stats_table = 0 then
      [*] = ;            e_dx := e_dx+(i+elem_d.p.size.w)*no;
      [*] = ;         i := _gui_TableGetFrameHeight(table_style);
      [*] = ;         e_dy := (i+h)*rows_no+i;
      [*] = ;
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            var columns,temp_str2 : String;
      [*] = ;            var xhd,bhd2 : Integer;
      [*] = ;
      [*] = ;            ehd := _gui_CreateImage_VVK('',windowHandle,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;
      [*] = ;            columns := '';
      [*] = ;            for i:=0 to no-1 do
      [*] = ;            begin
      [*] = ;               _sa_AddAsInt(columns,-1*sym_w);
      [*] = ;               _sa_AddAsInt(columns,-1*max_w);
      [*] = ;               //if _visible_stats_table = 0 then
      [*] = ;                  _sa_AddAsInt(columns,elem_d.p.size.w);
      [*] = ;            end;
      [*] = ;            _sys_FillRect(tmp_pos,0,0,0,0);
      [*] = ;            _gui_TableGetFrameStringExt(columns,table_style,gc_gui_TableFrameTop,temp_str);
      [*] = ;            if _log then _log_Values(temp_str+'|C1|C2|C3',0,sym_w,max_w,elem_d.p.size.w,0,0);
      [*] = ;            xhd:=_gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;            tmp_pos.pos.y := tmp_pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;
      [*] = ;            k := 0;
      [*] = ;            for i:=0 to rows_no-1 do
      [*] = ;            begin
      [*] = ;               temp_str2 := '';
      [*] = ;               for j := 0 to no-1 do
      [*] = ;               begin
      [*] = ;                  _sa_Add(temp_str2,'%style(Symbols)%%color(ignore)%'+SubStr(stats_str,k+1,1)+'%style(default)%%color(restore)%');
      [*] = ;                  _sa_Add(temp_str2,'^c'+txt[k]);
      [*] = ;                  //if _visible_stats_table = 0 then
      [*] = ;                     _sa_Add(temp_str2,''); // spacer
      [*] = ;                  k := k+1;
      [*] = ;               end;
      [*] = ;               _gui_TableFormatTextLineExt(elem_d.font_handle,table_style,columns,temp_str2,temp_str);
      [*] = ;               xhd:=_gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lt,elem_d.font_handle,elem_d.color);
      [*] = ;               w3 := GetGUIElementWidth(xhd) div no;
      [*] = ;               _sys_FillRect(tmp_pos2,0,0,w3,GetGUIElementHeight(xhd));
      [*] = ;               for j := 0 to no-1 do
      [*] = ;               begin
      [*] = ;                  case SubStr(stats_str,i*no+j+1,1) of
      [*] = ;                     'P': a_str := 'life';
      [*] = ;                     'Q': a_str := 'stamina';
      [*] = ;                     'R': a_str := 'moral';
      [*] = ;                     'S': a_str := 'speed';
      [*] = ;                     'T': a_str := 'attack';
      [*] = ;                     'U': a_str := 'counterattack';
      [*] = ;                     'V': a_str := 'defence';
      [*] = ;                     'W': a_str := 'rangeddefence';
      [*] = ;                     'X': a_str := 'resist';
      [*] = ;                     'Y': a_str := 'rangedattack';
      [*] = ;                     'Z': a_str := 'shootingrange';
      [*] = ;                     '[': a_str := 'ammo';
      [*] = ;                     '8': a_str := 'leader';
      [*] = ;                     '9': a_str := 'health';
      [*] = ;                     ':': a_str := 'magic';
      [*] = ;                     ';': a_str := 'siege';
      [*] = ;                     '<': a_str := 'initiative';
      [*] = ;                     '=': a_str := 'mobility';
      [*] = ;                     else a_str := '';
      [*] = ;                  end;
      [*] = ;                  bhd2 := _gui_CreateButton_VVK('',xhd,'',gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos2,'','',0);
      [*] = ;                  _gui_ft_AttachHint(bhd2,'VVK.HintUnitStatsCallback',a_str);
      [*] = ;                  SetGUIElementVisibleProperties(bhd2,'DisabledProperty',gc_gui_material_blank_0, 0, 0, 0, 0, 1, 1, 1, 1, 1);
      [*] = ;                  SetGUIElementEnabled(bhd2,false);
      [*] = ;                  tmp_pos2.pos.x := tmp_pos2.pos.x + w3;
      [*] = ;               end;
      [*] = ;               tmp_pos.pos.y := tmp_pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;
      [*] = ;               if (i = (rows_no-1)) then
      [*] = ;                  _gui_TableGetFrameStringExt(columns,table_style,gc_gui_TableFrameBottom,temp_str)
      [*] = ;               else
      [*] = ;                  _gui_TableGetFrameStringExt(columns,table_style,gc_gui_TableFrameCenter,temp_str);
      [*] = ;
      [*] = ;               xhd:=_gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,tmp_pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;               tmp_pos.pos.y := tmp_pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cMedals : begin
      [*] = ;         var d,dir,x,y,id,no,offs_y : Integer;
      [*] = ;         var tmp_pos2 : TRectangle;
      [*] = ;         var hdr_str : String;
      [*] = ;
      [*] = ;         if unit_handle <> 0 then
      [*] = ;            p := ParserSelectGameObject(unit_handle)
      [*] = ;         else
      [*] = ;            p := unit_p;
      [*] = ;
      [*] = ;         p := ParserSelectByHandleByKey(p,'Medals');
      [*] = ;
      [*] = ;         if _test_display then
      [*] = ;            no := 8
      [*] = ;         else
      [*] = ;            no := ParserGetCountByHandle(p);
      [*] = ;
      [*] = ;         _gui_GetInterfaceElement(if_handle,cAbilityHeaderOffset,elem2_d);
      [*] = ;
      [*] = ;         if no > 1 then
      [*] = ;            hdr_str := GetLocaleTableListItemByID('gui', 'unit_award_plural')
      [*] = ;         else
      [*] = ;            hdr_str := GetLocaleTableListItemByID('gui', 'unit_award');
      [*] = ;         if _log then _log_Values(hdr_str,no,0,0,0,0,0);
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,hdr_str,w,h);
      [*] = ;         offs_y := elem2_d.p.size.h+h;
      [*] = ;
      [*] = ;         if elem_d.p.size.w > elem_d.p.size.h then
      [*] = ;         begin
      [*] = ;            e_dx := elem_d.p.size.h*no;
      [*] = ;            d := elem_d.p.size.h;
      [*] = ;            dir := 0;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            e_dx := elem_d.p.size.w;
      [*] = ;            d := elem_d.p.size.w;
      [*] = ;            dir := 1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         x := 0;
      [*] = ;         y := 0;
      [*] = ;
      [*] = ;         _sys_FillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,d,d);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            _gui_GetInterfaceElement(if_handle,cMedalOffset,elem2_d);
      [*] = ;            _sys_FillRect(elem2_d.p,0,0,1,1);
      [*] = ;            elem2_d.p.size.w := d - ((elem2_d.p_raw.pos.x-elem_d.p_raw.pos.x)*2);
      [*] = ;            elem2_d.p.size.h := elem2_d.p.size.w; //d - ((elem2_d.p_raw.pos.y-elem_d.p_raw.pos.y)*2);
      [*] = ;
      [*] = ;            if dir = 0 then
      [*] = ;               tmp_pos.size.w := total_dx
      [*] = ;            else
      [*] = ;               tmp_pos.size.w := d;
      [*] = ;
      [*] = ;            for i:=0 to no-1 do
      [*] = ;            begin
      [*] = ;               if _test_display then
      [*] = ;                  id := i+1
      [*] = ;               else
      [*] = ;                  id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(p,i),'MedalID');
      [*] = ;               _sys_FillRect(tmp_pos2,tmp_pos.pos.x+x,tmp_pos.pos.y+y+offs_y,d,d);
      [*] = ;               ehd:=_gui_CreateButton_VVK('',windowHandle,'','icons.round.44x44.cover',gc_gui_align_parent_lt,tmp_pos2,'','',0);
      [*] = ;               _gui_ft_AttachHint_I1(ehd,'VVK.HintUnitMedalsCallback',id);
      [*] = ;               SetGUIElementVisibleProperties(ehd,'DisabledProperty','icons.round.44x44.cover.normal', 0, 0, 0, 0, 1, 1, 1, 1, 1);
      [*] = ;               SetGUIElementEnabled(ehd,false);
      [*] = ;               //SetGUIElementVisibleProperties(ehd, 'CheckOnProperty', 'icons.round.44x44.cover' + '.pressed', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;               _gui_CreateImage_VVK('',ehd,'icon.medal.'+IntToStr(id),gc_gui_align_parent_m,elem2_d.p);
      [*] = ;
      [*] = ;               if dir = 0 then
      [*] = ;               begin
      [*] = ;                  x := x + d;
      [*] = ;                  if ((x+d) > tmp_pos.size.w) then
      [*] = ;                  begin
      [*] = ;                     x := 0;
      [*] = ;                     y := y + d;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  y := y + d;
      [*] = ;                  if ((y+d) > elem_d.p.size.h) then
      [*] = ;                  begin
      [*] = ;                     y := 0;
      [*] = ;                     x := x + d;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (x > 0) or (y > 0) then
      [*] = ;            begin
      [*] = ;               e_dy := y + d + offs_y;
      [*] = ;               if dir = 0 then
      [*] = ;               begin
      [*] = ;                  if (d*no) > tmp_pos.size.w then
      [*] = ;                     e_dx := tmp_pos.size.w
      [*] = ;                  else
      [*] = ;                     e_dx := d*no;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  e_dx := elem_d.p.size.w;
      [*] = ;               _sys_FillRect(tmp_pos2,tmp_pos.pos.x,tmp_pos.pos.y,max(e_dx,w),h);
      [*] = ;               _gui_CreateText_VVK('',windowHandle,hdr_str,gc_gui_align_parent_lt,tmp_pos2,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;               if _log then _log_Values('E_DX|E_X|X',e_dx,e_x,x,0,0,0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         e_dx := max(e_dx,w);
      [*] = ;      end;
      [*] = ;      cLevel : begin
      [*] = ;         i := GetLevel();
      [*] = ;         temp_str := GetLocaleTableListItemByID('tooltip','unitinfo_level')+': '+IntToStr(i);
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,w,h);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_dx := Max(w,elem_d.p.size.w);
      [*] = ;         tmp_pos.size.w := e_dx;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            e_dy := h;
      [*] = ;            e_y := tmp_pos.pos.y;
      [*] = ;            ehd := _gui_CreateText_VVK('unitinfo_level',windowHandle,temp_str,elem_d.align,tmp_pos,gc_gui_align_lm,elem_d.font_handle,elem_d.color);
      [*] = ;            SetGUIAllowEvents(ehd, True, False, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cExpBar : begin
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         temp_str := GetLocaleTableListItemByID('hint','1')+': ';
      [*] = ;         GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str+'000%',w,h);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         //e_dx := tmp_pos.size.w+w;
      [*] = ;         e_dx := w;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            var e1,e2,ce : Integer;
      [*] = ;            var tmp_pos2 : TRectangle;
      [*] = ;
      [*] = ;            e_y := tmp_pos.pos.y;
      [*] = ;            //e_dy := tmp_pos.size.h;
      [*] = ;            e_dy := h;
      [*] = ;
      [*] = ;            _sys_FillRect(tmp_pos2,e_x,e_y,w,e_dy);
      [*] = ;            {_gui_CreateText_VVK('',windowHandle,temp_str,elem_d.align,tmp_pos2,gc_gui_align_lm,elem_d.font_handle,elem_d.color);
      [*] = ;            tmp_pos.pos.x := tmp_pos.pos.x+w;}
      [*] = ;
      [*] = ;            if _test_display then
      [*] = ;            begin
      [*] = ;               e1 := 1000;
      [*] = ;               e2 := 2000;
      [*] = ;               ce := 1500;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               i := GetLevel();
      [*] = ;
      [*] = ;               if is_hero <> 0 then
      [*] = ;               begin
      [*] = ;                  if hero_handle <> 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := i;
      [*] = ;                     GameObjectExecuteStateByHandle(hero_handle ,'GetNeededExpForLevel');
      [*] = ;                     e1 := IntRegister1;
      [*] = ;                     IntRegister0 := i+1;
      [*] = ;                     GameObjectExecuteStateByHandle(hero_handle ,'GetNeededExpForLevel');
      [*] = ;                     e2 := IntRegister1;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     e1 := 0;
      [*] = ;                     e2 := 0;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  IntRegister0 := unit_id;
      [*] = ;                  IntRegister1 := i;
      [*] = ;                  MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;                  e1 := IntRegister2;
      [*] = ;                  IntRegister0 := unit_id;
      [*] = ;                  IntRegister1 := i+1;
      [*] = ;                  MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;                  e2 := IntRegister2;
      [*] = ;               end;
      [*] = ;               ce := GetExperience();
      [*] = ;            end;
      [*] = ;
      [*] = ;            elem_d.p.size.w := 100;
      [*] = ;            if ce > e1 then
      [*] = ;            begin
      [*] = ;               if ce < e2 then
      [*] = ;                  i := Floor(((ce-e1)/(e2-e1))*elem_d.p.size.w)
      [*] = ;               else
      [*] = ;                  i := elem_d.p.size.w;
      [*] = ;               tmp_pos.size.w := i;
      [*] = ;               //ehd:=_gui_CreateImage_VVK('unitinfo_exp_meter',windowHandle,'unitpanel.meter.violet',elem_d.align,tmp_pos);
      [*] = ;               //SetGUIAllowEvents(ehd, True, False, False);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               i := 0;
      [*] = ;
      [*] = ;            i := min(i,99);
      [*] = ;            ehd := _gui_CreateText_VVK('unitinfo_exp_meter',windowHandle,temp_str+intToStr(i)+'%',elem_d.align,tmp_pos2,gc_gui_align_lm,elem_d.font_handle,elem_d.color);
      [*] = ;            SetGUIAllowEvents(ehd, True, False, False);
      [*] = ;            {tmp_pos.size.w := elem_d.p.size.w-i;
      [*] = ;            if tmp_pos.size.w > 0 then
      [*] = ;            begin
      [*] = ;               tmp_pos.pos.x := tmp_pos.pos.x+i;
      [*] = ;               ehd:=_gui_CreateImage_VVK('unitinfo_exp_meter',windowHandle,'misc.blank.black.alpha.1',elem_d.align,tmp_pos);
      [*] = ;               SetGUIAllowEvents(ehd, True, False, False);
      [*] = ;            end;}
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cIcon : begin
      [*] = ;         const cIconImage = $1e;
      [*] = ;         //const cIconVOffset = $1d;
      [*] = ;         const cIconRank = $1c;
      [*] = ;         const cIconPrice = $1b;
      [*] = ;         const cIconRes = $1a;
      [*] = ;         const cIconFrame = $19;
      [*] = ;         const cIconTemplate = 'unit_icon_details';
      [*] = ;         const cIconTemplateH = 'unit_hero_icon_details';
      [*] = ;
      [*] = ;         var icon_d : TInterfaceElementData;
      [*] = ;         var if_handle_i,pt,id,whd : Integer;
      [*] = ;         var tmp_pos2 : TRectangle;
      [*] = ;
      [*] = ;         if is_hero <> 0 then
      [*] = ;            if_handle_i := _gui_GetInterfaceWindowHandle(cIconTemplateH)
      [*] = ;         else
      [*] = ;            if_handle_i := _gui_GetInterfaceWindowHandle(cIconTemplate);
      [*] = ;
      [*] = ;         _sys_fillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;         stackable := _gui_DWCorrectElementPosition(tmp_pos,elem_d,total_x,total_y,extra_dy_offset);
      [*] = ;         e_x := tmp_pos.pos.x;
      [*] = ;         e_y := tmp_pos.pos.y;
      [*] = ;         e_dx := tmp_pos.size.w;
      [*] = ;         e_dy := tmp_pos.size.h;
      [*] = ;
      [*] = ;         if do_draw then
      [*] = ;         begin
      [*] = ;            _sys_FillRect(tmp_pos2,tmp_pos.pos.x,tmp_pos.pos.y,e_dx,e_dy);
      [*] = ;            ehd := _gui_CreateImage_VVK('',windowHandle,gc_gui_material_blank_0,elem_d.align,tmp_pos2);
      [*] = ;
      [*] = ;            if (is_hero <> 0) then
      [*] = ;            begin
      [*] = ;               if hero_handle <> 0 then
      [*] = ;                  temp_str := StrReplace(ParserGetValueByKeyByHandle(ParserSelectGameObject(hero_handle),'Portrait'),'map.hero.portrait.','info.portrait.')
      [*] = ;               else
      [*] = ;                  temp_str := 'astral.dialog.portrait.unknown';
      [*] = ;               _gui_GetInterfaceElement(if_handle_i,cIconImage,icon_d);
      [*] = ;               _gui_CreateImage_VVK('',ehd,temp_str,icon_d.align,icon_d.p);
      [*] = ;
      [*] = ;               _gui_GetInterfaceElement(if_handle_i,cIconFrame,icon_d);
      [*] = ;               _gui_CreateImage_VVK('',ehd,'astral.bonus.unit.frame',icon_d.align,icon_d.p);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               temp_str := 'icon.unit.'+IntToStr(unit_id);
      [*] = ;               _gui_GetInterfaceElement(if_handle_i,cIconImage,icon_d);
      [*] = ;               _gui_CreateImage_VVK('unitinfo_icon_'+IntToStr(unit_id),ehd,temp_str,icon_d.align,icon_d.p);
      [*] = ;
      [*] = ;               _gui_GetInterfaceElement(if_handle_i,cIconFrame,icon_d);
      [*] = ;               _gui_CreateImage_VVK('',ehd,'map.garrison.recruit.price.placer',icon_d.align,icon_d.p);
      [*] = ;
      [*] = ;               pt := _unit_GetUnitParserByID(unit_id);
      [*] = ;
      [*] = ;               if _gui_GetInterfaceElement(if_handle_i,cIconPrice,icon_d) then
      [*] = ;               begin
      [*] = ;                  var g : array[0..2] of Integer;
      [*] = ;
      [*] = ;                  g[0] := ParserGetIntValueByKeyByHandle(pt, 'GoldPrice');
      [*] = ;                  g[1] := ParserGetIntValueByKeyByHandle(pt, 'GemPrice');
      [*] = ;                  for i := 0 to 1 do
      [*] = ;                  begin
      [*] = ;                     if g[i] <> 0 then
      [*] = ;                     begin
      [*] = ;                        if i=0 then
      [*] = ;                           temp_str := gc_gui_GoldIconChar
      [*] = ;                        else
      [*] = ;                           temp_str := gc_gui_GemIconChar;
      [*] = ;                        _sys_FillRect(tmp_pos2,icon_d.p.pos.x,icon_d.p.pos.y+(i*icon_d.p.size.h),0,0);
      [*] = ;                        id := _gui_CreateText_VVK('',ehd,'%color(ignore)%'+temp_str+'%color(restore)%'+IntToStr(g[i]),icon_d.align,tmp_pos2,gc_gui_align_lm,icon_d.font_handle,icon_d.color);
      [*] = ;                        SetGUIElementHint(id,'gui|'+IntToStr(189+i));
      [*] = ;                        SetGUIAllowEvents(id, True, False, False);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if _gui_GetInterfaceElement(if_handle_i,cIconRes,icon_d) then
      [*] = ;               begin
      [*] = ;                  var pr : Integer;
      [*] = ;
      [*] = ;                  pr := ParserSelectByHandleByKey(pt, 'Resources');
      [*] = ;                  for i:=0 to ParserGetCountByHandle(pr)-1 do
      [*] = ;                  begin
      [*] = ;                     id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pr,i),'ResourceID');
      [*] = ;                     _sys_FillRect(tmp_pos2,icon_d.p.pos.x,icon_d.p.pos.y+(i*icon_d.p.size.h),0,0);
      [*] = ;                     whd := _gui_CreateImage_VVK('',ehd,'map.resource.'+IntToStr(id)+'.22x22',gc_gui_align_parent_lt,tmp_pos2);
      [*] = ;                     _gui_ft_AttachHint_I3(whd,'VVK.FTooltipResource',id-1,cFT_ResSkipAccess,0);
      [*] = ;                     SetGUIAllowEvents(whd,True,False,False);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if _gui_GetInterfaceElement(if_handle_i,cIconRank,icon_d) then
      [*] = ;               begin
      [*] = ;                  id := ParserGetIntValueByKeyByHandle(pt, 'Rank');
      [*] = ;                  id := _gui_CreateImage_VVK('unitinfo_rank_'+IntToStr(id),ehd,'building_level_'+IntToStr(id),gc_gui_align_parent_lt,icon_d.p);
      [*] = ;                  SetGUIAllowEvents(id,True,False,False);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetArguments(temp_str : String);
      [*] = ;begin
      [*] = ;   mode := _sa_GetAsInt(temp_str,0);
      [*] = ;   case mode of
      [*] = ;      cFT_UnitTemplate : begin
      [*] = ;         is_hero := 0;
      [*] = ;         army_p := 0;
      [*] = ;         unit_id := _sa_GetAsInt(temp_str,1);
      [*] = ;         unit_p := _unit_GetUnitParserByID(unit_id);
      [*] = ;         unit_uid := 0;
      [*] = ;      end;
      [*] = ;      cFT_UnitMapArmy : begin
      [*] = ;         is_hero := 0;
      [*] = ;         unit_id := -1;
      [*] = ;         unit_uid := 0;
      [*] = ;         army_p := _sa_GetAsInt(temp_str,2);
      [*] = ;         unit_p := _sa_GetAsInt(temp_str,1);
      [*] = ;      end;
      [*] = ;      cFT_UnitMapHero : begin
      [*] = ;         is_hero := 1;
      [*] = ;         unit_id := -1;
      [*] = ;         unit_uid := _sa_GetAsInt(temp_str,1);
      [*] = ;         unit_p := 0;
      [*] = ;         army_p := 0;
      [*] = ;      end;
      [*] = ;      cFT_UnitBattle : begin
      [*] = ;         is_hero := -1;
      [*] = ;         unit_id := -1;
      [*] = ;         unit_uid := _sa_GetAsInt(temp_str,1);
      [*] = ;         unit_p := 0;
      [*] = ;         army_p := 0;
      [*] = ;      end;
      [*] = ;      cFT_HeroTemplate : begin
      [*] = ;         is_hero := 1;
      [*] = ;         army_p := 0;
      [*] = ;         unit_id := _sa_GetAsInt(temp_str,1);
      [*] = ;         unit_p := _unit_GetUnitParserByID(unit_id);
      [*] = ;         unit_uid := 0;
      [*] = ;         hero_price :=IntToStr(_sa_GetAsInt(temp_str,2))+'|'+IntToStr(_sa_GetAsInt(temp_str,3));
      [*] = ;      end;
      [*] = ;      cFT_UnitAstralHero : begin
      [*] = ;         is_hero := 0;
      [*] = ;         army_p := _sa_GetAsInt(temp_str,3);
      [*] = ;         unit_id := _sa_GetAsInt(temp_str,1);
      [*] = ;         unit_p := _sa_GetAsInt(temp_str,2);
      [*] = ;         unit_uid := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var callback_mode : Integer = IntRegister0;
      [*] = ;var if_handle : Integer = IntRegister1;
      [*] = ;var field_id : Integer;
      [*] = ;
      [*] = ;GetArguments(StringRegister0);
      [*] = ;case callback_mode of
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

