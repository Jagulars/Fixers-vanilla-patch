section.begin
   Name = IsUnitSlotAvailable
   Description : struct.begin
      [*] = IntRegister0 - rank
      [*] = IntRegister1 - slot index
      [*] = OUT: BoolRegister0 - is slot available
      [*] = OUT: BoolRegister0 - is slot available
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var rank : Integer = IntRegister0;
      [*] = ;var slIndex : Integer = IntRegister1;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;ExecuteState('GetUnitSlots');
      [*] = ;
      [*] = ;if slIndex > IntRegister1 then
      [*] = ;BoolRegister0 := false
      [*] = ;else
      [*] = ;begin
      [*] = ;   BoolRegister0 := true;
      [*] = ;
      [*] = ;   var myParser : Integer = ParserSelectGameObject(GetGameObjectMyHandle);
      [*] = ;   var pMyUnits : Integer = ParserSelectByHandleByKey(myParser, 'Units');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pMyUnits)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMyUnit : Integer = ParserSelectByHandleByIndex(pMyUnits, i);
      [*] = ;      var slotRank : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'SlotRank');
      [*] = ;      var slotIndex : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'SlotIndex');
      [*] = ;
      [*] = ;      if (rank = slotRank) and (slIndex = slotIndex) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pMyUnit;
      [*] = ;         IntRegister1 := pMyUnits;
      [*] = ;         IntRegister2 := gc_battle_unit_iCurLife;
      [*] = ;         MapExecuteState('GetUnitPropertyByParser');
      [*] = ;         if IntRegister3 > 0 then
      [*] = ;         begin
      [*] = ;            BoolRegister0 := false;
      [*] = ;            exit;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
