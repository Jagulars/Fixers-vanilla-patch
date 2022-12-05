section.begin
   Name = MakeSabotage
   Description[*] = IntRegister0 - sabotage index
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\GLOBAL.INC\MAKESABOTAGE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;   
      [*] = ;var sabInd : Integer = IntRegister0;
      [*] = ;_gv_traceState(_log_name+'[Index: '+IntToStr(sabInd)+']',_log_trace);
      [*] = ;   
      [*] = ;if (sabInd >= 0) and (sabInd <= 2) then
      [*] = ;begin
      [*] = ;   var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;   
      [*] = ;   var arPrices : array [0..2] of Integer;
      [*] = ;   
      [*] = ;   ExecuteState('GetSabotagePrices');
      [*] = ;   arPrices[0] := IntRegister0;
      [*] = ;   arPrices[1] := IntRegister1;
      [*] = ;   arPrices[2] := IntRegister2;
      [*] = ;   
      [*] = ;   var price : Integer = arPrices[sabInd];
      [*] = ;   
      [*] = ;   if price >= 0 then
      [*] = ;   begin
      [*] = ;      ExecuteState('GetHeroHandle');
      [*] = ;      var heroHandle : Integer = IntRegister0;
      [*] = ;      var heroUID : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID);
      [*] = ;      var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;      if mapHeroHandle <> 0 then
      [*] = ;      begin
      [*] = ;         var mapPlHandle : Integer = GetGameObjectPlayerHandleByHandle(mapHeroHandle);
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   
      [*] = ;         //if plGold >= price then
      [*] = ;         begin
      [*] = ;            plGold := plGold - price;
      [*] = ;            SetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;   
      [*] = ;            IntRegister0 := 24;
      [*] = ;            GameObjectExecuteStateByHandle(mapHeroHandle, 'GetSkillLevel');
      [*] = ;            var skill24 : Integer = IntRegister1;
      [*] = ;   
      [*] = ;            IntRegister0 := 981;
      [*] = ;            GameObjectExecuteStateByHandle(mapHeroHandle, 'CheckAbility');
      [*] = ;            var abil981 : Integer = IntRegister1;
      [*] = ;   
      [*] = ;            if abil981 > 0 then
      [*] = ;              skill24 := skill24 + 1;
      [*] = ;   
      [*] = ;            ExecuteState('GetEnemyPlHandle');
      [*] = ;            var enPlHandle : Integer = IntRegister0;
      [*] = ;   
      [*] = ;            var bVisibleBattle : Boolean = _misc_IsVisibleBattle();
      [*] = ;      
      [*] = ;            var saboteurUID : Integer = GetGameObjectUniqueIdByHandle(heroHandle);
      [*] = ;   
      [*] = ;            var i : Integer;
      [*] = ;            for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;               case sabInd of
      [*] = ;                  0 :
      [*] = ;                  begin
      [*] = ;                     if _unit_CheckAbility(goHandle, gc_ability_tireless) = 0 then
      [*] = ;                     begin
      [*] = ;                        var oldStamina : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurStamina);
      [*] = ;                        var curStamina : Integer = oldStamina - 4 - abil981;
      [*] = ;                        if curStamina < 2 then
      [*] = ;                          curStamina := 2;
      [*] = ;                        SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurStamina, curStamina);
      [*] = ;                        if bVisibleBattle then
      [*] = ;                           _unit_SetupStatsTextData(goHandle, saboteurUID, GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife), oldStamina, GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurMoral));
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  1 :
      [*] = ;                  begin
      [*] = ;                     if _unit_CheckAbility(goHandle, gc_ability_poison_immunity) = 0 then
      [*] = ;                     begin
      [*] = ;                        var power : Integer = 1 + abil981;
      [*] = ;                        var pNewEffect : Integer = _unit_AddEffect(goHandle, 1, -power, gc_PoisonDuration);
      [*] = ;                        ParserSetBoolValueByKeyByHandle(pNewEffect, 'Visible', true);
      [*] = ;                        ParserSetIntValueByKeyByHandle(pNewEffect, 'ParentUpgradeID', 71);
      [*] = ;                        if bVisibleBattle and _obj_EnabledByFlag(gc_ObjectFlagBattleFX) then
      [*] = ;                           _fx_GetOrCreateFXByID(goHandle, 'fxpoisonattack', 0, 0, 0, 0, Random, 5);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  2 :
      [*] = ;                  begin
      [*] = ;                     if _unit_CheckAbility(goHandle, gc_ability_fearless) = 0 then
      [*] = ;                     begin
      [*] = ;                        var oldMoral : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurMoral);
      [*] = ;                        var curMoral : Integer = oldMoral - 4 - abil981;
      [*] = ;                        if curMoral < 1 then
      [*] = ;                          curMoral := 1;
      [*] = ;                        SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurMoral, curMoral);
      [*] = ;                        if bVisibleBattle then
      [*] = ;                           _unit_SetupStatsTextData(goHandle, saboteurUID, GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife), GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurStamina), oldMoral);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if bVisibleBattle then
      [*] = ;               GameObjectExecuteStateByHandle(heroHandle, 'ApplyAllVisualParams');
      [*] = ;            
      [*] = ;            var bTargetIOplayer : Boolean = (enPlHandle = GetPlayerHandleInterfaceIO);
      [*] = ;            if gBoolRegister_IsHumanPlayer and bTargetIOplayer and (_misc_IsLanBattle or SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC')) then
      [*] = ;            begin
      [*] = ;               var queryID : Integer = 0;
      [*] = ;               case sabInd of 
      [*] = ;                  0 : queryID := gc_gui_query_heroEnemyMakeFalseAlarm;
      [*] = ;                  1 : queryID := gc_gui_query_heroEnemyMakePoisonedWater;
      [*] = ;                  2 : queryID := gc_gui_query_heroEnemyMakePanic;
      [*] = ;               end;
      [*] = ;   
      [*] = ;               StringRegister0 := IntToStr(queryID);
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;   
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
