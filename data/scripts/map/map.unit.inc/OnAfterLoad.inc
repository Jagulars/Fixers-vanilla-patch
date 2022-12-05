section.begin
   Name = OnAfterLoad
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\ONAFTERLOAD';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;
      [*] = ;Log(_log_name+'['+GetGameObjectMyBaseName()+', UID: '+IntToStr(GetGameObjectUniqueIdByHandle(myGOHandle))+']');
      [*] = ;//_gv_traceState(_log_name+'['+GetGameObjectMyBaseName()+', UID: '+IntToStr(GetGameObjectUniqueIdByHandle(myGOHandle))+']',_log_trace);
      [*] = ;
      [*] = ;
      [*] = ;procedure CheckParser(root_p : Integer; key : String);
      [*] = ;begin
      [*] = ;   if ParserSelectByHandleByKey(root_p,key) = 0 then
      [*] = ;      ParserAddChildByIndex(root_p, key);
      [*] = ;end;
      [*] = ;
      [*] = ;var i, chp, pMyUnit : Integer;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyUnits : Integer = ParserSelectByHandleByKey(pMyParser, 'Units');
      [*] = ;
      [*] = ;const objectType = 'ShardHero';
      [*] = ;_obj_UpdateStackVariables(myGOHandle, objectType);
      [*] = ;
      [*] = ;chp := GetIntValueByIndex(gc_map_GOStack_MapUnit_iCurHP);
      [*] = ;for i := ParserGetCountByHandle(pMyUnits)-1 downto 0 do
      [*] = ;begin
      [*] = ;   pMyUnit := ParserSelectByHandleByIndex(pMyUnits, i);
      [*] = ;   if not ParserIsValueExistsByKeyByHandle(pMyUnit,'FCurLife') then
      [*] = ;      ParserSetFloatValueByKeyByHandle(pMyUnit, 'FCurLife', ParserGetIntValueByKeyByHandle(pMyUnit, 'CurLife'));
      [*] = ;   if ParserGetBoolValueByKeyByHandle(pMyUnit, 'IsHero') then
      [*] = ;   begin
      [*] = ;      if ParserGetIntValueByKeyByHandle(pMyUnit,'CurLife') <> chp then
      [*] = ;      begin
      [*] = ;         ErrorLogI(_log_name+' Hero life in army differs from his object value. ['+IntToStr(ParserGetIntValueByKeyByHandle(pMyUnit,'CurLife'))+'!='+IntToStr(chp)+']');
      [*] = ;         ParserSetIntValueByKeyByHandle(pMyUnit, 'CurLife',chp);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pMyUnit, 'FCurLife', chp);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;CheckParser(pMyParser,'Quests');
      [*] = ;CheckParser(pMyParser,'SiteLootItems');
      [*] = ;CheckParser(pMyParser,'LeftLootItems');
      [*] = ;chp := ParserSelectByHandleByKey(pMyParser, 'LeftLootItems');
      [*] = ;if ParserGetCountByHandle(chp) > 0 then
      [*] = ;begin
      [*] = ;   ErrorLogI(_log_name+'['+GetGameObjectMyBaseName()+'] LeftLootItems number is '+IntToStr(ParserGetCountByHandle(chp)));
      [*] = ;   ParserClearByHandle(chp);
      [*] = ;end;
      [*] = ;CheckParser(pMyParser,'PassableTargets');
      [*] = ;CheckParser(pMyParser,'EnemyPassTargets');
      [*] = ;
      [*] = ;//for i := GetGameObjectVarsCountByHandle(myGOHandle)-1 downto 0 do
      [*] = ;//Log(GetGameObjectKeyNameIndByHandle(myGOHandle, i)+' '+GetGameObjectValueIndByHandle(myGOHandle, i));
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;//_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

