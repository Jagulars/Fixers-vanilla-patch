section.begin
   Name = ResetProvinceHint
   Code : struct.begin
      [*] = ;var elmProvDefenderTooltip : Integer = _gui_GetWindow('prov_defender_tooltip');
      [*] = ;if elmProvDefenderTooltip <> 0 then
      [*] = ;begin
      [*] = ;   if gc_RecycleGUI then
      [*] = ;      _gui_Show(elmProvDefenderTooltip,false)
      [*] = ;   else
      [*] = ;      _gui_RootWindowRemoveWithFade(elmProvDefenderTooltip,0);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmMapTooltip : Integer = _gui_GetWindow('map_tooltip');
      [*] = ;if elmMapTooltip <> 0 then
      [*] = ;begin
      [*] = ;   if gc_RecycleGUI then
      [*] = ;      _gui_Show(elmMapTooltip,false)
      [*] = ;   else
      [*] = ;      _gui_RootWindowRemoveWithFade(elmMapTooltip,0);
      [*] = ;end;
   struct.end
section.end

