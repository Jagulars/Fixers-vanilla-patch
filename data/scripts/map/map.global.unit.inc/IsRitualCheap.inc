section.begin
   Name = IsRitualCheap
   Description : struct.begin
      [*] = ;IntRegister0 - ritual ID
      [*] = ;OUT: BoolRegister0 - is ritual cheap
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var ritualID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var cheap : Boolean = false;
      [*] = ;
      [*] = ;IntRegister0 := ritualID;
      [*] = ;ExecuteState('IsRitualAllowed');
      [*] = ;if BoolRegister0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := ritualID;
      [*] = ;   ExecuteState('GetRitualPrice');
      [*] = ;   var ritGold : Integer = IntRegister1;
      [*] = ;   var ritGem : Integer = IntRegister2;
      [*] = ;
      [*] = ;   var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;
      [*] = ;   var plGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var plGoldLimit : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldLimit);
      [*] = ;   var plGemLimit : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemLimit);
      [*] = ;
      [*] = ;   if ((ritGold = 0) or (plGold >= ritGold + 2 * plGoldLimit)) and ((ritGem = 0) or (plGem >= ritGem + 2 * plGemLimit) or ((ritualID = 5) and (plGem >= ritGem))) then
      [*] = ;   begin
      [*] = ;      cheap := true;
      [*] = ;
      [*] = ;      IntRegister0 := ritualID;
      [*] = ;      StateMachineExecuteState(GetMapInitMachineHandle, 'GetRitualParserByID', 0);
      [*] = ;      var pRitual : Integer = IntRegister1;
      [*] = ;      
      [*] = ;      var pRitResources : Integer = ParserSelectByHandleByKey(pRitual, 'Resources');
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      for i := ParserGetCountByHandle(pRitResources)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pRitResource : Integer = ParserSelectByHandleByIndex(pRitResources, i);
      [*] = ;         var resID : Integer = ParserGetIntValueByKeyByHandle(pRitResource, 'ResourceID');
      [*] = ;
      [*] = ;         IntRegister0 := resID;
      [*] = ;         ExecuteState('GetResCount');
      [*] = ;         var resCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if (resID > 7) and (resCount <= 0) then
      [*] = ;         begin
      [*] = ;            cheap := false;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := cheap;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

