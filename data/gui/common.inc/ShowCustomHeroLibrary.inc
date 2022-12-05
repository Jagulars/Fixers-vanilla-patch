section.begin
   Name = ShowCustomHeroLibrary
   Code : struct.begin
      [*] = ;var parentHandle : Integer = IntRegister0;
      [*] = ;var level_to_show : Integer = IntRegister1;
      [*] = ;var fontHandle2 : String;
      [*] = ;
      [*] = ;const cEventState = 'EventCustomHeroLibrary';
      [*] = ;
      [*] = ;function CreateLibraryTabs(elmParentHandle, rank : Integer) : Integer;
      [*] = ;begin
      [*] = ;   const cBtnRank = 301;
      [*] = ;
      [*] = ;   var posX : Integer = 0;
      [*] = ;   var posY : Integer = 2;
      [*] = ;   var hint : String;
      [*] = ;   var elmBtnHandle,i : Integer;
      [*] = ;   var elmLibraryTabs : Integer = _gui_CreateImage('', elmParentHandle, 'shell.tabshero.4btn.background', 'halParentMiddle', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;   posX := 47;
      [*] = ;   posY := 12;
      [*] = ;
      [*] = ;   for i := 0 to 4-1 do
      [*] = ;   begin
      [*] = ;      hint := GetLocaleTableListItemByID('gui', IntToStr(10))+' '+IntToStr(i+1);
      [*] = ;      elmBtnHandle := _gui_CreateButton('library_rank_'+IntToStr(i+1), elmLibraryTabs, '', 'shell.btn.rank.'+IntToStr(i+1), 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, hint, cBtnRank+i);
      [*] = ;      if (rank=(i+1)) or (gBoolRegister_InetStartBattle) then
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;      if (rank=(i+1)) then
      [*] = ;         _gui_CreateImage('', elmLibraryTabs, 'shell.btn.rank.'+IntToStr(i+1)+'.pressed', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      posX := posX + 54;
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := elmLibraryTabs;
      [*] = ;end;
      [*] = ;
      [*] = ;const cBaseTagLearnSpellID = 1000;
      [*] = ;const cSpellRankMarginSide = 4;//16;
      [*] = ;const cSpellButtonSize = 56;
      [*] = ;const cPanelDX = 540;
      [*] = ;const cColumnsNo = 2;
      [*] = ;const cColumnsDX = (cPanelDX div cColumnsNo);
      [*] = ;const cColumnsDY = cSpellButtonSize*2+cSpellRankMarginSide;
      [*] = ;const cSpellRankMarginTop = cColumnsDY+cSpellRankMarginSide*2;
      [*] = ;const cMaxSchoolsNo = 7;
      [*] = ;const cPriceBoxHeight = 16;
      [*] = ;
      [*] = ;var i,p,s,l,id,tag,slot_hd,j,w,h : Integer;
      [*] = ;var s_id : array [0..(cMaxSchoolsNo+1)] of array [0..$40] of Integer;
      [*] = ;var s_no : array [0..(cMaxSchoolsNo+1)] of Integer;
      [*] = ;var s_x : array [0..(cMaxSchoolsNo+1)] of Integer;
      [*] = ;var s_y : array [0..(cMaxSchoolsNo+1)] of Integer;
      [*] = ;var text : String;
      [*] = ;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;
      [*] = ;for i := 0 to cMaxSchoolsNo-1 do
      [*] = ;begin
      [*] = ;   s_no[i] := 0;
      [*] = ;   if i=0 then
      [*] = ;   begin
      [*] = ;      if level_to_show > 1 then
      [*] = ;      begin
      [*] = ;         s_x[i] := 0;
      [*] = ;         s_y[i] := 0;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         s_x[i] := cSpellRankMarginSide+(cPanelDX div 2);
      [*] = ;         s_y[i] := cSpellRankMarginTop-cColumnsDY;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var school : Integer = i;
      [*] = ;      var extraY, reducedMargin : Integer = 0;
      [*] = ;      if level_to_show > 1 then
      [*] = ;      begin
      [*] = ;         extraY := cSpellButtonSize;
      [*] = ;         reducedMargin := cColumnsDY;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      s_x[i] := cSpellRankMarginSide+cColumnsDX*((i-1) mod cColumnsNo)+(cColumnsDX div 2);
      [*] = ;      s_y[i] := cSpellRankMarginTop-reducedMargin+(cColumnsDY+extraY)*((school-1) div cColumnsNo);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i:=1 to gPrototypeData.spells.number-1 do
      [*] = ;begin
      [*] = ;   p := ParserSelectByHandleByIndex(gPrototypeData.spells.handle,i);
      [*] = ;   id := ParserGetIntValueByKeyByHandle(p,'SpellID');;
      [*] = ;   l := ParserGetIntValueByKeyByHandle(p,'Level');
      [*] = ;   s := ParserGetIntValueByKeyByHandle(p,'School');
      [*] = ;   if ((l=level_to_show) or ((level_to_show=1) and (l=0))) and (s < cMaxSchoolsNo) and (id > 0) then
      [*] = ;   begin
      [*] = ;      s_id[s][s_no[s]] := i;
      [*] = ;      s_no[s] := s_no[s] + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to cMaxSchoolsNo-1 do
      [*] = ;begin
      [*] = ;   if s_no[i] > 0 then
      [*] = ;   begin
      [*] = ;      text := 'element.strip.148';
      [*] = ;      p := _gui_CreateImage('', parentHandle, text, 'halParentLeft', 'valParentTop', s_x[i]-(GetGUITextureWidth(text) div 2), s_y[i], 0, 0, 0);
      [*] = ;      text := 'gui|'+IntToStr(727+i);
      [*] = ;      _gui_CreateText('', p, text, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(p), GetGUIElementHeight(p), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      s_y[i] := s_y[i] + GetGUIElementHeight(p);
      [*] = ;      s_x[i] := s_x[i] - ((min(4, s_no[i]) * cSpellButtonSize) div 2);
      [*] = ;      if i = 0 then s_x[i] := s_x[i] + cSpellButtonSize div 2;
      [*] = ;      
      [*] = ;      for j := 0 to (s_no[i])-1 do
      [*] = ;      begin
      [*] = ;         p := ParserSelectByHandleByIndex(gPrototypeData.spells.handle,s_id[i][j]);
      [*] = ;         var pointPrice : Integer = ParserGetIntValueByKeyByHandle(p, 'PointPrice');
      [*] = ;         if (pointPrice>0) then
      [*] = ;         begin
      [*] = ;            id := ParserGetIntValueByKeyByHandle(p, 'SpellID');
      [*] = ;            tag := cBaseTagLearnSpellID+id;
      [*] = ;
      [*] = ;            _gui_CreateImage('' , parentHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', s_x[i]-5, s_y[i]-5,62,62,tag);
      [*] = ;            slot_hd := _gui_CreateImage('open', parentHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', s_x[i], s_y[i], 0, 0, 0);
      [*] = ;            _gui_CreateImage('', slot_hd, 'icon.spell.'+IntToStr(id), 'halParentLeft', 'valParentTop', 0, 0, 0, 0, tag);
      [*] = ;
      [*] = ;            text := IntToStr(_inet_GetSpellPrice(id));
      [*] = ;            GetGUIElementFontTextFormatRect(fontHandle2, text, w, h);
      [*] = ;            p := _gui_CreateImage('', slot_hd, 'misc.blank.black.alpha.1', 'halParentRightWidth', 'valParentBottomHeight', 0, 0, w+6, cPriceBoxHeight, 0);
      [*] = ;            SetGUIElementUseUserColor(p, True);
      [*] = ;            SetGUIElementUserColor(p, 1, 1, 1, 0.7);
      [*] = ;            _gui_CreateText('', p, text, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(p), GetGUIElementHeight(p), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;            p := _gui_CreateButton('spell_slot', slot_hd, 'spell_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;            _gui_ft_AttachHint_I4_S2(p,'VVK.FTooltipSpell',id,$20000,$20000,cFT_SpellTypeDefault,cEventState,'1');
      [*] = ;            
      [*] = ;            s_x[i] := s_x[i] + cSpellButtonSize;
      [*] = ;            if (j = 3) and (s_no[i] > 4) then //next row
      [*] = ;            begin
      [*] = ;               s_x[i] := s_x[i] - (2 * cSpellButtonSize) - (s_no[i]-4) * cSpellButtonSize div 2;
      [*] = ;               s_y[i] := s_y[i] + cSpellButtonSize;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;CreateLibraryTabs(GetGUIElementParentByIndex(parentHandle), gIntRegister_InetLibraryRankMode);
   struct.end
section.end

