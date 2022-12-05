section.begin
   Name = EventNecromancy
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\EVENTNECROMANCY';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;const cBtnClose = 101;
      [*] = ;const cBtnHeroInfo = 102;
      [*] = ;const cRitualBase = 110;
      [*] = ;const cBtnScrollDownBaseTag = 200;
      [*] = ;const cBtnUnitSlotBaseTag = 300;
      [*] = ;
      [*] = ;MapExecuteState('bat.GetWinPlayerHandle');
      [*] = ;var winPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      cBtnScrollDownBaseTag..cBtnScrollDownBaseTag+gc_NecromancySlots-1 : begin
      [*] = ;         var slotInd : Integer = tag-cBtnScrollDownBaseTag;
      [*] = ;
      [*] = ;         IntRegister0 := slotInd + 1;
      [*] = ;         IntRegister1 := arrNecroInfo[slotInd].curIndex + 1;
      [*] = ;         PlayerExecuteStateByHandle(winPlHandle, 'FindNecromancyUnit');
      [*] = ;         var ind : Integer = IntRegister2;
      [*] = ;
      [*] = ;         arrNecroInfo[tag-cBtnScrollDownBaseTag].curIndex := ind;
      [*] = ;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         BoolRegister1 := false;
      [*] = ;         GUIExecuteState('ShowNecromancy');
      [*] = ;      end;
      [*] = ;      cBtnClose, gc_gui_hotkey_btnEnter, gc_gui_hotkey_btnEscape : begin
      [*] = ;         if (gIntRegister_CurGameMode = gc_GameModeStrategy) then
      [*] = ;            _gv_SetMapLock(-1,_log_name);
      [*] = ;
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('necromancy'),gc_gui_FadeTime0_2);
      [*] = ;         GUIExecuteState('battle.CheckSiteLootWindow');
      [*] = ;      end;
      [*] = ;      cBtnHeroInfo : begin
      [*] = ;         PlayerExecuteStateByHandle(winPlHandle, 'GetHeroHandle');
      [*] = ;         var heroHandle : Integer = IntRegister0;
      [*] = ;         if (heroHandle=0) then
      [*] = ;         ErrorLog('EventNecromancy : real error : map heroHandle=0');
      [*] = ;         var mapHeroUID : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID);
      [*] = ;         gIntRegister_GUIActiveHeroUID1 := mapHeroUID;
      [*] = ;         gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;         gIntRegister_GUICurHeroMode := gc_HeroPanelBothPanels;
      [*] = ;         GUIExecuteState('map.CreateHeroWindow');
      [*] = ;      end;
      [*] = ;      cRitualBase..cRitualBase+gc_NecromancySlots-1 : begin
      [*] = ;         PlayerExecuteStateByHandle(winPlHandle, 'GetMapPlayerHandle');
      [*] = ;         var mapPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;         var ind : Integer = arrNecroInfo[tag-cRitualBase].curIndex;
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(ind, winPlHandle);
      [*] = ;         var uid : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;
      [*] = ;         IntRegister0 := uid;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         PlayerExecuteStateByHandle(mapPlHandle, 'DoNecromancy');
      [*] = ;         // achiev
      [*] = ;         _achievement_Trigger(gc_achiev_undead_50,'');
      [*] = ;         //
      [*] = ;         BoolRegister0 := false;
      [*] = ;         BoolRegister1 := true;
      [*] = ;         GUIExecuteState('ShowNecromancy');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

