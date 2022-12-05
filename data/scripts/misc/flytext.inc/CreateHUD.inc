section.begin
   Name = CreateHUD
   Code : struct.begin
      [*] = ;var _log_name : String = 'MISC\FLYTEXT.INC\CREATEHUD';
      [*] = ;var _log_trace : Integer = $800000;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var layer: Integer = _gui_GetLayer(cHUDTacticsTextLayer);
      [*] = ;var hud,fp,fvalue,ftype: Integer;
      [*] = ;var pfx : String;
      [*] = ;
      [*] = ;if (layer=0) then
      [*] = ;begin
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;if gProfile.battle_flytext = 1 then pfx := '_2'
      [*] = ;else pfx := '_1';
      [*] = ;
      [*] = ;hud := GetGUIGroupHUDCollectionItemByGameObject(layer,GetGameObjectMyHandle());
      [*] = ;if (hud <> 0) then
      [*] = ;  RemoveGUIChildren(hud)
      [*] = ;else
      [*] = ;  hud := GUIGroupHUDCollectionAddGameObject(layer,GetGameObjectMyHandle());
      [*] = ;
      [*] = ;fvalue := GetIntValueByIndex(gc_stack_flytext_iValue);
      [*] = ;ftype := GetIntValueByIndex(gc_stack_flytext_iType);
      [*] = ;
      [*] = ;fp := _fx_FlyTextGetParserByID(ftype);
      [*] = ;if fp <> 0 then
      [*] = ;begin
      [*] = ;   var sc,tc : TColorRGBA;
      [*] = ;   var pos : TRectangle;
      [*] = ;   var attr,style,sp,whd,bhd,w,h,tw,th : Integer;
      [*] = ;   var text,font,v : String;
      [*] = ;
      [*] = ;   attr := ParserGetIntValueByKeyByHandle(fp,'Attr'+pfx);
      [*] = ;   text := ParserGetValueByKeyByHandle(fp,'Text'+pfx);
      [*] = ;   style := ParserGetIntValueByKeyByHandle(fp,'StyleP'+pfx);
      [*] = ;   if _log then _Log_Map('Text before: '+text+', Type: '+IntToStr(ftype)+', Value: '+IntToStr(fvalue));
      [*] = ;   if ((attr and gc_flytext_AttrValue) <> 0) then
      [*] = ;   begin
      [*] = ;      v :=IntToStr(floor(abs(fvalue)));
      [*] = ;      if fvalue >= 0 then
      [*] = ;      begin
      [*] = ;         if ((attr and gc_flytext_AttrPlusSign) <> 0) then
      [*] = ;            v := '+' + v;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         style := ParserGetIntValueByKeyByHandle(fp,'StyleN'+pfx);
      [*] = ;         if ((attr and gc_flytext_AttrMinusSign) <> 0) then
      [*] = ;            v := '-' + v;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if fvalue < 0 then
      [*] = ;         style := ParserGetIntValueByKeyByHandle(fp,'StyleN'+pfx);
      [*] = ;      v := '';
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ((attr and gc_flytext_AttrValueAsID) <> 0) then
      [*] = ;   begin
      [*] = ;      var t1,t2 : String;
      [*] = ;      var en : Integer;
      [*] = ;
      [*] = ;      en := _sa_GetNumSafe(text);
      [*] = ;      if (en>1) then
      [*] = ;      begin
      [*] = ;         _sa_Get(text,0,t1);
      [*] = ;         _sa_Get(text,1,t2);
      [*] = ;         en := 1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         t1 := text;
      [*] = ;         t2 := '';
      [*] = ;      end;
      [*] = ;      if fvalue < 0 then
      [*] = ;         style := ParserGetIntValueByKeyByHandle(fp,'StyleN'+pfx);
      [*] = ;
      [*] = ;      text := t1 + '|' +IntToStr(floor(abs(fvalue)));
      [*] = ;      if t2 <> '' then
      [*] = ;         text := text + '|' + t2;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ((attr and gc_flytext_AttrIDAsKey) <> 0) then
      [*] = ;   begin
      [*] = ;      if(_sa_GetNumSafe(text)<=1) then
      [*] = ;         text := text+'|'+IntToStr(ftype and gc_flytext_IDMask);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if(_sa_GetNumSafe(text)>1) then
      [*] = ;   begin
      [*] = ;      var t1,t2 : String;
      [*] = ;
      [*] = ;      _sa_Get(text,0,t1);
      [*] = ;      _sa_Get(text,1,t2);
      [*] = ;      t1 := GetLocaleTableListItemByID(t1,t2);
      [*] = ;      _sa_Get(text,2,t2);
      [*] = ;      if t1 <> '' then
      [*] = ;         text := t1;
      [*] = ;      if t2 <> '' then
      [*] = ;         text := text + t2;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if v <> '' then
      [*] = ;   begin
      [*] = ;      if text <> '' then
      [*] = ;         text := text + ' ' + v
      [*] = ;      else
      [*] = ;         text := v;
      [*] = ;   end;
      [*] = ;
      [*] = ;   sp := _fx_FlyTextStyleGetParserByID(style);
      [*] = ;
      [*] = ;   whd := _gui_CreateImage('', hud, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;   _gui_GetFont(gc_gui_fontsection_tactics,'Battlefield',gc_gui_fontsize_default,'',font);
      [*] = ;   GetGUIElementFontTextRect(font,text,tw,th);
      [*] = ;
      [*] = ;   w := ParserGetIntValueByKeyByHandle(sp,'SpotDX');
      [*] = ;   if w >= 0 then
      [*] = ;      w := w + tw
      [*] = ;   else
      [*] = ;      w := -1*w;
      [*] = ;
      [*] = ;   h := ParserGetIntValueByKeyByHandle(sp,'SpotDY');
      [*] = ;   if h >= 0 then
      [*] = ;      h := h + th
      [*] = ;   else
      [*] = ;      h := -1*h;
      [*] = ;
      [*] = ;   FormatHexToColor4(ParserGetValueByKeyByHandle(sp,'SpotColor'),sc.a,sc.r,sc.g,sc.b);
      [*] = ;   FormatHexToColor4(ParserGetValueByKeyByHandle(sp,'Color'),tc.a,tc.r,tc.g,tc.b);
      [*] = ;   _sys_FillRect(pos,-1*(w div 2),-1*(h div 2),w,h);
      [*] = ;
      [*] = ;   bhd := _gui_CreateImage_VVK('',whd,ParserGetValueByKeyByHandle(sp,'SpotName'),gc_gui_align_parent_lt,pos);
      [*] = ;   SetGUIElementUserColor(bhd, sc.r, sc.g, sc.b, sc.a);
      [*] = ;   SetGUIElementUseUserColor(bhd, True);
      [*] = ;
      [*] = ;   _sys_FillRect(pos,0,0,0,0);
      [*] = ;   sc.r := gc_gui_fontcolor_Black.r;
      [*] = ;   sc.g := gc_gui_fontcolor_Black.g;
      [*] = ;   sc.b := gc_gui_fontcolor_Black.b;
      [*] = ;   sc.a := 0.7;
      [*] = ;   bhd := _gui_CreateText_VVK('',bhd,text,gc_gui_align_parent_m,pos,gc_gui_align_middle,font,sc);
      [*] = ;   _sys_FillRect(pos,1,-1,0,0);
      [*] = ;   bhd := _gui_CreateText_VVK('',bhd,text,gc_gui_align_parent_lt,pos,gc_gui_align_middle,font,tc);
      [*] = ;
      [*] = ;   var speedMod : Float = _fx_GetFlyTextSpeedMod();
      [*] = ;
      [*] = ;   if _log then _Log_Map('Text after: '+text);
      [*] = ;   _gui_FadeWindow_VVK(whd, ParserGetIntValueByKeyByHandle(sp,'FadeDelay') / speedMod / 1000, 1);
      [*] = ;   //_gui_FadeElement(whd,ParserGetIntValueByKeyByHandle(sp,'FadeDelay')/1000,True,False,False);
      [*] = ;end;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
   OldCode : struct.begin
      [*] = ;var _log_name : String = 'MISC\FLYTEXT.INC\CREATEHUD';
      [*] = ;var _log_trace : Integer = $800000;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var hudCollection : Integer = _gui_GetLayer(cHUDTacticsTextLayer);
      [*] = ;var hudHandle : Integer;
      [*] = ;
      [*] = ;if (hudCollection=0) then
      [*] = ;begin
      [*] = ;   ErrorLogI(_log_name+' HUD collection hudtext not found.');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;hudHandle := GetGUIGroupHUDCollectionItemByGameObject(hudCollection,myHandle);
      [*] = ;if (hudHandle<>0) then
      [*] = ;  RemoveGUIChildren(hudHandle)
      [*] = ;else
      [*] = ;  hudHandle := GUIGroupHUDCollectionAddGameObject(hudCollection,myHandle);
      [*] = ;
      [*] = ;var colorR, colorG, colorB : Float = 1;
      [*] = ;var sColorR, sColorG, sColorB : Float = 0;
      [*] = ;var colorA : Float = 1;
      [*] = ;var sColorA : Float = 0.7;
      [*] = ;
      [*] = ;var iValue : Integer = GetIntValueByIndex(gc_stack_flytext_iValue);
      [*] = ;var iType : Integer = GetIntValueByIndex(gc_stack_flytext_iType);
      [*] = ;
      [*] = ;var sValue : String = '';
      [*] = ;var iStyle : Integer = 0;
      [*] = ;case iType of
      [*] = ;   gc_flytext_iLife : begin
      [*] = ;      //sValue := IntToStr(round(Abs(iValue)));
      [*] = ;      if (iValue>0) then
      [*] = ;      begin
      [*] = ;         sValue := '+'+IntToStr(iValue);
      [*] = ;         iStyle := 4;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         sValue := IntToStr(iValue);
      [*] = ;         iStyle := 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_flytext_iStamina : begin
      [*] = ;      if (iValue>0) then
      [*] = ;        sValue := '+'+IntToStr(iValue)
      [*] = ;      else
      [*] = ;        sValue := IntToStr(iValue);
      [*] = ;      iStyle := 2;
      [*] = ;   end;
      [*] = ;   gc_flytext_iMoral : begin
      [*] = ;      if (iValue>0) then
      [*] = ;        sValue := '+'+IntToStr(iValue)
      [*] = ;      else
      [*] = ;        sValue := IntToStr(iValue);
      [*] = ;      iStyle := 3;
      [*] = ;   end;
      [*] = ;   gc_flytext_iHeal : begin
      [*] = ;      sValue := '+'+IntToStr(iValue);
      [*] = ;      iStyle := 4;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityResistance : begin
      [*] = ;      sValue := 'gui|4';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityBrokenWeapon : begin
      [*] = ;      sValue := 'gui|371';
      [*] = ;      iStyle := 5;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityBrokenArmor : begin
      [*] = ;      sValue := 'gui|372';
      [*] = ;      iStyle := 5;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityMarch : begin
      [*] = ;      sValue := 'gui|67';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityScared : begin
      [*] = ;      sValue := 'gui|1';
      [*] = ;      iStyle := 1;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityPanic : begin
      [*] = ;      sValue := 'gui|2';
      [*] = ;      iStyle := 1;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityBerserk : begin
      [*] = ;      sValue := 'gui|3';
      [*] = ;      iStyle := 5;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityCollectAmmo : begin
      [*] = ;      //sValue := 'gui|262|'+IntToStr(iValue);
      [*] = ;      //iStyle := 6;
      [*] = ;      sValue := IntToStr(iValue);
      [*] = ;      iStyle := 9;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityNecrophagy : begin
      [*] = ;      sValue := 'gui|68';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityPetrification : begin
      [*] = ;      sValue := 'ability|46';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityWeb : begin
      [*] = ;      sValue := 'ability|47';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityCrushingBlow : begin
      [*] = ;      sValue := 'ability|59';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityRoundAttack : begin
      [*] = ;      sValue := 'ability|66';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;   gc_flytext_iSpellID : begin
      [*] = ;      sValue := 'spell|'+IntToStr(iValue);
      [*] = ;      iStyle := 7;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityBolo : begin
      [*] = ;      sValue := 'ability|171';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;   gc_flytext_iAbilityLunge : begin
      [*] = ;      sValue := 'ability|170';
      [*] = ;      iStyle := 6;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;case iStyle of
      [*] = ;   1 : begin // Жизнь - 1 красный
      [*] = ;      colorR := 1.0;
      [*] = ;      colorG := 0.2;
      [*] = ;      colorB := 0.0;
      [*] = ;   end;
      [*] = ;   2 : begin // Стамина - 2 желтый
      [*] = ;      colorR := 1.0;
      [*] = ;      colorG := 0.9;
      [*] = ;      colorB := 0.0;
      [*] = ;   end;
      [*] = ;   3 : begin // БД - 3 синий
      [*] = ;      colorR := 0.0;
      [*] = ;      colorG := 0.6;
      [*] = ;      colorB := 1.0;
      [*] = ;   end;
      [*] = ;   4 : begin // Лечение - 4 зеленый
      [*] = ;      colorR := 0.0;
      [*] = ;      colorG := 1.0;
      [*] = ;      colorB := 0.25;
      [*] = ;   end;
      [*] = ;   5 : begin // 5 оранжевый (вредные абилки)
      [*] = ;      colorR := 1.0;
      [*] = ;      colorG := 0.5;
      [*] = ;      colorB := 0.0;
      [*] = ;   end;
      [*] = ;   6 : begin // 6 желтый (абилки)
      [*] = ;      colorR := 1.0;
      [*] = ;      colorG := 0.9;
      [*] = ;      colorB := 0.0;
      [*] = ;   end;
      [*] = ;   7 : begin // 7 спеллы
      [*] = ;      colorR := 1.0;
      [*] = ;      colorG := 0.15;
      [*] = ;      colorB := 1.0;
      [*] = ;   end;
      [*] = ;   8 : begin // 8 белый
      [*] = ;      colorR := 0.9;
      [*] = ;      colorG := 0.9;
      [*] = ;      colorB := 0.9;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      colorR := GetgDbgFloat0;
      [*] = ;      colorG := GetgDbgFloat1;
      [*] = ;      colorB := GetgDbgFloat2;
      [*] = ;      colorR := 0.9;
      [*] = ;      colorG := 0.9;
      [*] = ;      colorB := 0.9;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var addValue : String = '';
      [*] = ;if (IsDelimiterCharExists(sValue, gc_gui_DelimiterChar)) then
      [*] = ;begin
      [*] = ;   var delimiterStringCount : Integer = GetDelimiterStringCount(sValue, gc_gui_DelimiterChar, gc_gui_QuoteChar);
      [*] = ;   if (delimiterStringCount>=3) then
      [*] = ;   begin
      [*] = ;      addValue := GetDelimiterStringByIndex(sValue, gc_gui_DelimiterChar, gc_gui_QuoteChar, 3);
      [*] = ;      sValue := GetDelimiterStringByIndex(sValue, gc_gui_DelimiterChar, gc_gui_QuoteChar, 0)+'|'+GetDelimiterStringByIndex(sValue, gc_gui_DelimiterChar, gc_gui_QuoteChar, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateImage('textParent', hudHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;var width, height : Integer;
      [*] = ;var fontHandle : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Battlefield',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;_gui_ConvertTableKeyToText(sValue);
      [*] = ;GetGUIElementFontTextRect(fontHandle, sValue, width, height);
      [*] = ;var elmHandle : Integer;
      [*] = ;var spotWidth, spotHeight : Integer;
      [*] = ;if (iType<=3) or (iType=gc_flytext_iAbilityCollectAmmo) then
      [*] = ;begin
      [*] = ;   //spotWidth := width+20;//3*round(sqrt(sqr(width div 2)+sqr(height div 2)))+20;
      [*] = ;   //spotHeight := height+20;
      [*] = ;   spotWidth := 38;
      [*] = ;   spotHeight := 34;
      [*] = ;   elmHandle := _gui_CreateImage('spotlight', elmParentHandle, 'gamepanel03.slotlight.gradient.black', 'halParentLeft', 'valParentTop', (-spotWidth div 2)+1, (-spotHeight div 2)-1, spotWidth, spotHeight, 0);
      [*] = ;   SetGUIElementUserColor(elmHandle, 0, 0, 0, 0.675);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   spotWidth := 3*round(sqrt(sqr(width div 2)+sqr(height div 2)))+20;
      [*] = ;   spotHeight := height+20;
      [*] = ;   //spotWidth := width+20;
      [*] = ;   //spotHeight := height+20;
      [*] = ;   //elmHandle := _gui_CreateImage('spotlight', elmParentHandle, 'gamepanel03.slotlight.oval.gradient.white', 'halParentLeft', 'valParentTop', (-spotWidth div 2)+1, (-spotHeight div 2)-1+height, spotWidth, spotHeight, 0);
      [*] = ;   //Gec hotfix
      [*] = ;   elmHandle := _gui_CreateImage('spotlight', elmParentHandle, 'gamepanel03.slotlight.oval.gradient.white', 'halParentLeft', 'valParentTop', (-spotWidth div 2), (-spotHeight div 2)-1, spotWidth, spotHeight, 0);
      [*] = ;   SetGUIElementUserColor(elmHandle, 0, 0, 0, 0.55);
      [*] = ;end;
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;//Log('Values: Width: '+IntToStr(width)+' Height: '+IntToStr(height)+' SpotDX: '+IntToStr(spotWidth)+' SpotDY: '+IntToStr(spotHeight));
      [*] = ;//SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;var elmTextHandle : Integer;
      [*] = ;//elmTextHandle := _gui_CreateText('value', elmParentHandle, sValue, 'halParentLeft', 'valParentTop', -(spotWidth div 2), -(spotHeight div 2), width, height*2, 'halMiddle', 'valBottom', fontHandle, sColorR, sColorG, sColorB, sColorA);
      [*] = ;//elmTextHandle := _gui_CreateText('value', elmTextHandle, sValue, 'halParentLeft', 'valParentTop', 1, -1, width, height*2, 'halMiddle', 'valBottom', fontHandle, colorR, colorG, colorB, colorA);
      [*] = ;
      [*] = ;//Gec hotfix
      [*] = ;//elmTextHandle := _gui_CreateText('value', elmParentHandle, sValue, 'halParentLeft', 'valParentTop', -(spotWidth div 2), -(spotHeight div 2), width, height, 'halMiddle', 'valMiddle', fontHandle, sColorR, sColorG, sColorB, sColorA);
      [*] = ;elmTextHandle := _gui_CreateText('value', elmParentHandle, sValue, 'halParentLeft', 'valParentTop', -(width div 2), -(height div 2), width, height, 'halMiddle', 'valMiddle', fontHandle, sColorR, sColorG, sColorB, sColorA);
      [*] = ;_gui_CreateText('value', elmTextHandle, sValue, 'halParentLeft', 'valParentTop', 1, -1, width, height, 'halMiddle', 'valMiddle', fontHandle, colorR, colorG, colorB, colorA);
      [*] = ;
      [*] = ;_gui_FadeElement(elmParentHandle, 0.25, True, False, False);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

