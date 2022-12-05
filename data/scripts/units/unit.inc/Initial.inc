section.begin
   Name = Initial
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\INITIAL';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myBaseName : String = GetGameObjectMyBaseName();
      [*] = ;var scaleAbs : Float = 0;
      [*] = ;var tpms : Float = 0; //track point move step
      [*] = ;var waif : Float = 1; //walk animation interval factor
      [*] = ;var bVisibleBattle : Boolean = _misc_IsVisibleBattle();
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+myBaseName+']',_log_trace);
      [*] = ;
      [*] = ;var uid : Integer = GetGameObjectUniqueIdByHandle(myHandle);
      [*] = ;if (GetVarsCount()=0) or (uid=0) or (not GetGameObjectMyPlayableObject()) or (not GetGameObjectMyVisible()) then
      [*] = ;begin
      [*] = ;   if uid = 0 then
      [*] = ;      uid := GameObjectMakeUniqId(myHandle);
      [*] = ;   
      [*] = ;   // Setup stack
      [*] = ;   if (not gBoolRegister_Loading) then
      [*] = ;   begin
      [*] = ;      ClearVariables();
      [*] = ;      _obj_ResetStackVariables(myHandle, 'BattleUnit');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var runNodeFX : String = '';
      [*] = ;
      [*] = ;   if not bVisibleBattle then
      [*] = ;   begin
      [*] = ;      waif := 0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var unitID : Integer = GetIntValueByIndex(gc_stack_unit_iUnitID);
      [*] = ;      if unitID = 0 then
      [*] = ;      begin
      [*] = ;         StringRegister0 := myBaseName;
      [*] = ;         MapExecuteState('GetUnitIDByName');
      [*] = ;         unitID := IntRegister0;
      [*] = ;      end;
      [*] = ;      var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;     
      [*] = ;      runNodeFX := ParserGetValueByKeyByHandle(pUnit, 'FX');
      [*] = ;      tpms := ParserGetFloatValueByKeyByHandle(pUnit, 'TPMS');
      [*] = ;      waif := ParserGetFloatValueByKeyByHandle(pUnit, 'Waif');
      [*] = ;      scaleAbs := ParserGetFloatValueByKeyByHandle(pUnit, 'Scale');
      [*] = ;
      [*] = ;      // We should Load all models when skeleton spawn
      [*] = ;      if SameText(myBaseName,'skeleton') then
      [*] = ;      begin
      [*] = ;         ProjectLoadLodActor('skeleton_death_sword');
      [*] = ;         ProjectLoadLodActor('skeleton_death_skull');
      [*] = ;         ProjectLoadLodActor('skeleton_death_neck');
      [*] = ;         ProjectLoadLodActor('skeleton_death_spine_1');
      [*] = ;         ProjectLoadLodActor('skeleton_death_spine_2');
      [*] = ;         ProjectLoadLodActor('skeleton_death_spine_3');
      [*] = ;         ProjectLoadLodActor('skeleton_death_spine_4');
      [*] = ;         ProjectLoadLodActor('skeleton_death_left_hand_1');
      [*] = ;         ProjectLoadLodActor('skeleton_death_left_hand_2');
      [*] = ;         ProjectLoadLodActor('skeleton_death_left_hand_3');
      [*] = ;         ProjectLoadLodActor('skeleton_death_right_hand_1');
      [*] = ;         ProjectLoadLodActor('skeleton_death_right_hand_2');
      [*] = ;         ProjectLoadLodActor('skeleton_death_right_hand_3');
      [*] = ;         ProjectLoadLodActor('skeleton_death_left_leg_1');
      [*] = ;         ProjectLoadLodActor('skeleton_death_left_leg_2');
      [*] = ;         ProjectLoadLodActor('skeleton_death_left_leg_3');
      [*] = ;         ProjectLoadLodActor('skeleton_death_right_leg_1');
      [*] = ;         ProjectLoadLodActor('skeleton_death_right_leg_2');
      [*] = ;         ProjectLoadLodActor('skeleton_death_right_leg_3');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if SameText(myBaseName,'ballista') then
      [*] = ;      begin
      [*] = ;         ProjectLoadLodActor('ballista_death_part1');
      [*] = ;         ProjectLoadLodActor('ballista_death_part2');
      [*] = ;         ProjectLoadLodActor('ballista_death_part3');
      [*] = ;         ProjectLoadLodActor('ballista_death_part4');
      [*] = ;         ProjectLoadLodActor('ballista_death_spear');
      [*] = ;         ProjectLoadLodActor('ballista_death_wheel1');
      [*] = ;         ProjectLoadLodActor('ballista_death_wheel2');
      [*] = ;         ProjectLoadLodActor('ballista_death_wheel3');
      [*] = ;         ProjectLoadLodActor('ballista_death_wheel4');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if SameText(myBaseName,'catapult') then
      [*] = ;      begin
      [*] = ;         ProjectLoadLodActor('catapult_death_part1');
      [*] = ;         ProjectLoadLodActor('catapult_death_part2');
      [*] = ;         ProjectLoadLodActor('catapult_death_part3');
      [*] = ;         ProjectLoadLodActor('catapult_death_part4');
      [*] = ;         ProjectLoadLodActor('catapult_death_part5');
      [*] = ;         ProjectLoadLodActor('catapult_death_part6');
      [*] = ;         ProjectLoadLodActor('catapult_death_part7');
      [*] = ;         ProjectLoadLodActor('ballista_death_wheel1');
      [*] = ;         ProjectLoadLodActor('ballista_death_wheel2');
      [*] = ;         ProjectLoadLodActor('ballista_death_wheel3');
      [*] = ;         ProjectLoadLodActor('ballista_death_wheel4');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if SameText(myBaseName,'juggernaut') then
      [*] = ;      begin
      [*] = ;         ProjectLoadLodActor('juggernaut_death');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow1');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow10');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow11');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow12');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow2');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow3');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow4');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow5');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow6');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow7');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow8');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_arrow9');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_flag');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_roll1');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_roll2');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_roll3');
      [*] = ;         ProjectLoadLodActor('juggernaut_death_roll4');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetGameObjectMyStateTargetPosition(GetGameObjectMyPositionX,GetGameObjectMyPositionY,GetGameObjectMyPositionZ);
      [*] = ;   GameObjectMyTrackPointClear;
      [*] = ;   SetGameObjectMyTrackPointMovementMode('mmNone');
      [*] = ;   SetGameObjectMyTargetRotatingMode('trmNone');
      [*] = ;   SetGameObjectMyAnimationControlerEnabled(true);
      [*] = ;   SetGameObjectMyAnimationCyclesMode('acmLoop');
      [*] = ;   SetGameObjectMyAnimationMode('aamLoop');
      [*] = ;   //SetGameObjectMyOnStateStartCyclesReached('OnStartCyclesReached');
      [*] = ;   SetGameObjectMyOnStateEndCyclesReached('OnAnimationReached');
      [*] = ;   SetGameObjectMyOnStateFBEndCyclesReached('OnFBAnimationReached');
      [*] = ;   SetGameObjectMyOnStateDistanceToPoint('', 0);
      [*] = ;   SetGameObjectMyTrackPointUseAnimationCycles(true);
      [*] = ;   SetGameObjectMyOnStateDirectionReached('OnDirectionReached');
      [*] = ;   SetGameObjectMyOnStateEndPointReached('EndPointReached');
      [*] = ;   //SetGameObjectTrackPointOnStatePresetSwitchReached(myHandle, 'OnPresetSwitch');
      [*] = ;   //SetGameObjectMyOnStateStartFrameReached('OnStartFrameReached');
      [*] = ;   SetGameObjectMyOnStateEndFrameReached('OnEndFrameReached');
      [*] = ;   SetGameObjectSTOHandleByHandle(myHandle, 0);
      [*] = ;   SetGameObjectMyPlayableObject(True);
      [*] = ;   SetGameObjectMyTrackPointAnimationNames('walk', 'idle');
      [*] = ;   SetGameObjectMinFrameBlendByHandle(myHandle, 6);
      [*] = ;   SetGameObjectMaxFrameBlendByHandle(myHandle, 8);
      [*] = ;   SetGameObjectDeferredFrameBlendByHandle(myHandle, false);
      [*] = ;
      [*] = ;   ExecuteState('Idle');
      [*] = ;   SetGameObjectMyCurrentFrame(Floor(Random*GetGameObjectEndFrameByHandle(myHandle)-1));
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      //_unit_PlaySoundLoop(myHandle, 'units', 'flight', gc_SoundLoopTagFlight, True);
      [*] = ;      //_unit_PlaySound(myHandle, 'units', 'rise');
      [*] = ;      //_unit_PlaySound(myHandle, 'units', 'rebirth');
      [*] = ;      SoundManagerPreloadSource('units', 'walk');
      [*] = ;      //SoundManagerPreloadSource('units', 'idle');
      [*] = ;      SoundManagerPreloadSource('units', 'wound');
      [*] = ;      SoundManagerPreloadSource('units', 'rise');
      [*] = ;      SoundManagerPreloadSource('units', 'attack');
      [*] = ;      SoundManagerPreloadSource('units', 'death');
      [*] = ;      SoundManagerPreloadSource('units', 'shot');
      [*] = ;      SoundManagerPreloadSource('units', 'cast');
      [*] = ;      SoundManagerPreloadSource('units', 'berserk');
      [*] = ;      SoundManagerPreloadSource('units', 'crushing_blow');
      [*] = ;      SoundManagerPreloadSource('units', 'round_attack');
      [*] = ;      SoundManagerPreloadSource('units', 'cannibalize');
      [*] = ;      SoundManagerPreloadSource('units', 'parry');
      [*] = ;      SoundManagerPreloadSource('units', 'up');
      [*] = ;      SoundManagerPreloadSource('units', 'down');
      [*] = ;   end;
      [*] = ;
      [*] = ;   //if gBoolRegister_WriteToGrid then
      [*] = ;   //ExecuteState('WriteToGrid');
      [*] = ;
      [*] = ;   //gBoolRegister_WriteToGrid := true;
      [*] = ;
      [*] = ;   if (myBaseName<>'skeleton') and bVisibleBattle then
      [*] = ;   begin
      [*] = ;      if (scaleAbs = 0) then
      [*] = ;         ErrorLogI(_log_name+' invalid scaleAbs. BaseName = ' + myBaseName)
      [*] = ;      else
      [*] = ;         SetGameObjectScaleByHandle(myHandle, scaleAbs, scaleAbs, scaleAbs);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if runNodeFX <> '' then
      [*] = ;      _fx_RunNodeFX(myHandle, runNodeFX);
      [*] = ;end;
      [*] = ;
      [*] = ;if not gBoolRegister_Loading then
      [*] = ;begin
      [*] = ;   ExecuteState('CreateParser');
      [*] = ;   ExecuteState('MakeStartUpgrades');
      [*] = ;end;
      [*] = ;
      [*] = ;var pMy : Integer = ParserSelectGameObject(myHandle);
      [*] = ;if (tpms=0) then
      [*] = ;begin
      [*] = ;   if bVisibleBattle then
      [*] = ;      ErrorLogI(_log_name+' tmps not set. BaseName = ' + myBaseName);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pMy, 'TPMoveStep', GetGameObjectTrackPointMoveStepByHandle(myHandle));
      [*] = ;   ParserSetFloatValueByKeyByHandle(pMy, 'WalkAnimIntervalFactor', 1);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pMy, 'TPTurnStep', 10);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   ParserSetFloatValueByKeyByHandle(pMy, 'TPMoveStep', tpms);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pMy, 'WalkAnimIntervalFactor', waif);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pMy, 'TPTurnStep', tpms*42);
      [*] = ;end;
      [*] = ;_unit_ModifyAnimIntervalFactor(myHandle, 0);
      [*] = ;
      [*] = ;SetGameObjectOnStateDestroyByHandle(myHandle, 'OnDestroy');
      [*] = ;
      [*] = ;//log('uid='+IntToStr(GetGameObjectUniqueIdByHandle(myHandle))+' name='+GetGameObjectMyCustomName+' uidcount='+IntToStr(MapUniqueGOListCount));
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

