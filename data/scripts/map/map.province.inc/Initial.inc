section.begin
   Name = Initial
   Code : struct.begin
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;
      [*] = ;GameObjectMakeUniqId(myHandle);
      [*] = ;
      [*] = ;SetIntValueByName('prov', 0); // gc_map_GOStack_Province_iParserHandle - province parser handle
      [*] = ;//SetIntValueByName('upd', 0);  // gc_map_GOStack_Province_iUpdate - update province hud - NOT USED ANYMORE!!
      [*] = ;                              // use _map_RefreshProvinceHUD(dummyUID) instead
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
