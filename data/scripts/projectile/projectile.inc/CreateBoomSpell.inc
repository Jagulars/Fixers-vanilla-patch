section.begin
   Name = CreateBoomSpell
   Code : struct.begin
      [*] = ;var _log_name : String = 'PROJECTILE\PROJECTILE.INC\CREATEBOOMSPELL';
      [*] = ;var _log_trace : Integer = $800001;
      [*] = ;var _log : Boolean = True;
      [*] = ;
      [*] = ;var spellID : Integer = GetIntValueByIndex(gc_stack_projectile_iType)-gc_projectile_iSpell;
      [*] = ;var ownerUID : Integer = GetIntValueByIndex(gc_stack_projectile_iOwner);
      [*] = ;var ownerGOHandle : Integer = GetGameObjectHandleByUniqueId(ownerUID);
      [*] = ;var tUID : Integer = GetIntValueByIndex(gc_stack_projectile_iTarget);
      [*] = ;var bPlaySound : Boolean = True;
      [*] = ;var bDisplayBoom : Boolean = _obj_EnabledByFlag(gc_ObjectFlagBattleFX);
      [*] = ;  
      [*] = ;_gv_traceState(_log_name+'[Spell ID: '+IntToStr(spellID)+', Caster: '+GetGameObjectCustomNameByHandle(ownerGOHandle)+']',_log_trace);
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
      [*] = ;procedure CreateBoomOnUnit(const goHandle, spellID : Integer);
      [*] = ;begin
      [*] = ;   if (goHandle<>0) then
      [*] = ;   begin
      [*] = ;      var bWound : Boolean = False;
      [*] = ;
      [*] = ;      if (spellID > 0) then
      [*] = ;      begin
      [*] = ;         var pSpell : Integer = ParserSelectByHandleByIndex(gPrototypeData.spells.handle, spellID);
      [*] = ;         
      [*] = ;         if bDisplayBoom then
      [*] = ;         begin
      [*] = ;            var fx : String = ParserGetValueByKeyByHandle(pSpell, 'FX');
      [*] = ;            if fx = '' then
      [*] = ;               fx := 'fx_default_spell';
      [*] = ;            
      [*] = ;            if ParserGetBoolValueByKeyByHandle(pSpell, 'IndependentFX') then
      [*] = ;            begin
      [*] = ;               _fx_CreateFX(0, fx, 0, GetGameObjectPositionXByHandle(goHandle), GetGameObjectPositionYByHandle(goHandle), GetGameObjectPositionZByHandle(goHandle), 0);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            case spellID of
      [*] = ;               gc_spell_web : begin
      [*] = ;                  if (GetEffectParser(goHandle, gc_upgrade_web, gc_spell_web)<>0) and (_fx_FindFXHandleByID(goHandle, true, 3)=0) then
      [*] = ;                     _fx_GetOrCreateFXByID(goHandle, 'fxspiderweb', 0, 0, 0, 0, 0, 3);
      [*] = ;               end;
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if _log then _log_obj('Spell FX: '+fx);
      [*] = ;                  var fxHnd : Integer = _fx_CreateFX(goHandle, fx, 0, 0, 0, 0, 0);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pSpellEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;         var i, abilityID : Integer;
      [*] = ;         var bAntiSpell : Boolean = false;
      [*] = ;         for i := ParserGetCountByHandle(pSpellEffects)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSpellEffect : Integer = ParserSelectByHandleByIndex(pSpellEffects, i);
      [*] = ;            abilityID := ParserGetIntValueByKeyByHandle(pSpellEffect, 'AbilityID');
      [*] = ;            
      [*] = ;            if (abilityID = gc_ability_dispel) then
      [*] = ;               bAntiSpell := true
      [*] = ;            else
      [*] = ;            if (abilityID = gc_ability_life) then
      [*] = ;            begin
      [*] = ;               if ParserGetBoolValueByKeyByHandle(pSpell, 'Negative') then
      [*] = ;                  bWound := True;
      [*] = ;            end
      [*] = ;         end;
      [*] = ;
      [*] = ;         if bAntiSpell then
      [*] = ;         begin
      [*] = ;            if (_fx_FindFXHandleByID(goHandle, true, 3)<>0) then
      [*] = ;            begin
      [*] = ;               if (GetEffectParser(goHandle, gc_upgrade_web, gc_spell_web)=0) then
      [*] = ;                  _fx_GetOrCreateFXByID(goHandle, 'fxspiderwebfinish', 0, 0, 0, 0, 0, 3);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'DeathAnimReady');
      [*] = ;      if _log then _log_obj(_log_name+'['+GetGameObjectCustomNameByHandle(goHandle)+', DAR: '+IntToStr(GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iDeathAnimReady))+']');
      [*] = ;
      [*] = ;      if GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife) > 0 then
      [*] = ;      begin
      [*] = ;         var pTarParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;         var bUID : Integer = ParserGetIntValueByKeyByHandle(pTarParser, 'BerserkUID');
      [*] = ;
      [*] = ;         if ((ownerUID > 0) and (bUID = ownerUID)) or ((ownerUID = 0) and (bUID = -1)) then
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'PlayBerserkAnimation')
      [*] = ;         else
      [*] = ;         if (bWound) then
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'OnDamage');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 0;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CheckDeathAnimation');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (ownerGOHandle<>0) then
      [*] = ;begin
      [*] = ;   if bPlaySound then
      [*] = ;   begin
      [*] = ;      var prevSoundHnd : Integer = SndGetOrCreateSound(GetGUIIntValue('SoundTag'), 'spells', GetSoundManagerListenerHandle);
      [*] = ;      if (not GetSndSoundPlaying(prevSoundHnd)) or (not SameText(GetSndSoundSourceName(prevSoundHnd), 'spell'+IntToStr(spellID))) then // ensure sound won't be played multiple times with mass spells.
      [*] = ;      begin
      [*] = ;         _gui_PlaySound('spells', 'spell'+IntToStr(spellID));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := spellID;
      [*] = ;   MapExecuteState('GetSpellParserByID');
      [*] = ;   var pSpell : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var pSpellEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;   var pSpellEffect : Integer = ParserSelectByHandleByIndex(pSpellEffects, 0);
      [*] = ;
      [*] = ;   var spCumulative : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Cumulative');
      [*] = ;   var spNegative : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Negative');
      [*] = ;   var spTarget : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Target');
      [*] = ;   var spArea : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Area');
      [*] = ;   var spRadius : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Radius');
      [*] = ;   var spOnEnemy : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'OnEnemy');
      [*] = ;   var spOnAlly : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'OnAlly');
      [*] = ;   var abilityID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'AbilityID');
      [*] = ;   //var power : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'Power');
      [*] = ;   if (abilityID = gc_ability_teleport) then spTarget := 5;
      [*] = ;
      [*] = ;   var hexX : Integer = GetIntValueByIndex(gc_stack_projectile_iTPosX);
      [*] = ;   var hexY : Integer = GetIntValueByIndex(gc_stack_projectile_iTPosY);
      [*] = ;   var pHexCells : Integer = gHexCells.handle;
      [*] = ;   var ind : Integer = gc_battle_GridSize * hexY + hexX;
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;   var hexPosX : Float = ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;   var hexPosY : Float = ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(ownerGOHandle);
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;   var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   if spArea = 2 then
      [*] = ;   begin
      [*] = ;      if spOnAlly then
      [*] = ;      begin
      [*] = ;         for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;            if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := spellID;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'IsSpellTarget');
      [*] = ;               if BoolRegister0 then
      [*] = ;                  CreateBoomOnUnit(goHandle, spellID);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if spOnEnemy then
      [*] = ;      begin
      [*] = ;         for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;
      [*] = ;            if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := spellID;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'IsSpellTarget');
      [*] = ;               if BoolRegister0 then
      [*] = ;                  CreateBoomOnUnit(goHandle, spellID);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case spTarget of
      [*] = ;         // unit
      [*] = ;         1 : begin
      [*] = ;            CreateBoomOnUnit(GetGameObjectHandleByUniqueID(tUID), spellID);
      [*] = ;         end;
      [*] = ;         // unit corpse
      [*] = ;         2, 4 : begin
      [*] = ;            var bCasted : Boolean = false;
      [*] = ;
      [*] = ;            if spOnAlly then
      [*] = ;            begin
      [*] = ;               for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;                  var playable : Boolean = GetGameObjectPlayableObjectByHandle(goHandle);
      [*] = ;
      [*] = ;                  var goX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  var goY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;                  if (not playable) and (goX = hexX) and (goY = hexY) then
      [*] = ;                  begin
      [*] = ;                     CreateBoomOnUnit(goHandle, spellID);
      [*] = ;                     bCasted := true;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if spOnEnemy and (not bCasted) then
      [*] = ;            begin
      [*] = ;               for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;                  var playable : Boolean = GetGameObjectPlayableObjectByHandle(goHandle);
      [*] = ;
      [*] = ;                  var goX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  var goY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;                  if (not playable) and (goX = hexX) and (goY = hexY) then
      [*] = ;                  begin
      [*] = ;                     CreateBoomOnUnit(goHandle, spellID);
      [*] = ;                     bCasted := true;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         // tile
      [*] = ;         3 : begin
      [*] = ;            if ParserGetBoolValueByKeyByHandle(pSpell, 'IndependentFX') and bDisplayBoom then
      [*] = ;            begin
      [*] = ;               var fx : String = ParserGetValueByKeyByHandle(pSpell, 'FX');
      [*] = ;               _fx_CreateFX(0, fx, 0, hexPosX, 0, hexPosY, 0);
      [*] = ;               bDisplayBoom := false;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if spOnAlly then
      [*] = ;            begin
      [*] = ;               for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;                  if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;                  begin
      [*] = ;                     var goX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;                     var goY : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;                     var size : Float = gc_HexSize * Sqrt(3);
      [*] = ;                     var dist : Integer = Round(VectorDistance(goX, 0, goY, hexPosX, 0, hexPosY) / size);
      [*] = ;
      [*] = ;                     if (dist <= spRadius) then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := spellID;
      [*] = ;                        IntRegister1 := 0;
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'IsSpellTarget');
      [*] = ;                        if BoolRegister0 then
      [*] = ;                           CreateBoomOnUnit(goHandle, spellID);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if spOnEnemy then
      [*] = ;            begin
      [*] = ;               for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;
      [*] = ;                  if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;                  begin
      [*] = ;                     var goX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;                     var goY : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;                     var size : Float = gc_HexSize * Sqrt(3);
      [*] = ;                     var dist : Integer = Round(VectorDistance(goX, 0, goY, hexPosX, 0, hexPosY) / size);
      [*] = ;
      [*] = ;                     if (dist <= spRadius) then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := spellID;
      [*] = ;                        IntRegister1 := 0;
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'IsSpellTarget');
      [*] = ;                        if BoolRegister0 then
      [*] = ;                           CreateBoomOnUnit(goHandle, spellID);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         5, 6 : begin
      [*] = ;            //if abilityID > 1000 then
      [*] = ;            begin
      [*] = ;               var bCasted : Boolean = false;
      [*] = ;               for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;                  var goX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  if (goX = hexX) and (GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY) = hexY) then
      [*] = ;                  begin
      [*] = ;                     CreateBoomOnUnit(goHandle, spellID);
      [*] = ;                     if abilityID > 1000 then
      [*] = ;                     begin
      [*] = ;                        bCasted := true;
      [*] = ;                        SetGameObjectVisibleByHandle(goHandle, true);
      [*] = ;                        if bDisplayBoom then
      [*] = ;                        _fx_CreateFX(ownerGOHandle, 'fx_default_spell', 0, 0, 0, 0, 0);
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (not bCasted) then
      [*] = ;               begin
      [*] = ;                  for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;
      [*] = ;                     var goX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                     if (goX = hexX) and (GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY) = hexY) then
      [*] = ;                     begin
      [*] = ;                        CreateBoomOnUnit(goHandle, spellID);
      [*] = ;                        if abilityID > 1000 then
      [*] = ;                        begin
      [*] = ;                           SetGameObjectVisibleByHandle(goHandle, true);
      [*] = ;                           if bDisplayBoom then
      [*] = ;                           _fx_CreateFX(ownerGOHandle, 'fx_default_spell', 0, 0, 0, 0, 0);
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   SetGameObjectIntValueIndByHandle(ownerGOHandle, gc_stack_unit_iTargetUID, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

