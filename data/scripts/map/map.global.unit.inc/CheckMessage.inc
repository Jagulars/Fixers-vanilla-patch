section.begin
   Name = CheckMessage
   Description : struct.begin
      [*] = ;IntRegister0 - player index
      [*] = ;OUT: BoolRegister0 - requirements met
   struct.end
   Code : struct.begin
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;var mType : Integer = gArrDiplomacy[myPlIndex][plIndex].message.mtype;
      [*] = ;
      [*] = ;var bConditionsMet : Boolean = true;
      [*] = ;
      [*] = ;if (mType > 0) then
      [*] = ;begin
      [*] = ;   if gArrDiplomacy[myPlIndex][plIndex].message.treaty = gc_TreatyUnion then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleByIndex(plIndex), 'GetUnionCount');
      [*] = ;      if (IntRegister0 > 0) then
      [*] = ;         bConditionsMet := false;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if bConditionsMet and ((mType = gc_MessageExchange) or (mType = gc_MessageTrade)) then
      [*] = ;   begin
      [*] = ;      bConditionsMet := _diplomacy_CheckTrade(plIndex, myPlIndex, mType, gArrDiplomacy[myPlIndex][plIndex].message.tradeTake);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := bConditionsMet;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

