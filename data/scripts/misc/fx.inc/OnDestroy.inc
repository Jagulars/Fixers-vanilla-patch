section.begin
   Name = OnDestroy
   UsedFileName = 
   Code : struct.begin
      [*] = ;if (gIntRegister_fxTree_RootHandle<>0) then
      [*] = ;begin
      [*] = ;   var destroyNode : String = GetValueByIndex(gc_GOStack_fx_destroyNode);
      [*] = ;   if (destroyNode<>'') then
      [*] = ;   begin
      [*] = ;      SetValueByIndex(gc_GOStack_fx_nextNode, destroyNode);
      [*] = ;      SetFloatValueByIndex(gc_GOStack_fx_sleepTime, 0);
      [*] = ;      ExecuteState('DoNextNode');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('DoClean');
      [*] = ;
      [*] = ;GameObjectMyCancelDelayExecuteState();
      [*] = ;
      [*] = ;{//ExecuteState('DoCleanSafe');
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;Log('FX OnDestroy '+IntToStr(myGOHandle));
      [*] = ;//Log('   OnDestroy GetGameObjectDelayExecuteStateNameByHandle '+GetGameObjectDelayExecuteStateNameByHandle(GetGameObjectMyHandle));
      [*] = ;//Log('   OnDestroy gc_GOStack_fx_nextNode '+GetValueByIndex(gc_GOStack_fx_nextNode));
      [*] = ;//GameObjectMyCancelDelayExecuteState();}
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end

