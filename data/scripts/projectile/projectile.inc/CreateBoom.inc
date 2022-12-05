section.begin
   Name = CreateBoom
   UsedFileName = 
   Code : struct.begin
      [*] = ;//var myType : Integer = GetGameObjectMyIntValueInd( gc_stack_projectile_iType);
      [*] = ;//var bHandle : Integer;
      [*] = ;var tGOUID : Integer = GetIntValueByIndex(gc_stack_projectile_iTarget);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tGOUID);
      [*] = ;
      [*] = ;function GetEffectParser(const goHandle, parUpgradeID, parSpellID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := parUpgradeID;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetEffectParserByUpgradeID');
      [*] = ;   Result := IntRegister1;
      [*] = ;   if Result=0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := parSpellID;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetEffectParserBySpellID');
      [*] = ;      Result := IntRegister1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure WoundNeighbours(target_h, tx, ty : Integer; friend : Boolean);
      [*] = ;begin
      [*] = ;   var i, pNeighbours, uid, goNeighbourHnd : Integer;
      [*] = ;
      [*] = ;   BoolRegister0 := not friend;
      [*] = ;   IntRegister0 := tx;
      [*] = ;   IntRegister1 := ty;
      [*] = ;   GameObjectExecuteStateByHandle(target_h, 'FindNeighbour');
      [*] = ;   pNeighbours := ParserSelectByHandleByKey(ParserSelectGameObject(target_h), 'Neighbours');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pNeighbours)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      uid := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pNeighbours,i), 'UID');
      [*] = ;      goNeighbourHnd := GetGameObjectHandleByUniqueId(uid);
      [*] = ;      
      [*] = ;      GameObjectExecuteStateByHandle(goNeighbourHnd, 'OnDamage');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (tGOHandle<>0) then
      [*] = ;begin
      [*] = ;   var ownerGOHnd : Integer = GetGameObjectHandleByUniqueId(GetIntValueByIndex(gc_stack_projectile_iOwner));
      [*] = ;   var ownerName : String = '';
      [*] = ;   if (ownerGOHnd<>0) then
      [*] = ;      _unit_PlaySound(ownerGOHnd, 'units', 'hit');
      [*] = ;   
      [*] = ;   if (ownerGOHnd<>0) and _obj_EnabledByFlag(gc_ObjectFlagBattleFX) then
      [*] = ;   begin
      [*] = ;      ownerName := GetGameObjectBaseNameByHandle(ownerGOHnd);
      [*] = ;      
      [*] = ;      var plHandle : Integer = _plr_GetOrCreatePlayer('projectiles', 'misc', 'cmPlayer', false);
      [*] = ;      
      [*] = ;      procedure CreatePFXBloodBoomInPosition(const Handle : Integer; x, y, z, time, vd, exps : Float; expn : Integer);
      [*] = ;      begin
      [*] = ;         const sPfxManager = 'BloodBoomGreen';
      [*] = ;         var sPfxName : String = 'BloodBoomGreen'+'.'+IntToStr(GetEffectCount(handle));
      [*] = ;
      [*] = ;         GameObjectPFXSrcLibCreateByHandle(Handle, sPfxManager, sPfxName);
      [*] = ;         //GameObjectPFXInitialPositionByHandle(Handle, sPfxManager, sPfxName, x, y, z);
      [*] = ;         //GameObjectPFXSetLifeTimeByHandle(Handle, sPfxManager, sPfxName, time);
      [*] = ;         //GameObjectPFXVelocityDispersionByHandle(Handle, sPfxManager, sPfxName, vd);
      [*] = ;         GameObjectPFXMaxExpInitSpeedByHandle(Handle, sPfxManager, sPfxName, exps);
      [*] = ;         //GameObjectPFXExpNumbParticlesByHandle(Handle, sPfxManager, sPfxName, expn);
      [*] = ;         GameObjectPFXSleepTimeByHandle(Handle, sPfxManager, sPfxName, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var endState : String;
      [*] = ;      if gc_RecycleProjectiles then
      [*] = ;         endState := 'Recycle'
      [*] = ;      else
      [*] = ;         endState := 'Destroy';
      [*] = ;        
      [*] = ;      case ownerName of
      [*] = ;         'wizard', 'lich' : begin
      [*] = ;            var goHnd : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHnd, endState, 0.5);
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(goHnd, 'shotvioletball0flash', 'shotvioletball0flash'+'.'+IntToStr(GetEffectCount(goHnd)));
      [*] = ;            GameObjectPFXSetLifeTimeByHandle(goHnd, 'shotvioletball0flash', 'shotvioletball0flash', 0.1);
      [*] = ;         end;
      [*] = ;         'sorcerer' : begin
      [*] = ;            var goHnd : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHnd, endState, 0.5);
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(goHnd, 'shotvioletball0flash_dark', 'shotvioletball0flash_dark'+'.'+IntToStr(GetEffectCount(goHnd)));
      [*] = ;            GameObjectPFXSetLifeTimeByHandle(goHnd, 'shotvioletball0flash_dark', 'shotvioletball0flash_dark', 0.1);
      [*] = ;
      [*] = ;            goHnd := _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHnd, endState, 0.2);
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(goHnd, 'shotshamanflash', 'shotshamanflash'+'.'+IntToStr(GetEffectCount(goHnd)));
      [*] = ;            GameObjectPFXSetLifeTimeByHandle(goHnd, 'shotshamanflash', 'shotshamanflash', 0.01);
      [*] = ;         end;
      [*] = ;         'mage', 'magewhite' : begin
      [*] = ;            var goHnd : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHnd, endState, 0.5);
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(goHnd, 'shotvioletball0flash', 'shotvioletball0flash'+'.'+IntToStr(GetEffectCount(goHnd)));
      [*] = ;            GameObjectPFXSetLifeTimeByHandle(goHnd, 'shotvioletball0flash', 'shotvioletball0flash', 0.1);
      [*] = ;         end;
      [*] = ;         'mageblack' : begin
      [*] = ;            var goHnd : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHnd, endState, 0.5);
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(goHnd, 'shotvioletball0flash_dark', 'shotvioletball0flash_dark'+'.'+IntToStr(GetEffectCount(goHnd)));
      [*] = ;            GameObjectPFXSetLifeTimeByHandle(goHnd, 'shotvioletball0flash_dark', 'shotvioletball0flash_dark', 0.1);
      [*] = ;         end;
      [*] = ;         'shaman', 'lizardmanpriest' : begin
      [*] = ;            var goHnd : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHnd, endState, 0.2);
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(goHnd, 'shotshamanflash', 'shotshamanflash'+'.'+IntToStr(GetEffectCount(goHnd)));
      [*] = ;            GameObjectPFXSetLifeTimeByHandle(goHnd, 'shotshamanflash', 'shotshamanflash', 0.01);
      [*] = ;         end;
      [*] = ;         'slug' : begin
      [*] = ;            var goHnd : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;            GameObjectDelayExecuteStateByHandle(goHnd, endState, 1.0);
      [*] = ;            CreatePFXBloodBoomInPosition(goHnd, 0, 0, 0, 0.35, 0.2, 0.4, 10);
      [*] = ;         end;
      [*] = ;         'spider', 'spiderblackwidow' : begin
      [*] = ;            if (GetEffectParser(tGOHandle, 77, -1)<>0) and (_fx_FindFXHandleByID(tGOHandle, true, 3)=0) then
      [*] = ;               _fx_GetOrCreateFXByID(tGOHandle, 'fxspiderweb', 0, 0, 0, 0, 0, 3);
      [*] = ;         end;
      [*] = ;         'basilisk', 'medusa' : begin
      [*] = ;            if (GetEffectParser(tGOHandle, 76, -1)<>0) and (_fx_FindFXHandleByID(tGOHandle, true, 6)=0) then
      [*] = ;            begin
      [*] = ;               _fx_GetOrCreateFXByID(tGOHandle, 'fxstone', 0, 0, 0, 0, 0, 6);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'devil', 'dragon', 'dragonfire' : begin
      [*] = ;            _fx_CreateFX(tGOHandle, 'fx_impact_burn', 0, 0, 0, 0, 0);
	  [*] = ;            _gui_PlaySound('spells', 'spell23');
      [*] = ;         end;
      [*] = ;         'dragonstorm' : begin
      [*] = ;            _fx_CreateFX(tGOHandle, 'fx_lightning', 0, 0, 0, 0, 0);
      [*] = ;            _gui_PlaySound('spells', 'spell22');
      [*] = ;         end;
      [*] = ;         'dragonunholy' : begin
      [*] = ;            _fx_CreateFX(tGOHandle, 'fx_disease', 0, 0, 0, 0, 0);
      [*] = ;            _fx_CreateFX(tGOHandle, 'fx_impact_burn', 0, 0, 0, 0, 0);
      [*] = ;            
	  [*] = ;            _gui_PlaySound('spells', 'spell23');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if _unit_CheckAbility(ownerGOHnd, gc_ability_fire_ammo) > 0 then
      [*] = ;      begin
      [*] = ;         _fx_CreateFX(tGOHandle, 'fx_blast_shot', 0, 0, 0, 0, 0);
      [*] = ;         //_unit_PlaySound('spells','spell4');
      [*] = ;         
      [*] = ;         var tGridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;         var tGridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;         WoundNeighbours(tGOHandle, tGridX, tGridY, true);
      [*] = ;         WoundNeighbours(tGOHandle, tGridX, tGridY, false);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // poison
      [*] = ;      if GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife) > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 1;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectDurationByAbility');
      [*] = ;         var dur : Integer = IntRegister1;
      [*] = ;         var poison : Integer = _unit_CheckAbility(ownerGOHnd, 78);
      [*] = ;         if (dur > 0) and (poison > 0) then
      [*] = ;         _fx_GetOrCreateFXByID(tGOHandle, 'fxpoisonattack', 0, 0, 0, 0, 0, 5);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (ownerName <> 'spider') and (ownerName <> 'spiderblackwidow') and (ownerName <> 'basilisk') and (ownerName <> 'medusa') then
      [*] = ;   begin
      [*] = ;      if (ownerName <> 'slug') then
      [*] = ;      begin
      [*] = ;         IntRegister1 := 0;
      [*] = ;         FloatRegister0 := 0;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'BloodBoom');
      [*] = ;      end;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'OnDamage');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

