section.begin
   Name = ShowMainMenu
   UsedFileName =
   Code : struct.begin
      [*] = ;StringRegister0 := 'main_menu';
      [*] = ;StringRegister1 := 'EventMenu';
      [*] = ;StringRegister2 := 'VVK.MainMenuCommands';
      [*] = ;StringRegister3 := '#menumainbutton|campaign|demo|custom|multiplayer|profile|settings|credits|editor|tools|exit';
      [*] = ;IntRegister0 := 0;
      [*] = ;GUIExecuteState('ShowListMenu');
   struct.end
section.end

