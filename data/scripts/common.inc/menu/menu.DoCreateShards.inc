section.begin
   Name = menu.DoCreateShards
   UsedFileName = 
   Code : struct.begin
      [*] = ;function DoStandPatternGroup(plHnd : Integer; pattern : String; x, z, angle : Float) : Integer;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var c : Integer = GetPlayerGameObjectsCountByHandle(plHnd);
      [*] = ;   StandPattern(plHnd, pattern, x, z, angle);
      [*] = ;   var grHnd : Integer = CreateGroupByPlHandle(plHnd, 'group.' + IntToStr(GetPlayerCountOfGroupsByHandle(plHnd)));
      [*] = ;   for i:=GetPlayerGameObjectsCountByHandle(plHnd)-1 downto c do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectHandleByIndex(i, plHnd);
      [*] = ;      GroupAddGameObjectByHandle(grHnd, goHnd);
      [*] = ;   end;
      [*] = ;   Result := grHnd;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoSpawnCloudSatellites(goHnd : Integer; posX, posY, posZ : Float; satCount : Integer; satSpawnRad, cloudScaleMod : Float);
      [*] = ;begin
      [*] = ;   var j : Integer;
      [*] = ;   var effHnd : Integer;
      [*] = ;   var count : Integer = floor(2+Random*(satCount-2));
      [*] = ;   for j:=0 to count-1 do
      [*] = ;   begin
      [*] = ;      var i : Integer = GetEffectCount(goHnd)+1;
      [*] = ;      GameObjectPFXSrcLibCreateByHandle(goHnd, 'defsprite', 'cloud'+IntToStr(i));
      [*] = ;      effHnd := GetEffectByKey(goHnd, 'cloud'+IntToStr(i));
      [*] = ;      var dirX, dirY, dirZ : Float;
      [*] = ;      var scale : Float = Lerp(15, 30, Random)*cloudScaleMod;
      [*] = ;
      [*] = ;      posZ := PosZ+Lerp(-2*satSpawnRad, 4*satSpawnRad, Random);
      [*] = ;      dirX := Lerp(0, 8*satSpawnRad, Random);
      [*] = ;      dirY := 0;
      [*] = ;      dirZ := 0;
      [*] = ;      VectorRotateY(dirX, dirY, dirZ, Random*360);
      [*] = ;      SetBehaviourAffineVectorProperty(effHnd, 'Position', posX+dirX, posY+dirZ, posZ);
      [*] = ;      SetBehaviourAffineVectorProperty(effHnd, 'Scale', scale, scale, scale);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel', Lerp(0.2, 0.25, Random));
      [*] = ;      SetBehaviourVectorProperty(effHnd, 'LifeColor', 0.9, 0.9, 1.0, 1);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'MirrorV', False);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Width', 1);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Height', 0.5);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoCreateEffects(const goHnd : Integer);
      [*] = ;begin
      [*] = ;   var j : Integer;
      [*] = ;   var effHnd : Integer;
      [*] = ;   var atmScale, satSpawnRadMod, cloudSpawnRadMin, cloudSpawnRadMax, cloudHeightMin, cloudHeightMax, cloudScaleMod : Float;
      [*] = ;   var satCount, cloudCount : Integer;
      [*] = ;   var traceXOffset, traceZOffset, traceScale : Float = 1;
      [*] = ;   var atmHeight : Float = 0;
      [*] = ;   case (StrToLowerCase(GetGameObjectBaseNameByHandle(goHnd))) of
      [*] = ;      'shard1' : begin
      [*] = ;         atmScale := 200;
      [*] = ;         cloudCount := 6;
      [*] = ;         cloudSpawnRadMin := 28;
      [*] = ;         cloudSpawnRadMax := 60;
      [*] = ;         cloudHeightMin := 15;
      [*] = ;         cloudHeightMax := 32.5;
      [*] = ;         cloudScaleMod := 2;
      [*] = ;         satCount := 5;
      [*] = ;         satSpawnRadMod := 0.8;
      [*] = ;         traceXOffset := 0;
      [*] = ;         traceZOffset := 0;
      [*] = ;         traceScale := 400;
      [*] = ;      end;
      [*] = ;      'shard2' : begin
      [*] = ;         atmScale := 205;
      [*] = ;         atmHeight := 0;
      [*] = ;         cloudCount := 5;
      [*] = ;         cloudSpawnRadMin := 40;
      [*] = ;         cloudSpawnRadMax := 65;
      [*] = ;         cloudHeightMin := 15;
      [*] = ;         cloudHeightMax := 26;
      [*] = ;         cloudScaleMod := 2.0;
      [*] = ;         satCount := 5;
      [*] = ;         satSpawnRadMod := 0.9;
      [*] = ;         traceXOffset := 0;
      [*] = ;         traceZOffset := 0;
      [*] = ;         traceScale := 410;
      [*] = ;      end;
      [*] = ;      'shard4' : begin
      [*] = ;         atmScale := 200;
      [*] = ;         atmHeight := 15;
      [*] = ;         cloudCount := 4;
      [*] = ;         cloudSpawnRadMin := 25;
      [*] = ;         cloudSpawnRadMax := 45;
      [*] = ;         cloudHeightMin := 25;
      [*] = ;         cloudHeightMax := 30;
      [*] = ;         cloudScaleMod := 1.7;
      [*] = ;         satCount := 5;
      [*] = ;         satSpawnRadMod := 0.9;
      [*] = ;         traceXOffset := 0;
      [*] = ;         traceZOffset := 0;
      [*] = ;         traceScale := 410;
      [*] = ;      end;
      [*] = ;      'shard3' : begin
      [*] = ;         atmScale := 200;
      [*] = ;         atmHeight := 8;
      [*] = ;         cloudCount := 4;
      [*] = ;         cloudSpawnRadMin := 30;
      [*] = ;         cloudSpawnRadMax := 45;
      [*] = ;         cloudHeightMin := 20;
      [*] = ;         cloudHeightMax := 26;
      [*] = ;         cloudScaleMod := 1.65;
      [*] = ;         satCount := 5;
      [*] = ;         satSpawnRadMod := 0.9;
      [*] = ;         traceXOffset := 0;
      [*] = ;         traceZOffset := 0;
      [*] = ;         traceScale := 350;
      [*] = ;      end;
      [*] = ;      'shard7' : begin
      [*] = ;         atmScale := 145;
      [*] = ;         cloudCount := 3;
      [*] = ;         cloudSpawnRadMin := 30;
      [*] = ;         cloudSpawnRadMax := 42;
      [*] = ;         cloudHeightMin := 19;
      [*] = ;         cloudHeightMax := 19;
      [*] = ;         cloudScaleMod := 1.4;
      [*] = ;         satCount := 6;
      [*] = ;         satSpawnRadMod := 0.9;
      [*] = ;         traceXOffset := 0;
      [*] = ;         traceZOffset := 0;
      [*] = ;         traceScale := 350;
      [*] = ;      end;
      [*] = ;      'shard8' : begin
      [*] = ;         atmScale := 145;
      [*] = ;         cloudCount := 3;
      [*] = ;         cloudSpawnRadMin := 30;
      [*] = ;         cloudSpawnRadMax := 38;
      [*] = ;         cloudHeightMin := 18;
      [*] = ;         cloudHeightMax := 22;
      [*] = ;         cloudScaleMod := 1.4;
      [*] = ;         satCount := 6;
      [*] = ;         satSpawnRadMod := 0.9;
      [*] = ;         traceXOffset := 0;
      [*] = ;         traceZOffset := 0;
      [*] = ;         traceScale := 350;
      [*] = ;      end;
      [*] = ;      'shard5' : begin
      [*] = ;         atmScale := 95;
      [*] = ;         atmHeight := 15;
      [*] = ;         cloudCount := 3;
      [*] = ;         cloudSpawnRadMin := 5;
      [*] = ;         cloudSpawnRadMax := 20;
      [*] = ;         cloudHeightMin := 28;
      [*] = ;         cloudHeightMax := 28;
      [*] = ;         cloudScaleMod := 1.15;
      [*] = ;         satCount := 5;
      [*] = ;         satSpawnRadMod := 0.8;
      [*] = ;         traceXOffset := 0;
      [*] = ;         traceZOffset := 0;
      [*] = ;         traceScale := 225;
      [*] = ;      end;
      [*] = ;      'shard6' : begin
      [*] = ;         atmScale := 100;
      [*] = ;         atmHeight := 15;
      [*] = ;         cloudCount := 3;
      [*] = ;         cloudSpawnRadMin := 5;
      [*] = ;         cloudSpawnRadMax := 20;
      [*] = ;         cloudHeightMin := 28;
      [*] = ;         cloudHeightMax := 28;
      [*] = ;         cloudScaleMod := 1.2;
      [*] = ;         satCount := 5;
      [*] = ;         satSpawnRadMod := 0.9;
      [*] = ;         traceXOffset := 0;
      [*] = ;         traceZOffset := 0;
      [*] = ;         traceScale := 225;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for j:=0 to cloudCount-1 do
      [*] = ;   begin
      [*] = ;      var i : Integer = GetEffectCount(goHnd)+1;
      [*] = ;      GameObjectPFXSrcLibCreateByHandle(goHnd, 'defsprite', 'cloud'+IntToStr(i));
      [*] = ;      effHnd := GetEffectByKey(goHnd, 'cloud'+IntToStr(i));
      [*] = ;      var posX, posY, posZ : Float = 0;
      [*] = ;      var dirX, dirY, dirZ : Float = 0;
      [*] = ;      var scale : Float = Lerp(17, 31, Random)*cloudScaleMod;
      [*] = ;      var hRand : Float = Random;
      [*] = ;      posZ := Lerp(cloudHeightMax*1.45, cloudHeightMin, hRand+(0.5-Random)*0.15);
      [*] = ;      dirX := Lerp(cloudSpawnRadMin, cloudSpawnRadMax, hRand);
      [*] = ;      VectorRotateY(dirX, dirY, dirZ, Random*360);
      [*] = ;      SetBehaviourAffineVectorProperty(effHnd, 'Position', posX+dirX, posY+dirZ, posZ);
      [*] = ;      DoSpawnCloudSatellites(goHnd, posX+dirX, posY+dirZ, posZ, satCount, satSpawnRadMod, cloudScaleMod);
      [*] = ;      SetBehaviourAffineVectorProperty(effHnd, 'Scale', scale, scale, scale);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel', Lerp(0.4, 0.7, Random));
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'MirrorV', False);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Width', 1);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Height', 0.5);
      [*] = ;   end;
      [*] = ;
      [*] = ;   GameObjectPFXSrcLibCreateByHandle(goHnd, 'defsprite', 'atmosphere');
      [*] = ;   effHnd := GetEffectByKey(goHnd, 'atmosphere');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'LibMaterialName', 'astralatmosphere');
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'MirrorV', False);
      [*] = ;   var posX, posY, posZ : Float = 0;
      [*] = ;   SetBehaviourAffineVectorProperty(effHnd, 'Position', posX, posY, posZ+atmHeight);
      [*] = ;   atmScale := atmScale*0.93;
      [*] = ;   SetBehaviourAffineVectorProperty(effHnd, 'Scale', atmScale, atmScale, atmScale);
      [*] = ;   SetBehaviourVectorProperty(effHnd, 'LifeColor', 0.8, 0.9, 1.0, 1);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'AlphaChannel', 0.725);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'NoZTest', True);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'NoZWrite', True);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'Width', 1);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'Height', 1);
      [*] = ;
      [*] = ;   if not gProfile.simplegraphics then // causes flickering with imposters
      [*] = ;   begin
      [*] = ;      GameObjectPFXSrcLibCreateByHandle(goHnd, 'defsprite', 'trace');
      [*] = ;      effHnd := GetEffectByKey(goHnd, 'trace');
      [*] = ;      SetBehaviourStringProperty(effHnd, 'LibMaterialName', 'astralshadow');
      [*] = ;      //SetBehaviourBoolProperty(effHnd, 'MirrorV', False);
      [*] = ;      SetBehaviourAffineVectorProperty(effHnd, 'Position', posX, posY, posZ);
      [*] = ;      SetBehaviourAffineVectorProperty(effHnd, 'Scale', traceScale, traceScale, traceScale);
      [*] = ;      SetBehaviourVectorProperty(effHnd, 'LifeColor', 1.0, 1.0, 1.0, 1);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'AlphaChannel', 0.55);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Rotation', 210);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'NoZTest', False);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'NoZWrite', True);
      [*] = ;      var width : Float = 0.45;
      [*] = ;      var height : Float = 3;
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Width', width);
      [*] = ;      SetBehaviourFloatProperty(effHnd, 'Height', height);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'MirrorV', True);
      [*] = ;      SetBehaviourBoolProperty(effHnd, 'MirrorU', True);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoCreateBehaviour(const goHnd : Integer; const radius, behangle, scale, speed, x, y, z, xdisp, zdisp : Float);
      [*] = ;begin
      [*] = ;   var behHnd : Integer = BehaviourCreate(goHnd, 'TXMoveRotateWaveBehaviour', true, false);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'OffsetTime', RandomExt);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'RollAngle', (0.5-RandomExt)*10);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WavingAmpX', 0.3+(0.5-RandomExt)*0.2);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WavingAmpY', 0.3+(0.5-RandomExt)*0.2);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WavingAmpZ', 0.3+(0.5-RandomExt)*0.2);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WavingFreqX', 2);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WavingFreqY', 0.5);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WavingFreqZ', 2);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WaveTimeX', 1*pi*0.1);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WaveTimeY', 2*pi*0.1);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'WaveTimeZ', 1*pi*0.1);
      [*] = ;   var waveSinCos : array [0..4] of String;
      [*] = ;   waveSinCos[0] := 'wscNone';
      [*] = ;   waveSinCos[1] := 'wscSin';
      [*] = ;   waveSinCos[2] := 'wscSin';
      [*] = ;   waveSinCos[3] := 'wscCos';
      [*] = ;   waveSinCos[4] := 'wscCos';
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosX', waveSinCos[Floor(RandomExt*5)]);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosY', waveSinCos[Floor(RandomExt*5)]);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosZ', waveSinCos[Floor(RandomExt*5)]);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'ClearPaths', '');
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathPosition', 'mppUse');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathScale', 'mpsNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathRotate', 'mprNone');
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'AddPath', '');
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to 36 do
      [*] = ;   begin
      [*] = ;      var angle : Float = behangle + i * 10;
      [*] = ;      if (angle>=360) then
      [*] = ;      angle := angle - 360;
      [*] = ;      SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,'+IntToStr(i)+']', x+radius*Cos(angle*pi/180)*xdisp);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,'+IntToStr(i)+']', y);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,'+IntToStr(i)+']', z+radius*Sin(angle*pi/180)*zdisp);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleX[0,'+IntToStr(i)+']', scale);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleY[0,'+IntToStr(i)+']', scale);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesScaleZ[0,'+IntToStr(i)+']', scale);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,'+IntToStr(i)+']', speed);
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetBehaviourIntProperty(behHnd, 'ActivePathIndex', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsShowPath[0]', false);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsLooped[0]', true);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'StartPathTravel', '');
      [*] = ;
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;end;
      [*] = ;
      [*] = ;function DoCreateShard(const plHnd : Integer; const px, py, pz, scale, angle, radius, behangle, speed : Float; const pattern : String; const bx, bz, dispx, dispz : Float) : Integer;
      [*] = ;begin
      [*] = ;   var shardHnd, i : Integer = 0;
      [*] = ;
      [*] = ;   var terrain : Integer = 0;
      [*] = ;   var patternTmp : String = pattern;
      [*] = ;   if (random<0.3) then
      [*] = ;   begin
      [*] = ;      if (random<0.5) then
      [*] = ;      begin
      [*] = ;         patternTmp := patternTmp+'-desert';
      [*] = ;         terrain := 6;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         patternTmp := patternTmp+'-deadland';
      [*] = ;         terrain := 7;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var grHnd : Integer = DoStandPatternGroup(plHnd, patternTmp, px, pz, angle);
      [*] = ;   for i:=GetGroupCountGameObjectsByHandle(grHnd)-1 downto 0 do
      [*] = ;   if (GetGameObjectPlayableObjectByHandle(GetGroupGOHandleByGOIndexByHandle(grHnd, i))) then
      [*] = ;   begin
      [*] = ;      shardHnd := GetGroupGOHandleByGOIndexByHandle(grHnd, i);
      [*] = ;      GameObjectMakeUniqId(shardHnd);
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (terrain=6) or (terrain=7) then
      [*] = ;   begin
      [*] = ;      var mat : String = GetGameObjectMaterialNameByHandle(shardHnd);
      [*] = ;      var num : String = SubStr(mat, StrLength(mat), 1);
      [*] = ;      mat := SubStr(mat, 1, StrLength(mat)-1);
      [*] = ;      if (terrain=6) then
      [*] = ;      mat := mat+'desert'+num
      [*] = ;      else
      [*] = ;      if (terrain=7) then
      [*] = ;      mat := mat+'deadland'+num;
      [*] = ;      SetGameObjectMaterialNameByHandle(shardHnd, mat);
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=GetGroupCountGameObjectsByHandle(grHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHnd, i);
      [*] = ;      if (goHnd<>shardHnd) then
      [*] = ;      begin
      [*] = ;         GroupRemoveGameObjectByHandle(grHnd, goHnd);
      [*] = ;         GameObjectParentToChildAbsolute(goHnd, shardHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var x : Float = GetGameObjectPositionXByHandle(shardHnd);
      [*] = ;   var y : Float = GetGameObjectPositionYByHandle(shardHnd)+py;
      [*] = ;   var z : Float = GetGameObjectPositionZByHandle(shardHnd);
      [*] = ;   SetGameObjectPositionByHandle(shardHnd, x, y, z);
      [*] = ;
      [*] = ;   GameObjectResetAndPitchTurnRollByHandle(shardHnd, -90, 90, 90);
      [*] = ;   SetGameObjectTurnAngleByHandle(shardHnd, 105);
      [*] = ;
      [*] = ;   var scalex : Float = GetGameObjectScaleXByHandle(shardHnd) * scale;
      [*] = ;   var scaley : Float = GetGameObjectScaleYByHandle(shardHnd) * scale;
      [*] = ;   var scalez : Float = GetGameObjectScaleZByHandle(shardHnd) * scale;
      [*] = ;   SetGameObjectScaleByHandle(shardHnd, scalex, scaley, scalez);
      [*] = ;
      [*] = ;   DoCreateEffects(shardHnd);
      [*] = ;   DoCreateBehaviour(shardHnd, radius, behangle, scalex, speed, bx, GetGameObjectPositionYByHandle(shardHnd), bz, dispx, dispz);
      [*] = ;
      [*] = ;   Result := shardHnd;
      [*] = ;end;
      [*] = ;
      [*] = ;const cAstralRaceName = 'astral';
      [*] = ;const cAstralControlMode = 'cmNone';
      [*] = ;
      [*] = ;var plSharsdHnd : Integer = GetPlayerHandleByName(gc_astral_shardsPlayerName);
      [*] = ;if plSharsdHnd = 0 then
      [*] = ;plSharsdHnd := CreatePlayer(gc_astral_shardsPlayerName, cAstralRaceName, cAstralControlMode)
      [*] = ;else
      [*] = ;ClearPlayerGameObjectsByHandle(plSharsdHnd);
      [*] = ;
      [*] = ;var arrPatterns : array [0..7] of String;
      [*] = ;arrPatterns[0] := 'astral-island-big-1';
      [*] = ;arrPatterns[1] := 'astral-island-big-2';
      [*] = ;arrPatterns[2] := 'astral-island-big-3';
      [*] = ;arrPatterns[3] := 'astral-island-big-4';
      [*] = ;arrPatterns[4] := 'astral-island-small-1';
      [*] = ;arrPatterns[5] := 'astral-island-small-2';
      [*] = ;arrPatterns[6] := 'astral-island-small-3';
      [*] = ;arrPatterns[7] := 'astral-island-small-4';
      [*] = ;
      [*] = ;const cMinShardsCount = 5; // 5
      [*] = ;const cMaxShardsCount = 10; // 10
      [*] = ;
      [*] = ;var maxShardsCount : Integer = cMinShardsCount+Floor(RandomExt*(cMaxShardsCount-cMinShardsCount))+1;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;for i := maxShardsCount-1 downto 0 do
      [*] = ;begin
      [*] = ;   var count : Integer = maxShardsCount div 2;
      [*] = ;
      [*] = ;   var behangle : Float = i*(360/count)+(0.5-RandomExt)*2*(360/count)*0.25;
      [*] = ;   if (behangle>=360) then
      [*] = ;   behangle := behangle-360;
      [*] = ;
      [*] = ;   var behx : Float = 0;
      [*] = ;   var behz : Float = -35;
      [*] = ;   var dispx : Float = 2.5;
      [*] = ;   var dispz : Float = 1;
      [*] = ;
      [*] = ;   var radius : Float = 10;
      [*] = ;
      [*] = ;   var posx : Float = behx + radius*Cos(behangle*pi/180)*dispx;
      [*] = ;   var posy : Float = i*3; // 8+i*3
      [*] = ;   var posz : Float = behz + radius*Sin(behangle*pi/180)*dispz;
      [*] = ;   posx := posx + (0.5-RandomExt) * radius;
      [*] = ;   posy := posy + (0.5-RandomExt) * radius;
      [*] = ;   posz := posz + (0.5-RandomExt) * radius;
      [*] = ;
      [*] = ;   var pattern : String = arrPatterns[Floor(RandomExt*8)];
      [*] = ;
      [*] = ;   var scale : Float = 1;
      [*] = ;   if (StrExists(pattern, 'small')) then
      [*] = ;   scale := 1.25
      [*] = ;   else
      [*] = ;   scale := 1.125;
      [*] = ;
      [*] = ;   var angle : Float = Floor(RandomExt*360);
      [*] = ;   var speed : Float = 0.2;
      [*] = ;
      [*] = ;   DoCreateShard(plSharsdHnd, posx, posy, posz, scale, angle, radius, behangle, speed, pattern, behx, behz, dispx, dispz);
      [*] = ;end;
   struct.end
section.end

