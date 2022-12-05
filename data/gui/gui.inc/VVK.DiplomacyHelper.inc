section.begin
   Name = VVK.DiplomacyHelper
   Description : struct.begin
      [*] = ;IntRegister0 - mode
      [*] = ;0 - pack diplomacy array into parser
      [*] = ;   IntRegister1 - players number
      [*] = ;   IntRegister2 - destination parser
      [*] = ;1 - unpack diplomacy array from parser
      [*] = ;   IntRegister1 - players number
      [*] = ;   IntRegister2 - source parser
      [*] = ;2 - pack diplomacy message array into parser
      [*] = ;   IntRegister1 - parser
      [*] = ;   IntRegister2 - from player index
      [*] = ;   IntRegister3 - to player index
      [*] = ;3 - unpack diplomacy message array from parser
      [*] = ;   IntRegister1 - parser
      [*] = ;   IntRegister2 - from player index
      [*] = ;   IntRegister3 - to player index
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure PackTradeToParser(p : Integer; trade : TTrade);
      [*] = ;begin
      [*] = ;   var i,j : Integer;
      [*] = ;
      [*] = ;   _pars_PackValue(p,1,'t');
      [*] = ;   _pars_PackValue(p,trade.gem,'gm');
      [*] = ;   _pars_PackValue(p,trade.gold,'gl');
      [*] = ;   for i := 0 to gc_MaxTradeResCount-1 do
      [*] = ;      _pars_PackBoolValue(p,trade.arrResources[i],'ar'+IntToStr(i));
      [*] = ;
      [*] = ;   for i := 0 to gc_MaxTradeResCount-1 do
      [*] = ;      _pars_PackValue(p,trade.arrProvinces[i],'ap'+IntToStr(i));
      [*] = ;
      [*] = ;   for i := 0 to 1 do
      [*] = ;   begin
      [*] = ;      for j := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;         _pars_PackValue(p,trade.arrItems[j][i],'ai'+IntToStr((i*gc_MaxTradeItemCount)+j));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure PackMessageToParser(p : Integer; msg : TDiplMessage);
      [*] = ;begin
      [*] = ;   var pt : Integer;
      [*] = ;
      [*] = ;   _pars_PackValue(p,msg.mType,'t');
      [*] = ;   _pars_PackValue(p,msg.treaty,'tr');
      [*] = ;   _pars_PackValue(p,msg.deal,'d');
      [*] = ;   _pars_PackStrValue(p,msg.text,'tx');
      [*] = ;   pt := ParserAddChildByIndex(p, 'tg');
      [*] = ;   PackTradeToParser(pt,msg.tradeGive);
      [*] = ;   pt := ParserAddChildByIndex(p, 'tt');
      [*] = ;   PackTradeToParser(pt,msg.tradeTake);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UnPackTradeFromParser(p : Integer;var trade : TTrade);
      [*] = ;begin
      [*] = ;   var i,j : Integer;
      [*] = ;
      [*] = ;   trade.trade := _pars_UnPackBoolValue(p,'t');
      [*] = ;   trade.gem := _pars_UnPackValue(p,'gm');
      [*] = ;   trade.gold := _pars_UnPackValue(p,'gl');
      [*] = ;   for i := 0 to gc_MaxTradeResCount-1 do
      [*] = ;      trade.arrResources[i] := _pars_UnPackBoolValue(p,'ar'+IntToStr(i));
      [*] = ;
      [*] = ;   for i := 0 to gc_MaxTradeResCount-1 do
      [*] = ;      trade.arrProvinces[i] := _pars_UnPackValue(p,'ap'+IntToStr(i));
      [*] = ;
      [*] = ;   for i := 0 to 1 do
      [*] = ;   begin
      [*] = ;      for j := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;         trade.arrItems[j][i] := _pars_UnPackValue(p,'ai'+IntToStr((i*gc_MaxTradeItemCount)+j));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UnPackMessageFromParser(p : Integer;var msg : TDiplMessage);
      [*] = ;begin
      [*] = ;   var pt : Integer;
      [*] = ;
      [*] = ;   msg.mType := _pars_UnPackValue(p,'t');
      [*] = ;   msg.treaty := _pars_UnPackValue(p,'tr');
      [*] = ;   msg.deal := _pars_UnPackValue(p,'d');
      [*] = ;   _pars_UnPackStrValue(p,msg.text,'tx');
      [*] = ;
      [*] = ;   pt := ParserSelectByHandleByKey(p,'tg');
      [*] = ;   if pt <> 0 then
      [*] = ;      UnPackTradeFromParser(pt,msg.tradeGive)
      [*] = ;   else
      [*] = ;      _diplomacy_ClearTrade(msg.tradeGive);
      [*] = ;
      [*] = ;   pt := ParserSelectByHandleByKey(p,'tt');
      [*] = ;   if pt <> 0 then
      [*] = ;      UnPackTradeFromParser(pt,msg.tradeTake)
      [*] = ;   else
      [*] = ;      _diplomacy_ClearTrade(msg.tradeTake);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure PackToParser(players_no, parser : Integer);
      [*] = ;begin
      [*] = ;   if gGame.diplomacy then
      [*] = ;   begin
      [*] = ;      var i,j,k,l,p,pt : Integer;
      [*] = ;
      [*] = ;      for i := 0 to players_no-1 do
      [*] = ;      begin
      [*] = ;         for j := 0 to players_no-1 do
      [*] = ;         begin
      [*] = ;            //p := ParserAddChildByIndex(parser, 'P'+IntToStr((i*players_no)+j));
      [*] = ;            p := ParserAddChildByIndex(parser, '*');
      [*] = ;            _pars_PackValue(p,gArrDiplomacy[i][j].treaty,'t');
      [*] = ;            _pars_PackValue(p,gArrDiplomacy[i][j].pass,'p');
      [*] = ;            _pars_PackValue(p,gArrDiplomacy[i][j].attitude,'at');
      [*] = ;            _pars_PackValue(p,gArrDiplomacy[i][j].answer,'an');
      [*] = ;            _pars_PackValue(p,gArrDiplomacy[i][j].canKill,'ck');
      [*] = ;            _pars_PackValue(p,gArrDiplomacy[i][j].power,'pw');
      [*] = ;            _pars_PackValue(p,gArrDiplomacy[i][j].meet,'m');
      [*] = ;            _pars_PackValue(p,gArrDiplomacy[i][j].random,'r');
      [*] = ;            //_pars_PackBoolValue(p,gArrDiplomacy[i][j].lanAnswer,'la');
      [*] = ;            if gArrDiplomacy[i][j].trade.trade then
      [*] = ;            begin
      [*] = ;               pt := ParserAddChildByIndex(p, 'tr');
      [*] = ;               PackTradeToParser(pt,gArrDiplomacy[i][j].trade);
      [*] = ;            end;
      [*] = ;            if gArrDiplomacy[i][j].message.mType <> 0 then
      [*] = ;            begin
      [*] = ;               pt := ParserAddChildByIndex(p, 'ms');
      [*] = ;               PackMessageToParser(pt,gArrDiplomacy[i][j].message);
      [*] = ;            end;
      [*] = ;            for k := 0 to 2 do
      [*] = ;            begin
      [*] = ;               for l := 0 to 7 do
      [*] = ;                  _pars_PackValue(p,gArrDiplomacy[i][j].arrTalk[l][k],'atk'+IntToStr((k*8)+l));
      [*] = ;            end;
      [*] = ;            for l := 0 to 3 do
      [*] = ;               _pars_PackValue(p,gArrDiplomacy[i][j].arrTraitor[l],'atr'+IntToStr(l));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UnpackFromParser(players_no, parser : Integer);
      [*] = ;begin
      [*] = ;   if gGame.diplomacy then
      [*] = ;   begin
      [*] = ;      var i,j,k,l,p,pt : Integer;
      [*] = ;
      [*] = ;      for i := 0 to players_no-1 do
      [*] = ;      begin
      [*] = ;         for j := 0 to players_no-1 do
      [*] = ;         begin
      [*] = ;            //p := ParserSelectByHandleByKey(parser, 'P'+IntToStr((i*players_no)+j));
      [*] = ;            p := ParserSelectByHandleByIndex(parser, (i*players_no)+j);
      [*] = ;            gArrDiplomacy[i][j].treaty := _pars_UnPackValue(p,'t');
      [*] = ;            gArrDiplomacy[i][j].pass := _pars_UnPackValue(p,'p');
      [*] = ;            gArrDiplomacy[i][j].attitude := _pars_UnPackValue(p,'at');
      [*] = ;            gArrDiplomacy[i][j].answer := _pars_UnPackValue(p,'an');
      [*] = ;            gArrDiplomacy[i][j].canKill := _pars_UnPackValue(p,'ck');
      [*] = ;            gArrDiplomacy[i][j].power := _pars_UnPackValue(p,'pw');
      [*] = ;            //gArrDiplomacy[i][j].lanAnswer := _pars_UnPackBoolValue(p,'la');
      [*] = ;            gArrDiplomacy[i][j].meet := _pars_UnPackValue(p,'m');
      [*] = ;            gArrDiplomacy[i][j].random := _pars_UnPackValue(p,'r');
      [*] = ;
      [*] = ;            pt := ParserSelectByHandleByKey(p,'tr');
      [*] = ;            if pt <> 0 then
      [*] = ;               UnPackTradeFromParser(pt,gArrDiplomacy[i][j].trade)
      [*] = ;            else
      [*] = ;               _diplomacy_ClearTrade(gArrDiplomacy[i][j].trade);
      [*] = ;
      [*] = ;            pt := ParserSelectByHandleByKey(p,'ms');
      [*] = ;            if pt <> 0 then
      [*] = ;               UnPackMessageFromParser(pt,gArrDiplomacy[i][j].message)
      [*] = ;            else
      [*] = ;               _diplomacy_ClearMessage(gArrDiplomacy[i][j].message);
      [*] = ;
      [*] = ;            for k := 0 to 2 do
      [*] = ;            begin
      [*] = ;               for l := 0 to 7 do
      [*] = ;                  gArrDiplomacy[i][j].arrTalk[l][k] := _pars_UnPackValue(p,'atk'+IntToStr((k*8)+l));
      [*] = ;            end;
      [*] = ;            for l := 0 to 3 do
      [*] = ;               gArrDiplomacy[i][j].arrTraitor[l] := _pars_UnPackValue(p,'atr'+IntToStr(l));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;
      [*] = ;case mode of
      [*] = ;   0 : PackToParser( IntRegister1, IntRegister2 );
      [*] = ;   1 : UnpackFromParser( IntRegister1, IntRegister2 );
      [*] = ;   2 : PackMessageToParser( IntRegister1, gArrDiplomacy[IntRegister2][IntRegister3].message);
      [*] = ;   3 : UnpackMessageFromParser( IntRegister1, gArrDiplomacy[IntRegister2][IntRegister3].message);
      [*] = ;end;
   struct.end
section.end
