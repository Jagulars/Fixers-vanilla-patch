section.begin
   Name = RestoreArmyVars
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myHandle);
      [*] = ;var pUnits : Integer = ParserSelectByHandleByKey(pMyParser, 'Units');
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pUnits)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pUnit : Integer = ParserSelectByHandleByIndex(pUnits, i);
      [*] = ;   var unitID : Integer =  ParserGetIntValueByKeyByHandle(pUnit, 'UnitID');
      [*] = ;
      [*] = ;   IntRegister0 := pUnit;
      [*] = ;   IntRegister1 := pUnits;
      [*] = ;   IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;   StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;   var maxLife : Integer = IntRegister3;
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnit, 'CurLife', maxLife);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pUnit, 'FCurLife', maxLife);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pUnit, 'LifeRatio', 1);
      [*] = ;
      [*] = ;   if i = 0 then
      [*] = ;   begin
      [*] = ;      SetIntValueByIndex(gc_map_GOStack_MapUnit_iCurHP, maxLife);
      [*] = ;      SetFloatValueByIndex(gc_map_GOStack_MapUnit_fCurToMaxLife, 1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := pUnit;
      [*] = ;   IntRegister1 := pUnits;
      [*] = ;   IntRegister2 := gc_battle_unit_iMaxMoral;
      [*] = ;   StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;   var maxMoral : Integer = IntRegister3;
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnit, 'CurMoral', maxMoral);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
