section.begin
   Name = AddLife
   Description : struct.begin
      [*] = ;IntRegister0 - add life value
   struct.end
   Code : struct.begin
      [*] = ;var lifeAdd : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\ADDLIFE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyUnits : Integer = ParserSelectByHandleByKey(myParser, 'Units');
      [*] = ;var pMyUnit0 : Integer = ParserSelectByHandleByIndex(pMyUnits, 0);
      [*] = ;
      [*] = ;IntRegister0 := gc_map_hero_iLife;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;var curLife : Integer = ParserGetIntValueByKeyByHandle(pMyUnit0, 'CurLife');
      [*] = ;curLife := Round(Clamp(curLife + lifeAdd, 1, maxLife));
      [*] = ;ParserSetIntValueByKeyByHandle(pMyUnit0, 'CurLife', curLife);
      [*] = ;ParserSetFloatValueByKeyByHandle(pMyUnit0, 'FCurLife', curLife);
      [*] = ;SetIntValueByIndex(gc_map_GOStack_MapUnit_iCurHP, curLife);
      [*] = ;
      [*] = ;var fCurToMax : Float = curLife / maxLife;
      [*] = ;SetFloatValueByIndex(gc_map_GOStack_MapUnit_fCurToMaxLife, fCurToMax);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

