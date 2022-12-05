section.begin
   Name = map.CloseDiplomacyWindow
   Code : struct.begin
      [*] = ;//gIntRegister_DiplomacyActivePlayerID := -1;
      [*] = ;_diplomacy_ClearMessage(gDiplMessage);
      [*] = ;gIntRegister_DiplomacyWindowMode := 0;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var placeHolder : Boolean;
      [*] = ;_gui_RemoveBlinkElement('btnPlayerOffer', placeHolder);
      [*] = ;//_gui_RemoveBlinkElement('btnAcceptDeal', placeHolder);
      [*] = ;//_gui_RemoveBlinkElement('btnDeclineDeal', placeHolder);
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;   _gui_RemoveBlinkElement('btnDiplomacyPlayer_'+IntToStr(i), placeHolder);
      [*] = ;
      [*] = ;if _misc_GetTutorialHintStatus <> gc_Tutorial_HintDisabled then
      [*] = ;   GUIExecuteState('DestroyTutorial');
      [*] = ;
      [*] = ;_gui_RootWindowRemoveWithFade(_gui_GetWindow('diplomacy'), gc_gui_FadeTime0_2);
      [*] = ;
      [*] = ;// update treasury in case items were reserved in deals
      [*] = ;if (_gui_GetWindow('map_shoppanel_bg.map_shoppanel_items') <> 0) then
      [*] = ;begin
      [*] = ;   if gIntRegister_GUICurCastleMode <> 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 3;
      [*] = ;      GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gIntRegister_GUICurHeroMode := gc_HeroPanelInventory;
      [*] = ;      GUIExecuteState('map.CreateHeroWindow');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;//ExecuteState('VVK.map.UpdateMainPanel');
   struct.end
section.end

