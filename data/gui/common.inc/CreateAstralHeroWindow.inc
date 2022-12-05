section.begin
   Name = CreateAstralHeroWindow
   Code : struct.begin
      [*] = ;BoolRegister0 := true;
      [*] = ;IntRegister0 := 0;
      [*] = ;IntRegister1 := 0;
      [*] = ;MapExecuteState('GetHeroImportData');
      [*] = ;var pAstralHero : Integer = _misc_ParserGetOrCreateByKey('astral_hero',false);
      [*] = ;
      [*] = ;var fontHandleT, fontHandleN, fontHandle2: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandleT);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Numbers',gc_gui_fontsize_default,'',fontHandleN); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_largest,'',fontHandle2); // HeaderM
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('astral_hero', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElementExt('astral_hero', _gui_GetLayerI(), 'halMiddle', 'valMiddle', 0, 0, 0, 0, 0);
      [*] = ;
      [*] = ;var i,elmHandle,elmHeaderHandle,elmTextHandle,elmSlotHandle,elmBtnHandle,elmImageHandle  : Integer;
      [*] = ;var text : String;
      [*] = ;const cEventState = 'EventAstralHeroWindow';
      [*] = ;
      [*] = ;// background
      [*] = ;var height : Integer = 710;
      [*] = ;var width : Integer = 700;
      [*] = ;var elmBackground : Integer = _gui_CreateLargeWindow(elmParentHandle, 'background', 'halParentMiddle', 'valParentMiddle', 0, 0, height, width, false);
      [*] = ;SetGUIAllowEvents(elmBackground, True, False, False);
      [*] = ;
      [*] = ;// header
      [*] = ;elmHeaderHandle := GetGUIElementIndexByNameParent('header', elmBackground);
      [*] = ;var heroName : String = ParserGetValueByKeyByHandle(pAstralHero, 'Name');
      [*] = ;elmTextHandle := _gui_CreateText('', elmHeaderHandle, GetLocaleTableListItemByID('hero_names',heroName), 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;// portrait
      [*] = ;var portraitName : String = ParserGetValueByKeyByHandle(pAstralHero, 'Portrait');
      [*] = ;elmHandle := _gui_CreateImageSimple('portrait', elmBackground, portraitName, 'halParentLeft', 'valParentTop', 46, 78);
      [*] = ;
      [*] = ;// hero class
      [*] = ;var classIndex : Integer;
      [*] = ;var heroLevel : Integer = ParserGetIntValueByKeyByHandle(pAstralHero, 'Level');
      [*] = ;var class1 : Integer = ParserGetIntValueByKeyByHandle(pAstralHero, 'Class1');
      [*] = ;var class2 : Integer = ParserGetIntValueByKeyByHandle(pAstralHero, 'Class2');
      [*] = ;if class2 = 0 then
      [*] = ;   classIndex := class1
      [*] = ;else
      [*] = ;   classIndex := 4 * class1 + class2;
      [*] = ;if heroLevel >= 20 then
      [*] = ;   classIndex := classIndex + 16;
      [*] = ;
      [*] = ;text := GetLocaleTableListItemByID('glossary', 'skill.1') +' '+ IntToStr(heroLevel);
      [*] = ;elmTextHandle := _gui_CreateText('hero_level', elmBackground, text, 'halParentMiddle', 'valParentTop', 0, 30, 190, 28, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;text := GetLocaleTableListItemByID('hero_class', IntToStr(classIndex));
      [*] = ;elmTextHandle := _gui_CreateText('class_name', elmBackground, text, 'halParentMiddle', 'valParentTop', 0, 56, 190, 28, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;SetGUIElementHint(elmTextHandle, GetLocaleTableListItemByID('hero_class', IntToStr(classIndex)+'.description'));
      [*] = ;
      [*] = ;
      [*] = ;// skills
      [*] = ;var pSkills : Integer = ParserSelectByHandleByKey(pAstralHero, 'Skills');
      [*] = ;const cSkillsMargin = 100;
      [*] = ;var xOff : Integer = 56;
      [*] = ;var yOff : Integer = 56;
      [*] = ;var elmHeroSkills : Integer = _gui_CreateImage('skills', elmBackground, gc_gui_material_blank_0, 'halParentMiddle', 'valParentTop', 0, cSkillsMargin, xOff*6, yOff*2, 0);
      [*] = ;
      [*] = ;var pSkill, skillID, level, posX, posY, skillIconNum : Integer;
      [*] = ;for i:=0 to gc_MaxHeroSkillCount do
      [*] = ;begin
      [*] = ;   posX := ((i) mod 6)*xOff;
      [*] = ;   posY := ((i) div 6)*yOff;
      [*] = ;   elmHandle := _gui_CreateImage('', elmHeroSkills, 'icon.frame.item', 'halParentLeft', 'valParentTop', posX-5, posY-5, 0, 0, 0);
      [*] = ;   
      [*] = ;   if i = 0 then
      [*] = ;   begin
      [*] = ;      elmSlotHandle := _gui_CreateImageSimple('heropanel_skill_open_slot', elmHeroSkills, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;         //SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;      elmHandle := _gui_CreateImage('', elmSlotHandle, 'icon.heroclass.'+IntToStr(classIndex-1), 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;      elmBtnHandle := _gui_CreateButton('skill_slot', elmSlotHandle, 'skill_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', 0);
      [*] = ;      _gui_ft_AttachHint_I2(elmBtnHandle,'VVK.HintHeroClassCallback',classIndex,0);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      pSkill := ParserSelectByHandleByIndex(pSkills, i-1);
      [*] = ;      skillID := ParserGetIntValueByKeyByHandle(pSkill, 'SkillID');
      [*] = ;      if (skillID>0) then
      [*] = ;      begin
      [*] = ;         level := ParserGetIntValueByKeyByHandle(pSkill, 'Level');
      [*] = ;         skillIconNum := 1+(skillID-1)*5+(level-1);
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('heropanel_skill_open_slot', elmHeroSkills, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         //SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;         elmHandle := _gui_CreateImage('', elmSlotHandle, 'icon.heroskill.'+IntToStr(skillIconNum), 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('skill_slot', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', 0);
      [*] = ;         _gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroSkillCallback',skillID,skillIconNum,'','');
      [*] = ;         //SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 1, 0.5, 0.5, 0.5, 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;const cAstralHeroApproveBtnTag = 100;
      [*] = ;const cAstralHeroCancelBtnTag = 101;
      [*] = ;const cBtnScrollBaseTag = 200;
      [*] = ;
      [*] = ;var itemsCount : Integer = ParserGetCountByHandle(gPrototypeData.items.handle);
      [*] = ;
      [*] = ;var scrollPosUnits, scrollPosItems, scrollPosSpells : Integer = 0;
      [*] = ;var pScrollPosTmp : Integer = _misc_ParserGetOrCreateByKey('pHeroScrollPosTmp',false);
      [*] = ;if (ParserGetCountByHandle(pScrollPosTmp)=0) then
      [*] = ;begin
      [*] = ;   ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems', scrollPosItems);
      [*] = ;   ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'scrollPosSpells', scrollPosSpells);
      [*] = ;   ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits', scrollPosUnits);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   scrollPosItems := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems');
      [*] = ;   scrollPosSpells := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'scrollPosSpells');
      [*] = ;   scrollPosUnits := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateBelongingsRow(index, pBelongings, posY, imageSize, maxScrollCount : Integer);
      [*] = ;begin
      [*] = ;   var count : Integer = ParserGetCountByHandle(pBelongings);
      [*] = ;   var header : String;
      [*] = ;   var i, posX, pBelonging, id, tag, tmpCount, elmBelongingHandle,elmHandle,elmBtnHandle,curScrollPos : Integer;
      [*] = ;   case index of
      [*] = ;      0 : begin
      [*] = ;         curScrollPos := scrollPosItems;
      [*] = ;         header := GetLocaleTableListItemByID('menu','204');
      [*] = ;      end;
      [*] = ;      1 : begin
      [*] = ;         curScrollPos := scrollPosSpells;
      [*] = ;         header := GetLocaleTableListItemByID('menu','203');
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         curScrollPos := scrollPosUnits;
      [*] = ;         header := GetLocaleTableListItemByID('menu','202');
      [*] = ;         count := count - 1; // don't show hero unit on units row
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   elmHandle := _gui_CreateImage('', elmBackground, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, posY, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmHandle, header, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   
      [*] = ;   if index = 2 then
      [*] = ;   posY := posY + 92
      [*] = ;   else
      [*] = ;   posY := posY + 70;
      [*] = ;   
      [*] = ;   var elmRowHandle : Integer = _gui_CreateImage('', elmBackground, gc_gui_material_blank_0, 'halParentMiddle', 'valParentTop', 0, posY, 0, 0, 0);
      [*] = ;   
      [*] = ;   var startInd : Integer = curScrollPos;
      [*] = ;   var endInd : Integer = maxScrollCount+curScrollPos;
      [*] = ;   var elmBtnArrowLeftHandle : Integer = _gui_CreateButton('arrowLeft', elmRowHandle, '', 'common.scroller.left', 'halParentMiddle', 'valParentMiddle', -(width div 2 - 50), 0, 0, 0, cEventState, '', cBtnScrollBaseTag+index*2);
      [*] = ;   if (curScrollPos<=0) then
      [*] = ;   begin
      [*] = ;      SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.4);
      [*] = ;      SetGUIElementEnabled(elmBtnArrowLeftHandle, False);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.8);
      [*] = ;   
      [*] = ;   var elmBtnArrowRightHandle : Integer = _gui_CreateButton('arrowRight', elmRowHandle, '', 'common.scroller.right', 'halParentMiddle', 'valParentMiddle', (width div 2 - 50), 0, 0, 0, cEventState, '', cBtnScrollBaseTag+index*2+1);
      [*] = ;   if ((count-curScrollPos)<=maxScrollCount) then
      [*] = ;   begin
      [*] = ;      SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.4);
      [*] = ;      SetGUIElementEnabled(elmBtnArrowRightHandle, False);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.8);
      [*] = ;   
      [*] = ;   var elmBelongingsHandle : Integer = _gui_CreateImage('', elmRowHandle, gc_gui_material_blank_0, 'halParentMiddle', 'valParentMiddle', 0, 0, 0, 0, 0);
      [*] = ;   var visualIndex : Integer = 0;
      [*] = ;   var material : String;
      [*] = ;   for i:=0 to count-1 do
      [*] = ;   begin
      [*] = ;      if (visualIndex < maxScrollCount) then
      [*] = ;      begin
      [*] = ;         if (i >= startInd) and (i < endInd) then
      [*] = ;         begin
      [*] = ;            if (count>maxScrollCount) then
      [*] = ;               tmpCount := maxScrollCount
      [*] = ;            else
      [*] = ;               tmpCount := count;
      [*] = ;            posX := -(tmpCount*(imageSize div 2));
      [*] = ;            elmBelongingHandle := _gui_CreateImage('', elmBelongingsHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentMiddle', posX+visualIndex*imageSize, 0, 0, 0, 0);
      [*] = ;
      [*] = ;            if index = 2 then
      [*] = ;               pBelonging := ParserSelectByHandleByIndex(pBelongings, i+1)
      [*] = ;            else 
      [*] = ;               pBelonging := ParserSelectByHandleByIndex(pBelongings, i);
      [*] = ;
      [*] = ;            case index of
      [*] = ;               0 : begin 
      [*] = ;                  id := ParserGetIntValueByKeyByHandle(pBelonging, 'ItemID');
	  [*] = ;                  if id > itemsCount-1 then // spell scroll
	  [*] = ;                     material := 'icon.scroll.'+IntToStr(ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.spells.handle, id-itemsCount), 'Level'))
	  [*] = ;                  else
	  [*] = ;                     material := 'icon.item.'+IntToStr(id);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmBelongingHandle, 'icon.frame.item', 'halParentLeft', 'valParentMiddle', -5, 0, 0, 0, 0);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmBelongingHandle, material, 'halParentLeft', 'valParentMiddle', 0, 0, 0, 0, 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('item_belonging_'+IntToStr(i), elmBelongingHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentMiddle', 0, 0, 52, 52, '', '', 0);
      [*] = ;                  _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',id,cFT_ItemPriceHide,ParserGetIntValueByKeyByHandle(pBelonging, 'Durability'),cFT_ItemHeroDefault,cEventState,'2');
      [*] = ;               end;
      [*] = ;               1 : begin 
      [*] = ;                  id := ParserGetIntValueByKeyByHandle(pBelonging, 'SpellID');
      [*] = ;                  elmHandle := _gui_CreateImage('', elmBelongingHandle, 'icon.frame.item', 'halParentLeft', 'valParentMiddle', -5, 0, 0, 0, 0);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmBelongingHandle, 'icon.spell.'+IntToStr(id), 'halParentLeft', 'valParentMiddle', 0, 0, 0, 0, 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('spell_belonging_'+IntToStr(i), elmBelongingHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentMiddle', 0, 0, 52, 52, '', '', 0);
      [*] = ;                  _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipSpell',id,$20000,$20000,cFT_SpellTypeDefault,cEventState,'1');
      [*] = ;               end;
      [*] = ;               2 : begin 
      [*] = ;                  id := ParserGetIntValueByKeyByHandle(pBelonging, 'UnitID');
      [*] = ;                  elmHandle := _gui_CreateImage('', elmBelongingHandle, 'astral.bonus.unit.frame', 'halParentLeft', 'valParentMiddle', -5, 0, 0, 0, 0);
      [*] = ;                  elmHandle := _gui_CreateImage('', elmBelongingHandle, 'icon.unit.'+IntToStr(id), 'halParentLeft', 'valParentMiddle', 0, 0, 70, 93, 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('unit_belonging_'+IntToStr(i), elmBelongingHandle, '', 'heropanel.unit.slot.cover', 'halParentLeft', 'valParentMiddle', 0, 0, 70, 93, '', '', 0);
      [*] = ;                  _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipUnit',cFT_UnitAstralHero,id,pBelonging,pBelongings,cEventState,'2');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            visualIndex := visualIndex+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;CreateBelongingsRow(0, ParserSelectByHandleByKey(pAstralHero,'Doll'), 220, 56, 9);
      [*] = ;CreateBelongingsRow(1, ParserSelectByHandleByKey(pAstralHero,'Spells'), 330, 56, 9);
      [*] = ;CreateBelongingsRow(2, ParserSelectByHandleByKey(pAstralHero,'Units'), 440, 74, 6);
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;elmHandle := _gui_CreateImage('', elmBackground, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 0, -32, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmHandle, '', 'map.radialhero.btn.move.cancel', 'halParentMiddle', 'valParentTop', 0, 0, 51, 51, cEventState, 'menu|47', cAstralHeroCancelBtnTag);
      [*] = ;
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;_gui_RootWindowAdd(elmParentHandle,cRootWindowModal);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;ExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

