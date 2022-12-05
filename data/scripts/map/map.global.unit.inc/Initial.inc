section.begin
   Name = Initial
   Code : struct.begin
      [*] = ;if not gBoolRegister_Loading then
      [*] = ;begin
      [*] = ;   ClearVariables();
      [*] = ;
      [*] = ;   var i, pStackVar : Integer;
      [*] = ;   const objectType = 'ShardPlayer';
      [*] = ;
      [*] = ;   var pStack : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByKey(gPrototypeData.objectTypes.handle, objectType), 'Stack');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pStack)-1 do 
      [*] = ;   begin
      [*] = ;      pStackVar := ParserSelectByHandleByIndex(pStack, i);
      [*] = ;      SetValueByName(ParserGetValueByKeyByHandle(pStackVar, 'Name'), ParserGetValueByKeyByHandle(pStackVar, 'Value'));
      [*] = ;   end;
      [*] = ;
      [*] = ;   ExecuteState('CreateParser');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Main');
   struct.end
section.end

