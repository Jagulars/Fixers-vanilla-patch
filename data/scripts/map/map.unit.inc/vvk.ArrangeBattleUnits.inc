section.begin
   Name = vvk.ArrangeBattleUnits
   Description : struct.begin
      [*] = ;Fixes units positions in parser for tactical mode
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\VVK.ARRANGEBATTLEUNITS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = false;
      [*] = ;var pos : array[0..(gc_battle_GridSize*2)] of Integer;
      [*] = ;var i,j,unit,units,x,y : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;for i := 0 to (gc_battle_GridSize*2)-1 do
      [*] = ;   pos[i] := 0;
      [*] = ;
      [*] = ;units := ParserSelectByHandleByKey(ParserSelectGameObject(GetGameObjectMyHandle()),'Units');
      [*] = ;for i := 0 to ParserGetCountByHandle(units)-1 do
      [*] = ;begin
      [*] = ;   unit := ParserSelectByHandleByIndex(units,i);
      [*] = ;   x := ParserGetIntValueByKeyByHandle(unit,'BattleX');
      [*] = ;   y := ParserGetIntValueByKeyByHandle(unit,'BattleY');
      [*] = ;   if x > 1 then x := 1;
      [*] = ;   if y >= gc_battle_GridSize then y := gc_battle_GridSize - 1;
      [*] = ;   if pos[x*gc_battle_GridSize+y] <> 0 then
      [*] = ;   begin
      [*] = ;      for j := 0 to (gc_battle_GridSize*2)-1 do
      [*] = ;      begin
      [*] = ;         if pos[j] = 0 then
      [*] = ;            break;
      [*] = ;      end;
      [*] = ;      if j = gc_battle_GridSize*2 then j := 0;
      [*] = ;      y := j mod gc_battle_GridSize;
      [*] = ;      x := j div gc_battle_GridSize;
      [*] = ;   end;
      [*] = ;   pos[x*gc_battle_GridSize+y] := 1;
      [*] = ;   ParserSetIntValueByKeyByHandle(unit,'BattleX',x);
      [*] = ;   ParserSetIntValueByKeyByHandle(unit,'BattleY',y);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
