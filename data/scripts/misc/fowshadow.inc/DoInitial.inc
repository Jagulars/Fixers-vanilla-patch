section.begin
   Name = DoInitial
   Description[*] = 
   UsedFileName = 
   Code : struct.begin
      [*] = ;var goMyHnd : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;SetGameObjectUseNoSPCullByHandle(goMyHnd, true);
      [*] = ;
      [*] = ;ClearVariables;
      [*] = ;
      [*] = ;// setup stack
      [*] = ;var initial : Integer = 1;  // default 0 just before initial, 1 initialized
      [*] = ;
      [*] = ;// stack indices
      [*] = ;// [0 gc_GOStack_fowshadow_init] - initialized [0..1] : (0 is empty, 1 is initialized)
      [*] = ;SetIntValueByName('init', initial);
      [*] = ;
      [*] = ;//if (GetGameObjectUniqueIdByHandle(goMyHnd)<=0) then
      [*] = ;//GameObjectMakeUniqId(goMyHnd);
      [*] = ;//SetGameObjectMyStateTargetPosition(GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;//SetGameObjectSTOHandleByHandle(goMyHnd, 0);
      [*] = ;//SetGameObjectMyPlayableObject(False);
      [*] = ;//SetGameObjectOnStateDestroyByHandle(goMyHnd, 'OnDestroy');
      [*] = ;
      [*] = ;SetGameObjectCustomNameByHandle(goMyHnd, GetGameObjectMyBaseName);
      [*] = ;
      [*] = ;ExecuteState('OnCreate');
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end
