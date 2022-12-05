section.begin
   Name = vvk.map.CreateProvinceIncomeTooltip
   Description : struct.begin
      [*] = ;IntRegister0 - 0-gold, 1-gem
      [*] = ;FloatRegister0 - total value
      [*] = ;StringRegister0 - stats string (see GetGoldAndGemIncomeExt)
      [*] = ;RET:
      [*] = ;   StringRegister0 - resulting tooltip
   struct.end
   Code : struct.begin
      [*] = ;procedure Fixed10ToStr(v : Integer; prefix : Boolean; var dst_str : String);
      [*] = ;begin
      [*] = ;   var temp_str : String;
      [*] = ;   var l : Integer;
      [*] = ; 
      [*] = ;   temp_str :=IntToStr(v);
      [*] = ;   if (v > 0) and prefix then temp_str := '+'+temp_str;
      [*] = ;   l := StrLength(temp_str);
      [*] = ;   if abs(v) < 10 then
      [*] = ;   begin
      [*] = ;      if v = 0 then
      [*] = ;         dst_str := '0'
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if v < 0 then dst_str := '-'
      [*] = ;         else if v > 0 then dst_str := '+'
      [*] = ;         else dst_str := '';
      [*] = ;         dst_str := dst_str + '0';
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      dst_str := SubStr(temp_str,1,l-1);
      [*] = ;   if (v mod 10) <> 0 then
      [*] = ;      dst_str := dst_str + '.' + SubStr(temp_str,l,1);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _StrReplace(src_str, search_str : String; fixed10 : Integer; prefix : Boolean; var dst_str : String);
      [*] = ;begin
      [*] = ;   var t,str : String;
      [*] = ;
      [*] = ;   Fixed10ToStr(fixed10,prefix,str);
      [*] = ;   t := StrReplace(src_str,search_str,str);
      [*] = ;   dst_str := t;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var v : Float = FloatRegister0;
      [*] = ;var gs : String = StringRegister0;
      [*] = ;var text,str : String;
      [*] = ;var k : Integer;
      [*] = ;      
      [*] = ;var bDisplayDetails : Boolean = not _map_CheckGenesisMode(gc_GM_ProvinceDetails);
      [*] = ;
      [*] = ;if _console_GetIntVar('DebugShowExtraInfo') > 0 then
      [*] = ;begin
      [*] = ;   text := 'Base: %base%'+gc_gui_BreakLine+'Outer: %outer%'+gc_gui_BreakLine+'Inner: %inner%'+gc_gui_BreakLine+'Sites: %sites%';
      [*] = ;   text := text+gc_gui_BreakLine+'Ritual: %ritual%'+gc_gui_BreakLine+'Defender: %defender%';
      [*] = ;   text := text+gc_gui_BreakLine+'LVL: %level_p%%, RACE: %race_p%%, MOOD: %mood_p%%'+gc_gui_BreakLine+'Explore: %explore%';
      [*] = ;   text := text+gc_gui_BreakLine+'Outer and Defenders: %outer_def_p%%';
      [*] = ;   if mode = 0 then
      [*] = ;      text := text+gc_gui_BreakLine+'Site perc: %site_p%%'+gc_gui_BreakLine+'Units plunder: %units_p%%'
      [*] = ;   else
      [*] = ;      text := StrReplace(text,'%mood_p%%','%mood%');
      [*] = ;   text := text+gc_gui_BreakLine+'-----------------------'+gc_gui_BreakLine+'TOTAL: '+FloatToStr(v);
      [*] = ;   //text := StrReplace(gs,'|','#');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if bDisplayDetails then
      [*] = ;   begin
      [*] = ;      if mode = 0 then
      [*] = ;         text := GetLocaleTableListItemByID('gui', 'province_income_extra_info.gold')
      [*] = ;      else
      [*] = ;         text := GetLocaleTableListItemByID('gui', 'province_income_extra_info.gem');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if mode = 0 then
      [*] = ;         text := GetLocaleTableListItemByID('ability', '75')
      [*] = ;      else
      [*] = ;         text := GetLocaleTableListItemByID('ability', '76');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if bDisplayDetails then
      [*] = ;for k := 0 to 20-1 do
      [*] = ;begin
      [*] = ;   case k of
      [*] = ;      0 : _StrReplace(text,'%base%',_sa_GetAsInt(gs,k),false,text);
      [*] = ;      1 : _StrReplace(text,'%outer%',_sa_GetAsInt(gs,k),true,text);
      [*] = ;      2 : _StrReplace(text,'%inner%',_sa_GetAsInt(gs,k),true,text);
      [*] = ;      3 : _StrReplace(text,'%sites%',_sa_GetAsInt(gs,k),true,text);
      [*] = ;      4 : _StrReplace(text,'%ritual%',_sa_GetAsInt(gs,k),true,text);
      [*] = ;      5 : _StrReplace(text,'%defender%',_sa_GetAsInt(gs,k),true,text);
      [*] = ;      6 : _StrReplace(text,'%level_p%',_sa_GetAsInt(gs,k){+1000},true,text);
      [*] = ;      7 : _StrReplace(text,'%race_p%',_sa_GetAsInt(gs,k)-1000,true,text);
      [*] = ;      8 : begin
      [*] = ;         if mode = 0 then
      [*] = ;            _StrReplace(text,'%mood_p%',_sa_GetAsInt(gs,k),true,text)
      [*] = ;         else
      [*] = ;            _StrReplace(text,'%mood%',_sa_GetAsInt(gs,k),true,text);
      [*] = ;      end;
      [*] = ;      9 : _StrReplace(text,'%explore%',-1*_sa_GetAsInt(gs,k),true,text);
      [*] = ;      10 : _StrReplace(text,'%outer_def_p%',_sa_GetAsInt(gs,k),true,text);
      [*] = ;      11 : _StrReplace(text,'%site_p%',_sa_GetAsInt(gs,k),true,text);
      [*] = ;      12 : _StrReplace(text,'%units_p%',-1*_sa_GetAsInt(gs,k),true,text);
      [*] = ;      13 : break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;StringRegister0 := text;
   struct.end
section.end
