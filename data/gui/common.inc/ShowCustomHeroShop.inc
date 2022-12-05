section.begin
   Name = ShowCustomHeroShop
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var parentHandle : Integer = IntRegister0;
      [*] = ;var inRank : Integer = IntRegister1;
      [*] = ;var scrollPos : Float = FloatRegister0;
      [*] = ;
      [*] = ;function _inet_GetItemRankAllowedByPrice(rank, price : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var visible : Boolean = False;
      [*] = ;   case rank of
      [*] = ;      1 : begin
      [*] = ;         if (price<=20) then
      [*] = ;            visible := True;
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         if (price>20) and (price<=50) then
      [*] = ;            visible := True;
      [*] = ;      end;
      [*] = ;      3 : begin
      [*] = ;         if (price>50) and (price<=100) then
      [*] = ;            visible := True;
      [*] = ;      end;
      [*] = ;      4 : begin
      [*] = ;         if (price>100) then
      [*] = ;            visible := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := visible;
      [*] = ;end;
      [*] = ;
      [*] = ;function _inet_GetItemRankAllowed(rank, shopLevel : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var visible : Boolean = False;
      [*] = ;   case rank of
      [*] = ;      1 : begin
      [*] = ;         if (shopLevel=1) or (shopLevel=2) then
      [*] = ;            visible := True;
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         if (shopLevel=3) then
      [*] = ;            visible := True;
      [*] = ;      end;
      [*] = ;      3 : begin
      [*] = ;         if (shopLevel=4) then
      [*] = ;            visible := True;
      [*] = ;      end;
      [*] = ;      4 : begin
      [*] = ;         if (shopLevel=5) or (shopLevel=6) then
      [*] = ;            visible := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := visible;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetSlotsMask(battle : TInetBattle;pItem : Integer) : Integer ;
      [*] = ;begin
      [*] = ;   var slots_mask : Integer = 0;
      [*] = ;   var pointPrice : Integer = ParserGetIntValueByKeyByHandle(pItem, 'PointPrice');
      [*] = ;   var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;
      [*] = ;   if (_inet_GetItemRankAllowedByPrice(inRank, round(pointPrice*gc_lan_itempricemod))) then
      [*] = ;   begin
      [*] = ;      var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemSlot');
      [*] = ;      var itemType : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;      var itemDurability : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;      if not (((itemType>=10) and (itemType<=13)) or ((itemType=0) and (itemSlot=0))) then
      [*] = ;      begin
      [*] = ;         var canUse : Boolean = _inet_GetCanUseItem(battle, itemID);
      [*] = ;
      [*] = ;         slots_mask := slots_mask or 1;
      [*] = ;         if (canUse) then slots_mask := slots_mask or 2;
      [*] = ;         if (itemSlot=1) or (ItemSlot=2) or (itemSlot=14) or (itemSlot=12) or (itemSlot=13) then slots_mask := slots_mask or 4;
      [*] = ;         if (itemSlot=3) or (itemSlot=4) or ((itemSlot=10) and (itemDurability>1)) or (itemSlot=8) or (itemSlot=7) then slots_mask := slots_mask or 8;
      [*] = ;         if (itemSlot=5) or (itemSlot=6) or (itemSlot=9) or ((itemSlot=10) and (itemDurability<=1)) or (itemSlot=11) then slots_mask := slots_mask or $10;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := slots_mask;
      [*] = ;end;
      [*] = ;
      [*] = ;const cEventState = 'EventCustomHeroShop';
      [*] = ;const cResetDragElementState = 'DoResetDragElement';
      [*] = ;const cBaseTagShopItemID = 1000;
      [*] = ;
      [*] = ;var fontHandle1, fontHandle2, fontHandle3 : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_smallest,'',fontHandle1);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandle3);
      [*] = ;
      [*] = ;procedure ShowCustomHeroShop(battle : TInetBattle;hero_items_mode : Integer);
      [*] = ;begin
      [*] = ;   const cSortButtonsNo = 5;
      [*] = ;   var items_count,i,sort_mask,mask : Integer;
      [*] = ;   var elmBtnHandleSortMode : array [0..cSortButtonsNo] of Integer;
      [*] = ;   var total_slots,tag : Integer;
      [*] = ;
      [*] = ;   //Кнопки сортировки предметов
      [*] = ;   var xOff : Integer = 46;
      [*] = ;   var posX : Integer = 0;
      [*] = ;   var posY : Integer = 0;
      [*] = ;   var elmSortTabs : Integer = _gui_CreateImage('sorttabs', parentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', 7, 0, 0, 0, 0);
      [*] = ;   const cBtnSort0 = 500;
      [*] = ;
      [*] = ;   for i := 0 to cSortButtonsNo-1 do
      [*] = ;   begin
      [*] = ;      case i of
      [*] = ;         0 : begin
      [*] = ;            elmBtnHandleSortMode[i] := _gui_CreateButton('castle_shop_sort_btn_all', elmSortTabs, '', 'map.radialhero.btn.treasury', 'halParentLeft', 'valParentBottomHeight', posX-6, posY+7, 0, 0, cEventState, '', cBtnSort0);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandleSortMode[i], 'CheckOnProperty', 'map.radialhero.btn.treasury.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;         end;
      [*] = ;         1 : elmBtnHandleSortMode[i] := _gui_CreateButtonFromCollection('castle_shop_sort_btn_hero_can_use', elmSortTabs, 'castle.shop.sort.btn.magic', 'halParentLeft', 'valParentBottomHeight', posX+xOff, posY, cEventState, cBtnSort0+i);
      [*] = ;         2 : elmBtnHandleSortMode[i] := _gui_CreateButtonFromCollection('castle_shop_sort_btn_weapon', elmSortTabs, 'castle.shop.sort.btn.weapon', 'halParentLeft', 'valParentBottomHeight', posX+xOff*2, posY, cEventState, cBtnSort0+i);
      [*] = ;         3 : elmBtnHandleSortMode[i] := _gui_CreateButtonFromCollection('castle_shop_sort_btn_armor', elmSortTabs, 'castle.shop.sort.btn.armor', 'halParentLeft', 'valParentBottomHeight', posX+xOff*3, posY, cEventState, cBtnSort0+i);
      [*] = ;         4 : elmBtnHandleSortMode[i] := _gui_CreateButtonFromCollection('castle_shop_sort_btn_jewels', elmSortTabs, 'castle.shop.sort.btn.jewels', 'halParentLeft', 'valParentBottomHeight', posX+xOff*4, posY, cEventState, cBtnSort0+i);
      [*] = ;         //5 : elmBtnHandleSortMode[i] := _gui_CreateButtonFromCollection('castle_shop_sort_btn_scrolls', elmSortTabs, 'castle.shop.sort.btn.scrolls', 'halParentLeft', 'valParentBottomHeight', posX+xOff*5, posY, '', gc_gui_shoppanel_btnSortScrolls);
      [*] = ;         //6 : elmBtnHandleSortMode[i] := _gui_CreateButtonFromCollection('castle_shop_sort_btn_summon_eggs', elmSortTabs, 'castle.shop.sort.btn.flags', 'halParentLeft', 'valParentBottomHeight', posX+xOff*6, posY, '', gc_gui_shoppanel_btnSortFlags);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gIntRegister_InetShopSortMode>cSortButtonsNo then
      [*] = ;         SetGUIElementChecked(elmBtnHandleSortMode[0],true)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if i=gIntRegister_InetShopSortMode then
      [*] = ;            SetGUIElementChecked(elmBtnHandleSortMode[i], true)
      [*] = ;         else
      [*] = ;            SetGUIElementChecked(elmBtnHandleSortMode[i], false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   const cItemsPerRow = 8;
      [*] = ;   const cMinSlotCount = 6*cItemsPerRow;
      [*] = ;   const cShopWidth = 52;
      [*] = ;   const cShopHeight = 52;
      [*] = ;   const cShopOffset = 4;
      [*] = ;   const cShopYOffset = 4;
      [*] = ;   const cItemLayerSizeX = 445;
      [*] = ;   const cItemLayerSizeY = 55*(cMinSlotCount div cItemsPerRow)+2;
      [*] = ;   const cItemLayerYOffset = cItemLayerSizeY+58;
      [*] = ;
      [*] = ;   for i:=0 to cMinSlotCount-1 do
      [*] = ;   begin
      [*] = ;      posX := (i mod cItemsPerRow)*(cShopWidth+cShopOffset);
      [*] = ;      posY := (i div cItemsPerRow)*(cShopHeight+cShopYOffset)-cItemLayerYOffset;
      [*] = ;      _gui_CreateImage('', parentHandle, 'icon.frame.item', 'halParentLeft', 'valParentBottom', posX-5, posY-5, 62, 62, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // scroll
      [*] = ;   var elmGuiLayer : Integer = AddNewElementByClassNameParent('scroll_layer', 'TXGuiLayer', 0, parentHandle);
      [*] = ;   SetGUIElementAlign(elmGuiLayer, 'halParentLeft', 'valParentBottom');
      [*] = ;   SetGUIElementAllPositionRect(elmGuiLayer, 0, -cItemLayerYOffset, cItemLayerSizeX, cItemLayerSizeY);
      [*] = ;   SetGUIElementMaterial(elmGuiLayer, gc_gui_material_blank_0);
      [*] = ;   SetGUIScrollEnabled(elmGuiLayer, True);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;   SetGUIElementAlign(elmVScroll, 'halParentLeft', 'valParentBottom');
      [*] = ;   SetGUIElementMaterialOffset(elmVScroll, -1, 0);
      [*] = ;   SetGUIElementAllPositionRect(elmVScroll, 445, -cItemLayerSizeY, 27, cItemLayerSizeY);
      [*] = ;   SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;   SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;   SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;   SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;   SetGUIAllowEvents(elmGuiLayer, True, False, False);
      [*] = ;   SetGUIElementPressState(elmGuiLayer, cResetDragElementState);
      [*] = ;
      [*] = ;   items_count := 0;
      [*] = ;   sort_mask := 1;
      [*] = ;   ArrayClear();
      [*] = ;   for i:=1 to gPrototypeData.items.number-1 do
      [*] = ;   begin
      [*] = ;      var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.items.handle, i);
      [*] = ;      var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;
      [*] = ;      mask := GetSlotsMask(battle,pItem);
      [*] = ;      if mask <> 0 then
      [*] = ;      begin
      [*] = ;         var visible : Boolean = False;
      [*] = ;
      [*] = ;         if ((mask and (1 shl gIntRegister_InetShopSortMode)) <> 0 ) then
      [*] = ;            visible := true;
      [*] = ;
      [*] = ;         if (visible) and (((gIntRegister_InetShopSortMode<>0) and ((mask and 2) = 0)) or (_inet_GetItemPrice(itemID)=0)) then
      [*] = ;            visible := false;
      [*] = ;
      [*] = ;         if (visible) then
      [*] = ;            ArrayPushValue(pItem);
      [*] = ;
      [*] = ;         sort_mask := sort_mask or mask;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   items_count := ArrayGetCount();
      [*] = ;   ArrayFlip();
      [*] = ;   total_slots := ((items_count+cItemsPerRow-1) div cItemsPerRow)*cItemsPerRow;
      [*] = ;   total_slots := max(cMinSlotCount,total_slots);
      [*] = ;
      [*] = ;   if _log then _log_Values('TOTAL|ITEMS',total_slots,items_count,0,0,0,0);
      [*] = ;   for i:=0 to (total_slots)-1 do
      [*] = ;   begin
      [*] = ;      posX := (i mod cItemsPerRow)*(cShopWidth+cShopOffset);
      [*] = ;      posY := (i div cItemsPerRow)*(cShopHeight+cShopYOffset);
      [*] = ;
      [*] = ;      if (i<items_count) then
      [*] = ;      begin
      [*] = ;         var pItem : Integer = ArrayPopValue();
      [*] = ;         var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;         var itemDurability : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;         var canUse : Boolean = _inet_GetCanUseItem(battle, itemID);
      [*] = ;
      [*] = ;         tag := cBaseTagShopItemID+itemID;
      [*] = ;
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateImage('open', elmGuiLayer, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;         var elmHandle : Integer;
      [*] = ;         var iconName,hint : String;
      [*] = ;         _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 62, 62, tag);
      [*] = ;         _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;         elmHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, cShopWidth, cShopHeight, tag);
      [*] = ;
      [*] = ;         if (not canUse) then
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmSlotHandle, 'heropanel.icon.52x52.red', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.6);
      [*] = ;         end;
      [*] = ;
      [*] = ;         elmHandle := _gui_CreateButton('item_slot', elmSlotHandle, 'item_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;         _gui_ft_AttachHint_I4_S2(elmHandle,'VVK.FTooltipItem',itemID,cFT_ItemPricePoints,-1,hero_items_mode,cEventState,'1');
      [*] = ;         SetGUIElementVisibleProperties(elmHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 1, 0.5, 0.5, 0.5, 1);
      [*] = ;
      [*] = ;         if (gIntRegister_InetShopPickedItemID=itemID) then
      [*] = ;            SetGUIElementChecked(elmHandle, True);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateImage('', elmGuiLayer, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;         tag := 0;
      [*] = ;         if (gIntRegister_InetPickedItemSlot>-1) then
      [*] = ;         begin
      [*] = ;            var elmHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;            elmHandle := _gui_CreateButton('castle_shop_slot_highlighted', elmSlotHandle, '', 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, cEventState, '', tag);
      [*] = ;            SetGUIElementVisibleProperties(elmHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 62, 62, tag);
      [*] = ;            _gui_CreateImage('castle_shop_empty_slot', elmSlotHandle, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', -2, -2, 56, 56, 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to cSortButtonsNo-1 do
      [*] = ;   begin
      [*] = ;      if ((sort_mask and (1 shl i)) <> 0) then
      [*] = ;         SetGUIElementEnabled(elmBtnHandleSortMode[i], True)
      [*] = ;      else
      [*] = ;         SetGUIElementEnabled(elmBtnHandleSortMode[i], False);
      [*] = ;   end;
      [*] = ;   SetGUIElementHeight(elmGuiLayer,((total_slots div 8)*(cShopHeight+cShopYOffset))-4);
      [*] = ;
      [*] = ;   // restore scroller position
      [*] = ;   SetGUIScrollBarPosition(elmVScroll, scrollPos);
      [*] = ;
      [*] = ;   function CreateShopTabs(elmParentHandle, rank : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      const cBtnRank1 = 301;
      [*] = ;      const cBtnRank2 = 302;
      [*] = ;      const cBtnRank3 = 303;
      [*] = ;      const cBtnRank4 = 304;
      [*] = ;
      [*] = ;      var posX : Integer = 0;
      [*] = ;      var posY : Integer = 2;
      [*] = ;      var elmSquadRecruitTabs : Integer = _gui_CreateImage('', elmParentHandle, 'shell.tabshero.4btn.background', 'halParentMiddle', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;      posX := 47;
      [*] = ;      posY := 12;
      [*] = ;
      [*] = ;      var elmHandle : Integer;
      [*] = ;      var hint : String = GetLocaleTableListItemByID('gui', IntToStr(10))+' '+IntToStr(1);
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('', elmSquadRecruitTabs, '', 'shell.btn.rank.1', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, hint, cBtnRank1);
      [*] = ;      if (rank=1) or (gBoolRegister_InetStartBattle) then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;      if (rank=1) then
      [*] = ;      elmHandle := _gui_CreateImage('', elmSquadRecruitTabs, 'shell.btn.rank.1.pressed', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;
      [*] = ;      posX := posX+54;
      [*] = ;      hint := GetLocaleTableListItemByID('gui', IntToStr(10))+' '+IntToStr(2);
      [*] = ;      elmBtnHandle := _gui_CreateButton('', elmSquadRecruitTabs, '', 'shell.btn.rank.2', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, hint, cBtnRank2);
      [*] = ;      if (rank=2) or (gBoolRegister_InetStartBattle) then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;      if (rank=2) then
      [*] = ;      elmHandle := _gui_CreateImage('', elmSquadRecruitTabs, 'shell.btn.rank.2.pressed', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;
      [*] = ;      posX := posX+53;
      [*] = ;      hint := GetLocaleTableListItemByID('gui', IntToStr(10))+' '+IntToStr(3);
      [*] = ;      elmBtnHandle := _gui_CreateButton('', elmSquadRecruitTabs, '', 'shell.btn.rank.3', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, hint, cBtnRank3);
      [*] = ;      if (rank=3) or (gBoolRegister_InetStartBattle) then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;      if (rank=3) then
      [*] = ;      elmHandle := _gui_CreateImage('', elmSquadRecruitTabs, 'shell.btn.rank.3.pressed', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;
      [*] = ;      posX := posX+53;
      [*] = ;      hint := GetLocaleTableListItemByID('gui', IntToStr(10))+' '+IntToStr(4);
      [*] = ;      elmBtnHandle := _gui_CreateButton('', elmSquadRecruitTabs, '', 'shell.btn.rank.4', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, cEventState, hint, cBtnRank4);
      [*] = ;      if (rank=4) or (gBoolRegister_InetStartBattle) then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;      if (rank=4) then
      [*] = ;      elmHandle := _gui_CreateImage('', elmSquadRecruitTabs, 'shell.btn.rank.4.pressed', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;
      [*] = ;      Result := elmSquadRecruitTabs;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var elmShopTabs : Integer = CreateShopTabs(GetGUIElementParentByIndex(parentHandle), gIntRegister_InetShopRankMode);
      [*] = ;end;
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;   ShowCustomHeroShop(gEditorCustomPlayerTemporary,cFT_ItemHeroMapEditor)
      [*] = ;else
      [*] = ;if (gBoolRegister_IsHotSeat) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_HotSeatActivePlayer=0) then
      [*] = ;      ShowCustomHeroShop(gHotSeatPlayer1,cFT_ItemHeroHotSeat1)
      [*] = ;   else
      [*] = ;      ShowCustomHeroShop(gHotSeatPlayer2,cFT_ItemHeroHotSeat2)
      [*] = ;end
      [*] = ;else
      [*] = ;   ShowCustomHeroShop(gInetBattle,cFT_ItemHeroMultiplayer);
   struct.end
section.end

