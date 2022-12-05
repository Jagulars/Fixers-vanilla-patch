section.begin
   Name = DoResetDragElement
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\DORESETDRAGELEMENT';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;if _log then _log_Values('MapSelectedSpellSlot|MapPickedSpellID',gIntRegister_MapSelectedSpellSlot,gIntRegister_MapPickedSpellID,0,0,0,0);
      [*] = ;if (gIntRegister_MapSelectedSpellSlot<>0) or (gIntRegister_MapPickedSpellID<>0) then
      [*] = ;begin
      [*] = ;   gIntRegister_MapSelectedSpellSlot := 0;
      [*] = ;   gIntRegister_MapPickedSpellID := 0;
      [*] = ;   IntRegister0 := 0; //0 - unit, 1 - item, 2 - spell
      [*] = ;   IntRegister1 := 0; //0 - hide
      [*] = ;   GUIExecuteState('DoDragElement');
      [*] = ;
      [*] = ;   if (gIntRegister_GUICurCastleMode=0) or (gIntRegister_GUICurHeroMode=0) then
      [*] = ;   begin
      [*] = ;      GUIExecuteState('map.CreateHeroWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := 4;
      [*] = ;      GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _log_Values('MapDismissHeroUID|MapSelectedUnitSlot|MapSelectedGarrisonUnitSlot|MapPickedUnitID',gIntRegister_MapDismissHeroUID,gIntRegister_MapSelectedUnitSlot,gIntRegister_MapSelectedGarrisonUnitSlot,gIntRegister_MapPickedUnitID,0,0);
      [*] = ;if (gIntRegister_MapDismissHeroUID=0) and ((gIntRegister_MapSelectedUnitSlot<>0) or (gIntRegister_MapSelectedGarrisonUnitSlot<>0) or (gIntRegister_MapPickedUnitID<>0)) then
      [*] = ;begin
      [*] = ;   gIntRegister_MapSelectedUnitSlot := 0;
      [*] = ;   gIntRegister_MapSelectedSlotHeroUID := 0;
      [*] = ;   gIntRegister_MapSelectedGarrisonUnitSlot := 0;
      [*] = ;   gIntRegister_MapPickedUnitID := 0;
      [*] = ;   gIntRegister_MapPickedUnitExp := 0;
      [*] = ;   gBoolRegister_MapMercenaryPicked := false;
      [*] = ;   IntRegister0 := 0; //0 - unit, 1 - item, 2 - spell
      [*] = ;   IntRegister1 := 0; //0 - hide
      [*] = ;   GUIExecuteState('DoDragElement');
      [*] = ;
      [*] = ;   if (gIntRegister_GUICurCastleMode=0) or (gIntRegister_GUICurHeroMode=0) then
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;      var curID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(gIntRegister_MapSelectedHex, 'DummyUID');
      [*] = ;      //_log_Values('HERO_MODE|SEL_HEX|DUID|CID',gIntRegister_GUICurHeroMode,gIntRegister_MapSelectedHex,dummyUID,curID,0,0);
      [*] = ;      if (GetGUIElementVisible(_gui_GetWindow('map_heropanel'))) or (dummyUID=curID) or (gIntRegister_MapSelectedHex=0) then
      [*] = ;      begin
      [*] = ;         GUIExecuteState('map.CreateHeroWindow');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         BoolRegister0 := True;
      [*] = ;         GUIExecuteState('map.CreateGarrisonWindow');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if GetGUIElementVisible(GetGUIElementIndexByNameParent('map_garrisonpanel', _gui_GetLayerI())) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 1;
      [*] = ;         GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _log_Values('MapPickedItemID',gIntRegister_MapPickedItemID,0,0,0,0,0);
      [*] = ;if (gIntRegister_MapPickedItemID<>0) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_CurGameMode=gc_GameModeStrategy) then
      [*] = ;   begin
      [*] = ;      if (gStringRegister_ItemPlace='Doll') then
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1{gIntRegister_MapSelectedUID});
      [*] = ;         if (goHandle<>0) then
      [*] = ;         begin
      [*] = ;            var pGoParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;            var pDoll : Integer = ParserSelectByHandleByKey(pGoParser, 'Doll');
      [*] = ;            var pPrevSlot : Integer = ParserSelectByHandleByIndex(pDoll, gIntRegister_MapSelectedItemSlot);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pPrevSlot, 'Picked', False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      gIntRegister_MapSelectedItemSlot := 0;
      [*] = ;      gIntRegister_MapPickedItemID := 0;
      [*] = ;      gIntRegister_MapPickedItemDurability := 0;
      [*] = ;      gIntRegister_MapPickedUnitID := 0;
      [*] = ;      gStringRegister_ItemPlace := '';
      [*] = ;
      [*] = ;      IntRegister0 := gc_dragdrop_item; //0 - unit, 1 - item, 2 - spell
      [*] = ;      IntRegister1 := 0; //0 - hide
      [*] = ;      GUIExecuteState('DoDragElement');
      [*] = ;
      [*] = ;      var bNoSpaceForItemWindow : Boolean = False;
      [*] = ;      var nospaceforitemElmName : Integer = _gui_GetWindow('nospaceforitem');
      [*] = ;      if (nospaceforitemElmName<>0) then
      [*] = ;         bNoSpaceForItemWindow := GetGUIElementVisible(nospaceforitemElmName);
      [*] = ;
      [*] = ;      if (bNoSpaceForItemWindow) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 0;
      [*] = ;         GUIExecuteState('map.CreateNoSpaceForItemWindow');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) or (gIntRegister_GUICurHeroMode=0) then
      [*] = ;      begin
      [*] = ;         GUIExecuteState('map.CreateHeroWindow');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if GetGUIElementVisible(GetGUIElementIndexByNameParent('map_spellpanel', _gui_GetLayerI())) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 4;
      [*] = ;            GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if GetGUIElementVisible(GetGUIElementIndexByNameParent('map_garrisonpanel', _gui_GetLayerI())) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 1;
      [*] = ;            GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := 3;
      [*] = ;            GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO, 'GetHeroHandle');
      [*] = ;      var heroHandle : Integer = IntRegister0;
      [*] = ;      var uid : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID);
      [*] = ;      var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;      if (mapHeroHandle<>0) then
      [*] = ;      begin
      [*] = ;         var heroParser : Integer = ParserSelectGameObject(mapHeroHandle);
      [*] = ;         var pHeroDoll : Integer = ParserSelectByHandleByKey(heroParser, 'Doll');
      [*] = ;         var pPrevSlot : Integer = ParserSelectByHandleByIndex(pHeroDoll, gIntRegister_MapSelectedItemSlot);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pPrevSlot, 'Picked', False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      gIntRegister_MapSelectedItemSlot := 0;
      [*] = ;      gIntRegister_MapPickedItemID := 0;
      [*] = ;      gIntRegister_MapPickedItemDurability := 0;
      [*] = ;      gIntRegister_MapPickedUnitID := 0;
      [*] = ;      gStringRegister_ItemPlace := '';
      [*] = ;
      [*] = ;      IntRegister0 := gc_dragdrop_item; //0 - unit, 1 - item, 2 - spell
      [*] = ;      IntRegister1 := 0; //0 - hide
      [*] = ;      GUIExecuteState('DoDragElement');
      [*] = ;
      [*] = ;      GUIExecuteState('battle.CreateSwitchWeapon');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

