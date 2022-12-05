section.begin
   Name = CancelDeal
   Description[*] = ;IntRegister0 - sender player index
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\CANCELDEAL';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;var plName : String = GetPlayerNameByIndex(plIndex);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', ProposePlayer: '+IntToStr(plIndex)+']',_log_trace);
      [*] = ;
      [*] = ;// release escrow that was stored to be used in this deal
      [*] = ;_diplomacy_Escrow(plIndex, myPlIndex, false);
      [*] = ;
      [*] = ;IntRegister0 := plIndex;
      [*] = ;IntRegister1 := 0;
      [*] = ;ExecuteState('MessageEntry');
      [*] = ;
      [*] = ;var mType : Integer = gArrDiplomacy[plIndex][myPlIndex].message.mType;
      [*] = ;if (mType = gc_MessageThrowDice) or (mType = gc_MessageDemandSurrender) then
      [*] = ;begin
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   ExecuteState('DeclareWar');
      [*] = ;end;
      [*] = ;
      [*] = ;if _diplomacy_IsProposal(gArrDiplomacy[plIndex][myPlIndex].message) then
      [*] = ;   _diplomacy_AssignMessage(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage, gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;
      [*] = ;_diplomacy_ClearMessage(gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

