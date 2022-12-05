section.begin
   Name = Initial
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;if (not GetGameObjectMyVisible) and (not gBoolRegister_Loading) then
      [*] = ;   ReloadGameObjectProperties(myGOHandle, GetGameObjectRaceNameByHandle(myGOHandle), GetGameObjectMyBaseName);
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end
