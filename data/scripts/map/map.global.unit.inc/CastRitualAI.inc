section.begin
   Name = CastRitualAI
   LanClientExecute = True
   UsedFileName =
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetCurrentPlayerName;
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;var plGoldLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldLimit);
      [*] = ;var plGemLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemLimit);
      [*] = ;var ritCanCast : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanCast);
      [*] = ;var plUnionRace : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;var plKarma : Integer = _map_GetPlayerKarma(myPlHandle);
      [*] = ;
      [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var pRituals : Integer = gPrototypeData.rituals.handle;
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;var i, j, k, l, m, pRitual, ritID, ritKarma, pProvince, pProvFog, fog, dummyUID, dummyHandle, provPlHandle, provPlIndex, level, raceID, pProvDefender, defenderID, pDefUnits, newTaste, newHeroUID, newPower : Integer;
      [*] = ;var goHandle, heroLevel, pGOParser, pGOUnits, unitID, pUnit, unitRank, curUID, pGOUnit, curLife, pDollSlots, pDollSlot, itemID, temp, mood, unrest, danger, defPower, treaty, canKill, goldIncome, gemIncome, resID : Integer;
      [*] = ;var isCastle, isGuarded, isDead : Boolean;
      [*] = ;
      [*] = ;for i := 0 to ritCanCast-1 do
      [*] = ;begin
      [*] = ;   var ritualID : Integer = 0;
      [*] = ;   var tProvince : Integer = 0;
      [*] = ;   var heroUID : Integer = 0;
      [*] = ;   var taste : Integer = 0;
      [*] = ;
      [*] = ;   // TODO: OPTIMIZATION - maybe exchanging 2 cycles would be better
      [*] = ;   for j := ParserGetCountByHandle(pRituals)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pRitual := ParserSelectByHandleByIndex(pRituals, j);
      [*] = ;      ritID := ParserGetIntValueByKeyByHandle(pRitual, 'RitualID');
      [*] = ;
      [*] = ;      IntRegister0 := ritID;
      [*] = ;      ExecuteState('IsRitualCheap');
      [*] = ;      if BoolRegister0 then
      [*] = ;      begin
      [*] = ;         ritKarma := Min(Max(ParserGetIntValueByKeyByHandle(pRitual, 'Karma'), -1), 1);
      [*] = ;         
      [*] = ;         for k := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            pProvince := ParserSelectByHandleByIndex(pProvinces, k);
      [*] = ;            pProvFog := ParserSelectByHandleByKey(pProvince, 'Fog');
      [*] = ;            fog := ParserGetIntValueByIndexByHandle(pProvFog, myPlIndex);
      [*] = ;
      [*] = ;            dummyUID := ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            if (fog = 0) and (dummyUID > 0) then
      [*] = ;            begin
      [*] = ;               dummyHandle := GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;               IntRegister0 := ritID;
      [*] = ;               IntRegister1 := myPlHandle;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'CanCastRitual');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;                  provPlHandle := GetPlayerHandleByName(provPlName);
      [*] = ;                  provPlIndex := GetPlayerIndexByHandle(provPlHandle);
      [*] = ;                  level := ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;                  raceID := ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;                  isCastle := ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;                  pProvDefender := ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;                  defenderID := ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;                  pDefUnits := ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;                  isGuarded := (ParserGetCountByHandle(pDefUnits) > 0);
      [*] = ;
      [*] = ;                  case ritID of 
      [*] = ;                     2, 3, 5, 10, 13, 19 : begin
      [*] = ;                        GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;                        mood := IntRegister0;
      [*] = ;                     end;
      [*] = ;                     else
      [*] = ;                        mood := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  case ritID of 
      [*] = ;                     2, 13 : begin
      [*] = ;                        StringRegister0 := myPlName;
      [*] = ;                        GameObjectExecuteStateByHandle(dummyHandle, 'GetPlayerUnrest');
      [*] = ;                        unrest := IntRegister0;
      [*] = ;                     end;
      [*] = ;                     else
      [*] = ;                        unrest := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  case ritID of 
      [*] = ;                     10, 13, 15 : begin
      [*] = ;                        IntRegister0 := pProvince;
      [*] = ;                        IntRegister1 := 0;
      [*] = ;                        ExecuteState('GetProvinceDanger');
      [*] = ;                        danger := IntRegister2;
      [*] = ;                     end;
      [*] = ;                     else
      [*] = ;                        danger := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  case ritID of 
      [*] = ;                     13, 15 : begin
      [*] = ;                        IntRegister0 := defenderID;
      [*] = ;                        IntRegister1 := pDefUnits;
      [*] = ;                        StateMachineExecuteState(initMachine, 'GetDefenderPower', 0);
      [*] = ;                        defPower := IntRegister2;
      [*] = ;                     end;
      [*] = ;                     else
      [*] = ;                        defPower := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  case ritID of 
      [*] = ;                     15, 18, 23 : begin
      [*] = ;                        IntRegister0 := 3;
      [*] = ;                        IntRegister1 := -1;
      [*] = ;                        GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;                        goldIncome := IntRegister0;
      [*] = ;                        gemIncome := IntRegister1;
      [*] = ;                     end;
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        goldIncome := 0;
      [*] = ;                        gemIncome := 0;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  case ritID of 
      [*] = ;                     14, 15, 18, 23 : begin
      [*] = ;                        IntRegister0 := 1;
      [*] = ;                        GameObjectExecuteStateByHandle(dummyHandle, 'GetResource');
      [*] = ;                        resID := IntRegister1;
      [*] = ;                     end;
      [*] = ;                     else
      [*] = ;                        resID := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if provPlIndex >= 0 then
      [*] = ;                  begin
      [*] = ;                     treaty := gArrDiplomacy[myPlIndex][provPlIndex].treaty;
      [*] = ;                     canKill := gArrDiplomacy[myPlIndex][provPlIndex].canKill;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     treaty := 0;
      [*] = ;                     canKill := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  case ritID of
      [*] = ;                     2 : // extravaganza
      [*] = ;                     begin
      [*] = ;                        if mood < 0 then
      [*] = ;                        newTaste := Round(Abs(mood * level + unrest div 25));
      [*] = ;                     end;
      [*] = ;                     3 : // enchanted coffer
      [*] = ;                     begin
      [*] = ;                        if (plGold <= plGoldLimit) and (mood > 0) then
      [*] = ;                        newTaste := mood * 2 + level;
      [*] = ;                     end;
      [*] = ;                     5 : // dark ritual
      [*] = ;                     begin
      [*] = ;                        if (plGem <= plGemLimit) and (mood > 0) then
      [*] = ;                        newTaste := mood * 2 + level;
      [*] = ;                     end;
      [*] = ;                     8 : // illusionary battle
      [*] = ;                     begin
      [*] = ;                        for l := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;                        begin
      [*] = ;                           goHandle := GetGameObjectHandleByIndex(l, myPlHandle);
      [*] = ;                           isDead := GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;                           curUID := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;                           if (not isDead) and (curUID = dummyUID) then
      [*] = ;                           begin
      [*] = ;                              temp := 0;
      [*] = ;                              pGOParser := ParserSelectGameObject(goHandle);
      [*] = ;                              pGOUnits := ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;
      [*] = ;                              for m := ParserGetCountByHandle(pGOUnits)-1 downto 0 do
      [*] = ;                              begin
      [*] = ;                                 pGOUnit := ParserSelectByHandleByIndex(pGOUnits, m);
      [*] = ;                                 curLife := ParserGetIntValueByKeyByHandle(pGOUnit, 'CurLife');
      [*] = ;
      [*] = ;                                 if curLife > 0 then
      [*] = ;                                 temp := temp + 3 - ParserGetIntValueByKeyByHandle(pGOUnit, 'Level') div 10;
      [*] = ;                              end;
      [*] = ;
      [*] = ;                              if temp > newTaste then
      [*] = ;                              begin
      [*] = ;                                 newTaste := temp;
      [*] = ;                                 newHeroUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     9 : // creation
      [*] = ;                     begin
      [*] = ;                        for l := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;                        begin
      [*] = ;                           goHandle := GetGameObjectHandleByIndex(l, myPlHandle);
      [*] = ;                           if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;                           begin
      [*] = ;                              pGOParser := ParserSelectGameObject(goHandle);
      [*] = ;                              pDollSlots := ParserSelectByHandleByKey(pGOParser, 'DollSlots');
      [*] = ;
      [*] = ;                              for m := gc_HeroDollSlotsCount-1 downto 0 do
      [*] = ;                              begin
      [*] = ;                                 pDollSlot := ParserSelectByHandleByIndex(pDollSlots, m);
      [*] = ;                                 itemID := ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemID');
      [*] = ;
      [*] = ;                                 if itemID = 0 then
      [*] = ;                                 newTaste := newTaste + 1;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     10 : // gifts of earth
      [*] = ;                     begin
      [*] = ;                        newTaste := level + danger * 10;
      [*] = ;                        if mood < 0 then
      [*] = ;                        newTaste := newTaste + mood * 10;
      [*] = ;                     end;
      [*] = ;                     13 : // heavenly guards
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := 64;
      [*] = ;                        IntRegister1 := 0;
      [*] = ;                        StateMachineExecuteState(initMachine, 'GetDefenderPower', 0);
      [*] = ;                        var newPower : Integer = IntRegister2;
      [*] = ;
      [*] = ;                        if isGuarded then
      [*] = ;                        begin
      [*] = ;                           newTaste := (newPower - defPower) * 20;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        newTaste := newPower * 30;
      [*] = ;
      [*] = ;                        newTaste := newTaste * danger;
      [*] = ;
      [*] = ;                        if (mood < 0) and (newTaste > 0) then
      [*] = ;                        newTaste := newTaste + Round(Abs((mood * level) div 3 + unrest div 100));
      [*] = ;
      [*] = ;                        if pProvince = pCastle then
      [*] = ;                        newTaste := newTaste * 2;
      [*] = ;                     end;
      [*] = ;                     14 : // mass insanity
      [*] = ;                     begin
      [*] = ;                        if (provPlHandle <> myPlHandle) and (provPlHandle <> 0) then
      [*] = ;                        begin
      [*] = ;                           newTaste := level - 5;
      [*] = ;
      [*] = ;                           if resID > 0 then
      [*] = ;                           newTaste := newTaste + 3;
      [*] = ;
      [*] = ;                           if isCastle then
      [*] = ;                           newTaste := newTaste + 10;
      [*] = ;
      [*] = ;                           case raceID of
      [*] = ;                              2, 3, 7 : newTaste := newTaste * 3;
      [*] = ;                              5 : newTaste := newTaste * 2;
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           if (raceID > 0) and (raceID = plUnionRace) then
      [*] = ;                           newTaste := newTaste * 2;
      [*] = ;
      [*] = ;                           if not isGuarded then
      [*] = ;                           newTaste := newTaste * 3
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              if (treaty = gc_TreatyWar) and (canKill < 0)  then
      [*] = ;                              newTaste := newTaste * 4;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     15 : // magic barrier
      [*] = ;                     begin
      [*] = ;                        if danger >= 3 then
      [*] = ;                        begin
      [*] = ;                           newTaste := goldIncome + 2 * gemIncome;
      [*] = ;
      [*] = ;                           IntRegister0 := resID;
      [*] = ;                           ExecuteState('GetResCount');
      [*] = ;                           var resCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;                           if (resID > 0) and (resCount < 2) then
      [*] = ;                           begin
      [*] = ;                              IntRegister0 := resID;
      [*] = ;                              ExecuteState('GetResPriceStat');
      [*] = ;                              var goldPrice : Integer = IntRegister1;
      [*] = ;                              var gemPrice : Integer = IntRegister2;
      [*] = ;
      [*] = ;                              newTaste := newTaste + goldPrice div 5 + gemPrice div 2;
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           if isGuarded then
      [*] = ;                           begin
      [*] = ;                              if defPower > 0 then
      [*] = ;                              newTaste := newTaste div defPower;
      [*] = ;
      [*] = ;                              if pProvince = pCastle then
      [*] = ;                              newTaste := newTaste * 2;
      [*] = ;
      [*] = ;                              newTaste := newTaste * (danger - 2);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     16 : // blizzard
      [*] = ;                     begin
      [*] = ;                        if (provPlHandle <> myPlHandle) and (provPlHandle <> 0) and (treaty = gc_TreatyWar) then
      [*] = ;                        begin
      [*] = ;                           var bCast : Boolean = false;
      [*] = ;                           for l := GetPlayerGameObjectsCountByHandle(provPlHandle)-1 downto 0 do
      [*] = ;                           begin
      [*] = ;                              goHandle := GetGameObjectHandleByIndex(l, provPlHandle);
      [*] = ;                              isDead := GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;                              curUID := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;                              heroLevel := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;
      [*] = ;                              if (not isDead) and (curUID = dummyUID) then
      [*] = ;                              begin
      [*] = ;                                 if heroLevel > 10 then
      [*] = ;                                 bCast := true;
      [*] = ;
      [*] = ;                                 newTaste := newTaste + heroLevel;
      [*] = ;
      [*] = ;                                 pGOParser := ParserSelectGameObject(goHandle);
      [*] = ;                                 pGOUnits := ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;
      [*] = ;                                 for m := ParserGetCountByHandle(pGOUnits)-1 downto 0 do
      [*] = ;                                 begin
      [*] = ;                                    pGOUnit := ParserSelectByHandleByIndex(pGOUnits, m);
      [*] = ;                                    unitID := ParserGetIntValueByKeyByHandle(pGOUnit, 'UnitID');
      [*] = ;
      [*] = ;                                    pUnit := _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;                                    unitRank := ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;                                    newTaste := newTaste + unitRank;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           if bCast then
      [*] = ;                           newTaste := newTaste * 10
      [*] = ;                           else
      [*] = ;                           newTaste := 0;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     17, 22, 24 : // rain of brimstone, conflagration, pestilence
      [*] = ;                     begin
      [*] = ;                        if (provPlHandle <> myPlHandle) and (provPlHandle <> 0) and (treaty = gc_TreatyWar) and (canKill < 0) then
      [*] = ;                        begin
      [*] = ;                           newTaste := Floor(RandomExt * 10) - 5;
      [*] = ;                           if isCastle then
      [*] = ;                           newTaste := newTaste + 10;
      [*] = ;
      [*] = ;                           for l := GetPlayerGameObjectsCountByHandle(provPlHandle)-1 downto 0 do
      [*] = ;                           begin
      [*] = ;                              goHandle := GetGameObjectHandleByIndex(l, provPlHandle);
      [*] = ;                              isDead := GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;                              curUID := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;                              heroLevel := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;
      [*] = ;                              if (not isDead) and (curUID = dummyUID) then
      [*] = ;                              newTaste := newTaste + heroLevel div 2;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     18, 23 : // undead uprising, demon invasion
      [*] = ;                     begin
      [*] = ;                        if (provPlHandle <> myPlHandle) and (provPlHandle <> 0) then
      [*] = ;                        begin
      [*] = ;                           newTaste := (goldIncome + gemIncome * 2) div 8;
      [*] = ;
      [*] = ;                           if resID > 0 then
      [*] = ;                           newTaste := newTaste + 3;
      [*] = ;
      [*] = ;                           if isCastle then
      [*] = ;                           newTaste := newTaste + 10;
      [*] = ;
      [*] = ;                           if (not isGuarded) or (defPower < 2) then
      [*] = ;                           newTaste := newTaste * 3;
      [*] = ;
      [*] = ;                           if (treaty = gc_TreatyWar) and (canKill < 0) then
      [*] = ;                           newTaste := newTaste * 4;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     19 : // gifts of heaven
      [*] = ;                     begin
      [*] = ;                        newTaste := 50 - mood * 2;
      [*] = ;                     end;
      [*] = ;                     21 : // tower of lightning
      [*] = ;                     begin
      [*] = ;                        newTaste := Floor(RandomExt * 30);
      [*] = ;
      [*] = ;                        var terrain : String = ParserGetValueByKeyByHandle(pProvince, 'Terrain');
      [*] = ;                        StringRegister0 := terrain;
      [*] = ;                        StateMachineExecuteState(initMachine, 'GetTerrainParserByName', 0);
      [*] = ;                        var pTerrain : Integer = IntRegister1;
      [*] = ;                        var terType : Integer = ParserGetIntValueByKeyByHandle(pTerrain, 'TerrainID');
      [*] = ;
      [*] = ;                        if terType = 4 then
      [*] = ;                        newTaste := newTaste + 10;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if bImprovedAI then
      [*] = ;                     newTaste := newTaste + Max(0, newTaste) * ritKarma * plKarma div 100;
      [*] = ;
      [*] = ;                  if newTaste > taste then
      [*] = ;                  begin
      [*] = ;                     taste := newTaste;
      [*] = ;                     ritualID := ritID;
      [*] = ;                     tProvince := pProvince;
      [*] = ;                     heroUID := newHeroUID;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ritualID > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := tProvince;
      [*] = ;      IntRegister1 := ritualID;
      [*] = ;      IntRegister2 := heroUID;
      [*] = ;      ExecuteState('CastRitual');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

