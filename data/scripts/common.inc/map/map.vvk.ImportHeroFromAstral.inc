section.begin
   Name = map.vvk.ImportHeroFromAstral
   Description : struct.begin
      [*] = ;Imports saved hero from astral if any
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\MAP\MAP.VVK.IMPORTHEROFROMASTRAL';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if gCampMapHero.units_no <> 0 then
      [*] = ;begin
      [*] = ;   var ph,h : Integer;
      [*] = ;
      [*] = ;   ph := GetPlayerHandleByName('Player.0');
      [*] = ;
      [*] = ;   IntRegister0 := -1*gCampMapHero.hero_class;
      [*] = ;   IntRegister1 := -1;
      [*] = ;   IntRegister2 := 0;
      [*] = ;   StringRegister0 := '';
      [*] = ;   BoolRegister0 := false;
      [*] = ;   PlayerExecuteStateByHandle(ph, 'RecruitHero');
      [*] = ;   h := IntRegister1;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   IntRegister1 := h;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   MapExecuteState('GetHeroImportData');
      [*] = ;   GameObjectExecuteStateByHandle(h,'vvk.ArrangeBattleUnits');
      [*] = ;   _misc_ParserGetOrCreateByKey('astral_hero',true);
      [*] = ;   gCampMapHero.units_no := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
