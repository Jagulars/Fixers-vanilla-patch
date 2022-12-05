section.begin
   Name = vvk.map.MainPanelCommands
   Description : struct.begin
      [*] = ;IntRegister0 - execution mode (0-execute, 1-return status)
      [*] = ;IntRegister1 - command id
      [*] = ;IntRegister3 - (!) window handle to which this one attached
      [*] = ;StringRegister0 - command name
      [*] = ;StringRegister1 - command parameters (from cfg file)
      [*] = ;StringRegister2 - state parameters (passed in RegisterWindowState)
      [*] = ;StringRegister3 - extra state parameters (passed in PostCommand)
      [*] = ;RETURNS:
      [*] = ;   IntRegister2 - (&0xff: 1 - command available, stop execution, 2 - command unavailable, stop execution, 0 - not supported, continue execution)
      [*] = ;                  high 24 bits are for user defined check availability attributes!
      [*] = ;   StringRegister0 - extra info for some commands
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\VVK.MAP.MAINPANELCOMMANDS';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure SetSelection(province_p : Integer);
      [*] = ;begin
      [*] = ;   gIntRegister_MapSelectedHex := province_p;
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsUnderSiege(pl_handle : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var dummyHnd : Integer;
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(pl_handle,'GetCastleParser');
      [*] = ;   dummyHnd := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(IntRegister0, 'DummyUID'));
      [*] = ;   GameObjectExecuteStateByHandle(dummyHnd, 'IsUnderSiege');
      [*] = ;   Result := BoolRegister0;
      [*] = ;end;
      [*] = ;
      [*] = ;// &1 - garr, &2 - shop in province, &4 - library in province, &8  - hero inventory,
      [*] = ;// &0x10 - hero spellbook, &0x20 - province is a castle province, &0x40 - hero is in enemy province, &0x80-castle under siege,
      [*] = ;// &0x10000 - hero handle is valid
      [*] = ;function GetGSLFlags(hero_obj : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var dummyUID, dummyHnd, castleUID : Integer;
      [*] = ;
      [*] = ;   Result := $10018;
      [*] = ;   PlayerExecuteStateByHandle(GetGameObjectPlayerHandleByHandle(hero_obj), 'GetCastleParser');
      [*] = ;   castleUID := ParserGetIntValueByKeyByHandle(IntRegister0, 'DummyUID');
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(GetGameObjectHandleByUniqueId(castleUID), 'IsUnderSiege');
      [*] = ;   if BoolRegister0 then
      [*] = ;      Result := Result or $80;
      [*] = ;
      [*] = ;   dummyUID := GetGameObjectIntValueIndByHandle(hero_obj,gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   dummyHnd := GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   if (castleUID=dummyUID) then
      [*] = ;   begin
      [*] = ;      Result := Result or $20;
      [*] = ;      if ((Result and $80) = 0) then
      [*] = ;         Result := Result or $7;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(hero_obj,'IsInEnemyProvince');
      [*] = ;      if (not BoolRegister0) then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHnd, 'IsGarrison');
      [*] = ;         if (BoolRegister0) or (gIntRegister_GUIActiveHeroUID2<>0) or (gMapEditor.enabled) then
      [*] = ;            Result := Result or 1;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHnd, 'IsShopAndLibrary');
      [*] = ;         if (BoolRegister0) {or (gIntRegister_GUIActiveHeroUID2<>0)} or (gMapEditor.enabled) then
      [*] = ;            Result := Result or 2;
      [*] = ;         if (BoolRegister1) or (gMapEditor.enabled) then
      [*] = ;            Result := Result or 4;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         Result := Result or $40;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetCastleMode() : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;
      [*] = ;   if gIntRegister_GUICurCastleMode <> 0 then
      [*] = ;   begin
      [*] = ;      var wnd_names : array [0..10] of String;
      [*] = ;      var i,n,whd : Integer;
      [*] = ;
      [*] = ;      i := 0;
      [*] = ;      wnd_names[i] := cCastleBuildingsWindowName; i := i + 1;
      [*] = ;      wnd_names[i] := cCastleGarrisonWindowName; i := i + 1;
      [*] = ;      wnd_names[i] := cCastleHeroRecruitWindowName; i := i + 1;
      [*] = ;      wnd_names[i] := cCastleShopWindowName; i := i + 1;
      [*] = ;      wnd_names[i] := cCastleLibraryWindowName; i := i + 1;
      [*] = ;      wnd_names[i] := cCastleBuildingsWindow2Name; i := i + 1;
      [*] = ;      n := i;
      [*] = ;
      [*] = ;      for i := 0 to n-1 do
      [*] = ;      begin
      [*] = ;         whd := _gui_GetWindow(wnd_names[i]);
      [*] = ;         if  (whd <> 0) then
      [*] = ;         begin
      [*] = ;            if i = (n-1) then
      [*] = ;               i := 0;
      [*] = ;            Result := i;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure PostToEvent(tag : Integer; state_name : String);
      [*] = ;begin
      [*] = ;   SetIntValueByName('Tag',tag);
      [*] = ;   GUIExecuteState(state_name);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetHeroUIDFromExtraAttr(extra_attr : String) : Integer;
      [*] = ;begin
      [*] = ;   if _sa_GetAsInt(extra_attr,0) <> 0 then
      [*] = ;      Result := _sa_GetAsInt(extra_attr,1)
      [*] = ;   else
      [*] = ;      Result := gIntRegister_GUIActiveHeroUID1;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var cname : String = StringRegister0;
      [*] = ;var cattr : String = StringRegister1;
      [*] = ;var sattr : String = StringRegister2;
      [*] = ;var extra_attr : String = StringRegister3;
      [*] = ;var res: Integer;
      [*] = ;var ret_s : String = '';
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if (GetGUIFocusedElementHandle()<>0) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   IntRegister2 := 0;
      [*] = ;   StringRegister0 := '';
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log and (mode=0) then _Log_gui('CMD: '+cname+', MODE: '+IntToStr(mode));
      [*] = ;res := 1;
      [*] = ;case StrToLowerCase(cname) of
      [*] = ;   // map related commands
      [*] = ;   'mapshowmenu' : begin
      [*] = ;      res := 0;
      [*] = ;      if (gIntRegister_GUICurCastleMode = 0) or (extra_attr <> '') then
      [*] = ;      begin
      [*] = ;         res := 1;
      [*] = ;         if (mode = 0) then
      [*] = ;         begin
      [*] = ;            if _gui_GetWindow('ingame_menu') <> 0 then
      [*] = ;               _cmd_Post('menumainbutton','continue','')
      [*] = ;            else
      [*] = ;               GUIExecuteState('ShowMenu');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapshowsettings' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;      begin
      [*] = ;         if _gui_GetWindow('Settings') = 0 then
      [*] = ;            _gui_ShowSettingsDialog();
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapnextturn' : begin
      [*] = ;      if mode = 0 then
      [*] = ;      begin
      [*] = ;         if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;            gIntRegister_PlayBell := 1;
      [*] = ;            
      [*] = ;         var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;         var bLoafers : Boolean = False;
      [*] = ;
      [*] = ;         if (gProfile.mesloafers) and (extra_attr = '') then
      [*] = ;         begin
      [*] = ;            var i,goHandle,task : Integer;
      [*] = ;            var dead : Boolean;
      [*] = ;
      [*] = ;            for i:=GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               goHandle := GetGameObjectHandleByIndex(i,plHandle);
      [*] = ;               if (GetGameObjectRaceTag(goHandle)=gc_map_PlayerRaceTag) then
      [*] = ;               begin
      [*] = ;                  task := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask);
      [*] = ;                  dead := GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;                  if (not dead) and (task=gc_UnitTaskRest) then
      [*] = ;                  begin
      [*] = ;                     bLoafers := True;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;            
      [*] = ;         if (extra_attr = '1') or (not bLoafers) then
      [*] = ;         begin
      [*] = ;            var bBuildRemaining : Boolean = false;
      [*] = ;            
      [*] = ;            if (gProfile.mesbuildinner) and (extra_attr <> '2') and (_sa_GetNum(GetPlayerValueByHandle(plHandle, gc_map_PLStack_MapUnit_nInnerBuildingsQueue)) = 0) then
      [*] = ;            begin
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'CanInnerBuild');
      [*] = ;               bBuildRemaining := BoolRegister1;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if (not bBuildRemaining) and (gProfile.mesbuildouter) and (extra_attr <> '2') then
      [*] = ;            begin
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'CanOuterBuild');
      [*] = ;               bBuildRemaining := BoolRegister1;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if (extra_attr = '2') or (not bBuildRemaining) then
      [*] = ;            begin
      [*] = ;               if (gGame.gameType = gc_GameTypeLanShard) and (_lan_stimer_Status(gc_lt_map_start_turn) = gc_lan_timer_status_armed) then // another player has not finished battles and queries yet
      [*] = ;               begin
      [*] = ;                  gBoolRegister_LanMapTurnPassed := true;
      [*] = ;                  gArr_LanTimers[gc_lt_map_start_turn].timer := GetCurrentTime;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  IntRegister0 := gc_gui_ModeMap;
      [*] = ;                  FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;                  StringRegister0 := 'end_turn';
      [*] = ;                  GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else // can still construct message
      [*] = ;            begin
      [*] = ;               var msg : String = GetLocaleTableListItemByID('message','111')+gc_gui_BreakLine+gc_gui_BreakLine+gc_gui_BreakLine+gc_gui_BreakLine+gc_gui_BreakLine+gc_gui_BreakLine+gc_gui_BreakLine+gc_gui_BreakLine;
      [*] = ;               var elmParentHandle : Integer = _gui_ShowQuestionDialogWithFade(msg,'#mapnextturn||2', 0,'',0,False,False,5,'');
      [*] = ;               
      [*] = ;               _gui_CreateTextStrip('header', elmParentHandle, 'gui|407', 'halParentMiddle', 'valParentTop', 0, 80);
      [*] = ;               
      [*] = ;               var elmBkg : Integer = GetGUIElementIndexByNameParent('window_bkg', elmParentHandle);
      [*] = ;               var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('mesbuildinner', elmBkg, gProfile.mesbuildinner, 'gui|97', 'halParentMiddle', 'valParentTop', 0, 125, '', 'message|107.description', 0);
      [*] = ;               elmCheckBoxHandle := _gui_CreateCheckBox('mesbuildouter', elmBkg, gProfile.mesbuildouter, 'gui|56', 'halParentMiddle', 'valParentTop', 0, 145, '', 'message|107.description', 0);
      [*] = ;               
      [*] = ;               var fontHandle : String;
      [*] = ;               _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle);   // HeaderS
      [*] = ;               var elmSliderHandle : Integer = _gui_CreateSlider('mesbuildgold', gProfile.mesbuildgold, IntToStr(Round(gProfile.mesbuildgold * 100))+'% %style(Symbols)%0%style(default)%', elmBkg, 'halParentRight', 'valParentTop', 0, 175, 'map.DoOnClickGUI', 'message|109', 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;               elmSliderHandle := _gui_CreateSlider('mesbuildgem', gProfile.mesbuildgem, IntToStr(Round(gProfile.mesbuildgem * 100))+'% %style(Symbols)%1%style(default)%', elmBkg, 'halParentRight', 'valParentTop', 216, 175, 'map.DoOnClickGUI', 'message|110', 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var elmParentHandle : Integer = _gui_ShowQuestionDialogWithFade(GetLocaleTableListItemByID('map.event','390')+gc_gui_BreakLine+gc_gui_BreakLine,'#mapnextturn||1', 0,'',0,False,False,5,'');
      [*] = ;            var elmHandle : Integer = GetGUIElementIndexByNameParent('btnAcceptFrame.btnAccept', elmParentHandle);
      [*] = ;            SetGUIElementHint(elmHandle, 'map.event|390.1');
      [*] = ;            elmHandle := GetGUIElementIndexByNameParent('btnCancelFrame.btnCancel', elmParentHandle);
      [*] = ;            SetGUIElementHint(elmHandle, 'map.event|390.2');
      [*] = ;            var elmBkg : Integer = GetGUIElementIndexByNameParent('window_bkg', elmParentHandle);
      [*] = ;            var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmBkg, gProfile.mesloafers, 'gui|'+IntToStr(427+2), 'halParentMiddle', 'valParentBottomHeight', -10, -55, '', 'message|68.description', gc_gui_question_btnCheckBoxMesLoafers);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapnextturnbell' : begin
      [*] = ;      Log('mapnextturnbell');
      [*] = ;      if (gGame.gameType <> gc_GameTypeLanShard) then
      [*] = ;      begin
      [*] = ;         gIntRegister_PlayBell := 1;
      [*] = ;         _cmd_Post('mapnextturn','','');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapgotomap' : begin
      [*] = ;      if (gIntRegister_GUICurCastleMode = 0) then
      [*] = ;         res := 0
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (mode = 0) then
      [*] = ;         begin
      [*] = ;            //_gui_RemoveBlinkElement('btnCastleClose', gBoolRegister_BtnCastleCloseBlink);
      [*] = ;            IntRegister0 := gc_gui_ModeMap;
      [*] = ;            StringRegister0 := '';
      [*] = ;            FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;            GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapgotocastle' : begin
      [*] = ;      if (gIntRegister_GUICurCastleMode <> 0) then
      [*] = ;         res := 0
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (gIntRegister_CurGameMode = gc_GameModeTactics) or (IsUnderSiege(GetPlayerHandleInterfaceIO())) then
      [*] = ;            res := 2;
      [*] = ;
      [*] = ;         if (res <> 2) and (mode = 0) then
      [*] = ;         begin
      [*] = ;            //_gui_RemoveBlinkElement('btnCastle', gBoolRegister_BtnCastleBlink);
      [*] = ;            IntRegister0 := gc_gui_ModeCastle;
      [*] = ;            StringRegister0 := '0';
      [*] = ;            FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;            GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'maprituals' : begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;      var ritCount : Integer;
      [*] = ;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetRitualCount');
      [*] = ;      ritCount := IntRegister0;
      [*] = ;
      [*] = ;      if (ritCount = 0) then
      [*] = ;         res := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCanCast) = 0) then
      [*] = ;            res := (1 or (_sa_GetAsInt(extra_attr,0) shl 8));
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (mode = 0) and ((res and $ff) = 1) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_gui_ModeMap;
      [*] = ;         FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;         StringRegister0 := 'ritual';
      [*] = ;         GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapalchemy' : begin
      [*] = ;      IntRegister0 := 34; // !!!
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'CheckInnerBuildAbility');
      [*] = ;      if (IntRegister1 = 0) then
      [*] = ;         res := 2
      [*] = ;      else
      [*] = ;         res := 1;
      [*] = ;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;      begin
      [*] = ;         gFloatRegister_AlchemySlider := 0.5;
      [*] = ;         GUIExecuteState('map.CreateAlchemy');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapnexthero' : begin
      [*] = ;      var isHeroAvailable : Boolean = False;
      [*] = ;      var i,goHnd : Integer;
      [*] = ;      var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;      for i := 0 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;      begin
      [*] = ;         goHnd := GetGameObjectHandleByIndex(i,plHandle);
      [*] = ;         if (not GetGameObjectBoolValueIndByHandle(goHnd,gc_map_GOStack_MapUnit_bIsDead)) then
      [*] = ;         begin
      [*] = ;            isHeroAvailable := True;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (not isHeroAvailable) then
      [*] = ;         res := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if mode = 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_gui_ModeMap;
      [*] = ;            FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;            StringRegister0 := 'next_hero';
      [*] = ;            GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;            if gBoolRegister_BtnNextHeroBlink then
      [*] = ;            _gui_RemoveBlinkElement('btnNextHero', gBoolRegister_BtnNextHeroBlink);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapdiplomacy' : begin
      [*] = ;      if (gc_demoVersion <> 1) and (gGame.diplomacy = true) then
      [*] = ;      begin
      [*] = ;         var plIndex, plHandle, treaty : Integer;
      [*] = ;         var myPlIndex : Integer = GetPlayerIndexByHandle(GetPlayerHandleInterfaceIO());
      [*] = ;
      [*] = ;         res := 2;
      [*] = ;         for plIndex := 0 to gGame.map.players-1 do
      [*] = ;         begin
      [*] = ;            if plIndex <> myPlIndex then
      [*] = ;            begin
      [*] = ;               plHandle := GetPlayerHandleByIndex(plIndex);
      [*] = ;               var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;               var plProfileID : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;               treaty := gArrDiplomacy[plIndex][myPlIndex].treaty;
      [*] = ;               if (treaty<>0) and (SameText(cMode, 'cmPlayer') or (plProfileID>0)) and (_plr_IsInGame(plHandle)) then
      [*] = ;               begin
      [*] = ;                  res := 1;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (mode = 0) and (res = 1) then
      [*] = ;         begin
      [*] = ;            if _misc_GetTutorialHintStatus = gc_Tutorial_HintEnabled then
      [*] = ;              GUIExecuteState('DestroyTutorial');
      [*] = ;            
      [*] = ;            // check if there is a new offer to display, and display it immediately when opening the window.
      [*] = ;            var highestPriority, displayPriority : Integer = 0;
      [*] = ;            var showReplyMyProposal : Boolean = false;
      [*] = ;            for plIndex := 0 to gGame.map.players-1 do
      [*] = ;            begin
      [*] = ;               if plIndex <> myPlIndex then
      [*] = ;               begin
      [*] = ;                  displayPriority := gArrDiplomacy[plIndex][myPlIndex].displayPriority;
      [*] = ;                  if displayPriority > highestPriority then
      [*] = ;                  begin
      [*] = ;                     highestPriority := displayPriority;
      [*] = ;                     gIntRegister_DiplomacyActivePlayerID := plIndex;
      [*] = ;                     if (displayPriority and $ff00) > 0 then // reply to my proposal
      [*] = ;                        showReplyMyProposal := true;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if gBoolRegister_BtnDiplomacyBlink then
      [*] = ;               _gui_RemoveBlinkElement('btnDiplomacy', gBoolRegister_BtnDiplomacyBlink);
      [*] = ;            
      [*] = ;            if (gIntRegister_DiplomacyActivePlayerID > -1) and (highestPriority > 0) then
      [*] = ;            begin
      [*] = ;               if showReplyMyProposal and (gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message.deal < 0) then // they have refused my proposal
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 1 // display current trade situation with the other player
      [*] = ;               else
      [*] = ;               if showReplyMyProposal then // they have accepted my proposal
      [*] = ;               begin 
      [*] = ;                  _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message.tradeGive);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[myPlIndex][gIntRegister_DiplomacyActivePlayerID].message.tradeTake);
      [*] = ;                  
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 3;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin  // display proposal of another player
      [*] = ;                  _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[gIntRegister_DiplomacyActivePlayerID][myPlIndex].message);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[gIntRegister_DiplomacyActivePlayerID][myPlIndex].message.tradeGive);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[gIntRegister_DiplomacyActivePlayerID][myPlIndex].message.tradeTake);
      [*] = ;                  
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 4;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               gIntRegister_DiplomacyWindowMode := 0; // display default screen
      [*] = ;            
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;   end;
      [*] = ;   'mapstatistics' : begin
      [*] = ;      if mode = 0 then
      [*] = ;      begin
      [*] = ;         if gBoolRegister_BtnStatisticsBlink then
      [*] = ;            _gui_RemoveBlinkElement('btnStatistics', gBoolRegister_BtnStatisticsBlink);
      [*] = ;         BoolRegister0 := false;
      [*] = ;         GUIExecuteState('map.CreateStatistics');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapprovincelist' : begin
      [*] = ;      if mode = 0 then
      [*] = ;      begin
      [*] = ;         gIntRegister_GUIProvinceListSortOrder := 0;
      [*] = ;         gIntRegister_GUIProvinceListSortMode := 0;
      [*] = ;         gIntRegister_GUIProvinceListStatMode := 0;
      [*] = ;         GUIExecuteState('map.CreateProvinceList');
      [*] = ;         _misc_UpdateCastleCameraPosition(0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapcancelritual' : begin
      [*] = ;      if (gIntRegister_MapPickedRitualID<>0) then
      [*] = ;      begin
      [*] = ;         if mode = 0 then
      [*] = ;         begin
      [*] = ;            var elmHudProvHandle : Integer = _gui_GetLayer(cHUDStrategyProvLayer);
      [*] = ;
      [*] = ;            gIntRegister_MapPickedRitualID := 0;
      [*] = ;
      [*] = ;            IntRegister0 := 5; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;            IntRegister1 := 0; //0 - hide
      [*] = ;            ExecuteState('DoDragElement');
      [*] = ;
      [*] = ;            if (elmHudProvHandle<>0) then
      [*] = ;               SetGUIElementVisible(elmHudProvHandle, True);
      [*] = ;            ExecuteState('GUIInvokeMouseMove');
      [*] = ;            ExecuteState('map.UpdateCursor');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      res := 0;
      [*] = ;   end;
      [*] = ;   'mapscrolltocastle' : begin
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;      begin
      [*] = ;         PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'GetCastleParser');
      [*] = ;         var pCastle : Integer = IntRegister0;
      [*] = ;         var lastPlayer : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'LastPlayer');
      [*] = ;         var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         if lastPlayer = 0 then
      [*] = ;         begin
      [*] = ;            SetCameraInfoSmoothingChange(True);
      [*] = ;            _misc_SetCameraTarget(dummyHandle);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;   end;
      [*] = ;   'mapterrainmenu' : begin
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;      begin
      [*] = ;         if mode = 0 then
      [*] = ;         begin
      [*] = ;            var elmName : String = '';
      [*] = ;            var ehd : Integer;
      [*] = ;
      [*] = ;            ehd := GetGUIElementUnderMouse();
      [*] = ;            if (ehd<>0) then
      [*] = ;               elmName := GetGUIElementNameByIndex(ehd);
      [*] = ;
      [*] = ;            if (ehd=0) or SameText(elmName, 'hud_res') or StrExists(elmName, 'provhud') then
      [*] = ;            begin
      [*] = ;               var X, Y, Z : Float;
      [*] = ;               var mx,my : Integer;
      [*] = ;
      [*] = ;               GetGUICurrentMouseCoord(mx,my); // engine bug workaround
      [*] = ;               ScreenToWorldRayCast(mx,my,x,y,z);
      [*] = ;               //GetCurrentMouseWorldCoord(X,Y,Z);
      [*] = ;
      [*] = ;               FloatRegister0 := x;
      [*] = ;               FloatRegister1 := z;
      [*] = ;               MapExecuteState('map.GetHexByCoord');
      [*] = ;               var pStratHexCell : Integer = IntRegister0;
      [*] = ;               var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;               var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;               var bAvailable : Boolean = False;
      [*] = ;               //_log_values('PH|SHEX|UHEX|X|Z',pStratHexCell,gIntRegister_MapSelectedHex,gIntRegister_MapUnderCursorHex,round(x),round(z),0);
      [*] = ;               if dummyHandle <> 0 then
      [*] = ;               begin
      [*] = ;                  var fog : Integer = ParserGetIntValueByIndexByHandle(ParserSelectByHandleByKey(pStratHexCell, 'Fog'), gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;                  GameObjectExecuteStateByHandle(dummyHandle, 'IsPlayable');
      [*] = ;                  if BoolRegister0 and ((fog = 0) or (fog = 1) or (not gGame.fog)) then
      [*] = ;                     bAvailable := True;
      [*] = ;               end;
      [*] = ;
      [*] = ;               SetSelection(pStratHexCell);
      [*] = ;               if (GetIntValueByName('CurProvHUDParser')=gIntRegister_MapSelectedHex) then
      [*] = ;               begin
      [*] = ;                  BoolRegister0 := True;
      [*] = ;                  ExecuteState('map.CloseProvRadialWindow');
      [*] = ;                  ExecuteState('GUIInvokeMouseMove');
      [*] = ;                  SetGuiIntValue('CurProvHUDParser', 0);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if bAvailable then
      [*] = ;                  begin
      [*] = ;                     if (GetIntValueByName('CurProvHUDParser')<>0) then
      [*] = ;                     begin
      [*] = ;                        SetBoolValueByName('KeyPressedAlt', False);
      [*] = ;                        BoolRegister0 := True;
      [*] = ;                        ExecuteState('map.CloseProvRadialWindow');
      [*] = ;                        ExecuteState('GUIInvokeMouseMove');
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     IntRegister0 := gIntRegister_MapSelectedHex;
      [*] = ;                     ExecuteState('map.GUIUpdateProvHUD');
      [*] = ;                     var provHUDHandle : Integer = IntRegister1;
      [*] = ;                     if (provHUDHandle<>0) then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := gIntRegister_MapSelectedHex;
      [*] = ;                        BoolRegister0 := true;
      [*] = ;                        gBoolRegister_GUIProvRadialPlaceInCenter := True;
      [*] = ;                        ExecuteState('map.CreateProvRadialWindow');
      [*] = ;                        SetGuiIntValue('CurProvHUDParser', gIntRegister_MapSelectedHex);
      [*] = ;                        ExecuteState('GUIInvokeMouseMove');
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;   end;
      [*] = ;   'mapapplyritual' : begin
      [*] = ;      if (mode = 0) and (gIntRegister_MapPickedRitualID <> 0) then
      [*] = ;      begin
      [*] = ;         var pProvFog : Integer = ParserSelectByHandleByKey(gIntRegister_MapUnderCursorHex, 'Fog');
      [*] = ;         var fog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;         if (not gGame.fog) or (fog < 2) then
      [*] = ;         begin
      [*] = ;            if (gIntRegister_MapPickedRitualID<0) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := gIntRegister_MapUnderCursorHex;
      [*] = ;               IntRegister1 := -gIntRegister_MapPickedRitualID;
      [*] = ;               PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'UncastRitual');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var dummyUID : Integer = ParserGetIntValueByKeyByHandle(gIntRegister_MapUnderCursorHex, 'DummyUID');
      [*] = ;               var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;               IntRegister0 := gIntRegister_MapPickedRitualID;
      [*] = ;               IntRegister1 := GetPlayerHandleInterfaceIO();
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'CanCastRitual');
      [*] = ;               if (BoolRegister0) then
      [*] = ;               begin
      [*] = ;                  var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(gIntRegister_MapUnderCursorHex, 'DummyUID'));
      [*] = ;                  var heroCount,heroHandle : Integer;
      [*] = ;
      [*] = ;                  gIntRegister_MapSelectedHex := gIntRegister_MapUnderCursorHex;
      [*] = ;                  if ParserGetBoolValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.rituals.handle, gIntRegister_MapPickedRitualID), 'OnHero') then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := GetPlayerHandleInterfaceIO();
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'GetHeroesData');
      [*] = ;                     heroHandle := IntRegister1;
      [*] = ;                     heroCount := IntRegister2;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     heroCount := 0;
      [*] = ;
      [*] = ;                  if (heroCount > 1) then
      [*] = ;                  begin
      [*] = ;                     gIntRegister_GUIMapChooseHeroProvince := gIntRegister_MapSelectedHex;
      [*] = ;                     gBoolRegister_GUIMapShowChooseDefender := false;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     _gui_PlaySound('rituals', 'ritual'+IntToStr(gIntRegister_MapPickedRitualID));
      [*] = ;                     IntRegister0 := gIntRegister_MapSelectedHex;
      [*] = ;                     IntRegister1 := gIntRegister_MapPickedRitualID;
      [*] = ;                     IntRegister2 := GetGameObjectUniqueIdByHandle(heroHandle);
      [*] = ;                     PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'CastRitual');
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  IntRegister0 := 5; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;                  IntRegister1 := 0; //0 - hide
      [*] = ;                  GUIExecuteState('DoDragElement');
      [*] = ;
      [*] = ;                  gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;                  GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'mapcancelritual' : begin
      [*] = ;      if (mode = 0) and (gIntRegister_MapPickedRitualID <> 0) then
      [*] = ;      begin
      [*] = ;         gIntRegister_MapPickedRitualID := 0;
      [*] = ;
      [*] = ;         IntRegister0 := 5; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;         IntRegister1 := 0; //0 - hide
      [*] = ;         GUIExecuteState('DoDragElement');
      [*] = ;         GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   '.mapshowminimap' : begin
      [*] = ;      if gIntRegister_GUICurCastleMode <> 0 then
      [*] = ;         res := 2;
      [*] = ;      if (res <> 2) and (mode = 0) then
      [*] = ;      begin
      [*] = ;         var ehd : Integer;
      [*] = ;         var cmode : Integer = _sa_GetAsInt(cattr,0);
      [*] = ;
      [*] = ;         ehd := _gui_GetWindow(cMapMiniMapWindowName);
      [*] = ;         case cmode of
      [*] = ;            -2 : begin
      [*] = ;               IntRegister0 := gIntRegister_MapMyPlayerIndex;
      [*] = ;               MapExecuteState('map.vvk.GenerateMiniMap');
      [*] = ;               if (ehd<>0) and (GetGUIElementStringTag(ehd) <> 'min') then
      [*] = ;                  IntRegister0 := 0
      [*] = ;               else
      [*] = ;                  IntRegister0 := 1;
      [*] = ;            end;
      [*] = ;            -1 : begin
      [*] = ;               if (ehd=0) or (GetGUIElementStringTag(ehd) <> 'min') then
      [*] = ;                  IntRegister0 := 1
      [*] = ;               else
      [*] = ;                  IntRegister0 := 0;
      [*] = ;            end;
      [*] = ;            0 : IntRegister0 := cmode;
      [*] = ;            1 : IntRegister0 := cmode;
      [*] = ;            2 : IntRegister0 := -1;
      [*] = ;         end;
      [*] = ;         GUIExecuteState('VVK.map.ShowMiniMap');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   // end of map commands
      [*] = ;   // castle related commands
      [*] = ;   'castlebuild' : begin
      [*] = ;      if (IsUnderSiege(GetPlayerHandleInterfaceIO())) then
      [*] = ;        res := 2;
      [*] = ;      if (res <> 2) and (mode = 0) then
      [*] = ;      begin
      [*] = ;         var temp_str, temp_str2 : String;
      [*] = ;         var i : Integer;
      [*] = ;
      [*] = ;         // force simple build mode
      [*] = ;         temp_str := '';
      [*] = ;         _sa_AddAsInt(temp_str,0);
      [*] = ;         for i := 1 to _sa_GetNum(gStrRegister_GUIBuildWindowState)-1 do
      [*] = ;         begin
      [*] = ;            _sa_Get(gStrRegister_GUIBuildWindowState,i,temp_str2);
      [*] = ;            _sa_Add(temp_str,temp_str2);
      [*] = ;         end;
      [*] = ;         gStrRegister_GUIBuildWindowState := temp_str;
      [*] = ;
      [*] = ;         if (gMapEditor.enabled) then
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;            SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCanOuterBuild, 1000);
      [*] = ;            SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCanInnerBuild, 1000);
      [*] = ;            SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCanHire, 1000);
      [*] = ;            SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, 100000);
      [*] = ;            SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, 100000);
      [*] = ;         end;
      [*] = ;
      [*] = ;         IntRegister0 := gc_gui_ModeCastle;
      [*] = ;         FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;         StringRegister0 := '1';
      [*] = ;         // mode(0,1,-1)|build window panel(0,1,2)|scale(0,1)|close button(0,1)
      [*] = ;         //if gIntRegister_GUICurCastleMode <> 0 then
      [*] = ;         //begin
      [*] = ;            //   //if (_gui_GetWindow(cCastleBuildingsWindow2Name) <> 0) or (_gui_GetWindow(cCastleBuildingsWindowName) <> 0) then
      [*] = ;            //   //   StringRegister0 := '0'
      [*] = ;            //   //else
      [*] = ;         //end;
      [*] = ;         //else
      [*] = ;         //   StringRegister0 := 'inner_build|-1';
      [*] = ;         GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;      end;
      [*] = ;      if (mode = 1) and ( extra_attr <> '') then
      [*] = ;      begin
      [*] = ;         //_log_Values('CM|CW1|CW2',GetCastleMode(),_gui_GetWindow(cCastleBuildingsWindow2Name),_gui_GetWindow(cCastleBuildingsWindowName),0,0,0);
      [*] = ;         if GetCastleMode() = 0 then
      [*] = ;            res := (res or $200);
      [*] = ;         if GetPlayerIntValueIndByHandle(GetPlayerHandleInterfaceIO(),gc_map_PLStack_MapUnit_iCanInnerBuild)<=0 then
      [*] = ;            res := (res or $100);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'castleheroes' : begin
      [*] = ;      if (IsUnderSiege(GetPlayerHandleInterfaceIO)) or ((gScenario.enabled) and (not GetPlayerBoolValueIndByHandle(GetPlayerHandleInterfaceIO, gc_map_PLStack_MapUnit_bAllowHireHero))) then
      [*] = ;        res := 2;
      [*] = ;      if (res <> 2) and (mode = 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_gui_ModeCastle;
      [*] = ;         FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;         StringRegister0 := '3';
      [*] = ;         GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;      end;
      [*] = ;      if (mode = 1) and ( extra_attr <> '') then
      [*] = ;      begin
      [*] = ;         if GetCastleMode() = 2 then
      [*] = ;            res := (res or $200);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'castlelibrary' : begin
      [*] = ;      if (IsUnderSiege(GetPlayerHandleInterfaceIO())) then
      [*] = ;        res := 2;
      [*] = ;      if (res <> 2) then
      [*] = ;      begin
      [*] = ;         var pProvSpells,i,j,pLevelSpells,pLevelSpell : Integer;
      [*] = ;         var bSpellsAvailable : Boolean = False;
      [*] = ;         var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;         pProvSpells := ParserSelectByHandleByKey(IntRegister0, 'SpellLevels');
      [*] = ;
      [*] = ;         for [MAIN]i:=0 to ParserGetCountByHandle(pProvSpells)-1 do
      [*] = ;         begin
      [*] = ;            pLevelSpells := ParserSelectByHandleByIndex(pProvSpells,i);
      [*] = ;            pLevelSpells := ParserSelectByHandleByKey(pLevelSpells, 'Spells');
      [*] = ;
      [*] = ;            for j:=0 to ParserGetCountByHandle(pProvSpells)-1 do
      [*] = ;            begin
      [*] = ;               pLevelSpell := ParserSelectByHandleByIndex(pLevelSpells, j);
      [*] = ;               if (ParserGetIntValueByKeyByHandle(pLevelSpell, 'SpellID') > 0) then
      [*] = ;               begin
      [*] = ;                  bSpellsAvailable := True;
      [*] = ;                  break(MAIN);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (not bSpellsAvailable) then
      [*] = ;            res := 2
      [*] = ;      end;
      [*] = ;      if (res <> 2) and (mode = 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_gui_ModeCastle;
      [*] = ;         FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;         StringRegister0 := '5';
      [*] = ;         GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;      end;
      [*] = ;      if (mode = 1) and ( extra_attr <> '') then
      [*] = ;      begin
      [*] = ;         if GetCastleMode() = 4 then
      [*] = ;            res := (res or $200);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'castletreasury' : begin
      [*] = ;      if (IsUnderSiege(GetPlayerHandleInterfaceIO())) then
      [*] = ;        res := 2;
      [*] = ;      if (res <> 2) and (mode = 0) then
      [*] = ;      begin
      [*] = ;         gBoolRegister_RepairItemMode := False;
      [*] = ;         gIntRegister_GUIShopSortMode := 0;
      [*] = ;         IntRegister0 := gc_gui_ModeCastle;
      [*] = ;         FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;         StringRegister0 := '4';
      [*] = ;         GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;      end;
      [*] = ;      if (mode = 1) and ( extra_attr <> '') then
      [*] = ;      begin
      [*] = ;         if GetCastleMode() = 3 then
      [*] = ;            res := (res or $200);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'castlegarrison' : begin
      [*] = ;      if (IsUnderSiege(GetPlayerHandleInterfaceIO())) then
      [*] = ;        res := 2;
      [*] = ;      if (res <> 2) and (mode = 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_gui_ModeCastle;
      [*] = ;         FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;         StringRegister0 := '2';
      [*] = ;         GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;      end;
      [*] = ;      if (mode = 1) and ( extra_attr <> '') then
      [*] = ;      begin
      [*] = ;         if GetCastleMode() = 1 then
      [*] = ;            res := (res or $200);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   // end of castle commands
      [*] = ;   // hero related commands
      [*] = ;   'heroexchange' : begin
      [*] = ;   end;
      [*] = ;   'herohiretroops' : begin
      [*] = ;   end;
      [*] = ;   'herovisitstores' : begin
      [*] = ;   end;
      [*] = ;   'herospellbook' : begin
      [*] = ;      var f,uid : Integer;
      [*] = ;
      [*] = ;      uid := GetHeroUIDFromExtraAttr(extra_attr);
      [*] = ;      f := GetGSLFlags(GetGameObjectHandleByUniqueId(uid));
      [*] = ;      if ((f and $4) = 0) then
      [*] = ;         res := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (((f and $20) <> 0) or (GetCastleMode() <> -1)) and (_cmd_CheckNF('castlelibrary','','') <> 1) then
      [*] = ;            res := 2;
      [*] = ;      end;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;      begin
      [*] = ;         if ((f and $20) <> 0) or (GetCastleMode() <> -1) then
      [*] = ;            _cmd_Post('castlelibrary','','')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            GUIExecuteState('map.CloseHeroWindow');
      [*] = ;            gIntRegister_GUICurHeroMode := gc_HeroPanelSpellbook;
      [*] = ;            gIntRegister_GUIActiveHeroUID1 := uid;
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'herosquad' : begin
      [*] = ;      var f,uid : Integer;
      [*] = ;
      [*] = ;      uid := GetHeroUIDFromExtraAttr(extra_attr);
      [*] = ;      f := GetGSLFlags(GetGameObjectHandleByUniqueId(uid));
      [*] = ;      if ((f and 1) = 0) then
      [*] = ;         res := 2;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;      begin
      [*] = ;         gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;         if ((f and $20) <> 0) or (GetCastleMode() <> -1) then
      [*] = ;            _cmd_Post('castlegarrison','','')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            GUIExecuteState('map.CloseSpellWindow');
      [*] = ;            GUIExecuteState('map.CloseShopWindow');
      [*] = ;            gIntRegister_GUIActiveHeroUID1 := uid;
      [*] = ;            gIntRegister_GUICurHeroMode := gc_HeroPanelUnitsOnly;
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'heroinventory' : begin
      [*] = ;      var f,uid : Integer;
      [*] = ;
      [*] = ;      uid := GetHeroUIDFromExtraAttr(extra_attr);
      [*] = ;      f := GetGSLFlags(GetGameObjectHandleByUniqueId(uid));
      [*] = ;      if ((f and $2) = 0) then
      [*] = ;         res := 2;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;      begin
      [*] = ;         var elmScrollLayer : Integer = _gui_GetWindow('map_shoppanel.map_shoppanel_bg.map_shoppanel_items.scroll_layer');
      [*] = ;
      [*] = ;         if (elmScrollLayer<>0) then
      [*] = ;         begin
      [*] = ;            var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;            if (elmVScroll<>0) then
      [*] = ;               SetGUIScrollBarPosition(elmVScroll, 0);
      [*] = ;         end;
      [*] = ;
      [*] = ;         gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;         if ((f and $20) <> 0) or (GetCastleMode() <> -1) then
      [*] = ;            _cmd_Post('castletreasury','','')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            GUIExecuteState('map.CloseUnitsWindow');
      [*] = ;            GUIExecuteState('map.CloseSpellWindow');
      [*] = ;            gBoolRegister_RepairItemMode := False;
      [*] = ;            gIntRegister_GUIShopSortMode := 0;
      [*] = ;            gIntRegister_GUIActiveHeroUID1 := uid;
      [*] = ;            gIntRegister_GUICurHeroMode := gc_HeroPanelInventory;
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'heroinfo' : begin
      [*] = ;      var f,uid : Integer;
      [*] = ;
      [*] = ;      uid := GetHeroUIDFromExtraAttr(extra_attr);
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;      begin
      [*] = ;         gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         ExecuteState('map.CloseHeroWindow');
      [*] = ;         gIntRegister_GUICurHeroMode := gc_HeroPanelBothPanels;
      [*] = ;         gIntRegister_GUIActiveHeroUID1 := uid;
      [*] = ;         GUIExecuteState('map.CreateHeroWindow');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'herodismiss' : begin
      [*] = ;      var hero_uid : Integer = _sa_GetAsInt(extra_attr,0);
      [*] = ;      var whd : Integer;
      [*] = ;
      [*] = ;      if _log then _log_Values('UID|EXTRA|MODE',hero_uid,_sa_GetAsInt(extra_attr,1),mode,0,0,0);
      [*] = ;      if (mode = 0) and (hero_uid <> 0) then
      [*] = ;      begin
      [*] = ;         _hero_GetName(GetGameObjectHandleByUniqueId(hero_uid), gStringRegister_MyHeroName);
      [*] = ;         if _sa_GetAsInt(extra_attr,1) <> 0 then
      [*] = ;         begin
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('map.CloseHeroWindow');
      [*] = ;
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByUniqueId(hero_uid);
      [*] = ;            var dummyUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;            IntRegister0 := goHandle;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            BoolRegister1 := false;
      [*] = ;            PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'KillHero');
      [*] = ;
      [*] = ;            IntRegister0 := dummyUID;
      [*] = ;            ExecuteState('map.DoHeroDismissUpdateGUI');
      [*] = ;            if (gIntRegister_GUICurCastleMode=1) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 2;
      [*] = ;               ExecuteState('map.CreateCastleBuildWindow');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gBoolRegister_RepairItemMode := False;
      [*] = ;            whd := _gui_ShowQuestionDialog('map.event|28', '#herodismiss||'+IntToStr(hero_uid)+'|1',0 , '', 0, true, false);
      [*] = ;            _gui_AlignQuestionDialog((gIntRegister_GUICurCastleMode=0), false, 640, 920, (gIntRegister_GUIActiveHeroUID1<>0), true);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'heroexplore' : begin
      [*] = ;      res := 1;
      [*] = ;   end;
      [*] = ;   'heroplunder' : begin
      [*] = ;   // extra_attr
      [*] = ;   // returns result in string so you should use CheckExt command
      [*] = ;   // [0] - mode
      [*] = ;   //       1 - get pillage related data
      [*] = ;   //         RET[0] - availability flags
      [*] = ;   //                  &0x01 - can be pillaged
      [*] = ;   //                  &0x10 - hero and game mode is valid
      [*] = ;   //         RET[1] - population value
      [*] = ;   // [1] - hero UID or 0 for gIntRegister_MapSelectedUID
      [*] = ;      var e_mode,flags,pop,hero_p : Integer;
      [*] = ;
      [*] = ;      res := 2;
      [*] = ;
      [*] = ;      e_mode := _sa_GetAsInt(extra_attr,0);
      [*] = ;      flags := 0;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;         hero_p := _sa_GetAsInt(extra_attr,1)
      [*] = ;      else
      [*] = ;         hero_p := 0;
      [*] = ;
      [*] = ;      if hero_p = 0 then
      [*] = ;         hero_p := gIntRegister_MapSelectedUID;
      [*] = ;
      [*] = ;      if hero_p <> 0 then
      [*] = ;         hero_p := GetGameObjectHandleByUniqueId(hero_p);
      [*] = ;
      [*] = ;      if hero_p <> 0 then
      [*] = ;      begin
      [*] = ;         flags := flags or $10;
      [*] = ;
      [*] = ;         pop := ParserGetIntValueByKeyByHandle(_misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(hero_p, gc_map_GOStack_MapUnit_iCurrentUID)), 'Population');
      [*] = ;         if pop > 0 then
      [*] = ;            flags := flags or 1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         pop := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         _sa_AddAsInt(ret_s,flags);
      [*] = ;         _sa_AddAsInt(ret_s,pop);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((flags and $11) = $11) then
      [*] = ;         res := 1;
      [*] = ;
      [*] = ;      if (mode=0) and (res=1) then
      [*] = ;      begin
      [*] = ;         SetGameObjectIntValueIndByHandle(hero_p,gc_map_GOStack_MapUnit_iTask, 3);
      [*] = ;         IntRegister0 := hero_p;
      [*] = ;         GUIExecuteState('map.HeroHUDControlTask');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'heroattackguard' : begin
      [*] = ;   // extra_attr
      [*] = ;   // returns result in string so you should use CheckExt command
      [*] = ;   // [0] - mode
      [*] = ;   //       1 - get availability bit mask
      [*] = ;   //         RET[0]
      [*] = ;   //           &0x01 - guard can be attacked
      [*] = ;   //           &0x10 - hero and game mode is valid
      [*] = ;   //         RET[1]  - guard id to attack
      [*] = ;   // [1] - hero object UID or 0 for gIntRegister_MapSelectedUID
      [*] = ;      var e_mode,flags,def_id,hero_p : Integer;
      [*] = ;
      [*] = ;      res := 2;
      [*] = ;
      [*] = ;      e_mode := _sa_GetAsInt(extra_attr,0);
      [*] = ;      flags := 0;
      [*] = ;      def_id := 0;
      [*] = ;      hero_p := 0;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;         hero_p := _sa_GetAsInt(extra_attr,1);
      [*] = ;
      [*] = ;      if hero_p = 0 then
      [*] = ;         hero_p := gIntRegister_MapSelectedUID;
      [*] = ;
      [*] = ;      if _log then _Log_values('UID|HANDLE',hero_p,GetGameObjectHandleByUniqueId(hero_p),0,0,0,0);
      [*] = ;      if hero_p <> 0 then
      [*] = ;         hero_p := GetGameObjectHandleByUniqueId(hero_p);
      [*] = ;
      [*] = ;      if hero_p <> 0 then
      [*] = ;      begin
      [*] = ;         var f : Integer;
      [*] = ;         var temp_str : String;
      [*] = ;
      [*] = ;         flags := flags or $10;
      [*] = ;
      [*] = ;         temp_str := '';
      [*] = ;         _sa_AddAsInt(temp_str,1);
      [*] = ;         _sa_AddAsInt(temp_str,_misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(hero_p, gc_map_GOStack_MapUnit_iCurrentUID)));
      [*] = ;
      [*] = ;         f := _cmd_CheckExtNF('provincehireguard','',temp_str,temp_str);
      [*] = ;         if (f = 1) and ((_sa_GetAsInt(temp_str,0) and 1) <> 0) then
      [*] = ;         begin
      [*] = ;            flags := flags or 1;
      [*] = ;            def_id := _sa_GetAsInt(temp_str,1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         _sa_AddAsInt(ret_s,flags);
      [*] = ;         _sa_AddAsInt(ret_s,def_id);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((flags and $11) = $11) then
      [*] = ;         res := 1;
      [*] = ;
      [*] = ;      if (mode=0) and (res=1) then
      [*] = ;      begin
      [*] = ;         SetGameObjectIntValueIndByHandle(hero_p, gc_map_GOStack_MapUnit_iTask, 6);
      [*] = ;         IntRegister0 := hero_p;
      [*] = ;         GUIExecuteState('map.HeroHUDControlTask');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'herocancelorder' : begin
      [*] = ;   // extra_attr
      [*] = ;   // returns result in string so you should use CheckExt command
      [*] = ;   // [0] - mode
      [*] = ;   //       1 - get availability bit mask
      [*] = ;   //         RET[0] - see GetGSLFlags
      [*] = ;   // [1] - hero object uid or 0 for gIntRegister_MapSelectedUID
      [*] = ;   // [2] - set to non-zero by tutorial to pass on data through
      [*] = ;      var e_mode,flags,uid : Integer;
      [*] = ;
      [*] = ;      res := 0;
      [*] = ;      e_mode := _sa_GetAsInt(extra_attr,0);
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;         uid := _sa_GetAsInt(extra_attr,1)
      [*] = ;      else
      [*] = ;         uid := 0;
      [*] = ;
      [*] = ;      if uid = 0 then
      [*] = ;         uid := gIntRegister_MapSelectedUID;
      [*] = ;
      [*] = ;      if uid <> 0 then
      [*] = ;      begin
      [*] = ;         flags := GetGSLFlags(GetGameObjectHandleByUniqueId(uid));
      [*] = ;         if ((flags and $40) = 0) then
      [*] = ;            res := 1
      [*] = ;         else
      [*] = ;            res := 2;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         flags := flags and $ffff;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;         _sa_AddAsInt(ret_s,flags);
      [*] = ;
      [*] = ;      if (mode=0) and (res=1) then
      [*] = ;      begin
      [*] = ;         uid := GetGameObjectHandleByUniqueId(uid);
      [*] = ;         IntRegister0 := uid;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         ExecuteState('map.DoCancelOrder');
      [*] = ;
      [*] = ;         IntRegister0 := GetGameObjectIntValueIndByHandle(uid, gc_map_GOStack_MapUnit_iCurrentUID); //DummyUID - if 0, then get activeHero current UID
      [*] = ;         IntRegister1 := 0; //setActiveHeroUID - if 0, then choose first picked hero
      [*] = ;         IntRegister2 := 0; //goUIDEndPointReached
      [*] = ;         ExecuteState('map.CreateHeroMultiHUD');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'herogoto' : begin
      [*] = ;   end;
      [*] = ;   // end of hero commands
      [*] = ;   // province related commands
      [*] = ;   'provincegarrison' : begin
      [*] = ;   // extra_attr
      [*] = ;   // returns result in string so you should use CheckExt command
      [*] = ;   // [0] - mode
      [*] = ;   //       1 - get fort and garrison related data
      [*] = ;   //         RET[0] - availability flags
      [*] = ;   //                  &0x01 - castle under siege
      [*] = ;   //                  &0x02 - garrison available
      [*] = ;   //                  &0x04 - province is a castle province
      [*] = ;   //                  &0x08 - selected hero is in province
      [*] = ;   //                  &0x10 - province and game mode is valid
      [*] = ;   //         RET[1] - current fort walls strength
      [*] = ;   //         RET[2] - max fort walls strength
      [*] = ;   // [1] - province parser or 0 for gIntRegister_MapSelectedHex
      [*] = ;   // [2] - hero parser or 0 for gIntRegister_MapSelectedUID
      [*] = ;      var e_mode,province_p,flags,walls,walls_max,pr_handle,hero_p,p_uid : Integer;
      [*] = ;
      [*] = ;      res := 2;
      [*] = ;      e_mode := _sa_GetAsInt(extra_attr,0);
      [*] = ;      flags := 0;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         province_p := _sa_GetAsInt(extra_attr,1);
      [*] = ;         if province_p = 0 then province_p := gIntRegister_MapSelectedHex;
      [*] = ;         hero_p := _sa_GetAsInt(extra_attr,2);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         province_p := 0;
      [*] = ;
      [*] = ;      if province_p = 0 then
      [*] = ;         province_p := gIntRegister_MapSelectedHex;
      [*] = ;
      [*] = ;      if hero_p = 0 then
      [*] = ;         hero_p := GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;
      [*] = ;      if province_p <> 0 then
      [*] = ;      begin
      [*] = ;         p_uid := ParserGetIntValueByKeyByHandle(province_p, 'DummyUID');
      [*] = ;         pr_handle := GetGameObjectHandleByUniqueId(p_uid);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         p_uid := 0;
      [*] = ;
      [*] = ;      if (hero_p <> 0) and (p_uid <> 0) then
      [*] = ;      begin
      [*] = ;         if GetGameObjectIntValueIndByHandle(hero_p, gc_map_GOStack_MapUnit_iCurrentUID) = p_uid then
      [*] = ;            flags := flags or 8;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if province_p <> 0 then
      [*] = ;      begin
      [*] = ;         var player_name : String = ParserGetValueByKeyByHandle(province_p, 'Player');
      [*] = ;
      [*] = ;         if (player_name='') or (GetPlayerHandleByName(player_name) <> GetPlayerHandleInterfaceIO()) then
      [*] = ;            province_p := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) and (province_p <> 0) then
      [*] = ;      begin
      [*] = ;         flags := $10;
      [*] = ;         if IsUnderSiege(GetPlayerHandleInterfaceIO()) then
      [*] = ;            flags := flags or 1;
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(pr_handle, 'GetMaxFortValue');
      [*] = ;         walls_max := IntRegister0;
      [*] = ;         walls := ParserGetIntValueByKeyByHandle(province_p,'Fort');
      [*] = ;
      [*] = ;         if ParserGetBoolValueByKeyByHandle(province_p, 'Castle') then
      [*] = ;         begin
      [*] = ;            flags := flags or $4;
      [*] = ;            if _cmd_CheckNF('castlegarrison','','') = 1 then
      [*] = ;               flags := flags or $2;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            GameObjectExecuteStateByHandle(pr_handle, 'IsGarrison');
      [*] = ;            if BoolRegister0 then
      [*] = ;               flags := flags or 2;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         walls := 0;
      [*] = ;         walls_max := 0;
      [*] = ;         flags := flags and ($ffff xor $10);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         _sa_AddAsInt(ret_s,flags);
      [*] = ;         _sa_AddAsInt(ret_s,walls);
      [*] = ;         _sa_AddAsInt(ret_s,walls_max);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((flags and $13) = $12) then
      [*] = ;         res := 1;
      [*] = ;
      [*] = ;      if (mode=0) and (res=1) then
      [*] = ;      begin
      [*] = ;         if ((flags and 4) <> 0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_gui_ModeCastle;
      [*] = ;            FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;            StringRegister0 := '2';
      [*] = ;            GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if ((flags and 8) <> 0) then
      [*] = ;            begin
      [*] = ;               gIntRegister_GUICurHeroMode := gc_HeroPanelUnitsOnly;
      [*] = ;               GUIExecuteState('map.CreateHeroWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               BoolRegister0 := True;
      [*] = ;               GUIExecuteState('map.CreateGarrisonWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'provincebuild' : begin
      [*] = ;   // extra_attr
      [*] = ;   // returns result in string so you should use CheckExt command
      [*] = ;   // [0] - mode
      [*] = ;   //       1 - get outer buildings related data
      [*] = ;   //         RET[0] - availability flags
      [*] = ;   //                  &0x01 - castle under siege
      [*] = ;   //                  &0x02 - already built this turn
      [*] = ;   //                  &0x04 - no free slots in province
      [*] = ;   //                  &0x08 - province is a castle province
      [*] = ;   //                  &0x10 - province and game mode is valid
      [*] = ;   //         RET[1] - max number of slots
      [*] = ;   //         RET[2] - number of free slots
      [*] = ;   // [1] - province parser or 0 for gIntRegister_MapSelectedHex
      [*] = ;   // [2] - hero parser or 0 if no hero
      [*] = ;      var i,id,e_mode,province_p,pl_handle,max_slots,avail_slots,flags,prov_ob: Integer;
      [*] = ;
      [*] = ;      flags := $10;
      [*] = ;      res := 1;
      [*] = ;      e_mode := _sa_GetAsInt(extra_attr,0);
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         province_p := _sa_GetAsInt(extra_attr,1);
      [*] = ;         if province_p = 0 then province_p := gIntRegister_MapSelectedHex;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         province_p := gIntRegister_MapSelectedHex;
      [*] = ;
      [*] = ;      if (province_p <> 0) and (ParserGetBoolValueByKeyByHandle(province_p, 'Castle')) then
      [*] = ;         flags := flags or 8;
      [*] = ;
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) and (province_p <> 0) and ((flags and 8) = 0) then
      [*] = ;      begin
      [*] = ;         pl_handle := GetPlayerHandleInterfaceIO();
      [*] = ;         if IsUnderSiege(pl_handle) then
      [*] = ;            flags := flags or 1;
      [*] = ;         if GetPlayerIntValueIndByHandle(pl_handle, gc_map_PLStack_MapUnit_iCanOuterBuild) <= 0 then
      [*] = ;            flags := flags or 2;
      [*] = ;
      [*] = ;         avail_slots := 0;
      [*] = ;         prov_ob :=  ParserSelectByHandleByKey(province_p, 'OuterBuildings');
      [*] = ;         max_slots := ParserGetCountByHandle(prov_ob);
      [*] = ;         for i := 0 to max_slots-1 do
      [*] = ;         begin
      [*] = ;            id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(prov_ob,i),'OuterBuildID');
      [*] = ;            if id = 0 then
      [*] = ;            begin
      [*] = ;               avail_slots := avail_slots + 1;
      [*] = ;               if e_mode = 0 then
      [*] = ;                  break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         flags := flags and ($ffff xor $10);
      [*] = ;         max_slots := 0;
      [*] = ;         avail_slots := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if avail_slots = 0 then
      [*] = ;         flags := flags or 4;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         _sa_AddAsInt(ret_s,flags);
      [*] = ;         _sa_AddAsInt(ret_s,max_slots);
      [*] = ;         _sa_AddAsInt(ret_s,avail_slots);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ((flags and $8) <> 0) then
      [*] = ;      begin
      [*] = ;         if mode=0 then
      [*] = ;            res := _cmd_Post('castlebuild','','')
      [*] = ;         else
      [*] = ;            res := _cmd_Check('castlebuild','','1');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ((flags and $10) = 0) then
      [*] = ;            res := 2;
      [*] = ;
      [*] = ;         if (mode=0) and (res=1) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := province_p;
      [*] = ;            GUIExecuteState('vvk.map.ShowOuterBuildList');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'provincesiteslist' : begin
      [*] = ;   // extra_attr
      [*] = ;   // returns result in string so you should use CheckExt command
      [*] = ;   // [0] - mode
      [*] = ;   //       1 - get sites related data
      [*] = ;   //         RET[0] - sites parser or zero if sites not available
      [*] = ;   //         RET[1] - explore level
      [*] = ;   //         RET[2] - available sites number
      [*] = ;   //         RET[3] - reserved
      [*] = ;   //       2 - get list of available sites
      [*] = ;   //         RET[0-3] see above
      [*] = ;   //         RET[4+] - list of indexes of available sites in province
      [*] = ;   // [1] - province parser or 0 for gIntRegister_MapSelectedHex
      [*] = ;   // [2] - hero parser or 0 if no hero
      [*] = ;      var i,e_mode,province_p,hero_p,sites,sites_no,explored : Integer;
      [*] = ;      var sites_s : String;
      [*] = ;
      [*] = ;      res := 2;
      [*] = ;      e_mode := _sa_GetAsInt(extra_attr,0);
      [*] = ;      explored := 0;
      [*] = ;      sites_s := '';
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         province_p := _sa_GetAsInt(extra_attr,1);
      [*] = ;         if province_p = 0 then province_p := gIntRegister_MapSelectedHex;
      [*] = ;         hero_p := _sa_GetAsInt(extra_attr,2);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         province_p := 0;
      [*] = ;
      [*] = ;      if province_p = 0 then
      [*] = ;      begin
      [*] = ;         i := _sa_GetAsInt(cattr,0);
      [*] = ;         case i of
      [*] = ;            2 : begin // just list sites
      [*] = ;               hero_p := 0;
      [*] = ;               province_p := gIntRegister_MapSelectedHex;
      [*] = ;            end;
      [*] = ;            else begin
      [*] = ;               province_p := gIntRegister_MapSelectedHex;
      [*] = ;               //if (province_p = 0) or (i=1) then
      [*] = ;               begin
      [*] = ;                  hero_p := GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;                  //_log_Values('P_H|H_H',province_p,hero_p,0,0,0,0);
      [*] = ;                  if hero_p <> 0 then
      [*] = ;                  begin
      [*] = ;                     province_p := _misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(hero_p,gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;                     SetSelection(province_p);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if i = 1 then province_p := 0;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (province_p<>0) or (gMapEditor.enabled) then
      [*] = ;      begin
      [*] = ;         var site,id : Integer;
      [*] = ;
      [*] = ;         sites := ParserSelectByHandleByKey(province_p,'Sites');
      [*] = ;         sites_no := 0;
      [*] = ;         if _console_GetIntVar('DebugShowAllSites') > 0 then explored := 100
      [*] = ;         else explored := ParserGetIntValueByKeyByHandle(province_p, 'Explored');
      [*] = ;
      [*] = ;         for i:=0 to ParserGetCountByHandle(sites)-1 do
      [*] = ;         begin
      [*] = ;            site := ParserSelectByHandleByIndex(sites,i);
      [*] = ;            id := ParserGetIntValueByKeyByHandle(site, 'SiteID');
      [*] = ;            if id > 0 then
      [*] = ;            begin
      [*] = ;               if (ParserGetIntValueByKeyByHandle(site,'Explore')<=explored) or (gMapEditor.enabled) then
      [*] = ;               begin
      [*] = ;                  sites_no := sites_no + 1;
      [*] = ;                  if e_mode = 2 then
      [*] = ;                     _sa_AddAsInt(sites_s,i)
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if sites_no = 0 then sites := 0;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         explored := 0;
      [*] = ;         sites := 0;
      [*] = ;         sites_no := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         _sa_AddAsInt(ret_s,sites);
      [*] = ;         _sa_AddAsInt(ret_s,explored);
      [*] = ;         _sa_AddAsInt(ret_s,sites_no);
      [*] = ;         _sa_AddAsInt(ret_s,0);
      [*] = ;         //_log_values('EXP|SITES',explored,_sa_GetNum(sites_s),0,0,0,0);
      [*] = ;         if sites_s <> '' then ret_s := ret_s + '|'+sites_s;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) and (province_p <> 0) and (sites <> 0) then
      [*] = ;         res := 1;
      [*] = ;
      [*] = ;      if (mode=0) and (res=1) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := province_p;
      [*] = ;         IntRegister1 := hero_p;
      [*] = ;         if hero_p <> 0 then BoolRegister0 := true
      [*] = ;         else BoolRegister0 := false;
      [*] = ;         GUIExecuteState('vvk.map.ShowSitesList');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'provincehireguard' : begin
      [*] = ;   // extra_attr
      [*] = ;   // returns result in string so you should use CheckExt command
      [*] = ;   // [0] - mode
      [*] = ;   //       1 - get availability bit mask
      [*] = ;   //         RET[0]
      [*] = ;   //           &0x01 - guard exists in province and cannot be disbanded
      [*] = ;   //           &0x02 - guard exists in province and can be disbanded
      [*] = ;   //           &0x04 - already hired this turn
      [*] = ;   //           &0x08 - guards are available to hire
      [*] = ;   //           &0x10 - not under siege
      [*] = ;   //         RET[1] - current defender id
      [*] = ;   //       2 - get list of available defenders
      [*] = ;   //         RET[0] - see mode=1
      [*] = ;   //         RET[1] - current defender id
      [*] = ;   //         RET[2+] - list of indexes of available defenders in province
      [*] = ;   // [1] - province parser or 0 for gIntRegister_MapSelectedHex
      [*] = ;
      [*] = ;      var e_mode : Integer = _sa_GetAsInt(extra_attr,0);
      [*] = ;      var p_province,pl_handle,c_defender,c_defender_id,defenders,i : Integer;
      [*] = ;      var flags : Integer = 0;
      [*] = ;      var guards_s : String = '';
      [*] = ;
      [*] = ;      res := 2;
      [*] = ;
      [*] = ;      p_province := _sa_GetAsInt(extra_attr,1);
      [*] = ;      if p_province = 0 then p_province := gIntRegister_MapSelectedHex;
      [*] = ;
      [*] = ;      if (p_province <> 0) and (not gMapEditor.enabled) then
      [*] = ;      begin
      [*] = ;         if (not SameText(GetPlayerNameInterfaceIO(), ParserGetValueByKeyByHandle(p_province, 'Player')))  then
      [*] = ;            p_province := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (p_province <> 0) or (gMapEditor.enabled) then
      [*] = ;      begin
      [*] = ;         pl_handle := GetPlayerHandleInterfaceIO();
      [*] = ;         if not IsUnderSiege(pl_handle) then
      [*] = ;         begin
      [*] = ;            flags := $10;
      [*] = ;            PlayerExecuteStateByHandle(pl_handle,'GetCastleParser');
      [*] = ;            defenders := ParserSelectByHandleByKey(IntRegister0, 'Defenders');
      [*] = ;            c_defender := ParserSelectByHandleByKey(p_province, 'Defender');
      [*] = ;
      [*] = ;            if c_defender <> 0 then c_defender_id := ParserGetIntValueByKeyByHandle(c_defender,'DefenderID')
      [*] = ;            else c_defender_id := 0;
      [*] = ;
      [*] = ;            //if e_mode = 2 then _sa_AddAsInt(guards_s,c_defender_id);
      [*] = ;
      [*] = ;            if c_defender_id <> 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := c_defender_id;
      [*] = ;               MapExecuteState('GetDefenderParserByID');
      [*] = ;               if not ParserGetBoolValueByKeyByHandle(IntRegister1,'CanDismiss') then flags := flags or 1
      [*] = ;               else flags := flags or 2;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (GetPlayerIntValueIndByHandle(pl_handle,gc_map_PLStack_MapUnit_iCanHire) <= 0) then flags := (flags or 4);
      [*] = ;
      [*] = ;            for i := 0 to ParserGetCountByHandle(defenders)-1 do
      [*] = ;            begin
      [*] = ;               c_defender := ParserSelectByHandleByIndex(defenders,i);
      [*] = ;               if (ParserGetIntValueByKeyByHandle(c_defender,'Count') <> 0) and (ParserGetIntValueByKeyByHandle(c_defender,'DefenderID') <> c_defender_id) then
      [*] = ;               begin
      [*] = ;                  flags := flags or 8;
      [*] = ;                  if e_mode = 2 then
      [*] = ;                     _sa_AddAsInt(guards_s,i)
      [*] = ;                  else
      [*] = ;                     break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            //_log_Values('FLAGS|GUARDS_NO|E_MODE',flags,_sa_GetNum(guards_s),e_mode,0,0,0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if e_mode <> 0 then
      [*] = ;      begin
      [*] = ;         _sa_AddAsInt(ret_s,flags);
      [*] = ;         _sa_AddAsInt(ret_s,c_defender_id);
      [*] = ;         if guards_s <> '' then ret_s := ret_s + '|' + guards_s;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) and (((flags and $10) <> 0) and ((flags and $b) <> 0)) or (gMapEditor.enabled) then
      [*] = ;         res := 1;
      [*] = ;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;         GUIExecuteState('vvk.map.ShowDefendersList');
      [*] = ;   end;
      [*] = ;   // end of province commands
      [*] = ;   // mouse buttons and general commands
      [*] = ;   else begin
      [*] = ;      var keycode : Integer = 0;
      [*] = ;
      [*] = ;      case StrToLowerCase(cname) of
      [*] = ;         'maplmbdown' : keycode := 1;
      [*] = ;         'maprmbdown' : keycode := 2;
      [*] = ;         'mapmmbdown' : keycode := 3;
      [*] = ;         'maplmbup' : keycode := 101;
      [*] = ;         'maprmbup' : keycode := 102;
      [*] = ;         'mapmmbup' : keycode := 4;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if keycode <> 0 then
      [*] = ;      begin
      [*] = ;         if (mode = 0) then
      [*] = ;            PostToEvent(keycode,'map.OnGUIMouseDown');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         res := 0;
      [*] = ;         if _log then _Log_gui('Command '+cname+' skipped.');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister2 := res;
      [*] = ;StringRegister0 := ret_s;
   struct.end
section.end

