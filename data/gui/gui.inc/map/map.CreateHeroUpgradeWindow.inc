section.begin
   Name = map.CreateHeroUpgradeWindow
   Description : struct.begin
      [*] = ;IntRegister0 - hero handle on STRATEGY map!
   struct.end
   Code : struct.begin
      [*] = ;var heroGOHandle : Integer = IntRegister0;
      [*] = ;var oldLevel : Integer = GetGameObjectIntValueIndByHandle(heroGOHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CREATEHEROUPGRADEWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;gIntRegister_HeroLevel := oldLevel + 1;
      [*] = ;GameObjectExecuteStateByHandle(heroGOHandle, 'GetClass');
      [*] = ;var classInd : Integer = IntRegister0;
      [*] = ;gStringRegister_HeroClass := GetLocaleTableListItemByID('hero_class', IntToStr(classInd));
      [*] = ;
      [*] = ;var fontHandleT, fontHandleH2, fontHandleH1: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_default,'',fontHandleT);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_large,'',fontHandleH2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_largest,'',fontHandleH1); // HeaderM
      [*] = ;
      [*] = ;var text : String;
      [*] = ;var width, height : Integer;
      [*] = ;if ((oldLevel+1)=20) then
      [*] = ;begin
      [*] = ;   classInd := classInd + 16;
      [*] = ;   text := GetLocaleTableListItemByID('hero_class', IntToStr(classInd)+'.description');
      [*] = ;end
      [*] = ;else
      [*] = ;   text := GetLocaleTableListItemByID('message', '10.description');
      [*] = ;
      [*] = ;var pGOParser : Integer = ParserSelectGameObject(heroGOHandle);
      [*] = ;var portrait : String = ParserGetValueByKeyByHandle(pGOParser, 'Portrait');
      [*] = ;_hero_GetName(heroGOHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;StringRegister0 := text;
      [*] = ;MapExecuteState('StringReplaceParams');
      [*] = ;text := StringRegister1;
      [*] = ;text := GetGUIWrappedTextFormatByFont(fontHandleT, text, 311-12);
      [*] = ;GetGUIElementFontTextFormatRect(fontHandleT, text, width, height);
      [*] = ;
      [*] = ;var noParamYOffset : Integer;
      [*] = ;var bLevel10 : Boolean = False;
      [*] = ;if ((oldLevel+1)=10) then
      [*] = ;   bLevel10 := True;
      [*] = ;
      [*] = ;if (bLevel10) then
      [*] = ;   noParamYOffset := -38
      [*] = ;else
      [*] = ;   noParamYOffset := 0;
      [*] = ;
      [*] = ;// achievements
      [*] = ;_achievement_Trigger(gc_achiev_hero_level_up,'');
      [*] = ;if bLevel10 then
      [*] = ;   _achievement_Trigger(gc_achiev_hero_level_10,'');
      [*] = ;if oldLevel=19 then
      [*] = ;   _achievement_Trigger(gc_achiev_hero_level_20,'');
      [*] = ;//
      [*] = ;var windowSizeY : Integer = 325+height+noParamYOffset;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'map_heroupgrade', 'halParentMiddle', 'valParentTop', 0, ((GetViewerHeight-(windowSizeY+330)) div 2), 345, windowSizeY, true);
      [*] = ;_gui_ft_UnRegister('map_heroupgrade');
      [*] = ;_gui_ft_Register('map_heroupgrade','VVK.FTooltipUpgradeWindow');
      [*] = ;//SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.65);
      [*] = ;//SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.75);
      [*] = ;var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;SetGUIElementVisible(elmHeaderHandle, False);
      [*] = ;SetGUIElementPressState(elmParentHandle,'EventQueryWindowModal');
      [*] = ;
      [*] = ;//Text message description
      [*] = ;var elmFrameHandle : Integer = _gui_CreateFrameBorder('frame', elmParentHandle, 'halParentLeft', 'valParentTop', 17, 185+noParamYOffset, 311, height+9);
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmFrameHandle, text, 'halParentLeft', 'valParentTop', 6, 6, width, height, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, 'element.strip.341', 'halParentLeft', 'valParentTop', 0, height+208+noParamYOffset, 0, 0, 0);
      [*] = ;text := 'gui|603';
      [*] = ;elmTextHandle := _gui_CreateText('skill_name', elmParentHandle, text, 'halParentMiddle', 'valParentTop', 0, height+208+5+noParamYOffset, 256, 28, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;//Hero portrait
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, portrait, 'halParentMiddle', 'valParentTop', 0, 28, 0, 0, 0);
      [*] = ;elmHandle := _gui_CreateImage('', elmHandle, 'gamepanel03.portrait.frame.big', 'halParentLeft', 'valParentTop', -87, -37, 0, 0, 0);
      [*] = ;
      [*] = ;elmHeaderHandle := _gui_CreateImage('header', elmParentHandle, 'element.header.strip.405', 'halParentMiddle', 'valParentTop', 0, 46-GetGUITextureHeight('element.header.strip.544'), 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHeaderHandle, 'gui|602', 'halParentLeft', 'valParentTop', 0, 7, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;//frame portrait
      [*] = ;//var elmFrameHandle : Integer = _gui_CreateFrameBorder('frame', elmParentHandle, 'halParentLeft', 'valParentTop', 237, 41+10, 298, 84-20);
      [*] = ;//var elmTextHandle : Integer = _gui_CreateText('', elmFrameHandle, textWraped, 'halParentLeft', 'valParentTop', 6, 6, 298-12, 84-20-12, 'halLeft', 'valMiddle', cFontSize, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;var bonusInd : Integer = -1;
      [*] = ;//if gIntRegister_HeroLevel <> 10 then
      [*] = ;//begin
      [*] = ;   IntRegister0 := gIntRegister_HeroLevel;
      [*] = ;   GameObjectExecuteStateByHandle(heroGOHandle, 'AddRandomBonus');
      [*] = ;   bonusInd := IntRegister1;
      [*] = ;//end;
      [*] = ;
      [*] = ;//Upgrade 1
      [*] = ;IntRegister0 := -1;
      [*] = ;IntRegister1 := -1;
      [*] = ;GameObjectExecuteStateByHandle(heroGOHandle, 'GetRandomUsedSkill');
      [*] = ;var skillID1 : Integer = IntRegister2;
      [*] = ;if skillID1 = -1 then
      [*] = ;begin
      [*] = ;   IntRegister0 := -1;
      [*] = ;   IntRegister1 := -1;
      [*] = ;   GameObjectExecuteStateByHandle(heroGOHandle, 'GetRandomSkill');
      [*] = ;   skillID1 := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := skillID1;
      [*] = ;GameObjectExecuteStateByHandle(heroGOHandle, 'GetSkillLevel');
      [*] = ;var SkillID1Lvl : Integer = IntRegister1 + 1;
      [*] = ;var skillIconNum : Integer = 1+(skillID1-1)*5+(SkillID1Lvl-1);
      [*] = ;var hint : String;
      [*] = ;const cEventState = 'map.ChooseHeroUpgrade';
      [*] = ;var tag : Integer;
      [*] = ;var elmBtnHandle : Integer;
      [*] = ;if (skillID1>=0) then
      [*] = ;begin
      [*] = ;   elmHandle := _gui_CreateImage('', elmParentHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', 65, height+248+noParamYOffset, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmHandle, 'icon.heroskill.' + IntToStr(skillIconNum), 'halParentLeft', 'valParentTop', 5, 5, 0, 0, 0);
      [*] = ;   tag := gc_gui_battle_btnSkillsBaseTag + skillID1;
      [*] = ;   elmBtnHandle := _gui_CreateButton('battle_heroupgrade_upg1_btn', elmHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', '', tag);
      [*] = ;   _gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroSkillCallback',skillID1,skillIconNum,cEventState,'');
      [*] = ;   SetGUIElementStringTag(elmBtnHandle,IntToStr(heroGOHandle));
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   GameObjectExecuteStateByHandle(heroGOHandle, 'AIHeroLevelUp');
      [*] = ;   GUIExecuteState('CheckUnitUpgrade');
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;//Upgrade 2
      [*] = ;IntRegister0 := skillID1;
      [*] = ;IntRegister1 := -1;
      [*] = ;GameObjectExecuteStateByHandle(heroGOHandle, 'GetRandomNotUsedSkill');
      [*] = ;var skillID2 : Integer = IntRegister2;
      [*] = ;if skillID2 = -1 then
      [*] = ;begin
      [*] = ;   IntRegister0 := skillID1;
      [*] = ;   IntRegister1 := -1;
      [*] = ;   GameObjectExecuteStateByHandle(heroGOHandle, 'GetRandomSkill');
      [*] = ;   skillID2 := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := skillID2;
      [*] = ;GameObjectExecuteStateByHandle(heroGOHandle, 'GetSkillLevel');
      [*] = ;var SkillID2Lvl : Integer = IntRegister1 + 1;
      [*] = ;
      [*] = ;skillIconNum := 1+(skillID2-1)*5+(SkillID2Lvl-1);
      [*] = ;
      [*] = ;if (skillID2>=0) then
      [*] = ;begin
      [*] = ;   elmHandle := _gui_CreateImage('', elmParentHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', 65+75, height+248+noParamYOffset, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmHandle, 'icon.heroskill.' + IntToStr(skillIconNum), 'halParentLeft', 'valParentTop', 5, 5, 0, 0, 0);
      [*] = ;   tag := gc_gui_battle_btnSkillsBaseTag + skillID2;
      [*] = ;   elmBtnHandle := _gui_CreateButton('battle_heroupgrade_upg2_btn', elmHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', '', tag);
      [*] = ;   _gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroSkillCallback',skillID2,skillIconNum,cEventState,'');
      [*] = ;   SetGUIElementStringTag(elmBtnHandle,IntToStr(heroGOHandle));
      [*] = ;end;
      [*] = ;
      [*] = ;//Upgrade 3
      [*] = ;IntRegister0 := skillID1;
      [*] = ;IntRegister1 := skillID2;
      [*] = ;GameObjectExecuteStateByHandle(heroGOHandle, 'GetRandomSkill');
      [*] = ;var skillID3 : Integer = IntRegister2;
      [*] = ;
      [*] = ;IntRegister0 := skillID3;
      [*] = ;GameObjectExecuteStateByHandle(heroGOHandle, 'GetSkillLevel');
      [*] = ;var SkillID3Lvl : Integer = IntRegister1 + 1;
      [*] = ;
      [*] = ;skillIconNum := 1+(skillID3-1)*5+(SkillID3Lvl-1);
      [*] = ;
      [*] = ;if (skillID3>=0) then
      [*] = ;begin
      [*] = ;   elmHandle := _gui_CreateImage('', elmParentHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', 65+75*2, height+248+noParamYOffset, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmHandle, 'icon.heroskill.' + IntToStr(skillIconNum), 'halParentLeft', 'valParentTop', 5, 5, 0, 0, 0);
      [*] = ;   tag := gc_gui_battle_btnSkillsBaseTag + skillID3;
      [*] = ;   elmBtnHandle := _gui_CreateButton('battle_heroupgrade_upg3_btn', elmHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', '', tag);
      [*] = ;   _gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroSkillCallback',skillID3,skillIconNum,cEventState,'');
      [*] = ;   SetGUIElementStringTag(elmBtnHandle,IntToStr(heroGOHandle));
      [*] = ;end;
      [*] = ;
      [*] = ;if (not bLevel10) and (bonusInd >= 0) then
      [*] = ;begin
      [*] = ;   //������ �������� ����
      [*] = ;   text := GetLocaleTableListItemByID('gui', 'ParamIncreased');
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandleT, text, width, height);
      [*] = ;   elmTextHandle := _gui_CreateText('heroupg_skill_name', elmParentHandle, text, 'halParentMiddle', 'valParentTop', 0, 169-32, width, height, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   //�� ��������
      [*] = ;   //116 - ������������
      [*] = ;   //117 - ����
      [*] = ;   //118 - ��������
      [*] = ;   var abilityID : Integer;
      [*] = ;   if (bonusInd<3) then // life
      [*] = ;      abilityID := 116 + bonusInd
      [*] = ;   else
      [*] = ;      abilityID := 1; // �����
      [*] = ;
      [*] = ;   text := GetLocaleTableListItemByID('ability', IntToStr(abilityID));
      [*] = ;   text := text + ' +1';
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandleT, text, width, height);
      [*] = ;   elmTextHandle := _gui_CreateText('heroupg_skill_value', elmParentHandle, text, 'halParentMiddle', 'valParentTop', 0, 169-13, width, height, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   //������ ���������� ���������
      [*] = ;   tag := gc_gui_battle_btnControlAbilityBaseTag + abilityID;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to 1 do
      [*] = ;   begin
      [*] = ;      var abilityPower : Integer = 0;
      [*] = ;      case bonusInd of
      [*] = ;         0 : abilityPower := GetGameObjectIntValueIndByHandle(heroGOHandle, gc_map_GOStack_MapUnit_iLeader);
      [*] = ;         1 : abilityPower := GetGameObjectIntValueIndByHandle(heroGOHandle, gc_map_GOStack_MapUnit_iMagic);
      [*] = ;         2 : abilityPower := GetGameObjectIntValueIndByHandle(heroGOHandle, gc_map_GOStack_MapUnit_iHealth);
      [*] = ;      end;
      [*] = ;
      [*] = ;      elmHandle := _gui_CreateImage('', elmParentHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', 12+i*259, 115, 0, 0, 0);
      [*] = ;      elmHandle := _gui_CreateImage('', elmHandle, 'icon.ability.' + IntToStr(abilityID), 'halParentLeft', 'valParentTop', 5, 5, 0, 0, tag);
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('', elmHandle, '', 'icons.52x52.cover', 'halParentLeft', 'valParentTop', 0, -1, 52, 52, '', '', tag);
      [*] = ;      _gui_ft_AttachHint_I2(elmBtnHandle,'VVK.HintHeroParamCallback',abilityID,abilityPower);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_CreateButton('btn_hero_window', elmParentHandle, '', 'map.mainpanel.btn.nexthero', 'halParentLeft', 'valParentTop', 10, 10, 0, 0, cEventState, 'gui|618', GetGameObjectUniqueIdByHandle(heroGOHandle));
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

