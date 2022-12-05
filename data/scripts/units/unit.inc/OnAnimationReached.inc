section.begin
   Name = OnAnimationReached
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\ONANIMATIONREACHED';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure DoClearFadeOut(goHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   BehaviourDestroy(GetEffectByKey(goHnd, 'fadeunit'));
      [*] = ;   for i:=GetGameObjectCountChildByHandle(goHnd)-1 downto 0 do
      [*] = ;      DoClearFadeOut(GetGameObjectGOHandleChildByHandle(goHnd, i));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SwitchToIdle(myHandle : Integer;keep_blend : Boolean);
      [*] = ;begin
      [*] = ;   var minFrameBlend : Integer;
      [*] = ;
      [*] = ;   if keep_blend then
      [*] = ;   begin
      [*] = ;      minFrameBlend := GetGameObjectMinFrameBlendByHandle(myHandle);
      [*] = ;      SetGameObjectMinFrameBlendByHandle(myHandle, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   _unit_ModifyAnimIntervalFactor(myHandle, 0);
      [*] = ;   GameObjectMySwitchToTreeAnimationCyclesDefault('idle');
      [*] = ;   if keep_blend then
      [*] = ;      SetGameObjectMinFrameBlendByHandle(myHandle, minFrameBlend);
      [*] = ;end;
      [*] = ;
      [*] = ;var myAnim : String = GetGameObjectMyAnimationCycleName();
      [*] = ;
      [*] = ;if not SameText(myAnim,'idle') then
      [*] = ;begin
      [*] = ;   var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;   var pMyParser : Integer = ParserSelectGameObject(myHandle);
      [*] = ;   var pMyAttackList : Integer = ParserSelectByHandleByKey(pMyParser, 'AttackList');
      [*] = ;   var pMyAttackAnimList : Integer = ParserSelectByHandleByKey(pMyParser, 'AttackAnimList');
      [*] = ;   var actAbility : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iActiveAbility);
      [*] = ;   var attackCount : Integer = ParserGetCountByHandle(pMyAttackList);
      [*] = ;   var attackAnimCount : Integer = ParserGetCountByHandle(pMyAttackAnimList);
      [*] = ;
      [*] = ;   _gv_traceState(_log_name+'[O:'+GetGameObjectMyCustomName()+',A:'+myAnim+',AAC:'+IntToStr(attackAnimCount)+',AC:'+IntToStr(attackCount)+',CAC:'+IntToStr(GetIntValueByIndex(gc_stack_unit_iCAttackCount))+']',_log_trace);
      [*] = ;
      [*] = ;   var bAnimAttack, bAnimWound, bAnimWoundAttack, bAnimShot, bAnimCast, bAnimDeath, bAnimHeal, bAnimParry, bAnimParryAttack, bAnimBerserk, bAnimCrushingBlow, bAnimRoundAttack, bAnimCannibalize : Boolean = False;
      [*] = ;   var skip_anim : Boolean = false;
      [*] = ;
      [*] = ;   case myAnim of
      [*] = ;      'attack' : bAnimAttack := True;
      [*] = ;      'wound' : bAnimWound := True;
      [*] = ;      'woundattack' : bAnimWoundAttack := True;
      [*] = ;      'shot' : bAnimShot := True;
      [*] = ;      'cast' : bAnimCast := True;
      [*] = ;      'death' : bAnimDeath := True;
      [*] = ;      'heal' : bAnimHeal := True;
      [*] = ;      'parry' : bAnimParry := True;
      [*] = ;      'parryattack' : bAnimParryAttack := True;
      [*] = ;      'berserk' : bAnimBerserk := True;
      [*] = ;      'crushing_blow' : bAnimCrushingBlow := True;
      [*] = ;      'round_attack' : bAnimRoundAttack := True;
      [*] = ;      'cannibalize' : bAnimCannibalize := True;
      [*] = ;      else skip_anim := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not skip_anim then
      [*] = ;   begin
      [*] = ;      if (bAnimBerserk) then
      [*] = ;      begin
      [*] = ;         SwitchToIdle(myHandle,false);
      [*] = ;         ParserSetIntValueByKeyByHandle(pMyParser, 'BerserkUID', 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (bAnimAttack) or (bAnimCrushingBlow) or (bAnimRoundAttack) or (bAnimParryAttack) or (bAnimWoundAttack) then
      [*] = ;         begin
      [*] = ;            SwitchToIdle(myHandle,true);
      [*] = ;            if (GetGameObjectMyTrackPointCount() > 0) then
      [*] = ;            begin
      [*] = ;               var tpX, tpY, tpZ : Float;
      [*] = ;               var tpCount : Integer = GetGameObjectMyTrackPointCount();
      [*] = ;
      [*] = ;               GetGameObjectMyTrackPointCoordsByIndex(tpCount-1, tpX, tpY, tpZ);
      [*] = ;
      [*] = ;               if VectorDistance(GetGameObjectMyPositionX(), 0, GetGameObjectMyPositionZ(), tpX, 0, tpZ) > gc_HexSize * Sqrt(3) / 2 then
      [*] = ;                  ExecuteState('Move');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (bAnimCast) or (bAnimHeal) or (bAnimCannibalize) or (bAnimParry) then
      [*] = ;            begin
      [*] = ;               SwitchToIdle(myHandle,true);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (bAnimShot) then
      [*] = ;               begin
      [*] = ;                  if GetIntValueByIndex(gc_stack_unit_iShotCount) > 0 then
      [*] = ;                     ExecuteState('VisualFireAttack')
      [*] = ;                  else
      [*] = ;                     SwitchToIdle(myHandle,true);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (bAnimDeath) then
      [*] = ;                  begin
      [*] = ;                     DoClearFadeOut(myHandle);
      [*] = ;                     SetGameObjectVisibleByHandle(myHandle, false);
      [*] = ;                     ExecuteState('AfterDeath');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if (bAnimWound) then
      [*] = ;                        SwitchToIdle(myHandle,true)
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if (bAnimWoundAttack) then
      [*] = ;                        begin
      [*] = ;                           var minFrameBlend : Integer = GetGameObjectMinFrameBlendByHandle(myHandle);
      [*] = ;                           SetGameObjectMinFrameBlendByHandle(myHandle, 0);
      [*] = ;                           _unit_ModifyAnimIntervalFactor(myHandle, gc_battle_unit_attackspeedmod);
      [*] = ;                           GameObjectMySwitchToTreeAnimationCyclesDefault('attack');
      [*] = ;                           SetGameObjectMinFrameBlendByHandle(myHandle, minFrameBlend);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (bAnimAttack) or (bAnimCrushingBlow) or (bAnimRoundAttack) or (bAnimParryAttack) or (bAnimWoundAttack) or (bAnimParry) or (bAnimBerserk) or (bAnimCast) or (bAnimWound) then
      [*] = ;      begin
      [*] = ;         var cAttack : Integer = GetIntValueByIndex(gc_stack_unit_iCAttackCount);
      [*] = ;         var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;         if cAttack > 0 then
      [*] = ;            SetIntValueByIndex(gc_stack_unit_iCAttackCount, cAttack-1);
      [*] = ;
      [*] = ;         if (bAnimBerserk) and (attackCount > 0) then
      [*] = ;            ExecuteState('CheckInvAttackAnimation')
      [*] = ;         else
      [*] = ;         if (ParserGetCountByHandle(pMyAttackAnimList) > 0) then
      [*] = ;            ExecuteState('CheckCAttackAnimation');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (bAnimBerserk) or (bAnimAttack) or (bAnimCrushingBlow) or (bAnimRoundAttack) or (bAnimParryAttack) or (bAnimWoundAttack) or (bAnimHeal) or (bAnimCannibalize) or (bAnimDeath) or (bAnimCast) then
      [*] = ;      begin
      [*] = ;         _log_gui(GetGameObjectMyCustomName()+' animation reached: '+myAnim);
      [*] = ;         _gv_SetBattleLock(-1,_log_name);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;end;
      [*] = ;
      [*] = ;if (_gv_GetBattleLock() = 0) and (gBoolRegister_BattleSwitchPlayer) and (not _misc_IsLanBattle()) then
      [*] = ;begin
      [*] = ;   IntRegister0 := -1;
      [*] = ;   MapExecuteState('bat.EndTurn');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

