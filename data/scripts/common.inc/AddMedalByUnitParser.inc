section.begin
   Name = AddMedalByUnitParser
   Description : struct.begin
      [*] = ;IntRegister0 - unit parser
      [*] = ;IntRegister1 - medal ID
   struct.end
   Code : struct.begin
      [*] = ;var medalID : Integer = IntRegister1;
      [*] = ;
      [*] = ;var pUnitMedals : Integer = ParserSelectByHandleByKey(IntRegister0, 'Medals');
      [*] = ;if pUnitMedals = 0 then
      [*] = ;   pUnitMedals := ParserAddChildByIndex(IntRegister0, 'Medals');
      [*] = ;
      [*] = ;var pUnitMedal : Integer = ParserAddChildByIndex(pUnitMedals, '*');
      [*] = ;ParserSetIntValueByKeyByHandle(pUnitMedal, 'MedalID', medalID);
   struct.end
section.end
