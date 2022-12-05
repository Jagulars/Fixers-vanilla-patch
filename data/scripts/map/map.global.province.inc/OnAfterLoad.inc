section.begin
   Name = OnAfterLoad
   Code : struct.begin
      [*] = ;var myHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myParser : Integer = ParserSelectPlayer(myHandle);
      [*] = ;if myParser = 0 then
      [*] = ;   myParser := ParserCreatePlayer(myHandle);
      [*] = ;ParserSetIntValueByKeyByHandle(myParser, 'ProvincesDummyObjectsParser', 1);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

