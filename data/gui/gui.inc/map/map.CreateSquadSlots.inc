section.begin
   Name = map.CreateSquadSlots
   Description : struct.begin
      [*] = ;IntRegister0 - hero handle
      [*] = ;IntRegister1 - province handle
      [*] = ;IntRegister2 - mode and attr
      [*] = ;   &0xff  - 0 - display province garrison
      [*] = ;          - 1 - display hero army
      [*] = ;   &0x100 - display astral energy price for unit
      [*] = ;IntRegister3 - parent handle
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CREATESQUADSLOTS';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;
      [*] = ;function GetSlotUnitParser(goHandle, panelType, slotRank, slotIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var GetSlotStateName : String;
      [*] = ;   if (panelType=0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;      MapExecuteState('GetProvinceParserByUID');
      [*] = ;      var pProvince : Integer = IntRegister1;
      [*] = ;      var pGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;      IntRegister0 := pGarrison;
      [*] = ;      IntRegister1 := slotRank;
      [*] = ;      IntRegister2 := slotIndex;
      [*] = ;      MapExecuteState('map.GetGarrisonSlotUnit');
      [*] = ;      Result := IntRegister3;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := slotRank;
      [*] = ;      IntRegister1 := slotIndex;
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetSlotUnit');
      [*] = ;      Result := IntRegister2;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateUnitMeters(elmParentHandle, goHeroHnd, pGOParser, pArmyUnits, buildMoraleMod : Integer);
      [*] = ;begin
      [*] = ;   var unitID : Integer = ParserGetIntValueByKeyByHandle(pGOParser, 'UnitID');
      [*] = ;
      [*] = ;   //Life meter
      [*] = ;   var posX : Integer = 2;
      [*] = ;   var posY : Integer = -19;
      [*] = ;   IntRegister0 := pGOParser;
      [*] = ;   IntRegister1 := pArmyUnits;
      [*] = ;   IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;   MapExecuteState('GetUnitPropertyByParser');
      [*] = ;   var maxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;   IntRegister0 := pGOParser;
      [*] = ;   IntRegister1 := pArmyUnits;
      [*] = ;   IntRegister2 := gc_battle_unit_iCurLife;
      [*] = ;   MapExecuteState('GetUnitPropertyByParser');
      [*] = ;   var curLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;   var sizeX : Integer = 3;
      [*] = ;   var sizeY : Integer = round(70*(curLife/maxLife));
      [*] = ;   if (sizeY>70) then
      [*] = ;      sizeY := 70;
      [*] = ;   var tag : Integer = 0;
      [*] = ;   var elmImageHandle : Integer = _gui_CreateImage('', elmParentHandle, 'battle.results.meter.life', 'halParentLeft', 'valParentBottomHeight', posX, posY, sizeX, sizeY, Tag);
      [*] = ;   if (sizeY<=0) then
      [*] = ;      SetGUIElementVisible(elmImageHandle, False);
      [*] = ;   //elmImageHandle := _gui_CreateImage('battle_result_unit_life_meter', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', posX-1, posY, sizeX+2, 70, Tag);
      [*] = ;   //SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('battle_result_unit_life_meter', elmParentHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', posX-1, posY, sizeX+2, 70, '', '', Tag);
      [*] = ;   SetGUIElementTag(elmBtnHandle, GetGUIElementTag(elmParentHandle));
      [*] = ;   SetGUIElementPressState(elmBtnHandle, GetGUIElementPressState(elmParentHandle));
      [*] = ;   SetGUIElementStringTag(elmBtnHandle, GetGUIElementStringTag(elmParentHandle));
      [*] = ;
      [*] = ;   var unitLevel : Integer = ParserGetIntValueByKeyByHandle(pGOParser, 'Level');
      [*] = ;
      [*] = ;   // Exp bar
      [*] = ;   IntRegister0 := unitID;
      [*] = ;   IntRegister1 := unitLevel;
      [*] = ;   MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;   var minExp : Integer = IntRegister2;
      [*] = ;   IntRegister0 := unitID;
      [*] = ;   IntRegister1 := unitLevel+1;
      [*] = ;   MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;   var maxExp : Integer = IntRegister2;
      [*] = ;   var curExp : Integer = 0;
      [*] = ;   curExp := ParserGetIntValueByKeyByHandle(pGOParser, 'Exp');
      [*] = ;   if (curExp>maxExp) then
      [*] = ;      curExp := maxExp;
      [*] = ;   var expPerc : Float = (curExp-minExp)/(maxExp-minExp);
      [*] = ;   if (expPerc>1) then
      [*] = ;      expPerc := 1;
      [*] = ;
      [*] = ;   //Exp meter
      [*] = ;   posX := 66-1;
      [*] = ;   posY := -19;
      [*] = ;   sizeX := 3;
      [*] = ;   sizeY := round(70*expPerc);
      [*] = ;   elmImageHandle := _gui_CreateImage('', elmParentHandle, 'battle.results.meter.exp', 'halParentLeft', 'valParentBottomHeight', posX, posY, sizeX, sizeY, Tag);
      [*] = ;   if (sizeY<=0) then
      [*] = ;      SetGUIElementVisible(elmImageHandle, False);
      [*] = ;   //elmImageHandle := _gui_CreateImage('battle_result_unit_exp_meter', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', posX-1, posY, sizeX+2, sizeY, Tag);
      [*] = ;   //SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   elmBtnHandle := _gui_CreateButton('battle_result_unit_exp_meter', elmParentHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', posX-1, posY, sizeX+2, 70, '', '', Tag);
      [*] = ;   SetGUIElementTag(elmBtnHandle, GetGUIElementTag(elmParentHandle));
      [*] = ;   SetGUIElementPressState(elmBtnHandle, GetGUIElementPressState(elmParentHandle));
      [*] = ;   SetGUIElementStringTag(elmBtnHandle, GetGUIElementStringTag(elmParentHandle));
      [*] = ;
      [*] = ;   //Meters background
      [*] = ;   posX := -7+5;
      [*] = ;   posY := -7+6;
      [*] = ;   elmImageHandle := _gui_CreateImage('', elmParentHandle, 'battle.results.meter.background.enemy', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, Tag);
      [*] = ;   //SetGUIAllowEvents(elmImageHandle, False, False, False);
      [*] = ;
      [*] = ;   //Unit level
      [*] = ;   var fontHandleN : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_strategy,'Numbers',gc_gui_fontsize_default,'',fontHandleN);
      [*] = ;
      [*] = ;   var text : String = IntToStr(unitLevel);
      [*] = ;   posX := 48-1;
      [*] = ;   posY := 79-6;
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('battle_result_unit_level', elmParentHandle, text, 'halParentLeft', 'valParentTop', posX-3, posY-3, 22, 22, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;   //SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;   elmBtnHandle := _gui_CreateButton('battle_result_unit_level', elmParentHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX-1, posY, 22, 22, '', '', Tag);
      [*] = ;   SetGUIElementTag(elmBtnHandle, GetGUIElementTag(elmParentHandle));
      [*] = ;   SetGUIElementPressState(elmBtnHandle, GetGUIElementPressState(elmParentHandle));
      [*] = ;   SetGUIElementStringTag(elmBtnHandle, GetGUIElementStringTag(elmParentHandle));
      [*] = ;
      [*] = ;   //Medal icons
      [*] = ;   var pUnitMedals : Integer = ParserSelectByHandleByKey(pGOParser, 'Medals');
      [*] = ;   posX := 27;
      [*] = ;   posY := 75;
      [*] = ;   var xOff : Integer = -15;
      [*] = ;   var i, ind : Integer;
      [*] = ;   ind := 0;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pUnitMedals)-1 do
      [*] = ;   begin
      [*] = ;      var pUnitMedal : Integer = ParserSelectByHandleByIndex(pUnitMedals, i);
      [*] = ;      var medalID : Integer = ParserGetIntValueByKeyByHandle(pUnitMedal, 'MedalID');
      [*] = ;      //if medalID = 6 then
      [*] = ;      //begin
      [*] = ;      //   elmImageHandle := _gui_CreateImage('', elmParentHandle, 'icon.medal.'+IntToStr(medalID), 'halParentRight', 'valParentTop', 20, 4, 20, 20, Tag);
      [*] = ;     // end
      [*] = ;      //else
      [*] = ;      begin
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmParentHandle, 'icon.medal.'+IntToStr(medalID), 'halParentLeft', 'valParentTop', posX+ind*xOff, posY, 20, 20, Tag);
      [*] = ;         ind := ind + 1;
      [*] = ;      end;
      [*] = ;      //var elmBtnHandle : Integer = _gui_CreateButton('', elmImageHandle, '', 'icons.round.44x44.cover', 'halParentLeft', 'valParentTop', -4, -6, (45-9), (47-9), '', hint, tag);
      [*] = ;      //_gui_ft_AttachTooltip_I1(elmBtnHandle,'VVK.HintUnitMedalsCallback',medalID);
      [*] = ;      //SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'icons.round.44x44.cover' + '.pressed', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   //Morale mods
      [*] = ;   var pIndex : Integer = ParserGetIndexOf(pGOParser);
      [*] = ;   IntRegister0 := pArmyUnits;
      [*] = ;   IntRegister1 := pIndex;
      [*] = ;   IntRegister2 := goHeroHnd;
      [*] = ;   MapExecuteState('GetUnitArmyMoralBonus');
      [*] = ;   var moralMod : Integer = IntRegister3 + buildMoraleMod;
      [*] = ;   if (moralMod<>0) then
      [*] = ;   begin
      [*] = ;      if (moralMod>0) then
      [*] = ;         text := '+'+IntToStr(moralMod)
      [*] = ;      else
      [*] = ;         text := IntToStr(moralMod);
      [*] = ;      var w, h : Integer;
      [*] = ;      GetGUIElementFontTextFormatRect(fontHandleN, text, w, h);
      [*] = ;      //elmImageHandle := _gui_CreateImage('', elmParentHandle, 'misc.blank.black.alpha.1', 'halParentLeft', 'valParentTop', Floor(GetgDbgFloat0), Floor(GetgDbgFloat1), w, h, 0);
      [*] = ;      if w<12 then
      [*] = ;         w := 12;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmParentHandle, 'misc.blank.black.alpha.1', 'halParentLeft', 'valParentTop', 5, 4, w+3, h, 0);
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.6);
      [*] = ;      //elmImageHandle := _gui_CreateImage('', elmParentHandle, 'misc.blank.black.alpha.0.25', 'halParentLeft', 'valParentTop', 5, 4, w+2, h, 0);
      [*] = ;      //elmImageHandle := _gui_CreateImage('', elmParentHandle, 'misc.blank.black.alpha.0.25', 'halParentLeft', 'valParentTop', 5, 4, w+2, h, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmParentHandle, text, 'halParentLeft', 'valParentTop', 6, 5, w+2, h{22, 22}, 'halMiddle', 'valMiddle', fontHandleN, 0.125, 0.5, 1, 1);
      [*] = ;      //SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;
      [*] = ;      elmBtnHandle := _gui_CreateButton('battle_result_moral_mod', elmParentHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 5, 4, w+3, h, '', '', Tag);
      [*] = ;      SetGUIElementTag(elmBtnHandle, GetGUIElementTag(elmParentHandle));
      [*] = ;      SetGUIElementPressState(elmBtnHandle, GetGUIElementPressState(elmParentHandle));
      [*] = ;      SetGUIElementStringTag(elmBtnHandle, GetGUIElementStringTag(elmParentHandle));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var goHeroHnd : Integer = IntRegister0;
      [*] = ;var goProvHnd : Integer = IntRegister1;
      [*] = ;var panelType : Integer = IntRegister2;
      [*] = ;var panelAttr : Integer;
      [*] = ;var parentHandle : Integer = IntRegister3;
      [*] = ;var selSlotHeroHnd : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedSlotHeroUID);
      [*] = ;var selSlotRank, selSlotIndex, selUnitRank : Integer = 0;
      [*] = ;var pickedUnitRank : Integer = 0;
      [*] = ;var pSelSlotUnit : Integer;
      [*] = ;var slotPressState : String;
      [*] = ;var dismissBtnTag,build_morale : Integer;
      [*] = ;var i : Integer;
      [*] = ;var elmImageHandle, elmBtnHandle : Integer;
      [*] = ;var maxRankInd : Integer;
      [*] = ;PlayerExecuteStateByHandle(GetGameObjectPlayerHandleByHandle(goHeroHnd), 'GetCastleParser');
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(IntRegister0, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;IntRegister0 := 24;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuildAbility');
      [*] = ;var mercMarket : Integer = IntRegister1;
      [*] = ;var pUnits : Integer = ParserSelectGameObject(goHeroHnd);
      [*] = ;pUnits := ParserSelectByHandleByKey(pUnits, 'Units');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(panelType)+']',_log_trace);
      [*] = ;
      [*] = ;panelAttr := (panelType and $ff00) shr 8;
      [*] = ;panelType := panelType and $ff ;
      [*] = ;build_morale := 0;
      [*] = ;if (panelType=0) then
      [*] = ;begin
      [*] = ;   slotPressState := 'map.PressGarrisonSlot';
      [*] = ;   dismissBtnTag := gc_gui_garrisonpanel_btnDismiss;
      [*] = ;   if goProvHnd <> 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 19; // buildings morale
      [*] = ;      GameObjectExecuteStateByHandle(goProvHnd, 'CheckInnerBuildAbility');
      [*] = ;      build_morale := IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := 10; // buildings morale
      [*] = ;      GameObjectExecuteStateByHandle(goProvHnd, 'CheckOuterBuildAbility');
      [*] = ;      build_morale := build_morale + IntRegister2;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   slotPressState := 'map.PressUnitSlot';
      [*] = ;   dismissBtnTag := gc_gui_unitpanel_btnDismiss;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_MapSelectedUnitSlot<>0) and (selSlotHeroHnd<>0) then
      [*] = ;begin
      [*] = ;   selSlotRank := gIntRegister_MapSelectedUnitSlot div 10;
      [*] = ;   selSlotIndex := gIntRegister_MapSelectedUnitSlot mod 10;
      [*] = ;
      [*] = ;   //pSelSlotUnit := GetSlotUnitParser(goHandle, goHandleType, selSlotRank, selSlotIndex);
      [*] = ;   pSelSlotUnit := GetSlotUnitParser(selSlotHeroHnd, 1, selSlotRank, selSlotIndex);
      [*] = ;   selUnitRank := ParserGetIntValueByKeyByHandle(_unit_GetUnitParserByID(ParserGetIntValueByKeyByHandle(pSelSlotUnit, 'unitID')), 'Rank');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (gIntRegister_MapSelectedGarrisonUnitSlot<>0) then
      [*] = ;   begin
      [*] = ;      selSlotRank := gIntRegister_MapSelectedGarrisonUnitSlot div 10;
      [*] = ;      selSlotIndex := gIntRegister_MapSelectedGarrisonUnitSlot mod 10;
      [*] = ;
      [*] = ;      //pSelSlotUnit := GetSlotUnitParser(goHandle, goHandleType, selSlotRank, selSlotIndex);
      [*] = ;      pSelSlotUnit := GetSlotUnitParser(goProvHnd, 0, selSlotRank, selSlotIndex);
      [*] = ;      selUnitRank := ParserGetIntValueByKeyByHandle(_unit_GetUnitParserByID(ParserGetIntValueByKeyByHandle(pSelSlotUnit, 'unitID')), 'Rank');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (gIntRegister_MapPickedUnitID<>0) then
      [*] = ;      begin
      [*] = ;         pickedUnitRank := ParserGetIntValueByKeyByHandle(_unit_GetUnitParserByID(gIntRegister_MapPickedUnitID), 'Rank');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUICurHeroMode=gc_HeroPanelExtraUnit) then
      [*] = ;   maxRankInd := 4
      [*] = ;else
      [*] = ;   maxRankInd := 3;
      [*] = ;
      [*] = ;for i:=0 to maxRankInd do // 5th rank is temporary for no space unit add
      [*] = ;begin
      [*] = ;   var slotCount : Integer;
      [*] = ;   case i of
      [*] = ;      0 : slotCount := 6;
      [*] = ;      1 : slotCount := 4;
      [*] = ;      2 : slotCount := 3;
      [*] = ;      3 : slotCount := 2;
      [*] = ;      4 : slotCount := 1; // 5th rank is temporary for no space unit add
      [*] = ;   end;
      [*] = ;
      [*] = ;   var j : Integer;
      [*] = ;   for j:=0 to slotCount-1 do
      [*] = ;   begin
      [*] = ;      var openSlots : Integer;
      [*] = ;      var rank : Integer = i+1;
      [*] = ;
      [*] = ;      var pGarrisonSlots, pGarrisonUnits : Integer = 0;
      [*] = ;      if (panelType=0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := GetGameObjectUniqueIdByHandle(goProvHnd);
      [*] = ;         MapExecuteState('GetProvinceParserByUID');
      [*] = ;         var pProvince : Integer = IntRegister1;
      [*] = ;         var pGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;         pGarrisonUnits := ParserSelectByHandleByKey(pGarrison, 'Units');
      [*] = ;         pGarrisonSlots := ParserSelectByHandleByKey(pGarrison, 'Slots');
      [*] = ;         openSlots := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGarrisonSlots, rank-1), 'Count');
      [*] = ;         //_log_Values('RANK|PROV|SLOT|NO',i,pProvince,pGarrisonSlot,openSlots,0,0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := rank;
      [*] = ;         GameObjectExecuteStateByHandle(goHeroHnd, 'GetUnitSlots');
      [*] = ;         openSlots := IntRegister1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var posX, posY : Integer;
      [*] = ;      if (rank=5) then
      [*] = ;      begin
      [*] = ;         posX := -213+305;
      [*] = ;         posY := -186-259;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         posX := -213+j*74+1;
      [*] = ;         posY := -186-i*97+1;
      [*] = ;      end;
      [*] = ;      if ((panelType=0) and (goHeroHnd=0)) or ((gIntRegister_GUICurCastleMode>0) and panelType=0) then
      [*] = ;         posX := posX-1;
      [*] = ;      if ((j+1)<=slotCount) then
      [*] = ;      begin
      [*] = ;         var matBlank : String = 'misc.blank.black.alpha.0';
      [*] = ;
      [*] = ;         var pSlotUnit : Integer;
      [*] = ;         if (panelType=0) then
      [*] = ;            pSlotUnit := GetSlotUnitParser(goProvHnd, panelType, rank, j)
      [*] = ;         else
      [*] = ;            pSlotUnit := GetSlotUnitParser(goHeroHnd, panelType, rank, j);
      [*] = ;         var unitID : Integer = ParserGetIntValueByKeyByHandle(pSlotUnit, 'unitID');
      [*] = ;         if ((j+1)<=openSlots) or ((rank=5) and (gIntRegister_GUICurHeroMode=gc_HeroPanelExtraUnit)) or (unitID<>0) then
      [*] = ;         begin
      [*] = ;            var pUnitID : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;            var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnitID, 'Rank');
      [*] = ;
      [*] = ;            var elmSlotHandle : Integer;
      [*] = ;            var swapAvailable : Boolean = True;
      [*] = ;            if (selSlotRank<unitRank) then
      [*] = ;               swapAvailable := False;
      [*] = ;
      [*] = ;            var highlight : Boolean = False;
      [*] = ;            var disabled : Boolean = False;
      [*] = ;            var checkon : Boolean = False;
      [*] = ;
      [*] = ;            if (gIntRegister_MapSelectedUnitSlot<>0) and (panelType=1) then
      [*] = ;            begin
      [*] = ;               if (rank=selSlotRank) and (j=selSlotIndex) and (selSlotHeroHnd=goHeroHnd) then
      [*] = ;                  checkon := True;
      [*] = ;
      [*] = ;               if (selUnitRank<>0) and (rank>=selUnitRank) and (swapAvailable) then
      [*] = ;                  highlight := True
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (gIntRegister_MapSelectedGarrisonUnitSlot<>0) and (panelType=0) then
      [*] = ;            begin
      [*] = ;               if (rank=selSlotRank) and (j=selSlotIndex) then
      [*] = ;                  checkon := True;
      [*] = ;
      [*] = ;               if (selUnitRank<>0) and (rank>=selUnitRank) and (swapAvailable) then
      [*] = ;                  highlight := True
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (pickedUnitRank<>0) then
      [*] = ;            begin
      [*] = ;               if (rank>=pickedUnitRank) and (unitID=0) then
      [*] = ;                  highlight := True
      [*] = ;               else
      [*] = ;                  disabled := True;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (selUnitRank<>0) then
      [*] = ;               begin
      [*] = ;                  if (rank>=selUnitRank) and (swapAvailable) then
      [*] = ;                     highlight := True
      [*] = ;                  else
      [*] = ;                     disabled := True;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            //if (selUnitRank=0) and (pickedUnitRank=0) then
      [*] = ;            elmSlotHandle := _gui_CreateImageSimple('open_'+IntToStr(i)+'_'+IntToStr(j), parentHandle, {matBlank}'heropanel.unit.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'astral.bonus.unit.frame', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;
      [*] = ;            var tag : Integer = gc_gui_hero_unitslots_btnBaseTag + 10 * rank + j;
      [*] = ;            var slotHeroUID : Integer = GetGameObjectUniqueIdByHandle(goHeroHnd);
      [*] = ;            if (pSlotUnit<>0) and (unitID<>0) then
      [*] = ;            begin
      [*] = ;               var pArmyParser : Integer;
      [*] = ;
      [*] = ;               IntRegister0 := pSlotUnit;
      [*] = ;               IntRegister1 := pUnits;
      [*] = ;               IntRegister2 := gc_battle_unit_iCurLife;
      [*] = ;               MapExecuteState('GetUnitPropertyByParser');
      [*] = ;               var bDead : Boolean = (IntRegister3 <= 0);
      [*] = ;
      [*] = ;               // portrait
      [*] = ;               elmImageHandle := _gui_CreateImage('icon', elmSlotHandle, 'icon.unit.'+IntToStr(unitID), 'halParentLeft', 'valParentTop', 0, 0, 70, 93, Tag);
      [*] = ;
      [*] = ;               if bDead then
      [*] = ;               begin
      [*] = ;                  var sizeX : Integer = 81;
      [*] = ;                  var sizeY : Integer = 108;
      [*] = ;                  var deadImageHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'misc.blank.black.alpha.1', 'halParentLeft', 'valParentTop', 7, 10, 70, 93, 0);
      [*] = ;                  SetGUIElementUserBlend(deadImageHandle, 0.55);
      [*] = ;                  deadImageHandle := _gui_CreateImage('', elmSlotHandle, 'battle.results.dead', 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY, 0);
      [*] = ;               end;
      [*] = ;
      [*] = ;               elmBtnHandle := _gui_CreateButton('unit_slot', elmSlotHandle, 'unit_slot', 'heropanel.unit.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 70, 93, '', '', tag);
      [*] = ;               if panelType=0 then
      [*] = ;                  pArmyParser := pGarrisonUnits
      [*] = ;               else
      [*] = ;                  pArmyParser := ParserSelectByHandleByKey(ParserSelectGameObject(goHeroHnd), 'Units');
      [*] = ;               _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipUnit',cFT_UnitMapArmy,pSlotUnit,pArmyParser,0,slotPressState,'3');
      [*] = ;               SetGUIElementStringTag(elmBtnHandle, IntToStr(slotHeroUID));
      [*] = ;               if (disabled) then
      [*] = ;               begin
      [*] = ;                  SetGUIElementUserBlend(elmImageHandle, 0.6);
      [*] = ;                  SetGUIElementUserBlend(elmBtnHandle, 0.6);
      [*] = ;                  //SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', matBlank{'heropanel.unit.slot.cover.normal'}, 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.unit.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (checkon) then
      [*] = ;                     SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (panelType=0) then //Garrison
      [*] = ;               begin
      [*] = ;                  //var pSlot : Integer = GetSlotUnitParser(goProvHnd, panelType, rank, j);
      [*] = ;                  CreateUnitMeters(elmBtnHandle, 0, pSlotUnit, pGarrisonUnits,build_morale);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin //Unit
      [*] = ;                  //var pSlot : Integer = GetSlotUnitParser(goHeroHnd, panelType, rank, j);
      [*] = ;                  CreateUnitMeters(elmBtnHandle, goHeroHnd, pSlotUnit, pUnits, build_morale);
      [*] = ;               end;
      [*] = ;
      [*] = ;               var hint : String;
      [*] = ;               if not bDead then
      [*] = ;               begin
      [*] = ;                  elmBtnHandle := _gui_CreateButton('dismiss', elmBtnHandle, 'dismiss', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRight', 'valParentTop', -18, 0, 18, 18, '', '', dismissBtnTag);
      [*] = ;
      [*] = ;                  if (mercMarket>0) and (gIntRegister_MapTurnIteration <> 1) then // no selling units during encounters 
      [*] = ;                  begin
      [*] = ;                     hint := 'gui|640';
      [*] = ;                     elmImageHandle := _gui_CreateImage('', elmBtnHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentTop', -2-18, -1, 23, 23, tag);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     hint := 'gui|641';
      [*] = ;                  SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;                  SetGUIElementStringTag(elmBtnHandle, 'dismiss');
      [*] = ;                  SetGUIElementVisible(elmBtnHandle, False);
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (highlight) then
      [*] = ;               begin
      [*] = ;                  elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, 'heropanel.unit.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('unitslot_highlight', elmSlotHandle, '', matBlank, 'halParentLeft', 'valParentTop', 1, 1, 70, 93, slotPressState, hint, tag);
      [*] = ;                  SetGUIElementStringTag(elmBtnHandle, IntToStr(slotHeroUID));
      [*] = ;                  SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.unit.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;                  SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;               end;
      [*] = ;               if ((panelAttr and 1) <> 0) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := GetGameObjectUniqueIdByHandle(goHeroHnd);
      [*] = ;                  IntRegister1 := pSlotUnit;
      [*] = ;                  IntRegister2 := $12;
      [*] = ;                  GUIExecuteState('VVK.map.GetHeroAstralTransferPrice');
      [*] = ;                  IntRegister2 := IntRegister0;
      [*] = ;                  IntRegister0 := elmSlotHandle;
      [*] = ;                  IntRegister1 := 1;
      [*] = ;                  GUIExecuteState('vvk.map.DisplayAstralPrice');
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (highlight) then
      [*] = ;               begin
      [*] = ;                  elmImageHandle := _gui_CreateImageSimple('open', elmSlotHandle, 'heropanel.unit.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('unitslot_highlight', elmSlotHandle, '', matBlank, 'halParentLeft', 'valParentTop', 0, 0, 70, 93, slotPressState, '', tag);
      [*] = ;                  SetGUIElementStringTag(elmBtnHandle, IntToStr(slotHeroUID));
      [*] = ;                  SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.unit.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;                  SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (disabled) then
      [*] = ;                  begin
      [*] = ;                     elmSlotHandle := _gui_CreateImageSimple('open', parentHandle, 'heropanel.unit.slot.empty.disabled', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;                     SetGUIElementUserBlend(elmSlotHandle, 0.5);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, matBlank, 'halParentLeft', 'valParentTop', 1, 3);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImageSimple('closed', parentHandle, 'heropanel.unit.slot.closed', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmImageHandle := _gui_CreateImageSimple('closed', parentHandle, 'heropanel.unit.slot.closed', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

