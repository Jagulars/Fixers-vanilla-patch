section.begin
   Name = ShowNecromancy
   Description : struct.begin
      [*] = ;BoolRegister0 - is first call
      [*] = ;BoolRegister1 - reset data
      [*] = ;OUT: BoolRegister2 - is window showed
   struct.end
   Code : struct.begin
      [*] = ;var firstCall : Boolean = BoolRegister0;
      [*] = ;var resetData : Boolean = BoolRegister1;
      [*] = ;
      [*] = ;var _log_name : String = 'GUI.INC\SHOWNECROMANCY';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;const cEventState = 'EventNecromancy';
      [*] = ;const cBtnClose = 101;
      [*] = ;const cBtnHeroInfo = 102;
      [*] = ;const cRitualBase = 110;
      [*] = ;const cBtnScrollDownBaseTag = 200;
      [*] = ;const cBtnUnitSlotBaseTag = 300;
      [*] = ;
      [*] = ;var showNecro : Boolean = false;
      [*] = ;
      [*] = ;MapExecuteState('bat.GetWinPlayerHandle');
      [*] = ;var winPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;if winPlHandle <> 0 then
      [*] = ;begin
      [*] = ;   PlayerExecuteStateByHandle(winPlHandle, 'GetHeroHandle');
      [*] = ;   var heroHandle : Integer = IntRegister0;
      [*] = ;   var curLife : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iCurLife);
      [*] = ;   var uid : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID);
      [*] = ;   var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(winPlHandle, 'GetMapPlayerHandle');
      [*] = ;   var mapPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   BoolRegister0 := resetData;
      [*] = ;   PlayerExecuteStateByHandle(winPlHandle, 'FillNecromancyInfo');
      [*] = ;   showNecro := BoolRegister1;
      [*] = ;
      [*] = ;   if showNecro or (not firstCall) then
      [*] = ;   begin
      [*] = ;      var fontHandle, fontHandle2, fontHandle3: String;
      [*] = ;      _gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_small,'',fontHandle);
      [*] = ;      _gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;      _gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_large,'',fontHandle3);
      [*] = ;
      [*] = ;      // Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;      var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('necromancy', _gui_GetLayerI());
      [*] = ;      var bVisible : Boolean = False;
      [*] = ;      if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;      bVisible := True;
      [*] = ;
      [*] = ;      var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'necromancy', 'halParentMiddle', 'valParentMiddle', 0, 0, 507, 438, true);
      [*] = ;      SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.85);
      [*] = ;      SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.85);
      [*] = ;      var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;      var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, 'message|17', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle3, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      var elmHandle : Integer;
      [*] = ;
      [*] = ;      var text : String = GetLocaleTableListItemByID('message', '17.description');
      [*] = ;      var cFontSize : String = fontHandle2;
      [*] = ;      const textPadding = 5;
      [*] = ;      var tWidth : Integer = 456-16;
      [*] = ;      text := GetGUIWrappedTextFormatByFont(cFontSize, text, tWidth-textPadding*2);
      [*] = ;      var width, height : Integer = 0;
      [*] = ;      GetGUIElementFontTextFormatRect(cFontSize, text, width, height);
      [*] = ;
      [*] = ;      elmHandle := _gui_CreateFrameBorder('', elmParentHandle, 'halParentLeft', 'valParentTop', 28, 34, tWidth+textPadding*2, 60+textPadding*2);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmHandle, text, 'halParentLeft', 'valParentTop', textPadding, textPadding, width, height, 'halLeft', 'valTop', cFontSize, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;      var plGem : Integer = GetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;      var i : Integer;
      [*] = ;
      [*] = ;      for i := 0 to gc_NecromancySlots-1 do
      [*] = ;      begin
      [*] = ;         var posX : Integer = 28;
      [*] = ;         var posY : Integer = 124;
      [*] = ;         var unitID : Integer = arrNecroInfo[i].unitID;
      [*] = ;         var unitCount : Integer = arrNecroInfo[i].count;
      [*] = ;
      [*] = ;         var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;         var goldPrice : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'GoldPrice');
      [*] = ;         var gemCost : Integer = goldPrice div 2;
      [*] = ;         var elmNecroHandle : Integer = _gui_CreateImage('', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX+i*95, posY, 0, 70, 0);
      [*] = ;         elmHandle := _gui_CreateImage('', elmNecroHandle, 'astral.bonus.unit.frame', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;         var tag : Integer = cBtnUnitSlotBaseTag+i;
      [*] = ;
      [*] = ;         if (unitCount>0) then
      [*] = ;         begin
      [*] = ;            // Stats start
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByIndex(arrNecroInfo[i].curIndex, winPlHandle);
      [*] = ;            const cStatOffsetX = -6;
      [*] = ;            const cStatOffsetY = -9;
      [*] = ;
      [*] = ;            elmHandle := _gui_CreateImage('', elmNecroHandle, 'icon.unit.'+IntToStr(unitID), 'halParentLeft', 'valParentTop', 0, 0, 70, 93, 0);
      [*] = ;            var elmBtnHandle : Integer = _gui_CreateButton('necrounit', elmNecroHandle, '', 'heropanel.unit.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 70, 93, '', '', 0);
      [*] = ;            _gui_ft_AttachHint_I6(elmBtnHandle,'VVK.FTooltipUnit',cFT_UnitBattle,GetGameObjectUniqueIdByHandle(goHandle),0,0,4,4); // right button - battle mode
      [*] = ;
      [*] = ;            //Life meter
      [*] = ;            IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;            var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;            IntRegister0 := gc_battle_unit_iCurLife;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;            var curLife : Integer = IntRegister1;
      [*] = ;            var sizeX : Integer = 3;
      [*] = ;            var sizeY : Integer = round(70*(curLife/maxLife));
      [*] = ;            posX := 7+1+cStatOffsetX;
      [*] = ;            posY := -28+40+cStatOffsetY;
      [*] = ;            elmHandle := _gui_CreateImage('', elmNecroHandle, 'battle.results.meter.life', 'halParentLeft', 'valParentBottomHeight', posX, posY, sizeX, sizeY, Tag);
      [*] = ;            if (sizeY<=0) then
      [*] = ;               SetGUIElementVisible(elmHandle, False);
      [*] = ;            elmHandle := _gui_CreateImage('battle_result_unit_life_meter', elmNecroHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', posX-1, posY, sizeX+2, sizeY, Tag);
      [*] = ;            //SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;
      [*] = ;            var unitLevel : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLevel);
      [*] = ;            var minExp : Integer = 0;
      [*] = ;            var maxExp : Integer = 0;
      [*] = ;
      [*] = ;            IntRegister0 := unitID;
      [*] = ;            IntRegister1 := unitLevel;
      [*] = ;            MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;            minExp := IntRegister2;
      [*] = ;
      [*] = ;            IntRegister0 := unitID;
      [*] = ;            IntRegister1 := unitLevel+1;
      [*] = ;            MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;            maxExp := IntRegister2;
      [*] = ;
      [*] = ;            var curExp : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iExperience);
      [*] = ;            if (curExp>maxExp) then
      [*] = ;               curExp := maxExp;
      [*] = ;            var expPerc : Float = (curExp-minExp)/(maxExp-minExp);
      [*] = ;
      [*] = ;            //Exp meter
      [*] = ;            posX := 72-1+cStatOffsetX;
      [*] = ;            posY := -28+40+cStatOffsetY;
      [*] = ;            sizeX := 3;
      [*] = ;            sizeY := round(70*expPerc);
      [*] = ;            elmHandle := _gui_CreateImage('', elmNecroHandle, 'battle.results.meter.exp', 'halParentLeft', 'valParentBottomHeight', posX, posY, sizeX, sizeY, Tag);
      [*] = ;            if (sizeY<=0) then
      [*] = ;               SetGUIElementVisible(elmHandle, False);
      [*] = ;            elmHandle := _gui_CreateImage('battle_result_unit_exp_meter', elmNecroHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', posX-1, posY, sizeX+2, sizeY, Tag);
      [*] = ;            //SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;            //Meters background
      [*] = ;            posX := -1+5+cStatOffsetX;
      [*] = ;            posY := 2+6+cStatOffsetY;
      [*] = ;            elmHandle := _gui_CreateImage('', elmNecroHandle, 'battle.results.meter.background.enemy', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, Tag);
      [*] = ;            //SetGUIAllowEvents(elmHandle, False, False, False);
      [*] = ;
      [*] = ;            //Unit level
      [*] = ;            text := IntToStr(unitLevel);
      [*] = ;            posX := 54-1+cStatOffsetX;
      [*] = ;            posY := 85-4+cStatOffsetY;
      [*] = ;            elmTextHandle := _gui_CreateText('battle_result_unit_level', elmNecroHandle, text, 'halParentLeft', 'valParentTop', posX-1, posY-3, 22, 22, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;            //SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;            // Stats finish
      [*] = ;         end;
      [*] = ;
      [*] = ;         elmHandle := _gui_CreateImage('', elmNecroHandle, 'astral.bonus.unit.energycost.cover', 'halParentLeft', 'valParentTop', -4, 95, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateImage('', elmNecroHandle, 'icon.gem.28x28', 'halParentLeft', 'valParentTop', 3, 95, 0, 0, 0);
      [*] = ;         if (unitCount>0) then
      [*] = ;         begin
      [*] = ;            SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;            elmTextHandle := _gui_CreateText('', elmNecroHandle, IntToStr(gemCost), 'halParentLeft', 'valParentTop', 26, 99, 36, 21, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.25);
      [*] = ;
      [*] = ;         if i = 0 then
      [*] = ;            IntRegister0 := 1
      [*] = ;         else
      [*] = ;            IntRegister0 := i;
      [*] = ;         GameObjectExecuteStateByHandle(mapHeroHandle, 'GetFreeUnitSlot');
      [*] = ;         var slotRank : Integer = IntRegister1;
      [*] = ;         var slotIndex : Integer = IntRegister2;
      [*] = ;
      [*] = ;         tag := cRitualBase + i;
      [*] = ;         var elmBtnHandle : Integer = _gui_CreateButton('necrohire', elmNecroHandle, '', 'gamepanel02.btn.magic', 'halParentLeft', 'valParentTop', 10, 126, 0, 0, cEventState, 'gui|95', tag);
      [*] = ;         if (unitCount = 0) or (gemCost > plGem) or (slotRank <= 0) then
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;         tag := cBtnScrollDownBaseTag+i;
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmNecroHandle, '', 'common.scroller.down', 'halParentLeft', 'valParentTop', 14, 178, 0, 0, cEventState, 'gui|321', tag);
      [*] = ;         if (unitCount<2) or (gemCost>plGem) then
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      elmHandle := _gui_CreateImage('', elmParentHandle, 'map.infopanel.crystals'{'astral.gem.icon.47x50'}, 'halParentLeft', 'valParentTop', 88, 359, 0, 0, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmParentHandle, IntToStr(plGem), 'halParentLeft', 'valParentTop', 88+44, 359+7, 48, 36, 'halLeft', 'valMiddle', fontHandle3, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('', elmParentHandle, '', 'map.castle.tabs.btn.hero', 'halParentLeft', 'valParentTop', 374, 356, 49, 49, cEventState, 'gui|146', cBtnHeroInfo);
      [*] = ;      elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 0, -32, 0, 0, 0);
      [*] = ;      elmBtnHandle := _gui_CreateButton('btnCancel', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'menu|47', cBtnClose);
      [*] = ;
      [*] = ;      _gui_RootWindowAdd(elmParentHandle,cRootWindowModal);
      [*] = ;      SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;
      [*] = ;      if (not bVisible) and (gIntRegister_CurGameMode = gc_GameModeStrategy) then
      [*] = ;         _gv_SetMapLock(1,_log_name);
      [*] = ;
      [*] = ;      var elmBlinkElement : Integer = _gui_GetWindow('blinker_top.blink_battle_endturn');
      [*] = ;      if (elmBlinkElement<>0) then
      [*] = ;         RemoveGUIElement(elmBlinkElement);
      [*] = ;
      [*] = ;      GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;BoolRegister2 := showNecro;
   struct.end
section.end

