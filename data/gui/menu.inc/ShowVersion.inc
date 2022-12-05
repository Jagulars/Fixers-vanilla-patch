section.begin
   Name = ShowVersion
   Code : struct.begin
      [*] = ;var font, gameVersion : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu, 'Text', gc_gui_fontsize_smallest, '', font);
      [*] = ;var w, h : Integer;
      [*] = ;_misc_GetBuildVersionExt(gameVersion);
      [*] = ;gameVersion := StrReplace(gameVersion, '_', ' ');
      [*] = ;GetGUIElementFontTextRect(font, gameVersion, w, h);
      [*] = ;_gui_CreateTextShadow('buildversion', _gui_GetLayerI, gameVersion, 'halRightWidth', 'valBottomHeight', -4, -1, w, h, 'halRight', 'valMiddle', font, 0.75, 0.75, 0.75, 0.75, 0, 0, 1, 1, False, 0, 0, 0, 0.75);
   struct.end
section.end

