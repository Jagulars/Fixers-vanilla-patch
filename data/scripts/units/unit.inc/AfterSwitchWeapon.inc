section.begin
   Name = AfterSwitchWeapon
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\AFTERSWITCHWEAPON';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;ExecuteState('CalcAbilities');
      [*] = ;if not gBoolRegister_BattlePlaceMode then
      [*] = ;   ExecuteState('ActionDone');
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myHandle);
      [*] = ;
      [*] = ;var mapHeroUID : Integer = GetIntValueByIndex(gc_stack_unit_iHeroUID);
      [*] = ;var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(mapHeroUID);
      [*] = ;var mapHeroParser : Integer = ParserSelectGameObject(mapHeroHandle);
      [*] = ;var pHeroDoll : Integer = ParserSelectByHandleByKey(mapHeroParser, 'Doll');
      [*] = ;
      [*] = ;if gBoolRegister_BattlePlaceMode then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxAmmo;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCurAmmo, IntRegister1);
      [*] = ;   gBoolRegister_BrokenWeapon := false;
      [*] = ;end;
      [*] = ;
      [*] = ;_inet_CreateOrderParser(myUID, -1, -1, gc_inet_actiontype_changeweapon, 0, 0, 0, pHeroDoll, lanOrderRandKey0, lanOrderRandKey1, 'AfterSwitchWeapon');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

