section.begin
   Name = bat.TowerShoot
   Description : struct.begin
      [*] = ;IntRegister0 - tower parser
      [*] = ;IntRegister1 - target game object handle
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var pTower : Integer = IntRegister0;
      [*] = ;var tGOHandle : Integer = IntRegister1;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.TOWERSHOOT';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var towerType : Integer = ParserGetIntValueByKeyByHandle(pTower, 'Type');
      [*] = ;var hit : Integer = 0;
      [*] = ;
      [*] = ;var randKey1, randKey0 : Integer;
      [*] = ;GetRandomExtKey64(randKey0, randKey1);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Index: '+IntToStr(gIntRegister_BattleCurTowerIndex)+',Type: '+IntToStr(towerType)+',Target: '+GetGameObjectCustomNameByHandle(tGOHandle)+',RandKey0: '+IntToStr(randKey0)+']',_log_trace);
      [*] = ;
      [*] = ;if tGOHandle <> 0 then
      [*] = ;begin
      [*] = ;   var oldLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;   var oldStamina : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;   var oldMoral : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;   var tUID : Integer = GetGameObjectUniqueIdByHandle(tGOHandle);
      [*] = ;
      [*] = ;   var attack : Integer = ParserGetIntValueByKeyByHandle(pTower, 'Attack');
      [*] = ;
      [*] = ;   var defence : Integer = 0;
      [*] = ;   if towerType = 0 then
      [*] = ;   defence := _unit_GetProperty(tGOHandle, gc_battle_unit_iRangedDefence)
      [*] = ;   else
      [*] = ;   defence := _unit_GetProperty(tGOHandle, gc_battle_unit_iResist);
      [*] = ;
      [*] = ;   IntRegister0 := attack;
      [*] = ;   IntRegister1 := defence;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   ExecuteState('bat.GetHit');
      [*] = ;   hit := IntRegister2;
      [*] = ;
      [*] = ;   var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;   if hit > tCurLife then
      [*] = ;      hit := tCurLife;
      [*] = ;
      [*] = ;   IntRegister0 := hit;
      [*] = ;   if towerType = 0 then
      [*] = ;      IntRegister1 := 1
      [*] = ;   else
      [*] = ;      IntRegister1 := 2;
      [*] = ;   IntRegister2 := -1;
      [*] = ;   GameObjectExecuteStateByHandle(tGOHandle, 'TakeDamage');
      [*] = ;   var deathAnimReady : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady) + 1;
      [*] = ;   SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady, deathAnimReady);
      [*] = ;   if _log then _log_gui(GetGameObjectBaseNameByHandle(tGOHandle)+' bat.TowerShoot dar '+IntToStr(GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady)));
      [*] = ;
      [*] = ;   var tIsHero : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;   if tIsHero and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 1;
      [*] = ;      IntRegister1 := tUID;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'DamageArmor');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      // creating projectile
      [*] = ;      var x : Float = ParserGetFloatValueByKeyByHandle(pTower, 'X');
      [*] = ;      var y : Float = ParserGetFloatValueByKeyByHandle(pTower, 'Y');
      [*] = ;      var z : Float = ParserGetFloatValueByKeyByHandle(pTower, 'Z');
      [*] = ;
      [*] = ;      var goX : Float = GetGameObjectPositionXByHandle(tGOHandle);
      [*] = ;      var goY : Float = GetGameObjectPositionYByHandle(tGOHandle);
      [*] = ;      var goZ : Float = GetGameObjectPositionZByHandle(tGOHandle);
      [*] = ;
      [*] = ;      var dirX : Float = x - goX;
      [*] = ;      var dirY : Float = y - goY;
      [*] = ;      var dirZ : Float = z - goZ;
      [*] = ;      VectorNormalize(dirX, dirY, dirZ);
      [*] = ;
      [*] = ;      var plHandle : Integer = _plr_GetOrCreatePlayer('projectiles', 'misc', 'cmPlayer', false);
      [*] = ;      var ptHandle : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', x, y, z);
      [*] = ;      var ptType : Integer = 0;
      [*] = ;
      [*] = ;      case towerType of
      [*] = ;         0 : begin
      [*] = ;            SetGameObjectVisualPropertiesByHandle(ptHandle, 'misc', 'weapon.arrow.archer');
      [*] = ;            ptType := gc_projectile_iTower;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            //baseName := 'sorcererscircle2';
      [*] = ;            ptType := gc_projectile_iMagicTower1;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            //baseName := 'library5';
      [*] = ;            ptType := gc_projectile_iMagicTower2;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            //baseName := 'magetower2';
      [*] = ;            ptType := gc_projectile_iMagicTower3;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            //baseName := 'magictower';
      [*] = ;            ptType := gc_projectile_iMagicTower4;
      [*] = ;         end;
      [*] = ;         5 : begin
      [*] = ;            //baseName := 'bf_magictower'; //must be 'lightningtower', but it is too low quality for large siege size.
      [*] = ;            ptType := gc_projectile_iMagicTower5;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            //baseName := 'bf_magictower';
      [*] = ;            ErrorLogI(_log_name+' Unknown tower projectile type');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ptHandle <> 0 then
      [*] = ;         _gv_SetBattleLock(1,_log_name);
      [*] = ;
      [*] = ;      var ptDirX : Float = -1;
      [*] = ;      var ptDirY : Float = 0;
      [*] = ;      var ptDirZ : Float = 0;
      [*] = ;
      [*] = ;      var angle : Float = VectorAngle(dirX, dirY, dirZ, ptDirX, ptDirY, ptDirZ);
      [*] = ;      VectorCross(dirX, dirY, dirZ, ptDirX, ptDirY, ptDirZ, x, y, z);
      [*] = ;      if y < 0 then
      [*] = ;         angle := -angle;
      [*] = ;
      [*] = ;      GameObjectRollByHandle(ptHandle, angle);
      [*] = ;      SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iOwner, 0);
      [*] = ;      SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iType, ptType);
      [*] = ;      SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iTarget, tUID);
      [*] = ;      SetGameObjectFloatValueIndByHandle(ptHandle, gc_stack_projectile_iTPosX, 0);
      [*] = ;      SetGameObjectFloatValueIndByHandle(ptHandle, gc_stack_projectile_iTPosY, 0);
      [*] = ;      GameObjectExecuteStateByHandle(ptHandle, 'InitialFly');
      [*] = ;
      [*] = ;      _unit_SetupStatsTextData(tGOHandle, 0, oldLife, oldStamina, oldMoral);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;   
      [*] = ;_gv_traceState(_log_name+'[Hit: '+IntToStr(hit)+',DAR: '+IntToStr(GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady))+']',$1000000 or _log_trace);
      [*] = ;
   struct.end
section.end

