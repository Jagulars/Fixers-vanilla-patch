section.begin
   Name = CheckCAttackAnimation
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\CHECKCATTACKANIMATION';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cEpsilonAngle = 10;
      [*] = ;
      [*] = ;var playBerserk : Boolean = false;
      [*] = ;var checkDeath : Boolean = false;
      [*] = ;var bModParams : Boolean = true;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var bThunderStrike : Boolean = false;
      [*] = ;
      [*] = ;procedure CheckAnimation(const goHandle : Integer; const attackAnim : String; const animExtraDelay : Float);
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;   var uid : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;   var bPrimaryTarget : Boolean = uid = GetIntValueByIndex(gc_stack_unit_iTargetUID);
      [*] = ;   
      [*] = ;   var pTarParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   var tCAttack : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCAttackCount);
      [*] = ;
      [*] = ;   var bPlayWound : Boolean = True;
      [*] = ;   
      [*] = ;   var FrameShift : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iDamageFrame);
      [*] = ;   if (attackAnim='parryattack') then
      [*] = ;      FrameShift := FrameShift+GetGameObjectAnimationCycleCountFrameByHandle(myGOHandle, 'parry')
      [*] = ;   else
      [*] = ;   if (attackAnim='woundattack') then
      [*] = ;      FrameShift := FrameShift+GetGameObjectAnimationCycleCountFrameByHandle(myGOHandle, 'wound')
      [*] = ;   else
      [*] = ;   if (attackAnim='wound') then
      [*] = ;      bPlayWound := False;
      [*] = ;   
      [*] = ;   var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myGOHandle);
      [*] = ;   var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myGOHandle);
      [*] = ;   var delayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor) + animExtraDelay;
      [*] = ;
      [*] = ;   Assert((delayTime > 0),_log_name+' CAttack delay time <= 0');
      [*] = ;      
      [*] = ;   if SameText(GetGameObjectDelayExecuteStateNameByHandle(goHandle), 'DeathAnimReady') then
      [*] = ;   begin
      [*] = ;      _log_obj('DeathAnimReady already waiting for delayed execute, executing now');
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'DeathAnimReady');
      [*] = ;   end;
      [*] = ;   GameObjectDelayExecuteStateByHandle(goHandle, 'DeathAnimReady', delayTime);
      [*] = ;
      [*] = ;   if ParserGetIntValueByKeyByHandle(pTarParser, 'BerserkUID') = myUID then
      [*] = ;   begin
      [*] = ;      GameObjectDelayExecuteStateByHandle(goHandle, 'PlayBerserkAnimation', delayTime);
      [*] = ;      playBerserk := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if bPlayWound then
      [*] = ;   begin
      [*] = ;      var bDisplayFX : Boolean = _obj_EnabledByFlag(gc_ObjectFlagBattleFX);
      [*] = ;         
      [*] = ;      if bDisplayFX then
      [*] = ;      begin
      [*] = ;         IntRegister0 := myUID;
      [*] = ;         FloatRegister0 := delayTime;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'BloodBoom');
      [*] = ;      end;
      [*] = ;
      [*] = ;      GameObjectDelayExecuteStateByHandle(goHandle, 'OnDamage', delayTime);
      [*] = ;
      [*] = ;      if bThunderStrike and (not bPrimaryTarget) then
      [*] = ;      begin
      [*] = ;         _gui_PlaySound('spells', 'spell22');
      [*] = ;         if bDisplayFX then
      [*] = ;            _fx_CreateFX(goHandle, 'fx_lightning', 0, 0, 0, 0, delayTime);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if bModParams then
      [*] = ;      begin
      [*] = ;         GameObjectDelayExecuteStateByHandle(myGOHandle, 'ApplyAllVisualParams', delayTime);
      [*] = ;         bModParams := false;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife) > 0) then
      [*] = ;      begin
      [*] = ;         if bDisplayFX and (_unit_CheckAbility(myGOHandle, gc_ability_poison_attack) > 0) and (_unit_CheckAbility(goHandle, gc_ability_poison_immunity) = 0)  then
      [*] = ;            _fx_GetOrCreateFXByID(goHandle, 'fxpoisonattack', 0, 0, 0, 0, 0, 5);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         GameObjectDelayExecuteStateByHandle(goHandle, 'CheckDeathAnimation', delayTime);
      [*] = ;         checkDeath := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if bDisplayFX and (_unit_CheckAbility(goHandle, gc_ability_poison_flesh) > 0) and (_unit_CheckAbility(myGOHandle, gc_ability_poison_immunity) = 0) then
      [*] = ;         _fx_GetOrCreateFXByID(myGOHandle, 'fxpoisonattack', 0, 0, 0, 0, 0, 5);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if _log then _log_obj(_log_name+'[Target: '+GetGameObjectCustomNameByHandle(goHandle)+', Delay: '+FloatToStr(delayTime)+', DAR: '+IntToStr(GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iDeathAnimReady)));
      [*] = ;end;
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyAttackAnimList : Integer = ParserSelectByHandleByKey(pMyParser, 'AttackAnimList');
      [*] = ;var pMyRoundTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'RoundTargets');
      [*] = ;var count : Integer = ParserGetCountByHandle(pMyAttackAnimList);
      [*] = ;
      [*] = ;var berserk : Boolean = SameText(GetGameObjectMyAnimationCycleName(), 'berserk');
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) and (count > 0) and (not berserk) then
      [*] = ;begin
      [*] = ;   var pMyAttackAnim : Integer = ParserSelectByHandleByIndex(pMyAttackAnimList, 0);
      [*] = ;
      [*] = ;   var anim : String = ParserGetValueByKeyByHandle(pMyAttackAnim, 'Animation');
      [*] = ;   var tUID : Integer = ParserGetIntValueByKeyByHandle(pMyAttackAnim, 'UID');
      [*] = ;   var bInvert : Boolean = ParserGetBoolValueByKeyByHandle(pMyAttackAnim, 'Invert'); // when defender first strike, applies to both attacker and defender
      [*] = ;
      [*] = ;   var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;
      [*] = ;   var dirX1 : Float = GetGameObjectPositionXByHandle(tGOHandle) - GetGameObjectMyPositionX();
      [*] = ;   var dirY1 : Float = GetGameObjectPositionYByHandle(tGOHandle) - GetGameObjectMyPositionY();
      [*] = ;   var dirZ1 : Float = GetGameObjectPositionZByHandle(tGOHandle) - GetGameObjectMyPositionZ();
      [*] = ;
      [*] = ;   var angle : Float = VectorAngle(GetGameObjectMyTransformedVirtualDirectionX(), GetGameObjectMyTransformedVirtualDirectionY(), GetGameObjectMyTransformedVirtualDirectionZ(), dirX1, dirY1, dirZ1);
      [*] = ;   var animSnd : String = anim;
      [*] = ;
      [*] = ;   _gv_traceState(_log_name+'['+GetGameObjectCustomNameByHandle(myGOHandle)+',AC:'+IntToStr(count)+',I:'+BoolToStr(bInvert)+',A:'+anim+']',_log_trace);
      [*] = ;   if (StrPos('wound', anim)>0) then
      [*] = ;      animSnd := StrReplace(anim, 'wound', '') // remove wound from woundattack
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (StrPos('parry', anim)>0) and (anim<>'parry') then
      [*] = ;         animSnd := StrReplace(anim, 'parry', ''); // remove parry from parryattack
      [*] = ;   end;
      [*] = ;   if _log then _log_gui('animsound '+animSnd);
      [*] = ;
      [*] = ;   if angle > cEpsilonAngle then
      [*] = ;   begin
      [*] = ;      SetGameObjectMyRotatingTargetCoords(GetGameObjectPositionXByHandle(tGOHandle), GetGameObjectPositionYByHandle(tGOHandle), GetGameObjectPositionZByHandle(tGOHandle));
      [*] = ;      SetGameObjectMyTrackPointAnimationNames('', '');
      [*] = ;
      [*] = ;      var tpts : Float = ParserGetFloatValueByKeyByHandle(pMyParser, 'TPTurnStep');
      [*] = ;      SetGameObjectMyTrackPointTurnStep(tpts*angle/60*_misc_CalcBattleSpeedModified(gc_battle_unit_turnspeedmod));
      [*] = ;      SetGameObjectMyTargetRotatingMode('trmToTargetCoordinates');
      [*] = ;
      [*] = ;      _unit_ModifyAnimIntervalFactor(myGOHandle, gc_battle_unit_attackspeedmod);
      [*] = ;      GameObjectMySwitchToTreeAnimationCycles(anim, false, false, false, false);
      [*] = ;      if (not StrExists(anim, 'wound')) and (not StrExists(anim, 'parry')) then
      [*] = ;         _unit_PlaySound(myGOHandle, 'units', animSnd);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var modifier : Float = gc_battle_unit_attackspeedmod;
      [*] = ;      if SameText('wound', anim) then
      [*] = ;         modifier := gc_battle_unit_woundspeedmod;
      [*] = ;      _unit_ModifyAnimIntervalFactor(myGOHandle, modifier);
      [*] = ;      GameObjectMySwitchToTreeAnimationCycles(anim, false, false, false, false);
      [*] = ;      if (not StrExists(anim, 'wound')) and (not StrExists(anim, 'parry')) then
      [*] = ;         _unit_PlaySound(myGOHandle, 'units', animSnd);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var stFrame, endFrame : Integer;
      [*] = ;   var exist : Boolean = GetGameObjectFrameAnimationDataByHandle(myGOHandle, anim, stFrame, endFrame);
      [*] = ;   if (not exist) and (not StrExists(anim, 'wound')) and (anim <> 'parryattack') then
      [*] = ;      ErrorLogI(_log_name+' '+GetGameObjectMyCustomName() + ' has no animation ' + anim + '!');
      [*] = ;
      [*] = ;   CheckAnimation(tGOHandle, anim, 0);
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
      [*] = ;         CheckAnimation(GetGameObjectHandleByUniqueId(uid), anim, animExtraDelay);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserFreeByHandle(pMyAttackAnim);
      [*] = ;
      [*] = ;   var tPlayable : Boolean = GetGameObjectPlayableObjectByHandle(tGOHandle);
      [*] = ;
      [*] = ;   if bInvert and (not playBerserk) and (not checkDeath) then // when defender strikes first
      [*] = ;   begin
      [*] = ;      var FrameShift : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iDamageFrame);
      [*] = ;      var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myGOHandle);
      [*] = ;      var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myGOHandle);
      [*] = ;      var delayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor);
      [*] = ;
      [*] = ;      var delayTimeFix : Float = delayTime+0.1;
      [*] = ;      //if (bInvert) then delayTimeFix := 0;
      [*] = ;      GameObjectDelayExecuteStateByHandle(tGOHandle, 'CheckInvAttackAnimation', delayTimeFix);
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iTargetUID, 0);
      [*] = ;   ParserClearByHandle(pMyRoundTargets);
      [*] = ;
      [*] = ;   ExecuteState('OnDamage');
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

