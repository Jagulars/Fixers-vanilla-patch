section.begin
   Name = HireUnits
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\HIREUNITS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myGOCustomName : String = GetGameObjectCustomNameByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;var plKarma : Integer = _map_GetPlayerKarma(myPlHandle);
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyUnits : Integer = ParserSelectByHandleByKey(pMyParser, 'Units');
      [*] = ;
      [*] = ;var pMyPlParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;var pSpecUnits : Integer = ParserSelectByHandleByKey(pMyPlParser, 'SpecUnits');
      [*] = ;var pTreasury : Integer = ParserAddChildByIndex(pMyPlParser, 'Treasury');
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var pRecruitUnits : Integer = ParserSelectByHandleByKey(pCastle, 'RecruitUnits');
      [*] = ;
      [*] = ;var dummyUID : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;IntRegister0 := dummyUID;
      [*] = ;StateMachineExecuteState(initMachine, 'GetProvinceParserByUID', 0);
      [*] = ;var pProvince : Integer = IntRegister1;
      [*] = ;var provPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;
      [*] = ;var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;var pGarrisonUnits : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Units');
      [*] = ;
      [*] = ;var pHireUnits : Integer = _misc_ParserGetOrCreateByKey('mui_hu_UnitsList',true);
      [*] = ;
      [*] = ;procedure ArrangeHeroUnits;
      [*] = ;begin
      [*] = ;   IntRegister0 := pMyUnits;
      [*] = ;   IntRegister1 := myGOHandle;
      [*] = ;   IntRegister2 := 0;
      [*] = ;   IntRegister3 := 0;
      [*] = ;   StateMachineExecuteState(initMachine, 'map.ArrangeUnits', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ArrangeGarrisonUnits;
      [*] = ;begin
      [*] = ;   IntRegister0 := pGarrisonUnits;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   IntRegister2 := pProvGarrison;
      [*] = ;   IntRegister3 := 0;
      [*] = ;   StateMachineExecuteState(initMachine, 'map.ArrangeUnits', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;function ChooseRandomUnit(pHireUnits : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var sum : Integer = 0;
      [*] = ;   Result := 0;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pHireUnits)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pHireUnit : Integer = ParserSelectByHandleByIndex(pHireUnits, i);
      [*] = ;      sum := sum + ParserGetIntValueByKeyByHandle(pHireUnit, 'Freq');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var randSum : Float = RandomExt * sum;
      [*] = ;   for i := ParserGetCountByHandle(pHireUnits)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pHireUnit : Integer = ParserSelectByHandleByIndex(pHireUnits, i);
      [*] = ;      randSum := randSum - ParserGetIntValueByKeyByHandle(pHireUnit, 'Freq');
      [*] = ;
      [*] = ;      if randSum <= 0 then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckRitual(ritualID, slotRank : Integer);
      [*] = ;begin
      [*] = ;   IntRegister0 := slotRank;
      [*] = ;   ExecuteState('GetFreeUnitSlot');
      [*] = ;   var slotRank : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := ritualID;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'IsRitualCheap');
      [*] = ;   var cheap : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   if (slotRank > 0) and cheap then
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := ritualID;
      [*] = ;      IntRegister2 := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'CastRitual');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'CalcSpecUnits');
      [*] = ;var specCount : Integer = ParserGetCountByHandle(pSpecUnits);
      [*] = ;
      [*] = ;var bCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;
      [*] = ;IntRegister0 := 4;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'CheckOuterBuildAbility');
      [*] = ;var outValue4 : Integer = IntRegister1;
      [*] = ;
      [*] = ;if outValue4 > 0 then
      [*] = ;bCastle := true;
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;if (bCastle or (specCount > 0)) and SameText(provPlayer, myPlName) then
      [*] = ;begin
      [*] = ;   var rank : Integer = 5;
      [*] = ;   var slotCount : Integer = 0;
      [*] = ;
      [*] = ;   while slotCount = 0 do
      [*] = ;   begin
      [*] = ;      rank := rank - 1 ;
      [*] = ;      IntRegister0 := rank;
      [*] = ;      ExecuteState('GetUnitSlots');
      [*] = ;      slotCount := IntRegister1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var karma : Integer = 0;
      [*] = ;   var bad : Boolean = false;
      [*] = ;   var good : Boolean = false;
      [*] = ;
      [*] = ;   // check karma of available units
      [*] = ;   if bCastle then
      [*] = ;   begin
      [*] = ;      for i := ParserGetCountByHandle(pRecruitUnits)-1 downto -1 do
      [*] = ;      begin
      [*] = ;         var unitID : Integer;
      [*] = ;         // check mercenary
      [*] = ;         if i = -1 then
      [*] = ;         begin
      [*] = ;            var pProvMercenary : Integer = ParserSelectByHandleByKey(pCastle, 'Mercenary');
      [*] = ;            unitID := ParserGetIntValueByKeyByHandle(pProvMercenary, 'UnitID');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         // check other units
      [*] = ;         begin
      [*] = ;            var pRecruitUnit : Integer = ParserSelectByHandleByIndex(pRecruitUnits, i);
      [*] = ;            unitID := ParserGetIntValueByKeyByHandle(pRecruitUnit, 'UnitID');
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;         var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;         var unitKarma : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Karma');
      [*] = ;
      [*] = ;         if unitRank <= rank then
      [*] = ;         begin
      [*] = ;            if unitKarma < 0 then
      [*] = ;            bad := true;
      [*] = ;            if unitKarma > 0 then
      [*] = ;            good := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if bad and (not good) then
      [*] = ;      karma := -1;
      [*] = ;      if (not bad) and good then
      [*] = ;      karma := 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if karma = 0 then
      [*] = ;   begin
      [*] = ;      var bad : Integer = 0;
      [*] = ;      var good : Integer = 0;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pMyUnits)-1 downto 1 do
      [*] = ;      begin
      [*] = ;         var pMyUnit : Integer = ParserSelectByHandleByIndex(pMyUnits, i);
      [*] = ;         var unitID : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'UnitID');
      [*] = ;         var unitLevel : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'Level');
      [*] = ;
      [*] = ;         var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;         var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;         var unitKarma : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Karma');
      [*] = ;
      [*] = ;         if unitKarma > 0 then
      [*] = ;         good := good + 2 * unitRank + unitLevel;
      [*] = ;         if unitKarma < 0 then
      [*] = ;         bad := bad + 2 * unitRank + unitLevel;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if bad > good then
      [*] = ;      karma := -1;
      [*] = ;      if good > bad then
      [*] = ;      karma := 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ArrangeHeroUnits;
      [*] = ;
      [*] = ;   if bCastle then
      [*] = ;   begin
      [*] = ;      ArrangeGarrisonUnits;
      [*] = ;
      [*] = ;      // take units from garrison
      [*] = ;      for i := 1 to 4 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := i;
      [*] = ;         ExecuteState('GetUnitSlots');
      [*] = ;         var count : Integer = IntRegister1;
      [*] = ;
      [*] = ;         for j := 0 to count-1 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := i;
      [*] = ;            IntRegister1 := j;
      [*] = ;            ExecuteState('GetSlotUnit');
      [*] = ;            var pMyUnit : Integer = IntRegister2;
      [*] = ;
      [*] = ;            var unitID : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'UnitID');
      [*] = ;            var pGOUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;            var goUnitRank : Integer = ParserGetIntValueByKeyByHandle(pGOUnit, 'Rank');
      [*] = ;            var goUnitCurLife : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'CurLife');
      [*] = ;
      [*] = ;            IntRegister0 := pMyUnit;
      [*] = ;            IntRegister1 := pMyUnits;
      [*] = ;            IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;            StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;            var maxGOUnitLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;            if (pMyUnit = 0) or (goUnitCurLife < maxGOUnitLife / 2) then
      [*] = ;            begin
      [*] = ;               var choosen : Integer = -1;
      [*] = ;
      [*] = ;               for k := ParserGetCountByHandle(pGarrisonUnits)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pGarrisonUnit : Integer = ParserSelectByHandleByIndex(pGarrisonUnits, k);
      [*] = ;                  var unitID : Integer = ParserGetIntValueByKeyByHandle(pGarrisonUnit, 'UnitID');
      [*] = ;                  var garrUnitSlotRank : Integer = ParserGetIntValueByKeyByHandle(pGarrisonUnit, 'SlotRank');
      [*] = ;                  var garrUnitCurLife : Integer = ParserGetIntValueByKeyByHandle(pGarrisonUnit, 'CurLife');
      [*] = ;
      [*] = ;                  var pGarrUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;                  var garrUnitRank : Integer = ParserGetIntValueByKeyByHandle(pGarrUnit, 'Rank');
      [*] = ;                  var garrUnitKarma : Integer = ParserGetIntValueByKeyByHandle(pGarrUnit, 'Karma');
      [*] = ;
      [*] = ;                  IntRegister0 := pGarrisonUnit;
      [*] = ;                  IntRegister1 := pGarrisonUnits;
      [*] = ;                  IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;                  StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;                  var maxGarrUnitLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;                  if (garrUnitRank <= i) and ((pMyUnit = 0) or (goUnitRank <= garrUnitSlotRank)) and
      [*] = ;                  (garrUnitCurLife > maxGarrUnitLife * 6 / 10) and
      [*] = ;                  ((garrUnitKarma = 0) or (karma = 0) or (garrUnitKarma * karma > 0)) then
      [*] = ;                  begin
      [*] = ;                     var pGarrisonChUnit : Integer = ParserSelectByHandleByIndex(pGarrisonUnits, choosen);
      [*] = ;                     var unitID : Integer = ParserGetIntValueByKeyByHandle(pGarrisonChUnit, 'UnitID');
      [*] = ;                     var garrChUnitCurLife : Integer = ParserGetIntValueByKeyByHandle(pGarrisonChUnit, 'CurLife');
      [*] = ;
      [*] = ;                     var pGarrChUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;                     var chRank : Integer = ParserGetIntValueByKeyByHandle(pGarrChUnit, 'Rank');
      [*] = ;
      [*] = ;                     IntRegister0 := pGarrisonChUnit;
      [*] = ;                     IntRegister1 := pGarrisonUnits;
      [*] = ;                     IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;                     StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;                     var maxGarrChUnitLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;                     if (choosen = 0) or (garrUnitRank > chRank) then
      [*] = ;                     choosen := k
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if (garrUnitRank = chRank) and (garrUnitCurLife / maxGarrUnitLife > garrChUnitCurLife / maxGarrChUnitLife) then
      [*] = ;                        choosen := k;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if choosen >= 0 then
      [*] = ;               begin
      [*] = ;                  var pGarrisonUnit : Integer = ParserSelectByHandleByIndex(pGarrisonUnits, choosen);
      [*] = ;                  var unitID : Integer = ParserGetIntValueByKeyByHandle(pGarrisonUnit, 'UnitID');
      [*] = ;
      [*] = ;                  var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;                  var unitKarma : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Karma');
      [*] = ;
      [*] = ;                  if unitKarma <> 0 then
      [*] = ;                  karma := Round(unitKarma / Abs(unitKarma));
      [*] = ;
      [*] = ;                  if pMyUnit <> 0 then
      [*] = ;                  begin
      [*] = ;                     var pTmpParser : Integer = _misc_ParserGetOrCreateByKey('mui_hu_Temp',true);
      [*] = ;                     ParserCopyFromByHandle(pMyUnit);
      [*] = ;
      [*] = ;                     ParserSelectByHandle(pMyUnit);
      [*] = ;                     ParserCopyFromByHandle(pGarrisonUnit);
      [*] = ;
      [*] = ;                     ParserSelectByHandle(pGarrisonUnit);
      [*] = ;                     ParserCopyFromByHandle(pTmpParser);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var pNewUnit : Integer = ParserAddChildByIndex(pMyUnits, '*');
      [*] = ;                     ParserCopyFromByHandle(pGarrisonUnit);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pNewUnit, 'SlotRank', i);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pNewUnit, 'SlotIndex', j);
      [*] = ;
      [*] = ;                     ParserFreeByHandle(pGarrisonUnit);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  ArrangeHeroUnits;
      [*] = ;                  ArrangeGarrisonUnits;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // leave in garrison wounded units
      [*] = ;      for i := ParserGetCountByHandle(pMyUnits)-1 downto 1 do
      [*] = ;      begin
      [*] = ;         var pMyUnit : Integer = ParserSelectByHandleByIndex(pMyUnits, i);
      [*] = ;
      [*] = ;         var unitID : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'UnitID');
      [*] = ;         var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;         var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;         var unitKarma : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Karma');
      [*] = ;         var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;         var curLife : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'CurLife');
      [*] = ;
      [*] = ;         IntRegister0 := pMyUnit;
      [*] = ;         IntRegister1 := pMyUnits;
      [*] = ;         IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;         StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;         var maxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;         if (unitType <> 2) and ((curLife < maxLife / 2) or (karma * unitKarma < 0)) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := pProvGarrison;
      [*] = ;            IntRegister1 := unitRank;
      [*] = ;            StateMachineExecuteState(initMachine, 'map.GetFreeGarrisonSlot', 0);
      [*] = ;            var slotRank : Integer = IntRegister2;
      [*] = ;            var slotIndex : Integer = IntRegister3;
      [*] = ;
      [*] = ;            if (slotRank > 0) and (slotIndex >= 0) then
      [*] = ;            begin
      [*] = ;               var pNewGarrisonUnit : Integer = ParserAddChildByIndex(pGarrisonUnits, '*');
      [*] = ;               ParserCopyFromByHandle(pMyUnit);
      [*] = ;
      [*] = ;               ParserSetIntValueByKeyByHandle(pNewGarrisonUnit, 'SlotRank', slotRank);
      [*] = ;               ParserSetIntValueByKeyByHandle(pNewGarrisonUnit, 'SlotIndex', slotIndex);
      [*] = ;
      [*] = ;               ParserFreeByHandle(pMyUnit);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      ArrangeHeroUnits;
      [*] = ;
      [*] = ;      // hire units
      [*] = ;      for rank := 4 downto 1 do
      [*] = ;      begin
      [*] = ;         var count : Integer = 1;
      [*] = ;
      [*] = ;         IntRegister0 := rank;
      [*] = ;         ExecuteState('GetFreeUnitSlot');
      [*] = ;         var freeRank : Integer = IntRegister1;
      [*] = ;         var freeIndex : Integer = IntRegister2;
      [*] = ;
      [*] = ;         while (count > 0) and (freeRank > 0) and (freeIndex >= 0) do
      [*] = ;         begin
      [*] = ;            count := 0;
      [*] = ;            ParserClearByHandle(pHireUnits);
      [*] = ;
      [*] = ;            var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;            var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;            // from garrison
      [*] = ;            if bCastle then
      [*] = ;            begin
      [*] = ;               for i := ParserGetCountByHandle(pRecruitUnits)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pRecruitUnit : Integer = ParserSelectByHandleByIndex(pRecruitUnits, i);
      [*] = ;                  var unitID : Integer = ParserGetIntValueByKeyByHandle(pRecruitUnit, 'UnitID');
      [*] = ;
      [*] = ;                  var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;                  var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;                  var unitKarma : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Karma');
      [*] = ;
      [*] = ;                  IntRegister0 := unitID;
      [*] = ;                  IntRegister1 := pProvince;
      [*] = ;                  BoolRegister0 := false;
      [*] = ;                  PlayerExecuteStateByHandle(myPlHandle, 'GetUnitPrice');
      [*] = ;                  var gold : Integer = IntRegister2;
      [*] = ;                  var gem : Integer = IntRegister3;
      [*] = ;
      [*] = ;                  if (unitRank = rank) and (plGold >= gold) and (plGem >= gem) then
      [*] = ;                  begin
      [*] = ;                     var pHireUnit : Integer = ParserAddChildByIndex(pHireUnits, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHireUnit, 'UnitID', unitID);
      [*] = ;
      [*] = ;                     IntRegister0 := unitID;
      [*] = ;                     StateMachineExecuteState(initMachine, 'GetUnitPowerByID', 0);
      [*] = ;                     var power : Integer = 10 + IntRegister1;
      [*] = ;
      [*] = ;                     if (karma * unitKarma < 0) then
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHireUnit, 'Freq', 1)
      [*] = ;                     else
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHireUnit, 'Freq', power);
      [*] = ;
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pHireUnit, 'Special', false);
      [*] = ;                     count := count + 1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // from sites
      [*] = ;            for i := ParserGetCountByHandle(pSpecUnits)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pSpecUnit : Integer = ParserSelectByHandleByIndex(pSpecUnits, i);
      [*] = ;               var unitID : Integer = ParserGetIntValueByKeyByHandle(pSpecUnit, 'UnitID');
      [*] = ;
      [*] = ;               var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;               var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;               var unitKarma : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Karma');
      [*] = ;
      [*] = ;               IntRegister0 := unitID;
      [*] = ;               IntRegister1 := pProvince;
      [*] = ;               BoolRegister0 := false;
      [*] = ;               PlayerExecuteStateByHandle(myPlHandle, 'GetUnitPrice');
      [*] = ;               var gold : Integer = IntRegister2;
      [*] = ;               var gem : Integer = IntRegister3;
      [*] = ;
      [*] = ;               if (unitRank = rank) and (plGold >= gold) and (plGem >= gem) then
      [*] = ;               begin
      [*] = ;                  var pHireUnit : Integer = ParserAddChildByIndex(pHireUnits, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHireUnit, 'UnitID', unitID);
      [*] = ;
      [*] = ;                  IntRegister0 := unitID;
      [*] = ;                  StateMachineExecuteState(initMachine, 'GetUnitPowerByID', 0);
      [*] = ;                  var power : Integer = 10 + IntRegister1;
      [*] = ;
      [*] = ;                  if (karma * unitKarma < 0) then
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHireUnit, 'Freq', 1)
      [*] = ;                  else
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHireUnit, 'Freq', power);
      [*] = ;
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pHireUnit, 'Special', true);
      [*] = ;                  count := count + 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if ParserGetCountByHandle(pHireUnits) > 0 then
      [*] = ;            begin
      [*] = ;               var unitInd : Integer = ChooseRandomUnit(pHireUnits);
      [*] = ;               var pHireUnit : Integer = ParserSelectByHandleByIndex(pHireUnits, unitInd);
      [*] = ;               var unitID : Integer = ParserGetIntValueByKeyByHandle(pHireUnit, 'UnitID');
      [*] = ;               var specUnit : Boolean = ParserGetBoolValueByKeyByHandle(pHireUnit, 'Special');
      [*] = ;
      [*] = ;               var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;               var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;               var unitKarma : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Karma');
      [*] = ;
      [*] = ;               IntRegister0 := unitRank;
      [*] = ;               ExecuteState('GetFreeUnitSlot');
      [*] = ;               var slotRank : Integer = IntRegister1;
      [*] = ;               var slotIndex : Integer = IntRegister2;
      [*] = ;
      [*] = ;               IntRegister0 := myGOHandle;
      [*] = ;               IntRegister1 := pProvince;
      [*] = ;               IntRegister2 := unitID;
      [*] = ;               IntRegister3 := slotRank;
      [*] = ;               IntRegister4 := slotIndex;
      [*] = ;               BoolRegister0 := false;
      [*] = ;               BoolRegister1 := false;
      [*] = ;               BoolRegister2 := (not specUnit);
      [*] = ;               PlayerExecuteStateByHandle(myPlHandle, 'BuyUnit');
      [*] = ;               _gui_ProgressCalculations(_log_name+' '+myGOCustomName + ' of player ' + myPlName + ' recruits ' + GetLocaleTableListItemByID('unit', IntToStr(unitID)));
      [*] = ;
      [*] = ;               if (karma = 0) and (unitKarma <> 0) then
      [*] = ;                  karma := Round(unitKarma / Abs(unitKarma));
      [*] = ;
      [*] = ;               // delete item from treasury if unit was from item
      [*] = ;               if specUnit then
      [*] = ;               begin
      [*] = ;                  for i:= ParserGetCountByHandle(pSpecUnits)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var pSpecUnit : Integer = ParserSelectByHandleByIndex(pSpecUnits, i);
      [*] = ;                     var spUnitID : Integer = ParserGetIntValueByKeyByHandle(pSpecUnit, 'UnitID');
      [*] = ;                     var unitCount : Integer = ParserGetIntValueByKeyByHandle(pSpecUnit, 'Count');
      [*] = ;
      [*] = ;                     if unitID = spUnitID then
      [*] = ;                     begin
      [*] = ;                        unitCount := unitCount-1;
      [*] = ;                        if unitCount = 0 then
      [*] = ;                           ParserFreeByHandle(pSpecUnit);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     for j := ParserGetCountByHandle(pTreasury)-1 downto 0 do
      [*] = ;                     begin
      [*] = ;                        var pTrItem : Integer = ParserSelectByHandleByIndex(pTreasury, j);
      [*] = ;                        var itemID : Integer = ParserGetIntValueByKeyByHandle(pTrItem, 'ItemID');
      [*] = ;
      [*] = ;                        if itemID > 0 then
      [*] = ;                        begin
      [*] = ;                           IntRegister0 := itemID;
      [*] = ;                           IntRegister1 := 84;
      [*] = ;                           StateMachineExecuteState(initMachine, 'CheckItemAbility', 0);
      [*] = ;                           var value : Integer = IntRegister2;
      [*] = ;
      [*] = ;                           if value = unitID then
      [*] = ;                           begin
      [*] = ;                              ParserSetIntValueByKeyByHandle(pTrItem, 'ItemID', 0);
      [*] = ;                              ParserSetIntValueByKeyByHandle(pTrItem, 'Durability', 0);
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            IntRegister0 := rank;
      [*] = ;            ExecuteState('GetFreeUnitSlot');
      [*] = ;            freeRank := IntRegister1;
      [*] = ;            freeIndex := IntRegister2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // rituals for summoning unit
      [*] = ;      if karma < 0 then
      [*] = ;      begin
      [*] = ;         CheckRitual(11, 2);
      [*] = ;         CheckRitual(6, 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

