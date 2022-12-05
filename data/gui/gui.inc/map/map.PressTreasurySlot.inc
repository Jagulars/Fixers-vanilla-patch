section.begin
   Name = map.PressTreasurySlot
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.PRESSTREASURYSLOT';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;
      [*] = ;var _log : Boolean = false;
      [*] = ;var sPress  : String  = GetValueByName('Press');
      [*] = ;var sKey  : String  = GetValueByName('Key');
      [*] = ;
      [*] = ;if (sKey='LButton') and (sPress='c') then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name+'[ID:'+IntToStr(gIntRegister_MapPickedItemID)+',P:'+gStringRegister_ItemPlace+']',_log_trace);
      [*] = ;   var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;   var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;   var pPlTreasury : Integer = ParserSelectByHandleByKey(pPlParser, 'Treasury');
      [*] = ;
      [*] = ;   var treasurySlot : Integer = GetIntValueByName('Tag') - gc_gui_treasuryitemslots_btnBaseTag;
      [*] = ;
      [*] = ;   var pTreasurySlot : Integer = ParserSelectByHandleByIndex(pPlTreasury, treasurySlot);
      [*] = ;   var trItemID : Integer = ParserGetIntValueByKeyByHandle(pTreasurySlot, 'ItemID');
      [*] = ;   var trItemDur : Integer = ParserGetIntValueByKeyByHandle(pTreasurySlot, 'Durability');
      [*] = ;
      [*] = ;   var pickedItemID : Integer = gIntRegister_MapPickedItemID;
      [*] = ;   var pickedItemDur : Integer = gIntRegister_MapPickedItemDurability;
      [*] = ;   var bUpdateHint : Boolean = False;
      [*] = ;
      [*] = ;   if (pickedItemID <> 0) then
      [*] = ;   begin
      [*] = ;      if SameText(gStringRegister_ItemPlace, 'Shop') then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pickedItemID;
      [*] = ;         IntRegister1 := GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;         IntRegister2 := gIntRegister_MapCurrentShop;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'BuyItem');
      [*] = ;         var lastItem : Boolean = BoolRegister0;
      [*] = ;         if ( BoolRegister1 ) then
      [*] = ;         begin
      [*] = ;            _gui_PlaySound('interface', 'money_spent');
      [*] = ;            ParserSetIntValueByKeyByHandle(pTreasurySlot, 'ItemID', pickedItemID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pTreasurySlot, 'Durability', pickedItemDur);
      [*] = ;         end;
      [*] = ;
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         IntRegister0 := pickedItemID;
      [*] = ;         IntRegister1 := GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;         IntRegister2 := gIntRegister_MapCurrentShop;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetItemPrice');
      [*] = ;         var gold : Integer = IntRegister3;
      [*] = ;         var gem : Integer = IntRegister4;
      [*] = ;         var enoughMoneyForNextCopy : Boolean = False;
      [*] = ;         if ((plGold >= gold) or (gold=0)) and ((plGem >= gem) or (gem=0)) then
      [*] = ;            enoughMoneyForNextCopy := True;
      [*] = ;
      [*] = ;         if (not GetGUIShiftStateCtrl()) or (lastItem) or (not enoughMoneyForNextCopy) then
      [*] = ;         begin
      [*] = ;            GUIExecuteState('DoResetDragElement');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var pPrevSlot : Integer = 0;
      [*] = ;         var heroCanUse : Boolean = true;
      [*] = ;         if SameText(gStringRegister_ItemPlace, 'Treasury') then
      [*] = ;         begin
      [*] = ;            pPrevSlot := ParserSelectByHandleByIndex(pPlTreasury, gIntRegister_MapSelectedItemSlot);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if SameText(gStringRegister_ItemPlace, 'Doll') then
      [*] = ;         begin
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;            var pGoParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;            var pDoll : Integer = ParserSelectByHandleByKey(pGoParser, 'Doll');
      [*] = ;            pPrevSlot := ParserSelectByHandleByIndex(pDoll, gIntRegister_MapSelectedItemSlot);
      [*] = ;
      [*] = ;            IntRegister0 := trItemID;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CanUseItem');
      [*] = ;            var canUse : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            IntRegister0 := trItemID;
      [*] = ;            MapExecuteState('GetItemParserByID');
      [*] = ;            var pItem : Integer = IntRegister1;
      [*] = ;            var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemSlot');
      [*] = ;            var itemType : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;
      [*] = ;            IntRegister0 := pickedItemID;
      [*] = ;            MapExecuteState('GetItemParserByID');
      [*] = ;            var pItem2 : Integer = IntRegister1;
      [*] = ;            var itemSlot2 : Integer = ParserGetIntValueByKeyByHandle(pItem2, 'ItemSlot');
      [*] = ;            var itemType2 : Integer = ParserGetIntValueByKeyByHandle(pItem2, 'ItemType');
      [*] = ;
      [*] = ;            var slotItemSlot : Integer = ParserGetIntValueByKeyByHandle(pPrevSlot, 'ItemSlot');
      [*] = ;
      [*] = ;            if (trItemID=0) or (slotItemSlot=0) or (canUse and ((itemSlot2 = itemSlot) or ((itemSlot2 = 1) and (itemSlot = 14)))) then
      [*] = ;               heroCanUse := true
      [*] = ;            else
      [*] = ;               heroCanUse := false;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (pPrevSlot=0) then
      [*] = ;            ErrorLogI(_log_name+' Unknown slot');
      [*] = ;
      [*] = ;         if (not SameText(gStringRegister_ItemPlace, 'Doll')) or (heroCanUse) then
      [*] = ;         begin
      [*] = ;            if (trItemID<>0) then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pPrevSlot, 'ItemID', trItemID);
      [*] = ;               ParserSetIntValueByKeyByHandle(pPrevSlot, 'Durability', trItemID);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pPrevSlot, 'ItemID', 0);
      [*] = ;               ParserSetIntValueByKeyByHandle(pPrevSlot, 'Durability', 0);
      [*] = ;            end;
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(pTreasurySlot, 'ItemID', pickedItemID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pTreasurySlot, 'Durability', pickedItemDur);
      [*] = ;         end;
      [*] = ;
      [*] = ;         ParserSetBoolValueByKeyByHandle(pPrevSlot, 'Picked', False);
      [*] = ;
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'RecalcCurrentHP');
      [*] = ;         var pMyQuests : Integer = ParserSelectByHandleByKey(ParserSelectGameObject(goHandle), 'Quests');
      [*] = ;         var i : Integer;
      [*] = ;         for i:=ParserGetCountByHandle(pMyQuests)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := i;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CheckQuestDone');
      [*] = ;         end;
      [*] = ;         GUIExecuteState('DoResetDragElement');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (trItemID<>0) and (_pars_ParserGetIntValueExt(pTreasurySlot, 'ReservedPlayer') < 0) then
      [*] = ;   begin
      [*] = ;      if (gBoolRegister_RepairItemMode) then
      [*] = ;      begin
      [*] = ;         //if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;         begin
      [*] = ;            if (gIntRegister_MapSelectedUID<>0) then
      [*] = ;            begin
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;               var pProvince : Integer = IntRegister0;
      [*] = ;
      [*] = ;               IntRegister0 := pTreasurySlot;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               IntRegister2 := gIntRegister_MapCurrentShop;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'RepairInvItem');
      [*] = ;
      [*] = ;               _gui_PlaySound('interface', 'repair_item');
      [*] = ;
      [*] = ;               bUpdateHint := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         gIntRegister_MapSelectedItemSlot := treasurySlot;
      [*] = ;         gIntRegister_MapPickedItemID := trItemID;
      [*] = ;         gIntRegister_MapPickedItemDurability := trItemDur;
      [*] = ;         gStringRegister_ItemPlace := 'Treasury';
      [*] = ;
      [*] = ;         IntRegister0 := gc_dragdrop_item;
      [*] = ;         IntRegister1 := trItemID;
      [*] = ;         GUIExecuteState('DoDragElement');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _Log_gui('Picked item ID = ' + IntToStr(gIntRegister_MapPickedItemID));
      [*] = ;   if _log then _Log_gui('Picked item durability = ' + IntToStr(gIntRegister_MapPickedItemDurability));
      [*] = ;
      [*] = ;   if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;   begin
      [*] = ;      gIntRegister_GUICurHeroMode := gc_HeroPanelInventory;
      [*] = ;      GUIExecuteState('map.CreateHeroWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := 3;
      [*] = ;      GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;   end;
      [*] = ;   if (bUpdateHint) then
      [*] = ;   begin
      [*] = ;      SetIntValueByName('ElementHandle', GetGUIElementUnderMouse());
      [*] = ;      GUIExecuteState('DoOnMouseEnter');
      [*] = ;      GUIExecuteState('DoOnHintGUI');
      [*] = ;   end;
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (sKey='RButton') and (sPress='c') then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,_log_trace);
      [*] = ;   if gIntRegister_MapPickedItemID <> 0 then
      [*] = ;      GUIExecuteState('DoResetDragElement');
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
   struct.end
section.end

