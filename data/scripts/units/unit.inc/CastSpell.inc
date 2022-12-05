section.begin
   Name = CastSpell
   Description : struct.begin
      [*] = ;IntRegister0 - spell ID
      [*] = ;IntRegister1 - target hex
      [*] = ;BoolRegister0 - play animation
   struct.end
   Code : struct.begin
      [*] = ;var spellID : Integer = IntRegister0;
      [*] = ;var pHexParser : Integer = IntRegister1;
      [*] = ;var bExplicitCast : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\CASTSPELL';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;const cEpsilonAngle = 10;
      [*] = ;
      [*] = ;var hexX : Integer = ParserGetIntValueByKeyByHandle(pHexParser, 'X');
      [*] = ;var hexY : Integer = ParserGetIntValueByKeyByHandle(pHexParser, 'Y');
      [*] = ;var hexPosX : Float = ParserGetFloatValueByKeyByHandle(pHexParser, 'CenterX');
      [*] = ;var hexPosY : Float = ParserGetFloatValueByKeyByHandle(pHexParser, 'CenterY');
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var aMode : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode);
      [*] = ;var autoBattle : Boolean = GetPlayerBoolValueIndByHandle(myPlHandle, gc_battle_PLStack_bAutoBattle);
      [*] = ;var isHero : Boolean = GetGameObjectBoolValueIndByHandle(myGOHandle, gc_stack_unit_bIsHero);
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;//var myCustomName : String = GetGameObjectMyCustomName();
      [*] = ;
      [*] = ;var tfUID : Integer = GetIntValueByIndex(gc_stack_unit_iTrueFormUID);
      [*] = ;var tfHandle : Integer = GetGameObjectHandleByUniqueId(tfUID);
      [*] = ;var isTFHero : Boolean = GetGameObjectBoolValueIndByHandle(tfHandle, gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(spellID)+']',_log_trace);
      [*] = ;
      [*] = ;GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;//Log(myCustomName + ' casts spell ' + IntToStr(spellID) + ' on hex (' + IntToStr(hexX) + ', ' + IntToStr(hexY) + ')');
      [*] = ;var pElmLog : Integer = 0;
      [*] = ;var pSrcUnit : Integer = 0;
      [*] = ;var pDestUnit : Integer = 0;
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   pElmLog := _log_battle_AddNewElement;
      [*] = ;   ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 4);
      [*] = ;   ParserSetIntValueByKeyByHandle(pElmLog, 'Param', spellID);
      [*] = ;
      [*] = ;   pSrcUnit := ParserSelectByHandleByKey(pElmLog, 'SrcUnit');
      [*] = ;   ParserSetIntValueByKeyByHandle(pSrcUnit, 'UID', myUID);
      [*] = ;end;
      [*] = ;
      [*] = ;var myGridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;var myGridY : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var mapHeroUID : Integer;
      [*] = ;if isHero then
      [*] = ;   mapHeroUID := GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iHeroUID)
      [*] = ;else
      [*] = ;   mapHeroUID := GetGameObjectIntValueIndByHandle(tfHandle, gc_stack_unit_iHeroUID);
      [*] = ;
      [*] = ;var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(mapHeroUID);
      [*] = ;var mapPlHandle : Integer = GetGameObjectPlayerHandleByHandle(mapHeroHandle);
      [*] = ;
      [*] = ;var pMyGOParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyGOSpells : Integer = ParserSelectByHandleByKey(pMyGOParser, 'Spells');
      [*] = ;
      [*] = ;IntRegister0 := spellID;
      [*] = ;MapExecuteState('GetSpellParserByID');
      [*] = ;var pSpell : Integer = IntRegister1;
      [*] = ;
      [*] = ;var pSpellEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;var pSpellEffect0 : Integer = ParserSelectByHandleByIndex(pSpellEffects, 0);
      [*] = ;var abilityID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect0, 'AbilityID');
      [*] = ;
      [*] = ;var spCumulative : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Cumulative');
      [*] = ;var spNegative : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Negative');
      [*] = ;var spTarget : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Target');
      [*] = ;var spArea : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Area');
      [*] = ;var spRadius : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Radius');
      [*] = ;var spOnEnemy : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'OnEnemy');
      [*] = ;var spOnAlly : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'OnAlly');
      [*] = ;
      [*] = ;var spPowerMod : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'PowerMod');
      [*] = ;
      [*] = ;var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;var curStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;var curMoral : Integer = GetIntValueByIndex(gc_stack_unit_iCurMoral);
      [*] = ;// Fly text data
      [*] = ;var oldLife : Integer = curLife;
      [*] = ;var oldStamina : Integer = curStamina;
      [*] = ;var oldMoral : Integer = curMoral;
      [*] = ;
      [*] = ;if abilityID = gc_ability_teleport then
      [*] = ;   spTarget := 5;
      [*] = ;
      [*] = ;procedure ClearEffectsBySpellID(goHandle, cSpellID : Integer);
      [*] = ;begin
      [*] = ;   var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   var pGOEffects : Integer = ParserSelectByHandleByKey(pGOParser, 'Effects');
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i := ParserGetCountByHandle(pGOEffects)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGOEffect : Integer = ParserSelectByHandleByIndex(pGOEffects, i);
      [*] = ;
      [*] = ;      if ParserGetIntValueByKeyByHandle(pGOEffect, 'ParentSpellID') = cSpellID then
      [*] = ;         ParserClearByHandle(pGOEffect);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CorpseSpell(corpseHandle : Integer);
      [*] = ;begin
      [*] = ;   if abilityID > 1000 then
      [*] = ;   begin
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect0, 'Power');
      [*] = ;
      [*] = ;      //if isHero and (mapHeroHandle<>0) then
      [*] = ;      power := power + _unit_CheckAbilityExt(myGOHandle, gc_ability_summoning_power) + _unit_CheckAbility(myGOHandle, gc_ability_necro_summoning_power);
      [*] = ;
      [*] = ;      var unitID : Integer = abilityID - 1000;
      [*] = ;
      [*] = ;      IntRegister0 := unitID;
      [*] = ;      IntRegister1 := power;
      [*] = ;      IntRegister2 := hexX;
      [*] = ;      IntRegister3 := hexY;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'SummonUnit');
      [*] = ;      var goHandle : Integer = IntRegister4;
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(corpseHandle, gc_stack_unit_iCurrentX, -1);
      [*] = ;      SetGameObjectIntValueIndByHandle(corpseHandle, gc_stack_unit_iCurrentY, -1);
      [*] = ;
      [*] = ;      if not gBoolRegister_BattleSimulate then
      [*] = ;      begin
      [*] = ;         var remainsUID : Integer = GetGameObjectIntValueIndByHandle(corpseHandle, gc_stack_unit_iRemainsUID);
      [*] = ;         var remainsHnd : Integer = GetGameObjectHandleByUniqueId(remainsUID);
      [*] = ;         if (remainsHnd <> 0) then
      [*] = ;         begin
      [*] = ;            if gc_RecycleBattleField then
      [*] = ;               _obj_Recycle(remainsHnd)
      [*] = ;            else
      [*] = ;               AddObjectToDestroyList(remainsHnd);
      [*] = ;         end;
      [*] = ;         SetGameObjectIntValueIndByHandle(corpseHandle, gc_stack_unit_iRemainsUID, 0);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if abilityID = gc_ability_life then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(corpseHandle, 'Resurrect');
      [*] = ;
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect0, 'Power');
      [*] = ;      //if isHero and (mapHeroHandle <> 0) then
      [*] = ;      begin
      [*] = ;         var abil905 : Integer = _unit_CheckAbilityExt(myGOHandle, gc_ability_spell_power);
      [*] = ;
      [*] = ;         power := power + (abil905 * spPowerMod) div 10;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if power > 100 then
      [*] = ;         power := 100;
      [*] = ;
      [*] = ;      var maxLife : Integer = _unit_GetProperty(corpseHandle, gc_battle_unit_iMaxLife);
      [*] = ;
      [*] = ;      var curLife : Integer = (maxLife * power) div 100;
      [*] = ;      if curLife < 1 then
      [*] = ;         curLife := 1;
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(corpseHandle, gc_stack_unit_iCurLife, curLife);
      [*] = ;      _unit_GUIUpdateUnitHUD(corpseHandle);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var spLifeCost : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'LifeCost');
      [*] = ;
      [*] = ;if bExplicitCast then
      [*] = ;begin
      [*] = ;   // spell cost
      [*] = ;   var pMyGOSpell : Integer = 0;
      [*] = ;   var bInterfacePlayer : Boolean = (myPlHandle = GetPlayerHandleInterfaceIO);
      [*] = ;   
      [*] = ;   if bInterfacePlayer and (not autoBattle) and (not gBoolRegister_QuickBattle) then
      [*] = ;      pMyGOSpell := ParserSelectByHandleByIndex(pMyGOSpells, gIntRegister_CurSpellIndex)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      for i := 0 to ParserGetCountByHandle(pMyGOSpells)-1 do
      [*] = ;      begin
      [*] = ;         var pMySpell : Integer = ParserSelectByHandleByIndex(pMyGOSpells, i);
      [*] = ;         var id : Integer = ParserGetIntValueByKeyByHandle(pMySpell, 'SpellID');
      [*] = ;         var used : Boolean = ParserGetBoolValueByKeyByHandle(pMySpell, 'Used');
      [*] = ;   
      [*] = ;         if (id = spellID) and (not used) then
      [*] = ;         begin
      [*] = ;            pMyGOSpell := pMySpell;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var spellAmmo : Integer = ParserGetIntValueByKeyByHandle(pMyGOSpell, 'Ammo');
      [*] = ;   
      [*] = ;   var plKarma : Integer = GetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;   
      [*] = ;   var spGemCost : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Cost');
      [*] = ;   var spStamCost : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'StamCost');
      [*] = ;   var spKarma : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Karma');
      [*] = ;   
      [*] = ;   if isHero or isTFHero then
      [*] = ;   begin
      [*] = ;      // world rule
      [*] = ;      if (_worldrule_GetWorldRuleAbilityExistByID(8)) then
      [*] = ;      begin
      [*] = ;         var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(8);
      [*] = ;         spGemCost := _misc_RoundUp((spGemCost*param1)/100);
      [*] = ;      end;
      [*] = ;   
      [*] = ;      var abil983 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_low_spells_cost);
      [*] = ;      spGemCost := (spGemCost * (100 - abil983)) div 100;
      [*] = ;   
      [*] = ;      ParserSetBoolValueByKeyByHandle(pMyGOSpell, 'Used', true);
      [*] = ;   
      [*] = ;      var myHero : Boolean = true;
      [*] = ;      if gBoolRegister_ArenaBattle and (gBoolRegister_ArenaWatcher or (aMode = 0)) then
      [*] = ;         myHero := false;
      [*] = ;   
      [*] = ;      if myHero and (spGemCost > 0) then
      [*] = ;      begin
      [*] = ;         var plGem : Integer = GetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         plGem := plGem - spGemCost;
      [*] = ;         SetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;   
      [*] = ;         var gemSpent : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iGemSpent);
      [*] = ;         gemSpent := gemSpent + spGemCost;
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iGemSpent, gemSpent);
      [*] = ;      end;
      [*] = ;   
      [*] = ;      if (not gBoolRegister_BattleSimulate) and myHero and (mapPlHandle <> 0) then
      [*] = ;      begin
      [*] = ;         plKarma := plKarma + spKarma;
      [*] = ;         SetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iKarma, plKarma);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var ammo : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCurAmmo);
      [*] = ;      SetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCurAmmo, ammo-spellAmmo);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var spellCast : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iSpellCast);
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iSpellCast, spellCast + spStamCost);
      [*] = ;   
      [*] = ;   var movePoints : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints);
      [*] = ;   IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var speed : Integer = IntRegister1;
      [*] = ;   
      [*] = ;   if (movePoints < speed) then
      [*] = ;      spStamCost := spStamCost + 1;
      [*] = ;   
      [*] = ;   IntRegister0 := -spStamCost;
      [*] = ;   ExecuteState('ChangeStamina');
      [*] = ;   curStamina := GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;   
      [*] = ;   if GetBoolValueByIndex(gc_stack_unit_bStealthMode) then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := false;
      [*] = ;      ExecuteState('SwitchStealthModeFlag');
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var archmage : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bArchmage);
      [*] = ;   
      [*] = ;   if archmage and (curStamina > 0) and (movePoints > 1) then
      [*] = ;   begin
      [*] = ;      movePoints := movePoints div 2;
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, movePoints);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bArchmage, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bActionTaken, true);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMelee, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bCanShoot, false);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ExecuteState('ActionDone');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var spellTargetGOHandle : Integer = 0;
      [*] = ;
      [*] = ;if spArea = 2 then
      [*] = ;begin
      [*] = ;   if spOnAlly then
      [*] = ;   begin
      [*] = ;      for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;         var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;         IntRegister0 := spellID;
      [*] = ;         IntRegister1 := 0;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'IsSpellTarget');
      [*] = ;         if (curLife > 0) and BoolRegister0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            IntRegister1 := myUID;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'UnderSpell');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if spOnEnemy then
      [*] = ;   begin
      [*] = ;      for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;         var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;         IntRegister0 := spellID;
      [*] = ;         IntRegister1 := 0;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'IsSpellTarget');
      [*] = ;         if (curLife > 0) and BoolRegister0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            IntRegister1 := myUID;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'UnderSpell');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   case spTarget of
      [*] = ;      // unit
      [*] = ;      1 : begin
      [*] = ;         var tGOHandle : Integer = GetGameObjectHandleByUniqueID(ParserGetIntValueByKeyByHandle(pHexParser, 'UID'));
      [*] = ;
      [*] = ;         IntRegister0 := spellID;
      [*] = ;         IntRegister1 := myUID;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'UnderSpell');
      [*] = ;         if IntRegister2 <> 0 then
      [*] = ;            spellTargetGOHandle := GetGameObjectHandleByUniqueID( IntRegister2 );
      [*] = ;      end;
      [*] = ;      // unit corpse
      [*] = ;      2, 4 : begin
      [*] = ;         var casted : Boolean = false;
      [*] = ;         var corpseHandle : Integer = 0;
      [*] = ;
      [*] = ;         if spOnAlly then
      [*] = ;         begin
      [*] = ;            for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;               var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;               var goX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;               var goY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;               if (curLife <= 0) and (goX = hexX) and (goY = hexY) then
      [*] = ;               begin
      [*] = ;                  corpseHandle := goHandle;
      [*] = ;                  spellTargetGOHandle := corpseHandle;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if spOnEnemy and (corpseHandle = 0) then
      [*] = ;         begin
      [*] = ;            for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;               var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;               var goX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;               var goY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;               if (curLife <= 0) and (goX = hexX) and (goY = hexY) then
      [*] = ;               begin
      [*] = ;                  corpseHandle := goHandle;
      [*] = ;                  spellTargetGOHandle := corpseHandle;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if corpseHandle <> 0 then
      [*] = ;         begin
      [*] = ;            CorpseSpell(corpseHandle);
      [*] = ;            casted := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      // tile
      [*] = ;      3 : begin
      [*] = ;         var plHandle : Integer = 0;
      [*] = ;
      [*] = ;         if spOnAlly then
      [*] = ;         begin
      [*] = ;            for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;               var goX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;               var goY : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;
      [*] = ;               var size : Float = gc_HexSize * Sqrt(3);
      [*] = ;               var dist : Integer = Round(VectorDistance(goX, 0, goY, hexPosX, 0, hexPosY) / size);
      [*] = ;
      [*] = ;               if (dist <= spRadius) then
      [*] = ;               begin
      [*] = ;                  var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;                  IntRegister0 := spellID;
      [*] = ;                  IntRegister1 := 0;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'IsSpellTarget');
      [*] = ;                  if (curLife > 0) and BoolRegister0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := spellID;
      [*] = ;                     IntRegister1 := myUID;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'UnderSpell');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if spOnEnemy then
      [*] = ;         begin
      [*] = ;            for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;
      [*] = ;               var goX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;               var goY : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;
      [*] = ;               var size : Float = gc_HexSize * Sqrt(3);
      [*] = ;               var dist : Integer = Round(VectorDistance(goX, 0, goY, hexPosX, 0, hexPosY) / size);
      [*] = ;
      [*] = ;               if (dist <= spRadius) then
      [*] = ;               begin
      [*] = ;                  var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;                  IntRegister0 := spellID;
      [*] = ;                  IntRegister1 := 0;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'IsSpellTarget');
      [*] = ;                  if (curLife > 0) and BoolRegister0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := spellID;
      [*] = ;                     IntRegister1 := myUID;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'UnderSpell');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      5, 6 : begin
      [*] = ;         var power : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect0, 'Power');
      [*] = ;
      [*] = ;         if abilityID > 1000 then
      [*] = ;         begin
      [*] = ;            //if isHero and (mapHeroHandle <> 0) then
      [*] = ;            power := power + _unit_CheckAbilityExt(myGOHandle, 907);
      [*] = ;
      [*] = ;            var unitID : Integer = abilityID - 1000;
      [*] = ;
      [*] = ;            IntRegister0 := unitID;
      [*] = ;            IntRegister1 := power;
      [*] = ;            IntRegister2 := hexX;
      [*] = ;            IntRegister3 := hexY;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'SummonUnit');
      [*] = ;            var goHandle : Integer = IntRegister4;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_TeleportUID);
      [*] = ;
      [*] = ;            if goHandle <> 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := hexX;
      [*] = ;               IntRegister1 := hexY;
      [*] = ;               BoolRegister0 := false;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'Replace');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var isDead : Boolean = false;
      [*] = ;if (spLifeCost > 0) and bExplicitCast then
      [*] = ;begin
      [*] = ;   var curLife : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCurLife);
      [*] = ;   var hit : Integer = spLifeCost;
      [*] = ;
      [*] = ;   if hit > curLife then
      [*] = ;      hit := curLife;
      [*] = ;
      [*] = ;   IntRegister0 := hit;
      [*] = ;   IntRegister1 := 2;
      [*] = ;   IntRegister2 := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;   FloatRegister0 := 0;
      [*] = ;   ExecuteState('TakeDamage');
      [*] = ;   isDead := BoolRegister0;
      [*] = ;end;
      [*] = ;
      [*] = ;if bExplicitCast and (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   var angle : Float = 0;
      [*] = ;   var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;   if GetGameObjectMyTrackPointMovementMode = 'mmNone' then
      [*] = ;   begin
      [*] = ;      if (myGridX <> hexX) or (myGridY <> hexY) then
      [*] = ;      begin
      [*] = ;         var dirX : Float = GetGameObjectMyTransformedVirtualDirectionX;
      [*] = ;         var dirY : Float = GetGameObjectMyTransformedVirtualDirectionY;
      [*] = ;         var dirZ : Float = GetGameObjectMyTransformedVirtualDirectionZ;
      [*] = ;
      [*] = ;         var dirX1 : Float = hexPosX - GetGameObjectMyPositionX();
      [*] = ;         var dirY1 : Float = 0;
      [*] = ;         var dirZ1 : Float = hexPosY - GetGameObjectMyPositionZ();
      [*] = ;
      [*] = ;         angle := VectorAngle(dirX, dirY, dirZ, dirX1, dirY1, dirZ1);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if angle > cEpsilonAngle then
      [*] = ;      begin
      [*] = ;         SetGameObjectMyRotatingTargetCoords(hexPosX, 0, hexPosY);
      [*] = ;         SetGameObjectMyTrackPointAnimationNames('', '');
      [*] = ;
      [*] = ;         var tpts : Float = ParserGetFloatValueByKeyByHandle(pMyParser, 'TPTurnStep');
      [*] = ;         SetGameObjectMyTrackPointTurnStep(tpts*angle/60*_misc_CalcBattleSpeedModified(gc_battle_unit_turnspeedmod));
      [*] = ;         SetGameObjectMyTargetRotatingMode('trmToTargetCoordinates');
      [*] = ;      end;
      [*] = ;
      [*] = ;      _unit_ModifyAnimIntervalFactor(myGOHandle, gc_battle_unit_attackspeedmod);
      [*] = ;      GameObjectMySwitchToTreeAnimationCyclesDefault('cast');
      [*] = ;      _unit_PlaySound(myGOHandle, 'units', 'cast');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var rotate : Boolean = false;
      [*] = ;      if (myGridX <> hexX) or (myGridY <> hexY) then
      [*] = ;         rotate := true;
      [*] = ;
      [*] = ;      ParserSetValueByKeyByHandle(pMyParser, 'DefferedAnimation', 'cast');
      [*] = ;      ParserSetBoolValueByKeyByHandle(pMyParser, 'AnimRotate', rotate);
      [*] = ;      if rotate then
      [*] = ;      begin
      [*] = ;         ParserSetFloatValueByKeyByHandle(pMyParser, 'AnimTargetX', hexX);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pMyParser, 'AnimTargetY', hexY);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (spellTargetGOHandle=0) then
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iSpellTargetUID, 0)
      [*] = ;   else
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iSpellTargetUID, GetGameObjectUniqueIdByHandle(spellTargetGOHandle));
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iSpellID, spellID);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iTargetX, hexX);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iTargetY, hexY);
      [*] = ;   var FrameShift : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCastFrame);
      [*] = ;   var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myGOHandle);
      [*] = ;   var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myGOHandle);
      [*] = ;   var DelayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor);
      [*] = ;   GameObjectMyDelayExecuteState('CreateSpellProjectile', DelayTime);
      [*] = ;
      [*] = ;   var stFrame, endFrame : Integer;
      [*] = ;   var exist : Boolean = GetGameObjectFrameAnimationDataByHandle(myGOHandle, 'cast', stFrame, endFrame);
      [*] = ;   if exist then
      [*] = ;   begin
      [*] = ;      if GetGameObjectMyVisible() then
      [*] = ;         _gv_SetBattleLock(1,_log_name+'[578]'); // gec add +1 to next +1, and add -1 lock count when projectile reach target, to avoid game hang on barbarian berserk animation in special situation
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ErrorLogI(_log_name+' '+GetGameObjectMyCustomName()+' has no animation cast!');
      [*] = ;      ExecuteState('Idle');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if GetGameObjectMyVisible() and (gIntRegister_SacrificeUID <> myUID) then
      [*] = ;      _gv_SetBattleLock(1,_log_name+'[569]');
      [*] = ;end;
      [*] = ;if (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   var pMyHex : Integer = _map_GetBattleHex(myGridX, myGridY);
      [*] = ;   if pMyHex <> pHexParser then
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iFacing, _map_GetFacing(pMyHex, pHexParser));
      [*] = ;end;
      [*] = ;
      [*] = ;if gIntRegister_SacrificeUID <> 0 then
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SacrificeUID);
      [*] = ;   if bExplicitCast and _obj_EnabledByFlag(gc_ObjectFlagBattleFX) then
      [*] = ;   begin
      [*] = ;      _fx_CreateFX(goHandle, 'fx_impact_burn', 0, 0, 0, 0, 0);
	  [*] = ;      //_gui_PlaySound('spells', 'spell23');
      [*] = ;   end;
      [*] = ;   
      [*] = ;   IntRegister0 := myUID;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'Death');
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'CheckDeathAnimation');
      [*] = ;   _unit_GUIUpdateUnitHUD(goHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;if isDead and (gIntRegister_SacrificeUID <> myUID) then
      [*] = ;   ExecuteState('CheckDeathAnimation');
      [*] = ;
      [*] = ;{ExecuteState('GetPhantomFormHandle');
      [*] = ;var pfHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;if pfHandle <> 0 then
      [*] = ;begin
      [*] = ;   var value : Integer = GetIntValueByIndex(gc_stack_unit_iMovePoints);
      [*] = ;   SetGameObjectIntValueIndByHandle(pfHandle, gc_stack_unit_iMovePoints, value);
      [*] = ;   var bValue : Boolean = GetBoolValueByIndex(gc_stack_unit_bSkipTurn);
      [*] = ;   SetGameObjectBoolValueIndByHandle(pfHandle, gc_stack_unit_bSkipTurn, bValue);
      [*] = ;   bValue := GetBoolValueByIndex(gc_stack_unit_bCanAct);
      [*] = ;   SetGameObjectBoolValueIndByHandle(pfHandle, gc_stack_unit_bCanAct, bValue);
      [*] = ;end;}
      [*] = ;
      [*] = ;//flytext for caster (not done in UnderSpell)
      [*] = ;if (GetIntValueByIndex(gc_stack_unit_iCurrentX) >= 0) and (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   _unit_SetupStatsTextData(myGOHandle, myUID, oldLife, oldStamina, oldMoral);
      [*] = ;   //_unit_CreateFlyTexts(myGOHandle, myUID);
      [*] = ;   //_unit_ModifyVisualParams(myGOHandle, myUID);
      [*] = ;end;
      [*] = ;
      [*] = ;_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategorySpell, spellID, 0);
      [*] = ;
      [*] = ;if bExplicitCast then
      [*] = ;begin
      [*] = ;   var netTargetUID : Integer;
      [*] = ;   if gIntRegister_SacrificeUID <> 0 then
      [*] = ;      netTargetUID := gIntRegister_SacrificeUID
      [*] = ;   else
      [*] = ;   if gIntRegister_TeleportUID <> 0 then
      [*] = ;      netTargetUID := gIntRegister_TeleportUID
      [*] = ;   else
      [*] = ;      netTargetUID := GetGameObjectUniqueIdByHandle(spellTargetGOHandle);
      [*] = ;
      [*] = ;   _inet_CreateOrderParser(myUID, hexX, hexY, gc_inet_actiontype_spell, spellID, 0, netTargetUID, 0, lanOrderRandKey0, lanOrderRandKey1,'CastSpell');
      [*] = ;end;
      [*] = ;
      [*] = ;gIntRegister_SacrificeUID := 0;
      [*] = ;gIntRegister_TeleportUID := 0;
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   _log_battle_Show();
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

