section.begin
   Name = ShowCustomHeroInventory
   Code : struct.begin
      [*] = ;function GetUnitProperty(heroHandle, indProperty : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := indProperty;
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle, 'GetProperty');
      [*] = ;   Result := IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;function _inet_CreateParamInfo(elmParent : Integer; battle : TInetBattle; posX, posY, sizeX : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var leader, health, magic , initiative, siege, mobility, life, attack, counterAttack, defence, rangedDefence, resist, speed, rangedAttack, shootingRange, ammo, stamina, moral, level : Integer = 0;
      [*] = ;   var bHeroExist : Boolean = (battle.hero[battle.curhero].class1>0);
      [*] = ;   if (bHeroExist) then
      [*] = ;   begin
      [*] = ;      _inet_CreateHeroUnit(battle);
      [*] = ;      var goHandle : Integer = _inet_GetHeroUnit;
      [*] = ;      leader := GetUnitProperty(goHandle, gc_map_hero_iLeaderProperty);
      [*] = ;      health := GetUnitProperty(goHandle, gc_map_hero_iHealthProperty);
      [*] = ;      magic  := GetUnitProperty(goHandle, gc_map_hero_iMagicProperty);
      [*] = ;      initiative := GetUnitProperty(goHandle, gc_map_hero_iInitiative);
      [*] = ;      siege := GetUnitProperty(goHandle, gc_map_hero_iSiege);
      [*] = ;      mobility := GetUnitProperty(goHandle, gc_map_hero_iMobility);
      [*] = ;      life := GetUnitProperty(goHandle, gc_map_hero_iLife);
      [*] = ;      attack := GetUnitProperty(goHandle, gc_map_hero_iAttack);
      [*] = ;      counterAttack := GetUnitProperty(goHandle, gc_map_hero_iCounterAttack);
      [*] = ;      defence := GetUnitProperty(goHandle, gc_map_hero_iDefence);
      [*] = ;      rangedDefence := GetUnitProperty(goHandle, gc_map_hero_iRangedDefence);
      [*] = ;      resist := GetUnitProperty(goHandle, gc_map_hero_iResist);
      [*] = ;      speed := GetUnitProperty(goHandle, gc_map_hero_iSpeed);
      [*] = ;      rangedAttack := GetUnitProperty(goHandle, gc_map_hero_iRangedAttack);
      [*] = ;      shootingRange := GetUnitProperty(goHandle, gc_map_hero_iShootingRange);
      [*] = ;      ammo := GetUnitProperty(goHandle, gc_map_hero_iAmmo);
      [*] = ;      stamina := GetUnitProperty(goHandle, gc_map_hero_iStamina);
      [*] = ;      moral := GetUnitProperty(goHandle, gc_map_hero_iMoral);
      [*] = ;      level := battle.hero[battle.curhero].level;
      [*] = ;      if (speed<1) then speed := 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   procedure ShowUnitPropertyExt(matName : String; langKey, elmParent, value : Integer; delimeter : String; prIndex2, xShift, yShift, xSize, ySize, ixPos, yxPos : Integer);
      [*] = ;   begin
      [*] = ;      var str : String = '';
      [*] = ;      if (bHeroExist) then
      [*] = ;         str := IntToStr(value);
      [*] = ;      var xSizeCut : Integer = 0;
      [*] = ;
      [*] = ;      const cFontParamsColorR = gc_gui_fontcolor_HeaderR;
      [*] = ;      const cFontParamsColorG = gc_gui_fontcolor_HeaderG;
      [*] = ;      const cFontParamsColorB = gc_gui_fontcolor_HeaderB;
      [*] = ;      const cFontParamsColorA = 1;
      [*] = ;      var fontHandle : String;
      [*] = ;      _gui_GetFont(gc_gui_fontsection_tactics,'PropertyValue',gc_gui_fontsize_default,'',fontHandle); // HeaderS
      [*] = ;      var elmTextHandle : Integer = _gui_CreateText('unitproperty', elmParent, str, 'halParentLeft', 'valParentTop', xShift + ixPos * (xSize)+1, yShift + yxPos * (ySize)+1, xSize, ySize, 'halLeft', 'valMiddle', fontHandle, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;
      [*] = ;      var elmImageHandle : Integer = _gui_CreateImage('unitproperty_image', elmTextHandle, matName, 'halParentLeft', 'valParentTop', -46, 0, 0, 0, 0);
      [*] = ;      if (str='') then
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.125)
      [*] = ;      else
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.9);
      [*] = ;
      [*] = ;      posX := xShift + ixPos * (xSize)-39;
      [*] = ;      posY := yShift + yxPos * (ySize);
      [*] = ;
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('', elmParent, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX, posY-2, xSize-8-xSizeCut, ySize-1, '', '', 0);
      [*] = ;      _gui_ft_AttachHint_I5(elmBtnHandle,'VVK.HintASERCallback',cFT_ASER_Ability,langKey,langKey,value,0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var xShift, yShift, xSize, ySize : Integer;
      [*] = ;   xShift := posX;
      [*] = ;   yShift := posY;
      [*] = ;   xSize := sizeX;
      [*] = ;   ySize := 34;
      [*] = ;
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.life.47x36', 1, elmParent, life, '', -1, xShift, yShift, xSize, ySize, 0, 0);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.stamina.47x36', 11, elmParent, stamina, '', -1, xShift, yShift, xSize, ySize, 1, 0);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.morale.47x36', 12, elmParent, moral, '', -1, xShift, yShift, xSize, ySize, 2, 0);
      [*] = ;
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.speed.47x36', 7, elmParent, speed, '', -1, xShift, yShift, xSize, ySize, 0, 1);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.attack.47x36', 2, elmParent, attack, '', -1, xShift, yShift, xSize, ySize, 1, 1);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.counterattack.47x36', 3, elmParent, counterattack, '', -1, xShift, yShift, xSize, ySize, 2, 1);
      [*] = ;
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.defence.47x36', 4, elmParent, defence, '', -1, xShift, yShift, xSize, ySize, 0, 2);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.rangeddefence.47x36', 5, elmParent, rangeddefence, '', -1, xShift, yShift, xSize, ySize, 1, 2);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.resist.47x36', 6, elmParent, resist, '', -1, xShift, yShift, xSize, ySize, 2, 2);
      [*] = ;
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.rangedattack.47x36', 8, elmParent, rangedattack, '', -1, xShift, yShift, xSize, ySize, 0, 3);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.rangeddistance.47x36', 9, elmParent, shootingrange, '', -1, xShift, yShift, xSize, ySize, 1, 3);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.ammo.47x36', 10, elmParent, ammo, '', -1, xShift, yShift, xSize, ySize, 2, 3);
      [*] = ;end;
      [*] = ;
      [*] = ;var parentHandle : Integer = IntRegister0;
      [*] = ;const cEventState = 'EventCustomHeroInventory';
      [*] = ;
      [*] = ;var itemSlotPosX : array [0..16] of Integer;
      [*] = ;var itemSlotPosY : array [0..16] of Integer;
      [*] = ;
      [*] = ;var itemSize : Integer = 52;
      [*] = ;var itemOffset : Integer = itemSize+4;
      [*] = ;var miniOffset : Integer = 19;
      [*] = ;
      [*] = ;itemSlotPosX[0] := 1*itemOffset;//1,0
      [*] = ;itemSlotPosX[1] := 2*itemOffset;//2,0
      [*] = ;itemSlotPosX[2] := 4*itemOffset;//4,0
      [*] = ;itemSlotPosX[3] := 0;//0,1
      [*] = ;itemSlotPosX[4] := 0;//0,2
      [*] = ;itemSlotPosX[5] := 0;//0,3
      [*] = ;itemSlotPosX[6] := 3*itemOffset;//3,0
      [*] = ;itemSlotPosX[7] := 0;//0,4
      [*] = ;itemSlotPosX[8] := 4*itemOffset;//4,1
      [*] = ;itemSlotPosX[9] := 4*itemOffset;//4,2
      [*] = ;itemSlotPosX[10] := 4*itemOffset;//4,3
      [*] = ;itemSlotPosX[11] := 0;//0,0
      [*] = ;itemSlotPosX[12] := 4*itemOffset;//4,4
      [*] = ;itemSlotPosX[13] := 0;//0,5
      [*] = ;itemSlotPosX[14] := 1*itemOffset;//1,5
      [*] = ;itemSlotPosX[15] := 3*itemOffset;//3,5
      [*] = ;itemSlotPosX[16] := 4*itemOffset;//4,5
      [*] = ;
      [*] = ;itemSlotPosY[0] := 0;
      [*] = ;itemSlotPosY[1] := 0;
      [*] = ;itemSlotPosY[2] := 0;
      [*] = ;itemSlotPosY[3] := 1*itemOffset+miniOffset;
      [*] = ;itemSlotPosY[4] := 2*itemOffset+miniOffset;
      [*] = ;itemSlotPosY[5] := 3*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[6] := 0;
      [*] = ;itemSlotPosY[7] := 4*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[8] := 1*itemOffset+miniOffset;
      [*] = ;itemSlotPosY[9] := 2*itemOffset+miniOffset;
      [*] = ;itemSlotPosY[10] := 3*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[11] := 0;
      [*] = ;itemSlotPosY[12] := 4*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[13] := 5*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[14] := 5*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[15] := 5*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[16] := 5*itemOffset+miniOffset*2;
      [*] = ;
      [*] = ;procedure ShowCustomHeroInventory(battle : TInetBattle;hero_items_mode : Integer);
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', parentHandle, 'heropanel.doll', 'halParentLeft', 'valParentBottomHeight', -77, -12, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', parentHandle, 'gamepanel03.bag', 'halParentLeft', 'valParentBottomHeight', 250, -220, 0, 0, 0);
      [*] = ;
      [*] = ;   var fontHandle : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;   const cHeroBonusMarginB = 0;
      [*] = ;   var heroBonusStripPosY : Integer = -58;//GetGUIElementPositionY(elmHeroSkills)+GetGUIElementPositionY(elmHeroSkillsLevelUp)+GetGUIElementHeight(elmHeroSkillsLevelUp)+cHeroBonusMarginB-yOff;
      [*] = ;   elmHandle := _gui_CreateImage('', parentHandle, 'element.strip.240', 'halParentMiddle', 'valParentTop', 122, 283, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmHandle, 'menu|180', 'halParentLeft', 'valParentTop', -1, -4, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   _inet_CreateParamInfo(parentHandle, battle, 293, 323, 79);
      [*] = ;
      [*] = ;   var goHandle : Integer = _inet_GetHeroUnit;
      [*] = ;   var initiative : Integer = GetUnitProperty(goHandle, gc_map_hero_iInitiative);
      [*] = ;   var posX : Integer = 338;
      [*] = ;   var posY : Integer = 477;
      [*] = ;   var text : String = IntToStr(initiative);
      [*] = ;
      [*] = ;   elmHandle := _gui_CreateImage('unitproperty_image', parentHandle, 'shell.heroparam.initiative', 'halParentLeft', 'valParentTop', posX-10, posY-6, 0, 0, 0);
      [*] = ;   if (initiative=0) then
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.325)
      [*] = ;   else
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.9);
      [*] = ;   if (battle.hero[battle.curhero].class1>0) then
      [*] = ;   begin
      [*] = ;      elmTextHandle := _gui_CreateText('', parentHandle, text, 'halParentLeft', 'valParentTop', posX+36, posY-2, 0, GetGUIElementHeight(elmHandle), 'halLeft', 'valBottomHeight', fontHandle, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;      if (initiative=0) then
      [*] = ;      SetGUIElementUserBlend(elmTextHandle, 0.4);
      [*] = ;   end;
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('heroparam_initiative', elmHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, -2, 70, GetGUIElementHeight(elmHandle), '', '', 0);
      [*] = ;   var abilityIndex : Integer = 101; //gc_map_hero_iInitiative
      [*] = ;   _gui_ft_AttachHint_I5(elmBtnHandle,'VVK.HintASERCallback',cFT_ASER_Ability,abilityIndex,abilityIndex,initiative,0);
      [*] = ;
      [*] = ;   var elmSlotHandle : Integer;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_HeroInventoryCount-1 do
      [*] = ;   begin
      [*] = ;      var posX, posY : Integer = 0;
      [*] = ;      if (i<gc_HeroDollSlotsCount) then
      [*] = ;      begin
      [*] = ;         posX := -72+itemSlotPosX[i];
      [*] = ;         posY := -337+itemSlotPosY[i]-1;
      [*] = ;         case i of
      [*] = ;            3, 8, 4, 9 : posY := posY+1;
      [*] = ;            5, 7, 10, 12 : posY := posY+2;
      [*] = ;         end;
      [*] = ;         if (i >= 13) and (i <= 16) then
      [*] = ;         posY := posY + 2;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         posX := 256+((i-gc_HeroDollSlotsCount) mod 4) * (56);
      [*] = ;         posY := -338+((i-gc_HeroDollSlotsCount) div 4) * (56);
      [*] = ;      end;
      [*] = ;
      [*] = ;      const cBtnDismiss = 200;
      [*] = ;      const cBtnBaseTagSlot = 1000;
      [*] = ;      var tag : Integer = cBtnBaseTagSlot+i;
      [*] = ;      var itemID : Integer = battle.hero[battle.curhero].arritems[i];
      [*] = ;
      [*] = ;      var highlight, disabled : Boolean = False;
      [*] = ;      var slotAllowItem : Boolean = True;
      [*] = ;
      [*] = ;      var pItem, itemSlot, itemType, itemMaxDurability : Integer = 0;
      [*] = ;      if (itemID<>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         pItem := IntRegister1;
      [*] = ;         itemSlot := ParserGetIntValueByKeyByHandle(pItem, 'ItemSlot');
      [*] = ;         itemType := ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;         itemMaxDurability := ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;      end;
      [*] = ;      var dollSlotIndex : Integer = _inet_GetDollItemSlot(i);
      [*] = ;
      [*] = ;      var pickedItemID : Integer = 0;
      [*] = ;      if (gIntRegister_InetShopPickedItemID<>0) then
      [*] = ;      pickedItemID := gIntRegister_InetShopPickedItemID
      [*] = ;      else
      [*] = ;      if (gIntRegister_InetPickedItemSlot>-1) then
      [*] = ;      pickedItemID := battle.hero[battle.curhero].arritems[gIntRegister_InetPickedItemSlot];
      [*] = ;
      [*] = ;      if (pickedItemID<>0) then
      [*] = ;      begin
      [*] = ;         if (itemID<>0) and (gIntRegister_InetShopPickedItemID<>0) then
      [*] = ;         begin
      [*] = ;            disabled := True
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := pickedItemID;
      [*] = ;            MapExecuteState('GetItemParserByID');
      [*] = ;            var pPickedItem : Integer = IntRegister1;
      [*] = ;            var pickedItemSlot : Integer = ParserGetIntValueByKeyByHandle(pPickedItem, 'ItemSlot');
      [*] = ;            var pickedItemType : Integer = ParserGetIntValueByKeyByHandle(pPickedItem, 'ItemType');
      [*] = ;            var pickedItemDurability : Integer = ParserGetIntValueByKeyByHandle(pPickedItem, 'Durability');
      [*] = ;
      [*] = ;            var canUse : Boolean = _inet_GetCanUseItem(battle, pickedItemID);
      [*] = ;
      [*] = ;            var slotAllowItem2 : Boolean = True;
      [*] = ;            var slotItemSlot : Integer = _inet_GetDollItemSlot(gIntRegister_InetPickedItemSlot);
      [*] = ;
      [*] = ;            if (itemID<>0) then
      [*] = ;            begin
      [*] = ;               var canUse2 : Boolean = _inet_GetCanUseItem(battle, itemID);
      [*] = ;               //Brain explode here
      [*] = ;               slotAllowItem2 := ((canUse2) and (ItemSlot = pickedItemSlot) or ((ItemSlot = 1) and (pickedItemSlot = 14))) or
      [*] = ;               ((dollSlotIndex=0) and (slotItemSlot=0)){ or
      [*] = ;               ((dollSlotIndex=0) and SameText(gStringRegister_ItemPlace, 'Treasury'))};
      [*] = ;
      [*] = ;               {if canUse and slotAllowItem2 and (ItemSlot = pickedItemSlot) or ((ItemSlot = 1) and (pickedItemSlot = 14)) then
      [*] = ;               slotAllowItem2 := False;}
      [*] = ;               if canUse and slotAllowItem2 and (ItemSlot = pickedItemSlot) or ((ItemSlot = 1) and (pickedItemSlot = 14)) then
      [*] = ;               slotAllowItem2 := True;
      [*] = ;            end;
      [*] = ;
      [*] = ;            //Brain explode here too
      [*] = ;            slotAllowItem := ((dollSlotIndex = 0) and (itemID=0)) or
      [*] = ;            ((itemID<>0) and (slotAllowItem2) and ((dollSlotIndex=0) or ((canUse) and ((dollSlotIndex = pickedItemSlot) or ((dollSlotIndex = 1) and (pickedItemSlot = 14)))))) or
      [*] = ;            ((canUse) and ((dollSlotIndex = pickedItemSlot) or ((dollSlotIndex = 1) and (pickedItemSlot = 14))));
      [*] = ;
      [*] = ;            if (slotAllowItem) then
      [*] = ;            highlight := True;
      [*] = ;
      [*] = ;            var noFreeSpace : Boolean = False;
      [*] = ;            //Check free space for two-handed weapon
      [*] = ;            var slIndex1 : Integer = _inet_GetSlotIndexByItemSlot(battle, 2);
      [*] = ;            var shieldItemID : Integer = battle.hero[battle.curhero].arritems[slIndex1];
      [*] = ;
      [*] = ;            var freeSlots : Integer = _inet_GetFreeInvSlotsCount(battle);
      [*] = ;            if (shieldItemID > 0) and (freeSlots < 1) then
      [*] = ;            noFreeSpace := true;
      [*] = ;
      [*] = ;            const cMeleeWeaponSlot = 3;
      [*] = ;            if (pickedItemSlot = 14) and (noFreeSpace) and (i=cMeleeWeaponSlot) then
      [*] = ;            disabled := True;
      [*] = ;
      [*] = ;            if (not slotAllowItem) and ((i<>gIntRegister_MapSelectedItemSlot) or (gIntRegister_InetShopPickedItemID<>0)) then
      [*] = ;            disabled := True;
      [*] = ;
      [*] = ;            if (disabled) then
      [*] = ;            highlight := false;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (itemID<>0) then
      [*] = ;      begin
      [*] = ;         //var hint : String = '%itemhint%|'+IntToStr(itemID)+'|'+IntToStr(4)+'|'+IntToStr(itemMaxDurability);
      [*] = ;         //var elmHandle : Integer = _gui_CreateImage('' , parentHandle, 'icon.frame.item', 'halParentLeft', 'valParentBottomHeight', posX-5, posY+5, 62, 62, tag);
      [*] = ;         elmSlotHandle := _gui_CreateImage('open', parentHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentBottomHeight', posX, posY, 0, 0, 0);
      [*] = ;         GUIInvalidateParentPositions(elmSlotHandle);
      [*] = ;         var iconName : String;
      [*] = ;         _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;         elmHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;
      [*] = ;         if (highlight) then
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmSlotHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;            var elmBtnHandle : Integer = _gui_CreateButton('', elmSlotHandle, '', 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, cEventState, '', tag);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.4);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;         end;
      [*] = ;
      [*] = ;         var canUse : Boolean = _inet_GetCanUseItem(battle, ItemID);
      [*] = ;         if (not canUse) then
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmSlotHandle, 'heropanel.icon.52x52.red', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.6);
      [*] = ;         end;
      [*] = ;
      [*] = ;         var elmBtnHandle : Integer = _gui_CreateButton('item_slot', elmSlotHandle, 'item_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;         _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPricePoints,itemMaxDurability,hero_items_mode,cEventState,'1');
      [*] = ;         if (disabled) then
      [*] = ;         begin
      [*] = ;            SetGUIElementUserBlend(elmHandle, 1.0);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.7);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (gIntRegister_MapSelectedItemSlot=i) and SameText(gStringRegister_ItemPlace, 'Doll') then
      [*] = ;         SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;         elmBtnHandle := _gui_CreateButton('dismiss', elmBtnHandle, 'dismiss', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRight', 'valParentTop', -16, 0, 18, 18, cEventState, 'gui|643', cBtnDismiss);
      [*] = ;         SetGUIElementStringTag(elmBtnHandle, 'dismiss');
      [*] = ;         SetGUIElementVisible(elmBtnHandle, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmSlotHandle := _gui_CreateImage('hero_inventory_bag_slot_open', parentHandle, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentBottomHeight', posX, posY, 52, 52, 0);
      [*] = ;
      [*] = ;         if (highlight) then
      [*] = ;         begin
      [*] = ;            var elmHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;            var elmBtnHandle : Integer = _gui_CreateButton('hero_inventory_slot_highlighted', elmSlotHandle, '', 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, cEventState, '', tag);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.4);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;            if (i<gc_HeroDollSlotsCount) then
      [*] = ;            begin
      [*] = ;               var hint : String = 'item_slot|'+IntToStr(dollSlotIndex);
      [*] = ;               SetGUIElementHint(elmSlotHandle, hint);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var hint : String = 'item_slot|'+IntToStr(dollSlotIndex);
      [*] = ;               SetGUIElementHint(elmSlotHandle, hint);
      [*] = ;               SetGUIElementUserBlend(elmSlotHandle, 0.85);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;   ShowCustomHeroInventory(gEditorCustomPlayerTemporary,cFT_ItemHeroMapEditor)
      [*] = ;else
      [*] = ;if (gBoolRegister_IsHotSeat) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_HotSeatActivePlayer=0) then
      [*] = ;      ShowCustomHeroInventory(gHotSeatPlayer1,cFT_ItemHeroHotSeat1)
      [*] = ;   else
      [*] = ;      ShowCustomHeroInventory(gHotSeatPlayer2,cFT_ItemHeroHotSeat2)
      [*] = ;end
      [*] = ;else
      [*] = ;   ShowCustomHeroInventory(gInetBattle,cFT_ItemHeroMultiplayer);
   struct.end
section.end

