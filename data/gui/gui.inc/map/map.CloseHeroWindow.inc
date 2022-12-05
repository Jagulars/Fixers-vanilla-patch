section.begin
   Name = map.CloseHeroWindow
   Description : struct.begin
      [*] = ;BoolRegister0 - check tutorial
   struct.end
   Code : struct.begin
      [*] = ;var checkTut : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CLOSEHEROWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;// rank 5 temporary (no space for unit) slot remove
      [*] = ;if (gIntRegister_GUICurHeroMode=gc_HeroPanelExtraUnit) then
      [*] = ;begin
      [*] = ;   IntRegister0 := 5;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   IntRegister2 := 0;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetSlotUnit');
      [*] = ;   if (IntRegister2<>0) then ParserFreeByHandle(IntRegister2);
      [*] = ;end;
      [*] = ;
      [*] = ;var pEncRecruitUnits : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(GetPlayerHandleInterfaceIO()), 'EncRecruitUnits');
      [*] = ;if (ParserGetCountByHandle(pEncRecruitUnits)>0) then
      [*] = ;begin
      [*] = ;   //_gv_SetMapLock(-1,_log_name);
      [*] = ;   ParserClearByHandle(pEncRecruitUnits);
      [*] = ;end;
      [*] = ;
      [*] = ;var heroPanel : Integer = _gui_GetWindow('map_heropanel');
      [*] = ;
      [*] = ;GUIExecuteState('map.CloseCastleTabs');
      [*] = ;GUIExecuteState('map.CloseUnitsWindow');
      [*] = ;GUIExecuteState('map.CloseSpellWindow');
      [*] = ;_gui_RootWindowRemoveWithFade(heroPanel, 0);
      [*] = ;_gui_RootWindowRemoveWithFade(_gui_GetWindow('map_hero_incastle_panel_info'),0);
      [*] = ;_gui_RootWindowRemoveWithFade(_gui_GetWindow('map_heropanel_second'),0);
      [*] = ;GUIExecuteState('map.CloseShopWindow');
      [*] = ;
      [*] = ;if gBoolRegister_UpdateHeroPath then
      [*] = ;begin
      [*] = ;   if gIntRegister_MapSelectedUID > 0 then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID), 'UpdatePath');
      [*] = ;      gIntRegister_GUIDrawPathUID := gIntRegister_MapSelectedUID;
      [*] = ;      GUIExecuteState('map.DrawPath');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _gv_GetMapLock > 90 then
      [*] = ;   _gv_SetMapLock($10000, _log_name);
      [*] = ;if _gv_GetBattleLock > 90 then
      [*] = ;   _gv_SetBattleLock($10000, _log_name);
      [*] = ;
      [*] = ;if checkTut then
      [*] = ;begin
      [*] = ;   checkTut := false;
      [*] = ;   // if this is hero, not castle window
      [*] = ;   if gIntRegister_GUICurHeroMode >= 0 then
      [*] = ;   begin
      [*] = ;      var heroClass : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;
      [*] = ;      if gTutorial.map then
      [*] = ;      begin
      [*] = ;         case gTutorial.move of
      [*] = ;            5, 10 : begin
      [*] = ;               if (gTutorial.trade >= 8) or (gTutorial.hire >= 7) or (gTutorial.library >= 6) then
      [*] = ;                  checkTut := true;
      [*] = ;            end;
      [*] = ;            13 : begin
      [*] = ;               if heroClass = 4 then
      [*] = ;               begin
      [*] = ;                  if gIntRegister_GUICurHeroMode = gc_HeroPanelInventory then
      [*] = ;                     checkTut := true;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if gIntRegister_GUICurHeroMode = gc_HeroPanelSpellbook then
      [*] = ;                     checkTut := true;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            17 : begin
      [*] = ;               if gIntRegister_GUICurHeroMode = gc_HeroPanelInventory then
      [*] = ;                  checkTut := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (_gui_GetWindow('necromancy') <> 0) then // redo necromancy window in case unit slots were cleared to fit undead
      [*] = ;begin
      [*] = ;   BoolRegister0 := false;
      [*] = ;   BoolRegister1 := true;
      [*] = ;   GUIExecuteState('ShowNecromancy');
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_RepairItemMode := False;
      [*] = ;gIntRegister_MapCurrentShop := 0;
      [*] = ;gIntRegister_GUIActiveHeroUID1 := 0;
      [*] = ;gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;gIntRegister_GUICurHeroMode := gc_HeroPanelNotValid;
      [*] = ;gIntRegister_CurrentEncounterID := 0;
      [*] = ;
      [*] = ;if (gIntRegister_CurGameMode = gc_GameModeStrategy) and (not _misc_IsMapLocked) then
      [*] = ;   MapExecuteState('map.CheckQueryExecute');
      [*] = ;
      [*] = ;if checkTut then
      [*] = ;begin
      [*] = ;   GUIExecuteState('CloseTutorial');
      [*] = ;   IntRegister0 := gTutorial.move;
      [*] = ;   MapExecuteState('CheckTutorialProgress');
      [*] = ;end;
      [*] = ;
      [*] = ;_misc_UpdateTutorialHint();
      [*] = ;//GUIExecuteState('vvk.map.UpdateMainPanel');
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

