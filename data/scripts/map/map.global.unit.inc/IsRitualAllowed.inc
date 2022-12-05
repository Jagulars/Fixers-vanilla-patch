section.begin
   Name = IsRitualAllowed
   Description : struct.begin
      [*] = IntRegister0 - ritual ID
      [*] = OUT: BoolRegister0 - is ritual allowed
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var ritualID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var bAllowed : Boolean = false;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var plCanCast : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanCast);
      [*] = ;if plCanCast > 0 then
      [*] = ;begin
      [*] = ;   ExecuteState('GetCastleParser');
      [*] = ;   var pProvince : Integer = IntRegister0;
      [*] = ;
      [*] = ;   var pMyRituals : Integer = ParserSelectByHandleByKey(pProvince, 'AvailableRituals');
      [*] = ;   var pMyRitual : Integer = ParserSelectByHandleByIndex(pMyRituals, ritualID);
      [*] = ;
      [*] = ;   var coolDown : Integer = ParserGetIntValueByKeyByHandle(pMyRitual, 'Cooldown');
      [*] = ;   var count : Integer = ParserGetIntValueByKeyByHandle(pMyRitual, 'Count');
      [*] = ;
      [*] = ;   if (count <> 0) and (coolDown = 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := ritualID;
      [*] = ;      ExecuteState('GetRitualPrice');
      [*] = ;      var ritGold : Integer = IntRegister1;
      [*] = ;      var ritGem : Integer = IntRegister2;
      [*] = ;
      [*] = ;      var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;      var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;      bAllowed := ((ritGold = 0) or (plGold >= ritGold)) and ((ritGem = 0) or (plGem >= ritGem));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := bAllowed;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
