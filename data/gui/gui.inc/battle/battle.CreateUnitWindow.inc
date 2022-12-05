section.begin
   Name = battle.CreateUnitWindow
   Code : struct.begin
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;var pGOParser : Integer = IntRegister1;
      [*] = ;var pArmyUnits : Integer = IntRegister2;
      [*] = ;
      [*] = ;gIntRegister_UnitInfoParser := pGOParser;
      [*] = ;if (pArmyUnits<>0) then
      [*] = ;begin
      [*] = ;   var pArmyUnit0 : Integer = ParserSelectByHandleByIndex(pArmyUnits, 0);
      [*] = ;   gIntRegister_CurHeroUIDInfo := ParserGetIntValueByKeyByHandle(pArmyUnit0, 'HeroUID');
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateScrollerParent(ElementName : String; Parent : Integer; hAlign, vAlign, MaterialName : String; posX, posY, sizeX, sizeY, scrollX, scrollY, scrollH : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var elmGuiLayer : Integer = AddNewElementByClassNameParent(ElementName, 'TXGuiLayer', 0, Parent);
      [*] = ;   SetGUIElementAlign(elmGuiLayer, hAlign, vAlign);
      [*] = ;   SetGUIElementAllPositionRect(elmGuiLayer, posX, posY, sizeX, sizeY);
      [*] = ;   SetGUIElementMaterial(elmGuiLayer, MaterialName);
      [*] = ;   SetGUIScrollEnabled(elmGuiLayer, True);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;   SetGUIElementAlign(elmVScroll, 'halParentLeft', 'valParentTop');
      [*] = ;   SetGUIElementMaterialOffset(elmVScroll, -1, 0);
      [*] = ;   SetGUIElementAllPositionRect(elmVScroll, scrollX, scrollY, 27, scrollH);
      [*] = ;   SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;   SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;   SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;   SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;   SetGUIAllowEvents(elmGuiLayer, True, False, False);
      [*] = ;   Result := elmGuiLayer;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ShowUnitProperty(goHandle, pGOParser, parentElmHandle : Integer; prIndex1, prIndex2, iShift, jShift : Integer);
      [*] = ;begin
      [*] = ;   var prop1, prop2 : Integer = 0;
      [*] = ;   if goHandle <> 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := prIndex1;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      prop1 := IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := prIndex2;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      prop2 := IntRegister1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := pGOParser;
      [*] = ;      IntRegister1 := pArmyUnits;
      [*] = ;      IntRegister2 := prIndex1;
      [*] = ;      MapExecuteState('GetUnitPropertyByParser');
      [*] = ;      prop1 := IntRegister3;
      [*] = ;
      [*] = ;      IntRegister0 := pGOParser;
      [*] = ;      IntRegister1 := pArmyUnits;
      [*] = ;      IntRegister2 := prIndex2;
      [*] = ;      MapExecuteState('GetUnitPropertyByParser');
      [*] = ;      prop2 := IntRegister3;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var str : String = '';
      [*] = ;   if (prIndex1 <> 0) then
      [*] = ;   str := IntToStr(prop1) + '/' + IntToStr(prop2)
      [*] = ;   else
      [*] = ;   if prIndex2 <> 0 then
      [*] = ;   str := IntToStr(prop2)
      [*] = ;   else
      [*] = ;   log('Unknown property in battle.CreateUnitWindow state');
      [*] = ;
      [*] = ;   const posX = 218;
      [*] = ;   const posY = 83;
      [*] = ;   var width, height : Integer;
      [*] = ;   var fontHandleN: String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_tactics,'PropertyValue',gc_gui_fontsize_default,'',fontHandleN);   // Unit Properties
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandleN, str, width, height);
      [*] = ;   var elmHandle : Integer = _gui_CreateText('unitinfo_properties_'+IntToStr(prIndex2), parentElmHandle, str, 'halParentLeft', 'valParentTop', posX-32 + 88*iShift, posY + 33*jShift, width+40, height+8{80, 26}, 'halLeft', 'valTop',  fontHandleN, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.7);
      [*] = ;   SetGUIElementTextAlign(elmHandle, 'halLeft', 'valMiddle', 32, 0);
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DrawMeterByCurMinMaxValue(elmHandle, curValue, minValue, maxValue, posX : Integer; posY : Integer; MatName : String);
      [*] = ;begin
      [*] = ;   if (curValue-minValue)>(maxValue-minValue) then
      [*] = ;   curValue := maxValue;
      [*] = ;   var length : Integer = Floor(((curValue-minValue)/(maxValue-minValue))*121);
      [*] = ;   if (length>121) then length := 121;
      [*] = ;   if (length>0) then
      [*] = ;   _gui_CreateImage('', elmHandle, MatName, 'halParentLeft', 'valParentTop', posX, posY, length, 14, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;const cEventHandler = 'ShowInfoWindow';
      [*] = ;const pressState = 'battle.CloseUnitWindow';
      [*] = ;
      [*] = ;if (goHandle = 0) and (pGOParser = 0) then
      [*] = ;exit;
      [*] = ;
      [*] = ;var heroHandle : Integer = 0;
      [*] = ;var pHero : Integer = 0;
      [*] = ;var unitID : Integer = 0;
      [*] = ;var isHero : Boolean = false;
      [*] = ;var bSummoned : Boolean = false;
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   gIntRegister_InfoUnitUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;   unitID := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;   isHero := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bIsHero);
      [*] = ;   bSummoned := GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bSummoned);
      [*] = ;
      [*] = ;   var heroUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iHeroUID);
      [*] = ;   if (heroUID<>0) then
      [*] = ;   begin
      [*] = ;      heroHandle := GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;      pHero := ParserSelectGameObject(heroHandle);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   unitID := ParserGetIntValueByKeyByHandle(pGOParser, 'UnitID');
      [*] = ;
      [*] = ;   isHero := ParserGetBoolValueByKeyByHandle(pGOParser, 'IsHero');
      [*] = ;   if isHero then
      [*] = ;   begin
      [*] = ;      var heroUID : Integer = ParserGetIntValueByKeyByHandle(pGOParser, 'HeroUID');
      [*] = ;      heroHandle := GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;      pHero := ParserSelectGameObject(heroHandle);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var top : Integer = _gui_GetLayerI();
      [*] = ;var tag : Integer = 0;
      [*] = ;var posX, posY : Integer;
      [*] = ;var xOff, yOff : Integer;
      [*] = ;var sizeX, sizeY : Integer;
      [*] = ;var width, height : Integer;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;var pUnitPrototype : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnitPrototype, 'Rank');
      [*] = ;
      [*] = ;var fontHandleH1, fontHandleH2, fontHandleT, fontHandleN, fontHandleN2: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_largest,'',fontHandleH1);   // Header lvl 1
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_large,'',fontHandleH2); // Header lvl 2
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_default,'',fontHandleT); // Simple text
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'PropertyValue',gc_gui_fontsize_default,'',fontHandleN);   // Unit Properties
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'SpellDuration',gc_gui_fontsize_small,'',fontHandleN2); // Icons Index
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('battle_unitpanel', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;bVisible := True;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElement('battle_unitpanel', top, 'halLeft', 'valTop', 0, 0, GetViewerWidth, GetViewerHeight, 0);
      [*] = ;SetGUIElementVisible(elmParentHandle, true);
      [*] = ;var pAbilities : Integer = gPrototypeData.abilities.handle;
      [*] = ;
      [*] = ;// Unit icon
      [*] = ;var elmImageHandle : Integer = _gui_CreateImage('', elmParentHandle, 'unitinfo.icon.background', 'halParentMiddle', 'valParentMiddle', -133, -172, 72, 95, 0);
      [*] = ;elmImageHandle := _gui_CreateImage('unitinfo_icon_'+IntToStr(unitID), elmImageHandle, 'icon.unit.'+IntToStr(unitID), 'halParentMiddle', 'valParentMiddle', posX, posY, 70, 93, 0);
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;
      [*] = ;// Background
      [*] = ;posX := 0;
      [*] = ;posY := 0;
      [*] = ;var elmBackgroundHandle : Integer = _gui_CreateImage('unitinfo_background', elmParentHandle, 'battle.unitinfo.background.type2', 'halParentMiddle', 'valParentMiddle', posX, posY, 493, 620, 0);
      [*] = ;SetGUIAllowEvents(elmBackgroundHandle, true, false, false);
      [*] = ;
      [*] = ;var karma : Integer = ParserGetIntValueByKeyByHandle(pUnitPrototype, 'Karma');
      [*] = ;var karmaText : String = GetLocaleTableListItemByID('gui', IntToStr(300+3+karma));
      [*] = ;
      [*] = ;// Header unit name
      [*] = ;var text : String;
      [*] = ;if (isHero) then
      [*] = ;begin
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle, 'GetClass');
      [*] = ;   var classInd : Integer = IntRegister0;
      [*] = ;   text := GetLocaleTableListItemByID('hero_class', IntToStr(classInd));
      [*] = ;end
      [*] = ;else
      [*] = ;text := GetLocaleTableListItemByID('unit', IntToStr(unitID))+' ('+karmaText+')';
      [*] = ;
      [*] = ;if (heroHandle <> 0) then
      [*] = ;begin
      [*] = ;   var heroName : String;
      [*] = ;   _hero_GetName(heroHandle, heroName);
      [*] = ;   text := heroName + ' '+ text;
      [*] = ;end;
      [*] = ;posX := 0;
      [*] = ;posY := -262;
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('unitinfo_name', elmBackgroundHandle, text, 'halParentMiddle', 'valParentMiddle', posX, posY, 420, 48, 'halMiddle', 'valMiddle', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;// Unit description
      [*] = ;posX := 64;
      [*] = ;posY := 440;
      [*] = ;sizeX := 351;
      [*] = ;sizeY := 114-2;
      [*] = ;var scrollParentHandle : Integer = CreateScrollerParent('scroll_layer', elmBackgroundHandle, 'halParentLeft', 'valParentTop', 'misc.blank.black.alpha.0', posX, posY, sizeX+8, sizeY, sizeX+5, 0, sizeY);
      [*] = ;text := GetLocaleTableListItemByID('unit', IntToStr(unitID)+'.description');
      [*] = ;text := GetGUIWrappedTextFormatByFont(fontHandleT, text, sizeX);
      [*] = ;GetGUIElementFontTextFormatRect(fontHandleT, text, width, height);
      [*] = ;posX := 0;
      [*] = ;posY := 2;
      [*] = ;var elmScrollToTextImage : Integer = _gui_CreateImage('scroll_to_text', scrollParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmScrollToTextImage, text, 'halParentLeft', 'valParentTop', posX, posY, width, height+4, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;SetGUIElementHeight(scrollParentHandle, height+7);
      [*] = ;
      [*] = ;// Text: ������ � ��������
      [*] = ;text := GetLocaleTableListItemByID('gui', '84');
      [*] = ;posX := 0;
      [*] = ;posY := -15;
      [*] = ;GetGUIElementFontTextFormatRect(fontHandleT, text, width, height);
      [*] = ;elmTextHandle := _gui_CreateText('unitinfo_text_skills', elmBackgroundHandle, text, 'halParentMiddle', 'valParentMiddle', posX, posY-5, width+10, height, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;// Text: ����������� �������
      [*] = ;text := GetLocaleTableListItemByID('gui', '85');
      [*] = ;posX := 0;
      [*] = ;posY := 54;
      [*] = ;GetGUIElementFontTextFormatRect(fontHandleT, text, width, height);
      [*] = ;elmTextHandle := _gui_CreateText('unitinfo_text_effects', elmBackgroundHandle, text, 'halParentMiddle', 'valParentMiddle', posX, posY, width+10, height, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;// Unit level
      [*] = ;var unitLevel : Integer = 0;
      [*] = ;if goHandle <> 0 then
      [*] = ;unitLevel := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLevel)
      [*] = ;else
      [*] = ;unitLevel := ParserGetIntValueByKeyByHandle(pGOParser, 'Level');
      [*] = ;
      [*] = ;text := IntToStr(unitLevel);
      [*] = ;posX := 114-12;
      [*] = ;posY := 190-12;
      [*] = ;elmTextHandle := _gui_CreateText('unitinfo_level', elmBackgroundHandle, text, 'halParentLeft', 'valParentTop', posX-1, posY-1, 24, 24, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 0.8);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;var heroName : String;
      [*] = ;_hero_GetName(heroHandle, heroName);
      [*] = ;
      [*] = ;// Exp bar
      [*] = ;var minExp : Integer = 0;
      [*] = ;var maxExp : Integer = 0;
      [*] = ;
      [*] = ;if isHero then
      [*] = ;begin
      [*] = ;   IntRegister0 := unitLevel;
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle ,'GetNeededExpForLevel');
      [*] = ;   minExp := IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := unitLevel+1;
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle ,'GetNeededExpForLevel');
      [*] = ;   maxExp := IntRegister1;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister0 := unitID;
      [*] = ;   IntRegister1 := unitLevel;
      [*] = ;   MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;   minExp := IntRegister2;
      [*] = ;
      [*] = ;   IntRegister0 := unitID;
      [*] = ;   IntRegister1 := unitLevel+1;
      [*] = ;   MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;   maxExp := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;var curExp : Integer = 0;
      [*] = ;if (goHandle<>0) then
      [*] = ;curExp := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iExperience)
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (ParserGetParent(pGOParser)<>gPrototypeData.units.handle) then
      [*] = ;   curExp := ParserGetIntValueByKeyByHandle(pGOParser, 'Exp')
      [*] = ;   else
      [*] = ;   curExp := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;posX := 53;
      [*] = ;posY := 200;
      [*] = ;DrawMeterByCurMinMaxValue(elmBackgroundHandle, curExp, minExp, maxExp, posX, posY, 'unitpanel.meter.violet');
      [*] = ;
      [*] = ;var elmHandle : Integer = _gui_CreateImage('unitinfo_exp_meter', elmBackgroundHandle, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', posX, posY, 121, 14, 0);
      [*] = ;SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;
      [*] = ;// Unit params
      [*] = ;var emptyProperty : Integer = 0;
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, gc_battle_unit_iCurLife, gc_battle_unit_iMaxLife, 0, 0);
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, gc_battle_unit_iCurStamina, gc_battle_unit_iMaxStamina, 1, 0)
      [*] = ;else
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iMaxStamina, 1, 0);
      [*] = ;
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iCurMoral, 2, 0);
      [*] = ;
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iSpeed, 0, 1);
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iAttack, 1, 1);
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iCounterAttack, 2, 1);
      [*] = ;
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iDefence, 0, 2);
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iRangedDefence, 1, 2);
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iResist, 2, 2);
      [*] = ;
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iRangedAttack, 0, 3);
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iShootingRange, 1, 3);
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, gc_battle_unit_iCurAmmo, gc_battle_unit_iMaxAmmo, 2, 3)
      [*] = ;else
      [*] = ;ShowUnitProperty(goHandle, pGOParser, elmBackgroundHandle, emptyProperty, gc_battle_unit_iMaxAmmo, 2, 3);
      [*] = ;
      [*] = ;if isHero then
      [*] = ;text := ''
      [*] = ;else
      [*] = ;begin
      [*] = ;   case unitRank of
      [*] = ;      1 : text := GetLocaleTableListItemByID('gui', 'I');
      [*] = ;      2 : text := GetLocaleTableListItemByID('gui', 'II');
      [*] = ;      3 : text := GetLocaleTableListItemByID('gui', 'III');
      [*] = ;      4 : text := GetLocaleTableListItemByID('gui', 'IV');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (text<>'') then
      [*] = ;begin
      [*] = ;   posX := 249-12;
      [*] = ;   posY := 221-11;
      [*] = ;   elmTextHandle := _gui_CreateText('unitinfo_rank_'+IntToStr(unitRank), elmBackgroundHandle, text, 'halParentLeft', 'valParentTop', posX-1, posY, 24, 24, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_CurGameMode<>gc_GameModeMenu) then
      [*] = ;begin
      [*] = ;   if (pGOParser<>0) then
      [*] = ;   IntRegister0 := pGOParser
      [*] = ;   else
      [*] = ;   IntRegister0 := pUnitPrototype;
      [*] = ;   IntRegister1 := goHandle;
      [*] = ;   MapExecuteState('GetUnitPaymentByParser');
      [*] = ;   var goldPayment : Integer = IntRegister2;
      [*] = ;   var gemPayment : Integer = IntRegister3;
      [*] = ;
      [*] = ;   var goldPrice : Integer = ParserGetIntValueByKeyByHandle(pUnitPrototype, 'GoldPrice');
      [*] = ;   var gemPrice : Integer = ParserGetIntValueByKeyByHandle(pUnitPrototype, 'GemPrice');
      [*] = ;
      [*] = ;   //if (goldPayment<>0) then
      [*] = ;   begin
      [*] = ;      var xMove : Integer = -50;
      [*] = ;      posX := 170+xMove;
      [*] = ;      posY := 238;
      [*] = ;      xOff := 100-xMove*2+10-10;
      [*] = ;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX-18, posY, 90, 42, 0);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      SetGUIElementHint(elmImageHandle, GetLocaleTableListItemByID('gui','310')+' ('+GetLocaleTableListItemByID('gui','712')+')');
      [*] = ;      //SetGUIElementHint(elmImageHandle, 'gui|712');
      [*] = ;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      if (goldPayment=0) and (goldPrice=0) then
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.35)
      [*] = ;      else
      [*] = ;      elmTextHandle := _gui_CreateText('goldpayment', elmBackgroundHandle, IntToStr(goldPrice)+' ('+IntToStr(goldPayment)+')', 'halParentLeft', 'valParentTop', posX+GetGUIElementWidth(elmImageHandle)-2, posY+5, 84, 35, 'halLeft', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;      var addicon : String = 'astral.beforebattle.curenergy.sign';
      [*] = ;      var addX : Integer = -18;
      [*] = ;      var addY : Integer = 12;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, addicon, 'halParentLeft', 'valParentTop', posX+addX, posY+addY, 0, 0, 0);
      [*] = ;
      [*] = ;      if (goldPayment=0) then
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.5);
      [*] = ;   end;
      [*] = ;
      [*] = ;   //if (gemPayment<>0) then
      [*] = ;   begin
      [*] = ;      var xMove : Integer = -50;
      [*] = ;      posX := 170+xMove;
      [*] = ;      posY := 238;
      [*] = ;      xOff := 100-xMove*2+10-10;
      [*] = ;
      [*] = ;      posX := posX+xOff;
      [*] = ;      posY := posY-3+2;
      [*] = ;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX-18, posY, 90, 42, 0);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      //SetGUIElementHint(elmImageHandle, 'gui|713');
      [*] = ;      SetGUIElementHint(elmImageHandle, GetLocaleTableListItemByID('gui','311')+' ('+GetLocaleTableListItemByID('gui','713')+')');
      [*] = ;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      if (gemPayment=0) and (gemPrice=0) then
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.35)
      [*] = ;      else
      [*] = ;      elmTextHandle := _gui_CreateText('gempayment', elmBackgroundHandle, IntToStr(gemPrice)+' ('+IntToStr(gemPayment)+')', 'halParentLeft', 'valParentTop', posX+GetGUIElementWidth(elmImageHandle), posY+5+3, 84, 35, 'halLeft', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;
      [*] = ;      var addicon : String = 'astral.beforebattle.curenergy.sign';
      [*] = ;      var addX : Integer = -18;
      [*] = ;      var addY : Integer = 15;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, addicon, 'halParentLeft', 'valParentTop', posX+addX, posY+addY, round(30*1), round(29*1), 0);
      [*] = ;      if (gemPayment=0) then
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.35);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// Scroll button skills left
      [*] = ;// Scroll button skills right
      [*] = ;// Scroll button effects left
      [*] = ;// Scroll button effects right
      [*] = ;// Close button
      [*] = ;posX := 223;
      [*] = ;posY := 559;
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('unitinfo_close_btn', elmBackgroundHandle, '', 'map.radialhero.btn.move.cancel', 'halParentLeft', 'valParentTop', posX, posY, 51, 51, pressState, '', 0);
      [*] = ;
      [*] = ;var pUnitParser : Integer;
      [*] = ;if goHandle <> 0 then
      [*] = ;pUnitParser := ParserSelectGameObject(goHandle)
      [*] = ;else
      [*] = ;pUnitParser := pGOParser;
      [*] = ;
      [*] = ;//Medal icon
      [*] = ;var pUnitMedals : Integer = ParserSelectByHandleByKey(pUnitParser, 'Medals');
      [*] = ;posX := 36;
      [*] = ;posY := 81;
      [*] = ;yOff := 40;
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to ParserGetCountByHandle(pUnitMedals)-1 do
      [*] = ;begin
      [*] = ;   var pUnitMedal : Integer = ParserSelectByHandleByIndex(pUnitMedals, i);
      [*] = ;   var medalID : Integer = ParserGetIntValueByKeyByHandle(pUnitMedal, 'MedalID');
      [*] = ;   var hint : String = 'medal|' + IntToStr(medalID) + '|LT'; {GetLocaleTableListItemByID('medal', IntToStr(medalID))}
      [*] = ;   elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, 'icon.medal.'+IntToStr(medalID), 'halParentLeft', 'valParentTop', posX, posY+i*yOff, 27, 27, Tag);
      [*] = ;   elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'icons.round.44x44.cover', 'halParentLeft', 'valParentTop', -4, -6, (45-9), (47-9), cEventHandler, hint, tag);
      [*] = ;   SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'icons.round.44x44.cover' + '.pressed', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1); // GEC Check. this line was added when creating gui script library
      [*] = ;   var strTag : String = 'Medal.' + IntToStr(medalID);
      [*] = ;   SetGUIElementStringTag(elmBtnHandle, strTag);
      [*] = ;end;
      [*] = ;
      [*] = ;// skills icon places
      [*] = ;posX := 61;
      [*] = ;posY := 306;
      [*] = ;xOff := 47;
      [*] = ;//var skillCount : Integer = 2; //TODO
      [*] = ;//for i := 0 to skillCount-1 do
      [*] = ;//elmBtnHandle := _gui_CreateButton('', elmBackgroundHandle, '', 'castle.building.icon.small.empty', 'halParentLeft', 'valParentTop', posX+i*xOff, posY, 43, 43, curState, '', tag);
      [*] = ;
      [*] = ;var ind : Integer = 0;
      [*] = ;
      [*] = ;if (bSummoned) then
      [*] = ;begin
      [*] = ;   var abilIndex : Integer = 103;
      [*] = ;   tag := gc_gui_battle_btnControlAbilityBaseTag + abilIndex;
      [*] = ;   var strTag : String = 'Ability.' + IntToStr(abilIndex);
      [*] = ;   var hint : String =  'ability|'+IntToStr(abilIndex);
      [*] = ;   elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, 'icon.ability.'+IntToStr(abilIndex), 'halParentLeft', 'valParentTop', posX+ind*xOff, posY, 43, 43, tag);
      [*] = ;   elmBtnHandle := _gui_CreateButton('ability_slot', elmImageHandle, 'ability_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 43, 43, cEventHandler, hint, tag);
      [*] = ;   SetGUIElementStringTag(elmBtnHandle, strTag);
      [*] = ;   ind := ind + 1;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pAbilities)-1 do
      [*] = ;begin
      [*] = ;   var pAbility : Integer = ParserSelectByHandleByIndex(pAbilities, i);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'AbilityID');
      [*] = ;   var visible : Boolean = ParserGetBoolValueByKeyByHandle(pAbility, 'Visible');
      [*] = ;
      [*] = ;   IntRegister0 := abilID;
      [*] = ;   StateMachineExecuteState(initMachine, 'GetAbilityParserByID', 0);
      [*] = ;   pAbility := IntRegister1;
      [*] = ;   var abilIndex : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'Index');
      [*] = ;   var numeric : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'Numeric');
      [*] = ;
      [*] = ;   if visible then
      [*] = ;   begin
      [*] = ;      var check : Boolean = false;
      [*] = ;      if goHandle <> 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := abilID;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;         check := (IntRegister1 > 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := 0;
      [*] = ;         IntRegister1 := pGOParser;
      [*] = ;         IntRegister2 := heroHandle;
      [*] = ;         IntRegister3 := abilID;
      [*] = ;         MapExecuteState('CheckUnitAbility');
      [*] = ;         check := (IntRegister4 > 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if check then
      [*] = ;      begin
      [*] = ;         tag := gc_gui_battle_btnControlAbilityBaseTag + abilIndex;
      [*] = ;         var strTag : String = 'Ability.' + IntToStr(abilIndex);
      [*] = ;         var hint : String =  'ability|'+IntToStr(abilIndex);
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, 'icon.ability.'+IntToStr(abilIndex), 'halParentLeft', 'valParentTop', posX+ind*xOff, posY, 43, 43, tag);
      [*] = ;         elmBtnHandle := _gui_CreateButton('ability_slot', elmImageHandle, 'ability_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 43, 43, cEventHandler, hint, tag);
      [*] = ;         SetGUIElementStringTag(elmBtnHandle, strTag);
      [*] = ;         ind := ind + 1;
      [*] = ;
      [*] = ;         if (numeric>0) then
      [*] = ;         begin
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeStrategy) or (gIntRegister_CurGameMode=gc_GameModeMenu) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 0;
      [*] = ;               IntRegister1 := gIntRegister_UnitInfoParser;
      [*] = ;               IntRegister2 := GetGameObjectHandleByUniqueId(gIntRegister_CurHeroUIDInfo);
      [*] = ;               IntRegister3 := abilID;
      [*] = ;               MapExecuteState('CheckUnitAbility');
      [*] = ;               gIntRegister_AbilityPower := IntRegister4;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := abilID;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;               gIntRegister_AbilityPower := IntRegister1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            gIntRegister_AbilityPower := 0;
      [*] = ;            {var tag : Integer = GetGUIElementTag(elmHandle);
      [*] = ;            if (abilID>0) and (abilID<=12) then
      [*] = ;            gIntRegister_AbilityPower := tag;}
      [*] = ;            var width, height : Integer;
      [*] = ;            GetGUIElementFontTextFormatRect(fontHandleN2, IntToStr(gIntRegister_AbilityPower), width, height);
      [*] = ;            elmImageHandle := _gui_CreateImage('unitinfo_ability_power', elmBtnHandle, 'pixel.0.0.0', 'halParentRight', 'valParentBottom', -width-8, -height-3+3, width+6+2, height+1, gIntRegister_AbilityPower);
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 1);
      [*] = ;            elmTextHandle := _gui_CreateText('unitinfo_ability_power_text', elmImageHandle, IntToStr(gIntRegister_AbilityPower), 'halParentLeft', 'valParentTop', 0, 1, width+7, height, 'halMiddle', 'valMiddle', fontHandleN2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.7);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;{}
      [*] = ;
      [*] = ;// effects icon places
      [*] = ;posX := 60;
      [*] = ;posY := 380;
      [*] = ;xOff := 47;
      [*] = ;
      [*] = ;var pUnitEffects : Integer = ParserSelectByHandleByKey(pUnitParser, 'Effects');
      [*] = ;var count : Integer = 0;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pUnitEffects)-1 do
      [*] = ;begin
      [*] = ;   var pUnitEffect : Integer = ParserSelectByHandleByIndex(pUnitEffects, i);
      [*] = ;   if ParserGetBoolValueByKeyByHandle(pUnitEffect, 'Visible') = false then
      [*] = ;   continue;
      [*] = ;
      [*] = ;   {var EffectID : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'EffectID');}
      [*] = ;   var ParentUpgradeID : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'ParentUpgradeID');
      [*] = ;   var ParentSpellID : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'ParentSpellID');
      [*] = ;   var effectPower : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'Power');
      [*] = ;   var effectDuration : Integer = ParserGetIntValueByKeyByHandle(pUnitEffect, 'Duration');
      [*] = ;
      [*] = ;   IntRegister0 := pUnitEffect;
      [*] = ;   MapExecuteState('bat.GetEffectIDByParser');
      [*] = ;   var effectID : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var imageName : String = '';
      [*] = ;   var hint : String = '';
      [*] = ;   var strTag : String = '';
      [*] = ;   if (ParentUpgradeID>0) then
      [*] = ;   begin
      [*] = ;      //imageName := 'icon.ability.' + IntToStr(ParentUpgradeID);
      [*] = ;      imageName := 'icon.skill.' + IntToStr(ParentUpgradeID);
      [*] = ;      hint := 'effects|'+IntToStr(effectID); //GetLocaleTableListItemByID('effects', IntToStr(effectID));
      [*] = ;      //strTag := 'Abilitiy.' + IntToStr(ParentUpgradeID);
      [*] = ;      strTag := 'Effects.' + IntToStr(EffectID) + '.' + IntToStr(ParentUpgradeID);
      [*] = ;      if (effectPower<>0) then
      [*] = ;      strTag := strTag + '.' + FloatToStr(Abs(effectPower));
      [*] = ;   end;
      [*] = ;   if (ParentSpellID>0) then
      [*] = ;   begin
      [*] = ;      imageName := 'icon.spell.' + IntToStr(ParentSpellID);
      [*] = ;      hint := 'effects|'+IntToStr(effectID); //GetLocaleTableListItemByID('effects', IntToStr(effectID));
      [*] = ;      strTag := 'EffectsSpell.' + IntToStr(EffectID) + '.' + IntToStr(ParentSpellID);
      [*] = ;   end;
      [*] = ;   if (imageName<>'') then
      [*] = ;   begin
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmBackgroundHandle, imageName, 'halParentLeft', 'valParentTop', posX+count*xOff, posY, 45, 45, Tag);
      [*] = ;      {hint := hint + gc_gui_BreakLine + gc_gui_BreakLine + GetLocaleTableListItemByID('gui', '86') + ': ';
      [*] = ;      if (effectDuration=0) then
      [*] = ;      hint := hint + GetLocaleTableListItemByID('gui', '87')
      [*] = ;      else
      [*] = ;      hint := hint + IntToStr(effectDuration);}
      [*] = ;      elmBtnHandle := _gui_CreateButton('effect', elmImageHandle, '', 'icons.52x52.cover', 'halParentLeft', 'valParentTop', 0, -1, 45, 47, cEventHandler, hint, effectDuration);
      [*] = ;      SetGUIElementStringTag(elmBtnHandle, strTag);
      [*] = ;      if (effectDuration>0) then
      [*] = ;      begin
      [*] = ;         var width, height : Integer;
      [*] = ;         GetGUIElementFontTextFormatRect(fontHandleN2, IntToStr(effectDuration), width, height);
      [*] = ;         elmImageHandle := _gui_CreateImage('unitinfo_effect_duration', elmBtnHandle, 'pixel.0.0.0', 'halParentRight', 'valParentBottom', -width-8, -height-3+3, width+6+2, height+1, effectDuration);
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 1);
      [*] = ;         elmTextHandle := _gui_CreateText('unitinfo_effect_duration_text', elmImageHandle, IntToStr(effectDuration), 'halParentLeft', 'valParentTop', 0, 1, width+7, height, 'halMiddle', 'valMiddle', fontHandleN2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.7);
      [*] = ;      end;
      [*] = ;      count := count + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//
      [*] = ;// Start
      [*] = ;//
      [*] = ;{
      [*] = ;// skills icon places
      [*] = ;posX := floor(GetgDbgFloat0);
      [*] = ;posY := floor(GetgDbgFloat1);
      [*] = ;xOff := 47;
      [*] = ;
      [*] = ;// --- Layer with scroll
      [*] = ;var elmScrollLayer : Integer = AddNewElementByClassNameParent('unitinfo_level_skills_bar', 'TXGuiLayer', 0, elmBackgroundHandle);
      [*] = ;SetGUIAllowEvents(elmScrollLayer, True, False, False);
      [*] = ;SetGUIElementAlign(elmScrollLayer, 'halParentLeft', 'valParentTop');
      [*] = ;SetGUIElementAllPositionRect(elmScrollLayer, posX, posY, 8*xOff, 45);
      [*] = ;SetGUIElementMaterial(elmScrollLayer, 'misc.blank.black.alpha.0');
      [*] = ;SetGUIScrollEnabled(elmScrollLayer, True);
      [*] = ;//var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;var elmHScroll : Integer = GetGUIElementHScroll(elmScrollLayer);
      [*] = ;var effectsCount : Integer = 0;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pAbilities)-1 do
      [*] = ;begin
      [*] = ;   var pAbility : Integer = ParserSelectByHandleByIndex(pAbilities, i);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'AbilityID');
      [*] = ;   var visible : Boolean = ParserGetBoolValueByKeyByHandle(pAbility, 'Visible');
      [*] = ;
      [*] = ;   IntRegister0 := abilID;
      [*] = ;   StateMachineExecuteState(initMachine, 'GetAbilityParserByID', 0);
      [*] = ;   pAbility := IntRegister1;
      [*] = ;   var abilIndex : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'Index');
      [*] = ;
      [*] = ;   if visible then
      [*] = ;   begin
      [*] = ;      IntRegister0 := abilID;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;      if (IntRegister1 > 0) then
      [*] = ;      begin
      [*] = ;         tag := gc_gui_battle_btnControlAbilityBaseTag + abilIndex;
      [*] = ;         var strTag : String = 'Ability.' + IntToStr(abilIndex);
      [*] = ;         var hint : String =  'ability|'+IntToStr(abilIndex);
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmScrollLayer, 'icon.ability.'+IntToStr(abilIndex), 'halParentLeft', 'valParentTop', 0+ind*xOff, 0, 43, 43, tag);
      [*] = ;         elmBtnHandle := _gui_CreateButton('ability_slot', elmImageHandle, 'spell_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 43, 43, cEventHandler, hint, tag);
      [*] = ;         SetGUIElementStringTag(elmBtnHandle, strTag);
      [*] = ;         ind := ind + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SetGUIElementWidth(elmScrollLayer, xOff*effectsCount); //all width
      [*] = ;
      [*] = ;// Effects scroller
      [*] = ;posX := floor(GetgDbgFloat2);
      [*] = ;posY := 0;
      [*] = ;xOff := 311;
      [*] = ;var curScrollPos : Float = GetGUIScrollBarPosition(elmHScroll);
      [*] = ;elmBtnHandle := _gui_CreateButton('battle_effect_scroll_left', elmScrollLayer, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', posX, posY, 43, 43, '', '', gc_gui_battle_btnEffectsScrollLeft);
      [*] = ;//SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'common.scroller.left.disabled.alpha', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;if effectsCount <= 6 then
      [*] = ;SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;else
      [*] = ;begin
      [*] = ;   if curScrollPos > 0 then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, true)
      [*] = ;   else
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;end;
      [*] = ;
      [*] = ;elmBtnHandle := _gui_CreateButton('battle_effect_scroll_right', elmScrollLayer, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', posX+xOff, posY, 43, 43, '', '', gc_gui_battle_btnEffectsScrollRight);
      [*] = ;//SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'common.scroller.right.disabled.alpha', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;if effectsCount <= 6 then
      [*] = ;SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;else
      [*] = ;begin
      [*] = ;   if curScrollPos < 1 then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, true)
      [*] = ;   else
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;end;
      [*] = ;}
      [*] = ;//
      [*] = ;// Finish
      [*] = ;//
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;const cEventState = 'battle.CloseUnitWindow';
      [*] = ;_gui_RootWindowAdd(elmParentHandle,cRootWindowModal);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;ExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

