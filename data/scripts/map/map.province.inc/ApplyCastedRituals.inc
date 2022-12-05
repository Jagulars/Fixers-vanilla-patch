section.begin
   Name = ApplyCastedRituals
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\APPLYCASTEDRITUALS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;//var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;
      [*] = ;var pCastedRituals : Integer = ParserSelectByHandleByKey(pProvince, 'CastedRituals');
      [*] = ;
      [*] = ;if (ParserGetCountByHandle(pCastedRituals) > 0) then
      [*] = ;begin
      [*] = ;   var i,p : Integer;
      [*] = ;   p := ParserSelectByHandleByIndex(pCastedRituals, 0);
      [*] = ;   i := ParserGetIntValueByKeyByHandle(p, 'RitualID');
      [*] = ;   _gv_traceState(_log_name+'['+IntToStr(i)+']',_log_trace);
      [*] = ;   if (gIntRegister_CurQueryHandle = 0) then
      [*] = ;   begin
      [*] = ;      if (GetPlayerHandleInterfaceIO = GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player'))) then
      [*] = ;         _gui_PlaySound('rituals', 'ritual'+IntToStr(i));
      [*] = ;   
      [*] = ;      var pProvRituals : Integer = ParserSelectByHandleByKey(pProvince, 'Rituals');
      [*] = ;
      [*] = ;      gIntRegister_CurProvinceIndex := GetGameObjectIndexByHandle(GetGameObjectMyHandle());
      [*] = ;
      [*] = ;      IntRegister0 := i;
      [*] = ;      MapExecuteState('GetRitualParserByID');
      [*] = ;      IntRegister0 := ParserGetIntValueByKeyByHandle( IntRegister1, 'Event');
      [*] = ;      ExecuteState('CreateEventByID');
      [*] = ;
      [*] = ;      ParserAddChildByIndex(pProvRituals, '*');
      [*] = ;      ParserCopyFromByHandle(p);
      [*] = ;      ParserFreeByHandle(p);
      [*] = ;   end;
      [*] = ;
      [*] = ;   SwitchTo('ApplyCastedRituals');
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SwitchTo('Nothing');
      [*] = ;end;
      [*] = ;
   struct.end
section.end

