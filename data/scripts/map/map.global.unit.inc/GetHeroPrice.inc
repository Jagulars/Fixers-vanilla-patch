section.begin
   Name = GetHeroPrice
   Description : struct.begin
      [*] = ;IntRegister0 - hero class
      [*] = ;OUT: IntRegister1 - gold price
      [*] = ;OUT: IntRegister2 - gem price
   struct.end
   Code : struct.begin
      [*] = ;var heroClass : Integer = IntRegister0;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;
      [*] = ;var heroCount : Integer = GetPlayerGameObjectsCountByHandle(myPlHandle);
      [*] = ;var trueCount : Integer = heroCount;
      [*] = ;var sameCount : Integer = 0;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;for i := 0 to heroCount-1 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   if GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;      trueCount := trueCount - 1
      [*] = ;   else
      [*] = ;   if (GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd1) = heroClass) then
      [*] = ;      sameCount := sameCount + 1;
      [*] = ;end;
      [*] = ;
      [*] = ;if trueCount > 3 then
      [*] = ;   trueCount := 3;
      [*] = ;
      [*] = ;IntRegister0 := trueCount;
      [*] = ;MapExecuteState('GetHeroPriceParserByID');
      [*] = ;var pHeroPrice : Integer = IntRegister1;
      [*] = ;
      [*] = ;var gold : Integer = ParserGetIntValueByKeyByHandle(pHeroPrice, 'GoldPrice');
      [*] = ;var gem : Integer = ParserGetIntValueByKeyByHandle(pHeroPrice, 'GemPrice');
      [*] = ;var mult : Integer = Round(Pow(gc_HeroPriceMult, sameCount));
      [*] = ;
      [*] = ;gold := gold * mult;
      [*] = ;gem := gem * mult;
      [*] = ;
      [*] = ;IntRegister0 := 13;
      [*] = ;ExecuteState('CheckInnerBuildAbility');
      [*] = ;var value : Integer = IntRegister1;
      [*] = ;
      [*] = ;gold := gold - Floor(gold * value / 100);
      [*] = ;gem := gem - Floor(gem * value / 100);
      [*] = ;
      [*] = ;IntRegister1 := gold;
      [*] = ;IntRegister2 := gem;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
