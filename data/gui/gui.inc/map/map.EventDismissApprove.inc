section.begin
   Name = map.EventDismissApprove
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.EVENTDISMISSAPPROVE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;const cBtnDismissCancel = 900;
      [*] = ;const cBtnBaseTagDismissUnit = 1000;
      [*] = ;const cBtnDismissUnitGarrison = 2000;
      [*] = ;const cBtnDismissItem = 3000;
      [*] = ;const cBtnDismissItemDoll = 4000;
      [*] = ;const cBtnDismissSpell = 5000;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if (tag>=cBtnBaseTagDismissUnit) and (tag<cBtnDismissUnitGarrison) then
      [*] = ;   begin
      [*] = ;      var parentElmTag : Integer = tag-cBtnBaseTagDismissUnit;
      [*] = ;      var rank : Integer = parentElmTag div 10;
      [*] = ;      var index : Integer = parentElmTag mod 10;
      [*] = ;
      [*] = ;      if (rank > 0) and (index >= 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := rank;
      [*] = ;         IntRegister1 := index;
      [*] = ;         var dismissGoHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapDismissHeroUID);
      [*] = ;         GameObjectExecuteStateByHandle(dismissGoHandle, 'GetSlotUnit');
      [*] = ;         var pUnit : Integer = IntRegister2;
      [*] = ;         var pGOHandle : Integer = ParserSelectGameObject(dismissGoHandle);
      [*] = ;         var pMyUnits : Integer = ParserSelectByHandleByKey(pGOHandle, 'Units');
      [*] = ;         IntRegister0 := pMyUnits;
      [*] = ;         IntRegister1 := ParserGetIndexOf(pUnit);
      [*] = ;         var plHandle : Integer;
      [*] = ;         if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;         plHandle := GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex)
      [*] = ;         else
      [*] = ;         plHandle := GetPlayerHandleInterfaceIO;
      [*] = ;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'DismissUnit');
      [*] = ;         gIntRegister_MapSelectedUnitSlot := 0;
      [*] = ;         gIntRegister_MapSelectedSlotHeroUID := 0;
      [*] = ;         gIntRegister_MapDismissHeroUID := 0;
      [*] = ;
      [*] = ;         if (gIntRegister_GUICurCastleMode=0) or (gIntRegister_GUICurHeroMode=0) then
      [*] = ;         begin
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := 1;
      [*] = ;            GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;         end;
      [*] = ;
      [*] = ;         gBoolRegister_UpdateHeroPath := true;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   case tag of
      [*] = ;      cBtnDismissCancel : begin
      [*] = ;         gIntRegister_MapSelectedUnitSlot := 0;
      [*] = ;         gIntRegister_MapSelectedSlotHeroUID := 0;
      [*] = ;         gIntRegister_MapSelectedGarrisonUnitSlot := 0;
      [*] = ;         gIntRegister_MapSelectedSpellSlot := 0;
      [*] = ;         gIntRegister_MapSelectedItemSlot := 0;
      [*] = ;         gIntRegister_MapPickedItemID := 0;
      [*] = ;         gIntRegister_MapPickedItemDurability := 0;
      [*] = ;         gIntRegister_MapPickedUnitID := 0;
      [*] = ;         gStringRegister_ItemPlace := '';
      [*] = ;         gIntRegister_MapDismissHeroUID := 0;
      [*] = ;      end;
      [*] = ;      cBtnDismissUnitGarrison : begin
      [*] = ;         var rank : Integer = gIntRegister_MapSelectedGarrisonUnitSlot div 10;
      [*] = ;         var index : Integer = gIntRegister_MapSelectedGarrisonUnitSlot mod 10;
      [*] = ;
      [*] = ;         if (rank > 0) and (index >= 0) then
      [*] = ;         begin
      [*] = ;            var pProvince : Integer;
      [*] = ;            if (gIntRegister_MapSelectedHex<>0) then
      [*] = ;               pProvince := gIntRegister_MapSelectedHex
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;               var dummyUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;               IntRegister0 := dummyUID;
      [*] = ;               MapExecuteState('GetProvinceParserByUID');
      [*] = ;               pProvince := IntRegister1;
      [*] = ;            end;
      [*] = ;
      [*] = ;            var pGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;            IntRegister0 := pGarrison;
      [*] = ;            IntRegister1 := rank;
      [*] = ;            IntRegister2 := index;
      [*] = ;            MapExecuteState('map.GetGarrisonSlotUnit');
      [*] = ;            var pUnit : Integer = IntRegister3;
      [*] = ;            var pUnits : Integer = ParserSelectByHandleByKey(pGarrison, 'Units');
      [*] = ;            IntRegister0 := pUnits;
      [*] = ;            IntRegister1 := ParserGetIndexOf(pUnit);
      [*] = ;            var plHandle : Integer;
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;               plHandle := GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex)
      [*] = ;            else
      [*] = ;               plHandle := GetPlayerHandleInterfaceIO;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'DismissUnit');
      [*] = ;            //ParserFreeByHandle(pUnit);
      [*] = ;            gIntRegister_MapSelectedGarrisonUnitSlot := 0;
      [*] = ;            gIntRegister_MapDismissHeroUID := 0;
      [*] = ;            if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;               var curID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;               var dummyUID : Integer = ParserGetIntValueByKeyByHandle(gIntRegister_MapSelectedHex, 'DummyUID');
      [*] = ;               if (gIntRegister_MapSelectedHex<>0) then
      [*] = ;               begin
      [*] = ;                  if (dummyUID=curID) then
      [*] = ;                  begin
      [*] = ;                     gIntRegister_GUICurHeroMode := gc_HeroPanelUnitsOnly;
      [*] = ;                     GUIExecuteState('map.CreateHeroWindow');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     BoolRegister0 := True;
      [*] = ;                     GUIExecuteState('map.CreateGarrisonWindow');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := 1;
      [*] = ;               GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnDismissSpell : begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;
      [*] = ;         var rank : Integer = gIntRegister_MapSelectedSpellSlot div 10;
      [*] = ;         var index : Integer = gIntRegister_MapSelectedSpellSlot mod 10;
      [*] = ;
      [*] = ;         IntRegister0 := rank;
      [*] = ;         IntRegister1 := index;
      [*] = ;         IntRegister2 := 0;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetSlotSpell');
      [*] = ;         var pSpell : Integer = IntRegister2;
      [*] = ;         ParserFreeByHandle(pSpell);
      [*] = ;         gIntRegister_MapSelectedSpellSlot := 0;
      [*] = ;
      [*] = ;         if (gIntRegister_GUICurCastleMode=0) or (gIntRegister_GUICurHeroMode=0) then
      [*] = ;         begin
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := 4;
      [*] = ;            GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnDismissItem : begin
      [*] = ;         var plHandle : Integer;
      [*] = ;         if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;         plHandle := GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex)
      [*] = ;         else
      [*] = ;         plHandle := GetPlayerHandleInterfaceIO;
      [*] = ;         var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;         var pPlTreasury : Integer = ParserSelectByHandleByKey(pPlParser, 'Treasury');
      [*] = ;         var pPrevSlot : Integer = ParserSelectByHandleByIndex(pPlTreasury, gIntRegister_MapSelectedItemSlot);
      [*] = ;
      [*] = ;         IntRegister0 := ParserGetIntValueByKeyByHandle(pPrevSlot, 'ItemID');;
      [*] = ;         IntRegister1 := ParserGetIntValueByKeyByHandle(pPrevSlot, 'Durability');
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'SellItem');
      [*] = ;         _gui_PlaySound('interface', 'money_spent');
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pPrevSlot, 'ItemID', 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pPrevSlot, 'Durability', 0);
      [*] = ;
      [*] = ;         gIntRegister_MapSelectedItemSlot := 0;
      [*] = ;         gIntRegister_MapPickedItemID := 0;
      [*] = ;         gIntRegister_MapPickedItemDurability := 0;
      [*] = ;         gIntRegister_MapPickedUnitID := 0;
      [*] = ;         gStringRegister_ItemPlace := '';
      [*] = ;         gIntRegister_MapDismissHeroUID := 0;
      [*] = ;
      [*] = ;         IntRegister0 := 1; //0 - unit, 1 - item, 2 - spell
      [*] = ;         IntRegister1 := 0; //0 - hide
      [*] = ;         GUIExecuteState('DoDragElement');
      [*] = ;
      [*] = ;         if (gIntRegister_GUICurCastleMode=0) or (gIntRegister_GUICurHeroMode=0) then
      [*] = ;         begin
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if GetGUIElementVisible(GetGUIElementIndexByNameParent('map_spellpanel', _gui_GetLayerI())) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 4;
      [*] = ;               GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if GetGUIElementVisible(GetGUIElementIndexByNameParent('map_garrisonpanel', _gui_GetLayerI())) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 1;
      [*] = ;               GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := 3;
      [*] = ;               GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnDismissItemDoll : begin
      [*] = ;         var plHandle : Integer;
      [*] = ;         if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;         plHandle := GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex)
      [*] = ;         else
      [*] = ;         plHandle := GetPlayerHandleInterfaceIO;
      [*] = ;         var dismissGoHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapDismissHeroUID);
      [*] = ;         var pGoParser : Integer = ParserSelectGameObject(dismissGoHandle);
      [*] = ;         var pDoll : Integer = ParserSelectByHandleByKey(pGoParser, 'Doll');
      [*] = ;         var pPrevSlot : Integer = ParserSelectByHandleByIndex(pDoll, gIntRegister_MapSelectedItemSlot);
      [*] = ;
      [*] = ;         ParserSetBoolValueByKeyByHandle(pPrevSlot, 'Picked', False);
      [*] = ;
      [*] = ;         var dummyUID : Integer = GetGameObjectIntValueIndByHandle(dismissGoHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;         var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;         var pCastleProv : Integer = IntRegister0;
      [*] = ;         var castleUID : Integer = ParserGetIntValueByKeyByHandle(pCastleProv, 'DummyUID');
      [*] = ;         var castle : Boolean = False;
      [*] = ;         if (castleUID=dummyUID) then
      [*] = ;         castle := True;
      [*] = ;         var isShop : Boolean;
      [*] = ;         if gIntRegister_MapTurnIteration = 1 then // no selling items during encounters 
      [*] = ;            isShop := false
      [*] = ;         else
      [*] = ;         if (castle) then
      [*] = ;         begin
      [*] = ;            isShop := True;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            GameObjectExecuteStateByHandle(dummyHnd, 'IsShopAndLibrary');
      [*] = ;            isShop := BoolRegister0;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (isShop) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := ParserGetIntValueByKeyByHandle(pPrevSlot, 'ItemID');;
      [*] = ;            IntRegister1 := ParserGetIntValueByKeyByHandle(pPrevSlot, 'Durability');
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'SellItem');
      [*] = ;            _gui_PlaySound('interface', 'money_spent');
      [*] = ;         end;
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pPrevSlot, 'ItemID', 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pPrevSlot, 'Durability', 0);
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dismissGoHandle, 'RecalcCurrentHP');
      [*] = ;         var pMyQuests : Integer = ParserSelectByHandleByKey(pGoParser, 'Quests');
      [*] = ;         var i : Integer;
      [*] = ;         for i:=ParserGetCountByHandle(pMyQuests)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := i;
      [*] = ;            GameObjectExecuteStateByHandle(dismissGoHandle, 'CheckQuestDone');
      [*] = ;         end;
      [*] = ;
      [*] = ;         gIntRegister_MapSelectedItemSlot := 0;
      [*] = ;         gIntRegister_MapPickedItemID := 0;
      [*] = ;         gIntRegister_MapPickedItemDurability := 0;
      [*] = ;         gIntRegister_MapPickedUnitID := 0;
      [*] = ;         gStringRegister_ItemPlace := '';
      [*] = ;         gIntRegister_MapDismissHeroUID := 0;
      [*] = ;
      [*] = ;         IntRegister0 := 1; //0 - unit, 1 - item, 2 - spell
      [*] = ;         IntRegister1 := 0; //0 - hide
      [*] = ;         GUIExecuteState('DoDragElement');
      [*] = ;
      [*] = ;         if (gIntRegister_GUICurCastleMode=0) or (gIntRegister_GUICurHeroMode=0) then
      [*] = ;         begin
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if GetGUIElementVisible(_gui_GetWindow('map_spellpanel')) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 4;
      [*] = ;               GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if GetGUIElementVisible(_gui_GetWindow('map_garrisonpanel')) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 1;
      [*] = ;               GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := 3;
      [*] = ;               GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

