section.begin
   Name = CheckDeathAnimation
   Description : struct.begin
      [*] = ;IntRegister0 - condition flags
      [*] = ;   &1 - ignore playable status
      [*] = ;   &2 - ignore life value
      [*] = ;   &4 - ignore counterattack count
      [*] = ;   &8 - ignore berserk uid
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\CHECKDEATHANIMATION';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure DoFadeInRemains();
      [*] = ;begin
      [*] = ;   if (GetIntValueByIndex(gc_stack_unit_iRemainsUID)=0) then
      [*] = ;   begin
      [*] = ;      var plHnd : Integer = _plr_GetOrCreatePlayer('battle.remains', 'misc', 'cmNone', false);
      [*] = ;      var remainsName : String;
      [*] = ;      if gc_RecycleBattleField then
      [*] = ;      remainsName := 'remains_R'
      [*] = ;      else
      [*] = ;      remainsName := 'remains';
      [*] = ;      var goHnd : Integer = _obj_GetInvisibleOrCreate(plHnd, 'misc', remainsName, GetGameObjectMyPositionX(), GetGameObjectMyPositionY(), GetGameObjectMyPositionZ());
      [*] = ;      var goUID : Integer = GameObjectMakeUniqId(goHnd);
      [*] = ;
      [*] = ;      //log('uid='+IntToStr(goUID)+' name='+GetGameObjectCustomNameByHandle(goHnd)+' uidcount='+IntToStr(MapUniqueGOListCount));
      [*] = ;
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iRemainsUID, goUID);
      [*] = ;      var effHnd : Integer = EffectCreateWithKey(goHnd, 'TXLifeColorEffect', 'remains', false);
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Clear', '');
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseAmbient', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseDiffuse', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseEmission', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseSpecular', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseAlphaChannel', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseShininess', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseTexOffset', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseTexScale', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseShaderID', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseBlendMode', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseColor', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseJustColorIfNoLight', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseFrontFace', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseBackFace', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseIgnoreFog', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseNoLighting', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseCullFace', False);
      [*] = ;      SetBehaviourIntProperty(effHnd,  'CurrIndex', 0);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'Enable', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'Loop', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'LoopBackward', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'BounceBackward', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'ZWrite', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'ZTest', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'OnEndReachedFreeEffect', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseOwnerAlpha', False);
      [*] = ;      //SetBehaviourStringProperty(effHnd, 'OnEndReachedState', 'OnRemains');
      [*] = ;      //SetBehaviourIntProperty(effHnd, 'OnReachedObject', GetGameObjectMyHandle);
      [*] = ;      //SetBehaviourIntProperty(effHnd, 'BlendingMode', 1); // bmTransparency
      [*] = ;      //SetBehaviourIntProperty(effHnd, 'FaceCulling', 1);  // fcCull
      [*] = ;      var frameCount : Integer = GetGameObjectAnimationCycleCountFrameByHandle(GetGameObjectMyHandle, 'death');
      [*] = ;      var intervalFactor : Float = GetGameObjectIntervalFactorByHandle(GetGameObjectMyHandle);
      [*] = ;      var orignInterval : Integer = GetGameObjectOrignIntervalByHandle(GetGameObjectMyHandle);
      [*] = ;      var totalTime : Float = 2*frameCount*orignInterval/(1000*intervalFactor);
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Add', '');
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel[0]', 0);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Time[0]', totalTime);
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Add', '');
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel[1]', 1);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Time[1]', totalTime);
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Add', '');
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel[2]', 1);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Time[2]', 0);
      [*] = ;
      [*] = ;      _fx_RunNodeFX(goHnd, 'fxdeathskull'); //GameObjectPFXSrcLibCreateByHandle(goHnd, 'deathcloudskull', 'deathcloudskull');
      [*] = ;      //GameObjectPFXSrcLibCreateByHandle(goHnd, 'deathcloudskullglow', 'deathcloudskullglow'); // don't forget about glow material
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoFadeOutUnit(goHnd : Integer; bFadeInRemains : Boolean);
      [*] = ;begin
      [*] = ;   if (not GetGameObjectIsParent(goHnd)) or (GetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iRemainsUID)=0) then
      [*] = ;   begin
      [*] = ;      if (GetGameObjectIsParent(goHnd)) and (bFadeInRemains) then
      [*] = ;      begin
      [*] = ;         var unitID : Integer = GetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iUnitID);
      [*] = ;         var summoned : Boolean = GetGameObjectBoolValueIndByHandle(goHnd, gc_stack_unit_bSummoned);
      [*] = ;         var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;         var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;         ExecuteState('IsFullDestroy');
      [*] = ;         if not BoolRegister0 then
      [*] = ;            DoFadeInRemains();
      [*] = ;      end;
      [*] = ;      var effHnd : Integer = EffectCreateWithKey(goHnd, 'TXAlphaFadeAnimationEffect', 'fadeunit', false);
      [*] = ;      if effHnd<>0 then
      [*] = ;      begin
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'InEnabled', True);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'InStartTime', 0);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'InEndTime', 1);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'InStartAlpha', 1);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'InEndAlpha', 0);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'OutEnabled', False);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'OutStartTime', 0);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'OutEndTime', 1);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'OutStartAlpha', 1);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'OutEndAlpha', 0);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'UseZWrite', True);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'UseBlend', True);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'UseAlpha', True);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'UseColor', False);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'UseCull', True);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'RenderDeferred', True);
      [*] = ;         if (GetGameObjectIsParent(goHnd)) then
      [*] = ;            SetBehaviourStringProperty(effHnd, 'AnimNameOnly', 'death')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var startFrame, endFrame : Integer;
      [*] = ;            GetGameObjectFrameAnimationDataByHandle(GetGameObjectRootHandleByHandle(goHnd), 'death', startFrame, endFrame);
      [*] = ;            SetBehaviourIntProperty(effHnd, 'AnimStartFrame', startFrame);
      [*] = ;            SetBehaviourIntProperty(effHnd, 'AnimEndFrame', endFrame);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=GetGameObjectCountChildByHandle(goHnd)-1 downto 0 do
      [*] = ;         DoFadeOutUnit(GetGameObjectGOHandleChildByHandle(goHnd, i), bFadeInRemains);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;var deathAnimReady : Integer = GetIntValueByIndex(gc_stack_unit_iDeathAnimReady);
      [*] = ;var bPlayable : Boolean = GetGameObjectMyPlayableObject();
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName+', CL: '+IntToStr(curLife)+', DAR: '+IntToStr(deathAnimReady)+', P: '+BoolToStr(bPlayable)+', BL: '+IntToStr(_gv_GetBattleLock())+']',_log_trace);
      [*] = ;
      [*] = ;if (deathAnimReady <= 0) and (bPlayable or gBoolRegister_BattleEndBattle) and (curLife <= 0) and (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;   var tfHandle,i,sf,ef : Integer;
      [*] = ;   var tfBaseName : String;
      [*] = ;   var b : Boolean = false;
      [*] = ;
      [*] = ;   var nodeID : Integer = _fx_GetIDByNodeName('fxspiderwebfinish');
      [*] = ;   if (_fx_FindFXHandleByID(myGOHandle, true, nodeID)<>0) then
      [*] = ;      _fx_GetOrCreateFXByID(myGOHandle, 'fxspiderwebfinish', 0, 0, 0, 0, 0, nodeID);
      [*] = ;
      [*] = ;   nodeID := _fx_GetIDByNodeName('fxstone');
      [*] = ;   if (_fx_FindFXHandleByID(myGOHandle, true, nodeID)<>0) then
      [*] = ;      _fx_GetOrCreateFXByID(myGOHandle, 'fxstonefinish', 0, 0, 0, 0, 0, nodeID);
      [*] = ;
      [*] = ;   nodeID := _fx_GetIDByNodeName('fx_freeze');
      [*] = ;   if (_fx_FindFXHandleByID(myGOHandle, true, nodeID)<>0) then
      [*] = ;      _fx_GetOrCreateFXByID(myGOHandle, 'fx_unfreeze', 0, 0, 0, 0, 0, nodeID);
      [*] = ;
      [*] = ;   nodeID := _fx_GetIDByNodeName('fx_stoneskin');
      [*] = ;   if (_fx_FindFXHandleByID(myGOHandle, true, nodeID)<>0) then
      [*] = ;      _fx_GetOrCreateFXByID(myGOHandle, 'fx_stoneskin_destroy', 0, 0, 0, 0, 0, nodeID);
      [*] = ;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   ExecuteState('ShowTrueForm');
      [*] = ;   tfHandle := IntRegister0;
      [*] = ;   tfBaseName := GetGameObjectBaseNameByHandle(tfHandle);
      [*] = ;
      [*] = ;   for i := 0 to 4-1 do
      [*] = ;   begin
      [*] = ;      case i of
      [*] = ;         0 : b := SameText(tfBaseName, 'skeleton');
      [*] = ;         1 : b := SameText(tfBaseName, 'ballista');
      [*] = ;         2 : b := SameText(tfBaseName, 'catapult');
      [*] = ;         3 : b := SameText(tfBaseName, 'juggernaut');
      [*] = ;      end;
      [*] = ;      if b then
      [*] = ;      begin
      [*] = ;         _fx_ClearFX(tfHandle, true, true);
      [*] = ;         ReloadGameObjectProperties(tfHandle, '', tfBaseName + '_death');
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _unit_PlaySound(tfHandle, 'units', 'death');
      [*] = ;   _unit_PlaySoundLoop(tfHandle, 'units', 'walk', gc_SoundLoopTagWalk, False);
      [*] = ;
      [*] = ;   var pUnit : Integer = _unit_GetUnitParserByID(GetGameObjectIntValueIndByHandle(tfHandle, gc_stack_unit_iUnitID)); //tfHandle is goHandle if no TrueForm exists.
      [*] = ;   var myUnitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;   DoFadeOutUnit(tfHandle, ((myUnitType<>2) and (myUnitType<>4)));
      [*] = ;
      [*] = ;   if SameText(tfBaseName, 'skeleton') then
      [*] = ;      SetGameObjectCurrentFrameBlendByHandle(tfHandle, -1);
      [*] = ;
      [*] = ;   ParserClearByHandle(ParserSelectByHandleByKey(pMyParser, 'AttackList'));
      [*] = ;   ParserClearByHandle(ParserSelectByHandleByKey(pMyParser, 'AttackAnimList'));
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCAttackCount, 0);
      [*] = ;   SetGameObjectIntValueIndByHandle(tfHandle,gc_stack_unit_iCAttackCount, 0);
      [*] = ;   SetGameObjectIntValueIndByHandle(tfHandle,gc_stack_unit_iCurLife, 0);
      [*] = ;   SetGameObjectPlayableObjectByHandle(tfHandle, false);
      [*] = ;
      [*] = ;   var curAnim : String = GetGameObjectMyFrameAnimationName; // write off the current animation's battle lock in case the animation didn't manage to finish before death anim is started.
      [*] = ;   if (curAnim = 'berserk') or (curAnim = 'attack') or (curAnim = 'crushing_blow') or (curAnim = 'round_attack') or (curAnim = 'parryattack') or (curAnim = 'woundattack') or (curAnim = 'heal') or (curAnim = 'cannibalize') or (curAnim = 'death') or (curAnim = 'cast') then
      [*] = ;      _gv_SetBattleLock(-1,_log_name);
      [*] = ;
      [*] = ;   if GetGameObjectFrameAnimationDataByHandle(tfHandle, 'death', sf, ef) then // does death animation exist at all
      [*] = ;   begin
      [*] = ;      _unit_ModifyAnimIntervalFactor(tfHandle, gc_battle_unit_deathspeedmod);
      [*] = ;      GameObjectSwitchToTreeAnimationCyclesDefaultByHandle(tfHandle, 'death');
      [*] = ;      SetGameObjectAnimationCyclesModeByHandle(tfHandle, 'acmPlayOnce');
      [*] = ;      _gv_SetBattleLock(1,_log_name);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      ErrorLogI(_log_name+' '+GetGameObjectCustomNameByHandle(tfHandle)+' has no death animation!');
      [*] = ;
      [*] = ;   gBoolRegister_GUIBattleResetHexGrid := True;
      [*] = ;
      [*] = ;   _fx_ShowEnvironmentAroundTacticalDeadUnit(GetGameObjectMyHandle());
      [*] = ;
      [*] = ;   ExecuteState('ApplyAllVisualParams');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

