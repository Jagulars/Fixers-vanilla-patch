section.begin
   Name = astral.AttackShard
   Description : struct.begin
      [*] = ;IntRegister0 - shard index
      [*] = ;BoolRegister0 - world attack
   struct.end
   Code : struct.begin
      [*] = ;var shardInd : Integer = IntRegister0;
      [*] = ;var wAttack : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\ASTRAL\ASTRAL.ATTACKSHARD';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var worldSize : Integer = _camp_player_GetWorldSize(gCampaign.arrCampPlayers[0]);
      [*] = ;
      [*] = ;gGame.seed := gShards[shardInd].seed;
      [*] = ;
      [*] = ;gGame.gameType := gc_GameTypeCampaign;
      [*] = ;gCampaign.activeShard := shardInd;
      [*] = ;
      [*] = ;if not _shard_IsMain(gShards[shardInd]) then
      [*] = ;begin
      [*] = ;   gCampaign.defender := false;
      [*] = ;   gGame.maxPlayers := gShards[shardInd].map.players;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   gGame.maxPlayers := 2;
      [*] = ;end;
      [*] = ;
      [*] = ;// generate battle map
      [*] = ;SetObjectBasedVisibilityCulling(false);
      [*] = ;SetTerrainVisible(true);
      [*] = ;SetTerrainBordersVisible(false);
      [*] = ;
      [*] = ;var currMapFileName : String = GetCurrentMapFileName;
      [*] = ;var mapName : String;
      [*] = ;if (currMapFileName<>'') then
      [*] = ;   mapName := currMapFileName// + '.map'
      [*] = ;else
      [*] = ;   mapName := 'global.map';
      [*] = ;
      [*] = ;var zoneName : String = 'Default';
      [*] = ;const cPresetName = 'Default';
      [*] = ;
      [*] = ;var iSeed : Integer = gShards[shardInd].seed;
      [*] = ;var randkey0 : Integer = 0;
      [*] = ;var randkey1 : Integer = iSeed;
      [*] = ;SetRandomExtKey64(randKey0, randKey1);
      [*] = ;SetMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;SetGlobalMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;
      [*] = ;var x : Integer = gShards[shardInd].map.x;
      [*] = ;var y : Integer = gShards[shardInd].map.y;
      [*] = ;
      [*] = ;const HEX_WIDTH = 10.575;
      [*] = ;var mapSize : Integer = 32;
      [*] = ;
      [*] = ;var shardWidth : Float = HEX_WIDTH * (x + 2);//+HEX_WIDTH/2;
      [*] = ;var shardHeight : Float = shardWidth * 0.885;
      [*] = ;var MapWidth : Integer = 170 + Round(shardWidth); {X*20+120}
      [*] = ;while MapWidth > mapSize do
      [*] = ;   mapSize := mapSize + 32;
      [*] = ;
      [*] = ;MapWidth := mapSize;
      [*] = ;mapSize := 32;
      [*] = ;var MapHeight : Integer = 130 + Round(shardHeight); {Y*20+100}
      [*] = ;while MapHeight > mapSize do
      [*] = ;   mapSize := mapSize+32;
      [*] = ;
      [*] = ;MapHeight := mapSize;
      [*] = ;
      [*] = ;ExecuteState('astral.SaveShardCoords');
      [*] = ;var uid : Integer = gShards[shardInd].uid;
      [*] = ;Log('Player attacks shard with UID = ' + IntToStr(uid));
      [*] = ;
      [*] = ;gProfile.genesismode := gMapSettings.genesismode;
	  [*] = ;_prof_SaveUserProfile();
      [*] = ;UserSaveProfile();
      [*] = ;
      [*] = ;gGame.genesismode := gMapSettings.genesismode;
      [*] = ;gBoolRegister_ConvertGenesisMode := True;
      [*] = ;GUIExecuteState('EventGenesisMode');
      [*] = ;
      [*] = ;const dataPath = '.\data\game\var\genesismode.cfg';
      [*] = ;var pReplacementData : Integer = _misc_ParserGetOrCreateByKey('replacement_data', true);
      [*] = ;ParserLoadFromFileByHandle(pReplacementData, dataPath);
      [*] = ;
      [*] = ;IntRegister0 := pReplacementData;
      [*] = ;BoolRegister0 := False;
      [*] = ;MapExecuteState('DataBanReplacement');
      [*] = ;
      [*] = ;var curVisualID : Integer = 0;
      [*] = ;// world rule
      [*] = ;case gShards[shardInd].terrain of
      [*] = ;   6 : curVisualID := 2;
      [*] = ;   7 : curVisualID := 3;
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;      curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;case curVisualID of
      [*] = ;   1 : zoneName := 'Crystals';
      [*] = ;   2 : zoneName := 'Desert';
      [*] = ;   3 : zoneName := 'Deadland';
      [*] = ;   4 : zoneName := 'Autumn';
      [*] = ;   5 : zoneName := 'Vulcan';
      [*] = ;   6 : zoneName := 'Ice';
      [*] = ;end;
      [*] = ;
      [*] = ;GenerateMapNeededExtBorder(mapName, zoneName, cPresetName, MapWidth, MapHeight, 5, randKey0, randKey1, 0, 0, 0, '', '', '', '', '', '', '.\data\gui\gui.cfg', ''{'GUIInitialize'}, 'Ingame1', '', 'MakeStratHexGrid', false);
      [*] = ;
      [*] = ;_gv_SetAstralLock(1,_log_name);
      [*] = ;
      [*] = ;SetLensFlareAngle(35);
      [*] = ;SetLensFlareZOffset(0.3);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

