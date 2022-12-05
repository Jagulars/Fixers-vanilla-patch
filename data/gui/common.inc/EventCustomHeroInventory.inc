section.begin
   Name = EventCustomHeroInventory
   Code : struct.begin
      [*] = ;procedure EventCustomHeroInventory(var battle : TInetBattle);
      [*] = ;begin
      [*] = ;   var sPress  : String = GetValueByName('Press');
      [*] = ;   var tag : Integer = GetIntValueByName('Tag');
      [*] = ;   var key : String = GetValueByName('Key');
      [*] = ;   var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;
      [*] = ;   const cBtnBaseTagSlot = 1000;
      [*] = ;   const cBtnDismiss = 200;
      [*] = ;
      [*] = ;   if (sPress='c') then
      [*] = ;   begin
      [*] = ;      if (tag>=cBtnBaseTagSlot) and (tag<cBtnBaseTagSlot+gc_HeroInventoryCount) then
      [*] = ;      begin
      [*] = ;         var arrIndex : Integer = tag-cBtnBaseTagSlot;
      [*] = ;         if (key='LButton') then
      [*] = ;         begin
      [*] = ;            if (arrIndex>-1) and (arrIndex<gc_HeroInventoryCount) then
      [*] = ;            begin
      [*] = ;               if (battle.hero[battle.curhero].arritems[arrIndex]=0) then //if nothing currently in the slot where the item is placed
      [*] = ;               begin
      [*] = ;                  if (gIntRegister_InetShopPickedItemID<>0) then //taking an item from shop
      [*] = ;                  begin
      [*] = ;                     battle.hero[battle.curhero].arritems[arrIndex] := gIntRegister_InetShopPickedItemID;
      [*] = ;                     if (not GetGUIShiftStateCtrl) then
      [*] = ;                     begin
      [*] = ;                        gIntRegister_InetShopPickedItemID := 0;
      [*] = ;                        IntRegister0 := 0; //0 - unit, 1 - item, 2 - spell, 3 - learnable spell scroll, 4 - eggs with units
      [*] = ;                        IntRegister1 := 0;
      [*] = ;                        ExecuteState('DoDragElement');
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (gIntRegister_InetPickedItemSlot>-1) then //refers to index of slot, not slot as in hero body parts
      [*] = ;                  begin
      [*] = ;                     var itemID : Integer = battle.hero[battle.curhero].arritems[gIntRegister_InetPickedItemSlot];
      [*] = ;                     _inet_SwapIntVars(battle.hero[battle.curhero].arritems[arrIndex], battle.hero[battle.curhero].arritems[gIntRegister_InetPickedItemSlot]);
      [*] = ;                     
      [*] = ;                     // shield/two-handed dislocation
      [*] = ;                     if (arrIndex < gc_HeroDollSlotsCount) then
      [*] = ;                     begin
      [*] = ;                        var pItemID : Integer = ParserSelectByHandleByIndex(gPrototypeData.extitems.handle, itemID);
      [*] = ;                        var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pItemID, 'ItemSlot');
      [*] = ;                     
      [*] = ;                        //remove shield
      [*] = ;                        if itemSlot = 14 then
      [*] = ;                        begin
      [*] = ;                           var shieldSlotIndex : Integer = _inet_GetSlotIndexByItemSlot(battle, 2);
      [*] = ;                           var shieldItemID : Integer = battle.hero[battle.curhero].arritems[shieldSlotIndex];
      [*] = ;                           if (shieldItemID<>0) and ((arrIndex=1) or (arrIndex=3)) then
      [*] = ;                              _inet_SwapIntVars(battle.hero[battle.curhero].arritems[shieldSlotIndex], battle.hero[battle.curhero].arritems[gIntRegister_InetPickedItemSlot]);
      [*] = ;                        end;
      [*] = ;                        //remove two-handed
      [*] = ;                        if itemSlot = 2 then
      [*] = ;                        begin
      [*] = ;                           var rightArmSlotIndex : Integer = _inet_GetSlotIndexByItemSlot(battle, 1);
      [*] = ;                           var rightArmItemID : Integer = battle.hero[battle.curhero].arritems[rightArmSlotIndex];
      [*] = ;                           var pRightArmItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extitems.handle, rightArmItemID);
      [*] = ;                           var rightArmItemSlot : Integer = ParserGetIntValueByKeyByHandle(pRightArmItem, 'ItemSlot');
      [*] = ;                           if (rightArmItemSlot=14) then
      [*] = ;                              _inet_SwapIntVars(battle.hero[battle.curhero].arritems[rightArmSlotIndex], battle.hero[battle.curhero].arritems[gIntRegister_InetPickedItemSlot]);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     
      [*] = ;                     gIntRegister_InetPickedItemSlot := -1;
      [*] = ;                     IntRegister0 := 0; //0 - unit, 1 - item, 2 - spell, 3 - learnable spell scroll, 4 - eggs with units
      [*] = ;                     IntRegister1 := 0;
      [*] = ;                     ExecuteState('DoDragElement');
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               //if (battle.hero[battle.curhero].arritems[arrIndex]<>0) then
      [*] = ;               begin
      [*] = ;                  if (gIntRegister_InetPickedItemSlot=-1) then
      [*] = ;                  begin
      [*] = ;                     var itemID : Integer = battle.hero[battle.curhero].arritems[arrIndex];
      [*] = ;                     gIntRegister_InetPickedItemSlot := arrIndex;
      [*] = ;                     IntRegister0 := 1; //0 - unit, 1 - item, 2 - spell, 3 - learnable spell scroll, 4 - eggs with units
      [*] = ;                     IntRegister1 := itemID;
      [*] = ;                     ExecuteState('DoDragElement');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     // check if theres a room for potential shield withdraw
      [*] = ;                     var slotFree : Boolean = true;
      [*] = ;                     var itemID : Integer = battle.hero[battle.curhero].arritems[gIntRegister_InetPickedItemSlot];
      [*] = ;                     var shieldItemID : Integer = 0;
      [*] = ;                     var shieldSlotIndex : Integer = -1;
      [*] = ;                     if (arrIndex<gc_HeroDollSlotsCount) then
      [*] = ;                     begin
      [*] = ;                        shieldSlotIndex := _inet_GetSlotIndexByItemSlot(battle, 2);
      [*] = ;                        shieldItemID := battle.hero[battle.curhero].arritems[shieldSlotIndex];
      [*] = ;                        if (shieldItemID<>0) and (_inet_GetFreeInvSlotsCount(battle)<1) then
      [*] = ;                        slotFree := false;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if (slotFree) then
      [*] = ;                     begin
      [*] = ;                        _inet_SwapIntVars(battle.hero[battle.curhero].arritems[arrIndex], battle.hero[battle.curhero].arritems[gIntRegister_InetPickedItemSlot]);
      [*] = ;                        gIntRegister_InetPickedItemSlot := -1;
      [*] = ;                        IntRegister0 := 0; //0 - unit, 1 - item, 2 - spell, 3 - learnable spell scroll, 4 - eggs with units
      [*] = ;                        IntRegister1 := 0;
      [*] = ;                        ExecuteState('DoDragElement');
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     // withdraw shield if two-handed
      [*] = ;                     var pItemID : Integer = ParserSelectByHandleByIndex(gPrototypeData.extitems.handle, itemID);
      [*] = ;                     var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pItemID, 'ItemSlot');
      [*] = ;                     var freeSlotIndex : Integer = _inet_GetFreeInvSlotIndex(battle);//get first free slot
      [*] = ;                     if (itemSlot=14) and ((arrIndex=1) or (arrIndex=3)) then
      [*] = ;                     begin
      [*] = ;                        if (shieldItemID<>0) then
      [*] = ;                        begin
      [*] = ;                           if (freeSlotIndex>-1) then
      [*] = ;                           _inet_SwapIntVars(battle.hero[battle.curhero].arritems[shieldSlotIndex], battle.hero[battle.curhero].arritems[freeSlotIndex]);
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     {else
      [*] = ;                     if (itemSlot=2) and (arrIndex=2) then
      [*] = ;                     begin
      [*] = ;                        var weaponSlotIndex : Integer = _inet_GetSlotIndexByItemSlot(1);
      [*] = ;                        var weaponItemID : Integer = battle.hero[battle.curhero].arritems[shieldSlotIndex];
      [*] = ;                        if (weaponItemID<>0) and (_inet_GetFreeInvSlotsCount>0) then
      [*] = ;                        begin
      [*] = ;                           var pWeaponItemID : Integer = ParserSelectByHandleByIndex(gPrototypeData.extitems.handle, itemID);
      [*] = ;                           var weaponItemSlot : Integer = ParserGetIntValueByKeyByHandle(pWeaponItemID, 'ItemSlot');
      [*] = ;
      [*] = ;                           if (weaponItemSlot=14) and (freeSlotIndex>-1) then
      [*] = ;                           _inet_SwapIntVars(battle.hero[battle.curhero].arritems[weaponSlotIndex], battle.hero[battle.curhero].arritems[freeSlotIndex]);
      [*] = ;                        end;
      [*] = ;                     end;}
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               gIntRegister_InetShopPickedItemID := -1;
      [*] = ;               IntRegister0 := 0; //0 - unit, 1 - item, 2 - spell, 3 - learnable spell scroll, 4 - eggs with units
      [*] = ;               IntRegister1 := 0;
      [*] = ;               ExecuteState('DoDragElement');
      [*] = ;            end;
      [*] = ;
      [*] = ;            ExecuteState('UpdateCustomHeroWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      case tag of
      [*] = ;         cBtnDismiss : begin
      [*] = ;            if (key='LButton') then
      [*] = ;            begin
      [*] = ;               var elmParent : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;               var parentTag : Integer = GetGUIElementTag(elmParent);
      [*] = ;               var arrIndex : Integer = parentTag-cBtnBaseTagSlot;
      [*] = ;               if (battle.hero[battle.curhero].arritems[arrIndex]<>0) then
      [*] = ;               battle.hero[battle.curhero].arritems[arrIndex] := 0;
      [*] = ;
      [*] = ;               ExecuteState('UpdateCustomHeroWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;EventCustomHeroInventory(gEditorCustomPlayerTemporary)
      [*] = ;else
      [*] = ;if (gBoolRegister_IsHotSeat) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_HotSeatActivePlayer=0) then
      [*] = ;   EventCustomHeroInventory(gHotSeatPlayer1)
      [*] = ;   else
      [*] = ;   EventCustomHeroInventory(gHotSeatPlayer2)
      [*] = ;end
      [*] = ;else
      [*] = ;EventCustomHeroInventory(gInetBattle);
   struct.end
section.end

