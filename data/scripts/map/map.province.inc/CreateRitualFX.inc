section.begin
   Name = CreateRitualFX
   Description[*] = ;IntRegister0 - ritual ID
   Code : struct.begin
      [*] = ;var ritualID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var pProvince : Integer = GetIntValueByIndex(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var pRitual : Integer = ParserSelectByHandleByIndex(gPrototypeData.rituals.handle, ritualID);
      [*] = ;var time : Integer = ParserGetIntValueByKeyByHandle(pRitual, 'Time');
      [*] = ;
      [*] = ;var pProvFog : Integer = ParserSelectByHandleByKey(pProvince, 'Fog');
      [*] = ;var fog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;if ((not gGame.fog) or (time > 0) or (fog = 0)) and _obj_EnabledByFlag(gc_ObjectFlagRitual) then
      [*] = ;begin
      [*] = ;   if ((ritualID>=1) and (ritualID<=24)) then
      [*] = ;   begin
      [*] = ;      if (_fx_FindFXHandleByID(myGOHandle, true, 1000+ritualID)=0) then
      [*] = ;      _fx_GetOrCreateFXByID(myGOHandle, 'fxritual_'+IntToStr(ritualID), 0, 0, 0, 0, 0, 1000+ritualID);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (_fx_FindFXHandleByID(myGOHandle, true, 1000)=0) then
      [*] = ;      begin
      [*] = ;         if (ritualID mod 2=0) then
      [*] = ;         _fx_GetOrCreateFXByID(myGOHandle, 'fxritual', 0, 0, 0, 0, 0, 1000)
      [*] = ;         else
      [*] = ;         _fx_GetOrCreateFXByID(myGOHandle, 'fxritual_0', 0, 0, 0, 0, 0, 1000);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gGame.fog and (fog <> 0) then
      [*] = ;_fx_SetVisibleFX(myGOHandle, false, false);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

