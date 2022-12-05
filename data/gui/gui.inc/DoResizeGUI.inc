section.begin
   Name = DoResizeGUI
   Code : struct.begin
      [*] = ;Log('DoResizeGUI');
      [*] = ;
      [*] = ;StringRegister0 := '';
      [*] = ;MapExecuteState('ResizeCamera');
      [*] = ;
      [*] = ;// these cause errors when quitting the game or sometimes white screen when visual overload.
      [*] = ;//if gIntRegister_CurGameMode = gc_GameModeStrategy then ExecuteState('map.DoResizeGUI');
      [*] = ;//if gIntRegister_CurGameMode = gc_GameModeTactics then ExecuteState('battle.DoResizeGUI');
      [*] = ;//NeedRestartGUI;
      [*] = ;
      [*] = ;_gui_RootWindowInit();
   struct.end
section.end

