section.begin
   Name = EventAstralHeroWindow
   Code : struct.begin
      [*] = ;const cAstralHeroApproveBtnTag = 100;
      [*] = ;const cAstralHeroCancelBtnTag = 101;
      [*] = ;const cBtnItemsScrollLeft = 200;
      [*] = ;const cBtnItemsScrollRight = 201;
      [*] = ;const cBtnSpellsScrollLeft = 202;
      [*] = ;const cBtnSpellsScrollRight = 203;
      [*] = ;const cBtnUnitsScrollLeft = 204;
      [*] = ;const cBtnUnitsScrollRight = 205;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var key : String = GetValueByName('Key');
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if SameText(key, 'LButton') or SameText(status, 'shortcut') then
      [*] = ;   begin
      [*] = ;      var scrollPosUnits, scrollPosItems, scrollPosSpells : Integer = 0;
      [*] = ;      var pScrollPosTmp : Integer = _misc_ParserGetOrCreateByKey('pHeroScrollPosTmp',false);
      [*] = ;      if (ParserGetCountByHandle(pScrollPosTmp)=0) then
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems', scrollPosItems);
      [*] = ;         ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'scrollPosSpells', scrollPosSpells);
      [*] = ;         ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits', scrollPosUnits);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         scrollPosItems := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems');
      [*] = ;         scrollPosSpells := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'scrollPosSpells');
      [*] = ;         scrollPosUnits := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits');
      [*] = ;      end;
      [*] = ;
      [*] = ;      case tag of
      [*] = ;         cBtnItemsScrollLeft : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems', scrollPosItems-1);
      [*] = ;         end;
      [*] = ;         cBtnItemsScrollRight : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems', scrollPosItems+1);
      [*] = ;         end;
      [*] = ;         cBtnSpellsScrollLeft : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosSpells', scrollPosSpells-1);
      [*] = ;         end;
      [*] = ;         cBtnSpellsScrollRight : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosSpells', scrollPosSpells+1);
      [*] = ;         end;
      [*] = ;         cBtnUnitsScrollLeft : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits', scrollPosUnits-1);
      [*] = ;         end;
      [*] = ;         cBtnUnitsScrollRight : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits', scrollPosUnits+1);
      [*] = ;         end;
      [*] = ;         cAstralHeroApproveBtnTag : begin
      [*] = ;            var pAstralHero : Integer = _misc_ParserGetOrCreateByKey('astral_hero', false);
      [*] = ;            var heroLevel : Integer = ParserGetIntValueByKeyByHandle(pAstralHero, 'Level');
      [*] = ;            var class1 : Integer = ParserGetIntValueByKeyByHandle(pAstralHero, 'Class1');
      [*] = ;            
      [*] = ;            var myPlHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;            IntRegister0 := class1;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'GetHeroPrice');
      [*] = ;            var gold : Integer = IntRegister1;
      [*] = ;            var gem : Integer = IntRegister2;
      [*] = ;            IntRegister0 := heroLevel;
      [*] = ;            IntRegister1 := myPlHandle;
      [*] = ;            MapExecuteState('GetAstralHeroPrice');
      [*] = ;            gold := gold + IntRegister2;
      [*] = ;            gem := gem + IntRegister3;
      [*] = ;            
      [*] = ;            var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold); 
      [*] = ;            var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem); 
      [*] = ;            SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold-gold);
      [*] = ;            SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem-gem);
      [*] = ;            
      [*] = ;            BoolRegister0 := true;
      [*] = ;            GUIExecuteState('map.RecruitHero');
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('astral_hero'),gc_gui_FadeTime0_2);
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('map_herorecruitpanel.recruitbck.recruitdummy.astral_hero_open'),gc_gui_FadeTime0_2);
      [*] = ;            IntRegister0 := 2;
      [*] = ;            GUIExecuteState('map.CreateCastleBuildWindow');
      [*] = ;         end;
      [*] = ;         cAstralHeroCancelBtnTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;            _misc_ParserGetOrCreateByKey('pHeroScrollPosTmp',true);
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('astral_hero'),gc_gui_FadeTime0_2);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (tag>=cBtnItemsScrollLeft) and (tag<=cBtnUnitsScrollRight) then
      [*] = ;         GUIExecuteState('CreateAstralHeroWindow');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
   struct.end
section.end

