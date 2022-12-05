section.begin
   Name = map.ShardFinishGame
   Code : struct.begin
      [*] = ;if gGame.gameType = 2 then
      [*] = ;begin
      [*] = ;   var shardInd : Integer = gCampaign.activeShard;
      [*] = ;   var aInd : Integer = gIntRegister_CampAttackPlayer;
      [*] = ;   var dInd : Integer = gIntRegister_CampDefendPlayer;
      [*] = ;
      [*] = ;   BoolRegister0 := gBoolRegister_MapWin;
      [*] = ;   MapExecuteState('map.SetupShardPlayer');
      [*] = ;
      [*] = ;   if not (((aInd = 0) and gBoolRegister_MapLose) or ((dInd = 0) and gBoolRegister_MapWin)) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := shardInd;
      [*] = ;      IntRegister1 := gShards[gCampaign.activeShard].ipPlayer;
      [*] = ;      ExecuteState('astral.AddHiddenBuildings');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var myPlHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;   if gBoolRegister_MapWin then
      [*] = ;   gIntRegister_ShardBattleResult := 2
      [*] = ;   else
      [*] = ;   gIntRegister_ShardBattleResult := 1;
      [*] = ;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   IntRegister0 := 1;
      [*] = ;   GUIExecuteState('map.CreateStatistics');
      [*] = ;   var score : Integer = IntRegister0;
      [*] = ;
      [*] = ;   gCampaign.arrCampPlayers[0].mapScore := gCampaign.arrCampPlayers[0].mapScore + score;
      [*] = ;
      [*] = ;   var plKarma : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;   var karma : Integer = gCampaign.arrCampPlayers[0].karma;
      [*] = ;   gCampaign.arrCampPlayers[0].karma := karma + Floor((plKarma - karma) * gc_ShardToAstralKarma);
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      var profile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;      if profile > 0 then
      [*] = ;      begin
      [*] = ;         var astralAtt : Integer = gCampaign.arrCampPlayers[profile].arrAttitude[0];
      [*] = ;         var attitude : Integer = gArrDiplomacy[i][0].attitude;
      [*] = ;         if gProfile.improvedai then
      [*] = ;         begin
      [*] = ;            var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, profile);
      [*] = ;            attitude := attitude * ParserGetIntValueByKeyByHandle(pProfile, 'Sensitivity') div 100;
      [*] = ;         end;
      [*] = ;        
      [*] = ;         astralAtt := astralAtt + Floor((attitude - astralAtt) * gc_ShardToAstralAtt);
      [*] = ;         gCampaign.arrCampPlayers[profile].arrAttitude[0] := astralAtt;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

