section.begin
   Name = map.DrawDiplomacyOfferCover
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.DRAWDIPLOMACYOFFERCOVER';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;
      [*] = ;var elmParent : Integer = IntRegister0;
      [*] = ;
      [*] = ;function _gui_MODIFIED_CreateSmallWindow(parent : Integer; elementName, hAlign, vAlign : String; posX, posY, sizeX, sizeY : Integer; modal : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   procedure ResizeTextureToWidth(elmHandle : Integer; elementName : String; width : Integer);
      [*] = ;   begin
      [*] = ;      var elmBackgroundHandle : Integer = GetGUIElementIndexByNameParent('material', elmHandle);
      [*] = ;      if (elmBackgroundHandle<>0) then
      [*] = ;      begin
      [*] = ;         var texWidth : Integer = GetGUITextureWidth(GetGUIElementMaterial(elmBackgroundHandle));
      [*] = ;         if (width>texWidth) then
      [*] = ;         SetGUIElementWidth(elmBackgroundHandle, width);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var elmMyParent : Integer;
      [*] = ;   if (parent=0) or (modal) then
      [*] = ;   elmMyParent := _gui_GetLayer(cInterfaceLayer)
      [*] = ;   else
      [*] = ;   elmMyParent := parent;
      [*] = ;   var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage(elementName, elmMyParent, hAlign, vAlign, posX, posY, sizeX, sizeY, 0);
      [*] = ;   var elmBackgroundHandle : Integer = _gui_GetOrCreateElementExtAsImage('background', elmParentHandle, 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY, 0);
      [*] = ;   var elmFrameHandle : Integer = _gui_GetOrCreateElementExtAsImage('frame', elmParentHandle, 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY, 0);
      [*] = ;   if (modal) then
      [*] = ;   begin
      [*] = ;      _gui_RootWindowAdd(elmParentHandle,cRootWindowModal);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', elmBackgroundHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY, 0);
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmBackgroundHandle, 'common.window.background', 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY);
      [*] = ;   ResizeTextureToWidth(elmHandle, 'material', sizeX);
      [*] = ;
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmFrameHandle, 'gamepanel03.snapshot.border.top', 'halParentLeft', 'valParentTop', 0, -11, sizeX, 0);
      [*] = ;   _gui_TileScaleElementToSize(elmHandle, sizeX, 0);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmFrameHandle, 'gamepanel03.snapshot.border.bottom', 'halParentLeft', 'valParentBottom', 0, 0, sizeX, 0);
      [*] = ;   _gui_TileScaleElementToSize(elmHandle, sizeX, 0);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmFrameHandle, 'gamepanel03.snapshot.border.left', 'halParentLeft', 'valParentTop', -11, 0, 0, sizeY);
      [*] = ;   _gui_TileScaleElementToSize(elmHandle, 0, sizeY);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmFrameHandle, 'gamepanel03.snapshot.border.right', 'halParentRight', 'valParentTop', 0, 0, 0, sizeY);
      [*] = ;   _gui_TileScaleElementToSize(elmHandle, 0, sizeY);
      [*] = ;   //elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.decor.top', 'halParentMiddle', 'valParentTop', 0, -3-GetGUITextureHeight('gamepanel03.snapshot.decor.top'), 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.decor.bottom', 'halParentMiddle', 'valParentBottom', 0, 3, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.decor.left', 'halParentLeft', 'valParentMiddle', -GetGUITextureWidth('gamepanel03.snapshot.decor.left'), 0, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.decor.right', 'halParentRight', 'valParentMiddle', 0, 0, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.corner.top.left', 'halParentLeft', 'valParentTop', -18, -33, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.corner.top.right', 'halParentRight', 'valParentTop', -48, -33, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.corner.bottom.left', 'halParentLeft', 'valParentBottom', -18, -12, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.corner.bottom.right', 'halParentRight', 'valParentBottom', -48, -12, 0, 0, 0);
      [*] = ;
      [*] = ;   Result := elmParentHandle;
      [*] = ;end;
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
      [*] = ;var bReverseTables : Boolean = false;
      [*] = ;var plIndex : Integer = gIntRegister_QueryDiplomacyPlayerID;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[PlIndex: '+IntToStr(plIndex)+']',_log_trace);
      [*] = ;
      [*] = ;if plIndex > $f then
      [*] = ;begin
      [*] = ;   bReverseTables := true;
      [*] = ;   plIndex := plIndex - $10;
      [*] = ;end
      [*] = ;else
      [*] = ;if plIndex < 0 then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;var myPlHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
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
      [*] = ;const cOfferAllianceBtnTag = 3;
      [*] = ;const cCancelAllianceBtnTag = 4;
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
      [*] = ;const cBtnInputBoxOfferGoldOk = 411;
      [*] = ;const cBtnInputBoxOfferGemOk = 421;
      [*] = ;const cBtnInputBoxDemandGoldOk = 416;
      [*] = ;const cBtnInputBoxDemandGemOk = 426;
      [*] = ;const cInputBoxOfferGoldInc = 430;
      [*] = ;const cInputBoxOfferGemInc = 440;
      [*] = ;const cInputBoxDemandGoldInc = 435;
      [*] = ;const cInputBoxDemandGemInc = 445;
      [*] = ;const cBtnInputBoxOfferGoldIncOk = 431;
      [*] = ;const cBtnInputBoxOfferGemIncOk = 441;
      [*] = ;const cBtnInputBoxDemandGoldIncOk = 436;
      [*] = ;const cBtnInputBoxDemandGemIncOk = 446;
      [*] = ;const cPlayerTag = 1000;
      [*] = ;const cOfferItemTag = 2000;
      [*] = ;const cDemandItemTag = 3000;
      [*] = ;const cOfferProvinceTag = 4000;
      [*] = ;const cDemandProvinceTag = 5000;
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
      [*] = ;var j : Integer;
      [*] = ;const cRowCount = 5;
      [*] = ;const cResOffX = cFrameWidth div cRowCount-3;
      [*] = ;const cResOffY = cFrameWidth div cRowCount-3;
      [*] = ;const cPaddingCanOffer = 38;
      [*] = ;const cOffersQueryOffX = -235;
      [*] = ;const cOffersQueryOffY = 64;
      [*] = ;const cDemandQueryOffX = -cOffersQueryOffX;
      [*] = ;const cDemandQueryOffY = cOffersQueryOffY;
      [*] = ;var scrollLayerWidth : Integer = 56*4+4;
      [*] = ;var scrollLayerHeight : Integer = 56*2+4;
      [*] = ;const scrollOnTableLayerHeight = 235;
      [*] = ;const cSmallWindowOffsetY = 17;
      [*] = ;const cSmallWindowDummyOffsetY = 36;
      [*] = ;
      [*] = ;procedure DrawGoldGemQueryBlock(mGiveGold, mGiveGem, mTakeGold, mTakeGem, parentElmOffer, parentElmDemand : Integer; var ShiftY1a, ShiftY2a : Integer);
      [*] = ;begin
      [*] = ;   var elmFrameHandle, elmHandle, inputHandle, elmBtnHandle : Integer = 0;
      [*] = ;   var bOfferGoldGem : Boolean = False;
      [*] = ;   var bDemandGoldGem : Boolean = False;
      [*] = ;   var r_pos : TRectangle;
      [*] = ;   if (mGiveGold>0) then
      [*] = ;   begin
      [*] = ;      //cInputBoxOfferGold
      [*] = ;      elmFrameHandle := _gui_CreateFrameBorder('frame_offergold', parentElmOffer, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame+ShiftY1a, cFrameWidth, cFrameHeight);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;      _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;      inputHandle := _gui_CreateInputControl_VVK('inputbox_offergold',elmFrameHandle,IntToStr(mGiveGold),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;      //inputHandle := CreateInputBoxSimple('inputbox_offergold', elmFrameHandle, IntToStr(mGiveGold), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      SetInputBoxSimpleEnabled(inputHandle, False);
      [*] = ;      _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentMiddle', 11, 0, 0, 0, 0);
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
      [*] = ;      SetInputBoxSimpleEnabled(inputHandle, False);
      [*] = ;      _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 11, 0, 0, 0, 0);
      [*] = ;      bOfferGoldGem := True;
      [*] = ;      ShiftY1a:=ShiftY1a+46;
      [*] = ;   end;
      [*] = ;   if (mTakeGold>0) then
      [*] = ;   begin
      [*] = ;      //cInputBoxOfferGold
      [*] = ;      elmFrameHandle := _gui_CreateFrameBorder('frame_demandgold', parentElmDemand, 'halParentLeft', 'valParentTop', cOfferMarginFrame div 2, cOfferMarginFrame+ShiftY2a, cFrameWidth, cFrameHeight);
      [*] = ;      elmHandle := _gui_CreateImage('', elmFrameHandle, cBlankMat, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmFrameHandle), GetGUIElementHeight(elmFrameHandle), 0);
      [*] = ;      _sys_FillRect(r_pos,11-3,4,cInputBoxWidth,0);
      [*] = ;      inputHandle := _gui_CreateInputControl_VVK('inputbox_demandgold',elmFrameHandle,IntToStr(mTakeGold),gc_gui_align_parent_m,true,r_pos,cInputBoxMaxChar, cEventState, 'gui|747');
      [*] = ;      //inputHandle := CreateInputBoxSimple('inputbox_demandgold', elmFrameHandle, IntToStr(mTakeGold), 'halParentMiddle', 'valParentMiddle', 11-3, 4, cInputBoxWidth, cInputBoxMaxChar, cEventState, 'gui|747', cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      SetInputBoxSimpleEnabled(inputHandle, False);
      [*] = ;      _gui_CreateImage('', elmFrameHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentMiddle', 11, 0, 0, 0, 0);
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
      [*] = ;      SetInputBoxSimpleEnabled(inputHandle, False);
      [*] = ;      _gui_CreateImage('', elmFrameHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', 11, 0, 0, 0, 0);
      [*] = ;      bDemandGoldGem := True;
      [*] = ;      ShiftY2a:=ShiftY2a+46;
      [*] = ;   end;
      [*] = ;   if (bOfferGoldGem) then
      [*] = ;      ShiftY1a:=ShiftY1a+cPaddingOffer;
      [*] = ;   if (bDemandGoldGem) then
      [*] = ;      ShiftY2a:=ShiftY2a+cPaddingOffer;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DrawResourceQueryBlock(message : TDiplMessage; elmParentHnd, plIndex, cOffersOffX, cOffersOffY, cDemandOffX, cDemandOffY : Integer; var Count1, Count2, ShiftY1, ShiftY2, Count1a, Count2a, ShiftY1a, ShiftY2a : Integer);
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;   var elmPlayerOffersHandle, elmImageHandle, elmBtnHandle, elmTextHandle : Integer;
      [*] = ;   for j:=1 to gPrototypeData.resources.number-1 do
      [*] = ;   begin
      [*] = ;      var resID : Integer = j;
      [*] = ;      if (message.tradeGive.arrResources[j-1]) then
      [*] = ;      begin
      [*] = ;         elmPlayerOffersHandle := _gui_CreateFrameBorder('', elmParentHnd, 'halParentMiddle', 'valParentTop', cOffersOffX-cResOffX-cResOffX+(Count1a mod cRowCount)*(cResOffX+4)-8, cOffersOffY+ShiftY1a+(Count1a div cRowCount)*(cResOffY+4), cResOffX, cResOffY{cFrameHeight-4});
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateImage('', elmPlayerOffersHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, 0);
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'map.resource.'+IntToStr(resID)+'.36x36', 'halParentMiddle', 'valParentMiddle', -1, 0, 0, 0, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, cEventState, 'resource|'+IntToStr(resID), cOfferResTag+j-1);
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.7);
      [*] = ;         SetGUIElementUserBlend(elmBtnHandle, 0.2);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         Count1a:=Count1a+1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (message.tradeTake.arrResources[j-1]) then
      [*] = ;      begin
      [*] = ;         elmPlayerOffersHandle := _gui_CreateFrameBorder('', elmParentHnd, 'halParentMiddle', 'valParentTop', cDemandOffX-cResOffX-cResOffX+(Count2a mod cRowCount)*(cResOffX+4)-8, cDemandOffY+ShiftY2a+(Count2a div cRowCount)*(cResOffY+4), cResOffX, cResOffY);
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateImage('', elmPlayerOffersHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, 0);
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'map.resource.'+IntToStr(resID)+'.36x36', 'halParentMiddle', 'valParentMiddle', -1, 0, 0, 0, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, cResOffX, cResOffY, cEventState, 'resource|'+IntToStr(resID), cDemandResTag+j-1);
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.7);
      [*] = ;         SetGUIElementUserBlend(elmBtnHandle, 0.2);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         Count2a:=Count2a+1;
      [*] = ;      end;
      [*] = ;   end;
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
      [*] = ;procedure DrawOfferQueryHUD(elmParent, mTreaty, mType : Integer);
      [*] = ;begin
      [*] = ;   //Treaty HUDs
      [*] = ;   var elmImageHandle, elmBtnHandle, elmPlayerOffersHandle, elmHandle : Integer;
      [*] = ;   const cOfferHUDOffsetY = 7+cSmallWindowOffsetY-24;
      [*] = ;   if (mTreaty>0) or (mType=cCancelTradeMode) then
      [*] = ;   begin
      [*] = ;      elmPlayerOffersHandle := _gui_CreateImage('', elmParent, cBlankMat, 'halParentMiddle', 'valParentTop', 0, cOfferHUDOffsetY, 0, 0, cCancelTreatyTag);
      [*] = ;      elmHandle := _gui_CreateCommonWindow('', '', '', 'halParentMiddle', 'valParentTop', 0, 0, 200, 69-6, False, False, False, 6, False);
      [*] = ;      AttachGUIElementToElement(elmHandle, elmPlayerOffersHandle);
      [*] = ;      SetGUIElementPositionX(elmHandle, -69);
      [*] = ;      SetGUIElementPositionY(elmHandle, -26);
      [*] = ;      var TextID : String;
      [*] = ;      case mTreaty of
      [*] = ;         cDeclareWarBtnTag: TextID:='184';
      [*] = ;         cOfferPeaceBtnTag: TextID:='185';
      [*] = ;         cOfferAllianceBtnTag: TextID:='186';
      [*] = ;         cCancelAllianceBtnTag: TextID:='174';
      [*] = ;         cCancelTradeBtnTag: TextID:='176';
      [*] = ;      end;
      [*] = ;      if (mType<>cCancelTradeMode) then
      [*] = ;      begin
      [*] = ;         if (mTreaty=4) then
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmHandle, 'icon.diplomacy.'+IntToStr(2), 'halParentLeft', 'valParentTop', 4, 7, 0, 0, 0);
      [*] = ;            _gui_CreateImage('', elmImageHandle, 'common.notenough.redline.cover', 'halParentLeft', 'valParentTop', 8, 8, 36, 36, 0);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmHandle, 'icon.diplomacy.'+IntToStr(mTreaty-1), 'halParentLeft', 'valParentTop', 4, 7, 0, 0, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, 'gui|'+IntToStr(178), cCancelTreatyTag);
      [*] = ;         SetGUIAllowEvents(elmBtnHandle, False, False, False);
      [*] = ;         _gui_CreateText('', elmImageHandle, GetLocaleTableListItemByID('gui', TextID) , 'halParentRight', 'valParentTop', 0, -1, 129, GetGUIElementHeight(elmImageHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         textID := '176';
      [*] = ;         _gui_CreateText('', elmHandle, GetLocaleTableListItemByID('gui', TextID) , 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (mType=cExchangeMode) or (mType=cTradeMode) then
      [*] = ;   begin
      [*] = ;      var txtID, imgID : Integer;;
      [*] = ;      if (mType=cExchangeMode) then
      [*] = ;      begin
      [*] = ;         txtID := 182;
      [*] = ;         imgID := 3;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      //if (mType=cTradeMode) then
      [*] = ;      begin
      [*] = ;         txtID := 181;
      [*] = ;         imgID := 4;
      [*] = ;      end;
      [*] = ;      elmPlayerOffersHandle := _gui_CreateImage('', elmParent, cBlankMat, 'halParentMiddle', 'valParentTop', 0, cOfferHUDOffsetY, 0, 0, cCancelTreatyTag);
      [*] = ;      elmHandle := _gui_CreateCommonWindow('', '', '', 'halParentMiddle', 'valParentTop', 0, 0, 200, 69-6, False, False, False, 6, False);
      [*] = ;      AttachGUIElementToElement(elmHandle, elmPlayerOffersHandle);
      [*] = ;      SetGUIElementPositionX(elmHandle, -69);
      [*] = ;      SetGUIElementPositionY(elmHandle, -26);
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmHandle, 'icon.diplomacy.'+IntToStr(imgID), 'halParentLeft', 'valParentTop', 4, 7, 0, 0, 0);
      [*] = ;      elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, 'gui|'+IntToStr(178), cClearMessageBtnTag);
      [*] = ;      SetGUIAllowEvents(elmBtnHandle, False, False, False);
      [*] = ;      var text : String = GetLocaleTableListItemByID('gui', IntToStr(txtID));
      [*] = ;      _gui_CreateText('', elmImageHandle, text, 'halParentRight', 'valParentTop', 0, -1, 129, GetGUIElementHeight(elmImageHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
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
      [*] = ;procedure DrawItemsQueryBlock(message : TDiplMessage; mGiveGold, mGiveGem, mTakeGold, mTakeGem, parentElmOffer, parentElmDemand, ShiftY1, ShiftY2, ShiftY1a, ShiftY2a : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   var pPlayer : Integer = ParserSelectPlayer(plHandle);
      [*] = ;   var pMyPlayer : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;   //var pPlTreasury : Integer = ParserSelectByHandleByKey(pPlayer,'Treasury');
      [*] = ;   //var pMyTreasury : Integer = ParserSelectByHandleByKey(pMyPlayer,'Treasury');
      [*] = ;
      [*] = ;   //Items
      [*] = ;   var ItemCount : Integer = 0;
      [*] = ;   ShiftY1 := ShiftY1+cPaddingCanOffer;
      [*] = ;
      [*] = ;   var tag, elmImageHandle, elmBtnHandle : Integer = 0;
      [*] = ;   var elmItemBlock : Integer = _gui_CreateImage('', parentElmOffer, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, ShiftY1a-4, scrollLayerWidth, scrollLayerHeight, Tag);
      [*] = ;
      [*] = ;   var NoRoom : Boolean = true;
      [*] = ;   for i:=0 to gc_MaxTradeItemCount-1 do
      [*] = ;   begin
      [*] = ;      if message.tradeGive.arrItems[i][0] = 0 then
      [*] = ;      NoRoom := false
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         {IntRegister0 := message.tradeGive.arrItems[i][0];
      [*] = ;         IntRegister1 := message.tradeGive.arrItems[i][1];
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'FindTreasuryItem');
      [*] = ;         var trIndex : Integer = IntRegister2;
      [*] = ;
      [*] = ;         if trIndex >= 0 then}
      [*] = ;         begin
      [*] = ;            //var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pPlTreasury, trIndex);
      [*] = ;            var itemID : Integer = message.tradeGive.arrItems[i][0];//ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;            var itemDur : Integer = message.tradeGive.arrItems[i][1];//ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;            var iconName : String;
      [*] = ;            _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;            var elmSlotHandle : Integer = _gui_CreateImage('', elmItemBlock, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 4+(i mod 4)*56, 4+(i div 4)*56, 0, 0, 0);
      [*] = ;            elmImageHandle := _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, tag);
      [*] = ;            elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;            //var hint : String = 'itemhint%|'+IntToStr(itemID)+'|'+IntToStr(3)+'|'+IntToStr(itemDur);
      [*] = ;            elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', '', tag);
      [*] = ;            _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBase,itemDur,cFT_ItemHeroDefault,cEventState,'3');
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 1);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.2);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            ItemCount:=ItemCount+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   var height : Integer = _misc_RoundUp(ItemCount/4)*56+4;
      [*] = ;   if (ItemCount>0) then
      [*] = ;   ShiftY1a:=ShiftY1a+height+10;
      [*] = ;   SetGUIElementHeight(elmItemBlock, height);
      [*] = ;
      [*] = ;   //On Table
      [*] = ;   ItemCount := 0;
      [*] = ;   elmItemBlock := _gui_CreateImage('', parentElmDemand, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, ShiftY2a-4, scrollLayerWidth, scrollLayerHeight, Tag);
      [*] = ;   //Demand
      [*] = ;   //On Table
      [*] = ;   NoRoom := true;
      [*] = ;   for i:=0 to gc_MaxTradeItemCount-1 do
      [*] = ;   begin
      [*] = ;      if message.tradeTake.arrItems[i][0] = 0 then
      [*] = ;      NoRoom := false
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         {IntRegister0 := message.tradeTake.arrItems[i][0];
      [*] = ;         IntRegister1 := message.tradeTake.arrItems[i][1];
      [*] = ;         PlayerExecuteStateByHandle(myPlHandle, 'FindTreasuryItem');
      [*] = ;         var trIndex : Integer = IntRegister2;
      [*] = ;
      [*] = ;         if trIndex >= 0 then}
      [*] = ;         begin
      [*] = ;            //var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pMyTreasury, trIndex);
      [*] = ;            var itemID : Integer = message.tradeTake.arrItems[i][0];//ParserGetIntValueByKeyByHandle(pTreasuryItem,'ItemID');
      [*] = ;            var itemDur : Integer = message.tradeTake.arrItems[i][1];//ParserGetIntValueByKeyByHandle(pTreasuryItem,'Durability');
      [*] = ;            //tag := cDemandItemTag + trIndex;
      [*] = ;            var iconName : String;
      [*] = ;            _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;            var elmSlotHandle : Integer = _gui_CreateImage('', elmItemBlock, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 4+(i mod 4)*56, 4+(i div 4)*56, 0, 0, 0);
      [*] = ;            elmImageHandle := _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, tag);
      [*] = ;            elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;            //var hint : String = 'itemhint%|'+IntToStr(itemID)+'|'+IntToStr(3)+'|'+IntToStr(itemDur);
      [*] = ;            elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', '', tag);
      [*] = ;            _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBase,itemDur,cFT_ItemHeroDefault,cEventState,'3');
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 1);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.2);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            ItemCount:=ItemCount+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   height := _misc_RoundUp(ItemCount/4)*56+4;
      [*] = ;   if (ItemCount>0) then
      [*] = ;   ShiftY2a:=ShiftY2a+height+10;
      [*] = ;   SetGUIElementHeight(elmItemBlock, height);
      [*] = ;   
      [*] = ;   const cProvinceItemHeight : Integer = 34;
      [*] = ;   //var scrollLayerHandProvinceHeight : Integer = cProvinceItemHeight*7+4;
      [*] = ;   elmItemBlock := _gui_CreateImage('', parentElmOffer, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, ShiftY1a-4, scrollLayerWidth, scrollLayerHeight, Tag);
      [*] = ;
      [*] = ;   // Province lists
      [*] = ;   // On Table
      [*] = ;   var pHexCells : Integer = gStratHexCells.handle;
      [*] = ;   //var provinceCount, provinceCountDemand : Integer = 0;
      [*] = ;   var provOnTableCount, provOnTableCountDemand : Integer = 0;
      [*] = ;   for i:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;   begin
      [*] = ;      var ind : Integer = message.tradeGive.arrProvinces[i];
      [*] = ;      if (ind>-1) then
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;         var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;         var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         var explored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;         var provinceRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;         var racePrefix : String = '';
      [*] = ;         case provinceRace of
      [*] = ;            1 : racePrefix := 'human';
      [*] = ;            2 : racePrefix := 'elf';
      [*] = ;            3 : racePrefix := 'dwarf';
      [*] = ;            4 : racePrefix := 'goblin';
      [*] = ;            5 : racePrefix := 'orc';
      [*] = ;            6 : racePrefix := 'halfling';
      [*] = ;            7 : racePrefix := 'centaur';
      [*] = ;            8 : racePrefix := 'lizardman';
      [*] = ;         end;
      [*] = ;         var elmName : String = 'map_infopanel_race_'+racePrefix;
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateFrameBorder('frame', elmItemBlock, 'halParentLeft', 'valParentTop', 4, 4+provOnTableCount*cProvinceItemHeight, 220, cProvinceItemHeight-4);
      [*] = ;         //var tag : Integer = cOfferProvinceTag+ind;
      [*] = ;         var hint : String = GetLocaleTableListItemByID('gui', '746');
      [*] = ;         AddProvinceInfoToHint(dummyHnd, hint);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmSlotHandle), GetGUIElementHeight(elmSlotHandle), cEventState, hint, tag);
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;         var elmHandle : Integer = _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', -2, 1, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;         // Province name
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         MapExecuteState('map.GetProvinceName');
      [*] = ;         var provName : String = StringRegister0;
      [*] = ;         var fontSize : String = '';
      [*] = ;         var width, height : Integer;
      [*] = ;
      [*] = ;         FindBestFontSize(provName, 220-cProvinceItemHeight*2, 3, width, height, fontSize);
      [*] = ;         elmHandle := _gui_CreateText('map_infopanel_province_name', elmSlotHandle, provName, 'halParentLeft', 'valParentTop', cProvinceItemHeight, 0, 220-cProvinceItemHeight*2, cProvinceItemHeight, 'halMiddle', 'valMiddle', fontSize, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;         //SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;         var resource : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;         var resourcePrefix : String = '';
      [*] = ;         case resource of
      [*] = ;            1 : resourcePrefix := 'iron';
      [*] = ;            2 : resourcePrefix := 'wood';
      [*] = ;            3 : resourcePrefix := 'horses';
      [*] = ;            4 : resourcePrefix := 'mandragora';
      [*] = ;            5 : resourcePrefix := 'arcanite';
      [*] = ;            6 : resourcePrefix := 'marble';
      [*] = ;            7 : resourcePrefix := 'mithril';
      [*] = ;            8 : resourcePrefix := 'diony';
      [*] = ;            9 : resourcePrefix := 'blacklotus';
      [*] = ;         end;
      [*] = ;         var resExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ResourceExplore');
      [*] = ;         if (resource>0) and (explored>=resExplore) then
      [*] = ;         begin
      [*] = ;            //elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', 0, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;            elmHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmSlotHandle, 'map.resource.'+IntToStr(resource)+'.61x61', 'halParentLeft', 'valParentTop', 220-cProvinceItemHeight, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;            SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         end;
      [*] = ;
      [*] = ;         provOnTableCount := provOnTableCount+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   height := _misc_RoundUp(provOnTableCount*cProvinceItemHeight)+4;
      [*] = ;   ShiftY1a:=ShiftY1a+height+10;
      [*] = ;   SetGUIElementHeight(parentElmOffer, ShiftY1a);
      [*] = ;
      [*] = ;   elmItemBlock := _gui_CreateImage('', parentElmDemand, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, ShiftY2a-4, scrollLayerWidth, scrollLayerHeight, Tag);
      [*] = ;
      [*] = ;   for i:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;   begin
      [*] = ;      var ind : Integer = message.tradeTake.arrProvinces[i];
      [*] = ;      if (ind>-1) then
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;         var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;         var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         var explored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;         var provinceRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;         var racePrefix : String = '';
      [*] = ;         case provinceRace of
      [*] = ;            1 : racePrefix := 'human';
      [*] = ;            2 : racePrefix := 'elf';
      [*] = ;            3 : racePrefix := 'dwarf';
      [*] = ;            4 : racePrefix := 'goblin';
      [*] = ;            5 : racePrefix := 'orc';
      [*] = ;            6 : racePrefix := 'halfling';
      [*] = ;            7 : racePrefix := 'centaur';
      [*] = ;            8 : racePrefix := 'lizardman';
      [*] = ;         end;
      [*] = ;         var elmName : String = 'map_infopanel_race_'+racePrefix;
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateFrameBorder('frame', elmItemBlock, 'halParentLeft', 'valParentTop', 4, 4+provOnTableCountDemand*cProvinceItemHeight, 220, cProvinceItemHeight-4);
      [*] = ;         //var tag : Integer = cDemandProvinceTag+ind;
      [*] = ;         var hint : String = GetLocaleTableListItemByID('gui', '746');
      [*] = ;         AddProvinceInfoToHint(dummyHnd, hint);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmSlotHandle), GetGUIElementHeight(elmSlotHandle), cEventState, hint, tag);
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;         var elmHandle : Integer = _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', -2, 1, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;         // Province name
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         MapExecuteState('map.GetProvinceName');
      [*] = ;         var provName : String = StringRegister0;
      [*] = ;         var fontSize : String = '';
      [*] = ;         var width, height : Integer;
      [*] = ;
      [*] = ;         FindBestFontSize(provName, 220-cProvinceItemHeight*2, 3, width, height, fontSize);
      [*] = ;         elmHandle := _gui_CreateText('map_infopanel_province_name', elmSlotHandle, provName, 'halParentLeft', 'valParentTop', cProvinceItemHeight, 0, 220-cProvinceItemHeight*2, cProvinceItemHeight, 'halMiddle', 'valMiddle', fontSize, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;         //SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;         var resource : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;         var resourcePrefix : String = '';
      [*] = ;         case resource of
      [*] = ;            1 : resourcePrefix := 'iron';
      [*] = ;            2 : resourcePrefix := 'wood';
      [*] = ;            3 : resourcePrefix := 'horses';
      [*] = ;            4 : resourcePrefix := 'mandragora';
      [*] = ;            5 : resourcePrefix := 'arcanite';
      [*] = ;            6 : resourcePrefix := 'marble';
      [*] = ;            7 : resourcePrefix := 'mithril';
      [*] = ;            8 : resourcePrefix := 'diony';
      [*] = ;            9 : resourcePrefix := 'blacklotus';
      [*] = ;         end;
      [*] = ;         var resExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ResourceExplore');
      [*] = ;         if (resource>0) and (explored>=resExplore) then
      [*] = ;         begin
      [*] = ;            //elmHandle := _gui_CreateImage(elmName, elmSlotHandle, 'map.infopanel.race.'+racePrefix, 'halParentLeft', 'valParentTop', 0, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;            elmHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmSlotHandle, 'map.resource.'+IntToStr(resource)+'.61x61', 'halParentLeft', 'valParentTop', 220-cProvinceItemHeight, 0, cProvinceItemHeight, cProvinceItemHeight, 0);
      [*] = ;            SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         end;
      [*] = ;         provOnTableCountDemand := provOnTableCountDemand+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   height := _misc_RoundUp(provOnTableCountDemand*cProvinceItemHeight)+4;
      [*] = ;   ShiftY2a:=ShiftY2a+height+10;
      [*] = ;   SetGUIElementHeight(parentElmDemand, ShiftY2a);
      [*] = ;end;
      [*] = ;
      [*] = ;var mTreaty : Integer = gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage.treaty;
      [*] = ;var mType : Integer = gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage.mType;
      [*] = ;if bReverseTables then
      [*] = ;begin
      [*] = ;   mTreaty := gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage.treaty;
      [*] = ;   mType := gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage.mType;
      [*] = ;end;
      [*] = ;
      [*] = ;var bNeedOfferDemandFrames : Boolean = ((mType=cTradeMode) or (mType=cExchangeMode));
      [*] = ;if (bNeedOfferDemandFrames)
      [*] = ;or ((mTreaty=cDeclareWarBtnTag) or (mTreaty=cOfferPeaceBtnTag) or (mTreaty=cOfferAllianceBtnTag) or (mTreaty=cCancelAllianceBtnTag)) then
      [*] = ;begin
      [*] = ;   var width : Integer = 250;
      [*] = ;   var height : Integer = 115-20;
      [*] = ;   if (bNeedOfferDemandFrames) then
      [*] = ;   begin
      [*] = ;      width := 740;
      [*] = ;      height := 300;
      [*] = ;   end;
      [*] = ;   //var elmDipQueryCoverHnd : Integer = _gui_CreateSmallWindow(elmParent, 'dipquerycover', 'halParentMiddle', 'valParentBottom', 0, cOffersQueryOffY-cOfferMarginFrame-cSmallWindowOffsetY, width, height, false);
      [*] = ;   var elmDipQueryCoverHnd : Integer = _gui_MODIFIED_CreateSmallWindow(elmParent, 'dipquerycover', 'halParentMiddle', 'valParentBottom', 0, cOffersQueryOffY-cOfferMarginFrame-cSmallWindowOffsetY, width, height, false);
      [*] = ;   var elmDipDummy : Integer = _gui_CreateImage('', elmDipQueryCoverHnd, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, cSmallWindowDummyOffsetY, GetGUIElementWidth(elmDipQueryCoverHnd), GetGUIElementHeight(elmDipQueryCoverHnd), 0);
      [*] = ;   var parentElmOffer, parentElmDemand : Integer = 0;
      [*] = ;   if (bNeedOfferDemandFrames) then
      [*] = ;   begin
      [*] = ;      var elmHandle : Integer = _gui_CreateFrameBorder('', elmDipDummy, 'halParentMiddle', 'valParentTop', cOffersQueryOffX, -cOfferMarginFrame+cSmallWindowOffsetY, cFrameWidth+cOfferMarginFrame*2, cFrameHeight*2+scrollLayerHeight+cPaddingOffer+cOfferMarginFrame*2);
      [*] = ;      elmHandle := _gui_CreateImage('', elmHandle, 'misc.blank.black.alpha.1', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 0);
      [*] = ;      SetGUIElementUserBlend(elmHandle, 0.65);
      [*] = ;      elmHandle := _gui_CreateFrameBorder('', elmDipDummy, 'halParentMiddle', 'valParentTop', cDemandQueryOffX, -cOfferMarginFrame+cSmallWindowOffsetY, cFrameWidth+cOfferMarginFrame*2, cFrameHeight*2+scrollLayerHeight+cPaddingOffer+cOfferMarginFrame*2);
      [*] = ;      elmHandle := _gui_CreateImage('', elmHandle, 'misc.blank.black.alpha.1', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 0);
      [*] = ;      SetGUIElementUserBlend(elmHandle, 0.65);
      [*] = ;      parentElmOffer := CreateScrollerParentExt('offers', elmDipDummy, 'halParentMiddle', 'valParentTop', gc_gui_material_blank_0, cOffersQueryOffX, cSmallWindowOffsetY, scrollLayerWidth, scrollOnTableLayerHeight, scrollLayerWidth, 0, scrollOnTableLayerHeight, true);
      [*] = ;      parentElmDemand := CreateScrollerParentExt('demand', elmDipDummy, 'halParentMiddle', 'valParentTop', gc_gui_material_blank_0, cDemandQueryOffX, cSmallWindowOffsetY, scrollLayerWidth, scrollOnTableLayerHeight, scrollLayerWidth, 0, scrollOnTableLayerHeight, true);
      [*] = ;   end;
      [*] = ;
      [*] = ;   procedure DrawDiplomacyOfferCover(message : TDiplMessage; tradeGive, tradeTake : TTrade);
      [*] = ;   begin
      [*] = ;      if (bNeedOfferDemandFrames) then
      [*] = ;      begin
      [*] = ;         var Count1, Count2, ShiftY1, ShiftY2, Count1a, Count2a, ShiftY1a, ShiftY2a : Integer = 0;
      [*] = ;         ShiftY1a := -cOfferMarginFrame;
      [*] = ;         ShiftY2a := -cOfferMarginFrame;
      [*] = ;         DrawGoldGemQueryBlock(tradeGive.gold, tradeGive.gem, tradeTake.gold, tradeTake.gem, parentElmOffer, parentElmDemand, ShiftY1a, ShiftY2a);
      [*] = ;
      [*] = ;         if (mType=cTradeMode) then
      [*] = ;         begin
      [*] = ;            ShiftY1a := ShiftY1a+cOfferMarginFrame;
      [*] = ;            ShiftY2a := ShiftY2a+cOfferMarginFrame;
      [*] = ;            DrawResourceQueryBlock(message, elmDipDummy, plIndex, cOffersQueryOffX, cSmallWindowOffsetY, cDemandQueryOffX, cSmallWindowOffsetY, Count1, Count2, ShiftY1, ShiftY2, Count1a, Count2a, ShiftY1a, ShiftY2a);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            ShiftY1a := ShiftY1a+cOfferMarginFrame;
      [*] = ;            ShiftY2a := ShiftY2a+cOfferMarginFrame;
      [*] = ;            DrawItemsQueryBlock(message, tradeGive.Gold, tradeGive.Gem, tradeTake.Gold, tradeTake.Gem, parentElmOffer, parentElmDemand, ShiftY1, ShiftY2, ShiftY1a, ShiftY2a);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      DrawOfferQueryHUD(elmDipDummy, mTreaty, mType);
      [*] = ;
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('', elmDipDummy, 'element.strip.341', 'halParentMiddle', 'valParentTop', 0, -34-cOfferMarginFrame-16, 0, 0, 0);
      [*] = ;      var text : String;
      [*] = ;      if bReverseTables then 
      [*] = ;      begin
      [*] = ;         if (gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage.deal >= 0) then
      [*] = ;            text := 'gui|743' // agreements
      [*] = ;         else
      [*] = ;         if (mTreaty = 0) and (_diplomacy_IsTradeFree(gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage.tradeGive)) and (not _diplomacy_IsTradeFree(gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage.tradeTake)) then
      [*] = ;            text := 'gui|198' // requests
      [*] = ;         else
      [*] = ;            text := 'gui|197'; // offers
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (not _diplomacy_IsProposal(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage)) then
      [*] = ;            text := 'gui|407' // messages
      [*] = ;         else
      [*] = ;         if (mTreaty = 0) and (_diplomacy_IsTradeFree(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage.tradeGive)) and (not _diplomacy_IsTradeFree(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage.tradeTake)) then
      [*] = ;            text := 'gui|198' // requests
      [*] = ;         else
      [*] = ;            text := 'gui|197'; // offers
      [*] = ;      end;
      [*] = ;      _gui_CreateText('', elmHandle, text, 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;      //elmHandle := _gui_CreateImage('', elmDipDummy, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, -34-cOfferMarginFrame+cSmallWindowOffsetY, 0, 0, 0);
      [*] = ;      //_gui_CreateText('', elmHandle, 'gui|743', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;      if (bNeedOfferDemandFrames) then
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmDipDummy, 'element.strip.240', 'halParentMiddle', 'valParentTop', cOffersQueryOffX, -34-cOfferMarginFrame+cSmallWindowOffsetY, 0, 0, 0);
      [*] = ;         _gui_CreateText('', elmHandle, 'gui|741', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;         elmHandle := _gui_CreateImage('', elmDipDummy, 'element.strip.240', 'halParentMiddle', 'valParentTop', cDemandQueryOffX, -34-cOfferMarginFrame+cSmallWindowOffsetY, 0, 0, 0);
      [*] = ;         _gui_CreateText('', elmHandle, 'gui|742', 'halParentMiddle', 'valParentTop', 0, -3, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if bReverseTables then
      [*] = ;      DrawDiplomacyOfferCover(gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage, gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage.tradeGive, gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage.tradeTake)
      [*] = ;   else
      [*] = ;      DrawDiplomacyOfferCover(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage, gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage.tradeGive, gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage.tradeTake);
      [*] = ;end;
      [*] = ;
      [*] = ;if bReverseTables then // clear after getting answer
      [*] = ;   _diplomacy_ClearMessage(gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage)
      [*] = ;else
      [*] = ;if (not _diplomacy_IsProposal(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage)) then // no answer required
      [*] = ;   _diplomacy_ClearMessage(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Reversed Tables: '+BoolToStr(bReverseTables)+', mType: '+IntToStr(mType)+', mTreaty: '+IntToStr(mTreaty)+']',$1000000 or _log_trace);
   struct.end
section.end

