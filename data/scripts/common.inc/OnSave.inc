section.begin
   Name = OnSave
   UsedFileName =
   Code : struct.begin
      [*] = ;var pMachineParser : Integer = ParserSelectCurrentStateMachine;
      [*] = ;if pMachineParser = 0 then
      [*] = ;   pMachineParser := ParserCreateCurrentStateMachine();
      [*] = ;
      [*] = ;var gameVersion : String;
      [*] = ;_misc_GetBuildVersionExt(gameVersion);
      [*] = ;ParserSetValueByKeyByHandle(pMachineParser, 'Version', gameVersion);
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(pMachineParser, 'ObjectFlags', gProfile.objectflags);
      [*] = ;ParserSetIntValueByKeyByHandle(pMachineParser, 'ShardScenery', gProfile.shardscenery);
      [*] = ;ParserSetIntValueByKeyByHandle(pMachineParser, 'TownScenery', gProfile.townscenery);
      [*] = ;ParserSetIntValueByKeyByHandle(pMachineParser, 'ProvinceScenery', gProfile.provincescenery);
      [*] = ;ParserSetIntValueByKeyByHandle(pMachineParser, 'BattleScenery', gProfile.battlescenery);
      [*] = ;
      [*] = ;// save random keys
      [*] = ;GetRandomExtKey64(gIntRegister_RandomExtKey0, gIntRegister_RandomExtKey1);
      [*] = ;GetMapGeneratorRandomKey(gIntRegister_MapGeneratorKey0, gIntRegister_MapGeneratorKey1);
      [*] = ;GetGlobalMapGeneratorRandomKey(gIntRegister_GlobalMapGeneratorKey0, gIntRegister_GlobalMapGeneratorKey1);
      [*] = ;
      [*] = ;var pCurRegisters : Integer = ParserSelectByHandleByKey(pMachineParser, 'Registers');
      [*] = ;if (pCurRegisters<>0) then
      [*] = ;ParserClearByHandle(pCurRegisters);
      [*] = ;pCurRegisters := ParserAddChildByIndex(pMachineParser, 'Registers');
      [*] = ;StateMachineGlobalVariablesSaveToParser(pCurRegisters, '', true, true);
      [*] = ;
      [*] = ;// save indices instead of handles
      [*] = ;IntRegister0 := pMachineParser;
      [*] = ;ExecuteState('SaveConvertBatRegisters');
      [*] = ;//Log('OnSave execute');
   struct.end
section.end

