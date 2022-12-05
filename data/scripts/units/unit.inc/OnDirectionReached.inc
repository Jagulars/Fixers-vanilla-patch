section.begin
   Name = OnDirectionReached
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myAnim : String = GetGameObjectMyAnimationCycleName();
      [*] = ;SetGameObjectMyTargetRotatingMode('trmNone');
      [*] = ;SetGameObjectMyTrackPointAnimationNames('walk', 'idle');
      [*] = ;   
      [*] = ;var modifier : Float;
      [*] = ;case myAnim of
      [*] = ;   'attack' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'wound' : modifier := gc_battle_unit_woundspeedmod;
      [*] = ;   'woundattack' : modifier := gc_battle_unit_woundspeedmod;
      [*] = ;   'shot' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'cast' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'death' : modifier := gc_battle_unit_deathspeedmod;
      [*] = ;   'heal' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'parry' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'parryattack' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'berserk' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'crushing_blow' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'round_attack' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   'cannibalize' : modifier := gc_battle_unit_attackspeedmod;
      [*] = ;   else modifier := 0;
      [*] = ;end;
      [*] = ;_unit_ModifyAnimIntervalFactor(GetGameObjectMyHandle, modifier); //IntervalFactor must be set here or it will be 1 (unaffected by battle speed mod) if unit xhanges direction during the action.
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

