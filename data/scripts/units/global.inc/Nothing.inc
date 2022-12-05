section.begin
   Name = Nothing
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\GLOBAL.INC\NOTHING';
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;if gFloatRegister_BattleFlyTextTime < GetCurrentTime() then
      [*] = ;begin
      [*] = ;   gFloatRegister_BattleFlyTextTime := GetCurrentTime() + gc_flytext_QueueDelay;
      [*] = ;   _fx_StartFlyText_VVK(0);
      [*] = ;end;
      [*] = ;
      [*] = ;if GetIntValueByIndex(gc_battle_PLStack_iIdleMode) <> gc_battle_idle_skip_global then
      [*] = ;begin
      [*] = ;   var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;   var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;   var pMyTowers : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Towers');
      [*] = ;   var towerCount : Integer = ParserGetCountByHandle(pMyTowers);
      [*] = ;
      [*] = ;   //if _log and (gIntRegister_CurGameMode = gc_GameModeTactics) then _Log_Map(_log_name+' Nothing. Towers = '+IntToStr(towerCount));
      [*] = ;
      [*] = ;   ExecuteState('CheckLose');
      [*] = ;   var lose : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   ExecuteState('GetEnemyPlHandle');
      [*] = ;   PlayerExecuteStateByHandle( IntRegister0 , 'CheckLose');
      [*] = ;   var enLose : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   if (_gv_GetBattleLock() = 0) and (lose or enLose) and (not gBoolRegister_BattleEndBattle) and gBoolRegister_MapProceedBattle and (gIntRegister_BattleCurPlIndex = myIndex) then
      [*] = ;      MapExecuteState('bat.DoFinishBattle')
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (not Lose) and (not enLose) and (myIndex = gIntRegister_BattleCurPlIndex) and (not gBoolRegister_BattleEndBattle) and (gIntRegister_QuerySpellUsage=0) then
      [*] = ;      begin
      [*] = ;         ExecuteState('CheckHumanTurn');
      [*] = ;         var humanTurn : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;         if humanTurn then
      [*] = ;         begin
      [*] = ;            if (not _misc_IsLanBattle()) then
      [*] = ;            begin
      [*] = ;               ExecuteState('IsAllActionsDone');
      [*] = ;               if BoolRegister0 and (gProfile.warendturn) and (_gv_GetBattleLock() = 0) then
      [*] = ;                  gBoolRegister_GUIEndTurn := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if ((not humanTurn) or (gIntRegister_BattleCurTowerIndex < towerCount)) then
      [*] = ;            ExecuteState('MoveUnits');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

