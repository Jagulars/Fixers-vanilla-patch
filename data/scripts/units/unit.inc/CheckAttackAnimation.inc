section.begin
   Name = CheckAttackAnimation
   Description : struct.begin
      [*] = ;BoolRegister0 - play invert animation
   struct.end
   Code : struct.begin
      [*] = ;var playInvert : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\CHECKATTACKANIMATION';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cEpsilonAngle = 10;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var bModParams : Boolean = true;
      [*] = ;var bThunderStrike : Boolean = false;
      [*] = ;
      [*] = ;procedure CheckAnimation(goHandle : Integer; attackAnim : String; playNow : Boolean; animExtraDelay : Float);
      [*] = ;begin
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bRunBack) then
      [*] = ;   begin
      [*] = ;      //var frameCount : Integer = GetGameObjectAnimationCycleCountFrameByHandle(myGOHandle, attackAnim);
      [*] = ;      var FrameShift : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iDamageFrame);
      [*] = ;      if (attackAnim='parryattack') then
      [*] = ;         FrameShift := FrameShift+GetGameObjectAnimationCycleCountFrameByHandle(myGOHandle, 'parry')
      [*] = ;      else
      [*] = ;         if (attackAnim='woundattack') then
      [*] = ;            FrameShift := FrameShift+GetGameObjectAnimationCycleCountFrameByHandle(myGOHandle, 'wound');
      [*] = ;      var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myGOHandle);
      [*] = ;      var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myGOHandle);
      [*] = ;      var delayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor) + animExtraDelay;
      [*] = ;      if _log then _log_obj('CheckAttackAnimation delaytime '+GetGameObjectMyBaseName+' '+FloatToStr(delayTime));
      [*] = ;      
      [*] = ;      if SameText(GetGameObjectDelayExecuteStateNameByHandle(goHandle), 'DeathAnimReady') then
      [*] = ;      begin
      [*] = ;         _log_obj('DeathAnimReady already waiting for delayed execute, executing now');
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'DeathAnimReady');
      [*] = ;      end;
      [*] = ;      GameObjectDelayExecuteStateByHandle(goHandle, 'DeathAnimReady', delayTime);
      [*] = ;
      [*] = ;      var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;      var uid : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;      var bPrimaryTarget : Boolean = uid = GetIntValueByIndex(gc_stack_unit_iTargetUID);
      [*] = ;
      [*] = ;      var pTarParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var pTarAttackList : Integer = ParserSelectByHandleByKey(pTarParser, 'AttackList');
      [*] = ;      var pTarAttackAnimList : Integer = ParserSelectByHandleByKey(pTarParser, 'AttackAnimList');
      [*] = ;      var tCAttack : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCAttackCount);
      [*] = ;      var tStatic : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bStatic);
      [*] = ;
      [*] = ;      // attack animation for enemy unit
      [*] = ;      var i : Integer;
      [*] = ;      var pTarAttack : Integer = 0;
      [*] = ;
      [*] = ;      if not tStatic then
      [*] = ;      begin
      [*] = ;         for i := ParserGetCountByHandle(pTarAttackList)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pTmpTarAttack : Integer = ParserSelectByHandleByIndex(pTarAttackList, i);
      [*] = ;            var uid : Integer = ParserGetIntValueByKeyByHandle(pTmpTarAttack, 'UID');
      [*] = ;
      [*] = ;            if uid = myUID then
      [*] = ;            begin
      [*] = ;               pTarAttack := pTmpTarAttack;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var playBerserk : Boolean = false;
      [*] = ;         if ParserGetIntValueByKeyByHandle(pTarParser, 'BerserkUID') = myUID then
      [*] = ;         begin
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHandle, 'PlayBerserkAnimation', delayTime);
      [*] = ;            playBerserk := true;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if pTarAttack <> 0 then // move from AttackList to AttackAnimList
      [*] = ;         begin
      [*] = ;            var pTarAttackAnim : Integer = ParserAddChildByIndex(pTarAttackAnimList, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pTarAttackAnim, 'UID', myUID);
      [*] = ;            var anim : String = ParserGetValueByKeyByHandle(pTarAttack, 'Animation');
      [*] = ;            ParserSetValueByKeyByHandle(pTarAttackAnim, 'Animation', anim);
      [*] = ;            var bInvert : Boolean = ParserGetBoolValueByKeyByHandle(pTarAttack, 'Invert');
      [*] = ;            ParserSetBoolValueByKeyByHandle(pTarAttackAnim, 'Invert', bInvert);
      [*] = ;
      [*] = ;            if (not playBerserk) and (tCAttack = 0) then
      [*] = ;            begin
      [*] = ;               var delayTimeFix : Float = delayTime+0.1;
      [*] = ;               if (bInvert) then delayTimeFix := 0;
      [*] = ;               GameObjectDelayExecuteStateByHandle(goHandle, 'CheckCAttackAnimation', delayTimeFix);
      [*] = ;            end;
      [*] = ;
      [*] = ;            tCAttack := tCAttack + 1;
      [*] = ;            SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCAttackCount, tCAttack);
      [*] = ;            ParserFreeByHandle(pTarAttack);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if playNow then
      [*] = ;      begin
      [*] = ;         var bDisplayFX : Boolean = _obj_EnabledByFlag(gc_ObjectFlagBattleFX);
      [*] = ;         
      [*] = ;         if bDisplayFX then
      [*] = ;         begin
      [*] = ;            IntRegister0 := myUID;
      [*] = ;            FloatRegister0 := delayTime;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'BloodBoom');
      [*] = ;         end;
      [*] = ;
      [*] = ;         if not bPrimaryTarget then // when not primary target in AoE attack
      [*] = ;         begin
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHandle, 'OnDamage', delayTime);
      [*] = ;
      [*] = ;            if bThunderStrike then
      [*] = ;            begin
      [*] = ;               _gui_PlaySound('spells', 'spell22');
      [*] = ;               if bDisplayFX then
      [*] = ;                  _fx_CreateFX(goHandle, 'fx_lightning', 0, 0, 0, 0, delayTime);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if bModParams then
      [*] = ;         begin
      [*] = ;            GameObjectDelayExecuteStateByHandle(myGOHandle, 'ApplyAllVisualParams', delayTime);
      [*] = ;            bModParams := false;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife) > 0) then
      [*] = ;         begin
      [*] = ;            if bDisplayFX and (_unit_CheckAbility(myGOHandle, gc_ability_poison_attack) > 0) and (_unit_CheckAbility(goHandle, gc_ability_poison_immunity) = 0)  then
      [*] = ;               _fx_GetOrCreateFXByID(goHandle, 'fxpoisonattack', 0, 0, 0, 0, 0, 5);
      [*] = ;         end
      [*] = ;         else
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHandle, 'CheckDeathAnimation', delayTime);
      [*] = ;
      [*] = ;         if bDisplayFX and (_unit_CheckAbility(goHandle, gc_ability_poison_flesh) > 0) and (_unit_CheckAbility(myGOHandle, gc_ability_poison_immunity) = 0) then
      [*] = ;            _fx_GetOrCreateFXByID(myGOHandle, 'fxpoisonattack', 0, 0, 0, 0, 0, 5);
      [*] = ;      end;
      [*] = ;   
      [*] = ;      if _log then _log_obj(_log_name+'[Target: '+GetGameObjectCustomNameByHandle(goHandle)+', Delay: '+FloatToStr(delayTime)+', DAR: '+IntToStr(GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iDeathAnimReady)));
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;      IntRegister1 := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;      IntRegister2 := GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;      IntRegister3 := GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;      MapExecuteState('bat.GetOppositeHex');
      [*] = ;      var pNewHex : Integer = IntRegister4;
      [*] = ;
      [*] = ;      var newGridX : Integer = ParserGetIntValueByKeyByHandle(pNewHex, 'X');
      [*] = ;      var newGridY : Integer = ParserGetIntValueByKeyByHandle(pNewHex, 'Y');
      [*] = ;      var ind : Integer = gc_battle_GridSize * newGridY + newGridX;
      [*] = ;      var tnHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;
      [*] = ;      IntRegister0 := -_unit_CheckAbility(goHandle, gc_ability_sly_boots);
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'ChangeStamina');
      [*] = ;
      [*] = ;      var movePoints : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iMovePoints);
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iMovePoints, 10);
      [*] = ;      IntRegister0 := tnHandle;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'Position');
      [*] = ;      if (not BoolRegister0 ) and _log then ErrorLogI(_log_name+' Warning: unit positioning to '+ParserGetValueByKeyByHandle(pNewHex,'X')+','+ParserGetValueByKeyByHandle(pNewHex,'Y')+'failed');
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iMovePoints, movePoints);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;   var pMyAttackList : Integer = ParserSelectByHandleByKey(pMyParser, 'AttackList');
      [*] = ;   var pMyRoundTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'RoundTargets');
      [*] = ;   var myAttackCount : Integer = ParserGetCountByHandle(pMyAttackList);
      [*] = ;
      [*] = ;   var tUID : Integer = GetIntValueByIndex(gc_stack_unit_iTargetUID);
      [*] = ;   var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;   var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;   var attackAnim : String = '';
      [*] = ;   var bCrush : Boolean = GetBoolValueByIndex(gc_stack_unit_bCrush);
      [*] = ;   var bRoundAttack : Boolean = GetBoolValueByIndex(gc_stack_unit_bRoundAttack);
      [*] = ;   var playNow : Boolean = false;
      [*] = ;
      [*] = ;   _gv_traceState(_log_name+'['+GetGameObjectCustomNameByHandle(myGOHandle)+',AC:'+IntToStr(myAttackCount)+',I:'+BoolToStr(playInvert)+']',_log_trace);
      [*] = ;
      [*] = ;   if myAttackCount > 0 then
      [*] = ;   begin
      [*] = ;      var pMyAttack : Integer = ParserSelectByHandleByIndex(pMyAttackList, 0);
      [*] = ;      var tUID : Integer = ParserGetIntValueByKeyByHandle(pMyAttack, 'UID');
      [*] = ;
      [*] = ;      tGOHandle := GetGameObjectHandleByUniqueId(tUID);
      [*] = ;      var pTarParser : Integer = ParserSelectGameObject(tGOHandle);
      [*] = ;      var pTarAttackList : Integer = ParserSelectByHandleByKey(pTarParser, 'AttackList');
      [*] = ;      var pTarAttackAnimList : Integer = ParserSelectByHandleByKey(pTarParser, 'AttackAnimList');
      [*] = ;      var tCAttack : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCAttackCount);
      [*] = ;      var tStatic : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bStatic);
      [*] = ;
      [*] = ;      var bInvert : Boolean = ParserGetBoolValueByKeyByHandle(pMyAttack, 'Invert');
      [*] = ;
      [*] = ;      if bCrush then
      [*] = ;         attackAnim := 'crushing_blow'
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if bRoundAttack then
      [*] = ;            attackAnim := 'round_attack'
      [*] = ;         else
      [*] = ;            attackAnim := 'attack';
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (not bInvert) or playInvert then
      [*] = ;      begin
      [*] = ;         playNow := true;
      [*] = ;
      [*] = ;         var dirX : Float = GetGameObjectMyTransformedVirtualDirectionX();
      [*] = ;         var dirY : Float = GetGameObjectMyTransformedVirtualDirectionY();
      [*] = ;         var dirZ : Float = GetGameObjectMyTransformedVirtualDirectionZ();
      [*] = ;
      [*] = ;         var dirX1 : Float = GetGameObjectPositionXByHandle(tGOHandle) - GetGameObjectMyPositionX();
      [*] = ;         var dirY1 : Float = GetGameObjectPositionYByHandle(tGOHandle) - GetGameObjectMyPositionY();
      [*] = ;         var dirZ1 : Float = GetGameObjectPositionZByHandle(tGOHandle) - GetGameObjectMyPositionZ();
      [*] = ;
      [*] = ;         var angle : Float = VectorAngle(dirX, dirY, dirZ, dirX1, dirY1, dirZ1);
      [*] = ;
      [*] = ;         if angle > cEpsilonAngle then
      [*] = ;         begin
      [*] = ;            SetGameObjectMyRotatingTargetCoords(GetGameObjectPositionXByHandle(tGOHandle), GetGameObjectPositionYByHandle(tGOHandle), GetGameObjectPositionZByHandle(tGOHandle));
      [*] = ;            SetGameObjectMyTrackPointAnimationNames('', '');
      [*] = ;
      [*] = ;            var tpts : Float = ParserGetFloatValueByKeyByHandle(pMyParser, 'TPTurnStep');
      [*] = ;            SetGameObjectMyTrackPointTurnStep(tpts*angle/60*_misc_CalcBattleSpeedModified(gc_battle_unit_turnspeedmod));
      [*] = ;            SetGameObjectMyTargetRotatingMode('trmToTargetCoordinates');
      [*] = ;         end;
      [*] = ;         if (not SameText(GetGameObjectMyAnimationCycleName(), 'berserk')) then
      [*] = ;         begin
      [*] = ;            _unit_ModifyAnimIntervalFactor(myGOHandle, gc_battle_unit_attackspeedmod);
      [*] = ;            GameObjectMySwitchToTreeAnimationCycles(attackAnim, false, false, false, false);
      [*] = ;            _unit_PlaySound(myGOHandle, 'units', attackAnim);
      [*] = ;
      [*] = ;            if (bCrush) then
      [*] = ;               _unit_SetupFlyText(GetGameObjectMyHandle(), myUID, gc_flytext_CategoryAbility, gc_ability_crushing_blow, 0)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (bRoundAttack) then
      [*] = ;                  _unit_SetupFlyText(GetGameObjectMyHandle(), myUID, gc_flytext_CategoryAbility, gc_ability_round_attack, 0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         ParserClearByHandle(pMyAttackList);
      [*] = ;
      [*] = ;         SetIntValueByIndex(gc_stack_unit_iCAttackCount, 1);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if playInvert {and (curLife = 0)} then
      [*] = ;      begin
      [*] = ;         if _log then _log_gui('CheckAttackAnimation playInvert, does this ever even happen?');
      [*] = ;         IntRegister0 := 0;
      [*] = ;         ExecuteState('CheckDeathAnimation');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not playNow then
      [*] = ;      attackAnim := '';
      [*] = ;
      [*] = ;   CheckAnimation(tGOHandle, attackAnim, playNow, 0);
      [*] = ;
      [*] = ;   var roundTargets : Integer = ParserGetCountByHandle(pMyRoundTargets);
      [*] = ;   if roundTargets > 0 then
      [*] = ;   begin
      [*] = ;      var i,uid : Integer;
      [*] = ;      var animExtraDelay : Float = 0;
      [*] = ;      bThunderStrike := (_unit_CheckAbility(myGOHandle, gc_ability_lightning) > 0);
      [*] = ;
      [*] = ;      for i := roundTargets-1 downto 0 do
      [*] = ;      begin
      [*] = ;         if bThunderStrike then animExtraDelay := animExtraDelay + 0.2;
      [*] = ;         uid := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pMyRoundTargets, i), 'UID');
      [*] = ;         CheckAnimation(GetGameObjectHandleByUniqueId(uid), attackAnim, playNow, animExtraDelay);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if playNow then
      [*] = ;      begin
      [*] = ;         if GetBoolValueByIndex(gc_stack_unit_bFireBreath) then
      [*] = ;            _gui_PlaySound('spells', 'spell24');
      [*] = ;            
      [*] = ;         ParserClearByHandle(pMyRoundTargets);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if playNow then
      [*] = ;   begin
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bCrush, false);
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bRoundAttack, false);
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bFireBreath, false);
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bPoisonBite, false);
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bAstralStrike, false);
      [*] = ;      SetBoolValueByIndex(gc_stack_unit_bLunge, false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   _gv_traceState(_log_name+'[TC:'+IntToStr(GetIntValueByIndex(gc_stack_unit_iCAttackCount))+']',$1000000 or _log_trace);
      [*] = ;end;
      [*] = ;
      [*] = ;SetIntValueByIndex(gc_stack_unit_iTargetUID, 0);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

