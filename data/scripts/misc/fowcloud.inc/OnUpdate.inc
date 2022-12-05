section.begin
   Name = OnUpdate
   UsedFileName = 
   Code : struct.begin
      [*] = ;function IsAccurate(prohnd : Integer) : Boolean; // check if no fog on any neighbour
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   var pProvFog : Integer = ParserSelectByHandleByKey(proHnd, 'Fog');
      [*] = ;   var fog : Integer = ParserGetIntValueByKeyByHandle(pProvFog, IntToStr(gIntRegister_MapMyPlayerIndex));
      [*] = ;   var foginside : Boolean = (fog=2);
      [*] = ;   if foginside then
      [*] = ;   begin
      [*] = ;      var ind : Integer;
      [*] = ;      for ind:=0 to 5 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := prohnd;
      [*] = ;         IntRegister1 := ind;
      [*] = ;         StateMachineExecuteState(GetMapInitMachineHandle, 'map.GetNeighbourHexByIndex', 0);
      [*] = ;         var neighbourHnd : Integer = IntRegister2;
      [*] = ;         if neighbourHnd<>0 then
      [*] = ;         begin
      [*] = ;            var pProvFog : Integer = ParserSelectByHandleByKey(neighbourHnd, 'Fog');
      [*] = ;            var nFog : Integer = ParserGetIntValueByKeyByHandle(pProvFog, IntToStr(gIntRegister_MapMyPlayerIndex));
      [*] = ;            if (nFog<>2) then
      [*] = ;            begin
      [*] = ;               Result := True;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetProvHandleByIndex(proInd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserSelectByHandleByIndex(gStratHexCells.handle, proInd);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoUpdateEffects(goHnd : Integer);
      [*] = ;begin
      [*] = ;   var prohnd : Integer = GetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_prohnd); // province handle
      [*] = ;   var proind : Integer = GetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_proind); // province index
      [*] = ;   var proacc : Integer = GetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_proacc); // province accurate
      [*] = ;   var profog : Integer = GetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_profog); // province fogtype
      [*] = ;   var curind : Integer = GetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_curind); // current index effects : 0 empty (default), 1 fog, 2 accurate, 3 light, 4 flashfog, 5 flashaccurate, 6 flashlight
      [*] = ;   var tarind : Integer = GetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_tarind); // target index effects (to lerp)
      [*] = ;
      [*] = ;   var newhnd : Integer = GetProvHandleByIndex(proind);
      [*] = ;   if (prohnd<>newhnd) then
      [*] = ;   ErrorLog('fowcloud.aix - OnUpdate : invalid/changed province handle');
      [*] = ;   prohnd := newhnd;
      [*] = ;   var pProvFog : Integer = ParserSelectByHandleByKey(prohnd, 'Fog');
      [*] = ;   profog := ParserGetIntValueByKeyByHandle(pProvFog, IntToStr(gIntRegister_MapMyPlayerIndex));
      [*] = ;   var accurate : Boolean = IsAccurate(prohnd);
      [*] = ;   if accurate then
      [*] = ;      proacc := 1
      [*] = ;   else
      [*] = ;      proacc := 0;
      [*] = ;   curind := 0;
      [*] = ;
      [*] = ;   var effHnd : Integer;
      [*] = ;   var effKey : String;
      [*] = ;   var effVisible : Boolean;
      [*] = ;
      [*] = ;   procedure UpdateVisibility(effHnd : Integer; effVisible : Boolean);
      [*] = ;   begin
      [*] = ;      var effPrevVisible : Boolean = GetBehaviourBoolProperty(effHnd, 'Visible'); 
      [*] = ;      var redoAlpha: Boolean = (not effPrevVisible) and (not gBoolRegister_GUIStartup);
      [*] = ;      if (effPrevVisible<>effVisible) then
      [*] = ;      begin
      [*] = ;         if (not effPrevVisible) then // was invisible, make visible
      [*] = ;        begin
      [*] = ;            SetBehaviourBoolProperty(effHnd, 'Visible', True);
      [*] = ;            SetBehaviourBoolProperty(effHnd, 'Enabled', True);
      [*] = ;            SetBehaviourFloatProperty(effHnd, 'AlphaStartFactor', 0);
      [*] = ;            SetBehaviourFloatProperty(effHnd, 'AlphaEndFactor', 1);
      [*] = ;         end
      [*] = ;         else // was visible, make invisible
      [*] = ;         begin
      [*] = ;            SetBehaviourBoolProperty(effHnd, 'Visible', True);
      [*] = ;            SetBehaviourBoolProperty(effHnd, 'Enabled', True);
      [*] = ;            SetBehaviourFloatProperty(effHnd, 'AlphaStartFactor', 1);
      [*] = ;            SetBehaviourFloatProperty(effHnd, 'AlphaEndFactor', 0);
      [*] = ;            redoAlpha := true;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'Visible', effVisible);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'Enabled', effVisible);
      [*] = ;         if effVisible then
      [*] = ;         begin
      [*] = ;            SetBehaviourFloatProperty(effHnd, 'AlphaStartFactor', 0);
      [*] = ;            SetBehaviourFloatProperty(effHnd, 'AlphaEndFactor', 1);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            SetBehaviourFloatProperty(effHnd, 'AlphaStartFactor', 1);
      [*] = ;            SetBehaviourFloatProperty(effHnd, 'AlphaEndFactor', 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if redoAlpha then
      [*] = ;      begin
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'AlphaTime', 1);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'AlphaDelta', 0);
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'AlphaPower', 1);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'AlphaReset', True);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'AlphaDisabled', True);
      [*] = ;         SetBehaviourBoolProperty(effHnd, 'AlphaInvisible', True);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // 1 fog
      [*] = ;   effKey := 'fog';
      [*] = ;   effHnd := GetEffectByKey(goHnd, effKey);
      [*] = ;   effVisible := (profog=2) and (not accurate);
      [*] = ;   UpdateVisibility(effHnd, effVisible);
      [*] = ;   if (effVisible) then curind := 1;
      [*] = ;
      [*] = ;   // 2 accurate
      [*] = ;   effKey := 'accurate';
      [*] = ;   effHnd := GetEffectByKey(goHnd, effKey);
      [*] = ;   effVisible := (profog=2) and (accurate);
      [*] = ;   UpdateVisibility(effHnd, effVisible);
      [*] = ;   if (effVisible) then curind := 2;
      [*] = ;
      [*] = ;   // 3 light
      [*] = ;   effKey := 'light';
      [*] = ;   effHnd := GetEffectByKey(goHnd, effKey);
      [*] = ;   effVisible := (profog=1);
      [*] = ;   UpdateVisibility(effHnd, effVisible);
      [*] = ;   if (effVisible) then curind := 3;
      [*] = ;
      [*] = ;   // 4 flashfog
      [*] = ;   effKey := 'flashfog';
      [*] = ;   effHnd := GetEffectByKey(goHnd, effKey);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Visible', false);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Enabled', false);
      [*] = ;   SetBehaviourStringProperty(effHnd, 'OnEndTimeState', '');
      [*] = ;
      [*] = ;   // 5 flashaccurate
      [*] = ;   effKey := 'flashaccurate';
      [*] = ;   effHnd := GetEffectByKey(goHnd, effKey);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Visible', false);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Enabled', false);
      [*] = ;   SetBehaviourStringProperty(effHnd, 'OnEndTimeState', '');
      [*] = ;
      [*] = ;   // 6 flashlight
      [*] = ;   effKey := 'flashlight';
      [*] = ;   effHnd := GetEffectByKey(goHnd, effKey);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Visible', false);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Enabled', false);
      [*] = ;   SetBehaviourStringProperty(effHnd, 'OnEndTimeState', '');
      [*] = ;
      [*] = ;   // 7 lightning
      [*] = ;   effHnd := GameObjectGetOrCreateEffectFXSourceByHandle(goHnd, 'fowlightning', 'lightning');
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'SleepTime', 0);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'TimeLoop', True);
      [*] = ;   SetBehaviourStringProperty(effHnd, 'OnEndTimeState', '');
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Visible', false);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Enabled', false);
      [*] = ;   SetBehaviourAffineVectorProperty(effHnd, 'Position', 0, 0, 0);
      [*] = ;
      [*] = ;   // 8 glow
      [*] = ;   effHnd := GameObjectGetOrCreateEffectFXSourceByHandle(goHnd, 'fowglow', 'glow');
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'SleepTime', 0);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'TimeLoop', True);
      [*] = ;   SetBehaviourStringProperty(effHnd, 'OnEndTimeState', '');
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Visible', false);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'Enabled', false);
      [*] = ;
      [*] = ;   SetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_status, 1); // idle
      [*] = ;   SetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_prohnd, prohnd);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_proacc, proacc);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_profog, profog);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_curind, curind);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_tarind, 0{tarind});
      [*] = ;   SetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_flanum, 0{flanum});
      [*] = ;   SetGameObjectIntValueIndByHandle(goHnd, gc_GOStack_fowcloud_lignum, 0{lignum});
      [*] = ;
      [*] = ;   var fowuid : Integer = ParserGetIntValueByKeyByHandle(prohnd, 'fowuid');
      [*] = ;   var gouid : Integer = GetGameObjectUniqueIdByHandle(goHnd);
      [*] = ;   if (fowuid<>gouid) then
      [*] = ;   ErrorLog('fowcloud.aix - OnUpdate : invalid/changed fowuid');
      [*] = ;   ParserSetIntValueByKeyByHandle(prohnd, 'fowuid', gouid);
      [*] = ;
      [*] = ;   var behHnd : Integer = GetBehaviourByClassName(goHnd, 'TXMoveRotateWaveBehaviour');
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Enabled', (curind<>0));
      [*] = ;
      [*] = ;   GameObjectCancelDelayExecuteStateByHandle(goHnd);
      [*] = ;   if (curind=1) or (curind=2) then
      [*] = ;   GameObjectDelayExecuteStateByHandle(goHnd, 'DoShowFlash', {60+Random*30}Random*90)
      [*] = ;   else
      [*] = ;   if (curind=3) then
      [*] = ;   GameObjectDelayExecuteStateByHandle(goHnd, 'DoShowFlash', {90+Random*30}Random*120)
      [*] = ;   else
      [*] = ;   GameObjectDelayExecuteStateByHandle(goHnd, 'DoShowLightning', {150+Random*60}Random*210);
      [*] = ;end;
      [*] = ;
      [*] = ;DoUpdateEffects(GetGameObjectMyHandle);
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end

