section.begin
   Name = map.GetNeighbourHexByIndex
   Description : struct.begin
      [*] = ;IntRegister0 - province parser
      [*] = ;IntRegister1 - neighbour index
      [*] = ;OUT: IntRegister2 - neigbour province parser
      [*] = ;     IntRegister3 - neigbour province index
   struct.end
   Code : struct.begin
      [*] = ;var ind : Integer = IntRegister1;
      [*] = ;var pProvNeighbours : Integer = ParserSelectByHandleByKey( IntRegister0 , 'Neighbours');
      [*] = ;var nInd : Integer;
      [*] = ;//var _log_name : String = 'COMMON.INC\MAP\MAP.GETNEIGHBOURHEXBYINDEX';
      [*] = ;//var _log_trace : Integer = $20000;
      [*] = ;//_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if ind < ParserGetCountByHandle(pProvNeighbours) then
      [*] = ;begin
      [*] = ;   nInd := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pProvNeighbours, ind), 'Index');
      [*] = ;   ind := ParserSelectByHandleByIndex(gStratHexCells.handle, nInd);
      [*] = ;end
      [*] = ;else
      [*] = ;   ind := 0;
      [*] = ;
      [*] = ;//_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister2 := ind;
      [*] = ;IntRegister3 := nInd;
   struct.end
section.end
