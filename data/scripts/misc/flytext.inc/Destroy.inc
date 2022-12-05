section.begin
   Name = Destroy
   Code : struct.begin
      [*] = ;var myHnd : Integer = GetGameObjectMyHandle();
      [*] = ;
      [*] = ;if gc_RecycleFlyTexts then
      [*] = ;   _obj_Recycle(myHnd)
      [*] = ;else
      [*] = ;begin
      [*] = ;   var hudCollection : Integer = _gui_GetLayer(cHUDTacticsTextLayer);
      [*] = ;   if (hudCollection<>0) then
      [*] = ;   begin
      [*] = ;      var hudHandle : Integer = GetGUIGroupHUDCollectionItemByGameObject(hudCollection, myHnd);
      [*] = ;      if (hudHandle<>0) then
      [*] = ;         GUIGroupHUDCollectionDeleteGameObject(hudCollection, myHnd);
      [*] = ;   end;
      [*] = ;   BehaviourClear(myHnd);
      [*] = ;   GameObjectRequestToDestroyByHandle(myHnd);
      [*] = ;end;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
