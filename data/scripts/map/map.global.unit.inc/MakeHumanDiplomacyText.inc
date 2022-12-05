section.begin
   Name = MakeHumanDiplomacyText
   Code : struct.begin
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;var textIndex : Integer = IntRegister1;
      [*] = ;var textParam : Integer = IntRegister2;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;var profile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;function CheckTrade(trade : TTrade) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   if trade.gem > 0 then
      [*] = ;   Result := true;
      [*] = ;   if trade.gold > 0 then
      [*] = ;   Result := true;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   if not Result then
      [*] = ;   begin
      [*] = ;      for i := 0 to gc_MaxTradeResCount-1 do
      [*] = ;      if trade.arrResources[i] then
      [*] = ;      begin
      [*] = ;         Result := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not Result then
      [*] = ;   begin
      [*] = ;      for i := 0 to gc_MaxTradeProvCount-1 do
      [*] = ;      if trade.arrProvinces[i] >= 0 then
      [*] = ;      begin
      [*] = ;         Result := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not Result then
      [*] = ;   begin
      [*] = ;      for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;      if trade.arrItems[i][0] > 0 then
      [*] = ;      begin
      [*] = ;         Result := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   var give : Boolean = CheckTrade(gArrDiplomacy[myPlIndex][plIndex].message.tradeGive);
      [*] = ;   var take : Boolean = CheckTrade(gArrDiplomacy[myPlIndex][plIndex].message.tradeTake);
      [*] = ;
      [*] = ;   case gArrDiplomacy[myPlIndex][plIndex].message.treaty of
      [*] = ;      gc_TreatyWar : _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 4, 0);
      [*] = ;      gc_TreatyPeace : _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 5, 0);
      [*] = ;      gc_TreatyUnion : _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 6, 0);
      [*] = ;      gc_TreatyCancelUnion : _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 11, 0);
      [*] = ;      0 : begin
      [*] = ;         if gArrDiplomacy[myPlIndex][plIndex].message.mType = gc_MessageCancelTrade then
      [*] = ;         _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 10, 0)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if give and (not take) then
      [*] = ;            _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 13, 0) // it's a gift.
      [*] = ;            else
      [*] = ;            if (not give) and take then
      [*] = ;            _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 12, 0)
      [*] = ;            else
      [*] = ;            if give and take then
      [*] = ;            begin
      [*] = ;               case gArrDiplomacy[myPlIndex][plIndex].message.mType of
      [*] = ;                  gc_MessageTrade : _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 7, 0);
      [*] = ;                  gc_MessageExchange : _misc_PlMakeDiplomacyText(myPlIndex, plIndex, 8, 0);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
   Description[*] = ;IntRegister0 - player index
section.end

