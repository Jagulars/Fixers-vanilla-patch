section.begin
   Name = DoAttack
   Description : struct.begin
      [*] = ;IntRegister0 - attack bonus
      [*] = ;BoolRegister0 - do invert attack and counter attack animations
      [*] = ;OUT: BoolRegister1 - is target run back
   struct.end
   Code : struct.begin
      [*] = ;var attBonus : Integer = IntRegister0;
      [*] = ;var invert : Boolean = BoolRegister0;
      [*] = ;var runBack : Boolean = false;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\DOATTACK';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;if not GetBoolValueByIndex(gc_stack_unit_bRunBack) then
      [*] = ;begin
      [*] = ;   var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;   var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;   var myIsHero : Boolean = GetGameObjectBoolValueIndByHandle(myGOHandle, gc_stack_unit_bIsHero);
      [*] = ;   var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;   var myCustomName : String = GetGameObjectMyCustomName();
      [*] = ;   var tUID : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID);
      [*] = ;   var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;   var tGridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;   var tGridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;   var tIsHero : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bIsHero);
      [*] = ;   var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;   var tCurStamina : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;
      [*] = ;   // Fly text data
      [*] = ;   var oldMyLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;   var oldMyStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;   var oldMyMoral : Integer = GetIntValueByIndex(gc_stack_unit_iCurMoral);
      [*] = ;   var oldLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;   var oldStamina : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;   var oldMoral : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;   var myGridX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;   var myGridY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;   var myMovePoints : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints);
      [*] = ;   var summoned : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bSummoned);
      [*] = ;   var lunge : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bLunge);
      [*] = ;
      [*] = ;   var dist : Integer = _misc_GetHexDist(myGridX, myGridY, tGridX, tGridY);
      [*] = ;
      [*] = ;   _gv_traceState(_log_name+'['+myCustomName+', Target: '+GetGameObjectCustomNameByHandle(tGOHandle)+', AB:'+IntToStr(attBonus)+',I:'+BoolToStr(invert)+']',_log_trace);
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var mySpeed : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;   var pMyNeighbours : Integer = ParserSelectByHandleByKey(pMyParser, 'Neighbours');
      [*] = ;
      [*] = ;   var FrameShift : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iDamageFrame);
      [*] = ;   var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myGOHandle);
      [*] = ;   var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myGOHandle);
      [*] = ;   var delayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor);
      [*] = ;
      [*] = ;   var pMyAttackList : Integer = ParserSelectByHandleByKey(pMyParser, 'AttackList');
      [*] = ;   var pMyAttack : Integer = ParserAddChildByIndex(pMyAttackList, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyAttack, 'UID', tUID);
      [*] = ;   ParserSetValueByKeyByHandle(pMyAttack, 'Animation', 'attack');
      [*] = ;   ParserSetBoolValueByKeyByHandle(pMyAttack, 'Invert', invert);
      [*] = ;
      [*] = ;   var pElmLog : Integer = 0;
      [*] = ;   var pSrcUnit : Integer = 0;
      [*] = ;   var pDestUnit : Integer = 0;
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      pElmLog := _log_battle_AddNewElement();
      [*] = ;      pSrcUnit := ParserSelectByHandleByKey(pElmLog, 'SrcUnit');
      [*] = ;      ParserSetIntValueByKeyByHandle(pSrcUnit, 'UID', myUID);
      [*] = ;
      [*] = ;      var pDestUnits : Integer = ParserSelectByHandleByKey(pElmLog, 'DestUnits');
      [*] = ;      pDestUnit := _log_battle_AddUnitInfoToParser(pDestUnits);
      [*] = ;      ParserSetIntValueByKeyByHandle(pDestUnit, 'UID', tUID);
      [*] = ;
      [*] = ;      if gBoolRegister_BattleIsAttackerAction then
      [*] = ;         ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 1)
      [*] = ;      else
      [*] = ;         ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 2);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var bCrush : Boolean = GetBoolValueByIndex(gc_stack_unit_bCrush);
      [*] = ;   var bRoundAttack : Boolean = GetBoolValueByIndex(gc_stack_unit_bRoundAttack);
      [*] = ;   var bPoisonBite : Boolean = GetBoolValueByIndex(gc_stack_unit_bPoisonBite);
      [*] = ;   var bAstralStrike : Boolean = GetBoolValueByIndex(gc_stack_unit_bAstralStrike);
      [*] = ;   var bLunge : Boolean = GetBoolValueByIndex(gc_stack_unit_bLunge);
      [*] = ;   //Log('My direction: (' + FloatToStr(dirX) + ', ' + FloatToStr(dirZ) + ')');
      [*] = ;
      [*] = ;   var i, j, hit : Integer;
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iActionType, 1);
      [*] = ;
      [*] = ;   if gBoolRegister_BattleIsAttackerAction then
      [*] = ;   begin
      [*] = ;      IntRegister0 := myUID;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'CheckSlyBootsAbility');
      [*] = ;      if BoolRegister0 then
      [*] = ;      begin
      [*] = ;         if (( _unit_CheckAbility(tGOHandle, gc_ability_immobilized) = 0 ) and ( _unit_CheckAbility(tGOHandle, gc_ability_cantmove) = 0 )) then
      [*] = ;         begin
      [*] = ;            SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bRunBack, true);
      [*] = ;            runBack := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
	  [*] = ;   var side : Integer = -1;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      var facing : Integer = _map_GetFacing(_map_GetBattleHex(myGridX, myGridY), _map_GetBattleHex(tGridX, tGridY));
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iFacing, facing);
      [*] = ;      _log_map('Facing '+IntToStr(facing));
      [*] = ;      _log_map('Target facing '+IntToStr(GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iFacing)));
      [*] = ;      
      [*] = ;      if not gBoolRegister_BattleIsAttackerAction then
      [*] = ;         side := 3
      [*] = ;      else
      [*] = ;         side := _unit_GetAttackSide(facing, tGOHandle);
      [*] = ;     _log_map('Side '+IntToStr(side));
      [*] = ;   end;
      [*] = ;   {if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      var angle : Float;
      [*] = ;      if not gBoolRegister_BattleIsAttackerAction then
      [*] = ;         angle := 180
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var myTPCount : Integer = GetGameObjectMyTrackPointCount();
      [*] = ;         var x, y, z : Float;
      [*] = ;         if myTPCount > 0 then
      [*] = ;            GetGameObjectMyTrackPointCoordsByIndex(myTPCount-1, x, y, z)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            x := GetGameObjectMyPositionX();
      [*] = ;            y := GetGameObjectMyPositionY();
      [*] = ;            z := GetGameObjectMyPositionZ();
      [*] = ;         end;
      [*] = ;         var enX : Float = GetGameObjectPositionXByHandle(tGOHandle);
      [*] = ;         var enY : Float = GetGameObjectPositionYByHandle(tGOHandle);
      [*] = ;         var enZ : Float = GetGameObjectPositionZByHandle(tGOHandle);
      [*] = ;
      [*] = ;         var vx : Float = enX - x;
      [*] = ;         var vy : Float = 0;
      [*] = ;         var vz : Float = enZ - z;
      [*] = ;
      [*] = ;         var enDirX : Float = GetGameObjectTransformedVirtualDirectionXByHandle(tGOHandle);
      [*] = ;         var enDirY : Float = GetGameObjectTransformedVirtualDirectionYByHandle(tGOHandle);
      [*] = ;         var enDirZ : Float = GetGameObjectTransformedVirtualDirectionZByHandle(tGOHandle);
      [*] = ;
      [*] = ;         angle := VectorAngle(vx, vy, vz, enDirX, enDirY, enDirZ);
      [*] = ;      end;
      [*] = ;
      [*] = ;      side := Round(Abs(angle / 60));
      [*] = ;   end;}
      [*] = ;
      [*] = ;   IntRegister0 := tGOHandle;
      [*] = ;   IntRegister1 := side;
      [*] = ;   BoolRegister0 := gBoolRegister_BattleIsAttackerAction;
      [*] = ;   BoolRegister1 := false;
      [*] = ;   BoolRegister2 := bAstralStrike;
      [*] = ;   BoolRegister3 := true;
      [*] = ;   ExecuteState('GetMeleeHit');
      [*] = ;   hit := IntRegister2;
      [*] = ;   if side >= 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := tUID;
      [*] = ;      IntRegister1 := side;
      [*] = ;      ExecuteState('GetBackstabBonus');
      [*] = ;   end
      [*] = ;   else
      [*] = ;      IntRegister0 := 0;
      [*] = ;   hit := hit + IntRegister0;
      [*] = ;   if IntRegister0 > 0 then
      [*] = ;      _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_backstab, IntRegister0);
      [*] = ;
      [*] = ;   if gBoolRegister_BattleIsAttackerAction then
      [*] = ;      hit := hit + attBonus;
      [*] = ;
      [*] = ;   if hit > tCurLife then
      [*] = ;      hit := tCurLife;
      [*] = ;
      [*] = ;   if gBoolRegister_BattleIsAttackerAction then
      [*] = ;   begin
      [*] = ;      // trampling
      [*] = ;      if (tCurLife - hit < _unit_CheckAbility(myGOHandle, gc_ability_trumpling)) and (_unit_CheckAbility(tGOHandle, gc_ability_flying) = 0) and (_unit_CheckAbility(myGOHandle, gc_ability_cantmove) = 0) then
      [*] = ;      begin
      [*] = ;         hit := tCurLife;
      [*] = ;
      [*] = ;         var abil74 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_reincarnation);
      [*] = ;         var abil91 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_dark_pact);
      [*] = ;         var tRaiseCorpse : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bRaiseCorpse);
      [*] = ;
      [*] = ;         if (not tRaiseCorpse) and (abil74 = 0) and (abil91 = 0) then
      [*] = ;         begin
      [*] = ;            SetIntValueByIndex(gc_stack_unit_iCurrentX, tGridX);
      [*] = ;            SetIntValueByIndex(gc_stack_unit_iCurrentY, tGridY);
      [*] = ;
      [*] = ;            var ind : Integer = gc_battle_GridSize * myGridY + myGridX;
      [*] = ;            var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;            ParserSetIntValueByKeyByHandle(pHexCell, 'UID', 0);
      [*] = ;
      [*] = ;            ind := gc_battle_GridSize * tGridY + tGridX;
      [*] = ;            pHexCell := ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;            ParserSetIntValueByKeyByHandle(pHexCell, 'UID', myUID);
      [*] = ;            _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_trumpling, 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var myMeleeDamageDone : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMeleeDamageDone);
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iMeleeDamageDone, myMeleeDamageDone + hit);
      [*] = ;
      [*] = ;   IntRegister0 := tUID;
      [*] = ;   IntRegister1 := hit;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   BoolRegister1 := true;
      [*] = ;   BoolRegister2 := (not runBack);
      [*] = ;   ExecuteState('HitEffect');
      [*] = ;
      [*] = ;   //if not runBack then
      [*] = ;   begin
      [*] = ;      // change stamina
      [*] = ;      var stamina : Integer = 0;
      [*] = ;      var abil106 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_second_breath);
      [*] = ;
      [*] = ;      if gBoolRegister_BattleIsAttackerAction and (myMovePoints < mySpeed) and (abil106 = 0) then
      [*] = ;         stamina := -2
      [*] = ;      else
      [*] = ;         stamina := -1;
      [*] = ;
      [*] = ;      // world rule
      [*] = ;      if _worldrule_GetWorldRuleAbilityExistByID(21) then
      [*] = ;      begin
      [*] = ;         if (gBoolRegister_BattleIsAttackerAction) then
      [*] = ;            stamina := stamina+_worldrule_GetWorldRuleAbilityParam1(21)
      [*] = ;         else
      [*] = ;            stamina := stamina+_worldrule_GetWorldRuleAbilityParam2(21);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if not runBack then
      [*] = ;      begin
      [*] = ;         IntRegister0 := stamina;
      [*] = ;         ExecuteState('ChangeStamina');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if GetBoolValueByIndex(gc_stack_unit_bStealthMode) then
      [*] = ;      begin
      [*] = ;         BoolRegister0 := false;
      [*] = ;         ExecuteState('SwitchStealthModeFlag');
      [*] = ;      end;
      [*] = ;
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bActionTaken, true);
      [*] = ;
      [*] = ;      if gBoolRegister_BattleIsAttackerAction then
      [*] = ;      begin
      [*] = ;         var bPlayerControl : Boolean = (not gBoolRegister_QuickBattle) and (not GetPlayerBoolValueIndByHandle(myPlHandle, gc_battle_PLStack_bAutoBattle)) and SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPlayer');
      [*] = ;
      [*] = ;         // AI does not know how to utilize swiftness
      [*] = ;         if bPlayerControl and (GetIntValueByIndex(gc_stack_unit_iMovePoints) > 0) and (_unit_CheckAbility(myGOHandle, gc_ability_swiftness) > 0) and (_unit_CheckAbility(myGOHandle, gc_ability_cantmove) = 0) then
      [*] = ;         begin
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanMelee, false);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanShoot, false);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanCast, false);
      [*] = ;            SetIntValueByIndex(gc_stack_unit_iActiveAbility, 0);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            ExecuteState('ActionDone');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gBoolRegister_BattleIsAttackerAction and (not runBack) then
      [*] = ;      begin
      [*] = ;         if bRoundAttack then
      [*] = ;         begin
      [*] = ;            IntRegister0 := -_unit_CheckAbility(myGOHandle, gc_ability_round_attack);
      [*] = ;            ExecuteState('ChangeStamina');
      [*] = ;         end;
      [*] = ;         if bCrush then
      [*] = ;         begin
      [*] = ;            IntRegister0 := -_unit_CheckAbility(myGOHandle, gc_ability_crushing_blow);
      [*] = ;            ExecuteState('ChangeStamina');
      [*] = ;         end;
      [*] = ;         if bPoisonBite then
      [*] = ;         begin
      [*] = ;            IntRegister0 := -4;
      [*] = ;            ExecuteState('ChangeStamina');
      [*] = ;         end;
      [*] = ;         if bAstralStrike then
      [*] = ;         begin
      [*] = ;            IntRegister0 := -_unit_CheckAbility(myGOHandle, gc_ability_astral_strike);
      [*] = ;            ExecuteState('ChangeStamina');
      [*] = ;         end;
      [*] = ;         if bLunge then
      [*] = ;         begin
      [*] = ;            IntRegister0 := -_unit_CheckAbility(myGOHandle, gc_ability_lunge);
      [*] = ;            ExecuteState('ChangeStamina');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if tIsHero and (not gBoolRegister_BattleSimulate) and (not runBack) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 1;
      [*] = ;         IntRegister1 := myUID;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'DamageArmor');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if myIsHero and (not gBoolRegister_BattleSimulate) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 1;
      [*] = ;         IntRegister1 := 1;
      [*] = ;         ExecuteState('DamageWeapon');
      [*] = ;      end;
      [*] = ;
      [*] = ;      //if gBoolRegister_BattleIsAttackerAction then
      [*] = ;      //Log('Attack points: ' + IntToStr(damage))
      [*] = ;      //else
      [*] = ;      //Log('Counter attack points: ' + IntToStr(damage));
      [*] = ;
      [*] = ;      //Log('Health points: ' + IntToStr(goHP));
      [*] = ;
      [*] = ;      if not runBack then
      [*] = ;      begin
      [*] = ;         IntRegister0 := hit;
      [*] = ;         IntRegister1 := 0;
      [*] = ;         IntRegister2 := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;         FloatRegister0 := delayTime;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'TakeDamage');
      [*] = ;
      [*] = ;         var deathAnimReady : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady) + 1;
      [*] = ;         SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady, deathAnimReady);
      [*] = ;
      [*] = ;         if BoolRegister0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 2;
      [*] = ;            ExecuteState('ChangeMoral');
      [*] = ;
      [*] = ;            var myEnemySlayed : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iEnemySlayed);
      [*] = ;            SetGameObjectMyIntValueInd(gc_stack_unit_iEnemySlayed, myEnemySlayed+1);
      [*] = ;
      [*] = ;            //if gBoolRegister_BattleIsAttackerAction then
      [*] = ;            SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iKillerUID, myUID);
      [*] = ;
      [*] = ;            IntRegister0 := tUID;
      [*] = ;            ExecuteState('SoulSteal');
      [*] = ;
      [*] = ;            if (_unit_CheckAbility(myGOHandle, gc_ability_necromant) > 0) and (not summoned) then
      [*] = ;               SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bRaiseCorpse, true);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;         begin
      [*] = ;            _unit_SetupStatsTextData(tGOHandle, myUID, oldLife, oldStamina, oldMoral);
      [*] = ;            _unit_SetupStatsTextData(myGOHandle, myUID, oldMyLife, oldMyStamina, oldMyMoral);
      [*] = ;
      [*] = ;            if lunge and (dist = 2) then
      [*] = ;               _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility,gc_ability_lunge,0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _gv_traceState(_log_name+'[DAR: '+IntToStr(GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady))+', RB: '+BoolToStr(runBack)+', H: '+IntToStr(hit)+']',$1000000 or _log_trace);
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister1 := runBack;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

