section.begin
   Name = battle.CreateControlPanelWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.CREATECONTROLPANELWINDOW';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;const cAbilityEventHandler : String = 'battle.ActivateAbility';
      [*] = ;
      [*] = ;var mapMainPanelHandle : Integer = _gui_GetWindow('map_mainpanel');
      [*] = ;if GetGUIElementVisible(mapMainPanelHandle) then
      [*] = ;   ErrorLogI(_log_name+' map_mainpanel was visible. CHECK THIS');
      [*] = ;
      [*] = ;GUIExecuteState('battle.IsLockMode');
      [*] = ;var isLockMode : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var tag : Integer = 0;
      [*] = ;var posX, posY : Integer;
      [*] = ;var xOff, yOff, xStep, yStep : Integer;
      [*] = ;var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;var hoverGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_EndHexUID);
      [*] = ;var statGoHandle : Integer;
      [*] = ;
      [*] = ;if (gIntRegister_EndHexUID<>0) and GetGameObjectVisibleByHandle(hoverGOHandle) then
      [*] = ;   statGoHandle := hoverGOHandle
      [*] = ;else
      [*] = ;   statGoHandle := goHandle;
      [*] = ;
      [*] = ;var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;var pStatGOParser : Integer = ParserSelectGameObject(statGoHandle);
      [*] = ;var hint : String;
      [*] = ;
      [*] = ;function CheckPlayerCanAct() : Boolean;
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;   var goCount : Integer = GetPlayerGameObjectsCountByHandle(plHandle);
      [*] = ;   var i,goHandle : Integer;
      [*] = ;
      [*] = ;   Result := False;
      [*] = ;   for i := 0 to goCount-1 do
      [*] = ;   begin
      [*] = ;      goHandle := GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      if GetGameObjectPlayableObjectByHandle(goHandle) and GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct) then
      [*] = ;      begin
      [*] = ;         Result := True;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetUnitProperty(goHandle, indProperty : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := indProperty;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;   Result := IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ShowUnitPropertyExt(matName, langTable, langKey : String; goHandle, elmParent, prIndex1 : Integer; delimeter : String; prIndex2, xShift, yShift, xSize, ySize, ixPos, yxPos : Integer);
      [*] = ;begin
      [*] = ;   var str : String = '';
      [*] = ;   var str2 : String = '';
      [*] = ;   var prop1, prop2 : Integer = 0;
      [*] = ;   var xSizeCut : Integer = 0;
      [*] = ;
      [*] = ;   if (goHandle<>0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := prIndex1;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      prop1 := IntRegister1;
      [*] = ;      prop2 := 0;
      [*] = ;
      [*] = ;      if prIndex2 <> -1 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := prIndex2;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;         prop2 := IntRegister1;
      [*] = ;         str := IntToStr(prop1){ + delimeter + IntToStr(prop2)};
      [*] = ;      end
      [*] = ;      else
      [*] = ;         str := IntToStr(prop1);
      [*] = ;
      [*] = ;      if (prIndex1 = gc_battle_unit_iRangedAttack) and (prop1 = 0) then
      [*] = ;         str := '';
      [*] = ;      if (prIndex1 = gc_battle_unit_iShootingRange) and (prop1 = 0) then
      [*] = ;         str := '';
      [*] = ;      if (prIndex2 = gc_battle_unit_iMaxAmmo) and (prop2 = 0) then
      [*] = ;         str := '';
      [*] = ;      if (prIndex1 = gc_battle_unit_iDefence) and (prop1 = 0) then
      [*] = ;         str := '';
      [*] = ;      if (prIndex1 = gc_battle_unit_iRangedDefence) and (prop1 = 0) then
      [*] = ;         str := '';
      [*] = ;      if (prIndex1 = gc_battle_unit_iResist) and (prop1 = 0) then
      [*] = ;         str := '';
      [*] = ;
      [*] = ;      if (prIndex1 = gc_battle_unit_iCounterAttack) or (prIndex1 = gc_battle_unit_iCurMoral) then
      [*] = ;         xSizeCut := 26;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var fontHandle : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_tactics,'PropertyValue',gc_gui_fontsize_default,'',fontHandle); // HeaderS
      [*] = ;   var elmTextHandle : Integer;
      [*] = ;
      [*] = ;   _gui_CreateText('unitproperty', elmParent, str, 'halParentLeft', 'valParentTop', xShift + ixPos * (xSize)+1, yShift + yxPos * (ySize)+1, xSize, ySize, 'halLeft', 'valBottomHeight', fontHandle, 0, 0, 0, 1);
      [*] = ;   if (prIndex1 = gc_battle_unit_iMovePoints) then
      [*] = ;   begin
      [*] = ;      var bCanAct : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct);
      [*] = ;      if bCanAct then
      [*] = ;         elmTextHandle := _gui_CreateText('unitproperty', elmParent, str, 'halParentLeft', 'valParentTop', xShift + ixPos * (xSize), yShift + yxPos * (ySize), xSize, ySize, 'halLeft', 'valBottomHeight', fontHandle, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1)
      [*] = ;      else
      [*] = ;         elmTextHandle := _gui_CreateText('unitproperty', elmParent, str, 'halParentLeft', 'valParentTop', xShift + ixPos * (xSize), yShift + yxPos * (ySize), xSize, ySize, 'halLeft', 'valBottomHeight', fontHandle, gc_gui_fontcolor_RedR, gc_gui_fontcolor_RedG, gc_gui_fontcolor_RedB, 1)
      [*] = ;   end
      [*] = ;   else
      [*] = ;      elmTextHandle := _gui_CreateText('unitproperty', elmParent, str, 'halParentLeft', 'valParentTop', xShift + ixPos * (xSize), yShift + yxPos * (ySize), xSize, ySize, 'halLeft', 'valBottomHeight', fontHandle, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;
      [*] = ;   var elmImageHandle : Integer = _gui_CreateImage('unitproperty_image', elmTextHandle, matName, 'halParentLeft', 'valParentTop', -46, 0, 0, 0, 0);
      [*] = ;   if (str='') then
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.125)
      [*] = ;   else
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.9);
      [*] = ;
      [*] = ;   posX := xShift + ixPos * (xSize)-39;
      [*] = ;   posY := yShift + yxPos * (ySize);
      [*] = ;
      [*] = ;   elmTextHandle := _gui_CreateButton('', elmParent, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX, posY-2, xSize-8-xSizeCut, ySize-1, '', '', 0);
      [*] = ;   _gui_ft_AttachHint_I5(elmTextHandle,'VVK.HintASERCallback',cFT_ASER_Ability,0,StrToInt(langKey),prop1,0);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ShowAbilities(elmHandle, elmBtnHandle, goHandle, xOff, yOff, xStep, yStep : Integer; elmMainPanelHnd : Integer);
      [*] = ;begin
      [*] = ;   var pGOUpgrades : Integer = ParserSelectByHandleByKey(pGOParser, 'Upgrades');
      [*] = ;   var pGOMedals : Integer = ParserSelectByHandleByKey(pGOParser, 'Medals');
      [*] = ;   var pGOEffects : Integer = ParserSelectByHandleByKey(pGOParser, 'Effects');
      [*] = ;   var goAbilityID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iActiveAbility);
      [*] = ;   var curSlot : Integer = 0;
      [*] = ;   var i,ano : Integer;
      [*] = ;   var pAbilities : Integer = gPrototypeData.abilities.handle;
      [*] = ;
      [*] = ;   ano := 0;
      [*] = ;   for i:=0 to gPrototypeData.abilities.number-1 do
      [*] = ;   begin
      [*] = ;      var pAbility : Integer = ParserSelectByHandleByIndex(pAbilities, i);
      [*] = ;      var abilityID : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'AbilityID');
      [*] = ;      var abilityIdx : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'Index');
      [*] = ;      var activate : Boolean = ParserGetBoolValueByKeyByHandle(pAbility, 'Activate');
      [*] = ;      if (activate) then
      [*] = ;      begin
      [*] = ;         var value : Integer = _unit_CheckAbility(goHandle, abilityID);
      [*] = ;         if (value>0) then
      [*] = ;         begin
      [*] = ;            var btnName, iconName : String = '';
      [*] = ;            var btnNameSuffix : String = '';
      [*] = ;            case abilityID of
      [*] = ;               20 : btnNameSuffix := 'DoubleShot';
      [*] = ;               23 : btnNameSuffix := 'collectammo';
      [*] = ;               24 : btnNameSuffix := 'curewounds';
      [*] = ;               29 : btnNameSuffix := 'ForcedMarch';
      [*] = ;               49 : btnNameSuffix := 'Necrophagy';
      [*] = ;               59 : btnNameSuffix := 'CrushingBlow';
      [*] = ;               66 : btnNameSuffix := 'RoundAttack';
      [*] = ;               111 : btnNameSuffix := '144';
      [*] = ;               114 : btnNameSuffix := '147';
      [*] = ;               126 : btnNameSuffix := '155';
      [*] = ;               127 : btnNameSuffix := '156';
      [*] = ;               132 : btnNameSuffix := '168';
      [*] = ;               134 : btnNameSuffix := '170';
      [*] = ;               136 : btnNameSuffix := '172';
      [*] = ;            end;
      [*] = ;            if (btnNameSuffix<>'') then
      [*] = ;            begin
      [*] = ;               btnName := 'battle.ability.btn.'+btnNameSuffix;
      [*] = ;               iconName := btnName+'.icon';
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               btnName := 'icons.round.44x44.cover';
      [*] = ;               iconName := 'icon.ability.'+IntToStr(abilityIdx);
      [*] = ;            end;
      [*] = ;            var elmX : Integer = xOff + curSlot * xStep;
      [*] = ;            var elmY : Integer = yOff;
      [*] = ;            var tag : Integer = gc_gui_battle_btnControlAbilityBaseTag + abilityID;
      [*] = ;            //elmBtnHandle := _gui_CreateButton('', elmHandle, '', 'icons.round.44x44.cover', 'halParentLeft', 'valParentTop', elmX+4, elmY+6, 45, 47, cAbilityEventHandler, '', tag);
      [*] = ;            //SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'icons.round.44x44.cover' + '.pressed', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;            if (statGoHandle=GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID)) then
      [*] = ;            begin
      [*] = ;               var elmImageHandle : Integer = _gui_CreateImage('' , elmHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', elmX+3, elmY+6, 52-5, 52-5, 0);
      [*] = ;               elmBtnHandle := _gui_CreateButton('ability_'+IntToStr(ano), elmHandle, '', btnName, 'halParentLeft', 'valParentTop', elmX+3, elmY+6, 0, 0, cAbilityEventHandler, '', tag);
      [*] = ;               ano := ano + 1;
      [*] = ;               SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', btnName+'.pressed', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;               SetGUIElementStringTag(elmBtnHandle,IntToStr(abilityID));
      [*] = ;               SetGUIElementHint(elmBtnHandle, 'ability|'+IntToStr(abilityIdx)+'|1280|'+ IntToStr(value)+'|0|#battledoability,'+IntToStr(abilityID)+',battleabilityslottrigger,'+IntToStr(ano-1));
      [*] = ;
      [*] = ;               var checked : Boolean = false;
      [*] = ;               case abilityID of
      [*] = ;                  20, 24, 132 : checked := (abilityID = goAbilityID);
      [*] = ;                  59 : checked := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCrush);
      [*] = ;                  66 : checked := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bRoundAttack);
      [*] = ;                  111 : checked := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bStealthMode);
      [*] = ;                  114 : checked := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bFireBreath);
      [*] = ;                  126 : checked := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bPoisonBite);
      [*] = ;                  127 : checked := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bAstralStrike);
      [*] = ;                  134 : checked := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bLunge);
      [*] = ;               end;
      [*] = ;               SetGUIElementChecked(elmBtnHandle, checked);
      [*] = ;
      [*] = ;               IntRegister0 := abilityID;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'IsAbilityAvailable');
      [*] = ;               var enabled : Boolean = ((not isLockMode) and BoolRegister0 and (not gBoolRegister_BattlePlaceMode));
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, enabled);
      [*] = ;
      [*] = ;               if (not enabled) then
      [*] = ;               begin
      [*] = ;                  const cFade = 0.85;
      [*] = ;                  SetGUIElementUseUserColor(elmBtnHandle, True);
      [*] = ;                  SetGUIElementUserColor(elmBtnHandle, cFade, cFade, cFade, 1);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var elmImageHandle : Integer = _gui_CreateImage('' , elmHandle, iconName, 'halParentLeft', 'valParentTop', elmX+3, elmY+6, 52-5, 52-5, 0);
      [*] = ;               const cFade = 0.5;
      [*] = ;               SetGUIElementUseUserColor(elmImageHandle, True);
      [*] = ;               SetGUIElementUserColor(elmImageHandle, cFade, cFade, cFade, 1);
      [*] = ;            end;
      [*] = ;
      [*] = ;            curSlot := curSlot + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var elmBattleMenuPanel : Integer = _gui_GetOrCreateElement('battle_menupanel', _gui_GetLayerI(), 'halParentLeft', 'valParentTop', 0, 0, GetViewerWidth(), GetViewerHeight(), Tag);
      [*] = ;SetGUIElementVisible(elmBattleMenuPanel, true);
      [*] = ;_gui_RootWindowAdd(elmBattleMenuPanel,cRootWindowCP);
      [*] = ;
      [*] = ;// Background
      [*] = ;const cBgWidth = 2048;
      [*] = ;const cBgHeight = 156;
      [*] = ;var elmBattleMenuPanelDummy : Integer = _gui_CreateDummy('battle_unitpanel', elmBattleMenuPanel, 'halMiddle', 'valBottomHeight', 0, 0, cBgWidth, cBgHeight, Tag);
      [*] = ;
      [*] = ;posX := 451;
      [*] = ;posY := 27;
      [*] = ;var elmImageHandle : Integer = _gui_CreateImage('' , elmBattleMenuPanelDummy, 'battle.controlpanel.bottom.uniticon.background', 'halParentLeft', 'valParentTop', posX, posY, 74, 91, 0);
      [*] = ;
      [*] = ;var elmBattleMenuPanelBackgroundMask : Integer = _gui_CreateImage('' , elmBattleMenuPanelDummy, gc_gui_material_blank_0, 'halParentMiddle', 'valParentBottomHeight', 0, -1, cBgWidth-820, cBgHeight-30, 0); //posY = -1, for making bottom camera scroller work
      [*] = ;SetGUIAllowEvents(elmBattleMenuPanelBackgroundMask, true, false, false);
      [*] = ;
      [*] = ;//�������� �����
      [*] = ;var unitID : Integer = GetGameObjectIntValueIndByHandle(statGoHandle, gc_stack_unit_iUnitID);
      [*] = ;if (statGoHandle<>0) then
      [*] = ;begin
      [*] = ;   const cControlPanelUnitIconBtnTag = 100;
      [*] = ;
      [*] = ;   posX := 453;
      [*] = ;   posY := 26;
      [*] = ;   if unitID <> 0 then
      [*] = ;   begin
      [*] = ;      var isHero : Boolean = GetGameObjectBoolValueIndByHandle(statGoHandle, gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;      if isHero then
      [*] = ;      begin
      [*] = ;         var heroHandle : Integer = GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(statGoHandle, gc_stack_unit_iHeroUID));
      [*] = ;         var temp_str : String;
      [*] = ;
      [*] = ;         temp_str := StrReplace(ParserGetValueByKeyByHandle(ParserSelectGameObject(heroHandle),'Portrait'),'map.hero.portrait.','info.portrait.');
      [*] = ;         elmImageHandle := _gui_CreateImage('icon', elmBattleMenuPanelDummy, temp_str, 'halParentLeft', 'valParentTop', posX, posY, 70, 93, 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         elmImageHandle := _gui_CreateImage('icon', elmBattleMenuPanelDummy, 'icon.unit.'+IntToStr(unitID), 'halParentLeft', 'valParentTop', posX, posY, 70, 93, 0);
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('battle_unit_icon_'+IntToStr(unitID), elmImageHandle, '', 'heropanel.unit.slot.cover', 'halParentLeft', 'valParentTop', 0, 6, 72, 96-11, '', '', 0);
      [*] = ;      _gui_ft_AttachHint_I6(elmBtnHandle,'VVK.FTooltipUnit',cFT_UnitBattle,GetGameObjectUniqueIdByHandle(statGoHandle),0,0,4,4); // gIntRegister_SelectedUID right button - battle mode
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var elmBattleUnitPanelAbilityButtons : Integer = _gui_CreateDummy('battle_unitproperties1', elmBattleMenuPanelDummy, 'halParentLeft', 'valParentTop', 0, 0, cBgWidth, cBgHeight, Tag);
      [*] = ;var elmUnitPanelActiveAbilities : Integer = _gui_CreateDummy('battle_activeabilities', elmBattleMenuPanelDummy, 'halParentLeft', 'valParentTop', 0, 0, cBgWidth, cBgHeight, Tag);
      [*] = ;
      [*] = ;xOff := 876;
      [*] = ;yOff := 103;
      [*] = ;xStep := 52;
      [*] = ;yStep := 57;
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to 3 do
      [*] = ;   elmImageHandle := _gui_CreateImage('' , elmBattleUnitPanelAbilityButtons, 'battle.ability.icon.52x52.empty', 'halParentLeft', 'valParentTop', xOff+i*xStep+1, yOff+3, 51, 51, 0);
      [*] = ;if (statGoHandle<>0) then
      [*] = ;   ShowAbilities(elmBattleUnitPanelAbilityButtons, elmUnitPanelActiveAbilities, statGoHandle, xOff, yOff, xStep, yStep, elmBattleMenuPanelDummy);
      [*] = ;
      [*] = ;var elmBattleMenuPanelBackground : Integer = _gui_CreateImage('battle_unitpanel_background' , elmBattleMenuPanelDummy, 'battle.controlpanel.bottom.background', 'halParentMiddle', 'valParentBottomHeight', 0, 0, cBgWidth, cBgHeight, 0);
      [*] = ;SetGUIAllowEvents(elmBattleMenuPanelBackground, false{true}, false, false);
      [*] = ;
      [*] = ;//��� �����
      [*] = ;if (unitID>0) then
      [*] = ;begin
      [*] = ;   var fontHandle : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_tactics,'UnitName',gc_gui_fontsize_default,'',fontHandle); // HeaderS
      [*] = ;   var text : String;
      [*] = ;   var isHero : Boolean = GetGameObjectBoolValueIndByHandle(statGoHandle, gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;   if (isHero) then
      [*] = ;   begin
      [*] = ;      var heroHandle : Integer = GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(statGoHandle, gc_stack_unit_iHeroUID));
      [*] = ;      //GameObjectExecuteStateByHandle(heroHandle, 'GetClass');
      [*] = ;      //var classInd : Integer = IntRegister0;
      [*] = ;      //text := GetLocaleTableListItemByID('hero_class', IntToStr(classInd));
      [*] = ;      _hero_GetName(heroHandle,text);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      text := GetLocaleTableListItemByID('unit', IntToStr(unitID));
      [*] = ;
      [*] = ;   posX := 489;
      [*] = ;   posY := 16;
      [*] = ;
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('battle_unit_name', elmBattleMenuPanelBackground, text, 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;//������� ����������
      [*] = ;var xShift, yShift, xSize, ySize : Integer;
      [*] = ;xShift := 580;
      [*] = ;yShift := 34;
      [*] = ;xSize := 93;
      [*] = ;ySize := 34;
      [*] = ;const cParamDelimeter = '/';
      [*] = ;var elmBattleUnitProperities : Integer = _gui_CreateDummy('battle_unitproperties', elmBattleMenuPanelDummy, 'halParentMiddle', 'valParentBottomHeight', 0, 0, cBgWidth, cBgHeight, Tag);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.life.47x36', 'ability', '1', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iCurLife, cParamDelimeter, gc_battle_unit_iMaxLife, xShift, yShift, xSize, ySize, 0, 0);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.stamina.47x36', 'ability', '11', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iCurStamina, cParamDelimeter, gc_battle_unit_iMaxStamina, xShift, yShift, xSize, ySize, 1, 0);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.morale.47x36', 'ability', '12', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iCurMoral, '', -1, xShift, yShift, xSize, ySize, 2, 0);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.speed.47x36', 'ability', '7', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iMovePoints, '', -1, xShift, yShift, xSize, ySize, 0, 1);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.attack.47x36', 'ability', '2', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iAttack, '', -1, xShift, yShift, xSize, ySize, 1, 1);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.counterattack.47x36', 'ability', '3', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iCounterAttack, '', -1, xShift, yShift, xSize, ySize, 2, 1);
      [*] = ;
      [*] = ;xShift := 580;
      [*] = ;yShift := 34;
      [*] = ;xSize := 88;
      [*] = ;ySize := 34;
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.defence.47x36', 'ability', '4', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iDefence, '', -1, xShift, yShift, xSize, ySize, 3, 0);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.rangeddefence.47x36', 'ability', '5', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iRangedDefence, '', -1, xShift, yShift, xSize, ySize, 4, 0);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.resist.47x36', 'ability', '6', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iResist, '', -1, xShift, yShift, xSize, ySize, 5, 0);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.rangedattack.47x36', 'ability', '8', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iRangedAttack, '', -1, xShift, yShift, xSize, ySize, 3, 1);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.rangeddistance.47x36', 'ability', '9', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iShootingRange, '', -1, xShift, yShift, xSize, ySize, 4, 1);
      [*] = ;ShowUnitPropertyExt('gamepanel01.unitparam.ammo.47x36', 'ability', '10', statGoHandle, elmBattleUnitProperities, gc_battle_unit_iCurAmmo, cParamDelimeter, gc_battle_unit_iMaxAmmo, xShift, yShift, xSize, ySize, 5, 1);
      [*] = ;
      [*] = ;//������� � ������� �����
      [*] = ;var unitLevel : Integer = -1;
      [*] = ;if (statGoHandle<>0) then
      [*] = ;   unitLevel := GetGameObjectIntValueIndByHandle(statGoHandle, gc_stack_unit_iLevel);
      [*] = ;
      [*] = ;xOff := 444;
      [*] = ;yOff := 108;
      [*] = ;var fontHandle : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'LevelValue',gc_gui_fontsize_default,'',fontHandle); // HeaderS
      [*] = ;var elmBattleUnitExpLevel : Integer = _gui_CreateImageSimple('battle_unitproperties_explevel', elmBattleMenuPanelDummy, 'battlepanel.meter.round', 'halParentLeft', 'valParentTop', xOff-7, yOff-7);
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('battle_unitproperties_level', elmBattleMenuPanelDummy, IntToStr(unitLevel), 'halParentLeft', 'valParentTop', xOff, yOff, 20, 20, 'halMiddle', 'valBottomHeight', fontHandle, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;SetGUIElementHint(elmTextHandle, 'glossary|skill.1|CC|0|-60');
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;//������ "EndTurn"
      [*] = ;xOff := 1487;
      [*] = ;yOff := 97;
      [*] = ;var plCanAct : Boolean = CheckPlayerCanAct;
      [*] = ;var elmBattleUnitPanelButtons : Integer = _gui_CreateDummy('battle_unitproperties_buttons', elmBattleMenuPanelDummy, 'halParentLeft', 'valParentTop', 0, 0, cBgWidth, cBgHeight, Tag);
      [*] = ;if (gBoolRegister_BattlePlaceMode) then
      [*] = ;begin
      [*] = ;   hint := 'gui|127|MT|0|0|battlenextturn';
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('battle_mainpanel_btn_startbattle', elmBattleUnitPanelButtons, '', 'battle.controlpanel.btn.startbattle', 'halParentLeft', 'valParentTop', xOff, yOff, 107, 61, '', hint, gc_gui_battle_btnExitPlacementMode);
      [*] = ;   if _cmd_CheckNF('battlenextturn','','') <> 1 then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if not gTutorial.map then
      [*] = ;         _gui_CreateBlinkElement('blink_battle_start', elmBtnHandle, 'battle.controlpanel.btn.startbattle.hover', false, 0, 0, 0, 0)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if gBoolRegister_BtnBatEndTurnBlink then
      [*] = ;            _gui_CreateBlinkElement('btnBatEndTurn', elmBtnHandle, 'gamepanel01.btn.endturn.highlight', false, 0, 0, 0, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButtonFromCollection('battle_mainpanel_btn_endturn', elmBattleUnitPanelButtons, 'map.mainpanel.btn.endturn', 'halParentLeft', 'valParentTop', xOff, yOff, '', gc_gui_battle_btnEndTurn);
      [*] = ;
      [*] = ;   hint := 'gui|100|MT|0|0|battlenextturn';
      [*] = ;   SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;
      [*] = ;   if _cmd_Check('battlenextturn','','') <> 1 then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;
      [*] = ;   if (not _misc_IsLanBattle) then
      [*] = ;   begin
      [*] = ;      if GetGUIElementEnabled(elmBtnHandle) and (not plCanAct) and (not gProfile.warEndTurn) then
      [*] = ;         _gui_CreateBlinkElement('blink_battle_endturn', elmBtnHandle, 'gamepanel01.btn.endturn.highlight', false, 0, 0, 0, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;xOff := 1425;
      [*] = ;yOff := 108;
      [*] = ;hint := 'gui|96|MT|0|0|battleshowmenu';
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('battle_mainpanel_btn_options', elmBattleUnitPanelButtons, '', 'map.mainpanel.btn.menu3', 'halParentLeft', 'valParentTop', xOff, yOff, 49, 49, '', hint, gc_gui_battle_btnSettings);
      [*] = ;if gBoolRegister_BtnBattleSettingsBlink then
      [*] = ;   _gui_CreateBlinkElement('btnSettings', elmBtnHandle, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;if _cmd_Check('battleshowmenu','','') <> 1 then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;
      [*] = ;if (statGoHandle=0) then
      [*] = ;begin
      [*] = ;   //SetGUIElementVisible(elmBattleUnitProperities, false);
      [*] = ;   //SetGUIElementVisible(elmBattleUnitExpLevel, false);
      [*] = ;   SetGUIElementVisible(elmTextHandle, false);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   //SetGUIElementVisible(elmBattleUnitProperities, true);
      [*] = ;   //SetGUIElementVisible(elmBattleUnitExpLevel, true);
      [*] = ;   SetGUIElementVisible(elmTextHandle, true);
      [*] = ;end;
      [*] = ;
      [*] = ;//������ ���������
      [*] = ;xOff  := 1134;
      [*] = ;yOff  := 108;
      [*] = ;xStep := 63;
      [*] = ;yStep := 57;
      [*] = ;
      [*] = ;var elmBtnRestHandle, elmBtnSpellBookHandle, elmBtnSwitchWeaponHandle, elmBtnNextUnitHandle : Integer;
      [*] = ;hint := 'gui|119|MT|0|0|battleunitrest';
      [*] = ;elmBtnRestHandle := _gui_CreateButton('battle_control_btn_rest', elmBattleUnitPanelButtons, '', 'battle.controlpanel.btn.rest', 'halParentLeft', 'valParentTop', xOff, yOff, 49, 49, '', hint, gc_gui_battle_btnControlRest);
      [*] = ;SetGUIElementVisibleProperties(elmBtnRestHandle, 'CheckOnProperty', 'battle.controlpanel.btn.rest' + '.pressed', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1); // GEC Check. this line was added when creating gui script library
      [*] = ;hint := 'gui|123|MT|0|0|battlecastspell';
      [*] = ;//elmBtnSpellBookHandle := _gui_CreateButtonFromCollection('battle_control_btn_spellbook', elmBattleUnitPanelButtons, 'map.mainpanel.btn.ritual', 'halParentLeft', 'valParentTop', xOff+51, yOff-1, '', gc_gui_battle_btnControlSpellBook);
      [*] = ;elmBtnSpellBookHandle := _gui_CreateButton('battle_control_btn_spellbook', elmBattleUnitPanelButtons, '', 'map.radialhero.btn.magic', 'halParentLeft', 'valParentTop', xOff+51+1, yOff-1+1, 0, 0, '', '', gc_gui_battle_btnControlSpellBook);
      [*] = ;SetGUIElementHint(elmBtnSpellBookHandle, hint);
      [*] = ;//TODO - Switch Weapon
      [*] = ;hint := 'gui|451|MT|0|0|battleswitchweapon';
      [*] = ;elmBtnSwitchWeaponHandle := _gui_CreateButton('battle_control_btn_switchweapon', elmBattleUnitPanelButtons, '', 'battle.controlpanel.btn.switchweapon', 'halParentLeft', 'valParentTop', xOff+104, yOff, 49, 49, '', hint, gc_gui_battle_btnControlSwitchWeapon);
      [*] = ;SetGUIElementVisibleProperties(elmBtnSwitchWeaponHandle, 'CheckOnProperty', 'battle.controlpanel.btn.switchweapon' + '.pressed', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;hint := 'gui|120|MT|0|0|battleunitnext';
      [*] = ;elmBtnNextUnitHandle := _gui_CreateButtonFromCollection('battle_control_btn_nextunit', elmBattleUnitPanelButtons, 'map.mainpanel.btn.nexthero', 'halParentLeft', 'valParentTop', xOff+198, yOff-2, '', gc_gui_battle_btnControlNextUnit);
      [*] = ;SetGUIElementHint(elmBtnNextUnitHandle, hint);
      [*] = ;
      [*] = ;if (isLockMode) {or (gBoolRegister_BattlePlaceMode)} or (not plCanAct) or (gIntRegister_CurSpell>0) then
      [*] = ;   SetGUIElementEnabled(elmBtnNextUnitHandle, false)
      [*] = ;else
      [*] = ;   SetGUIElementEnabled(elmBtnNextUnitHandle, true);
      [*] = ;
      [*] = ;var isHero : Boolean = false;
      [*] = ;var canAct : Boolean = false;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   isHero := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bIsHero);
      [*] = ;   canAct := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct);
      [*] = ;end;
      [*] = ;
      [*] = ;if (goHandle<>0) and (not gBoolRegister_BattlePlaceMode) and (not isLockMode) then
      [*] = ;begin
      [*] = ;   if GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bResting) then
      [*] = ;      SetGUIElementChecked(elmBtnRestHandle, true)
      [*] = ;   else
      [*] = ;      SetGUIElementEnabled(elmBtnRestHandle, _unit_CanRest(goHandle));
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementEnabled(elmBtnRestHandle, false);
      [*] = ;end;
      [*] = ;
      [*] = ;if (_cmd_CheckNF('battlecastspell','','')) <> 1 then
      [*] = ;   SetGUIElementEnabled(elmBtnSpellBookHandle, false);
      [*] = ;
      [*] = ;if (goHandle <> 0) and (not isLockMode) then
      [*] = ;begin
      [*] = ;   if (not isHero) or (gIntRegister_CurSpell>0) or (not canAct) then
      [*] = ;      SetGUIElementEnabled(elmBtnSwitchWeaponHandle, false);
      [*] = ;end
      [*] = ;else
      [*] = ;   SetGUIElementEnabled(elmBtnSwitchWeaponHandle, false);
      [*] = ;
      [*] = ;if gBoolRegister_BtnSwitchWeaponBlink then
      [*] = ;begin
      [*] = ;   var f : Boolean;
      [*] = ;   if GetGUIElementEnabled(elmBtnSwitchWeaponHandle) then
      [*] = ;      _gui_CreateBlinkElement('btnSwitchWeapon', elmBtnSwitchWeaponHandle, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0)
      [*] = ;   else
      [*] = ;      _gui_RemoveBlinkElement('btnSwitchWeapon', f);
      [*] = ;end;
      [*] = ;
      [*] = ;//������ ��������
      [*] = ;xOff  := 69;
      [*] = ;yOff  := 657;
      [*] = ;xStep := 72;
      [*] = ;yStep := 57;
      [*] = ;
      [*] = ;//Spell dismiss button
      [*] = ;if (gIntRegister_CurSpell>0) then
      [*] = ;begin
      [*] = ;   posX := 1185; //1425;
      [*] = ;   posY := 107; //45;
      [*] = ;   hint := 'gui|124|MT';
      [*] = ;   elmBtnHandle := _gui_CreateButton('battle_spell_cancel', elmBattleUnitPanelButtons, 'battle_cancelspell', 'map.radialhero.btn.move.cancel', 'halParentLeft', 'valParentTop', posX, posY, 51, 51, '', hint, gc_gui_battle_btnDismissSpell);
      [*] = ;end;
      [*] = ;
      [*] = ;// effects icon places
      [*] = ;posX := 555;
      [*] = ;posY := 106;
      [*] = ;xOff := 47;
      [*] = ;
      [*] = ;// --- Layer with scroll
      [*] = ;var elmScrollLayer : Integer = AddNewElementByClassNameParent('battle_unit_effects_bar', 'TXGuiLayer', 0, elmBattleMenuPanelBackground);
      [*] = ;SetGUIAllowEvents(elmScrollLayer, True, False, False);
      [*] = ;SetGUIElementAlign(elmScrollLayer, 'halParentLeft', 'valParentTop');
      [*] = ;SetGUIElementAllPositionRect(elmScrollLayer, posX, posY, 6*xOff, 45);
      [*] = ;SetGUIElementMaterial(elmScrollLayer, 'misc.blank.black.alpha.0');
      [*] = ;SetGUIScrollEnabled(elmScrollLayer, True);
      [*] = ;//var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;var elmHScroll : Integer = GetGUIElementHScroll(elmScrollLayer);
      [*] = ;var effectsCount : Integer = 0;
      [*] = ;var visibleEffCount : Integer = 0;
      [*] = ;
      [*] = ;if (statGoHandle<>0) then
      [*] = ;begin
      [*] = ;   var pUnitParser : Integer = ParserSelectGameObject(statGoHandle);
      [*] = ;   var pUnitEffects : Integer = ParserSelectByHandleByKey(pUnitParser, 'Effects');
      [*] = ;   effectsCount := ParserGetCountByHandle(pUnitEffects);
      [*] = ;
      [*] = ;   for i := 0 to effectsCount-1 do
      [*] = ;   begin
      [*] = ;      var pUnitEffect : Integer = ParserSelectByHandleByIndex(pUnitEffects, i);
      [*] = ;      var visible : Boolean = ParserGetBoolValueByKeyByHandle(pUnitEffect, 'Visible');
      [*] = ;
      [*] = ;      if (visible) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pUnitEffect;
      [*] = ;         MapExecuteState('bat.GetEffectIDByParser');
      [*] = ;         var effectID : Integer = IntRegister1;
      [*] = ;         var ParentUpgradeID : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'ParentUpgradeID');
      [*] = ;         var ParentSpellID : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'ParentSpellID');
      [*] = ;         var effectPower : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'Power');
      [*] = ;         var effectDuration : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'Duration');
      [*] = ;         var imageName : String = '';
      [*] = ;         var p : array [0..5] of Integer;
      [*] = ;
      [*] = ;         if (ParentUpgradeID>0) then
      [*] = ;         begin
      [*] = ;            p[0] := cFT_ASER_Effect;
      [*] = ;            p[1] := EffectID;
      [*] = ;            p[2] := ParentUpgradeID;
      [*] = ;            p[3] := 0;
      [*] = ;            if effectPower <> 0 then
      [*] = ;               p[4] := Round(Abs(effectPower))
      [*] = ;            else
      [*] = ;               p[4] := 0;
      [*] = ;
      [*] = ;            imageName := 'icon.skill.' + IntToStr(ParentUpgradeID);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (ParentSpellID>0) then
      [*] = ;            begin
      [*] = ;               if (effectID>0) then
      [*] = ;               begin
      [*] = ;                  p[0] := cFT_ASER_EffectSpell;
      [*] = ;                  p[1] := EffectID;
      [*] = ;                  p[2] := ParentSpellID;
      [*] = ;                  p[3] := 0;
      [*] = ;                  p[4] := effectDuration;
      [*] = ;                  imageName := 'icon.spell.' + IntToStr(ParentSpellID);
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  ErrorLogI('effectID=0');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (imageName<>'') then
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmScrollLayer, imageName, 'halParentLeft', 'valParentTop', visibleEffCount*xOff, 0, 45, 45, Tag);
      [*] = ;            elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'icons.52x52.cover', 'halParentLeft', 'valParentTop', 0, -1, 45, 47, '', '', 0);
      [*] = ;            _gui_ft_AttachHint_I5(elmBtnHandle,'VVK.HintASERCallback',p[0],p[1],p[2],p[3],p[4]);
      [*] = ;            visibleEffCount := visibleEffCount+1;
      [*] = ;            if (effectDuration>0) then
      [*] = ;            begin
      [*] = ;               _gui_GetFont(gc_gui_fontsection_tactics,'SpellDuration',gc_gui_fontsize_small,'',fontHandle); // NormalL
      [*] = ;               var width, height : Integer;
      [*] = ;               GetGUIElementFontTextFormatRect(fontHandle, IntToStr(effectDuration), width, height);
      [*] = ;               elmImageHandle := _gui_CreateImage('unitinfo_effect_duration', elmBtnHandle, 'pixel.0.0.0', 'halParentRight', 'valParentBottom', -width-8, -height-3, width+6, height+1, effectDuration);
      [*] = ;               SetGUIElementUserBlend(elmImageHandle, 0.75);
      [*] = ;               elmTextHandle := _gui_CreateText('unitinfo_effect_duration_text', elmImageHandle, IntToStr(effectDuration), 'halParentLeft', 'valParentTop', 0, 1, width+7, height, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (statGoHandle<>0) then
      [*] = ;begin
      [*] = ;   var pGOMedals : Integer = ParserSelectByHandleByKey(pStatGOParser, 'Medals');
      [*] = ;   // check in medals
      [*] = ;   var medalCount : Integer = ParserGetCountByHandle(pGOMedals);
      [*] = ;   posX := 466;
      [*] = ;   posY := 125;
      [*] = ;   var elmMedalsDummy : Integer = _gui_CreateImage('battle_unit_medals_bar', elmBattleMenuPanelDummy, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', posX, posY, 60, 26, 0);
      [*] = ;   var medalID,pMedal : Integer;
      [*] = ;
      [*] = ;   SetGUIAllowEvents(elmMedalsDummy, True, False, False);
      [*] = ;   for i := medalCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      medalID := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGOMedals, i),'MedalID');
      [*] = ;      IntRegister0 := medalID;
      [*] = ;      MapExecuteState('GetMedalParserByID');
      [*] = ;      pMedal := IntRegister1;
      [*] = ;
      [*] = ;      posX := 5-20*i+(round(20*medalCount/2)); //500 22
      [*] = ;      posY := 0;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmMedalsDummy, 'icon.medal.'+IntToStr(medalID), 'halParentLeft', 'valParentTop', posX, posY, 24, 24, tag);
      [*] = ;      _gui_ft_AttachHint_I1(elmImageHandle,'VVK.HintUnitMedalsCallback',medalID);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      //SetGUIElementPressState(elmImageHandle, cEventHandler);
      [*] = ;      SetGUIElementCursorByIndex(elmImageHandle, 6);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SetGUIElementWidth(elmScrollLayer, xOff*visibleEffCount); //all width
      [*] = ;
      [*] = ;// Effects scroller
      [*] = ;posX := 518;
      [*] = ;posY := 106;
      [*] = ;xOff := 311;
      [*] = ;var curScrollPos : Float = GetGUIScrollBarPosition(elmHScroll);
      [*] = ;elmBtnHandle := _gui_CreateButton('battle_effect_scroll_left', elmBattleMenuPanelBackground, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', posX, posY, 43, 43, '', '', gc_gui_battle_btnEffectsScrollLeft);
      [*] = ;//SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'common.scroller.left.disabled.alpha', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;if visibleEffCount <= 6 then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;else
      [*] = ;begin
      [*] = ;   if curScrollPos > 0 then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, true)
      [*] = ;   else
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;end;
      [*] = ;
      [*] = ;elmBtnHandle := _gui_CreateButton('battle_effect_scroll_right', elmBattleMenuPanelBackground, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', posX+xOff, posY, 43, 43, '', '', gc_gui_battle_btnEffectsScrollRight);
      [*] = ;//SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'common.scroller.right.disabled.alpha', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;if visibleEffCount <= 6 then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;else
      [*] = ;begin
      [*] = ;   if curScrollPos < 1 then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, true)
      [*] = ;   else
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

