section.begin
   Name = CheckFreeze
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var pParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;pParser := ParserSelectByHandleByKey(pParser, 'Effects');
      [*] = ;
      [*] = ;var i, pEffect : Integer;
      [*] = ;for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;begin
      [*] = ;   pEffect := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;   if ParserGetIntValueByKeyByHandle(pEffect, 'ParentSpellID') = gc_spell_word_of_ice then
      [*] = ;   begin
      [*] = ;      _fx_CreateFX(myGOHandle, 'fx_freeze', 0, 0, 0, 0, 0);
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

