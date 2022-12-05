section.begin
   Name = DoInitial
   Description[*] = 
   UsedFileName = 
   Code : struct.begin
      [*] = ;var goMyHnd : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;SetGameObjectUseNoSPCullByHandle(goMyHnd, true);
      [*] = ;
      [*] = ;ClearVariables;
      [*] = ;
      [*] = ;// setup stack
      [*] = ;var initial : Integer = 0;  // default 0 just before initial, 1 is map, 2 is castle
      [*] = ;var provind : Integer = -1; // province index
      [*] = ;
      [*] = ;// stack indices
      [*] = ;// [0 gc_GOStack_fowrainbow_init] - initialized [0..2] : (0 is empty, 1 is map, 2 is castle)
      [*] = ;SetIntValueByName('init', initial);
      [*] = ;// [1 gc_GOStack_fowrainbow_prov] - province index
      [*] = ;SetIntValueByName('prov', provind);
      [*] = ;
      [*] = ;SetGameObjectCustomNameByHandle(goMyHnd, GetGameObjectMyBaseName);
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end
