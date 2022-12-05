section.begin
   Name = OnAfterFullLoad
   Code : struct.begin
      [*] = ;if (gIntRegister_CurGameMode=gc_GameModeStrategy) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_MapSelectedUID<>0) then
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;      if (goHandle<>0) then
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'UpdateTrackNodes')
      [*] = ;      else
      [*] = ;         gIntRegister_MapSelectedUID := 0;
      [*] = ;   end;
      [*] = ;   gIntRegister_GUIDrawPathUID := gIntRegister_MapSelectedUID;
      [*] = ;   ExecuteState('map.DrawPath');
      [*] = ;end;
      [*] = ;
      [*] = ;MapExecuteState('ResizeCamera');
   struct.end
section.end

