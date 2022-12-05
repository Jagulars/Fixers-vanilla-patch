section.begin
   Name = VVK.ControlGameModeChange
   Description : struct.begin
      [*] = ;IntRegister0 - operation modefalse=start mode switch, true= mode switch finished
      [*] = ;               0 - mode switch start
      [*] = ;               1 - mode switch do switch
      [*] = ;               2 - mode switch - can run user commands
      [*] = ;               3 - actual change done, can run user commands
      [*] = ;               4 - called from switch game mode _before_ 0 switch regardless of current modes
      [*] = ;                   (made for antifreeze bug workaround and tutorial!) If returns false then mode switch should be ignored
      [*] = ;  please be aware that if old_mode == new_mode then only states 3 and 4 are called
      [*] = ;IntRegister1 - old mode
      [*] = ;IntRegister2 - new mode
      [*] = ;FloatRegister0 - original time delay
      [*] = ;StringRegister0 - optional parameters
      [*] = ;RETURN:
      [*] = ;   if mode is 4 then BoolRegister0 = false if switch should be ignored
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\VVK.CONTROLGAMEMODECHANGE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;//mode: 0 - hide element, 1 - destroy element, 2 - leave as is or fade, 3 - call state instead of window operations
      [*] = ;//      4 - call state with BoolRegister0=True, -1 - end of list
      [*] = ;type WindowData = class
      [*] = ;   parent : Integer;
      [*] = ;   mode : Integer;
      [*] = ;   wnd_name : String;
      [*] = ;   extra_name : String;
      [*] = ;end;
      [*] = ;var wnd_names : array [0..$20] of WindowData;
      [*] = ;
      [*] = ;procedure UpdateHeroHUDSelectionState(goHnd : Integer; state : Boolean);
      [*] = ;begin
      [*] = ;   var hudUnitCollection : Integer = _gui_GetLayer(cHUDStrategyHeroLayer);
      [*] = ;   var hudHnd : Integer = GetGUIGroupHUDCollectionItemByGameObject(hudUnitCollection, goHnd);
      [*] = ;   var elmSelHnd : Integer = GetGUIElementIndexByNameParent('map_radialhero_frame_selection', hudHnd);
      [*] = ;   var elmHnd : Integer = GetGUIElementIndexByNameParent('map_radialhero_portrait_dummy', hudHnd);
      [*] = ;   var frame : String;
      [*] = ;
      [*] = ;   elmHnd := GetGUIElementIndexByNameParent('map_radialhero_portrait_image', elmHnd);
      [*] = ;   elmHnd := GetGUIElementIndexByNameParent('map_radialhero_frame', elmHnd);
      [*] = ;
      [*] = ;   if (state) then
      [*] = ;      frame := 'map.heroselection.yellowcircle'
      [*] = ;   else
      [*] = ;      frame := 'map.heroselection.browncircle';
      [*] = ;
      [*] = ;   SetGUIElementMaterial(elmHnd, frame);
      [*] = ;   SetGUIElementVisible(elmSelHnd, state);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UpdateMainPanelWindows();
      [*] = ;begin
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow(gc_gui_CPPopupButtonsName),gc_gui_FadeTime0_2);
      [*] = ;   GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   GUIExecuteState('map.UpdateCursor');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RemoveInterfaceWindows(new_mode : Integer);
      [*] = ;begin
      [*] = ;   var i,whd,cm : Integer;
      [*] = ;
      [*] = ;   for i := 0 to $1f do
      [*] = ;   begin
      [*] = ;      cm := -1;
      [*] = ;      case wnd_names[i].mode of
      [*] = ;         0 : begin
      [*] = ;            if new_mode = gc_gui_ModeBattle then
      [*] = ;               cm := 1
      [*] = ;            else
      [*] = ;               cm := 0;
      [*] = ;         end;
      [*] = ;         1 : cm := 1;
      [*] = ;         2 : begin
      [*] = ;            if new_mode = gc_gui_ModeBattle then
      [*] = ;               cm := 1
      [*] = ;         end;
      [*] = ;         3 : cm := 3;
      [*] = ;         4: begin
      [*] = ;            BoolRegister0 := True;
      [*] = ;            cm := 3;
      [*] = ;         end;
      [*] = ;         5 : cm := 4;
      [*] = ;         6 : begin
      [*] = ;            StringRegister0 := wnd_names[i].extra_name;
      [*] = ;            StringRegister1 := '0|0|0|0|1';
      [*] = ;            IntRegister0 := 0;
      [*] = ;            cm := 3;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;            cm := $100;
      [*] = ;      end;
      [*] = ;      if cm = $100 then
      [*] = ;         break;
      [*] = ;
      [*] = ;      if cm <> 3 then
      [*] = ;      begin
      [*] = ;         if wnd_names[i].parent = 0 then
      [*] = ;            whd := GetGUIElementTopIndexByName(wnd_names[i].wnd_name)
      [*] = ;         else
      [*] = ;            whd := GetGUIElementIndexByNameParent(wnd_names[i].wnd_name, wnd_names[i].parent);
      [*] = ;
      [*] = ;         if whd <> 0 then
      [*] = ;         begin
      [*] = ;            case cm of
      [*] = ;               0 : SetGUIElementVisible(whd,false);
      [*] = ;               1 : _gui_FadeWindow_VVK(whd,gc_gui_FadeTime0_2,2);
      [*] = ;               4 : SetGUIElementVisible(whd,true);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         GUIExecuteState(wnd_names[i].wnd_name);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var old_mode,new_mode,top,i : Integer;
      [*] = ;var delay : Float;
      [*] = ;var params : String;
      [*] = ;var ok_to_proceed : Boolean = True;
      [*] = ;
      [*] = ;var operMode : Integer = IntRegister0;
      [*] = ;old_mode := IntRegister1;
      [*] = ;new_mode := IntRegister2;
      [*] = ;delay := FloatRegister0;
      [*] = ;params := StringRegister0;
      [*] = ;top := _gui_GetLayerI();
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[OM:'+IntToStr(operMode)+',OLDM:'+IntToStr(old_mode)+',NEWM:'+IntToStr(new_mode)+',PARAM:'+params+']',_log_trace);
      [*] = ;
      [*] = ;//if _log then _log_Gui('[REQ_EM] Current: '+IntToStr(old_mode)+', New: '+IntToStr(new_mode)+', Time: '+FloatToStr(delay)+', Params: '+params+', '+IntToStr(IntRegister0));
      [*] = ;
      [*] = ;case operMode of
      [*] = ;   0 : begin
      [*] = ;      _gui_FadeScreen(true,delay);
      [*] = ;      //SetValueByName(gc_gui_Timer_TooltipsPrefix+gc_gui_Timer_TooltipInnerBuild,'');
      [*] = ;   end;
      [*] = ;   1 : begin
      [*] = ;      _gui_FadeScreen(false,delay);
      [*] = ;
      [*] = ;      case old_mode of
      [*] = ;         gc_gui_ModeMap: begin
      [*] = ;            i := 0;
      [*] = ;            wnd_names[i].wnd_name := 'map_infopanel'; wnd_names[i].parent := top; wnd_names[i].mode := 0; i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'defender_dismiss'; wnd_names[i].parent := top; wnd_names[i].mode := 1;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'defender_tooltip'; wnd_names[i].parent := top; wnd_names[i].mode := 1;  i := i + 1;
      [*] = ;            //wnd_names[i].wnd_name := 'site_loot_window'; wnd_names[i].parent := top; wnd_names[i].mode := 1;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'hudhero'; wnd_names[i].parent := 0; wnd_names[i].mode := 0;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'hudprov'; wnd_names[i].parent := 0; wnd_names[i].mode := 0;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := cMapMiniMapWindowName; wnd_names[i].parent := top; wnd_names[i].mode := 1;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'ResetProvinceHint'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseProvDefenderWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseProvOuterBuildWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseProvRitualWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseProvSiteWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseProvRadialWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 4;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'VVK.BuildWindow2'; wnd_names[i].parent := 0; wnd_names[i].mode := 6; wnd_names[i].extra_name := cCastleBuildingsWindow2Name; i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'VVK.ShowBuildWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 6; wnd_names[i].extra_name := cCastleBuildingsWindowName; i := i + 1;
      [*] = ;            //wnd_names[i].wnd_name := gc_gui_CPBottomName; wnd_names[i].parent := top; wnd_names[i].mode := 2;  i := i + 1;
      [*] = ;            //wnd_names[i].wnd_name := gc_gui_CPStatusTextName; wnd_names[i].parent := top; wnd_names[i].mode := 2;  i := i + 1;
      [*] = ;            //wnd_names[i].wnd_name := gc_gui_CPResTooltipName; wnd_names[i].parent := top; wnd_names[i].mode := 2;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := ''; wnd_names[i].parent := top; wnd_names[i].mode := -1;  i := i + 1;
      [*] = ;            RemoveInterfaceWindows(new_mode);
      [*] = ;         end;
      [*] = ;         gc_gui_ModeCastle: begin
      [*] = ;            i := 0;
      [*] = ;            wnd_names[i].wnd_name := 'VVK.BuildWindow2'; wnd_names[i].parent := 0; wnd_names[i].mode := 6; wnd_names[i].extra_name := cCastleBuildingsWindow2Name; i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'VVK.ShowBuildWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 6; wnd_names[i].extra_name := cCastleBuildingsWindowName; i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'DoResetDragElement'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseCastleWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseSpellWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseShopWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseUnitsWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseHeroRecruitWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseCastleTabs'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'map.CloseHeroWindow'; wnd_names[i].parent := 0; wnd_names[i].mode := 3;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := 'defender_tooltip'; wnd_names[i].parent := top; wnd_names[i].mode := 1;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := cInnerBuildingTooltipWindowName; wnd_names[i].parent := top; wnd_names[i].mode := 1;  i := i + 1;
      [*] = ;            wnd_names[i].wnd_name := ''; wnd_names[i].parent := 0; wnd_names[i].mode := -1;  i := i + 1;
      [*] = ;            RemoveInterfaceWindows(new_mode);
      [*] = ;            gBoolRegister_RepairItemMode := False;
      [*] = ;
      [*] = ;            if gBoolRegister_BtnCastleBlink then
      [*] = ;               _gui_RemoveBlinkElement('btnCastle', gBoolRegister_BtnCastleBlink);
      [*] = ;         end;
      [*] = ;         //gc_gui_ModeBattle: begin
      [*] = ;         //end;
      [*] = ;         //gc_gui_ModeEndTurn
      [*] = ;      end;
      [*] = ;      case new_mode of
      [*] = ;         gc_gui_ModeMap: begin
      [*] = ;            gIntRegister_GUICurCastleMode := 0;
      [*] = ;
      [*] = ;            if old_mode <> gc_gui_ModeBattle then
      [*] = ;            begin
      [*] = ;               gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;               SetGUIElementVisible(_gui_GetLayer(cHUDStrategyHeroLayer), true);
      [*] = ;               SetGUIElementVisible(_gui_GetLayer(cHUDStrategyProvLayer), true);
      [*] = ;               //_gui_UpdateSettingsLowest(gProfile.settingslowest);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var waterName : String = 'default';
      [*] = ;
      [*] = ;               SetBoolValueByName('FadeFromBattleMode', false);
      [*] = ;               MapExecuteState('bat.SwitchToMap');
      [*] = ;
      [*] = ;               if (_worldrule_GetWorldRuleVisualExistByID(3)) and (_worldrule_GetWorldRuleVisualParams(3, 1)=5) then
      [*] = ;                  waterName := 'lava';
      [*] = ;               SetCurrentWaterName(waterName);
      [*] = ;
      [*] = ;               GUIExecuteState('DoCreate');
      [*] = ;            end;
      [*] = ;
      [*] = ;            SetCameraInfoSmoothingChange(false);
      [*] = ;            CameraInfoLoadToCurrentView('@lastStratCamera');
      [*] = ;            StringRegister0 := '';
      [*] = ;            MapExecuteState('ResizeCamera');
      [*] = ;            SetCameraControlMode('ccmRTS');
      [*] = ;            SetCameraInfoSmoothingChange(true);
      [*] = ;
      [*] = ;            MapExecuteState('map.DoShowMapShadow');
      [*] = ;            MapExecuteState('map.DoHideBattleShadow');
      [*] = ;            MapExecuteState('map.DoHideCastleShadow');
      [*] = ;            MapExecuteState('map.DoFogFadeOff');
      [*] = ;            _cmd_Post('.mapshowminimap','-2','');
      [*] = ;
      [*] = ;            case old_mode of
      [*] = ;               gc_gui_ModeBattle:
      [*] = ;               begin
      [*] = ;                  if gBoolRegister_AfterEndTurn then  // set ONLY in lan game in endconflicts parser for master player!
      [*] = ;                  begin
      [*] = ;                     gBoolRegister_AfterEndTurn := false;
      [*] = ;                     MapExecuteState('map.AfterEndTurn');
      [*] = ;                     _gv_SetMapLock(-1,_log_name);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if gStringRegister_AfterBattleQuery <> '' then
      [*] = ;                  begin
      [*] = ;                     if (gGame.gameType = gc_GameTypeLanShard) and (gIntRegister_QueryPlayerIndex >= 0) and (gStringRegister_AfterBattleQuery = IntToStr(gc_gui_query_playerCampPlayerLose)) then
      [*] = ;                     begin
      [*] = ;                        // hack for 2 players ONLY
      [*] = ;                        if SameText(GetPlayerControlModeByHandle(GetPlayerHandleByIndex(gIntRegister_QueryPlayerIndex)),'cmPlayer') then
      [*] = ;                           gStringRegister_AfterBattleQuery := IntToStr(gc_gui_query_lan_playerWin);
      [*] = ;                     end;
      [*] = ;                     StringRegister0 := gStringRegister_AfterBattleQuery;
      [*] = ;                     GUIExecuteState('map.RequestQueryWindow');
      [*] = ;                     //gIntRegister_QueryPlayerIndex := -1;
      [*] = ;                     gStringRegister_AfterBattleQuery := '';
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  GUIExecuteState('map.CheckEndGame');
      [*] = ;               end;
      [*] = ;               gc_gui_ModeCastle : begin
      [*] = ;                  if gBoolRegister_BtnCastleCloseBlink then
      [*] = ;                     _gui_RemoveBlinkElement('btnCastleClose', gBoolRegister_BtnCastleCloseBlink);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if gTutorial.map then
      [*] = ;            begin
      [*] = ;               if (gTutorial.move = 20) and (gTutorial.build = 5) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := 20;
      [*] = ;                  MapExecuteState('CheckTutorialProgress');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if _misc_GetTutorialHintStatus() <> gc_Tutorial_HintEnabled then
      [*] = ;            begin
      [*] = ;               IntRegister0 := -1;
      [*] = ;               MapExecuteState('CheckTutorialProgress');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         gc_gui_ModeCastle: begin
      [*] = ;            gIntRegister_GUICurCastleMode := 1;
      [*] = ;            //_gui_UpdateSettingsLowest(gProfile.settingslowest);
      [*] = ;
      [*] = ;            if not GetCameraExist('@lastStratCamera') then
      [*] = ;               AddCameraInfo('@lastStratCamera');
      [*] = ;            CameraInfoSaveFromCurrentView('@lastStratCamera');
      [*] = ;            SetCameraControlMode('ccmNone');
      [*] = ;
      [*] = ;            SetCameraInfoSmoothingChange(false);
      [*] = ;            StringRegister0 := '@tCStart';
      [*] = ;            MapExecuteState('ResizeCamera');
      [*] = ;            SetCameraInfoSmoothingChange(true);
      [*] = ;
      [*] = ;            MapExecuteState('map.DoHideMapShadow');
      [*] = ;            MapExecuteState('map.DoHideBattleShadow');
      [*] = ;            MapExecuteState('map.DoShowCastleShadow');
      [*] = ;            MapExecuteState('map.DoFogFadeOff');
      [*] = ;            GUIExecuteState('map.UpdateCursor');
      [*] = ;
      [*] = ;            if gBoolRegister_BtnCastleBlink then
      [*] = ;               _gui_RemoveBlinkElement('btnCastle', gBoolRegister_BtnCastleBlink);
      [*] = ;         end;
      [*] = ;         gc_gui_ModeBattle: begin
      [*] = ;            gIntRegister_GUICurCastleMode := 0;
      [*] = ;
      [*] = ;            if old_mode = gc_gui_ModeMap then
      [*] = ;            begin
      [*] = ;               if not GetCameraExist('@lastStratCamera') then
      [*] = ;                  AddCameraInfo('@lastStratCamera');
      [*] = ;               CameraInfoSaveFromCurrentView('@lastStratCamera');
      [*] = ;            end;
      [*] = ;
      [*] = ;            SetCameraInfoSmoothingChange(false);
      [*] = ;            CameraInfoLoadToCurrentView('@battleCamera');
      [*] = ;            StringRegister0 := '';
      [*] = ;            MapExecuteState('ResizeCamera');
      [*] = ;            SetCameraInfoSmoothingChange(true);
      [*] = ;
      [*] = ;            gBoolRegister_QuickBattle := false;
      [*] = ;            gBoolRegister_IsHumanPlayer := true;
      [*] = ;
      [*] = ;            Assert(((gIntRegister_BattleProvIndex1 <> -1) and (gIntRegister_BattleProvIndex2 <> -1)),'Battle without defined province patterns');
      [*] = ;            if (gIntRegister_BattleProvIndex1 = -1) then
      [*] = ;            begin
      [*] = ;               gIntRegister_BattleProvIndex1 := 1;
      [*] = ;               IntRegister0 := 1;
      [*] = ;               MapExecuteState('GetTerrainParserByID');
      [*] = ;               gStringRegister_Battle_RightTType := ParserGetValueByKeyByHandle( IntRegister1, 'Name');
      [*] = ;               gStringRegister_Battle_LeftTType := gStringRegister_Battle_RightTType;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (gIntRegister_BattleProvIndex2 = -1) then
      [*] = ;            begin
      [*] = ;               gIntRegister_BattleProvIndex2 := 1;
      [*] = ;               IntRegister0 := 1;
      [*] = ;               MapExecuteState('GetTerrainParserByID');
      [*] = ;               gStringRegister_Battle_RightTType := ParserGetValueByKeyByHandle( IntRegister1, 'Name');
      [*] = ;               gStringRegister_Battle_LeftTType := gStringRegister_Battle_RightTType;
      [*] = ;            end;
      [*] = ;
      [*] = ;            //if gBoolRegister_ArenaBattle or (gBoolRegister_MapResolveConflicts and (gGame.gameType = gc_GameTypeLanShard)) then
      [*] = ;            //begin
      [*] = ;               gBoolRegister_BattleSimulate := false;
      [*] = ;               MapExecuteState('bat.GenerateMap');
      [*] = ;               CadencerProgressDeltaTime();
      [*] = ;            //end
      [*] = ;            {else
      [*] = ;            begin
      [*] = ;               var goHandle : Integer;
      [*] = ;
      [*] = ;               goHandle := GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, _gv_GetCurrentPlayerHandle());
      [*] = ;
      [*] = ;               if goHandle <> 0 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := gIntRegister_BattleDefendArmy;
      [*] = ;                  IntRegister1 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'StartBattleWithArmy');
      [*] = ;                  // flag will be set there and switch to battle state will be called from there
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var dummyHandle,pProvince,siegePlHandle : Integer;
      [*] = ;                  var underSiege : Boolean;
      [*] = ;
      [*] = ;                  // rebel
      [*] = ;                  dummyHandle := _map_GetCurrentProvinceHandle();
      [*] = ;                  pProvince := GetGameObjectIntValueIndByHandle(dummyHandle, gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;                  GameObjectExecuteStateByHandle(dummyHandle, 'IsUnderSiege');
      [*] = ;                  siegePlHandle := IntRegister0;
      [*] = ;                  underSiege := BoolRegister0;
      [*] = ;
      [*] = ;                  if (not underSiege) then
      [*] = ;                  begin
      [*] = ;                     gBoolRegister_BattleSimulate := false;
      [*] = ;                     MapExecuteState('bat.GenerateMap');
      [*] = ;                     CadencerProgressDeltaTime();
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     // rebel siege
      [*] = ;                     var pTerrainType,provPlHandle : Integer;
      [*] = ;                     var sTerrainType, provPlName : String;
      [*] = ;
      [*] = ;                     IntRegister0 := ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType');
      [*] = ;                     MapExecuteState('GetTerrainParserByID');
      [*] = ;                     pTerrainType := IntRegister1;
      [*] = ;                     sTerrainType := ParserGetValueByKeyByHandle(pTerrainType, 'Name');
      [*] = ;
      [*] = ;                     provPlName := ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;                     provPlHandle := GetPlayerHandleByName(provPlName);
      [*] = ;
      [*] = ;                     gIntRegister_BattleAttackArmy := ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;                     gIntRegister_BattleAttackHeroHandle := 0;
      [*] = ;                     gIntRegister_BattleAttackPlayer := 0;
      [*] = ;
      [*] = ;                     gIntRegister_BattleDefendArmy := ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;                     gIntRegister_BattleDefendHeroHandle := 0;
      [*] = ;                     gIntRegister_BattleDefendPlayer := provPlHandle;
      [*] = ;
      [*] = ;                     gIntRegister_BattleGuardIndex := -1;
      [*] = ;                     gIntRegister_BattleDefenderIndex := -1;
      [*] = ;
      [*] = ;                     gStringRegister_Battle_RightTType := sTerrainType;
      [*] = ;                     gStringRegister_Battle_LeftTType := sTerrainType;
      [*] = ;
      [*] = ;                     gIntRegister_BattleProvIndex1 := ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;                     gIntRegister_BattleProvIndex2 := ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;                     gIntRegister_BattleSiteIndex := 0;
      [*] = ;
      [*] = ;                     gIntRegister_MapBattleProvince := pProvince;
      [*] = ;
      [*] = ;                     gBoolRegister_BattleSimulate := false;
      [*] = ;                     MapExecuteState('bat.GenerateMap');
      [*] = ;                     CadencerProgressDeltaTime();
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;}
      [*] = ;            GUIExecuteState('map.SwitchToBattle');
      [*] = ;         end;
      [*] = ;         gc_gui_ModeSwitchToAstral : begin
      [*] = ;            if gTutorial.map then
      [*] = ;               StateMachineSetBoolValueByName(GetMapInitMachineHandle(), 'LoadAstral', false)
      [*] = ;            else
      [*] = ;               StateMachineSetBoolValueByName(GetMapInitMachineHandle(), 'LoadAstral', true);
      [*] = ;
      [*] = ;            MapExecuteState('astral.Create');
      [*] = ;         end;
      [*] = ;         gc_gui_ModeExitGame, gc_gui_ModeSwitchToMainMenu : begin
      [*] = ;            if new_mode = gc_gui_ModeExitGame then
      [*] = ;               _run_ExitGame()
      [*] = ;            else
      [*] = ;               _run_DoCreateMenu();
      [*] = ;         end;
      [*] = ;         gc_gui_ModeExitLanGame, gc_gui_ModeSwitchToLanMenu : begin
      [*] = ;            var gf : Integer = _misc_GetGameFlags();
      [*] = ;
      [*] = ;            if ((gf and (gc_GameTypeFlagSingle or gc_GameTypeFlagInternet)) = gc_GameTypeFlagInternet) then
      [*] = ;            begin
      [*] = ;               var p : Integer = _misc_ParserGetOrCreateByKey('lan_controlgamemodechange',true);
      [*] = ;
      [*] = ;               //_lan_timer_Arm(gc_lt_map_loading_sync,0,false);
      [*] = ;               ParserSetIntValueByKeyByHandle(p, 'ExitMode', new_mode);
      [*] = ;               if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;                  _inet_LanSendParserExt(gc_LAN_SHUTDOWN_GAME, p)
      [*] = ;               else
      [*] = ;               if (gGame.gameType = gc_GameTypeLanBattle) and (not gBoolRegister_BattleEndBattle) then
      [*] = ;                  _lan_LanSendParserToEnemy(gc_LAN_SHUTDOWN_GAME, p);
      [*] = ;
      [*] = ;               if GetLanMode >= 2 then
      [*] = ;                 LanPublicServerCloseSession();
      [*] = ;               
      [*] = ;               if new_mode = gc_gui_ModeExitLanGame then
      [*] = ;                  _run_ExitGame()
      [*] = ;               else
      [*] = ;                  _run_DoCreateMenu();
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if new_mode = gc_gui_ModeExitLanGame then
      [*] = ;                  _run_ExitGame()
      [*] = ;               else
      [*] = ;                  _run_DoCreateMenu();
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   2 : begin
      [*] = ;      case new_mode of
      [*] = ;         gc_gui_ModeCastle: begin
      [*] = ;            var dc,sub_mode,whd : Integer;
      [*] = ;            var plHnd : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;            PlayerExecuteStateByHandle(plHnd, 'GetCastleParser');
      [*] = ;            gIntRegister_MapSelectedHex := IntRegister0;
      [*] = ;
      [*] = ;            dc := _sa_GetNum(params);
      [*] = ;            if dc > 0 then
      [*] = ;               sub_mode := _sa_GetAsInt(params,0)
      [*] = ;            else
      [*] = ;               sub_mode := 0;
      [*] = ;
      [*] = ;            if sub_mode <= 0 then
      [*] = ;            begin
      [*] = ;               //check if we have no hero, jump to hero recruit tab at castle
      [*] = ;               var isHeroAvailable : Boolean = False;
      [*] = ;               var i,goHnd : Integer;
      [*] = ;
      [*] = ;               for i := 0 to GetPlayerGameObjectsCountByHandle(plHnd)-1 do
      [*] = ;               begin
      [*] = ;                  goHnd := GetGameObjectHandleByIndex(i,plHnd);
      [*] = ;                  if (not GetGameObjectBoolValueIndByHandle(goHnd, gc_map_GOStack_MapUnit_bIsDead)) then
      [*] = ;                  begin
      [*] = ;                     isHeroAvailable := True;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (isHeroAvailable) then
      [*] = ;                  sub_mode := -1*sub_mode
      [*] = ;               else
      [*] = ;                  sub_mode := 3;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (gTutorial.map) and (gTutorial.build = 0) then
      [*] = ;               IntRegister0 := 0
      [*] = ;            else
      [*] = ;               IntRegister0 := sub_mode - 1;
      [*] = ;            GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            if old_mode <> gc_gui_ModeCastle then
      [*] = ;               _misc_UpdateCastleCameraPosition(-1);
      [*] = ;            UpdateMainPanelWindows();
      [*] = ;         end;
      [*] = ;         gc_gui_ModeMap: begin
      [*] = ;            var m_mode : String;
      [*] = ;
      [*] = ;            //if _log then _log_Gui('FOG: '+BoolToStr(gGame.fog));
      [*] = ;            MapExecuteState('map.DoShowFog');
      [*] = ;            MapExecuteState('map.DoFogFadeOff');
      [*] = ;            _sa_Get(params,0,m_mode);
      [*] = ;            case m_mode of
      [*] = ;               'end_turn': begin
      [*] = ;                  var whd : Integer;
      [*] = ;
      [*] = ;                  _gui_FadeScreen(false,0);
      [*] = ;                  LogI('WARNING! End turn is called from DoProgress - AntiFreeze would not work!');
      [*] = ;                  whd := _gui_GetWindow('endturn_commands');
      [*] = ;                  if whd <> 0 then
      [*] = ;                     _gui_RootWindowRemoveWithFade(whd,0);
      [*] = ;                  _cmd_RegisterStateForDummy('endturn_commands','VVK.Map.EndTurnCommands','0',cRootWindowTop,cRootWindowAttrHighest);
      [*] = ;                  // boosting up console priority
      [*] = ;                  _gui_RootWindowAddExt(_gui_GetWindow('chat_command_interceptor'),cRootWindowTop,cRootWindowAttrHighest,0,'');
      [*] = ;                  MapExecuteState('map.BeforeEndTurn');
      [*] = ;               end;
      [*] = ;               'ritual' : begin
      [*] = ;                  GUIExecuteState('map.CloseHeroWindow');
      [*] = ;                  GUIExecuteState('vvk.map.ShowRitualsList');
      [*] = ;               end;
      [*] = ;               'next_hero' : begin
      [*] = ;                  var goHandle : Integer;
      [*] = ;
      [*] = ;                  if (gIntRegister_MapSelectedUID<>0) then
      [*] = ;                  UpdateHeroHUDSelectionState(GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID), false); //unselect prev unit
      [*] = ;
      [*] = ;                  PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO, 'SelectNextHero');
      [*] = ;                  SetCameraInfoSmoothingChange(true);
      [*] = ;                  goHandle := GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;                  _misc_SetCameraTarget(goHandle);
      [*] = ;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'Select');
      [*] = ;                  UpdateHeroHUDSelectionState(goHandle, true);
      [*] = ;                  GUIExecuteState('map.DrawGroupDataViewer');
      [*] = ;                  gIntRegister_GUIDrawPathUID := gIntRegister_MapSelectedUID;
      [*] = ;                  GUIExecuteState('map.DrawPath');
      [*] = ;                  _map_RefreshProvincesHUDs();
      [*] = ;
      [*] = ;                  IntRegister0 := 0; //DummyUID - if 0, then get activeHero current UID
      [*] = ;                  IntRegister1 := GetGameObjectUniqueIdByHandle(goHandle); //setActiveHeroUID - if 0, then choose first picked hero
      [*] = ;                  IntRegister2 := 0; //goUIDEndPointReached
      [*] = ;                  GUIExecuteState('map.CreateHeroMultiHUD');
      [*] = ;               end;
      [*] = ;               'inner_build' : begin // on/off/toggle
      [*] = ;                  var on_off : Integer = _sa_GetAsInt(params,1);
      [*] = ;                  var temp_str,state_str,temp_str2 : String;
      [*] = ;
      [*] = ;                  if on_off = -1 then
      [*] = ;                  begin
      [*] = ;                     if _gui_GetWindow(cCastleBuildingsWindowName) <> 0 then
      [*] = ;                        on_off := 0
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if _gui_GetWindow(cCastleBuildingsWindow2Name) <> 0 then
      [*] = ;                           on_off := 0
      [*] = ;                        else
      [*] = ;                           on_off := 1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  temp_str := '';
      [*] = ;                  if on_off = 0 then
      [*] = ;                     _sa_AddAsInt(temp_str,0)
      [*] = ;                  else
      [*] = ;                     _sa_AddAsInt(temp_str,1);
      [*] = ;
      [*] = ;                  temp_str2 := gStrRegister_GUIBuildWindowState;
      [*] = ;                  if _sa_GetAsInt(temp_str2,0) = 0 then
      [*] = ;                  begin
      [*] = ;                     StringRegister0 := cCastleBuildingsWindowName;
      [*] = ;                     StringRegister1 := '0|0|0|0|0';
      [*] = ;                     IntRegister0 := 0;
      [*] = ;                     GUIExecuteState('VVK.ShowBuildWindow');
      [*] = ;                     gStrRegister_GUIBuildWindowState := temp_str2;
      [*] = ;                     StringRegister0 := cCastleBuildingsWindow2Name;
      [*] = ;                     _sa_AddAsInt(temp_str,_sa_GetAsInt(temp_str2,1));
      [*] = ;                     _sa_AddAsInt(temp_str,_sa_GetAsInt(temp_str2,3));
      [*] = ;                     IntRegister0 := _sa_GetAsInt(temp_str2,2);
      [*] = ;                     if IntRegister0 = 0 then
      [*] = ;                     begin
      [*] = ;                        IntRegister1 := 0;
      [*] = ;                        IntRegister2 := 0;
      [*] = ;                     end;
      [*] = ;                     state_str := 'VVK.BuildWindow2';
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     StringRegister0 := cCastleBuildingsWindow2Name;
      [*] = ;                     StringRegister1 := '0|0|0|0|0';
      [*] = ;                     IntRegister0 := 0;
      [*] = ;                     GUIExecuteState('VVK.BuildWindow2');
      [*] = ;                     gStrRegister_GUIBuildWindowState := temp_str2;
      [*] = ;                     StringRegister0 := cCastleBuildingsWindowName;
      [*] = ;                     IntRegister0 := 0;
      [*] = ;                     _sa_AddAsInt(temp_str,1);
      [*] = ;                     _sa_AddAsInt(temp_str,1);
      [*] = ;                     _sa_AddAsInt(temp_str,_sa_GetAsInt(temp_str2,1));
      [*] = ;                     state_str := 'VVK.ShowBuildWindow';
      [*] = ;                  end;
      [*] = ;                  StringRegister1 := temp_str;
      [*] = ;                  GUIExecuteState(state_str);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            UpdateMainPanelWindows();
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //3 : begin
      [*] = ;   //end;
      [*] = ;   4 : begin
      [*] = ;      case new_mode of
      [*] = ;         gc_gui_ModeCastle: begin
      [*] = ;            IntRegister0 := 0;
      [*] = ;            IntRegister1 := gc_gui_mainpanel_btnCastle;
      [*] = ;            GUIExecuteState('VVK.map.MainPanelUpdateButtonsState');
      [*] = ;            ok_to_proceed := BoolRegister0;
      [*] = ;         end;
      [*] = ;         gc_gui_ModeMap: begin
      [*] = ;            {var m_mode : String;
      [*] = ;
      [*] = ;            _sa_Get(params,0,m_mode);
      [*] = ;            if m_mode = 'end_turn' then
      [*] = ;            begin
      [*] = ;               _gui_FadeElement(GetGUIElementIndexByNameParent('showtutorial', _gui_GetLayer(cTutorialLayer)), gc_gui_FadeTime0_2, false, true, true);
      [*] = ;               if old_mode = gc_gui_ModeCastle then
      [*] = ;               begin
      [*] = ;                  // special case - a harsh workaround here
      [*] = ;                     IntRegister0 := 0;
      [*] = ;                     IntRegister1 := gIntRegister_GUIShardGameMode;
      [*] = ;                     IntRegister2 := new_mode;
      [*] = ;                     StringRegister0 := params;
      [*] = ;                     FloatRegister0 := 0;
      [*] = ;                     GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;                     gIntRegister_GUIShardGameMode := new_mode;
      [*] = ;                     IntRegister0 := 1;
      [*] = ;                     IntRegister1 := old_mode;
      [*] = ;                     IntRegister2 := new_mode;
      [*] = ;                     StringRegister0 := params;
      [*] = ;                     FloatRegister0 := 0;
      [*] = ;                     GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;                     IntRegister0 := 2;
      [*] = ;                     IntRegister1 := old_mode;
      [*] = ;                     IntRegister2 := new_mode;
      [*] = ;                     StringRegister0 := params;
      [*] = ;                     FloatRegister0 := 0;
      [*] = ;                     GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;                     IntRegister0 := 3;
      [*] = ;                     IntRegister1 := old_mode;
      [*] = ;                     IntRegister2 := new_mode;
      [*] = ;                     StringRegister0 := params;
      [*] = ;                     FloatRegister0 := 0;
      [*] = ;                     GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;                     ok_to_proceed := False;
      [*] = ;               end;
      [*] = ;               StateMachineExecuteState(initMachine, 'map.BeforeEndTurn', 0); // we will never return from this function untill turn is finished!
      [*] = ;            end;}
      [*] = ;
      [*] = ;            if old_mode = gc_gui_ModeCastle then
      [*] = ;            begin
      [*] = ;               if gTutorial.hero = 3 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := -2;
      [*] = ;                  MapExecuteState('CheckTutorialProgress');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if operMode = 3 then
      [*] = ;   _misc_UpdateTutorialHint()
      [*] = ;else
      [*] = ;   if (operMode = 0) or (operMode = 4) then
      [*] = ;      _misc_SetTutorialHintVisible(false);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;BoolRegister0 := ok_to_proceed;
   struct.end
section.end

