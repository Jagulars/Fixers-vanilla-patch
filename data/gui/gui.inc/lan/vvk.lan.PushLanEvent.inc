section.begin
   Name = vvk.lan.PushLanEvent
   Description : struct.begin
      [*] = ;IntRegister0 - event_id
      [*] = ;IntRegister1 - from id
      [*] = ;IntRegister2 - to id
      [*] = ;IntRegister3 - tag? (leDisconnect, leTerminated)
      [*] = ;IntRegister4 - parser id (leSessionParser, leParser)
      [*] = ;IntRegister5 - parser handle (leSessionParser, leParser)
      [*] = ;StringRegister0 - session message (for event_id = leShellSessionMessage)
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;function CheckRepetition(event_id, parser_id, from_id, parser : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   
      [*] = ;   if (event_id = leSessionParser) and (parser_id = gc_LAN_SHARD_SYNC_READY) then
      [*] = ;   begin
      [*] = ;      var i, pParser : Integer;
      [*] = ;      for i := 0 to gIntRegister_LanParsersNumber[gIntRegister_LanParsersBufferIndex]-1 do
      [*] = ;      begin
      [*] = ;         pParser := gArr_LanParsersQueue[i][gIntRegister_LanParsersBufferIndex].parser;
      [*] = ;   
      [*] = ;         if (ParserGetIntValueByKeyByHandle(pParser, 'LanID') = from_id) and (ParserGetIntValueByKeyByHandle(pParser, 'TimerID') = ParserGetIntValueByKeyByHandle(parser, 'TimerID')) then
      [*] = ;         begin
      [*] = ;            Result := True;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure PushLanEvent(event_id, from_id, to_id, tag, parser_id, parser : Integer; msg : String);
      [*] = ;begin
      [*] = ;   if (not CheckRepetition(event_id, parser_id, from_id, parser)) then
      [*] = ;   begin
      [*] = ;      var n : Integer = gIntRegister_LanParsersBufferIndex;
      [*] = ;      var idx : Integer = gIntRegister_LanParsersNumber[n];
      [*] = ;      var p : Integer = 0;
      [*] = ;      var pName : String = 'LanQueueParser_'+IntToStr(n)+'_'+IntToStr(idx);
      [*] = ;
      [*] = ;      gArr_LanParsersQueue[idx][n].t := event_id;
      [*] = ;      case event_id of
      [*] = ;         leSessionParser, leParser, leShellSessionMessage : begin
      [*] = ;            var pfx : String;
      [*] = ;
      [*] = ;            case event_id of
      [*] = ;               leSessionParser : pfx := 'F';
      [*] = ;               leParser : pfx := 'A';
      [*] = ;               leShellSessionMessage : begin
      [*] = ;                  pfx := 'M';
      [*] = ;                  p := _misc_ParserGetOrCreateByKey(pName,true);
      [*] = ;                  ParserSetValueByKeyByHandle(p, 'Msg', msg);
      [*] = ;                  ParserSetIntValueByKeyByHandle(p, 'From', from_id);
      [*] = ;                  parser_id := gc_LAN_MESSAGE;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            _lan_LogReceivedParser(pfx+IntToStr(from_id),parser_id,parser,from_id);
      [*] = ;            if p = 0 then
      [*] = ;            begin
      [*] = ;               p := _misc_ParserGetOrCreateByKey(pName, True);
      [*] = ;               ParserCopyFromByHandle(parser);
      [*] = ;            end;
      [*] = ;            gArr_LanParsersQueue[idx][n].parser := p;
      [*] = ;            gArr_LanParsersQueue[idx][n].id := parser_id;
      [*] = ;         end;
      [*] = ;         leDisconnect, leTerminated : gArr_LanParsersQueue[idx][n].id := tag;
      [*] = ;         leShellClientDisconnected : gArr_LanParsersQueue[idx][n].id := from_id;
      [*] = ;         else gArr_LanParsersQueue[idx][n].id := from_id;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if _log then _log_valuesL('EVENT_ID|'+pName+'|FROM|TO',event_id,gArr_LanParsersQueue[idx][n].id,from_id,to_id,0,0);
      [*] = ;      gIntRegister_LanParsersNumber[n] := idx+1;
      [*] = ;      if idx >= gc_lan_max_parsers_queue_limit then
      [*] = ;      begin
      [*] = ;         ErrorLog('[LAN] Possible lockup in progress gui detected. Forcing LAN event processing');
      [*] = ;         if gIntRegister_LanParsersNumber[n xor 1] <> 0 then
      [*] = ;            ErrorLog('[LAN] Previous buffer not empty.');
      [*] = ;         GUIExecuteState('vvk.lan.OnProgressGUI');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;PushLanEvent( IntRegister0, IntRegister1, IntRegister2, IntRegister3, IntRegister4, IntRegister5, StringRegister0);
   struct.end
section.end
