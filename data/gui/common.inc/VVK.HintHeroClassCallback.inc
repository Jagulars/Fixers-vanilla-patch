section.begin
   Name = VVK.HintHeroClassCallback
   Description : struct.begin
      [*] = ;See VVK.FTooltipInnerBuilding.inc for details
      [*] = ;
      [*] = ;Callback attributes
      [*] = ;[0] - class index (& 0x10000 if class id tooltip should be ignored)
      [*] = ;[1] - strategy map hero UID (used for filling in gStringRegister_SkillName global variable)
      [*] = ;[2-4] - states for buttons to call if not empty
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;function ProcessOnHint(whd : Integer;ext : Boolean;args : String;var ret_i : Integer;var ret_s : String;var rete_s : String) : Integer;
      [*] = ;begin
      [*] = ;   var text,text_e : String;
      [*] = ;   var c_id : Integer;
      [*] = ;
      [*] = ;   c_id := _sa_GetAsInt(args,0);
      [*] = ;   ret_i := 0;
      [*] = ;   text_e := '';
      [*] = ;
      [*] = ;   if ((c_id and $10000) = 0) then
      [*] = ;   begin
      [*] = ;      text := GetLocaleTableListItemByID('hero_class_d', IntToStr(c_id));
      [*] = ;
      [*] = ;      if not ext then
      [*] = ;      begin
      [*] = ;         if GetLocaleTableListItemByID('hero_class', IntToStr(c_id)+'.description') <> '' then
      [*] = ;            ret_i := ret_i or 2
      [*] = ;      end
      [*] = ;      else
      [*] = ;         text_e := GetLocaleTableListItemByID('hero_class', IntToStr(c_id)+'.description');
      [*] = ;
      [*] = ;      ret_i := ret_i or 4;
      [*] = ;      ret_s := text;
      [*] = ;      rete_s := text_e;
      [*] = ;      Result := 3;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ret_s := '';
      [*] = ;      rete_s := '';
      [*] = ;      Result := 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessMouseButton(whd,mx,my,b : Integer;args : String) : Boolean;
      [*] = ;begin
      [*] = ;   var state : String;
      [*] = ;
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   _sa_Get(args,2+b,state);
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
      [*] = ;         GUIExecuteState(state);
      [*] = ;         Result := true;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (b=1) or (state <> '') then
      [*] = ;      begin
      [*] = ;         var c_id : Integer;
      [*] = ;         var skill_id : Integer = _sa_GetAsInt(args,1);
      [*] = ;
      [*] = ;         c_id := (_sa_GetAsInt(args,0) and $ffff);
      [*] = ;
      [*] = ;         if skill_id <> 0 then skill_id := GetGameObjectHandleByUniqueId(skill_id);
      [*] = ;         if skill_id <> 0 then skill_id := ParserSelectByHandleByKey(ParserSelectGameObject(skill_id), 'Units');
      [*] = ;         if skill_id <> 0 then skill_id := ParserSelectByHandleByIndex( skill_id, 0); // first unit is always hero!
      [*] = ;         if skill_id <> 0 then skill_id := ParserSelectByHandleByKey(skill_id, 'Upgrades');
      [*] = ;         if skill_id <> 0 then skill_id := ParserSelectByHandleByIndex(skill_id, 0);
      [*] = ;         if skill_id <> 0 then skill_id := ParserGetIntValueByKeyByHandle(skill_id,'UpgradeID');
      [*] = ;         if skill_id <> 0 then gStringRegister_SkillName := GetLocaleTableListItemByID('upgrade', IntToStr(skill_id))
      [*] = ;         else gStringRegister_SkillName := GetLocaleTableListItemByID('skill', '26');
      [*] = ;
      [*] = ;         StringRegister0 := GetLocaleTableListItemByID('hero_class_d', IntToStr(c_id));
      [*] = ;         StringRegister1 := GetLocaleTableListItemByID('hero_class_d', IntToStr(c_id)+'.description');
      [*] = ;         StringRegister2 := 'icon.heroclass.'+IntToStr(c_id-1);
      [*] = ;         GUIExecuteState('VVK.ShowInfoWindow');
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
      [*] = ;   cFloatTooltipOnMouseButton : BoolRegister0 := ProcessMouseButton(IntRegister1,IntRegister2,IntRegister3,IntRegister4,StringRegister0);
      [*] = ;end;
   struct.end
section.end

