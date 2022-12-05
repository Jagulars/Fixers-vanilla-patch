section.begin
   Name = VVK.FTooltipUnit
   Description : struct.begin
      [*] = ;See VVK.FTooltipInnerBuilding.inc for details
      [*] = ;
      [*] = ;----------------
      [*] = ;Base tooltip window:
      [*] = ;   tag = source window handle
      [*] = ;   string_tag = object_id string
      [*] = ;----------------
      [*] = ;Callback attributes
      [*] = ;[0] - type
      [*] = ;   cFT_UnitTemplate - display unit template
      [*] = ;      [1] - unit id
      [*] = ;      [2] - non zero - should display summon hint
      [*] = ;      [3] - reserved
      [*] = ;   cFT_UnitMapArmy - display unit on strategy map
      [*] = ;      [1] - Unit parser
      [*] = ;      [2] - Army parser (could be 0 if unit is standalone - garrison, etc)
      [*] = ;      [3] - reserved
      [*] = ;   cFT_UnitMapHero - display hero information on startegy map
      [*] = ;      [1] - Hero UID
      [*] = ;      [2], [3] - reserved
      [*] = ;   cFT_UnitBattle - display unit/hero information in tactics
      [*] = ;      [1] - Hero/Unit UID
      [*] = ;      [2], [3] - reserved
      [*] = ;   cFT_HeroTemplate - display possible hero information from template
      [*] = ;      [1] - Hero unit ID
      [*] = ;      [2] - Hiring hero price, gold
      [*] = ;      [3] - Hiring hero price, gems
      [*] = ;[4] - left button state (opt)
      [*] = ;[5] - right button state (opt)
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure GetUnitName(mode,a1,a2 : Integer; var ret_s : String );
      [*] = ;begin
      [*] = ;   var unit_id : Integer;
      [*] = ;
      [*] = ;   case mode of
      [*] = ;      cFT_UnitTemplate : begin
      [*] = ;         if a2 = 1 then
      [*] = ;         begin
      [*] = ;            ret_s := GetLocaleTableListItemByID('ability', '78') +': '+GetLocaleTableListItemByID('unit', IntToStr(a1))+gc_gui_BreakLine+gc_gui_BreakLine;
      [*] = ;            ret_s := ret_s + GetLocaleTableListItemByID('ability', '78.description');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            ret_s := GetLocaleTableListItemByID('unit', IntToStr(a1));
      [*] = ;      end;
      [*] = ;      cFT_UnitMapArmy : begin
      [*] = ;         var rank : Integer;
      [*] = ;
      [*] = ;         unit_id := ParserGetIntValueByKeyByHandle(a1,'UnitID');
      [*] = ;         rank := ParserGetIntValueByKeyByHandle(_unit_GetUnitParserByID(unit_id), 'Rank');
      [*] = ;         ret_s := GetLocaleTableListItemByID('unit', IntToStr(unit_id))+' ('+GetLocaleTableListItemByID('gui', IntToStr(10))+' '+IntToStr(rank)+')';
      [*] = ;      end;
      [*] = ;      cFT_UnitMapHero : begin
      [*] = ;         var hero_handle : Integer;
      [*] = ;         var h_name : String;
      [*] = ;
      [*] = ;         hero_handle := GetGameObjectHandleByUniqueId(a1);
      [*] = ;         if hero_handle <> 0 then
      [*] = ;            _hero_GetName(hero_handle,h_name)
      [*] = ;         else
      [*] = ;            h_name := '???';
      [*] = ;
      [*] = ;         ret_s := h_name;
      [*] = ;      end;
      [*] = ;      cFT_UnitBattle : begin
      [*] = ;         var handle,rank,unit_id : Integer;
      [*] = ;         var h_name : String;
      [*] = ;
      [*] = ;         handle := GetGameObjectHandleByUniqueId(a1);
      [*] = ;         if GetGameObjectBoolValueIndByHandle(handle,gc_stack_unit_bIsHero) then
      [*] = ;         begin
      [*] = ;            var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(handle, gc_stack_unit_iHeroUID));
      [*] = ;            _hero_GetName(mapHeroHandle,h_name);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            unit_id := GetGameObjectIntValueIndByHandle(handle, gc_stack_unit_iUnitID);
      [*] = ;            rank := ParserGetIntValueByKeyByHandle(_unit_GetUnitParserByID(unit_id), 'Rank');
      [*] = ;            h_name := GetLocaleTableListItemByID('unit', IntToStr(unit_id))+' ('+GetLocaleTableListItemByID('gui', IntToStr(10))+' '+IntToStr(rank)+')';
      [*] = ;         end;
      [*] = ;
      [*] = ;         ret_s := h_name;
      [*] = ;      end;
      [*] = ;      cFT_HeroTemplate : begin
      [*] = ;         ret_s := GetLocaleTableListItemByID('unit', IntToStr(a1));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessOnHint(whd : Integer;ext : Boolean;args : String;var ret_i : Integer;var ret_s : String;var rete_s : String) : Integer;
      [*] = ;begin
      [*] = ;   if ext then
      [*] = ;   begin
      [*] = ;      Result := 1;
      [*] = ;      ret_i := 0;
      [*] = ;      ret_s := '';
      [*] = ;      rete_s := '';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var temp_str : String;
      [*] = ;
      [*] = ;      Result := 3;
      [*] = ;      ret_i := 4;
      [*] = ;      GetUnitName(_sa_GetAsInt(args,0),_sa_GetAsInt(args,1),_sa_GetAsInt(args,2),temp_str);
      [*] = ;      ret_s := temp_str;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessMouseButton(whd,mx,my,b : Integer;args : String) : Boolean;
      [*] = ;begin
      [*] = ;   var state : String;
      [*] = ;
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   _sa_Get(args,4+b,state);
      [*] = ;   if StrLength(state) > 4 then
      [*] = ;   begin
      [*] = ;      var key : String;
      [*] = ;
      [*] = ;      case b of
      [*] = ;         0 : key := 'LButton';
      [*] = ;         1 : key := 'RButton';
      [*] = ;         2 : key := 'MButton';
      [*] = ;         else key := '';
      [*] = ;      end;
      [*] = ;      if key <> '' then
      [*] = ;      begin
      [*] = ;         SetIntValueByName('ElementHandle',whd);
      [*] = ;         SetIntValueByName('Tag',GetGUIElementTag(whd));
      [*] = ;         SetValueByName('Press','c');
      [*] = ;         SetValueByName('Key',key);
      [*] = ;         if _log then _log_Values('TAG|'+key,GetGUIElementTag(whd),0,0,0,0,0);
      [*] = ;         GUIExecuteState(state);
      [*] = ;         Result := true;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (b=1) or (state <> '') then
      [*] = ;      begin
      [*] = ;         var rb_mode : Integer = StrToInt(state);
      [*] = ;
      [*] = ;         GUIExecuteState('DoResetDragElement');
      [*] = ;         SetGUIElementVisible(GetGUIElementIndexByNameParent('dismiss',whd),False);
      [*] = ;         StringRegister0 := args;
      [*] = ;         GUIExecuteState('vvk.ShowUnitInfoModal');
      [*] = ;         Result := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;
      [*] = ;case mode of
      [*] = ;   cFloatTooltipOnHint : begin
      [*] = ;      var ret_s,rete_s : String;
      [*] = ;      var ret_i : Integer;
      [*] = ;
      [*] = ;      IntRegister0 := ProcessOnHint(IntRegister1,BoolRegister0,StringRegister0,ret_i,ret_s,rete_s);
      [*] = ;      StringRegister0 := ret_s;
      [*] = ;      StringRegister1 := rete_s;
      [*] = ;      IntRegister1 := ret_i;
      [*] = ;   end;
      [*] = ;   //cFloatTooltipMouseMove : ProcessMouseMove(IntRegister1,IntRegister2,IntRegister3,IntRegister4,IntRegister5,StringRegister0,StringRegister1);
      [*] = ;   //cFloatTooltipDisplay : Display(IntRegister1,IntRegister2,IntRegister3,IntRegister4,StringRegister0,StringRegister1,StringRegister2,StringRegister3,BoolRegister0);
      [*] = ;   //cFloatTooltipIsSameObject : BoolRegister0 := IsSameObject(IntRegister1,StringRegister0);
      [*] = ;   //cFloatTooltipUpdatePos: BoolRegister0 := UpdatePos(IntRegister1,IntRegister2,IntRegister3,IntRegister4,StringRegister0);
      [*] = ;   cFloatTooltipOnMouseButton : BoolRegister0 := ProcessMouseButton(IntRegister1,IntRegister2,IntRegister3,IntRegister4,StringRegister0);
      [*] = ;end;
   struct.end
section.end

