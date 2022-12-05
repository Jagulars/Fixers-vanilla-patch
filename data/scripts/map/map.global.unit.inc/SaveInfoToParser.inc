section.begin
   Name = SaveInfoToParser
   Description : struct.begin
      [*] = ;IntRegister0 - parser handle
      [*] = ;IntRegister1 - mode
      [*] = ;   0 - full save
      [*] = ;   1 - lan transfer save
   struct.end
   Code : struct.begin
      [*] = ;var mode : Integer = IntRegister1;
      [*] = ;var pParser : Integer = IntRegister0;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;ParserClearByHandle(pParser);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(pParser, 'Player', myPlIndex);
      [*] = ;
      [*] = ;var pPlParser : Integer = ParserAddChildByIndex(pParser, 'PlayerParser');
      [*] = ;ParserCopyFromByHandle(pMyParser);
      [*] = ;
      [*] = ;if (ParserGetIntValueByKeyByHandle(pMyParser, 'Surrender') <> 0) and (mode = 1) then
      [*] = ;begin
      [*] = ;   SwitchTo('Nothing');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var pPlStack : Integer = ParserAddChildByIndex(pParser, 'PlayerStack');
      [*] = ;
      [*] = ;for i := 0 to GetVarsCount()-1 do
      [*] = ;   ParserSetValueByKeyByHandle(pPlStack, GetNameByIndex(i), GetValueByIndex(i));
      [*] = ;
      [*] = ;var pPlHeroes : Integer = ParserAddChildByIndex(pParser, 'Heroes');
      [*] = ;var heroCount : Integer = GetPlayerGameObjectsCountByHandle(myPlHandle);
      [*] = ;for i := 0 to heroCount-1 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   var pPlHero : Integer = ParserAddChildByIndex(pPlHeroes, '*');
      [*] = ;   IntRegister0 := pPlHero;
      [*] = ;   IntRegister1 := mode;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'SaveInfoToParser');
      [*] = ;end;
      [*] = ;
      [*] = ;StateMachineGlobalVariablesSaveToParser(ParserAddChildByIndex(pParser, 'Game'), 'gGame', false, false);
      [*] = ;
      [*] = ;var pParsProvinces : Integer = ParserAddChildByIndex(pParser, 'Provinces');
      [*] = ;var pAttackRituals : Integer = ParserAddChildByIndex(pParser, 'AttackRituals');
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pProvinces)-1 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;   var updPlayer : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'UpdatePlayer');
      [*] = ;
      [*] = ;   if updPlayer = myPlIndex then
      [*] = ;   begin
      [*] = ;      if dummyHandle <> 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := ParserAddChildByIndex(pParsProvinces, '*');
      [*] = ;         IntRegister1 := mode;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'SaveInfoToParser');
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'ResetUpdateFlags');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var pCastedRituals : Integer = ParserSelectByHandleByKey(pProvince, 'CastedRituals');
      [*] = ;   var castedCount : Integer = ParserGetCountByHandle(pCastedRituals);
      [*] = ;
      [*] = ;   if (castedCount > 0) then
      [*] = ;   begin
      [*] = ;      var provPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      var enemyProv : Boolean = (not SameText(provPlayer, GetCurrentPlayerName));
      [*] = ;      var otherHumanPlayerProv : Boolean = (enemyProv and SameText(GetPlayerControlModeByHandle(GetPlayerHandleByName(provPlayer)),'cmPlayer'));
      [*] = ;      
      [*] = ;      if enemyProv then
      [*] = ;      for j := 0 to castedCount-1 do
      [*] = ;      begin
      [*] = ;         var pCastedRitual : Integer = ParserSelectByHandleByIndex(pCastedRituals, j);
      [*] = ;         var pAttackRitual : Integer = ParserAddChildByIndex(pAttackRituals, '*');
      [*] = ;         ParserCopyFromByHandle(pCastedRitual);
      [*] = ;         if otherHumanPlayerProv then // The ritual is never applied on this computer when cast on province of another human player, consequently it would never be deleted so it needs to be deleted here.
      [*] = ;            ParserFreeByhandle(pCastedRitual);
      [*] = ;         ParserSetIntValueByKeyByHandle(pAttackRitual, 'ProvinceIndex', i);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_diplomacy_PackToParser(gGame.map.players,ParserAddChildByIndex(pParser, 'Diplomacy'));
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

