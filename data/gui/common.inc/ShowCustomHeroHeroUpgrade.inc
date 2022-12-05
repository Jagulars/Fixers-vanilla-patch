section.begin
   Name = ShowCustomHeroHeroUpgrade
   Description : struct.begin
      [*] = ;IntRegister0 - parent element handle
   struct.end
   Code : struct.begin
      [*] = ;var gui_elem_handle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\SHOWCUSTOMHEROHEROUPGRADE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;function _inet_GetSkillLimit(battle : TInetBattle; skillID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   if (battle.hero[battle.curhero].class1=battle.hero[battle.curhero].class2) then
      [*] = ;   Result := 5
      [*] = ;   else
      [*] = ;   Result := 3;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetUnitProperty(heroHandle, indProperty : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := indProperty;
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle, 'GetProperty');
      [*] = ;   Result := IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;function _inet_CreateParamInfo(elmParent : Integer; battle : TInetBattle; posX, posY, sizeX : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var leader, health, magic , initiative, siege, mobility, life, attack, counterAttack, defence, rangedDefence, resist, speed, rangedAttack, shootingRange, ammo, stamina, moral, level : Integer = 0;
      [*] = ;   var bHeroExist : Boolean = (battle.hero[battle.curhero].class1>0);
      [*] = ;   if (bHeroExist) then
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = _inet_GetHeroUnit;
      [*] = ;      leader := GetUnitProperty(goHandle, gc_map_hero_iLeaderProperty);
      [*] = ;      health := GetUnitProperty(goHandle, gc_map_hero_iHealthProperty);
      [*] = ;      magic  := GetUnitProperty(goHandle, gc_map_hero_iMagicProperty);
      [*] = ;      initiative := GetUnitProperty(goHandle, gc_map_hero_iInitiative);
      [*] = ;      siege := GetUnitProperty(goHandle, gc_map_hero_iSiege);
      [*] = ;      mobility := GetUnitProperty(goHandle, gc_map_hero_iMobility);
      [*] = ;      life := GetUnitProperty(goHandle, gc_map_hero_iLife);
      [*] = ;      attack := GetUnitProperty(goHandle, gc_map_hero_iAttack);
      [*] = ;      counterAttack := GetUnitProperty(goHandle, gc_map_hero_iCounterAttack);
      [*] = ;      defence := GetUnitProperty(goHandle, gc_map_hero_iDefence);
      [*] = ;      rangedDefence := GetUnitProperty(goHandle, gc_map_hero_iRangedDefence);
      [*] = ;      resist := GetUnitProperty(goHandle, gc_map_hero_iResist);
      [*] = ;      speed := GetUnitProperty(goHandle, gc_map_hero_iSpeed);
      [*] = ;      rangedAttack := GetUnitProperty(goHandle, gc_map_hero_iRangedAttack);
      [*] = ;      shootingRange := GetUnitProperty(goHandle, gc_map_hero_iShootingRange);
      [*] = ;      ammo := GetUnitProperty(goHandle, gc_map_hero_iAmmo);
      [*] = ;      stamina := GetUnitProperty(goHandle, gc_map_hero_iStamina);
      [*] = ;      moral := GetUnitProperty(goHandle, gc_map_hero_iMoral);
      [*] = ;      level := battle.hero[battle.curhero].level;
      [*] = ;      if (speed<1) then speed := 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   procedure ShowUnitPropertyExt(matName : String; langKey, elmParent, value : Integer; delimeter : String; prIndex2, xShift, yShift, xSize, ySize, ixPos, yxPos : Integer);
      [*] = ;   begin
      [*] = ;      var str : String = '';
      [*] = ;      if (bHeroExist) then
      [*] = ;         str := IntToStr(value);
      [*] = ;      var xSizeCut : Integer = 0;
      [*] = ;
      [*] = ;      const cFontParamsColorR = gc_gui_fontcolor_HeaderR;
      [*] = ;      const cFontParamsColorG = gc_gui_fontcolor_HeaderG;
      [*] = ;      const cFontParamsColorB = gc_gui_fontcolor_HeaderB;
      [*] = ;      const cFontParamsColorA = 1;
      [*] = ;      var fontHandle : String;
      [*] = ;      _gui_GetFont(gc_gui_fontsection_tactics,'PropertyValue',gc_gui_fontsize_default,'',fontHandle); // HeaderS
      [*] = ;      var elmTextHandle : Integer = _gui_CreateText('unitproperty', elmParent, str, 'halParentLeft', 'valParentTop', xShift + ixPos * (xSize)+1, yShift + yxPos * (ySize)+1, xSize, ySize, 'halLeft', 'valMiddle', fontHandle, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;
      [*] = ;      var elmImageHandle : Integer = _gui_CreateImage('unitproperty_image', elmTextHandle, matName, 'halParentLeft', 'valParentTop', -46, 0, 0, 0, 0);
      [*] = ;      if (str='') then
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.125)
      [*] = ;      else
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.9);
      [*] = ;
      [*] = ;      posX := xShift + ixPos * (xSize)-39;
      [*] = ;      posY := yShift + yxPos * (ySize);
      [*] = ;
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('', elmParent, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX, posY-2, xSize-8-xSizeCut, ySize-1, '', '', 0);
      [*] = ;      _gui_ft_AttachHint_I5(elmBtnHandle,'VVK.HintASERCallback',cFT_ASER_Ability,langKey,langKey,value,0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var xShift, yShift, xSize, ySize : Integer;
      [*] = ;   xShift := posX;
      [*] = ;   yShift := posY;
      [*] = ;   xSize := sizeX;
      [*] = ;   ySize := 34;
      [*] = ;
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.life.47x36', 1, elmParent, life, '', -1, xShift, yShift, xSize, ySize, 0, 0);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.stamina.47x36', 11, elmParent, stamina, '', -1, xShift, yShift, xSize, ySize, 1, 0);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.morale.47x36', 12, elmParent, moral, '', -1, xShift, yShift, xSize, ySize, 2, 0);
      [*] = ;
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.speed.47x36', 7, elmParent, speed, '', -1, xShift, yShift, xSize, ySize, 0, 1);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.attack.47x36', 2, elmParent, attack, '', -1, xShift, yShift, xSize, ySize, 1, 1);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.counterattack.47x36', 3, elmParent, counterattack, '', -1, xShift, yShift, xSize, ySize, 2, 1);
      [*] = ;
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.defence.47x36', 4, elmParent, defence, '', -1, xShift, yShift, xSize, ySize, 0, 2);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.rangeddefence.47x36', 5, elmParent, rangeddefence, '', -1, xShift, yShift, xSize, ySize, 1, 2);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.resist.47x36', 6, elmParent, resist, '', -1, xShift, yShift, xSize, ySize, 2, 2);
      [*] = ;
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.rangedattack.47x36', 8, elmParent, rangedattack, '', -1, xShift, yShift, xSize, ySize, 0, 3);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.rangeddistance.47x36', 9, elmParent, shootingrange, '', -1, xShift, yShift, xSize, ySize, 1, 3);
      [*] = ;   ShowUnitPropertyExt('gamepanel01.unitparam.ammo.47x36', 10, elmParent, ammo, '', -1, xShift, yShift, xSize, ySize, 2, 3);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ShowCustomHeroHeroUpgrade(battle : TInetBattle);
      [*] = ;begin
      [*] = ;   var parentHandle : Integer = gui_elem_handle;
      [*] = ;   _inet_CreateHeroUnit(battle);
      [*] = ;
      [*] = ;   //const cBtnLevelUp = 101;
      [*] = ;   const cBtnBaseTagNewClass = 480;
      [*] = ;   const cBtnBaseTagBonusID = 490;
      [*] = ;   const cBtnBaseTagHeroSkill = 500;
      [*] = ;   const cBtnBaseTagHeroSkillRemove = 600;
      [*] = ;   const cEventState = 'EventCustomHeroHeroUpgrade';
      [*] = ;
      [*] = ;   var fontHandle, fontHandleB : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;
      [*] = ;   var posX : Integer = 0;
      [*] = ;   var posY : Integer = 0;
      [*] = ;   var xOff : Integer = 56;
      [*] = ;   var yOff : Integer = 56;
      [*] = ;
      [*] = ;   var heroClass : Integer = _inet_GetClass(battle.hero[battle.curhero]);
      [*] = ;
      [*] = ;   if (battle.hero[battle.curhero].level=10) and (battle.hero[battle.curhero].class2=0) then
      [*] = ;   begin
      [*] = ;      const cNewClassMarginB = -278;
      [*] = ;      var elmNewClass : Integer = _gui_CreateImage('newclass', parentHandle, gc_gui_material_blank_0, 'halParentMiddle', 'valParentBottomHeight', 0, cNewClassMarginB, 75*4, yOff*2, 0);
      [*] = ;
      [*] = ;      //class to proceed
      [*] = ;      var newClassID : Integer = heroClass*4+heroClass;
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('', elmNewClass, 'icon.frame.item', 'halParentLeft', 'valParentTop', 0*75, 0, 0, 0, 0);
      [*] = ;      elmHandle := _gui_CreateImage('', elmHandle, 'icon.heroclass.' + IntToStr(newClassID-1), 'halParentLeft', 'valParentTop', 5, 5, 0, 0, 0);
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('', elmHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, '', cBtnBaseTagNewClass+battle.hero[battle.curhero].class1);
      [*] = ;      SetGUIElementStringTag(elmBtnHandle, 'Class.' + IntToStr(newClassID));
      [*] = ;
      [*] = ;      var ind : Integer = 0;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to 3 do
      [*] = ;      begin
      [*] = ;         if ((i+1)<>heroClass) then
      [*] = ;         begin
      [*] = ;            var newClassID : Integer = heroClass*4+i+1;
      [*] = ;            var elmHandle : Integer = _gui_CreateImage('', elmNewClass, 'icon.frame.item', 'halParentLeft', 'valParentTop', (ind+1)*75, 0, 0, 0, 0);
      [*] = ;            elmHandle := _gui_CreateImage('', elmHandle, 'icon.heroclass.' + IntToStr(newClassID-1), 'halParentLeft', 'valParentTop', 5, 5, 0, 0, 0);
      [*] = ;            var elmBtnHandle : Integer = _gui_CreateButton('', elmHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, '', cBtnBaseTagNewClass+i+1);
      [*] = ;            SetGUIElementStringTag(elmBtnHandle, 'Class.' + IntToStr(newClassID));
      [*] = ;            ind := ind+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      const cNewClassDescriptionMarginT = 68;
      [*] = ;      var elmFrameHandle : Integer = _gui_CreateFrameBorder('frame', elmNewClass, 'halParentMiddle', 'valParentTop', 0, cNewClassDescriptionMarginT+45, 244+203, GetGUIElementFontHeight(fontHandle)*6+4);
      [*] = ;      elmHandle := _gui_CreateImage('', elmNewClass, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, cNewClassDescriptionMarginT, 0, 0, 0);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      // hero class
      [*] = ;      const cSkillsMarginB = -298;
      [*] = ;      var elmHeroSkills : Integer = _gui_CreateImage('skills', parentHandle, gc_gui_material_blank_0, 'halParentMiddle', 'valParentBottomHeight', 0, cSkillsMarginB, xOff*6, yOff*2, 0);
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to gc_MaxHeroSkillCount do
      [*] = ;      begin
      [*] = ;         posX := ((i) mod 6)*xOff;
      [*] = ;         posY := ((i) div 6)*yOff;
      [*] = ;         var elmHandle : Integer = _gui_CreateImage('', elmHeroSkills, 'icon.frame.item', 'halParentLeft', 'valParentTop', posX-5, posY-5, 0, 0, 0);
      [*] = ;      end;
      [*] = ;      //GetLocaleTableListItemByID('gui', '602');
      [*] = ;      var pSkills : Integer = gPrototypeData.skills.handle;
      [*] = ;      if (heroClass>0) then
      [*] = ;      begin
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateImageSimple('heropanel_skill_open_slot', elmHeroSkills, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;         //SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;         var hint : String;
      [*] = ;         var elmHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'icon.heroclass.'+IntToStr(heroClass-1), 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;         var elmBtnHandle : Integer = _gui_CreateButton('skill_slot', elmSlotHandle, 'skill_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', 0);
      [*] = ;         _gui_ft_AttachHint_I2(elmBtnHandle,'VVK.HintHeroClassCallback',heroClass,0);
      [*] = ;
      [*] = ;         var baseSkillCount, additionalSkillCount : Integer = 0;
      [*] = ;         for i:=0 to gc_MaxHeroSkillCount-1 do
      [*] = ;         begin
      [*] = ;            var skillID : Integer = battle.hero[battle.curhero].arrskills[i].id;
      [*] = ;            if (skillID>0) then
      [*] = ;            begin
      [*] = ;               var pSkill : Integer = ParserSelectByHandleByIndex(pSkills, skillID);
      [*] = ;               var skClass : Integer = ParserGetIntValueByKeyByHandle(pSkill, 'Class');
      [*] = ;               if (skClass>0) then
      [*] = ;               begin
      [*] = ;                  var skillLevel : Integer = battle.hero[battle.curhero].arrskills[i].level;
      [*] = ;                  if (skClass=battle.hero[battle.curhero].class1) then
      [*] = ;                  begin
      [*] = ;                     if skillLevel > 3 then
      [*] = ;                     begin
      [*] = ;                        additionalSkillCount := additionalSkillCount + skillLevel-3;
      [*] = ;                        skillLevel := 3;
      [*] = ;                     end;
      [*] = ;                     baseSkillCount := baseSkillCount + skillLevel;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (skClass=battle.hero[battle.curhero].class2) then
      [*] = ;                     additionalSkillCount := additionalSkillCount + skillLevel;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for i:=0 to gc_MaxHeroSkillCount-1 do
      [*] = ;         begin
      [*] = ;            posX := ((i+1) mod 6)*xOff;
      [*] = ;            posY := ((i+1) div 6)*yOff;
      [*] = ;            var skillID : Integer = battle.hero[battle.curhero].arrskills[i].id;
      [*] = ;            if (skillID>0) then
      [*] = ;            begin
      [*] = ;               var skillLevel : Integer = battle.hero[battle.curhero].arrskills[i].level;
      [*] = ;               var skillIconNum : Integer = 1+(skillID-1)*5+(skillLevel-1);
      [*] = ;               var elmSlotHandle : Integer = _gui_CreateImageSimple('heropanel_skill_open_slot', elmHeroSkills, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;               //SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;               var elmHandle : Integer = _gui_CreateImage('', elmSlotHandle, 'icon.heroskill.'+IntToStr(skillIconNum), 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 0);
      [*] = ;               var elmBtnHandle : Integer = _gui_CreateButton('skill_slot', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', cBtnBaseTagHeroSkillRemove+i);
      [*] = ;               _gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroSkillCallback',skillID,skillIconNum,cEventState,'');
      [*] = ;               SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 1, 0.5, 0.5, 0.5, 1);
      [*] = ;               if (battle.hero[battle.curhero].class2>0) and (baseSkillCount<=10) and (additionalSkillCount>0) and (skillLevel <= 3) then
      [*] = ;               begin
      [*] = ;                  var pSkill : Integer = ParserSelectByHandleByIndex(pSkills, battle.hero[battle.curhero].arrskills[i].id);
      [*] = ;                  var skClass : Integer = ParserGetIntValueByKeyByHandle(pSkill, 'Class');
      [*] = ;                  if (skClass>0) and (skClass=battle.hero[battle.curhero].class1) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                     SetGUIElementUserBlend(elmBtnHandle, 0.0);
      [*] = ;                     SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var posX : Integer = 0;
      [*] = ;      var posY : Integer = 4;
      [*] = ;      const cNewSkillStripMarginB = -234;
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('', parentHandle, 'element.strip.451' 'halParentMiddle', 'valParentBottomHeight', 0, cNewSkillStripMarginB, 0, 0, 0);
      [*] = ;      var text : String = 'menu|181';
      [*] = ;      var elmTextHandle : Integer = _gui_CreateText('' , elmHandle, text, 'halParentLeft', 'valParentTop', posX, posY, GetGUIElementWidth(elmHandle), 25, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;      //const cLevelUpMarginB = 12;
      [*] = ;      //var elmBtnNewLevelHandle : Integer = _gui_CreateButton('', elmHeroSkills, '', 'castle.hero.recruit.window.btn.recruit', 'halParentMiddle', 'valParentBottom', 0, cLevelUpMarginB, 0, 0, cEventState, '', cBtnLevelUp);
      [*] = ;      //var elmTextHandle : Integer = _gui_CreateText('', elmBtnNewLevelHandle, GetLocaleTableListItemByID('gui', '602'), 'halParentLeft', 'valParentTop', 24, 14, 88, 23, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;      var skillCount : Integer;
      [*] = ;      for i:=0 to gc_MaxHeroSkillCount-1 do
      [*] = ;      begin
      [*] = ;         if (battle.hero[battle.curhero].arrskills[i].id>0) then
      [*] = ;         skillCount := skillCount+battle.hero[battle.curhero].arrskills[i].level;
      [*] = ;      end;
      [*] = ;
      [*] = ;      xOff := 56;
      [*] = ;      yOff := 56;
      [*] = ;      const cHeroSkilsLevelUpMarginB = 24+46;
      [*] = ;      var elmHeroSkillsLevelUp : Integer = _gui_CreateImage('skills', elmHeroSkills, gc_gui_material_blank_0, 'halParentMiddle', 'valParentTop', 0, {GetGUIElementPositionY(elmBtnNewLevelHandle)+GetGUIElementHeight(elmBtnNewLevelHandle)+}GetGUIElementHeight(elmHeroSkills)+cHeroSkilsLevelUpMarginB, xOff*7, yOff*2, 0);
      [*] = ;
      [*] = ;      //SetGUIElementEnabled(elmBtnNewLevelHandle, False);
      [*] = ;      var maxHeroClassSkillsToLearn : Integer = 7;
      [*] = ;      if (battle.hero[battle.curhero].class2>0) and (battle.hero[battle.curhero].class1<>battle.hero[battle.curhero].class2) then
      [*] = ;      maxHeroClassSkillsToLearn := maxHeroClassSkillsToLearn*2;
      [*] = ;
      [*] = ;      for i:=0 to maxHeroClassSkillsToLearn-1 do
      [*] = ;      begin
      [*] = ;         posX := ((i) mod 7)*xOff;
      [*] = ;         posY := ((i) div 7)*yOff;
      [*] = ;         var elmFrameHandle : Integer = _gui_CreateImage('', elmHeroSkillsLevelUp, 'icon.frame.item', 'halParentLeft', 'valParentTop', posX-5, posY-5, 0, 0, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var ind : Integer = 0;
      [*] = ;      for i:=0 to ParserGetCountByHandle(pSkills)-1 do
      [*] = ;      begin
      [*] = ;         posX := ((ind) mod 7)*xOff;
      [*] = ;         posY := ((ind) div 7)*yOff;
      [*] = ;         var pSkill : Integer = ParserSelectByHandleByIndex(pSkills, i);
      [*] = ;         var skillID : Integer = ParserGetIntValueByKeyByHandle(pSkill, 'SkillID');
      [*] = ;         var skClass : Integer = ParserGetIntValueByKeyByHandle(pSkill, 'Class');
      [*] = ;         if (skClass>0) and (skClass=battle.hero[battle.curhero].class1) then
      [*] = ;         begin
      [*] = ;            var allowed : Boolean = true;
      [*] = ;            var mySkillLevel : Integer = 0;
      [*] = ;            var j : Integer;
      [*] = ;            for j:=0 to gc_MaxHeroSkillCount-1 do
      [*] = ;            begin
      [*] = ;               if (skillID=battle.hero[battle.curhero].arrskills[j].id) then
      [*] = ;               begin
      [*] = ;                  mySkillLevel := battle.hero[battle.curhero].arrskills[j].level;
      [*] = ;                  if (mySkillLevel>=_inet_GetSkillLimit(battle, skillID)) then
      [*] = ;                  begin
      [*] = ;                     allowed := false;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (mySkillLevel=0) and (battle.hero[battle.curhero].arrskills[gc_MaxHeroSkillCount-1].id>0) then
      [*] = ;            allowed := false;
      [*] = ;
      [*] = ;            if (battle.hero[battle.curhero].level>=gc_map_MaxHeroLevel) then
      [*] = ;            allowed := False;
      [*] = ;
      [*] = ;            var hint : String;
      [*] = ;            if (mySkillLevel=5) then mySkillLevel := 4;
      [*] = ;            var skillIconNum : Integer = 1+(skillID-1)*5+(mySkillLevel);
      [*] = ;            var elmSlotHandle : Integer = _gui_CreateImage('heropanel_skill_open_slot', elmHeroSkillsLevelUp, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;            //SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;            elmHandle := _gui_CreateImage('', elmSlotHandle, 'icon.heroskill.'+IntToStr(skillIconNum), 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 0);
      [*] = ;            var tag : Integer = cBtnBaseTagHeroSkill+skillID;
      [*] = ;            var elmBtnHandle : Integer = _gui_CreateButton('skill_slot_new', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;            _gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroSkillCallback',skillID,skillIconNum,cEventState,'');
      [*] = ;            if (not allowed) then
      [*] = ;            begin
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;               SetGUIElementUserBlend(elmBtnHandle, 0.0);
      [*] = ;               SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;            end;
      [*] = ;            ind := ind+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (battle.hero[battle.curhero].class1<>battle.hero[battle.curhero].class2) then
      [*] = ;      begin
      [*] = ;         for i:=0 to ParserGetCountByHandle(pSkills)-1 do
      [*] = ;         begin
      [*] = ;            posX := ((ind) mod 7)*xOff;
      [*] = ;            posY := ((ind) div 7)*yOff;
      [*] = ;            var pSkill : Integer = ParserSelectByHandleByIndex(pSkills, i);
      [*] = ;            var skillID : Integer = ParserGetIntValueByKeyByHandle(pSkill, 'SkillID');
      [*] = ;            var skClass : Integer = ParserGetIntValueByKeyByHandle(pSkill, 'Class');
      [*] = ;            if (skClass>0) and (skClass=battle.hero[battle.curhero].class2) then
      [*] = ;            begin
      [*] = ;               var allowed : Boolean = true;
      [*] = ;               var mySkillLevel : Integer = 0;
      [*] = ;               var j : Integer;
      [*] = ;               for j:=0 to gc_MaxHeroSkillCount-1 do
      [*] = ;               begin
      [*] = ;                  if (skillID=battle.hero[battle.curhero].arrskills[j].id) then
      [*] = ;                  begin
      [*] = ;                     mySkillLevel := battle.hero[battle.curhero].arrskills[j].level;
      [*] = ;                     if (mySkillLevel>=_inet_GetSkillLimit(battle, skillID)) then
      [*] = ;                     begin
      [*] = ;                        allowed := false;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (mySkillLevel=0) and (battle.hero[battle.curhero].arrskills[gc_MaxHeroSkillCount-1].id>0) then
      [*] = ;               allowed := false;
      [*] = ;
      [*] = ;               if (battle.hero[battle.curhero].level>=gc_map_MaxHeroLevel) then
      [*] = ;               allowed := False;
      [*] = ;
      [*] = ;               var hint : String;
      [*] = ;               if (mySkillLevel=5) then mySkillLevel := 4;
      [*] = ;               var skillIconNum : Integer = 1+(skillID-1)*5+(mySkillLevel);
      [*] = ;               var elmSlotHandle : Integer = _gui_CreateImage('heropanel_skill_open_slot', elmHeroSkillsLevelUp, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;               //SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;               elmHandle := _gui_CreateImage('', elmSlotHandle, 'icon.heroskill.'+IntToStr(skillIconNum), 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 0);
      [*] = ;               var tag : Integer = cBtnBaseTagHeroSkill+skillID;
      [*] = ;               var elmBtnHandle : Integer = _gui_CreateButton('skill_slot_new', elmSlotHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;               _gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroSkillCallback',skillID,skillIconNum,cEventState,'');
      [*] = ;               if (not allowed) then
      [*] = ;               begin
      [*] = ;                  SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                  SetGUIElementUserBlend(elmBtnHandle, 0.0);
      [*] = ;                  SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;               end;
      [*] = ;               ind := ind+1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var bonusType, bonusValue : Integer = 0;
      [*] = ;   _unit_GetFixedHeroBonus(heroClass, battle.hero[battle.curhero].level+1, bonusType, bonusValue);
      [*] = ;   var abilityPower : Integer;
      [*] = ;   if (bonusValue>0) then
      [*] = ;   case bonusType of
      [*] = ;      0 : abilityPower := battle.hero[battle.curhero].leader;
      [*] = ;      1 : abilityPower := battle.hero[battle.curhero].magic;
      [*] = ;      2 : abilityPower := battle.hero[battle.curhero].health;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var abilityID : Integer;
      [*] = ;   if (bonusType<3) then // life
      [*] = ;   abilityID := 116+bonusType
      [*] = ;   else
      [*] = ;   abilityID := 1; // Жизнь
      [*] = ;
      [*] = ;   const cHeroBonusMarginB = 0;
      [*] = ;   var heroBonusStripPosY : Integer = -58;//GetGUIElementPositionY(elmHeroSkills)+GetGUIElementPositionY(elmHeroSkillsLevelUp)+GetGUIElementHeight(elmHeroSkillsLevelUp)+cHeroBonusMarginB-yOff;
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', parentHandle, 'element.strip.240', 'halParentMiddle', 'valParentBottomHeight', 0, heroBonusStripPosY, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmHandle, 'menu|180', 'halParentLeft', 'valParentTop', 0, -4, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   var tag : Integer = cBtnBaseTagBonusID+bonusType;
      [*] = ;   var heroBonusPosY : Integer = heroBonusStripPosY+yOff+4;
      [*] = ;   var elmHeroBonus : Integer = _gui_CreateImage('', parentHandle, gc_gui_material_blank_0, 'halParentMiddle', 'valParentBottomHeight', 0, heroBonusPosY, xOff, yOff, 0);
      [*] = ;
      [*] = ;   posX := -211;
      [*] = ;   posY := 18;
      [*] = ;   yOff := 34;
      [*] = ;   var text, matName, elementName : String;
      [*] = ;   var i : Integer;
      [*] = ;   var bClassSelect : Boolean = (battle.hero[battle.curhero].level=10) and (battle.hero[battle.curhero].class2=0);
      [*] = ;   for i:=0 to 2 do
      [*] = ;   begin
      [*] = ;      var value : Integer = 0;
      [*] = ;      case i of
      [*] = ;         0 : begin
      [*] = ;            value := battle.hero[battle.curhero].health;
      [*] = ;            text := IntToStr(value);
      [*] = ;            if (bonusValue>0) and (bonusType=2) and (not bClassSelect) then
      [*] = ;            text := text+' (+1)';
      [*] = ;            matName := 'gamepanel04.unitparam.health';
      [*] = ;            elementName := 'heroparam_health';
      [*] = ;            abilityPower := battle.hero[battle.curhero].health;
      [*] = ;            abilityID := 118;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            value := battle.hero[battle.curhero].leader;
      [*] = ;            text := IntToStr(value);
      [*] = ;            if (bonusValue>0) and (bonusType=0) and (not bClassSelect) then
      [*] = ;            text := text+' (+1)';
      [*] = ;            matName := 'gamepanel04.unitparam.leader';
      [*] = ;            elementName := 'heroparam_leader';
      [*] = ;            abilityPower := battle.hero[battle.curhero].leader;
      [*] = ;            abilityID := 116;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            value := battle.hero[battle.curhero].magic;
      [*] = ;            text := IntToStr(value);
      [*] = ;            if (bonusValue>0) and (bonusType=1) and (not bClassSelect) then
      [*] = ;            text := text+' (+1)';
      [*] = ;            matName := 'gamepanel04.unitparam.magic';
      [*] = ;            elementName := 'heroparam_magic';
      [*] = ;            abilityPower := battle.hero[battle.curhero].magic;
      [*] = ;            abilityID := 117;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      var fontHandle : String;
      [*] = ;      _gui_GetFont(gc_gui_fontsection_tactics,'PropertyValue',gc_gui_fontsize_default,'',fontHandle); // HeaderS
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('unitproperty_image', elmHeroBonus, matName, 'halParentLeft', 'valParentTop', posX, posY+yOff*i, 0, 0, 0);
      [*] = ;      if (value=0) then
      [*] = ;      SetGUIElementUserBlend(elmHandle, 0.325)
      [*] = ;      else
      [*] = ;      SetGUIElementUserBlend(elmHandle, 0.9);
      [*] = ;      if (heroClass>0) then
      [*] = ;      var elmTextHandle : Integer = _gui_CreateText('', elmHeroBonus, text, 'halParentLeft', 'valParentTop', posX+38, posY+yOff*i, 0, GetGUIElementHeight(elmHandle), 'halLeft', 'valBottomHeight', fontHandle, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;      if (value=0) then
      [*] = ;      SetGUIElementUserBlend(elmTextHandle, 0.4);
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton(elementName, elmHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, -2, 70, GetGUIElementHeight(elmHandle), '', '', 0);
      [*] = ;      _gui_ft_AttachHint_I2(elmBtnHandle,'VVK.HintHeroParamCallback',abilityID,abilityPower);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var goHandle : Integer = _inet_GetHeroUnit;
      [*] = ;   var initiative : Integer = GetUnitProperty(goHandle, gc_map_hero_iInitiative);
      [*] = ;   posX := 193;
      [*] = ;   posY := -49;
      [*] = ;   text := IntToStr(initiative);
      [*] = ;   matName := 'shell.heroparam.initiative';
      [*] = ;   //matName := 'gamepanel04.unitparam.magic';
      [*] = ;   elementName := 'heroparam_initiative';
      [*] = ;   abilityPower := initiative;
      [*] = ;   elmHandle := _gui_CreateImage('unitproperty_image', elmHeroBonus, matName, 'halParentLeft', 'valParentTop', posX-5, posY-6+yOff*i, 0, 0, 0);
      [*] = ;   if (initiative=0) then
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.325)
      [*] = ;   else
      [*] = ;   SetGUIElementUserBlend(elmHandle, 0.9);
      [*] = ;   if (heroClass>0) then
      [*] = ;   begin
      [*] = ;      elmTextHandle := _gui_CreateText('', elmHeroBonus, text, 'halParentLeft', 'valParentTop', posX+38+7, posY+yOff*i-2, 0, GetGUIElementHeight(elmHandle), 'halLeft', 'valBottomHeight', fontHandle, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;      if (initiative=0) then
      [*] = ;      SetGUIElementUserBlend(elmTextHandle, 0.4);
      [*] = ;   end;
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton(elementName, elmHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, -2, 70, GetGUIElementHeight(elmHandle), '', '', 0);
      [*] = ;   var abilityIndex : Integer = 101; //gc_map_hero_iInitiative
      [*] = ;   _gui_ft_AttachHint_I5(elmBtnHandle,'VVK.HintASERCallback',cFT_ASER_Ability,abilityIndex,abilityIndex,initiative,0);
      [*] = ;
      [*] = ;   _inet_CreateParamInfo(elmHeroBonus, battle, -50, -4, 82);
      [*] = ;end;
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;   ShowCustomHeroHeroUpgrade(gEditorCustomPlayerTemporary)
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (gBoolRegister_IsHotSeat) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_HotSeatActivePlayer=0) then
      [*] = ;         ShowCustomHeroHeroUpgrade(gHotSeatPlayer1)
      [*] = ;      else
      [*] = ;         ShowCustomHeroHeroUpgrade(gHotSeatPlayer2)
      [*] = ;   end
      [*] = ;   else
      [*] = ;      ShowCustomHeroHeroUpgrade(gInetBattle);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

