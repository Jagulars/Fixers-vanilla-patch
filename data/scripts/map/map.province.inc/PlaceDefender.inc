section.begin
   Name = PlaceDefender
   Description : struct.begin
      [*] = ;IntRegister0 - defender ID
   struct.end
   Code : struct.begin
      [*] = ;var defenderID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;
      [*] = ;IntRegister0 := defenderID;
      [*] = ;MapExecuteState('GetDefenderParserByID');
      [*] = ;var pDefender : Integer = IntRegister1;
      [*] = ;var defInit : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'Initiative');
      [*] = ;
      [*] = ;if ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID') > 0 then
      [*] = ;   ExecuteState('DismissDefender');
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(pProvDefender, 'DefenderID', defenderID);
      [*] = ;ParserSetIntValueByKeyByHandle(pProvDefender, 'Initiative', defInit);
      [*] = ;
      [*] = ;var pProvDefUnits : Integer = ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;var i, j : Integer;
      [*] = ;var pDefUnits : Integer = ParserSelectByHandleByKey(pDefender, 'Units');
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pDefUnits)-1 do
      [*] = ;begin
      [*] = ;   var pDefUnit : Integer = ParserSelectByHandleByIndex(pDefUnits, i);
      [*] = ;   var unitID : Integer = ParserGetIntValueByKeyByHandle(pDefUnit, 'UnitID');
      [*] = ;   var level : Integer = ParserGetIntValueByKeyByHandle(pDefUnit, 'Level');
      [*] = ;   var count : Integer = ParserGetIntValueByKeyByHandle(pDefUnit, 'Count');
      [*] = ;
      [*] = ;   IntRegister0 := unitID;
      [*] = ;   IntRegister1 := level;
      [*] = ;   MapExecuteState('GetUnitExpByLevel');
      [*] = ;   var exp : Integer = IntRegister2;
      [*] = ;
      [*] = ;   for j := 0 to count-1 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvDefUnits;
      [*] = ;      IntRegister1 := unitID;
      [*] = ;      IntRegister2 := exp;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      MapExecuteState('AddUnitToParser');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := defenderID;
      [*] = ;IntRegister1 := 5;
      [*] = ;MapExecuteState('CheckDefenderAbility');
      [*] = ;if IntRegister2 > 0 then
      [*] = ;begin
      [*] = ;   var provPlHandle : Integer = GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player'));
      [*] = ;   var provPlInd : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;
      [*] = ;   if provPlInd = gIntRegister_MapMyPlayerIndex then
      [*] = ;      MapExecuteState('map.DoShowFog')
      [*] = ;   else
      [*] = ;      PlayerExecuteStateByHandle(provPlHandle, 'CalcFogMap');
      [*] = ;   gBoolRegister_GUIUpdateMapHexGrid := true;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

