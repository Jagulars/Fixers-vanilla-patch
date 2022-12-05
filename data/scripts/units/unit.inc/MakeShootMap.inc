section.begin
   Name = MakeShootMap
   Description : struct.begin
      [*] = ;IntRegister0 - grid position X
      [*] = ;IntRegister1 - grid position Y
      [*] = ;IntRegister2 - shooting range
      [*] = ;shoot 2 means within range, shoot 1 means hex next to shooter - for healers only.
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var shootGridX : Integer = IntRegister0;
      [*] = ;var shootGridY : Integer = IntRegister1;
      [*] = ;var range : Integer = IntRegister2;
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;
      [*] = ;var ind : Integer = gc_battle_GridSize * shootGridY + shootGridX;
      [*] = ;var pShootHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;function CheckCell(x, y, dist : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if (x >= 0) and (x < gc_battle_GridSize) and (y >= 0) and (y < gc_battle_GridSize) then
      [*] = ;   begin
      [*] = ;      var ind : Integer = gc_battle_GridSize * y + x;
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;      var checked : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'Checked');
      [*] = ;      var land : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Land');
      [*] = ;
      [*] = ;      var tnHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;
      [*] = ;      if not checked then
      [*] = ;      begin
      [*] = ;         var shoot : Integer;
      [*] = ;         if dist = 0 then
      [*] = ;         shoot := 1
      [*] = ;         else
      [*] = ;         shoot := 2;
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'Land', dist+1);
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'Shoot', shoot);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pHexCell, 'Checked', true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckNeighbours(x, y, dist : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var ind : Integer = gc_battle_GridSize * y + x;
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;   var checked : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'Checked');
      [*] = ;   var land : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Land');
      [*] = ;
      [*] = ;   var f : Boolean = false;
      [*] = ;   if checked and (land = dist) then
      [*] = ;   begin
      [*] = ;      CheckCell(x - 1 + y mod 2, y-1, dist);
      [*] = ;      CheckCell(x + y mod 2, y-1, dist);
      [*] = ;      CheckCell(x - 1 + y mod 2, y+1, dist);
      [*] = ;      CheckCell(x + y mod 2, y+1, dist);
      [*] = ;      CheckCell(x - 1, y, dist);
      [*] = ;      CheckCell(x + 1, y, dist);
      [*] = ;
      [*] = ;      Result := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;ExecuteState('ClearShootMap');
      [*] = ;
      [*] = ;if gBoolRegister_BattleSimulate then
      [*] = ;begin
      [*] = ;   IntRegister0 := shootGridX;
      [*] = ;   IntRegister1 := shootGridY;
      [*] = ;   IntRegister2 := range;
      [*] = ;   ExecuteState('MakeSimShootMap');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if GetBoolValueByIndex(gc_stack_unit_bCanShoot) then
      [*] = ;   begin
      [*] = ;      for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pHexCell, 'Checked', false);
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'Land', 0);
      [*] = ;      end;
      [*] = ;      
      [*] = ;      var f : Boolean = true;
      [*] = ;      var dist : Integer = 0;
      [*] = ;      ParserSetBoolValueByKeyByHandle(pShootHexCell, 'Checked', true);
      [*] = ;      
      [*] = ;      while f and (dist < range) do
      [*] = ;      begin
      [*] = ;         f := false;
      [*] = ;         
      [*] = ;         for i := 0 to gc_battle_GridSize-1 do
      [*] = ;         for j := 0 to gc_battle_GridSize-1 do
      [*] = ;         begin
      [*] = ;            f := CheckNeighbours(i, j, dist) or f;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         dist := dist + 1;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      ParserSetIntValueByKeyByHandle(pShootHexCell, 'Shoot', 2);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

