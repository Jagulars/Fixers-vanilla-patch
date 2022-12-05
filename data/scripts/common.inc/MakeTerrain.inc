section.begin
   Name = MakeTerrain
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\MAKETERRAIN';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;TimeLog('Generating province data...');
      [*] = ;
      [*] = ;const cWaterOffset     = 0.7;
      [*] = ;const cPatternPlName   = 'pattern';
      [*] = ;const cPatternPlRace   = 'nature';
      [*] = ;const cProvincePlName  = 'prov.pattern';
      [*] = ;const cProvincePlRace  = 'buildings';
      [*] = ;const cDummyPlName     = 'province.dummy';
      [*] = ;const cDummyPlRace     = 'map.province';
      [*] = ;const cPlayerRace      = 'map.unit';
      [*] = ;const cDummyGOBaseName = 'map.province';
      [*] = ;const cOuterPatPlName  = 'plOuterBuild';
      [*] = ;const cParticlePlName  = 'particles';
      [*] = ;const cParticlePlRace  = 'misc';
      [*] = ;
      [*] = ;const cMaxMountainTryCount = 2000;
      [*] = ;const cMaxProvCount = 1000;
      [*] = ;const cSmoothRadius = 5;
      [*] = ;const cSmoothPasses = 10;
      [*] = ;const cSmoothOffset = 3;
      [*] = ;const cDefCastleDist = -1;
      [*] = ;
      [*] = ;var i, j, k, l : Integer;
      [*] = ;
      [*] = ;// parser names
      [*] = ;var pProvinceTypes  : Integer;
      [*] = ;var pProvinceLevels : Integer;
      [*] = ;var pPrefixes       : Integer;
      [*] = ;var pSuffixes       : Integer;
      [*] = ;var pProvinceNames  : Integer;
      [*] = ;var pTerrainTypes   : Integer;
      [*] = ;var pResources      : Integer;
      [*] = ;var pSites          : Integer;
      [*] = ;var pRaces          : Integer;
      [*] = ;//var pUnits          : Integer;
      [*] = ;var pGuardTypes     : Integer;
      [*] = ;var pGuards         : Integer;
      [*] = ;var pDefenders      : Integer;
      [*] = ;var pQuests         : Integer;
      [*] = ;var pOuterBuildings : Integer;
      [*] = ;var pRituals        : Integer;
      [*] = ;
      [*] = ;var avProvinceSize : Float = 0;
      [*] = ;var pResourceCount : Integer;
      [*] = ;
      [*] = ;// TODO: hack for curGame.Seed = 0 (same hack as in original Eador)
      [*] = ;if gGame.seed = 0 then
      [*] = ;begin
      [*] = ;   var randKey0, randKey1 : Integer;
      [*] = ;   GenerateMapRandKey(randKey0, randKey1);
      [*] = ;   if _log then _Log_map(_log_name+' randKey0 = '+IntToStr(randKey0)+' randKey1 = '+IntToStr(randKey1));
      [*] = ;   gGame.seed := randKey1 mod gc_MaxSeedValue;
      [*] = ;end;
      [*] = ;
      [*] = ;var curGamePlayerSet : array[0..gc_MaxMapPlayers-1] of Integer; // Список игроков, установленных при старте игры
      [*] = ;var arrProvinces : array [0..cMaxProvCount] of Integer;
      [*] = ;
      [*] = ;function IsFreePlayerID(id : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := true;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      if (id = curGamePlayerSet[i]) then
      [*] = ;      begin
      [*] = ;         Result := false;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function FindUniqueRandomPlayerID : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   ArrayClear;
      [*] = ;
      [*] = ;   for i := 1 to gc_MaxMapPlayers do
      [*] = ;   begin
      [*] = ;      if IsFreePlayerID(i) then
      [*] = ;      ArrayPushValue(i);
      [*] = ;   end;
      [*] = ;   if (ArrayGetCount > 0) then
      [*] = ;   begin
      [*] = ;      var ind : Integer = _rand_Random(ArrayGetCount);
      [*] = ;      Result := ArrayGetValueByIndex(ind);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   ErrorLog('availableCount=0');
      [*] = ;end;
      [*] = ;
      [*] = ;// world rule checkers
      [*] = ;var bWorldRuleAbilityExist12 : Boolean = _worldrule_GetWorldRuleAbilityExistByID(12);
      [*] = ;
      [*] = ;// world rule
      [*] = ;if (_worldrule_GetWorldRuleAbilityExistByID(10)) then
      [*] = ;begin
      [*] = ;   var pWorldRule : Integer = _worldrule_GetWorldRuleParser();
      [*] = ;   var pWorldRuleAbilities : Integer = ParserSelectByHandleByKey(pWorldRule, 'Abilities');
      [*] = ;   var j : Integer;
      [*] = ;   for j:=0 to ParserGetCountByHandle(pWorldRuleAbilities)-1 do
      [*] = ;   begin
      [*] = ;      var pWorldRuleAbility : Integer = ParserSelectByHandleByIndex(pWorldRuleAbilities, j);
      [*] = ;      var abilityID : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'AbilityID');
      [*] = ;      if (abilityID=10) then
      [*] = ;      begin
      [*] = ;         var param1 : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'Param1');
      [*] = ;         var param2 : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'Param2');
      [*] = ;         case param1 of
      [*] = ;            1 : gGame.map.water := round((gGame.map.water*param2)/100);
      [*] = ;            2 : gGame.map.hill := round((gGame.map.hill*param2)/100);
      [*] = ;            3 : gGame.map.forest := round((gGame.map.forest*param2)/100);
      [*] = ;            4 : gGame.map.swamp := round((gGame.map.swamp*param2)/100);
      [*] = ;            5 : gGame.map.desert := round((gGame.map.desert*param2)/100);
      [*] = ;            6 : gGame.map.deadLand := round((gGame.map.deadLand*param2)/100);
      [*] = ;            7 : gGame.map.isles := round((gGame.map.isles*param2)/100);
      [*] = ;            8 : gGame.map.dissolve := round((gGame.map.dissolve*param2)/100);
      [*] = ;            9 : gGame.map.neutrals := round((gGame.map.neutrals*param2)/100);
      [*] = ;            10 : gGame.map.resource := round((gGame.map.resource*param2)/100);
      [*] = ;            11 : gGame.map.site := round((gGame.map.site*param2)/100);
      [*] = ;            12 : gGame.map.population := round((gGame.map.population*param2)/100);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var curVisualID : Integer = 0;
      [*] = ;if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;   curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;
      [*] = ;var pProfile : Integer = 0;
      [*] = ;if (gGame.gameType = gc_GameTypeCampaign) and (gIntRegister_CampAttackPlayer >= 0) and (gIntRegister_CampDefendPlayer >= 0) and (not gCampaign.defender) then
      [*] = ;begin
      [*] = ;   pProfile := ParserSelectByHandleByIndex(gPrototypeData.players.handle, gIntRegister_CampDefendPlayer);
      [*] = ;   var landType : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'LandType');
      [*] = ;   var landPoss : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'LandPoss');
      [*] = ;
      [*] = ;   case landType of
      [*] = ;      2 : begin
      [*] = ;         gGame.map.forest := gGame.map.forest + landPoss;
      [*] = ;         if gGame.map.forest + gGame.map.hill + gGame.map.swamp > 90 then
      [*] = ;            gGame.map.forest := 90 - gGame.map.hill - gGame.map.swamp;
      [*] = ;      end;
      [*] = ;      3 : begin
      [*] = ;         gGame.map.hill := gGame.map.hill + landPoss;
      [*] = ;         if gGame.map.forest + gGame.map.hill + gGame.map.swamp > 90 then
      [*] = ;            gGame.map.hill := 90 - gGame.map.forest - gGame.map.swamp;
      [*] = ;      end;
      [*] = ;      4 : begin
      [*] = ;         gGame.map.swamp := gGame.map.swamp + landPoss;
      [*] = ;         if gGame.map.forest + gGame.map.hill + gGame.map.swamp > 90 then
      [*] = ;            gGame.map.swamp := 90 - gGame.map.forest - gGame.map.hill;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var mapPlayers    : Integer = gGame.map.players;
      [*] = ;var mapX          : Integer = gGame.map.x;
      [*] = ;var mapY          : Integer = gGame.map.y;
      [*] = ;var mapWater      : Integer = gGame.map.water;
      [*] = ;var mapHill       : Integer = gGame.map.hill;
      [*] = ;var mapForest     : Integer = gGame.map.forest;
      [*] = ;var mapSwamp      : Integer = gGame.map.swamp;
      [*] = ;var mapDesert     : Integer = gGame.map.desert;
      [*] = ;var mapDeadLand   : Integer = gGame.map.deadLand;
      [*] = ;var mapIsles      : Integer = gGame.map.isles;
      [*] = ;var mapDissolve   : Integer = gGame.map.dissolve;
      [*] = ;var mapNeutrals   : Integer = gGame.map.neutrals;
      [*] = ;var mapResource   : Integer = gGame.map.resource;
      [*] = ;var mapSite       : Integer = gGame.map.site;
      [*] = ;var mapPopulation : Integer = gGame.map.population;
      [*] = ;
      [*] = ;var activeShard : Integer = gCampaign.activeShard;
      [*] = ;var campDiff : Integer = gCampaign.difficulty;
      [*] = ;
      [*] = ;ClearPlayers;
      [*] = ;
      [*] = ;for i := 0 to mapPlayers-1 do
      [*] = ;begin
      [*] = ;   var cMode : String;
      [*] = ;
      [*] = ;   if i = 0 then
      [*] = ;      cMode := 'cmPlayer'
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case gGame.gameType of
      [*] = ;         gc_GameTypeCustom, gc_GameTypeCampaign : begin
      [*] = ;            cMode := 'cmPC';
      [*] = ;         end;
      [*] = ;         gc_GameTypeHotseat, gc_GameTypeLanShard : begin
      [*] = ;            if gGame.arrPlayerControl[i] = 0 then
      [*] = ;               cMode := 'cmPC'
      [*] = ;            else
      [*] = ;               cMode := 'cmPlayer';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var plName : String = 'Player.' + IntToStr(i);
      [*] = ;   var plHandle : Integer = CreatePlayer(plName, cPlayerRace, cMode);
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'Initial');
      [*] = ;end;
      [*] = ;
      [*] = ;_diplomacy_InitAllDiplomacy();
      [*] = ;
      [*] = ;var patPlHandle : Integer = CreatePlayer(cPatternPlName, cPatternPlRace, 'cmNone');
      [*] = ;var provincePlHandle : Integer = CreatePlayer(cProvincePlName, cProvincePlRace, 'cmNone');
      [*] = ;var dummyPlHandle : Integer = CreatePlayer(cDummyPlName, cDummyPlRace, 'cmPC');
      [*] = ;var particlePlHandle : Integer = GetPlayerHandleByName(cParticlePlName);
      [*] = ;if (particlePlHandle<>0) then
      [*] = ;DeletePlayerByHandle(particlePlHandle);
      [*] = ;particlePlHandle := CreatePlayer(cParticlePlName, cParticlePlRace, 'cmPC'); //cmPC to progress state machine
      [*] = ;
      [*] = ;var machineHandle : Integer = GetMapInitMachineHandle();
      [*] = ;var pMachineParser : Integer = ParserSelectStateMachineByHandle(machineHandle);
      [*] = ;if pMachineParser = 0 then
      [*] = ;   pMachineParser := ParserCreateStateMachineByHandle(machineHandle);
      [*] = ;
      [*] = ;var iFloodDeep : Integer;
      [*] = ;var ZoneCount, MaxZoneCount : Integer;
      [*] = ;var MaxMountainCount : Integer = 0;
      [*] = ;
      [*] = ;var pGridVertices : Integer = gGridVertices.handle;
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;var HexCount : Integer = ParserGetCountByHandle(pStratHexCells);
      [*] = ;
      [*] = ;// terrain type percents
      [*] = ;var WaterCount    : Integer = 0;
      [*] = ;var MountainCount : Integer = 0;
      [*] = ;var HillCount     : Integer = 0;
      [*] = ;var ForestCount   : Integer = 0;
      [*] = ;var SwampCount    : Integer = 0;
      [*] = ;var DesertCount   : Integer = 0;
      [*] = ;var DeadLandCount : Integer = 0;
      [*] = ;var PlainCount    : Integer = 0;
      [*] = ;
      [*] = ;var GridSize : Integer = _map_GetGridSize();
      [*] = ;
      [*] = ;var pPatternCover : Integer = gPatternCoverTerrainTypes.handle;
      [*] = ;
      [*] = ;// loading parsers
      [*] = ;
      [*] = ;pProvinceTypes := gPrototypeData.provinceTypes.handle;
      [*] = ;pProvinceLevels := gPrototypeData.provinceLevels.handle;
      [*] = ;pProvinceNames := gPrototypeData.provinceNames.handle;
      [*] = ;pPrefixes := gPrototypeData.prefixes.handle;
      [*] = ;pSuffixes := gPrototypeData.suffixes.handle;
      [*] = ;pTerrainTypes := gPrototypeData.terrainTypes.handle;
      [*] = ;pResources := gPrototypeData.resources.handle;
      [*] = ;pSites := gPrototypeData.sites.handle;
      [*] = ;pRaces := gPrototypeData.races.handle;
      [*] = ;//pUnits := gPrototypeData.units.handle;
      [*] = ;pGuardTypes := gPrototypeData.guardTypes.handle;
      [*] = ;pGuards := gPrototypeData.guards.handle;
      [*] = ;pDefenders := gPrototypeData.defenders.handle;
      [*] = ;pQuests := gPrototypeData.quests.handle;
      [*] = ;pOuterBuildings := gPrototypeData.outerbuildings.handle;
      [*] = ;pRituals := gPrototypeData.rituals.handle;
      [*] = ;
      [*] = ;procedure CopyVerticesToHexGrid;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := i;
      [*] = ;      ExecuteState('SetHexVertices');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function PutZoneSpot(index, radius : Integer; TerrainType : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   ArrayClear;
      [*] = ;   ArrayPushValue(index);
      [*] = ;
      [*] = ;   var j, g, k : Integer;
      [*] = ;   var curFreq : Float = radius;
      [*] = ;   var stepFreq : Float = 1;
      [*] = ;   var newCount : Integer = 0;
      [*] = ;   var pCurHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, index);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pCurHexCell, 'Freq', curFreq);
      [*] = ;   ParserSetIntValueByKeyByHandle(pCurHexCell, 'TerrainType', TerrainType);
      [*] = ;   Result := Result + 1;
      [*] = ;   ZoneCount := ZoneCount + 1;
      [*] = ;   if ZoneCount < MaxZoneCount then
      [*] = ;   begin
      [*] = ;      while [MAIN]ArrayGetCount > 0 do
      [*] = ;      begin
      [*] = ;         var arInd : Integer;
      [*] = ;         var ind : Integer;
      [*] = ;         var arCount : Integer = ArrayGetCount;
      [*] = ;         var freq : Float = 0;
      [*] = ;         var pCurHexCell : Integer;
      [*] = ;
      [*] = ;         repeat
      [*] = ;            //if newCount > 0 then
      [*] = ;            arInd := ArrayGetCount - 1 - _rand_Random(newCount);
      [*] = ;            //arInd := ArrayGetCount-1;
      [*] = ;            ind := ArrayGetValueByIndex(arInd);
      [*] = ;            pCurHexCell := ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;            freq := ParserGetFloatValueByKeyByHandle(pCurHexCell, 'Freq');
      [*] = ;            if freq <= 0 then
      [*] = ;            begin
      [*] = ;               if newCount > 0 then
      [*] = ;               newCount := newCount - 1;
      [*] = ;               ArrayDeleteItemByIndex(arInd);
      [*] = ;            end;
      [*] = ;         until (freq > 0) or (ArrayGetCount = 0);
      [*] = ;         curFreq := freq;
      [*] = ;
      [*] = ;         if ArrayGetCount = 0 then
      [*] = ;         break;
      [*] = ;
      [*] = ;         ParserSetFloatValueByKeyByHandle(pCurHexCell, 'Freq', curFreq);
      [*] = ;         ParserSetIntValueByKeyByHandle(pCurHexCell, 'TerrainType', TerrainType);
      [*] = ;         //Result := Result + 1;
      [*] = ;         var curX, curY, curZ : Float;
      [*] = ;         GetTrackNodePositionByIndex(ind, curX, curY, curZ);
      [*] = ;         newCount := 0;
      [*] = ;
      [*] = ;         for g := -1 to 1 do
      [*] = ;         begin
      [*] = ;            for k := -1 to 1 do
      [*] = ;            if (g <> 0) or (k <> 0) then
      [*] = ;            begin
      [*] = ;               var indNext : Integer = ind + g * GridSize + k;
      [*] = ;               if (indNext >= 0) and (indNext < HexCount) then
      [*] = ;               begin
      [*] = ;                  var nextX, nextY, nextZ : Float;
      [*] = ;                  GetTrackNodePositionByIndex(indNext, nextX, nextY, nextZ);
      [*] = ;                  var pNextHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, indNext);
      [*] = ;                  var nTerrainType : Integer = ParserGetIntValueByKeyByHandle(pNextHexCell, 'TerrainType');
      [*] = ;
      [*] = ;                  var dist : Float = VectorDistance(curX, 0, curZ, nextX, 0, nextZ);
      [*] = ;                  var aDist : Float = Sqrt(3) * gc_StratHexSize;
      [*] = ;                  var freq : Float = ParserGetFloatValueByKeyByHandle(pNextHexCell, 'Freq');
      [*] = ;
      [*] = ;                  if (freq = -1) and (dist < aDist + 0.1) and (nTerrainType = gc_PlainTerrainType) then
      [*] = ;                  begin
      [*] = ;                     if (RandomExt*iFloodDeep < curFreq) then
      [*] = ;                     begin
      [*] = ;                        ParserSetFloatValueByKeyByHandle(pNextHexCell, 'Freq', curFreq-stepFreq);
      [*] = ;                        ParserSetIntValueByKeyByHandle(pNextHexCell, 'TerrainType', TerrainType);
      [*] = ;                        Result := Result + 1;
      [*] = ;                        ArrayPushValue(indNext);
      [*] = ;                        newCount := newCount + 1;
      [*] = ;                        //Log('Inc water count');
      [*] = ;                        ZoneCount := ZoneCount + 1;
      [*] = ;                        if ZoneCount = MaxZoneCount then
      [*] = ;                        break(MAIN);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         ArrayDeleteItemByIndex(arInd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetMaskHex(const pMaskCell, centerInd : Integer; var indHexMask : Integer; var angle : Float);
      [*] = ;begin
      [*] = ;   var x : Float = ParserGetFloatValueByKeyByHandle(pMaskCell, 'XOffset');
      [*] = ;   var y : Float = ParserGetFloatValueByKeyByHandle(pMaskCell, 'YOffset');
      [*] = ;   var indMask : Integer;
      [*] = ;
      [*] = ;   if (x = 0) and (y = 0) then
      [*] = ;      indHexMask := centerInd
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var angle : Float;
      [*] = ;      if (x = -1) and (y = -1) then angle := -60;
      [*] = ;      if (x = -1) and (y = 0) then angle := 0;
      [*] = ;      if (x = -1) and (y = 1) then angle := 60;
      [*] = ;      if (x = 1) and (y = -1) then angle := -120;
      [*] = ;      if (x = 1) and (y = 0) then angle := 180;
      [*] = ;      if (x = 1) and (y = 1) then angle := 120;
      [*] = ;
      [*] = ;      indHexMask := _map_GetNeighbourHexIndexByAngle(centerInd, angle);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function MountainPatternAllowed(const pPattern, hexIndex : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   var pMask : Integer = ParserSelectByHandleByKey(pPattern, 'Mask');
      [*] = ;   var i, j, indHexMask : Integer;
      [*] = ;   var angle : Float;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pMask)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      GetMaskHex(ParserSelectByHandleByIndex(pMask, i), hexIndex, indHexMask, angle);
      [*] = ;      var terrainType : Integer = _map_GetHexNeighbourIntValueByAngle(hexIndex, angle, 'TerrainType');
      [*] = ;
      [*] = ;      if terrainType <> gc_PlainTerrainType then
      [*] = ;      begin
      [*] = ;         Result := False;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // ensure no other mountains or water adjacent
      [*] = ;      for j := 0 to 5 do
      [*] = ;      begin
      [*] = ;         angle := j * 60;
      [*] = ;         terrainType := _map_GetHexNeighbourIntValueByAngle(indHexMask, angle, 'TerrainType');
      [*] = ;         if terrainType <> gc_PlainTerrainType then
      [*] = ;         begin
      [*] = ;            Result := False;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AdjustVertices;
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   var dirX : Float = 0;
      [*] = ;   var dirY : Float = 0;
      [*] = ;   var dirZ : Float = 0;
      [*] = ;   var hexX, hexZ : Float;
      [*] = ;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   //for i := 0 to 2 * GridSize do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var pVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;      var myTerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;      var x : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;      var z : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;
      [*] = ;      if (myTerrainType = gc_WaterTerrainType) {or (myTerrainType = gc_MountainTerrainType)} then
      [*] = ;      begin
      [*] = ;         for j := 0 to 5 do
      [*] = ;         begin
      [*] = ;            var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, j);
      [*] = ;            var vIndex : Integer = _map_GetVertexIndex(i, j);
      [*] = ;            var pGridVertice : Integer = ParserSelectByHandleByIndex(pGridVertices, vIndex);
      [*] = ;
      [*] = ;            var xv : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;            var zv : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;            var angle1 : Float = j * 60;
      [*] = ;            var ind1 : Integer = _map_GetNeighbourHexIndexByAngle(i, angle1);
      [*] = ;            var pStratHexCell1 : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind1);
      [*] = ;            {IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := j;
      [*] = ;            ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;            var pStratHexCell1 : Integer = IntRegister2;
      [*] = ;            var ind1 : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell1, 'Index');}
      [*] = ;            var TerrainType1 : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell1, 'TerrainType');
      [*] = ;            var x1 : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell1, 'CenterX');
      [*] = ;            var z1 : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell1, 'CenterY');
      [*] = ;
      [*] = ;            var angle2 : Float = (j+1) * 60;
      [*] = ;            var ind2 : Integer = _map_GetNeighbourHexIndexByAngle(i, angle2);
      [*] = ;            var pStratHexCell2 : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind2);
      [*] = ;            {IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := j+1;
      [*] = ;            ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;            var pStratHexCell2 : Integer = IntRegister2;
      [*] = ;            var ind2 : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell2, 'Index');}
      [*] = ;            var TerrainType2 : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell2, 'TerrainType');
      [*] = ;            var x2 : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell2, 'CenterX');
      [*] = ;            var z2 : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell2, 'CenterY');
      [*] = ;
      [*] = ;            //if ((ind1 > -1) and (ind2 > -1)) or ((ind1 = -1) and (ind2 = -1)) then
      [*] = ;            begin
      [*] = ;               if (ind1 = -1) and (ind2 = -1) then
      [*] = ;               begin
      [*] = ;                  dirX := xv - x;
      [*] = ;                  dirZ := zv - z;
      [*] = ;                  hexX := x;
      [*] = ;                  hexZ := z;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (ind1 = -1) then
      [*] = ;               begin
      [*] = ;                  if TerrainType2 <> myTerrainType then
      [*] = ;                  begin
      [*] = ;                     dirX := xv - x;
      [*] = ;                     dirZ := zv - z;
      [*] = ;                     hexX := x;
      [*] = ;                     hexZ := z;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var dirX1 : Float = xv - x;
      [*] = ;                     var dirY1 : Float = 0;
      [*] = ;                     var dirZ1 : Float = zv - z;
      [*] = ;                     VectorNormalize(dirX1, dirY1, dirZ1);
      [*] = ;
      [*] = ;                     var dirX2 : Float = xv - x2;
      [*] = ;                     var dirY2 : Float = 0;
      [*] = ;                     var dirZ2 : Float = zv - z2;
      [*] = ;                     VectorNormalize(dirX2, dirY2, dirZ2);
      [*] = ;
      [*] = ;                     dirX := dirX1 + dirX2;
      [*] = ;                     dirZ := dirZ1 + dirZ2;
      [*] = ;
      [*] = ;                     hexX := xv + gc_StratHexSize * dirX;
      [*] = ;                     hexZ := zv + gc_StratHexSize * dirZ;
      [*] = ;
      [*] = ;                     //continue;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (ind2 = -1) then
      [*] = ;               begin
      [*] = ;                  if TerrainType1 <> myTerrainType then
      [*] = ;                  begin
      [*] = ;                     dirX := xv - x;
      [*] = ;                     dirZ := zv - z;
      [*] = ;                     hexX := x;
      [*] = ;                     hexZ := z;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var dirX1 : Float = xv - x;
      [*] = ;                     var dirY1 : Float = 0;
      [*] = ;                     var dirZ1 : Float = zv - z;
      [*] = ;                     VectorNormalize(dirX1, dirY1, dirZ1);
      [*] = ;
      [*] = ;                     var dirX2 : Float = xv - x1;
      [*] = ;                     var dirY2 : Float = 0;
      [*] = ;                     var dirZ2 : Float = zv - z1;
      [*] = ;                     VectorNormalize(dirX2, dirY2, dirZ2);
      [*] = ;
      [*] = ;                     dirX := dirX1 + dirX2;
      [*] = ;                     dirZ := dirZ1 + dirZ2;
      [*] = ;
      [*] = ;                     hexX := xv + gc_StratHexSize * dirX;
      [*] = ;                     hexZ := zv + gc_StratHexSize * dirZ;
      [*] = ;
      [*] = ;                     //continue;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (TerrainType1 <> myTerrainType) and (TerrainType2 <> myTerrainType) then
      [*] = ;               begin
      [*] = ;                  dirX := xv - x;
      [*] = ;                  dirZ := zv - z;
      [*] = ;                  hexX := x;
      [*] = ;                  hexZ := z;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (TerrainType1 = myTerrainType) and (TerrainType2 <> myTerrainType) then
      [*] = ;               begin
      [*] = ;                  dirX := xv - x2;
      [*] = ;                  dirZ := zv - z2;
      [*] = ;                  hexX := x2;
      [*] = ;                  hexZ := z2;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (TerrainType1 <> myTerrainType) and (TerrainType2 = myTerrainType) then
      [*] = ;               begin
      [*] = ;                  dirX := xv - x1;
      [*] = ;                  dirZ := zv - z1;
      [*] = ;                  hexX := x1;
      [*] = ;                  hexZ := z1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               continue;
      [*] = ;
      [*] = ;               VectorNormalize(dirX, dirY, dirZ);
      [*] = ;
      [*] = ;               var bHex : Boolean = false;
      [*] = ;               var bVertex : Boolean = false;
      [*] = ;
      [*] = ;               // new
      [*] = ;               bHex := _map_IsTerrainType(hexX, hexZ, myTerrainType);
      [*] = ;               bVertex := _map_IsTerrainType(xv, zv, myTerrainType);
      [*] = ;               //Log('Game objects inside hex = ' + BoolToStr(bVertex));
      [*] = ;               // new
      [*] = ;
      [*] = ;               while (not (bHex xor bVertex)) and (xv > -GetMapWidth div 2) and (xv < GetMapWidth div 2) and
      [*] = ;               (zv > -GetMapHeight div 2) and (zv < GetMapHeight div 2) do
      [*] = ;               begin
      [*] = ;                  xv := xv + dirX;
      [*] = ;                  zv := zv + dirZ;
      [*] = ;                  bHex := _map_IsTerrainType(hexX, hexZ, myTerrainType);
      [*] = ;                  bVertex := _map_IsTerrainType(xv, zv, myTerrainType);
      [*] = ;                  //Log('New position: (' + FloatToStr(xv) + ', ' + FloatToStr(zv) + ')');
      [*] = ;                  //Log('Game objects = ' + BoolToStr(bVertex));
      [*] = ;               end;
      [*] = ;
      [*] = ;               //Log('Hex position: (' + FloatToStr(hexX) + ', ' + FloatToStr(hexZ) + ')');
      [*] = ;               //Log('Vertex position: (' + FloatToStr(xv) + ', ' + FloatToStr(zv) + ')');
      [*] = ;
      [*] = ;               if (xv > -GetMapWidth div 2) and (xv < GetMapWidth div 2) and
      [*] = ;               (zv > -GetMapHeight div 2) and (zv < GetMapHeight div 2) then
      [*] = ;               begin
      [*] = ;                  var waterX, waterZ : Float;
      [*] = ;                  var terX, terZ : Float;
      [*] = ;
      [*] = ;                  if _map_IsTerrainType(hexX, hexZ, myTerrainType) then
      [*] = ;                  begin
      [*] = ;                     waterX := hexX;
      [*] = ;                     waterZ := hexZ;
      [*] = ;                     terX := xv;
      [*] = ;                     terZ := zv;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     terX := hexX;
      [*] = ;                     terZ := hexZ;
      [*] = ;                     waterX := xv;
      [*] = ;                     waterZ := zv;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  var newX, newZ : Float;
      [*] = ;
      [*] = ;                  _map_GetShorePosition(terX, terZ, waterX, waterZ);
      [*] = ;
      [*] = ;                  newX := (terX + waterX) / 2;
      [*] = ;                  newZ := (terZ + waterZ) / 2;
      [*] = ;                  //Log('Move (' + FloatToStr(x) + ', ' + FloatToStr(z) + ') to (' + FloatToStr(newX) + ', ' + FloatToStr(newZ) + ')');
      [*] = ;                  //Log('_______________________________________');
      [*] = ;                  ParserSetFloatValueByKeyByHandle(pGridVertice, 'X', newX);
      [*] = ;                  ParserSetFloatValueByKeyByHandle(pGridVertice, 'Y', newZ);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   CopyVerticesToHexGrid;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsHexAvailable(pStratHexCell : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if pStratHexCell <> 0 then
      [*] = ;   begin
      [*] = ;      var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;      Result := (TerrainType <> gc_WaterTerrainType) and (TerrainType <> gc_MountainTerrainType);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsHexWithResource(pStratHexCell : Integer) : Integer;
      [*] = ;begin
      [*] = ;   if pStratHexCell <> 0 then
      [*] = ;   begin
      [*] = ;      var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;
      [*] = ;      case TerrainType of
      [*] = ;         gc_WaterTerrainType, gc_MountainTerrainType : Result := 0;
      [*] = ;         gc_DesertTerrainType, gc_DeadLandTerrainType : Result := 1;
      [*] = ;         else Result := 2;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetTerrainTypeCount(cTerrainType : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   case cTerrainType of
      [*] = ;      gc_PlainTerrainType : Result := PlainCount;
      [*] = ;      gc_ForestTerrainType : Result := ForestCount;
      [*] = ;      gc_HillTerrainType : Result := HillCount;
      [*] = ;      gc_SwampTerrainType : Result := SwampCount;
      [*] = ;      gc_DesertTerrainType : Result := DesertCount;
      [*] = ;      gc_DeadLandTerrainType : Result := DeadLandCount;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetTerrainTypeCount(cTerrainType : Integer; count : Integer);
      [*] = ;begin
      [*] = ;   case cTerrainType of
      [*] = ;      gc_PlainTerrainType : PlainCount := count;
      [*] = ;      gc_ForestTerrainType : ForestCount := count;
      [*] = ;      gc_HillTerrainType : HillCount := count;
      [*] = ;      gc_SwampTerrainType : SwampCount := count;
      [*] = ;      gc_DesertTerrainType : DesertCount := count;
      [*] = ;      gc_DeadLandTerrainType : DeadLandCount := count;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetResourceInHex(pStratHexCell : Integer);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   var sum : Integer = 0;
      [*] = ;   var pSite : Integer;
      [*] = ;   var terrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;
      [*] = ;   IntRegister0 := terrainType;
      [*] = ;   ExecuteState('GetTerrainParserByID');
      [*] = ;   var pTerrainType : Integer = IntRegister1;
      [*] = ;   var sTerrainType : String = ParserGetValueByKeyByHandle(pTerrainType, 'Name');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pSites)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pSite := ParserSelectByHandleByIndex(pSites, i);
      [*] = ;      var pAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;      var f : Boolean;
      [*] = ;
      [*] = ;      for j := ParserGetCountByHandle(pAbilities)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pAbility : Integer = ParserSelectByHandleByIndex(pAbilities, j);
      [*] = ;         var baseRes : Boolean = ParserGetBoolValueByKeyByHandle(pSite, 'BaseResource');
      [*] = ;
      [*] = ;         var ability : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'AbilityID');
      [*] = ;         if baseRes and (ability = 1) then
      [*] = ;         begin
      [*] = ;            var pTerrainType : Integer = ParserSelectByHandleByKey(pSite, 'TerrainType');
      [*] = ;            var freq : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, sTerrainType);
      [*] = ;            sum := sum + freq;
      [*] = ;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if sum > 0 then
      [*] = ;   begin
      [*] = ;      var ind : Float = RandomExt * sum;
      [*] = ;      sum := 0;
      [*] = ;
      [*] = ;      var resInd : Integer;
      [*] = ;
      [*] = ;      for [MAIN]i := ParserGetCountByHandle(pSites)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pSite := ParserSelectByHandleByIndex(pSites, i);
      [*] = ;         var pAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;         var baseRes : Boolean = ParserGetBoolValueByKeyByHandle(pSite, 'BaseResource');
      [*] = ;         var f : Boolean;
      [*] = ;
      [*] = ;         if not baseRes then continue;
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pAbilities)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pAbility : Integer = ParserSelectByHandleByIndex(pAbilities, j);
      [*] = ;            var ability : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'AbilityID');
      [*] = ;            if ability = 1 then
      [*] = ;            begin
      [*] = ;               var pTerrainType : Integer = ParserSelectByHandleByKey(pSite, 'TerrainType');
      [*] = ;               var freq : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, sTerrainType);
      [*] = ;               sum := sum + freq;
      [*] = ;
      [*] = ;               if sum >= ind then
      [*] = ;               begin
      [*] = ;                  resInd := ParserGetIntValueByKeyByHandle(pAbility, 'Param1');
      [*] = ;                  break(MAIN);
      [*] = ;               end;
      [*] = ;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'Resource', resInd);
      [*] = ;      var pResource : Integer = ParserSelectByHandleByIndex(pResources, resInd);
      [*] = ;
      [*] = ;      var resName : String = ParserGetValueByKeyByHandle(pResource, 'Name');
      [*] = ;      var count : Integer = ParserGetIntValueByKeyByHandle(pResourceCount, resName);
      [*] = ;      count := count + 1;
      [*] = ;      ParserSetIntValueByKeyByHandle(pResourceCount, resName, count);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CalcDistancesToCastles(overSea : Boolean);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var castle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;
      [*] = ;      ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Checked', castle);
      [*] = ;
      [*] = ;      if castle then
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', 0)
      [*] = ;      else
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', cDefCastleDist);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var f : Boolean = true;
      [*] = ;   var curDist : Integer = 0;
      [*] = ;
      [*] = ;   while f do
      [*] = ;   begin
      [*] = ;      f := false;
      [*] = ;      for i := 0 to HexCount-1 do
      [*] = ;      begin
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;
      [*] = ;         if not IsHexAvailable(pStratHexCell) then
      [*] = ;         continue;
      [*] = ;
      [*] = ;         var checked : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Checked');
      [*] = ;         var t : Boolean = false;
      [*] = ;         if not checked then
      [*] = ;         begin
      [*] = ;            var dist : Integer = 10000;
      [*] = ;
      [*] = ;            for j := 0 to 5 do
      [*] = ;            begin
      [*] = ;               //var angle : Float = 60 * j;
      [*] = ;               //var ind : Integer = _map_GetNeighbourHexIndexByAngle(i, angle);
      [*] = ;               //var pNextStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;               IntRegister0 := pStratHexCell;
      [*] = ;               IntRegister1 := j;
      [*] = ;               ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;               var pNextStratHexCell : Integer = IntRegister2;
      [*] = ;
      [*] = ;               var nextChecked : Boolean = ParserGetBoolValueByKeyByHandle(pNextStratHexCell, 'Checked');
      [*] = ;
      [*] = ;               if IsHexAvailable(pNextStratHexCell) and nextChecked then
      [*] = ;               begin
      [*] = ;                  var nextDist : Integer = ParserGetIntValueByKeyByHandle(pNextStratHexCell, 'CastleDist');
      [*] = ;                  if (nextDist = curDist) and (nextDist + 1 < dist) then
      [*] = ;                  begin
      [*] = ;                     dist := nextDist + 1;
      [*] = ;                     f := true;
      [*] = ;                     t := true;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if t then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', dist);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Checked', true);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      curDist := curDist + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // increasing castle dist due to original Eador
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;
      [*] = ;      if IsHexAvailable(pStratHexCell) then
      [*] = ;      begin
      [*] = ;         var dist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'CastleDist');
      [*] = ;         if dist >= 0 then
      [*] = ;         dist := dist + 1
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if overSea then
      [*] = ;            dist := 8;
      [*] = ;         end;
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', dist);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure MakeHexArray(freeHexCount, minDist, castleCount : Integer);
      [*] = ;begin
      [*] = ;   var i, j, free : Integer;
      [*] = ;   ArrayClear();
      [*] = ;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;
      [*] = ;      var castleDist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'CastleDist');
      [*] = ;      if IsHexAvailable(pStratHexCell) and ((castleDist >= minDist) or ((castleDist = cDefCastleDist) and ((castleCount = 0) or (gGame.gameType <> gc_GameTypeCampaign)))) then
      [*] = ;      begin
      [*] = ;         free := 0;
      [*] = ;         for j := 0 to 5 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := j;
      [*] = ;            ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;            var pNextStratHexCell : Integer = IntRegister2;
      [*] = ;
      [*] = ;            if IsHexAvailable(pNextStratHexCell) then
      [*] = ;            free := free + 1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if free >= freeHexCount then
      [*] = ;            ArrayPushValue(i);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetRandomSiteByTerrainType(tType : String) : Integer;
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   var sum : Float = 0;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pSites)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pSite : Integer = ParserSelectByHandleByIndex(pSites, i);
      [*] = ;      if ParserGetIntValueByKeyByHandle(pSite, 'Place') > 0 then
      [*] = ;      begin
      [*] = ;         var pTerrainType : Integer = ParserSelectByHandleByKey(pSite, 'TerrainType');
      [*] = ;         var freq : Float = ParserGetFloatValueByKeyByHandle(pTerrainType, tType);
      [*] = ;         sum := sum + freq;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var randSum : Float = RandomExt * sum;
      [*] = ;   var pSite : Integer;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pSites)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pSite := ParserSelectByHandleByIndex(pSites, i);
      [*] = ;      if ParserGetIntValueByKeyByHandle(pSite, 'Place') > 0 then
      [*] = ;      begin
      [*] = ;         var pTerrainType : Integer = ParserSelectByHandleByKey(pSite, 'TerrainType');
      [*] = ;         var freq : Float = ParserGetFloatValueByKeyByHandle(pTerrainType, tType);
      [*] = ;         randSum := randSum - freq;
      [*] = ;
      [*] = ;         if randSum <= 0 then
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := i;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetRandomGuardTypeBySiteParser(pSite : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var sum : Float = 0;
      [*] = ;   var pSiteGuards : Integer = ParserSelectByHandleByKey(pSite, 'Guards');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pSiteGuards)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pSiteGuard : Integer = ParserSelectByHandleByIndex(pSiteGuards, i);
      [*] = ;      var guardID : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'Guard');
      [*] = ;      var freq : Float = ParserGetFloatValueByKeyByHandle(pSiteGuard, 'Possibility');
      [*] = ;      sum := sum + freq;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var randSum : Float = RandomExt * sum;
      [*] = ;   var guardID : Integer;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pSiteGuards)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pSiteGuard : Integer = ParserSelectByHandleByIndex(pSiteGuards, i);
      [*] = ;      guardID := ParserGetIntValueByKeyByHandle(pSiteGuard, 'Guard');
      [*] = ;      var freq : Float = ParserGetFloatValueByKeyByHandle(pSiteGuard, 'Possibility');
      [*] = ;      randSum := randSum - freq;
      [*] = ;
      [*] = ;      if randSum <= 0 then
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := guardID;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoGenerateClouds();
      [*] = ;begin
      [*] = ;   var plCloudHnd : Integer = 0;
      [*] = ;
      [*] = ;   const goBaseName = 'clouds';
      [*] = ;   const plCloudName = 'clouds';
      [*] = ;   const plCloudRace = 'misc';
      [*] = ;
      [*] = ;   plCloudHnd := GetPlayerHandleByName(plCloudName);
      [*] = ;   if (plCloudHnd=0) then
      [*] = ;      plCloudHnd := CreatePlayer(plCloudName, plCloudRace, 'cmPC')
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (SameText(GetPlayerRaceNameByHandle(plCloudHnd), plCloudRace)) then
      [*] = ;      begin
      [*] = ;         const sectorStep = 12;
      [*] = ;
      [*] = ;         ClearPlayerGameObjectsByHandle(plCloudHnd);
      [*] = ;
      [*] = ;         var sectorCountWidth : Integer = (GetMapWidth div sectorStep);
      [*] = ;         var sectorCountHeight : Integer = (GetMapHeight div sectorStep);
      [*] = ;
      [*] = ;         var iw, ih : Integer;
      [*] = ;         for iw:=0 to sectorCountWidth-1 do
      [*] = ;         begin
      [*] = ;            for ih:=0 to sectorCountHeight-1 do
      [*] = ;            begin
      [*] = ;               if (RandomExt>0.5) then
      [*] = ;               begin
      [*] = ;                  var x : Float = ((iw*sectorStep)+RandomExt*sectorStep) - (GetMapWidth div 2);
      [*] = ;                  var y : Float = 8;
      [*] = ;                  var z : Float = ((ih*sectorStep)+RandomExt*sectorStep) - (GetMapHeight div 2);
      [*] = ;                  var goCloudHnd : Integer = CreatePlayerGameObjectHandleByHandle(plCloudHnd, plCloudRace, goBaseName, x, y, z);
      [*] = ;                  if (GetGameObjectIntValueByHandle(goCloudHnd, 'sat')=0) then
      [*] = ;                  GameObjectExecuteStateByHandle(goCloudHnd, 'doRandom');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure MakeCastleName(pStratHexCell : Integer);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;
      [*] = ;   var myTerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   var myProvinceType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;   var sum : Float = 0;
      [*] = ;
      [*] = ;   ArrayClear();
      [*] = ;   for i := ParserGetCountByHandle(pProvinceNames)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvinceName : Integer = ParserSelectByHandleByIndex(pProvinceNames, i);
      [*] = ;      var pTerrainTypes  : Integer = ParserSelectByHandleByKey(pProvinceName, 'TerrainList');
      [*] = ;      var pProvinceTypes : Integer = ParserSelectByHandleByKey(pProvinceName, 'ProvinceTypeList');
      [*] = ;
      [*] = ;      var bTerrain  : Boolean = false;
      [*] = ;      var bProvince : Boolean = false;
      [*] = ;
      [*] = ;      for j := 0 to ParserGetCountByHandle(pTerrainTypes)-1 do
      [*] = ;      begin
      [*] = ;         var pTerrainType : Integer = ParserSelectByHandleByIndex(pTerrainTypes, j);
      [*] = ;         var tType : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, 'TerrainType');
      [*] = ;
      [*] = ;         if (myTerrainType = tType) or (tType = 0) then
      [*] = ;         begin
      [*] = ;            bTerrain := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for j := 0 to ParserGetCountByHandle(pProvinceTypes)-1 do
      [*] = ;      begin
      [*] = ;         var pProvinceType : Integer = ParserSelectByHandleByIndex(pProvinceTypes, j);
      [*] = ;         var prType : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'ProvinceType');
      [*] = ;
      [*] = ;         if (myProvinceType = prType) or (prType = 0) then
      [*] = ;         begin
      [*] = ;            bProvince := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if bTerrain and bProvince then
      [*] = ;      begin
      [*] = ;         var freq : Float = ParserGetFloatValueByKeyByHandle(pProvinceName, 'Rarity');
      [*] = ;         sum := sum + freq;
      [*] = ;         ArrayPushValue(i);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ArrayGetCount > 0 then
      [*] = ;   begin
      [*] = ;      var randSum : Float = RandomExt * sum;
      [*] = ;
      [*] = ;      for i := 0 to ArrayGetCount-1 do
      [*] = ;      begin
      [*] = ;         var ind : Integer = ArrayGetValueByIndex(i);
      [*] = ;         var pProvinceName : Integer = ParserSelectByHandleByIndex(pProvinceNames, ind);
      [*] = ;
      [*] = ;         randSum := randsum - ParserGetFloatValueByKeyByHandle(pProvinceName, 'Rarity');
      [*] = ;         if randSum <= 0 then
      [*] = ;         begin
      [*] = ;            var name : String = ParserGetValueByKeyByHandle(pProvinceName, 'Name');
      [*] = ;            ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', name);
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ErrorLog('No suitable name for castle found.');
      [*] = ;      ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', '????');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetRulerDiff : Integer;
      [*] = ;begin
      [*] = ;   var pCampDiff : Integer = ParserSelectByHandleByIndex(gPrototypeData.campDifficulties.handle, campDiff);
      [*] = ;   var startAI : Integer = ParserGetIntValueByKeyByHandle(pCampDiff, 'StartAI');
      [*] = ;   var endAI : Integer = ParserGetIntValueByKeyByHandle(pCampDiff, 'EndAI');
      [*] = ;   var step : Integer = ParserGetIntValueByKeyByHandle(pCampDiff, 'Step');
      [*] = ;
      [*] = ;   Result := startAI + gCampaign.currentTurn div step;
      [*] = ;   if Result > endAI then
      [*] = ;   Result := endAI;
      [*] = ;   Result := Result + 1;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure MakeLocalLord(plInd, lordInd : Integer);
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(plInd);
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLordIndex, lordInd);
      [*] = ;   _camp_player_Clear(gCampaign.arrCampLords[lordInd]);
      [*] = ;   var buildCount : Integer = gCampaign.currentTurn div 2 + gCampaign.currentTurn div 2 * campDiff div 4 + _rand_Random(2 + campDiff);
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to buildCount-1 do
      [*] = ;   _camp_player_AddBuild(gCampaign.arrCampLords[lordInd]);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure InitCastle(ind : Integer);
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;   var arInd : Integer = _rand_Random(ArrayGetCount);
      [*] = ;   var plInd : Integer = ArrayGetValueByIndex(arInd);
      [*] = ;   var plName : String = GetPlayerNameByIndex(plInd);
      [*] = ;   ArrayDeleteItemByIndex(arInd);
      [*] = ;
      [*] = ;   ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Castle', true);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', 0);
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Player', plName);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddProvGarrison(pStratHexCell : Integer);
      [*] = ;begin
      [*] = ;   var castle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;   var pProvGarrison : Integer = ParserAddChildByIndex(pStratHexCell, 'Garrison');
      [*] = ;   var pGarrisonSlots : Integer = ParserAddChildByIndex(pProvGarrison, 'Slots');
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   for i := 1 to 4 do
      [*] = ;   begin
      [*] = ;      var pGarrisonSlot : Integer = ParserAddChildByIndex(pGarrisonSlots, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pGarrisonSlot, 'SlotRank', i);
      [*] = ;      if castle and (i = 1) then
      [*] = ;      ParserSetIntValueByKeyByHandle(pGarrisonSlot, 'Count', 6)
      [*] = ;      else
      [*] = ;      ParserSetIntValueByKeyByHandle(pGarrisonSlot, 'Count', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pGarrisonUnits : Integer = ParserAddChildByIndex(pProvGarrison, 'Units');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure InitCastleProvince(pStratHexCell, plIndex : Integer);
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;   var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;
      [*] = ;   var provInd : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Index');
      [*] = ;   ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Castle', true);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', 1);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType', 7);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Explored', 50);
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Player', plName);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceRace', 1);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Population', 10);
      [*] = ;
      [*] = ;   AddProvGarrison(pStratHexCell);
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'GemInc', 5);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'GoldInc', 20);
      [*] = ;
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCastleProvIndex, provInd);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetProvTerrainType(provInd, terType : Integer);
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, provInd);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', terType);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateProvGameObjects;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var xc : Float = ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;      var zc : Float = ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;
      [*] = ;      if not IsHexAvailable(pHexCell) then
      [*] = ;      continue;
      [*] = ;
      [*] = ;      var goHandle : Integer = CreatePlayerGameObjectHandleByHandle(dummyPlHandle, cDummyPlRace, cDummyGOBaseName, xc, 0, zc);
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_Province_iParserHandle, pHexCell);
      [*] = ;
      [*] = ;      var UID : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'DummyUID', UID); // dummy game object unique ID
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CalcProvinceIncome(pStratHexCell : Integer);
      [*] = ;begin
      [*] = ;   var provType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;   var pProvinceType : Integer = ParserSelectByHandleByIndex(pProvinceTypes, provType);
      [*] = ;   var prGoldInc : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'Gold');
      [*] = ;   var prGemInc : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'Gem');
      [*] = ;
      [*] = ;   var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   var pTerrainType : Integer = ParserSelectByHandleByIndex(pTerrainTypes, terType);
      [*] = ;   var terGoldInc : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, 'Gold');
      [*] = ;   var terGemInc : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, 'Gem');
      [*] = ;
      [*] = ;   var prSize : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'Size');
      [*] = ;
      [*] = ;   var bRestoreAvSize : Boolean = False;
      [*] = ;   if (avProvinceSize=0) and (prSize=0) then // For tutorial and map editor, to prevent div 0. faust, chech is it possible to calc sizes before this function
      [*] = ;   begin
      [*] = ;      bRestoreAvSize := True;
      [*] = ;      avProvinceSize := 1;
      [*] = ;      prSize := 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var goldInc : Integer;
      [*] = ;   goldInc := terGoldInc + prGoldInc;
      [*] = ;   goldInc := Floor(goldInc * (prSize / avProvinceSize));
      [*] = ;   goldInc := goldInc + 2 - _rand_Random(5);
      [*] = ;   if goldInc <= 0 then
      [*] = ;   goldInc := 1;
      [*] = ;
      [*] = ;   var gemInc : Integer;
      [*] = ;   gemInc := terGemInc + prGemInc;
      [*] = ;   gemInc := Floor(gemInc * (prSize / avProvinceSize));
      [*] = ;   gemInc := gemInc - _rand_Random(4);
      [*] = ;   if gemInc < 0 then
      [*] = ;   gemInc := 0;
      [*] = ;
      [*] = ;   // world rule
      [*] = ;   if (_worldrule_GetWorldRuleAbilityExistByID(1)) then
      [*] = ;   begin
      [*] = ;      var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(1);
      [*] = ;      var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(1);
      [*] = ;      goldInc := (goldInc*param1) div 100;
      [*] = ;      gemInc := (gemInc*param2) div 100;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'GoldInc', goldInc);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'GemInc', gemInc);
      [*] = ;
      [*] = ;   if (bRestoreAvSize) then
      [*] = ;   avProvinceSize := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetProvinceResource(provInd, resID, resExplore : Integer; bGuarded : Boolean);
      [*] = ;begin
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, provInd);
      [*] = ;   var CastleDist : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'CastleDist');
      [*] = ;
      [*] = ;   var pProvSites : Integer = ParserSelectByHandleByKey(pHexCell, 'Sites');
      [*] = ;   var pProvSite : Integer = ParserAddChildByIndex(pProvSites, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvSite, 'Resource', resID);
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'Resource', resID);
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'ResourceExplore', resExplore);
      [*] = ;
      [*] = ;   IntRegister0 := resID;
      [*] = ;   ExecuteState('GetSiteParserByID');
      [*] = ;   var pSite : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var siteName : String = ParserGetValueByKeyByHandle(pSite, 'Hint');
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvSite, 'Explore', resExplore);
      [*] = ;   ParserSetValueByKeyByHandle(pProvSite, 'Name', siteName);
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvSite, 'SiteID', i);
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvSite, 'Level', 0);
      [*] = ;
      [*] = ;   if (bGuarded) then
      [*] = ;   begin
      [*] = ;      // setting resource guard
      [*] = ;      var pResource : Integer = ParserSelectByHandleByIndex(pResources, i);
      [*] = ;      var guardLevel : Integer = ParserGetIntValueByKeyByHandle(pResource, 'Rarity');
      [*] = ;      guardLevel := Round(Clamp(guardLevel, 0, 3));
      [*] = ;
      [*] = ;      var guardType : Integer = GetRandomGuardTypeBySiteParser(pSite);
      [*] = ;
      [*] = ;      IntRegister0 := guardType;
      [*] = ;      ExecuteState('GetGuardTypeParserByID');
      [*] = ;      var pGuardType : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var guardKarma : Integer = ParserGetIntValueByKeyByHandle(pGuardType, 'Karma');
      [*] = ;      var pGuardIDs : Integer = ParserSelectByHandleByKey(pGuardType, 'GuardID');
      [*] = ;      var pGuardID : Integer = ParserSelectByHandleByIndex(pGuardIDs, guardLevel);
      [*] = ;      var guardID : Integer = ParserGetIntValueByKeyByHandle(pGuardID, 'GuardID');
      [*] = ;
      [*] = ;      IntRegister0 := pProvSite;
      [*] = ;      IntRegister1 := guardType;
      [*] = ;      IntRegister2 := guardID;
      [*] = ;      IntRegister3 := guardKarma;
      [*] = ;      ExecuteState('map.AddGuard');
      [*] = ;      var pSiteGuard : Integer = IntRegister4;
      [*] = ;      ParserSetBoolValueByKeyByHandle(pSiteGuard, 'NeedRestore', false);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pHexCell, 'ResourceGuarded', true);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddSpellToProvince(pProvince, spellID : Integer);
      [*] = ;begin
      [*] = ;   var pSpell : Integer = ParserSelectByHandleByIndex(gPrototypeData.spells.handle, spellID);
      [*] = ;   var level : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Level');
      [*] = ;   var pProvSpells : Integer = ParserSelectByHandleByKey(pProvince, 'SpellLevels');
      [*] = ;   var pProvLevelSpells : Integer = ParserSelectByHandleByIndex(pProvSpells, 0);
      [*] = ;   pProvLevelSpells := ParserSelectByHandleByKey(pProvLevelSpells, 'Spells');
      [*] = ;
      [*] = ;   var pProvSpell : Integer = ParserAddChildByIndex(pProvLevelSpells, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvSpell, 'SpellID', spellID);
      [*] = ;end;
      [*] = ;
      [*] = ;function AddTutorialSite(pStratHexCell, siteID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := pStratHexCell;
      [*] = ;   IntRegister1 := siteID;
      [*] = ;   IntRegister2 := 1;
      [*] = ;   IntRegister3 := 0;
      [*] = ;   IntRegister4 := 0;
      [*] = ;   IntRegister5 := 0;
      [*] = ;   ExecuteState('AddSite');
      [*] = ;   var pNewSite : Integer = IntRegister6;
      [*] = ;   var pSiteGuard : Integer = ParserSelectByHandleByKey(pNewSite, 'Guard');
      [*] = ;   ParserSetIntValueByKeyByHandle(pSiteGuard, 'Initiative', 0);
      [*] = ;   var pGuardUnits : Integer = ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;   ParserClearByHandle(pGuardUnits);
      [*] = ;
      [*] = ;   Result := pNewSite;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetProvDefender(provIndex, defID : Integer);
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, provIndex);
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   IntRegister0 := defID;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'PlaceDefender');
      [*] = ;   var pProvGuard : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Guard');
      [*] = ;   var pGuardUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;   ParserClearByHandle(pGuardUnits);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetMapEditorData();
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      if (gMapEditor.grid[i].castle) and (gMapEditor.grid[i].terrain>0) and (gMapEditor.grid[i].terrain<5) then
      [*] = ;      begin
      [*] = ;         // setup castles
      [*] = ;         InitCastleProvince(pStratHexCell, gMapEditor.grid[i].player);
      [*] = ;         if (gMapEditor.grid[i].name='') then
      [*] = ;         begin
      [*] = ;            if (gMapEditor.grid[i].player<>0) then
      [*] = ;               MakeCastleName(pStratHexCell)
      [*] = ;            else
      [*] = ;               ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', gProfile.land);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (not gMapEditor.grid[i].enabled) then
      [*] = ;      SetProvTerrainType(i, gc_MountainTerrainType)
      [*] = ;      else
      [*] = ;      if (gMapEditor.grid[i].terrain=0) then
      [*] = ;      SetProvTerrainType(i, 1+Floor(RandomExt*6))
      [*] = ;      else
      [*] = ;      SetProvTerrainType(i, gMapEditor.grid[i].terrain);
      [*] = ;
      [*] = ;      if (not gMapEditor.grid[i].castle) and (gMapEditor.grid[i].terrain>0) and (gMapEditor.grid[i].terrain<5) then
      [*] = ;      begin
      [*] = ;         // set province owner
      [*] = ;         if (gMapEditor.grid[i].player>-1) then
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(gMapEditor.grid[i].player);
      [*] = ;            var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;            ParserSetValueByKeyByHandle(pStratHexCell, 'Player', plName);
      [*] = ;         end;
      [*] = ;
      [*] = ;         // setup province type
      [*] = ;         if (gMapEditor.grid[i].provincetype<>0) then
      [*] = ;         begin
      [*] = ;            // set province type
      [*] = ;            var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provincetypes.handle, gMapEditor.grid[i].provincetype);
      [*] = ;            ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType', gMapEditor.grid[i].provincetype);
      [*] = ;            ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceRace', ParserGetIntValueByKeyByHandle(pProvinceType, 'RaceID'));
      [*] = ;            ParserSetIntValueByKeyByHandle(pStratHexCell, 'Population', ParserGetIntValueByKeyByHandle(pProvinceType, 'Population'));
      [*] = ;            ParserSetIntValueByKeyByHandle(pStratHexCell, 'Explored', ParserGetIntValueByKeyByHandle(pProvinceType, 'Explored'));
      [*] = ;            CalcProvinceIncome(pStratHexCell);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // check this out SetTutorialExtData
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetMapEditorPlayers;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var lordInd : Integer = 1;
      [*] = ;   var bHuman : Boolean = False;
      [*] = ;   for i:=0 to mapPlayers-1 do
      [*] = ;   begin
      [*] = ;      if (gMapEditor.players[i].human) then
      [*] = ;      begin
      [*] = ;         bHuman := True;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (not bHuman) then
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(0);
      [*] = ;      gMapEditor.players[0].human := True;
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCanOuterBuild, 1000);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCanInnerBuild, 1000);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCanHire, 1000);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, 100000);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, 100000);
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=0 to mapPlayers-1 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      if (gMapEditor.players[i].id>-1) then
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile, gMapEditor.players[i].id);
      [*] = ;      if (gMapEditor.players[i].difficulty>-1) then
      [*] = ;      begin
      [*] = ;         gGame.arrplayerdifficulty[i].basediff := gMapEditor.players[i].difficulty;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDifficulty, gMapEditor.players[i].difficulty);
      [*] = ;      end;
      [*] = ;      if (gMapEditor.players[i].gold>-1) then
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, gMapEditor.players[i].gold);
      [*] = ;      if (gMapEditor.players[i].gem>-1) then
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, gMapEditor.players[i].gem);
      [*] = ;      if (gMapEditor.players[i].human) then
      [*] = ;      begin
      [*] = ;         SetPlayerControlModeByHandle(plHandle, 'cmPlayer');
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma, gMapEditor.players[i].karma);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      SetPlayerControlModeByHandle(plHandle, 'cmPC');
      [*] = ;      if (gMapEditor.players[i].union>-1) then
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iUnion, gMapEditor.players[i].union);
      [*] = ;      if (gMapEditor.players[i].locallord) then
      [*] = ;      begin
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLordIndex, lordInd);
      [*] = ;         lordInd := lordInd+1;
      [*] = ;      end;
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to mapPlayers-1 do
      [*] = ;      gArrDiplomacy[i][j].treaty := gMapEditor.players[i].treaty[j];
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetMapEditorExtData;
      [*] = ;begin
      [*] = ;   log('SetMapEditorExtData');
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;      var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;      if (gMapEditor.grid[i].name<>'') then
      [*] = ;      ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', gMapEditor.grid[i].name);
      [*] = ;
      [*] = ;      if (not gMapEditor.grid[i].castle) then
      [*] = ;      begin
      [*] = ;         // setup resource
      [*] = ;         if (gMapEditor.grid[i].resourceid>0) then
      [*] = ;         begin
      [*] = ;            var pResource : Integer = ParserSelectByHandleByIndex(gPrototypeData.resources.handle, gMapEditor.grid[i].resourceid);
      [*] = ;            var resRarity : Integer = ParserGetIntValueByKeyByHandle(pResource, 'Rarity');
      [*] = ;            var CastleDist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'CastleDist');
      [*] = ;            var resExplore : Integer = 1;
      [*] = ;            if (not gMapEditor.grid[i].resexplored) then
      [*] = ;            begin
      [*] = ;               resExplore := Floor(RandomExt * 20 + 40 + resRarity * 30 - CastleDist * 10);
      [*] = ;               var provExplore : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Explored');
      [*] = ;               if (provExplore>=resExplore) then
      [*] = ;               resExplore := provExplore+1;
      [*] = ;            end;
      [*] = ;            resExplore := Round(Clamp(resExplore, 0, 100));
      [*] = ;            var bGuarded : Boolean = (resRarity * 2 + 3 > CastleDist);
      [*] = ;            SetProvinceResource(i, gMapEditor.grid[i].resourceid, resExplore, bGuarded);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gMapEditor.grid[i].defenderid>0) then
      [*] = ;      SetProvDefender(i, gMapEditor.grid[i].defenderid);
      [*] = ;
      [*] = ;      if (gMapEditor.grid[i].goldinc>-1) then
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'GoldInc', gMapEditor.grid[i].goldinc);
      [*] = ;
      [*] = ;      if (gMapEditor.grid[i].geminc>-1) then
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'GemInc', gMapEditor.grid[i].geminc);
      [*] = ;
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to 2 do
      [*] = ;      begin
      [*] = ;         if (gMapEditor.grid[i].outerbuild[j]>0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gMapEditor.grid[i].outerbuild[j];
      [*] = ;            IntRegister1 := j;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //AddSpellToProvince(pCastle, 4);
      [*] = ;      //pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 10);
      [*] = ;      //var pProvFog : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Fog');
      [*] = ;      //ParserSetIntValueByKeyByHandle(pProvFog, '0', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=0 to gMapEditor.map.players-1 do
      [*] = ;   begin
      [*] = ;      if (gMapEditor.players[i].castleprovind>-1) then
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;
      [*] = ;         {// shop items
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;         var pCastle : Integer = IntRegister0;
      [*] = ;         var pProvShop : Integer = ParserSelectByHandleByKey(pCastle, 'Shop');
      [*] = ;         var pProvItems : Integer = ParserSelectByHandleByKey(pProvShop, 'Items');
      [*] = ;         ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 1);
      [*] = ;         ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 5);
      [*] = ;
      [*] = ;         var pProvRecruitUnits : Integer = ParserSelectByHandleByKey(pCastle, 'RecruitUnits');
      [*] = ;         ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvRecruitUnits, '*'), 'UnitID', 1);
      [*] = ;         ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvRecruitUnits, '*'), 'UnitID', 2);}
      [*] = ;
      [*] = ;         _editor_AssignInnerBuildingsToCurrentMap(plHandle, gMapEditor.players[i]);
      [*] = ;         //_editor_AssignPlayerHeroesToCurrentMap(plHandle, gMapEditor.players[i]); done in MakeStratHexGrid as last generation action
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetTutorialData;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', 2);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(0);
      [*] = ;   var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;   var enPlHandle : Integer = GetPlayerHandleByIndex(1);
      [*] = ;   var enPlName : String = GetPlayerNameByHandle(enPlHandle);
      [*] = ;
      [*] = ;   // enemy castle
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, 1);
      [*] = ;   InitCastleProvince(pStratHexCell, 1);
      [*] = ;
      [*] = ;   var pGarrison : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Garrison');
      [*] = ;
      [*] = ;   for i := 0 to 5 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := pGarrison;
      [*] = ;      IntRegister1 := 4;
      [*] = ;      IntRegister2 := 30;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      ExecuteState('AddUnitToParser');
      [*] = ;   end;
      [*] = ;   MakeCastleName(pStratHexCell);
      [*] = ;
      [*] = ;   // player's castle
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 27);
      [*] = ;   InitCastleProvince(pStratHexCell, 0);
      [*] = ;
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', gProfile.land);
      [*] = ;
      [*] = ;   // other provinces
      [*] = ;   SetProvTerrainType(0, gc_MountainTerrainType);
      [*] = ;   SetProvTerrainType(6, gc_MountainTerrainType);
      [*] = ;   SetProvTerrainType(12, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(18, gc_MountainTerrainType);
      [*] = ;   SetProvTerrainType(24, gc_ForestTerrainType);
      [*] = ;   SetProvTerrainType(30, gc_ForestTerrainType);
      [*] = ;
      [*] = ;   SetProvTerrainType(7, gc_HillTerrainType);
      [*] = ;   SetProvTerrainType(13, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(19, gc_ForestTerrainType);
      [*] = ;   SetProvTerrainType(25, gc_PlainTerrainType);
      [*] = ;   SetProvTerrainType(31, gc_PlainTerrainType);
      [*] = ;
      [*] = ;   SetProvTerrainType(2, gc_HillTerrainType);
      [*] = ;   SetProvTerrainType(8, gc_HillTerrainType);
      [*] = ;   SetProvTerrainType(14, gc_MountainTerrainType);
      [*] = ;   SetProvTerrainType(20, gc_MountainTerrainType);
      [*] = ;   SetProvTerrainType(26, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(32, gc_PlainTerrainType);
      [*] = ;
      [*] = ;   SetProvTerrainType(3, gc_MountainTerrainType);
      [*] = ;   SetProvTerrainType(9, gc_MountainTerrainType);
      [*] = ;   SetProvTerrainType(15, gc_ForestTerrainType);
      [*] = ;   SetProvTerrainType(21, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(33, gc_ForestTerrainType);
      [*] = ;
      [*] = ;   SetProvTerrainType(4, gc_MountainTerrainType);
      [*] = ;   SetProvTerrainType(10, gc_PlainTerrainType);
      [*] = ;   SetProvTerrainType(16, gc_PlainTerrainType);
      [*] = ;   SetProvTerrainType(22, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(28, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(34, gc_SwampTerrainType);
      [*] = ;
      [*] = ;   SetProvTerrainType(5, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(11, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(17, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(23, gc_WaterTerrainType);
      [*] = ;   SetProvTerrainType(29, gc_SwampTerrainType);
      [*] = ;   SetProvTerrainType(35, gc_ForestTerrainType);
      [*] = ;
      [*] = ;   // set enemy owner
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 2);
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Player', enPlName);
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 8);
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Player', enPlName);
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 7);
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Player', enPlName);
      [*] = ;
      [*] = ;   for i := 1 to 2 do
      [*] = ;   begin
      [*] = ;      var ind : Integer = 4 + i * 6;
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType', 1);
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceRace', 1);
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'Population', 300);
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'Explored', 1);
      [*] = ;      CalcProvinceIncome(pStratHexCell);
      [*] = ;   end;
      [*] = ;
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 16);
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Player', plName);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Population', 10000);
      [*] = ;
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 15);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType', 2);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceRace', 1);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Population', 100);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Explored', 30);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'GoldInc', 8);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'GemInc', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetTutorialExtData;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(0);
      [*] = ;   var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;   var enPlHandle : Integer = GetPlayerHandleByIndex(1);
      [*] = ;   var enPlName : String = GetPlayerNameByHandle(enPlHandle);
      [*] = ;
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, 1);
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   IntRegister0 := 6;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'PlaceDefender');
      [*] = ;
      [*] = ;   IntRegister0 := 39;
      [*] = ;   PlayerExecuteStateByHandle(enPlHandle, 'AddInnerBuild');
      [*] = ;
      [*] = ;   var pProvGarrison : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Garrison');
      [*] = ;   for i := 0 to 5 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvGarrison;
      [*] = ;      IntRegister1 := 4;
      [*] = ;      IntRegister2 := 30;
      [*] = ;      IntRegister3 := 1;
      [*] = ;      IntRegister4 := i;
      [*] = ;      ExecuteState('map.AddUnitToGarrison');
      [*] = ;   end;
      [*] = ;
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 7);
      [*] = ;   dummyUID := ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;   dummyHandle := GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   IntRegister0 := 10;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 16);
      [*] = ;   dummyUID := ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;   dummyHandle := GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   IntRegister0 := 7;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;
      [*] = ;   IntRegister0 := 18;
      [*] = ;   IntRegister1 := 1;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;
      [*] = ;   IntRegister0 := 19;
      [*] = ;   IntRegister1 := 2;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;   pProvGarrison := ParserSelectByHandleByKey(pStratHexCell, 'Garrison');
      [*] = ;   var pGarrSlots : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Slots');
      [*] = ;   for i := ParserGetCountByHandle(pGarrSlots)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGarrSlot : Integer = ParserSelectByHandleByIndex(pGarrSlots, i);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGarrSlot, 'Count', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pProvSites : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Sites');
      [*] = ;   ParserClearByHandle(pProvSites);
      [*] = ;
      [*] = ;   var pNewSite : Integer = AddTutorialSite(pStratHexCell, 11);
      [*] = ;   ParserSetIntValueByKeyByHandle(pNewSite, 'Explore', 1);
      [*] = ;   var pSiteGuard : Integer = ParserSelectByHandleByKey(pNewSite, 'Guard');
      [*] = ;   ParserSetIntValueByKeyByHandle(pSiteGuard, 'GuardType', 4);
      [*] = ;   var pGuardUnits : Integer = ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;   for i := 0 to 2 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      IntRegister1 := 13;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      ExecuteState('AddUnitToParser');
      [*] = ;   end;
      [*] = ;
      [*] = ;   pNewSite := AddTutorialSite(pStratHexCell, 12);
      [*] = ;   ParserSetIntValueByKeyByHandle(pNewSite, 'Explore', 2);
      [*] = ;   pSiteGuard := ParserSelectByHandleByKey(pNewSite, 'Guard');
      [*] = ;   ParserSetIntValueByKeyByHandle(pSiteGuard, 'GuardType', 6);
      [*] = ;   pGuardUnits := ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;   for i := 0 to 2 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      IntRegister1 := 14;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      ExecuteState('AddUnitToParser');
      [*] = ;   end;
      [*] = ;
      [*] = ;   pNewSite := AddTutorialSite(pStratHexCell, 10);
      [*] = ;   ParserSetIntValueByKeyByHandle(pNewSite, 'Explore', 3);
      [*] = ;   pSiteGuard := ParserSelectByHandleByKey(pNewSite, 'Guard');
      [*] = ;   ParserSetIntValueByKeyByHandle(pSiteGuard, 'GuardType', 5);
      [*] = ;   pGuardUnits := ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;   for i := 0 to 1 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      IntRegister1 := 19;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      ExecuteState('AddUnitToParser');
      [*] = ;
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      IntRegister1 := 20;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      ExecuteState('AddUnitToParser');
      [*] = ;   end;
      [*] = ;
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 15);
      [*] = ;   dummyUID := ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;   dummyHandle := GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   var provType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;   var pProvinceType : Integer = ParserSelectByHandleByIndex(pProvinceTypes, provType);
      [*] = ;   var pPrGuardTypes : Integer = ParserSelectByHandleByKey(pProvinceType, 'GuardTypes');
      [*] = ;   var pPrGuardType : Integer = ParserSelectByHandleByIndex(pPrGuardTypes, 0);
      [*] = ;   var guardType : Integer = ParserGetIntValueByKeyByHandle(pPrGuardType, 'GuardType');
      [*] = ;   var guardDialog : Integer = ParserGetIntValueByKeyByHandle(pPrGuardType, 'Dialog');
      [*] = ;   var guardEncounter : Integer = ParserGetIntValueByKeyByHandle(pPrGuardType, 'Encounter');
      [*] = ;
      [*] = ;   IntRegister0 := pStratHexCell;
      [*] = ;   IntRegister1 := guardType;
      [*] = ;   IntRegister2 := 5;
      [*] = ;   IntRegister3 := 0;
      [*] = ;   ExecuteState('map.AddGuard');
      [*] = ;   var pProvGuard : Integer = IntRegister4;
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvGuard, 'Dialog', guardDialog);
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvGuard, 'Encounter', guardEncounter);
      [*] = ;
      [*] = ;   IntRegister0 := 10;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, 0);
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, 0);
      [*] = ;
      [*] = ;   // shop items
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;   var pCastle : Integer = IntRegister0;
      [*] = ;   var pProvShop : Integer = ParserSelectByHandleByKey(pCastle, 'Shop');
      [*] = ;   var pProvItems : Integer = ParserSelectByHandleByKey(pProvShop, 'Items');
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 1);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 5);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 9);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 13);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 17);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 29);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 37);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 41);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 42);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 46);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 51);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 55);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 63);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvItems, '*'), 'ItemID', 59);
      [*] = ;
      [*] = ;   var pProvRecruitUnits : Integer = ParserSelectByHandleByKey(pCastle, 'RecruitUnits');
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvRecruitUnits, '*'), 'UnitID', 1);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pProvRecruitUnits, '*'), 'UnitID', 2);
      [*] = ;
      [*] = ;   AddSpellToProvince(pCastle, 4);
      [*] = ;   AddSpellToProvince(pCastle, 12);
      [*] = ;   AddSpellToProvince(pCastle, 14);
      [*] = ;
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, 10);
      [*] = ;   var pProvFog : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Fog');
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvFog, '0', 0);
      [*] = ;
      [*] = ;   SetProvDefender(2, 1);
      [*] = ;   SetProvDefender(7, 1);
      [*] = ;   SetProvDefender(8, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ChangeTerrainType(pStratHexCell : Integer);
      [*] = ;begin
      [*] = ;   var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   if (terType = gc_DeadLandTerrainType) or (terType = gc_DesertTerrainType) or ((terType = gc_PlainTerrainType) and ((curVisualID=2) or (curVisualID=3))) then
      [*] = ;   begin
      [*] = ;      var ind : Integer;
      [*] = ;      if (curVisualID=2) or (curVisualID=3) then
      [*] = ;         ind := 1+_rand_Random(3) // can't place plain under castle on desert or deadland shards
      [*] = ;      else
      [*] = ;         ind := _rand_Random(4);
      [*] = ;      
      [*] = ;      case ind of
      [*] = ;         0 : terType := gc_PlainTerrainType;
      [*] = ;         1 : terType := gc_ForestTerrainType;
      [*] = ;         2 : terType := gc_HillTerrainType;
      [*] = ;         3 : terType := gc_SwampTerrainType;
      [*] = ;      end;
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', terType);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gGame.gameType <> gc_GameTypeHotseatBattle) and (gGame.gameType <> gc_GameTypeLanBattle) then
      [*] = ;   LoadPatterns(true, true)
      [*] = ;else
      [*] = ;   LoadPatterns(true, false);
      [*] = ;
      [*] = ;// initialize provinces
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Index', i);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'CenterX', 0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'CenterY', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', 0);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Castle', false);
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Player', '');
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', cDefCastleDist);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Checked', false);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType', 0); // province type
      [*] = ;   ParserSetBoolValueByKeyByHandle(pStratHexCell, 'SetProvinceType', true);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceRace', 0); // province race
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', ''); // province name
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Prefix', ''); // province name prefix
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'Suffix', ''); // province name suffix
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceLevel', 0); // province level
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Population', 0); // population
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Fort', 0); // strength of walls
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'GoldInc', 0); // gold increase
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'GemInc', 0); // gem increase
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Explored', 0); // percent of exploration
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Resource', 0); // resource
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'ResourceExplore', 0); // resource level of exploration
      [*] = ;   ParserSetBoolValueByKeyByHandle(pStratHexCell, 'ResourceGuarded', false); // is resource guarded
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Coast', 0);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Sea', false);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'DummyUID', 0); // dummy game object unique ID
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'PatternPlayer', ''); // pattern player name
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'PatternGroup', ''); // pattern group name
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'MoveMap', -2);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'MobilMap', -1000);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'HeroPointX', 0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'HeroPointY', 0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'EventWin', 0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'EventLose', 0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'EventDraw', 0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'LastPlayer', -1);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Recalculate', false); // need to recalculate hero targets
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'UpdatePlayer', -1); // last update player index
      [*] = ;
      [*] = ;   var pProvFog : Integer = ParserAddChildByIndex(pStratHexCell, 'Fog'); // province fog type: 0 - no fog, 1 - half fog, 2 - full fog
      [*] = ;   for j := 0 to gGame.map.players-1 do
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvFog, IntToStr(j), 2);
      [*] = ;
      [*] = ;   // temp values
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'PrevPathInd', -1);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Stable', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Port', 0);
      [*] = ;
      [*] = ;   var pProvNeighbours : Integer = ParserAddChildByIndex(pStratHexCell, 'Neighbours');
      [*] = ;   var pProvSites : Integer = ParserAddChildByIndex(pStratHexCell, 'Sites');
      [*] = ;   var pHeroes : Integer = ParserAddChildByIndex(pStratHexCell, 'MoveHeroes');
      [*] = ;end;
      [*] = ;
      [*] = ;// create list of province neighbours
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var tnHandle : Integer = GetTrackNodeHandleByIndex(i);
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var pNeighbours : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Neighbours');
      [*] = ;
      [*] = ;   for j := 0 to HexCount-1 do
      [*] = ;   if j <> i then
      [*] = ;   begin
      [*] = ;      var tnHandle1 : Integer = GetTrackNodeHandleByIndex(j);
      [*] = ;      var pNStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, j);
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pNStratHexCell, 'DummyUID');
      [*] = ;
      [*] = ;      if GetTrackNodesConnectedByHandle(tnHandle, tnHandle1) {and (dummyUID > 0)} then
      [*] = ;      begin
      [*] = ;         var pNeighbour : Integer = ParserAddChildByIndex(pNeighbours, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pNeighbour, 'Index', j);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// setup cur game params
      [*] = ;for i := 0 to ParserGetCountByHandle(pResources)-1 do
      [*] = ;gGame.resPrices[i] := 100;
      [*] = ;
      [*] = ;gGame.resBuy := gc_ResBuyChange - mapPlayers div 5;
      [*] = ;
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Freq', -1);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_PlainTerrainType);
      [*] = ;end;
      [*] = ;
      [*] = ;// races quests
      [*] = ;for i := 0 to ParserGetCountByHandle(pRaces)-1 do
      [*] = ;begin
      [*] = ;   gGame.arrRaceQuest[i] := 1;
      [*] = ;   _rand_ClearRoll;
      [*] = ;   var count : Integer = 0;
      [*] = ;
      [*] = ;   var pRace : Integer = ParserSelectByHandleByIndex(pRaces, i);
      [*] = ;   var pRaceQuests : Integer = ParserSelectByHandleByKey(pRace, 'Quests');
      [*] = ;   for j := ParserGetCountByHandle(pRaceQuests)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pRaceQuest : Integer = ParserSelectByHandleByIndex(pRaceQuests, j);
      [*] = ;      var questID : Integer = ParserGetIntValueByKeyByHandle(pRaceQuest, 'QuestID');
      [*] = ;
      [*] = ;      if questID > 0 then
      [*] = ;      begin
      [*] = ;         var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, questID);
      [*] = ;         gArrRollerN[count] := questID;
      [*] = ;         gArrRollerP[count] := ParserGetIntValueByKeyByHandle(pQuest, 'Possibility');
      [*] = ;         count := count + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if count > 0 then
      [*] = ;   gGame.arrRaceQuest[i] := _rand_Roll(false);
      [*] = ;end;
      [*] = ;
      [*] = ;Log('Adding players...');
      [*] = ;
      [*] = ;// add players
      [*] = ;case gGame.gameType of
      [*] = ;   gc_GameTypeCustom, gc_GameTypeHotseat, gc_GameTypeLanShard : begin
      [*] = ;      // custom map
      [*] = ;      for i := 0 to mapPlayers-1 do
      [*] = ;         curGamePlayerSet[i] := gGame.arrPlayerSet[i];
      [*] = ;
      [*] = ;      for i := 0 to mapPlayers-1 do
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;         var plProfile : Integer = gGame.arrPlayerSet[i];
      [*] = ;         if SameText(cMode, 'cmPC') and (plProfile=0) then
      [*] = ;         begin
      [*] = ;            plProfile := FindUniqueRandomPlayerID();
      [*] = ;            curGamePlayerSet[i] := plProfile;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var plDiff : Integer = gMapSettings.arrPlayers[i].advdiff.basediff;
      [*] = ;         if ((gc_demoVersion=1) or (gc_expoVersion=1)) and (gIntRegister_CurDemoMode>0) then
      [*] = ;         begin
      [*] = ;            if i > 0 then
      [*] = ;               plProfile := i
      [*] = ;            else
      [*] = ;               plProfile := 0;
      [*] = ;
      [*] = ;            if i = 0 then
      [*] = ;               plDiff := 0
      [*] = ;            else
      [*] = ;               plDiff := 2;
      [*] = ;         end;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDifficulty, plDiff);
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile, plProfile);
      [*] = ;         gGame.arrplayerdifficulty[i].basediff := plDiff;
      [*] = ;
      [*] = ;         if plProfile > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := plProfile;
      [*] = ;            ExecuteState('GetProfileParserByID');
      [*] = ;            var pProfile : Integer = IntRegister1;
      [*] = ;
      [*] = ;            var karma : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Karma');
      [*] = ;            SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma, karma);
      [*] = ;
      [*] = ;            if SameText(cMode, 'cmPC') then
      [*] = ;            begin
      [*] = ;               var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, plProfile);
      [*] = ;               case gGame.gameType of
      [*] = ;                  gc_GameTypeHotseat : begin
      [*] = ;                     gArrHotseatProfiles[i].name := GetLocaleTableListItemByID('players', IntToStr(plProfile));
      [*] = ;                     gArrHotseatProfiles[i].land := 'players|'+IntToStr(plProfile)+'.castlename';
      [*] = ;                     gArrHotseatProfiles[i].color1 := ParserGetIntValueByKeyByHandle(pProfile, 'Color1');
      [*] = ;                     gArrHotseatProfiles[i].color2 := ParserGetIntValueByKeyByHandle(pProfile, 'Color2');
      [*] = ;                     gArrHotseatProfiles[i].sign := ParserGetIntValueByKeyByHandle(pProfile, 'Herb');
      [*] = ;                     gArrHotseatProfiles[i].avatar := plProfile;
      [*] = ;                  end;
      [*] = ;                  gc_GameTypeLanShard : begin
      [*] = ;                     gLanShardGame.arrLanPlayers[i].profile.name := GetLocaleTableListItemByID('players', IntToStr(plProfile));
      [*] = ;                     gLanShardGame.arrLanPlayers[i].profile.land := 'players|'+IntToStr(plProfile)+'.castlename';
      [*] = ;                     gLanShardGame.arrLanPlayers[i].profile.color1 := ParserGetIntValueByKeyByHandle(pProfile, 'Color1');
      [*] = ;                     gLanShardGame.arrLanPlayers[i].profile.color2 := ParserGetIntValueByKeyByHandle(pProfile, 'Color2');
      [*] = ;                     gLanShardGame.arrLanPlayers[i].profile.sign := ParserGetIntValueByKeyByHandle(pProfile, 'Herb');
      [*] = ;                     gLanShardGame.arrLanPlayers[i].profile.avatar := plProfile;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      _map_MapGeneratorDefault(gMapSettings, True)
      [*] = ;   end;
      [*] = ;   gc_GameTypeCampaign : begin
      [*] = ;      // campaign
      [*] = ;      var myPlHandle : Integer = GetPlayerHandleByIndex(0);
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iProfile, 0);
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iDifficulty, campDiff);
      [*] = ;      _map_SetGameCustomDifficultyOptionsDefault(gGame.arrplayerdifficulty[0], False, campDiff);
      [*] = ;
      [*] = ;      if gIntRegister_CampAttackPlayer >= 0 then
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(1);
      [*] = ;
      [*] = ;         if gIntRegister_CampAttackPlayer = 0 then
      [*] = ;            SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile, gIntRegister_CampDefendPlayer)
      [*] = ;         else
      [*] = ;            SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile, gIntRegister_CampAttackPlayer);
      [*] = ;
      [*] = ;         var diff : Integer = GetRulerDiff + 1;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDifficulty, diff);
      [*] = ;         gGame.arrplayerdifficulty[1].basediff := diff;
      [*] = ;         _map_SetGameCustomDifficultyOptionsDefault(gGame.arrplayerdifficulty[1], False, diff);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _rand_ClearRoll();
      [*] = ;         var count : Integer = 0;
      [*] = ;         for i := 1 to gc_MaxCampPlayer-1 do
      [*] = ;         begin
      [*] = ;            if gCampaign.arrCampPlayers[i].firstMeet and gCampaign.arrCampPlayers[i].inGame and ((i <> 10) or (gCampaign.arrDialogs[670] = 0)) and
      [*] = ;            ((mapPlayers <> 2) or (i <> 3) or (gCampaign.arrCampPlayers[3].treaty = 0)) then // belez aliance
      [*] = ;            begin
      [*] = ;               gArrRollerN[count] := i;
      [*] = ;               gArrRollerP[count] := 10;
      [*] = ;               count := count + 1;
      [*] = ;            end
      [*] = ;         end;
      [*] = ;
      [*] = ;         for i := 1 to mapPlayers-1 do
      [*] = ;         begin
      [*] = ;            gGame.arrPlayerSet[i] := 0;
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;
      [*] = ;            if (count > 0) and (((mapPlayers > 2) and (i = 1)) or (_rand_Random(100) < 50 + count * 5)) then
      [*] = ;            begin
      [*] = ;               // campaign players
      [*] = ;               var profile : Integer = _rand_Roll(true);
      [*] = ;               gGame.arrPlayerSet[i] := profile;
      [*] = ;               SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile, profile);
      [*] = ;               var diff : Integer = GetRulerDiff;
      [*] = ;               diff := Round(Clamp(diff, 1, 6));
      [*] = ;               SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDifficulty, diff);
      [*] = ;               _map_SetGameCustomDifficultyOptionsDefault(gGame.arrplayerdifficulty[i], False, diff);
      [*] = ;               count := count - 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var arBuild : array [0..16] of Integer;
      [*] = ;         var needBuild : Integer = 0;
      [*] = ;         // add other PC camp player buildings
      [*] = ;         for i := 0 to count + mapPlayers - 2 do
      [*] = ;         begin
      [*] = ;            if (gArrRollerN[i] > 0) and (gArrRollerP[i] > 0) and (_rand_Random(2 + campDiff) > 0) then
      [*] = ;            begin
      [*] = ;               var ind : Integer = gArrRollerN[i];
      [*] = ;               arBuild[needBuild] := gArrRollerN[i];
      [*] = ;               _camp_player_AddBuild(gCampaign.arrCampPlayers[ind]);
      [*] = ;               needBuild := needBuild + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var lordInd : Integer = 1;
      [*] = ;         for i := 1 to mapPlayers-1 do
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;            if GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile) = 0 then
      [*] = ;            begin
      [*] = ;               // local lord
      [*] = ;               MakeLocalLord(i, lordInd);
      [*] = ;               gGame.arrPlayerSet[i] := -lordInd;
      [*] = ;               lordInd := lordInd + 1;
      [*] = ;
      [*] = ;               if gTutorial.map then
      [*] = ;               begin
      [*] = ;                  SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDifficulty, 0);
      [*] = ;                  _map_SetGameCustomDifficultyOptionsDefault(gGame.arrplayerdifficulty[i], False, 0);
      [*] = ;                  gGame.arrplayerdifficulty[i].basediff := 0;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var pCampDiff : Integer = ParserSelectByHandleByIndex(gPrototypeData.campDifficulties.handle, campDiff);
      [*] = ;                  var startAI : Integer = ParserGetIntValueByKeyByHandle(pCampDiff, 'StartAI');
      [*] = ;                  var endAI : Integer = ParserGetIntValueByKeyByHandle(pCampDiff, 'EndAI');
      [*] = ;                  var step : Integer = ParserGetIntValueByKeyByHandle(pCampDiff, 'Step');
      [*] = ;
      [*] = ;                  var shLevel : Integer = gShards[activeShard].level - 1;
      [*] = ;                  var lDiff : Integer = startAI + shLevel div (9 div (endAI - startAI));
      [*] = ;                  lDiff := Round(Clamp(lDiff, 0, 5));
      [*] = ;
      [*] = ;                  SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDifficulty, lDiff);
      [*] = ;                  _map_SetGameCustomDifficultyOptionsDefault(gGame.arrplayerdifficulty[i], False, lDiff);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         gGame.diplomacy := true;
      [*] = ;         gGame.fog := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gCampaign.arrDialogs[40] > 0 then
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion, 5);
      [*] = ;
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma, gCampaign.arrCampPlayers[0].karma);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// set overlord's attitudes
      [*] = ;for i := 1 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   var profile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;   if profile > 0 then
      [*] = ;   begin
      [*] = ;      var pPlayer : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, profile);
      [*] = ;      var pPlAttitudes : Integer = ParserSelectByHandleByKey(pPlayer, 'Attitude');
      [*] = ;      
      [*] = ;      if gGame.gameType = gc_GameTypeCampaign then
      [*] = ;         gArrDiplomacy[i][0].attitude := gCampaign.arrCampPlayers[profile].arrAttitude[0];
      [*] = ;
      [*] = ;      for j := 1 to gGame.map.players-1 do
      [*] = ;      if i <> j then
      [*] = ;      begin
      [*] = ;         var plHandle1 : Integer = GetPlayerHandleByIndex(j);
      [*] = ;         var profile1 : Integer = GetPlayerIntValueIndByHandle(plHandle1, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;         if profile1 > 0 then
      [*] = ;         begin
      [*] = ;            var pPlAttitude : Integer = ParserSelectByHandleByIndex(pPlAttitudes, profile1);
      [*] = ;            var attitude : Integer = ParserGetIntValueByKeyByHandle(pPlAttitude, 'Value');
      [*] = ;            gArrDiplomacy[i][j].attitude := attitude;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i:=0 to mapPlayers-1 do
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   var plDiff : Integer = gGame.arrplayerdifficulty[i].basediff;
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;   var gem : Integer = 0;
      [*] = ;   var gold : Integer = 0;
      [*] = ;
      [*] = ;   if (cMode='cmPC') then
      [*] = ;   begin
      [*] = ;      gem := 20 + plDiff * 5;
      [*] = ;      gold := 500 + plDiff * 50;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gem := gGame.arrplayerdifficulty[i].startgem;
      [*] = ;      gold := gGame.arrplayerdifficulty[i].startgold;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold + gold);
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem + gem);
      [*] = ;end;
      [*] = ;
      [*] = ;if (not gMapEditor.enabled) then
      [*] = ;begin
      [*] = ;   var myPlHandle : Integer = 0;
      [*] = ;   if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;   begin
      [*] = ;      var myLanID : Integer = LanMyInfoID();
      [*] = ;      for i := 0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;      if gLanShardGame.arrlanplayers[i].lanid = myLanID then
      [*] = ;      begin
      [*] = ;         myPlHandle := GetPlayerHandleByIndex(i);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      myPlHandle := GetPlayerHandleByIndex(0);
      [*] = ;
      [*] = ;   _gv_SetIOHandle(myPlHandle,_log_name);
      [*] = ;   gIntRegister_MapMyPlayerIndex := GetPlayerIndexByHandle(myPlHandle);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to mapPlayers-1 do
      [*] = ;   begin
      [*] = ;      if (gMapEditor.players[i].human) then
      [*] = ;      begin
      [*] = ;         var myPlHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         _gv_SetIOHandle(myPlHandle,_log_name);
      [*] = ;         gIntRegister_MapMyPlayerIndex := GetPlayerIndexByHandle(myPlHandle);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var spotCount : Integer = 0;
      [*] = ;
      [*] = ;var pMountains : Integer = ParserSelectByHandleByKey(pMachineParser, 'MountainPatterns');
      [*] = ;if pMountains = 0 then
      [*] = ;   pMountains := ParserAddChildByIndex(pMachineParser, 'MountainPatterns')
      [*] = ;else
      [*] = ;   ParserClearByHandle(pMountains); // we need to clear previous patterns because apparently machineparser is not cleared on new map generation
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;begin
      [*] = ;   if (gBoolRegister_EditorFastGeneration) then
      [*] = ;   _map_LevelTerrain();
      [*] = ;   SetMapEditorData;
      [*] = ;   SetMapEditorPlayers;
      [*] = ;   _map_GenerateSimpleMountainPatterns();
      [*] = ;   CalcDistancesToCastles(true);
      [*] = ;end
      [*] = ;else
      [*] = ;if gTutorial.map then
      [*] = ;begin
      [*] = ;   SetTutorialData;
      [*] = ;   _map_GenerateSimpleMountainPatterns();
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   // world rule Guarded world
      [*] = ;   if _worldrule_GetWorldRuleAbilityExistByID(13) and (_worldrule_GetWorldRuleAbilityParam1(13)=1) then
      [*] = ;   begin
      [*] = ;      // Хранители мира -  4 игрока, 4 хребта, 2 провинции в центре, 10х10
      [*] = ;      if (mapPlayers<>4) or (mapX<>10) then
      [*] = ;      ErrorLog('worldrule = Хранители мира (AbilityID = 13, Param1 = 1), bad map condition');
      [*] = ;
      [*] = ;      for i := 0 to 4 do
      [*] = ;      begin
      [*] = ;         var ind : Integer = 4 + i * 10;
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_MountainTerrainType);
      [*] = ;         MaxMountainCount := MaxMountainCount + 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 5 to 9 do
      [*] = ;      begin
      [*] = ;         var ind : Integer = 5 + i * 10;
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_MountainTerrainType);
      [*] = ;         MaxMountainCount := MaxMountainCount + 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 0 to 3 do
      [*] = ;      begin
      [*] = ;         var ind : Integer = 5 * 10 + i;
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_MountainTerrainType);
      [*] = ;         MaxMountainCount := MaxMountainCount + 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 6 to 9 do
      [*] = ;      begin
      [*] = ;         var ind : Integer = 4 * 10 + i;
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_MountainTerrainType);
      [*] = ;         MaxMountainCount := MaxMountainCount + 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         if ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType') = gc_MountainTerrainType then
      [*] = ;         begin
      [*] = ;            var posX, posY, posZ : Float;
      [*] = ;            GetTrackNodePositionByIndex(i, posX, posY, posZ);
      [*] = ;
      [*] = ;            var patName : String = 'map-hexmountain-1-1';
      [*] = ;            if RandomExt < 0.5 then
      [*] = ;            patName := 'map-hexmountain-1-2';
      [*] = ;
      [*] = ;            var pMountain : Integer = ParserAddChildByIndex(pMountains, '*');
      [*] = ;            ParserSetValueByKeyByHandle(pMountain, 'PatternName', patName);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pMountain, 'PosX', posX);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pMountain, 'PosZ', posZ);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      // setup water cells
      [*] = ;      MaxZoneCount := Floor(HexCount * mapWater / 100);
      [*] = ;      var IslesCount : Integer = Floor(mapIsles * MaxZoneCount / 100);
      [*] = ;
      [*] = ;      iFloodDeep := Floor(MaxZoneCount/10+5);
      [*] = ;      Log('Water flood deep = ' + IntToStr(iFloodDeep));
      [*] = ;      var WaterRadius : Integer = Floor(iFloodDeep*15/mapDissolve);
      [*] = ;      Log('Water radius = ' + IntToStr(WaterRadius));
      [*] = ;
      [*] = ;      spotCount := 0;
      [*] = ;      ZoneCount := 0;
      [*] = ;
      [*] = ;      // generating water
      [*] = ;      case gGame.map.typ of
      [*] = ;         1 :
      [*] = ;         begin
      [*] = ;            for i := 0 to mapY-1 do
      [*] = ;            begin
      [*] = ;               var ind : Integer = i;
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_WaterTerrainType);
      [*] = ;
      [*] = ;               ind := HexCount - 1 - i;
      [*] = ;               pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_WaterTerrainType);
      [*] = ;            end;
      [*] = ;
      [*] = ;            for i := 0 to mapX-1 do
      [*] = ;            begin
      [*] = ;               var ind : Integer = i * mapY;
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_WaterTerrainType);
      [*] = ;
      [*] = ;               ind := ind + mapY- 1;
      [*] = ;               pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_WaterTerrainType);
      [*] = ;            end;
      [*] = ;
      [*] = ;            ZoneCount := (mapX + mapY - 2) * 2;
      [*] = ;
      [*] = ;            while ZoneCount < MaxZoneCount do
      [*] = ;            begin
      [*] = ;               ArrayClear;
      [*] = ;               for i := 0 to hexCount-1 do
      [*] = ;               begin
      [*] = ;                  var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;                  if ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType') = gc_WaterTerrainType then
      [*] = ;                  ArrayPushValue(i);
      [*] = ;               end;
      [*] = ;
      [*] = ;               var ind : Integer = _rand_Random(ArrayGetCount);
      [*] = ;               var hexInd : Integer = ArrayGetValueByIndex(ind);
      [*] = ;
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, hexInd);
      [*] = ;               PutZoneSpot(ind, WaterRadius, gc_WaterTerrainType);
      [*] = ;               spotCount := spotCount + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         0, 2 :
      [*] = ;         begin
      [*] = ;            while ZoneCount < MaxZoneCount do
      [*] = ;            begin
      [*] = ;               var ind : Integer = _rand_Random(HexCount);
      [*] = ;
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;               var freq : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'Freq');
      [*] = ;
      [*] = ;               if freq = -1 then
      [*] = ;               begin
      [*] = ;                  PutZoneSpot(ind, WaterRadius, gc_WaterTerrainType);
      [*] = ;                  spotCount := spotCount + 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      Log('Water spot count = ' + IntToStr(spotCount));
      [*] = ;
      [*] = ;      // putting isles
      [*] = ;      var tType : Integer;
      [*] = ;      var pStratHexCell : Integer;
      [*] = ;      var freq : Float;
      [*] = ;
      [*] = ;      Log('Isles count = ' + IntToStr(IslesCount));
      [*] = ;      for i := 0 to IslesCount-1 do
      [*] = ;      begin
      [*] = ;         ArrayClear();
      [*] = ;         for j := 0 to hexCount-1 do
      [*] = ;         begin
      [*] = ;            var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, j);
      [*] = ;            if ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType') = gc_WaterTerrainType then
      [*] = ;               ArrayPushValue(j);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if ArrayGetCount() > 0 then
      [*] = ;         begin
      [*] = ;            var ind : Integer = _rand_Random(ArrayGetCount());
      [*] = ;            var hexInd : Integer = ArrayGetValueByIndex(ind);
      [*] = ;            var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, hexInd);
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_PlainTerrainType);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Freq', -1);
      [*] = ;
      [*] = ;            ArrayClear();
      [*] = ;            for j := 0 to hexCount-1 do
      [*] = ;            begin
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, j);
      [*] = ;               if ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType') = gc_PlainTerrainType then
      [*] = ;                  ArrayPushValue(j);
      [*] = ;            end;
      [*] = ;
      [*] = ;            if ArrayGetCount() > 0 then
      [*] = ;            begin
      [*] = ;               var ind : Integer = _rand_Random(ArrayGetCount);
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ArrayGetValueByIndex(ind));
      [*] = ;
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_WaterTerrainType);
      [*] = ;               ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Freq', 1);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // put mountains
      [*] = ;      var pMountainPatterns : Integer = 0;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pPatternCover)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pHandle : Integer = ParserSelectByHandleByIndex(pPatternCover, i);
      [*] = ;
      [*] = ;         var TerrainType : String = ParserGetValueByKeyByHandle(pHandle, 'TerrainType');
      [*] = ;         if SameText(TerrainType, 'Mountain') then
      [*] = ;         begin
      [*] = ;            pMountainPatterns := pHandle;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      pMountainPatterns := ParserSelectByHandleByKey(pMountainPatterns, 'PatternPriority');
      [*] = ;      pMountainPatterns := ParserSelectByHandleByIndex(pMountainPatterns, 0);
      [*] = ;      pMountainPatterns := ParserSelectByHandleByKey(pMountainPatterns, 'PatternList');
      [*] = ;
      [*] = ;      for i := 0 to HexCount-1 do
      [*] = ;      begin
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;         if TerrainType = gc_WaterTerrainType then
      [*] = ;            WaterCount := WaterCount + 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if pMountainPatterns <> 0 then
      [*] = ;      begin
      [*] = ;         MaxMountainCount := Round((HexCount - WaterCount) * mapHill * 0.32 / 100);
      [*] = ;         var mCount : Integer = 0;
      [*] = ;
      [*] = ;         Log('Mountain count = ' + IntToStr(MaxMountainCount));
      [*] = ;         var tryCount : Integer = 0;
      [*] = ;
      [*] = ;         while (mCount < MaxMountainCount) and (tryCount < cMaxMountainTryCount) do
      [*] = ;         begin
      [*] = ;            tryCount := tryCount + 1;
      [*] = ;            var ind : Integer = _rand_Random(HexCount);
      [*] = ;            var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;            var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;
      [*] = ;            if TerrainType = gc_PlainTerrainType then
      [*] = ;            begin
      [*] = ;               var patternIndex : Integer = _misc_GetRandomPatternIndex(pMountainPatterns, curVisualID, True); // we need RandomExt here because the pattern could alter other provinces terrain depending on what's picked.
      [*] = ;               var pPattern : Integer = ParserSelectByHandleByIndex(pMountainPatterns, patternIndex);
      [*] = ;
      [*] = ;               if MountainPatternAllowed(pPattern, ind) then
      [*] = ;               begin
      [*] = ;                  var indHexMask : Integer;
      [*] = ;                  var posX, posY, posZ, angle : Float;
      [*] = ;                  GetTrackNodePositionByIndex(ind, posX, posY, posZ);
      [*] = ;                  
      [*] = ;                  var patName : String = ParserGetValueByKeyByHandle(pPattern, 'PatternName');
      [*] = ;                  //Log('Mountain position : (' + FloatToStr(posX) + ', ' + FloatToStr(posZ) + ')');
      [*] = ;                  //StandPattern(patPlHandle, patName, posX, posZ, 0);
      [*] = ;                  var pMountain : Integer = ParserAddChildByIndex(pMountains, '*');
      [*] = ;                  ParserSetValueByKeyByHandle(pMountain, 'PatternName', patName);
      [*] = ;                  ParserSetFloatValueByKeyByHandle(pMountain, 'PosX', posX);
      [*] = ;                  ParserSetFloatValueByKeyByHandle(pMountain, 'PosZ', posZ);
      [*] = ;               
      [*] = ;                  var pMask : Integer = ParserSelectByHandleByKey(pPattern, 'Mask');
      [*] = ;
      [*] = ;                  mCount := mCount + ParserGetCountByHandle(pMask);
      [*] = ;
      [*] = ;                  for i := ParserGetCountByHandle(pMask)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     GetMaskHex(ParserSelectByHandleByIndex(pMask, i), ind, indHexMask, angle);
      [*] = ;                     
      [*] = ;                     var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, indHexMask);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHexCell, 'TerrainType', gc_MountainTerrainType);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;      if TerrainType = gc_MountainTerrainType then
      [*] = ;         MountainCount := MountainCount + 1;
      [*] = ;   end;
      [*] = ;   Log('___________________________________________');
      [*] = ;
      [*] = ;   // setup hill cells
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Freq', -1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   MaxZoneCount := Floor((HexCount - WaterCount) * mapHill / 100) - MaxMountainCount;
      [*] = ;
      [*] = ;   iFloodDeep := Floor(MaxZoneCount/10+6);
      [*] = ;   Log('Hill flood deep = ' + IntToStr(iFloodDeep));
      [*] = ;   var HillRadius : Integer = Floor(iFloodDeep*10/mapDissolve);
      [*] = ;   Log('Hill radius = ' + IntToStr(HillRadius));
      [*] = ;
      [*] = ;   spotCount := 0;
      [*] = ;   ZoneCount := 0;
      [*] = ;
      [*] = ;   while ZoneCount < MaxZoneCount do
      [*] = ;   begin
      [*] = ;      var count : Integer = 0;
      [*] = ;      _rand_ClearRoll;
      [*] = ;      for i := 0 to HexCount-1 do
      [*] = ;      begin
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;         if terType = gc_PlainTerrainType then
      [*] = ;         begin
      [*] = ;            gArrRollerN[count] := i;
      [*] = ;            gArrRollerP[count] := 1;
      [*] = ;            count := count + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if count = 0 then
      [*] = ;      break;
      [*] = ;
      [*] = ;      var ind : Integer = _rand_Roll(false);
      [*] = ;      HillCount := HillCount + PutZoneSpot(ind, HillRadius, gc_HillTerrainType);
      [*] = ;      spotCount := spotCount + 1;
      [*] = ;   end;
      [*] = ;   Log('Hill spot count = ' + IntToStr(spotCount));
      [*] = ;   Log('___________________________________________');
      [*] = ;
      [*] = ;   // setup forest cells
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Freq', -1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   MaxZoneCount := Floor((HexCount - WaterCount) * mapForest / 100);
      [*] = ;   if MaxZoneCount + WaterCount + MountainCount + HillCount <= HexCount then
      [*] = ;   begin
      [*] = ;      iFloodDeep := Floor(MaxZoneCount/10+6);
      [*] = ;      Log('Forest flood deep = ' + IntToStr(iFloodDeep));
      [*] = ;      var ForestRadius : Integer = Floor(iFloodDeep*10/mapDissolve);
      [*] = ;      Log('Forest radius = ' + IntToStr(ForestRadius));
      [*] = ;
      [*] = ;      spotCount := 0;
      [*] = ;      ZoneCount := 0;
      [*] = ;
      [*] = ;      while ZoneCount < MaxZoneCount do
      [*] = ;      begin
      [*] = ;         var count : Integer = 0;
      [*] = ;         _rand_ClearRoll;
      [*] = ;         for i := 0 to HexCount-1 do
      [*] = ;         begin
      [*] = ;            var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;            var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;            if terType = gc_PlainTerrainType then
      [*] = ;            begin
      [*] = ;               gArrRollerN[count] := i;
      [*] = ;               gArrRollerP[count] := 1;
      [*] = ;               count := count + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if count = 0 then
      [*] = ;         break;
      [*] = ;
      [*] = ;         var ind : Integer = _rand_Roll(false);
      [*] = ;         ForestCount := ForestCount + PutZoneSpot(ind, ForestRadius, gc_ForestTerrainType);
      [*] = ;         spotCount := spotCount + 1;
      [*] = ;      end;
      [*] = ;      Log('Forest spot count = ' + IntToStr(spotCount));
      [*] = ;      Log('___________________________________________');
      [*] = ;   end;
      [*] = ;
      [*] = ;   // setup swamp cells
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Freq', -1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   MaxZoneCount := Floor((HexCount - WaterCount) * mapSwamp / 100);
      [*] = ;   if (MaxZoneCount + WaterCount + MountainCount + HillCount + ForestCount) > HexCount then
      [*] = ;   begin
      [*] = ;      MaxZoneCount := (HexCount - (WaterCount + MountainCount + HillCount + ForestCount)) div 2;
      [*] = ;   end;
      [*] = ;
      [*] = ;   iFloodDeep := Floor(MaxZoneCount/10+6);
      [*] = ;   Log('Swamp flood deep = ' + IntToStr(iFloodDeep));
      [*] = ;   var SwampRadius : Integer = Floor(iFloodDeep*10/mapDissolve);
      [*] = ;   Log('Swamp radius = ' + IntToStr(SwampRadius));
      [*] = ;
      [*] = ;   spotCount := 0;
      [*] = ;   ZoneCount := 0;
      [*] = ;
      [*] = ;   while ZoneCount < MaxZoneCount do
      [*] = ;   begin
      [*] = ;      var count : Integer = 0;
      [*] = ;      _rand_ClearRoll;
      [*] = ;      for i := 0 to HexCount-1 do
      [*] = ;      begin
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;         if terType = gc_PlainTerrainType then
      [*] = ;         begin
      [*] = ;            gArrRollerN[count] := i;
      [*] = ;            gArrRollerP[count] := 1;
      [*] = ;            count := count + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if count = 0 then
      [*] = ;      break;
      [*] = ;
      [*] = ;      var ind : Integer = _rand_Roll(false);
      [*] = ;      SwampCount := SwampCount + PutZoneSpot(ind, SwampRadius, gc_SwampTerrainType);
      [*] = ;      spotCount := spotCount + 1;
      [*] = ;   end;
      [*] = ;   Log('Swamp spot count = ' + IntToStr(spotCount));
      [*] = ;   Log('___________________________________________');
      [*] = ;
      [*] = ;   // setup desert cells
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Freq', -1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   MaxZoneCount := Floor((HexCount - WaterCount) * mapDesert / 100);
      [*] = ;   if (MaxZoneCount + WaterCount + MountainCount + HillCount + ForestCount + SwampCount) > HexCount then
      [*] = ;   begin
      [*] = ;      MaxZoneCount := (HexCount - (WaterCount + MountainCount + HillCount + ForestCount + SwampCount)) div 2;
      [*] = ;   end;
      [*] = ;
      [*] = ;   iFloodDeep := Floor(MaxZoneCount/10+6);
      [*] = ;   Log('Desert flood deep = ' + IntToStr(iFloodDeep));
      [*] = ;   var DesertRadius : Integer = Floor(iFloodDeep*15/mapDissolve);
      [*] = ;   Log('Desert radius = ' + IntToStr(DesertRadius));
      [*] = ;
      [*] = ;   spotCount := 0;
      [*] = ;   ZoneCount := 0;
      [*] = ;
      [*] = ;   while ZoneCount < MaxZoneCount do
      [*] = ;   begin
      [*] = ;      var count : Integer = 0;
      [*] = ;      _rand_ClearRoll;
      [*] = ;      for i := 0 to HexCount-1 do
      [*] = ;      begin
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;         if terType = gc_PlainTerrainType then
      [*] = ;         begin
      [*] = ;            gArrRollerN[count] := i;
      [*] = ;            gArrRollerP[count] := 1;
      [*] = ;            count := count + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if count = 0 then
      [*] = ;      break;
      [*] = ;
      [*] = ;      DesertCount := DesertCount + PutZoneSpot(_rand_Roll(false), DesertRadius, gc_DesertTerrainType);
      [*] = ;      spotCount := spotCount + 1;
      [*] = ;   end;
      [*] = ;   Log('Desert spot count = ' + IntToStr(spotCount));
      [*] = ;   Log('___________________________________________');
      [*] = ;
      [*] = ;   // setup dead land cells
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Freq', -1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   MaxZoneCount := Floor((HexCount - WaterCount) * mapDeadLand / 100);
      [*] = ;   if (MaxZoneCount + WaterCount + MountainCount + HillCount + ForestCount + SwampCount + DesertCount) > HexCount then
      [*] = ;   begin
      [*] = ;      MaxZoneCount := (HexCount - (WaterCount + MountainCount + HillCount + ForestCount + SwampCount + DesertCount)) div 2;
      [*] = ;   end;
      [*] = ;
      [*] = ;   iFloodDeep := Floor(MaxZoneCount/10+6);
      [*] = ;   Log('Dead land flood deep = ' + IntToStr(iFloodDeep));
      [*] = ;   var DeadLandRadius : Integer = Floor(iFloodDeep*40/mapDissolve);
      [*] = ;   Log('Dead land radius = ' + IntToStr(DeadLandRadius));
      [*] = ;
      [*] = ;   spotCount := 0;
      [*] = ;   ZoneCount := 0;
      [*] = ;
      [*] = ;   while ZoneCount < MaxZoneCount do
      [*] = ;   begin
      [*] = ;      var count : Integer = 0;
      [*] = ;      _rand_ClearRoll;
      [*] = ;      for i := 0 to HexCount-1 do
      [*] = ;      begin
      [*] = ;         var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;         if terType = gc_PlainTerrainType then
      [*] = ;         begin
      [*] = ;            gArrRollerN[count] := i;
      [*] = ;            gArrRollerP[count] := 1;
      [*] = ;            count := count + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if count = 0 then
      [*] = ;      break;
      [*] = ;
      [*] = ;      var ind : Integer = _rand_Roll(false);
      [*] = ;      DeadLandCount := DeadLandCount + PutZoneSpot(ind, DeadLandRadius, gc_DeadLandTerrainType);
      [*] = ;      spotCount := spotCount + 1;
      [*] = ;   end;
      [*] = ;   Log('Dead land spot count = ' + IntToStr(spotCount));
      [*] = ;   Log('___________________________________________');
      [*] = ;
      [*] = ;   Log('Water count = ' + IntToStr(WaterCount));
      [*] = ;   Log('Mountain count = ' + IntToStr(MountainCount));
      [*] = ;   Log('Forest count = ' + IntToStr(ForestCount));
      [*] = ;   Log('Hill count = ' + IntToStr(HillCount));
      [*] = ;   Log('Swamp count = ' + IntToStr(SwampCount));
      [*] = ;   Log('Desert count = ' + IntToStr(DesertCount));
      [*] = ;   Log('Dead land count = ' + IntToStr(DeadLandCount));
      [*] = ;   Log('Plain count = ' + IntToStr(PlainCount));
      [*] = ;
      [*] = ;   // setup castles
      [*] = ;   if _worldrule_GetWorldRuleAbilityExistByID(13) and (_worldrule_GetWorldRuleAbilityParam1(13)=1) then // Хранители мира -  4 игрока, 4 хребта, 2 провинции в центре, 10х10
      [*] = ;   begin
      [*] = ;      ArrayClear();
      [*] = ;      for i := 0 to 3 do
      [*] = ;         ArrayPushValue(i);
      [*] = ;
      [*] = ;      InitCastle(1 + 1 * 10);
      [*] = ;      InitCastle((10 - 2) + 1 * 10);
      [*] = ;      InitCastle((10 - 2) + (10 - 2) * 10);
      [*] = ;      InitCastle(1 + (10 - 2) * 10);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var dist : Integer;
      [*] = ;      var freeHexCount : Integer;
      [*] = ;      var castleCount : Integer;
      [*] = ;      var f : Boolean;
      [*] = ;
      [*] = ;      for [DIST]dist := GridSize downto 1 do
      [*] = ;      begin
      [*] = ;         var minNeigh : Integer = 4;
      [*] = ;         if dist < 6 then
      [*] = ;         minNeigh := 3;
      [*] = ;
      [*] = ;         for [FREE]freeHexCount := 6 downto minNeigh do
      [*] = ;         begin
      [*] = ;            for i := 0 to HexCount-1 do
      [*] = ;            begin
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Castle', false);
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', cDefCastleDist);
      [*] = ;               ParserSetValueByKeyByHandle(pStratHexCell, 'Player', '');
      [*] = ;            end;
      [*] = ;
      [*] = ;            f := true;
      [*] = ;
      [*] = ;            for castleCount := 0 to mapPlayers-1 do
      [*] = ;            begin
      [*] = ;               CalcDistancesToCastles(false);
      [*] = ;               MakeHexArray(freeHexCount, dist, castleCount);
      [*] = ;               var arCount : Integer = ArrayGetCount;
      [*] = ;               if ArrayGetCount = 0 then
      [*] = ;               begin
      [*] = ;                  f := false;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var ind : Integer = _rand_Random(ArrayGetCount);
      [*] = ;               var hexInd : Integer = ArrayGetValueByIndex(ind);
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, hexInd);
      [*] = ;               var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;
      [*] = ;               var plHandle : Integer = GetPlayerHandleByIndex(castleCount);
      [*] = ;               var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;               var plInd : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;
      [*] = ;               ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Castle', true);
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'CastleDist', 0);
      [*] = ;               ParserSetValueByKeyByHandle(pStratHexCell, 'Player', plName);
      [*] = ;               //ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Checked', true);
      [*] = ;            end;
      [*] = ;
      [*] = ;            if f then
      [*] = ;            break(DIST);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;
      [*] = ;      if isCastle then
      [*] = ;      begin
      [*] = ;         var provPlName : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;         var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;         SetPlayerIntValueIndByHandle(provPlHandle, gc_map_PLStack_MapUnit_iCastleProvIndex, i);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var provPlName : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;      var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;      var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;
      [*] = ;      if isCastle then
      [*] = ;      begin
      [*] = ;         var plInd : Integer = -1;
      [*] = ;         var plHandle : Integer = 0;
      [*] = ;
      [*] = ;         for j := 0 to GetCountOfPlayers-1 do
      [*] = ;         begin
      [*] = ;            var tmpPlHandle : Integer = GetPlayerHandleByIndex(j);
      [*] = ;            if GetPlayerRaceTagByHandle(tmpPlHandle) = gc_map_PlayerRaceTag then
      [*] = ;            plInd := plInd + 1;
      [*] = ;
      [*] = ;            if tmpPlHandle = provPlHandle then
      [*] = ;            begin
      [*] = ;               plHandle := tmpPlHandle;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pProvinceType : Integer = ParserSelectByHandleByIndex(pProvinceTypes, 7);
      [*] = ;         var prRace : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'RaceID');
      [*] = ;         var pProvinceName : Integer = ParserSelectByHandleByIndex(pProvinceNames, 11);
      [*] = ;         var prName : String = ParserGetValueByKeyByHandle(pProvinceName, 'Name');
      [*] = ;
      [*] = ;         if (prName='') then
      [*] = ;         prName := provPlName + '.Province';
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType', 7);
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'ProvinceRace', prRace);
      [*] = ;         ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', prName);
      [*] = ;
      [*] = ;         var iPopulation : Integer = 10;
      [*] = ;         var iGoldInc : Integer = 0;
      [*] = ;         var iGemInc  : Integer = 0;
      [*] = ;         var iExplore : Integer = 0;
      [*] = ;
      [*] = ;         ChangeTerrainType(pStratHexCell);
      [*] = ;         for j := 0 to 5 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := j;
      [*] = ;            ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;            ChangeTerrainType(IntRegister2);
      [*] = ;         end;
      [*] = ;         var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;
      [*] = ;         case terType of
      [*] = ;            gc_ForestTerrainType, gc_HillTerrainType :
      [*] = ;            begin
      [*] = ;               iGoldInc := 12;
      [*] = ;               iGemInc := 4;
      [*] = ;               iExplore := 50;
      [*] = ;            end;
      [*] = ;            gc_SwampTerrainType :
      [*] = ;            begin
      [*] = ;               iGoldInc := 9;
      [*] = ;               iGemInc := 5;
      [*] = ;               iExplore := 40;
      [*] = ;            end;
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               iGoldInc := 15;
      [*] = ;               iGemInc := 3;
      [*] = ;               iExplore := 60;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;         if (cMode='cmPlayer') then
      [*] = ;         begin
      [*] = ;            iGoldInc := iGoldInc + gGame.arrplayerdifficulty[plInd].goldincomeadd;
      [*] = ;            iGemInc := iGemInc + gGame.arrplayerdifficulty[plInd].gemincomeadd;
      [*] = ;            if _map_CheckGenesisMode(gc_GM_BonusIncome) then
      [*] = ;            begin
      [*] = ;               iGoldInc := iGoldInc - 5;
      [*] = ;               iGemInc := iGemInc - 2;
      [*] = ;            end;
      [*] = ;            iPopulation := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.difficulty.handle, gGame.arrplayerdifficulty[plInd].basediff), 'Population');
      [*] = ;         end;
      [*] = ;
      [*] = ;         // world rule
      [*] = ;         if (_worldrule_GetWorldRuleAbilityExistByID(1)) then
      [*] = ;         begin
      [*] = ;            var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(1);
      [*] = ;            var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(1);
      [*] = ;            iGoldInc := (iGoldInc*param1) div 100;
      [*] = ;            iGemInc := (iGemInc*param2) div 100;
      [*] = ;         end;
      [*] = ;         if (_worldrule_GetWorldRuleAbilityExistByID(20)) then
      [*] = ;         begin
      [*] = ;            var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(20);
      [*] = ;            var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(20);
      [*] = ;            if (terType=param1) then
      [*] = ;            iGemInc := (iGemInc*param2) div 100;
      [*] = ;         end;
      [*] = ;         if (_worldrule_GetWorldRuleAbilityExistByID(22)) then
      [*] = ;         begin
      [*] = ;            var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(22);
      [*] = ;            if (terType=param1) then
      [*] = ;            begin
      [*] = ;               var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(22);
      [*] = ;               if (iGoldInc+param2>0) then
      [*] = ;               iGoldInc := iGoldInc+param2
      [*] = ;               else
      [*] = ;               iGoldInc := 0;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (_worldrule_GetWorldRuleAbilityExistByID(23)) then
      [*] = ;         begin
      [*] = ;            var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(23);
      [*] = ;            if (terType=param1) then
      [*] = ;            begin
      [*] = ;               var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(23);
      [*] = ;               if (iGemInc+param2>0) then
      [*] = ;               iGemInc := iGemInc+param2
      [*] = ;               else
      [*] = ;               iGemInc := 0;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (_worldrule_GetWorldRuleAbilityExistByID(9)) then
      [*] = ;         begin
      [*] = ;            var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(9);
      [*] = ;            var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(9);
      [*] = ;            iExplore := round(Clamp(((iExplore*param1) div 100), 0, 100));
      [*] = ;            if (iPopulation>0) then
      [*] = ;            iPopulation := (iPopulation*param2) div 100;
      [*] = ;         end;
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'GoldInc', iGoldInc);
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'GemInc', iGemInc);
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'Explored', iExplore);
      [*] = ;         ParserSetIntValueByKeyByHandle(pStratHexCell, 'Population', iPopulation);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // calculate hex distances to castles
      [*] = ;   Log('Calculating distances to castles...');
      [*] = ;   CalcDistancesToCastles(true);
      [*] = ;
      [*] = ;   if _worldrule_GetWorldRuleAbilityExistByID(13) and (_worldrule_GetWorldRuleAbilityParam1(13)=1) then // Хранители мира -  4 игрока, 4 хребта, 2 провинции в центре, 10х10
      [*] = ;   begin
      [*] = ;      var terType : Integer = _worldrule_GetWorldRuleAbilityParam2(13);
      [*] = ;      var ind : Integer = 4 * 10 + 5;
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', terType);
      [*] = ;
      [*] = ;      ind := 5 * 10 + 4;
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', terType);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // setting castle name and place special site for PC players
      [*] = ;   Log('Setting castle name and place special site for PC players');
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var name : String = '';
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;
      [*] = ;      var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;      if isCastle then
      [*] = ;      begin
      [*] = ;         var plName : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;         var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;         var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;         var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;         var plProfile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;         if _log then _Log_map('Found castle of '+plName+' controlled by '+cMode);
      [*] = ;         if _log then _log_valuesM('   PL_HANDLE|PL_INDEX|PL_PROFILE',plHandle,plIndex,plProfile,0,0,0);
      [*] = ;         if cMode = 'cmPlayer' then
      [*] = ;         begin
      [*] = ;            case gGame.gameType of
      [*] = ;               gc_GameTypeCampaign, gc_GameTypeCustom : name := gProfile.land;
      [*] = ;               gc_GameTypeHotseat : name := gArrHotseatProfiles[plIndex].land;
      [*] = ;               gc_GameTypeLanShard : name := gLanShardGame.arrLanPlayers[plIndex].profile.land;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (name='') or (gIntRegister_CurDemoMode>0) then //demo map should use makecastlename, even if we have name. Or we get other map.
      [*] = ;               MakeCastleName(pStratHexCell)
      [*] = ;            else
      [*] = ;               ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', name);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if plProfile > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := plProfile;
      [*] = ;               ExecuteState('GetProfileParserByID');
      [*] = ;               var pProfile : Integer = IntRegister1;
      [*] = ;
      [*] = ;               name := 'players|'+IntToStr(plProfile)+'.castlename'; //ParserGetValueByKeyByHandle(pProfile, 'ProvName');
      [*] = ;               ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', name);
      [*] = ;
      [*] = ;               case plProfile of
      [*] = ;                  5 : ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_ForestTerrainType);
      [*] = ;                  12 : ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_ForestTerrainType);
      [*] = ;                  13 : ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_SwampTerrainType);
      [*] = ;                  14 : ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_HillTerrainType);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               MakeCastleName(pStratHexCell);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if _log then _Log_map('   Castle named as '+ParserGetValueByKeyByHandle(pStratHexCell, 'ProvinceName'));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   Log('Setting extra visuals. Visual ID='+IntToStr(curVisualID));
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;
      [*] = ;      case curVisualID of
      [*] = ;         2 : begin
      [*] = ;            if (TerrainType=gc_PlainTerrainType) then
      [*] = ;            begin
      [*] = ;               TerrainType := gc_DesertTerrainType;
      [*] = ;               var castleDist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'CastleDist');
      [*] = ;               if (castleDist=2) then // first circle around castle
      [*] = ;               begin
      [*] = ;                  var randTerType : Integer = gc_ForestTerrainType + _rand_Random(3); // forest, swamp, hill
      [*] = ;                  ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', randTerType);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_DesertTerrainType);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            if (TerrainType=gc_PlainTerrainType) then
      [*] = ;            begin
      [*] = ;               TerrainType := gc_DeadLandTerrainType;
      [*] = ;               var castleDist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'CastleDist');
      [*] = ;               if (castleDist=2) then // first circle around castle
      [*] = ;               begin
      [*] = ;                  var randTerType : Integer = gc_ForestTerrainType + _rand_Random(3); // forest, swamp, hill
      [*] = ;                  ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', randTerType);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCell, 'TerrainType', gc_DeadLandTerrainType);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // setting resources around castles
      [*] = ;   pResourceCount := _misc_ParserGetOrCreateByKey('ResourceCount',true);
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pResources)-1 do
      [*] = ;   begin
      [*] = ;      var pResource : Integer = ParserSelectByHandleByIndex(pResources, i);
      [*] = ;      var resName : String = ParserGetValueByKeyByHandle(pResource, 'Name');
      [*] = ;      ParserSetIntValueByKeyByHandle(pResourceCount, resName, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   Log('Setting resources around castles...');
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var index : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Index');
      [*] = ;      var castle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;
      [*] = ;      if castle then
      [*] = ;      begin
      [*] = ;         var FirstInd : Integer = -1;
      [*] = ;         var SecondInd : Integer = -1;
      [*] = ;
      [*] = ;         var pFirstHexCell : Integer = 0;
      [*] = ;         var pSecondHexCell : Integer = 0;
      [*] = ;
      [*] = ;         var FirstTerrainType : Integer = 0;
      [*] = ;         var SecondTerrainType : Integer = 0;
      [*] = ;
      [*] = ;         // searching in second circle
      [*] = ;         for [MAIN]j := 0 to 5 do
      [*] = ;         begin
      [*] = ;            //var angle : Float = 60 * j;
      [*] = ;            //var ind : Integer = _map_GetNeighbourHexIndexByAngle(i, angle);
      [*] = ;            //var pStratHexCell1 : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;            IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := j;
      [*] = ;            ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;            var pStratHexCell1 : Integer = IntRegister2;
      [*] = ;            var ind : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell1, 'Index');
      [*] = ;
      [*] = ;            if IsHexWithResource(pStratHexCell1) > 0 then
      [*] = ;            begin
      [*] = ;               for k := 0 to 5 do
      [*] = ;               begin
      [*] = ;                  //var angle1 : Float = 60 * k;
      [*] = ;                  //var nextInd : Integer = _map_GetNeighbourHexIndexByAngle(ind, angle1);
      [*] = ;                  //var pStratHexCell2 : Integer = ParserSelectByHandleByIndex(pStratHexCells, nextInd);
      [*] = ;                  IntRegister0 := pStratHexCell1;
      [*] = ;                  IntRegister1 := k;
      [*] = ;                  ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;                  var pStratHexCell2 : Integer = IntRegister2;
      [*] = ;                  var nextInd : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell2, 'Index');
      [*] = ;                  var tType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell2, 'TerrainType');
      [*] = ;
      [*] = ;                  if IsHexWithResource(pStratHexCell2) = 2 then
      [*] = ;                  begin
      [*] = ;                     var CastleDist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell2, 'CastleDist');
      [*] = ;                     if CastleDist = 3 then
      [*] = ;                     begin
      [*] = ;                        if pFirstHexCell = 0 then
      [*] = ;                        begin
      [*] = ;                           FirstInd := nextInd;
      [*] = ;                           pFirstHexCell := pStratHexCell2;
      [*] = ;                           FirstTerrainType := tType;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           if tType <> FirstTerrainType then
      [*] = ;                           begin
      [*] = ;                              SecondInd := nextInd;
      [*] = ;                              pSecondHexCell := pStratHexCell2;
      [*] = ;                              SecondTerrainType := tType;
      [*] = ;                              break(MAIN);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // searching in first circle
      [*] = ;         if pSecondHexCell = 0 then
      [*] = ;         begin
      [*] = ;            for [MAIN]j := 0 to 5 do
      [*] = ;            begin
      [*] = ;               //var angle : Float = 60 * j;
      [*] = ;               //var ind : Integer = _map_GetNeighbourHexIndexByAngle(i, angle);
      [*] = ;               //var pStratHexCell1 : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;               IntRegister0 := pStratHexCell;
      [*] = ;               IntRegister1 := j;
      [*] = ;               ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;               var pStratHexCell1 : Integer = IntRegister2;
      [*] = ;               var ind : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell1, 'Index');
      [*] = ;               var tType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell1, 'TerrainType');
      [*] = ;
      [*] = ;               if IsHexWithResource(pStratHexCell1) = 2 then
      [*] = ;               begin
      [*] = ;                  if pFirstHexCell = 0 then
      [*] = ;                  begin
      [*] = ;                     FirstInd := ind;
      [*] = ;                     pFirstHexCell := pStratHexCell1;
      [*] = ;                     FirstTerrainType := tType;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if tType <> FirstTerrainType then
      [*] = ;                     begin
      [*] = ;                        SecondInd := ind;
      [*] = ;                        pSecondHexCell := pStratHexCell1;
      [*] = ;                        SecondTerrainType := tType;
      [*] = ;                        break(MAIN);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if pFirstHexCell = 0 then
      [*] = ;         continue;
      [*] = ;
      [*] = ;         // changing one of nearest terrain types
      [*] = ;         if pSecondHexCell = 0 then
      [*] = ;         begin
      [*] = ;            ArrayClear;
      [*] = ;            for j := 0 to 5 do
      [*] = ;            begin
      [*] = ;               //var angle : Float = 60 * j;
      [*] = ;               //var ind : Integer = _map_GetNeighbourHexIndexByAngle(i, angle);
      [*] = ;               //var pStratHexCell1 : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;               IntRegister0 := pStratHexCell;
      [*] = ;               IntRegister1 := j;
      [*] = ;               ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;               var pStratHexCell1 : Integer = IntRegister2;
      [*] = ;               var ind : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell1, 'Index');
      [*] = ;
      [*] = ;               if IsHexWithResource(pStratHexCell1) > 0 then
      [*] = ;               begin
      [*] = ;                  if ind <> FirstInd then
      [*] = ;                  ArrayPushValue(ind);
      [*] = ;
      [*] = ;                  for k := 0 to 5 do
      [*] = ;                  begin
      [*] = ;                     //var angle1 : Float = 60 * k;
      [*] = ;                     //var nextInd : Integer = _map_GetNeighbourHexIndexByAngle(ind, angle1);
      [*] = ;                     //var pStratHexCell2 : Integer = ParserSelectByHandleByIndex(pStratHexCells, nextInd);
      [*] = ;                     IntRegister0 := pStratHexCell1;
      [*] = ;                     IntRegister1 := k;
      [*] = ;                     ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;                     var pStratHexCell2 : Integer = IntRegister2;
      [*] = ;                     var nextInd : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell2, 'Index');
      [*] = ;
      [*] = ;                     if (IsHexWithResource(pStratHexCell2) > 0) and (pStratHexCell2 <> pStratHexCell) then
      [*] = ;                     begin
      [*] = ;                        if nextInd <> FirstInd then
      [*] = ;                        ArrayPushValue(nextInd);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if ArrayGetCount > 0 then
      [*] = ;            begin
      [*] = ;               // choosing hex to change
      [*] = ;               var ind : Integer = _rand_Random(ArrayGetCount);
      [*] = ;               ind := ArrayGetValueByIndex(ind);
      [*] = ;
      [*] = ;               // choosing new terrain type
      [*] = ;               var tInd : Integer = -1;
      [*] = ;               while (tInd = FirstTerrainType) or (tInd = gc_DeadLandTerrainType) or (tInd = gc_DesertTerrainType) do
      [*] = ;               tInd := _rand_Random(ParserGetCountByHandle(pTerrainTypes));
      [*] = ;
      [*] = ;               SecondInd := ind;
      [*] = ;               pSecondHexCell := ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;
      [*] = ;               ParserSetIntValueByKeyByHandle(pSecondHexCell, 'TerrainType', tInd);
      [*] = ;
      [*] = ;               var countOld : Integer = GetTerrainTypeCount(FirstTerrainType);
      [*] = ;               var countNew : Integer = GetTerrainTypeCount(SecondTerrainType);
      [*] = ;               countOld := countOld-1;
      [*] = ;               countNew := countNew+1;
      [*] = ;               SetTerrainTypeCount(FirstTerrainType, countOld);
      [*] = ;               SetTerrainTypeCount(SecondTerrainType, countNew);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if pSecondHexCell = 0 then
      [*] = ;         continue;
      [*] = ;
      [*] = ;         // we have two hexes with different terrain types
      [*] = ;         SetResourceInHex(pFirstHexCell);
      [*] = ;         SetResourceInHex(pSecondHexCell);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // setting resources on map
      [*] = ;   Log('Setting resources on map...');
      [*] = ;   for i := 1 to ParserGetCountByHandle(pResources)-1 do
      [*] = ;   begin
      [*] = ;      var resInd : Integer = i;
      [*] = ;      var pResource : Integer = ParserSelectByHandleByIndex(pResources, i);
      [*] = ;      var resName : String = ParserGetValueByKeyByHandle(pResource, 'Name');
      [*] = ;      var resRarity : Integer = ParserGetIntValueByKeyByHandle(pResource, 'Rarity');
      [*] = ;      var MaxDrop : Integer = 1 + _rand_Random(2);
      [*] = ;      var TerrainType : Integer = 0;
      [*] = ;      var FreeLand : Integer;
      [*] = ;
      [*] = ;      var rCount : Integer = 0;
      [*] = ;      var rName : String;
      [*] = ;
      [*] = ;      if (i = 1) or (i = 6) or (i = 7) then
      [*] = ;      begin
      [*] = ;         rName := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pResources, 1), 'Name');
      [*] = ;         rCount := rCount + ParserGetIntValueByKeyByHandle(pResourceCount, rName);
      [*] = ;         rName := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pResources, 6), 'Name');
      [*] = ;         rCount := rCount + ParserGetIntValueByKeyByHandle(pResourceCount, rName);
      [*] = ;         rName := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pResources, 7), 'Name');
      [*] = ;         rCount := rCount + ParserGetIntValueByKeyByHandle(pResourceCount, rName);
      [*] = ;
      [*] = ;         MaxDrop := MaxDrop + Floor(HillCount / 7 / (resRarity + 1));
      [*] = ;         TerrainType := gc_HillTerrainType;
      [*] = ;         FreeLand := HillCount - rCount;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (i = 2) or (i = 8) then
      [*] = ;      begin
      [*] = ;         rName := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pResources, 2), 'Name');
      [*] = ;         rCount := rCount + ParserGetIntValueByKeyByHandle(pResourceCount, rName);
      [*] = ;         rName := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pResources, 8), 'Name');
      [*] = ;         rCount := rCount + ParserGetIntValueByKeyByHandle(pResourceCount, rName);
      [*] = ;
      [*] = ;         MaxDrop := MaxDrop + Floor(ForestCount / 7 / (resRarity + 1));
      [*] = ;         TerrainType := gc_ForestTerrainType;
      [*] = ;         FreeLand := ForestCount - rCount;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (i = 4) or (i = 5) or (i = 9) then
      [*] = ;      begin
      [*] = ;         rName := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pResources, 4), 'Name');
      [*] = ;         rCount := rCount + ParserGetIntValueByKeyByHandle(pResourceCount, rName);
      [*] = ;         rName := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pResources, 5), 'Name');
      [*] = ;         rCount := rCount + ParserGetIntValueByKeyByHandle(pResourceCount, rName);
      [*] = ;         rName := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pResources, 9), 'Name');
      [*] = ;         rCount := rCount + ParserGetIntValueByKeyByHandle(pResourceCount, rName);
      [*] = ;
      [*] = ;         MaxDrop := MaxDrop + Floor(SwampCount / 7 / (resRarity + 1));
      [*] = ;         TerrainType := gc_SwampTerrainType;
      [*] = ;         FreeLand := SwampCount - rCount;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (i = 3) then
      [*] = ;      begin
      [*] = ;         MaxDrop := MaxDrop + (HexCount - WaterCount - MountainCount - HillCount - ForestCount -
      [*] = ;         SwampCount - DesertCount - DeadLandCount) div 15;
      [*] = ;         TerrainType := gc_PlainTerrainType;
      [*] = ;         FreeLand := HexCount - WaterCount - MountainCount - HillCount - ForestCount -
      [*] = ;         SwampCount - DesertCount - DeadLandCount - ParserGetIntValueByIndexByHandle(pResourceCount, 3)
      [*] = ;      end;
      [*] = ;
      [*] = ;      MaxDrop := MaxDrop + mapResource div 3;
      [*] = ;      MaxDrop := MaxDrop + Floor(MaxDrop * (mapResource - 2) / 5);
      [*] = ;      var resCount : Integer = ParserGetIntValueByKeyByHandle(pResourceCount, resName);
      [*] = ;
      [*] = ;      var prCount : Integer = 0;
      [*] = ;      for j := 0 to cMaxProvCount-1 do
      [*] = ;      arrProvinces[j] := 0;
      [*] = ;
      [*] = ;      for j := 0 to HexCount-1 do
      [*] = ;      begin
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, j);
      [*] = ;         var hexTerrainType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'TerrainType');
      [*] = ;         var hexResource : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Resource');
      [*] = ;         var provType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'ProvinceType');
      [*] = ;
      [*] = ;         if IsHexAvailable(pHexCell) and (hexTerrainType = TerrainType) and (hexResource = 0) and (provType = 0) then
      [*] = ;         begin
      [*] = ;            arrProvinces[prCount] := j;
      [*] = ;            prCount := prCount + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //for j := 0 to FreeLand-2-1 do
      [*] = ;      //for j := 0 to MaxDrop - resCount - 1 do
      [*] = ;      var counter : Integer = Min(FreeLand - 2, MaxDrop - resCount);
      [*] = ;
      [*] = ;      for j := 0 to counter-1 do
      [*] = ;      //while (resCount < MaxDrop) and (FreeLand > 2) do
      [*] = ;      begin
      [*] = ;         if prCount = 0 then
      [*] = ;         break;
      [*] = ;
      [*] = ;         var arInd : Integer = _rand_Random(prCount);
      [*] = ;         var ind : Integer = arrProvinces[arInd];
      [*] = ;         for k := arInd to cMaxProvCount-2 do
      [*] = ;         arrProvinces[k] := arrProvinces[k+1];
      [*] = ;         prCount := prCount - 1;
      [*] = ;
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;         var CastleDist : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'CastleDist');
      [*] = ;         var resExplore : Integer = Floor(RandomExt * 20 + 40 + resRarity * 30 - CastleDist * 10);
      [*] = ;         resExplore := Round(Clamp(resExplore, 0, 100));
      [*] = ;         var bGuarded : Boolean = (resRarity * 2 + 3 > CastleDist);
      [*] = ;
      [*] = ;         SetProvinceResource(ind, resInd, resExplore, bGuarded);
      [*] = ;
      [*] = ;         resCount := resCount + 1;
      [*] = ;         FreeLand := FreeLand - 1;
      [*] = ;      end;
      [*] = ;      ParserSetIntValueByKeyByHandle(pResourceCount, resName, resCount);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('RandomizeVertices');
      [*] = ;
      [*] = ;// setting province names
      [*] = ;Log('Setting lake, sea and mountain province names...');
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'TerrainType');
      [*] = ;   var castle : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'Castle');
      [*] = ;
      [*] = ;   if castle then
      [*] = ;   continue;
      [*] = ;
      [*] = ;   if TerrainType = gc_MountainTerrainType then
      [*] = ;   ParserSetValueByKeyByHandle(pHexCell, 'ProvinceName', 'ProvinceName.Mountain')
      [*] = ;   else
      [*] = ;   if TerrainType = gc_WaterTerrainType then
      [*] = ;   begin
      [*] = ;      var waterCount : Integer = 0;
      [*] = ;      for j := 0 to 5 do
      [*] = ;      begin
      [*] = ;         //var angle : Float = j * 60;
      [*] = ;         //var ind : Integer = _map_GetNeighbourHexIndexByAngle(i, angle);
      [*] = ;         //var pNextHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;         IntRegister0 := pHexCell;
      [*] = ;         IntRegister1 := j;
      [*] = ;         ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;         var pNextHexCell : Integer = IntRegister2;
      [*] = ;
      [*] = ;         var nextTerrainType : Integer = ParserGetIntValueByKeyByHandle(pNextHexCell, 'TerrainType');
      [*] = ;         if nextTerrainType = gc_WaterTerrainType then
      [*] = ;         waterCount := waterCount + 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if waterCount = 0 then
      [*] = ;      ParserSetValueByKeyByHandle(pHexCell, 'ProvinceName', 'ProvinceName.Lake')
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ParserSetValueByKeyByHandle(pHexCell, 'ProvinceName', 'ProvinceName.Sea');
      [*] = ;         ParserSetBoolValueByKeyByHandle(pHexCell, 'Sea', true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// setting coast types
      [*] = ;Log('Setting coast types...');
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'TerrainType');
      [*] = ;
      [*] = ;   if TerrainType <> gc_WaterTerrainType then
      [*] = ;   begin
      [*] = ;      var waterCount : Integer = 0;
      [*] = ;      var seaCount : Integer = 0;
      [*] = ;
      [*] = ;      for j := 0 to 5 do
      [*] = ;      begin
      [*] = ;         //var angle : Float = j * 60;
      [*] = ;         //var ind : Integer = _map_GetNeighbourHexIndexByAngle(i, angle);
      [*] = ;         //var pNextHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;         IntRegister0 := pHexCell;
      [*] = ;         IntRegister1 := j;
      [*] = ;         ExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;         var pNextHexCell : Integer = IntRegister2;
      [*] = ;
      [*] = ;         var nextTerrainType : Integer = ParserGetIntValueByKeyByHandle(pNextHexCell, 'TerrainType');
      [*] = ;         if nextTerrainType = gc_WaterTerrainType then
      [*] = ;         begin
      [*] = ;            waterCount := waterCount + 1;
      [*] = ;            if ParserGetBoolValueByKeyByHandle(pNextHexCell, 'Sea') then
      [*] = ;            seaCount := seaCount + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      case waterCount of
      [*] = ;         0 : ParserSetIntValueByKeyByHandle(pHexCell, 'Coast', 0);
      [*] = ;         6 : ParserSetIntValueByKeyByHandle(pHexCell, 'Coast', 2);
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if seaCount > 0 then
      [*] = ;            ParserSetIntValueByKeyByHandle(pHexCell, 'Coast', 1)
      [*] = ;            else
      [*] = ;            ParserSetIntValueByKeyByHandle(pHexCell, 'Coast', 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var size : Float = 0;
      [*] = ;   
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'X', i div mapY);  //for some reason on shard map, Y is horizontal while X is vertical from map perspective, unlike in battles. This treats them same as in battles though.
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Y', i mod mapX);
      [*] = ;   
      [*] = ;   var x0, z0 : Float;
      [*] = ;   _map_GetVerticesCenter(pStratHexCell, x0, z0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'CenterX', x0);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'CenterY', z0);
      [*] = ;
      [*] = ;   var pHexVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;   for j := 0 to 5 do
      [*] = ;   begin
      [*] = ;      var pVertice : Integer = ParserSelectByHandleByIndex(pHexVertices, j);
      [*] = ;      var x1 : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;      var z1 : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;      pVertice := ParserSelectByHandleByIndex(pHexVertices, (j+1) mod 6);
      [*] = ;      var x2 : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;      var z2 : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;      size := size + GetTriangleArea(x0, z0, x1, z1, x2, z2);
      [*] = ;   end;
      [*] = ;   ParserSetFloatValueByKeyByHandle(pStratHexCell, 'Size', size);
      [*] = ;   avProvinceSize := avProvinceSize + size;
      [*] = ;end;
      [*] = ;
      [*] = ;avProvinceSize := avProvinceSize / HexCount;
      [*] = ;
      [*] = ;if (not gMapEditor.enabled) then
      [*] = ;begin
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var provType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'ProvinceType');
      [*] = ;      if provType > 0 then
      [*] = ;      ParserSetBoolValueByKeyByHandle(pHexCell, 'SetProvinceType', false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// setting province types, population, exploration, gold increase and gem increase
      [*] = ;Log('Setting province types, population, exploration, gold increase and gem increase...');
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var setProvType : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'SetProvinceType');
      [*] = ;
      [*] = ;   var castle : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'Castle');
      [*] = ;
      [*] = ;   if castle or (not IsHexAvailable(pHexCell)) or (not setProvType) then
      [*] = ;   continue;
      [*] = ;
      [*] = ;   var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'TerrainType');
      [*] = ;   var CastleDist : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'CastleDist');
      [*] = ;
      [*] = ;   IntRegister0 := TerrainType;
      [*] = ;   ExecuteState('GetTerrainParserByID');
      [*] = ;   var pTerrainType : Integer = IntRegister1;
      [*] = ;   var sTerrainType : String = ParserGetValueByKeyByHandle(pTerrainType, 'Name');
      [*] = ;
      [*] = ;   // world rule
      [*] = ;   var bWorldRuleProvinceTypesExist : Boolean = _worldrule_GetWorldRuleProvinceTypesExist;
      [*] = ;
      [*] = ;   _rand_ClearRoll;
      [*] = ;   var count : Integer = 0;
      [*] = ;
      [*] = ;   var pType : Integer = 1;
      [*] = ;   if (gMapEditor.enabled) and (gMapEditor.grid[i].provincetype<>0) then
      [*] = ;      pType := gMapEditor.grid[i].provincetype
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      for j := 0 to ParserGetCountByHandle(pProvinceTypes)-1 do
      [*] = ;      begin
      [*] = ;         var pProvinceType : Integer = ParserSelectByHandleByIndex(pProvinceTypes, j);
      [*] = ;         var diff : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'Difficulty');
      [*] = ;
      [*] = ;         if diff < CastleDist-1 then
      [*] = ;         begin
      [*] = ;            var pTerrainType : Integer = ParserSelectByHandleByKey(pProvinceType, 'TerrainType');
      [*] = ;            var freq : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, sTerrainType);
      [*] = ;
      [*] = ;            // world rule
      [*] = ;            if (bWorldRuleProvinceTypesExist) then
      [*] = ;            begin
      [*] = ;               if (_worldrule_GetWorldRuleProvinceTypeExistByID(j)) then
      [*] = ;               freq := (freq*_worldrule_GetWorldRuleProvinceTypePossibilityByID(j)) div 100;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if pProfile <> 0 then
      [*] = ;            begin
      [*] = ;               var provType : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'ProvType');
      [*] = ;               var provPoss : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'ProvPoss');
      [*] = ;
      [*] = ;               if provType = j then
      [*] = ;               freq := freq + provPoss;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if freq > 0 then
      [*] = ;            begin
      [*] = ;               gArrRollerN[count] := j;
      [*] = ;               gArrRollerP[count] := freq;
      [*] = ;               count := count + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if count > 0 then
      [*] = ;      pType := _rand_Roll(false)
      [*] = ;      else
      [*] = ;      pType := 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pProvinceType : Integer = ParserSelectByHandleByIndex(pProvinceTypes, pType);
      [*] = ;   var prDifficult : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'Difficulty');
      [*] = ;
      [*] = ;   {for j := 0 to ParserGetCountByHandle(pProvinceTypes)-1 do
      [*] = ;   begin
      [*] = ;      pProvinceType := ParserSelectByHandleByIndex(pProvinceTypes, j);
      [*] = ;      prDifficult := ParserGetIntValueByKeyByHandle(pProvinceType, 'Difficulty');
      [*] = ;
      [*] = ;      if prDifficult < CastleDist-1 then
      [*] = ;      begin
      [*] = ;         var pTerType : Integer = ParserSelectByHandleByKey(pProvinceType, 'TerrainType');
      [*] = ;         var freq : Integer = ParserGetIntValueByKeyByHandle(pTerType, sTerrainType);
      [*] = ;
      [*] = ;         // world rule
      [*] = ;         if (bWorldRuleProvinceTypesExist) then
      [*] = ;         begin
      [*] = ;            if (_worldrule_GetWorldRuleProvinceTypeExistByID(j)) then
      [*] = ;            freq := (freq*_worldrule_GetWorldRuleProvinceTypePossibilityByID(j)) div 100;
      [*] = ;         end;
      [*] = ;
      [*] = ;         curSum := curSum + freq;
      [*] = ;
      [*] = ;         if curSum > indSum then
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;
      [*] = ;   if _worldrule_GetWorldRuleAbilityExistByID(13) and (_worldrule_GetWorldRuleAbilityParam1(13)=1) then // Хранители мира -  4 игрока, 4 хребта, 2 провинции в центре, 10х10
      [*] = ;   begin
      [*] = ;      if (i = 4 * 10 + 5) or (i = 5 * 10 + 4) then
      [*] = ;      begin
      [*] = ;         var prType : Integer = _worldrule_GetWorldRuleAbilityParam1(19);
      [*] = ;         pProvinceType := ParserSelectByHandleByIndex(pProvinceTypes, prType);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var level : Integer = CastleDist - prDifficult;
      [*] = ;   level := Round(Clamp(level, 0, 3));
      [*] = ;
      [*] = ;   var prType : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'ProvinceTypeID');
      [*] = ;   var prRace : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'RaceID');
      [*] = ;   var prPopulation : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'Population');
      [*] = ;   var prLevelPop : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'LevelPop');
      [*] = ;   var prExplored : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'Explored');
      [*] = ;   var population : Integer = prPopulation + level * prLevelPop;
      [*] = ;
      [*] = ;   var terPopMode : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, 'Population');
      [*] = ;   var terExpMode : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, 'Explored');
      [*] = ;
      [*] = ;   if population > 0 then
      [*] = ;   begin
      [*] = ;      population := Floor(population * terPopMode / 100);
      [*] = ;      population := population + Floor(RandomExt * population / 5);
      [*] = ;      population := population + Floor(population * (mapPopulation - 2) / 5);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var levelExp : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'LevelExplored');
      [*] = ;   var explored : Integer;
      [*] = ;   explored := prExplored + level * levelExp + _rand_Random(5);
      [*] = ;   explored := Floor(explored * terExpMode / 100);
      [*] = ;   explored := explored + Floor(explored * (mapPopulation - 2) / 5);
      [*] = ;
      [*] = ;   // world rule
      [*] = ;   if (_worldrule_GetWorldRuleAbilityExistByID(9)) then
      [*] = ;   begin
      [*] = ;      var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(9);
      [*] = ;      var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(9);
      [*] = ;      explored := round(Clamp(((explored*param1) div 100), 0, 100));
      [*] = ;      if (population>0) then
      [*] = ;      population := (population*param2) div 100;
      [*] = ;   end;
      [*] = ;
      [*] = ;   explored := Round(Clamp(explored, 0, 100));
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'ProvinceType', prType);
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'ProvinceRace', prRace);
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'Population', population);
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'Explored', explored);
      [*] = ;
      [*] = ;   CalcProvinceIncome(pHexCell);
      [*] = ;end;
      [*] = ;
      [*] = ;// setting province names
      [*] = ;for j := 0 to ParserGetCountByHandle(pProvinceNames)-1 do
      [*] = ;begin
      [*] = ;   var pProvinceName  : Integer = ParserSelectByHandleByIndex(pProvinceNames, j);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pProvinceName, 'Busy', false);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pProvinceName, 'IsRight', false);
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   for j := 0 to ParserGetCountByHandle(pProvinceNames)-1 do
      [*] = ;   begin
      [*] = ;      var pProvinceName  : Integer = ParserSelectByHandleByIndex(pProvinceNames, j);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pProvinceName, 'IsRight', false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var setProvType : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'SetProvinceType');
      [*] = ;   var castle : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'Castle');
      [*] = ;
      [*] = ;   if castle or (not IsHexAvailable(pHexCell)) {or (not setProvType)} then
      [*] = ;   continue;
      [*] = ;
      [*] = ;   var myTerrainType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'TerrainType');
      [*] = ;   var myProvinceType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'ProvinceType');
      [*] = ;   var myCoast : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Coast');
      [*] = ;   var pProvinceName  : Integer;
      [*] = ;   var sum : Float = 0;
      [*] = ;
      [*] = ;   IntRegister0 := myTerrainType;
      [*] = ;   ExecuteState('GetTerrainParserByID');
      [*] = ;   var pTerrainType : Integer = IntRegister1;
      [*] = ;   var sTerrainType : String = ParserGetValueByKeyByHandle(pTerrainType, 'Name');
      [*] = ;
      [*] = ;   for j := 0 to ParserGetCountByHandle(pProvinceNames)-1 do
      [*] = ;   begin
      [*] = ;      pProvinceName := ParserSelectByHandleByIndex(pProvinceNames, j);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pProvinceName, 'IsRight', false);
      [*] = ;      var pTerrainTypes  : Integer = ParserSelectByHandleByKey(pProvinceName, 'TerrainList');
      [*] = ;      var pProvinceTypes : Integer = ParserSelectByHandleByKey(pProvinceName, 'ProvinceTypeList');
      [*] = ;      var Coast : Integer = ParserGetIntValueByKeyByHandle(pProvinceName, 'Coastal');
      [*] = ;      var Busy : Boolean = ParserGetBoolValueByKeyByHandle(pProvinceName, 'Busy');
      [*] = ;
      [*] = ;      if Busy = true then
      [*] = ;      continue;
      [*] = ;
      [*] = ;      if Coast <> myCoast then
      [*] = ;      continue;
      [*] = ;
      [*] = ;      var bTerrain  : Boolean = false;
      [*] = ;      var bProvince : Boolean = false;
      [*] = ;
      [*] = ;      for k := 0 to ParserGetCountByHandle(pTerrainTypes)-1 do
      [*] = ;      begin
      [*] = ;         var pTerrainType : Integer = ParserSelectByHandleByIndex(pTerrainTypes, k);
      [*] = ;         var tType : String = ParserGetValueByKeyByHandle(pTerrainType, 'TerrainType');
      [*] = ;
      [*] = ;         if SameText(sTerrainType, tType) or (tType = '') then
      [*] = ;         begin
      [*] = ;            bTerrain := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for k := 0 to ParserGetCountByHandle(pProvinceTypes)-1 do
      [*] = ;      begin
      [*] = ;         var pProvinceType : Integer = ParserSelectByHandleByIndex(pProvinceTypes, k);
      [*] = ;         var prType : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'ProvinceType');
      [*] = ;
      [*] = ;         if (myProvinceType = prType) or (prType = 0) then
      [*] = ;         begin
      [*] = ;            bProvince := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if bTerrain and bProvince then
      [*] = ;      begin
      [*] = ;         var freq : Float = ParserGetFloatValueByKeyByHandle(pProvinceName, 'Rarity');
      [*] = ;         sum := sum + freq;
      [*] = ;         ParserSetBoolValueByKeyByHandle(pProvinceName, 'IsRight', true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if sum > 0 then
      [*] = ;   begin
      [*] = ;      var indSum : Float = RandomExt * sum;
      [*] = ;      var curSum : Float = 0;
      [*] = ;      for j := 0 to ParserGetCountByHandle(pProvinceNames)-1 do
      [*] = ;      begin
      [*] = ;         pProvinceName := ParserSelectByHandleByIndex(pProvinceNames, j);
      [*] = ;         var isRight : Boolean = ParserGetBoolValueByKeyByHandle(pProvinceName, 'IsRight');
      [*] = ;
      [*] = ;         if isRight then
      [*] = ;         begin
      [*] = ;            var freq : Float = ParserGetFloatValueByKeyByHandle(pProvinceName, 'Rarity');
      [*] = ;            curSum := curSum + freq;
      [*] = ;
      [*] = ;            if curSum >= indSum then
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var prName : String = ParserGetValueByKeyByHandle(pProvinceName, 'Name');
      [*] = ;      //var hint : String = ParserGetValueByKeyByHandle(pProvinceName, 'Hint');
      [*] = ;      ParserSetValueByKeyByHandle(pHexCell, 'ProvinceName', prName);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pProvinceName, 'Busy', true);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var ind : Integer = _rand_Random(ParserGetCountByHandle(pPrefixes));
      [*] = ;      var pPrefix : Integer = ParserSelectByHandleByIndex(pPrefixes, ind);
      [*] = ;      var prefix : String = ParserGetValueByKeyByHandle(pPrefix, 'Name');
      [*] = ;      ParserSetValueByKeyByHandle(pHexCell, 'Prefix', prefix);
      [*] = ;
      [*] = ;      ind := _rand_Random(ParserGetCountByHandle(pSuffixes));
      [*] = ;      var pSuffix : Integer = ParserSelectByHandleByIndex(pSuffixes, ind);
      [*] = ;      var suffix : String = ParserGetValueByKeyByHandle(pSuffix, 'Name');
      [*] = ;      ParserSetValueByKeyByHandle(pHexCell, 'Suffix', suffix);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// generating province patterns
      [*] = ;Log('Generating province patterns...');
      [*] = ;WaterCount    := 0;
      [*] = ;MountainCount := 0;
      [*] = ;HillCount     := 0;
      [*] = ;ForestCount   := 0;
      [*] = ;SwampCount    := 0;
      [*] = ;DesertCount   := 0;
      [*] = ;DeadLandCount := 0;
      [*] = ;PlainCount    := 0;
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;DecalManagerClear; // clear decals
      [*] = ;
      [*] = ;AdjustVertices;
      [*] = ;CreateProvGameObjects;
      [*] = ;
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   
      [*] = ;   {var x, y, z : Float;
      [*] = ;   var x0, z0 : Float;
      [*] = ;   x := 0;
      [*] = ;   z := 0;
      [*] = ;   var pVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;
      [*] = ;   for j := 0 to 5 do
      [*] = ;   begin
      [*] = ;      var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, j);
      [*] = ;      x0 := ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;      z0 := ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;      x := x + x0;
      [*] = ;      z := z + z0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   x := x / 6;
      [*] = ;   z := z / 6;}
      [*] = ;
      [*] = ;   case TerrainType of
      [*] = ;      gc_MountainTerrainType : MountainCount := MountainCount + 1;
      [*] = ;      gc_WaterTerrainType : WaterCount := WaterCount + 1;
      [*] = ;      gc_PlainTerrainType : PlainCount := PlainCount + 1;
      [*] = ;      gc_ForestTerrainType : ForestCount := ForestCount + 1;
      [*] = ;      gc_HillTerrainType : HillCount := HillCount + 1;
      [*] = ;      gc_SwampTerrainType : SwampCount := SwampCount + 1;
      [*] = ;      gc_DesertTerrainType : DesertCount := DesertCount + 1;
      [*] = ;      gc_DeadLandTerrainType : DeadLandCount := DeadLandCount + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// add special sites for lords
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;
      [*] = ;   var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;   if isCastle then
      [*] = ;   begin
      [*] = ;      var plName : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;      var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;      var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;      var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;      var plProfile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;      if (cMode = 'cmPC') and (plProfile > 0) then
      [*] = ;      begin
      [*] = ;         var siteID : Integer = 0;
      [*] = ;         var dist : Integer = 0;
      [*] = ;
      [*] = ;         case plProfile of
      [*] = ;            9 : begin
      [*] = ;               siteID := 35;
      [*] = ;               dist := 3;
      [*] = ;            end;
      [*] = ;            12 : begin
      [*] = ;               siteID := 43;
      [*] = ;               dist := 3;
      [*] = ;            end;
      [*] = ;            13 : begin
      [*] = ;               siteID := 45;
      [*] = ;               dist := 0;
      [*] = ;            end;
      [*] = ;            14 : begin
      [*] = ;               siteID := 44;
      [*] = ;               dist := 3;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if siteID > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := siteID;
      [*] = ;            IntRegister2 := dist;
      [*] = ;            IntRegister3 := 0;
      [*] = ;            IntRegister4 := -1;
      [*] = ;            IntRegister5 := 0;
      [*] = ;            ExecuteState('AddSite');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// setup province level and pattern
      [*] = ;if (gGame.gameType <> gc_GameTypeHotseatBattle) and (gGame.gameType <> gc_GameTypeLanBattle) then
      [*] = ;begin
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var castle : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'Castle');
      [*] = ;
      [*] = ;      var xc : Float = ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;      var zc : Float = ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;
      [*] = ;      if not IsHexAvailable(pHexCell) then
      [*] = ;      continue;
      [*] = ;
      [*] = ;      // set dummy game object
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'DummyUID');
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;      ParserSetValueByKeyByHandle(pHexCell, 'PatternPlayer', cProvincePlName);
      [*] = ;
      [*] = ;      if castle then
      [*] = ;      begin
      [*] = ;         // set province level
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetLevel');
      [*] = ;         var provLevel : Integer = IntRegister0;
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'ProvinceLevel', provLevel);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'CalcLevel');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // setting province guards
      [*] = ;   if (not ((gMapEditor.enabled) and (gBoolRegister_EditorFastGeneration))) then
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var setProvType : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'SetProvinceType');
      [*] = ;      var castle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;
      [*] = ;      var pProvGuard : Integer = ParserAddChildByIndex(pStratHexCell, 'Guard');
      [*] = ;
      [*] = ;      if castle or (not IsHexAvailable(pStratHexCell)) or (not setProvType) then
      [*] = ;         continue;
      [*] = ;
      [*] = ;      var prType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;      var prCastleDist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'CastleDist');
      [*] = ;
      [*] = ;      IntRegister0 := prType;
      [*] = ;      ExecuteState('GetProvTypeParserByID');
      [*] = ;      var pProvinceType : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var ind : Integer = 0;
      [*] = ;      var pPrGuardTypes : Integer = ParserSelectByHandleByKey(pProvinceType, 'GuardTypes');
      [*] = ;      if (gMapEditor.enabled) and (gMapEditor.grid[i].guardtype>0) then
      [*] = ;      begin
      [*] = ;         for j := 0 to ParserGetCountByHandle(pPrGuardTypes)-1 do
      [*] = ;         begin
      [*] = ;            var pPrGuardType : Integer = ParserSelectByHandleByIndex(pPrGuardTypes, j);
      [*] = ;            if (pPrGuardType=gMapEditor.grid[i].guardtype) then
      [*] = ;            begin
      [*] = ;               ind := j;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var pPrGuardTypes : Integer = ParserSelectByHandleByKey(pProvinceType, 'GuardTypes');
      [*] = ;         var sum : Float = 0;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pPrGuardTypes)-1 do
      [*] = ;         begin
      [*] = ;            var pPrGuardType : Integer = ParserSelectByHandleByIndex(pPrGuardTypes, j);
      [*] = ;            var freq : Float = ParserGetFloatValueByKeyByHandle(pPrGuardType, 'Possibility');
      [*] = ;            sum := sum + freq;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var rand : Float = RandomExt * sum;
      [*] = ;         var curSum : Float = 0;
      [*] = ;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pPrGuardTypes)-1 do
      [*] = ;         begin
      [*] = ;            var pPrGuardType : Integer = ParserSelectByHandleByIndex(pPrGuardTypes, j);
      [*] = ;            var freq : Float = ParserGetFloatValueByKeyByHandle(pPrGuardType, 'Possibility');
      [*] = ;            curSum := curSum + freq;
      [*] = ;
      [*] = ;            if curSum >= rand then
      [*] = ;            begin
      [*] = ;               ind := j;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pPrGuardType : Integer = ParserSelectByHandleByIndex(pPrGuardTypes, ind);
      [*] = ;      var guardType : Integer = ParserGetIntValueByKeyByHandle(pPrGuardType, 'GuardType');
      [*] = ;      var guardDialog : Integer = ParserGetIntValueByKeyByHandle(pPrGuardType, 'Dialog');
      [*] = ;      var guardEncounter : Integer = ParserGetIntValueByKeyByHandle(pPrGuardType, 'Encounter');
      [*] = ;
      [*] = ;      var pGuardType : Integer = ParserSelectByHandleByIndex(pGuardTypes, guardType);
      [*] = ;      var guardKarma : Integer = ParserGetIntValueByKeyByHandle(pGuardType, 'Karma');
      [*] = ;      var guardID : Integer = 0;
      [*] = ;      if (gMapEditor.enabled) and (gMapEditor.grid[i].guardid>0) then
      [*] = ;         guardID := gMapEditor.grid[i].guardid
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var prGuardPower : Integer;
      [*] = ;
      [*] = ;         if (prCastleDist < 0) then
      [*] = ;            prGuardPower := 15
      [*] = ;         else
      [*] = ;            prGuardPower := 1 + (prCastleDist-2) * 3 + _rand_Random(prCastleDist-2) - _rand_Random(prCastleDist-2);
      [*] = ;
      [*] = ;         if (prGuardPower > mapNeutrals) then
      [*] = ;            prGuardPower := mapNeutrals;
      [*] = ;
      [*] = ;         // world rule
      [*] = ;         if (_worldrule_GetWorldRuleAbilityExistByID(11)) then
      [*] = ;         begin
      [*] = ;            var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(11);
      [*] = ;            if (prCastleDist>=param1) then
      [*] = ;            begin
      [*] = ;               var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(11);
      [*] = ;               prGuardPower := prGuardPower+param2;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pGuardIDs : Integer = ParserSelectByHandleByKey(pGuardType, 'GuardID');
      [*] = ;         var guardLevel : Integer = 0;
      [*] = ;         var curPower : Integer = 1000;
      [*] = ;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pGuardIDs)-1 do
      [*] = ;         begin
      [*] = ;            var pGuardID : Integer = ParserSelectByHandleByIndex(pGuardIDs, j);
      [*] = ;            var GuardID : Integer = ParserGetIntValueByKeyByHandle(pGuardID, 'GuardID');
      [*] = ;
      [*] = ;            for k := 0 to ParserGetCountByHandle(pGuards)-1 do
      [*] = ;            begin
      [*] = ;               var pGuard : Integer = ParserSelectByHandleByIndex(pGuards, k);
      [*] = ;               var tempGuardID : Integer = ParserGetIntValueByKeyByHandle(pGuard, 'GuardID');
      [*] = ;               if tempGuardID = GuardID then
      [*] = ;               begin
      [*] = ;                  var guardPower : Integer = ParserGetIntValueByKeyByHandle(pGuard, 'Power');
      [*] = ;                  if Abs(guardPower - prGuardPower) < Abs(curPower - prGuardPower) then
      [*] = ;                  begin
      [*] = ;                     curPower := guardPower;
      [*] = ;                     guardLevel := j;
      [*] = ;                  end;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if _worldrule_GetWorldRuleAbilityExistByID(13) and (_worldrule_GetWorldRuleAbilityParam1(13)=1) then // Хранители мира -  4 игрока, 4 хребта, 2 провинции в центре, 10х10
      [*] = ;         begin
      [*] = ;            if (i = 4 * 10 + 5) or (i = 5 * 10 + 4) then
      [*] = ;            guardLevel := 3;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if guardLevel > 3 then
      [*] = ;            guardLevel := 3;
      [*] = ;
      [*] = ;         var pGuardID : Integer = ParserSelectByHandleByIndex(pGuardIDs, guardLevel);
      [*] = ;         guardID := ParserGetIntValueByKeyByHandle(pGuardID, 'GuardID');
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := pStratHexCell;
      [*] = ;      IntRegister1 := guardType;
      [*] = ;      IntRegister2 := guardID;
      [*] = ;      IntRegister3 := guardKarma;
      [*] = ;      ExecuteState('map.AddGuard');
      [*] = ;      pProvGuard := IntRegister4;
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvGuard, 'Dialog', guardDialog);
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvGuard, 'Encounter', guardEncounter);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // generate quest sites
      [*] = ;   var questsCount : Integer = ParserGetCountByHandle(pQuests);
      [*] = ;   var arQuest : array [0..100] of Boolean;
      [*] = ;
      [*] = ;   for i := 0 to questsCount-1 do
      [*] = ;   begin
      [*] = ;      var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, i);
      [*] = ;      var questGiver : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Giver');
      [*] = ;      var questType : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Type');
      [*] = ;
      [*] = ;      if (questGiver>0) and (questType<>7) and (questType<>8) then
      [*] = ;      arQuest[i] := true
      [*] = ;      else
      [*] = ;      arQuest[i] := false;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (not ((gMapEditor.enabled) and (gBoolRegister_EditorFastGeneration))) then
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;
      [*] = ;      if not IsHexAvailable(pStratHexCell) then
      [*] = ;      continue;
      [*] = ;
      [*] = ;      var possib : Integer = 100 - ((questsCount - 13) * 150) div (mapX * mapY);
      [*] = ;      possib := Round(Clamp(possib, 50, 98));
      [*] = ;
      [*] = ;      if _rand_RandomSeed2(100, gGame.seed, i) > possib then
      [*] = ;      begin
      [*] = ;         _rand_ClearRoll;
      [*] = ;         var count : Integer = 0;
      [*] = ;         for j := 1 to questsCount do
      [*] = ;         begin
      [*] = ;            if arQuest[j] then
      [*] = ;            begin
      [*] = ;               var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, j);
      [*] = ;               gArrRollerN[count] := j;
      [*] = ;               gArrRollerP[count] := ParserGetIntValueByKeyByHandle(pQuest, 'Possibility');
      [*] = ;               count := count + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if count > 0 then
      [*] = ;         begin
      [*] = ;            var questIndex : Integer = _rand_Roll(false);
      [*] = ;            arQuest[questIndex] := false;
      [*] = ;            var quest : Integer = ParserSelectByHandleByIndex(pQuests, questIndex);
      [*] = ;            var questGiver : Integer = ParserGetIntValueByKeyByHandle(quest, 'Giver');
      [*] = ;            var prCastleDist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'CastleDist');
      [*] = ;
      [*] = ;            IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := questGiver;
      [*] = ;            IntRegister2 := prCastleDist-2;
      [*] = ;            IntRegister3 := questIndex;
      [*] = ;            IntRegister4 := 0;
      [*] = ;            IntRegister5 := 0;
      [*] = ;            ExecuteState('AddSite');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // generate province sites
      [*] = ;   if (not ((gMapEditor.enabled) and (gBoolRegister_EditorFastGeneration))) then
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;
      [*] = ;      if not IsHexAvailable(pStratHexCell) then
      [*] = ;      continue;
      [*] = ;
      [*] = ;      var prType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;      var prCastleDist : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'CastleDist');
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;      var prExplored : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Explored');
      [*] = ;      var terrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;      var castle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;
      [*] = ;      IntRegister0 := terrainType;
      [*] = ;      ExecuteState('GetTerrainParserByID');
      [*] = ;      var pTerrainType : Integer = IntRegister1;
      [*] = ;      var prTerrainType : String = ParserGetValueByKeyByHandle(pTerrainType, 'Name');
      [*] = ;
      [*] = ;      if (prType > 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := prType;
      [*] = ;         ExecuteState('GetProvTypeParserByID');
      [*] = ;         var pProvinceType : Integer = IntRegister1;
      [*] = ;
      [*] = ;         var prSiteCount : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'Sites');
      [*] = ;         var siteCount : Integer = prSiteCount + _rand_Random(11) - 5;
      [*] = ;         siteCount := siteCount + (siteCount*(mapSite-1)) div 10;
      [*] = ;
      [*] = ;         // world rule
      [*] = ;         if (_worldrule_GetWorldRuleAbilityExistByID(18)) then
      [*] = ;         begin
      [*] = ;            var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(18);
      [*] = ;            siteCount := (siteCount*param1) div 100;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if siteCount > Min(gc_MaxProvinceSite-3, 99 - prExplored) then
      [*] = ;         siteCount := Min(gc_MaxProvinceSite-3, 99 - prExplored);
      [*] = ;
      [*] = ;         // force sites
      [*] = ;         for j := ParserGetCountByHandle(pSites)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSite : Integer = ParserSelectByHandleByIndex(pSites, j);
      [*] = ;            var siteID : Integer = ParserGetIntValueByKeyByHandle(pSite, 'SiteID');
      [*] = ;
      [*] = ;            var pSiteAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;            for k := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, k);
      [*] = ;               var ability : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'AbilityID');
      [*] = ;               if ability = 5 then // always generate this site
      [*] = ;               begin
      [*] = ;                  var param1 : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'Param1');
      [*] = ;                  if param1 = prType then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := pStratHexCell;
      [*] = ;                     IntRegister1 := siteID;
      [*] = ;                     IntRegister2 := prCastleDist-2;
      [*] = ;                     IntRegister3 := 0;
      [*] = ;                     IntRegister4 := 0;
      [*] = ;                     IntRegister5 := 0;
      [*] = ;                     ExecuteState('AddSite');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var sum : Integer = 0;
      [*] = ;
      [*] = ;         // world rule
      [*] = ;         var bWorldRuleSiteExist : Boolean = _worldrule_GetWorldRuleSitesExist;
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pSites)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSite : Integer = ParserSelectByHandleByIndex(pSites, j);
      [*] = ;            var place : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Place');
      [*] = ;            var pTerrainType : Integer = ParserSelectByHandleByKey(pSite, 'TerrainType');
      [*] = ;
      [*] = ;            if (place > 0) and _map_IsSiteEnabled(j) then
      [*] = ;            begin
      [*] = ;               var poss : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, prTerrainType);
      [*] = ;
      [*] = ;               // world rule
      [*] = ;               if (bWorldRuleSiteExist) then
      [*] = ;               begin
      [*] = ;                  var siteID : Integer = ParserGetIntValueByKeyByHandle(pSite, 'SiteID');
      [*] = ;                  if (_worldrule_GetWorldRuleSiteExistByID(siteID)) then
      [*] = ;                  begin
      [*] = ;                     var siteModPossibility : Integer = _worldrule_GetWorldRuleSitePossibilityByID(siteID);
      [*] = ;                     poss := (poss*siteModPossibility) div 100;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               sum := sum + poss;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for j := 0 to siteCount-1 do
      [*] = ;         begin
      [*] = ;            var randSum : Float = RandomExt * sum;
      [*] = ;            var pSite : Integer = 0;
      [*] = ;
      [*] = ;            for k := ParserGetCountByHandle(pSites)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pTmpSite : Integer = ParserSelectByHandleByIndex(pSites, k);
      [*] = ;               var place : Integer = ParserGetIntValueByKeyByHandle(pTmpSite, 'Place');
      [*] = ;               var pTerrainType : Integer = ParserSelectByHandleByKey(pTmpSite, 'TerrainType');
      [*] = ;
      [*] = ;               if (place > 0) and _map_IsSiteEnabled(k) then
      [*] = ;               begin
      [*] = ;                  var poss : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, prTerrainType);
      [*] = ;
      [*] = ;                  // world rule
      [*] = ;                  if (bWorldRuleSiteExist) then
      [*] = ;                  begin
      [*] = ;                     var siteID : Integer = ParserGetIntValueByKeyByHandle(pTmpSite, 'SiteID');
      [*] = ;                     if (_worldrule_GetWorldRuleSiteExistByID(siteID)) then
      [*] = ;                     begin
      [*] = ;                        var siteModPossibility : Integer = _worldrule_GetWorldRuleSitePossibilityByID(siteID);
      [*] = ;                        poss := (poss*siteModPossibility) div 100;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  randSum := randSum - poss;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if randSum <= 0 then
      [*] = ;               begin
      [*] = ;                  pSite := pTmpSite;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            var siteID : Integer = ParserGetIntValueByKeyByHandle(pSite, 'SiteID');
      [*] = ;            IntRegister0 := pStratHexCell;
      [*] = ;            IntRegister1 := siteID;
      [*] = ;            IntRegister2 := prCastleDist-2;
      [*] = ;            IntRegister3 := 0;
      [*] = ;            IntRegister4 := 0;
      [*] = ;            IntRegister5 := 0;
      [*] = ;            ExecuteState('AddSite');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// campaign quests
      [*] = ;if gGame.gameType = gc_GameTypeCampaign then
      [*] = ;begin
      [*] = ;   ExecuteState('map.ClearMoveMap');
      [*] = ;   var plUnitHnd : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex); // GetPlayerHandleInterfaceIO;
      [*] = ;   PlayerExecuteStateByHandle(plUnitHnd, 'GetCastleParser');
      [*] = ;   var pProvinceCastle : Integer = IntRegister0;
      [*] = ;   IntRegister0 := pProvinceCastle;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   ExecuteState('map.MakeMoveMap');
      [*] = ;
      [*] = ;   for i := 0 to gc_MaxCampaignQuest-1 do
      [*] = ;   begin
      [*] = ;      var questID : Integer = gCampaign.arrQuests[i].questIndex;
      [*] = ;      var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, questID);
      [*] = ;      var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;      var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, 0);
      [*] = ;      var place : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Place');
      [*] = ;      var target : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Target');
      [*] = ;      var quantity : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Quantity');
      [*] = ;
      [*] = ;      if (questID > 0) and (gCampaign.arrQuests[i].status < 2) and (place <> 0) then
      [*] = ;      begin
      [*] = ;         var dist : Integer = 100;
      [*] = ;         var chInd : Integer = -1;
      [*] = ;
      [*] = ;         for j := 0 to hexCount-1 do
      [*] = ;         begin
      [*] = ;            var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, j);
      [*] = ;            if IsHexAvailable(pStratHexCell) then
      [*] = ;            begin
      [*] = ;               var provType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;               var moveMap : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'MoveMap');
      [*] = ;               var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;               var pProvSites : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Sites');
      [*] = ;               var siteCount : Integer = ParserGetCountByHandle(pProvSites);
      [*] = ;
      [*] = ;               var wRule : Boolean = false;
      [*] = ;               case curVisualID of
      [*] = ;                  2 : begin
      [*] = ;                     if (place = gc_PlainTerrainType) and (terType = gc_DesertTerrainType) then
      [*] = ;                     wRule := true;
      [*] = ;                  end;
      [*] = ;                  3 : begin
      [*] = ;                     if (place = gc_PlainTerrainType) and (terType = gc_DeadLandTerrainType) then
      [*] = ;                     wRule := true;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (provType <> 7) and (moveMap > 0) and (siteCount < gc_MaxProvinceSite) and
      [*] = ;               ((place < 0) or (place = terType) or wRule) then
      [*] = ;               begin
      [*] = ;                  if (Abs(moveMap - quantity) < dist) or ((Abs(moveMap - quantity) = dist) and (_rand_Random(10) < 5)) then
      [*] = ;                  begin
      [*] = ;                     dist := Round(Abs(moveMap - quantity));
      [*] = ;                     chInd := j;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if chInd >= 0 then
      [*] = ;         begin
      [*] = ;            var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, chInd);
      [*] = ;            var pProvSites : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Sites');
      [*] = ;            var name : String = 'quest|' + IntToStr(questID);
      [*] = ;            ParserSetValueByKeyByHandle(pStratHexCell, 'ProvinceName', name);
      [*] = ;
      [*] = ;            var pNewSite : Integer = ParserAddChildByIndex(pProvSites, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pNewSite, 'SiteID', target);
      [*] = ;            var siteInd : Integer = ParserGetCountByHandle(pProvSites)-1;
      [*] = ;
      [*] = ;            var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;            var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, 0);
      [*] = ;            var guardType : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Index');
      [*] = ;            var guardLevel : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Exp');
      [*] = ;
      [*] = ;            var pGuardType : Integer = ParserSelectByHandleByIndex(pGuardTypes, guardType);
      [*] = ;            var pGuardIDs : Integer = ParserSelectByHandleByKey(pGuardType, 'GuardID');
      [*] = ;            var pGuardID : Integer = ParserSelectByHandleByIndex(pGuardIDs, guardLevel);
      [*] = ;            var guardID : Integer = ParserGetIntValueByKeyByHandle(pGuardID, 'GuardID');
      [*] = ;
      [*] = ;            IntRegister0 := pNewSite;
      [*] = ;            IntRegister1 := guardType;
      [*] = ;            IntRegister2 := guardID;
      [*] = ;            IntRegister3 := 0;
      [*] = ;            ExecuteState('map.AddGuard');
      [*] = ;            var pSiteGuard : Integer = IntRegister4;
      [*] = ;            ParserSetBoolValueByKeyByHandle(pSiteGuard, 'NeedRestore', false);
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(pNewSite, 'Explore', 0);
      [*] = ;            gCampaign.arrQuests[i].siteIndex := siteInd;
      [*] = ;            gCampaign.arrQuests[i].provIndex := chInd;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gCampaign.arrQuests[i].status := -1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// break connections with water and mountain track nodes
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   if not IsHexAvailable(pStratHexCell) then
      [*] = ;   begin
      [*] = ;      var tnHandle : Integer = GetTrackNodeHandleByIndex(i);
      [*] = ;      SetTrackNodeEnabledByHandle(tnHandle, false);
      [*] = ;      for j := 0 to GetTrackNodeNeighboursCountByHandle(tnHandle)-1 do
      [*] = ;      begin
      [*] = ;         var tnHandle1 : Integer = GetTrackNodeNeighbourHandleByHandleByIndex(tnHandle, j);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;// add castle parsers to provinces
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;   var castle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;
      [*] = ;   if castle then
      [*] = ;   begin
      [*] = ;      var provPlName : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;      var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;      var provPlIndex : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;      var cMode : String = GetPlayerControlModeByHandle(provPlHandle);
      [*] = ;      //if SameText(cMode, 'cmPlayer') then
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'UpdatePlayer', provPlIndex);
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'Fort', 100);
      [*] = ;      ParserAddChildByIndex(pStratHexCell, 'InnerBuildings');
      [*] = ;      var pProvSpells : Integer = ParserAddChildByIndex(pStratHexCell, 'SpellLevels');
      [*] = ;      for j := 0 to 4 do
      [*] = ;      begin
      [*] = ;         var pProvLevelSpells : Integer = ParserAddChildByIndex(pProvSpells, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvLevelSpells, 'Level', j);
      [*] = ;         ParserAddChildByIndex(pProvLevelSpells, 'Spells');
      [*] = ;      end;
      [*] = ;
      [*] = ;      ParserAddChildByIndex(pStratHexCell, 'RecruitUnits');
      [*] = ;      var pAvOuterBuildings : Integer = ParserAddChildByIndex(pStratHexCell, 'AvOuterBuildings');
      [*] = ;      for j := 0 to ParserGetCountByHandle(pOuterBuildings)-1 do
      [*] = ;      begin
      [*] = ;         var pAvOuterBuilding : Integer = ParserAddChildByIndex(pAvOuterBuildings, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pAvOuterBuilding, 'BuildID', j);
      [*] = ;         ParserSetIntValueByKeyByHandle(pAvOuterBuilding, 'Count', 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      ParserAddChildByIndex(pStratHexCell, 'Items');
      [*] = ;      //ParserAddChildByIndex(pStratHexCell, 'Defenders');
      [*] = ;
      [*] = ;      var pCastleDefenders : Integer = ParserAddChildByIndex(pStratHexCell, 'Defenders');
      [*] = ;      for j := 0 to ParserGetCountByHandle(pDefenders)-1 do
      [*] = ;      begin
      [*] = ;         var pCastleDefender : Integer = ParserAddChildByIndex(pCastleDefenders, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pCastleDefender, 'DefenderID', j);
      [*] = ;         ParserSetIntValueByKeyByHandle(pCastleDefender, 'Count', 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pCastleRituals : Integer = ParserAddChildByIndex(pStratHexCell, 'AvailableRituals');
      [*] = ;      for j := 0 to ParserGetCountByHandle(pRituals)-1 do
      [*] = ;      begin
      [*] = ;         var pCastleRitual : Integer = ParserAddChildByIndex(pCastleRituals, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pCastleRitual, 'RitualID', j);
      [*] = ;         ParserSetIntValueByKeyByHandle(pCastleRitual, 'Count', 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pCastleRitual, 'Cooldown', 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pProvMercenary : Integer = ParserAddChildByIndex(pStratHexCell, 'Mercenary');
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvMercenary, 'UnitID', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvMercenary, 'Timer', 0);
      [*] = ;
      [*] = ;      //Hero stand not in province center
      [*] = ;      var cX : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;      var cY : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;      var pVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;      {var maxDist : Float = 0;
      [*] = ;      var ind : Integer = 0;
      [*] = ;      for k := 0 to 5 do
      [*] = ;      begin
      [*] = ;         var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, k);
      [*] = ;         var x : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;         var y : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;         if VectorDistance(cx, 0, cy, x, 0, y) > maxDist then
      [*] = ;         begin
      [*] = ;            maxDist := VectorDistance(cx, 0, cy, x, 0, y);
      [*] = ;            ind := k;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, ind);
      [*] = ;      var x : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;      var y : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');}
      [*] = ;      const hPointInd = 0;
      [*] = ;      var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, hPointInd);
      [*] = ;      var x : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;      var y : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;      {var tmpX : Float = (cx+2*x)/(1+2);
      [*] = ;      var tmpY : Float = (cy+2*y)/(1+2);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pStratHexCell, 'HeroPointX', tmpX);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pStratHexCell, 'HeroPointY', tmpY);}
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;   end;
      [*] = ;
      [*] = ;   // set outer buildings parsers
      [*] = ;   var pProvOuterBuildings : Integer = ParserAddChildByIndex(pStratHexCell, 'OuterBuildings');
      [*] = ;   var pLandmarks : Integer = ParserAddChildByIndex(pStratHexCell, 'Landmarks');
      [*] = ;
      [*] = ;   var ind : array [0..4] of Integer;
      [*] = ;
      [*] = ;   var cX : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;   var cY : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;   var pVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;
      [*] = ;   for j := 0 to 4 do //3 - landmark, 4 - heropoint
      [*] = ;   begin
      [*] = ;      var pProvOuterBuilding : Integer = 0;
      [*] = ;      var pLandmark : Integer = 0;
      [*] = ;
      [*] = ;      if j < 3 then
      [*] = ;      begin
      [*] = ;         pProvOuterBuilding := ParserAddChildByIndex(pProvOuterBuildings, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID', 0);
      [*] = ;
      [*] = ;         var grName : String = 'group.outer.' + IntToStr(dummyUID) + '.' + IntToStr(j);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID', 0);
      [*] = ;         ParserSetValueByKeyByHandle(pProvOuterBuilding, 'PatternPlayer', cProvincePlName);
      [*] = ;         ParserSetValueByKeyByHandle(pProvOuterBuilding, 'PatternGroup', grName);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if j < 4 then
      [*] = ;      begin
      [*] = ;         pLandmark := ParserAddChildByIndex(pLandmarks, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pLandmark, 'LandmarkID', 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var maxDist : Float = 0;
      [*] = ;
      [*] = ;      const hPointInd = 0;
      [*] = ;      for k := 0 to 5 do
      [*] = ;      if ((j <> 4) and (k <> hPointInd)) and (k <> ind[0]) and (k <> ind[1]) and (k <> ind[2]) and (k <> ind[3]) {and (k <> ind[4])} then
      [*] = ;      begin
      [*] = ;         var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, k);
      [*] = ;         var x : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;         var y : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;         if VectorDistance(cx, 0, cy, x, 0, y) > maxDist then
      [*] = ;         begin
      [*] = ;            maxDist := VectorDistance(cx, 0, cy, x, 0, y);
      [*] = ;            ind[j] := k;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      ind[4] := hPointInd;
      [*] = ;
      [*] = ;      var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, ind[j]);
      [*] = ;      var x : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;      var y : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;      if (j<3) then
      [*] = ;      begin
      [*] = ;         var tmpX : Float = (cx+2*x)/(1+2);
      [*] = ;         var tmpY : Float = (cy+2*y)/(1+2);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pProvOuterBuilding, 'X', tmpX);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pProvOuterBuilding, 'Y', tmpY);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (j<4) then
      [*] = ;      begin
      [*] = ;         var tmpX : Float = (cx+2*x)/(1+2);
      [*] = ;         var tmpY : Float = (cy+2*y)/(1+2);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pLandmark, 'X', tmpX);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pLandmark, 'Y', tmpY);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         //Hero stand not in province center
      [*] = ;         var tmpX : Float = (cx+x)/(2);
      [*] = ;         var tmpY : Float = (cy+y)/(2);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pStratHexCell, 'HeroPointX', tmpX);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pStratHexCell, 'HeroPointY', tmpY);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pProvDefender : Integer = ParserAddChildByIndex(pStratHexCell, 'Defender');
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvDefender, 'DefenderID', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvDefender, 'Initiative', 0);
      [*] = ;   var pDefendUnits : Integer = ParserAddChildByIndex(pProvDefender, 'Units');
      [*] = ;   var pProvRituals : Integer = ParserAddChildByIndex(pStratHexCell, 'Rituals');
      [*] = ;   var pProvCastedRituals : Integer = ParserAddChildByIndex(pStratHexCell, 'CastedRituals');
      [*] = ;   var pProvAttitudes : Integer = ParserAddChildByIndex(pStratHexCell, 'Attitudes');
      [*] = ;   var pProvUnrests : Integer = ParserAddChildByIndex(pStratHexCell, 'Unrests');
      [*] = ;   var pProvShop : Integer = ParserAddChildByIndex(pStratHexCell, 'Shop');
      [*] = ;   var pProvShopItems : Integer = ParserAddChildByIndex(pProvShop, 'Items');
      [*] = ;   var pPriceModifiers : Integer = ParserAddChildByIndex(pProvShop, 'PriceModifiers');
      [*] = ;
      [*] = ;   for j := 0 to mapPlayers-1 do
      [*] = ;   begin
      [*] = ;      var pPriceModifier : Integer = ParserAddChildByIndex(pPriceModifiers, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pPriceModifier, 'PlayerIndex', j);
      [*] = ;      ParserSetIntValueByKeyByHandle(pPriceModifier, 'PriceModifier', 100);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pProvRebel : Integer = ParserAddChildByIndex(pStratHexCell, 'Rebel');
      [*] = ;   var pProvRebelUnits : Integer = ParserAddChildByIndex(pProvRebel, 'Units');
      [*] = ;
      [*] = ;   AddProvGarrison(pStratHexCell);
      [*] = ;
      [*] = ;   for j := 0 to GetCountOfPlayers-1 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(j);
      [*] = ;      if GetPlayerRaceTagByHandle(plHandle) = gc_map_PlayerRaceTag then
      [*] = ;      begin
      [*] = ;         var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;         var pProvAttitude : Integer = ParserAddChildByIndex(pProvAttitudes, '*');
      [*] = ;         ParserSetValueByKeyByHandle(pProvAttitude, 'Player', plName);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvAttitude, 'Attitude', 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvAttitude, 'Timer', 0);
      [*] = ;
      [*] = ;         var pProvUnrest : Integer = ParserAddChildByIndex(pProvUnrests, '*');
      [*] = ;         ParserSetValueByKeyByHandle(pProvUnrest, 'Player', plName);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvUnrest, 'Unrest', 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvUnrest, 'PrevUnrest', 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var provPlName : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;   var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;   var provPlIndex : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;   var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   // world rule add extra buildings
      [*] = ;   var explored : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Explored');
      [*] = ;   if (explored>=100) then
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'FinishExploration');
      [*] = ;   if (bWorldRuleAbilityExist12) and (not isCastle) then
      [*] = ;   begin
      [*] = ;      var population : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Population');
      [*] = ;      if (population>0) then
      [*] = ;      begin
      [*] = ;         var pWorldRule : Integer = _worldrule_GetWorldRuleParser();
      [*] = ;         var pWorldRuleAbilities : Integer = ParserSelectByHandleByKey(pWorldRule, 'Abilities');
      [*] = ;         var j : Integer;
      [*] = ;         for j:=0 to ParserGetCountByHandle(pWorldRuleAbilities)-1 do
      [*] = ;         begin
      [*] = ;            var pWorldRuleAbility : Integer = ParserSelectByHandleByIndex(pWorldRuleAbilities, j);
      [*] = ;            var abilityID : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'AbilityID');
      [*] = ;            if (abilityID=12) then
      [*] = ;            begin
      [*] = ;               var param1 : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'Param1');
      [*] = ;               var param2 : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'Param2');
      [*] = ;
      [*] = ;               IntRegister0 := param1;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'IsBuildingAvailable');
      [*] = ;               var terrainAllow : Boolean = BoolRegister4;
      [*] = ;
      [*] = ;               if (terrainAllow) then
      [*] = ;               begin
      [*] = ;                  if (RandomExt<(param2/100)) then
      [*] = ;                  begin
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'GetFreeOuterBuildSlot');
      [*] = ;                     var slotIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;                     if (slotIndex>=0) and (slotIndex<3) then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := param1;
      [*] = ;                        IntRegister1 := slotIndex;
      [*] = ;                        GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if provPlHandle <> 0 then
      [*] = ;   begin
      [*] = ;      if (not gTutorial.map) or isCastle or (provPlIndex > 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := provPlHandle;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'SetupPlayerFlag');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if not gTutorial.map then
      [*] = ;      ParserSetIntValueByKeyByHandle(pStratHexCell, 'LastPlayer', provPlIndex);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gTutorial.map then
      [*] = ;   SetTutorialExtData();
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;   SetMapEditorExtData();
      [*] = ;
      [*] = ;if (gGame.gameType <> gc_GameTypeLanBattle) and (gGame.gameType <> gc_GameTypeHotseatBattle) then
      [*] = ;begin
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'CalcFogMap');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// enable buttons
      [*] = ;if not gTutorial.map then
      [*] = ;begin
      [*] = ;   BoolRegister0 := true;
      [*] = ;   ExecuteState('SetButtonsEnabled');
      [*] = ;end;
      [*] = ;
      [*] = ;var pBattleLog : Integer = ParserSelectByHandleByKey(pMachineParser, 'BattleLog');
      [*] = ;if pBattleLog = 0 then
      [*] = ;   pBattleLog := ParserAddChildByIndex(pMachineParser, 'BattleLog')
      [*] = ;else
      [*] = ;   ParserClearByHandle(pBattleLog);
      [*] = ;
      [*] = ;Log('___________________________________________');
      [*] = ;Log('Water count = ' + IntToStr(WaterCount));
      [*] = ;Log('Mountain count = ' + IntToStr(MountainCount));
      [*] = ;Log('Forest count = ' + IntToStr(ForestCount));
      [*] = ;Log('Hill count = ' + IntToStr(HillCount));
      [*] = ;Log('Swamp count = ' + IntToStr(SwampCount));
      [*] = ;Log('Desert count = ' + IntToStr(DesertCount));
      [*] = ;Log('Dead land count = ' + IntToStr(DeadLandCount));
      [*] = ;Log('Plain count = ' + IntToStr(PlainCount));
      [*] = ;
      [*] = ;gIntRegister_CurGameMode := gc_GameModeStrategy;
      [*] = ;SetActiveTrackNodeList(0);
      [*] = ;
      [*] = ;gGame.currentTurn := 1;
      [*] = ;
      [*] = ;_misc_ParserGetOrCreateByKey('MountainPatterns',true);
      [*] = ;_misc_ParserGetOrCreateByKey('ResourceCount',true);
      [*] = ;
      [*] = ;SetCloudsVisible(True);
      [*] = ;SetCloudsActive(True);
      [*] = ;SetCloudsSpeedFactor(10);
      [*] = ;MakeRandomClouds();
      [*] = ;//DoGenerateClouds()
      [*] = ;
      [*] = ;Log('Setting fog of war...');
      [*] = ;
      [*] = ;if gGame.fog then
      [*] = ;  MapExecuteState('map.DoFogOfWar');
      [*] = ;
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(pMachineParser, 'Queries');
      [*] = ;if pQueries = 0 then pQueries := ParserAddChildByIndex(pMachineParser, 'Queries')
      [*] = ;else ParserClearByHandle(pQueries);
      [*] = ;var pSyncInfo : Integer = ParserAddChildByIndex(pMachineParser, 'SyncInfo');
      [*] = ;//ParserClearByHandle(pSyncInfo);
      [*] = ;var pSyncPlInfo : Integer = ParserAddChildByIndex(pSyncInfo, 'Players');
      [*] = ;var pSyncGame : Integer = ParserAddChildByIndex(pSyncInfo, 'Game');
      [*] = ;var pSyncConflicts : Integer = ParserAddChildByIndex(pSyncInfo, 'Conflicts');
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) and (GetLanMode() >= 2) then
      [*] = ;begin
      [*] = ;   StateMachineGlobalVariablesSaveToParser(pSyncGame, 'gGame', false, false);
      [*] = ;   gIntRegister_LanMapUID := _rand_Random($7fff);
      [*] = ;   gStringRegister_LanMapSaveName := '';
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_GUIExecuteStartEvent := (gGame.worldRule > 0);
      [*] = ;
      [*] = ;// Beta 3 hack
      [*] = ;//gGame.diplomacy := False;
      [*] = ;
      [*] = ;_init_GenDLC();
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeCampaign then
      [*] = ;   MapExecuteState('map.vvk.ImportHeroFromAstral');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

