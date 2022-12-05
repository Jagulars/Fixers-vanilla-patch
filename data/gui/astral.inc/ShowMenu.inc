section.begin
   Name = ShowMenu
   UsedFileName =
   Code : struct.begin
      [*] = ;StringRegister0 := 'astral_menu';
      [*] = ;StringRegister1 := 'EventMenu';
      [*] = ;StringRegister2 := 'VVK.MainMenuCommands';
      [*] = ;StringRegister3 := '#menumainbutton|continue|difficulty|genesismode|save|load|settings|achievements|exit';
      [*] = ;IntRegister0 := cRootWindowModal;
      [*] = ;ExecuteState('ShowListMenu');
   struct.end
section.end

