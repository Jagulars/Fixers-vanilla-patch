section.begin
   Name = OnDestroy
   UsedFileName = 
   Code : struct.begin
      [*] = ;//_Log_obj('unit OnDestroy '+GetGameObjectMyBaseName);
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;var remainsUID : Integer = GetIntValueByIndex(gc_stack_unit_iRemainsUID);
      [*] = ;var remainsHnd : Integer = GetGameObjectHandleByUniqueId(remainsUID);
      [*] = ;if (remainsHnd<>0) then
      [*] = ;begin
      [*] = ;   if gc_RecycleBattleField then
      [*] = ;      _obj_Recycle(remainsHnd)
      [*] = ;   else
      [*] = ;      AddObjectToDestroyList(remainsHnd);
      [*] = ;end;
      [*] = ;SetIntValueByIndex(gc_stack_unit_iRemainsUID, 0);
      [*] = ;
      [*] = ;var gridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;var gridY : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;
      [*] = ;var hexUID : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;if hexUID = myUID then
      [*] = ;ParserSetIntValueByKeyByHandle(pHexCell, 'UID', 0);
      [*] = ;
      [*] = ;_fx_ShowEnvironmentAroundTacticalDeadUnit(myGOHandle);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
