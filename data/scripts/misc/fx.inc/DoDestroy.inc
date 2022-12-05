section.begin
   Name = DoDestroy
   UsedFileName = 
   Code : struct.begin
      [*] = ;//Log('fx DoDestroy');
      [*] = ;ExecuteState('DoCleanSafe');
      [*] = ;
      [*] = ;var ownerHnd : Integer = GetGameObjectMyHandle;
      [*] = ;AddObjectToDestroyList(ownerHnd);
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end
