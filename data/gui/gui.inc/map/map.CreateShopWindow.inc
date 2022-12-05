section.begin
   Name = map.CreateShopWindow
   Code : struct.begin
      [*] = ;const cTempOffsetFromBottom = 0;
      [*] = ;
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var posX, posY : Integer;
      [*] = ;var xOff, yOff : Integer;
      [*] = ;const cShopEventHandler = 'map.ShopPickItem';
      [*] = ;const cTreasuryEventHandler = 'map.PressTreasurySlot';
      [*] = ;const cBgWidth = 604;
      [*] = ;const cBgHeight = 828;
      [*] = ;const cShopWidth = 52;
      [*] = ;const cShopHeight = 52;
      [*] = ;
      [*] = ;var fontHandleT, fontHandleH2, fontHandleH1: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandleT);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_large,'',fontHandleH2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_largest,'',fontHandleH1); // HeaderM
      [*] = ;
      [*] = ;const cFontParamsColorR = gc_gui_fontcolor_HeaderRedR;
      [*] = ;const cFontParamsColorG = gc_gui_fontcolor_HeaderRedG;
      [*] = ;const cFontParamsColorB = gc_gui_fontcolor_HeaderRedB;
      [*] = ;const cFontParamsColorA = 1;
      [*] = ;
      [*] = ;var cShopX : Integer = 106;
      [*] = ;var cShopY : Integer = 154;
      [*] = ;var cShopOffset : Integer = 4;
      [*] = ;var cShopYOffset : Integer = 4;
      [*] = ;var top : Integer = _gui_GetLayerI();
      [*] = ;var elmImageHandle  : Integer;
      [*] = ;var elmBtnHandle    : Integer;
      [*] = ;var tag : Integer = 0;
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;var pCastleProvince : Integer = IntRegister0;
      [*] = ;var pProvince : Integer = pCastleProvince;
      [*] = ;
      [*] = ;SetGUIElementVisible(_gui_GetWindow('map_shoppanel'),true);
      [*] = ;
      [*] = ;var elmScrollLayer : Integer = GetGUIElementIndexByNameParent('map_shoppanel.map_shoppanel_bg.map_shoppanel_items.scroll_layer', _gui_GetLayerI());
      [*] = ;var lastScrollPos : Float = 0;
      [*] = ;if (elmScrollLayer<>0) then
      [*] = ;begin
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;   if (elmVScroll<>0) then
      [*] = ;   lastScrollPos := GetGUIScrollBarPosition(elmVScroll);
      [*] = ;end;
      [*] = ;var elmShopPanelHandle : Integer = _gui_GetOrCreateElement('map_shoppanel', top, 'halMiddle', 'valParentBottomHeight', 0, 0, 0, 0, Tag);
      [*] = ;_gui_RootWindowAddExt(elmShopPanelHandle,cRootWindowActive,0,cRootWindowAttrScaleByY,'');
      [*] = ;
      [*] = ;if (gIntRegister_GUICurCastleMode<>0) and (goHandle <> 0) then
      [*] = ;begin
      [*] = ;   var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   var castleUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   if (castleUID<>curUID) then
      [*] = ;      goHandle := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;var castlePosX : Integer = -5;
      [*] = ;var heroPosX : Integer = 355-39;
      [*] = ;var elmShopPanelBg : Integer;
      [*] = ;var elmShopBgHandle : Integer;
      [*] = ;var elmText : Integer;
      [*] = ;var alignOffsetX, alignOffsetY : Integer;
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;begin
      [*] = ;   elmShopPanelBg := _gui_CreateDummy('map_shoppanel_bg', elmShopPanelHandle, 'halParentMiddle', 'valBottomHeight', heroPosX, cTempOffsetFromBottom, 0, 0, Tag);
      [*] = ;   elmImageHandle := _gui_CreateImage('map_shoppanel_background', elmShopPanelBg, 'map.heropanel.rightside.background', 'halParentMiddle', 'valParentBottomHeight', 0, 0, 681, 1020, Tag);
      [*] = ;
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;   posX := -5;
      [*] = ;   posY := -54;
      [*] = ;   //map.heropanel.shop.background
      [*] = ;   //elmShopBgHandle := _gui_CreateImage('castle_shop_background', elmShopPanelBg, 'map.heropanel.shop.background', 'halParentMiddle', 'valParentBottomHeight', posX, posY, cBgWidth, cBgHeight, Tag);
      [*] = ;   elmShopBgHandle := _gui_CreateImage('castle_shop_background', elmShopPanelBg, 'castle.shop.background'{'map.heropanel.shop.background'}, 'halParentMiddle', 'valParentBottomHeight', posX+7, posY-19, 0, 0, Tag);
      [*] = ;   //elmImageHandle := _gui_CreateImage('', elmShopBgHandle, 'decor.dragon', 'halParentLeft', 'valParentTop', -30, -131, 678, 207, Tag);
      [*] = ;
      [*] = ;   posX := 0;
      [*] = ;   posY := -857;
      [*] = ;   elmText := _gui_CreateText('', elmShopPanelBg, GetLocaleTableListItemByID('gui', '592'), 'halParentMiddle', 'valParentBottomHeight', posX, posY, 380, 32, 'halMiddle', 'valTop', fontHandleH1, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;
      [*] = ;   alignOffsetX := -343+17;
      [*] = ;   alignOffsetY := -905-20+cTempOffsetFromBottom;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   elmShopPanelBg := _gui_CreateDummy('map_shoppanel_bg', elmShopPanelHandle, 'halLeft', 'valBottomHeight', castlePosX, 0, 711, 925, Tag);
      [*] = ;   elmImageHandle := _gui_CreateImage('map_shoppanel_background' , elmShopPanelBg, 'map.heropanel.leftside.background', 'halParentLeft', 'valParentBottomHeight', 0, 0, 711, 925, Tag);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;   posX := 31;
      [*] = ;   posY := -73;
      [*] = ;   elmShopBgHandle := _gui_CreateImage('castle_shop_background' , elmShopPanelBg, 'castle.shop.background', 'halParentLeft', 'valParentBottomHeight', posX, posY, 587, 796, Tag);
      [*] = ;   elmImageHandle := _gui_CreateImageSimple('', elmShopPanelBg, 'element.header.strip.629', 'halParentLeft', 'valParentBottomHeight', 10, -832);
      [*] = ;
      [*] = ;   posX := -31;
      [*] = ;   posY := -857;
      [*] = ;   elmText := _gui_CreateText('', elmShopPanelBg, GetLocaleTableListItemByID('gui', '592'), 'halParentMiddle', 'valParentBottomHeight', posX, posY, 380, 32, 'halMiddle', 'valTop', fontHandleH1, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;
      [*] = ;   alignOffsetX := -35+31;
      [*] = ;   alignOffsetY := -925;
      [*] = ;end;
      [*] = ;
      [*] = ;if gIntRegister_MapCurrentShop = 0 then
      [*] = ;   gIntRegister_MapCurrentShop := ParserSelectByHandleByKey(pCastleProvince, 'Shop');
      [*] = ;
      [*] = ;var pProvItems : Integer = ParserSelectByHandleByKey(gIntRegister_MapCurrentShop, 'Items');
      [*] = ;var elmShopItems : Integer = _gui_CreateDummy('map_shoppanel_items', elmShopPanelBg, 'halParentLeft', 'valParentBottomHeight', alignOffsetX, alignOffsetY, 0, 0, Tag);
      [*] = ;var shopItemCount : Integer = ParserGetCountByHandle(pProvItems);
      [*] = ;var elmSlotHandle : Integer;
      [*] = ;
      [*] = ;//Кнопки сортировки предметов
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;begin
      [*] = ;   posX := -244+17;
      [*] = ;   posY := -94+5;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   posX := 78+17;
      [*] = ;   posY := -94+5;
      [*] = ;end;
      [*] = ;xOff := 46;
      [*] = ;//var elmBtnHandleSortMode0 : Integer = _gui_CreateButtonFromCollection('castle_shop_sort_btn_all', elmShopPanelBg, 'castle.shop.sort.btn.all'     , 'halParentLeft', 'valParentBottomHeight', posX         , posY, '', gc_gui_shoppanel_btnSortAll);
      [*] = ;var elmBtnHandleSortMode0 : Integer = _gui_CreateButton('castle_shop_sort_btn_all', elmShopPanelBg, '', 'map.radialhero.btn.treasury', 'halParentLeft', 'valParentBottomHeight', posX-6, posY+7, 0, 0, '', '', gc_gui_shoppanel_btnSortAll);
      [*] = ;SetGUIElementVisibleProperties(elmBtnHandleSortMode0, 'CheckOnProperty', 'map.radialhero.btn.treasury.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;var elmBtnHandleSortMode1 : Integer = _gui_CreateButtonFromCollection('castle_shop_sort_btn_hero_can_use', elmShopPanelBg, 'castle.shop.sort.btn.magic'   , 'halParentLeft', 'valParentBottomHeight', posX + xOff  , posY, '', gc_gui_shoppanel_btnSortMagic);
      [*] = ;var elmBtnHandleSortMode2 : Integer = _gui_CreateButtonFromCollection('castle_shop_sort_btn_weapon', elmShopPanelBg, 'castle.shop.sort.btn.weapon'  , 'halParentLeft', 'valParentBottomHeight', posX + xOff*2, posY, '', gc_gui_shoppanel_btnSortWeapon);
      [*] = ;var elmBtnHandleSortMode3 : Integer = _gui_CreateButtonFromCollection('castle_shop_sort_btn_armor', elmShopPanelBg, 'castle.shop.sort.btn.armor'   , 'halParentLeft', 'valParentBottomHeight', posX + xOff*3, posY, '', gc_gui_shoppanel_btnSortArmor);
      [*] = ;var elmBtnHandleSortMode4 : Integer = _gui_CreateButtonFromCollection('castle_shop_sort_btn_jewels', elmShopPanelBg, 'castle.shop.sort.btn.jewels'  , 'halParentLeft', 'valParentBottomHeight', posX + xOff*4, posY, '', gc_gui_shoppanel_btnSortJewels);
      [*] = ;var elmBtnHandleSortMode5 : Integer = _gui_CreateButtonFromCollection('castle_shop_sort_btn_scrolls', elmShopPanelBg, 'castle.shop.sort.btn.scrolls' , 'halParentLeft', 'valParentBottomHeight', posX + xOff*5, posY, '', gc_gui_shoppanel_btnSortScrolls);
      [*] = ;var elmBtnHandleSortMode6 : Integer = _gui_CreateButtonFromCollection('castle_shop_sort_btn_summon_eggs', elmShopPanelBg, 'castle.shop.sort.btn.flags'   , 'halParentLeft', 'valParentBottomHeight', posX + xOff*6, posY, '', gc_gui_shoppanel_btnSortFlags);
      [*] = ;
      [*] = ;SetGUIElementChecked(elmBtnHandleSortMode0, false);
      [*] = ;SetGUIElementChecked(elmBtnHandleSortMode1, false);
      [*] = ;SetGUIElementChecked(elmBtnHandleSortMode2, false);
      [*] = ;SetGUIElementChecked(elmBtnHandleSortMode3, false);
      [*] = ;SetGUIElementChecked(elmBtnHandleSortMode4, false);
      [*] = ;SetGUIElementChecked(elmBtnHandleSortMode5, false);
      [*] = ;SetGUIElementChecked(elmBtnHandleSortMode6, false);
      [*] = ;
      [*] = ;SetGUIElementEnabled(elmBtnHandleSortMode0, True);
      [*] = ;SetGUIElementEnabled(elmBtnHandleSortMode1, false);
      [*] = ;SetGUIElementEnabled(elmBtnHandleSortMode2, false);
      [*] = ;SetGUIElementEnabled(elmBtnHandleSortMode3, false);
      [*] = ;SetGUIElementEnabled(elmBtnHandleSortMode4, false);
      [*] = ;SetGUIElementEnabled(elmBtnHandleSortMode5, false);
      [*] = ;SetGUIElementEnabled(elmBtnHandleSortMode6, false);
      [*] = ;
      [*] = ;case gIntRegister_GUIShopSortMode of
      [*] = ;   1 : SetGUIElementChecked(elmBtnHandleSortMode1, true);
      [*] = ;   2 : SetGUIElementChecked(elmBtnHandleSortMode2, true);
      [*] = ;   3 : SetGUIElementChecked(elmBtnHandleSortMode3, true);
      [*] = ;   4 : SetGUIElementChecked(elmBtnHandleSortMode4, true);
      [*] = ;   5 : SetGUIElementChecked(elmBtnHandleSortMode5, true);
      [*] = ;   6 : SetGUIElementChecked(elmBtnHandleSortMode6, true);
      [*] = ;   else
      [*] = ;   SetGUIElementChecked(elmBtnHandleSortMode0, true);
      [*] = ;end;
      [*] = ;
      [*] = ;// shop items
      [*] = ;var ind : Integer = -1;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;// scroll
      [*] = ;var elmGuiLayer : Integer = AddNewElementByClassNameParent('scroll_layer', 'TXGuiLayer', 0, elmShopItems);
      [*] = ;SetGUIElementAlign(elmGuiLayer, 'halParentLeft', 'valParentTop');
      [*] = ;posX  := cShopX;
      [*] = ;posY  := cShopY+1;
      [*] = ;var sizeX : Integer = 445;
      [*] = ;var sizeY : Integer = 276;
      [*] = ;SetGUIElementAllPositionRect(elmGuiLayer, posX, posY, sizeX, sizeY);
      [*] = ;SetGUIElementMaterial(elmGuiLayer, gc_gui_material_blank_0);
      [*] = ;SetGUIScrollEnabled(elmGuiLayer, True);
      [*] = ;var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;SetGUIElementAlign(elmVScroll, 'halParentLeft', 'valParentTop');
      [*] = ;SetGUIElementMaterialOffset(elmVScroll, -1, 0);
      [*] = ;SetGUIElementAllPositionRect(elmVScroll, 445, 0, 27, sizeY);
      [*] = ;SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;SetGUIAllowEvents(elmGuiLayer, True, False, False);
      [*] = ;SetGUIElementPressState(elmGuiLayer, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;var visibleShopItemCount : Integer = 0;
      [*] = ;for i := 0 to shopItemCount-1 do
      [*] = ;begin
      [*] = ;   var pProvItem : Integer = ParserSelectByHandleByIndex(pProvItems, i);
      [*] = ;   var itemID : Integer = ParserGetIntValueByKeyByHandle(pProvItem, 'ItemID');
      [*] = ;   if (itemID<>0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := itemID;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetItemParserByID', 0);
      [*] = ;      var pItem : Integer = IntRegister1;
      [*] = ;      var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemSlot');
      [*] = ;      var itemType : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;      var itemDurability : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;      var visible : Boolean = False;
      [*] = ;      var canUse : Boolean = True;
      [*] = ;      if (goHandle<>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := ItemID;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'CanUseItem');
      [*] = ;         canUse := BoolRegister0;
      [*] = ;      end;
      [*] = ;      case gIntRegister_GUIShopSortMode of
      [*] = ;         1 : if (canUse) then visible := True;
      [*] = ;         2 : if (itemSlot=1) or (ItemSlot=2) or (itemSlot=14) or (itemSlot=12) or (itemSlot=13) then visible := True;
      [*] = ;         3 : if (itemSlot=3) or (itemSlot=4) or ((itemSlot=10) and (itemDurability>1)) or (itemSlot=8) or (itemSlot=7) then visible := True;
      [*] = ;         4 : if (itemSlot=5) or (itemSlot=6) or (itemSlot=9) or ((itemSlot=10) and (itemDurability<=1)) or (itemSlot=11) then visible := True;
      [*] = ;         5 : if (itemType>=10) and (itemType<=13) then visible := True;
      [*] = ;         6 : if (itemType=0) and (itemSlot=0) then visible := True;
      [*] = ;         else
      [*] = ;         visible := True;
      [*] = ;      end;
      [*] = ;      if (visible) then
      [*] = ;      visibleShopItemCount := visibleShopItemCount+1
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var hint : String;
      [*] = ;var addCount : Integer;
      [*] = ;const cMinSlotCount = 40;
      [*] = ;//if ((visibleShopItemCount mod 8)>0) then
      [*] = ;begin
      [*] = ;   if (visibleShopItemCount>=cMinSlotCount) then
      [*] = ;   addCount := 8-(visibleShopItemCount mod 8)+8
      [*] = ;   else
      [*] = ;   addCount := (cMinSlotCount-visibleShopItemCount);
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to (shopItemCount+addCount)-1 do
      [*] = ;begin
      [*] = ;   ind := ind+1;
      [*] = ;
      [*] = ;   posX := (ind mod 8) * (cShopWidth + cShopOffset);
      [*] = ;   posY := (ind div 8) * (cShopHeight + cShopYOffset);
      [*] = ;
      [*] = ;   tag := gc_gui_shopitemslots_btnBaseTag + ind;
      [*] = ;
      [*] = ;   var highlight, disabled : Boolean = False;
      [*] = ;   if (gIntRegister_MapPickedItemID<>0) and (not SameText(gStringRegister_ItemPlace, 'Shop')) then
      [*] = ;   highlight := True;
      [*] = ;
      [*] = ;   if (i<shopItemCount) then
      [*] = ;   begin
      [*] = ;      var pProvItem : Integer = ParserSelectByHandleByIndex(pProvItems, i);
      [*] = ;      var itemID : Integer = ParserGetIntValueByKeyByHandle(pProvItem, 'ItemID');
      [*] = ;      var count : Integer = ParserGetIntValueByKeyByHandle(pProvItem, 'Count');
      [*] = ;
      [*] = ;      var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;      var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;      var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;      IntRegister0 := itemID;
      [*] = ;      IntRegister1 := GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;      IntRegister2 := gIntRegister_MapCurrentShop;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetItemPrice');
      [*] = ;      var gold : Integer = IntRegister3;
      [*] = ;      var gem : Integer = IntRegister4;
      [*] = ;
      [*] = ;      if (gBoolRegister_RepairItemMode) then
      [*] = ;         disabled := True;
      [*] = ;
      [*] = ;      if (plGold<gold) or (plGem<gem) then
      [*] = ;         disabled := True;
      [*] = ;
      [*] = ;      if (disabled) then
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('open', elmGuiLayer, 'heropanel.icon.52x52.slot.empty.disabled', 'halParentLeft', 'valParentTop', posX, posY)
      [*] = ;      else
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('open', elmGuiLayer, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;
      [*] = ;      if (itemID<>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         StateMachineExecuteState(initMachine, 'GetItemParserByID', 0);
      [*] = ;         var pItem : Integer = IntRegister1;
      [*] = ;         var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemSlot');
      [*] = ;         var itemType : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;         var itemDurability : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;         var visible : Boolean = False;
      [*] = ;         var canUse : Boolean = True;
      [*] = ;         if (goHandle<>0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := ItemID;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CanUseItem');
      [*] = ;            canUse := BoolRegister0;
      [*] = ;         end;
      [*] = ;
      [*] = ;         case gIntRegister_GUIShopSortMode of
      [*] = ;            1 : if (canUse) then visible := True;
      [*] = ;            2 : if (itemSlot=1) or (ItemSlot=2) or (itemSlot=14) or (itemSlot=12) or (itemSlot=13) then visible := True;
      [*] = ;            3 : if (itemSlot=3) or (itemSlot=4) or ((itemSlot=10) and (itemDurability>1)) or (itemSlot=8) or (itemSlot=7) then visible := True;
      [*] = ;            4 : if (itemSlot=5) or (itemSlot=6) or (itemSlot=9) or ((itemSlot=10) and (itemDurability<=1)) or (itemSlot=11) then visible := True;
      [*] = ;            5 : if (itemType>=10) and (itemType<=13) then visible := True;
      [*] = ;            6 : if (itemType=0) and (itemSlot=0) then visible := True;
      [*] = ;            else
      [*] = ;            visible := True;
      [*] = ;         end;
      [*] = ;         if (goHandle<>0) and (canUse) then SetGUIElementEnabled(elmBtnHandleSortMode1, True);
      [*] = ;         if (itemSlot=1) or (ItemSlot=2) or (itemSlot=14) or (itemSlot=12) or (itemSlot=13) then SetGUIElementEnabled(elmBtnHandleSortMode2, True);
      [*] = ;         if (itemSlot=3) or (itemSlot=4) or ((itemSlot=10) and (itemDurability>1)) or (itemSlot=8) or (itemSlot=7) then SetGUIElementEnabled(elmBtnHandleSortMode3, True);
      [*] = ;         if (itemSlot=5) or (itemSlot=6) or (itemSlot=9) or ((itemSlot=10) and (itemDurability<=1)) or (itemSlot=11) then SetGUIElementEnabled(elmBtnHandleSortMode4, True);
      [*] = ;         if (itemType>=10) and (itemType<=13) then SetGUIElementEnabled(elmBtnHandleSortMode5, True);
      [*] = ;         if (itemType=0) and (itemSlot=0) then SetGUIElementEnabled(elmBtnHandleSortMode6, True);
      [*] = ;
      [*] = ;         if (visible) then
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImage('' , elmSlotHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 62, 62, tag);
      [*] = ;            var iconName : String;
      [*] = ;            _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;            elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, cShopWidth, cShopHeight, tag);
      [*] = ;            if (goHandle<>0) then
      [*] = ;            begin
      [*] = ;               if (not canUse) then
      [*] = ;               begin
      [*] = ;                  elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, 'heropanel.icon.52x52.red', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;                  SetGUIElementUserBlend(elmImageHandle, 0.5);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            elmBtnHandle := _gui_CreateButton('item_slot', elmSlotHandle, 'item_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;            _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBuy,itemDurability,gIntRegister_GUIActiveHeroUID1,cShopEventHandler,'3');
      [*] = ;
      [*] = ;            if (count>0) then
      [*] = ;            begin
      [*] = ;               var width, height : Integer;
      [*] = ;               GetGUIElementFontTextFormatRect(fontHandleT, IntToStr(count), width, height);
      [*] = ;               elmImageHandle := _gui_CreateImage('item_shop_count', elmBtnHandle, 'pixel.0.0.0', 'halParentRight', 'valParentBottom', -width-8, -height-3, width+6, height+1, count);
      [*] = ;               SetGUIElementUserBlend(elmImageHandle, 0.75);
      [*] = ;               var elmTextHandle : Integer = _gui_CreateText('item_shop_count_text', elmImageHandle, IntToStr(count), 'halParentLeft', 'valParentTop', 0, 1, width+7, height, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (disabled) then
      [*] = ;            begin
      [*] = ;               SetGUIElementEnabled(elmBtnHandle,False);
      [*] = ;               SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 1, 0.5, 0.5, 0.5, 1);
      [*] = ;               SetGUIElementVisibleProperties(elmBtnHandle, 'DownProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 1, 0.5, 0.5, 0.5, 1);
      [*] = ;               SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 1, 0.5, 0.5, 0.5, 1);
      [*] = ;               var elmHintBtnHandle : Integer = _gui_CreateButton('item_slot_hint', elmBtnHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), '', '', tag);
      [*] = ;               _gui_ft_AttachHint_I4_S2(elmHintBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBuy,itemDurability,gIntRegister_GUIActiveHeroUID1,cShopEventHandler,'3');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (gIntRegister_MapPickedItemID<>0) and (gIntRegister_MapSelectedItemSlot=ind) and SameText(gStringRegister_ItemPlace, 'Shop') then
      [*] = ;            SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         ind := ind-1;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (highlight) then
      [*] = ;      begin
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('', elmGuiLayer, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, {'misc.blank.black.alpha.0'}'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('castle_shop_slot_highlighted', elmSlotHandle, '', 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, cShopEventHandler, '', tag);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.3);
      [*] = ;         SetGUIElementUserBlend(elmBtnHandle, 0.3);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('', elmGuiLayer, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         elmImageHandle := _gui_CreateImage('castle_shop_empty_slot', elmSlotHandle, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', -2, -2, 56, 56, 0);
      [*] = ;         SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;         SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;var shopItemsHeight : Integer = (ind div 8) * (cShopHeight + cShopYOffset) + cShopHeight;
      [*] = ;SetGUIElementHeight(elmGuiLayer, shopItemsHeight);
      [*] = ;
      [*] = ;// restore scroller position
      [*] = ;SetGUIScrollBarPosition(elmVScroll, lastScrollPos);
      [*] = ;
      [*] = ;// treasury items
      [*] = ;xOff := 106;
      [*] = ;yOff := 502;
      [*] = ;
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;var pPlTreasury : Integer = ParserSelectByHandleByKey(pPlParser, 'Treasury');
      [*] = ;
      [*] = ;var isDamagedItems : Boolean = False;
      [*] = ;for i := 0 to gc_TreasurySize-1 do
      [*] = ;begin
      [*] = ;   var pTreasurySlot : Integer = ParserSelectByHandleByIndex(pPlTreasury, i);
      [*] = ;   var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasurySlot, 'ItemID');
      [*] = ;   var itemDurability : Integer = ParserGetIntValueByKeyByHandle(pTreasurySlot, 'Durability');
      [*] = ;   var itemReservedPlInd : Integer = _pars_ParserGetIntValueExt(pTreasurySlot, 'ReservedPlayer');
      [*] = ;
      [*] = ;   posX := xOff + (i mod 8) * (cShopWidth + cShopOffset);
      [*] = ;   posY := yOff + (i div 8) * (cShopHeight + cShopYOffset);
      [*] = ;
      [*] = ;   var highlight : Boolean = False;
      [*] = ;   var disabled : Boolean = (itemReservedPlInd >= 0);
      [*] = ;   if (gIntRegister_MapPickedItemID<>0) then
      [*] = ;   begin
      [*] = ;      if ((not SameText(gStringRegister_ItemPlace, 'Shop')) or (itemID=0)) and (itemReservedPlInd < 0) then
      [*] = ;      highlight := True
      [*] = ;      else
      [*] = ;      disabled := True;
      [*] = ;   end;
      [*] = ;
      [*] = ;   tag := gc_gui_treasuryitemslots_btnBaseTag + i;
      [*] = ;   if (itemID<>0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := itemID;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetItemParserByID', 0);
      [*] = ;      var pItem : Integer = IntRegister1;
      [*] = ;      var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemSlot');
      [*] = ;      var itemType : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;      var itemMaxDurability : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;      var visible : Boolean = False;
      [*] = ;      var canUse : Boolean = True;
      [*] = ;      if (goHandle<>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := ItemID;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'CanUseItem');
      [*] = ;         canUse := BoolRegister0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gBoolRegister_RepairItemMode) and (not disabled) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         IntRegister1 := itemDurability;
      [*] = ;         IntRegister2 := GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;         IntRegister3 := gIntRegister_MapCurrentShop;
      [*] = ;         PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO, 'GetItemRepPrice');
      [*] = ;         var repGoldPrice : Integer = IntRegister4;
      [*] = ;         var repGemPrice : Integer = IntRegister5;
      [*] = ;
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         if ((repGoldPrice=0) and (repGemPrice=0)) or ((repGoldPrice>0) and (plGold<repGoldPrice)) or ((repGemPrice>0) and (plGem<repGemPrice)) then
      [*] = ;            disabled := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      case gIntRegister_GUIShopSortMode of
      [*] = ;         1 : if (canUse) then visible := True;
      [*] = ;         2 : if (itemSlot=1) or (ItemSlot=2) or (itemSlot=14) or (itemSlot=12) or (itemSlot=13) then visible := True;
      [*] = ;         3 : if (itemSlot=3) or (itemSlot=4) or ((itemSlot=10) and (itemMaxDurability>1)) or (itemSlot=8) or (itemSlot=7) then visible := True;
      [*] = ;         4 : if (itemSlot=5) or (itemSlot=6) or (itemSlot=9) or ((itemSlot=10) and (itemMaxDurability<=1)) or (itemSlot=11) then visible := True;
      [*] = ;         5 : if (itemType>=10) and (itemType<=13) then visible := True;
      [*] = ;         6 : if (itemType=0) and (itemSlot=0) then visible := True;
      [*] = ;         else
      [*] = ;         visible := True;
      [*] = ;      end;
      [*] = ;      if (goHandle<>0) and (canUse) then SetGUIElementEnabled(elmBtnHandleSortMode1, True);
      [*] = ;      if (itemSlot=1) or (ItemSlot=2) or (itemSlot=14) or (itemSlot=12) or (itemSlot=13) then SetGUIElementEnabled(elmBtnHandleSortMode2, True);
      [*] = ;      if (itemSlot=3) or (itemSlot=4) or ((itemSlot=10) and (itemDurability>1)) or (itemSlot=8) or (itemSlot=7) then SetGUIElementEnabled(elmBtnHandleSortMode3, True);
      [*] = ;      if (itemSlot=5) or (itemSlot=6) or (itemSlot=9) or ((itemSlot=10) and (itemDurability<=1)) or (itemSlot=11) then SetGUIElementEnabled(elmBtnHandleSortMode4, True);
      [*] = ;      if (itemType>=10) and (itemType<=13) then SetGUIElementEnabled(elmBtnHandleSortMode5, True);
      [*] = ;      if (itemType=0) and (itemSlot=0) then SetGUIElementEnabled(elmBtnHandleSortMode6, True);
      [*] = ;
      [*] = ;      elmSlotHandle := _gui_CreateImageSimple('open', elmShopItems, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;
      [*] = ;      var iconName : String;
      [*] = ;      _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;      elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, cShopWidth, cShopHeight, tag);
      [*] = ;      if (not visible) then
      [*] = ;      begin
      [*] = ;         highlight := False;
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.15);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (highlight) then
      [*] = ;      begin
      [*] = ;         elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, {'misc.blank.black.alpha.0'}'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, cTreasuryEventHandler, '', tag);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;         SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (goHandle<>0) then
      [*] = ;      begin
      [*] = ;         if (not canUse) then
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, 'heropanel.icon.52x52.red', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;            if (not visible) then
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 0.15)
      [*] = ;            else
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 0.5);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      elmBtnHandle := _gui_CreateButton('item_slot', elmSlotHandle, 'item_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;
      [*] = ;      if (itemReservedPlInd >= 0) then
      [*] = ;      begin
      [*] = ;         hint := GetLocaleTableListItemByID('gui', '386');
      [*] = ;         
      [*] = ;         PlayerExecuteStateByHandle(GetPlayerHandleByIndex(itemReservedPlInd), 'GetName');
      [*] = ;         hint := hint + gc_gui_BreakLine + StringRegister0;
      [*] = ;         
      [*] = ;         SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceSell,itemDurability,gIntRegister_GUIActiveHeroUID1,cTreasuryEventHandler,'3');
      [*] = ;
      [*] = ;      if (not visible) then
      [*] = ;      begin
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'misc.blank.black.alpha.0', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;
      [*] = ;      if (disabled) then
      [*] = ;      begin
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 1.0);
      [*] = ;         SetGUIElementUserBlend(elmBtnHandle, 0.7);
      [*] = ;         if (gBoolRegister_RepairItemMode) then
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 26, 0.5, 0.5, 0.5, 1)
      [*] = ;         else
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (gBoolRegister_RepairItemMode) then
      [*] = ;      begin
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'UpProperty', 'heropanel.icon.52x52.slot.cover.normal', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.cover.hover', 0, 0, 0, 0, 25, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DownProperty', 'heropanel.icon.52x52.slot.cover.pressed', 0, 0, 0, 0, 25, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 26, 0.5, 0.5, 0.5, 1);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'heropanel.icon.52x52.slot.cover.checkon', 0, 0, 0, 0, 25, 0.5, 0.5, 0.5, 1);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gIntRegister_MapSelectedItemSlot=i) and SameText(gStringRegister_ItemPlace, 'Treasury') then
      [*] = ;      SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;      if (itemMaxDurability>1) and (itemDurability=0) then
      [*] = ;      elmImageHandle := _gui_CreateImage('' , elmBtnHandle, 'item.broken.mark', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, tag);
      [*] = ;
      [*] = ;      hint := 'gui|639';
      [*] = ;      elmBtnHandle := _gui_CreateButton('dismiss', elmBtnHandle, 'dismiss', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRight', 'valParentTop', -16, 0, 18, 18, '', hint, gc_gui_itempanel_btnDismiss);
      [*] = ;      SetGUIElementStringTag(elmBtnHandle, 'dismiss');
      [*] = ;      SetGUIElementVisible(elmBtnHandle, False);
      [*] = ;
      [*] = ;      if (visible) and (not isDamagedItems) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         IntRegister1 := itemDurability;
      [*] = ;         IntRegister2 := GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;         IntRegister3 := gIntRegister_MapCurrentShop;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetItemRepPrice');
      [*] = ;         var goldPrice : Integer = IntRegister4;
      [*] = ;         var gemPrice : Integer = IntRegister5;
      [*] = ;
      [*] = ;         if (goldPrice>0) or (gemPrice>0) then
      [*] = ;         isDamagedItems := True;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var bDiplomacyItem : Boolean = false;
      [*] = ;      if ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeHotseat)) and (i div 8 >= 4) then
      [*] = ;         bDiplomacyItem := true;
      [*] = ;      
      [*] = ;      var material, hint : String = '';
      [*] = ;      if bDiplomacyItem then
      [*] = ;      begin
      [*] = ;         material := 'icon.diplomacy.3';
      [*] = ;         hint := GetLocaleTableListItemByID('gui', 'diplomacy_items');
      [*] = ;      end
      [*] = ;      else
      [*] = ;         material := 'heropanel.icon.52x52.slot.empty';
      [*] = ;      
      [*] = ;      if (highlight) then
      [*] = ;      begin
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('', elmShopItems, material, 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, {'misc.blank.black.alpha.0'}'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('castle_treasury_slot_highlighted', elmSlotHandle, '', 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, cTreasuryEventHandler, hint, tag);
      [*] = ;         SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;         if bDiplomacyItem then
      [*] = ;            SetGUIElementUserBlend(elmSlotHandle, 0.2)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 0.3);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.3);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('', elmShopItems, material, 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         elmImageHandle := _gui_CreateImage('castle_treasury_empty_slot', elmShopItems, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', posX, posY, 56, 56, 0);
      [*] = ;         SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;         SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;         if bDiplomacyItem then
      [*] = ;         begin
      [*] = ;            SetGUIElementUserBlend(elmSlotHandle, 0.2);
      [*] = ;            SetGUIElementHint(elmImageHandle, hint);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//Подписи на бумаге
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;begin
      [*] = ;   posX := 3;
      [*] = ;   posY := -786;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   posX := -27;
      [*] = ;   posY := -786;
      [*] = ;end;
      [*] = ;yOff := 348;
      [*] = ;elmText := _gui_CreateText('castle_shop_treasury_strip', elmShopPanelBg, GetLocaleTableListItemByID('gui', '591'), 'halParentMiddle', 'valParentBottomHeight', posX, posY, 240, 28, 'halMiddle', 'valMiddle', fontHandleH2, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;SetGUIAllowEvents(elmText, True, False, False);
      [*] = ;elmText := _gui_CreateText('castle_shop_store_strip', elmShopPanelBg, GetLocaleTableListItemByID('gui', '561'), 'halParentMiddle', 'valParentBottomHeight', posX, posY+yOff, 240, 28, 'halMiddle', 'valMiddle', fontHandleH2, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;SetGUIAllowEvents(elmText, True, False, False);
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;var repairAllGoldPrice : Integer = 0;
      [*] = ;var repairAllGemPrice : Integer = 0;
      [*] = ;if (goHandle<>0) then
      [*] = ;begin
      [*] = ;   IntRegister0 := gIntRegister_MapCurrentShop;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetInvRepairPrice');
      [*] = ;   repairAllGoldPrice := IntRegister1;
      [*] = ;   repairAllGemPrice := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;//Кнопка починки всего
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;begin
      [*] = ;   posX := 88+98;
      [*] = ;   posY := -92+8;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   posX := 410+98;
      [*] = ;   posY := -92+8;
      [*] = ;end;
      [*] = ;
      [*] = ;var bRepairDisabled : Boolean = False;
      [*] = ;hint := GetLocaleTableListItemByID('gui', '143');
      [*] = ;if (goHandle<>0) then
      [*] = ;begin
      [*] = ;   if ((repairAllGoldPrice>0) or (repairAllGemPrice>0)) then
      [*] = ;   begin
      [*] = ;      if (repairAllGoldPrice>plGold) or (repairAllGemPrice>plGem) then
      [*] = ;      begin
      [*] = ;         hint := hint + ' ('+GetLocaleTableListItemByID('gui', '608')+')';
      [*] = ;         bRepairDisabled := True;
      [*] = ;      end;
      [*] = ;      hint := hint + gc_gui_BreakLine + gc_gui_BreakLine + GetLocaleTableListItemByID('gui', '14');
      [*] = ;      if (repairAllGoldPrice>0) then
      [*] = ;      hint := hint + gc_gui_BreakLine + GetLocaleTableListItemByID('gui', '189') + ': ' + IntToStr(repairAllGoldPrice);
      [*] = ;      if (repairAllGemPrice>0) then
      [*] = ;      hint := hint + gc_gui_BreakLine + GetLocaleTableListItemByID('gui', '190') + ': ' + IntToStr(repairAllGemPrice);
      [*] = ;   end;
      [*] = ;   if ((repairAllGoldPrice=0) and (repairAllGemPrice=0)) then
      [*] = ;   begin
      [*] = ;      hint := hint+' ('+GetLocaleTableListItemByID('gui', '650')+')';
      [*] = ;      bRepairDisabled := True;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   hint := hint + ' ('+GetLocaleTableListItemByID('gui', '651')+')';
      [*] = ;   bRepairDisabled := True;
      [*] = ;end;
      [*] = ;
      [*] = ;//_gui_CreateImage('', elmShopPanelBg, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentBottomHeight', posX-54, posY+10, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('castle_shop_repair_all', elmShopPanelBg, '', 'castle.shop.repairall.btn', 'halParentLeft', 'valParentBottomHeight', posX, posY, 0, 0, '', hint, gc_gui_shoppanel_btnRepairAll);
      [*] = ;
      [*] = ;if (bRepairDisabled) then
      [*] = ;SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;else
      [*] = ;begin
      [*] = ;   if gBoolRegister_BtnRepairAllBlink then
      [*] = ;   _gui_CreateBlinkElement('btnRepairAll', elmBtnHandle, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;//Кнопка починки
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;begin
      [*] = ;   posX := 129+9;
      [*] = ;   posY := -83+2;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   posX := 451+9;
      [*] = ;   posY := -83+2;
      [*] = ;end;
      [*] = ;if (not gBoolRegister_RepairItemMode) then
      [*] = ;   hint := 'gui|144'
      [*] = ;else
      [*] = ;   hint := 'gui|145';
      [*] = ;
      [*] = ;elmBtnHandle := _gui_CreateButton('castle_shop_repair', elmShopPanelBg, '', 'castle.shop.repair.btn', 'halParentLeft', 'valParentBottomHeight', posX, posY, 0, 0, '', hint, gc_gui_shoppanel_btnRepair);
      [*] = ;if (not isDamagedItems) and (repairAllGoldPrice=0) and (repairAllGemPrice=0) then
      [*] = ;begin
      [*] = ;   if (gBoolRegister_RepairItemMode) then
      [*] = ;   begin
      [*] = ;      gBoolRegister_RepairItemMode := False;
      [*] = ;      IntRegister0 := goHandle;
      [*] = ;      ExecuteState('map.CreateShopWindow');
      [*] = ;   end;
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;   hint := GetLocaleTableListItemByID('gui', '144')+' ('+GetLocaleTableListItemByID('gui', '650')+')';
      [*] = ;   SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;end
      [*] = ;else
      [*] = ;if (gBoolRegister_RepairItemMode) then
      [*] = ;   SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;if GetGUIElementEnabled(elmBtnHandle) then
      [*] = ;begin
      [*] = ;   if gBoolRegister_BtnRepairBlink then
      [*] = ;      _gui_CreateBlinkElement('btnRepair', elmBtnHandle, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;end;
   struct.end
section.end

