section.begin
   Name = menu.DoInitial
   UsedFileName =
   Code : struct.begin
      [*] = ;TimeLog('menu.DoInitial start');
      [*] = ;gBoolRegister_GUIStartup := true;
      [*] = ;
      [*] = ;DebugDrawClean('');
      [*] = ;GUIClearDataViewerZones;
      [*] = ;ClearTrackNodeList('');
      [*] = ;
      [*] = ;LoadPatterns(True, True);
      [*] = ;
      [*] = ;gIntRegister_CurGameMode := gc_GameModeMenu;
      [*] = ;
      [*] = ;SetProjectOptionAsString('HorizonRenderEnabled', 'False');
      [*] = ;SetProjectOptionAsString('SelfShadowingTerrain', 'False');
      [*] = ;SetDateTimeManagerEnabled(false);
      [*] = ;SetTimeSpeedFactor(10);
      [*] = ;SetTerrainBordersEnabled(false);
      [*] = ;SetTerrainVisible(false);
      [*] = ;SetTerrainBordersVisible(false);
      [*] = ;SetObjectBasedVisibilityCulling(true);
      [*] = ;SetCameraPropertiesFromFile('.\data\cameras\camera.cfg');
      [*] = ;SetCameraDepthOfView(1000);
      [*] = ;SetLensFlareAngle(35);
      [*] = ;SetLensFlareZOffset(0.3);
      [*] = ;
      [*] = ;SetLightPattern('astral_neutral');
      [*] = ;
      [*] = ;IntRegister0 := _obj_GetCheckSceneryFlags($ff, gProfile.shardscenery, gProfile.townscenery, gProfile.provincescenery, gProfile.battlescenery);
      [*] = ;GUIExecuteState('CheckScenery');
      [*] = ;
      [*] = ;gBoolRegister_GUIProgressOnceOnGUIDoCreate := True;
      [*] = ;//if gProfile.simplegraphics then
      [*] = ;//   _actor_CheckSimplifiedGraphics();
      [*] = ;
      [*] = ;TimeLog('menu.DoInitial end');
   struct.end
section.end
