section.begin
   Name = map.SwitchToBattle
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.SWITCHTOBATTLE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;procedure Fade(fade_in : Boolean;Time : Float);
      [*] = ;begin
      [*] = ;   var not_fade_in : Boolean = (not fade_in);
      [*] = ;   var iImgHandle : Integer = _gui_getFadeBlack();
      [*] = ;
      [*] = ;   SetGUIElementFadeInEnabled(iImgHandle, fade_in);
      [*] = ;   SetGUIElementFadeOutEnabled(iImgHandle, not_fade_in);
      [*] = ;   SetGUIElementFreezeEnabled(iImgHandle, fade_in);
      [*] = ;   SetGUIElementFadeAutoDestroy(iImgHandle, not_fade_in);
      [*] = ;   SetGUIElementFadingTimes(iImgHandle, Time, 0.0);
      [*] = ;   SetGUIElementFadeStart(iImgHandle, True);
      [*] = ;end;
      [*] = ;
      [*] = ;gIntRegister_CurGameMode := gc_GameModeTactics;
      [*] = ;gBoolRegister_BattleEndBattle := false;
      [*] = ;
      [*] = ;IntRegister0 := _obj_GetCheckSceneryFlags(gProfile.objectflags, gProfile.shardscenery, gProfile.townscenery, gProfile.provincescenery, $ff);
      [*] = ;ExecuteState('CheckScenery');
      [*] = ;
      [*] = ;var waterName : String;
      [*] = ;if (_worldrule_GetWorldRuleVisualExistByID(3)) and (_worldrule_GetWorldRuleVisualParams(3, 1)=5) then
      [*] = ;   waterName := 'lava'
      [*] = ;else
      [*] = ;   waterName := 'tactic0';
      [*] = ;SetCurrentWaterName(waterName);
      [*] = ;
      [*] = ;_gui_PlaySound('interface', 'battle_begins');
      [*] = ;ExecuteState('DoCreate');
      [*] = ;ExecuteState('battle.SetPlacementMode');
      [*] = ;ExecuteState('battle.CreateControlPanelWindow');
      [*] = ;
      [*] = ;Fade(false,1.25);
      [*] = ;
      [*] = ;MapExecuteState('map.DoHideMapShadow');
      [*] = ;MapExecuteState('map.DoShowBattleShadow');
      [*] = ;MapExecuteState('map.DoHideCastleShadow');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

