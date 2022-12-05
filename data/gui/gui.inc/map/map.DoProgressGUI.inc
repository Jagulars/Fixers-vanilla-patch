section.begin
   Name = map.DoProgressGUI
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.DOPROGRESSGUI';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var i,j,k,plHandle : Integer;
      [*] = ;
      [*] = ;if GetUserBoolValue('GUIDebug') then
      [*] = ;begin
      [*] = ;   if (gFloatRegister_gDbgFloat0PrevValue <> gIntRegister_dbgX) or (gFloatRegister_gDbgFloat1PrevValue <> gIntRegister_dbgY) or (gFloatRegister_gDbgFloat2PrevValue <> gIntRegister_dbgZ) then
      [*] = ;   begin
      [*] = ;      Log('xOffset=' + IntToStr(gIntRegister_dbgX) + ' YOffset=' + IntToStr(gIntRegister_dbgY) + ' dbgZ=' + IntToStr(gIntRegister_dbgZ));
      [*] = ;      if GetUserBoolValue('Debug') then
      [*] = ;         MapExecuteState('ResizeCamera');
      [*] = ;   end;
      [*] = ;   gFloatRegister_gDbgFloat0PrevValue := gIntRegister_dbgX;
      [*] = ;   gFloatRegister_gDbgFloat1PrevValue := gIntRegister_dbgY;
      [*] = ;   gFloatRegister_gDbgFloat2PrevValue := gIntRegister_dbgZ;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;   GUIExecuteState('map.EditorProgressGUI');
      [*] = ;
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;   GUIExecuteState('UpdateCameraRestrict');
      [*] = ;
      [*] = ;GUIExecuteState('map.HeroHUDControl');
      [*] = ;GUIExecuteState('map.ProvHUDControl');
      [*] = ;
      [*] = ;if (gBoolRegister_GUIUpdateMapDrawPath) then
      [*] = ;begin
      [*] = ;   GUIExecuteState('map.DrawPath');
      [*] = ;   gBoolRegister_GUIUpdateMapDrawPath := False;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIUpdateInterfacePanel) then
      [*] = ;begin
      [*] = ;   var ehd : Integer = _gui_GetWindow('map_infopanel');
      [*] = ;
      [*] = ;   if ehd <> 0 then SetGUIElementTag(ehd,-1);
      [*] = ;   if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;   begin
      [*] = ;      GUIExecuteState('map.DrawSelectedHex');
      [*] = ;      if _log then _Log_Gui(_log_name+' Infopanel redraw!');
      [*] = ;      GUIExecuteState('map.CreateInfoPanel');
      [*] = ;   end;
      [*] = ;   ehd := _gui_GetWindow(cMapMiniMapWindowName);
      [*] = ;   if (gIntRegister_MapUnderCursorHex <> 0) and (ehd <> 0) then
      [*] = ;   begin
      [*] = ;      var args : String = GetGUIElementStringTag(ehd);
      [*] = ;
      [*] = ;      if not SameText(args,'min') then
      [*] = ;      begin
      [*] = ;         var p,whd,x,y : Integer;
      [*] = ;
      [*] = ;         whd := GetGUIElementIndexByNameParent('minimap.pointer',ehd);
      [*] = ;         if whd <> 0 then
      [*] = ;         begin
      [*] = ;            var scale_f : Float = _sa_GetAsFloat(args,3);
      [*] = ;
      [*] = ;            IntRegister0 := 0;
      [*] = ;            IntRegister1 := 0;
      [*] = ;            IntRegister2 := ParserGetIntValueByKeyByHandle(gIntRegister_MapUnderCursorHex,'Index');
      [*] = ;            MapExecuteState('map.vvk.MiniMapHelper');
      [*] = ;            x := IntRegister0;
      [*] = ;            y := IntRegister1;
      [*] = ;            SetGUIElementPosition(whd,floor(x*scale_f)-(GetGUIElementWidth(whd) div 2),floor(y*scale_f)-(GetGUIElementHeight(whd) div 2))
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   GUIExecuteState('VVK.map.UpdateMainPanel');
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := False;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIMapCheckEndGame) and (_gv_GetMapLock() = 0) and (not gMapEditor.enabled) then
      [*] = ;begin
      [*] = ;   GUIExecuteState('map.CheckEndGame');
      [*] = ;   gBoolRegister_GUIMapCheckEndGame := False;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIMapUpdate) then
      [*] = ;begin
      [*] = ;   gBoolRegister_GUIMapUpdate := False;
      [*] = ;   GUIExecuteState('map.UpdateMouseMove');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_NeedSeasonChangeObjects) then
      [*] = ;begin
      [*] = ;   MapExecuteState('CreateSeasons');
      [*] = ;   gBoolRegister_NeedSeasonChangeObjects := False; // Need to set after execute CreateSeasons
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('vvk.map.ProgressProvinceGUI');
      [*] = ;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   plHandle := GetPlayerHandleByIndex(i);
      [*] = ;
      [*] = ;   if (plHandle=GetPlayerHandleInterfaceIO()) or (gMapEditor.enabled) then
      [*] = ;   begin
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         if (GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iUpdate)>0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := goHandle;
      [*] = ;            GUIExecuteState('map.GUIUpdateHeroHUD');
      [*] = ;
      [*] = ;            for k := 0 to 2 do
      [*] = ;            begin
      [*] = ;               case k of
      [*] = ;                  0 : IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID); //DummyUID - if 0, then get activeHero current UID
      [*] = ;                  1 : IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iBeforeTargetUID);
      [*] = ;                  2 : IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;               end;
      [*] = ;               if (IntRegister0 <> 0) or (k=0) then
      [*] = ;               begin
      [*] = ;                  IntRegister1 := 0; //setActiveHeroUID - if 0, then choose first picked hero
      [*] = ;                  IntRegister2 := 0; //goUIDEndPointReached
      [*] = ;                  GUIExecuteState('map.CreateHeroMultiHUD');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iUpdate, 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) and (GetLanMode() = 1) and _plr_IsInGame(plHandle) then
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'Nothing');
      [*] = ;end;
      [*] = ;
      [*] = ;//Camera follows active hero
      [*] = ;if (not gBoolRegister_MapTurnFinished) then
      [*] = ;begin
      [*] = ;   var myIndex : Integer = GetPlayerIndexByHandle(GetPlayerHandleInterfaceIO());
      [*] = ;   if (myIndex=_gv_GetCurrentPlayer()) then
      [*] = ;   begin
      [*] = ;      if (not IsCameraMoveToPosition()) then
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, GetPlayerHandleInterfaceIO());
      [*] = ;
      [*] = ;         if (goHandle<>0) and (GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask) > 0) then
      [*] = ;         begin
      [*] = ;            SetCameraInfoSmoothingChange(False);
      [*] = ;            _misc_SetCameraTarget(goHandle);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIProcessBuildingsQuery) and (gBoolRegister_MapTurnFinished) and (_gui_GetWindow('queryWindow') = 0) then
      [*] = ;begin
      [*] = ;   gBoolRegister_GUIProcessBuildingsQuery := False;
      [*] = ;   PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'GetCastleParser');
      [*] = ;   GameObjectExecuteStateByHandle(GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(IntRegister0, 'DummyUID')), 'IsUnderSiege');
      [*] = ;   if (not BoolRegister0) then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := true;
      [*] = ;      StringRegister0 := cProcessBuildingsQueueWindowName;
      [*] = ;      GUIExecuteState('VVK.map.ProcessBuildingsQueue');
      [*] = ;   end;
      [*] = ;   GUIExecuteState('VVK.map.ShowLastTurnIncome');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIUpdateMapHexGrid) then
      [*] = ;begin
      [*] = ;   gBoolRegister_GUIUpdateMapHexGrid := False;
      [*] = ;   GUIExecuteState('map.DrawHexGrid');
      [*] = ;   GUIExecuteState('map.DrawSelectedHex');
      [*] = ;end;
      [*] = ;
      [*] = ;// update gold/gem input box in diplomacy window
      [*] = ;if (gIntRegister_DiplomacyActivePlayerID > -1) and (gIntRegister_DiplomacyWindowMode > 1) then
      [*] = ;begin
      [*] = ;   function GetInputBoxIntValue(sideName, partName : String) : Integer;
      [*] = ;   begin
      [*] = ;      var elmHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.'+sideName+'.frame_'+partName+'.inputbox_'+partName+'.text', _gui_GetLayerI());
      [*] = ;      Result := StrToInt(GetGUIElementText(elmHnd));
      [*] = ;   end;
      [*] = ;   procedure SetInputBoxIntValue(sideName, partName : String; value : Integer);
      [*] = ;   begin
      [*] = ;      var elmHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.'+sideName+'.frame_'+partName+'.inputbox_'+partName+'.text', _gui_GetLayerI());
      [*] = ;      SetGUIElementText(elmHnd, IntToStr(value));
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var bUpdateInput : Boolean = false;
      [*] = ;   
      [*] = ;   var inputAmount : Integer = GetInputBoxIntValue('offers', 'offergold');
      [*] = ;   if (inputAmount > 0) and (inputAmount <> gDiplMessage.tradeGive.gold) then
      [*] = ;   begin
      [*] = ;      var myPlHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;      var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;      var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;      if gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message.mType = gc_MessageExchange then
      [*] = ;         plGold := plGold + gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message.tradeGive.gold; // include escrow
      [*] = ;      
      [*] = ;      if inputAmount > plGold then
      [*] = ;      begin
      [*] = ;         inputAmount := plGold;
      [*] = ;         SetInputBoxIntValue('offers', 'offergold', inputAmount);
      [*] = ;      end;
      [*] = ;      gDiplMessage.tradeGive.gold := inputAmount;
      [*] = ;      bUpdateInput := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      inputAmount := GetInputBoxIntValue('offers', 'offergem');
      [*] = ;      if (inputAmount > 0) and (inputAmount <> gDiplMessage.tradeGive.gem) then
      [*] = ;      begin
      [*] = ;         var myPlHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;         var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;         var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         if gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message.mType = gc_MessageExchange then
      [*] = ;            plGem := plGem + gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message.tradeGive.gem; // include escrow
      [*] = ;      
      [*] = ;         if inputAmount > plGem then
      [*] = ;         begin
      [*] = ;            inputAmount := plGem;
      [*] = ;            SetInputBoxIntValue('offers', 'offergem', inputAmount);
      [*] = ;         end;
      [*] = ;         gDiplMessage.tradeGive.gem := inputAmount;
      [*] = ;         bUpdateInput := true;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         inputAmount := GetInputBoxIntValue('demand', 'demandgold');
      [*] = ;         if (inputAmount > 0) and (inputAmount <> gDiplMessage.tradeTake.gold) then
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeTake.gold := inputAmount;
      [*] = ;            bUpdateInput := true;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            inputAmount := GetInputBoxIntValue('demand', 'demandgem');
      [*] = ;            if (inputAmount > 0) and (inputAmount <> gDiplMessage.tradeTake.gem) then
      [*] = ;            begin
      [*] = ;               gDiplMessage.tradeTake.gem := inputAmount;
      [*] = ;               bUpdateInput := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;      
      [*] = ;   if bUpdateInput then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_DiplomacyWindowMode = 3) or (gIntRegister_DiplomacyWindowMode = 4) then // a sent message has been modified
      [*] = ;      begin
      [*] = ;         gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;         GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;      end
      [*] = ;      else // no need to redo the whole window, just check the send message button
      [*] = ;      begin
      [*] = ;         var elmBtnHandle : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.btn_send_message', _gui_GetLayerI());
      [*] = ;         if GetGUIElementVisible(elmBtnHandle) then
      [*] = ;         begin
      [*] = ;            var hint : String = '';
      [*] = ;            if _diplomacy_IsMessageDraftValid(hint) then
      [*] = ;            begin
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, True);
      [*] = ;               SetGUIElementHint(elmBtnHandle, '');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;               SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

