section.begin
   Name = vvk.battle.MainPanelCommands
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
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\VVK.BATTLE.MAINPANELCOMMANDS';
      [*] = ;
      [*] = ;var _log : Boolean = false;
      [*] = ;var _autosave : Boolean;
      [*] = ;
      [*] = ;function TryPressButton(btnNamePath : String; parent : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var elmMyParent : Integer;
      [*] = ;
      [*] = ;   Result := False;
      [*] = ;   if (parent=0) then elmMyParent := _gui_GetLayerI()
      [*] = ;   else elmMyParent := parent;
      [*] = ;
      [*] = ;   var elmBtnHandle : Integer = GetGUIElementIndexByNameParent(btnNamePath, elmMyParent);
      [*] = ;   if (elmBtnHandle<>0) then
      [*] = ;   begin
      [*] = ;      var bVisible : Boolean = True;
      [*] = ;      var elmTmpHandle : Integer = elmBtnHandle;
      [*] = ;      while elmTmpHandle <> _gui_GetLayerI() do
      [*] = ;      begin
      [*] = ;         if (not GetGUIElementVisible(elmTmpHandle)) then
      [*] = ;         begin
      [*] = ;            bVisible := False;
      [*] = ;            break;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            elmTmpHandle := GetGUIElementParentByIndex(elmTmpHandle);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (bVisible) and GetGUIElementEnabled(elmBtnHandle) then
      [*] = ;      begin
      [*] = ;         var pressState : String = GetGUIElementPressState(elmBtnHandle);
      [*] = ;         var tag : Integer = GetGUIElementTag(elmBtnHandle);
      [*] = ;
      [*] = ;         if (pressState='') then
      [*] = ;            pressState := 'battle.DoOnClickGUI';
      [*] = ;
      [*] = ;         SetIntValueByName('ElementHandle', elmBtnHandle);
      [*] = ;         SetIntValueByName('Tag', tag);
      [*] = ;         SetValueByName('Key', 'LButton');
      [*] = ;         SetValueByName('Press', 'c');
      [*] = ;         GUIExecuteState(pressState);
      [*] = ;         Result := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//if ability_id < 0 then press button number -ability_id
      [*] = ;function TryPressAbilityButton(btnNamePath : String; ability_id : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var whd,i,ehd: Integer;
      [*] = ;   var v : Boolean;
      [*] = ;
      [*] = ;   Result := False;
      [*] = ;
      [*] = ;   if ability_id > 0 then
      [*] = ;   begin
      [*] = ;      for i := 0 to $10 do
      [*] = ;      begin
      [*] = ;         whd := _gui_GetWindow(btnNamePath+'.ability_'+IntToStr(i));
      [*] = ;         if whd = 0 then
      [*] = ;            break;
      [*] = ;         if (StrToInt(GetGUIElementStringTag(whd)) = ability_id) then
      [*] = ;            break;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      whd := _gui_GetWindow(btnNamePath+'.ability_'+IntToStr(-1*ability_id));
      [*] = ;
      [*] = ;   if whd <> 0 then
      [*] = ;   begin
      [*] = ;      v := True;
      [*] = ;      ehd := whd;
      [*] = ;      while ehd <> _gui_GetLayerI() do
      [*] = ;      begin
      [*] = ;         if (not GetGUIElementVisible(ehd)) then
      [*] = ;         begin
      [*] = ;            v := False;
      [*] = ;            break;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            ehd := GetGUIElementParentByIndex(ehd);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (v) and GetGUIElementEnabled(whd) then
      [*] = ;      begin
      [*] = ;         var pressState : String = GetGUIElementPressState(whd);
      [*] = ;         var tag : Integer = GetGUIElementTag(whd);
      [*] = ;
      [*] = ;         if (pressState='') then
      [*] = ;            pressState := 'battle.DoOnClickGUI';
      [*] = ;
      [*] = ;         SetIntValueByName('ElementHandle', whd);
      [*] = ;         SetIntValueByName('Tag', tag);
      [*] = ;         SetValueByName('Key', 'LButton');
      [*] = ;         SetValueByName('Press', 'c');
      [*] = ;         GUIExecuteState(pressState);
      [*] = ;         Result := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure PostToEvent(tag : Integer; state_name : String);
      [*] = ;begin
      [*] = ;   SetIntValueByName('Tag',tag);
      [*] = ;   //if _log then Log('GUIDown in battle: '+state_name);
      [*] = ;   GUIExecuteState(state_name);
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var cname : String = StringRegister0;
      [*] = ;var cattr : String = StringRegister1;
      [*] = ;var sattr : String = StringRegister2;
      [*] = ;var extra_attr : String = StringRegister3;
      [*] = ;var res : Integer;
      [*] = ;
      [*] = ;_autosave := false;
      [*] = ;if gIntRegister_GVLogging <> gc_gvlog_log_none then
      [*] = ;begin
      [*] = ;   if GetGUIIntValue('BattleAutosave') > 0 then
      [*] = ;      _autosave := true;
      [*] = ;end;
      [*] = ;//_autosave := false;
      [*] = ;
      [*] = ;if mode = 0 then
      [*] = ;   if _log then _log_Gui('[BA] CMD: '+cname+', MODE: '+IntToStr(mode));
      [*] = ;res := 1;
      [*] = ;case StrToLowerCase(cname) of
      [*] = ;   'battleshowmenu' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;      begin
      [*] = ;         _cmd_Post('battlecancelspell','','');
      [*] = ;         if _gui_GetWindow('ingame_menu') <> 0 then
      [*] = ;            _cmd_Post('menumainbutton','continue','')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            GUIExecuteState('ShowMenu');
      [*] = ;            _gv_SetBattleLock(1,_log_name);
      [*] = ;
      [*] = ;            if gBoolRegister_BtnBattleSettingsBlink then
      [*] = ;               _gui_RemoveBlinkElement('btnSettings', gBoolRegister_BtnBattleSettingsBlink);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'battlenextturn' : begin
      [*] = ;      GUIExecuteState('battle.IsLockMode');
      [*] = ;      if BoolRegister0 then
      [*] = ;         res := 2;
      [*] = ;
      [*] = ;      if (mode = 0) and (res=1) then
      [*] = ;      begin
      [*] = ;         _cmd_Post('battlecancelspell','','');
      [*] = ;         
      [*] = ;         if (gBoolRegister_BattlePlaceMode) then
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;            SetPlayerBoolValueIndByHandle(plHandle, gc_battle_PLStack_bUnitPlacement, false);
      [*] = ;            
      [*] = ;            MapExecuteState('bat.CheckSabotage');
      [*] = ;            var isExit : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            if isExit and ((gGame.gameType = gc_GameTypeHotseatBattle) or (gGame.gameType = gc_GameTypeHotseat)) then
      [*] = ;            begin
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'GetEnemyPlHandle');
      [*] = ;               var enPlHandle : Integer = IntRegister0;
      [*] = ;               var enPlace : Boolean = GetPlayerBoolValueIndByHandle(enPlHandle, gc_battle_PLStack_bUnitPlacement);
      [*] = ;
      [*] = ;               if (not _misc_IsLanBattle()) and enPlace and SameText(GetPlayerControlModeByHandle(enPlHandle), 'cmPlayer') then
      [*] = ;               begin
      [*] = ;                  MapExecuteState('bat.SwitchInterfacePlayer');
      [*] = ;                  isExit := false;
      [*] = ;
      [*] = ;                  var i : Integer;
      [*] = ;                  for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;                     SetGameObjectVisibleByHandle(GetGameObjectHandleByIndex(i, enPlHandle), true);
      [*] = ;               end;
      [*] = ;               gIntRegister_SelectedUID := 0;
      [*] = ;               GUIExecuteState('battle.DoDrawHexGrid');
      [*] = ;            end;
      [*] = ;
      [*] = ;            if isExit then
      [*] = ;            begin
      [*] = ;               PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'GetEnemyPlHandle');
      [*] = ;               var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;               if (not _misc_IsLanBattle()) and ((gGame.gameType = gc_GameTypeHotseatBattle) or ((gGame.gameType = gc_GameTypeHotseat) and SameText(GetPlayerControlModeByHandle(enPlHandle), 'cmPlayer'))) then
      [*] = ;                  MapExecuteState('bat.SwitchInterfacePlayer');
      [*] = ;
      [*] = ;               var myPlInd : Integer = GetPlayerIndexByHandle(GetPlayerHandleInterfaceIO());
      [*] = ;
      [*] = ;               if gBoolRegister_BtnBatEndTurnBlink then
      [*] = ;                  _gui_RemoveBlinkElement('btnBatEndTurn', gBoolRegister_BtnBatEndTurnBlink);
      [*] = ;
      [*] = ;               GUIExecuteState('battle.ExitPlacementMode');
      [*] = ;               if (gIntRegister_SelectedUID = 0) and (myPlInd = gIntRegister_BattleCurPlIndex) then
      [*] = ;                  GUIExecuteState('battle.SelectNextUnit');
      [*] = ;               GUIExecuteState('battle.DoDrawHexGrid');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (_misc_IsLanBattle()) and (_gv_GetBattleLock()=0) then
      [*] = ;               GUIExecuteState('lan.OnEndTurn')
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if _autosave then
      [*] = ;               begin
      [*] = ;                  StringRegister0 := 'battle';
      [*] = ;                  BoolRegister0 := True;
      [*] = ;                  IntRegister0 := 0;
      [*] = ;                  MapExecuteState('SaveMap');
      [*] = ;               end;
      [*] = ;               GUIExecuteState('battle.EndTurn');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'battlenextturnbell' : begin
      [*] = ;      if (gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;      begin
      [*] = ;         gIntRegister_PlayBell := 1;
      [*] = ;         _cmd_Post('battlenextturn','','');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'battleunitnext' : begin
      [*] = ;      if mode = 0 then
      [*] = ;         TryPressButton('battle_menupanel.battle_unitpanel.battle_unitproperties_buttons.battle_control_btn_nextunit', 0);
      [*] = ;   end;
      [*] = ;   'battleunitrest' : begin
      [*] = ;      if mode = 0 then
      [*] = ;         TryPressButton('battle_menupanel.battle_unitpanel.battle_unitproperties_buttons.battle_control_btn_rest', 0);
      [*] = ;   end;
      [*] = ;   'battleswitchweapon' : begin
      [*] = ;      if mode = 0 then
      [*] = ;         TryPressButton('battle_menupanel.battle_unitpanel.battle_unitproperties_buttons.battle_control_btn_switchweapon', 0);
      [*] = ;   end;
      [*] = ;   'battlecastspell' : begin
      [*] = ;      var handle : Integer;
      [*] = ;
      [*] = ;      res := 2;
      [*] = ;      handle := GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;      GUIExecuteState('battle.IsLockMode');
      [*] = ;
      [*] = ;      if (handle <> 0) and (not BoolRegister0) and (not gBoolRegister_BattlePlaceMode) then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(handle,'IsSpellsInAbilities');
      [*] = ;         if BoolRegister0 then
      [*] = ;         begin
      [*] = ;            res := 1;
      [*] = ;            if not GetGameObjectBoolValueIndByHandle(handle,gc_stack_unit_bCanAct) then
      [*] = ;               res := res or (_sa_GetAsInt(extra_attr,0) shl 8);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (mode = 0) and ((res and $ff) = 1) then
      [*] = ;      begin
      [*] = ;         GUIExecuteState('vvk.battle.ShowSpellBook');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'battledoability' : begin
      [*] = ;      if mode = 0 then
      [*] = ;         TryPressAbilityButton('battle_menupanel.battle_unitpanel.battle_unitproperties1',StrToInt(cattr));
      [*] = ;   end;
      [*] = ;   'battleabilityslottrigger' : begin
      [*] = ;      if mode = 0 then
      [*] = ;         TryPressAbilityButton('battle_menupanel.battle_unitpanel.battle_unitproperties1',-1*StrToInt(cattr));
      [*] = ;   end;
      [*] = ;   'battleautobattle' : begin
      [*] = ;      if (gBoolRegister_BattlePlaceMode and _misc_IsLanBattle) or (gBoolRegister_BattleEndBattle) or (gBoolRegister_ArenaBattle and gBoolRegister_ArenaWatcher) then
      [*] = ;         res := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if mode = 0 then
      [*] = ;         begin
      [*] = ;            if StrToInt(cattr) <> 0 then
      [*] = ;               BoolRegister0 := true
      [*] = ;            else
      [*] = ;               BoolRegister0 := false;
      [*] = ;            GUIExecuteState('battle.SetAutoBattle');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'battlequickbattle' : begin
      [*] = ;      var myPlHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;      var myAutoBattle : Boolean = GetPlayerBoolValueIndByHandle(myPlHandle, gc_battle_PLStack_bAutoBattle);
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;      var enPlHandle : Integer = IntRegister0;
      [*] = ;      var enCMode : String = GetPlayerControlModeByHandle(enPlHandle);
      [*] = ;      var enAutoBattle : Boolean = GetPlayerBoolValueIndByHandle(enPlHandle, gc_battle_PLStack_bAutoBattle);
      [*] = ;
      [*] = ;      if {(_misc_IsLanBattle()) or} (gBoolRegister_BattleEndBattle) or myAutoBattle or
      [*] = ;      (SameText(enCMode, 'cmPlayer') and (not enAutoBattle)) then
      [*] = ;         res := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if mode = 0 then
      [*] = ;         begin
      [*] = ;            if gBoolRegister_BattlePlaceMode then
      [*] = ;               GUIExecuteState('battle.ExitPlacementMode');
      [*] = ;
      [*] = ;            if StrToInt(cattr) <> 0 then
      [*] = ;               BoolRegister0 := true
      [*] = ;            else
      [*] = ;               BoolRegister0 := false;
      [*] = ;            MapExecuteState('bat.SetQuickBattle');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if _log then _log_Values('QB_RES',res,0,0,0,0,0);
      [*] = ;   end;
      [*] = ;   'battletoggleunithud' : begin
      [*] = ;      if mode = 0 then
      [*] = ;      begin
      [*] = ;         gProfile.warbar := (gProfile.warbar+1) mod 3;
      [*] = ;         GUIExecuteState('battle.UnitHUDControl');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'battlehandtohand' : begin
      [*] = ;      if mode = 0 then
      [*] = ;         PostToEvent(101,'battle.OnGUIMouseDown');
      [*] = ;   end;
      [*] = ;   'battleforcehandtohand' : begin
      [*] = ;      if mode = 0 then
      [*] = ;      begin
      [*] = ;         if StrToInt(cattr) <> 0 then
      [*] = ;         begin
      [*] = ;            SetBoolValueByName('KeyPressedCtrl', True);
      [*] = ;            gBoolRegister_GUIBattleUpdateHexGrid := true;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            SetBoolValueByName('KeyPressedCtrl', False);
      [*] = ;            gBoolRegister_GUIBattleResetHexGrid := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'battleunfreeze' : begin
      [*] = ;      var c : Integer = _gv_GetBattleLock();
      [*] = ;
      [*] = ;      res := 2;
      [*] = ;      if (c > 0) then
      [*] = ;      begin
      [*] = ;         if (_gui_RootWindowGetTopmost(cRootWindowModal) = 0) and ((GetCurrentTime() - _gv_GetBattleLockLastChangeTime()) >= gc_gui_battle_antifreeze_delay) and (not _misc_IsLanBattle()) then
      [*] = ;         begin
      [*] = ;            res := 1;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               _gv_SetBattleLock(-1*c,_log_name+'[battleunfreeze]');
      [*] = ;               ErrorLogI(_log_name+'[battleunfreeze] Manual lock override: '+IntToStr(c));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'maplmbdown' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;         PostToEvent(1,'battle.OnGUIMouseDown');
      [*] = ;   end;
      [*] = ;   'maplmbup' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;         PostToEvent(101,'battle.OnGUIMouseDown');
      [*] = ;   end;
      [*] = ;   'maprmbdown' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;         PostToEvent(2,'battle.OnGUIMouseDown');
      [*] = ;   end;
      [*] = ;   'maprmbup' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;         PostToEvent(102,'battle.OnGUIMouseDown');
      [*] = ;   end;
      [*] = ;   'mapmmbdown' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;         PostToEvent(3,'battle.OnGUIMouseDown');
      [*] = ;   end;
      [*] = ;   'mapmmbup' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;         PostToEvent(4,'battle.OnGUIMouseDown');
      [*] = ;   end;
      [*] = ;   'battleapplyspell' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;         PostToEvent(101,'battle.OnGUIMouseDown');
      [*] = ;   end;
      [*] = ;   'battlecancelspell' : begin
      [*] = ;      if (mode = 0) and (gIntRegister_CurSpell<>-1) then
      [*] = ;      begin
      [*] = ;         gIntRegister_CurSpell := -1;
      [*] = ;         gIntRegister_CurSpellIndex := -1;
      [*] = ;         IntRegister0 := 6; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;         IntRegister1 := 0; //0 - hide
      [*] = ;         GUIExecuteState('DoDragElement');
      [*] = ;         gIntRegister_SacrificeUID := 0;
      [*] = ;         gIntRegister_TeleportUID := 0;
      [*] = ;         gBoolRegister_GUIBattleUpdateHexGrid := true;
      [*] = ;         gBoolRegister_GUIUpdateInterfacePanel := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   else begin
      [*] = ;      if _log then _log_Gui('Command '+cname+' skipped.');
      [*] = ;      res := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister2 := res;
   struct.end
section.end

