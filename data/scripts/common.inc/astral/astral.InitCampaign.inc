section.begin
   Name = astral.InitCampaign
   Code : struct.begin
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;_camp_CampaignClear();
      [*] = ;_camp_tutorial_Init();
      [*] = ;
      [*] = ;for i := 0 to gc_MaxTutorialHistory-1 do
      [*] = ;   gArrTutorialHistory[i] := 0;
      [*] = ;
      [*] = ;ExecuteState('ResetButtonsBlink');
      [*] = ;
      [*] = ;gMapSettings.genesismode := gProfile.genesismode;
      [*] = ;gGame.gameType := gc_GameTypeCampaign;
   struct.end
section.end

