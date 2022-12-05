section.begin
   Name = FadeControl
   UsedFileName =
   Code : struct.begin
      [*] = ;var guiDoRunCampaignTimer : Float = GetFloatValueByName('guiDoRunCampaignTimer');
      [*] = ;var guiDoRunDemoStratTimer : Float = GetFloatValueByName('guiDoRunDemoStratTimer');
      [*] = ;var guiDoRunDemoBattleTimer1 : Float = GetFloatValueByName('guiDoRunDemoBattleTimer1');
      [*] = ;var guiDoRunDemoBattleTimer2 : Float = GetFloatValueByName('guiDoRunDemoBattleTimer2');
      [*] = ;var guiDoRunDemoBattleTimer3 : Float = GetFloatValueByName('guiDoRunDemoBattleTimer3');
      [*] = ;var guiDoRunContinueCampaignTimer : Float = GetFloatValueByName('guiDoRunContinueCampaignTimer');
      [*] = ;var guiDoRunContinueCustomTimer : Float = GetFloatValueByName('guiDoRunContinueCustomTimer');
      [*] = ;var guiDoRunExitGame : Float = GetFloatValueByName('guiDoRunExitGame');
      [*] = ;const cFadeTime = 0.65;
      [*] = ;
      [*] = ;if (guiDoRunCampaignTimer>0) and (guiDoRunCampaignTimer+cFadeTime<GetGameTime) then
      [*] = ;begin
      [*] = ;   ExecuteState('DoCampaign');
      [*] = ;   MapExecuteState('astral.Create');
      [*] = ;end;
      [*] = ;
      [*] = ;if (guiDoRunDemoStratTimer>0) and (guiDoRunDemoStratTimer+cFadeTime<GetGameTime) then
      [*] = ;begin
      [*] = ;   StringRegister0 := '.\data\maps\demo\DemoKey.4224';
      [*] = ;   ExecuteState('DoDemoScenario');
      [*] = ;end;
      [*] = ;
      [*] = ;if (guiDoRunDemoBattleTimer1>0) and (guiDoRunDemoBattleTimer1+cFadeTime<GetGameTime) then
      [*] = ;begin
      [*] = ;   StringRegister0 := '.\data\maps\demo\DemoKey.8994';
      [*] = ;   ExecuteState('DoDemoScenario');
      [*] = ;end;
      [*] = ;if (guiDoRunDemoBattleTimer2>0) and (guiDoRunDemoBattleTimer2+cFadeTime<GetGameTime) then
      [*] = ;begin
      [*] = ;   StringRegister0 := '.\data\maps\demo\DemoKey.1000';
      [*] = ;   ExecuteState('DoDemoScenario');
      [*] = ;end;
      [*] = ;if (guiDoRunDemoBattleTimer3>0) and (guiDoRunDemoBattleTimer3+cFadeTime<GetGameTime) then
      [*] = ;begin
      [*] = ;   StringRegister0 := '.\data\maps\demo\DemoKey.1020';
      [*] = ;   ExecuteState('DoDemoScenario');
      [*] = ;end;
      [*] = ;
      [*] = ;if (guiDoRunContinueCampaignTimer>0) and (guiDoRunContinueCampaignTimer+cFadeTime<GetGameTime) then
      [*] = ;begin
      [*] = ;   SetFloatValueByName('guiDoRunContinueCampaignTimer', 0);
      [*] = ;   _prof_SyncCustomsFolderExt(gc_GameTypeFlagCampaign,0,-1);
      [*] = ;   StringRegister0 := gProfile.lastcampaignsave;
      [*] = ;   MapExecuteState('LoadMap');
      [*] = ;end;
      [*] = ;
      [*] = ;if (guiDoRunContinueCustomTimer>0) and (guiDoRunContinueCustomTimer+cFadeTime<GetGameTime) then
      [*] = ;begin
      [*] = ;   SetFloatValueByName('guiDoRunContinueCustomTimer', 0);
      [*] = ;   _prof_SyncCustomsFolderExt(gc_GameTypeFlagSingle,0,-1);
      [*] = ;   StringRegister0 := gProfile.lastcustomsave;
      [*] = ;   MapExecuteState('LoadMap');
      [*] = ;end;
      [*] = ;
      [*] = ;if (guiDoRunExitGame>0) and (guiDoRunExitGame+0.45<GetGameTime) then
      [*] = ;begin
      [*] = ;   _run_ExitGame();
      [*] = ;end;
   struct.end
section.end

