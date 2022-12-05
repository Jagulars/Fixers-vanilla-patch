section.begin
   Name = DoInetShardGame
   Description : struct.begin
      [*] = ; IntRegister0 - start game parser
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure StartNewGame(pLan : Integer);
      [*] = ;begin
      [*] = ;   const cMapName = 'global.map';
      [*] = ;   const cPresetName = 'Default';
      [*] = ;
      [*] = ;   var i, j : Integer;
      [*] = ;   var zoneName : String = 'Default';
      [*] = ;   var randKey0 : Integer = ParserGetIntValueByKeyByHandle(pLan, 'randkey0');
      [*] = ;   var randKey1 : Integer = ParserGetIntValueByKeyByHandle(pLan, 'randkey1');
      [*] = ;
      [*] = ;   if _log then _log_lan('randKey0 = '+IntToStr(randKey0)+', randKey1 = '+IntToStr(randKey1));
      [*] = ;
      [*] = ;   SetRandomExtKey64(randKey0, randKey1);
      [*] = ;   SetMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;   SetGlobalMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;
      [*] = ;   var iSeed : Integer = randKey1 mod gc_MaxSeedValue;
      [*] = ;
      [*] = ;   var mapSize : Integer = 32;
      [*] = ;   var iMapSize : Integer = gMapSettings.size*2+6;
      [*] = ;
      [*] = ;   if (gMapEditor.enabled) then
      [*] = ;      iMapSize := gMapEditor.map.x;
      [*] = ;
      [*] = ;   const HEX_WIDTH = 10.575;
      [*] = ;   var shardWidth : Float = HEX_WIDTH*(iMapSize+2);
      [*] = ;   var shardHeight : Float = shardWidth*0.885;
      [*] = ;   var MapWidth : Integer = 40+130+Round(shardWidth);
      [*] = ;   while (MapWidth>mapSize) do
      [*] = ;      mapSize := mapSize+32;
      [*] = ;
      [*] = ;   MapWidth := mapSize;
      [*] = ;   mapSize := 32;
      [*] = ;   var MapHeight : Integer = 40+90+Round(shardHeight);
      [*] = ;   while (MapHeight>mapSize) do
      [*] = ;      mapSize := mapSize+32;
      [*] = ;   MapHeight := mapSize;
      [*] = ;
      [*] = ;   var plCount : Integer = gMapSettings.players+2;
      [*] = ;   for i := plCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      if (gMapSettings.arrplayers[i].control > 0) and (gLanShardGame.arrLanPlayers[i].lanID = 0) then
      [*] = ;      begin
      [*] = ;         for j := i to plCount-2 do
      [*] = ;         begin
      [*] = ;            gLanShardGame.arrLanPlayers[j].lanID := gLanShardGame.arrLanPlayers[j+1].lanID;
      [*] = ;            _inet_AssignHotseatProfile(gLanShardGame.arrLanPlayers[j+1].profile, gLanShardGame.arrLanPlayers[j].profile);
      [*] = ;
      [*] = ;            gMapSettings.arrplayers[j].id := gMapSettings.arrplayers[j+1].id;
      [*] = ;            gMapSettings.arrplayers[j].control := gMapSettings.arrplayers[j+1].control;
      [*] = ;            _misc_AssignDifficulty(gMapSettings.arrplayers[j+1].advdiff, gMapSettings.arrplayers[j].advdiff);
      [*] = ;         end;
      [*] = ;         plCount := plCount-1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   gMapSettings.players := plCount-2;
      [*] = ;
      [*] = ;   _misc_CreateStratMapParser(iSeed);
      [*] = ;
      [*] = ;   // world rule - need after CreateStratMapParser, cause it setup gGame.worldrule
      [*] = ;   if _worldrule_GetWorldRuleVisualExistByID(3) then
      [*] = ;   begin
      [*] = ;      case _worldrule_GetWorldRuleVisualParams(3, 1) of
      [*] = ;         1 : zoneName := 'Crystals';
      [*] = ;         2 : zoneName := 'Desert';
      [*] = ;         3 : zoneName := 'Deadland';
      [*] = ;         4 : zoneName := 'Autumn';
      [*] = ;         5 : zoneName := 'Vulcan';
      [*] = ;         6 : zoneName := 'Ice';
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var game : String = LanPublicServerProfInfo;_sa_SetIntAtIndex(game,12,Max(_sa_GetAsInt(game,12)+1,_sa_GetAsInt(game,14)+1));
      [*] = ;   LanSetMyProfInfo(game);LanPublicServerRegister();LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;   StateMachineClearVariables(GetMapInitMachineHandle);
      [*] = ;   gTutorial.map := false;
      [*] = ;   GenerateMapNeededExtBorder(cMapName, zoneName, cPresetName, MapWidth, MapHeight, 5, randKey0, randKey1, 0, 0, 0, '', '', '', '', '', '', '.\data\gui\gui.cfg', ''{'GUIInitialize'}, 'Ingame1', '', 'MakeStratHexGrid', false);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure LoadSavedGame(mapname : String);
      [*] = ;begin
      [*] = ;   var save_name,players : String;
      [*] = ;   var game_uid,n : Integer;
      [*] = ;
      [*] = ;   _inet_GetInetShardSaveParamsFromMap(mapname,save_name,game_uid,players);
      [*] = ;   n := _sa_GetNum(players);
      [*] = ;   if _log then _log_valuesL(save_name+'|PLAYERS',game_uid,n,0,0,0,0);
      [*] = ;
      [*] = ;   _prof_SyncCustomsFolderExt(gc_GameTypeFlagInternet,game_uid,-1);
      [*] = ;   StringRegister0 := save_name;
      [*] = ;   MapExecuteState('LoadMap');
      [*] = ;end;
      [*] = ;
      [*] = ;var p : Integer = IntRegister0;
      [*] = ;var mapname : String;
      [*] = ;
      [*] = ;mapname := ParserGetValueByKeyByHandle(p, 'SaveGame');
      [*] = ;if _log then _log_lan('LAN LOAD/NEW: '+mapname);
      [*] = ;if mapname <> '' then
      [*] = ;   LoadSavedGame(mapname)
      [*] = ;else
      [*] = ;   StartNewGame(p);
   struct.end
section.end

