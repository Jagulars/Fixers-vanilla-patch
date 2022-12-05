section.begin
   Name = Resurrect
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var speed : Float = _misc_CalcBattleSpeedModified(gc_battle_unit_turnspeedmod);
      [*] = ;
      [*] = ;procedure DoFadeInUnit(goHandle : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var effHnd : Integer = EffectCreateWithKey(goHandle, 'TXLifeColorEffect', 'resurrect', False);
      [*] = ;   if effHnd<>0 then
      [*] = ;   begin
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Clear', '');
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseAmbient', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseDiffuse', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseEmission', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseSpecular', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseShininess', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseTexOffset', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseTexScale', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseShaderID', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseColor', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseJustColorIfNoLight', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseIgnoreFog', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseNoLighting', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseCullFace', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseAlphaChannel', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseBlendMode', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseFrontFace', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseBackFace', True);
      [*] = ;      SetBehaviourIntProperty(effHnd, 'BlendingMode', 1);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'RenderDeferred', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'Loop', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'LoopBackward', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'OnEndReachedFreeEffect', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'Enable', True);
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Add', '');
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel[0]', 0);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Time[0]', 10 / speed);
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Add', '');
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel[1]', 1);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Time[1]', 0);
      [*] = ;      SetBehaviourIntProperty(effHnd, 'CurrIndex', 0);
      [*] = ;   end;
      [*] = ;   for i:=GetGameObjectCountChildByHandle(goHandle)-1 downto 0 do
      [*] = ;      DoFadeInUnit(GetGameObjectGOHandleChildByHandle(goHandle, i));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoFadeOutRemains(goHandle : Integer);
      [*] = ;begin
      [*] = ;   var effHnd : Integer = EffectCreateWithKey(goHandle, 'TXLifeColorEffect', 'remains', False);
      [*] = ;   if effHnd<>0 then
      [*] = ;   begin
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Clear', '');
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseAmbient', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseDiffuse', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseEmission', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseSpecular', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseShininess', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseTexOffset', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseTexScale', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseShaderID', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseColor', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseJustColorIfNoLight', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseIgnoreFog', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseNoLighting', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseCullFace', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseAlphaChannel', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseBlendMode', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseFrontFace', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseBackFace', True);
      [*] = ;      SetBehaviourIntProperty(effHnd, 'BlendingMode', 1);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'RenderDeferred', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'Loop', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'LoopBackward', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'OnEndReachedFreeOwner', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'OnEndReachedFreeEffect', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'Enable', True);
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Add', '');
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel[0]', 1);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Time[0]', 3 / speed);
      [*] = ;      SetBehaviourStringProperty(effHnd, 'Add', '');
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel[1]', 0);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Time[1]', 0);
      [*] = ;      SetBehaviourIntProperty(effHnd, 'CurrIndex', 0);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'UseOwnerAlpha', False);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not gBoolRegister_BattleSimulate) and (not gBoolRegister_QuickBattle) then
      [*] = ;begin
      [*] = ;   ExecuteState('Idle');
      [*] = ;
      [*] = ;   SetGameObjectMyAnimationCyclesMode('acmLoop');
      [*] = ;   SetGameObjectMyVisible(true);
      [*] = ;
      [*] = ;   DoFadeInUnit(myGOHandle);
      [*] = ;
      [*] = ;   var grHandle : Integer = GetGameObjectMyGrHandle;
      [*] = ;   if grHandle <> 0 then
      [*] = ;      GroupAddGameObjectByHandle(grHandle, myGOHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;SetGameObjectMyPlayableObject(true);
      [*] = ;
      [*] = ;ExecuteState('WriteToGrid');
      [*] = ;
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iFear, 0);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct, true);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bResting, false);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_march;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMarch, (IntRegister1 > 0));
      [*] = ;
      [*] = ;var remainsHnd : Integer = GetGameObjectHandleByUniqueId(GetIntValueByIndex(gc_stack_unit_iRemainsUID));
      [*] = ;if (remainsHnd<>0) then
      [*] = ;   DoFadeOutRemains(remainsHnd); //GameObjectDestroyByHandle(remainsHnd);
      [*] = ;SetIntValueByIndex(gc_stack_unit_iRemainsUID, 0);
      [*] = ;
      [*] = ;_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_reincarnation, 0);
      [*] = ;_fx_HideEnvironmentAroundTacticalUnit(myGOHandle);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

