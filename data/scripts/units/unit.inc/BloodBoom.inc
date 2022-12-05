section.begin
   Name = BloodBoom
   Description : struct.begin
      [*] = ;IntRegister0 - attacker UID
      [*] = ;FloatRegister0 - delay time
   struct.end
   Code : struct.begin
      [*] = ;if not _obj_EnabledByFlag(gc_ObjectFlagBattleFX) then
      [*] = ;begin
      [*] = ;   SwitchTo('Nothing');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var attGOHandle : Integer = GetGameObjectHandleByUniqueId(IntRegister0);
      [*] = ;var delayTime : Float = FloatRegister0;
      [*] = ;
      [*] = ;procedure CreatePFXBloodBoomInPosition(const Handle : Integer; x, y, z, time, vd, exps : Float; expn : Integer);
      [*] = ;begin
      [*] = ;   const sPfxManager = 'BloodBoom';
      [*] = ;   var sPfxName : String = 'BloodBoom'+'.'+IntToStr(GetEffectCount(Handle));
      [*] = ;   GameObjectPFXSrcLibCreateByHandle(Handle, sPfxManager, sPfxName);
      [*] = ;   GameObjectPFXInitialPositionByHandle(Handle, sPfxManager, sPfxName, x, y, z);
      [*] = ;   GameObjectPFXSetLifeTimeByHandle(Handle, sPfxManager, sPfxName, time);
      [*] = ;   GameObjectPFXVelocityDispersionByHandle(Handle, sPfxManager, sPfxName, vd);
      [*] = ;   GameObjectPFXMaxExpInitSpeedByHandle(Handle, sPfxManager, sPfxName, exps);
      [*] = ;   GameObjectPFXExpNumbParticlesByHandle(Handle, sPfxManager, sPfxName, expn);
      [*] = ;   GameObjectPFXSleepTimeByHandle(Handle, sPfxManager, sPfxName, delayTime);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var x, y, z : Float;
      [*] = ;GetGameObjectAxisAlignedDimensionsByHandle(myHandle, x, y, z);
      [*] = ;
      [*] = ;if GetGameObjectBoolValueIndByHandle(attGOHandle, gc_stack_unit_bFireBreath) then
      [*] = ;   _fx_CreateFX(myHandle, 'fx_impact_burn', 0, 0, 0, 0, delayTime);
      [*] = ;
      [*] = ;{if (_unit_CheckAbility(attGOHandle, gc_ability_disease) > 0) then
      [*] = ;begin
      [*] = ;   _fx_CreateFX(myHandle, 'fx_disease', 0, 0, 0, 0, delayTime);
      [*] = ;end;}
      [*] = ;
      [*] = ;{if (_unit_CheckAbility(attGOHandle, gc_ability_fire_attack) > 0) then
      [*] = ;begin
      [*] = ;   _fx_CreateFX(myHandle, 'fx_fire', 0, 0, 0, 0, delayTime);
      [*] = ;end;}
      [*] = ;
      [*] = ;var baseName : String = GetGameObjectMyBaseName();
      [*] = ;if (baseName <> 'skeleton') and (baseName <> 'daemonice') and (baseName <> 'treeman')  and (baseName <> 'treemanunholy') then // non-mechanical units that should not display blood
      [*] = ;begin
      [*] = ;   var unitID : Integer = GetIntValueByIndex(gc_stack_unit_iUnitID);
      [*] = ;   var unitType : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID), 'UnitType');
      [*] = ;   if unitType <> 4 then
      [*] = ;      CreatePFXBloodBoomInPosition(myHandle, 0, z*0.5, 0, 0.35, 0.2, 0.4, 10);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

