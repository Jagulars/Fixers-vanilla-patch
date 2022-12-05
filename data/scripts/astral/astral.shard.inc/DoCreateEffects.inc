section.begin
   Name = DoCreateEffects
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
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
      [*] = ;var j : Integer;
      [*] = ;var effHnd : Integer;
      [*] = ;var atmScale, satSpawnRadMod, cloudSpawnRadMin, cloudSpawnRadMax, cloudHeightMin, cloudHeightMax, cloudScaleMod : Float;
      [*] = ;var satCount, cloudCount : Integer;
      [*] = ;var traceXOffset, traceZOffset, traceScale : Float = 1;
      [*] = ;var atmHeight : Float = 0;
      [*] = ;case GetGameObjectMyBaseName of
      [*] = ;   'shard1' : begin
      [*] = ;      atmScale := 200;
      [*] = ;      cloudCount := 6;
      [*] = ;      cloudSpawnRadMin := 28;
      [*] = ;      cloudSpawnRadMax := 60;
      [*] = ;      cloudHeightMin := 15;
      [*] = ;      cloudHeightMax := 32.5;
      [*] = ;      cloudScaleMod := 2;
      [*] = ;      satCount := 5;
      [*] = ;      satSpawnRadMod := 0.8;
      [*] = ;      traceXOffset := 0;
      [*] = ;      traceZOffset := 0;
      [*] = ;      traceScale := 400;
      [*] = ;   end;
      [*] = ;   'shard2' : begin
      [*] = ;      atmScale := 205;
      [*] = ;      atmHeight := 0;
      [*] = ;      cloudCount := 5;
      [*] = ;      cloudSpawnRadMin := 40;
      [*] = ;      cloudSpawnRadMax := 65;
      [*] = ;      cloudHeightMin := 15;
      [*] = ;      cloudHeightMax := 26;
      [*] = ;      cloudScaleMod := 2.0;
      [*] = ;      satCount := 5;
      [*] = ;      satSpawnRadMod := 0.9;
      [*] = ;      traceXOffset := 0;
      [*] = ;      traceZOffset := 0;
      [*] = ;      traceScale := 410;
      [*] = ;   end;
      [*] = ;   'shard4' : begin
      [*] = ;      atmScale := 200;
      [*] = ;      atmHeight := 15;
      [*] = ;      cloudCount := 4;
      [*] = ;      cloudSpawnRadMin := 25;
      [*] = ;      cloudSpawnRadMax := 45;
      [*] = ;      cloudHeightMin := 25;
      [*] = ;      cloudHeightMax := 30;
      [*] = ;      cloudScaleMod := 1.7;
      [*] = ;      satCount := 5;
      [*] = ;      satSpawnRadMod := 0.9;
      [*] = ;      traceXOffset := 0;
      [*] = ;      traceZOffset := 0;
      [*] = ;      traceScale := 410;
      [*] = ;   end;
      [*] = ;   'shard3' : begin
      [*] = ;      atmScale := 200;
      [*] = ;      atmHeight := 8;
      [*] = ;      cloudCount := 4;
      [*] = ;      cloudSpawnRadMin := 30;
      [*] = ;      cloudSpawnRadMax := 45;
      [*] = ;      cloudHeightMin := 20;
      [*] = ;      cloudHeightMax := 26;
      [*] = ;      cloudScaleMod := 1.65;
      [*] = ;      satCount := 5;
      [*] = ;      satSpawnRadMod := 0.9;
      [*] = ;      traceXOffset := 0;
      [*] = ;      traceZOffset := 0;
      [*] = ;      traceScale := 350;
      [*] = ;   end;
      [*] = ;   'shard7' : begin
      [*] = ;      atmScale := 145;
      [*] = ;      cloudCount := 3;
      [*] = ;      cloudSpawnRadMin := 30;
      [*] = ;      cloudSpawnRadMax := 42;
      [*] = ;      cloudHeightMin := 19;
      [*] = ;      cloudHeightMax := 19;
      [*] = ;      cloudScaleMod := 1.4;
      [*] = ;      satCount := 6;
      [*] = ;      satSpawnRadMod := 0.9;
      [*] = ;      traceXOffset := 0;
      [*] = ;      traceZOffset := 0;
      [*] = ;      traceScale := 350;
      [*] = ;   end;
      [*] = ;   'shard8' : begin
      [*] = ;      atmScale := 145;
      [*] = ;      cloudCount := 3;
      [*] = ;      cloudSpawnRadMin := 30;
      [*] = ;      cloudSpawnRadMax := 38;
      [*] = ;      cloudHeightMin := 18;
      [*] = ;      cloudHeightMax := 22;
      [*] = ;      cloudScaleMod := 1.4;
      [*] = ;      satCount := 6;
      [*] = ;      satSpawnRadMod := 0.9;
      [*] = ;      traceXOffset := 0;
      [*] = ;      traceZOffset := 0;
      [*] = ;      traceScale := 350;
      [*] = ;   end;
      [*] = ;   'shard5' : begin
      [*] = ;      atmScale := 95;
      [*] = ;      atmHeight := 15;
      [*] = ;      cloudCount := 3;
      [*] = ;      cloudSpawnRadMin := 5;
      [*] = ;      cloudSpawnRadMax := 20;
      [*] = ;      cloudHeightMin := 28;
      [*] = ;      cloudHeightMax := 28;
      [*] = ;      cloudScaleMod := 1.15;
      [*] = ;      satCount := 5;
      [*] = ;      satSpawnRadMod := 0.8;
      [*] = ;      traceXOffset := 0;
      [*] = ;      traceZOffset := 0;
      [*] = ;      traceScale := 225;
      [*] = ;   end;
      [*] = ;   'shard6' : begin
      [*] = ;      atmScale := 100;
      [*] = ;      atmHeight := 15;
      [*] = ;      cloudCount := 3;
      [*] = ;      cloudSpawnRadMin := 5;
      [*] = ;      cloudSpawnRadMax := 20;
      [*] = ;      cloudHeightMin := 28;
      [*] = ;      cloudHeightMax := 28;
      [*] = ;      cloudScaleMod := 1.2;
      [*] = ;      satCount := 5;
      [*] = ;      satSpawnRadMod := 0.9;
      [*] = ;      traceXOffset := 0;
      [*] = ;      traceZOffset := 0;
      [*] = ;      traceScale := 225;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for j:=0 to cloudCount-1 do
      [*] = ;begin
      [*] = ;   var i : Integer = GetEffectCount(myGOHandle)+1;
      [*] = ;   GameObjectPFXSrcLibCreateByHandle(myGOHandle, 'defsprite', 'cloud'+IntToStr(i));
      [*] = ;   effHnd := GetEffectByKey(myGOHandle, 'cloud'+IntToStr(i));
      [*] = ;   var posX, posY, posZ : Float;
      [*] = ;   var dirX, dirY, dirZ : Float;
      [*] = ;   var scale : Float = Lerp(17, 31, Random)*cloudScaleMod;
      [*] = ;   var hRand : Float = Random;
      [*] = ;   posZ := Lerp(cloudHeightMax*1.45, cloudHeightMin, hRand+(0.5-Random)*0.15);
      [*] = ;
      [*] = ;   dirX := Lerp(cloudSpawnRadMin, cloudSpawnRadMax, hRand);
      [*] = ;   dirY := 0;
      [*] = ;   dirZ := 0;
      [*] = ;   VectorRotateY(dirX, dirY, dirZ, Random*360);
      [*] = ;
      [*] = ;   SetBehaviourAffineVectorProperty(effHnd, 'Position', posX+dirX, posY+dirZ, posZ);
      [*] = ;   DoSpawnCloudSatellites(myGOHandle, posX+dirX, posY+dirZ, posZ, satCount, satSpawnRadMod, cloudScaleMod);
      [*] = ;   SetBehaviourAffineVectorProperty(effHnd, 'Scale', scale, scale, scale);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'AlphaChannel', Lerp(0.4, 0.7, Random));
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'MirrorV', False);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'Width', 1);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'Height', 0.5);
      [*] = ;end;
      [*] = ;
      [*] = ;//fx_round
      [*] = ;//fx_aura
      [*] = ;//fx_round_white
      [*] = ;GameObjectPFXSrcLibCreateByHandle(myGOHandle, 'defsprite', 'atmosphere');
      [*] = ;effHnd := GetEffectByKey(myGOHandle, 'atmosphere');
      [*] = ;SetBehaviourStringProperty(effHnd, 'LibMaterialName', 'astralatmosphere');
      [*] = ;SetBehaviourBoolProperty(effHnd, 'MirrorV', False);
      [*] = ;var posX, posY, posZ : Float = 0;
      [*] = ;var dirX, dirY, dirZ : Float = 0;
      [*] = ;SetBehaviourAffineVectorProperty(effHnd, 'Position', posX, posY, posZ+atmHeight);
      [*] = ;atmScale := atmScale*0.93;
      [*] = ;SetBehaviourAffineVectorProperty(effHnd, 'Scale', atmScale, atmScale, atmScale);
      [*] = ;SetBehaviourVectorProperty(effHnd, 'LifeColor', 0.8, 0.9, 1.0, 1);
      [*] = ;SetBehaviourFloatProperty(effHnd, 'AlphaChannel', 0.725);
      [*] = ;SetBehaviourBoolProperty(effHnd, 'NoZTest', True);
      [*] = ;SetBehaviourBoolProperty(effHnd, 'NoZWrite', True);
      [*] = ;SetBehaviourFloatProperty(effHnd, 'Width', 1);
      [*] = ;SetBehaviourFloatProperty(effHnd, 'Height', 1);
      [*] = ;
      [*] = ;if not gProfile.simplegraphics then // causes flickering with imposters
      [*] = ;begin
      [*] = ;   GameObjectPFXSrcLibCreateByHandle(myGOHandle, 'defsprite', 'trace');
      [*] = ;   effHnd := GetEffectByKey(myGOHandle, 'trace');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'LibMaterialName', 'astralshadow');
      [*] = ;   //SetBehaviourBoolProperty(effHnd, 'MirrorV', False);
      [*] = ;   SetBehaviourAffineVectorProperty(effHnd, 'Position', posX, posY, posZ);
      [*] = ;   SetBehaviourAffineVectorProperty(effHnd, 'Scale', traceScale, traceScale, traceScale);
      [*] = ;   SetBehaviourVectorProperty(effHnd, 'LifeColor', 1.0, 1.0, 1.0, 1);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'AlphaChannel', 0.55);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'Rotation', 210);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'NoZTest', False);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'NoZWrite', True);
      [*] = ;   var width : Float = 0.45;
      [*] = ;   var height : Float = 3;
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'Width', width);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'Height', height);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'MirrorV', True);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'MirrorU', True);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
