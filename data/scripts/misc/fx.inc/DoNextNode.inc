section.begin
   Name = DoNextNode
   UsedFileName = 
   Code : struct.begin
      [*] = ;const _log = false;
      [*] = ;
      [*] = ;
      [*] = ;{const cParticlePlName = 'particles';
      [*] = ;const cParticlePlRace = 'misc';
      [*] = ;var particlePlHandle : Integer = GetPlayerHandleByName(cParticlePlName);
      [*] = ;if (particlePlHandle=0) then
      [*] = ;   CreatePlayer(cParticlePlName, cParticlePlRace, 'cmNone');}
      [*] = ;
      [*] = ;function GetParentWithTLF(parent : Integer) : Integer;
      [*] = ;begin
      [*] = ;   if (IsGameObjectWithTLF(parent)) then
      [*] = ;   Result := parent
      [*] = ;   else
      [*] = ;   if (not GetGameObjectIsParent(parent)) then
      [*] = ;   Result := GetParentWithTLF(GetGameObjectParentHandle(parent))
      [*] = ;   else
      [*] = ;   Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SwitchAnimation(goHnd : Integer; frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth : Boolean; minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame : Integer; frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName : String);
      [*] = ;begin
      [*] = ;   if (frameAnimationResetBlend) then
      [*] = ;   GameObjectResetFrameAnimationBlend(goHnd);
      [*] = ;
      [*] = ;   if (deferredFrameBlend<>GetGameObjectDeferredFrameBlendByHandle(goHnd)) then
      [*] = ;   SetGameObjectDeferredFrameBlendByHandle(goHnd, deferredFrameBlend);
      [*] = ;
      [*] = ;   if (minFrameBlend<>GetGameObjectMinFrameBlendByHandle(goHnd)) then
      [*] = ;   SetGameObjectMinFrameBlendByHandle(goHnd, minFrameBlend);
      [*] = ;
      [*] = ;   if (maxFrameBlend<>GetGameObjectMaxFrameBlendByHandle(goHnd)) then
      [*] = ;   SetGameObjectMaxFrameBlendByHandle(goHnd, maxFrameBlend);
      [*] = ;
      [*] = ;   if (frameAnimationMode<>'') then
      [*] = ;   begin
      [*] = ;      var currFrameAnimationMode : String = GetGameObjectAnimationModeByHandle(goHnd);
      [*] = ;      if (not SameText(frameAnimationMode, currFrameAnimationMode)) then
      [*] = ;      SetGameObjectAnimationModeByHandle(goHnd, frameAnimationMode);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (frameAnimationName<>'') then
      [*] = ;   begin
      [*] = ;      var currFrameAnimationName : String = GetGameObjectFrameAnimationNameByHandle(goHnd);
      [*] = ;      if (not SameText(frameAnimationName, currFrameAnimationName)) then
      [*] = ;      begin
      [*] = ;         if (frameAnimationBlend) then
      [*] = ;         GameObjectSwitchToFrameAnimationBlendByHandle(goHnd, frameAnimationName, frameAnimationBlendRandom, frameAnimationBlendSmooth, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame)
      [*] = ;         else
      [*] = ;         GameObjectSwitchToFrameAnimationByHandle(goHnd, frameAnimationName, frameAnimationRandom);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (frameFBAnimationName<>'') then
      [*] = ;   GameObjectSetFBFrameAnimationByHandle(goHnd, frameFBAnimationName, frameFBAnimationRandom);
      [*] = ;
      [*] = ;   if (cyclesAnimationLib<>'') then
      [*] = ;   begin
      [*] = ;      var currCyclesAnimationLib : String = GetGameObjectAnimationCyclesListByHandle(goHnd);
      [*] = ;      if (not SameText(cyclesAnimationLib, currCyclesAnimationLib)) then
      [*] = ;      SetGameObjectAnimationCyclesListByHandle(goHnd, cyclesAnimationLib);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (cyclesAnimationEnabled<>GetGameObjectAnimationControlerEnabledByHandle(goHnd)) then
      [*] = ;   SetGameObjectAnimationControlerEnabledByHandle(goHnd, cyclesAnimationEnabled);
      [*] = ;
      [*] = ;   if (cyclesAnimationMode<>'') then
      [*] = ;   begin
      [*] = ;      if _log then _log_Obj('cyclesAnimationMode '+cyclesAnimationMode);
      [*] = ;      var currCyclesAnimationMode : String = GetGameObjectAnimationCyclesModeByHandle(goHnd);
      [*] = ;      if (not SameText(cyclesAnimationMode, currCyclesAnimationMode)) then
      [*] = ;      SetGameObjectAnimationCyclesModeByHandle(goHnd, cyclesAnimationMode);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (cyclesAnimationName<>'') then
      [*] = ;   begin
      [*] = ;      var currCyclesAnimationName : String = GetGameObjectAnimationCycleNameByHandle(goHnd);
      [*] = ;      if (not SameText(cyclesAnimationName, currCyclesAnimationName)) then
      [*] = ;      begin
      [*] = ;         //if (cyclesAnimationMode<>'') then
      [*] = ;         //begin
      [*] = ;            //   var currCyclesAnimationMode : String = GetGameObjectAnimationCyclesModeByHandle(goHnd);
      [*] = ;            //   if (not SameText(cyclesAnimationMode, currCyclesAnimationMode)) then
      [*] = ;            //   SetGameObjectAnimationCyclesModeByHandle(goHnd, cyclesAnimationMode);
      [*] = ;         //end;
      [*] = ;         if (cyclesAnimationTree) then
      [*] = ;         begin
      [*] = ;            if (cyclesAnimationDefault) and (frameAnimationBlend) then
      [*] = ;            GameObjectSwitchToTreeAnimationCyclesBlendDefaultByHandle(goHnd, cyclesAnimationName, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame)
      [*] = ;            else
      [*] = ;            if (cyclesAnimationDefault) then
      [*] = ;            GameObjectSwitchToTreeAnimationCyclesDefaultByHandle(goHnd, cyclesAnimationName)
      [*] = ;            else
      [*] = ;            if (frameAnimationBlend) then
      [*] = ;            GameObjectSwitchToTreeAnimationCyclesBlendByHandle(goHnd, cyclesAnimationName, cyclesAnimationRandom, frameAnimationRandom, cyclesFBAnimationRandom, frameFBAnimationRandom, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame)
      [*] = ;            else
      [*] = ;            GameObjectSwitchToTreeAnimationCyclesByHandle(goHnd, cyclesAnimationName, cyclesAnimationRandom, frameAnimationRandom, cyclesFBAnimationRandom, frameFBAnimationRandom);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (cyclesAnimationDefault) and (frameAnimationBlend) then
      [*] = ;            GameObjectSwitchToAnimationCyclesBlendDefaultByHandle(goHnd, cyclesAnimationName, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame)
      [*] = ;            else
      [*] = ;            if (cyclesAnimationDefault) then
      [*] = ;            GameObjectSwitchToAnimationCyclesDefaultByHandle(goHnd, cyclesAnimationName)
      [*] = ;            else
      [*] = ;            if (frameAnimationBlend) then
      [*] = ;            GameObjectSwitchToAnimationCyclesBlendByHandle(goHnd, cyclesAnimationName, cyclesAnimationRandom, frameAnimationRandom, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame)
      [*] = ;            else
      [*] = ;            GameObjectSwitchToAnimationCyclesByHandle(goHnd, cyclesAnimationName, cyclesAnimationRandom, frameAnimationRandom);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (cyclesFBAnimationName<>'') then
      [*] = ;   begin
      [*] = ;      var currCyclesFBAnimationName : String = GetGameObjectFBAnimationCycleNameByHandle(goHnd);
      [*] = ;      if (not SameText(cyclesFBAnimationName, currCyclesFBAnimationName)) then
      [*] = ;      begin
      [*] = ;         //if (cyclesAnimationMode<>'') then
      [*] = ;         //begin
      [*] = ;            //   var currCyclesAnimationMode : String = GetGameObjectAnimationCyclesModeByHandle(goHnd);
      [*] = ;            //   if (not SameText(cyclesAnimationMode, currCyclesAnimationMode)) then
      [*] = ;            //   SetGameObjectAnimationCyclesModeByHandle(goHnd, cyclesAnimationMode);
      [*] = ;         //end;
      [*] = ;         if (cyclesFBAnimationDefault) and (cyclesFBAnimationBlend) then
      [*] = ;         GameObjectSwitchToFBAnimationCyclesBlendDefaultByHandle(goHnd, cyclesFBAnimationName, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame)
      [*] = ;         else
      [*] = ;         if (cyclesAnimationDefault) then
      [*] = ;         GameObjectSwitchToFBAnimationCyclesDefaultByHandle(goHnd, cyclesFBAnimationName)
      [*] = ;         else
      [*] = ;         if (frameAnimationBlend) then
      [*] = ;         GameObjectSwitchToFBAnimationCyclesBlendByHandle(goHnd, cyclesFBAnimationName, cyclesFBAnimationRandom, frameFBAnimationRandom, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame)
      [*] = ;         else
      [*] = ;         GameObjectSwitchToFBAnimationCyclesByHandle(goHnd, cyclesFBAnimationName, cyclesFBAnimationRandom, frameFBAnimationRandom);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SwitchChildrenAnimation(goHnd : Integer; frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth : Boolean; minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame : Integer; frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName : String);
      [*] = ;begin
      [*] = ;   var i, goChild : Integer;
      [*] = ;   for i:=0 to GetGameObjectCountChildByHandle(goHnd)-1 do
      [*] = ;   begin
      [*] = ;      goChild := GetGameObjectGOHandleChildByHandle(goHnd, i);
      [*] = ;      SwitchAnimation(goChild, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      SwitchChildrenAnimation(goChild, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOrCreateParserGameObject(goHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserSelectGameObject(goHnd);
      [*] = ;   if (Result=0) then
      [*] = ;   Result := ParserCreateGameObject(goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetParserGameObject(goHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserSelectGameObject(goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOrCreateStructGameObject(const goHnd : Integer; const structKey : String) : Integer;
      [*] = ;begin
      [*] = ;   var parserHnd : Integer = GetOrCreateParserGameObject(goHnd);
      [*] = ;   Result := ParserSelectByHandleByKey(parserHnd, structKey);
      [*] = ;   if (Result=0) then
      [*] = ;   Result := ParserAddChildByIndex(parserHnd, structKey);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetStructGameObject(const goHnd : Integer; const structKey : String) : Integer;
      [*] = ;begin
      [*] = ;   var parserHnd : Integer = GetParserGameObject(goHnd);
      [*] = ;   Result := ParserSelectByHandleByKey(parserHnd, structKey);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetStructIndexOfValue(const structHnd : Integer; const value : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(structHnd)-1 do
      [*] = ;   if SameText(value, ParserGetValueByIndexByHandle(structHnd, i)) then
      [*] = ;   begin
      [*] = ;      Result := i;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddStructValue(const structHnd : Integer; const value : String);
      [*] = ;begin
      [*] = ;   ParserSetValueByKeyByHandle(structHnd, '*', value);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddStructUniqValue(const structHnd : Integer; const value : String);
      [*] = ;begin
      [*] = ;   var i : Integer = GetStructIndexOfValue(structHnd, value);
      [*] = ;   if (i=-1) then
      [*] = ;   AddStructValue(structHnd, value);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetStructIndexOfIntValue(const structHnd, value : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(structHnd)-1 do
      [*] = ;   if (value=ParserGetIntValueByIndexByHandle(structHnd, i)) then
      [*] = ;   begin
      [*] = ;      Result := i;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddStructIntValue(const structHnd, value : Integer);
      [*] = ;begin
      [*] = ;   ParserSetIntValueByKeyByHandle(structHnd, '*', value);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddStructUniqIntValue(const structHnd, value : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer = GetStructIndexOfIntValue(structHnd, value);
      [*] = ;   if (i=-1) then
      [*] = ;   AddStructIntValue(structHnd, value);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetUseIdentityMatrix(goHnd : Integer; const val : Boolean);
      [*] = ;begin
      [*] = ;   if (GetGameObjectUseIdentityMatrix(goHnd)<>val) then
      [*] = ;   SetGameObjectUseIdentityMatrix(goHnd, val);
      [*] = ;   if (GetGameObjectUseNoChildrenRecTransformationChanged(goHnd)<>val) then
      [*] = ;   SetGameObjectUseNoChildrenRecTransformationChanged(goHnd, val);
      [*] = ;   var i, goChild : Integer;
      [*] = ;   for i:=0 to GetGameObjectCountChildByHandle(goHnd)-1 do
      [*] = ;   begin
      [*] = ;      goChild := GetGameObjectGOHandleChildByHandle(goHnd, i);
      [*] = ;      SetUseIdentityMatrix(goChild, val);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ParserGetBoolValueByKeyByHandleDef(const struct : Integer; const key : String; const def : Boolean) : Boolean;
      [*] = ;begin
      [*] = ;   if (ParserGetValueByKeyByHandle(struct, key)<>'') then
      [*] = ;   Result := ParserGetBoolValueByKeyByHandle(struct, key)
      [*] = ;   else
      [*] = ;   Result := def;
      [*] = ;end;
      [*] = ;
      [*] = ;function ParserGetIntValueByKeyByHandleDef(const struct : Integer; const key : String; const def : Integer) : Integer;
      [*] = ;begin
      [*] = ;   if (ParserGetValueByKeyByHandle(struct, key)<>'') then
      [*] = ;   Result := ParserGetIntValueByKeyByHandle(struct, key)
      [*] = ;   else
      [*] = ;   Result := def;
      [*] = ;end;
      [*] = ;
      [*] = ;function ParserGetFloatValueByKeyByHandleDef(const struct : Integer; const key : String; const def : Float) : Float;
      [*] = ;begin
      [*] = ;   if (ParserGetValueByKeyByHandle(struct, key)<>'') then
      [*] = ;   Result := ParserGetFloatValueByKeyByHandle(struct, key)
      [*] = ;   else
      [*] = ;   Result := def;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RndVector(var vx : Float; var vy : Float; var vz : Float; const f, dispRangeX, dispRangeY, dispRangeZ : Float);
      [*] = ;begin
      [*] = ;   var f2 : Float = 2*f;
      [*] = ;
      [*] = ;   var px : Float = dispRangeX*f2;
      [*] = ;   var py : Float = dispRangeY*f2;
      [*] = ;   var pz : Float = dispRangeZ*f2;
      [*] = ;
      [*] = ;   vx := (Random-0.5)*px;
      [*] = ;   vy := (Random-0.5)*py;
      [*] = ;   vz := (Random-0.5)*pz;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DispersionRange(var posx : Float; var posy : Float; var posz : Float; const initx, inity, initz, posdisp, disprangex, disprangey, disprangez : Float);
      [*] = ;begin
      [*] = ;   var vx, vy, vz : Float;
      [*] = ;
      [*] = ;   RndVector(vx, vy, vz, posdisp, disprangex, disprangey, disprangez);
      [*] = ;
      [*] = ;   posx := vx+initx;
      [*] = ;   posy := vy+inity;
      [*] = ;   posz := vz+initz;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RndVectorForScale(var vx : Float; var vy : Float; var vz : Float; const f, dispRangeX, dispRangeY, dispRangeZ : Float);
      [*] = ;begin
      [*] = ;   var f2 : Float = 2*f;
      [*] = ;
      [*] = ;   var px : Float = dispRangeX*f2;
      [*] = ;   var py : Float = dispRangeY*f2;
      [*] = ;   var pz : Float = dispRangeZ*f2;
      [*] = ;
      [*] = ;   var rn : Float = Random;
      [*] = ;
      [*] = ;   vx := (rn-0.5)*px;
      [*] = ;   vy := (rn-0.5)*py;
      [*] = ;   vz := (rn-0.5)*pz;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DispersionRangeForScale(var posx : Float; var posy : Float; var posz : Float; const initx, inity, initz, posdisp, disprangex, disprangey, disprangez : Float);
      [*] = ;begin
      [*] = ;   var vx, vy, vz : Float;
      [*] = ;
      [*] = ;   RndVectorForScale(vx, vy, vz, posdisp, disprangex, disprangey, disprangez);
      [*] = ;
      [*] = ;   posx := vx+initx;
      [*] = ;   posy := vy+inity;
      [*] = ;   posz := vz+initz;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RndVectorAbs(var vx : Float; var vy : Float; var vz : Float; const f, dispRangeX, dispRangeY, dispRangeZ : Float);
      [*] = ;begin
      [*] = ;   var px : Float = dispRangeX*f;
      [*] = ;   var py : Float = dispRangeY*f;
      [*] = ;   var pz : Float = dispRangeZ*f;
      [*] = ;
      [*] = ;   vx := (Random)*px;
      [*] = ;   vy := (Random)*py;
      [*] = ;   vz := (Random)*pz;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DispersionRangeAbs(var posx : Float; var posy : Float; var posz : Float; const initx, inity, initz, posdisp, disprangex, disprangey, disprangez : Float);
      [*] = ;begin
      [*] = ;   var vx, vy, vz : Float;
      [*] = ;
      [*] = ;   RndVectorAbs(vx, vy, vz, posdisp, disprangex, disprangey, disprangez);
      [*] = ;
      [*] = ;   posx := vx+initx;
      [*] = ;   posy := vy+inity;
      [*] = ;   posz := vz+initz;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetHandleSetupFor(const setupFor : String; parentHnd, rootHnd, targetHnd, selfHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   if SameText(setupFor, 'forParent') then
      [*] = ;   Result := parentHnd
      [*] = ;   else
      [*] = ;   if SameText(setupFor, 'forRoot') then
      [*] = ;   Result := rootHnd
      [*] = ;   else
      [*] = ;   if SameText(setupFor, 'forTarget') then
      [*] = ;   Result := targetHnd
      [*] = ;   else
      [*] = ;   //if SameText(setupFor, 'forSelf') then
      [*] = ;   Result := selfHnd;
      [*] = ;   
      [*] = ;   if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;      _log_Obj('   GetHandleSetupFor '+setupFor+': '+IntToStr(Result));
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourHandleByIndex(ownerHnd, behavIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   Result := ParserGetIntValueByIndexByHandle(structBehavioursHnd, behavIndex);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourHandleByKey(ownerHnd : Integer; behavKey : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structBehavioursHnd)-1 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      var behKey : String = GetBehaviourKey(behHnd);
      [*] = ;      if SameText(behKey, behavKey) then
      [*] = ;      begin
      [*] = ;         Result := behHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourHandleByClass(ownerHnd : Integer; behavClass : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structBehavioursHnd)-1 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      var behClass : String = GetBehaviourClassName(behHnd);
      [*] = ;      if SameText(behClass, behavClass) then
      [*] = ;      begin
      [*] = ;         Result := behHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourHandleByKeyAndBase(ownerHnd : Integer; behavKey : String; baseObjectHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structBehavioursHnd)-1 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      var behKey : String = GetBehaviourKey(behHnd);
      [*] = ;      var basHnd : Integer = GetBehaviourBaseObject(behHnd);
      [*] = ;      if (basHnd=baseObjectHnd) and (SameText(behKey, behavKey)) then
      [*] = ;      begin
      [*] = ;         Result := behHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourHandleByClassAndBase(ownerHnd : Integer; behavClass : String; baseObjectHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structBehavioursHnd)-1 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      var behClass : String = GetBehaviourClassName(behHnd);
      [*] = ;      var basHnd : Integer = GetBehaviourBaseObject(behHnd);
      [*] = ;      if (basHnd=baseObjectHnd) and (SameText(behClass, behavClass)) then
      [*] = ;      begin
      [*] = ;         Result := behHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourIndexByHandle(ownerHnd, behavHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structBehavioursHnd)-1 do
      [*] = ;   if (behavHandle=ParserGetIntValueByIndexByHandle(structBehavioursHnd, i)) then
      [*] = ;   begin
      [*] = ;      Result := i;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourIndexByKey(ownerHnd : Integer; behavKey : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structBehavioursHnd)-1 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      var behKey : String = GetBehaviourKey(behHnd);
      [*] = ;      if SameText(behKey, behavKey) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourIndexByClass(ownerHnd : Integer; behavClass : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structBehavioursHnd)-1 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      var behClass : String = GetBehaviourClassName(behHnd);
      [*] = ;      if SameText(behClass, behavClass) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourKeyByIndex(ownerHnd, behavIndex : Integer) : String;
      [*] = ;begin
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, behavIndex);
      [*] = ;   Result := GetBehaviourKey(behHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourKeyByHandle(ownerHnd, behavHandle : Integer) : String;
      [*] = ;begin
      [*] = ;   if (GetOwnerBehaviourIndexByHandle(ownerHnd, behavHandle)=-1) then
      [*] = ;   Result := ''
      [*] = ;   else
      [*] = ;   Result := GetBehaviourKey(behavHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourKeyByClass(ownerHnd : Integer; behavClass : String) : String;
      [*] = ;begin
      [*] = ;   Result := '';
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structBehavioursHnd)-1 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      var behClass : String = GetBehaviourClassName(behHnd);
      [*] = ;      if SameText(behClass, behavClass) then
      [*] = ;      begin
      [*] = ;         Result := GetBehaviourKey(behHnd);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourClassByIndex(ownerHnd, behavIndex : Integer) : String;
      [*] = ;begin
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, behavIndex);
      [*] = ;   Result := GetBehaviourClassName(behHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourClassByHandle(ownerHnd, behavHandle : Integer) : String;
      [*] = ;begin
      [*] = ;   if (GetOwnerBehaviourIndexByHandle(ownerHnd, behavHandle)=-1) then
      [*] = ;   Result := ''
      [*] = ;   else
      [*] = ;   Result := GetBehaviourClassName(behavHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerBehaviourClassByKey(ownerHnd : Integer; behavKey : String) : String;
      [*] = ;begin
      [*] = ;   var behHnd : Integer = GetOwnerBehaviourHandleByKey(ownerHnd, behavKey);
      [*] = ;   Result := GetBehaviourClassName(behHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyOwnerBehaviour(ownerHnd, behavHandle : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;      _log_Obj('DestroyOwnerBehaviour ownerHnd: '+IntToStr(ownerHnd));
      [*] = ;   var behavIndex : Integer = GetOwnerBehaviourIndexByHandle(ownerHnd, behavHandle);
      [*] = ;   if (behavIndex<>-1) then
      [*] = ;   ParserFreeByHandle(ParserSelectByHandleByIndex(GetStructGameObject(ownerHnd, 'Behaviours'), behavIndex));
      [*] = ;   if (immediately) then
      [*] = ;   BehaviourDestroy(behavHandle)
      [*] = ;   else
      [*] = ;   AddObjectToDestroyList(behavHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateOwnerBehaviour(ownerHnd, parentHnd : Integer; behavClass, behavKey : String; uniq : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;      _log_Obj('CreateOwnerBehaviour ownerHnd: '+IntToStr(ownerHnd)+' parentHnd: '+IntToStr(parentHnd));
      [*] = ;   if (behavKey='') then
      [*] = ;   Result := BehaviourCreate(parentHnd, behavClass, uniq, false)
      [*] = ;   else
      [*] = ;   Result := BehaviourCreateWithKey(parentHnd, behavClass, behavKey, false);
      [*] = ;
      [*] = ;   var structBehavioursHnd : Integer = GetOrCreateStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   AddStructUniqIntValue(structBehavioursHnd, Result);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerBehaviours(ownerHnd : Integer; progressChildrenIncluded, immediately : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=ParserGetCountByHandle(structBehavioursHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;         _log_Obj('ClearOwnerBehaviour ownerHnd: '+IntToStr(ownerHnd));
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      var behClass : String = GetBehaviourClassName(behHnd);
      [*] = ;      if (not progressChildrenIncluded) and (SameText(behClass, 'TXProgressChildrenBehaviour')) then continue;
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(structBehavioursHnd, i));
      [*] = ;      if (immediately) then
      [*] = ;      BehaviourDestroy(behHnd)
      [*] = ;      else
      [*] = ;      AddObjectToDestroyList(behHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearBehaviours(ownerHnd : Integer; goHnd : Integer; progressChildrenIncluded, immediately : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var c : Integer = GetBehaviourCount(goHnd);
      [*] = ;   for i:=c-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = GetBehaviourByIndex(goHnd, i);
      [*] = ;      var behClass : String = GetBehaviourClassName(behHnd);
      [*] = ;      //var behKey : String = GetBehaviourKey(behHnd);
      [*] = ;      if (not progressChildrenIncluded) and (SameText(behClass, 'TXProgressChildrenBehaviour')) then continue;
      [*] = ;      DestroyOwnerBehaviour(ownerHnd, behHnd, immediately); //BehaviourDestroy(behHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectHandleByIndex(ownerHnd, effectIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   Result := ParserGetIntValueByIndexByHandle(structEffectsHnd, effectIndex);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectHandleByKey(ownerHnd : Integer; effectKey : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structEffectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      var effKey : String = GetBehaviourKey(effHnd);
      [*] = ;      if SameText(effKey, effectKey) then
      [*] = ;      begin
      [*] = ;         Result := effHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectHandleByClass(ownerHnd : Integer; effectClass : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structEffectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      var effClass : String = GetBehaviourClassName(effHnd);
      [*] = ;      if SameText(effClass, effectClass) then
      [*] = ;      begin
      [*] = ;         Result := effHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectHandleByKeyAndBase(ownerHnd : Integer; effectKey : String; baseObjectHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structEffectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      var effKey : String = GetBehaviourKey(effHnd);
      [*] = ;      var basHnd : Integer = GetBehaviourBaseObject(effHnd);
      [*] = ;      if (basHnd=baseObjectHnd) and (SameText(effKey, effectKey)) then
      [*] = ;      begin
      [*] = ;         Result := effHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectHandleByClassAndBase(ownerHnd : Integer; effectClass : String; baseObjectHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structEffectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      var effClass : String = GetBehaviourClassName(effHnd);
      [*] = ;      var basHnd : Integer = GetBehaviourBaseObject(effHnd);
      [*] = ;      if (basHnd=baseObjectHnd) and (SameText(effClass, effectClass)) then
      [*] = ;      begin
      [*] = ;         Result := effHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectIndexByHandle(ownerHnd, effectHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structEffectsHnd)-1 do
      [*] = ;   if (effectHandle=ParserGetIntValueByIndexByHandle(structEffectsHnd, i)) then
      [*] = ;   begin
      [*] = ;      Result := i;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectIndexByKey(ownerHnd : Integer; effectKey : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structEffectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      var effKey : String = GetBehaviourKey(effHnd);
      [*] = ;      if SameText(effKey, effectKey) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectIndexByClass(ownerHnd : Integer; effectClass : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structEffectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      var effClass : String = GetBehaviourClassName(effHnd);
      [*] = ;      if SameText(effClass, effectClass) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectKeyByIndex(ownerHnd, effectIndex : Integer) : String;
      [*] = ;begin
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, effectIndex);
      [*] = ;   Result := GetBehaviourKey(effHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectKeyByHandle(ownerHnd, effectHandle : Integer) : String;
      [*] = ;begin
      [*] = ;   if (GetOwnerEffectIndexByHandle(ownerHnd, effectHandle)=-1) then
      [*] = ;   Result := ''
      [*] = ;   else
      [*] = ;   Result := GetBehaviourKey(effectHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectKeyByClass(ownerHnd : Integer; effectClass : String) : String;
      [*] = ;begin
      [*] = ;   Result := '';
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structEffectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      var effClass : String = GetBehaviourClassName(effHnd);
      [*] = ;      if SameText(effClass, effectClass) then
      [*] = ;      begin
      [*] = ;         Result := GetBehaviourKey(effHnd);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectClassByIndex(ownerHnd, effectIndex : Integer) : String;
      [*] = ;begin
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, effectIndex);
      [*] = ;   Result := GetBehaviourClassName(effHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectClassByHandle(ownerHnd, effectHandle : Integer) : String;
      [*] = ;begin
      [*] = ;   if (GetOwnerEffectIndexByHandle(ownerHnd, effectHandle)=-1) then
      [*] = ;   Result := ''
      [*] = ;   else
      [*] = ;   Result := GetBehaviourClassName(effectHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerEffectClassByKey(ownerHnd : Integer; effectKey : String) : String;
      [*] = ;begin
      [*] = ;   var effHnd : Integer = GetOwnerEffectHandleByKey(ownerHnd, effectKey);
      [*] = ;   Result := GetBehaviourClassName(effHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyOwnerEffect(ownerHnd, effectHandle : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var effectIndex : Integer = GetOwnerEffectIndexByHandle(ownerHnd, effectHandle);
      [*] = ;   if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;      _log_Obj('DestroyOwnerEffect: '+IntToStr(effectHandle)+' ownerHnd: '+IntToStr(ownerHnd));
      [*] = ;   
      [*] = ;   if (effectIndex<>-1) then
      [*] = ;   ParserFreeByHandle(ParserSelectByHandleByIndex(GetStructGameObject(ownerHnd, 'Effects'), effectIndex));
      [*] = ;   if (immediately) then
      [*] = ;   BehaviourDestroy(effectHandle)
      [*] = ;   else
      [*] = ;   AddObjectToDestroyList(effectHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateOwnerEffect(ownerHnd, parentHnd : Integer; effectClass, effectKey : String; uniq : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   if (effectKey='') then
      [*] = ;   Result := EffectCreate(parentHnd, effectClass, uniq, false)
      [*] = ;   else
      [*] = ;   Result := EffectCreateWithKey(parentHnd, effectClass, effectKey, false);
      [*] = ;   if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;      _log_Obj('CreateOwnerEffect Result: '+IntToStr(Result)+' ownerHnd: '+IntToStr(ownerHnd)+' parentHnd: '+IntToStr(parentHnd));
      [*] = ;
      [*] = ;   var structEffectsHnd : Integer = GetOrCreateStructGameObject(ownerHnd, 'Effects');
      [*] = ;   AddStructUniqIntValue(structEffectsHnd, Result);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateOwnerEffectFXSource(ownerHnd, parentHnd : Integer; libSourceName, libManagerName, effectKey : String) : Integer;
      [*] = ;begin
      [*] = ;   if (libSourceName<>'') then
      [*] = ;   Result := GameObjectGetOrCreateEffectFXSourceByHandle(parentHnd, libSourceName, effectKey)
      [*] = ;   else
      [*] = ;   if (libManagerName<>'') then
      [*] = ;   Result := GameObjectGetOrCreateEffectFXManagerByHandle(parentHnd, libManagerName, effectKey);
      [*] = ;
      [*] = ;   var structEffectsHnd : Integer = GetOrCreateStructGameObject(ownerHnd, 'Effects');
      [*] = ;   AddStructUniqIntValue(structEffectsHnd, Result);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerEffects(ownerHnd : Integer; tlfAnimationIncluded, immediately : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=ParserGetCountByHandle(structEffectsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;         _log_Obj('ClearOwnerEffect '+IntToStr(effHnd)+' ownerHnd: '+IntToStr(ownerHnd));
      [*] = ;      var effClass : String = GetBehaviourClassName(effHnd);
      [*] = ;      if (not tlfAnimationIncluded) and (SameText(effClass, 'TXTLFAnimationEffect')) then continue;
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(structEffectsHnd, i));
      [*] = ;      if (immediately) then
      [*] = ;      BehaviourDestroy(effHnd)
      [*] = ;      else
      [*] = ;      AddObjectToDestroyList(effHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearEffects(ownerHnd, goHnd : Integer; tlfAnimationIncluded, immediately : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var c : Integer = GetEffectCount(goHnd);
      [*] = ;   for i:=c-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = GetEffectByIndex(goHnd, i);
      [*] = ;      var effClass : String = GetBehaviourClassName(effHnd);
      [*] = ;      if (not tlfAnimationIncluded) and (SameText(effClass, 'TXTLFAnimationEffect')) then continue;
      [*] = ;      DestroyOwnerEffect(ownerHnd, effHnd, immediately);
      [*] = ;   end;
      [*] = ;   //EffectClear(goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerDecalsCount(ownerHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   Result := ParserGetCountByHandle(structDecalsHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerDecalHandleByIndex(ownerHnd, decalIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   Result := ParserGetIntValueByIndexByHandle(structDecalsHnd, decalIndex);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerDecalHandleByName(ownerHnd : Integer; decalName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structDecalsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var decHnd : Integer = ParserGetIntValueByIndexByHandle(structDecalsHnd, i);
      [*] = ;      var decNam : String = GetDecalNameByHandle(decHnd);
      [*] = ;      if SameText(decNam, decalName) then
      [*] = ;      begin
      [*] = ;         Result := decHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerDecalIndexByHandle(ownerHnd, decalHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structDecalsHnd)-1 do
      [*] = ;   if (decalHandle=ParserGetIntValueByIndexByHandle(structDecalsHnd, i)) then
      [*] = ;   begin
      [*] = ;      Result := i;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerDecalIndexByName(ownerHnd : Integer; decalName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structDecalsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var decHnd : Integer = ParserGetIntValueByIndexByHandle(structDecalsHnd, i);
      [*] = ;      var decNam : String = GetDecalNameByHandle(decHnd);
      [*] = ;      if SameText(decNam, decalName) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerDecalNameByIndex(ownerHnd, decalIndex : Integer) : String;
      [*] = ;begin
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   var decHnd : Integer = ParserGetIntValueByIndexByHandle(structDecalsHnd, decalIndex);
      [*] = ;   Result := GetDecalNameByHandle(decHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerDecalNameByHandle(ownerHnd, decalHandle : Integer) : String;
      [*] = ;begin
      [*] = ;   if (GetOwnerDecalIndexByHandle(ownerHnd, decalHandle)=-1) then
      [*] = ;   Result := ''
      [*] = ;   else
      [*] = ;   Result := GetDecalNameByHandle(decalHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyOwnerDecal(ownerHnd, decalHandle : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var decalIndex : Integer = GetOwnerDecalIndexByHandle(ownerHnd, decalHandle);
      [*] = ;   if (decalIndex<>-1) then
      [*] = ;   ParserFreeByHandle(ParserSelectByHandleByIndex(GetStructGameObject(ownerHnd, 'Decals'), decalIndex));
      [*] = ;   if (immediately) then
      [*] = ;   DestroyDecalByHandle(decalHandle)
      [*] = ;   else
      [*] = ;   AddObjectToDestroyList(decalHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyOwnerDecalByIndex(ownerHnd, decalIndex : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var decalHandle : Integer = GetOwnerDecalHandleByIndex(ownerHnd, decalIndex);
      [*] = ;   ParserFreeByHandle(ParserSelectByHandleByIndex(GetStructGameObject(ownerHnd, 'Decals'), decalIndex));
      [*] = ;   if (immediately) then
      [*] = ;   DestroyDecalByHandle(decalHandle)
      [*] = ;   else
      [*] = ;   AddObjectToDestroyList(decalHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateOwnerDecal(ownerHnd, parentHnd : Integer; lib, name : String; x, z, a : Float; directAttach, behaviourAttach : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   if (directAttach) then
      [*] = ;   DestroyOwnerDecal(ownerHnd, GetGameObjectDecalHandleByHandle(parentHnd), true);
      [*] = ;
      [*] = ;   Result := AddNewDecalByLibName(parentHnd, x, z, a, lib, name);
      [*] = ;   var structDecalsHnd : Integer = GetOrCreateStructGameObject(ownerHnd, 'Decals');
      [*] = ;   AddStructUniqIntValue(structDecalsHnd, Result);
      [*] = ;
      [*] = ;   if (behaviourAttach) then
      [*] = ;   begin
      [*] = ;      // TODO
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetDecal(name : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := DecalManagerGetDecalHandleByName(name);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerDecals(ownerHnd : Integer; attachedIncluded, immediately : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   for i:=ParserGetCountByHandle(structDecalsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var decalHandle : Integer = ParserGetIntValueByIndexByHandle(structDecalsHnd, i);
      [*] = ;      if (not attachedIncluded) and (GetDecalParentHndByHandle(decalHandle)<>0) then continue;
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(structDecalsHnd, i));
      [*] = ;      if (immediately) then
      [*] = ;      DestroyDecalByHandle(decalHandle)
      [*] = ;      else
      [*] = ;      AddObjectToDestroyList(decalHandle);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerDecalsAttachedOnly(ownerHnd : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   for i:=ParserGetCountByHandle(structDecalsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var decalHandle : Integer = ParserGetIntValueByIndexByHandle(structDecalsHnd, i);
      [*] = ;      if (GetDecalParentHndByHandle(decalHandle)<>0) then
      [*] = ;      begin
      [*] = ;         ParserFreeByHandle(ParserSelectByHandleByIndex(structDecalsHnd, i));
      [*] = ;         if (immediately) then
      [*] = ;         DestroyDecalByHandle(decalHandle)
      [*] = ;         else
      [*] = ;         AddObjectToDestroyList(decalHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerDecalsByName(ownerHnd : Integer; name, matname : String; immediately : Boolean);
      [*] = ;begin
      [*] = ;   //GetDecalMaterialNameByHandle
      [*] = ;   //GetDecalNameByHandle
      [*] = ;   //DecalManagerGetDecalHandleByNameExt
      [*] = ;   var i : Integer;
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   for i:=ParserGetCountByHandle(structDecalsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var decalHandle : Integer = ParserGetIntValueByIndexByHandle(structDecalsHnd, i);
      [*] = ;      if ((name='') or (SameText(name, GetDecalNameByHandle(decalHandle))))
      [*] = ;      and((matname='') or (SameText(matname, GetDecalMaterialNameByHandle(decalHandle)))) then
      [*] = ;      begin
      [*] = ;         ParserFreeByHandle(ParserSelectByHandleByIndex(structDecalsHnd, i));
      [*] = ;         if (immediately) then
      [*] = ;         DestroyDecalByHandle(decalHandle)
      [*] = ;         else
      [*] = ;         AddObjectToDestroyList(decalHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearDecalsByName(ownerHnd : Integer; name, matname : String; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var decalHandle : Integer = DecalManagerGetDecalHandleByNameExt(name, matname);
      [*] = ;   while (decalHandle<>0) do
      [*] = ;   begin
      [*] = ;      DestroyOwnerDecal(ownerHnd, decalHandle, immediately);
      [*] = ;      decalHandle := DecalManagerGetDecalHandleByNameExt(name, matname);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectsCount(ownerHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   Result := ParserGetCountByHandle(structObjectsHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectHandleByIndex(ownerHnd, objectIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   Result := ParserGetIntValueByIndexByHandle(structObjectsHnd, objectIndex);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectHandleByBaseName(ownerHnd : Integer; objectBaseName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structObjectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var objHnd : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, i);
      [*] = ;      var objBase : String = GetGameObjectBaseNameByHandle(objHnd);
      [*] = ;      if SameText(objBase, objectBaseName) then
      [*] = ;      begin
      [*] = ;         Result := objHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectHandleByCustomName(ownerHnd : Integer; objectCustomName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structObjectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var objHnd : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, i);
      [*] = ;      var objCust : String = GetGameObjectCustomNameByHandle(objHnd);
      [*] = ;      if SameText(objCust, objectCustomName) then
      [*] = ;      begin
      [*] = ;         Result := objHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function FindChildHandle(const parentHandle : Integer; hierarchy : Boolean; raceName, baseName, customName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetGameObjectCountChildByHandle(parentHandle)-1 do
      [*] = ;   begin
      [*] = ;      var childHandle : Integer = GetGameObjectGOHandleChildByHandle(parentHandle, i);
      [*] = ;      if ((raceName='') or (SameText(raceName, GetGameObjectRaceNameByHandle(childHandle))))
      [*] = ;      and((baseName='') or (SameText(baseName, GetGameObjectBaseNameByHandle(childHandle))))
      [*] = ;      //and((playerName='') or (SameText(playerName, GetGameObjectPlayerNameByHandle(childHandle))))
      [*] = ;      and((customName='') or (SameText(customName, GetGameObjectCustomNameByHandle(childHandle)))) then
      [*] = ;      begin
      [*] = ;         Result := childHandle;
      [*] = ;         break;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (hierarchy) then
      [*] = ;      Result := FindChildHandle(childHandle, hierarchy, raceName, baseName, customName);
      [*] = ;      if (Result<>0) then break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetChildHandleByIndex(const parentHandle, index : Integer; raceName, baseName, customName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var childHandle : Integer = GetGameObjectGOHandleChildByHandle(parentHandle, index);
      [*] = ;   if ((raceName='') or (SameText(raceName, GetGameObjectRaceNameByHandle(childHandle))))
      [*] = ;   and((baseName='') or (SameText(baseName, GetGameObjectBaseNameByHandle(childHandle))))
      [*] = ;   and((customName='') or (SameText(customName, GetGameObjectCustomNameByHandle(childHandle)))) then
      [*] = ;   begin
      [*] = ;      Result := childHandle;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsChildOfHierarchy(childHnd, parentOfHierarchyHnd : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if (GetGameObjectIsParent(childHnd)) then
      [*] = ;   Result := false
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var parentHnd : Integer = GetGameObjectParentHandle(childHnd);
      [*] = ;      if (parentHnd=parentOfHierarchyHnd) then
      [*] = ;      Result := true
      [*] = ;      else
      [*] = ;      Result := IsChildOfHierarchy(parentHnd, parentOfHierarchyHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectHandleByData(ownerHnd, parentHnd : Integer; hierarchy : Boolean; raceName, baseName, playerName, customName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structObjectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var objHnd : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, i);
      [*] = ;      var objParentHnd : Integer;
      [*] = ;      if (GetGameObjectIsParent(objHnd)) then
      [*] = ;      objParentHnd := 0
      [*] = ;      else
      [*] = ;      objParentHnd := GetGameObjectParentHandle(objHnd);
      [*] = ;      var objRaceName : String = GetGameObjectRaceNameByHandle(objHnd);
      [*] = ;      var objBaseName : String = GetGameObjectBaseNameByHandle(objHnd);
      [*] = ;      var objPlayerName : String = GetGameObjectPlayerNameByHandle(objHnd);
      [*] = ;      var objCustomName : String = GetGameObjectCustomNameByHandle(objHnd);
      [*] = ;      if ((parentHnd=-1) or (parentHnd=objParentHnd) or ((hierarchy) and (IsChildOfHierarchy(objHnd, parentHnd))))
      [*] = ;      and((raceName='') or (SameText(raceName, objRaceName)))
      [*] = ;      and((baseName='') or (SameText(baseName, objBaseName)))
      [*] = ;      and((playerName='') or (SameText(playerName, objPlayerName)))
      [*] = ;      and((customName='') or (SameText(customName, objCustomName))) then
      [*] = ;      begin
      [*] = ;         Result := objHnd;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetObjectHandleByData(parentHnd : Integer; hierarchy : Boolean; raceName, baseName, playerName, customName : String) : Integer;
      [*] = ;begin
      [*] = ;   if (parentHnd<>0) then
      [*] = ;   Result := FindChildHandle(parentHnd, hierarchy, raceName, baseName, customName)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      Result := 0;
      [*] = ;      var plIndex  : Integer = 0;
      [*] = ;      var plCount  : Integer = GetCountOfPlayers;
      [*] = ;      var plHandle : Integer = GetPlayerHandleByName(playerName);
      [*] = ;      if (plHandle<>0) then
      [*] = ;      begin
      [*] = ;         plIndex := GetPlayerIndexByHandle(plHandle);
      [*] = ;         plCount := plIndex+1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (playerName<>'') then
      [*] = ;      plIndex := -1;
      [*] = ;      var i : Integer;
      [*] = ;      if (plIndex>=0) and (plIndex<plCount) then
      [*] = ;      for i:=plIndex to plCount-1 do
      [*] = ;      begin
      [*] = ;         var plHnd : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         var goInd : Integer;
      [*] = ;         for goInd:=0 to GetPlayerGameObjectsCountByHandle(plHnd)-1 do
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = GetGameObjectHandleByIndex(goInd, plHnd);
      [*] = ;            var goRaceName : String = GetGameObjectRaceNameByHandle(goHnd);
      [*] = ;            var goBaseName : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;            var goCustomName : String = GetGameObjectCustomNameByHandle(goHnd);
      [*] = ;            if ((raceName='') or (SameText(raceName, goRaceName)))
      [*] = ;            and((baseName='') or (SameText(baseName, goBaseName)))
      [*] = ;            and((customName='') or (SameText(customName, goCustomName))) then
      [*] = ;            begin
      [*] = ;               Result := goHnd;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectIndexByHandle(ownerHnd, objectHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structObjectsHnd)-1 do
      [*] = ;   if (objectHandle=ParserGetIntValueByIndexByHandle(structObjectsHnd, i)) then
      [*] = ;   begin
      [*] = ;      Result := i;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectIndexByBaseName(ownerHnd : Integer; objectBaseName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structObjectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var objHnd : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, i);
      [*] = ;      var objBase : String = GetGameObjectBaseNameByHandle(objHnd);
      [*] = ;      if SameText(objBase, objectBaseName) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectIndexByCustomName(ownerHnd : Integer; objectCustomName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=0 to ParserGetCountByHandle(structObjectsHnd)-1 do
      [*] = ;   begin
      [*] = ;      var objHnd : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, i);
      [*] = ;      var objCust : String = GetGameObjectCustomNameByHandle(objHnd);
      [*] = ;      if SameText(objCust, objectCustomName) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectBaseNameByIndex(ownerHnd, objectIndex : Integer) : String;
      [*] = ;begin
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   var objHnd : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, objectIndex);
      [*] = ;   Result := GetGameObjectBaseNameByHandle(objHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectBaseNameByHandle(ownerHnd, objectHandle : Integer) : String;
      [*] = ;begin
      [*] = ;   var objInd : Integer = GetOwnerObjectIndexByHandle(ownerHnd, objectHandle);
      [*] = ;   if (objInd=-1) then
      [*] = ;   Result := ''
      [*] = ;   else
      [*] = ;   Result := GetGameObjectBaseNameByHandle(objectHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectBaseNameByCustomName(ownerHnd : Integer; objectCustomName : String) : String;
      [*] = ;begin
      [*] = ;   var objHnd : Integer = GetOwnerObjectHandleByCustomName(ownerHnd, objectCustomName);
      [*] = ;   Result := GetGameObjectBaseNameByHandle(objHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectCustomNameByIndex(ownerHnd, objectIndex : Integer) : String;
      [*] = ;begin
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   var objHnd : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, objectIndex);
      [*] = ;   Result := GetGameObjectCustomNameByHandle(objHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectCustomNameByHandle(ownerHnd, objectHandle : Integer) : String;
      [*] = ;begin
      [*] = ;   var objInd : Integer = GetOwnerObjectIndexByHandle(ownerHnd, objectHandle);
      [*] = ;   if (objInd=-1) then
      [*] = ;   Result := ''
      [*] = ;   else
      [*] = ;   Result := GetGameObjectCustomNameByHandle(objectHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetOwnerObjectCustomNameByBaseName(ownerHnd : Integer; objectBaseName : String) : String;
      [*] = ;begin
      [*] = ;   var objHnd : Integer = GetOwnerObjectHandleByBaseName(ownerHnd, objectBaseName);
      [*] = ;   Result := GetGameObjectCustomNameByHandle(objHnd);
      [*] = ;end;
      [*] = ;   
      [*] = ;function CheckFinished(goHandle : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var status : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_GOStack_fx_status);
      [*] = ;   var childCount : Integer = GetGameObjectCountChildByHandle(goHandle);
      [*] = ;   if gc_LogRecycling then
      [*] = ;      _log_obj('CheckFinished '+IntToStr(goHandle)+' status: '+IntToStr(status)+', childCount: '+IntToStr(childCount)+', parent: '+IntToStr(GetGameObjectParentHandle(goHandle)));
      [*] = ;   Result := (status = 0) or (status = 3) or (status = 4) or (status = 5);
      [*] = ;     
      [*] = ;   var i, childHandle : Integer;
      [*] = ;   for i := 0 to childCount-1 do
      [*] = ;   begin
      [*] = ;      childHandle := GetGameObjectGOHandleChildByHandle(goHandle, i);
      [*] = ;         
      [*] = ;      Result := CheckFinished(childHandle) and Result;
      [*] = ;   end;
      [*] = ;      
      [*] = ;   if Result then
      [*] = ;      SetGameObjectVisibleByHandle(goHandle, false);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyOwnerObject(ownerHnd, objectHandle : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var objectIndex : Integer = GetOwnerObjectIndexByHandle(ownerHnd, objectHandle);
      [*] = ;   if (objectIndex<>-1) then
      [*] = ;   ParserFreeByHandle(ParserSelectByHandleByIndex(GetStructGameObject(ownerHnd, 'Objects'), objectIndex));
      [*] = ;   if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;      _log_obj('DestroyOwnerObject ownerHnd '+IntToStr(objectHandle)+ ' objectHandle '+IntToStr(objectHandle)+ ' objectIndex '+IntToStr(objectIndex)+ ' childCount '+IntToStr(GetGameObjectCountChildByHandle(objectHandle)));
      [*] = ;   
      [*] = ;   if gc_RecycleFX then
      [*] = ;   begin
      [*] = ;      if CheckFinished(objectHandle) then
      [*] = ;         _obj_Recycle(objectHandle);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (immediately) then
      [*] = ;      GameObjectDestroyByHandle(objectHandle)
      [*] = ;   else
      [*] = ;      AddObjectToDestroyList(objectHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyOwnerObjectByIndex(ownerHnd, objectIndex : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var objectHandle : Integer = GetOwnerObjectHandleByIndex(ownerHnd, objectIndex);
      [*] = ;   ParserFreeByHandle(ParserSelectByHandleByIndex(GetStructGameObject(ownerHnd, 'Objects'), objectIndex));
      [*] = ;   
      [*] = ;   if gc_RecycleFX then
      [*] = ;   begin
      [*] = ;      if CheckFinished(objectHandle) then
      [*] = ;         _obj_Recycle(objectHandle);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (immediately) then
      [*] = ;      GameObjectDestroyByHandle(objectHandle)
      [*] = ;   else
      [*] = ;      AddObjectToDestroyList(objectHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateOwnerObject(ownerHnd, parentHnd, playerHnd : Integer; raceName, baseName, customName : String; x, y, z : Float) : Integer;
      [*] = ;begin
      [*] = ;   if (parentHnd<>0) then
      [*] = ;   begin
      [*] = ;      Result := _obj_ChildGetInvisibleOrCreate(parentHnd, raceName, baseName);
      [*] = ;      //Result := GameObjectAddNewChild(parentHnd, raceName, baseName)
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := _obj_GetInvisibleOrCreate(playerHnd, raceName, baseName, x, y, z);
      [*] = ;
      [*] = ;   if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;      _log_Obj('CreateOwnerObject Result: '+IntToStr(Result)+' ownerHnd: '+IntToStr(ownerHnd)+' parentHnd: '+IntToStr(parentHnd));
      [*] = ;
      [*] = ;   if (Result<>0) then
      [*] = ;   begin
      [*] = ;      SetGameObjectCustomNameByHandle(Result, customName);
      [*] = ;      SetGameObjectPositionByHandle(Result, x, y, z);
      [*] = ;      var structObjectsHnd : Integer = GetOrCreateStructGameObject(ownerHnd, 'Objects');
      [*] = ;      AddStructUniqIntValue(structObjectsHnd, Result);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerObjects(ownerHnd : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=ParserGetCountByHandle(structObjectsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var objectHandle : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, i);
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(structObjectsHnd, i));
      [*] = ;   
      [*] = ;      if gc_RecycleFX then
      [*] = ;      begin
      [*] = ;         if CheckFinished(objectHandle) then
      [*] = ;            _obj_Recycle(objectHandle);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (immediately) then
      [*] = ;         GameObjectDestroyByHandle(objectHandle)
      [*] = ;      else
      [*] = ;         AddObjectToDestroyList(objectHandle);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerObjectsByName(ownerHnd : Integer; baseName, customName, playerName : String; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=ParserGetCountByHandle(structObjectsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var objectHandle : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, i);
      [*] = ;      if ((baseName='') or (SameText(baseName, GetGameObjectBaseNameByHandle(objectHandle))))
      [*] = ;      and((customName='') or (SameText(customName, GetGameObjectCustomNameByHandle(objectHandle))))
      [*] = ;      and((playerName='') or (SameText(playerName, GetGameObjectPlayerNameByHandle(objectHandle)))) then
      [*] = ;      begin
      [*] = ;         ParserFreeByHandle(ParserSelectByHandleByIndex(structObjectsHnd, i));
      [*] = ;   
      [*] = ;         if gc_RecycleFX then
      [*] = ;         begin
      [*] = ;            if CheckFinished(objectHandle) then
      [*] = ;               _obj_Recycle(objectHandle);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (immediately) then
      [*] = ;            GameObjectDestroyByHandle(objectHandle)
      [*] = ;         else
      [*] = ;            AddObjectToDestroyList(objectHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateTLFAnimationEffect(ownerHnd, goHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := CreateOwnerEffect(ownerHnd, goHnd, 'TXTLFAnimationEffect', 'TLFAnimation'+IntToStr(goHnd), true);
      [*] = ;   GameObjectRootSetupIdentityRecTransformationByHandle(goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateProgressChildrenBehaviour(ownerHnd, goHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := CreateOwnerBehaviour(ownerHnd, GetGameObjectRootHandleByHandle(goHnd), 'TXProgressChildrenBehaviour', 'ProgressChildren'{+IntToStr(goHnd)}, true);
      [*] = ;   GameObjectRootSetupIdentityRecTransformationByHandle(goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyTLFAnimationEffect(ownerHnd, goHnd : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var effHnd : Integer = GetOwnerEffectHandleByClassAndBase(ownerHnd, 'TXTLFAnimationEffect', goHnd);
      [*] = ;   DestroyOwnerEffect(ownerHnd, effHnd, immediately);
      [*] = ;   GameObjectRootSetupIdentityRecTransformationByHandle(goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyProgressChildrenBehaviour(ownerHnd, goHnd : Integer; immediately : Boolean);
      [*] = ;begin
      [*] = ;   var behHnd : Integer = GetOwnerBehaviourHandleByClass(ownerHnd, 'TXProgressChildrenBehaviour');
      [*] = ;   DestroyOwnerEffect(ownerHnd, behHnd, immediately);
      [*] = ;   GameObjectRootSetupIdentityRecTransformationByHandle(goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoAutoTLFAnimationEffect(ownerHnd, goHnd : Integer);
      [*] = ;begin
      [*] = ;   if (IsGameObjectWithTLF(goHnd)){and (GetGameObjectCountChildByHandle(goHnd)>0)} then
      [*] = ;   CreateTLFAnimationEffect(ownerHnd, goHnd);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetGameObjectCountChildByHandle(goHnd)-1 do
      [*] = ;   DoAutoTLFAnimationEffect(ownerHnd, GetGameObjectGOHandleChildByHandle(goHnd, i));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CalculateHierarchyBehaviours(goHnd : Integer; var count : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetGameObjectCountChildByHandle(goHnd)-1 do
      [*] = ;   begin
      [*] = ;      var chHnd : Integer = GetGameObjectGOHandleChildByHandle(goHnd, i);
      [*] = ;      count := count + GetBehaviourCount(chHnd);
      [*] = ;      count := count + GetEffectCount(chHnd);
      [*] = ;      CalculateHierarchyBehaviours(chHnd, count);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoAutoProgressChildrenBehaviour(ownerHnd, goHnd : Integer);
      [*] = ;begin
      [*] = ;   var count : Integer = 0;
      [*] = ;   CalculateHierarchyBehaviours(goHnd, count);
      [*] = ;   if (count>0) then
      [*] = ;   CreateProgressChildrenBehaviour(ownerHnd, goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetTransformationStruct(goHnd, transformationStruct : Integer);
      [*] = ;begin
      [*] = ;   if (transformationStruct<>0) and (ParserGetCountByHandle(transformationStruct)>0) then
      [*] = ;   begin
      [*] = ;      var useAbsolutePosition : Boolean = ParserGetBoolValueByKeyByHandleDef(transformationStruct, 'useAbsolutePosition', false);
      [*] = ;
      [*] = ;      var initialPositionStruct : Integer = ParserSelectByHandleByKey(transformationStruct, 'initialPosition');
      [*] = ;      var positionDispersion : Float = ParserGetFloatValueByKeyByHandleDef(transformationStruct, 'positionDispersion', 0);
      [*] = ;      var positionDispersionRangeStruct : Integer = ParserSelectByHandleByKey(transformationStruct, 'positionDispersionRange');
      [*] = ;      var positionAbsolute : Boolean = ParserGetBoolValueByKeyByHandleDef(transformationStruct, 'positionAbsolute', false);
      [*] = ;
      [*] = ;      var useAbsoluteScale : Boolean = ParserGetBoolValueByKeyByHandleDef(transformationStruct, 'useAbsoluteScale', false);
      [*] = ;
      [*] = ;      var initialScaleStruct : Integer = ParserSelectByHandleByKey(transformationStruct, 'initialScale');
      [*] = ;      var scaleDispersion : Float = ParserGetFloatValueByKeyByHandleDef(transformationStruct, 'scaleDispersion', 0);
      [*] = ;      var scaleDispersionRangeStruct : Integer = ParserSelectByHandleByKey(transformationStruct, 'scaleDispersionRange');
      [*] = ;      var scaleAbsolute : Boolean = ParserGetBoolValueByKeyByHandleDef(transformationStruct, 'scaleAbsolute', false);
      [*] = ;
      [*] = ;      var selfMatrixStruct : Integer = ParserSelectByHandleByKey(transformationStruct, 'selfMatrix');
      [*] = ;      if (selfMatrixStruct<>0) then
      [*] = ;      begin
      [*] = ;         var isParent : Boolean = GetGameObjectIsParent(goHnd);
      [*] = ;         var useIdentityMatrix : Boolean = ParserGetBoolValueByKeyByHandleDef(selfMatrixStruct, 'useIdentityMatrix', not isParent);
      [*] = ;         var useNoChildrenRecTransformationChanged : Boolean = ParserGetBoolValueByKeyByHandleDef(selfMatrixStruct, 'useNoChildrenRecTransformationChanged', isParent);
      [*] = ;         if (useIdentityMatrix<>GetGameObjectUseIdentityMatrix(goHnd)) then
      [*] = ;         SetGameObjectUseIdentityMatrix(goHnd, useIdentityMatrix);
      [*] = ;         if (useNoChildrenRecTransformationChanged<>GetGameObjectUseNoChildrenRecTransformationChanged(goHnd)) then
      [*] = ;         SetGameObjectUseNoChildrenRecTransformationChanged(goHnd, useNoChildrenRecTransformationChanged);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var parentMatrixStruct : Integer = ParserSelectByHandleByKey(transformationStruct, 'parentMatrix');
      [*] = ;      if (parentMatrixStruct<>0) and (not GetGameObjectIsParent(goHnd)) then
      [*] = ;      begin
      [*] = ;         var goParentHnd : Integer = GetGameObjectParentHandle(goHnd);
      [*] = ;         var isParent : Boolean = GetGameObjectIsParent(goParentHnd);
      [*] = ;         var useIdentityMatrix : Boolean = ParserGetBoolValueByKeyByHandleDef(parentMatrixStruct, 'useIdentityMatrix', false);
      [*] = ;         var useNoChildrenRecTransformationChanged : Boolean = ParserGetBoolValueByKeyByHandleDef(parentMatrixStruct, 'useNoChildrenRecTransformationChanged', true);
      [*] = ;         if (useIdentityMatrix<>GetGameObjectUseIdentityMatrix(goParentHnd)) then
      [*] = ;         SetGameObjectUseIdentityMatrix(goParentHnd, useIdentityMatrix);
      [*] = ;         if (useNoChildrenRecTransformationChanged<>GetGameObjectUseNoChildrenRecTransformationChanged(goParentHnd)) then
      [*] = ;         SetGameObjectUseNoChildrenRecTransformationChanged(goParentHnd, useNoChildrenRecTransformationChanged);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var rootMatrixStruct : Integer = ParserSelectByHandleByKey(transformationStruct, 'rootMatrix');
      [*] = ;      if (rootMatrixStruct<>0) and (not GetGameObjectIsParent(goHnd)) then
      [*] = ;      begin
      [*] = ;         var goRootHnd : Integer = GetGameObjectRootHandleByHandle(goHnd);
      [*] = ;         var isParent : Boolean = GetGameObjectIsParent(goRootHnd);
      [*] = ;         var useIdentityMatrix : Boolean = ParserGetBoolValueByKeyByHandleDef(rootMatrixStruct, 'useIdentityMatrix', not isParent);
      [*] = ;         var useNoChildrenRecTransformationChanged : Boolean = ParserGetBoolValueByKeyByHandleDef(rootMatrixStruct, 'useNoChildrenRecTransformationChanged', isParent);
      [*] = ;         if (useIdentityMatrix<>GetGameObjectUseIdentityMatrix(goRootHnd)) then
      [*] = ;         SetGameObjectUseIdentityMatrix(goRootHnd, useIdentityMatrix);
      [*] = ;         if (useNoChildrenRecTransformationChanged<>GetGameObjectUseNoChildrenRecTransformationChanged(goRootHnd)) then
      [*] = ;         SetGameObjectUseNoChildrenRecTransformationChanged(goRootHnd, useNoChildrenRecTransformationChanged);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var rollAngle : String = ParserGetValueByKeyByHandle(transformationStruct, 'rollAngle');
      [*] = ;      if (rollAngle<>'') then
      [*] = ;      SetGameObjectRollAngleByHandle(goHnd, StrToFloat(rollAngle));
      [*] = ;      var turnAngle : String = ParserGetValueByKeyByHandle(transformationStruct, 'turnAngle');
      [*] = ;      if (turnAngle<>'') then
      [*] = ;      SetGameObjectTurnAngleByHandle(goHnd, StrToFloat(turnAngle));
      [*] = ;      var pitchAngle : String = ParserGetValueByKeyByHandle(transformationStruct, 'pitchAngle');
      [*] = ;      if (pitchAngle<>'') then
      [*] = ;      SetGameObjectPitchAngleByHandle(goHnd, StrToFloat(pitchAngle));
      [*] = ;
      [*] = ;      var setupIdentityRecTransformation : Boolean = ParserGetBoolValueByKeyByHandleDef(transformationStruct, 'setupIdentityRecTransformation', false);
      [*] = ;      var rootSetupIdentityRecTransformation : Boolean = ParserGetBoolValueByKeyByHandleDef(transformationStruct, 'rootSetupIdentityRecTransformation', false);
      [*] = ;
      [*] = ;      var initialPositionX, initialPositionY, initialPositionZ : Float = 0;
      [*] = ;      if (initialPositionStruct<>0) then
      [*] = ;      begin
      [*] = ;         initialPositionX := ParserGetFloatValueByKeyByHandle(initialPositionStruct, 'X');
      [*] = ;         initialPositionY := ParserGetFloatValueByKeyByHandle(initialPositionStruct, 'Y');
      [*] = ;         initialPositionZ := ParserGetFloatValueByKeyByHandle(initialPositionStruct, 'Z');
      [*] = ;      end;
      [*] = ;      var positionDispersionRangeX, positionDispersionRangeY, positionDispersionRangeZ : Float = 0;
      [*] = ;      if (positionDispersionRangeStruct<>0) then
      [*] = ;      begin
      [*] = ;         positionDispersionRangeX := ParserGetFloatValueByKeyByHandle(positionDispersionRangeStruct, 'X');
      [*] = ;         positionDispersionRangeY := ParserGetFloatValueByKeyByHandle(positionDispersionRangeStruct, 'Y');
      [*] = ;         positionDispersionRangeZ := ParserGetFloatValueByKeyByHandle(positionDispersionRangeStruct, 'Z');
      [*] = ;      end;
      [*] = ;      var positionX, positionY, positionZ : Float = 0;
      [*] = ;      DispersionRange(positionX, positionY, positionZ, initialPositionX, initialPositionY, initialPositionZ, positionDispersion, positionDispersionRangeX, positionDispersionRangeY, positionDispersionRangeZ);
      [*] = ;      if (initialPositionStruct<>0) then
      [*] = ;      begin
      [*] = ;         if (useAbsolutePosition) then
      [*] = ;         begin
      [*] = ;            if positionAbsolute then
      [*] = ;            SetGameObjectAbsolutePositionByHandle(goHnd, positionX, positionY, positionZ)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var ax, ay, az : Float;
      [*] = ;               _obj_GetGameObjectAbsolutePosition(goHnd, ax, ay, az, true);
      [*] = ;               SetGameObjectAbsolutePositionByHandle(goHnd, ax+positionX, ay+positionY, az+positionZ);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if positionAbsolute then
      [*] = ;            SetGameObjectPositionByHandle(goHnd, positionX, positionY, positionZ)
      [*] = ;            else
      [*] = ;            //GetGameObjectTLFTransformedPositionZByHandle();
      [*] = ;            SetGameObjectPositionByHandle(goHnd, GetGameObjectPositionXByHandle(goHnd)+positionX, GetGameObjectPositionYByHandle(goHnd)+positionY, GetGameObjectPositionZByHandle(goHnd)+positionZ);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var initialScaleX, initialScaleY, initialScaleZ : Float = 1;
      [*] = ;      if (initialScaleStruct<>0) then
      [*] = ;      begin
      [*] = ;         initialScaleX := ParserGetFloatValueByKeyByHandle(initialScaleStruct, 'X');
      [*] = ;         initialScaleY := ParserGetFloatValueByKeyByHandle(initialScaleStruct, 'Y');
      [*] = ;         initialScaleZ := ParserGetFloatValueByKeyByHandle(initialScaleStruct, 'Z');
      [*] = ;      end;
      [*] = ;      var scaleDispersionRangeX, scaleDispersionRangeY, scaleDispersionRangeZ : Float = 0;
      [*] = ;      if (scaleDispersionRangeStruct<>0) then
      [*] = ;      begin
      [*] = ;         scaleDispersionRangeX := ParserGetFloatValueByKeyByHandle(scaleDispersionRangeStruct, 'X');
      [*] = ;         scaleDispersionRangeY := ParserGetFloatValueByKeyByHandle(scaleDispersionRangeStruct, 'Y');
      [*] = ;         scaleDispersionRangeZ := ParserGetFloatValueByKeyByHandle(scaleDispersionRangeStruct, 'Z');
      [*] = ;      end;
      [*] = ;      var scaleX, scaleY, scaleZ : Float = 0;
      [*] = ;      DispersionRangeForScale(scaleX, scaleY, scaleZ, initialScaleX, initialScaleY, initialScaleZ, scaleDispersion, scaleDispersionRangeX, scaleDispersionRangeY, scaleDispersionRangeZ);
      [*] = ;      if (initialScaleStruct<>0) then
      [*] = ;      begin
      [*] = ;         if scaleAbsolute then
      [*] = ;         SetGameObjectScaleByHandle(goHnd, scaleX, scaleY, scaleZ)
      [*] = ;         else
      [*] = ;         if useAbsoluteScale then
      [*] = ;         begin
      [*] = ;            var x, y, z : Float;
      [*] = ;            GetGameObjectAbsoluteScaleByHandle(goHnd, x, y, z);
      [*] = ;            SetGameObjectScaleByHandle(goHnd, x*scaleX, y*scaleY, z*scaleZ);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         SetGameObjectScaleByHandle(goHnd, GetGameObjectScaleXByHandle(goHnd)*scaleX, GetGameObjectScaleYByHandle(goHnd)*scaleY, GetGameObjectScaleZByHandle(goHnd)*scaleZ);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (setupIdentityRecTransformation) then
      [*] = ;      GameObjectSetupIdentityRecTransformationByHandle(goHnd);
      [*] = ;      if (rootSetupIdentityRecTransformation) then
      [*] = ;      GameObjectRootSetupIdentityRecTransformationByHandle(goHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetStateMachineStruct(goHnd, statemachineStruct : Integer);
      [*] = ;begin
      [*] = ;   if (statemachineStruct<>0) and (ParserGetCountByHandle(statemachineStruct)>0) then
      [*] = ;   begin
      [*] = ;      var interval : Integer = ParserGetIntValueByKeyByHandleDef(statemachineStruct, 'interval', GetGameObjectStateMachineIntervalByHandle(goHnd));
      [*] = ;      var active : Boolean = ParserGetBoolValueByKeyByHandleDef(statemachineStruct, 'active', GetGameObjectStateMachineActiveByHandle(goHnd));
      [*] = ;      var executeState : String = ParserGetValueByKeyByHandle(statemachineStruct, 'executeState');
      [*] = ;      var delayCancel : Boolean = ParserGetBoolValueByKeyByHandleDef(statemachineStruct, 'delayCancel', false);
      [*] = ;      var delayState : String = ParserGetValueByKeyByHandle(statemachineStruct, 'delayState');
      [*] = ;      var delayTime : Float = ParserGetFloatValueByKeyByHandleDef(statemachineStruct, 'delayTime', 0);
      [*] = ;      var switchState : String = ParserGetValueByKeyByHandle(statemachineStruct, 'switchState');
      [*] = ;      var stackStructChild : Integer = ParserSelectByHandleByKey(statemachineStruct, 'stack');
      [*] = ;      var destroyState : String = ParserGetValueByKeyByHandle(statemachineStruct, 'destroyState');
      [*] = ;      var destroyNode : String = ParserGetValueByKeyByHandle(statemachineStruct, 'destroyNode');
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to ParserGetCountByHandle(stackStructChild)-1 do
      [*] = ;      begin
      [*] = ;         var variable : Integer = ParserSelectByHandleByIndex(stackStructChild, i);
      [*] = ;         var key : String = ParserGetKeyName(variable);
      [*] = ;         var value : String = ParserGetValueByIndexByHandle(stackStructChild, i);
      [*] = ;         SetGameObjectValueByHandle(goHnd, key, value);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (interval<>GetGameObjectStateMachineIntervalByHandle(goHnd)) then
      [*] = ;      SetGameObjectStateMachineIntervalByHandle(goHnd, interval);
      [*] = ;
      [*] = ;      if (active<>GetGameObjectStateMachineActiveByHandle(goHnd)) then
      [*] = ;      SetGameObjectStateMachineActiveByHandle(goHnd, active);
      [*] = ;
      [*] = ;      if (executeState<>'') then
      [*] = ;      GameObjectExecuteStateByHandle(goHnd, executeState);
      [*] = ;
      [*] = ;      if (delayCancel) then
      [*] = ;      GameObjectCancelDelayExecuteStateByHandle(goHnd);
      [*] = ;
      [*] = ;      if (delayState<>'') and (delayTime>0) then
      [*] = ;      GameObjectDelayExecuteStateByHandle(goHnd, delayState, delayTime);
      [*] = ;
      [*] = ;      if (switchState<>'') then
      [*] = ;      GameObjectSwitchToStateByHandle(goHnd, switchState);
      [*] = ;
      [*] = ;      if (destroyState<>'') and (not SameText(destroyState, GetGameObjectOnStateDestroyByHandle(goHnd))) then
      [*] = ;      SetGameObjectOnStateDestroyByHandle(goHnd, destroyState);
      [*] = ;      // TODO :
      [*] = ;      //destroyNode
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetCollisionStruct(goHnd, collisionStruct : Integer);
      [*] = ;begin
      [*] = ;   if (collisionStruct<>0) and (ParserGetCountByHandle(collisionStruct)>0) then
      [*] = ;   begin
      [*] = ;      var detection : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'detection', GetGameObjectCollisionDetectionByHandle(goHnd));
      [*] = ;      var rayCastIntersect : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'rayCastIntersect', GetGameObjectRayCastIntersectEnabledByHandle(goHnd));
      [*] = ;      var priority : Integer = ParserGetIntValueByKeyByHandleDef(collisionStruct, 'priority', GetGameObjectCollisionPriorityByHandle(goHnd));
      [*] = ;      var boundingMode : Integer = ParserGetIntValueByKeyByHandleDef(collisionStruct, 'boundingMode', GetGameObjectBoundingModeByHandle(goHnd));
      [*] = ;      var boundingData : Integer = ParserGetIntValueByKeyByHandleDef(collisionStruct, 'boundingData', GetGameObjectBoundingDataByHandle(goHnd));
      [*] = ;      var boundingSpace : Integer = ParserGetIntValueByKeyByHandleDef(collisionStruct, 'boundingSpace', GetGameObjectBoundingSpaceByHandle(goHnd));
      [*] = ;      var boundingAABBStruct : Integer = ParserSelectByHandleByKey(collisionStruct, 'boundingAABB');
      [*] = ;      var boundingAABBMinStruct : Integer = ParserSelectByHandleByKey(boundingAABBStruct, 'min');
      [*] = ;      var boundingAABBMaxStruct : Integer = ParserSelectByHandleByKey(boundingAABBStruct, 'max');
      [*] = ;      var boundingSphere : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'boundingSphere', GetGameObjectCustomBoundingSphereByHandle(goHnd));
      [*] = ;      var collidedState : String = ParserGetValueByKeyByHandle(collisionStruct, 'collidedState');
      [*] = ;      var collidedNode : String = ParserGetValueByKeyByHandle(collisionStruct, 'collidedNode');
      [*] = ;      var uncollidedState : String = ParserGetValueByKeyByHandle(collisionStruct, 'uncollidedState');
      [*] = ;      var uncollidedNode : String = ParserGetValueByKeyByHandle(collisionStruct, 'uncollidedNode');
      [*] = ;      var useCustAABBinSP : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'useCustAABBinSP', GetGameObjectUseCustAABBinSPByHandle(goHnd));
      [*] = ;      var useCameraCollision : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'useCameraCollision', GetGameObjectUseCameraCollisionByHandle(goHnd));
      [*] = ;      var useNoSPCull : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'useNoSPCull', GetGameObjectUseNoSPCullByHandle(goHnd));
      [*] = ;      var uncollideDelta : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'uncollideDelta', GetGameObjectUncollideDeltaByHandle(goHnd));
      [*] = ;      var rayCastUsingTLF : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'rayCastUsingTLF', GetGameObjectRayCastUsingTLFByHandle(goHnd));
      [*] = ;      var rayCastNotifyState : String = ParserGetValueByKeyByHandle(collisionStruct, 'rayCastNotifyState');
      [*] = ;      var rayCastNotifyNode : String = ParserGetValueByKeyByHandle(collisionStruct, 'rayCastNotifyNode');
      [*] = ;      var inertiaEnabled : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'inertiaEnabled', GetGameObjectCollisionInertiaByHandle(goHnd));
      [*] = ;      var inertiaMovable : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'inertiaMovable', GetGameObjectCIMovableByHandle(goHnd));
      [*] = ;      var inertiaMass : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaMass', GetGameObjectCIMassByHandle(goHnd));
      [*] = ;      var inertiaIntersectRadius : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaIntersectRadius', GetGameObjectCIIntersectRadiusByHandle(goHnd));
      [*] = ;      var inertiaMaxDistKoef : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaMaxDistKoef', GetGameObjectCIMaxDistKoefByHandle(goHnd));
      [*] = ;      var inertiaDeltaStep : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaDeltaStep', GetGameObjectCIDeltaStepByHandle(goHnd));
      [*] = ;      var inertiaRotationSpeed : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaRotationSpeed', GetGameObjectCIRotationSpeedByHandle(goHnd));
      [*] = ;      var inertiaStuckAngle : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaStuckAngle', GetGameObjectCIStuckAngleByHandle(goHnd));
      [*] = ;      var inertiaEpsilonAngle : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaEpsilonAngle', GetGameObjectCIEpsilonAngleByHandle(goHnd));
      [*] = ;      var inertiaEpsilonShift : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaEpsilonShift', GetGameObjectCIEpsilonShiftByHandle(goHnd));
      [*] = ;      var inertiaEpsilonMove : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaEpsilonMove', GetGameObjectCIEpsilonMoveByHandle(goHnd));
      [*] = ;      var inertiaDistExtPointEpsilon : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaDistExtPointEpsilon', GetGameObjectCIDistExtPointEpsilonByHandle(goHnd));
      [*] = ;      var inertiaAvoidPointMaxAngle : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaAvoidPointMaxAngle', GetGameObjectCIAvoidPointMaxAngleByHandle(goHnd));
      [*] = ;      var inertiaMaxCollideCounter : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'inertiaMaxCollideCounter', GetGameObjectCIMaxCollideCounterByHandle(goHnd));
      [*] = ;      var bvRayCastIntersectEnabled : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'bvRayCastIntersectEnabled', GetGameObjectBVRayCastIntersectEnabledByHandle(goHnd));
      [*] = ;      var bvUseTrackNode : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'bvUseTrackNode', GetGameObjectBVUseTrackNodeByHandle(goHnd));
      [*] = ;      var bvTestShpereRadius : Float = ParserGetFloatValueByKeyByHandleDef(collisionStruct, 'bvTestShpereRadius', GetGameObjectBVTestShpereRadiusByHandle(goHnd));
      [*] = ;      var bvTestEnabled : Boolean = ParserGetBoolValueByKeyByHandleDef(collisionStruct, 'bvTestEnabled', False{GetGameObjectBVTestEnabledByHandle(goHnd)});
      [*] = ;
      [*] = ;      if (detection<>GetGameObjectCollisionDetectionByHandle(goHnd)) then
      [*] = ;      SetGameObjectCollisionDetectionByHandle(goHnd, detection);
      [*] = ;
      [*] = ;      if (rayCastIntersect<>GetGameObjectRayCastIntersectEnabledByHandle(goHnd)) then
      [*] = ;      SetGameObjectRayCastIntersectEnabledByHandle(goHnd, rayCastIntersect);
      [*] = ;
      [*] = ;      if (priority<>GetGameObjectCollisionPriorityByHandle(goHnd)) then
      [*] = ;      SetGameObjectCollisionPriorityByHandle(goHnd, priority);
      [*] = ;
      [*] = ;      if (boundingMode<>GetGameObjectBoundingModeByHandle(goHnd)) then
      [*] = ;      SetGameObjectBoundingModeByHandle(goHnd, boundingMode);
      [*] = ;
      [*] = ;      if (boundingData<>GetGameObjectBoundingDataByHandle(goHnd)) then
      [*] = ;      SetGameObjectBoundingDataByHandle(goHnd, boundingData);
      [*] = ;
      [*] = ;      if (boundingSpace<>GetGameObjectBoundingSpaceByHandle(goHnd)) then
      [*] = ;      SetGameObjectBoundingSpaceByHandle(goHnd, boundingSpace);
      [*] = ;
      [*] = ;      if (boundingAABBStruct<>0) then
      [*] = ;      begin
      [*] = ;         if (boundingAABBMinStruct<>0) and (boundingAABBMaxStruct<>0) then
      [*] = ;         begin
      [*] = ;            var boundingAABBMinX : Float = ParserGetFloatValueByKeyByHandle(boundingAABBMinStruct, 'X');
      [*] = ;            var boundingAABBMinY : Float = ParserGetFloatValueByKeyByHandle(boundingAABBMinStruct, 'Y');
      [*] = ;            var boundingAABBMinZ : Float = ParserGetFloatValueByKeyByHandle(boundingAABBMinStruct, 'Z');
      [*] = ;
      [*] = ;            var boundingAABBMaxX : Float = ParserGetFloatValueByKeyByHandle(boundingAABBMaxStruct, 'X');
      [*] = ;            var boundingAABBMaxY : Float = ParserGetFloatValueByKeyByHandle(boundingAABBMaxStruct, 'Y');
      [*] = ;            var boundingAABBMaxZ : Float = ParserGetFloatValueByKeyByHandle(boundingAABBMaxStruct, 'Z');
      [*] = ;
      [*] = ;            SetGameObjectCustomBoundingAABBByHandle(goHnd, boundingAABBMinX, boundingAABBMinY, boundingAABBMinZ, boundingAABBMaxX, boundingAABBMaxY, boundingAABBMaxZ);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (boundingSphere<>GetGameObjectCustomBoundingSphereByHandle(goHnd)) then
      [*] = ;      SetGameObjectCustomBoundingSphereByHandle(goHnd, boundingSphere);
      [*] = ;
      [*] = ;      if (not SameText(collidedState, GetGameObjectCollidedStateNameByHandle(goHnd))) then
      [*] = ;      SetGameObjectCollidedStateNameByHandle(goHnd, collidedState);
      [*] = ;
      [*] = ;      // TODO : collidedNode
      [*] = ;
      [*] = ;      if (not SameText(uncollidedState, GetGameObjectUncollidedStateNameByHandle(goHnd))) then
      [*] = ;      SetGameObjectUncollidedStateNameByHandle(goHnd, uncollidedState);
      [*] = ;
      [*] = ;      // TODO : uncollidedNode
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetAnimationStruct(goHnd, nodeTarget, animStruct : Integer);
      [*] = ;begin
      [*] = ;   if _log then
      [*] = ;      _log_Obj('SetAnimationStruct '+GetGameObjectBaseNameByHandle(goHnd)+' '+IntToStr(goHnd));
      [*] = ;   
      [*] = ;   if (animStruct<>0) and (ParserGetCountByHandle(animStruct)>0) then
      [*] = ;   begin
      [*] = ;      var goParentHnd : Integer = 0;
      [*] = ;      var goRootHnd : Integer = 0;
      [*] = ;      if (not GetGameObjectIsParent(goHnd)) then
      [*] = ;      begin
      [*] = ;         goParentHnd := GetGameObjectParentHandle(goHnd);
      [*] = ;         goRootHnd := GetGameObjectRootHandleByHandle(goHnd);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         goParentHnd := goHnd;
      [*] = ;         goRootHnd := goHnd;
      [*] = ;      end;
      [*] = ;      var frameAnimationResetBlend : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'frameAnimationResetBlend', false);
      [*] = ;      var deferredFrameBlend : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'deferredFrameBlend', GetGameObjectDeferredFrameBlendByHandle(goHnd));
      [*] = ;      var minFrameBlend : Integer = ParserGetIntValueByKeyByHandleDef(animStruct, 'minFrameBlend', GetGameObjectMinFrameBlendByHandle(goHnd));
      [*] = ;      var maxFrameBlend : Integer = ParserGetIntValueByKeyByHandleDef(animStruct, 'maxFrameBlend', GetGameObjectMaxFrameBlendByHandle(goHnd));
      [*] = ;      var frameAnimationMode : String = ParserGetValueByKeyByHandle(animStruct, 'frameAnimationMode');
      [*] = ;      var frameAnimationName : String = ParserGetValueByKeyByHandle(animStruct, 'frameAnimationName');
      [*] = ;      var frameAnimationNameRandStruct : Integer = ParserSelectByHandleByKey(animStruct, 'frameAnimationNameRand');
      [*] = ;      if (frameAnimationNameRandStruct<>0) and (ParserGetCountByHandle(frameAnimationNameRandStruct)>0) then
      [*] = ;      begin
      [*] = ;         var frameAnimationNameRandInd : Integer = Floor(Random*ParserGetCountByHandle(frameAnimationNameRandStruct));
      [*] = ;         frameAnimationName := ParserGetValueByIndexByHandle(frameAnimationNameRandStruct, frameAnimationNameRandInd);
      [*] = ;      end;
      [*] = ;      var frameAnimationRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'frameAnimationRandom', false);
      [*] = ;      var frameAnimationBlend : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'frameAnimationBlend', false);
      [*] = ;      var frameAnimationBlendRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'frameAnimationBlendRandom', false);
      [*] = ;      var frameAnimationBlendSmooth : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'frameAnimationBlendSmooth', true);
      [*] = ;      var frameAnimationBlendMinFrame : Integer = ParserGetIntValueByKeyByHandleDef(animStruct, 'frameAnimationBlendMinFrame', GetGameObjectMinFrameBlendByHandle(goHnd));
      [*] = ;      var frameAnimationBlendMaxFrame : Integer = ParserGetIntValueByKeyByHandleDef(animStruct, 'frameAnimationBlendMaxFrame', GetGameObjectMaxFrameBlendByHandle(goHnd));
      [*] = ;      //var frameAnimationStartReachedNode : String = ParserGetValueByKeyByHandle(animStruct, 'frameAnimationStartReachedNode');
      [*] = ;      //var frameAnimationEndReachedNode : String = ParserGetValueByKeyByHandle(animStruct, 'frameAnimationEndReachedNode');
      [*] = ;      var frameFBAnimationName : String = ParserGetValueByKeyByHandle(animStruct, 'frameFBAnimationName');
      [*] = ;      var frameFBAnimationNameRandStruct : Integer = ParserSelectByHandleByKey(animStruct, 'frameFBAnimationNameRand');
      [*] = ;      if (frameFBAnimationNameRandStruct<>0) and (ParserGetCountByHandle(frameFBAnimationNameRandStruct)>0) then
      [*] = ;      begin
      [*] = ;         var frameFBAnimationNameRandInd : Integer = Floor(Random*ParserGetCountByHandle(frameFBAnimationNameRandStruct));
      [*] = ;         frameFBAnimationName := ParserGetValueByIndexByHandle(frameFBAnimationNameRandStruct, frameFBAnimationNameRandInd);
      [*] = ;      end;
      [*] = ;      var frameFBAnimationRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'frameFBAnimationRandom', false);
      [*] = ;      var cyclesAnimationEnabled : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'cyclesAnimationEnabled', false);
      [*] = ;      var cyclesAnimationLib : String = ParserGetValueByKeyByHandle(animStruct, 'cyclesAnimationLib');
      [*] = ;      var cyclesAnimationName : String = ParserGetValueByKeyByHandle(animStruct, 'cyclesAnimationName');
      [*] = ;      var cyclesAnimationNameRandStruct : Integer = ParserSelectByHandleByKey(animStruct, 'cyclesAnimationNameRand');
      [*] = ;      if (cyclesAnimationNameRandStruct<>0) and (ParserGetCountByHandle(cyclesAnimationNameRandStruct)>0) then
      [*] = ;      begin
      [*] = ;         var cyclesAnimationNameRandInd : Integer = Floor(Random*ParserGetCountByHandle(cyclesAnimationNameRandStruct));
      [*] = ;         cyclesAnimationName := ParserGetValueByIndexByHandle(cyclesAnimationNameRandStruct, cyclesAnimationNameRandInd);
      [*] = ;      end;
      [*] = ;      var cyclesAnimationMode : String = ParserGetValueByKeyByHandle(animStruct, 'cyclesAnimationMode');
      [*] = ;      var cyclesAnimationRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'cyclesAnimationRandom', false);
      [*] = ;      var cyclesAnimationTree : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'cyclesAnimationTree', false);
      [*] = ;      var cyclesAnimationDefault : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'cyclesAnimationDefault', false);
      [*] = ;      var cyclesFBAnimationName : String = ParserGetValueByKeyByHandle(animStruct, 'cyclesFBAnimationName');
      [*] = ;      var cyclesFBAnimationNameRandStruct : Integer = ParserSelectByHandleByKey(animStruct, 'cyclesFBAnimationNameRand');
      [*] = ;      if (cyclesFBAnimationNameRandStruct<>0) and (ParserGetCountByHandle(cyclesFBAnimationNameRandStruct)>0) then
      [*] = ;      begin
      [*] = ;         var cyclesFBAnimationNameRandInd : Integer = Floor(Random*ParserGetCountByHandle(cyclesFBAnimationNameRandStruct));
      [*] = ;         cyclesFBAnimationName := ParserGetValueByIndexByHandle(cyclesFBAnimationNameRandStruct, cyclesFBAnimationNameRandInd);
      [*] = ;      end;
      [*] = ;      var cyclesFBAnimationRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'cyclesFBAnimationRandom', false);
      [*] = ;      var cyclesFBAnimationDefault : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'cyclesFBAnimationDefault', false);
      [*] = ;      var cyclesFBAnimationBlend : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'cyclesFBAnimationBlend', false);
      [*] = ;      var cyclesFBAnimationBlendMinFrame : Integer = ParserGetIntValueByKeyByHandleDef(animStruct, 'cyclesFBAnimationBlendMinFrame', GetGameObjectMinFrameBlendByHandle(goHnd));
      [*] = ;      var cyclesFBAnimationBlendMaxFrame : Integer = ParserGetIntValueByKeyByHandleDef(animStruct, 'cyclesFBAnimationBlendMaxFrame', GetGameObjectMaxFrameBlendByHandle(goHnd));
      [*] = ;      //var cyclesAnimationStartReachedNode : String = ParserGetValueByKeyByHandle(animStruct, 'cyclesAnimationStartReachedNode');
      [*] = ;      //var cyclesAnimationEndReachedNode : String = ParserGetValueByKeyByHandle(animStruct, 'cyclesAnimationEndReachedNode');
      [*] = ;      //var cyclesFBAnimationEndReachedNode : String = ParserGetValueByKeyByHandle(animStruct, 'cyclesFBAnimationEndReachedNode');
      [*] = ;
      [*] = ;      var switchSelf : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchSelf', true);
      [*] = ;      var switchParent : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchParent', false);
      [*] = ;      var switchRoot : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchRoot', false);
      [*] = ;      var switchTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchTarget', false);
      [*] = ;      var switchStateTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchStateTarget', false);
      [*] = ;      var switchRootStateTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchRootStateTarget', false);
      [*] = ;      var switchTargetStateTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchTargetStateTarget', false);
      [*] = ;
      [*] = ;      var switchChildrenSelf : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchChildrenSelf', false);
      [*] = ;      var switchChildrenParent : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchChildrenParent', false);
      [*] = ;      var switchChildrenRoot : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchChildrenRoot', false);
      [*] = ;      var switchChildrenTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchChildrenTarget', false);
      [*] = ;      var switchChildrenStateTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchChildrenStateTarget', false);
      [*] = ;      var switchChildrenRootStateTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchChildrenRootStateTarget', false);
      [*] = ;      var switchChildrenTargetStateTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(animStruct, 'switchChildrenTargetStateTarget', false);
      [*] = ;
      [*] = ;      if (switchSelf) then
      [*] = ;      SwitchAnimation(goHnd, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchParent then
      [*] = ;      SwitchAnimation(goParentHnd, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchRoot then
      [*] = ;      SwitchAnimation(goRootHnd, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchTarget then
      [*] = ;      SwitchAnimation(nodeTarget, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchStateTarget then
      [*] = ;      SwitchAnimation(GetGameObjectSTOHandleByHandle(goHnd), frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchRootStateTarget then
      [*] = ;      SwitchAnimation(GetGameObjectSTOHandleByHandle(goRootHnd), frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchTargetStateTarget then
      [*] = ;      SwitchAnimation(GetGameObjectSTOHandleByHandle(nodeTarget), frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;
      [*] = ;      if switchChildrenSelf then
      [*] = ;      SwitchChildrenAnimation(goHnd, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchChildrenParent then
      [*] = ;      SwitchChildrenAnimation(goParentHnd, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchChildrenRoot then
      [*] = ;      SwitchChildrenAnimation(goRootHnd, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchChildrenTarget then
      [*] = ;      SwitchChildrenAnimation(nodeTarget, frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchChildrenStateTarget then
      [*] = ;      SwitchChildrenAnimation(GetGameObjectSTOHandleByHandle(goHnd), frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchChildrenRootStateTarget then
      [*] = ;      SwitchChildrenAnimation(GetGameObjectSTOHandleByHandle(goRootHnd), frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;      if switchChildrenTargetStateTarget then
      [*] = ;      SwitchChildrenAnimation(GetGameObjectSTOHandleByHandle(nodeTarget), frameAnimationRandom, frameFBAnimationRandom, cyclesAnimationEnabled, cyclesAnimationTree, cyclesAnimationDefault, cyclesAnimationRandom, cyclesFBAnimationRandom, cyclesFBAnimationDefault, cyclesFBAnimationBlend, frameAnimationResetBlend, deferredFrameBlend, frameAnimationBlend, frameAnimationBlendRandom, frameAnimationBlendSmooth, minFrameBlend, maxFrameBlend, frameAnimationBlendMinFrame, frameAnimationBlendMaxFrame, cyclesFBAnimationBlendMinFrame, cyclesFBAnimationBlendMaxFrame, frameAnimationMode, frameAnimationName, frameFBAnimationName, cyclesAnimationLib, cyclesAnimationMode, cyclesAnimationName, cyclesFBAnimationName);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetPropertiesStruct(goHnd, propStruct : Integer);
      [*] = ;begin
      [*] = ;   if (propStruct<>0) and (ParserGetCountByHandle(propStruct)>0) then
      [*] = ;   begin
      [*] = ;      var propRaceName : String = ParserGetValueByKeyByHandle(propStruct, 'raceName');
      [*] = ;      var propBaseName : String = ParserGetValueByKeyByHandle(propStruct, 'baseName');
      [*] = ;      var propPlayerName : String = ParserGetValueByKeyByHandle(propStruct, 'playerName');
      [*] = ;      var propCustomName : String = ParserGetValueByKeyByHandle(propStruct, 'customName');
      [*] = ;
      [*] = ;      var propRandomNamesStruct : Integer = ParserSelectByHandleByKey(propStruct, 'randomNames');
      [*] = ;      if (propRandomNamesStruct<>0) and (ParserGetCountByHandle(propRandomNamesStruct)>0) then
      [*] = ;      begin
      [*] = ;         var propRandomNamesInd : Integer = Floor(Random*ParserGetCountByHandle(propRandomNamesStruct));
      [*] = ;         var propRandomNamesChild : Integer = ParserSelectByHandleByIndex(propRandomNamesStruct, propRandomNamesInd);
      [*] = ;         propRaceName := ParserGetValueByKeyByHandle(propRandomNamesChild, 'raceName');
      [*] = ;         propBaseName := ParserGetValueByKeyByHandle(propRandomNamesChild, 'baseName');
      [*] = ;         propPlayerName := ParserGetValueByKeyByHandle(propRandomNamesChild, 'playerName');
      [*] = ;         propCustomName := ParserGetValueByKeyByHandle(propRandomNamesChild, 'customName');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (propRaceName<>'') and (propBaseName<>'') then
      [*] = ;      begin
      [*] = ;         var currRaceName : String = GetGameObjectRaceNameByHandle(goHnd);
      [*] = ;         var currBaseName : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;         if (not (SameText(currBaseName, propBaseName))) and (not (SameText(currRaceName, propRaceName))) then
      [*] = ;         SetGameObjectVisualPropertiesByHandle(goHnd, propRaceName, propBaseName);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (propPlayerName<>'') then
      [*] = ;      begin
      [*] = ;         var currPlayerName : String = GetGameObjectPlayerNameByHandle(goHnd);
      [*] = ;         if (not (SameText(currPlayerName, propPlayerName))) then
      [*] = ;         begin
      [*] = ;            var propPlayerHandle : Integer =  GetPlayerHandleByName(propPlayerName);
      [*] = ;            if (propPlayerHandle=0) then
      [*] = ;            propPlayerHandle := CreatePlayer(propPlayerName, 'misc', 'cmPC');
      [*] = ;            if (propPlayerHandle<>0) then
      [*] = ;            SetGameObjectPlayerHandleByHandle(goHnd, propPlayerHandle);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (propCustomName<>'') then
      [*] = ;      begin
      [*] = ;         var currCustomName : String = GetGameObjectCustomNameByHandle(goHnd);
      [*] = ;         if (not (SameText(currCustomName, propCustomName))) then
      [*] = ;         SetGameObjectCustomNameByHandle(goHnd, propCustomName);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetRenderStruct(goHnd, renderStruct : Integer);
      [*] = ;begin
      [*] = ;   if _log then
      [*] = ;      _log_Obj('SetRenderStruct '+GetGameObjectBaseNameByHandle(goHnd)+' '+IntToStr(goHnd));
      [*] = ;   
      [*] = ;   if (renderStruct<>0) and (ParserGetCountByHandle(renderStruct)>0) then
      [*] = ;   begin
      [*] = ;      var renderShaderID : Integer = ParserGetIntValueByKeyByHandle(renderStruct, 'shaderID');
      [*] = ;      var renderUniform1fStruct : Integer = ParserSelectByHandleByKey(renderStruct, 'uniform1f');
      [*] = ;      var renderUniform1fCount : Integer = ParserGetCountByHandle(renderUniform1fStruct);
      [*] = ;      var renderUniform4fStruct : Integer = ParserSelectByHandleByKey(renderStruct, 'uniform4f');
      [*] = ;      var renderUniform4fCount : Integer = ParserGetCountByHandle(renderUniform4fStruct);
      [*] = ;      var renderLodActorName : String = ParserGetValueByKeyByHandle(renderStruct, 'lodActorName');
      [*] = ;      var renderMeshName : String = ParserGetValueByKeyByHandle(renderStruct, 'meshName');
      [*] = ;      var renderMaterialName : String = ParserGetValueByKeyByHandle(renderStruct, 'materialName');
      [*] = ;      var renderRandomNamesStruct : Integer = ParserSelectByHandleByKey(renderStruct, 'randomNames');
      [*] = ;      if (renderRandomNamesStruct<>0) and (ParserGetCountByHandle(renderRandomNamesStruct)>0) then
      [*] = ;      begin
      [*] = ;         var renderRandomNamesInd : Integer = Floor(Random*ParserGetCountByHandle(renderRandomNamesStruct));
      [*] = ;         var renderRandomNamesChild : Integer = ParserSelectByHandleByIndex(renderRandomNamesStruct, renderRandomNamesInd);
      [*] = ;         renderLodActorName := ParserGetValueByKeyByHandle(renderRandomNamesChild, 'lodActorName');
      [*] = ;         renderMeshName := ParserGetValueByKeyByHandle(renderRandomNamesChild, 'meshName');
      [*] = ;         renderMaterialName := ParserGetValueByKeyByHandle(renderRandomNamesChild, 'materialName');
      [*] = ;      end;
      [*] = ;      var renderVisible : Boolean = ParserGetBoolValueByKeyByHandle(renderStruct, 'visible');
      [*] = ;
      [*] = ;      if (renderLodActorName<>'') then
      [*] = ;      begin
      [*] = ;         var currLodActorName : String = GetGameObjectLODActorNameByHandle(goHnd);
      [*] = ;         if (not (SameText(currLodActorName, renderLodActorName))) then
      [*] = ;         SetGameObjectLODActorNameByHandle(goHnd, renderLodActorName);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (renderMeshName<>'') then
      [*] = ;      begin
      [*] = ;         var currMeshName : String = GameObjectGetActorNameByHandle(goHnd);
      [*] = ;         if (not (SameText(currMeshName, renderMeshName))) then
      [*] = ;         SetGameObjectActorNameByHandle(goHnd, renderMeshName);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (renderMaterialName<>'') then
      [*] = ;      begin
      [*] = ;         var defaultMaterial : String = '';
      [*] = ;         _obj_GetDefaultMaterial(goHnd, defaultMaterial);
      [*] = ;         
      [*] = ;         if defaultMaterial <> '' then
      [*] = ;         begin
      [*] = ;            if SameText(renderMaterialName, 'default') then
      [*] = ;               renderMaterialName := defaultMaterial;
      [*] = ;            
      [*] = ;            if _log then _log_Obj('renderMaterialName '+renderMaterialName);
      [*] = ;            var currMaterialName : String = GetGameObjectMaterialNameByHandle(goHnd);
      [*] = ;            if (not (SameText(currMaterialName, renderMaterialName))) then
      [*] = ;            begin
      [*] = ;               var i : Integer;
      [*] = ;               var bOverride : Boolean = true;
      [*] = ;               var priorityMaterials : Integer = ParserSelectByHandleByKey(renderStruct, 'priorityMaterials');
      [*] = ;               for i := 0 to ParserGetCountByHandle(priorityMaterials)-1 do
      [*] = ;               begin
      [*] = ;                  var priorityMaterial : Integer = ParserSelectByHandleByIndex(priorityMaterials, i);
      [*] = ;                  if SameText(currMaterialName, ParserGetValueByKeyByHandle(priorityMaterial, 'material')) then
      [*] = ;                  begin
      [*] = ;                     bOverride := false;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               
      [*] = ;               if bOverride then
      [*] = ;               begin
      [*] = ;                  if _log then _log_Obj('set renderMaterial '+GetGameObjectBaseNameByHandle(goHnd)+' '+IntToStr(goHnd));
      [*] = ;                  SetGameObjectMaterialNameByHandle(goHnd, renderMaterialName);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // TODO : shaderID
      [*] = ;      //if (ParserGetValueByKeyByHandle(renderStruct, 'shaderID')<>'') then
      [*] = ;      //begin
      [*] = ;      //end;
      [*] = ;
      [*] = ;      if (renderUniform1fStruct<>0) and (renderUniform1fCount>0) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to renderUniform1fCount-1 do
      [*] = ;         begin
      [*] = ;            var renderUniform1fStructChild : Integer = ParserSelectByHandleByIndex(renderUniform1fStruct, i);
      [*] = ;            var renderUniform1fIndex : Integer = ParserGetIntValueByKeyByHandle(renderUniform1fStructChild, 'index');
      [*] = ;            var renderUniform1fValue : Float = ParserGetFloatValueByKeyByHandle(renderUniform1fStructChild, 'value');
      [*] = ;            var renderUniform1fRandomStruct : Integer = ParserSelectByHandleByKey(renderUniform1fStructChild, 'random');
      [*] = ;            if (renderUniform1fRandomStruct<>0) and (ParserGetCountByHandle(renderUniform1fRandomStruct)>0) then
      [*] = ;            begin
      [*] = ;               var renderUniform1fRandomInd : Integer = Floor(Random*ParserGetCountByHandle(renderUniform1fRandomStruct));
      [*] = ;               renderUniform1fValue := ParserGetFloatValueByIndexByHandle(renderUniform1fRandomStruct, renderUniform1fRandomInd);
      [*] = ;            end;
      [*] = ;            var renderUniform1fChild : Boolean = ParserGetBoolValueByKeyByHandle(renderUniform1fStructChild, 'child');
      [*] = ;            SetGameObjectUniform1f(goHnd, renderUniform1fIndex, renderUniform1fValue, renderUniform1fChild);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (renderUniform4fStruct<>0) and (renderUniform4fCount>0) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to renderUniform4fCount-1 do
      [*] = ;         begin
      [*] = ;            var renderUniform4fStructChild : Integer = ParserSelectByHandleByIndex(renderUniform4fStruct, i);
      [*] = ;            var renderUniform4fIndex : Integer = ParserGetIntValueByKeyByHandle(renderUniform4fStructChild, 'index');
      [*] = ;            var renderUniform4fValue : Integer = ParserSelectByHandleByKey(renderUniform4fStructChild, 'value');
      [*] = ;            var renderUniform4fValueX : Float = ParserGetFloatValueByKeyByHandle(renderUniform4fValue, 'X');
      [*] = ;            var renderUniform4fValueY : Float = ParserGetFloatValueByKeyByHandle(renderUniform4fValue, 'Y');
      [*] = ;            var renderUniform4fValueZ : Float = ParserGetFloatValueByKeyByHandle(renderUniform4fValue, 'Z');
      [*] = ;            var renderUniform4fValueW : Float = ParserGetFloatValueByKeyByHandle(renderUniform4fValue, 'W');
      [*] = ;            var renderUniform4fRandomStruct : Integer = ParserSelectByHandleByKey(renderUniform4fStructChild, 'random');
      [*] = ;            if (renderUniform4fRandomStruct<>0) and (ParserGetCountByHandle(renderUniform4fRandomStruct)>0) then
      [*] = ;            begin
      [*] = ;               var renderUniform4fRandomInd : Integer = Floor(Random*ParserGetCountByHandle(renderUniform4fRandomStruct));
      [*] = ;               var renderUniform4fRandomChild : Integer = ParserSelectByHandleByIndex(renderUniform4fRandomStruct, renderUniform4fRandomInd);
      [*] = ;               renderUniform4fValueX := ParserGetFloatValueByKeyByHandle(renderUniform4fRandomChild, 'X');
      [*] = ;               renderUniform4fValueY := ParserGetFloatValueByKeyByHandle(renderUniform4fRandomChild, 'Y');
      [*] = ;               renderUniform4fValueZ := ParserGetFloatValueByKeyByHandle(renderUniform4fRandomChild, 'Z');
      [*] = ;               renderUniform4fValueW := ParserGetFloatValueByKeyByHandle(renderUniform4fRandomChild, 'W');
      [*] = ;            end;
      [*] = ;            var renderUniform4fChild : Boolean = ParserGetBoolValueByKeyByHandle(renderUniform4fStructChild, 'child');
      [*] = ;            SetGameObjectUniform4f(goHnd, renderUniform4fIndex, renderUniform4fValueX, renderUniform4fValueY, renderUniform4fValueZ, renderUniform4fValueW, renderUniform4fChild);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (ParserGetValueByKeyByHandle(renderStruct, 'visible')<>'') then
      [*] = ;      begin
      [*] = ;         var currVisible : Boolean = GetGameObjectVisibleByHandle(goHnd);
      [*] = ;         if (currVisible<>renderVisible) then
      [*] = ;         SetGameObjectVisibleByHandle(goHnd, renderVisible);
      [*] = ;      end;
      [*] = ;         
      [*] = ;      if ParserGetBoolValueByKeyByHandle(renderStruct, 'applyToChildren') then
      [*] = ;      begin
      [*] = ;         var childRaceName : String = ParserGetValueByKeyByHandle(renderStruct, 'childRaceName');
      [*] = ;         var childBaseName : String = ParserGetValueByKeyByHandle(renderStruct, 'childBaseName');
      [*] = ;         var childCustomName : String = ParserGetValueByKeyByHandle(renderStruct, 'childCustomName');
      [*] = ;         
      [*] = ;         var i, childHandle : Integer;
      [*] = ;         for i:=0 to GetGameObjectCountChildByHandle(goHnd)-1 do
      [*] = ;         begin
      [*] = ;            childHandle := GetGameObjectGOHandleChildByHandle(goHnd, i);
      [*] = ;            if (childHandle <> 0) and (not SameText(GetGameObjectBaseNameByHandle(childHandle), 'fx')) then
      [*] = ;            begin
      [*] = ;               SetRenderStruct(childHandle, renderStruct);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddRelativePosition(goHnd, nodeTarget : Integer; coordTargetX, coordTargetY, coordTargetZ : Float; relative : String; var rx : Float; var ry : Float; var rz : Float);
      [*] = ;begin
      [*] = ;   var goParentHnd : Integer = 0;
      [*] = ;   var goRootHnd : Integer = 0;
      [*] = ;   if (not GetGameObjectIsParent(goHnd)) then
      [*] = ;   begin
      [*] = ;      goParentHnd := GetGameObjectParentHandle(goHnd);
      [*] = ;      goRootHnd := GetGameObjectRootHandleByHandle(goHnd);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      goParentHnd := goHnd;
      [*] = ;      goRootHnd := goHnd;
      [*] = ;   end;
      [*] = ;   if (relative<>'') then
      [*] = ;   case StrToLowerCase(relative) of
      [*] = ;      //'absolute' :
      [*] = ;      'locOfSelf' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectLocalPosition(goHnd, x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'absOfSelf' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectAbsolutePosition(goHnd, x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'locOfParent' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectLocalPosition(goParentHnd, x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'absOfParent' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectAbsolutePosition(goParentHnd, x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'locOfRoot' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectLocalPosition(goRootHnd, x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'absOfRoot' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectAbsolutePosition(goRootHnd, x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'locOfTarget' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectLocalPosition(nodeTarget, x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'absOfTarget' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectAbsolutePosition(nodeTarget, x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'locOfCoordTarget' :
      [*] = ;      begin
      [*] = ;         rx := rx + coordTargetX;
      [*] = ;         ry := ry + coordTargetY;
      [*] = ;         rz := rz + coordTargetZ;
      [*] = ;      end;
      [*] = ;      'locOfStateTarget' :
      [*] = ;      begin
      [*] = ;         rx := rx + GetGameObjectStateTargetPositionXByHandle(goHnd);
      [*] = ;         ry := ry + GetGameObjectStateTargetPositionYByHandle(goHnd);
      [*] = ;         rz := rz + GetGameObjectStateTargetPositionZByHandle(goHnd);
      [*] = ;      end;
      [*] = ;      'locOfParentStateTarget' :
      [*] = ;      begin
      [*] = ;         rx := rx + GetGameObjectStateTargetPositionXByHandle(goParentHnd);
      [*] = ;         ry := ry + GetGameObjectStateTargetPositionYByHandle(goParentHnd);
      [*] = ;         rz := rz + GetGameObjectStateTargetPositionZByHandle(goParentHnd);
      [*] = ;      end;
      [*] = ;      'locOfRootStateTarget' :
      [*] = ;      begin
      [*] = ;         rx := rx + GetGameObjectStateTargetPositionXByHandle(goRootHnd);
      [*] = ;         ry := ry + GetGameObjectStateTargetPositionYByHandle(goRootHnd);
      [*] = ;         rz := rz + GetGameObjectStateTargetPositionZByHandle(goRootHnd);
      [*] = ;      end;
      [*] = ;      'locOfTargetStateTarget' :
      [*] = ;      begin
      [*] = ;         rx := rx + GetGameObjectStateTargetPositionXByHandle(nodeTarget);
      [*] = ;         ry := ry + GetGameObjectStateTargetPositionYByHandle(nodeTarget);
      [*] = ;         rz := rz + GetGameObjectStateTargetPositionZByHandle(nodeTarget);
      [*] = ;      end;
      [*] = ;      'locOfStateTargetObject' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectLocalPosition(GetGameObjectSTOHandleByHandle(goHnd), x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'absOfStateTargetObject' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectAbsolutePosition(GetGameObjectSTOHandleByHandle(goHnd), x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'locOfParentStateTargetObject' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectLocalPosition(GetGameObjectSTOHandleByHandle(goParentHnd), x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'absOfParentStateTargetObject' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectAbsolutePosition(GetGameObjectSTOHandleByHandle(goParentHnd), x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'locOfRootStateTargetObject' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectLocalPosition(GetGameObjectSTOHandleByHandle(goRootHnd), x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'absOfRootStateTargetObject' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectAbsolutePosition(GetGameObjectSTOHandleByHandle(goRootHnd), x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'locOfTargetStateTargetObject' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectLocalPosition(GetGameObjectSTOHandleByHandle(nodeTarget), x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;      'absOfTargetStateTargetObject' :
      [*] = ;      begin
      [*] = ;         var x, y, z : Float = 0;
      [*] = ;         _obj_GetGameObjectAbsolutePosition(GetGameObjectSTOHandleByHandle(nodeTarget), x, y, z, true);
      [*] = ;         rx := rx + x;
      [*] = ;         ry := ry + y;
      [*] = ;         rz := rz + z;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetTrackpointStruct(goHnd, nodeTarget : Integer; coordTargetX, coordTargetY, coordTargetZ : Float; trackpointStruct : Integer);
      [*] = ;begin
      [*] = ;   if (trackpointStruct<>0) and (ParserGetCountByHandle(trackpointStruct)>0) then
      [*] = ;   begin
      [*] = ;      var callStateBefore : String = ParserGetValueByKeyByHandle(trackpointStruct, 'callStateBefore');
      [*] = ;      var clear : Boolean = ParserGetBoolValueByKeyByHandleDef(trackpointStruct, 'clear', false);
      [*] = ;      // ---
      [*] = ;      var addPointRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(trackpointStruct, 'addPointRandom', false);
      [*] = ;      var addPointRandomMinCount : Integer = ParserGetIntValueByKeyByHandleDef(trackpointStruct, 'addPointRandomMinCount', 1);
      [*] = ;      var addPointRandomMaxCount : Integer = ParserGetIntValueByKeyByHandleDef(trackpointStruct, 'addPointRandomMaxCount', 1);
      [*] = ;      var addPointRandomCurCount : Integer = Round(Random*(addPointRandomMaxCount-addPointRandomMinCount))+addPointRandomMinCount;
      [*] = ;      var addPointRelative : String = ParserGetValueByKeyByHandle(trackpointStruct, 'addPointRelative');
      [*] = ;      // locOfSelf
      [*] = ;      // absOfSelf
      [*] = ;      // locOfParent
      [*] = ;      // absOfParent
      [*] = ;      // locOfRoot
      [*] = ;      // absOfRoot
      [*] = ;      // locOfTarget
      [*] = ;      // absOfTarget
      [*] = ;      // locOfCoordTarget
      [*] = ;      // locOfStateTarget
      [*] = ;      // locOfParentStateTarget
      [*] = ;      // locOfRootStateTarget
      [*] = ;      // locOfTargetStateTarget
      [*] = ;      // locOfStateTargetObject
      [*] = ;      // absOfStateTargetObject
      [*] = ;      // locOfParentStateTargetObject
      [*] = ;      // absOfParentStateTargetObject
      [*] = ;      // locOfRootStateTargetObject
      [*] = ;      // absOfRootStateTargetObject
      [*] = ;      // locOfTargetStateTargetObject
      [*] = ;      // absOfTargetStateTargetObject
      [*] = ;      var addPointCoordsStruct : Integer = ParserSelectByHandleByKey(trackpointStruct, 'addPointCoords');
      [*] = ;      var currentPointIndex : Integer = ParserGetIntValueByKeyByHandleDef(trackpointStruct, 'currentPointIndex', GetGameObjectTrackPointCurrentPointIndexByHandle(goHnd));
      [*] = ;      var currentPointIndexRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(trackpointStruct, 'currentPointIndexRandom', false);
      [*] = ;      // ---
      [*] = ;      var extPointReached : String = ParserGetValueByKeyByHandle(trackpointStruct, 'extPointReached');
      [*] = ;      var extPointEnabled : Boolean = ParserGetBoolValueByKeyByHandleDef(trackpointStruct, 'extPointEnabled', GetGameObjectTrackPointExtPointEnabled(goHnd));
      [*] = ;      var extPointCIBuild : Boolean = ParserGetBoolValueByKeyByHandleDef(trackpointStruct, 'extPointCIBuild', GetGameObjectCIBuildExtPointsByHandle(goHnd));
      [*] = ;      var extPointCIDist : Float = ParserGetFloatValueByKeyByHandleDef(trackpointStruct, 'extPointCIDist', GetGameObjectCIDistExtPointEpsilonByHandle(goHnd));
      [*] = ;      var extPointPositionStruct : Integer = ParserSelectByHandleByKey(trackpointStruct, 'extPointPosition');
      [*] = ;      var extPointInitPosX, extPointInitPosY, extPointInitPosZ : Float = 0;
      [*] = ;      if (extPointPositionStruct<>0) then
      [*] = ;      begin
      [*] = ;         extPointInitPosX := ParserGetFloatValueByKeyByHandleDef(extPointPositionStruct, 'X', 0);
      [*] = ;         extPointInitPosY := ParserGetFloatValueByKeyByHandleDef(extPointPositionStruct, 'Y', 0);
      [*] = ;         extPointInitPosZ := ParserGetFloatValueByKeyByHandleDef(extPointPositionStruct, 'Z', 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      GetGameObjectTrackPointExtPoint(goHnd, extPointInitPosX, extPointInitPosY, extPointInitPosZ);
      [*] = ;      var extPointDispersion : Float = ParserGetFloatValueByKeyByHandleDef(trackpointStruct, 'extPointDispersion', 0);
      [*] = ;      var extPointDispersionRangeStruct : Integer = ParserSelectByHandleByKey(trackpointStruct, 'extPointDispersionRange');
      [*] = ;      var extPointDispersionRangeX, extPointDispersionRangeY, extPointDispersionRangeZ : Float = 0;
      [*] = ;      if (extPointDispersionRangeStruct<>0) then
      [*] = ;      begin
      [*] = ;         extPointDispersionRangeX := ParserGetFloatValueByKeyByHandleDef(extPointDispersionRangeStruct, 'X', 0);
      [*] = ;         extPointDispersionRangeY := ParserGetFloatValueByKeyByHandleDef(extPointDispersionRangeStruct, 'Y', 0);
      [*] = ;         extPointDispersionRangeZ := ParserGetFloatValueByKeyByHandleDef(extPointDispersionRangeStruct, 'Z', 0);
      [*] = ;      end;
      [*] = ;      var extPointRelative : String = ParserGetValueByKeyByHandle(trackpointStruct, 'extPointRelative');
      [*] = ;      AddRelativePosition(goHnd, nodeTarget, coordTargetX, coordTargetY, coordTargetZ, extPointRelative, extPointInitPosX, extPointInitPosY, extPointInitPosZ);
      [*] = ;      var extPointPositionX, extPointPositionY, extPointPositionZ : Float = 0;
      [*] = ;      DispersionRange(extPointPositionX, extPointPositionY, extPointPositionZ, extPointInitPosX, extPointInitPosY, extPointInitPosZ, extPointDispersion, extPointDispersionRangeX, extPointDispersionRangeY, extPointDispersionRangeZ);
      [*] = ;      // ---
      [*] = ;      var animationMove : String = ParserGetValueByKeyByHandle(trackpointStruct, 'animationMove');
      [*] = ;      var animationStand : String = ParserGetValueByKeyByHandle(trackpointStruct, 'animationStand');
      [*] = ;      var movementMode : String = ParserGetValueByKeyByHandle(trackpointStruct, 'movementMode');
      [*] = ;      var useAnimationCycles : Boolean = ParserGetBoolValueByKeyByHandleDef(trackpointStruct, 'useAnimationCycles', GetGameObjectTrackPointUseAnimationCyclesByHandle(goHnd));
      [*] = ;      var moveStep : Float = ParserGetFloatValueByKeyByHandleDef(trackpointStruct, 'moveStep', GetGameObjectTrackPointMoveStepByHandle(goHnd));
      [*] = ;      var moveStepInterval : Integer = ParserGetIntValueByKeyByHandleDef(trackpointStruct, 'moveStepInterval', GetGameObjectTrackPointMoveStepIntervalByHandle(goHnd));
      [*] = ;      var epsilonDistance : Float = ParserGetFloatValueByKeyByHandleDef(trackpointStruct, 'epsilonDistance', GetGameObjectEpsilonDistanceByHandle(goHnd));
      [*] = ;      var virtualDirectionStructChild : Integer = ParserSelectByHandleByKey(trackpointStruct, 'virtualDirection');
      [*] = ;      var virtualDirectionX : Float = ParserGetFloatValueByKeyByHandle(virtualDirectionStructChild, 'X');
      [*] = ;      var virtualDirectionY : Float = ParserGetFloatValueByKeyByHandle(virtualDirectionStructChild, 'Y');
      [*] = ;      var virtualDirectionZ : Float = ParserGetFloatValueByKeyByHandle(virtualDirectionStructChild, 'Z');
      [*] = ;      var turnStep : Float = ParserGetFloatValueByKeyByHandleDef(trackpointStruct, 'turnStep', GetGameObjectTrackPointTurnStepByHandle(goHnd));
      [*] = ;      var turnStepInterval : Integer = ParserGetIntValueByKeyByHandleDef(trackpointStruct, 'turnStepInterval', GetGameObjectTrackPointTurnStepIntervalByHandle(goHnd));
      [*] = ;      var epsilonAngle : Float = ParserGetFloatValueByKeyByHandleDef(trackpointStruct, 'epsilonAngle', GetGameObjectEpsilonAngleByHandle(goHnd));
      [*] = ;      var virtualUpStructChild : Integer = ParserSelectByHandleByKey(trackpointStruct, 'virtualUp');
      [*] = ;      var virtualUpX : Float = ParserGetFloatValueByKeyByHandle(virtualUpStructChild, 'X');
      [*] = ;      var virtualUpY : Float = ParserGetFloatValueByKeyByHandle(virtualUpStructChild, 'Y');
      [*] = ;      var virtualUpZ : Float = ParserGetFloatValueByKeyByHandle(virtualUpStructChild, 'Z');
      [*] = ;      var distanceToPointReached : String = ParserGetValueByKeyByHandle(trackpointStruct, 'distanceToPointReached');
      [*] = ;      var distanceToPoint : Float = ParserGetFloatValueByKeyByHandleDef(trackpointStruct, 'distanceToPoint', 0);
      [*] = ;      var startPointReached : String = ParserGetValueByKeyByHandle(trackpointStruct, 'startPointReached');
      [*] = ;      var endPointReached : String = ParserGetValueByKeyByHandle(trackpointStruct, 'endPointReached');
      [*] = ;      var directionReached : String = ParserGetValueByKeyByHandle(trackpointStruct, 'directionReached');
      [*] = ;      var rotatingMode : String = ParserGetValueByKeyByHandle(trackpointStruct, 'rotatingMode');
      [*] = ;      var intervalFactor : Float = ParserGetFloatValueByKeyByHandleDef(trackpointStruct, 'intervalFactor', GetGameObjectIntervalFactorByHandle(goHnd));
      [*] = ;      var callStateAfter : String = ParserGetValueByKeyByHandle(trackpointStruct, 'callStateAfter');
      [*] = ;
      [*] = ;      if (callStateBefore<>'') then
      [*] = ;      GameObjectExecuteStateByHandle(goHnd, callStateBefore);
      [*] = ;
      [*] = ;      if (clear) then
      [*] = ;      GameObjectTrackPointClearByHandle(goHnd);
      [*] = ;
      [*] = ;      var addPointCurIndex : Integer = 0;
      [*] = ;      var addPointCurCount : Integer = ParserGetCountByHandle(addPointCoordsStruct);
      [*] = ;      if (addPointRandom) then
      [*] = ;      addPointCurCount := addPointRandomCurCount;
      [*] = ;      for addPointCurIndex:=0 to addPointCurCount-1 do
      [*] = ;      begin
      [*] = ;         var addPointCoordsIndex : Integer = addPointCurIndex;
      [*] = ;         if (addPointRandom) then
      [*] = ;         addPointCoordsIndex := Floor(Random*ParserGetCountByHandle(addPointCoordsStruct));
      [*] = ;         var addPointCoordsChild : Integer = ParserSelectByHandleByIndex(addPointCoordsStruct, addPointCoordsIndex);
      [*] = ;         var addPointCoordsInitX : Float = ParserGetFloatValueByKeyByHandleDef(addPointCoordsChild, 'posX', 0);
      [*] = ;         var addPointCoordsInitY : Float = ParserGetFloatValueByKeyByHandleDef(addPointCoordsChild, 'posY', 0);
      [*] = ;         var addPointCoordsInitZ : Float = ParserGetFloatValueByKeyByHandleDef(addPointCoordsChild, 'posZ', 0);
      [*] = ;         var addPointCoordsDisp : Float = ParserGetFloatValueByKeyByHandleDef(addPointCoordsChild, 'disp', 0);
      [*] = ;         var addPointCoordsDispX : Float = ParserGetFloatValueByKeyByHandleDef(addPointCoordsChild, 'dispX', 0);
      [*] = ;         var addPointCoordsDispY : Float = ParserGetFloatValueByKeyByHandleDef(addPointCoordsChild, 'dispY', 0);
      [*] = ;         var addPointCoordsDispZ : Float = ParserGetFloatValueByKeyByHandleDef(addPointCoordsChild, 'dispZ', 0);
      [*] = ;         AddRelativePosition(goHnd, nodeTarget, coordTargetX, coordTargetY, coordTargetZ, addPointRelative, addPointCoordsInitX, addPointCoordsInitY, addPointCoordsInitZ);
      [*] = ;         var addPointCoordsPosX, addPointCoordsPosY, addPointCoordsPosZ : Float = 0;
      [*] = ;         DispersionRange(addPointCoordsPosX, addPointCoordsPosY, addPointCoordsPosZ, addPointCoordsInitX, addPointCoordsInitY, addPointCoordsInitZ, addPointCoordsDisp, addPointCoordsDispX, addPointCoordsDispY, addPointCoordsDispZ);
      [*] = ;         GameObjectTrackPointAddByHandle(goHnd, addPointCoordsPosX, {addPointCoordsPosY}0, addPointCoordsPosZ);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (moveStep<>GetGameObjectTrackPointMoveStepByHandle(goHnd)) then
      [*] = ;      SetGameObjectTrackPointMoveStepByHandle(goHnd, moveStep);
      [*] = ;
      [*] = ;      if (moveStepInterval<>GetGameObjectTrackPointMoveStepIntervalByHandle(goHnd)) then
      [*] = ;      SetGameObjectTrackPointMoveStepIntervalByHandle(goHnd, moveStepInterval);
      [*] = ;
      [*] = ;      if (epsilonDistance<>GetGameObjectEpsilonDistanceByHandle(goHnd)) then
      [*] = ;      SetGameObjectEpsilonDistanceByHandle(goHnd, epsilonDistance);
      [*] = ;
      [*] = ;      if (virtualDirectionStructChild<>0) then
      [*] = ;      SetGameObjectVirtualDirectionByHandle(goHnd, virtualDirectionX, virtualDirectionY, virtualDirectionZ);
      [*] = ;
      [*] = ;      if (turnStep<>GetGameObjectTrackPointTurnStepByHandle(goHnd)) then
      [*] = ;      SetGameObjectTrackPointTurnStepByHandle(goHnd, turnStep);
      [*] = ;
      [*] = ;      if (turnStepInterval<>GetGameObjectTrackPointTurnStepIntervalByHandle(goHnd)) then
      [*] = ;      SetGameObjectTrackPointTurnStepIntervalByHandle(goHnd, turnStepInterval);
      [*] = ;
      [*] = ;      if (epsilonAngle<>GetGameObjectEpsilonAngleByHandle(goHnd)) then
      [*] = ;      SetGameObjectEpsilonAngleByHandle(goHnd, epsilonAngle);
      [*] = ;
      [*] = ;      if (virtualUpStructChild<>0) then
      [*] = ;      SetGameObjectVirtualUpByHandle(goHnd, virtualUpX, virtualUpY, virtualUpZ);
      [*] = ;
      [*] = ;      if (not SameText(distanceToPointReached, GetGameObjectOnStateDistanceToPointByHandle(goHnd))) and (distanceToPoint<>0) then
      [*] = ;      SetGameObjectOnStateDistanceToPointByHandle(goHnd, distanceToPointReached, distanceToPoint);
      [*] = ;
      [*] = ;      if (not SameText(startPointReached, GetGameObjectOnStateStartPointReachedByHandle(goHnd))) then
      [*] = ;      SetGameObjectOnStateStartPointReachedByHandle(goHnd, startPointReached);
      [*] = ;
      [*] = ;      if (not SameText(endPointReached, GetGameObjectOnStateEndPointReachedByHandle(goHnd))) then
      [*] = ;      SetGameObjectOnStateEndPointReachedByHandle(goHnd, endPointReached);
      [*] = ;
      [*] = ;      if (not SameText(directionReached, GetGameObjectOnStateDirectionReachedByHandle(goHnd))) then
      [*] = ;      SetGameObjectOnStateDirectionReachedByHandle(goHnd, directionReached);
      [*] = ;
      [*] = ;      if (rotatingMode<>'') then
      [*] = ;      SetGameObjectTargetRotatingModeByHandle(goHnd, rotatingMode);
      [*] = ;
      [*] = ;      if (currentPointIndexRandom) then
      [*] = ;      currentPointIndex := Floor(Random*GetGameObjectTrackPointCountByHandle(goHnd));
      [*] = ;
      [*] = ;      if (currentPointIndex<>GetGameObjectTrackPointCurrentPointIndexByHandle(goHnd)) and (currentPointIndex>=0) and (currentPointIndex<GetGameObjectTrackPointCountByHandle(goHnd)) then
      [*] = ;      SetGameObjectTrackPointCurrentPointIndexByHandle(goHnd, currentPointIndex);
      [*] = ;
      [*] = ;      if (useAnimationCycles<>GetGameObjectTrackPointUseAnimationCyclesByHandle(goHnd)) then
      [*] = ;      SetGameObjectTrackPointUseAnimationCyclesByHandle(goHnd, useAnimationCycles);
      [*] = ;
      [*] = ;      if (not SameText(animationMove, GetGameObjectTrackPointAnimationNameMoveByHandle(goHnd)))
      [*] = ;      or (not SameText(animationStand, GetGameObjectTrackPointAnimationNameStandByHandle(goHnd))) then
      [*] = ;      SetGameObjectTrackPointAnimationNamesByHandle(goHnd, animationMove, animationStand);
      [*] = ;
      [*] = ;      if (movementMode<>'') and (not SameText(movementMode, GetGameObjectTrackPointMovementModeByHandle(goHnd))) then
      [*] = ;      SetGameObjectTrackPointMovementModeByHandle(goHnd, movementMode);
      [*] = ;
      [*] = ;      if (intervalFactor<>GetGameObjectIntervalFactorByHandle(goHnd)) then
      [*] = ;      SetGameObjectIntervalFactorByHandle(goHnd, intervalFactor);
      [*] = ;
      [*] = ;      SetGameObjectTrackPointExtPoint(goHnd, extPointPositionX, extPointPositionY, extPointPositionZ);
      [*] = ;
      [*] = ;      if {(extPointReached<>'') and }(not SameText(extPointReached, GetGameObjectTrackPointOnStateExtPointReached(goHnd))) then
      [*] = ;      SetGameObjectTrackPointOnStateExtPointReached(goHnd, extPointReached);
      [*] = ;
      [*] = ;      if (extPointCIDist<>GetGameObjectCIDistExtPointEpsilonByHandle(goHnd)) then
      [*] = ;      SetGameObjectCIDistExtPointEpsilonByHandle(goHnd, extPointCIDist);
      [*] = ;
      [*] = ;      if (extPointCIBuild<>GetGameObjectCIBuildExtPointsByHandle(goHnd)) then
      [*] = ;      SetGameObjectCIBuildExtPointsByHandle(goHnd, extPointCIBuild);
      [*] = ;
      [*] = ;      if (extPointEnabled<>GetGameObjectTrackPointExtPointEnabled(goHnd)) then
      [*] = ;      SetGameObjectTrackPointExtPointEnabled(goHnd, extPointEnabled);
      [*] = ;
      [*] = ;      if (callStateAfter<>'') then
      [*] = ;      GameObjectExecuteStateByHandle(goHnd, callStateAfter);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetMiscStruct(ownerHnd, goHnd, miscStruct : Integer);
      [*] = ;begin
      [*] = ;   if (miscStruct<>0) and (ParserGetCountByHandle(miscStruct)>0) then
      [*] = ;   begin
      [*] = ;      var autoTLFAnimationEffect : Boolean = ParserGetBoolValueByKeyByHandleDef(miscStruct, 'autoTLFAnimationEffect', false);
      [*] = ;      var autoProgressChildrenBehaviour : Boolean = ParserGetBoolValueByKeyByHandleDef(miscStruct, 'autoProgressChildrenBehaviour', false);
      [*] = ;      var createTLFAnimationEffect : Boolean = ParserGetBoolValueByKeyByHandleDef(miscStruct, 'createTLFAnimationEffect', false);
      [*] = ;      var destroyTLFAnimationEffect : Boolean = ParserGetBoolValueByKeyByHandleDef(miscStruct, 'destroyTLFAnimationEffect', false);
      [*] = ;      var createProgressChildrenBehaviour : Boolean = ParserGetBoolValueByKeyByHandleDef(miscStruct, 'createProgressChildrenBehaviour', false);
      [*] = ;      var destroyProgressChildrenBehaviour : Boolean = ParserGetBoolValueByKeyByHandleDef(miscStruct, 'destroyProgressChildrenBehaviour', false);
      [*] = ;      var setupIdentityRecTransformation : Boolean = ParserGetBoolValueByKeyByHandleDef(miscStruct, 'setupIdentityRecTransformation', false);
      [*] = ;
      [*] = ;      var goParentHnd : Integer = 0;
      [*] = ;      var goRootHnd : Integer = 0;
      [*] = ;      if (not GetGameObjectIsParent(goHnd)) then
      [*] = ;      begin
      [*] = ;         goParentHnd := GetGameObjectParentHandle(goHnd);
      [*] = ;         goRootHnd := GetGameObjectRootHandleByHandle(goHnd);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         goParentHnd := goHnd;
      [*] = ;         goRootHnd := goHnd;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (autoTLFAnimationEffect) then
      [*] = ;      DoAutoTLFAnimationEffect(ownerHnd, goRootHnd);
      [*] = ;
      [*] = ;      if (autoProgressChildrenBehaviour) then
      [*] = ;      DoAutoProgressChildrenBehaviour(ownerHnd, goRootHnd);
      [*] = ;
      [*] = ;      if (createTLFAnimationEffect) then
      [*] = ;      CreateTLFAnimationEffect(ownerHnd, goHnd);
      [*] = ;
      [*] = ;      if (createProgressChildrenBehaviour) then
      [*] = ;      CreateProgressChildrenBehaviour(ownerHnd, goRootHnd);
      [*] = ;
      [*] = ;      if (destroyTLFAnimationEffect) then
      [*] = ;      DestroyTLFAnimationEffect(ownerHnd, goHnd, true);
      [*] = ;
      [*] = ;      if (destroyProgressChildrenBehaviour) then
      [*] = ;      DestroyProgressChildrenBehaviour(ownerHnd, goRootHnd, True);
      [*] = ;
      [*] = ;      if (setupIdentityRecTransformation) then
      [*] = ;      GameObjectRootSetupIdentityRecTransformationByHandle(goHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetManagersStruct(managersStruct : Integer);
      [*] = ;begin
      [*] = ;   if (managersStruct<>0) and (ParserGetCountByHandle(managersStruct)>0) then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to ParserGetCountByHandle(managersStruct)-1 do
      [*] = ;      begin
      [*] = ;         var childStruct : Integer = ParserSelectByHandleByIndex(managersStruct, i);
      [*] = ;         //var setupFor : String = ParserGetValueByKeyByHandle(childStruct, 'setupFor');
      [*] = ;         //var goHnd : Integer = GetHandleSetupFor(setupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         var managerName : String = ParserGetValueByKeyByHandle(childStruct, 'name'); // managerName
      [*] = ;         var pfxtype : String = ParserGetValueByKeyByHandle(childStruct, 'pfxtype');
      [*] = ;         //var goManagersStruct : Integer = GetOrCreateStructGameObject(goMyHnd, 'managers');
      [*] = ;         //var goManagerIndex : Integer = GetStructIndexOfValue(goManagersStruct, managerName);
      [*] = ;         //if (goManagerIndex<>-1) then
      [*] = ;         //ErrorLog('manager already exists at fx.aix state DoNextNode : GetStructIndexOfValue '+managerName);
      [*] = ;         if (GetPFXManagerExisted(managerName)) then
      [*] = ;         begin
      [*] = ;            ErrorLog('manager already exists at fx.aix state DoNextNode : GetPFXManagerExisted '+managerName);
      [*] = ;            if (not SameText(pfxtype, GetPFXManagerType(managerName))) then
      [*] = ;            begin
      [*] = ;               ErrorLog('existing manager is not compatible by pfxtype at fx.aix state DoNextNode : managerName = '+managerName);
      [*] = ;               SetPFXManagerType(managerName, pfxtype);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         GetOrCreatePFXManager(managerName);
      [*] = ;         LoadPFXManagerFromParser(managerName, childStruct);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetBehavioursStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, behavioursStruct : Integer);
      [*] = ;begin
      [*] = ;   if (behavioursStruct<>0) and (ParserGetCountByHandle(behavioursStruct)>0) then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to ParserGetCountByHandle(behavioursStruct)-1 do
      [*] = ;      begin
      [*] = ;         var behaviourStruct : Integer = ParserSelectByHandleByIndex(behavioursStruct, i);
      [*] = ;         var setupFor : String = ParserGetValueByKeyByHandle(behaviourStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(setupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         var className : String = ParserGetValueByKeyByHandle(behaviourStruct, 'className');
      [*] = ;         var name : String = ParserGetValueByKeyByHandle(behaviourStruct, 'name'); // key
      [*] = ;         var uniq : Boolean = ParserGetBoolValueByKeyByHandleDef(behaviourStruct, 'uniq', true);
      [*] = ;         var destroy : Boolean = ParserGetBoolValueByKeyByHandleDef(behaviourStruct, 'destroy', false);
      [*] = ;         var direct : Boolean = ParserGetBoolValueByKeyByHandleDef(behaviourStruct, 'direct', false);
      [*] = ;         if (className = 'TXMoveRotateWaveBehaviour') then
      [*] = ;         begin
      [*] = ;            var NeedRandomWavingAmp  : Boolean = ParserGetBoolValueByKeyByHandleDef(behaviourStruct, 'NeedRandomWavingAmp', false);
      [*] = ;            var NeedRandomWavingFreg : Boolean = ParserGetBoolValueByKeyByHandleDef(behaviourStruct, 'NeedRandomWavingFreg', false);
      [*] = ;            var RandomWaveTime : Boolean = ParserGetBoolValueByKeyByHandleDef(behaviourStruct, 'RandomWaveTime', false);
      [*] = ;            if (NeedRandomWavingAmp) then
      [*] = ;            begin
      [*] = ;               var WavingAmpXMax : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingAmpXMax');
      [*] = ;               var WavingAmpYMax : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingAmpYMax');
      [*] = ;               var WavingAmpZMax : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingAmpZMax');
      [*] = ;               var WavingAmpX : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingAmpX');
      [*] = ;               var WavingAmpY : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingAmpY');
      [*] = ;               var WavingAmpZ : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingAmpZ');
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WavingAmpX', WavingAmpX + floor((WavingAmpXMax - WavingAmpX) * Random()));
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WavingAmpY', WavingAmpY + floor((WavingAmpYMax - WavingAmpY) * Random()));
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WavingAmpZ', WavingAmpZ + floor((WavingAmpZMax - WavingAmpZ) * Random()));
      [*] = ;            end;
      [*] = ;            if (NeedRandomWavingFreg) then
      [*] = ;            begin
      [*] = ;               var WavingFregXMax : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingFregXMax');
      [*] = ;               var WavingFregYMax : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingFregYMax');
      [*] = ;               var WavingFregZMax : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingFregZMax');
      [*] = ;               var WavingFregX : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingFregX');
      [*] = ;               var WavingFregY : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingFregY');
      [*] = ;               var WavingFregZ : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'WavingFregZ');
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WavingFregX', WavingFregX + floor((WavingFregXMax - WavingFregX) * Random()));
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WavingFregY', WavingFregY + floor((WavingFregYMax - WavingFregY) * Random()));
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WavingFregZ', WavingFregZ + floor((WavingFregZMax - WavingFregZ) * Random()));
      [*] = ;            end;
      [*] = ;            if (RandomWaveTime) then
      [*] = ;            begin
      [*] = ;               var RandomBorder : Integer = ParserGetIntValueByKeyByHandle(behaviourStruct,'RandomBorder');
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WaveTimeX',_rand_Random(RandomBorder));
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WaveTimeY',_rand_Random(RandomBorder));
      [*] = ;               ParserSetIntValueByKeyByHandle(behaviourStruct,'WaveTimeZ',_rand_Random(RandomBorder));
      [*] = ;            end;
      [*] = ;         end;
	  [*] = ;         if (destroy) then
      [*] = ;         begin
      [*] = ;            var behHnd : Integer = 0;
      [*] = ;            if (name<>'') then
      [*] = ;            begin
      [*] = ;               if direct then
      [*] = ;               behHnd := GetBehaviourByKey(goHnd, name)
      [*] = ;               else
      [*] = ;               behHnd := GetOwnerBehaviourHandleByKey(goMyHnd, name);
      [*] = ;               while (behHnd<>0) do
      [*] = ;               begin
      [*] = ;                  DestroyOwnerBehaviour(goMyHnd, behHnd, false); //BehaviourDestroy(behHnd);
      [*] = ;                  if direct then
      [*] = ;                  behHnd := GetBehaviourByKey(goHnd, name)
      [*] = ;                  else
      [*] = ;                  behHnd := GetOwnerBehaviourHandleByKey(goMyHnd, name);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (className<>'') then
      [*] = ;            begin
      [*] = ;               if direct then
      [*] = ;               behHnd := GetBehaviourByClassName(goHnd, className)
      [*] = ;               else
      [*] = ;               behHnd := GetOwnerBehaviourHandleByClass(goMyHnd, className);
      [*] = ;               while (behHnd<>0) do
      [*] = ;               begin
      [*] = ;                  DestroyOwnerBehaviour(goMyHnd, behHnd, false); //BehaviourDestroy(behHnd);
      [*] = ;                  if direct then
      [*] = ;                  behHnd := GetBehaviourByClassName(goHnd, className)
      [*] = ;                  else
      [*] = ;                  behHnd := GetOwnerBehaviourHandleByClass(goMyHnd, className);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (className<>'') then
      [*] = ;         begin
      [*] = ;            var behHnd : Integer = 0;
      [*] = ;            if direct then
      [*] = ;            begin
      [*] = ;               if (name='') then
      [*] = ;               behHnd := BehaviourCreate(goHnd, className, uniq, false)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;               behHnd := BehaviourCreateWithKey(goHnd, className, name, false);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            behHnd := CreateOwnerBehaviour(goMyHnd, goHnd, className, name, uniq);
      [*] = ;            if (behHnd=0) then
      [*] = ;            ErrorLog('error at fx.aix state DoNextNode : BehaviourCreate className '+className);
      [*] = ;            SetBehaviourPropertiesFromParserByHandle(behHnd, behaviourStruct);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DestroyEffectHierarchy(ownerHnd, parentHnd : Integer; className, keyName : String; direct : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetGameObjectCountChildByHandle(parentHnd)-1 do
      [*] = ;   begin
      [*] = ;      var childHnd : Integer = GetGameObjectGOHandleChildByHandle(parentHnd, i);
      [*] = ;      var effHnd : Integer = 0;
      [*] = ;      if (keyName<>'') then
      [*] = ;      begin
      [*] = ;         if direct then
      [*] = ;         effHnd := GetEffectByKey(childHnd, keyName)
      [*] = ;         else
      [*] = ;         effHnd := GetOwnerEffectHandleByKey(ownerHnd, keyName);
      [*] = ;         while (effHnd<>0) do
      [*] = ;         begin
      [*] = ;            DestroyOwnerEffect(ownerHnd, effHnd, false);
      [*] = ;            if direct then
      [*] = ;            effHnd := GetEffectByKey(childHnd, keyName)
      [*] = ;            else
      [*] = ;            effHnd := GetOwnerEffectHandleByKey(ownerHnd, keyName);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (className<>'') then
      [*] = ;      begin
      [*] = ;         if direct then
      [*] = ;         effHnd := GetEffectByClassName(childHnd, className)
      [*] = ;         else
      [*] = ;         effHnd := GetOwnerEffectHandleByClass(ownerHnd, className);
      [*] = ;         while (effHnd<>0) do
      [*] = ;         begin
      [*] = ;            DestroyOwnerEffect(ownerHnd, effHnd, false);
      [*] = ;            if direct then
      [*] = ;            effHnd := GetEffectByClassName(childHnd, className)
      [*] = ;            else
      [*] = ;            effHnd := GetOwnerEffectHandleByClass(ownerHnd, className);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      DestroyEffectHierarchy(ownerHnd, childHnd, className, keyName, direct);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateEffectFXSourceHierarchy(ownerHnd, parentHnd : Integer; libSourceName, libManagerName, keyName : String; effectStruct : Integer; direct : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetGameObjectCountChildByHandle(parentHnd)-1 do
      [*] = ;   begin
      [*] = ;      var childHnd : Integer = GetGameObjectGOHandleChildByHandle(parentHnd, i);
      [*] = ;      var effHnd : Integer = 0;
      [*] = ;      if direct then
      [*] = ;      begin
      [*] = ;         if (libSourceName<>'') then
      [*] = ;         effHnd := GameObjectGetOrCreateEffectFXSourceByHandle(childHnd, libSourceName, keyName)
      [*] = ;         else
      [*] = ;         if (libManagerName<>'') then
      [*] = ;         effHnd := GameObjectGetOrCreateEffectFXManagerByHandle(childHnd, libManagerName, keyName);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      effHnd := CreateOwnerEffectFXSource(ownerHnd, childHnd, libSourceName, libManagerName, keyName);
      [*] = ;      if (effHnd=0) then
      [*] = ;      ErrorLog('error at fx.aix state DoNextNode : CreateEffectFXSourceHierarchy libSourceName '+libSourceName);
      [*] = ;      SetBehaviourPropertiesFromParserByHandle(effHnd, effectStruct);
      [*] = ;      CreateEffectFXSourceHierarchy(ownerHnd, childHnd, libSourceName, libManagerName, keyName, effectStruct, direct);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateEffectHierarchy(ownerHnd, parentHnd : Integer; className, keyName : String; uniq : Boolean; effectStruct : Integer; direct : Boolean);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetGameObjectCountChildByHandle(parentHnd)-1 do
      [*] = ;   begin
      [*] = ;      var childHnd : Integer = GetGameObjectGOHandleChildByHandle(parentHnd, i);
      [*] = ;      var effHnd : Integer = 0;
      [*] = ;      if direct then
      [*] = ;      begin
      [*] = ;         if (keyName='') then
      [*] = ;         effHnd := EffectCreate(childHnd, className, uniq, false)
      [*] = ;         else
      [*] = ;         effHnd := EffectCreateWithKey(childHnd, className, keyName, false);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      effHnd := CreateOwnerEffect(ownerHnd, childHnd, className, keyName, uniq);
      [*] = ;      if (effHnd=0) then
      [*] = ;      ErrorLog('error at fx.aix state DoNextNode : CreateEffectHierarchy className '+className);
      [*] = ;      SetBehaviourPropertiesFromParserByHandle(effHnd, effectStruct);
      [*] = ;      CreateEffectHierarchy(ownerHnd, childHnd, className, keyName, uniq, effectStruct, direct);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetEffectsStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, effectsStruct : Integer);
      [*] = ;begin
      [*] = ;   if (effectsStruct<>0) and (ParserGetCountByHandle(effectsStruct)>0) then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to ParserGetCountByHandle(effectsStruct)-1 do
      [*] = ;      begin
      [*] = ;         var effectStruct : Integer = ParserSelectByHandleByIndex(effectsStruct, i);
      [*] = ;         var setupFor : String = ParserGetValueByKeyByHandle(effectStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(setupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         var libraryEffect : Boolean = ParserGetBoolValueByKeyByHandleDef(effectStruct, 'LibraryEffect', false);
      [*] = ;         var libSourceName : String = ParserGetValueByKeyByHandle(effectStruct, 'LibSourceName');
      [*] = ;         var libManagerName : String = ParserGetValueByKeyByHandle(effectStruct, 'LibManagerName');
      [*] = ;         var className : String = ParserGetValueByKeyByHandle(effectStruct, 'className');
      [*] = ;         var name : String = ParserGetValueByKeyByHandle(effectStruct, 'name'); // key
      [*] = ;         var uniq : Boolean = ParserGetBoolValueByKeyByHandleDef(effectStruct, 'uniq', true);
      [*] = ;         var destroy : Boolean = ParserGetBoolValueByKeyByHandleDef(effectStruct, 'destroy', false);
      [*] = ;         var direct : Boolean = ParserGetBoolValueByKeyByHandleDef(effectStruct, 'direct', false);
      [*] = ;         var hierarchy : Boolean = ParserGetBoolValueByKeyByHandleDef(effectStruct, 'hierarchy', false);
      [*] = ;         if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;            _log_Obj('   Effect: '+name);
      [*] = ;         
      [*] = ;         if (destroy) then
      [*] = ;         begin
      [*] = ;            var effHnd : Integer = 0;
      [*] = ;            if (name<>'') then
      [*] = ;            begin
      [*] = ;               if direct then
      [*] = ;               effHnd := GetEffectByKey(goHnd, name)
      [*] = ;               else
      [*] = ;               effHnd := GetOwnerEffectHandleByKey(goMyHnd, name);
      [*] = ;               while (effHnd<>0) do
      [*] = ;               begin
      [*] = ;                  DestroyOwnerEffect(goMyHnd, effHnd, false); //BehaviourDestroy(effHnd);
      [*] = ;                  if direct then
      [*] = ;                  effHnd := GetEffectByKey(goHnd, name)
      [*] = ;                  else
      [*] = ;                  effHnd := GetOwnerEffectHandleByKey(goMyHnd, name);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (className<>'') then
      [*] = ;            begin
      [*] = ;               if direct then
      [*] = ;               effHnd := GetEffectByClassName(goHnd, className)
      [*] = ;               else
      [*] = ;               effHnd := GetOwnerEffectHandleByClass(goMyHnd, className);
      [*] = ;               while (effHnd<>0) do
      [*] = ;               begin
      [*] = ;                  DestroyOwnerEffect(goMyHnd, effHnd, false); //BehaviourDestroy(effHnd);
      [*] = ;                  if direct then
      [*] = ;                  effHnd := GetEffectByClassName(goHnd, className)
      [*] = ;                  else
      [*] = ;                  effHnd := GetOwnerEffectHandleByClass(goMyHnd, className);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (hierarchy) then
      [*] = ;            DestroyEffectHierarchy(goMyHnd, goHnd, className, name, direct);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (libraryEffect) then
      [*] = ;         begin
      [*] = ;            var effHnd : Integer = 0;
      [*] = ;            if direct then
      [*] = ;            begin
      [*] = ;               if (libSourceName<>'') then
      [*] = ;                  effHnd := GameObjectGetOrCreateEffectFXSourceByHandle(goHnd, libSourceName, name)
      [*] = ;               else
      [*] = ;               if (libManagerName<>'') then
      [*] = ;                  effHnd := GameObjectGetOrCreateEffectFXManagerByHandle(goHnd, libManagerName, name);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               effHnd := CreateOwnerEffectFXSource(goMyHnd, goHnd, libSourceName, libManagerName, name);
      [*] = ;            
      [*] = ;            if (effHnd=0) then
      [*] = ;               ErrorLog('error at fx.aix state DoNextNode : EffectCreate className '+className);
      [*] = ;            
      [*] = ;            SetBehaviourPropertiesFromParserByHandle(effHnd, effectStruct);
      [*] = ;            if (hierarchy) then
      [*] = ;               CreateEffectFXSourceHierarchy(goMyHnd, goHnd, libSourceName, libManagerName, name, effectStruct, direct);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (className<>'') then
      [*] = ;         begin
      [*] = ;            var effHnd : Integer = 0;
      [*] = ;            if direct then
      [*] = ;            begin
      [*] = ;               if (name='') then
      [*] = ;                  effHnd := EffectCreate(goHnd, className, uniq, false)
      [*] = ;               else
      [*] = ;                  effHnd := EffectCreateWithKey(goHnd, className, name, false);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               effHnd := CreateOwnerEffect(goMyHnd, goHnd, className, name, uniq);
      [*] = ;            
      [*] = ;            if (effHnd=0) then
      [*] = ;               ErrorLog('error at fx.aix state DoNextNode : EffectCreate className '+className);
      [*] = ;            
      [*] = ;            SetBehaviourPropertiesFromParserByHandle(effHnd, effectStruct);
      [*] = ;            if (hierarchy) then
      [*] = ;               CreateEffectHierarchy(goMyHnd, goHnd, className, name, uniq, effectStruct, direct);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetDestroyStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, destroyStruct : Integer);
      [*] = ;begin
      [*] = ;   if (destroyStruct<>0) and (ParserGetCountByHandle(destroyStruct)>0) then
      [*] = ;   begin
      [*] = ;      var destroySetupFor : String = ParserGetValueByKeyByHandle(destroyStruct, 'setupFor');
      [*] = ;      var goHnd : Integer = GetHandleSetupFor(destroySetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;
      [*] = ;      var immediatelyBehaviours : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'immediatelyBehaviours', false);
      [*] = ;      var immediatelyEffects : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'immediatelyEffects', false);
      [*] = ;      var immediatelyDecals : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'immediatelyDecals', false);
      [*] = ;      var immediatelyObjects : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'immediatelyObjects', false);
      [*] = ;
      [*] = ;      var myself : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'self', false);
      [*] = ;      var parent : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'parent', false);
      [*] = ;      var root : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'root', false);
      [*] = ;      var target : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'target', false);
      [*] = ;      var selfStateTargetObject : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'selfStateTargetObject', false);
      [*] = ;      var parentStateTargetObject : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'parentStateTargetObject', false);
      [*] = ;      var rootStateTargetObject : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'rootStateTargetObject', false);
      [*] = ;      var targetStateTargetObject : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'targetStateTargetObject', false);
      [*] = ;
      [*] = ;      var clearBehavioursList : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearBehavioursList', false);
      [*] = ;      var clearBehavioursDirect : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearBehavioursDirect', false);
      [*] = ;      var clearBehavioursProgressChildrenIncluded : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearBehavioursProgressChildrenIncluded', false);
      [*] = ;      var clearEffectsList : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearEffectsList', false);
      [*] = ;      var clearEffectsDirect : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearEffectsDirect', false);
      [*] = ;      var clearEffectsTLFAnimationIncluded : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearEffectsTLFAnimationIncluded', false);
      [*] = ;      var clearDecalsList : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearDecalsList', false);
      [*] = ;      var clearDecalsDirect : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearDecalsDirect', false);
      [*] = ;      var clearDecalsAttachedOnly : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearDecalsAttachedOnly', false);
      [*] = ;      var clearDecalsAttachedIncluded : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearDecalsAttachedIncluded', false);
      [*] = ;      var clearObjectsList : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearObjectsList', false);
      [*] = ;      var clearObjectsDirect : Boolean = ParserGetBoolValueByKeyByHandleDef(destroyStruct, 'clearObjectsDirect', false);
      [*] = ;
      [*] = ;      var behavioursStruct : Integer = ParserSelectByHandleByKey(destroyStruct, 'behavioursList');
      [*] = ;      var effectsStruct : Integer = ParserSelectByHandleByKey(destroyStruct, 'effectsList');
      [*] = ;      var decalsStruct : Integer = ParserSelectByHandleByKey(destroyStruct, 'decalsList');
      [*] = ;      var objectsStruct : Integer = ParserSelectByHandleByKey(destroyStruct, 'objectsList');
      [*] = ;
      [*] = ;      {
      [*] = ;      var myHnd : Integer = goHnd;
      [*] = ;      var parentHnd, rootHnd : Integer = 0;
      [*] = ;      if (not GetGameObjectIsParent(myHnd)) then
      [*] = ;      begin
      [*] = ;         parentHnd := GetGameObjectParentHandle(myHnd);
      [*] = ;         rootHnd := GetGameObjectRootHandleByHandle(myHnd);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         parentHnd := myHnd;
      [*] = ;         rootHnd := myHnd;
      [*] = ;      end;
      [*] = ;      var targetHnd : Integer = nodeTarget; //GetGameObjectIntValueIndByHandle(myHnd, gc_GOStack_fx_nodeTarget);
      [*] = ;      }
      [*] = ;
      [*] = ;      if (behavioursStruct<>0) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to ParserGetCountByHandle(behavioursStruct)-1 do
      [*] = ;         begin
      [*] = ;            var behavioursChild : Integer = ParserSelectByHandleByIndex(behavioursStruct, i);
      [*] = ;            var className : String = ParserGetValueByKeyByHandle(behavioursChild, 'className');
      [*] = ;            var name : String = ParserGetValueByKeyByHandle(behavioursChild, 'name'); // key
      [*] = ;            var direct : Boolean = ParserGetBoolValueByKeyByHandleDef(behavioursChild, 'direct', false);
      [*] = ;            var directFor : String = ParserGetValueByKeyByHandle(behavioursChild, 'directFor');
      [*] = ;            var directHnd : Integer = GetHandleSetupFor(directFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;            var behHnd : Integer = 0;
      [*] = ;            if (name<>'') then
      [*] = ;            begin
      [*] = ;               if direct then
      [*] = ;               behHnd := GetBehaviourByKey(directHnd, name)
      [*] = ;               else
      [*] = ;               behHnd := GetOwnerBehaviourHandleByKey(goMyHnd, name);
      [*] = ;               while (behHnd<>0) do
      [*] = ;               begin
      [*] = ;                  DestroyOwnerBehaviour(goMyHnd, behHnd, false); //BehaviourDestroy(behHnd);
      [*] = ;                  if direct then
      [*] = ;                  behHnd := GetBehaviourByKey(directHnd, name)
      [*] = ;                  else
      [*] = ;                  behHnd := GetOwnerBehaviourHandleByKey(goMyHnd, name);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (className<>'') then
      [*] = ;            begin
      [*] = ;               if direct then
      [*] = ;               behHnd := GetBehaviourByClassName(directHnd, className)
      [*] = ;               else
      [*] = ;               behHnd := GetOwnerBehaviourHandleByClass(goMyHnd, className);
      [*] = ;               while (behHnd<>0) do
      [*] = ;               begin
      [*] = ;                  DestroyOwnerBehaviour(goMyHnd, behHnd, false); //BehaviourDestroy(behHnd);
      [*] = ;                  if direct then
      [*] = ;                  behHnd := GetBehaviourByClassName(directHnd, className)
      [*] = ;                  else
      [*] = ;                  behHnd := GetOwnerBehaviourHandleByClass(goMyHnd, className);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (effectsStruct<>0) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to ParserGetCountByHandle(effectsStruct)-1 do
      [*] = ;         begin
      [*] = ;            var effectsChild : Integer = ParserSelectByHandleByIndex(effectsStruct, i);
      [*] = ;            var className : String = ParserGetValueByKeyByHandle(effectsChild, 'className');
      [*] = ;            var name : String = ParserGetValueByKeyByHandle(effectsChild, 'name'); // key
      [*] = ;            var direct : Boolean = ParserGetBoolValueByKeyByHandleDef(effectsChild, 'direct', false);
      [*] = ;            var directFor : String = ParserGetValueByKeyByHandle(effectsChild, 'directFor');
      [*] = ;            var directHnd : Integer = GetHandleSetupFor(directFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;
      [*] = ;            var effHnd : Integer = 0;
      [*] = ;            if (name<>'') then
      [*] = ;            begin
      [*] = ;               if direct then
      [*] = ;               effHnd := GetEffectByKey(directHnd, name)
      [*] = ;               else
      [*] = ;               effHnd := GetOwnerEffectHandleByKey(goMyHnd, name);
      [*] = ;               while (effHnd<>0) do
      [*] = ;               begin
      [*] = ;                  DestroyOwnerEffect(goMyHnd, effHnd, false); //BehaviourDestroy(effHnd);
      [*] = ;                  if direct then
      [*] = ;                  effHnd := GetEffectByKey(directHnd, name)
      [*] = ;                  else
      [*] = ;                  effHnd := GetOwnerEffectHandleByKey(goMyHnd, name);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (className<>'') then
      [*] = ;            begin
      [*] = ;               if direct then
      [*] = ;               effHnd := GetEffectByClassName(directHnd, className)
      [*] = ;               else
      [*] = ;               effHnd := GetOwnerEffectHandleByClass(goMyHnd, className);
      [*] = ;               while (effHnd<>0) do
      [*] = ;               begin
      [*] = ;                  DestroyOwnerEffect(goMyHnd, effHnd, false); //BehaviourDestroy(effHnd);
      [*] = ;                  if direct then
      [*] = ;                  effHnd := GetEffectByClassName(directHnd, className)
      [*] = ;                  else
      [*] = ;                  effHnd := GetOwnerEffectHandleByClass(goMyHnd, className);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (decalsStruct<>0) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to ParserGetCountByHandle(decalsStruct)-1 do
      [*] = ;         begin
      [*] = ;            var decalsChild : Integer = ParserSelectByHandleByIndex(decalsStruct, i);
      [*] = ;            var name : String = ParserGetValueByKeyByHandle(decalsChild, 'name');
      [*] = ;            var matname : String = ParserGetValueByKeyByHandle(decalsChild, 'matname');
      [*] = ;            var direct : Boolean = ParserGetBoolValueByKeyByHandleDef(decalsChild, 'direct', false);
      [*] = ;            var clearFromIndex : Integer = ParserGetIntValueByKeyByHandleDef(decalsChild, 'clearFromIndex', 0);
      [*] = ;            var clearFromFirst : Boolean = ParserGetBoolValueByKeyByHandleDef(decalsChild, 'clearFromFirst', false);
      [*] = ;            var clearFromLatest : Boolean = ParserGetBoolValueByKeyByHandleDef(decalsChild, 'clearFromLatest', false);
      [*] = ;            var clearRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(decalsChild, 'clearRandom', false);
      [*] = ;            var clearMinCount : Integer = ParserGetIntValueByKeyByHandleDef(decalsChild, 'clearMinCount', 0);
      [*] = ;            var clearMaxCount : Integer = ParserGetIntValueByKeyByHandleDef(decalsChild, 'clearMaxCount', 0);
      [*] = ;            var clearCurCount : Integer = Round(Random*(clearMaxCount-clearMinCount))+clearMinCount;
      [*] = ;            var ownerDecalsCount : Integer = GetOwnerDecalsCount(goMyHnd);
      [*] = ;            if (clearCurCount>ownerDecalsCount) then
      [*] = ;            clearCurCount := ownerDecalsCount;
      [*] = ;            if (clearCurCount>0) then
      [*] = ;            begin
      [*] = ;               if (clearRandom) then
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=0 to clearCurCount-1 do
      [*] = ;                  begin
      [*] = ;                     var clearDecalIndex : Integer = Floor(Random*GetOwnerDecalsCount(goMyHnd));
      [*] = ;                     var decalHandle : Integer = GetOwnerDecalHandleByIndex(goMyHnd, clearDecalIndex);
      [*] = ;                     if ((name='') or (SameText(name, GetDecalNameByHandle(decalHandle))))
      [*] = ;                     and((matname='') or (SameText(matname, GetDecalMaterialNameByHandle(decalHandle)))) then
      [*] = ;                     DestroyOwnerDecalByIndex(goMyHnd, clearDecalIndex, immediatelyDecals);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (clearFromLatest) then
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=ownerDecalsCount-1 downto ownerDecalsCount-clearCurCount do
      [*] = ;                  begin
      [*] = ;                     var clearDecalIndex : Integer = j;
      [*] = ;                     var decalHandle : Integer = GetOwnerDecalHandleByIndex(goMyHnd, clearDecalIndex);
      [*] = ;                     if ((name='') or (SameText(name, GetDecalNameByHandle(decalHandle))))
      [*] = ;                     and((matname='') or (SameText(matname, GetDecalMaterialNameByHandle(decalHandle)))) then
      [*] = ;                     DestroyOwnerDecalByIndex(goMyHnd, clearDecalIndex, immediatelyDecals);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (clearFromFirst) then
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=0 to clearCurCount-1 do
      [*] = ;                  begin
      [*] = ;                     var decalHandle : Integer = GetOwnerDecalHandleByIndex(goMyHnd, 0);
      [*] = ;                     if ((name='') or (SameText(name, GetDecalNameByHandle(decalHandle))))
      [*] = ;                     and((matname='') or (SameText(matname, GetDecalMaterialNameByHandle(decalHandle)))) then
      [*] = ;                     DestroyOwnerDecalByIndex(goMyHnd, 0, immediatelyDecals);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  var c : Integer = clearFromIndex + clearCurCount;
      [*] = ;                  if (c>ownerDecalsCount) then
      [*] = ;                  c := ownerDecalsCount;
      [*] = ;                  for j:=clearFromIndex to c-1 do
      [*] = ;                  begin
      [*] = ;                     var decalHandle : Integer = GetOwnerDecalHandleByIndex(goMyHnd, clearFromIndex);
      [*] = ;                     if ((name='') or (SameText(name, GetDecalNameByHandle(decalHandle))))
      [*] = ;                     and((matname='') or (SameText(matname, GetDecalMaterialNameByHandle(decalHandle)))) then
      [*] = ;                     DestroyOwnerDecalByIndex(goMyHnd, clearFromIndex, immediatelyDecals);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (direct) then
      [*] = ;               ClearDecalsByName(goMyHnd, name, matname, immediatelyDecals)
      [*] = ;               else
      [*] = ;               ClearOwnerDecalsByName(goMyHnd, name, matname, immediatelyDecals);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (objectsStruct<>0) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to ParserGetCountByHandle(objectsStruct)-1 do
      [*] = ;         begin
      [*] = ;            var objectsChild : Integer = ParserSelectByHandleByIndex(objectsStruct, i);
      [*] = ;            var baseName : String = ParserGetValueByKeyByHandle(objectsChild, 'baseName');
      [*] = ;            var customName : String = ParserGetValueByKeyByHandle(objectsChild, 'customName');
      [*] = ;            var playerName : String = ParserGetValueByKeyByHandle(objectsChild, 'playerName');
      [*] = ;            var direct : Boolean = ParserGetBoolValueByKeyByHandleDef(objectsChild, 'direct', false);
      [*] = ;            var clearFromIndex : Integer = ParserGetIntValueByKeyByHandleDef(objectsChild, 'clearFromIndex', 0);
      [*] = ;            var clearFromFirst : Boolean = ParserGetBoolValueByKeyByHandleDef(objectsChild, 'clearFromFirst', false);
      [*] = ;            var clearFromLatest : Boolean = ParserGetBoolValueByKeyByHandleDef(objectsChild, 'clearFromLatest', false);
      [*] = ;            var clearRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(objectsChild, 'clearRandom', false);
      [*] = ;            var clearMinCount : Integer = ParserGetIntValueByKeyByHandleDef(objectsChild, 'clearMinCount', 0);
      [*] = ;            var clearMaxCount : Integer = ParserGetIntValueByKeyByHandleDef(objectsChild, 'clearMaxCount', 0);
      [*] = ;            var clearCurCount : Integer = Round(Random*(clearMaxCount-clearMinCount))+clearMinCount;
      [*] = ;            var ownerObjectsCount : Integer = GetOwnerObjectsCount(goMyHnd);
      [*] = ;            if (clearCurCount>ownerObjectsCount) then
      [*] = ;               clearCurCount := ownerObjectsCount;
      [*] = ;            if (clearCurCount>0) then
      [*] = ;            begin
      [*] = ;               if (clearRandom) then
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=0 to clearCurCount-1 do
      [*] = ;                  begin
      [*] = ;                     var clearObjectIndex : Integer = Floor(Random*GetOwnerObjectsCount(goMyHnd));
      [*] = ;                     var objectHandle : Integer = GetOwnerObjectHandleByIndex(goMyHnd, clearObjectIndex);
      [*] = ;                     if ((baseName='') or (SameText(baseName, GetGameObjectBaseNameByHandle(objectHandle))))
      [*] = ;                     and((customName='') or (SameText(customName, GetGameObjectCustomNameByHandle(objectHandle))))
      [*] = ;                     and((playerName='') or (SameText(playerName, GetGameObjectPlayerNameByHandle(objectHandle)))) then
      [*] = ;                     DestroyOwnerObjectByIndex(goMyHnd, clearObjectIndex, immediatelyObjects);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (clearFromLatest) then
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=ownerObjectsCount-1 downto ownerObjectsCount-clearCurCount do
      [*] = ;                  begin
      [*] = ;                     var clearObjectIndex : Integer = j;
      [*] = ;                     var objectHandle : Integer = GetOwnerObjectHandleByIndex(goMyHnd, clearObjectIndex);
      [*] = ;                     if ((baseName='') or (SameText(baseName, GetGameObjectBaseNameByHandle(objectHandle))))
      [*] = ;                     and((customName='') or (SameText(customName, GetGameObjectCustomNameByHandle(objectHandle))))
      [*] = ;                     and((playerName='') or (SameText(playerName, GetGameObjectPlayerNameByHandle(objectHandle)))) then
      [*] = ;                     DestroyOwnerObjectByIndex(goMyHnd, clearObjectIndex, immediatelyObjects);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (clearFromFirst) then
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=0 to clearCurCount-1 do
      [*] = ;                  begin
      [*] = ;                     var objectHandle : Integer = GetOwnerObjectHandleByIndex(goMyHnd, 0);
      [*] = ;                     if ((baseName='') or (SameText(baseName, GetGameObjectBaseNameByHandle(objectHandle))))
      [*] = ;                     and((customName='') or (SameText(customName, GetGameObjectCustomNameByHandle(objectHandle))))
      [*] = ;                     and((playerName='') or (SameText(playerName, GetGameObjectPlayerNameByHandle(objectHandle)))) then
      [*] = ;                     DestroyOwnerObjectByIndex(goMyHnd, 0, immediatelyObjects);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  var c : Integer = clearFromIndex + clearCurCount;
      [*] = ;                  if (c>ownerObjectsCount) then
      [*] = ;                  c := ownerObjectsCount;
      [*] = ;                  for j:=clearFromIndex to c-1 do
      [*] = ;                  begin
      [*] = ;                     var objectHandle : Integer = GetOwnerObjectHandleByIndex(goMyHnd, clearFromIndex);
      [*] = ;                     if ((baseName='') or (SameText(baseName, GetGameObjectBaseNameByHandle(objectHandle))))
      [*] = ;                     and((customName='') or (SameText(customName, GetGameObjectCustomNameByHandle(objectHandle))))
      [*] = ;                     and((playerName='') or (SameText(playerName, GetGameObjectPlayerNameByHandle(objectHandle)))) then
      [*] = ;                     DestroyOwnerObjectByIndex(goMyHnd, clearFromIndex, immediatelyObjects);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (direct) then
      [*] = ;               begin
      [*] = ;                  var objectHandle : Integer = GetObjectHandleByData(0, false, '', baseName, playerName, customName);
      [*] = ;                  //var objectHandle : Integer = GetGameObjectHandleByCustomName(customName, GetPlayerHandleByName(playerName));
      [*] = ;                  if objectHandle<>0 then
      [*] = ;                  begin
      [*] = ;                     if gc_RecycleFX then
      [*] = ;                        _obj_Recycle(objectHandle)
      [*] = ;                     else
      [*] = ;                     if immediatelyObjects then
      [*] = ;                        GameObjectDestroyByHandle(objectHandle)
      [*] = ;                     else
      [*] = ;                        AddObjectToDestroyList(objectHandle);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               ClearOwnerObjectsByName(goMyHnd, baseName, customName, playerName, immediatelyObjects);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (clearBehavioursList) then
      [*] = ;      ClearOwnerBehaviours(goMyHnd, clearBehavioursProgressChildrenIncluded, immediatelyBehaviours);
      [*] = ;
      [*] = ;      if (clearBehavioursDirect) then
      [*] = ;      ClearBehaviours(goMyHnd, goHnd, clearBehavioursProgressChildrenIncluded, immediatelyBehaviours);
      [*] = ;
      [*] = ;      if (clearEffectsList) then
      [*] = ;      ClearOwnerEffects(goMyHnd, clearEffectsTLFAnimationIncluded, immediatelyEffects);
      [*] = ;
      [*] = ;      if (clearEffectsDirect) then
      [*] = ;      ClearEffects(goMyHnd, goHnd, clearEffectsTLFAnimationIncluded, immediatelyEffects);
      [*] = ;
      [*] = ;      if (clearDecalsList) then
      [*] = ;      begin
      [*] = ;         if clearDecalsAttachedOnly then
      [*] = ;         ClearOwnerDecalsAttachedOnly(goMyHnd, immediatelyDecals)
      [*] = ;         else
      [*] = ;         ClearOwnerDecals(goMyHnd, clearDecalsAttachedIncluded, immediatelyDecals);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (clearDecalsDirect) then
      [*] = ;      begin
      [*] = ;         // TODO
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (clearObjectsList) then
      [*] = ;      ClearOwnerObjects(goMyHnd, immediatelyObjects);
      [*] = ;
      [*] = ;      if (clearObjectsDirect) then
      [*] = ;      begin
      [*] = ;         // TODO
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (myself) then
      [*] = ;      DestroyOwnerObject(goMyHnd, goHnd, immediatelyObjects)
      [*] = ;      else
      [*] = ;      if (parent) then
      [*] = ;      DestroyOwnerObject(goMyHnd, goParentHnd, immediatelyObjects)
      [*] = ;      else
      [*] = ;      if (root) then
      [*] = ;      DestroyOwnerObject(goMyHnd, goRootHnd, immediatelyObjects)
      [*] = ;      else
      [*] = ;      if (target) then
      [*] = ;      DestroyOwnerObject(goMyHnd, nodeTarget, immediatelyObjects)
      [*] = ;      else
      [*] = ;      if (selfStateTargetObject) then
      [*] = ;      DestroyOwnerObject(goMyHnd, GetGameObjectSTOHandleByHandle(goHnd), immediatelyObjects)
      [*] = ;      else
      [*] = ;      if (parentStateTargetObject) then
      [*] = ;      DestroyOwnerObject(goMyHnd, GetGameObjectSTOHandleByHandle(goParentHnd), immediatelyObjects)
      [*] = ;      else
      [*] = ;      if (rootStateTargetObject) then
      [*] = ;      DestroyOwnerObject(goMyHnd, GetGameObjectSTOHandleByHandle(goRootHnd), immediatelyObjects)
      [*] = ;      else
      [*] = ;      if (targetStateTargetObject) then
      [*] = ;      DestroyOwnerObject(goMyHnd, GetGameObjectSTOHandleByHandle(nodeTarget), immediatelyObjects);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetObjectsStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, objectsStruct : Integer);
      [*] = ;begin
      [*] = ;   if (objectsStruct<>0) and (ParserGetCountByHandle(objectsStruct)>0) then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to ParserGetCountByHandle(objectsStruct)-1 do
      [*] = ;      begin
      [*] = ;         var objectStruct : Integer = ParserSelectByHandleByIndex(objectsStruct, i);
      [*] = ;         var setupFor : String = ParserGetValueByKeyByHandle(objectStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(setupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;
      [*] = ;         var getOrCreate : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getOrCreate', true);
      [*] = ;         var justCreate : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'justCreate', false);
      [*] = ;         var justGet : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'justGet', false);
      [*] = ;
      [*] = ;         var getAsOwnedObject : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsOwnedObject', true);
      [*] = ;         var getAsChildOfSelf : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsChildOfSelf', false);
      [*] = ;         var getAsChildOfParent : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsChildOfParent', false);
      [*] = ;         var getAsChildOfRoot : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsChildOfRoot', false);
      [*] = ;         var getAsChildOfTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsChildOfTarget', false);
      [*] = ;         var getAsChildOfHierarchySelf : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsChildOfHierarchySelf', false);
      [*] = ;         var getAsChildOfHierarchyParent : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsChildOfHierarchyParent', false);
      [*] = ;         var getAsChildOfHierarchyRoot : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsChildOfHierarchyRoot', false);
      [*] = ;         var getAsChildOfHierarchyTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsChildOfHierarchyTarget', false);
      [*] = ;         var getAsParentOfScene : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'getAsParentOfScene', false);
      [*] = ;
      [*] = ;         var createAsOwnedObject : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'createAsOwnedObject', true);
      [*] = ;         var createAsChildOfSelf : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'createAsChildOfSelf', true);
      [*] = ;         var createAsChildOfParent : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'createAsChildOfParent', false);
      [*] = ;         var createAsChildOfRoot : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'createAsChildOfRoot', false);
      [*] = ;         var createAsChildOfTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'createAsChildOfTarget', false);
      [*] = ;         var createAsParentOnScene : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'createAsParentOfScene', false);
      [*] = ;
      [*] = ;         var raceName : String = ParserGetValueByKeyByHandle(objectStruct, 'raceName');
      [*] = ;         var baseName : String = ParserGetValueByKeyByHandle(objectStruct, 'baseName');
      [*] = ;         var playerName : String = ParserGetValueByKeyByHandle(objectStruct, 'playerName');
      [*] = ;         var customName : String = ParserGetValueByKeyByHandle(objectStruct, 'customName');
      [*] = ;
      [*] = ;         var posInitX : Float = ParserGetFloatValueByKeyByHandleDef(objectStruct, 'posInitX', 0);
      [*] = ;         var posInitY : Float = ParserGetFloatValueByKeyByHandleDef(objectStruct, 'posInitY', 0);
      [*] = ;         var posInitZ : Float = ParserGetFloatValueByKeyByHandleDef(objectStruct, 'posInitZ', 0);
      [*] = ;
      [*] = ;         var tmpx, tmpy, tmpz : Float = 0;
      [*] = ;         if (createAsParentOnScene) then
      [*] = ;            _obj_GetGameObjectAbsolutePosition(goHnd, tmpx, tmpy, tmpz, true)
      [*] = ;         else
      [*] = ;            _obj_GetGameObjectLocalPosition(goHnd, tmpx, tmpy, tmpz, true);
      [*] = ;         posInitX := posInitX + tmpx;
      [*] = ;         posInitY := posInitY + tmpy;
      [*] = ;         posInitZ := posInitZ + tmpz;
      [*] = ;
      [*] = ;         var posDisp : Float = ParserGetFloatValueByKeyByHandleDef(objectStruct, 'posDisp', 0);
      [*] = ;         var posRangeX : Float = ParserGetFloatValueByKeyByHandleDef(objectStruct, 'posRangeX', 0);
      [*] = ;         var posRangeY : Float = ParserGetFloatValueByKeyByHandleDef(objectStruct, 'posRangeY', 0);
      [*] = ;         var posRangeZ : Float = ParserGetFloatValueByKeyByHandleDef(objectStruct, 'posRangeZ', 0);
      [*] = ;
      [*] = ;         var createMinCount : Integer = ParserGetIntValueByKeyByHandleDef(objectStruct, 'createMinCount', 1);
      [*] = ;         var createMaxCount : Integer = ParserGetIntValueByKeyByHandleDef(objectStruct, 'createMaxCount', 1);
      [*] = ;         var createCurCount : Integer = Round(Random*(createMaxCount-createMinCount))+createMinCount;
      [*] = ;
      [*] = ;         var poolObject : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'poolObject', false);
      [*] = ;         var RandomPitchAngle : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'RandomPitchAngle', false);
      [*] = ;         var RandomRollAngle : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'RandomRollAngle', false);
      [*] = ;         var RandomTurnAngle : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'RandomTurnAngle', false);
      [*] = ;         var destroy : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'destroy', false);
      [*] = ;
      [*] = ;         var setToTargetSelf : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'setToTargetSelf', false);
      [*] = ;         var setToStateTargetObjectSelf : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'setToStateTargetObjectSelf', false);
      [*] = ;         var setToStateTargetObjectParent : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'setToStateTargetObjectParent', false);
      [*] = ;         var setToStateTargetObjectRoot : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'setToStateTargetObjectRoot', false);
      [*] = ;         var setToStateTargetObjectTarget : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'setToStateTargetObjectTarget', false);
      [*] = ;
      [*] = ;         var properties : Integer = ParserSelectByHandleByKey(objectStruct, 'properties');
      [*] = ;         var render : Integer = ParserSelectByHandleByKey(objectStruct, 'render');
      [*] = ;         var transformation : Integer = ParserSelectByHandleByKey(objectStruct, 'transformation');
      [*] = ;         var animation : Integer = ParserSelectByHandleByKey(objectStruct, 'animation');
      [*] = ;         var trackpoint : Integer = ParserSelectByHandleByKey(objectStruct, 'trackpoint');
      [*] = ;         var statemachine : Integer = ParserSelectByHandleByKey(objectStruct, 'statemachine');
      [*] = ;         var collision : Integer = ParserSelectByHandleByKey(objectStruct, 'collision');
      [*] = ;         var behavioursAsOwned : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'behavioursAsOwned', false);
      [*] = ;         var behaviours : Integer = ParserSelectByHandleByKey(objectStruct, 'behaviours');
      [*] = ;         var effectsAsOwned : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'effectsAsOwned', false);
      [*] = ;         var effects : Integer = ParserSelectByHandleByKey(objectStruct, 'effects');
      [*] = ;         var misc : Integer = ParserSelectByHandleByKey(objectStruct, 'misc');
      [*] = ;         var fxStruct : Integer = ParserSelectByHandleByKey(objectStruct, 'fx');
      [*] = ;
      [*] = ;         var nodeNamesStruct : Integer = ParserSelectByHandleByKey(objectStruct, 'nodeNames');
      [*] = ;         var nodeNamesRandom : Boolean = ParserGetBoolValueByKeyByHandleDef(objectStruct, 'nodeNamesRandom', false);
      [*] = ;         var nodeNamesRandomMin : Integer = ParserGetIntValueByKeyByHandleDef(objectStruct, 'nodeNamesRandomMin', 0);
      [*] = ;         var nodeNamesRandomMax : Integer = ParserGetIntValueByKeyByHandleDef(objectStruct, 'nodeNamesRandomMax', 0);
      [*] = ;         var nodeNamesRandomNum : Integer = ParserGetCountByHandle(nodeNamesStruct);
      [*] = ;         if (nodeNamesRandom) then
      [*] = ;         nodeNamesRandomNum := Round(Random*(nodeNamesRandomMax-nodeNamesRandomMin))+nodeNamesRandomMin;
      [*] = ;
      [*] = ;         var wasCreated : Boolean = false;
      [*] = ;         var objectHandle : Integer = 0;
      [*] = ;         var objectParent : Integer = 0;
      [*] = ;         if (justGet) or (getOrCreate) then
      [*] = ;         begin
      [*] = ;            if (getAsOwnedObject) then
      [*] = ;            begin
      [*] = ;               if (getAsChildOfSelf) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, goHnd, false, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfParent) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, goParentHnd, false, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfRoot) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, goRootHnd, false, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfTarget) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, nodeTarget, false, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfHierarchySelf) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, goHnd, true, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfHierarchyParent) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, goParentHnd, true, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfHierarchyRoot) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, goRootHnd, true, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfHierarchyTarget) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, nodeTarget, true, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsParentOfScene) and (objectHandle=0) then
      [*] = ;               objectHandle := GetOwnerObjectHandleByData(goMyHnd, 0, false, raceName, baseName, playerName, customName);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (getAsChildOfSelf) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(goHnd, false, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfParent) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(goParentHnd, false, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfRoot) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(goRootHnd, false, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfTarget) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(nodeTarget, false, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfHierarchySelf) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(goHnd, true, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfHierarchyParent) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(goParentHnd, true, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfHierarchyRoot) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(goRootHnd, true, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsChildOfHierarchyTarget) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(nodeTarget, true, raceName, baseName, playerName, customName);
      [*] = ;               if (getAsParentOfScene) and (objectHandle=0) then
      [*] = ;               objectHandle := GetObjectHandleByData(0, false, raceName, baseName, playerName, customName);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         procedure BuildObject(objectHandle : Integer);
      [*] = ;         begin
      [*] = ;            if (setToTargetSelf) then
      [*] = ;            SetIntValueByIndex(gc_GOStack_fx_nodeTarget, objectHandle);
      [*] = ;            if (setToStateTargetObjectSelf) then
      [*] = ;            SetGameObjectSTOHandleByHandle({goHnd}goMyHnd, objectHandle);
      [*] = ;            if (setToStateTargetObjectParent) then
      [*] = ;            SetGameObjectSTOHandleByHandle(goParentHnd, objectHandle);
      [*] = ;            if (setToStateTargetObjectRoot) then
      [*] = ;            SetGameObjectSTOHandleByHandle(goRootHnd, objectHandle);
      [*] = ;            if (setToStateTargetObjectTarget) then
      [*] = ;            SetGameObjectSTOHandleByHandle(nodeTarget, objectHandle);
      [*] = ;            SetPropertiesStruct(objectHandle, properties);
      [*] = ;            if (render<>0) and (ParserGetCountByHandle(render)>0) then
      [*] = ;            begin
      [*] = ;               var renderSetupFor : String = ParserGetValueByKeyByHandle(render, 'setupFor');
      [*] = ;               var renderHandle : Integer = GetHandleSetupFor(renderSetupFor, goParentHnd, goRootHnd, nodeTarget, objectHandle);
      [*] = ;               SetRenderStruct(renderHandle, render);
      [*] = ;            end;
      [*] = ;            SetTransformationStruct(objectHandle, transformation);
      [*] = ;            if (animation<>0) and (ParserGetCountByHandle(animation)>0) then
      [*] = ;            begin
      [*] = ;               var animationSetupFor : String = ParserGetValueByKeyByHandle(animation, 'setupFor');
      [*] = ;               var animationHandle : Integer = GetHandleSetupFor(animationSetupFor, goParentHnd, goRootHnd, nodeTarget, objectHandle);
      [*] = ;               SetAnimationStruct(animationHandle, nodeTarget, animation);
      [*] = ;            end;
      [*] = ;            SetTrackpointStruct(objectHandle, objectHandle, 0, 0, 0, trackpoint);
      [*] = ;            if (statemachine<>0) and (ParserGetCountByHandle(statemachine)>0) then
      [*] = ;            begin
      [*] = ;               var stateMachineSetupFor : String = ParserGetValueByKeyByHandle(statemachine, 'setupFor');
      [*] = ;               var stateObjectHandle : Integer = GetHandleSetupFor(stateMachineSetupFor, goParentHnd, goRootHnd, nodeTarget, objectHandle);
      [*] = ;               SetStateMachineStruct(stateObjectHandle, statemachine);
      [*] = ;            end;
      [*] = ;            SetCollisionStruct(objectHandle, collision);
      [*] = ;            //behavioursAsOwned
      [*] = ;            SetBehavioursStruct(objectHandle, objectHandle, objectHandle, objectHandle, behaviours);
      [*] = ;            //effectsAsOwned
      [*] = ;            SetEffectsStruct(objectHandle, objectHandle, objectHandle, objectHandle, effects);
      [*] = ;            SetMiscStruct(objectHandle, objectHandle, misc);
      [*] = ;         
      [*] = ;            if (fxStruct<>0) and (ParserGetCountByHandle(fxStruct)>0) and SameText(GetGameObjectBaseNameByHandle(objectHandle), 'fx') then
      [*] = ;            begin
      [*] = ;               var switchStruct : Integer = ParserSelectByHandleByKey(fxStruct, 'switch');
      [*] = ;               if (switchStruct<>0) and (ParserGetCountByHandle(switchStruct)>0) then
      [*] = ;               begin
      [*] = ;                  var switchNextNode : String = ParserGetValueByKeyByHandle(switchStruct, 'nextNode');
      [*] = ;                  SetGameObjectValueIndByHandle(objectHandle, gc_GOStack_fx_nextNode, switchNextNode);
      [*] = ;                  var switchSleepTime : Float = ParserGetFloatValueByKeyByHandleDef(switchStruct, 'sleepTime', GetGameObjectFloatValueIndByHandle(objectHandle, gc_GOStack_fx_sleepTime));
      [*] = ;                  SetGameObjectFloatValueIndByHandle(objectHandle, gc_GOStack_fx_sleepTime, switchSleepTime);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            var nodeInd : Integer;
      [*] = ;            for nodeInd:=0 to nodeNamesRandomNum-1 do
      [*] = ;            begin
      [*] = ;               var nodeNamesIndex : Integer = nodeInd;
      [*] = ;               if (nodeNamesRandom) then
      [*] = ;               nodeNamesIndex := Floor(Random*ParserGetCountByHandle(nodeNamesStruct));
      [*] = ;               var nodeNamesChild : Integer = ParserSelectByHandleByIndex(nodeNamesStruct, nodeNamesIndex);
      [*] = ;               var nodeNamesTime : Float = ParserGetFloatValueByKeyByHandleDef(nodeNamesChild, 'time', 0);
      [*] = ;               var nodeNamesName : String = ParserGetValueByKeyByHandle(nodeNamesChild, 'name');
      [*] = ;               var nodeNamesAsOwned : Boolean = ParserGetBoolValueByKeyByHandleDef(nodeNamesChild, 'asOwned', false);
      [*] = ;               if (nodeNamesName<>'') then
      [*] = ;               begin
      [*] = ;                  var fxHnd : Integer = 0;
      [*] = ;                  gStringRegister_fxTree_NodeName := nodeNamesName;
      [*] = ;                  //gIntRegister_fxTree_NodeTarget := 0;
      [*] = ;                  //gFloatRegister_fxTree_CoordTargetX := 0;
      [*] = ;                  //gFloatRegister_fxTree_CoordTargetY := 0;
      [*] = ;                  //gFloatRegister_fxTree_CoordTargetZ := 0;
      [*] = ;                  gFloatRegister_fxTree_SleepTime := nodeNamesTime;
      [*] = ;                  if (nodeNamesAsOwned) then
      [*] = ;                     fxHnd := CreateOwnerObject(goMyHnd, objectHandle, 0, 'misc', 'fx', 'fx', 0, 0, 0)
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     fxHnd := _obj_ChildGetInvisibleOrCreate(objectHandle, 'misc', 'fx');
      [*] = ;                     //fxHnd := GameObjectAddNewChild(objectHandle, 'misc', 'fx');
      [*] = ;                  end;
      [*] = ;                  // gc_GOStack_fx_nextNode      = 5; // 'nextnode'   order to nextNode
      [*] = ;                  // gc_GOStack_fx_nodeTarget    = 6; // 'nodetarget' gIntRegister_fxTree_NodeTarget
      [*] = ;                  // gc_GOStack_fx_coordTargetX  = 7; // 'coordtargetx' gFloatRegister_fxTree_CoordTargetX
      [*] = ;                  // gc_GOStack_fx_coordtargetY  = 8; // 'coordtargety' gFloatRegister_fxTree_CoordTargetY
      [*] = ;                  // gc_GOStack_fx_coordtargetZ  = 9; // 'coordtargetz' gFloatRegister_fxTree_CoordTargetZ
      [*] = ;                  // gc_GOStack_fx_timeDelay     = 10;// 'timeDelay'    gFloatRegister_fxTree_TimeDelay
      [*] = ;                  {
      [*] = ;                  SetGameObjectValueIndByHandle(fxHnd, gc_GOStack_fx_nextNode, nodeNamesName);
      [*] = ;                  SetGameObjectIntValueIndByHandle(fxHnd, gc_GOStack_fx_nodeTarget, 0);
      [*] = ;                  SetGameObjectFloatValueIndByHandle(fxHnd, gc_GOStack_fx_coordTargetX, 0);
      [*] = ;                  SetGameObjectFloatValueIndByHandle(fxHnd, gc_GOStack_fx_coordTargetY, 0);
      [*] = ;                  SetGameObjectFloatValueIndByHandle(fxHnd, gc_GOStack_fx_coordTargetZ, 0);
      [*] = ;                  SetGameObjectFloatValueIndByHandle(fxHnd, gc_GOStack_fx_sleepTime, nodeNamesTime);
      [*] = ;                  }
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (objectHandle=0) and ((getOrCreate) or (justCreate)) then
      [*] = ;         begin
      [*] = ;            if (createAsChildOfSelf) then
      [*] = ;            objectParent := goHnd
      [*] = ;            else
      [*] = ;            if (createAsChildOfParent) then
      [*] = ;            objectParent := goParentHnd
      [*] = ;            else
      [*] = ;            if (createAsChildOfRoot) then
      [*] = ;            objectParent := goRootHnd
      [*] = ;            else
      [*] = ;            if (createAsChildOfTarget) then
      [*] = ;            objectParent := nodeTarget
      [*] = ;            else
      [*] = ;            objectParent := 0;
      [*] = ;
      [*] = ;            var plHnd : Integer = GetPlayerHandleByName(playerName);
      [*] = ;            var createIndex : Integer;
      [*] = ;            for createIndex:=0 to createCurCount-1 do
      [*] = ;            begin
      [*] = ;               var x, y, z : Float = 0;
      [*] = ;               DispersionRange(x, y, z, posInitX, posInitY, posInitZ, posDisp, posRangeX, posRangeY, posRangeZ);
      [*] = ;               if SameText(raceName, 'misc') and SameText(baseName, 'fx') then
      [*] = ;                  gStringRegister_fxTree_NodeName := '';
      [*] = ;               
      [*] = ;               if (createAsOwnedObject) then
      [*] = ;                  objectHandle := CreateOwnerObject(goMyHnd, objectParent, plHnd, raceName, baseName, customName, x, y, z)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (objectParent<>0) then
      [*] = ;                     objectHandle := _obj_ChildGetInvisibleOrCreate(objectParent, raceName, baseName)
      [*] = ;                  else
      [*] = ;                     objectHandle := _obj_GetInvisibleOrCreate(plHnd, raceName, baseName, x, y, z);
      [*] = ;                  
      [*] = ;                  SetGameObjectCustomNameByHandle(objectHandle, customName);
      [*] = ;                  SetGameObjectPositionByHandle(objectHandle, x, y, z);
      [*] = ;                  if (RandomPitchAngle) then
      [*] = ;                     SetGameObjectPitchAngleByHandle(objectHandle,_rand_random(360));
      [*] = ;                  if (RandomRollAngle)  then
      [*] = ;                     SetGameObjectRollAngleByHandle(objectHandle,_rand_random(360));
      [*] = ;                  if (RandomTurnAngle)  then
      [*] = ;                     SetGameObjectTurnAngleByHandle(objectHandle,_rand_random(360));
      [*] = ;               end;
      [*] = ;               
      [*] = ;               if (objectHandle=0) then
      [*] = ;                  ErrorLog('CreateOwnerObject error at fx.aix state DoNextNode')
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  wasCreated := true;
      [*] = ;                  //poolObject
      [*] = ;                  //destroy
      [*] = ;                  BuildObject(objectHandle);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (objectHandle<>0) {and (not wasCreated)} then
      [*] = ;         begin
      [*] = ;            BuildObject(objectHandle);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetDecalsStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, decalsStruct : Integer);
      [*] = ;begin
      [*] = ;   if (decalsStruct<>0) and (ParserGetCountByHandle(decalsStruct)>0) then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to ParserGetCountByHandle(decalsStruct)-1 do
      [*] = ;      begin
      [*] = ;         var decalStruct : Integer = ParserSelectByHandleByIndex(decalsStruct, i);
      [*] = ;         var setupFor : String = ParserGetValueByKeyByHandle(decalStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(setupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         var getOrCreate : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'getOrCreate', true);
      [*] = ;         var justCreate : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'justCreate', false);
      [*] = ;         var justGet : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'justGet', false);
      [*] = ;         var name : String = ParserGetValueByKeyByHandle(decalStruct, 'name');
      [*] = ;         var attach : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'attach', false);
      [*] = ;         var deattach : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'deattach', false);
      [*] = ;         var destroy : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'destroy', false);
      [*] = ;
      [*] = ;         var numMinCount : Integer = ParserGetIntValueByKeyByHandleDef(decalStruct, 'numMinCount', 1);
      [*] = ;         var numMaxCount : Integer = ParserGetIntValueByKeyByHandleDef(decalStruct, 'numMaxCount', 1);
      [*] = ;         var numCurCount : Integer = Round(Random*(numMaxCount-numMinCount))+numMinCount; // Floor ?
      [*] = ;         var numIndCount : Integer;
      [*] = ;         if (not justCreate) then numCurCount := 1;
      [*] = ;         for numIndCount:=0 to numCurCount-1 do
      [*] = ;         begin
      [*] = ;            //var positionStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'position');
      [*] = ;            var initialPositionStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'initialPosition');
      [*] = ;            var positionDispersion : Float = ParserGetFloatValueByKeyByHandleDef(decalStruct, 'positionDispersion', 0);
      [*] = ;            var positionDispersionRangeStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'positionDispersionRange');
      [*] = ;            var positionAbsolute : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'positionAbsolute', false);
      [*] = ;            var initialPositionX, initialPositionZ : Float = 0;
      [*] = ;            if (initialPositionStruct<>0) then
      [*] = ;            begin
      [*] = ;               initialPositionX := ParserGetFloatValueByKeyByHandle(initialPositionStruct, 'X');
      [*] = ;               initialPositionZ := ParserGetFloatValueByKeyByHandle(initialPositionStruct, 'Z');
      [*] = ;            end;
      [*] = ;            var positionDispersionRangeX, positionDispersionRangeZ : Float = 0;
      [*] = ;            if (positionDispersionRangeStruct<>0) then
      [*] = ;            begin
      [*] = ;               positionDispersionRangeX := ParserGetFloatValueByKeyByHandle(positionDispersionRangeStruct, 'X');
      [*] = ;               positionDispersionRangeZ := ParserGetFloatValueByKeyByHandle(positionDispersionRangeStruct, 'Z');
      [*] = ;            end;
      [*] = ;            var positionX, positionY, positionZ : Float = 0;
      [*] = ;            DispersionRange(positionX, positionY, positionZ, initialPositionX, 0, initialPositionZ, positionDispersion, positionDispersionRangeX, 0, positionDispersionRangeZ);
      [*] = ;            if not positionAbsolute then
      [*] = ;            begin
      [*] = ;               positionX := GetGameObjectPositionXByHandle(goHnd)+positionX;
      [*] = ;               //positionY := GetGameObjectPositionYByHandle(goHnd)+positionY;
      [*] = ;               positionZ := GetGameObjectPositionZByHandle(goHnd)+positionZ;
      [*] = ;            end;
      [*] = ;
      [*] = ;            //var texRollAngle : Float = ParserGetFloatValueByKeyByHandleDef(decalStruct, 'texRollAngle', 0);
      [*] = ;            var curTexRollAngle : Float = 0;
      [*] = ;            var texRollAngleStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'texRollAngle');
      [*] = ;            if (texRollAngleStruct<>0) then
      [*] = ;            begin
      [*] = ;               var minTexRollAngle : Float = ParserGetFloatValueByKeyByHandleDef(texRollAngleStruct, 'minTexRollAngle', 0);
      [*] = ;               var maxTexRollAngle : Float = ParserGetFloatValueByKeyByHandleDef(texRollAngleStruct, 'maxTexRollAngle', 0);
      [*] = ;               curTexRollAngle := Random*(maxTexRollAngle-minTexRollAngle)+minTexRollAngle;
      [*] = ;            end;
      [*] = ;
      [*] = ;            var libDecalName : String = ParserGetValueByKeyByHandle(decalStruct, 'libDecalName');
      [*] = ;            var libDecalRandStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'libDecalRand');
      [*] = ;            if (libDecalRandStruct<>0) and (ParserGetCountByHandle(libDecalRandStruct)>0) then
      [*] = ;            begin
      [*] = ;               var libDecalRandInd : Integer = Floor(Random*ParserGetCountByHandle(libDecalRandStruct));
      [*] = ;               libDecalName := ParserGetValueByIndexByHandle(libDecalRandStruct, libDecalRandInd);
      [*] = ;            end;
      [*] = ;
      [*] = ;            var decHnd : Integer = 0;
      [*] = ;            var wasBorned : Boolean = false;
      [*] = ;
      [*] = ;            if (justGet) then
      [*] = ;            decHnd := GetOwnerDecalHandleByName(goMyHnd, name)
      [*] = ;            else
      [*] = ;            if (getOrCreate) then
      [*] = ;            begin
      [*] = ;               decHnd := GetOwnerDecalHandleByName(goMyHnd, name);
      [*] = ;               if (decHnd=0) then
      [*] = ;               begin
      [*] = ;                  decHnd := CreateOwnerDecal(goMyHnd, goHnd, libDecalName, name, positionX, positionZ, curTexRollAngle, attach, false);
      [*] = ;                  wasBorned := true;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (justCreate) then
      [*] = ;            begin
      [*] = ;               decHnd := CreateOwnerDecal(goMyHnd, goHnd, libDecalName, name, positionX, positionZ, curTexRollAngle, attach, false);
      [*] = ;               wasBorned := true;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (decHnd<>0) then
      [*] = ;            begin
      [*] = ;               if (not wasBorned) then
      [*] = ;               begin
      [*] = ;                  var decParentHnd : Integer = GetDecalParentHndByHandle(decHnd);
      [*] = ;                  if (attach) then
      [*] = ;                  begin
      [*] = ;                     if (decParentHnd<>goHnd) then
      [*] = ;                     SetDecalParentHndByHandle(decHnd, goHnd);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (deattach) then
      [*] = ;                  begin
      [*] = ;                     if (decParentHnd<>0) then
      [*] = ;                     SetDecalParentHndByHandle(decHnd, 0);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var w, h, x, z, texOff0, texOff1, scale0, scale1, texScale0, texScale1, texAng, eps : Float;
      [*] = ;               var texRot, texScale, texOff, texOffRot : Boolean;
      [*] = ;               var libMat, decName : String;
      [*] = ;               GetDecalDataByHandle(decHnd, w, h, x, z, texOff0, texOff1, scale0, scale1, texScale0, texScale1, texAng, eps, texRot, texScale, texOff, texOffRot, libMat, decName);
      [*] = ;
      [*] = ;               var width : Float = ParserGetFloatValueByKeyByHandleDef(decalStruct, 'width', w);
      [*] = ;               var height : Float = ParserGetFloatValueByKeyByHandleDef(decalStruct, 'height', h);
      [*] = ;               var texOffsetStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'texOffset');
      [*] = ;               var texOffsetX : Float = ParserGetFloatValueByKeyByHandleDef(texOffsetStruct, 'X', texOff0);
      [*] = ;               var texOffsetZ : Float = ParserGetFloatValueByKeyByHandleDef(texOffsetStruct, 'Z', texOff1);
      [*] = ;               //var scaleFactorStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'scaleFactor');
      [*] = ;               //var scaleFactorX : Float = ParserGetFloatValueByKeyByHandleDef(scaleFactorStruct, 'X', scale0);
      [*] = ;               //var scaleFactorZ : Float = ParserGetFloatValueByKeyByHandleDef(scaleFactorStruct, 'Z', scale1);
      [*] = ;               var texScaleStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'texScale');
      [*] = ;               var texScaleX : Float = ParserGetFloatValueByKeyByHandleDef(texScaleStruct, 'X', texScale0);
      [*] = ;               var texScaleZ : Float = ParserGetFloatValueByKeyByHandleDef(texScaleStruct, 'Z', texScale1);
      [*] = ;               var epsilon : Float = ParserGetFloatValueByKeyByHandleDef(decalStruct, 'epsilon', eps);
      [*] = ;               var texRotateEnable : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'texRotateEnable', texRot);
      [*] = ;               var texScaleEnable : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'texScaleEnable', texScale);
      [*] = ;               var texOffsetEnable : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'texOffsetEnable', texOff);
      [*] = ;               var texOffsetByRotate : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'texOffsetByRotate', texOffRot);
      [*] = ;               var libMaterialName : String = ParserGetValueByKeyByHandle(decalStruct, 'libMaterialName');
      [*] = ;               var libMaterialRandStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'libMaterialRand');
      [*] = ;               if (libMaterialRandStruct<>0) and (ParserGetCountByHandle(libMaterialRandStruct)>0) then
      [*] = ;               begin
      [*] = ;                  var libMaterialRandInd : Integer = Floor(Random*ParserGetCountByHandle(libMaterialRandStruct));
      [*] = ;                  libMaterialName := ParserGetValueByIndexByHandle(libMaterialRandStruct, libMaterialRandInd);
      [*] = ;               end;
      [*] = ;               if (libMaterialName='') then libMaterialName := libMat;
      [*] = ;               if (name='') then name := decName;
      [*] = ;               var scaleFactorX : Float = scale0;
      [*] = ;               var scaleFactorZ : Float = scale1;
      [*] = ;               var initialScaleStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'initialScale');
      [*] = ;               var scaleDispersion : Float = ParserGetFloatValueByKeyByHandleDef(decalStruct, 'scaleDispersion', 0);
      [*] = ;               var scaleDispersionRangeStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'scaleDispersionRange');
      [*] = ;               var scaleAbsolute : Boolean = ParserGetBoolValueByKeyByHandleDef(decalStruct, 'scaleAbsolute', false);
      [*] = ;               var initialScaleX, initialScaleZ : Float = 1;
      [*] = ;               var scaleDispersionRangeX, scaleDispersionRangeZ : Float = 0;
      [*] = ;               if (initialScaleStruct<>0) and (scaleDispersionRangeStruct<>0) then
      [*] = ;               begin
      [*] = ;                  initialScaleX := ParserGetFloatValueByKeyByHandle(initialScaleStruct, 'X');
      [*] = ;                  initialScaleZ := ParserGetFloatValueByKeyByHandle(initialScaleStruct, 'Z');
      [*] = ;                  scaleDispersionRangeX := ParserGetFloatValueByKeyByHandle(scaleDispersionRangeStruct, 'X');
      [*] = ;                  scaleDispersionRangeZ := ParserGetFloatValueByKeyByHandle(scaleDispersionRangeStruct, 'Z');
      [*] = ;                  var scaleX, scaleY, scaleZ : Float = 0;
      [*] = ;                  DispersionRangeAbs(scaleX, scaleY, scaleZ, initialScaleX, 1, initialScaleZ, scaleDispersion, scaleDispersionRangeX, 0, scaleDispersionRangeZ);
      [*] = ;                  if scaleAbsolute then
      [*] = ;                  begin
      [*] = ;                     scaleFactorX := scaleX;
      [*] = ;                     scaleFactorZ := scaleZ;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     scaleFactorX := scaleFactorX * scaleX;
      [*] = ;                     scaleFactorZ := scaleFactorZ * scaleZ;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               //positionX := ParserGetFloatValueByKeyByHandleDef(positionStruct, 'X', x);
      [*] = ;               //positionZ := ParserGetFloatValueByKeyByHandleDef(positionStruct, 'Z', z);
      [*] = ;               if (initialPositionStruct=0) then
      [*] = ;               begin
      [*] = ;                  positionX := x;
      [*] = ;                  positionZ := z;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (texRollAngleStruct=0) then
      [*] = ;               curTexRollAngle := texAng;
      [*] = ;
      [*] = ;               SetDecalDataByHandle(decHnd, width, height, positionX, positionZ, texOffsetX, texOffsetZ, scaleFactorX, scaleFactorZ, texScaleX, texScaleZ, curTexRollAngle, epsilon, texRotateEnable, texScaleEnable, texOffsetEnable, texOffsetByRotate, libMaterialName, name);
      [*] = ;
      [*] = ;               if (ParserGetBoolValueByKeyByHandleDef(decalStruct, 'behavioursClear', false)) then
      [*] = ;               BaseObjectBehaviourClear(decHnd);
      [*] = ;               var behsStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'behaviours');
      [*] = ;               if (behsStruct<>0) then
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=0 to ParserGetCountByHandle(behsStruct)-1 do
      [*] = ;                  begin
      [*] = ;                     var behStruct : Integer = ParserSelectByHandleByIndex(behsStruct, j);
      [*] = ;                     var className : String = ParserGetValueByKeyByHandle(behStruct, 'className');
      [*] = ;                     var name : String = ParserGetValueByKeyByHandle(behStruct, 'name'); // key
      [*] = ;                     var uniq : Boolean = ParserGetBoolValueByKeyByHandle(behStruct, 'uniq');
      [*] = ;                     var destroy : Boolean = ParserGetBoolValueByKeyByHandle(behStruct, 'destroy');
      [*] = ;                     if (destroy) then
      [*] = ;                     begin
      [*] = ;                        var behHnd : Integer = 0;
      [*] = ;                        if (name<>'') then
      [*] = ;                        behHnd := GetBaseObjectBehaviourByKey(decHnd, name)
      [*] = ;                        else
      [*] = ;                        if (className<>'') then
      [*] = ;                        behHnd := GetBaseObjectBehaviourByClassName(decHnd, className);
      [*] = ;                        if (behHnd<>0) then
      [*] = ;                        BehaviourDestroy(behHnd);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     if (className<>'') then
      [*] = ;                     begin
      [*] = ;                        var behHnd : Integer = 0;
      [*] = ;                        if (name='') then
      [*] = ;                        behHnd := BaseObjectBehaviourCreate(decHnd, className, uniq, false)
      [*] = ;                        else
      [*] = ;                        behHnd := BaseObjectBehaviourCreateWithKey(decHnd, className, name, false);
      [*] = ;                        if (behHnd=0) then
      [*] = ;                        ErrorLog('error at fx.aix state DoNextNode : BaseObjectBehaviourCreate className '+className);
      [*] = ;                        SetBehaviourPropertiesFromParserByHandle(behHnd, behStruct);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (ParserGetBoolValueByKeyByHandleDef(decalStruct, 'effectsClear', false)) then
      [*] = ;               BaseObjectEffectClear(decHnd);
      [*] = ;               var effsStruct : Integer = ParserSelectByHandleByKey(decalStruct, 'effects');
      [*] = ;               if (effsStruct<>0) then
      [*] = ;               begin
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=0 to ParserGetCountByHandle(effsStruct)-1 do
      [*] = ;                  begin
      [*] = ;                     var effStruct : Integer = ParserSelectByHandleByIndex(effsStruct, j);
      [*] = ;                     var className : String = ParserGetValueByKeyByHandle(effStruct, 'className');
      [*] = ;                     var name : String = ParserGetValueByKeyByHandle(effStruct, 'name'); // key
      [*] = ;                     var uniq : Boolean = ParserGetBoolValueByKeyByHandle(effStruct, 'uniq');
      [*] = ;                     var destroy : Boolean = ParserGetBoolValueByKeyByHandle(effStruct, 'destroy');
      [*] = ;                     if (destroy) then
      [*] = ;                     begin
      [*] = ;                        var effHnd : Integer = 0;
      [*] = ;                        if (name<>'') then
      [*] = ;                        effHnd := GetBaseObjectEffectByKey(decHnd, name)
      [*] = ;                        else
      [*] = ;                        if (className<>'') then
      [*] = ;                        effHnd := GetBaseObjectEffectByClassName(decHnd, className);
      [*] = ;                        if (effHnd<>0) then
      [*] = ;                        BehaviourDestroy(effHnd);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     if (className<>'') then
      [*] = ;                     begin
      [*] = ;                        var effHnd : Integer = 0;
      [*] = ;                        if (name='') then
      [*] = ;                        effHnd := BaseObjectEffectCreate(decHnd, className, uniq, false)
      [*] = ;                        else
      [*] = ;                        effHnd := BaseObjectEffectCreateWithKey(decHnd, className, name, false);
      [*] = ;                        if (effHnd=0) then
      [*] = ;                        ErrorLog('error at fx.aix state DoNextNode : BaseObjectEffectCreate className '+className);
      [*] = ;                        SetBehaviourPropertiesFromParserByHandle(effHnd, effStruct);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if destroy then
      [*] = ;               DestroyDecalByHandle(decHnd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;if GetIntValueByIndex(gc_GOStack_fx_status) = 5 then
      [*] = ;begin
      [*] = ;   SwitchTo('DoNothing');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (GetFloatValueByIndex(gc_GOStack_fx_sleepTime)>0) then
      [*] = ;begin
      [*] = ;   GameObjectDelayExecuteStateByHandle(GetGameObjectMyHandle(), 'DoNextNode', GetFloatValueByIndex(gc_GOStack_fx_sleepTime));
      [*] = ;   SetFloatValueByIndex(gc_GOStack_fx_sleepTime, 0);
      [*] = ;   SetIntValueByIndex(gc_GOStack_fx_status, 2); // 2 - sleep
      [*] = ;   SwitchTo('DoNothing');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var nextNodeName : String = GetValueByIndex(gc_GOStack_fx_nextNode);
      [*] = ;var nextNodeHandle : Integer = 0;
      [*] = ;
      [*] = ;if (nextNodeName<>'') then
      [*] = ;begin
      [*] = ;   var goMyHnd : Integer = GetGameObjectMyHandle;
      [*] = ;   if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;      _log_Obj(IntToStr(goMyHnd)+', DoNextNode: '+nextNodeName);
      [*] = ;   
      [*] = ;   if (gIntRegister_fxTree_RootHandle=0) then
      [*] = ;   ExecuteState('DoLibLoad');
      [*] = ;   gStringRegister_fxTree_NodeName := nextNodeName;
      [*] = ;   ExecuteState('GetLibNodeByName');
      [*] = ;   nextNodeHandle := gIntRegister_fxTree_NodeHandle;
      [*] = ;   gStringRegister_fxTree_NodeName := '';
      [*] = ;   gIntRegister_fxTree_NodeHandle := 0;
      [*] = ;   if (nextNodeHandle<>0) then
      [*] = ;   begin
      [*] = ;      SetIntValueByIndex(gc_GOStack_fx_status, 1); // 1 - run
      [*] = ;      SetFloatValueByIndex(gc_GOStack_fx_progTime, GetGameTime);
      [*] = ;      SetValueByIndex(gc_GOStack_fx_nodeName, nextNodeName);
      [*] = ;      SetValueByIndex(gc_GOStack_fx_nextNode, '');
      [*] = ;
      [*] = ;      // nextNodeHandle
      [*] = ;      var nodeTarget : Integer = GetIntValueByIndex(gc_GOStack_fx_nodeTarget);
      [*] = ;      var coordTargetX : Float = GetFloatValueByIndex(gc_GOStack_fx_coordTargetX);
      [*] = ;      var coordTargetY : Float = GetFloatValueByIndex(gc_GOStack_fx_coordTargetY);
      [*] = ;      var coordTargetZ : Float = GetFloatValueByIndex(gc_GOStack_fx_coordTargetZ);
      [*] = ;
      [*] = ;      var isRoot : Boolean = GetGameObjectIsParent(goMyHnd);
      [*] = ;      var goParentHnd : Integer = 0;
      [*] = ;      var goRootHnd : Integer = 0;
      [*] = ;      if (not isRoot) then
      [*] = ;      begin
      [*] = ;         goParentHnd := GetGameObjectParentHandle(goMyHnd);
      [*] = ;         goRootHnd := GetGameObjectRootHandleByHandle(goMyHnd);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         goParentHnd := goMyHnd;
      [*] = ;         goRootHnd := goMyHnd;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if _log or (gc_RecycleFX and gc_LogRecycling) then
      [*] = ;         _log_Obj('FX Parent: '+IntToStr(goParentHnd)+' '+GetGameObjectBaseNameByHandle(goParentHnd));
      [*] = ;
      [*] = ;      //
      [*] = ;      // destroy
      [*] = ;      //
      [*] = ;      if not gc_RecycleFX then
      [*] = ;      begin
      [*] = ;         var destroyStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'destroy');
      [*] = ;         if (destroyStruct<>0) and (ParserGetCountByHandle(destroyStruct)>0) then
      [*] = ;         SetDestroyStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, destroyStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // objects
      [*] = ;      //
      [*] = ;      var objectsStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'objects');
      [*] = ;      if (objectsStruct<>0) and (ParserGetCountByHandle(objectsStruct)>0) then
      [*] = ;      SetObjectsStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, objectsStruct);
      [*] = ;
      [*] = ;      //
      [*] = ;      // decals
      [*] = ;      //
      [*] = ;      var decalsStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'decals');
      [*] = ;      if (decalsStruct<>0) and (ParserGetCountByHandle(decalsStruct)>0) then
      [*] = ;      SetDecalsStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, decalsStruct);
      [*] = ;
      [*] = ;      //
      [*] = ;      // properties
      [*] = ;      //
      [*] = ;      var propStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'properties');
      [*] = ;      if (propStruct<>0) and (ParserGetCountByHandle(propStruct)>0) then
      [*] = ;      begin
      [*] = ;         var propSetupFor : String = ParserGetValueByKeyByHandle(propStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(propSetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         SetPropertiesStruct(goHnd, propStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // render
      [*] = ;      //
      [*] = ;      var renderStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'render');
      [*] = ;      if (renderStruct<>0) and (ParserGetCountByHandle(renderStruct)>0) then
      [*] = ;      begin
      [*] = ;         var renderSetupFor : String = ParserGetValueByKeyByHandle(renderStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(renderSetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         SetRenderStruct(goHnd, renderStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // animation
      [*] = ;      //
      [*] = ;      var animStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'animation');
      [*] = ;      if (animStruct<>0) and (ParserGetCountByHandle(animStruct)>0) then
      [*] = ;      begin
      [*] = ;         var animSetupFor : String = ParserGetValueByKeyByHandle(animStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(animSetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         SetAnimationStruct(goHnd, nodeTarget, animStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // trackpoint
      [*] = ;      //
      [*] = ;      var trackpointStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'trackpoint');
      [*] = ;      if (trackpointStruct<>0) and (ParserGetCountByHandle(trackpointStruct)>0) then
      [*] = ;      begin
      [*] = ;         var trackpointSetupFor : String = ParserGetValueByKeyByHandle(trackpointStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(trackpointSetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         SetTrackpointStruct(goHnd, nodeTarget, coordTargetX, coordTargetY, coordTargetZ, trackpointStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // statemachine
      [*] = ;      //
      [*] = ;      var statemachineStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'statemachine');
      [*] = ;      if (statemachineStruct<>0) and (ParserGetCountByHandle(statemachineStruct)>0) then
      [*] = ;      begin
      [*] = ;         var statemachineSetupFor : String = ParserGetValueByKeyByHandle(statemachineStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(statemachineSetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         SetStateMachineStruct(goHnd, statemachineStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // transformation
      [*] = ;      //
      [*] = ;      var transformationStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'transformation');
      [*] = ;      if (transformationStruct<>0) and (ParserGetCountByHandle(transformationStruct)>0) then
      [*] = ;      begin
      [*] = ;         var transformationSetupFor : String = ParserGetValueByKeyByHandle(transformationStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(transformationSetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         SetTransformationStruct(goHnd, transformationStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // collision
      [*] = ;      //
      [*] = ;      var collisionStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'collision');
      [*] = ;      if (collisionStruct<>0) and (ParserGetCountByHandle(collisionStruct)>0) then
      [*] = ;      begin
      [*] = ;         var collisionSetupFor : String = ParserGetValueByKeyByHandle(collisionStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(collisionSetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         SetCollisionStruct(goHnd, collisionStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // behaviours
      [*] = ;      //
      [*] = ;      var behavioursStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'behaviours');
      [*] = ;      if (behavioursStruct<>0) and (ParserGetCountByHandle(behavioursStruct)>0) then
      [*] = ;      SetBehavioursStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, behavioursStruct);
      [*] = ;
      [*] = ;      //
      [*] = ;      // managers
      [*] = ;      //
      [*] = ;      var managersStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'managers');
      [*] = ;      if (managersStruct<>0) and (ParserGetCountByHandle(managersStruct)>0) then
      [*] = ;      SetManagersStruct(managersStruct);
      [*] = ;
      [*] = ;      //
      [*] = ;      // effects
      [*] = ;      //
      [*] = ;      var effectsStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'effects');
      [*] = ;      if (effectsStruct<>0) and (ParserGetCountByHandle(effectsStruct)>0) then
      [*] = ;      SetEffectsStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, effectsStruct);
      [*] = ;
      [*] = ;      //
      [*] = ;      // misc
      [*] = ;      //
      [*] = ;      var miscStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'misc');
      [*] = ;      if (miscStruct<>0) and (ParserGetCountByHandle(miscStruct)>0) then
      [*] = ;      begin
      [*] = ;         var miscSetupFor : String = ParserGetValueByKeyByHandle(miscStruct, 'setupFor');
      [*] = ;         var goHnd : Integer = GetHandleSetupFor(miscSetupFor, goParentHnd, goRootHnd, nodeTarget, goMyHnd);
      [*] = ;         SetMiscStruct(goMyHnd, goHnd, miscStruct);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //
      [*] = ;      // fx
      [*] = ;      //
      [*] = ;      var bDestroy : Boolean = false;
      [*] = ;         
      [*] = ;      var fxStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'fx');
      [*] = ;      if (fxStruct<>0) and (ParserGetCountByHandle(fxStruct)>0) then
      [*] = ;      begin
      [*] = ;         var destroyNode : String = ParserGetValueByKeyByHandle(fxStruct, 'destroyNode');
      [*] = ;         SetValueByIndex(gc_GOStack_fx_destroyNode, destroyNode);
      [*] = ;
      [*] = ;         // TODO : Hierarchy
      [*] = ;         var destroyBehav : Boolean = ParserGetBoolValueByKeyByHandleDef(fxStruct, 'destroyBehaviours', GetBoolValueByIndex(gc_GOStack_fx_destroyBehav));
      [*] = ;         SetBoolValueByIndex(gc_GOStack_fx_destroyBehav, destroyBehav);
      [*] = ;         var destroyEffect : Boolean = ParserGetBoolValueByKeyByHandleDef(fxStruct, 'destroyEffect', GetBoolValueByIndex(gc_GOStack_fx_destroyEffect));
      [*] = ;         SetBoolValueByIndex(gc_GOStack_fx_destroyEffect, destroyEffect);
      [*] = ;         var destroyDecal : Boolean = ParserGetBoolValueByKeyByHandleDef(fxStruct, 'destroyDecal', GetBoolValueByIndex(gc_GOStack_fx_destroyDecal));
      [*] = ;         SetBoolValueByIndex(gc_GOStack_fx_destroyDecal, destroyDecal);
      [*] = ;         var destroyObject : Boolean = ParserGetBoolValueByKeyByHandleDef(fxStruct, 'destroyObject', GetBoolValueByIndex(gc_GOStack_fx_destroyObject));
      [*] = ;         SetBoolValueByIndex(gc_GOStack_fx_destroyObject, destroyObject);
      [*] = ;
      [*] = ;         var id : String = ParserGetValueByKeyByHandle(fxStruct, 'id');
      [*] = ;         if (id<>'') then
      [*] = ;         begin
      [*] = ;            if SameText(id, 'this') then
      [*] = ;            SetIntValueByIndex(gc_GOStack_fx_id, _fx_GetIDByNodeName(nextNodeName))
      [*] = ;            else
      [*] = ;            SetIntValueByIndex(gc_GOStack_fx_id, StrToInt(id));
      [*] = ;         end;
      [*] = ;
      [*] = ;         var i : Integer;
      [*] = ;         var stackStruct : Integer = ParserSelectByHandleByKey(fxStruct, 'stack');
      [*] = ;         for i:=0 to ParserGetCountByHandle(stackStruct)-1 do
      [*] = ;         begin
      [*] = ;            var variable : Integer = ParserSelectByHandleByIndex(stackStruct, i);
      [*] = ;            var key : String = ParserGetKeyName(variable);
      [*] = ;            var value : String = ParserGetValueByIndexByHandle(stackStruct, i);
      [*] = ;            SetGameObjectValueByHandle(goMyHnd, key, value);
      [*] = ;         end;
      [*] = ;
      [*] = ;         var switchStruct : Integer = ParserSelectByHandleByKey(fxStruct, 'switch');
      [*] = ;         if (switchStruct<>0) and (ParserGetCountByHandle(switchStruct)>0) then
      [*] = ;         begin
      [*] = ;            var switchNextNode : String = ParserGetValueByKeyByHandle(switchStruct, 'nextNode');
      [*] = ;            SetValueByIndex(gc_GOStack_fx_nextNode, switchNextNode);
      [*] = ;            var switchSleepTime : Float = ParserGetFloatValueByKeyByHandleDef(switchStruct, 'sleepTime', GetFloatValueByIndex(gc_GOStack_fx_sleepTime));
      [*] = ;            SetFloatValueByIndex(gc_GOStack_fx_sleepTime, switchSleepTime);
      [*] = ;         end;
      [*] = ;
      [*] = ;         var runStruct : Integer = ParserSelectByHandleByKey(fxStruct, 'run');
      [*] = ;         if (runStruct<>0) and (ParserGetCountByHandle(runStruct)>0) then
      [*] = ;         begin
      [*] = ;            var runNextNode : String = ParserGetValueByKeyByHandle(runStruct, 'nextNode');
      [*] = ;            var runSleepTime : Float = ParserGetFloatValueByKeyByHandleDef(runStruct, 'sleepTime', 0);
      [*] = ;            if (runNextNode<>'') then
      [*] = ;            begin
      [*] = ;               //SetFloatValueByIndex(gc_GOStack_fx_sleepTime, 0);
      [*] = ;               SetValueByIndex(gc_GOStack_fx_nextNode, runNextNode);
      [*] = ;               GameObjectCancelDelayExecuteStateByHandle(goMyHnd);
      [*] = ;               GameObjectDelayExecuteStateByHandle(goMyHnd, 'DoNextNode', runSleepTime);
      [*] = ;               SetIntValueByIndex(gc_GOStack_fx_status, 2); // 2 - sleep
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;   
      [*] = ;         if gc_RecycleFX then
      [*] = ;         begin
      [*] = ;            if (ParserGetBoolValueByKeyByHandleDef(fxStruct, 'reqDestroy', false)) then
      [*] = ;            begin
      [*] = ;               //ExecuteState('DoCleanSafe');
      [*] = ;               if GetBoolValueByIndex(gc_GOStack_fx_destroyEffect) then
      [*] = ;                  ClearOwnerEffects(goMyHnd, false, false);
      [*] = ;            
      [*] = ;               if GetBoolValueByIndex(gc_GOStack_fx_destroyDecal) then
      [*] = ;                  ClearOwnerDecals(goMyHnd, false, false);
      [*] = ;            
      [*] = ;               if GetBoolValueByIndex(gc_GOStack_fx_destroyBehav) then
      [*] = ;                  ClearOwnerBehaviours(goMyHnd, false, false);
      [*] = ;            
      [*] = ;               if GetBoolValueByIndex(gc_GOStack_fx_destroyObject) then
      [*] = ;                  ClearOwnerObjects(goMyHnd, false);
      [*] = ;            
      [*] = ;               bDestroy := true;
      [*] = ;               //AddObjectToDestroyList(goMyHnd);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var reqDestroy : Boolean = ParserGetBoolValueByKeyByHandleDef(fxStruct, 'reqDestroy', false);
      [*] = ;            if (reqDestroy) then
      [*] = ;               ExecuteState('DoDestroy');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gc_RecycleFX then
      [*] = ;      begin
      [*] = ;         if (GetIntValueByIndex(gc_GOStack_fx_status)=1) then // 1 - run
      [*] = ;            SetIntValueByIndex(gc_GOStack_fx_status, 3); // 3 - finished
      [*] = ;         
      [*] = ;         var destroyStruct : Integer = ParserSelectByHandleByKey(nextNodeHandle, 'destroy');
      [*] = ;         if (destroyStruct<>0) and (ParserGetCountByHandle(destroyStruct)>0) then
      [*] = ;         SetDestroyStruct(goMyHnd, goParentHnd, goRootHnd, nodeTarget, destroyStruct);
      [*] = ;            
      [*] = ;         if bDestroy then
      [*] = ;            _obj_Recycle(goMyHnd);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      SetIntValueByIndex(gc_GOStack_fx_status, 4); // 4 - error
      [*] = ;      ErrorLog('DoNextNode nextNodeHandle = 0, nodeName: '+nextNodeName+', goHandle: '+IntToStr(GetGameObjectMyHandle));
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetIntValueByIndex(gc_GOStack_fx_status, 4); // 4 - error
      [*] = ;   if _log then ErrorLog('DoNextNode nextNodeName = null, goHandle: '+IntToStr(GetGameObjectMyHandle));
      [*] = ;end;
      [*] = ;
      [*] = ;if (GetIntValueByIndex(gc_GOStack_fx_status)=1) then // 1 - run
      [*] = ;begin
      [*] = ;   SetIntValueByIndex(gc_GOStack_fx_status, 3); // 3 - finished
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end

