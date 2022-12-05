section.begin
   Name = map.ChangeArmyLife
   Description : struct.begin
      [*] = ;IntRegister0 - army parser handle
      [*] = ;IntRegister1 - power
      [*] = ;IntRegister2 - param1
      [*] = ;IntRegister3 - param2
   struct.end
   Code : struct.begin
      [*] = ;var pArmyUnits : Integer = IntRegister0;
      [*] = ;var power : Integer = IntRegister1;
      [*] = ;var iType : Integer = IntRegister2;
      [*] = ;var iTargets : Integer = IntRegister3;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\MAP\MAP.CHANGEARMYLIFE';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var heal : Integer = power;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pArmyUnits)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pArmyUnit : Integer = ParserSelectByHandleByIndex(pArmyUnits, i);
      [*] = ;   var unitID : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'UnitID');
      [*] = ;   var curLife : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'CurLife');
      [*] = ;
      [*] = ;   IntRegister0 := pArmyUnit;
      [*] = ;   IntRegister1 := pArmyUnits;
      [*] = ;   IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;   ExecuteState('GetUnitPropertyByParser');
      [*] = ;   var maxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;   var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;   var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;   if (curLife > 0) and ((iTargets = 0) or ((unitType <> 2) and (unitType <> 4))) then
      [*] = ;   begin
      [*] = ;      var hit : Integer;
      [*] = ;
      [*] = ;      if iType = 0 then
      [*] = ;         hit := power
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if power > 0 then
      [*] = ;            hit := Floor(power * maxLife / 100 + 1)
      [*] = ;         else
      [*] = ;            hit := Floor(power * curLife / 100 - 1);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if hit < 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pArmyUnit;
      [*] = ;         IntRegister1 := pArmyUnits;
      [*] = ;         IntRegister2 := gc_battle_unit_iResist;
      [*] = ;         ExecuteState('GetUnitPropertyByParser');
      [*] = ;         var resist : Integer = IntRegister3;
      [*] = ;
      [*] = ;         hit := hit + resist;
      [*] = ;         if hit > 0 then
      [*] = ;            hit := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      curLife := curLife + hit;
      [*] = ;      curLife := Round(Clamp(curLife, 1, maxLife));
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pArmyUnit, 'CurLife', curLife);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pArmyUnit, 'FCurLife', curLife);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pArmyUnit, 'LifeRatio', curLife / maxLife);
      [*] = ;
      [*] = ;      // special case if unit is a hero
      [*] = ;      if ParserGetBoolValueByKeyByHandle(pArmyUnit, 'IsHero') then
      [*] = ;      begin
      [*] = ;         var maphero_handle : Integer;
      [*] = ;         var fCurToMax : Float;
      [*] = ;
      [*] = ;         maphero_handle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pArmyUnit, 'HeroUID'));
      [*] = ;         if maphero_handle <> 0 then
      [*] = ;         begin
      [*] = ;            SetGameObjectIntValueIndByHandle(maphero_handle,gc_map_GOStack_MapUnit_iCurHP,curLife);
      [*] = ;
      [*] = ;            IntRegister0 := gc_map_hero_iLife;
      [*] = ;            GameObjectExecuteStateByHandle(maphero_handle, 'GetProperty');
      [*] = ;            fCurToMax := curLife / IntRegister1;
      [*] = ;            SetGameObjectFloatValueIndByHandle(maphero_handle,gc_map_GOStack_MapUnit_fCurToMaxLife,fCurToMax);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
