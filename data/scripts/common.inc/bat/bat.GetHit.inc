section.begin
   Name = bat.GetHit
   Description : struct.begin
      [*] = ;IntRegister0 - attack value
      [*] = ;IntRegister1 - defend value
      [*] = ;BoolRegister0 - true if should simulate attack
      [*] = ;OUT: IntRegister2 - hit value
      [*] = ;     IntRegister3 - lowest hit value
      [*] = ;     IntRegister4 - highest hit value
   struct.end
   Code : struct.begin
      [*] = ;var defence : Integer = IntRegister1;
      [*] = ;var bRandom : Boolean = BoolRegister0;
      [*] = ;var add : Integer = 1;
      [*] = ;var max : Integer = 3;
      [*] = ;var damage : array [0..3] of Integer;
      [*] = ;var attack : array [0..3] of Integer;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;function GetDamage(attack, defence, mode : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var damage : Integer;
      [*] = ;   var k : Float;
      [*] = ;
      [*] = ;   if attack < 1 then
      [*] = ;      attack := 1;
      [*] = ;
      [*] = ;   if defence >= attack then
      [*] = ;   begin
      [*] = ;      if gBoolRegister_BattleSimulate or ((not bRandom) and (mode = 0)) then
      [*] = ;      begin
      [*] = ;         if defence - attack < 5 then
      [*] = ;            damage := 1
      [*] = ;         else
      [*] = ;            damage := 0;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         case mode of
      [*] = ;            0 : k := RandomExt*(20+attack-defence);
      [*] = ;            1 : k := 0;
      [*] = ;            2 : k := (20+attack-defence);
      [*] = ;         end;
      [*] = ;         
      [*] = ;         if (defence - attack < 10) and (k >= 10) then
      [*] = ;            damage := 1
      [*] = ;         else
      [*] = ;            damage := 0;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      damage := attack - defence;
      [*] = ;
      [*] = ;   Result := damage;
      [*] = ;end;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to 2 do
      [*] = ;begin
      [*] = ;   attack[i] := IntRegister0;
      [*] = ;   damage[i] := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if defence < 0 then
      [*] = ;   defence := 0;
      [*] = ;
      [*] = ;if (not gBoolRegister_BattleSimulate) or gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard)) then
      [*] = ;begin
      [*] = ;   if _log then 
      [*] = ;   begin
      [*] = ;      var randKey1, randKey0 : Integer;
      [*] = ;      GetRandomExtKey64(randKey0, randKey1);
      [*] = ;      _log_Map('bat.GetHit: randKey0 '+IntToStr(randKey0)+' randKey1 '+IntToStr(randKey1));
      [*] = ;      _log_Map('bat.GetHit: attack '+IntToStr(attack[0])+' defence '+IntToStr(defence)+' add '+IntToStr(add)+' max '+IntToStr(max));
      [*] = ;   end;
      [*] = ;
      [*] = ;   if attack[0] > 4 then
      [*] = ;   begin
      [*] = ;      add := attack[0] div 5;
      [*] = ;      max := add * 2 + 1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if (bRandom) then
      [*] = ;      attack[0] := attack[0] + add - Floor(RandomExt() * max);
      [*] = ;   attack[1] := attack[1] + add - max;
      [*] = ;   attack[2] := attack[2] + add;
      [*] = ;   
      [*] = ;   if _log then _log_Map('bat.GetHit: attack modified: '+IntToStr(attack[0])+' defence '+IntToStr(defence)+' add '+IntToStr(add)+' max '+IntToStr(max));
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to 2 do
      [*] = ;   damage[i] := GetDamage(attack[i],defence,i);
      [*] = ;
      [*] = ;IntRegister2 := damage[0];
      [*] = ;IntRegister3 := damage[1];
      [*] = ;IntRegister4 := damage[2];
   struct.end
section.end
