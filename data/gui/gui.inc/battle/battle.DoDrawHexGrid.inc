section.begin
   Name = battle.DoDrawHexGrid
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.DODRAWHEXGRID';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;const cPlacementModeInHexA = 0.0125;
      [*] = ;const cScaleDataViewer = 4.0;
      [*] = ;
      [*] = ;const cInHexReachR = 1;
      [*] = ;const cInHexReachG = 1;
      [*] = ;const cInHexReachB = 0;
      [*] = ;const cInHexReachA = 0.5;
      [*] = ;const cOutHexReachR = 1;
      [*] = ;const cOutHexReachG = 1;
      [*] = ;const cOutHexReachB = 0;
      [*] = ;const cOutHexReachA = 0;
      [*] = ;const cHexReachSize = 0.1;
      [*] = ;
      [*] = ;const cInSelectedHexR = 1;
      [*] = ;const cInSelectedHexG = 1;
      [*] = ;const cInSelectedHexB = 0.4;
      [*] = ;const cInSelectedHexA = 0.5; //0.15
      [*] = ;const cOutSelectedHexR = 1;
      [*] = ;const cOutSelectedHexG = 1;
      [*] = ;const cOutSelectedHexB = 0.4;
      [*] = ;const cOutSelectedHexA = 0;
      [*] = ;const cSelectedHexSize = 0.125; //0.3
      [*] = ;
      [*] = ;const cStartHexDraw = false;
      [*] = ;const cEndHexDraw = false;
      [*] = ;const cDistEpsilon = 0.01;
      [*] = ;
      [*] = ;procedure UpdateGroupByHandle(group_handle, obj_handle : Integer; matName : String);
      [*] = ;begin
      [*] = ;   GroupClearGameObjectsByHandle(group_handle);
      [*] = ;   if obj_handle <> 0 then
      [*] = ;      GroupAddGameObjectByHandle(group_handle, obj_handle);
      [*] = ;   GUISetGroupDataViewerMatName(matName);
      [*] = ;   GUISetGroupDataViewerSize(cScaleDataViewer);
      [*] = ;   GUISetGroupDataViewerBlinked(False);
      [*] = ;   GUISetGroupDataViewerFade(False);
      [*] = ;   GUIAddGroupDataViewer(group_handle);
      [*] = ;   // update hover unit brush finish
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DrawHexByTrackNodeHandle(DVZone, tnHandle : Integer; hexSize : Float; doInside : Boolean);
      [*] = ;begin
      [*] = ;   var x, y, z : Float;
      [*] = ;   var i : Integer;
      [*] = ;   GetTrackNodePositionByHandle(tnHandle, x, y, z);
      [*] = ;
      [*] = ;   if (doInside) then
      [*] = ;   begin
      [*] = ;      for i := 0 to 5 do
      [*] = ;      begin
      [*] = ;         var angle : Float = 30 + i*60;
      [*] = ;         var dirX : Float = gc_HexSize*(1); //gc_HexSize*0.99;
      [*] = ;         var dirY : Float = 0;
      [*] = ;         var dirZ : Float = 0;
      [*] = ;         VectorRotateY(dirX, dirY, dirZ, angle);
      [*] = ;
      [*] = ;         var dirX1 : Float = dirX;
      [*] = ;         var dirY1 : Float = dirY;
      [*] = ;         var dirZ1 : Float = dirZ;
      [*] = ;         var offset : Float = 0;
      [*] = ;         VectorRotateY(dirX1, dirY1, dirZ1, 60 + offset);
      [*] = ;         //DebugDrawLine('Grid', x + dirX, 0.1, z + dirZ, x + dirX1, 0.1, z + dirZ1, 0, 1, 0);
      [*] = ;         GUIDataViewerZonePointListAdd(DVZone, x + dirX, 0.1, z + dirZ);
      [*] = ;         GUIDataViewerZonePointListAdd(DVZone, x + dirX1, 0.1, z + dirZ1);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      for i := 0 to 5 do
      [*] = ;      begin
      [*] = ;         var angle : Float = -30 - i*60;
      [*] = ;         var dirX : Float = gc_HexSize*(1); //gc_HexSize*0.99;
      [*] = ;         var dirY : Float = 0;
      [*] = ;         var dirZ : Float = 0;
      [*] = ;         VectorRotateY(dirX, dirY, dirZ, angle);
      [*] = ;
      [*] = ;         var dirX1 : Float = dirX;
      [*] = ;         var dirY1 : Float = dirY;
      [*] = ;         var dirZ1 : Float = dirZ;
      [*] = ;         var offset : Float = 0;
      [*] = ;         VectorRotateY(dirX1, dirY1, dirZ1, 60 + offset);
      [*] = ;         //DebugDrawLine('Grid', x + dirX, 0.1, z + dirZ, x + dirX1, 0.1, z + dirZ1, 0, 1, 0);
      [*] = ;         GUIDataViewerZonePointListAdd(DVZone, x + dirX1, 0.1, z + dirZ1);
      [*] = ;         GUIDataViewerZonePointListAdd(DVZone, x + dirX, 0.1, z + dirZ);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var i,j,h : Integer;
      [*] = ;var matName : String;
      [*] = ;
      [*] = ;GUIExecuteState('InitViewerZones');
      [*] = ;
      [*] = ;for i := GUIGetDataViewerZoneCount()-1 downto 4 do
      [*] = ;   GUIDeleteDataViewerZone(i);
      [*] = ;GUIFullClearGroupDataViewer(); // clear brush
      [*] = ;var myPlHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;// update base unit brush start
      [*] = ;for j := 0 to 1 do
      [*] = ;begin
      [*] = ;   if (gProfile.brushunderunit) then
      [*] = ;   begin
      [*] = ;      if j=0 then
      [*] = ;         matName := 'highlight.friend'
      [*] = ;      else
      [*] = ;         matName := 'highlight.enemy';
      [*] = ;   end
      [*] = ;   else
      [*] = ;      matName := '';
      [*] = ;   if j=0 then h := myPlHandle
      [*] = ;   else h := enPlHandle;
      [*] = ;
      [*] = ;   GUISetGroupDataViewerMatName(matName);
      [*] = ;   GUISetGroupDataViewerSize(cScaleDataViewer);
      [*] = ;   GUISetGroupDataViewerBlinked(False);
      [*] = ;   GUISetGroupDataViewerFade(False);
      [*] = ;   PlayerExecuteStateByHandle(h, 'RefreshGlobalGroup');
      [*] = ;   PlayerExecuteStateByHandle(h, 'GetGlobalGroupHandle');
      [*] = ;   GUIAddGroupDataViewer( IntRegister0 );
      [*] = ;end;
      [*] = ;
      [*] = ;type THex = class
      [*] = ;   isReach, isReachTarget, isShootTarget, isShootRange : Boolean = False;
      [*] = ;end;
      [*] = ;
      [*] = ;const gridSize = gc_battle_GridSize*gc_battle_GridSize;
      [*] = ;var hexGridArray : array[0..gridSize] of THex;
      [*] = ;
      [*] = ;// hovered unit
      [*] = ;var hoverUID : Integer = gIntRegister_EndHexUID;
      [*] = ;var hoverGoHandle : Integer = 0;
      [*] = ;var hoverIsEnemy : Boolean = False;
      [*] = ;
      [*] = ;if (hoverUID<>0) and (hoverUID<>gIntRegister_SelectedUID) then
      [*] = ;begin
      [*] = ;   hoverGoHandle := GetGameObjectHandleByUniqueId(hoverUID);
      [*] = ;   if GetGameObjectVisibleByHandle(hoverGOHandle) then
      [*] = ;   begin
      [*] = ;      var hoverPlHandle : Integer = GetGameObjectPlayerHandleByHandle(hoverGoHandle);
      [*] = ;      hoverIsEnemy := (myPlHandle<>hoverPlHandle);
      [*] = ;
      [*] = ;      var hoverMovePoints : Integer = GetGameObjectIntValueIndByHandle(hoverGOHandle, gc_stack_unit_iMovePoints);
      [*] = ;      var hoverSpeed : Integer = _unit_GetProperty(hoverGOHandle, gc_battle_unit_iSpeed);
      [*] = ;      if hoverIsEnemy then
      [*] = ;      begin
      [*] = ;         SetGameObjectIntValueIndByHandle(hoverGOHandle, gc_stack_unit_iMovePoints, hoverSpeed);
      [*] = ;         GameObjectExecuteStateByHandle(hoverGoHandle, 'Select');
      [*] = ;         SetGameObjectIntValueIndByHandle(hoverGOHandle, gc_stack_unit_iMovePoints, hoverMovePoints);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         GameObjectExecuteStateByHandle(hoverGoHandle, 'Select');
      [*] = ;
      [*] = ;      var abil36 : Integer = _unit_CheckAbility(hoverGOHandle, gc_ability_immobilized);
      [*] = ;      var abil88 : Integer = _unit_CheckAbility(hoverGOHandle, gc_ability_cantmove);
      [*] = ;      var movable : Boolean = (abil36 = 0) and (abil88 = 0) and (hoverIsEnemy or (hoverMovePoints > 0));
      [*] = ;
      [*] = ;      // update hover unit brush start
      [*] = ;      if (not hoverIsEnemy) then
      [*] = ;         matName := 'highlight.friend.hover'
      [*] = ;      else
      [*] = ;         matName := 'highlight.enemy.hover';
      [*] = ;      PlayerExecuteStateByHandle(hoverPlHandle, 'GetMouseGroupHandle');
      [*] = ;      UpdateGroupByHandle( IntRegister0,hoverGoHandle,matName);
      [*] = ;
      [*] = ;      var hoverGridX : Integer = GetGameObjectIntValueIndByHandle(hoverGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;      var hoverGridY : Integer = GetGameObjectIntValueIndByHandle(hoverGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;      var hoverInd : Integer = gc_battle_GridSize * hoverGridY + hoverGridX;
      [*] = ;      var hoverTnHandle : Integer = GetTrackNodeHandleByIndex(hoverInd);
      [*] = ;
      [*] = ;      for i := 0 to GetTrackNodeCount()-1 do
      [*] = ;      begin
      [*] = ;         var x, y, z : Float;
      [*] = ;         var tnHandle : Integer = GetTrackNodeHandleByIndex(i);
      [*] = ;         var tnEnabled : Boolean = GetTrackNodeEnabledByHandle(tnHandle);
      [*] = ;         GetTrackNodePositionByIndex(i, x, y, z);
      [*] = ;
      [*] = ;         var pHexHandle : Integer = ParserSelectByHandleByIndex(gHexCells.handle, i);
      [*] = ;         var hexUID : Integer = ParserGetIntValueByKeyByHandle(pHexHandle, 'UID');
      [*] = ;
      [*] = ;         if (tnHandle<>hoverTnHandle) then
      [*] = ;         begin
      [*] = ;            var endPointValid : Boolean;
      [*] = ;            var goEnemyUID : Integer = 0;
      [*] = ;
      [*] = ;            if movable then
      [*] = ;            begin
      [*] = ;               if hexUID <> 0 then
      [*] = ;                  _unit_IsValidEndPoint(hoverGoHandle, tnHandle, true, hoverIsEnemy, endPointValid, goEnemyUID)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, i);
      [*] = ;                  var land : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Land');
      [*] = ;                  var isNeighbour : Boolean = GetTrackNodesConnectedByHandle(tnHandle, hoverTnHandle);
      [*] = ;                  endPointValid := (isNeighbour and tnEnabled) or ((land > 0) and (land <= hoverSpeed));
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               endPointValid := false;
      [*] = ;
      [*] = ;            if (endPointValid) then
      [*] = ;            begin
      [*] = ;               if (goEnemyUID<>0) then
      [*] = ;                  hexGridArray[i].isReachTarget := True
      [*] = ;               else
      [*] = ;                  hexGridArray[i].isReach := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//var stX, stY, stZ : Float;
      [*] = ;//var dist : Float;
      [*] = ;var selGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;var selMovePoints : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iMovePoints);
      [*] = ;var selSpeed : Integer = _unit_GetProperty(selGOHandle, gc_battle_unit_iSpeed);
      [*] = ;var selTnHandle : Integer = 0;
      [*] = ;
      [*] = ;var aMode : Integer = GetPlayerIntValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_battle_PLStack_iAttackMode);
      [*] = ;
      [*] = ;if (selGOHandle<>0) then
      [*] = ;begin
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'GetSelectedGroupHandle');
      [*] = ;   UpdateGroupByHandle( IntRegister0,selGOHandle,'selection.friend');
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(selGOHandle, 'Select');
      [*] = ;
      [*] = ;   //GetTrackNodePositionByHandle(gIntRegister_StartTrackNode, stX, stY, stZ);
      [*] = ;   //dist := GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iMovePoints);
      [*] = ;   //dist := dist + 1;
      [*] = ;   //if dist = 0 then
      [*] = ;   //   dist := 1;
      [*] = ;
      [*] = ;   //dist := dist * Sqrt(3) * gc_HexSize;
      [*] = ;
      [*] = ;   var selGridX : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;   var selGridY : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;   var selInd : Integer = gc_battle_GridSize * selGridY + selGridX;
      [*] = ;   selTnHandle := GetTrackNodeHandleByIndex(selInd);
      [*] = ;end;
      [*] = ;
      [*] = ;var s_radius,s_target : Integer;
      [*] = ;var x_end,y_end,hex_size : Float;
      [*] = ;
      [*] = ;if (gIntRegister_CurSpell>0) then
      [*] = ;begin
      [*] = ;   var pSpell : Integer = ParserSelectByHandleByIndex(gPrototypeData.spells.handle, gIntRegister_CurSpell);
      [*] = ;   s_target := ParserGetIntValueByKeyByHandle(pSpell, 'Target');
      [*] = ;   s_radius := ParserGetIntValueByKeyByHandle(pSpell, 'Radius');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   s_radius := 0;
      [*] = ;   s_target := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if gIntRegister_EndHexCell <> 0 then
      [*] = ;begin
      [*] = ;   x_end := ParserGetFloatValueByKeyByHandle(gIntRegister_EndHexCell, 'CenterX');
      [*] = ;   y_end := ParserGetFloatValueByKeyByHandle(gIntRegister_EndHexCell, 'CenterY');
      [*] = ;   hex_size := gc_HexSize * Sqrt(3);
      [*] = ;end
      [*] = ;else
      [*] = ;   hex_size := 0;
      [*] = ;
      [*] = ;
      [*] = ;const decalPrefix = 'battlehex_';
      [*] = ;var prefixLen : Integer = StrLength(decalPrefix);
      [*] = ;var decalHandle : Integer;
      [*] = ;for i := DecalManagerGetDecalCount-1 downto 0 do
      [*] = ;begin
      [*] = ;   decalHandle := DecalManagerGetDecalHandleByIndex(i);
      [*] = ;   if SameText(SubStr(GetDecalNameByHandle(decalHandle), 0, prefixLen), decalPrefix) then
      [*] = ;      SetDecalVisibleByHandle(decalHandle, false);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure PlaceHexDecal(x, z : Float; name : String);
      [*] = ;begin
      [*] = ;   var i, decalHandle : Integer;
      [*] = ;   {var decalCount : Integer = DecalManagerGetDecalCount;
      [*] = ;   var decalX, decalZ : Float;
      [*] = ;   var bOldFound : Boolean = false;
      [*] = ;   
      [*] = ;   // check if there already exists a decal of same on the same spot.
      [*] = ;   for i := 0 to decalCount-1 do
      [*] = ;   begin
      [*] = ;      decalHandle := DecalManagerGetDecalHandleByIndex(i);
      [*] = ;      GetDecalPositionByHandle(decalHandle, decalX, decalZ);
      [*] = ;      
      [*] = ;      if (decalX > x-0.001) and (decalX < x+0.001) and (decalZ > z-0.001) and (decalZ < z+0.001) then
      [*] = ;      begin
      [*] = ;         if SameText(GetDecalNameByHandle(decalHandle), name) then
      [*] = ;         begin
      [*] = ;            Log('useold samepos ');
      [*] = ;            SetDecalVisibleByHandle(decalHandle, true);
      [*] = ;            bOldFound := true;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            SetDecalVisibleByHandle(decalHandle, false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if bOldFound then
      [*] = ;      exit;}
      [*] = ;   
      [*] = ;   for i := DecalManagerGetDecalCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      decalHandle := DecalManagerGetDecalHandleByIndex(i);
      [*] = ;   
      [*] = ;      if (not GetDecalVisibleByHandle(decalHandle)) and SameText(GetDecalNameByHandle(decalHandle), decalPrefix+name) then
      [*] = ;      begin
      [*] = ;         SetDecalVisibleByHandle(decalHandle, true);
      [*] = ;         SetDecalPositionByHandle(decalHandle, x, z);
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   decalHandle := PutDecalByName(x, z, name);
      [*] = ;   SetDecalNameByHandle(decalHandle, decalPrefix+name);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;for i := 0 to GetTrackNodeCount()-1 do
      [*] = ;begin
      [*] = ;   var x, y, z : Float;
      [*] = ;   var tnHandle : Integer = GetTrackNodeHandleByIndex(i);
      [*] = ;   var tnEnabled : Boolean = GetTrackNodeEnabledByHandle(tnHandle);
      [*] = ;
      [*] = ;   GetTrackNodePositionByIndex(i, x, y, z);
      [*] = ;
      [*] = ;   var isReach : Boolean = false;
      [*] = ;   var isReachTarget : Boolean = false;
      [*] = ;   var isShootTarget : Boolean = false;
      [*] = ;   var isShootRange : Boolean = false;
      [*] = ;
      [*] = ;   var isPlacement : Boolean = false;
      [*] = ;   var isSelected : Boolean = false;
      [*] = ;   var isEnd : Boolean = false;
      [*] = ;   var isCanAct : Boolean = false;
      [*] = ;
      [*] = ;   // hex unit handle
      [*] = ;   var pHexHandle : Integer = ParserSelectByHandleByIndex(gHexCells.handle, i);
      [*] = ;   var hexUID : Integer = ParserGetIntValueByKeyByHandle(pHexHandle, 'UID');
      [*] = ;   var hexGoHandle : Integer = 0;
      [*] = ;   if (hexUID<>0) then
      [*] = ;      hexGoHandle := GetGameObjectHandleByUniqueId(hexUID);
      [*] = ;
      [*] = ;   if (tnHandle = gIntRegister_EndTrackNode) then
      [*] = ;      isEnd := True;
      [*] = ;
      [*] = ;   if (selGOHandle<>0) and (hexGoHandle<>0) then
      [*] = ;   begin
      [*] = ;      _unit_IsMyShootEndPoint(selGOHandle, tnHandle, gBoolRegister_BattlePlaceMode, isShootTarget, isShootRange);
      [*] = ;      isCanAct := GetGameObjectBoolValueIndByHandle(selGOHandle, gc_stack_unit_bCanAct);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var isSpellTarget : Boolean = false;
      [*] = ;   var healTarget : Integer = 0; // 0 - если юнит не €вл€етс€ целью дл€ лечени€, 1 - если €вл€етс€, но недостижим, 2 - если €вл€етс€ и достижим
      [*] = ;   if (gBoolRegister_BattlePlaceMode) then
      [*] = ;   begin
      [*] = ;      if (((i mod gc_battle_GridSize)>1) and (aMode = 1)) or (((i mod gc_battle_GridSize)<6) and (aMode = 0)) then
      [*] = ;         isPlacement := True
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if selGOHandle <> 0 then
      [*] = ;            isReach := true;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (selGOHandle<>0) then
      [*] = ;   begin
      [*] = ;      if (tnHandle=selTnHandle) then
      [*] = ;         isSelected := True
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (gIntRegister_CurSpell>0) and (hex_size > 0) then
      [*] = ;         begin
      [*] = ;            if (s_target=3) then
      [*] = ;            begin
      [*] = ;               var x : Float = ParserGetFloatValueByKeyByHandle(pHexHandle, 'CenterX');
      [*] = ;               var y : Float = ParserGetFloatValueByKeyByHandle(pHexHandle, 'CenterY');
      [*] = ;               var dist : Float = Round(VectorDistance(x, 0, y, x_end, 0, y_end) / hex_size);
      [*] = ;
      [*] = ;               if (dist<=s_radius) then
      [*] = ;                  isSpellTarget := True;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := gIntRegister_CurSpell;
      [*] = ;               IntRegister1 := pHexHandle;
      [*] = ;               GameObjectExecuteStateByHandle(selGOHandle, 'CanCastSpell');
      [*] = ;               isSpellTarget := BoolRegister0;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var actAbility : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iActiveAbility);
      [*] = ;         if (hexGoHandle<>0) and ((actAbility = gc_ability_healing) or (actAbility = gc_ability_repair)) then
      [*] = ;         begin
      [*] = ;            if actAbility = gc_ability_healing then
      [*] = ;               IntRegister0 := 0
      [*] = ;            else
      [*] = ;               IntRegister0 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(hexGoHandle, 'IsHealTarget');
      [*] = ;            healTarget := IntRegister1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var endPointValid : Boolean;
      [*] = ;         var goEnemyUID : Integer = 0;
      [*] = ;
      [*] = ;         if hexUID <> 0 then
      [*] = ;            _unit_IsValidEndPoint(selGOHandle, tnHandle, true, false, endPointValid, goEnemyUID)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var land : Integer = ParserGetIntValueByKeyByHandle(pHexHandle, 'Land');
      [*] = ;            var isNeighbour : Boolean = GetTrackNodesConnectedByHandle(tnHandle, selTNHandle);
      [*] = ;            endPointValid := (isNeighbour  and tnEnabled and (selMovePoints >= selSpeed)) or ((land > 0) and (land <= selMovePoints));
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (endPointValid) then
      [*] = ;         begin
      [*] = ;            if (goEnemyUID = 0) then
      [*] = ;               isReach := True
      [*] = ;            else
      [*] = ;               isReachTarget := True;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // 1 - hexnormal (edge) : normal default hex - прозрачный белый
      [*] = ;   // 2 - hexend (edge) : isEnd, no sel, no hover - светло серый
      [*] = ;   // 3 - hexendfriend (edge) : isEnd, no sel, hover, not isEnemy - легка€ желта€ обводка, можно выбрать
      [*] = ;   // 4 - hexendreach (full) : isEnd, sel, no hover, reach - желтый достижимый подкурсорный
      [*] = ;
      [*] = ;   // 5 - hexplacement (edge) : isPlacement - почти не видимый белый
      [*] = ;   // 6 - hexhoverreach (full) : no sel, hover, reach2 - слабо зеленый
      [*] = ;   // 7 - hexattack (full) : attack - €рко красный
      [*] = ;
      [*] = ;   // 8 - hexselected (edge) : isSelected - €рко желтый
      [*] = ;   // 9 - hexreach (full) : isReach - зеленый
      [*] = ;
      [*] = ;   // 10 - hexdoublereach (full) : isReach1, isReach2 //темно зеленый
      [*] = ;   // 11 - hexspellfriend (full) : isSpellTarget or healTarget=2 is friend
      [*] = ;   // 12 - hexspellenemy (full) : isSpellTarget or healTarget=2 is enemy
      [*] = ;
      [*] = ;   var hexStyle : Integer = 0;
      [*] = ;   if (isSelected) then
      [*] = ;      hexStyle := 8
      [*] = ;   else
      [*] = ;   if (isPlacement) then
      [*] = ;      hexStyle := 5
      [*] = ;   else
      [*] = ;   if (gIntRegister_CurSpell>0) or ((healTarget=2) and (GetGameObjectPlayerHandleByHandle(hexGoHandle)=myPlHandle)) then
      [*] = ;   begin
      [*] = ;      if (isSpellTarget) or (healTarget=2) then
      [*] = ;      begin
      [*] = ;         if (GetGameObjectPlayerHandleByHandle(hexGoHandle)=myPlHandle) then // friend
      [*] = ;            hexStyle := 11
      [*] = ;         else
      [*] = ;            hexStyle := 12;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (isEnd) then
      [*] = ;   begin
      [*] = ;      if (selGoHandle=0) then
      [*] = ;      begin
      [*] = ;         if (hoverGoHandle=0) then
      [*] = ;            hexStyle := 1
      [*] = ;         else
      [*] = ;         if (not hoverIsEnemy) then
      [*] = ;            hexStyle := 3
      [*] = ;         else
      [*] = ;            hexStyle := 1
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (hoverGoHandle=0) then
      [*] = ;         begin
      [*] = ;            if (isReach) then
      [*] = ;               hexStyle := 4
      [*] = ;            else
      [*] = ;               hexStyle := 1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (isReachTarget) or (isShootTarget) then
      [*] = ;            hexStyle := 7
      [*] = ;         else
      [*] = ;         if (not hoverIsEnemy) then
      [*] = ;            hexStyle := 3
      [*] = ;         else
      [*] = ;            hexStyle := 1;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (selGoHandle=0) then
      [*] = ;   begin
      [*] = ;      if (hoverGoHandle=0) then
      [*] = ;         hexStyle := 1
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (not gBoolRegister_BattlePlaceMode) and ((isReach) or (hexGridArray[i].isReach)) then
      [*] = ;            hexStyle := 6
      [*] = ;         else
      [*] = ;            hexStyle := 1;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (gBoolRegister_BattlePlaceMode) or (hoverGoHandle=0) or (hoverGoHandle=selGoHandle) then
      [*] = ;      begin
      [*] = ;         if ((isReachTarget) or (isShootTarget)) and (isCanAct) then
      [*] = ;            hexStyle := 7
      [*] = ;         else
      [*] = ;         if (isReach) then
      [*] = ;            hexStyle := 9
      [*] = ;         else
      [*] = ;            hexStyle := 1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ((isReachTarget) or (isShootTarget)) and (isCanAct) then
      [*] = ;            hexStyle := 7
      [*] = ;         else
      [*] = ;         if (isReach) then
      [*] = ;         begin
      [*] = ;            if (not hexGridArray[i].isReach) then
      [*] = ;               hexStyle := 9
      [*] = ;            else
      [*] = ;               hexStyle := 10
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (hexGridArray[i].isReach) then
      [*] = ;            hexStyle := 6
      [*] = ;         else
      [*] = ;            hexStyle := 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var decalBaseName : String;
      [*] = ;   case hexStyle of
      [*] = ;      1 : decalBaseName := 'hexnormal';
      [*] = ;      2 : decalBaseName := 'hexend';
      [*] = ;      3 : decalBaseName := 'hexendfriend';
      [*] = ;      4 : decalBaseName := 'hexendreach';
      [*] = ;      5 : decalBaseName := 'hexplacement';
      [*] = ;      6 : decalBaseName := 'hexhoverreach';
      [*] = ;      7 : decalBaseName := 'hexattack';
      [*] = ;      8 : decalBaseName := 'hexselected';
      [*] = ;      9 : decalBaseName := 'hexreach';
      [*] = ;      10 : decalBaseName := 'hexdoublereach';
      [*] = ;      11 : decalBaseName := 'hexspellfriend';
      [*] = ;      12 : decalBaseName := 'hexspellenemy';
      [*] = ;   end;
      [*] = ;   // not yet used hexendenemy, hexdoublereachedge
      [*] = ;
      [*] = ;   if (isEnd) and (hexStyle<>8) and (not isPlacement) and (hexStyle<>1) then
      [*] = ;   begin
      [*] = ;      if (hexStyle=11) then
      [*] = ;         PlaceHexDecal(x, z, 'hexendspellfriend')
      [*] = ;      else
      [*] = ;      if (GetGameObjectPlayerHandleByHandle(hexGoHandle)=myPlHandle) then
      [*] = ;         PlaceHexDecal(x, z, 'hexendfriend')
      [*] = ;      else
      [*] = ;      if (hexStyle=7) or (hexStyle=12) then
      [*] = ;         PlaceHexDecal(x, z, 'hexattackedge')
      [*] = ;      else
      [*] = ;         PlaceHexDecal(x, z, 'hexend');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (hexStyle=8) then
      [*] = ;      PlaceHexDecal(z, x, 'hexend');
      [*] = ;
      [*] = ;   //if (not isPlacement) then
      [*] = ;   //begin
      [*] = ;   //   if (gProfile.wargrid) then
      [*] = ;   //      PlaceHexDecal(z, x, 'hexnormal');
      [*] = ;   //end;
      [*] = ;
      [*] = ;   if (not gProfile.wargrid) then
      [*] = ;   begin
      [*] = ;      if ((hexStyle<>1) and (hexStyle<>9) and (hexStyle<>6) and (hexStyle<>5) and (hexStyle<>10) and (hexStyle<13)) or
      [*] = ;      ((gBoolRegister_BattlePlaceMode) and (hexStyle=1)) or
      [*] = ;      ((gBoolRegister_BattlePlaceMode) and (hexStyle=9)) then
      [*] = ;         PlaceHexDecal(z, x, decalBaseName);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (hexStyle>0) and (hexStyle<13) then
      [*] = ;      PlaceHexDecal(x, z, decalBaseName);
      [*] = ;
      [*] = ;   if (gProfile.wargrid) then
      [*] = ;   begin
      [*] = ;      if (hexStyle=6) then
      [*] = ;         PlaceHexDecal(x, z, 'hexhoverreachedge');
      [*] = ;
      [*] = ;      if (hexStyle=9) or (hexStyle=10) then
      [*] = ;         PlaceHexDecal(x, z, 'hexhoverreachedge');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gBoolRegister_BattlePlaceMode) then
      [*] = ;   begin
      [*] = ;      if (hexStyle=6) then
      [*] = ;         PlaceHexDecal(x, z, 'hexhoverreachedge');
      [*] = ;
      [*] = ;      if (hexStyle=9) or (hexStyle=10) then
      [*] = ;         PlaceHexDecal(x, z, 'hexhoverreachedge');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;if (not gBoolRegister_BattlePlaceMode) then
      [*] = ;   GUIExecuteState('battle.DrawPath');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

