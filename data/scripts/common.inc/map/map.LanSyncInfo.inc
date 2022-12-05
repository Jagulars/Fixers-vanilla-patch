section.begin
   Name = map.LanSyncInfo
   Description : struct.begin
      [*] = ;IntRegister0 - sync parser
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\MAP\MAP.LANSYNCINFO';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var pSyncParser : Integer = IntRegister0;
      [*] = ;var pSyncPlayers : Integer = ParserSelectByHandleByKey(pSyncParser, 'Players');
      [*] = ;var pSyncGame : Integer = ParserSelectByHandleByKey(pSyncParser, 'Game');
      [*] = ;var pSyncConflicts : Integer = ParserSelectByHandleByKey(pSyncParser, 'Conflicts');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if _log then _Log_Map('[map.LanSyncInfo] execute');
      [*] = ;
      [*] = ;procedure GetConflictInfoFromParser(pParser : Integer);
      [*] = ;begin
      [*] = ;   var plInd : Integer = ParserGetIntValueByKeyByHandle(pParser, 'Player');
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;
      [*] = ;   if plHandle <> 0 then
      [*] = ;   begin
      [*] = ;      var gold : Integer = ParserGetIntValueByKeyByHandle(pParser, 'Gold');
      [*] = ;      var gem : Integer = ParserGetIntValueByKeyByHandle(pParser, 'Gem');
      [*] = ;
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, gold);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, gem);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pHero : Integer = ParserSelectByHandleByKey(pParser, 'Hero');
      [*] = ;   var heroInd : Integer = ParserGetIntValueByKeyByHandle(pHero, 'Index');
      [*] = ;   if (plHandle <> 0) and (heroInd >= 0) then
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(plHandle, heroInd);
      [*] = ;      var dead : Boolean = ParserGetBoolValueByKeyByHandle(pHero, 'Dead');
      [*] = ;      if dead then
      [*] = ;      begin
      [*] = ;         IntRegister0 := goHandle;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         BoolRegister1 := true;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'KillHero');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := pHero;
      [*] = ;         IntRegister1 := 1;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'LoadInfoFromParser');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;for i := 0 to ParserGetCountByHandle(pSyncPlayers)-1 do
      [*] = ;begin
      [*] = ;   var pSyncPlayer : Integer = ParserSelectByHandleByIndex(pSyncPlayers, i);
      [*] = ;   var plIndex : Integer = ParserGetIntValueByKeyByHandle(pSyncPlayer, 'Player');
      [*] = ;
      [*] = ;   if plIndex <> gIntRegister_MapMyPlayerIndex then
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;      var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;      var heroCount : Integer = GetPlayerGameObjectsCountByHandle(plHandle);
      [*] = ;
      [*] = ;      // synchronize provinces
      [*] = ;      var pSyncProvinces : Integer = ParserSelectByHandleByKey(pSyncPlayer, 'Provinces');
      [*] = ;      for j := ParserGetCountByHandle(pSyncProvinces)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pSyncProvince : Integer = ParserSelectByHandleByIndex(pSyncProvinces, j);
      [*] = ;         var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pSyncProvince, 'DummyUID');
      [*] = ;         if dummyUID > 0 then
      [*] = ;         begin
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;            IntRegister0 := pSyncProvince;
      [*] = ;            IntRegister1 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'LoadInfoFromParser');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // synchronize attack rituals
      [*] = ;      var pSyncAttackRituals : Integer = ParserSelectByHandleByKey(pSyncPlayer, 'AttackRituals');
      [*] = ;      for j := ParserGetCountByHandle(pSyncAttackRituals)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pAttackRitual : Integer = ParserSelectByHandleByIndex(pSyncAttackRituals, j);
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, ParserGetIntValueByKeyByHandle(pAttackRitual, 'ProvinceIndex'));
      [*] = ;         var pCastedRituals : Integer = ParserSelectByHandleByKey(pProvince, 'CastedRituals');
      [*] = ;         var pOldRituals : Integer = ParserSelectByHandleByKey(pProvince, 'Rituals');
      [*] = ;
      [*] = ;         ParserAddChildByIndex(pCastedRituals, '*');
      [*] = ;         ParserCopyFromByHandle(pAttackRitual);
      [*] = ;
      [*] = ;         if _obj_EnabledByFlag(gc_ObjectFlagRitual) then
      [*] = ;         begin
      [*] = ;            var newRitualID : Integer = ParserGetIntValueByKeyByHandle(pAttackRitual, 'RitualID');
      [*] = ;            var found : Boolean = false;
      [*] = ;            for k := ParserGetCountByHandle(pOldRituals)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pOldRitual : Integer = ParserSelectByHandleByIndex(pOldRituals, k);
      [*] = ;               if ParserGetIntValueByKeyByHandle(pOldRitual, 'RitualID') = newRitualID then
      [*] = ;               begin
      [*] = ;                  found := true;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         
      [*] = ;            if not found then
      [*] = ;            for k := ParserGetCountByHandle(pCastedRituals)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pCastedRitual : Integer = ParserSelectByHandleByIndex(pCastedRituals, k);
      [*] = ;               if ParserGetIntValueByKeyByHandle(pCastedRitual, 'RitualID') = newRitualID then
      [*] = ;               begin
      [*] = ;                  found := true;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         
      [*] = ;            if not found then
      [*] = ;            begin
      [*] = ;               IntRegister0 := newRitualID;
      [*] = ;               GameObjectExecuteStateByHandle(GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID')), 'CreateRitualFX');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // synchronize player parser and stack
      [*] = ;      var pSyncPlParser : Integer = ParserSelectByHandleByKey(pSyncPlayer, 'PlayerParser');
      [*] = ;      ParserCopyToByHandle(pPlParser);
      [*] = ;
      [*] = ;      var pSyncPlStack : Integer = ParserSelectByHandleByKey(pSyncPlayer, 'PlayerStack');
      [*] = ;      for j := 0 to ParserGetCountByHandle(pSyncPlStack)-1 do
      [*] = ;         SetPlayerValueIndByHandle(plHandle, j, ParserGetValueByIndexByHandle(pSyncPlStack, j));
      [*] = ;
      [*] = ;      // synchronize heroes parser and stacks
      [*] = ;      var pSyncPlHeroes : Integer = ParserSelectByHandleByKey(pSyncPlayer, 'Heroes');
      [*] = ;      for j := 0 to ParserGetCountByHandle(pSyncPlHeroes)-1 do
      [*] = ;      begin
      [*] = ;         var pSyncPlHero : Integer = ParserSelectByHandleByIndex(pSyncPlHeroes, j);
      [*] = ;         var pSyncHeroStack : Integer = ParserSelectByHandleByKey(pSyncPlHero, 'Stack');
      [*] = ;         var hClass : Integer = ParserGetIntValueByIndexByHandle(pSyncHeroStack, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;         //var uid : Integer = ParserGetIntValueByKeyByHandle(pSyncPlHero, 'UID');
      [*] = ;         var uid : Integer = ParserGetIntValueByIndexByHandle(pSyncHeroStack, gc_map_GOStack_MapUnit_iUID);
      [*] = ;
      [*] = ;         var goHandle : Integer = 0;
      [*] = ;         for k := 0 to heroCount-1 do
      [*] = ;         begin
      [*] = ;            var goHandle1 : Integer = GetGameObjectHandleByIndex(k, plHandle);
      [*] = ;            var goUID : Integer = GetGameObjectIntValueIndByHandle(goHandle1, gc_map_GOStack_MapUnit_iUID);
      [*] = ;            var goClass : Integer = GetGameObjectIntValueIndByHandle(goHandle1, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;            if (goUID = uid) then
      [*] = ;            begin
      [*] = ;               if (goClass = hClass) then
      [*] = ;               begin
      [*] = ;                  goHandle := goHandle1;
      [*] = ;                  break;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  ErrorLogI('COMMON: map.LanSyncInfo - UIDS are same ['+IntToStr(uid)+'] but classes differ '+IntToStr(goClass)+' and '+IntToStr(hClass));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if goHandle = 0 then // another human player has recruited a new hero, must be done on recipient's computer as well
      [*] = ;         begin
      [*] = ;            if _log then _log_lan('['+_log_name+'] Recruit hero for another player');
      [*] = ;            IntRegister0 := hClass;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'RecruitHero');
      [*] = ;            goHandle := GetGameObjectHandleByIndex(GetPlayerGameObjectsCountByHandle(plHandle)-1, plHandle);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if goHandle <> 0 then // load info for the new hero or the existing hero
      [*] = ;         begin
      [*] = ;            IntRegister0 := pSyncPlHero;
      [*] = ;            IntRegister1 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'LoadInfoFromParser');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // synchronize dead heroes
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         var uid : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iUID);
      [*] = ;         var hClass : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;
      [*] = ;         var permaDead : Boolean = true;
      [*] = ;         for k := ParserGetCountByHandle(pSyncPlHeroes)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSyncPlHero : Integer = ParserSelectByHandleByIndex(pSyncPlHeroes, k);
      [*] = ;            var pSyncHeroStack : Integer = ParserSelectByHandleByKey(pSyncPlHero, 'Stack');
      [*] = ;            var hClass1 : Integer = ParserGetIntValueByIndexByHandle(pSyncHeroStack, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;            //var uid1 : Integer = ParserGetIntValueByKeyByHandle(pSyncPlHero, 'UID');
      [*] = ;            var uid1 : Integer = ParserGetIntValueByIndexByHandle(pSyncHeroStack, gc_map_GOStack_MapUnit_iUID);
      [*] = ;            var buried : Boolean = ParserGetBoolValueByIndexByHandle(pSyncHeroStack, gc_map_GOStack_MapUnit_bBuried);
      [*] = ;
      [*] = ;            if (hClass1 = hClass) and (uid1 = uid) and (not buried) then
      [*] = ;            begin
      [*] = ;               permaDead := false;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if permaDead then
      [*] = ;         begin
      [*] = ;            IntRegister0 := goHandle;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            BoolRegister1 := true;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'KillHero');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // synchronize res prices
      [*] = ;      var pSyncResPrices : Integer = ParserSelectByHandleByKey(pSyncGame, 'ResPrices'); // parser from server
      [*] = ;
      [*] = ;      var pSyncPlGame : Integer = ParserSelectByHandleByKey(pSyncPlayer, 'Game');
      [*] = ;      var pSyncPlResPrices : Integer = ParserSelectByHandleByKey(pSyncPlGame, 'ResPrices'); // my parser
      [*] = ;
      [*] = ;      for j := ParserGetCountByHandle(pSyncResPrices)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var serverPrice : Integer = ParserGetIntValueByIndexByHandle(pSyncResPrices, j);
      [*] = ;         var price : Integer = ParserGetIntValueByIndexByHandle(pSyncPlResPrices, j);
      [*] = ;
      [*] = ;         gGame.resPrices[j] := gGame.resPrices[j] + price - serverPrice;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // create a new array where the diplomacy is sorted
      [*] = ;      var oldArrDiplomacy : array [0..gc_MaxMapPlayers] of array [0..gc_MaxMapPlayers] of TDiplomacy;//TDiplomacy[gc_MaxMapPlayers][gc_MaxMapPlayers];
      [*] = ;      var pSyncDiplomacy : Integer = ParserSelectByHandleByKey(pSyncPlayer, 'Diplomacy');
      [*] = ;
      [*] = ;      for j := 0 to gGame.map.players-1 do
      [*] = ;         for k := 0 to gGame.map.players-1 do
      [*] = ;            _diplomacy_AssignDiplomacy(gArrDiplomacy[j][k], oldArrDiplomacy[j][k]); // store old diplomacy
      [*] = ;
      [*] = ;      _diplomacy_UnpackFromParser(gGame.map.players,pSyncDiplomacy); // unpacks to gArrDiplomacy
      [*] = ;
      [*] = ;      for j := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         //if (j <> gIntRegister_MapMyPlayerIndex) then // update other players' diplomacy
      [*] = ;         //begin
      [*] = ;            _diplomacy_AssignDiplomacy(gArrDiplomacy[plIndex][j], oldArrDiplomacy[plIndex][j]);
      [*] = ;            if SameText(GetPlayerControlModeByHandle(GetPlayerHandleByIndex(j)), 'cmPC') then // no need to protect AI players from diplomacy override
      [*] = ;               _diplomacy_AssignDiplomacy(gArrDiplomacy[j][plIndex], oldArrDiplomacy[j][plIndex]);
      [*] = ;         //end
      [*] = ;         //else // from me to someone else
      [*] = ;         //begin
      [*] = ;            //if not oldArrDiplomacy[j][plIndex].lanAnswer then
      [*] = ;           // begin
      [*] = ;            //   _diplomacy_AssignDiplomacy(gArrDiplomacy[plIndex][j], oldArrDiplomacy[plIndex][j]);
      [*] = ;            //   _diplomacy_AssignDiplomacy(gArrDiplomacy[j][plIndex], oldArrDiplomacy[j][plIndex]);
      [*] = ;           // end;
      [*] = ;        // end
      [*] = ;      end;
      [*] = ;
      [*] = ;      for j := 0 to gGame.map.players-1 do
      [*] = ;         for k := 0 to gGame.map.players-1 do
      [*] = ;            _diplomacy_AssignDiplomacy(oldArrDiplomacy[j][k], gArrDiplomacy[j][k]); // add the changes
      [*] = ;   end;
      [*] = ;   //else
      [*] = ;   begin
      [*] = ;      if ParserGetIntValueByKeyByHandle(ParserSelectByHandleByKey(pSyncPlayer, 'PlayerParser'), 'Surrender') <> 0 then
      [*] = ;      begin
      [*] = ;         if _log then _log_lan('map.LanSyncInfo, Surrender player index '+IntToStr(plIndex));
      [*] = ;         BoolRegister0 := true;
      [*] = ;         PlayerExecuteStateByHandle(GetPlayerHandleByIndex(plIndex), 'CheckPlayerLose');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pSyncConflicts)-1 do
      [*] = ;begin
      [*] = ;   var pSyncConflict : Integer = ParserSelectByHandleByIndex(pSyncConflicts, i);
      [*] = ;   //var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pSyncConflict, 'DummyUID');
      [*] = ;   GetConflictInfoFromParser(ParserSelectByHandleByKey(pSyncConflict, 'Attack'));
      [*] = ;   GetConflictInfoFromParser(ParserSelectByHandleByKey(pSyncConflict, 'Defend'));
      [*] = ;end;
      [*] = ;
      [*] = ;var randKey0 : Integer = ParserGetIntValueByKeyByHandle(pSyncParser, 'RandKey0');
      [*] = ;var randKey1 : Integer = ParserGetIntValueByKeyByHandle(pSyncParser, 'RandKey1');
      [*] = ;SetRandomExtKey64(randKey0, randKey1);
      [*] = ;SetMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;SetGlobalMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;
      [*] = ;// save/load
      [*] = ;gIntRegister_LanMapUID := ParserGetIntValueByKeyByHandle(pSyncParser, 'SaveMapKey');
      [*] = ;gStringRegister_LanMapSaveName := ParserGetValueByKeyByHandle(pSyncParser, 'SaveMapName');
      [*] = ;
      [*] = ;ParserClearByHandle(pSyncGame);
      [*] = ;ParserClearByHandle(pSyncPlayers);
      [*] = ;//ParserClearByHandle(pSyncConflicts);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

