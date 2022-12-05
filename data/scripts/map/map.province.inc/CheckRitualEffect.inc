section.begin
   Name = CheckRitualEffect
   Description : struct.begin
      [*] = ;IntRegister0 - effect ID (effectID < 0 - check in 'Casted rituals' as well
      [*] = ;OUT: BoolRegister0 - is effect in rituals
      [*] = ;     BoolRegister1 - true if effect is in casted rituals only
      [*] = ;     IntRegister1 - ritual id
      [*] = ;     IntRegister2 - index of ritual in list of province' rituals
   struct.end
   Code : struct.begin
      [*] = ;var effectID : Integer = IntRegister0;
      [*] = ;var _log : Boolean = false;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var pProvRituals : Integer;
      [*] = ;var i,j,k : Integer;
      [*] = ;var isEffect : Boolean = false;
      [*] = ;var r_id : Integer = 0;
      [*] = ;var r_idx : Integer = -1;
      [*] = ;var max_idx : Integer = 0;
      [*] = ;
      [*] = ;if effectID < 0 then
      [*] = ;begin
      [*] = ;   effectID := -1*effectID;
      [*] = ;   max_idx := 1;
      [*] = ;end;
      [*] = ;
      [*] = ;for k := 0 to max_idx do
      [*] = ;begin
      [*] = ;   if k = 0 then pProvRituals := ParserSelectByHandleByKey(pProvince, 'Rituals')
      [*] = ;   else pProvRituals := ParserSelectByHandleByKey(pProvince, 'CastedRituals');
      [*] = ;
      [*] = ;   for [MAIN]i := ParserGetCountByHandle(pProvRituals)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvRitual : Integer = ParserSelectByHandleByIndex(pProvRituals, i);
      [*] = ;
      [*] = ;      r_id := ParserGetIntValueByKeyByHandle(pProvRitual, 'RitualID');
      [*] = ;      IntRegister0 := r_id;
      [*] = ;      MapExecuteState('GetRitualParserByID');
      [*] = ;      var pRitEffects : Integer = ParserSelectByHandleByKey( IntRegister1, 'Effects');
      [*] = ;
      [*] = ;      for j := ParserGetCountByHandle(pRitEffects)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pRitEffect : Integer = ParserSelectByHandleByIndex(pRitEffects, j);
      [*] = ;         var effID : Integer = ParserGetIntValueByKeyByHandle(pRitEffect, 'EffectID');
      [*] = ;
      [*] = ;         if effID = effectID then
      [*] = ;         begin
      [*] = ;            isEffect := true;
      [*] = ;            r_idx := i;
      [*] = ;            break(MAIN);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if isEffect and _log then
      [*] = ;   begin
      [*] = ;      _log_ValuesM('Ritual_Effect_Found|Table|Idx',effectID,k,i,0,0,0);
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := isEffect;
      [*] = ;BoolRegister1 := (k > 0);
      [*] = ;IntRegister1 := r_id;
      [*] = ;IntRegister2 := r_idx;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
