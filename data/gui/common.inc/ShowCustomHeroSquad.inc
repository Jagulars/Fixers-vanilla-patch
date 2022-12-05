section.begin
   Name = ShowCustomHeroSquad
   Description : struct.begin
      [*] = ;IntRegister0 - parent window handle
   struct.end
   Code : struct.begin
      [*] = ;const cEventState = 'EventCustomHeroSquad';
      [*] = ;const cBtnLevelUp = 300;
      [*] = ;
      [*] = ;var parentHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\SHOWCUSTOMHEROSQUAD';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;function GetUnitSlotsCount(battle : TInetBattle; rank : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := rank;
      [*] = ;   IntRegister1 := battle.hero[battle.curhero].leader;
      [*] = ;   MapExecuteState('GetUnitSlotsByRank');
      [*] = ;   Result := IntRegister0;
      [*] = ;end;
      [*] = ;
      [*] = ;var fontHandle1, fontHandle2, fontHandle3 : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_smallest,'',fontHandle1);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandle3);
      [*] = ;
      [*] = ;procedure ShowCustomHeroSquad(battle : TInetBattle);
      [*] = ;begin
      [*] = ;   var shopPickedUnitRank, pickedSlotRank, pickedUnitRank : Integer = 0;
      [*] = ;   if (gIntRegister_InetShopPickedUnitID<>0) then
      [*] = ;   begin
      [*] = ;      var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, gIntRegister_InetShopPickedUnitID);
      [*] = ;      shopPickedUnitRank := ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;   end;
      [*] = ;   if (gIntRegister_InetPickedUnitSlot<>0) then
      [*] = ;   begin
      [*] = ;      pickedSlotRank := _inet_GetUnitRank(gIntRegister_InetPickedUnitSlot);
      [*] = ;      var unitID : Integer = battle.hero[battle.curhero].arrunits[gIntRegister_InetPickedUnitSlot].unitid;
      [*] = ;      var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;      pickedUnitRank := ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   var arrIndex : Integer = 0;
      [*] = ;   for i:=0 to 3 do // 5th rank is temporary for no space unit add
      [*] = ;   begin
      [*] = ;      var slotCount : Integer;
      [*] = ;      case i of
      [*] = ;         0 : slotCount := 6;
      [*] = ;         1 : slotCount := 4;
      [*] = ;         2 : slotCount := 3;
      [*] = ;         3 : slotCount := 2;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('', parentHandle, 'shell.rank.'+IntToStr(i+1), 'halParentLeft', 'valParentBottomHeight', -101, -25-97*i, 0, 0, 0);
      [*] = ;
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to slotCount-1 do
      [*] = ;      begin
      [*] = ;         arrIndex := arrIndex+1;
      [*] = ;         var openSlots : Integer;
      [*] = ;         var rank : Integer = i+1;
      [*] = ;         openSlots := GetUnitSlotsCount(battle, rank);
      [*] = ;
      [*] = ;         var posX : Integer = j*74;
      [*] = ;         var posY : Integer = -i*97;
      [*] = ;         if ((j+1)<=slotCount) then
      [*] = ;         begin
      [*] = ;            var matBlank : String = 'misc.blank.black.alpha.0';
      [*] = ;            var unitID : Integer = battle.hero[battle.curhero].arrunits[_inet_GetUnitIndex(rank, j)].unitid;
      [*] = ;            if ((j+1)<=openSlots) {or (unitID<>0)} then
      [*] = ;            begin
      [*] = ;               var pUnitID : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;               var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnitID, 'Rank');
      [*] = ;
      [*] = ;               var elmSlotHandle : Integer;
      [*] = ;               var swapAvailable : Boolean = True;
      [*] = ;               if (pickedSlotRank<unitRank) then
      [*] = ;                  swapAvailable := False;
      [*] = ;
      [*] = ;               var highlight : Boolean = False;
      [*] = ;               var disabled : Boolean = False;
      [*] = ;               var checkon : Boolean = False;
      [*] = ;
      [*] = ;               if (gIntRegister_InetPickedUnitSlot<>0) then
      [*] = ;               begin
      [*] = ;                  if (rank=pickedSlotRank) and (arrIndex=gIntRegister_InetPickedUnitSlot)  then
      [*] = ;                     checkon := True;
      [*] = ;
      [*] = ;                  if (pickedUnitRank<>0) and (rank>=pickedUnitRank) and (swapAvailable) then
      [*] = ;                     highlight := True
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (shopPickedUnitRank<>0) then
      [*] = ;               begin
      [*] = ;                  if (rank>=shopPickedUnitRank) and (unitID=0) then
      [*] = ;                     highlight := True
      [*] = ;                  else
      [*] = ;                     disabled := True;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (pickedUnitRank<>0) then
      [*] = ;                  begin
      [*] = ;                     if (rank>=pickedUnitRank) and (swapAvailable) then
      [*] = ;                        highlight := True
      [*] = ;                     else
      [*] = ;                        disabled := True;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               elmSlotHandle := _gui_CreateImage('open', parentHandle, 'heropanel.unit.slot.empty', 'halParentLeft', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;               var elmHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'astral.bonus.unit.frame', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;
      [*] = ;               const cBtnBaseTagSlot = 1000;
      [*] = ;               var tag : Integer = cBtnBaseTagSlot+arrIndex;
      [*] = ;               if (unitID<>0) then
      [*] = ;               begin
      [*] = ;                  var hint : String;// = GetLocaleTableListItemByID('unit', IntToStr(unitID))+' ('+GetLocaleTableListItemByID('gui', IntToStr(10))+' '+IntToStr(unitRank)+')';
      [*] = ;                  elmHandle := _gui_CreateImage('', elmSlotHandle, 'icon.unit.'+IntToStr(unitID), 'halParentLeft', 'valParentTop', 0, 0, 70, 93, Tag);
      [*] = ;
      [*] = ;                  const cPriceBoxHeight = 17;
      [*] = ;                  var text : String = IntToStr(_inet_GetUnitPrice(unitID, battle.hero[battle.curhero].arrunits[arrIndex].level));
      [*] = ;                  var w, h : Integer;
      [*] = ;                  GetGUIElementFontTextFormatRect(fontHandle2, text, w, h);
      [*] = ;                  var elmPriceHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'misc.blank.black.alpha.1', 'halParentRightWidth', 'valParentBottomHeight', 0, 0, w+6, cPriceBoxHeight, 0);
      [*] = ;                  SetGUIElementUseUserColor(elmPriceHandle, True);
      [*] = ;                  SetGUIElementUserColor(elmPriceHandle, 1, 1, 1, 0.7);
      [*] = ;                  var elmTextHandle : Integer = _gui_CreateText('', elmPriceHandle, text, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmPriceHandle), GetGUIElementHeight(elmPriceHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;
      [*] = ;                  var elmBtnHandle : Integer = _gui_CreateButton('unit_slot', elmSlotHandle, 'unit_slot', 'heropanel.unit.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 70, 93, '', '', tag);
      [*] = ;                  _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipUnit',cFT_UnitTemplate,unitID,0,0,cEventState,'1');
      [*] = ;                  if (disabled) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementUserBlend(elmHandle, 0.6);
      [*] = ;                     SetGUIElementUserBlend(elmBtnHandle, 0.6);
      [*] = ;                     //SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', matBlank{'heropanel.unit.slot.cover.normal'}, 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                     SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.unit.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (checkon) then
      [*] = ;                     SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;                  //CreateUnitMeters(elmBtnHandle, goHeroHnd, pSlotUnit, pUnits);
      [*] = ;                  const cBtnDismiss = 200;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('dismiss', elmBtnHandle, 'dismiss', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRight', 'valParentTop', -18, 0, 18, 18, cEventState, 'gui|641', cBtnDismiss);
      [*] = ;                  SetGUIElementStringTag(elmBtnHandle, 'dismiss');
      [*] = ;                  SetGUIElementVisible(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  if (highlight) then
      [*] = ;                  begin
      [*] = ;                     elmHandle := _gui_CreateImage('', elmSlotHandle, 'heropanel.unit.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;                     elmBtnHandle := _gui_CreateButton('unitslot_highlight', elmSlotHandle, '', matBlank, 'halParentLeft', 'valParentTop', 1, 1, 70, 93, cEventState, hint, tag);
      [*] = ;                     SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.unit.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;                     SetGUIElementUserBlend(elmHandle, 0.4);
      [*] = ;                     SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;                  end
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (highlight) then
      [*] = ;                  begin
      [*] = ;                     elmHandle := _gui_CreateImage('open', elmSlotHandle, 'heropanel.unit.slot.empty.highlight', 'halParentLeft', 'valParentBottomHeight', 0, 0, 0, 0, 0);
      [*] = ;                     var elmBtnHandle : Integer = _gui_CreateButton('unitslot_highlight', elmSlotHandle, '', matBlank, 'halParentLeft', 'valParentTop', 0, 0, 70, 93, cEventState, '', tag);
      [*] = ;                     SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.unit.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;                     SetGUIElementUserBlend(elmHandle, 0.4);
      [*] = ;                     SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (disabled) then
      [*] = ;                  begin
      [*] = ;                     elmSlotHandle := _gui_CreateImage('open', parentHandle, 'heropanel.unit.slot.empty.disabled', 'halParentLeft', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;                     SetGUIElementUserBlend(elmSlotHandle, 0.5);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     elmHandle := _gui_CreateImage('', elmSlotHandle, matBlank, 'halParentLeft', 'valParentBottomHeight', 1, 3, 0, 0, 0);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var elmSlotHandle : Integer = _gui_CreateImage('open', parentHandle, {matBlank}'heropanel.unit.slot.empty', 'halParentLeft', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;               var elmHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'astral.bonus.unit.frame', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;               elmHandle := _gui_CreateImage('closed', elmSlotHandle, 'heropanel.unit.slot.closed', 'halParentLeft', 'valParentBottomHeight', 0, 0, 0, 0, 0);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var elmSlotHandle : Integer = _gui_CreateImage('open', parentHandle, {matBlank}'heropanel.unit.slot.empty', 'halParentLeft', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;            var elmHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'astral.bonus.unit.frame', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;            elmHandle := _gui_CreateImage('closed', elmSlotHandle, 'heropanel.unit.slot.closed', 'halParentLeft', 'valParentBottomHeight', 0, 0, 0, 0, 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;   ShowCustomHeroSquad(gEditorCustomPlayerTemporary)
      [*] = ;else
      [*] = ;if (gBoolRegister_IsHotSeat) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_HotSeatActivePlayer=0) then
      [*] = ;      ShowCustomHeroSquad(gHotSeatPlayer1)
      [*] = ;   else
      [*] = ;      ShowCustomHeroSquad(gHotSeatPlayer2)
      [*] = ;end
      [*] = ;else
      [*] = ;   ShowCustomHeroSquad(gInetBattle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

