section.begin
   Name = astral.CaptureShard
   Code : struct.begin
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;var shardUID : Integer = IntRegister1;
      [*] = ;
      [*] = ;procedure CaptureShard(var campPlayer : TCampPlayer; var shard : TShard; addHidden : Boolean);
      [*] = ;begin
      [*] = ;   var shardHnd : Integer = GetGameObjectHandleByUniqueId(shard.uid);
      [*] = ;   SetGameObjectBoolValueIndByHandle(shardHnd, gc_astral_GOStack_bCaptured, true);
      [*] = ;   var mainShardInd : Integer = campPlayer.mainShard;
      [*] = ;   var mainShardUID : Integer = gShards[mainShardInd].uid;
      [*] = ;
      [*] = ;   IntRegister0 := campPlayer.ipProfile;
      [*] = ;   IntRegister1 := shard.num;
      [*] = ;   BoolRegister0 := addHidden;
      [*] = ;   ExecuteState('astral.CaptureShardLogic');
      [*] = ;
      [*] = ;   var behHnd : Integer = GetBehaviourByClassName(shardHnd, 'TXMoveRotateWaveBehaviour');
      [*] = ;   //SetBehaviourFloatProperty(behHnd, 'OffsetTime', RandomExt);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'ClearPaths', '');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathPosition', 'mppUse');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathScale', 'mpsUse');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathRotate', 'mprNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'AddPath', '');
      [*] = ;
      [*] = ;   var mainShardHnd : Integer = GetGameObjectHandleByUniqueId(mainShardUID);
      [*] = ;   var mPosX : Float = GetGameObjectPositionXByHandle(mainShardHnd);
      [*] = ;   var mPosY : Float = GetGameObjectPositionYByHandle(mainShardHnd)+2;
      [*] = ;   var mPosZ : Float = GetGameObjectPositionZByHandle(mainShardHnd)-1.5;
      [*] = ;   var posX : Float = GetGameObjectPositionXByHandle(shardHnd);
      [*] = ;   var posY : Float = GetGameObjectPositionYByHandle(shardHnd);
      [*] = ;   var posZ : Float = GetGameObjectPositionZByHandle(shardHnd);
      [*] = ;   var scaleX : Float =  GetGameObjectScaleXByHandle(shardHnd);
      [*] = ;   var scaleY : Float =  GetGameObjectScaleYByHandle(shardHnd);
      [*] = ;   var scaleZ : Float =  GetGameObjectScaleZByHandle(shardHnd);
      [*] = ;   var distance : Float = VectorDistance(mPosX, mPosY, mPosZ, posX, posY, posZ);
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   i := 0;
      [*] = ;   var speed : Float = 1;
      [*] = ;   var curDistance : Float = 0;
      [*] = ;   while curDistance < distance do
      [*] = ;   begin
      [*] = ;      var vidn : Float = curDistance/(distance-curDistance);
      [*] = ;      var sPosX : Float = (posX+mPosX*vidn)/(1+vidn);
      [*] = ;      var sPosY : Float = (posY+mPosY*vidn)/(1+vidn);
      [*] = ;      var sPosZ : Float = (posZ+mPosZ*vidn)/(1+vidn);
      [*] = ;      SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,'+IntToStr(i)+']', sPosX);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,'+IntToStr(i)+']', sPosY);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,'+IntToStr(i)+']', sPosZ);
      [*] = ;      var sDistance : Float = VectorDistance(mPosX, mPosY, mPosZ, sPosX, sPosY, sPosZ);
      [*] = ;      if (speed<8) then
      [*] = ;      speed := speed * 1.15;
      [*] = ;      if (sDistance<8) then
      [*] = ;      begin
      [*] = ;         scaleX := scaleX*0.975;//0.75
      [*] = ;         scaleY := scaleY*0.975;
      [*] = ;         scaleZ := scaleZ*0.975;
      [*] = ;         if (distance>8) then
      [*] = ;         speed := speed/1.225;
      [*] = ;      end;
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleX[0,'+IntToStr(i)+']', scaleX);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleY[0,'+IntToStr(i)+']', scaleY);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleZ[0,'+IntToStr(i)+']', scaleZ);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,'+IntToStr(i)+']', speed);
      [*] = ;      curDistance := curDistance+0.5;
      [*] = ;      i := i+1;
      [*] = ;   end;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,'+IntToStr(i)+']', mPosX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,'+IntToStr(i)+']', mPosY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,'+IntToStr(i)+']', mPosZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleX[0,'+IntToStr(i)+']', scaleX*0.01);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleY[0,'+IntToStr(i)+']', scaleY*0.01);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleZ[0,'+IntToStr(i)+']', scaleZ*0.01);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,'+IntToStr(i)+']', (2.5)*speed);
      [*] = ;   SetBehaviourIntProperty(behHnd, 'ActivePathIndex', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsShowPath[0]', false);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsLooped[0]', false);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'StartPathTravel', '');
      [*] = ;
      [*] = ;   GameObjectDelayExecuteStateByHandle(shardHnd, 'Hide', distance/1.75);
      [*] = ;
      [*] = ;   if campPlayer.ipProfile = 0 then
      [*] = ;   begin
      [*] = ;      //move main shard up
      [*] = ;      posX := GetGameObjectPositionXByHandle(mainShardHnd);
      [*] = ;      posY := GetGameObjectPositionYByHandle(mainShardHnd);
      [*] = ;      posZ := GetGameObjectPositionZByHandle(mainShardHnd);
      [*] = ;      //SetGameObjectPositionByHandle(mainShardHnd, posX, posY, posZ);
      [*] = ;
      [*] = ;      behHnd := GetBehaviourByClassName(mainShardHnd, 'TXMoveRotateWaveBehaviour');
      [*] = ;      var behY : Float = GetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,1]');
      [*] = ;      SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;      SetBehaviourStringProperty(behHnd, 'ClearPaths', '');
      [*] = ;      SetBehaviourStringProperty(behHnd, 'MovementPathPosition', 'mppUse');
      [*] = ;      SetBehaviourStringProperty(behHnd, 'MovementPathScale', 'mpsNone');
      [*] = ;      SetBehaviourStringProperty(behHnd, 'MovementPathRotate', 'mprNone');
      [*] = ;      SetBehaviourStringProperty(behHnd, 'AddPath', '');
      [*] = ;
      [*] = ;      SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,0]', posX);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,0]', posY);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,0]', posZ);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,0]', 0.3);
      [*] = ;
      [*] = ;      var trgY : Float;
      [*] = ;      if behY > posY then
      [*] = ;      trgY := behY + 3
      [*] = ;      else
      [*] = ;      trgY := posY + 3;
      [*] = ;
      [*] = ;      SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,1]', PosX);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,1]', trgY);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,1]', PosZ);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,1]', 0.3);
      [*] = ;      SetBehaviourIntProperty(behHnd, 'ActivePathIndex', 0);
      [*] = ;      SetBehaviourBoolProperty(behHnd, 'PathsShowPath[0]', false);
      [*] = ;      SetBehaviourBoolProperty(behHnd, 'PathsLooped[0]', false);
      [*] = ;      SetBehaviourStringProperty(behHnd, 'StartPathTravel', '');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;{function CanGetBuildingsFromOneShard(cnt : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   var i, j : Integer = 0;
      [*] = ;
      [*] = ;   for i := 0 to gc_MaxShards-1 do
      [*] = ;   if (gShards[i].uid > 0) and (gShards[i].ipPlayer < 0) then
      [*] = ;   begin
      [*] = ;      for j := 0 to gc_MaxShardBuild-1 do
      [*] = ;      if gShards[i].arBuilding[j] = 0 then
      [*] = ;      break;
      [*] = ;
      [*] = ;      if j <= cnt then
      [*] = ;      begin
      [*] = ;         Result := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;{function IsBuildingInList(pParser : Integer; buildingID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   var pBuildLevels : Integer = ParserSelectByHandleByKey(pParser, 'Levels');
      [*] = ;   var i, j : Integer;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pBuildLevels)-1 do
      [*] = ;   begin
      [*] = ;      var pBuildLevel : Integer = ParserSelectByHandleByIndex(pBuildLevels, i);
      [*] = ;      var pLevelBuildings : Integer = ParserSelectByHandleByKey(pBuildLevel, 'Buildings');
      [*] = ;
      [*] = ;      for j := 0 to ParserGetCountByHandle(pLevelBuildings)-1 do
      [*] = ;      begin
      [*] = ;         var pLevelBuilding : Integer = ParserSelectByHandleByIndex(pLevelBuildings, j);
      [*] = ;         var id : Integer = ParserGetIntValueByKeyByHandle(pLevelBuilding, 'BuildingID');
      [*] = ;
      [*] = ;         if id = buildingID then
      [*] = ;         begin
      [*] = ;            Result := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;// make list of overlords
      [*] = ;_rand_ClearRoll;
      [*] = ;var i, j : Integer;
      [*] = ;var arPlayers : array [0..gc_MaxCampPlayer] of Integer;
      [*] = ;var count : Integer = 0;
      [*] = ;
      [*] = ;for i := 1 to gc_MaxCampPlayer-1 do
      [*] = ;begin
      [*] = ;   if gCampaign.arrCampPlayers[i].firstMeet and gCampaign.arrCampPlayers[i].inGame then
      [*] = ;   begin
      [*] = ;      var f : Boolean = true;
      [*] = ;      for j := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         if gGame.arrPlayerSet[j] = i then
      [*] = ;         begin
      [*] = ;            f := false;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if f then
      [*] = ;      begin
      [*] = ;         //gArrRollerN[count] := i;
      [*] = ;         //gArrRollerP[count] := 10;
      [*] = ;         arPlayers[count] := i;
      [*] = ;         count := count + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var shardHnd : Integer = GetGameObjectHandleByUniqueId(shardUID);
      [*] = ;var shardInd : Integer = _shard_GetShardByUID(shardUID);
      [*] = ;if (shardHnd <> 0) and (shardInd >= 0) then
      [*] = ;begin
      [*] = ;   var i, j, k, l : Integer;
      [*] = ;   var mainShardInd : Integer = gCampaign.arrCampPlayers[plIndex].mainShard;
      [*] = ;   var mainShardUID : Integer = gShards[mainShardInd].uid;
      [*] = ;
      [*] = ;   if shardInd <> mainShardInd then
      [*] = ;   begin
      [*] = ;      if plIndex = 0 then
      [*] = ;      begin
      [*] = ;         for i := 0 to gc_MaxShardBuild-1 do
      [*] = ;         begin
      [*] = ;            var buildID : Integer = gShards[shardInd].arBuilding[i];
      [*] = ;
      [*] = ;            if buildID > 0 then
      [*] = ;            begin
      [*] = ;               for j := 0 to gc_MaxShards-1 do
      [*] = ;               if (j <> shardInd) and (not _shard_IsMain(gShards[j])) then
      [*] = ;               begin
      [*] = ;                  for k := 0 to gc_MaxShardBuild-1 do
      [*] = ;                  if gShards[j].arBuilding[k] = buildID then
      [*] = ;                  begin
      [*] = ;                     if count > 0 then
      [*] = ;                     begin
      [*] = ;                        //var playerID : Integer = _rand_Roll(true);
      [*] = ;                        var ind : Integer = _rand_Random(count);
      [*] = ;                        var playerID : Integer = arPlayers[ind];
      [*] = ;
      [*] = ;                        for l := ind to count-1 do
      [*] = ;                        arPlayers[l] := arPlayers[l+1];
      [*] = ;                        count := count - 1;
      [*] = ;
      [*] = ;                        CaptureShard(gCampaign.arrCampPlayers[playerID], gShards[j], true);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     // destroy shard
      [*] = ;                     var uid : Integer = gShards[j].uid;
      [*] = ;                     var goHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'DoDestroy');
      [*] = ;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      CaptureShard(gCampaign.arrCampPlayers[plIndex], gShards[shardInd], false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (plIndex = 0) and (gTutorial.bonus = 0) then
      [*] = ;gTutorial.bonus := 1;
      [*] = ;
      [*] = ;gIntRegister_AstralSelectedShard := 0;
      [*] = ;
      [*] = ;BoolRegister0 := false;
      [*] = ;BoolRegister1 := true;
      [*] = ;ExecuteState('astral.EndTurn');
   struct.end
   Description : struct.begin
      [*] = ;IntRegister0 - player index
      [*] = ;IntRegister1 - capture shard uid
   struct.end
section.end

