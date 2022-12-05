section.begin
   Name = Turn
   Description : struct.begin
      [*] = ;IntRegister0 : direction index
   struct.end
   Code : struct.begin
      [*] = ;var dir : Integer = IntRegister0;
      [*] = ;
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var facing : Integer = dir + 3;
      [*] = ;if facing > 5 then
      [*] = ;facing := facing - 6;
      [*] = ;SetIntValueByIndex(gc_stack_unit_iFacing, facing);
      [*] = ;
      [*] = ;var angle, dirX, dirY, dirZ : Float = 0;
      [*] = ;dirX := 1;
      [*] = ;case dir of
      [*] = ;   0 : angle := 0;
      [*] = ;   1 : angle := 60;
      [*] = ;   2 : angle := 120;
      [*] = ;   3 : angle := 180;
      [*] = ;   4 : angle := 240;
      [*] = ;   5 : angle := 300;
      [*] = ;end;
      [*] = ;VectorRotateY(dirX, dirY, dirZ, -angle);
      [*] = ;SetGameObjectMyRotatingTargetCoords(GetGameObjectMyPositionX+dirX, 0, GetGameObjectMyPositionZ+dirZ);
      [*] = ;SetGameObjectMyTrackPointAnimationNames('', '');
      [*] = ;var tpts : Float = ParserGetFloatValueByKeyByHandle(ParserSelectGameObject(myGOHandle), 'TPTurnStep');
      [*] = ;SetGameObjectMyTrackPointTurnStep(tpts{*angle/60}*_misc_CalcBattleSpeedModified(gc_battle_unit_turnspeedmod));
      [*] = ;SetGameObjectMyTargetRotatingMode('trmToTargetCoordinates');
      [*] = ;
      [*] = ;_inet_CreateOrderParser(GetGameObjectUniqueIdByHandle(myGOHandle), dir, -1, gc_inet_actiontype_turn, 0, 0, 0, 0, lanOrderRandKey0, lanOrderRandKey1, 'Turn');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

