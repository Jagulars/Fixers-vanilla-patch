section.begin
   Name = CheckFreeze
   Description : struct.begin
      [*] = ;BoolRegister0 - is frozen
   struct.end
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;function CheckRituals(pProvRituals : Integer; bCastedRituals : Boolean) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   
      [*] = ;   var i, j, pProvRitual, pRitual, pRitEffects, pRitEffect, effID : Integer;
      [*] = ;            
      [*] = ;   for i := ParserGetCountByHandle(pProvRituals)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pProvRitual := ParserSelectByHandleByIndex(pProvRituals, i);
      [*] = ;
      [*] = ;      IntRegister0 := ParserGetIntValueByKeyByHandle(pProvRitual, 'RitualID');
      [*] = ;      MapExecuteState('GetRitualParserByID');
      [*] = ;      pRitual := IntRegister1;
      [*] = ;      pRitEffects := ParserSelectByHandleByKey(pRitual, 'Effects');
      [*] = ;
      [*] = ;      for j := ParserGetCountByHandle(pRitEffects)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pRitEffect := ParserSelectByHandleByIndex(pRitEffects, j);
      [*] = ;         effID := ParserGetIntValueByKeyByHandle(pRitEffect, 'EffectID');
      [*] = ;
      [*] = ;         if effID = 8 then // freeze effect
      [*] = ;         begin
      [*] = ;            if bCastedRituals or (ParserGetIntValueByKeyByHandle(pProvRitual, 'Length') = 0) then // recent
      [*] = ;            begin
      [*] = ;               Result := True;
      [*] = ;               exit;
      [*] = ;            end;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := GetIntValueByIndex(gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;MapExecuteState('GetProvinceParserByUID');
      [*] = ;var pProvince : Integer = IntRegister1;
      [*] = ;
      [*] = ;BoolRegister0 := CheckRituals(ParserSelectByHandleByKey(pProvince, 'CastedRituals'), true) or CheckRituals(ParserSelectByHandleByKey(pProvince, 'Rituals'), false);
   struct.end
section.end

