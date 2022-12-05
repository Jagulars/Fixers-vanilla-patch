section.begin
   Name = LoadInfoFromParser
   Description : struct.begin
      [*] = ;IntRegister0 - parser handle
      [*] = ;IntRegister1 - mode
      [*] = ;   0 - full load
      [*] = ;   1 - lan transfer load
   struct.end
   Code : struct.begin
      [*] = ;var mode : Integer = IntRegister1;
      [*] = ;var pInputParser : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;var x : Float = ParserGetFloatValueByKeyByHandle(pInputParser, 'X');
      [*] = ;var z : Float = ParserGetFloatValueByKeyByHandle(pInputParser, 'Z');
      [*] = ;var angle : Float = ParserGetFloatValueByKeyByHandle(pInputParser, 'Angle');
      [*] = ;
      [*] = ;SetGameObjectMyPosition(x, 0, z);
      [*] = ;GameObjectMyDoRayCastTerrain;
      [*] = ;SetGameObjectMyRollAngle(angle);
      [*] = ;
      [*] = ;var pTrackPoints : Integer = ParserSelectByHandleByKey(pInputParser, 'TrackPoints');
      [*] = ;GameObjectMyTrackPointClear;
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to ParserGetCountByHandle(pTrackPoints)-1 do
      [*] = ;begin
      [*] = ;   var pTrackPoint : Integer = ParserSelectByHandleByIndex(pTrackPoints, i);
      [*] = ;   var x : Float = ParserGetFloatValueByKeyByHandle(pTrackPoint, 'X');
      [*] = ;   var y : Float = ParserGetFloatValueByKeyByHandle(pTrackPoint, 'Y');
      [*] = ;   var z : Float = ParserGetFloatValueByKeyByHandle(pTrackPoint, 'Z');
      [*] = ;   GameObjectMyTrackPointAdd(x, y, z);
      [*] = ;end;
      [*] = ;
      [*] = ;var pNewParser : Integer = ParserSelectByHandleByKey(pInputParser, 'Parser');
      [*] = ;if (pNewParser <> 0) and (ParserGetCountByHandle(pNewParser) > 0) then
      [*] = ;   ParserCopyToByHandle(pMyParser);
      [*] = ;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var pMyUnits : Integer = ParserSelectByHandleByKey(pMyParser, 'Units');
      [*] = ;var pMyUnit0 : Integer = ParserSelectByHandleByIndex(pMyUnits, 0);
      [*] = ;ParserSetIntValueByKeyByHandle(pMyUnit0, 'HeroUID', myUID);
      [*] = ;
      [*] = ;var pNewStack : Integer = ParserSelectByHandleByKey(pInputParser, 'Stack');
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pNewStack)-1 do
      [*] = ;begin
      [*] = ;   var value : String = ParserGetValueByIndexByHandle(pNewStack, i);
      [*] = ;   SetValueByIndex(i, value);
      [*] = ;end;
      [*] = ;
      [*] = ;if GetBoolValueByIndex(gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;begin
      [*] = ;   IntRegister0 := myGOHandle;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   BoolRegister1 := true;
      [*] = ;   PlayerExecuteStateByHandle(GetGameObjectPlayerHandleByHandle(myGOHandle), 'KillHero');
      [*] = ;end
      [*] = ;else
      [*] = ;if GetBoolValueByIndex(gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;   SetGameObjectMyVisible(false);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

