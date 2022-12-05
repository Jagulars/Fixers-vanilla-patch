section.begin
   Name = TryAttackProvince
   Description : struct.begin
      [*] = ;IntRegister0 - province handle
      [*] = ;IntRegister1 - army power
      [*] = ;BoolRegister0 - should use IR1 instead of comparing armies
   struct.end
   Code : struct.begin
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var inputPower : Integer = IntRegister1;
      [*] = ;var takePower : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\TRYATTACKPROVINCE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myCustomName : String = GetGameObjectCustomNameByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;var maxTargets : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_map_GOStack_MapUnit_iMaxTargets);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;var provPlIndex : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;
      [*] = ;var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;var provDist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'IsPlayable');
      [*] = ;var provPlayable : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'CanPassProvince');
      [*] = ;var canPass : Boolean = BoolRegister0;
      [*] = ;var passPlIndex : Integer = IntRegister1;
      [*] = ;
      [*] = ;if (dummyUID > 0) and provPlayable and (not canPass) and
      [*] = ;((passPlIndex = -1) or (gArrDiplomacy[myPlIndex][passPlIndex].treaty = 1)) and (provDist > 0) then
      [*] = ;begin
      [*] = ;   var power : Integer = 0;
      [*] = ;   var heroDeath : Boolean = false;
      [*] = ;
      [*] = ;   if takePower then
      [*] = ;      power := inputPower
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := -1;
      [*] = ;      BoolRegister0 := true;
      [*] = ;      BoolRegister1 := true;
      [*] = ;      ExecuteState('AdvCompareArmiesStrength');
      [*] = ;      power := IntRegister2;
      [*] = ;      heroDeath := BoolRegister2;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (provPlHandle = 0) then
      [*] = ;   begin
      [*] = ;      // add neutral targets
      [*] = ;      var pMyTargets : Integer = 0;
      [*] = ;      if _misc_IsProvinceNeutral(pProvince) then //if desert or dead lands
      [*] = ;      begin
      [*] = ;         if passPlIndex = -1 then
      [*] = ;         pMyTargets := ParserSelectByHandleByKey(pMyParser, 'PassableTargets')//if guards already defeated, I think
      [*] = ;         else
      [*] = ;         pMyTargets := ParserSelectByHandleByKey(pMyParser, 'EnemyPassTargets');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      pMyTargets := ParserSelectByHandleByKey(pMyParser, 'NeutralTargets');
      [*] = ;
      [*] = ;      var pNewTarget : Integer = 0;
      [*] = ;
      [*] = ;      if ParserGetCountByHandle(pMyTargets) < maxTargets then//just add. No need to check desirability
      [*] = ;         pNewTarget := ParserAddChildByIndex(pMyTargets, '*')//add to either PassableTargets, EnemyPassTargets or NeutralTargets depending on above, I think
      [*] = ;      else
      [*] = ;      begin//check desirability and sort from least to most desirables
      [*] = ;         for i := 0 to maxTargets-1 do
      [*] = ;         begin
      [*] = ;            var pMyTarget : Integer = ParserSelectByHandleByIndex(pMyTargets, i);//choose from either PassableTargets, EnemyPassTargets or NeutralTargets and iterate to maxtargets
      [*] = ;
      [*] = ;            var trgDist : Integer = ParserGetIntValueByKeyByHandle(pMyTarget, 'Distance');//take existing target params
      [*] = ;            var trgPower : Integer = ParserGetIntValueByKeyByHandle(pMyTarget, 'Power');
      [*] = ;
      [*] = ;            if pNewTarget = 0 then
      [*] = ;            begin
      [*] = ;               // TODO: maybe we should change priority of attacking provinces (formula or something else)
      [*] = ;               if (trgPower < power) or ((trgPower = power) and (trgDist > provDist)) then //if the current province is more suitable target (checks only distance and army strenght. Too simple)
      [*] = ;                  pNewTarget := pMyTarget;//assign parser to newtarget
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var selDist : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Distance');//take newtarget(=current province) params
      [*] = ;               var selPower : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Power');
      [*] = ;
      [*] = ;               if (trgPower < selPower) or ((trgPower = selPower) and (trgDist > selDist)) then //if the current province is more suitable target
      [*] = ;                  pNewTarget := pMyTarget;//assign parser to newtarget
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if pNewTarget <> 0 then //set the new target's actual parameters if it was assigned a parser
      [*] = ;      begin
      [*] = ;         _gui_ProgressCalculations(_log_name+' Neutral target for ' + myCustomName + ' (DummyUID = ' + IntToStr(dummyUID) + ', power = ' + IntToStr(power) + ')');
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'DummyUID', dummyUID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'Distance', provDist);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'Power', power);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pNewTarget, 'HeroDeath', heroDeath);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if gArrDiplomacy[myPlIndex][provPlIndex].treaty = 1 then
      [*] = ;   begin
      [*] = ;      // add enemy targets
      [*] = ;      var pMyEnemyTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'EnemyTargets');
      [*] = ;      var pNewTarget : Integer = 0;
      [*] = ;
      [*] = ;      if ParserGetCountByHandle(pMyEnemyTargets) < maxTargets then
      [*] = ;         pNewTarget := ParserAddChildByIndex(pMyEnemyTargets, '*')
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         for i := 0 to maxTargets-1 do
      [*] = ;         begin
      [*] = ;            var pMyEnemyTarget : Integer = ParserSelectByHandleByIndex(pMyEnemyTargets, i);
      [*] = ;
      [*] = ;            var trgDist : Integer = ParserGetIntValueByKeyByHandle(pMyEnemyTarget, 'Distance');
      [*] = ;            var trgPower : Integer = ParserGetIntValueByKeyByHandle(pMyEnemyTarget, 'Power');
      [*] = ;            var trgIsCastle : Boolean = ParserGetBoolValueByKeyByHandle(pMyEnemyTarget, 'Castle');
      [*] = ;
      [*] = ;            if pNewTarget = 0 then
      [*] = ;            begin
      [*] = ;               if (isCastle and (not trgIsCastle)) or (trgPower < power) or ((trgPower = power) and (trgDist > provDist)) then
      [*] = ;               pNewTarget := pMyEnemyTarget;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var selDist : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Distance');
      [*] = ;               var selPower : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Power');
      [*] = ;
      [*] = ;               if (not trgIsCastle) and ((trgPower < selPower) or ((trgPower = selPower) and (trgDist > selDist))) then
      [*] = ;               pNewTarget := pMyEnemyTarget;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if pNewTarget <> 0 then
      [*] = ;      begin
      [*] = ;         _gui_ProgressCalculations(_log_name+' Enemy target for ' + myCustomName + ' (DummyUID = ' + IntToStr(dummyUID) + ', power = ' + IntToStr(power) + ')');
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'DummyUID', dummyUID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'Distance', provDist);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'Power', power);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pNewTarget, 'HeroDeath', heroDeath);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

