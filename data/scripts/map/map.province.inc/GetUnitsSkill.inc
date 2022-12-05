section.begin
   Name = GetUnitsSkill
   Description : struct.begin
      [*] = ;IntRegister0 - ability ID
      [*] = ;OUT: IntRegister0 - ability value
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var abilityID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;var pGarrisonUnits : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Units');
      [*] = ;var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var i, j : Integer;
      [*] = ;var value : Integer = 0;
      [*] = ;
      [*] = ;// garrison
      [*] = ;for i := ParserGetCountByHandle(pGarrisonUnits)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pGarrisonUnit : Integer = ParserSelectByHandleByIndex(pGarrisonUnits, i);
      [*] = ;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   IntRegister1 := pGarrisonUnit;
      [*] = ;   IntRegister2 := 0;
      [*] = ;   IntRegister3 := abilityID;
      [*] = ;   MapExecuteState('CheckUnitAbility');
      [*] = ;   value := value + IntRegister4;
      [*] = ;end;
      [*] = ;
      [*] = ;// hero armies
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;   begin
      [*] = ;      var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;      if curUID = dummyUID then
      [*] = ;      begin
      [*] = ;         var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;         var pGOUnits : Integer = ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pGOUnits)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pGOUnit : Integer = ParserSelectByHandleByIndex(pGOUnits, j);
      [*] = ;
      [*] = ;            IntRegister0 := 0;
      [*] = ;            IntRegister1 := pGOUnit;
      [*] = ;            IntRegister2 := goHandle;
      [*] = ;            IntRegister3 := abilityID;
      [*] = ;            MapExecuteState('CheckUnitAbility');
      [*] = ;            value := value + IntRegister4;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister1 := value;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

