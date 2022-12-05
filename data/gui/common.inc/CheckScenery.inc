section.begin
   Name = CheckScenery
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\CHECKSCENERY';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var checkFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Check Flags: '+IntToStr(checkFlags)+']',_log_trace);
      [*] = ;
      [*] = ;var pSceneryData : Integer = _misc_ParserGetOrCreateByKey('scenery_data', False);
      [*] = ;if ParserGetCountByHandle(pSceneryData) = 0 then
      [*] = ;   ParserLoadFromFile(gc_SceneryDataPath);
      [*] = ;
      [*] = ;procedure ClearSceneryBySection(const sectionKey : String);
      [*] = ;begin
      [*] = ;   var stateName : String;
      [*] = ;   var i, pPruner : Integer;
      [*] = ;   
      [*] = ;   var pPruners : Integer = ParserSelectByHandleByKey(pSceneryData, sectionKey);
      [*] = ;   
      [*] = ;   // clear scenery
      [*] = ;   for i := 0 to ParserGetCountByHandle(pPruners)-1 do
      [*] = ;   begin
      [*] = ;      pPruner := ParserSelectByHandleByIndex(pPruners, i);
      [*] = ;      stateName := ParserGetValueByKeyByHandle(pPruner, 'StateName');
      [*] = ;      
      [*] = ;      if stateName <> '' then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 1;
      [*] = ;         MapExecuteState(stateName);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateSceneryBySection(const sectionKey : String; const graphicsLevel : Integer);
      [*] = ;begin
      [*] = ;   var stateName, playerName : String;
      [*] = ;   var i, j, k, pPruner, pPlayers, pPrunerPlayer, count : Integer;
      [*] = ;   
      [*] = ;   var pPruners : Integer = ParserSelectByHandleByKey(pSceneryData, sectionKey);
      [*] = ;   
      [*] = ;   // create and prune
      [*] = ;   for i := 0 to ParserGetCountByHandle(pPruners)-1 do
      [*] = ;   begin
      [*] = ;      pPruner := ParserSelectByHandleByIndex(pPruners, i);
      [*] = ;      stateName := ParserGetValueByKeyByHandle(pPruner, 'StateName');
      [*] = ;      
      [*] = ;      if (stateName <> '') and (graphicsLevel < _pars_GetIntValueByKeyByHandleDef(pPruner, 'ClearAll', 1000)) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 2;
      [*] = ;         MapExecuteState(stateName);
      [*] = ;         
      [*] = ;         pPlayers := ParserSelectByHandleByKey(pPruner, 'Players');
      [*] = ;            
      [*] = ;         for j := 0 to ParserGetCountByHandle(pPlayers)-1 do
      [*] = ;         begin
      [*] = ;            pPrunerPlayer := ParserSelectByHandleByIndex(pPlayers, j);
      [*] = ;            _obj_CleanPruner();
      [*] = ;         
      [*] = ;            playerName := ParserGetValueByKeyByHandle(pPrunerPlayer, 'Name');
      [*] = ;            count := _obj_PrunePlayer(pPrunerPlayer, graphicsLevel, 0);
      [*] = ;            _log_Obj(playerName+ ' objects pruned: '+IntToStr(count)+', graphics level: '+IntToStr(graphicsLevel));
      [*] = ;               
      [*] = ;             // we need to store province scenery pruner so we can easily prune each time new province patterns are added.
      [*] = ;            if SameText(playerName, 'prov.pattern') then
      [*] = ;            begin
      [*] = ;               for k := 0 to gc_MaxPrunerObjects-1 do
      [*] = ;               begin
      [*] = ;                  gProvinceSceneryPruner[k].baseName := gSceneryPruner[k].baseName;
      [*] = ;                  gProvinceSceneryPruner[k].frequency := gSceneryPruner[k].frequency;
      [*] = ;                  gProvinceSceneryPruner[k].count := gSceneryPruner[k].count;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckRituals();
      [*] = ;begin
      [*] = ;   procedure CheckProvinceRituals(const provHandle, pProvRituals : Integer; const bDestroy : Boolean);
      [*] = ;   begin
      [*] = ;      var i, pRitual : Integer;
      [*] = ;      for i := 0 to ParserGetCountByHandle(pProvRituals)-1 do
      [*] = ;      begin
      [*] = ;         pRitual := ParserSelectByHandleByIndex(pProvRituals, i);
      [*] = ;         IntRegister0 := ParserGetIntValueByKeyByHandle(pRitual, 'RitualID');
      [*] = ;         if bDestroy then
      [*] = ;            GameObjectExecuteStateByHandle(provHandle, 'DestroyRitualFX')
      [*] = ;         else
      [*] = ;            GameObjectExecuteStateByHandle(provHandle, 'CreateRitualFX');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure CheckProvincesRitual(const bDestroy : Boolean);
      [*] = ;   begin
      [*] = ;      var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;      var i, pStratHexCell, provHandle : Integer;
      [*] = ;      for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         provHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID'));
      [*] = ;
      [*] = ;         if provHandle <> 0 then
      [*] = ;         begin
      [*] = ;            CheckProvinceRituals(provHandle, ParserSelectByHandleByKey(pStratHexCell, 'CastedRituals'), bDestroy);
      [*] = ;            CheckProvinceRituals(provHandle, ParserSelectByHandleByKey(pStratHexCell, 'Rituals'), bDestroy);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if _obj_EnabledByFlag(gc_ObjectFlagRitual) then
      [*] = ;      CheckProvincesRitual(False)
      [*] = ;   else
      [*] = ;      CheckProvincesRitual(True);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckAstral();
      [*] = ;begin
      [*] = ;   MapExecuteState('astral.DoCreateBackground');
      [*] = ;   
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName('shards_fly');
      [*] = ;   var count : Integer = GetPlayerGameObjectsCountByHandle(plHandle);
      [*] = ;   
      [*] = ;   if _obj_EnabledByFlag(gc_ObjectFlagAstralDecor) then
      [*] = ;   begin
      [*] = ;      if count = 0 then
      [*] = ;      begin
      [*] = ;         MapExecuteState('astral.DoCreateSpaceFog');
      [*] = ;         MapExecuteState('astral.DoCreateMeteors');
      [*] = ;         if gIntRegister_CurGameMode = gc_GameModeMenu then
      [*] = ;            MapExecuteState('menu.DoCreateShards');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if count > 0 then
      [*] = ;      begin
      [*] = ;         ClearPlayerGameObjectsByHandle(plHandle);
      [*] = ;         ClearPlayerGameObjectsByHandle(GetPlayerHandleByName('pfxPlayer'));
      [*] = ;         if gIntRegister_CurGameMode = gc_GameModeMenu then
      [*] = ;            DeletePlayerByHandle(GetPlayerHandleByName(gc_astral_shardsPlayerName));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;case gIntRegister_CurGameMode of
      [*] = ;   gc_GameModeMenu, gc_GameModeAstral : begin
      [*] = ;     if (checkFlags and 1) > 0 then CheckAstral();
      [*] = ;   end;
      [*] = ;   gc_GameModeTactics, gc_GameModeStrategy : 
      [*] = ;   begin
      [*] = ;      if (gGame.gameType <> gc_GameTypeHotseatBattle) and (gGame.gameType <> gc_GameTypeLanBattle) then
      [*] = ;      begin
      [*] = ;         if (checkFlags and 14) > 0 then
      [*] = ;         begin
      [*] = ;            if (checkFlags and 2) > 0 then ClearSceneryBySection('ShardScenery');
      [*] = ;            if (checkFlags and 4) > 0 then ClearSceneryBySection('TownScenery');
      [*] = ;            if (checkFlags and 8) > 0 then ClearSceneryBySection('ProvinceScenery');
      [*] = ;            
      [*] = ;            var tnListIndex : Integer = GetActiveTrackNodeListIndex();
      [*] = ;            if tnListIndex <> 0 then
      [*] = ;               SetActiveTrackNodeList(0); // we need to switch zero (map track nodes) in case we are in battle where track node list index is one.
      [*] = ;         
      [*] = ;            _map_DefaultTrackNodePositions();
      [*] = ;            if (checkFlags and 2) > 0 then CreateSceneryBySection('ShardScenery', gProfile.shardscenery);
      [*] = ;            if (checkFlags and 4) > 0 then CreateSceneryBySection('TownScenery', gProfile.townscenery);
      [*] = ;            if (checkFlags and 8) > 0 then CreateSceneryBySection('ProvinceScenery', gProfile.provincescenery);
      [*] = ;            _map_AdjustTrackNodesToProvinces();   
      [*] = ;            
      [*] = ;            if tnListIndex <> 0 then
      [*] = ;               SetActiveTrackNodeList(tnListIndex);
      [*] = ;         
      [*] = ;            gBoolRegister_NeedSeasonChangeObjects := True;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         if (checkFlags and 1) > 0 then CheckRituals();
      [*] = ;      end;
      [*] = ;         
      [*] = ;      if (checkFlags and $10) > 0 then 
      [*] = ;      begin
      [*] = ;         ClearSceneryBySection('BattleScenery');
      [*] = ;         
      [*] = ;         if (gIntRegister_CurGameMode = gc_GameModeTactics) then
      [*] = ;         begin
      [*] = ;            CreateSceneryBySection('BattleScenery', gProfile.battlescenery);
      [*] = ;            gBoolRegister_NeedSeasonChangeBattle := True;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      MapExecuteState('CreateSeasons');
      [*] = ;      gBoolRegister_NeedSeasonChangeObjects := False;
      [*] = ;      gBoolRegister_NeedSeasonChangeBattle := False;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
