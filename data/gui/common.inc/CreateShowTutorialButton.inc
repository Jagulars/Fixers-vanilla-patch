section.begin
   Name = CreateShowTutorialButton
   Code : struct.begin
      [*] = ;if ((gTutorial.map) or (gIntRegister_CurGameMode=gc_GameModeAstral)) and (gProfile.mestutor) and (gArrTutorialHistory[0]<>0) then
      [*] = ;begin
      [*] = ;   const cEventState = 'EventTutorial';
      [*] = ;   const cBtnShowTutorial = 200;
      [*] = ;   
      [*] = ;   var xPos : Integer = 24;
      [*] = ;   var yPos : Integer = 96;
      [*] = ;   if (gIntRegister_CurGameMode <> gc_GameModeStrategy) then
      [*] = ;   begin
      [*] = ;      xPos := 32;
      [*] = ;      yPos := 32;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var elmHandle : Integer = _gui_GetOrCreateElementExtAsImage('showtutorialbtn', _gui_GetLayer(cTutorialLayer), 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateButton('showtutorialbtn', elmHandle, '', 'tempshell.journal', 'halParentLeft', 'valParentTop', xPos, yPos, 0, 0, cEventState, 'gui|737', cBtnShowTutorial);
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.9);
      [*] = ;end;
   struct.end
section.end

