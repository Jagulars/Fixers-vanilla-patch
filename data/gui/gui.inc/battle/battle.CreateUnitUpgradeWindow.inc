section.begin
   Name = battle.CreateUnitUpgradeWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.CREATEUNITUPGRADEWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(gIntRegister_BattleCurPlIndex)+','+IntToStr(gIntRegister_CurGameMode)+']',_log_trace);
      [*] = ;
      [*] = ;// choose game object for increasing level
      [*] = ;var plHandle : Integer = 0;
      [*] = ;
      [*] = ;MapExecuteState('GetCurrentArmyParser');
      [*] = ;var pArmyUnits : Integer = IntRegister0;
      [*] = ;
      [*] = ;if (gIntRegister_CurGameMode = gc_GameModeTactics) or (gBoolRegister_IsDefenderAutoBattle) then
      [*] = ;   plHandle := GetPlayerHandleByIndex(gIntRegister_BattleCurPlIndex);
      [*] = ;
      [*] = ;var armyCount : Integer = ParserGetCountByHandle(pArmyUnits);
      [*] = ;var pArmyUnit : Integer = 0;
      [*] = ;
      [*] = ;var newLevel, oldLevel, i, goHandle, medalID : Integer;
      [*] = ;var isHero : Boolean;
      [*] = ;var bCloseWindow : Boolean = false;
      [*] = ;var curLife : Integer = 0;
      [*] = ;
      [*] = ;repeat
      [*] = ;   pArmyUnit := ParserSelectByHandleByIndex(pArmyUnits, gIntRegister_BattleCurGOIndex);
      [*] = ;   _log_gui(_log_name+' parser unit: '+ParserGetValueByKeyByHandle(pArmyUnit, 'Name')+', index: '+IntToStr(gIntRegister_BattleCurGOIndex));
      [*] = ;   curLife := ParserGetIntValueByKeyByHandle(pArmyUnit, 'CurLife');
      [*] = ;
      [*] = ;   oldLevel := ParserGetIntValueByKeyByHandle(pArmyUnit, 'Level');
      [*] = ;
      [*] = ;   IntRegister0 := pArmyUnit;
      [*] = ;   MapExecuteState('CalcUnitLevelByParser');
      [*] = ;   newLevel := IntRegister1;
      [*] = ;
      [*] = ;   isHero := ParserGetBoolValueByKeyByHandle(pArmyUnit, 'IsHero');
      [*] = ;
      [*] = ;   if isHero or (curLife = 0) then
      [*] = ;      gIntRegister_BattleCurGOIndex := gIntRegister_BattleCurGOIndex + 1
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (newLevel > oldLevel) and (gProfile.autolvlup > 0) then
      [*] = ;      begin
      [*] = ;         var unitID : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'UnitID');
      [*] = ;         var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;         var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;
      [*] = ;         if gProfile.autolvlup >= rank then
      [*] = ;         begin
      [*] = ;
      [*] = ;            for i := oldLevel to newLevel-1  do
      [*] = ;            begin
      [*] = ;               IntRegister0 := pArmyUnit;
      [*] = ;               MapExecuteState('UnitLevelUpByParser');
      [*] = ;            end;
      [*] = ;
      [*] = ;            oldLevel := newLevel;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (newLevel <= oldLevel) then
      [*] = ;      begin
      [*] = ;         // check medal
      [*] = ;         if (plHandle <> 0) then // no medals unless enter battle personally
      [*] = ;         begin
      [*] = ;            medalID := 0;
      [*] = ;            for i := 0 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;            begin
      [*] = ;               goHandle := GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;               if GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iArmyIndex) = gIntRegister_BattleCurGOIndex then
      [*] = ;               begin
      [*] = ;                  _log_gui(_log_name+' player unit: '+GetGameObjectBaseNameByHandle(goHandle)+', index: '+IntToStr(i));
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'GetMedal');
      [*] = ;                  //IntRegister0 := Round(RandomExt()*14+1);
      [*] = ;                  medalID := IntRegister0;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if medalID > 0 then
      [*] = ;            begin
      [*] = ;               _gui_RootWindowRemoveWithFade(_gui_GetWindow('battle_unitupgrade'),0);
      [*] = ;
      [*] = ;               StringRegister0 := 'battle.CloseUnitMedalWindow';
      [*] = ;               IntRegister0 := pArmyUnits;
      [*] = ;               IntRegister1 := gIntRegister_BattleCurGOIndex;
      [*] = ;               IntRegister2 := medalID;
      [*] = ;               GUIExecuteState('battle.CreateUnitMedalWindow');
      [*] = ;               if (not GetBoolValueByName('SndLevelUpPlayed')) then
      [*] = ;               begin
      [*] = ;                  _gui_PlaySound('interface', 'level_up_unit');
      [*] = ;                  SetBoolValueByName('SndLevelUpPlayed', True);
      [*] = ;               end;
      [*] = ;               _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;               exit; // this script is called again after medal window is closed
      [*] = ;            end
      [*] = ;            else
      [*] = ;               gIntRegister_BattleCurGOIndex := gIntRegister_BattleCurGOIndex + 1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            gIntRegister_BattleCurGOIndex := gIntRegister_BattleCurGOIndex + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if gIntRegister_BattleCurGOIndex >= armyCount then
      [*] = ;   begin
      [*] = ;      bCloseWindow := true;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;until (newLevel > oldLevel) and (not isHero) and (curLife > 0);
      [*] = ;
      [*] = ;if bCloseWindow then
      [*] = ;begin
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow('battle_unitupgrade'),0);
      [*] = ;
      [*] = ;   if gBoolRegister_MapProceedBattle or gBoolRegister_IsDefenderAutoBattle then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := true;
      [*] = ;      BoolRegister1 := true;
      [*] = ;      GUIExecuteState('ShowNecromancy');
      [*] = ;      if not BoolRegister2 then
      [*] = ;         GUIExecuteState('battle.CheckSiteLootWindow');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (gIntRegister_CurGameMode = gc_GameModeStrategy) then
      [*] = ;      _gv_SetMapLock(-1,_log_name);
      [*] = ;
      [*] = ;   gIntRegister_MapActiveHeroHandle := 0;
      [*] = ;
      [*] = ;   SetBoolValueByName('SndLevelUpPlayed', False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   StringRegister0 := 'battle.CreateUnitUpgradeWindow';
      [*] = ;   IntRegister0 := pArmyUnits;
      [*] = ;   IntRegister1 := gIntRegister_BattleCurGOIndex;
      [*] = ;   IntRegister2 := -1;
      [*] = ;   IntRegister3 := -1;
      [*] = ;   GUIExecuteState('vvk.battle.ShowUnitUpgradeWindow');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

