section.begin
   Name = OnAfterLoad
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\ONAFTERLOAD';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var myHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myParser : Integer = ParserSelectPlayer(myHandle);
      [*] = ;if myParser = 0 then
      [*] = ;   myParser := ParserCreatePlayer(myHandle);
      [*] = ;
      [*] = ;Log(_log_name+'['+GetPlayerNameByHandle(myHandle)+']');
      [*] = ;
      [*] = ;var valueName, value, value2 : String;
      [*] = ;var i, j, pStackVar, correctValueIndex : Integer;
      [*] = ;
      [*] = ;const objectType = 'ShardPlayer';
      [*] = ;var pStack : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByKey(gPrototypeData.objectTypes.handle, objectType), 'Stack');
      [*] = ;var stackVarCount : Integer = ParserGetCountByHandle(pStack);
      [*] = ;
      [*] = ;// Ensure that all needed values exist
      [*] = ;for i := 0 to stackVarCount-1 do
      [*] = ;begin
      [*] = ;   pStackVar := ParserSelectByHandleByIndex(pStack, i);
      [*] = ;   valueName := ParserGetValueByKeyByHandle(pStackVar, 'Name');
      [*] = ;   if (not GetValueExistedByName(valueName)) then
      [*] = ;   begin
      [*] = ;      ErrorLogI(valueName+' stack value is missing. Adding.');
      [*] = ;      SetValueByName(valueName, ParserGetValueByKeyByHandle(pStackVar, 'Value'));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var bAllClear : Boolean = false;
      [*] = ;repeat // Ensure that values occupy correct indices.
      [*] = ;   for i := GetVarsCount()-1 downto 0 do
      [*] = ;   begin
      [*] = ;      correctValueIndex := -1;
      [*] = ;      valueName := GetNameByIndex(i);
      [*] = ;      for j := stackVarCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pStackVar := ParserSelectByHandleByIndex(pStack, j);
      [*] = ;         if SameText(ParserGetValueByKeyByHandle(pStackVar, 'Name'), valueName) then
      [*] = ;         begin
      [*] = ;            correctValueIndex := j;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (correctValueIndex = -1) then
      [*] = ;      begin
      [*] = ;         ErrorLogI(valueName+' stack value is not needed, ignore.');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (i <> correctValueIndex) then // swap values
      [*] = ;      begin
      [*] = ;         ErrorLogI(valueName+' stack value wrong index: '+IntToStr(i)+' instead of '+IntToStr(correctValueIndex)+', swapping');
      [*] = ;         value2 := GetValueByIndex(correctValueIndex);
      [*] = ;         value := GetValueByIndex(i);
      [*] = ;         SetNameByIndex(i, GetNameByIndex(correctValueIndex));
      [*] = ;         SetNameByIndex(correctValueIndex, valueName);
      [*] = ;         SetValueByIndex(i, value2);
      [*] = ;         SetValueByIndex(correctValueIndex, value);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if i = 0 then
      [*] = ;      bAllClear := true;
      [*] = ;   end;
      [*] = ;until bAllClear;
      [*] = ;
      [*] = ;if ParserSelectByHandleByKey(myParser, 'KilledPlayers') = 0 then
      [*] = ;   ParserAddChildByIndex(myParser, 'KilledPlayers');
      [*] = ;
      [*] = ;if ParserSelectByHandleByKey(myParser, 'EventItems') = 0 then
      [*] = ;   ParserAddChildByIndex(myParser, 'EventItems');
      [*] = ;
      [*] = ;if ParserSelectByHandleByKey(myParser, 'Conflicts') = 0 then
      [*] = ;   ParserAddChildByIndex(myParser, 'Conflicts');
      [*] = ;
      [*] = ;if not ParserIsValueExistsByKeyByHandle(myParser, 'LastTurnCorruption') then ParserSetIntValueByKeyByHandle(myParser,'LastTurnCorruption',$10000);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

