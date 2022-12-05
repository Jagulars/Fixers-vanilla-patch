section.begin
   Name = map.CreateDiplomacyWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CREATEDIPLOMACYWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var displayMode : Integer = gIntRegister_DiplomacyWindowMode; // 0 = empty screen (no player selected), 1 = current situation, 2 = editing message, 3 = viewing my proposal, 4 = viewing their proposal
      [*] = ;
      [*] = ;function GetInputBox(sideName, partName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := GetGUIElementIndexByNameParent('diplomacy.dip_background.'+sideName+'.frame_'+partName+'.inputbox_'+partName+'.text', _gui_GetLayerI());
      [*] = ;end;
      [*] = ;
      [*] = ;function GetInputBoxIntValue(sideName, partName : String) : Integer;
      [*] = ;begin
      [*] = ;   var elmHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.'+sideName+'.frame_'+partName+'.inputbox_'+partName+'.text', _gui_GetLayerI());
      [*] = ;   Result := StrToInt(GetGUIElementText(elmHnd));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetInputBoxSimpleEnabled(inputBoxHnd : Integer; bEnabled : Boolean);
      [*] = ;begin
      [*] = ;   //var elmHnd : Integer = GetGUIElementIndexByNameParent('text', inputBoxHnd);
      [*] = ;   SetGUIAllowEvents(inputBoxHnd, bEnabled, False, False);
      [*] = ;   if bEnabled then
      [*] = ;      SetGUIElementUserBlend(inputBoxHnd, 1)
      [*] = ;   else
      [*] = ;      SetGUIElementUserBlend(inputBoxHnd, 0.5);
      [*] = ;end;
      [*] = ;
      [*] = ;var fontHandle, fontHandle2, fontHandle3, fontHandleH, fontHandleH2, fontHandleInput : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_smallest,'',fontHandle);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandle2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_large,'',fontHandle3); // HeaderM
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_largest,'',fontHandleH); // HeaderM
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_largest,'',fontHandleH2); // HeaderM
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Input',gc_gui_fontsize_default,'',fontHandleInput);
      [*] = ;
      [*] = ;const cDeclareWarBtnTag = 1;
      [*] = ;const cOfferPeaceBtnTag = 2;
      [*] = ;const cOfferUnionBtnTag = 3;
      [*] = ;const cCancelUnionBtnTag = 4;
      [*] = ;const cCancelTradeBtnTag = 5;
      [*] = ;const cOfferTradeBtnTag = 6;
      [*] = ;const cOfferExchangeBtnTag = 7;
      [*] = ;const cSendMessageBtnTag = 8;
      [*] = ;const cClearMessageBtnTag = 9;
      [*] = ;const cOfferResTag = 10;
      [*] = ;const cEditMessageBtnTag = 90;
      [*] = ;const cDemandResTag = 20;
      [*] = ;const cCancelTreatyTag = 31;
      [*] = ;const cOfferGoldIncTag = 32;
      [*] = ;const cOfferGemIncTag = 33;
      [*] = ;const cDemandGoldIncTag = 34;
      [*] = ;const cDemandGemIncTag = 35;
      [*] = ;const cOfferGoldTag = 36;
      [*] = ;const cOfferGemTag = 37;
      [*] = ;const cDemandGoldTag = 38;
      [*] = ;const cDemandGemTag = 39;
      [*] = ;const cShowMyMessage = 40;
      [*] = ;const cShowTheirMessage = 41;
      [*] = ;const cHideMessage = 42;
      [*] = ;const cAcceptDeal = 43;
      [*] = ;const cDeclineDeal = 44;
      [*] = ;const cAcceptBtnTag = 100;
      [*] = ;const cCancelBtnTag = 101;
      [*] = ;const cCloseBtnTag = 102;
      [*] = ;const cLogEvent1BtnTag = 200;
      [*] = ;const cInputMinus = 301;
      [*] = ;const cInputPlus = 302;
      [*] = ;const cInputBoxOfferGold = 410;
      [*] = ;const cInputBoxOfferGem = 420;
      [*] = ;const cInputBoxDemandGold = 415;
      [*] = ;const cInputBoxDemandGem = 425;
      [*] = ;const cBtnInputBoxOfferGoldCancel = 411;
      [*] = ;const cBtnInputBoxOfferGemCancel = 421;
      [*] = ;const cBtnInputBoxDemandGoldCancel = 416;
      [*] = ;const cBtnInputBoxDemandGemCancel = 426;
      [*] = ;const cInputBoxOfferGoldInc = 430;
      [*] = ;const cInputBoxOfferGemInc = 440;
      [*] = ;const cInputBoxDemandGoldInc = 435;
      [*] = ;const cInputBoxDemandGemInc = 445;
      [*] = ;const cBtnInputBoxOfferGoldIncCancel = 431;
      [*] = ;const cBtnInputBoxOfferGemIncCancel = 441;
      [*] = ;const cBtnInputBoxDemandGoldIncCancel = 436;
      [*] = ;const cBtnInputBoxDemandGemIncCancel = 446;
      [*] = ;const cPlayerTag = 1000;
      [*] = ;const cOfferItemTag = 2000;
      [*] = ;const cDemandItemTag = 3000;
      [*] = ;const cCancelOfferItemTag = 4000;
      [*] = ;const cCancelDemandItemTag = 5000;
      [*] = ;const cOfferProvinceTag = 6000;
      [*] = ;const cDemandProvinceTag = 7000;
      [*] = ;
      [*] = ;const cTradeMode = 2;
      [*] = ;const cExchangeMode = 3;
      [*] = ;const cCancelTradeMode = 4;
      [*] = ;
      [*] = ;// ----
      [*] = ;const cOfferMarginFrame = 8;
      [*] = ;const cFrameWidth = 56*4-4;
      [*] = ;const cFrameHeight = 42;
      [*] = ;const cBlankMat = 'misc.blank.black.alpha.0.25';
      [*] = ;const cInputBoxWidth = 124+30;
      [*] = ;const cInputBoxMaxChar = 5;
      [*] = ;const cEventState = 'map.EventDiplomacyWindow';
      [*] = ;const cInputTextPosX = 36;
      [*] = ;const cInputTextPosY = 1;
      [*] = ;const cPaddingOffer = 20;
      [*] = ;var myPlHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var j : Integer;
      [*] = ;const cOffersOffX = -235;
      [*] = ;const cOffersOffY = 424;
      [*] = ;const cDemandOffX = -cOffersOffX;
      [*] = ;const cDemandOffY = cOffersOffY;
      [*] = ;const cRowCount = 5;
      [*] = ;const cResOffX = cFrameWidth div cRowCount-3;
      [*] = ;const cResOffY = cFrameWidth div cRowCount-3;
      [*] = ;
      [*] = ;procedure DrawGoldGemBlock(mGiveGold, mGiveGem, mTakeGold, mTakeGem, parentElmOffer, parentElmDemand : Integer; var ShiftY1a, ShiftY2a : Integer; bAllowChanges : Boolean);
      [*] = ;begin
      [*] = ;   var elmFrameHandle, elmHandle, inputHandle, elmBtnHandle : Integer = 0;
      [*] = ;   var bOfferGoldGem : Boolean = False;
      [*] = ;   var bDemandGoldGem : Boolean = False;
      [*] = ;   var r_pos : TRectangle;
      [*] = ;   if (mGiveGold>0) then
      [*] = ;   begin
      [*] = ;      //cInputBoxOfferGold
      [*] = ;      elmFrameHandle := _gui_CreateFrameBorder('frame_offergold', parentElmOffer, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame, cFrameWidth, cFrameHeight);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;
      [*] = ;      _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;      inputHandle := _gui_CreateInputControl_VVK('inputbox_offergold',elmFrameHandle,IntToStr(mGiveGold),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;      //inputHandle := CreateInputBoxSimple('inputbox_offergold', elmFrameHandle, IntToStr(mGiveGold), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      if bAllowChanges then
      [*] = ;         elmBtnHandle := _gui_CreateButton('inputbox_offergold_ok', elmFrameHandle, '', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRightWidth', 'valParentTop', -1-13, 2+10, 0, 0, cEventState, 'gui|746', cBtnInputBoxOfferGoldCancel)
      [*] = ;      else
      [*] = ;         SetInputBoxSimpleEnabled(inputHandle, False);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentMiddle', 11, 0, 0, 0, 0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      SetGUIElementHint(elmHandle, GetLocaleTableListItemByID('gui', '187'));
      [*] = ;      
      [*] = ;      bOfferGoldGem := True;
      [*] = ;      ShiftY1a:=ShiftY1a+46;
      [*] = ;   end;
      [*] = ;   if (mGiveGem>0) then
      [*] = ;   begin
      [*] = ;      //cInputBoxOfferGem
      [*] = ;      elmFrameHandle := _gui_CreateFrameBorder('frame_offergem', parentElmOffer, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame+ShiftY1a, cFrameWidth, cFrameHeight);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;      _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;      inputHandle := _gui_CreateInputControl_VVK('inputbox_offergem',elmFrameHandle,IntToStr(mGiveGem),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;      //inputHandle := CreateInputBoxSimple('inputbox_offergem', elmFrameHandle, IntToStr(mGiveGem), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      if bAllowChanges then
      [*] = ;         elmBtnHandle := _gui_CreateButton('inputbox_offergem_ok', elmFrameHandle, '', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRightWidth', 'valParentTop', -1-13, 2+10, 0, 0, cEventState, 'gui|746', cBtnInputBoxOfferGemCancel)
      [*] = ;      else
      [*] = ;         SetInputBoxSimpleEnabled(inputHandle, False);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 11, 0, 0, 0, 0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      SetGUIElementHint(elmHandle, GetLocaleTableListItemByID('gui', '188'));
      [*] = ;      
      [*] = ;      bOfferGoldGem := True;
      [*] = ;      ShiftY1a:=ShiftY1a+46;
      [*] = ;   end;
      [*] = ;   if (mTakeGold>0) then
      [*] = ;   begin
      [*] = ;      //cInputBoxOfferGold
      [*] = ;      elmFrameHandle := _gui_CreateFrameBorder('frame_demandgold', parentElmDemand, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame, cFrameWidth, cFrameHeight);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;      _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;      inputHandle := _gui_CreateInputControl_VVK('inputbox_demandgold',elmFrameHandle,IntToStr(mTakeGold),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;      //inputHandle := CreateInputBoxSimple('inputbox_demandgold', elmFrameHandle, IntToStr(mTakeGold), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      if bAllowChanges then
      [*] = ;         elmBtnHandle := _gui_CreateButton('inputbox_demandgold_ok', elmFrameHandle, '', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRightWidth', 'valParentTop', -1-13, 2+10, 0, 0, cEventState, 'gui|746', cBtnInputBoxDemandGoldCancel)
      [*] = ;      else
      [*] = ;         SetInputBoxSimpleEnabled(inputHandle, False);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentMiddle', 11, 0, 0, 0, 0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      SetGUIElementHint(elmHandle, GetLocaleTableListItemByID('gui', '187'));
      [*] = ;      
      [*] = ;      bDemandGoldGem := True;
      [*] = ;      ShiftY2a:=ShiftY2a+46;
      [*] = ;   end;
      [*] = ;   if (mTakeGem>0) then
      [*] = ;   begin
      [*] = ;      //cInputBoxOfferGem
      [*] = ;      elmFrameHandle := _gui_CreateFrameBorder('frame_demandgem', parentElmDemand, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame+ShiftY2a, cFrameWidth, cFrameHeight);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;      _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;      inputHandle := _gui_CreateInputControl_VVK('inputbox_demandgem',elmFrameHandle,IntToStr(mTakeGem),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;      //inputHandle := CreateInputBoxSimple('inputbox_demandgem', elmFrameHandle, IntToStr(mTakeGem), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      if bAllowChanges then
      [*] = ;         elmBtnHandle := _gui_CreateButton('inputbox_demandgem_ok', elmFrameHandle, '', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRightWidth', 'valParentTop', -1-13, 2+10, 0, 0, cEventState, 'gui|746', cBtnInputBoxDemandGemCancel)
      [*] = ;      else
      [*] = ;         SetInputBoxSimpleEnabled(inputHandle, False);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 11, 0, 0, 0, 0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      SetGUIElementHint(elmHandle, GetLocaleTableListItemByID('gui', '188'));
      [*] = ;      
      [*] = ;      bDemandGoldGem := True;
      [*] = ;      ShiftY2a:=ShiftY2a+46;
      [*] = ;   end;
      [*] = ;   if (bOfferGoldGem) then
      [*] = ;      ShiftY1a:=ShiftY1a+cPaddingOffer;
      [*] = ;   if (bDemandGoldGem) then
      [*] = ;      ShiftY2a:=ShiftY2a+cPaddingOffer;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DrawResourceBlockAlreadyTrade(elmParentHnd, plIndex : Integer; var Count1a, Count2a, ShiftY1a, ShiftY2a : Integer);
      [*] = ;begin
      [*] = ;   for j:=0 to gc_MaxTradeResCount-1 do
      [*] = ;   begin
      [*] = ;      var resID : Integer = j+1;
      [*] = ;      var elmPlayerOffersHandle, elmImageHandle, elmBtnHandle : Integer;
      [*] = ;      if (gArrDiplomacy[myPlIndex][plIndex].trade.arrResources[j]) then
      [*] = ;      begin
      [*] = ;         elmPlayerOffersHandle := _gui_CreateFrameBorder('', elmParentHnd, 'halParentMiddle', 'valParentTop', cOffersOffX-cResOffX-cResOffX+(Count1a mod cRowCount)*(cResOffX+4)-8, cOffersOffY+ShiftY1a+(Count1a div cRowCount)*(cResOffY+4), cResOffX, cResOffY{cFrameHeight-4});
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateImage('', elmPlayerOffersHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, 0);
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'map.resource.'+IntToStr(resID)+'.36x36', 'halParentMiddle', 'valParentMiddle', -1, 0, 0, 0, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, cEventState, 'tooltip|castle_resource_'+IntToStr(resID)+'_yes', cOfferResTag+j-1);
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.7);
      [*] = ;         SetGUIElementUserBlend(elmBtnHandle, 0.2);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         Count1a:=Count1a+1;
      [*] = ;      end;
      [*] = ;      if (gArrDiplomacy[plIndex][myPlIndex].trade.arrResources[j]) then
      [*] = ;      begin
      [*] = ;         elmPlayerOffersHandle := _gui_CreateFrameBorder('', elmParentHnd, 'halParentMiddle', 'valParentTop', cDemandOffX-cResOffX-cResOffX+(Count2a mod cRowCount)*(cResOffX+4)-8, cDemandOffY+ShiftY2a+(Count2a div cRowCount)*(cResOffY+4), cResOffX, cResOffY);
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateImage('', elmPlayerOffersHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, 0);
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'map.resource.'+IntToStr(resID)+'.36x36', 'halParentMiddle', 'valParentMiddle', -1, 0, 0, 0, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, cEventState, 'tooltip|castle_resource_'+IntToStr(resID)+'_yes', cDemandResTag+j-1);
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.7);
      [*] = ;         SetGUIElementUserBlend(elmBtnHandle, 0.2);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         Count2a:=Count2a+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DrawResourceBlock(elmParentHnd, plIndex : Integer; var Count1, Count2, ShiftY1, ShiftY2, Count1a, Count2a, ShiftY1a, ShiftY2a : Integer; bDrawOnHand, bAllowChanges : Boolean);
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;   var elmPlayerOffersHandle, elmImageHandle, elmBtnHandle, elmTextHandle : Integer;
      [*] = ;   for j:=1 to gPrototypeData.resources.number-1 do
      [*] = ;   begin
      [*] = ;      var resID : Integer = j;
      [*] = ;      //Offer
      [*] = ;      IntRegister0 := resID;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'GetResCount');
      [*] = ;      var res1 : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := resID;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetResCount');
      [*] = ;      var res2 : Integer = IntRegister1;
      [*] = ;
      [*] = ;      if gArrDiplomacy[myPlIndex][plIndex].trade.arrResources[j-1] then
      [*] = ;      begin
      [*] = ;         res1 := res1+1;
      [*] = ;         res2 := res2-1;
      [*] = ;      end;
      [*] = ;      if gArrDiplomacy[plIndex][myPlIndex].trade.arrResources[j-1] then
      [*] = ;      begin
      [*] = ;         res1 := res1-1;
      [*] = ;         res2 := res2+1;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      var hint : String;
      [*] = ;      if res1 > 0 then
      [*] = ;         hint := 'tooltip|castle_resource_'+IntToStr(resID)+'_yes'
      [*] = ;      else
      [*] = ;         hint := 'resource|'+IntToStr(resID);
      [*] = ;      
      [*] = ;      res1 := res1 - _diplomacy_GetReservedResCount(myPlIndex, -1, resID);
      [*] = ;      res2 := res2 - _diplomacy_GetReservedResCount(plIndex, -1, resID);
      [*] = ;
      [*] = ;      var bOffered : Boolean = False;
      [*] = ;      if (Res1>0) then
      [*] = ;      begin
      [*] = ;         if (not gDiplMessage.tradeGive.arrResources[j-1]) then
      [*] = ;         begin
      [*] = ;            if (bDrawOnHand) and bAllowChanges then
      [*] = ;            begin
      [*] = ;               elmPlayerOffersHandle := _gui_CreateFrameBorder('', elmParentHnd, 'halParentLeft', 'valParentTop', cResOffX-cResOffX div 2+(Count1 mod cRowCount)*(cResOffX+4)-5, ShiftY1+(Count1 div cRowCount)*(cResOffY+4), cResOffX, cResOffY);
      [*] = ;               var elmSlotHandle : Integer = _gui_CreateImage('', elmPlayerOffersHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, 0);
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'map.resource.'+IntToStr(resID)+'.36x36', 'halParentMiddle', 'valParentMiddle', -1, 0, 0, 0, 0);
      [*] = ;               elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, cEventState, hint, cOfferResTag+j-1);
      [*] = ;               if (Res2 > 0) and (not SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer')) then // don't allow offering of resources the other player already has unless it's another human player (so you can't be sure which resources he already has)
      [*] = ;               begin
      [*] = ;                  SetGUIElementUserBlend(elmImageHandle, 0.5);
      [*] = ;                  SetGUIElementUserBlend(elmBtnHandle, 0.7);
      [*] = ;                  SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;               end;
      [*] = ;               var width, height : Integer;
      [*] = ;               GetGUIElementFontTextFormatRect(fontHandle2, IntToStr(Res1), width, height);
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmBtnHandle, 'pixel.0.0.0', 'halParentRight', 'valParentBottom', -width-6, -height+2, width+6, height-2, 0);
      [*] = ;               SetGUIElementUserBlend(elmImageHandle, 1);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmImageHandle, IntToStr(Res1), 'halParentLeft', 'valParentTop', 0, 1, GetGUIElementWidth(elmImageHandle), GetGUIElementHeight(elmImageHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.7);
      [*] = ;               Count1:=Count1+1;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            elmPlayerOffersHandle := _gui_CreateFrameBorder('', elmParentHnd, 'halParentMiddle', 'valParentTop', cOffersOffX-cResOffX-cResOffX+(Count1a mod cRowCount)*(cResOffX+4)-8, cOffersOffY+ShiftY1a+(Count1a div cRowCount)*(cResOffY+4), cResOffX, cResOffY{cFrameHeight-4});
      [*] = ;            var elmSlotHandle : Integer = _gui_CreateImage('', elmPlayerOffersHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, 0);
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'map.resource.'+IntToStr(resID)+'.36x36', 'halParentMiddle', 'valParentMiddle', -1, 0, 0, 0, 0);
      [*] = ;            elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, cEventState, hint, cOfferResTag+j-1);
      [*] = ;            if not bAllowChanges then
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            bOffered := True;
      [*] = ;            Count1a:=Count1a+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //Demand
      [*] = ;      if (not bOffered) and (res2 > 1) then
      [*] = ;      begin
      [*] = ;         if (not gDiplMessage.tradeTake.arrResources[j-1]) then
      [*] = ;         begin
      [*] = ;            if (bDrawOnHand) and bAllowChanges then
      [*] = ;            begin
      [*] = ;               elmPlayerOffersHandle := _gui_CreateFrameBorder('', elmParentHnd, 'halParentRightWidth', 'valParentTop', (Count2 mod cRowCount)*(cResOffX+4)-7-cRowCount*cResOffX, ShiftY1+(Count2 div cRowCount)*(cResOffY+4), cResOffX, cResOffY);
      [*] = ;               var elmSlotHandle : Integer = _gui_CreateImage('', elmPlayerOffersHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, 0);
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'map.resource.'+IntToStr(resID)+'.36x36', 'halParentMiddle', 'valParentMiddle', -1, 0, 0, 0, 0);
      [*] = ;               elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, cEventState, hint, cDemandResTag+j-1);
      [*] = ;               if Res1 >0 then
      [*] = ;               begin
      [*] = ;                  SetGUIElementUserBlend(elmImageHandle, 0.5);
      [*] = ;                  SetGUIElementUserBlend(elmBtnHandle, 0.7);
      [*] = ;                  SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;               end;
      [*] = ;               {var width, height : Integer;
      [*] = ;               GetGUIElementFontTextFormatRect(fontHandle2, IntToStr(Res2), width, height);
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmBtnHandle, 'pixel.0.0.0', 'halParentRight', 'valParentBottom', -width-6, -height+2, width+6, height-2, 0);
      [*] = ;               SetGUIElementUserBlend(elmImageHandle, 1);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmImageHandle, IntToStr(Res2), 'halParentLeft', 'valParentTop', 0, 1, GetGUIElementWidth(elmImageHandle), GetGUIElementHeight(elmImageHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.7);}
      [*] = ;               Count2:=Count2+1;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            elmPlayerOffersHandle := _gui_CreateFrameBorder('', elmParentHnd, 'halParentMiddle', 'valParentTop', cDemandOffX-cResOffX-cResOffX+(Count2a mod cRowCount)*(cResOffX+4)-8, cDemandOffY+ShiftY2a+(Count2a div cRowCount)*(cResOffY+4), cResOffX, cResOffY);
      [*] = ;            var elmSlotHandle : Integer = _gui_CreateImage('', elmPlayerOffersHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, 0);
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'map.resource.'+IntToStr(resID)+'.36x36', 'halParentMiddle', 'valParentMiddle', -1, 0, 0, 0, 0);
      [*] = ;            elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, cEventState, hint, cDemandResTag+j-1);
      [*] = ;            if not bAllowChanges then
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            Count2a:=Count2a+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddProvinceInfoToHint(dummyHnd : Integer; var text : String);
      [*] = ;begin
      [*] = ;   IntRegister0 := 3;
      [*] = ;   IntRegister1 := -1;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHnd, 'GetGoldAndGemIncomeExt');
      [*] = ;   var goldIncome : Integer = IntRegister0;
      [*] = ;   var gemIncome : Integer = IntRegister1;
      [*] = ;   text := text+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('tooltip', 'map_infopanel_province_gold_income')+': '+IntToStr(goldIncome);
      [*] = ;   text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('tooltip', 'map_infopanel_province_gem_income')+': '+IntToStr(gemIncome);
      [*] = ;end;
      [*] = ;
      [*] = ;function FindBestFontSize(text : String; max_width : Integer; sizes_to_match : Integer; var width : Integer; var height : Integer; var font: String) : Integer;
      [*] = ;begin
      [*] = ;   var fontHandle : String;
      [*] = ;   var idx : Integer;
      [*] = ;   var sizes_array : array [0..gc_gui_max_sizes_number-1] of Integer;
      [*] = ;   var w,h :Integer;
      [*] = ;
      [*] = ;   sizes_array[0] := gc_gui_fontsize_smallest;
      [*] = ;   sizes_array[1] := gc_gui_fontsize_small;
      [*] = ;   sizes_array[2] := gc_gui_fontsize_default;
      [*] = ;
      [*] = ;   idx := sizes_to_match;
      [*] = ;
      [*] = ;   while idx > 0 do
      [*] = ;   begin
      [*] = ;      _gui_GetFont(gc_gui_fontsection_strategy,'Text',sizes_array[idx-1],'',fontHandle);
      [*] = ;
      [*] = ;      GetGUIElementFontTextFormatRect(fontHandle, text, w, h);
      [*] = ;      if (w <= max_width) then
      [*] = ;      break;
      [*] = ;      idx := idx - 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   font := fontHandle;
      [*] = ;   width := w;
      [*] = ;   height := h;
      [*] = ;
      [*] = ;   Result := idx;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateScrollerParentExt(ElementName : String; Parent : Integer; hAlign, vAlign, MaterialName : String; posX, posY, sizeX, sizeY, scrollX, scrollY, scrollH : Integer; showScroller : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var elmGuiLayer : Integer = AddNewElementByClassNameParent(ElementName, 'TXGuiLayer', 0, Parent);
      [*] = ;   SetGUIElementAlign(elmGuiLayer, hAlign, vAlign);
      [*] = ;   SetGUIElementAllPositionRect(elmGuiLayer, posX, posY, sizeX, sizeY);
      [*] = ;   SetGUIElementMaterial(elmGuiLayer, MaterialName);
      [*] = ;   SetGUIScrollEnabled(elmGuiLayer, True);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;   SetGUIElementAlign(elmVScroll, 'halParentLeft', 'valParentTop');
      [*] = ;   SetGUIElementMaterialOffset(elmVScroll, -1, 0);
      [*] = ;   SetGUIElementAllPositionRect(elmVScroll, scrollX, scrollY, 27, scrollH);
      [*] = ;   if (showScroller) then
      [*] = ;   begin
      [*] = ;      SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   SetGUIElementMaterial(elmVScroll, 'misc.blank.black.alpha.0');
      [*] = ;   SetGUIAllowEvents(elmGuiLayer, True, False, False);
      [*] = ;   Result := elmGuiLayer;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateGUIInput(elmName : String; parent : Integer; haligh, valign : String; posX, posY, defaultValue : Integer; pressState : String; tagMinus, tagPlus : Integer) : Integer;
      [*] = ;begin
      [*] = ;   const cInputWidth = 100;
      [*] = ;   const cInputHeight = 26;
      [*] = ;   var fontHandle : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_menu,'Input',gc_gui_fontsize_default,'',fontHandle);   // HeaderS
      [*] = ;   var elmInputHandle : Integer = _gui_CreateImage(elmName, parent, cBlankMat, haligh, valign, posX, posY, cInputWidth, cInputHeight, 0);
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('', elmInputHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', 0, 0, cInputHeight, cInputHeight, pressState, '', tagMinus);
      [*] = ;   elmBtnHandle := _gui_CreateButton('', elmInputHandle, '', 'common.scroller.right', 'halParentLeft', 'valParentTop',  GetGUIElementWidth(elmInputHandle)-cInputHeight, 0, cInputHeight, cInputHeight, pressState, '', tagPlus);
      [*] = ;   var value : Integer = defaultValue;
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('value', elmInputHandle, IntToStr(value), 'halParentLeft', 'valParentTop', 0,  0, GetGUIElementWidth(elmInputHandle), GetGUIElementHeight(elmInputHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   GetGUIElementIndexByNameParent('diplomacy.background.input_test_1.value', _gui_GetLayerI());
      [*] = ;   Result := elmInputHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetAttitudeName(Value: Integer; var Name : String);
      [*] = ;begin
      [*] = ;   Name := '';
      [*] = ;   var ind, minAttitude, maxAttitude: Integer;
      [*] = ;   var attitudesCount : Integer = gPrototypeData.attitudes.number;
      [*] = ;   for ind:=0 to attitudesCount-1 do
      [*] = ;   begin
      [*] = ;      var pAttitude : Integer = ParserSelectByHandleByIndex(gPrototypeData.attitudes.handle, ind);
      [*] = ;      minAttitude:=ParserGetIntValueByKeyByHandle(pAttitude, 'Min');
      [*] = ;      maxAttitude:=ParserGetIntValueByKeyByHandle(pAttitude, 'Max');
      [*] = ;      if (Value>=minAttitude) and (Value<=maxAttitude) then
      [*] = ;      begin
      [*] = ;         Name := GetLocaleTableListItemByID('attitude', IntToStr(ind));
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var top : Integer =  _gui_GetLayerI();
      [*] = ;var posX, posY, sizeX, sizeY : Integer;
      [*] = ;var Tag : Integer = 0;
      [*] = ;var elmImageHandle, elmBtnHandle, elmTextHandle : Integer;
      [*] = ;var text : String;
      [*] = ;var vAlign, hAlign : String = '';
      [*] = ;posX := 0;
      [*] = ;posY := 0;
      [*] = ;sizeX := 0; //width
      [*] = ;sizeY := 0; //height
      [*] = ;hAlign := 'halMiddle'; //horisontal alignment, possible values: halLeft, halMiddle, halRight
      [*] = ;vAlign := 'valBottomHeight'; //vertical alignment, possible values: valTop, valMiddle, valBottomHeight
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('diplomacy', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) {and GetGUIElementVisible(prevElmParentHandle)} then
      [*] = ;begin
      [*] = ;   var placeHolder : Boolean;
      [*] = ;   _gui_RemoveBlinkElement('btnPlayerOffer', placeHolder);
      [*] = ;   //_gui_RemoveBlinkElement('btnAcceptDeal', placeHolder);
      [*] = ;   //_gui_RemoveBlinkElement('btnDeclineDeal', placeHolder);
      [*] = ;   
      [*] = ;   bVisible := True;
      [*] = ;   {var tag : Integer = GetIntValueByName('Tag');
      [*] = ;   if (tag<>cClearMessageBtnTag) and (tag<>cOfferExchangeBtnTag) and (tag<>cOfferExchangeBtnTag) and (tag<>cEditMessageBtnTag) and ((tag<cPlayerTag) or (tag>=cOfferItemTag)) and (tag<>cShowMyMessage) and (tag<>cShowTheirMessage) and (tag<>cHideMessage) then
      [*] = ;   begin
      [*] = ;      var elmHandle : Integer = GetInputBox('offers', 'offergold');
      [*] = ;      if (elmHandle<>0) and GetGUIElementVisible(elmHandle) then
      [*] = ;         gDiplMessage.tradeGive.gold := StrToInt(GetGUIElementText(elmHandle));
      [*] = ;      elmHandle := GetInputBox('offers', 'offergem');
      [*] = ;      if (elmHandle<>0) and GetGUIElementVisible(elmHandle) then
      [*] = ;         gDiplMessage.tradeGive.gem := StrToInt(GetGUIElementText(elmHandle));
      [*] = ;      elmHandle := GetInputBox('demand', 'demandgold');
      [*] = ;      if (elmHandle<>0) and GetGUIElementVisible(elmHandle) then
      [*] = ;         gDiplMessage.tradeTake.gold := StrToInt(GetGUIElementText(elmHandle));
      [*] = ;      elmHandle := GetInputBox('demand', 'demandgem');
      [*] = ;      if (elmHandle<>0) and GetGUIElementVisible(elmHandle) then
      [*] = ;         gDiplMessage.tradeTake.gem := StrToInt(GetGUIElementText(elmHandle));
      [*] = ;   end;}
      [*] = ;end;
      [*] = ;
      [*] = ;sizeX := 1240;
      [*] = ;sizeY := 658+48+14; // 44 is header size
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'diplomacy', 'halParentMiddle', 'valParentMiddle', 0, 4, sizeX, sizeY, True);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.65+0.15);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.75+0.1);
      [*] = ;var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHeaderHandle, 'gui|98', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandleH, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;//_gui_RootWindowAdd(elmParentHandle,cRootWindowNormal{cRootWindowModal});
      [*] = ;_gui_RootWindowAdd(elmParentHandle,cRootWindowModal);
      [*] = ;
      [*] = ;//posX := -(sizeX div 2);
      [*] = ;//posY := -sizeY;
      [*] = ;const yGlobalOff = 22;
      [*] = ;var elmDiplomacyBackground : Integer = _gui_CreateImage('dip_background', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, yGlobalOff, GetGUIElementWidth(elmParentHandle), GetGUIElementHeight(elmParentHandle), Tag);
      [*] = ;//var elmDiplomacyBackground : Integer = _gui_CreateLargeWindow(elmParentHandle, 'dip_background', 'halParentMiddle', 'valParentBottomHeight', 0, 0, sizeX, sizeY, True);
      [*] = ;
      [*] = ;var elmHandle : Integer = _gui_CreateImage('btnAcceptFrame', elmDiplomacyBackground, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 0, -32-yGlobalOff, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('btnAccept', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'menu|47', cCloseBtnTag);
      [*] = ;
      [*] = ;var Count : Integer = 0;
      [*] = ;
      [*] = ;var pPlayer, pMyPlayer : Integer;
      [*] = ;var plHandle, pTmpHandle : Integer;
      [*] = ;var myPlName : String = GetPlayerNameInterfaceIO;
      [*] = ;
      [*] = ;var plProfileID : Integer = 0;
      [*] = ;var plIndex : Integer;
      [*] = ;var elmPlayerOffersHandle : Integer;
      [*] = ;var placeHolder : Boolean;
      [*] = ;
      [*] = ;var visibleCount : Integer = 0;
      [*] = ;for plIndex:=0 to gGame.map.players-1 do
      [*] = ;if plIndex <> myPlIndex then
      [*] = ;begin
      [*] = ;   _gui_RemoveBlinkElement('btnDiplomacyPlayer_'+IntToStr(plIndex), placeHolder);
      [*] = ;   plHandle := GetPlayerHandleByIndex(plIndex);
      [*] = ;   var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;   plProfileID := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;   if (SameText(cMode, 'cmPlayer') or (plProfileID > 0)) and (_plr_IsInGame(plHandle)) then
      [*] = ;   begin
      [*] = ;      if gArrDiplomacy[plIndex][myPlIndex].treaty <> 0 then
      [*] = ;      begin
      [*] = ;         visibleCount := visibleCount+1;
      [*] = ;         if (gIntRegister_DiplomacyActivePlayerID<0) then
      [*] = ;            gIntRegister_DiplomacyActivePlayerID := plIndex;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         if SameText(GetPlayerControlModeByHandle(plHandle),'cmPC') then
      [*] = ;            visibleCount := visibleCount+1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//const cDisableAgreements = false;
      [*] = ;
      [*] = ;var query : String = '';
      [*] = ;var queryPlName : String = '';
      [*] = ;
      [*] = ;var visibleIndex : Integer = 0;
      [*] = ;for plIndex:=0 to gGame.map.players-1 do
      [*] = ;if plIndex <> myPlIndex then
      [*] = ;begin
      [*] = ;   plHandle := GetPlayerHandleByIndex(plIndex);
      [*] = ;   var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;   if SameText(cMode, 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      case gGame.gameType of
      [*] = ;         gc_GameTypeHotseat : plProfileID := gArrHotseatProfiles[plIndex].avatar;
      [*] = ;         gc_GameTypeLanShard : plProfileID := gLanShardGame.arrLanPlayers[plIndex].profile.avatar;
      [*] = ;         else plProfileID := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   plProfileID := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;   if (SameText(cMode, 'cmPlayer') or (plProfileID>0)) and (_plr_IsInGame(plHandle)) then
      [*] = ;   begin
      [*] = ;      var treaty : Integer = gArrDiplomacy[plIndex][myPlIndex].treaty;
      [*] = ;      if treaty <> 0 then
      [*] = ;      begin
      [*] = ;         posX := (GetGUIElementWidth(elmDiplomacyBackground) div 2)-40*visibleCount+80*visibleIndex;
      [*] = ;         posY := 18-yGlobalOff;
      [*] = ;         var bSelected : Boolean = False;
      [*] = ;         var elmSmallPortraitHandle : Integer;
      [*] = ;         //if SameText(GetPlayerControlModeByHandle(plHandle),'cmPC') then
      [*] = ;         begin
      [*] = ;            elmSmallPortraitHandle := _gui_CreateImage('round_portrait_'+IntToStr(plIndex), elmDiplomacyBackground, 'astral.players.icon.small.'+IntToStr(plProfileID), 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;            
      [*] = ;            elmImageHandle := _gui_CreateImage('round_portrait_'+IntToStr(plIndex)+'_border', elmDiplomacyBackground, 'map.heroselection.browncircle', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;            
      [*] = ;            if (gArrDiplomacy[plIndex][myPlIndex].displayPriority > 0) then
      [*] = ;               _gui_CreateBlinkElement('btnDiplomacyPlayer_'+IntToStr(plIndex), elmImageHandle, 'gamepanel01.btn.round.73x73.highlight', false, 0, 0, 0, 0);
      [*] = ;            
      [*] = ;            SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;            SetGUIElementPressState(elmImageHandle, 'map.EventDiplomacyWindow');
      [*] = ;            SetGUIElementTag(elmImageHandle, cPlayerTag+plIndex);
      [*] = ;            SetGUIElementCursorByName(elmImageHandle, 'crHand');
      [*] = ;
      [*] = ;            var isTrade : Boolean = gArrDiplomacy[plIndex][myPlIndex].trade.trade;
      [*] = ;            var xOff : Integer = 0;
      [*] = ;            if (isTrade) then
      [*] = ;               xOff := 14;
      [*] = ;            var elmHnd : Integer = _gui_CreateImage('', elmImageHandle, 'icon.diplomacy.'+IntToStr(treaty-1), 'halParentMiddle', 'valParentBottom', -xOff, 0, 52 div 2, 52 div 2, 0);
      [*] = ;            SetGUIAllowEvents(elmHnd, True, False, False);
      [*] = ;            var textID : String;
      [*] = ;            case treaty of
      [*] = ;               cDeclareWarBtnTag : textID := '184';
      [*] = ;               cOfferPeaceBtnTag : textID := '185';
      [*] = ;               cOfferUnionBtnTag : textID := '186';
      [*] = ;            end;
      [*] = ;            SetGUIElementHint(elmHnd, GetLocaleTableListItemByID('gui', textID));
      [*] = ;
      [*] = ;            //elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, 'gui|'+IntToStr(178), cCancelTreatyTag);
      [*] = ;            if (isTrade) then
      [*] = ;            begin
      [*] = ;               elmHnd := _gui_CreateImage('', elmImageHandle, 'icon.diplomacy.'+IntToStr(4), 'halParentMiddle', 'valParentBottom', xOff, 0, 52 div 2, 52 div 2, 0);
      [*] = ;               SetGUIAllowEvents(elmHnd, True, False, False);
      [*] = ;               SetGUIElementHint(elmHnd, GetLocaleTableListItemByID('gui', '183'));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         {else
      [*] = ;         begin
      [*] = ;            //!!!Заглушка. Вставить портрет игрока!!!!
      [*] = ;            elmSmallPortraitHandle := _gui_CreateImage('', elmDiplomacyBackground, 'map.castle.tabs.btn.hero.normal', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;         end;}
      [*] = ;
      [*] = ;         if (plIndex=gIntRegister_DiplomacyActivePlayerID) then
      [*] = ;         begin
      [*] = ;            bSelected := True;
      [*] = ;            
      [*] = ;            var hint : String = '';
      [*] = ;            var displayPriority : Integer = gArrDiplomacy[plIndex][myPlIndex].displayPriority;
      [*] = ;            //var bMessageSent : Boolean = {(gDiplMessage.mType=0) and (}(gArrDiplomacy[myPlIndex][plIndex].message.mType>0) or (gArrDiplomacy[myPlIndex][plIndex].message.treaty>0){ and (gDiplMessage.treaty=0))}; //TODO, add check if i got already message for this ruler
      [*] = ;            if displayPriority > 0 then
      [*] = ;               _log_map(_log_name+'[Display Priority: '+IntToStr(displayPriority)+']')
      [*] = ;            else
      [*] = ;               _gui_RemoveBlinkElement('btnDiplomacy', gBoolRegister_BtnDiplomacyBlink);
      [*] = ;
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmDiplomacyBackground, 'map.heroselection.yellowcircle', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;            var portrait : String = 'astral.dialog.portrait.'+IntToStr(plProfileID-1);
      [*] = ;            var elmPortaitWindow : Integer = _gui_CreateSmallWindow(elmDiplomacyBackground, 'portraitwindow', 'halParentMiddle', 'valParentTop', 0, 130, GetGUITextureWidth(portrait), GetGUITextureHeight(portrait), false);
      [*] = ;            var elmPortraitHandle : Integer = _gui_CreateImage('', elmPortaitWindow, portrait, 'halParentMiddle', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'GetName');
      [*] = ;            var myName : String = StringRegister0;
      [*] = ;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'GetName');
      [*] = ;            var plName : String = StringRegister0;
      [*] = ;            
      [*] = ;            // between human players in lan shard games. 0 = pending/none, 1 = accepted, 2 = refused
      [*] = ;            var myDeal : Integer = gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message.deal;
      [*] = ;            var oppDeal : Integer = gArrDiplomacy[gIntRegister_DiplomacyActivePlayerID][myPlIndex].message.deal;
      [*] = ;            var dealSealed : Boolean = (myDeal > 0) or (oppDeal > 0);
      [*] = ;            //var canEditMessage : Boolean = (not dealSealed) and 
      [*] = ;
      [*] = ;            var elmHandle : Integer = _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, 105-7, 0, 0, 0);
      [*] = ;            _gui_CreateText('', elmHandle, plName, 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;            pPlayer := ParserSelectPlayer(plHandle);
      [*] = ;            pMyPlayer := ParserSelectPlayer(myPlHandle);
      [*] = ;            //var pArrPlayerRes : Integer = ParserSelectByHandleByKey(pPlayer,'Resources');
      [*] = ;            //var pArrMyPlayerRes : Integer = ParserSelectByHandleByKey(pMyPlayer,'Resources');
      [*] = ;            var pPlTreasury : Integer = ParserSelectByHandleByKey(pPlayer,'Treasury');
      [*] = ;            var pMyTreasury : Integer = ParserSelectByHandleByKey(pMyPlayer,'Treasury');
      [*] = ;
      [*] = ;            var mTreaty : Integer = gDiplMessage.treaty;
      [*] = ;            var mType : Integer = gDiplMessage.mType;
      [*] = ;            var mGiveGold, mGiveGem, mTakeGold, mTakeGem : Integer;
      [*] = ;
      [*] = ;            var isTrade : Boolean = gArrDiplomacy[plIndex][myPlIndex].trade.trade;
      [*] = ;            var bTradeMessage : Boolean = (mType=cTradeMode);
      [*] = ;            if (isTrade) and (not bTradeMessage) and (mType<>cExchangeMode) then // show current situation
      [*] = ;            begin
      [*] = ;               mGiveGold := gArrDiplomacy[myPlIndex][plIndex].trade.gold;
      [*] = ;               mGiveGem := gArrDiplomacy[myPlIndex][plIndex].trade.gem;
      [*] = ;               mTakeGold := gArrDiplomacy[plIndex][myPlIndex].trade.gold;
      [*] = ;               mTakeGem := gArrDiplomacy[plIndex][myPlIndex].trade.gem;
      [*] = ;            end
      [*] = ;            else // show proposal
      [*] = ;            begin
      [*] = ;               mGiveGold := gDiplMessage.tradeGive.gold;
      [*] = ;               mGiveGem := gDiplMessage.tradeGive.gem;
      [*] = ;               mTakeGold := gDiplMessage.tradeTake.gold;
      [*] = ;               mTakeGem := gDiplMessage.tradeTake.gem;
      [*] = ;            end;
      [*] = ;
      [*] = ;            //Offer buttons
      [*] = ;            var OpponentKarma : Integer = GetPlayerIntValueIndByHandle(plHandle,gc_map_PLStack_MapUnit_iKarma);
      [*] = ;            var attitude : Integer = gArrDiplomacy[plIndex][myPlIndex].attitude;
      [*] = ;            //const cBtnName = 'castle.hero.recruit.window.btn.recruit';
      [*] = ;            const cBtnName = 'common.btn';
      [*] = ;            //posX := -(12+GetGUITextureWidth(cBtnName+'.normal'));
      [*] = ;            posX := -(20+(GetGUIElementWidth(elmPortaitWindow)+GetGUITextureWidth(cBtnName+'.normal')) div 2);
      [*] = ;            posY := 128;
      [*] = ;            var yOff : Integer = 43;
      [*] = ;            sizeX := 160;
      [*] = ;            sizeY := 30;
      [*] = ;
      [*] = ;            var offerTradeTextID : String = '163';
      [*] = ;            if (isTrade) then
      [*] = ;            offerTradeTextID := '175';
      [*] = ;
      [*] = ;            case treaty of
      [*] = ;               gc_TreatyWar : 
      [*] = ;               begin
      [*] = ;                  const cBtnTextOffX = 3;//-1;
      [*] = ;                  const cBtnTextOffY = -3;//-1;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cOfferPeaceBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '160'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if (mTreaty=cOfferPeaceBtnTag) or dealSealed then // peace offer already included in the message
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cOfferTradeBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', offerTradeTextID), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if ((mTreaty=0) or (mType > 0)) or dealSealed then // cannot make business if peace offer not included
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cOfferExchangeBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '164'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if ((mTreaty=0) or (mType > 0)) or dealSealed then // cannot make business if peace offer not included
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;               end;
      [*] = ;               gc_TreatyPeace : 
      [*] = ;               begin
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cDeclareWarBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '161'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if ((mTreaty>0) or ((mType>0) and ((mType<4)))) or dealSealed then // cannot declare war with business offer
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cOfferUnionBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '162'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if ((mTreaty>0) or (mType = gc_MessageCancelTrade)) or dealSealed then // cannot offer union at same time as cancelling trade agreement
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  // delimiter
      [*] = ;                  posY := posY+yOff;
      [*] = ;
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cOfferTradeBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', offerTradeTextID), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if ((mTreaty=gc_TreatyWar) or (mType > 0)) or dealSealed then  // cannot declare war with business offer
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cOfferExchangeBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '164'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if ((mTreaty=gc_TreatyWar) or (mType > 0)) or dealSealed then   // cannot declare war with business offer
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  if (IsTrade) then
      [*] = ;                  begin
      [*] = ;                     posY := posY+yOff;
      [*] = ;                     elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cCancelTradeBtnTag);
      [*] = ;                     elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '176'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                     if (mTreaty=gc_TreatyWar) or (mTreaty=gc_TreatyUnion) or (mType=cCancelTradeMode) or dealSealed then // Trade always cancelled with war. Union cannot be offered with trade cancel.
      [*] = ;                        SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_TreatyUnion : 
      [*] = ;               begin
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cCancelUnionBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '174'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if (mTreaty>0) or (mType>0) or dealSealed then // cannot cancel union if other things are on the table
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  // delimiter
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cOfferTradeBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', offerTradeTextID), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if (mTreaty>0) or (mType>0) or dealSealed then // cannot offer trade if other things are on the table (normally you can offer union with other things but now already in union)
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  posY := posY+yOff;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cOfferExchangeBtnTag);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '164'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  if ((mTreaty>0) or (mType>0)) or dealSealed then // cannot offer exchange if other things are on the table (already in union)
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;                  if (IsTrade) then
      [*] = ;                  begin
      [*] = ;                     posY := posY+yOff;
      [*] = ;                     elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cBtnName, 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, cEventState, '', cCancelTradeBtnTag);
      [*] = ;                     elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '176'), 'halParentLeft', 'valParentTop', cBtnTextOffX, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                     if ((mTreaty=gc_TreatyWar) or (mType=cCancelTradeMode)) or dealSealed then // Trade always cancelled with war.
      [*] = ;                        SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentMiddle', 'valParentTop', posX, 119-21, 0, 0, 0);
      [*] = ;            _gui_CreateText('', elmHandle, 'gui|743', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;            
      [*] = ;            // enemies list
      [*] = ;            var enemyCount : Integer = 0;
      [*] = ;            var i : Integer;
      [*] = ;            for i:=0 to gGame.map.players-1 do
      [*] = ;            begin
      [*] = ;               if (i<>myPlIndex) and (plIndex<>i) then
      [*] = ;               begin
      [*] = ;                  var tmpPlHandle : Integer = GetPlayerHandleByIndex(i);  
      [*] = ;                  var tmpPlProfileID : Integer = GetPlayerIntValueIndByHandle(tmpPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;                  if (gGame.gameType = gc_GameTypeHotseat) and SameText(GetPlayerControlModeByHandle(tmpPlHandle), 'cmPlayer') then
      [*] = ;                     tmpPlProfileID := gArrHotseatProfiles[i].avatar;
      [*] = ;                  
      [*] = ;                  if (tmpPlProfileID>0) and (_plr_IsInGame(tmpPlHandle)) then
      [*] = ;                  begin
      [*] = ;                     var plTreaty : Integer = gArrDiplomacy[plIndex][i].treaty;
      [*] = ;                     var myTreaty : Integer = gArrDiplomacy[i][myPlIndex].treaty;
      [*] = ;                     if (plTreaty=1) and (myTreaty<>0) then
      [*] = ;                     begin
      [*] = ;                        const cEnemyPlSize = 52;
      [*] = ;                        var tmpPosX : Integer = -posX-round(cEnemyPlSize*1.5)+(enemyCount mod 4)*cEnemyPlSize;
      [*] = ;                        var tmpPosY : Integer = 119-21+36+(enemyCount div 4)*cEnemyPlSize;
      [*] = ;                        elmSmallPortraitHandle := _gui_CreateImage('', elmDiplomacyBackground, 'astral.players.icon.small.'+IntToStr(tmpPlProfileID), 'halParentMiddle', 'valParentTop', tmpPosX, tmpPosY, cEnemyPlSize, cEnemyPlSize, 0);
      [*] = ;                        elmImageHandle := _gui_CreateImage('', elmDiplomacyBackground, 'map.heroselection.browncircle', 'halParentMiddle', 'valParentTop', tmpPosX, tmpPosY, cEnemyPlSize, cEnemyPlSize, 0);
      [*] = ;                        SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;                        SetGUIElementPressState(elmImageHandle, 'map.EventDiplomacyWindow');
      [*] = ;                        SetGUIElementTag(elmImageHandle, cPlayerTag+i);
      [*] = ;                        SetGUIElementCursorByName(elmImageHandle, 'crHand');
      [*] = ;                        enemyCount := enemyCount+1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentMiddle', 'valParentTop', -posX, 119-21, 0, 0, 0);
      [*] = ;            _gui_CreateText('', elmHandle, 'gui|155', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;            if (enemyCount=0) then
      [*] = ;            begin
      [*] = ;               SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;               SetGUIElementUserColor(elmHandle, 0.75, 0.75, 0.75, 0.75);
      [*] = ;            end;
      [*] = ;
      [*] = ;            //const cBtnSendCloseOffY = 12;
      [*] = ;            //const cMainBtnName = 'castle.building.btn.main';
      [*] = ;            //const cBtnMainTextOffX = 0;//-1;
      [*] = ;            //const cBtnMainTextOffY = -1;//-1;
      [*] = ;            //var cBtnMainOffX : Integer = (GetGUITextureWidth(cMainBtnName+'.normal') div 2)+60-10;
      [*] = ;            const cBtnSendCloseOffY = 18;
      [*] = ;            const cMainBtnName = cBtnName;
      [*] = ;            const cBtnMainTextOffX = 0;
      [*] = ;            const cBtnMainTextOffY = -1;
      [*] = ;            var cBtnMainOffX : Integer = (GetGUITextureWidth(cMainBtnName+'.normal') div 2)+60;
      [*] = ;            
      [*] = ;            //Accept offer button
      [*] = ;            if (displayMode = 4) then
      [*] = ;            begin
      [*] = ;               if not dealSealed then
      [*] = ;               begin
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cMainBtnName, 'halParentMiddle', 'valParentBottomHeight', -cBtnMainOffX, cBtnSendCloseOffY-yGlobalOff, 0, 0, cEventState, '', cAcceptDeal);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|354', 'halParentLeft', 'valParentTop', cBtnMainTextOffX, cBtnMainTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  //_gui_CreateBlinkElement('btnAcceptDeal', elmBtnHandle, 'gamepanel01.btn.icon.66x67.highlight', false, 0, 6, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle)-12);
      [*] = ;                  
      [*] = ;                  IntRegister0 := myPlIndex;
      [*] = ;                  PlayerExecuteStateByHandle(plIndex, 'CheckMessage');
      [*] = ;                  if BoolRegister0 then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, True);
      [*] = ;                     SetGUIElementHint(elmBtnHandle, '');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementHint(elmBtnHandle, 'gui|246');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else //Send message button
      [*] = ;            if ((gDiplMessage.mType>0) or (mTreaty>0)) and (displayMode > 1) and (not dealSealed) then
      [*] = ;            begin
      [*] = ;               elmBtnHandle := _gui_CreateButton('btn_send_message', elmDiplomacyBackground, '', cMainBtnName, 'halParentMiddle', 'valParentBottomHeight', -cBtnMainOffX, cBtnSendCloseOffY-yGlobalOff, 0, 0, cEventState, '', cSendMessageBtnTag);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '169'), 'halParentLeft', 'valParentTop', cBtnMainTextOffX, cBtnMainTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;               
      [*] = ;               hint := '';
      [*] = ;               if _diplomacy_IsMessageDraftValid(hint) then
      [*] = ;               begin
      [*] = ;                  SetGUIElementEnabled(elmBtnHandle, True);
      [*] = ;                  SetGUIElementHint(elmBtnHandle, '');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                  SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            //else //Edit message button
      [*] = ;            //begin
      [*] = ;            //   elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cMainBtnName, 'halParentMiddle', 'valParentBottomHeight', -cBtnMainOffX, cBtnSendCloseOffY-yGlobalOff, 0, 0, cEventState, '', cEditMessageBtnTag);
      [*] = ;            //   elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|180', 'halParentLeft', 'valParentTop', cBtnMainTextOffX, cBtnMainTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;            //   if (mTreaty=0) and (mType=0) then
      [*] = ;            //      SetGUIElementEnabled(elmBtnHandle, True)
      [*] = ;            //   else
      [*] = ;            //      SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            //end;
      [*] = ;
      [*] = ;            //Refuse offer button
      [*] = ;            if (displayMode = 4) then
      [*] = ;            begin
      [*] = ;               if not dealSealed then
      [*] = ;               begin
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cMainBtnName, 'halParentMiddle', 'valParentBottomHeight', cBtnMainOffX, cBtnSendCloseOffY-yGlobalOff, 0, 0, cEventState, '', cDeclineDeal);
      [*] = ;                  elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|195', 'halParentLeft', 'valParentTop', cBtnMainTextOffX, cBtnMainTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;                  //_gui_CreateBlinkElement('btnDeclineDeal', elmBtnHandle, 'gamepanel01.btn.icon.66x67.highlight', false, 0, 6, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle)-12);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else // Clear message button
      [*] = ;            if ((gDiplMessage.mType>0) or (mTreaty>0)) and (displayMode > 1) and (not dealSealed) then
      [*] = ;            begin
      [*] = ;               if (displayMode = 3) then
      [*] = ;                  hint := GetLocaleTableListItemByID('gui', 'withdraw_message')
      [*] = ;               else
      [*] = ;                  hint := GetLocaleTableListItemByID('gui', '168'); // cancel message
      [*] = ;               
      [*] = ;               elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cMainBtnName, 'halParentMiddle', 'valParentBottomHeight', cBtnMainOffX, cBtnSendCloseOffY-yGlobalOff, 0, 0, cEventState, '', cClearMessageBtnTag);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmBtnHandle, hint, 'halParentLeft', 'valParentTop', cBtnMainTextOffX, cBtnMainTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;               if (mTreaty = 0) and (mType = 0) then
      [*] = ;                  SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            end;
      [*] = ;
      [*] = ;            // View my offer button
      [*] = ;            if (oppDeal < 1) and (gArrDiplomacy[myPlIndex][plIndex].message.mType > 0) and (myDeal > -1) then
      [*] = ;            begin
      [*] = ;               var text : String = '   '+myName+' >>';
      [*] = ;               var buttonTag : Integer = cShowMyMessage;
      [*] = ;               var imageMaterial : String = 'map.mainpanel.btn.diplomacy.normal';
      [*] = ;               
      [*] = ;               if (displayMode = 3) then
      [*] = ;               begin
      [*] = ;                  buttonTag := cHideMessage;
      [*] = ;                  imageMaterial := 'map.mainpanel.btn.provincelist.pressed';
      [*] = ;               end;
      [*] = ;               
      [*] = ;               posY := cBtnSendCloseOffY-yGlobalOff-50;
      [*] = ;               posX := 0;//-cBtnMainOffX*2-50;
      [*] = ;               if myDeal > 0 then
      [*] = ;               begin
      [*] = ;                  if (displayMode = 3) then
      [*] = ;                     text := '>>              <<'
      [*] = ;                  else
      [*] = ;                     text := '<<              >>';
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (gArrDiplomacy[plIndex][myPlIndex].message.mType > 0) and (oppDeal = 0) then
      [*] = ;                  posY := posY-50;
      [*] = ;               
      [*] = ;               elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cMainBtnName, 'halParentMiddle', 'valParentBottomHeight', posX, posY, 0, 0, cEventState, '', buttonTag);
      [*] = ;               if dealSealed then
      [*] = ;                  SetGUIElementHint(elmBtnHandle, 'gui|deal_sealed');
      [*] = ;               
      [*] = ;               if (displayMode = 3) then
      [*] = ;                  SetGUIElementVisibleProperties(elmBtnHandle, 'UpProperty', cMainBtnName + '.pressed', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmBtnHandle, text, 'halParentLeft', 'valParentTop', cBtnMainTextOffX, cBtnMainTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;               
      [*] = ;               // scroll icon
      [*] = ;               if myDeal < 1 then
      [*] = ;                  posX := posX-85;
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmDiplomacyBackground, imageMaterial, 'halParentMiddle', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;               if ((displayPriority and $ff00) > 0) then // if they have answered my offer
      [*] = ;                  _gui_CreateBlinkElement('btnPlayerOffer', elmImageHandle, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;            end;
      [*] = ;
      [*] = ;            // View their offer button
      [*] = ;            if (myDeal < 1) and (gArrDiplomacy[plIndex][myPlIndex].message.mType > 0) and (oppDeal > -1) then
      [*] = ;            begin
      [*] = ;               var text : String = '<< '+plName+'   ';
      [*] = ;               var buttonTag : Integer = cShowTheirMessage;
      [*] = ;               var imageMaterial : String = 'map.mainpanel.btn.diplomacy.normal';
      [*] = ;               
      [*] = ;               if (displayMode = 4) then
      [*] = ;               begin
      [*] = ;                  buttonTag := cHideMessage;
      [*] = ;                  imageMaterial := 'map.mainpanel.btn.provincelist.pressed';
      [*] = ;               end;
      [*] = ;               
      [*] = ;               posY := cBtnSendCloseOffY-yGlobalOff-50;
      [*] = ;               posX := 0;//cBtnMainOffX*2+50;
      [*] = ;               if oppDeal > 0 then
      [*] = ;               begin
      [*] = ;                  if (displayMode = 4) then
      [*] = ;                     text := '>>              <<'
      [*] = ;                  else
      [*] = ;                     text := '<<              >>';
      [*] = ;               end;
      [*] = ;               
      [*] = ;               elmBtnHandle := _gui_CreateButton('', elmDiplomacyBackground, '', cMainBtnName, 'halParentMiddle', 'valParentBottomHeight', posX, posY, 0, 0, cEventState, '', buttonTag);
      [*] = ;               if dealSealed then
      [*] = ;                  SetGUIElementHint(elmBtnHandle, 'gui|deal_sealed');
      [*] = ;               
      [*] = ;               if (displayMode = 4) then
      [*] = ;                  SetGUIElementVisibleProperties(elmBtnHandle, 'UpProperty', cMainBtnName + '.pressed', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmBtnHandle, text, 'halParentLeft', 'valParentTop', cBtnMainTextOffX, cBtnMainTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;               
      [*] = ;               // scroll icon
      [*] = ;               if oppDeal < 1 then
      [*] = ;                  posX := posX+85;
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmDiplomacyBackground, imageMaterial, 'halParentMiddle', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;               if ((displayPriority and $ff) > 0) then // if they have new offer
      [*] = ;                  _gui_CreateBlinkElement('btnPlayerOffer', elmImageHandle, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;            end;
      [*] = ;
      [*] = ;            //Treaty HUDs
      [*] = ;            if (mTreaty>0) or (mType=cCancelTradeMode) then
      [*] = ;            begin
      [*] = ;               elmPlayerOffersHandle := _gui_CreateImage('', elmDiplomacyBackground, cBlankMat, 'halParentMiddle', 'valParentTop', 0, 440, 0, 0, cCancelTreatyTag);
      [*] = ;               elmHandle := _gui_CreateCommonWindow('', '', '', 'halParentMiddle', 'valParentTop', 0, 0, 200, 69-6, False, False, False, 6, False);
      [*] = ;               AttachGUIElementToElement(elmHandle, elmPlayerOffersHandle);
      [*] = ;               SetGUIElementPositionX(elmHandle, -69);
      [*] = ;               SetGUIElementPositionY(elmHandle, -26);
      [*] = ;               var TextID : String;
      [*] = ;               case mTreaty of
      [*] = ;                  cDeclareWarBtnTag: TextID:='161';
      [*] = ;                  cOfferPeaceBtnTag: TextID:='160';
      [*] = ;                  cOfferUnionBtnTag: TextID:='162';
      [*] = ;                  cCancelUnionBtnTag: TextID:='174';
      [*] = ;                  cCancelTradeBtnTag: TextID:='176';
      [*] = ;               end;
      [*] = ;               if (mType<>cCancelTradeMode) then // political message
      [*] = ;               begin
      [*] = ;                  if (mTreaty=gc_TreatyCancelUnion) then
      [*] = ;                  begin
      [*] = ;                     elmImageHandle := _gui_CreateImage('', elmHandle, 'icon.diplomacy.'+IntToStr(2), 'halParentLeft', 'valParentTop', 4, 7, 0, 0, 0);
      [*] = ;                     _gui_CreateImage('', elmImageHandle, 'common.notenough.redline.cover', 'halParentLeft', 'valParentTop', 8, 8, 36, 36, 0);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     elmImageHandle := _gui_CreateImage('', elmHandle, 'icon.diplomacy.'+IntToStr(mTreaty-1), 'halParentLeft', 'valParentTop', 4, 7, 0, 0, 0);
      [*] = ;                  
      [*] = ;                  if (not dealSealed) and (displayMode < 4) then
      [*] = ;                     elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, 'gui|'+IntToStr(178), cCancelTreatyTag);
      [*] = ;                  
      [*] = ;                  _gui_CreateText('', elmImageHandle, GetLocaleTableListItemByID('gui', TextID) , 'halParentRight', 'valParentTop', 0, -1, 142, GetGUIElementHeight(elmImageHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  textID := '176';
      [*] = ;                  _gui_CreateText('', elmHandle, GetLocaleTableListItemByID('gui', TextID) , 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (mType=cExchangeMode) or (mType=cTradeMode) then
      [*] = ;            begin
      [*] = ;               var txtID, imgID : Integer;
      [*] = ;               if (mType=cExchangeMode) then
      [*] = ;               begin
      [*] = ;                  txtID := 164;
      [*] = ;                  imgID := 3;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               //if (mType=cTradeMode) then
      [*] = ;               begin
      [*] = ;                  txtID := 163;
      [*] = ;                  imgID := 4;
      [*] = ;               end;
      [*] = ;               elmPlayerOffersHandle := _gui_CreateImage('', elmDiplomacyBackground, cBlankMat, 'halParentMiddle', 'valParentTop', 0, 440, 0, 0, cCancelTreatyTag);
      [*] = ;               elmHandle := _gui_CreateCommonWindow('', '', '', 'halParentMiddle', 'valParentTop', 0, 0, 200, 69-6, False, False, False, 6, False);
      [*] = ;               AttachGUIElementToElement(elmHandle, elmPlayerOffersHandle);
      [*] = ;               SetGUIElementPositionX(elmHandle, -69);
      [*] = ;               SetGUIElementPositionY(elmHandle, -26);
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmHandle, 'icon.diplomacy.'+IntToStr(imgID), 'halParentLeft', 'valParentTop', 4, 7, 0, 0, 0);
      [*] = ;               if (not dealSealed) and (displayMode < 4) then
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, 'gui|'+IntToStr(178), cClearMessageBtnTag);
      [*] = ;               
      [*] = ;               text := GetLocaleTableListItemByID('gui', IntToStr(txtID));
      [*] = ;               _gui_CreateText('', elmImageHandle, text, 'halParentRight', 'valParentTop', 0, -1, 142, GetGUIElementHeight(elmImageHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (isTrade) then
      [*] = ;            begin
      [*] = ;               elmPlayerOffersHandle := _gui_CreateImage('', elmDiplomacyBackground, cBlankMat, 'halParentMiddle', 'valParentTop', 0, 440, 0, 0, cCancelTradeBtnTag);
      [*] = ;               elmHandle := _gui_CreateCommonWindow('', '', '', 'halParentMiddle', 'valParentTop', 0, 0, 200, 69-6, False, False, False, 6, False);
      [*] = ;               AttachGUIElementToElement(elmHandle, elmPlayerOffersHandle);
      [*] = ;               SetGUIElementPositionX(elmHandle, -69);
      [*] = ;               SetGUIElementPositionY(elmHandle, -26);
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmHandle, 'icon.diplomacy.'+IntToStr(4), 'halParentLeft', 'valParentTop', 4, 7, 0, 0, 0);
      [*] = ;               if not dealSealed then
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, 'gui|'+IntToStr(176), cCancelTradeBtnTag);
      [*] = ;               
      [*] = ;               var timer : Integer = gArrDiplomacy[myPlIndex][plIndex].arrTalk[5][1];
      [*] = ;               var bAnswer : Boolean = (gArrDiplomacy[myPlIndex][plIndex].arrTalk[5][0]=1);
      [*] = ;               var duration : Integer = gc_DipAgreementTimer-(gGame.currentTurn-timer);
      [*] = ;               text := GetLocaleTableListItemByID('gui', '183');
      [*] = ;               if (bAnswer) and (duration>0) and (timer>0) and (duration<=gc_DipAgreementTimer) then
      [*] = ;               text := text+gc_gui_BreakLine+'('+IntToStr(duration)+')';
      [*] = ;               _gui_CreateText('', elmImageHandle, text, 'halParentRight', 'valParentTop', 0, -1, 142, GetGUIElementHeight(elmImageHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;            end;
      [*] = ;
      [*] = ;            //Trade
      [*] = ;            const cAvailableOfferOffX = 32-16;
      [*] = ;            const cAvailableOfferOffY = 132;
      [*] = ;            const cAvailableOfferProvinceOffY = 132+209;
      [*] = ;            const cAvailableDemandOffX = -cAvailableOfferOffX-9;
      [*] = ;            const cAvailableDemandOffY = cAvailableOfferOffY;
      [*] = ;            const cAvailableDemandProvinceOffY = cAvailableOfferProvinceOffY;
      [*] = ;            var scrollLayerWidth : Integer = 56*4+4;
      [*] = ;            var scrollLayerHeight : Integer = 56*2+4;
      [*] = ;            var scrollLayerHandHeight : Integer = 56*3+4;
      [*] = ;            const cProvinceItemHeight : Integer = 34;
      [*] = ;            var scrollLayerHandProvinceHeight : Integer = cProvinceItemHeight*7+4;
      [*] = ;            const cPaddingCanOffer = 38;
      [*] = ;
      [*] = ;            const scrollOnTableLayerHeight = 235;
      [*] = ;            elmHandle := _gui_CreateFrameBorder('', elmDiplomacyBackground, 'halParentMiddle', 'valParentTop', cOffersOffX, cOffersOffY-cOfferMarginFrame, cFrameWidth+cOfferMarginFrame*2, cFrameHeight*2+scrollLayerHeight+cPaddingOffer+cOfferMarginFrame*2);
      [*] = ;            elmHandle := _gui_CreateFrameBorder('', elmDiplomacyBackground, 'halParentMiddle', 'valParentTop', cDemandOffX, cOffersOffY-cOfferMarginFrame, cFrameWidth+cOfferMarginFrame*2, cFrameHeight*2+scrollLayerHeight+cPaddingOffer+cOfferMarginFrame*2);
      [*] = ;            var elmScrollLayerOfferHandle : Integer = CreateScrollerParentExt('offers', elmDiplomacyBackground, 'halParentMiddle', 'valParentTop', gc_gui_material_blank_0, cOffersOffX, cOffersOffY-cOfferMarginFrame, scrollLayerWidth, scrollOnTableLayerHeight, scrollLayerWidth, 0, scrollOnTableLayerHeight, true);
      [*] = ;            var elmScrollLayerDemandHandle : Integer = CreateScrollerParentExt('demand', elmDiplomacyBackground, 'halParentMiddle', 'valParentTop', gc_gui_material_blank_0, cDemandOffX, cDemandOffY-cOfferMarginFrame, scrollLayerWidth, scrollOnTableLayerHeight, scrollLayerWidth, 0, scrollOnTableLayerHeight, true);
      [*] = ;
      [*] = ;            var myGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;            if gArrDiplomacy[myPlIndex][plIndex].message.mType = gc_MessageExchange then
      [*] = ;               myGold := myGold + gArrDiplomacy[myPlIndex][plIndex].message.tradeGive.gold; // include escrow
      [*] = ;            var myGoldStr : String = IntToStr(Max(0, myGold));
      [*] = ;            
      [*] = ;            var myGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;            if gArrDiplomacy[myPlIndex][plIndex].message.mType = gc_MessageExchange then
      [*] = ;               myGem := myGem + gArrDiplomacy[myPlIndex][plIndex].message.tradeGive.gem; // include escrow
      [*] = ;            var myGemStr : String = IntToStr(Max(0, myGem));
      [*] = ;            
      [*] = ;            var enGoldStr : String = '?';
      [*] = ;            if treaty = gc_TreatyUnion then
      [*] = ;            begin
      [*] = ;               var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;               if gArrDiplomacy[plIndex][myPlIndex].message.mType = gc_MessageExchange then
      [*] = ;                  plGold := plGold + gArrDiplomacy[plIndex][myPlIndex].message.tradeGive.gold; // include escrow
      [*] = ;               
      [*] = ;               enGoldStr := IntToStr(Max(0, plGold));
      [*] = ;            end;
      [*] = ;            
      [*] = ;            var enGemStr : String = '?';
      [*] = ;            if treaty = gc_TreatyUnion then
      [*] = ;            begin
      [*] = ;               var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;               if gArrDiplomacy[plIndex][myPlIndex].message.mType = gc_MessageExchange then
      [*] = ;                  plGem := plGem + gArrDiplomacy[plIndex][myPlIndex].message.tradeGive.gem; // include escrow
      [*] = ;               
      [*] = ;               enGemStr := IntToStr(Max(0, plGem));
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if (mType<>cExchangeMode) and ((bTradeMessage) or (isTrade)) then
      [*] = ;            begin
      [*] = ;               //Gold/gem
      [*] = ;               //===================== Offer =========================
      [*] = ;               var ShiftY1, ShiftY2, ShiftY1a, ShiftY2a :Integer = 0;
      [*] = ;               var inputHandle, elmFrameHandle : Integer;
      [*] = ;
      [*] = ;               if (bTradeMessage) and (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame', elmDiplomacyBackground, 'halParentLeft', 'valParentTop', cAvailableOfferOffX, cAvailableOfferOffY, cFrameWidth div 2-2, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), cEventState, 'gui|187', cOfferGoldTag);
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmFrameHandle, myGoldStr, 'halParentLeft', 'valParentTop', 46, 0, 0, GetGUIElementHeight(elmFrameHandle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (mGiveGold>0) or (mTakeGold>0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (bTradeMessage) and (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame', elmDiplomacyBackground, 'halParentLeft', 'valParentTop', cAvailableOfferOffX+(cFrameWidth div 2)+2, cAvailableOfferOffY, cFrameWidth div 2-2, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), cEventState, 'gui|188', cOfferGemTag);
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmFrameHandle, myGemStr, 'halParentLeft', 'valParentTop', 46, 0, 0, GetGUIElementHeight(elmFrameHandle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (mGiveGem>0) or (mTakeGem>0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               //===================== Demand =========================
      [*] = ;               if (bTradeMessage) and (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame', elmDiplomacyBackground, 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX-(cFrameWidth div 2)-2-8, cAvailableDemandOffY, cFrameWidth div 2-2, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), cEventState, 'gui|187', cDemandGoldTag);
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmFrameHandle, enGoldStr, 'halParentLeft', 'valParentTop', 46, 0, 0, GetGUIElementHeight(elmFrameHandle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (mGiveGold>0) or (mTakeGold>0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (bTradeMessage) and (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame', elmDiplomacyBackground, 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX-8, cAvailableDemandOffY, cFrameWidth div 2-2, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), cEventState, 'gui|188', cDemandGemTag);
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmFrameHandle, enGemStr, 'halParentLeft', 'valParentTop', 46, 0, 0, GetGUIElementHeight(elmFrameHandle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (mGiveGem>0) or (mTakeGem>0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               ShiftY1:=ShiftY1a+10;
      [*] = ;               ShiftY1:=cAvailableOfferOffY+84-4;
      [*] = ;
      [*] = ;               var bAllowChanges : Boolean = (not dealSealed);
      [*] = ;               DrawGoldGemBlock(mGiveGold, mGiveGem, mTakeGold, mTakeGem, elmScrollLayerOfferHandle, elmScrollLayerDemandHandle, ShiftY1a, ShiftY2a, (bTradeMessage and bAllowChanges));
      [*] = ;
      [*] = ;               //Resources
      [*] = ;               var Count1, Count2, Count1a, Count2a : Integer = 0;
      [*] = ;               if (isTrade) and (not bTradeMessage) then
      [*] = ;                  DrawResourceBlockAlreadyTrade(elmDiplomacyBackground, plIndex, Count1a, Count2a, ShiftY1a, ShiftY2a)
      [*] = ;               else
      [*] = ;               if (bTradeMessage) then
      [*] = ;                  DrawResourceBlock(elmDiplomacyBackground, plIndex, Count1, Count2, ShiftY1, ShiftY2, Count1a, Count2a, ShiftY1a, ShiftY2a, True, bAllowChanges);
      [*] = ;
      [*] = ;               // Headers strips
      [*] = ;               if (bTradeMessage) and (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentLeft', 'valParentTop', 7, cAvailableOfferOffY-34, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|739', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentLeft', 'valParentTop', 7, cAvailableOfferOffY-34+84, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|748', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX+3, cAvailableOfferOffY-34, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|740', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX+3, cAvailableOfferOffY-34+84, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|748', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            //Exchange
      [*] = ;            if (mType=cExchangeMode) then
      [*] = ;            begin
      [*] = ;               //Gold/gem
      [*] = ;               //===================== Offer =========================
      [*] = ;               var ShiftY1, ShiftY2, ShiftY1a, ShiftY2a :Integer = 0;
      [*] = ;               var inputHandle, elmFrameHandle : Integer;
      [*] = ;               var bOfferGoldGem : Boolean = False;
      [*] = ;               var bDemandGoldGem : Boolean = False;
      [*] = ;               var r_pos : TRectangle;
      [*] = ;               if (mGiveGold>0) then
      [*] = ;               begin
      [*] = ;                  //cInputBoxOfferGold
      [*] = ;                  //elmFrameHandle := _gui_CreateFrameBorder('frame_offergold', elmDiplomacyBackground, 'halParentMiddle', 'valParentTop', cOffersOffX, cOffersOffY, cFrameWidth, cFrameHeight);
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame_offergold', elmScrollLayerOfferHandle, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame, cFrameWidth, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;                  inputHandle := _gui_CreateInputControl_VVK('inputbox_offergold',elmFrameHandle,IntToStr(mGiveGold),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;                  //inputHandle := CreateInputBoxSimple('inputbox_offergold', elmFrameHandle, IntToStr(mGiveGold), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (not dealSealed) then
      [*] = ;                     elmBtnHandle := _gui_CreateButton('inputbox_offergold_ok', elmFrameHandle, '', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRightWidth', 'valParentTop', -1-13, 2+10, 0, 0, cEventState, 'gui|746', cBtnInputBoxOfferGoldCancel);
      [*] = ;                  _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentMiddle', 11, 0, 0, 0, 0);
      [*] = ;                  ShiftY1a:=ShiftY1a+46;
      [*] = ;                  if dealSealed then
      [*] = ;                  begin
      [*] = ;                     SetGUIAllowEvents(inputHandle, False, False, False);
      [*] = ;                     SetGUIElementHint(inputHandle, '');
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame', elmDiplomacyBackground, 'halParentLeft', 'valParentTop', cAvailableOfferOffX, cAvailableOfferOffY, cFrameWidth div 2-2, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), cEventState, 'gui|189', cOfferGoldTag);
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmFrameHandle, myGoldStr, 'halParentLeft', 'valParentTop', 46, 0, 0, GetGUIElementHeight(elmFrameHandle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (mGiveGold>0) or (mTakeGold>0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (mGiveGem>0) then
      [*] = ;               begin
      [*] = ;                  //cInputBoxOfferGem
      [*] = ;                  //elmFrameHandle := _gui_CreateFrameBorder('frame_offergem', elmDiplomacyBackground, 'halParentMiddle', 'valParentTop', cOffersOffX, cOffersOffY+ShiftY1a, cFrameWidth, cFrameHeight);
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame_offergem', elmScrollLayerOfferHandle, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame+ShiftY1a, cFrameWidth, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;                  inputHandle := _gui_CreateInputControl_VVK('inputbox_offergem',elmFrameHandle,IntToStr(mGiveGem),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;                  //inputHandle := CreateInputBoxSimple('inputbox_offergem', elmFrameHandle, IntToStr(mGiveGem), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (not dealSealed) then
      [*] = ;                     elmBtnHandle := _gui_CreateButton('inputbox_offergem_ok', elmFrameHandle, '', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRightWidth', 'valParentTop', -1-13, 2+10, 0, 0, cEventState, 'gui|746', cBtnInputBoxOfferGemCancel);
      [*] = ;                  _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 11, 0, 0, 0, 0);
      [*] = ;                  ShiftY1a:=ShiftY1a+46;
      [*] = ;                  if dealSealed then
      [*] = ;                  begin
      [*] = ;                     SetGUIAllowEvents(inputHandle, False, False, False);
      [*] = ;                     SetGUIElementHint(inputHandle, '');
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame', elmDiplomacyBackground, 'halParentLeft', 'valParentTop', cAvailableOfferOffX+(cFrameWidth div 2)+2, cAvailableOfferOffY, cFrameWidth div 2-2, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), cEventState, 'gui|190', cOfferGemTag);
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmFrameHandle, myGemStr, 'halParentLeft', 'valParentTop', 46, 0, 0, GetGUIElementHeight(elmFrameHandle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (mGiveGem>0) or (mTakeGem>0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               //===================== Demand =========================
      [*] = ;               if (mTakeGold>0) then
      [*] = ;               begin
      [*] = ;                  //cInputBoxOfferGold
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame_demandgold', elmScrollLayerDemandHandle, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame, cFrameWidth, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;                  inputHandle := _gui_CreateInputControl_VVK('inputbox_demandgold',elmFrameHandle,IntToStr(mTakeGold),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;                  //inputHandle := CreateInputBoxSimple('inputbox_demandgold', elmFrameHandle, IntToStr(mTakeGold), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (not dealSealed) then
      [*] = ;                     elmBtnHandle := _gui_CreateButton('inputbox_demandgold_ok', elmFrameHandle, '', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRightWidth', 'valParentTop', -1-13, 2+10, 0, 0, cEventState, 'gui|746', cBtnInputBoxDemandGoldCancel);
      [*] = ;                  _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentMiddle', 11, 0, 0, 0, 0);
      [*] = ;                  ShiftY2a:=ShiftY2a+46;
      [*] = ;                  if dealSealed then
      [*] = ;                  begin
      [*] = ;                     SetGUIAllowEvents(inputHandle, False, False, False);
      [*] = ;                     SetGUIElementHint(inputHandle, '');
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame', elmDiplomacyBackground, 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX-(cFrameWidth div 2)-2-8, cAvailableDemandOffY, cFrameWidth div 2-2, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), cEventState, 'gui|189', cDemandGoldTag);
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;               
      [*] = ;                  _gui_CreateText('', elmFrameHandle, enGoldStr, 'halParentLeft', 'valParentTop', 46, 0, 0, GetGUIElementHeight(elmFrameHandle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (mGiveGold>0) or (mTakeGold>0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (mTakeGem>0) then
      [*] = ;               begin
      [*] = ;                  //cInputBoxOfferGem
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame_demandgem', elmScrollLayerDemandHandle, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame+ShiftY2a, cFrameWidth, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;                  inputHandle := _gui_CreateInputControl_VVK('inputbox_demandgem',elmFrameHandle,IntToStr(mTakeGem),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;                  //inputHandle := CreateInputBoxSimple('inputbox_demandgem', elmFrameHandle, IntToStr(mTakeGem), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (not dealSealed) then
      [*] = ;                     elmBtnHandle := _gui_CreateButton('inputbox_demandgem_ok', elmFrameHandle, '', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRightWidth', 'valParentTop', -1-13, 2+10, 0, 0, cEventState, 'gui|746', cBtnInputBoxDemandGemCancel);
      [*] = ;                  _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 11, 0, 0, 0, 0);
      [*] = ;                  ShiftY2a:=ShiftY2a+46;
      [*] = ;                  if dealSealed then
      [*] = ;                  begin
      [*] = ;                     SetGUIAllowEvents(inputHandle, False, False, False);
      [*] = ;                     SetGUIElementHint(inputHandle, '');
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmFrameHandle := _gui_CreateFrameBorder('frame', elmDiplomacyBackground, 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX-8, cAvailableDemandOffY, cFrameWidth div 2-2, cFrameHeight);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), cEventState, 'gui|190', cDemandGemTag);
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;               
      [*] = ;                  _gui_CreateText('', elmFrameHandle, enGemStr, 'halParentLeft', 'valParentTop', 46, 0, 0, GetGUIElementHeight(elmFrameHandle), 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                  if (mGiveGem>0) or (mTakeGem>0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmFrameHandle, 0.5);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               //Items
      [*] = ;               var ItemCount : Integer = 0;
      [*] = ;               ShiftY1 := ShiftY1+cPaddingCanOffer;
      [*] = ;
      [*] = ;               if (mGiveGold>0) or (mGiveGem>0) then
      [*] = ;               ShiftY1a := ShiftY1a+cPaddingOffer;
      [*] = ;
      [*] = ;               //elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'gamepanel03.bag', 'halParentLeft', 'valParentTop', 310, 400+ShiftY1a, 0, 0, 0);
      [*] = ;               //var elmScrollLayerHandle : Integer = CreateScrollerParentExt('dip_items', elmScrollLayerOfferHandle, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, 0, cOfferMarginFrame+ShiftY1a-4, scrollLayerWidth, scrollLayerHeight, scrollLayerWidth, 0, scrollLayerHeight, true);
      [*] = ;               //var elmScrollLayerHandle : Integer = _gui_CreateImage('dip_items', elmScrollLayerOfferHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, cOfferMarginFrame+ShiftY1a-4, scrollLayerWidth, scrollLayerHeight, 0);
      [*] = ;               //SetGUIAllowEvents(elmScrollLayerHandle, False, False, False);
      [*] = ;               var elmItemBlock : Integer = _gui_CreateImage('', elmScrollLayerOfferHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, cOfferMarginFrame+ShiftY1a-4, scrollLayerWidth, scrollLayerHeight, Tag);
      [*] = ;               //===================== Offer =========================
      [*] = ;               //On Table
      [*] = ;               var i, k, pTreasuryItem, itemID, itemDur, available, reservedPlayerInd : Integer;
      [*] = ;
      [*] = ;               var treasuryCount : Integer = ParserGetCountByHandle(pMyTreasury);
      [*] = ;               var NoRoom : Boolean = true;
      [*] = ;               for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;               begin
      [*] = ;                  if gDiplMessage.tradeGive.arrItems[i][0] = 0 then
      [*] = ;                     NoRoom := false
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gDiplMessage.tradeGive.arrItems[i][0];
      [*] = ;                     IntRegister1 := gDiplMessage.tradeGive.arrItems[i][1];
      [*] = ;                     PlayerExecuteStateByHandle(myPlHandle, 'FindTreasuryItem');
      [*] = ;                     var trIndex : Integer = IntRegister2;
      [*] = ;
      [*] = ;                     if trIndex >= 0 then
      [*] = ;                     begin
      [*] = ;                        pTreasuryItem := ParserSelectByHandleByIndex(pMyTreasury, trIndex);
      [*] = ;                        itemID := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;                        itemDur := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;                        tag := cCancelOfferItemTag + trIndex;
      [*] = ;                        var iconName : String;
      [*] = ;                        _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;                        var elmSlotHandle : Integer = _gui_CreateImage('', elmItemBlock, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 4+(i mod 4)*56, 4+(i div 4)*56, 0, 0, 0);
      [*] = ;                        elmImageHandle := _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, tag);
      [*] = ;                        elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;                        //var hint : String = 'itemhint%|'+IntToStr(itemID)+'|'+IntToStr(3)+'|'+IntToStr(itemDur);
      [*] = ;                        elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, '', tag);
      [*] = ;                        if dealSealed then
      [*] = ;                        begin
      [*] = ;                           SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                           SetGUIElementUserBlend(elmSlotHandle, 0.5);
      [*] = ;                        end;
      [*] = ;                        _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBase,itemDur,cFT_ItemHeroDefault,'','3');
      [*] = ;                        ItemCount:=ItemCount+1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               var height : Integer = _misc_RoundUp(ItemCount/4)*56+4;
      [*] = ;               if (ItemCount>0) then
      [*] = ;               ShiftY1a:=ShiftY1a+height+10;
      [*] = ;               //SetGUIElementHeight(elmScrollLayerHandle, height);
      [*] = ;               SetGUIElementHeight(elmItemBlock, height);
      [*] = ;               
      [*] = ;               //On Hands
      [*] = ;               var elmScrollLayerHandle : Integer = CreateScrollerParentExt('dip_items', elmDiplomacyBackground, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, cAvailableOfferOffX-4, cAvailableOfferOffY+84-4, scrollLayerWidth, scrollLayerHandHeight, scrollLayerWidth, 0, scrollLayerHandHeight, true);
      [*] = ;               elmItemBlock := _gui_CreateImage('', elmScrollLayerHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, scrollLayerWidth, scrollLayerHandHeight, Tag);
      [*] = ;               var ItemCountOffer : Integer = 0;
      [*] = ;
      [*] = ;               var indices : array [0..gc_MaxTradeItemCount-1] of Integer;
      [*] = ;               for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;               indices[i] := -1;
      [*] = ;
      [*] = ;               if (not dealSealed) then
      [*] = ;               for i := 0 to treasuryCount-1 do
      [*] = ;               begin
      [*] = ;                  pTreasuryItem := ParserSelectByHandleByIndex(pMyTreasury, i);
      [*] = ;
      [*] = ;                  reservedPlayerInd := _pars_ParserGetIntValueExt(pTreasuryItem, 'ReservedPlayer');
      [*] = ;                  if (reservedPlayerInd >= 0) and (reservedPlayerInd <> plIndex) then
      [*] = ;                     continue;
      [*] = ;
      [*] = ;                  itemID := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;                  
      [*] = ;                  if itemID > 0 then
      [*] = ;                  begin
      [*] = ;                     itemDur := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;
      [*] = ;                     available := 1;
      [*] = ;
      [*] = ;                     // check if the item is already offered in current exchange view
      [*] = ;                     for j := 0 to gc_MaxTradeItemCount-1 do 
      [*] = ;                     if (indices[j] = -1) and (gDiplMessage.tradeGive.arrItems[j][0] = itemID) and (gDiplMessage.tradeGive.arrItems[j][1] = itemDur) then
      [*] = ;                     begin
      [*] = ;                        available := 0;
      [*] = ;                        indices[j] := i;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  
      [*] = ;                     // if this item not yet offered in this exchange.
      [*] = ;                     {if (available > 0) then
      [*] = ;                     begin
      [*] = ;                        available := available - _diplomacy_GetReservedItem(myPlIndex, -1, itemID, itemDur); // don't allow offering of items already given in deals that are already sealed.
      [*] = ;                     
      [*] = ;                        // check if there are more than one of the same item with same durability in the treasury.
      [*] = ;                        if available <= 0 then 
      [*] = ;                        begin
      [*] = ;                           var pTreasuryItem2, itemID2, itemDur2 : Integer;
      [*] = ;                           for j := i+1 to treasuryCount-1 do
      [*] = ;                           begin
      [*] = ;                              pTreasuryItem2 := ParserSelectByHandleByIndex(pMyTreasury, j);
      [*] = ;                              itemID2 := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;                              itemDur2 := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;                              if (itemID2 = itemID) and (itemDur2 = itemDur) then
      [*] = ;                                 available := available + 1;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;}
      [*] = ;                  
      [*] = ;                     if (available > 0) then
      [*] = ;                     begin
      [*] = ;                        var elmSlotHandle : Integer = _gui_CreateImage('', elmItemBlock, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 4+(ItemCountOffer mod 4)*56, 4+(ItemCountOffer div 4)*56, 0, 0, 0);
      [*] = ;                        elmImageHandle := _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, tag);
      [*] = ;                        tag := cOfferItemTag+i;
      [*] = ;                        var iconName : String;
      [*] = ;                        _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;                        elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, 0, 0, tag);
      [*] = ;                        //var hint : String = 'itemhint%|'+IntToStr(itemID)+'|'+IntToStr(3)+'|'+IntToStr(itemDur);
      [*] = ;                        elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, '', tag);
      [*] = ;                        _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBase,itemDur,cFT_ItemHeroDefault,'','3');
      [*] = ;                        if (NoRoom) then
      [*] = ;                        begin
      [*] = ;                           SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                           SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                        end;
      [*] = ;                        ItemCountOffer:=ItemCountOffer+1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               height := _misc_RoundUp(ItemCountOffer/4)*56+4;
      [*] = ;               ShiftY1:=ShiftY1+height+10;
      [*] = ;               SetGUIElementHeight(elmScrollLayerHandle, height);
      [*] = ;
      [*] = ;               //===================== Demand =========================
      [*] = ;               //On Table
      [*] = ;               ItemCount := 0;
      [*] = ;               ShiftY2 := ShiftY2+cPaddingCanOffer;
      [*] = ;
      [*] = ;               if (bDemandGoldGem) then
      [*] = ;               ShiftY2a:=ShiftY2a+46;
      [*] = ;               if (mTakeGold>0) or (mTakeGem>0) then
      [*] = ;               ShiftY2a := ShiftY2a+cPaddingOffer;
      [*] = ;
      [*] = ;               //elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'gamepanel03.bag', 'halParentLeft', 'valParentTop', 310, 400+ShiftY1a, 0, 0, 0);
      [*] = ;               //elmScrollLayerHandle := CreateScrollerParentExt('dip_items', elmScrollLayerDemandHandle, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, 0, ShiftY2a-4, scrollLayerWidth, scrollLayerHeight, scrollLayerWidth, 0, scrollLayerHeight, true);
      [*] = ;               //SetGUIAllowEvents(elmScrollLayerHandle, False, False, False);
      [*] = ;               elmItemBlock := _gui_CreateImage('', elmScrollLayerDemandHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, ShiftY2a-4, scrollLayerWidth, scrollLayerHeight, Tag);
      [*] = ;               //Demand
      [*] = ;               //On Table
      [*] = ;               NoRoom := true;
      [*] = ;               for i:=0 to gc_MaxTradeItemCount-1 do
      [*] = ;               begin
      [*] = ;                  if gDiplMessage.tradeTake.arrItems[i][0] = 0 then
      [*] = ;                     NoRoom := false
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gDiplMessage.tradeTake.arrItems[i][0];
      [*] = ;                     IntRegister1 := gDiplMessage.tradeTake.arrItems[i][1];
      [*] = ;                     PlayerExecuteStateByHandle(plHandle, 'FindTreasuryItem');
      [*] = ;                     var trIndex : Integer = IntRegister2;
      [*] = ;
      [*] = ;                     if trIndex >= 0 then
      [*] = ;                     begin
      [*] = ;                        pTreasuryItem := ParserSelectByHandleByIndex(pPlTreasury, trIndex);
      [*] = ;                        itemID := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;                        itemDur := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;                        tag := cCancelDemandItemTag + trIndex;
      [*] = ;                        var iconName : String;
      [*] = ;                        _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;                        var elmSlotHandle : Integer = _gui_CreateImage('', elmItemBlock, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 4+(i mod 4)*56, 4+(i div 4)*56, 0, 0, 0);
      [*] = ;                        elmImageHandle := _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, tag);
      [*] = ;                        elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;                        //var hint : String = '%itemhint%|'+IntToStr(itemID)+'|'+IntToStr(3)+'|'+IntToStr(itemDur);
      [*] = ;                        elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, '', tag);
      [*] = ;                        if dealSealed then
      [*] = ;                        begin
      [*] = ;                           SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                           SetGUIElementUserBlend(elmSlotHandle, 0.5);
      [*] = ;                        end;
      [*] = ;                        _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBase,itemDur,cFT_ItemHeroDefault,'','3');
      [*] = ;                        ItemCount:=ItemCount+1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               height := _misc_RoundUp(ItemCount/4)*56+4;
      [*] = ;               if (ItemCount>0) then
      [*] = ;               ShiftY2a:=ShiftY2a+height+10;
      [*] = ;               //SetGUIElementHeight(elmScrollLayerHandle, height);
      [*] = ;               SetGUIElementHeight(elmItemBlock, height);
      [*] = ;               
      [*] = ;               //On Hands
      [*] = ;               treasuryCount := ParserGetCountByHandle(pPlTreasury);
      [*] = ;
      [*] = ;               elmScrollLayerHandle := CreateScrollerParentExt('dip_items', elmDiplomacyBackground, 'halParentRightWidth', 'valParentTop', gc_gui_material_blank_0, cAvailableDemandOffX-4, cAvailableDemandOffY+84-4, scrollLayerWidth, scrollLayerHandHeight, scrollLayerWidth, 0, scrollLayerHandHeight, true);
      [*] = ;               elmItemBlock := _gui_CreateImage('', elmScrollLayerHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, scrollLayerWidth, scrollLayerHandHeight, Tag);
      [*] = ;               var ItemCountDemand : Integer = 0;
      [*] = ;               
      [*] = ;               for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;               indices[i] := -1;
      [*] = ;               
      [*] = ;               if (not dealSealed) then
      [*] = ;               for i:=0 to treasuryCount-1 do
      [*] = ;               begin
      [*] = ;                  pTreasuryItem := ParserSelectByHandleByIndex(pPlTreasury, i);
      [*] = ;
      [*] = ;                  reservedPlayerInd := _pars_ParserGetIntValueExt(pTreasuryItem, 'ReservedPlayer');
      [*] = ;                  if (reservedPlayerInd >= 0) and (reservedPlayerInd <> myPlIndex) then
      [*] = ;                     continue;
      [*] = ;
      [*] = ;                  itemID := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;                  
      [*] = ;                  if SameText(cMode, 'cmPlayer') and (i div 8 < 4) then // don't show every item of another human player in diplomacy window.
      [*] = ;                     itemID := 0;
      [*] = ;                  
      [*] = ;                  if itemID > 0 then
      [*] = ;                  begin
      [*] = ;                     itemDur := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;
      [*] = ;                     available := 1;
      [*] = ;
      [*] = ;                    // check if the item is already demanded in current exchange view
      [*] = ;                     for j := 0 to gc_MaxTradeItemCount-1 do 
      [*] = ;                     if (indices[j] = -1) and (gDiplMessage.tradeTake.arrItems[j][0] = itemID) and (gDiplMessage.tradeTake.arrItems[j][1] = itemDur) then
      [*] = ;                     begin
      [*] = ;                        available := 0;
      [*] = ;                        indices[j] := i;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  
      [*] = ;                     // if this item not yet demanded in this exchange.
      [*] = ;                     {if (available > 0) then
      [*] = ;                     begin
      [*] = ;                        available := available - _diplomacy_GetReservedItem(plIndex, -1, itemID, itemDur); // don't allow offering of items already given in deals that are already sealed.
      [*] = ;                     
      [*] = ;                        // check if there are more than one of the same item with same durability in the treasury.
      [*] = ;                        if available <= 0 then 
      [*] = ;                        begin
      [*] = ;                           var pTreasuryItem2, itemID2, itemDur2 : Integer;
      [*] = ;                           for j := i+1 to treasuryCount-1 do
      [*] = ;                           begin
      [*] = ;                              pTreasuryItem2 := ParserSelectByHandleByIndex(pPlTreasury, j);
      [*] = ;                              itemID2 := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;                              itemDur2 := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;                              if (itemID2 = itemID) and (itemDur2 = itemDur) then
      [*] = ;                                 available := available + 1;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;}
      [*] = ;                  
      [*] = ;                     if (available > 0) then
      [*] = ;                     begin
      [*] = ;                        var elmSlotHandle : Integer = _gui_CreateImage('', elmItemBlock, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 4+(ItemCountDemand mod 4)*56, 4+(ItemCountDemand div 4)*56, 0, 0, 0);
      [*] = ;                        elmImageHandle := _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, tag);
      [*] = ;                        tag := cDemandItemTag+i;
      [*] = ;
      [*] = ;                        var iconName : String;
      [*] = ;                        _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;                        elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, 0, 0, tag);
      [*] = ;                        elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, '', tag);
      [*] = ;                        _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBase,itemDur,cFT_ItemHeroDefault,'','3');
      [*] = ;                        if (NoRoom) then
      [*] = ;                        begin
      [*] = ;                           SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                           SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                        end;
      [*] = ;                        ItemCountDemand:=ItemCountDemand+1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               height := _misc_RoundUp(ItemCountDemand/4)*56+4;
      [*] = ;               ShiftY2:=ShiftY2+height+10;
      [*] = ;               SetGUIElementHeight(elmScrollLayerHandle, height);
      [*] = ;
      [*] = ;               //elmScrollLayerHandle := CreateScrollerParentExt('dip_province', elmScrollLayerOfferHandle, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, 0, cOfferMarginFrame+ShiftY1a-4, scrollLayerWidth, scrollLayerHeight, scrollLayerWidth, 0, scrollLayerHeight, true);
      [*] = ;               //SetGUIAllowEvents(elmScrollLayerHandle, False, False, False);
      [*] = ;               elmItemBlock := _gui_CreateImage('', elmScrollLayerOfferHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, cOfferMarginFrame+ShiftY1a-4, scrollLayerWidth, scrollLayerHeight, Tag);
      [*] = ;
      [*] = ;               // Province lists
      [*] = ;               // On Table
      [*] = ;               var pHexCells : Integer = gStratHexCells.handle;
      [*] = ;               var provinceCount, provinceCountDemand : Integer = 0;
      [*] = ;               var provOnTableCount, provOnTableCountDemand : Integer = 0;
      [*] = ;               for i:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;               begin
      [*] = ;                  var ind : Integer = gDiplMessage.tradeGive.arrProvinces[i];
      [*] = ;                  if (ind>-1) then
      [*] = ;                  begin
      [*] = ;                     var pProvince : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;                     var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;                     var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;                     var explored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;                     var provinceRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;                     var racePrefix : String = '';
      [*] = ;                     case provinceRace of
      [*] = ;                        1 : racePrefix := 'human';
      [*] = ;                        2 : racePrefix := 'elf';
      [*] = ;                        3 : racePrefix := 'dwarf';
      [*] = ;                        4 : racePrefix := 'goblin';
      [*] = ;                        5 : racePrefix := 'orc';
      [*] = ;                        6 : racePrefix := 'halfling';
      [*] = ;                        7 : racePrefix := 'centaur';
      [*] = ;                        8 : racePrefix := 'lizardman';
      [*] = ;                     end;
      [*] = ;                     var elmName : String = 'map_infopanel_race_'+racePrefix;
      [*] = ;                     var elmSlotHandle : Integer = _gui_CreateFrameBorder('frame', elmItemBlock, 'halParentLeft', 'valParentTop', 4, 4+provOnTableCount*cProvinceItemHeight, 220, cProvinceItemHeight-4);
      [*] = ;                     var tag : Integer = cOfferProvinceTag+ind;
      [*] = ;                     hint := GetLocaleTableListItemByID('gui', '746');
      [*] = ;                     AddProvinceInfoToHint(dummyHnd, hint);
      [*] = ;                     elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmSlotHandle), GetGUIElementHeight(elmSlotHandle), cEventState, hint, tag);
      [*] = ;                     if dealSealed then
      [*] = ;                     begin
      [*] = ;                        SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                        SetGUIElementUserBlend(elmSlotHandle, 0.5);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', -2, 1, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                     SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;                     // Province name
      [*] = ;                     IntRegister0 := pProvince;
      [*] = ;                     MapExecuteState('map.GetProvinceName');
      [*] = ;                     var provName : String = StringRegister0;
      [*] = ;                     var fontSize : String = '';
      [*] = ;                     var width, height : Integer;
      [*] = ;
      [*] = ;                     FindBestFontSize(provName, 220-cProvinceItemHeight*2, 3, width, height, fontSize);
      [*] = ;                     elmHandle := _gui_CreateText('map_infopanel_province_name', elmSlotHandle, provName, 'halParentLeft', 'valParentTop', cProvinceItemHeight, 0, 220-cProvinceItemHeight*2, cProvinceItemHeight, 'halMiddle', 'valMiddle', fontSize, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                     //SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;                     var resource : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;                     var resourcePrefix : String = '';
      [*] = ;                     case resource of
      [*] = ;                        1 : resourcePrefix := 'iron';
      [*] = ;                        2 : resourcePrefix := 'wood';
      [*] = ;                        3 : resourcePrefix := 'horses';
      [*] = ;                        4 : resourcePrefix := 'mandragora';
      [*] = ;                        5 : resourcePrefix := 'arcanite';
      [*] = ;                        6 : resourcePrefix := 'marble';
      [*] = ;                        7 : resourcePrefix := 'mithril';
      [*] = ;                        8 : resourcePrefix := 'diony';
      [*] = ;                        9 : resourcePrefix := 'blacklotus';
      [*] = ;                     end;
      [*] = ;                     var resExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ResourceExplore');
      [*] = ;                     if (resource>0) and (explored>=resExplore) then
      [*] = ;                     begin
      [*] = ;                        //elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', 0, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                        elmHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmSlotHandle, 'map.resource.'+IntToStr(resource)+'.61x61', 'halParentLeft', 'valParentTop', 220-cProvinceItemHeight, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                        SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     provOnTableCount := provOnTableCount+1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               height := _misc_RoundUp(provOnTableCount*cProvinceItemHeight)+4;
      [*] = ;               ShiftY1a:=ShiftY1a+height+10;
      [*] = ;               SetGUIElementHeight(elmScrollLayerOfferHandle, ShiftY1a);
      [*] = ;
      [*] = ;               // My provinces
      [*] = ;               // On Hand
      [*] = ;               elmScrollLayerHandle := CreateScrollerParentExt('dip_province', elmDiplomacyBackground, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, cAvailableOfferOffX-4, cAvailableOfferProvinceOffY+84-4, scrollLayerWidth, scrollLayerHandProvinceHeight, scrollLayerWidth, 0, scrollLayerHandProvinceHeight, true);
      [*] = ;               var bProvOfferLimitReached : Boolean = (provOnTableCount=gc_MaxTradeProvCount);
      [*] = ;               if (bProvOfferLimitReached) then
      [*] = ;               SetGUIElementUserBlend(elmScrollLayerHandle, 0.35);
      [*] = ;               elmItemBlock := _gui_CreateImage('', elmScrollLayerHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, scrollLayerWidth, scrollLayerHandHeight, Tag);
      [*] = ;
      [*] = ;               if (not dealSealed) then
      [*] = ;               for i:=0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;               begin
      [*] = ;                  var bPicked : Boolean = False;
      [*] = ;                  for j:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;                  begin
      [*] = ;                     if (gDiplMessage.tradeGive.arrProvinces[j]=i) then
      [*] = ;                     begin
      [*] = ;                        bPicked := True;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (not bPicked) then
      [*] = ;                  begin
      [*] = ;                     var pProvince : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;                     if SameText(ParserGetValueByKeyByHandle(pProvince, 'Player'), GetPlayerNameInterfaceIO) then
      [*] = ;                     begin
      [*] = ;                        var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;                        var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;                        var bCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;                        if (not bCastle) and (_diplomacy_GetReservedProvince(myPlIndex, -1, i) = 0) then
      [*] = ;                        begin
      [*] = ;                           var explored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;                           var provinceRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;                           var racePrefix : String = '';
      [*] = ;                           case provinceRace of
      [*] = ;                              1 : racePrefix := 'human';
      [*] = ;                              2 : racePrefix := 'elf';
      [*] = ;                              3 : racePrefix := 'dwarf';
      [*] = ;                              4 : racePrefix := 'goblin';
      [*] = ;                              5 : racePrefix := 'orc';
      [*] = ;                              6 : racePrefix := 'halfling';
      [*] = ;                              7 : racePrefix := 'centaur';
      [*] = ;                              8 : racePrefix := 'lizardman';
      [*] = ;                           end;
      [*] = ;                           var elmName : String = 'map_infopanel_race_'+racePrefix;
      [*] = ;                           var elmSlotHandle : Integer = _gui_CreateFrameBorder('frame', elmItemBlock, 'halParentLeft', 'valParentTop', 4, 4+provinceCount*cProvinceItemHeight, 220, cProvinceItemHeight-4);
      [*] = ;                           var tag : Integer = cOfferProvinceTag+i;
      [*] = ;                           hint := GetLocaleTableListItemByID('gui', '192');
      [*] = ;                           AddProvinceInfoToHint(dummyHnd, hint);
      [*] = ;
      [*] = ;                           elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmSlotHandle), GetGUIElementHeight(elmSlotHandle), cEventState, hint, tag);
      [*] = ;                           if (bProvOfferLimitReached) then
      [*] = ;                           SetGUIAllowEvents(elmBtnHandle, False, False, False);
      [*] = ;
      [*] = ;                           elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', -2, 1, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                           SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;                           // Province name
      [*] = ;                           IntRegister0 := pProvince;
      [*] = ;                           MapExecuteState('map.GetProvinceName');
      [*] = ;                           var provName : String = StringRegister0;
      [*] = ;                           var fontSize : String = '';
      [*] = ;                           var width, height : Integer;
      [*] = ;
      [*] = ;                           FindBestFontSize(provName, 220-cProvinceItemHeight*2, 3, width, height, fontSize);
      [*] = ;                           elmHandle := _gui_CreateText('map_infopanel_province_name', elmSlotHandle, provName, 'halParentLeft', 'valParentTop', cProvinceItemHeight, 0, 220-cProvinceItemHeight*2, cProvinceItemHeight, 'halMiddle', 'valMiddle', fontSize, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                           //SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;                           var resource : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;                           var resourcePrefix : String = '';
      [*] = ;                           case resource of
      [*] = ;                              1 : resourcePrefix := 'iron';
      [*] = ;                              2 : resourcePrefix := 'wood';
      [*] = ;                              3 : resourcePrefix := 'horses';
      [*] = ;                              4 : resourcePrefix := 'mandragora';
      [*] = ;                              5 : resourcePrefix := 'arcanite';
      [*] = ;                              6 : resourcePrefix := 'marble';
      [*] = ;                              7 : resourcePrefix := 'mithril';
      [*] = ;                              8 : resourcePrefix := 'diony';
      [*] = ;                              9 : resourcePrefix := 'blacklotus';
      [*] = ;                           end;
      [*] = ;                           var resExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ResourceExplore');
      [*] = ;                           if (resource>0) and (explored>=resExplore) then
      [*] = ;                           begin
      [*] = ;                              //elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', 0, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                              elmHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmSlotHandle, 'map.resource.'+IntToStr(resource)+'.61x61', 'halParentLeft', 'valParentTop', 220-cProvinceItemHeight, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                              SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;                           end;
      [*] = ;                           provinceCount := provinceCount+1;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               height := provinceCount*cProvinceItemHeight+4;
      [*] = ;               SetGUIElementHeight(elmScrollLayerHandle, height);
      [*] = ;
      [*] = ;               // Enemy provinces list
      [*] = ;               // On Table
      [*] = ;               elmItemBlock := _gui_CreateImage('', elmScrollLayerDemandHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, cOfferMarginFrame+ShiftY2a-4, scrollLayerWidth, scrollLayerHeight, Tag);
      [*] = ;
      [*] = ;               for i:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;               begin
      [*] = ;                  var ind : Integer = gDiplMessage.tradeTake.arrProvinces[i];
      [*] = ;                  if (ind>-1) then
      [*] = ;                  begin
      [*] = ;                     var pProvince : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;                     var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;                     var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;                     var explored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;                     var provinceRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;                     var racePrefix : String = '';
      [*] = ;                     case provinceRace of
      [*] = ;                        1 : racePrefix := 'human';
      [*] = ;                        2 : racePrefix := 'elf';
      [*] = ;                        3 : racePrefix := 'dwarf';
      [*] = ;                        4 : racePrefix := 'goblin';
      [*] = ;                        5 : racePrefix := 'orc';
      [*] = ;                        6 : racePrefix := 'halfling';
      [*] = ;                        7 : racePrefix := 'centaur';
      [*] = ;                        8 : racePrefix := 'lizardman';
      [*] = ;                     end;
      [*] = ;                     var elmName : String = 'map_infopanel_race_'+racePrefix;
      [*] = ;                     var elmSlotHandle : Integer = _gui_CreateFrameBorder('frame', elmItemBlock, 'halParentLeft', 'valParentTop', 4, 4+provOnTableCountDemand*cProvinceItemHeight, 220, cProvinceItemHeight-4);
      [*] = ;                     var tag : Integer = cDemandProvinceTag+ind;
      [*] = ;                     hint := GetLocaleTableListItemByID('gui', '746');
      [*] = ;                     AddProvinceInfoToHint(dummyHnd, hint);
      [*] = ;                     elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmSlotHandle), GetGUIElementHeight(elmSlotHandle), cEventState, hint, tag);
      [*] = ;                     if dealSealed then
      [*] = ;                     begin
      [*] = ;                        SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                        SetGUIElementUserBlend(elmSlotHandle, 0.5);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', -2, 1, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                     SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;                     // Province name
      [*] = ;                     IntRegister0 := pProvince;
      [*] = ;                     MapExecuteState('map.GetProvinceName');
      [*] = ;                     var provName : String = StringRegister0;
      [*] = ;                     var fontSize : String = '';
      [*] = ;                     var width, height : Integer;
      [*] = ;
      [*] = ;                     FindBestFontSize(provName, 220-cProvinceItemHeight*2, 3, width, height, fontSize);
      [*] = ;                     elmHandle := _gui_CreateText('map_infopanel_province_name', elmSlotHandle, provName, 'halParentLeft', 'valParentTop', cProvinceItemHeight, 0, 220-cProvinceItemHeight*2, cProvinceItemHeight, 'halMiddle', 'valMiddle', fontSize, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                     //SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;                     var resource : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;                     var resourcePrefix : String = '';
      [*] = ;                     case resource of
      [*] = ;                        1 : resourcePrefix := 'iron';
      [*] = ;                        2 : resourcePrefix := 'wood';
      [*] = ;                        3 : resourcePrefix := 'horses';
      [*] = ;                        4 : resourcePrefix := 'mandragora';
      [*] = ;                        5 : resourcePrefix := 'arcanite';
      [*] = ;                        6 : resourcePrefix := 'marble';
      [*] = ;                        7 : resourcePrefix := 'mithril';
      [*] = ;                        8 : resourcePrefix := 'diony';
      [*] = ;                        9 : resourcePrefix := 'blacklotus';
      [*] = ;                     end;
      [*] = ;                     var resExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ResourceExplore');
      [*] = ;                     if (resource>0) and (explored>=resExplore) then
      [*] = ;                     begin
      [*] = ;                        //elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', 0, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                        elmHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmSlotHandle, 'map.resource.'+IntToStr(resource)+'.61x61', 'halParentLeft', 'valParentTop', 220-cProvinceItemHeight, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                        SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;                     end;
      [*] = ;                     provOnTableCountDemand := provOnTableCountDemand+1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               height := _misc_RoundUp(provOnTableCountDemand*cProvinceItemHeight)+4;
      [*] = ;               ShiftY2a:=ShiftY2a+height+10;
      [*] = ;               SetGUIElementHeight(elmScrollLayerDemandHandle, ShiftY2a);
      [*] = ;
      [*] = ;               // Enemy provinces
      [*] = ;               // On Hand
      [*] = ;               elmScrollLayerHandle := CreateScrollerParentExt('dip_province', elmDiplomacyBackground, 'halParentRightWidth', 'valParentTop', gc_gui_material_blank_0, cAvailableDemandOffX-4, cAvailableDemandProvinceOffY+84-4, scrollLayerWidth, scrollLayerHandProvinceHeight, scrollLayerWidth, 0, scrollLayerHandProvinceHeight, true);
      [*] = ;               var bProvDemandLimitReached : Boolean = (provOnTableCountDemand=gc_MaxTradeProvCount);
      [*] = ;               if (bProvDemandLimitReached) then
      [*] = ;               SetGUIElementUserBlend(elmScrollLayerHandle, 0.35);
      [*] = ;               elmItemBlock := _gui_CreateImage('', elmScrollLayerHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, scrollLayerWidth, scrollLayerHandHeight, Tag);
      [*] = ;
      [*] = ;               if (not dealSealed) then
      [*] = ;               for i:=0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;               begin
      [*] = ;                  var bPicked : Boolean = False;
      [*] = ;                  for j:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;                  begin
      [*] = ;                     if (gDiplMessage.tradeTake.arrProvinces[j]=i) then
      [*] = ;                     begin
      [*] = ;                        bPicked := True;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (not bPicked) then
      [*] = ;                  begin
      [*] = ;                     var pProvince : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;                     if SameText(ParserGetValueByKeyByHandle(pProvince, 'Player'), GetPlayerNameByIndex(plIndex)) then
      [*] = ;                     begin
      [*] = ;                        var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;                        var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;                        var bCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;                        var pProvFog : Integer = ParserSelectByHandleByKey(pProvince, 'Fog');
      [*] = ;                        var fog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, myplIndex);
      [*] = ;                        if (not bCastle) and ((fog=0) or (not gGame.fog)) and (_diplomacy_GetReservedProvince(plIndex, -1, i) = 0) then
      [*] = ;                        begin
      [*] = ;                           var explored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;                           var provinceRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;                           var racePrefix : String = '';
      [*] = ;                           case provinceRace of
      [*] = ;                              1 : racePrefix := 'human';
      [*] = ;                              2 : racePrefix := 'elf';
      [*] = ;                              3 : racePrefix := 'dwarf';
      [*] = ;                              4 : racePrefix := 'goblin';
      [*] = ;                              5 : racePrefix := 'orc';
      [*] = ;                              6 : racePrefix := 'halfling';
      [*] = ;                              7 : racePrefix := 'centaur';
      [*] = ;                              8 : racePrefix := 'lizardman';
      [*] = ;                           end;
      [*] = ;                           var elmName : String = 'map_infopanel_race_'+racePrefix;
      [*] = ;                           var elmSlotHandle : Integer = _gui_CreateFrameBorder('frame', elmItemBlock, 'halParentLeft', 'valParentTop', 4, 4+provinceCountDemand*cProvinceItemHeight, 220, cProvinceItemHeight-4);
      [*] = ;                           var tag : Integer = cDemandProvinceTag+i;
      [*] = ;                           hint := GetLocaleTableListItemByID('gui', '192');
      [*] = ;                           AddProvinceInfoToHint(dummyHnd, hint);
      [*] = ;                           elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmSlotHandle), GetGUIElementHeight(elmSlotHandle), cEventState, hint, tag);
      [*] = ;                           if (bProvDemandLimitReached) then
      [*] = ;                           SetGUIAllowEvents(elmBtnHandle, False, False, False);
      [*] = ;
      [*] = ;                           elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', -2, 1, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                           SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;                           // Province name
      [*] = ;                           IntRegister0 := pProvince;
      [*] = ;                           MapExecuteState('map.GetProvinceName');
      [*] = ;                           var provName : String = StringRegister0;
      [*] = ;                           var fontSize : String = '';
      [*] = ;                           var width, height : Integer;
      [*] = ;
      [*] = ;                           FindBestFontSize(provName, 220-cProvinceItemHeight*2, 3, width, height, fontSize);
      [*] = ;                           elmHandle := _gui_CreateText('map_infopanel_province_name', elmSlotHandle, provName, 'halParentLeft', 'valParentTop', cProvinceItemHeight, 0, 220-cProvinceItemHeight*2, cProvinceItemHeight, 'halMiddle', 'valMiddle', fontSize, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;                           //SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;                           var resource : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;                           var resourcePrefix : String = '';
      [*] = ;                           case resource of
      [*] = ;                              1 : resourcePrefix := 'iron';
      [*] = ;                              2 : resourcePrefix := 'wood';
      [*] = ;                              3 : resourcePrefix := 'horses';
      [*] = ;                              4 : resourcePrefix := 'mandragora';
      [*] = ;                              5 : resourcePrefix := 'arcanite';
      [*] = ;                              6 : resourcePrefix := 'marble';
      [*] = ;                              7 : resourcePrefix := 'mithril';
      [*] = ;                              8 : resourcePrefix := 'diony';
      [*] = ;                              9 : resourcePrefix := 'blacklotus';
      [*] = ;                           end;
      [*] = ;                           var resExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ResourceExplore');
      [*] = ;                           if (resource>0) and (explored>=resExplore) then
      [*] = ;                           begin
      [*] = ;                              //elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', 0, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                              elmHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmSlotHandle, 'map.resource.'+IntToStr(resource)+'.61x61', 'halParentLeft', 'valParentTop', 220-cProvinceItemHeight, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;                              SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;                           end;
      [*] = ;                           provinceCountDemand := provinceCountDemand+1;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               height := provinceCountDemand*cProvinceItemHeight+4;
      [*] = ;               SetGUIElementHeight(elmScrollLayerHandle, height);
      [*] = ;
      [*] = ;               // Headers strips
      [*] = ;               if (not dealSealed) then
      [*] = ;               begin
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentLeft', 'valParentTop', 7, cAvailableOfferOffY-34, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|739', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentLeft', 'valParentTop', 7, cAvailableOfferOffY-34+84, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|744', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;                  if (ItemCountOffer=0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;                     SetGUIElementUserColor(elmHandle, 0.75, 0.75, 0.75, 0.75);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentLeft', 'valParentTop', 7, cAvailableOfferOffY-34+84+56*3+40, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|745', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;                  if (provinceCount=0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;                     SetGUIElementUserColor(elmHandle, 0.75, 0.75, 0.75, 0.75);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX+3, cAvailableOfferOffY-34, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|740', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX+3, cAvailableOfferOffY-34+84, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|744', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;                  if (ItemCountDemand=0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;                     SetGUIElementUserColor(elmHandle, 0.75, 0.75, 0.75, 0.75);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentRightWidth', 'valParentTop', cAvailableDemandOffX+3, cAvailableOfferOffY-34+84+56*3+40, 0, 0, 0);
      [*] = ;                  _gui_CreateText('', elmHandle, 'gui|745', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;                  if (provinceCountDemand=0) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;                     SetGUIElementUserColor(elmHandle, 0.75, 0.75, 0.75, 0.75);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            var TxtIndex : Integer = Treaty+183;
      [*] = ;            IntRegister0 := myPlIndex;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'GetAttitude');
      [*] = ;            attitude := IntRegister1;
      [*] = ;            var name : String = '';
      [*] = ;            GetAttitudeName(attitude, name);
      [*] = ;            elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.148', 'halParentMiddle', 'valParentTop', 0, 380-16, 0, 0, 0);
      [*] = ;            text := GetLocaleTableListItemByID('gui', IntToStr(TxtIndex));
      [*] = ;            if (treaty>1) and (treaty<4) then
      [*] = ;            begin
      [*] = ;               //var duration : Integer = gc_DipAgreementTimer-gArrDiplomacy[myPlIndex][plIndex].arrTalk[treaty][1];
      [*] = ;               var timer : Integer = gArrDiplomacy[myPlIndex][plIndex].arrTalk[treaty][1];
      [*] = ;               var duration : Integer = gc_DipAgreementTimer-(gGame.currentTurn-timer);
      [*] = ;               if (duration>0) and (timer>0) and (duration<=gc_DipAgreementTimer) then
      [*] = ;               text := text+' ('+IntToStr(duration)+')';
      [*] = ;            end;
      [*] = ;            _gui_CreateText('', elmHandle, text, 'halParentLeft', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;            elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, 380-16+26, 0, 0, 0);
      [*] = ;            _gui_CreateText('', elmHandle, name, 'halParentLeft', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;            //case displayMode of
      [*] = ;            //   1 : text := '   '+myName+' >>';
      [*] = ;            //   2 : text := 'gui|741';
      [*] = ;            //   3 : text := 'gui|742';
      [*] = ;            //end;
      [*] = ;            text := '   '+myName+' >>';
      [*] = ;            elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentMiddle', 'valParentTop', cOffersOffX, cOffersOffY-34-cOfferMarginFrame, 0, 0, 0);
      [*] = ;            _gui_CreateText('', elmHandle, text, 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;            //case displayMode of
      [*] = ;            //   1 : text := '<< '+plName+'   ';
      [*] = ;            //   2 : text := 'gui|742';
      [*] = ;            //   3 : text := 'gui|741';
      [*] = ;            //end;
      [*] = ;            text := '<< '+plName+'   ';
      [*] = ;            elmHandle := _gui_CreateImage('', elmDiplomacyBackground, 'element.strip.240', 'halParentMiddle', 'valParentTop', cDemandOffX, cOffersOffY-34-cOfferMarginFrame, 0, 0, 0);
      [*] = ;            _gui_CreateText('', elmHandle, text, 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;            //if (bMessageSent) then
      [*] = ;            //begin
      [*] = ;            //   elmHandle := _gui_CreateCommonWindow('', '', '', 'halParentLeft', 'valParentTop', 0, 0, 200, 63, False, False, False, 6, False);
      [*] = ;            //   AttachGUIElementToElement(elmHandle, elmDiplomacyBackground);
      [*] = ;            //   SetGUIElementPosition(elmHandle, gIntRegister_dbgX, gIntRegister_dbgY);
      [*] = ;            //   SetGUIElementAlign(elmHandle, 'halParentMiddle', 'valParentBottomHeight');
      [*] = ;            //   _gui_CreateText('', elmHandle, 'Message sent', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;            //end;
      [*] = ;            gIntRegister_QueryDiplomacyPlayerID := -1;
      [*] = ;            
      [*] = ;            // display query window of new messages
      [*] = ;            if (gArrDiplomacy[plIndex][myPlIndex].answer <> 0) and ((displayPriority and $ff00) > 0) then // their answer to my proposal has priority.
      [*] = ;            begin
      [*] = ;               IntRegister0 := myPlIndex;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'SendAnswer');
      [*] = ;               query := gArrDiplomacy[plIndex][myPlIndex].message.text;
      [*] = ;               gArrDiplomacy[plIndex][myPlIndex].message.text := '';
	  [*] = ;               gArrDiplomacy[plIndex][myPlIndex].answer := 0;
	  [*] = ;               gArrDiplomacy[plIndex][myPlIndex].displayPriority := displayPriority and $ff00ff;
      [*] = ;               gIntRegister_QueryDiplomacyPlayerID := plIndex + $10; // to be used in DrawDiplomacyOfferCover
      [*] = ;            end
      [*] = ;            else // check if they have a new proposal
      [*] = ;            if (gArrDiplomacy[plIndex][myPlIndex].message.deal = 0) and (gArrDiplomacy[myPlIndex][plIndex].answer = 0) and ((displayPriority and $ff) > 0) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := myPlIndex;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'MakeHumanDiplomacyText');
      [*] = ;               query := gArrDiplomacy[plIndex][myPlIndex].message.text;
      [*] = ;               gArrDiplomacy[plIndex][myPlIndex].message.text := '';
	  [*] = ;               gArrDiplomacy[plIndex][myPlIndex].displayPriority := displayPriority and $ffff00;
      [*] = ;               gIntRegister_QueryDiplomacyPlayerID := plIndex; // to be used in DrawDiplomacyOfferCover
      [*] = ;            end
      [*] = ;            else // check if their offer withdrawn
      [*] = ;            if (gArrDiplomacy[plIndex][myPlIndex].message.deal < 0) and (gArrDiplomacy[myPlIndex][plIndex].answer = 0) and ((displayPriority and $ff) > 0) then
      [*] = ;            begin
      [*] = ;               query := IntToStr(gc_gui_query_diplOfferWithdrawn);
	  [*] = ;               gArrDiplomacy[myPlIndex][plIndex].displayPriority := displayPriority and $ffff00;
      [*] = ;               gIntRegister_QueryDiplomacyPlayerID := plIndex; // to be used in DrawDiplomacyOfferCover
      [*] = ;            end
      [*] = ;            else 
      [*] = ;            if ((displayPriority and $ff0000) > 0) then
      [*] = ;            begin
      [*] = ;               // unused
      [*] = ;               gArrDiplomacy[plIndex][myPlIndex].displayPriority := gArrDiplomacy[plIndex][myPlIndex].displayPriority and $00ffff; // reset
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if query <> '' then
      [*] = ;                queryPlName := plName;
      [*] = ;         end;
      [*] = ;         if (not bSelected) then
      [*] = ;         begin
      [*] = ;            SetGUIElementUseUserColor(elmSmallPortraitHandle, True);
      [*] = ;            SetGUIElementUserColor(elmSmallPortraitHandle, 1, 1, 1, 0.75);
      [*] = ;            SetGUIElementUserBlend(elmSmallPortraitHandle, 0.5);
      [*] = ;         end;
      [*] = ;
      [*] = ;         Count:=Count+1;
      [*] = ;         visibleIndex := visibleIndex+1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if SameText(GetPlayerControlModeByHandle(plHandle),'cmPC') then
      [*] = ;         begin
      [*] = ;            posX := (GetGUIElementWidth(elmDiplomacyBackground) div 2)-40*visibleCount+80*visibleIndex;
      [*] = ;            posY := 20;
      [*] = ;            //posY := 18-yGlobalOff;
      [*] = ;            plProfileID := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;            var elmSmallPortraitHandle : Integer = _gui_CreateImage('', elmDiplomacyBackground, 'astral.players.icon.small.0', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmDiplomacyBackground, 'map.heroselection.browncircle', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;            SetGUIElementHint(elmImageHandle, 'gui|271');
      [*] = ;            SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;            //SetGUIElementPressState(elmImageHandle, 'map.EventDiplomacyWindow');
      [*] = ;            SetGUIElementTag(elmImageHandle, cPlayerTag+plIndex);
      [*] = ;            //SetGUIElementCursorByName(elmImageHandle, 'crHand');
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 0.25);
      [*] = ;            visibleIndex := visibleIndex+1;
      [*] = ;         end
      [*] = ;      end
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;_gui_RootWindowAddM(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;IntRegister0 := -10;
      [*] = ;MapExecuteState('CheckTutorialProgress');
      [*] = ;
      [*] = ;if query <> '' then
      [*] = ;begin
	  [*] = ;   gIntRegister_QueryPlayerIndex := gIntRegister_DiplomacyActivePlayerID;
      [*] = ;   gStringRegister_EnemyPlayerName := queryPlName;
      [*] = ;   StringRegister0 := query;
      [*] = ;   ExecuteState('map.RequestQueryWindow');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

