section.begin
   Name = battle.EventResultWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.EVENTRESULTWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var press : String = GetValueByName('Press');
      [*] = ;
      [*] = ;const cAcceptBtnTag = 10001;
      [*] = ;
      [*] = ;if (GetValueByName('Key')='RButton') then
      [*] = ;begin
      [*] = ;   GUIExecuteState('EventItemDetailedWindow');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (press='c') and (tag=cAcceptBtnTag) then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow('battle_results'), gc_gui_FadeTime0_2);
      [*] = ;
      [*] = ;   MapExecuteState('bat.GetWinPlayerHandle');
      [*] = ;   var winPlHandle : Integer = IntRegister0;
      [*] = ;   var losePlHandle : Integer = IntRegister1;
      [*] = ;   PlayerExecuteStateByHandle(winPlHandle, 'GetMapPlayerHandle');
      [*] = ;   var mapPlHandle : Integer = IntRegister0;
      [*] = ;   var mapPlIndex : Integer = GetPlayerIndexByHandle(mapPlHandle);
      [*] = ;   PlayerExecuteStateByHandle(losePlHandle, 'GetMapPlayerHandle');
      [*] = ;   var mapLosePlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   if (gGame.gameType = gc_GameTypeLanBattle) or (gGame.gameType = gc_GameTypeHotseatBattle) then
      [*] = ;   begin
      [*] = ;      if gGame.gameType = gc_GameTypeLanBattle then
      [*] = ;         LanTerminateGame();
      [*] = ;      _misc_ParserGetOrCreateByKey('LanSync',true);
      [*] = ;      _run_DoCreateMenu();
      [*] = ;      _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetFloatValueByName('guiBattleResultWindowDelay', 0);
      [*] = ;   gBoolRegister_GUIBattleResultWindow := False;
      [*] = ;
      [*] = ;   if gBoolRegister_ArenaBattle and gBoolRegister_ArenaWatcher then
      [*] = ;      MapExecuteState('bat.AfterWatchBattle')
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var attackPlHandle : Integer = GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;      var defendPlHandle : Integer = GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;
      [*] = ;      MapExecuteState('bat.AddUnitsExperience');
      [*] = ;
      [*] = ;      if ((not gBoolRegister_IsDefenderBattle) or gBoolRegister_IsDefenderAutoBattle) and ((mapPlIndex = gIntRegister_MapMyPlayerIndex) or ((gGame.gameType = gc_GameTypeHotseat) and (not SameText(GetPlayerControlModeByHandle(mapLosePlHandle), 'cmPlayer')))) then
      [*] = ;      begin
      [*] = ;         gIntRegister_BattleCurPlIndex := GetPlayerIndexByHandle(winPlHandle);
      [*] = ;         gIntRegister_BattleCurGOIndex := 0;
      [*] = ;
      [*] = ;         PlayerExecuteStateByHandle(winPlHandle, 'GetHeroHandle');
      [*] = ;         var goHandle : Integer = IntRegister0;
      [*] = ;         var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;         var heroUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iHeroUID);
      [*] = ;         var heroGOHandle : Integer = GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;         GameObjectExecuteStateByHandle(heroGOHandle, 'IsLevelUp');
      [*] = ;
      [*] = ;         if BoolRegister0 and (curLife > 0) then
      [*] = ;         begin
      [*] = ;            _gui_PlaySound('interface', 'level_up_heroe');
      [*] = ;            IntRegister0 := heroGOHandle;
      [*] = ;            GUIExecuteState('CheckHeroUpgrade');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gIntRegister_BattleCurGOIndex := 0;
      [*] = ;            GUIExecuteState('battle.CreateUnitUpgradeWindow');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         MapExecuteState('bat.ProceedHeroesDeath');
      [*] = ;
      [*] = ;         if gBoolRegister_IsDefenderBattle then
      [*] = ;            _gv_SetMapLock(-1,_log_name);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;end;
   struct.end
section.end

