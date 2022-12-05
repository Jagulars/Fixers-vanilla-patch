section.begin
   Name = EventMenu
   UsedFileName =
   Code : struct.begin
      [*] = ;const cBtnContinue = 16 + $20000;
      [*] = ;const cBtnSettings = 6 + $20000;
      [*] = ;const cBtnDifficulty = 104 + $20000;
      [*] = ;const cBtnSaveGame = 54 + $20000;
      [*] = ;const cBtnLoadGame = 39 + $20000;
      [*] = ;const cBtnExit = 18 + $20000;
      [*] = ;const cBtnAchievements = 9+$20000;
      [*] = ;
      [*] = ;const cBtnContinue_S = 30 + $20000;
      [*] = ;const cBtnSurrender = 20 + $20000;
      [*] = ;const cBtnExitToMainMenu = 107 + $20000;
      [*] = ;const cBtnExitToDesktop = 108 + $20000;
      [*] = ;
      [*] = ;const cDifficultyBaseTagMin = 117 + $20000;
      [*] = ;const cDifficultyBaseTagMax = 117 + 6 + $20000;
      [*] = ;const cBtnContinue_D = 110 + $20000;
      [*] = ;const cBtnGenesisMode = 238 + $20000;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      cBtnContinue : _cmd_Post('menumainbutton','continue','');
      [*] = ;      cBtnSettings : _cmd_Post('menumainbutton','settings','');
      [*] = ;      cBtnAchievements : _cmd_Post('menumainbutton','achievements','');
      [*] = ;      cBtnDifficulty : _cmd_Post('menumainbutton','difficulty','');
      [*] = ;      cBtnSaveGame : _cmd_Post('menumainbutton','save','');
      [*] = ;      cBtnLoadGame : _cmd_Post('menumainbutton','load','');
      [*] = ;      cBtnExit : _cmd_Post('menumainbutton','exit','');
      [*] = ;
      [*] = ;      cBtnExitToMainMenu : _cmd_Post('menuexitbutton','tomain','');
      [*] = ;      cBtnExitToDesktop: _cmd_Post('menuexitbutton','todesktop','');
      [*] = ;      cBtnSurrender: _cmd_Post('menuexitbutton','surrender','');
      [*] = ;      cBtnContinue_S : _cmd_Post('menuexitbutton','continue','');
      [*] = ;
      [*] = ;      cBtnContinue_D : _cmd_Post('menudifficultybutton','continue','');
      [*] = ;      cBtnGenesisMode : _cmd_Post('menumainbutton','genesismode','');
      [*] = ;      else begin
      [*] = ;         if (tag>=cDifficultyBaseTagMin) and (tag<=cDifficultyBaseTagMax) then
      [*] = ;            _cmd_Post('menudifficultybutton',IntToStr(tag-cDifficultyBaseTagMin+1),'');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

