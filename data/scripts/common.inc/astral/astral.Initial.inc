section.begin
   Name = astral.Initial
   UsedFileName = 
   Code : struct.begin
      [*] = ;DebugDrawClean('');
      [*] = ;GUIClearDataViewerZones;
      [*] = ;ClearTrackNodeList('');
      [*] = ;
      [*] = ;SetDateTimeManagerEnabled(false);
      [*] = ;SetTimeSpeedFactor(10);
      [*] = ;SetTerrainBordersEnabled(false);
      [*] = ;SetLensFlareAngle(35);
      [*] = ;SetLensFlareZOffset(0.3);
      [*] = ;SetProjectOptionAsString('HorizonRenderEnabled', 'False');
      [*] = ;SetProjectOptionAsString('SelfShadowingTerrain', 'False');
      [*] = ;
      [*] = ;LoadPatterns(True, True);
      [*] = ;
      [*] = ;gIntRegister_CurGameMode := gc_GameModeAstral;
      [*] = ;
      [*] = ;if GetBoolValueByName('LoadAstral') then
      [*] = ;begin
      [*] = ;   ExecuteState('astral.LoadShards');
      [*] = ;   //ExecuteState('astral.BackToCampaign');
      [*] = ;end
      [*] = ;else
      [*] = ;   ExecuteState('astral.NewCampaign');
      [*] = ;
      [*] = ;SetCameraPropertiesFromFile('.\data\cameras\camera.cfg');
      [*] = ;
      [*] = ;SetTerrainVisible(false);
      [*] = ;SetTerrainBordersVisible(false);
      [*] = ;SetObjectBasedVisibilityCulling(true);
      [*] = ;
      [*] = ;SetLightPattern('astral_neutral');
      [*] = ;SetCameraDepthOfView(1000);
      [*] = ;SetLensFlareAngle(35);
      [*] = ;SetLensFlareZOffset(0.3);
      [*] = ;
      [*] = ;IntRegister0 := _obj_GetCheckSceneryFlags($ff, gProfile.shardscenery, gProfile.townscenery, gProfile.provincescenery, gProfile.battlescenery);
      [*] = ;GUIExecuteState('CheckScenery');
      [*] = ;
      [*] = ;gBoolRegister_GUIProgressOnceOnGUIDoCreate := True;
      [*] = ;//if gProfile.simplegraphics then
      [*] = ;//   _actor_CheckSimplifiedGraphics();
      [*] = ;
      [*] = ;SetIntValueByName('astral.init', 1);
   struct.end
section.end

