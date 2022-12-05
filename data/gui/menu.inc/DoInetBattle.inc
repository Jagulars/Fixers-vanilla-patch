section.begin
   Name = DoInetBattle
   Code : struct.begin
      [*] = ;function GetRandomTerrainType(allowedTerrains : Integer) : Integer;
      [*] = ;begin
      [*] = ;   _rand_ClearRoll;
      [*] = ;   
      [*] = ;   var count : Integer = 0;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to gc_TerrainChoiceCount-1 do
      [*] = ;   begin
      [*] = ;      if ((_misc_GetBitFlagByIndex(i) and allowedTerrains) > 0) then
      [*] = ;      begin
      [*] = ;         gArrRollerN[count] := i+1; // terrain type id
      [*] = ;         gArrRollerP[count] := 10; // possibility
      [*] = ;         count := count + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := _rand_Roll(false);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateStratMapParser(iSeed : Integer);
      [*] = ;begin
      [*] = ;   var myName : String;
      [*] = ;   var myPoints, myAllowPointsDif, myHeroClass1, myHeroClass2, myAllowedHeroClasses, myAllowedTerrains : Integer;
      [*] = ;
      [*] = ;   _inet_GetInetGameParamsMy(myName, myPoints, myAllowPointsDif, myHeroClass1, myHeroClass2, myAllowedHeroClasses, myAllowedTerrains);
      [*] = ;
      [*] = ;   gGame.seed := iSeed;
      [*] = ;   gGame.worldrule := 0;
      [*] = ;
      [*] = ;   gGame.map.players := 2;
      [*] = ;   gGame.map.difficulty := 0;
      [*] = ;   gGame.map.x := 3;
      [*] = ;   gGame.map.y := 3;
      [*] = ;   gGame.map.typ := 0;
      [*] = ;   gGame.map.water := 0;
      [*] = ;   gGame.map.hill := 0;
      [*] = ;   gGame.map.forest := 0;
      [*] = ;   gGame.map.swamp := 0;
      [*] = ;   gGame.map.desert := 0;
      [*] = ;   gGame.map.deadland := 0;
      [*] = ;   gGame.map.isles := 0;
      [*] = ;   gGame.map.dissolve := 0;
      [*] = ;   gGame.map.neutrals := 0;
      [*] = ;   gGame.map.resource := 0;
      [*] = ;   gGame.map.site := 0;
      [*] = ;   gGame.map.population := 0;
      [*] = ;
      [*] = ;   _map_SetGameCustomDifficultyOptionsDefault(gMapSettings.arrplayers[0].advdiff, False, 3);
      [*] = ;   _map_SetGameCustomDifficultyOptionsDefault(gMapSettings.arrplayers[1].advdiff, False, 3);
      [*] = ;   gMapSettings.arrplayers[0].advdiff.basediff := 3;
      [*] = ;   gMapSettings.arrplayers[1].advdiff.basediff := 3;
      [*] = ;
      [*] = ;   gMapSettings.arrplayers[0].control := 1;
      [*] = ;   gMapSettings.arrplayers[1].control := 1;
      [*] = ;
      [*] = ;
      [*] = ;   if (GetLanMode()>=2) then
      [*] = ;   begin
      [*] = ;      gInetBattle.map.lefttype := GetRandomTerrainType(myAllowedTerrains);
      [*] = ;      gInetBattle.map.righttype := GetRandomTerrainType(gLanHeroClient.allowedterrains);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      // keep this order
      [*] = ;      gInetBattle.map.lefttype := GetRandomTerrainType(gLanHeroServer.allowedterrains);
      [*] = ;      gInetBattle.map.righttype := GetRandomTerrainType(myAllowedTerrains);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (randomExt()<0.7) then
      [*] = ;      gInetBattle.map.visualid := 0
      [*] = ;   else
      [*] = ;      gInetBattle.map.visualid := 1+floor(randomExt*3);
      [*] = ;end;
      [*] = ;
      [*] = ;const cMapName = 'global.map';
      [*] = ;const cPresetName = 'Default';
      [*] = ;const HEX_WIDTH = 10.575;
      [*] = ;
      [*] = ;var zoneName : String = 'Default';
      [*] = ;var randKey0 : Integer = gLanHeroServer.randkey0;
      [*] = ;var randKey1 : Integer = gLanHeroServer.randkey1;
      [*] = ;var mapSize : Integer = 32;
      [*] = ;var iMapSize : Integer = 6;
      [*] = ;
      [*] = ;if (not IsLanGame()) and (randKey0=0) and (randKey1=0) then
      [*] = ;   GenerateMapRandKey(randKey0, randKey1);
      [*] = ;SetRandomExtKey64(randKey0, randKey1);
      [*] = ;SetMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;SetGlobalMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;
      [*] = ;var iSeed : Integer = randKey1 mod gc_MaxSeedValue;
      [*] = ;
      [*] = ;var shardWidth : Float = HEX_WIDTH*(iMapSize+2);
      [*] = ;var shardHeight : Float = shardWidth*0.885;
      [*] = ;var MapWidth : Integer = 40+130+Round(shardWidth);
      [*] = ;
      [*] = ;while (MapWidth>mapSize) do
      [*] = ;   mapSize := mapSize+32;
      [*] = ;
      [*] = ;MapWidth := mapSize;
      [*] = ;
      [*] = ;//optimization
      [*] = ;MapWidth := MapWidth-32*4;
      [*] = ;
      [*] = ;mapSize := 32;
      [*] = ;var MapHeight : Integer = 40+90+Round(shardHeight);
      [*] = ;while (MapHeight>mapSize) do
      [*] = ;   mapSize := mapSize+32;
      [*] = ;MapHeight := mapSize;
      [*] = ;
      [*] = ;//optimization
      [*] = ;MapHeight := MapHeight-32*2;
      [*] = ;
      [*] = ;CreateStratMapParser(iSeed);
      [*] = ;logi('randkey1='+IntToStr(randKey1)+' seed='+IntToStr(iSeed)+' lefttype='+IntToStr(gInetBattle.map.lefttype)+' righttype='+IntToStr(gInetBattle.map.righttype)+' visualid='+IntToStr(gInetBattle.map.visualid));
      [*] = ;
      [*] = ;StateMachineClearVariables(GetMapInitMachineHandle);
      [*] = ;if (IsLanGame()) then
      [*] = ;begin
      [*] = ;   gIntRegsiter_LanBatClientID := gLanHeroServer.lanid;
      [*] = ;   gIntRegsiter_LanBatServerID := gLanHeroClient.lanid;
      [*] = ;end
      [*] = ;else
      [*] = ;   gGame.gametype := gc_GameTypeHotseatBattle;
      [*] = ;
      [*] = ;gTutorial.map := false;
      [*] = ;gIntRegister_CurGameMode := gc_GameModeStrategy;
      [*] = ;GUIExecuteState('VVK.lan.resetbattleglobals');
      [*] = ;   
      [*] = ;GenerateMapNeededExtBorder(cMapName, zoneName, cPresetName, MapWidth, MapHeight, 5, randKey0, randKey1, 0, 0, 0, '', '', '', '', '', '', '.\data\gui\gui.cfg', ''{'GUIInitialize'}, 'Ingame1', '', 'MakeStratHexGrid', false);
   struct.end
section.end

