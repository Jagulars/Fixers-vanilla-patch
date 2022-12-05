section.begin
   Name = CreateProjectile
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\CREATEPROJECTILE';
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;var dirX : Float = GetGameObjectMyTransformedVirtualDirectionX;
      [*] = ;var dirY : Float = GetGameObjectMyTransformedVirtualDirectionY;
      [*] = ;var dirZ : Float = GetGameObjectMyTransformedVirtualDirectionZ;
      [*] = ;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myHandle);
      [*] = ;var tUID : Integer = GetIntValueByIndex(gc_stack_unit_iTargetUID);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;
      [*] = ;var FrameShift : Integer = 6;
      [*] = ;var ptType : Integer = gc_projectile_iEmpty;
      [*] = ;
      [*] = ;var plHandle : Integer = _plr_GetOrCreatePlayer('projectiles', 'misc', 'cmPlayer', false);
      [*] = ;var ptHandle : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;
      [*] = ;case GetGameObjectMyBaseName of
      [*] = ;   'warrior' : begin
      [*] = ;      FrameShift := 35;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('warrior_arrow', false);
      [*] = ;   end;
      [*] = ;   'commander' : begin
      [*] = ;      FrameShift := 170;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('commander_arrow', false);
      [*] = ;   end;
      [*] = ;   'halfling' : SetGameObjectMyChildVisibleByBaseName('halfling_stone', false);
      [*] = ;   'slinger' : SetGameObjectMyChildVisibleByBaseName('slinger_stone', false);
      [*] = ;   'archer' : SetGameObjectMyChildVisibleByBaseName('archer_arrow', false);
      [*] = ;   'centaur' : SetGameObjectMyChildVisibleByBaseName('centaur_arrow', false);
      [*] = ;   'scout' : begin
      [*] = ;      FrameShift := 35;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('scout_arrow', false);
      [*] = ;   end;
      [*] = ;   'horsearcher' : begin
      [*] = ;      FrameShift := 20;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('horsearcher_arrow', false);
      [*] = ;   end;
      [*] = ;   'elf' : SetGameObjectMyChildVisibleByBaseName('elf_arrow', false);
      [*] = ;   'barbarian' : begin
      [*] = ;      FrameShift := 50;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('barbarian_axe_small', false);
      [*] = ;   end;
      [*] = ;   'crossbowman' : begin
      [*] = ;      FrameShift := 50;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('crossbowman_arrow', false);
      [*] = ;   end;
      [*] = ;   'thief' : begin
      [*] = ;      FrameShift := 22;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('thief_knife_right', false);
      [*] = ;   end;
      [*] = ;   'spearman' : begin
      [*] = ;      FrameShift := 6;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('spearman_spear', false);
      [*] = ;   end;
      [*] = ;   'giant' : SetGameObjectMyChildVisibleByBaseName('giant_stone', false);
      [*] = ;   'assassin' : begin
      [*] = ;      FrameShift := 24;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('assassin_knife', false);
      [*] = ;   end;
      [*] = ;   'catapult' : SetGameObjectMyChildVisibleByBaseName('catapult_stone', false);
      [*] = ;   'ballista' : SetGameObjectMyChildVisibleByBaseName('ballista_missile', false);
      [*] = ;   'giantfire' : SetGameObjectMyChildVisibleByBaseName('giant_stone', false);
      [*] = ;   'dragon', 'dragonfire', 'dragonstorm', 'dragonunholy' : begin
      [*] = ;      FrameShift := 20;
      [*] = ;   end;
      [*] = ;   'centaurchief' : begin
      [*] = ;      FrameShift := 20;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('centaurchief_lance', false);
      [*] = ;   end;
      [*] = ;   'centaurhuntsman' : begin
      [*] = ;      FrameShift := 20;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('centaurhuntsman_bolo', false);
      [*] = ;   end;
      [*] = ;   'dwarfmechanic' : begin
      [*] = ;      FrameShift := 90;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('dwarfmechanic_arrow', false);
      [*] = ;   end;
      [*] = ;   'elfdruid' : begin
      [*] = ;      FrameShift := 50;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('elfdruid_arrow', false);
      [*] = ;   end;
      [*] = ;   'elfranger' : begin
      [*] = ;      FrameShift := 80;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('elfranger_arrow', false);
      [*] = ;   end;
      [*] = ;   'goblinalchemist' : SetGameObjectMyChildVisibleByBaseName('goblinalchemist_bottle', false);
      [*] = ;   'goblinpoisonspit' : SetGameObjectMyChildVisibleByBaseName('goblinpoisonspit_tube_thorn', false);
      [*] = ;   'halflingforager' : begin
      [*] = ;      FrameShift := 30;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('halflingforager_stone', false);
      [*] = ;   end;
      [*] = ;   'halflingspy' : SetGameObjectMyChildVisibleByBaseName('halflingspy_stone', false);
      [*] = ;   'orcthrower' : begin
      [*] = ;      FrameShift := 40;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('orcthrower_dubina_small_3', false);
      [*] = ;   end;
      [*] = ;   'cataphract' : begin
      [*] = ;      FrameShift := 20;
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('cataphract_arrow', false);
      [*] = ;   end;
      [*] = ;   'juggernaut' : begin
      [*] = ;      FrameShift := 20;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=1 to 12 do
      [*] = ;      SetGameObjectMyChildVisibleByBaseName('juggernaut_arrow'+IntToStr(i), false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myHandle);
      [*] = ;var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myHandle);
      [*] = ;var DelayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor);
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   GameObjectMyDelayExecuteState('RestoreHiddenProjectile', DelayTime);
      [*] = ;
      [*] = ;var ptDirX : Float = -1;
      [*] = ;var ptDirY : Float = 0;
      [*] = ;var ptDirZ : Float = 0;
      [*] = ;var angle : Float = VectorAngle(dirX, dirY, dirZ, ptDirX, ptDirY, ptDirZ);
      [*] = ;var x, y, z : Float;
      [*] = ;VectorCross(dirX, dirY, dirZ, ptDirX, ptDirY, ptDirZ, x, y, z);
      [*] = ;if y < 0 then
      [*] = ;angle := -angle;
      [*] = ;
      [*] = ;GameObjectRollByHandle(ptHandle, angle);
      [*] = ;SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iOwner, myUID);
      [*] = ;//SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iType, 0); // not needed
      [*] = ;SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iTarget, tUID);
      [*] = ;SetGameObjectFloatValueIndByHandle(ptHandle, gc_stack_projectile_iTPosX, 0);
      [*] = ;SetGameObjectFloatValueIndByHandle(ptHandle, gc_stack_projectile_iTPosY, 0);
      [*] = ;GameObjectExecuteStateByHandle(ptHandle, 'InitialFly');
      [*] = ;
      [*] = ;var arrows : Integer = GetIntValueByIndex(gc_stack_unit_iArrowsCount);
      [*] = ;SetIntValueByIndex(gc_stack_unit_iArrowsCount, arrows+1);
      [*] = ;var shotCount : Integer = GetIntValueByIndex(gc_stack_unit_iShotCount);
      [*] = ;SetIntValueByIndex(gc_stack_unit_iShotCount, shotCount-1);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;
   struct.end
section.end

