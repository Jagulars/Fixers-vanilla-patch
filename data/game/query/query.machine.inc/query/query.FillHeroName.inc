section.begin
   Name = query.FillHeroName
   Description : struct.begin
      [*] = ;Fills gStringRegister_MyHeroName from gIntRegister_MapCurHeroIndex and _gv_GetCurrentPlayer()
   struct.end
   Code : struct.begin
      [*] = ;var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, _gv_GetCurrentPlayerHandle());
      [*] = ;if goHandle <> 0 then
      [*] = ;   _hero_GetName(goHandle, gStringRegister_MyHeroName)
      [*] = ;else
      [*] = ;   gStringRegister_MyHeroName := '????';
   struct.end
section.end
