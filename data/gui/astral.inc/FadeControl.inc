section.begin
   Name = FadeControl
   UsedFileName =
   Code : struct.begin
      [*] = ;var guiDoAttackShardTimer : Float = GetFloatValueByName('guiDoAttackShardTimer');
      [*] = ;var guiDoRunMainMenu : Float = GetFloatValueByName('guiDoRunMainMenu');
      [*] = ;var guiDoRunSurrenderTimer : Float = GetFloatValueByName('guiDoRunSurrenderTimer');
      [*] = ;var guiDoRunExitGame : Float = GetFloatValueByName('guiDoRunExitGame');
      [*] = ;const cFadeTime = 0.65;
      [*] = ;if (guiDoRunMainMenu>0) and (guiDoRunMainMenu+cFadeTime<GetGameTime()) then
      [*] = ;   _run_DoCreateMenu;
      [*] = ;if (guiDoRunSurrenderTimer>0) and (guiDoRunSurrenderTimer+cFadeTime<GetGameTime()) then
      [*] = ;   _run_DoCreateMenu;
      [*] = ;if (guiDoRunExitGame>0) and (guiDoRunExitGame+cFadeTime<GetGameTime()) then
      [*] = ;   _run_ExitGame();
   struct.end
section.end
