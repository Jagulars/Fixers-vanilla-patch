section.begin
   Name = OnStartCyclesReached
   Code : struct.begin
      [*] = ;if GetIntValueByIndex(gc_GOStack_fx_status) <> 5 then
      [*] = ;begin
      [*] = ;   if (gIntRegister_fxTree_RootHandle=0) then
      [*] = ;      ExecuteState('DoLibLoad');
      [*] = ;   gStringRegister_fxTree_NodeName := GetValueByIndex(gc_GOStack_fx_nodeName);
      [*] = ;   ExecuteState('GetLibNodeByName');
      [*] = ;   var nodeHandle : Integer = gIntRegister_fxTree_NodeHandle;
      [*] = ;
      [*] = ;   if (nodeHandle<>0) then
      [*] = ;   begin
      [*] = ;      var animStruct : Integer = ParserSelectByHandleByKey(nodeHandle, 'animation');
      [*] = ;      if (animStruct<>0) then
      [*] = ;      begin
      [*] = ;         var cyclesAnimationStartReachedNode : String = ParserGetValueByKeyByHandle(animStruct, 'cyclesAnimationStartReachedNode');
      [*] = ;         if (cyclesAnimationStartReachedNode<>'') then
      [*] = ;         begin
      [*] = ;            SetValueByIndex(gc_GOStack_fx_nextNode, cyclesAnimationStartReachedNode);
      [*] = ;            ExecuteState('DoNextNode');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end
