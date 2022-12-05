section.begin
   Name = AddMercenary
   UsedFileName = 
   Code : struct.begin
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pPlProvince : Integer = IntRegister0;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pPlProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var pMercenaryLevels : Integer = gPrototypeData.mercenaries.handle;
      [*] = ;
      [*] = ;// adding mercenaries
      [*] = ;IntRegister0 := 6;
      [*] = ;ExecuteState('CheckInnerBuildAbility');
      [*] = ;var level : Integer = IntRegister1;
      [*] = ;
      [*] = ;// no mercenary buildings
      [*] = ;if level = 0 then
      [*] = ;exit;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var sum : Integer = 0;
      [*] = ;
      [*] = ;for i := 0 to level-1 do
      [*] = ;begin
      [*] = ;   var pMercenaryLevel : Integer = ParserSelectByHandleByIndex(pMercenaryLevels, i);
      [*] = ;   var pMercenaries : Integer = ParserSelectByHandleByKey(pMercenaryLevel, 'Mercenaries');
      [*] = ;
      [*] = ;   for j := ParserGetCountByHandle(pMercenaries)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMercenary : Integer = ParserSelectByHandleByIndex(pMercenaries, j);
      [*] = ;      sum := sum + ParserGetIntValueByKeyByHandle(pMercenary, 'Frequency');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;      _log_map('Mercenary sum '+IntToStr(sum));
      [*] = ;
      [*] = ;var randSum : Float = RandomExt * sum;
      [*] = ;      _log_map('Mercenary randSum '+FloatToStr(randSum));
      [*] = ;
      [*] = ;for i := 0 to level-1 do
      [*] = ;begin
      [*] = ;   var pMercenaryLevel : Integer = ParserSelectByHandleByIndex(pMercenaryLevels, i);
      [*] = ;   var pMercenaries : Integer = ParserSelectByHandleByKey(pMercenaryLevel, 'Mercenaries');
      [*] = ;
      [*] = ;   for j := ParserGetCountByHandle(pMercenaries)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMercenary : Integer = ParserSelectByHandleByIndex(pMercenaries, j);
      [*] = ;      randSum := randSum - ParserGetIntValueByKeyByHandle(pMercenary, 'Frequency');
      [*] = ;      _log_map('Mercenary UnitID '+IntToStr(ParserGetIntValueByKeyByHandle(pMercenary, 'UnitID'))+', frequency '+IntToStr(ParserGetIntValueByKeyByHandle(pMercenary, 'Frequency')));
      [*] = ;
      [*] = ;      if randSum < 0 then
      [*] = ;      begin
      [*] = ;         var pProvMercenary : Integer = ParserSelectByHandleByKey(pPlProvince, 'Mercenary');
      [*] = ;         var unitID : Integer = ParserGetIntValueByKeyByHandle(pMercenary, 'UnitID');
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvMercenary, 'UnitID', unitID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvMercenary, 'Timer', 0);
      [*] = ;
      [*] = ;         _log_map('New Mercenary, unitID '+IntToStr(unitID));
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
