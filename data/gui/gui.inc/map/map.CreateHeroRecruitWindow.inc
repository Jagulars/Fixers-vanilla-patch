section.begin
   Name = map.CreateHeroRecruitWindow
   Code : struct.begin
      [*] = ;var posX, posY : Integer;
      [*] = ;var xOff, yOff : Integer;
      [*] = ;var top : Integer = _gui_GetLayerI();
      [*] = ;var tag : Integer = 0;
      [*] = ;var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;var fontHandleT, fontHandleH2, fontHandleH1, fontHandleB, fontHandleN: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Button',gc_gui_fontsize_default,'',fontHandleB);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Numbers',gc_gui_fontsize_default,'',fontHandleN);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandleT);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_large,'',fontHandleH2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_largest,'',fontHandleH1); // HeaderM
      [*] = ;
      [*] = ;function CreateScrollerParentExt(ElementName : String; Parent : Integer; hAlign, vAlign, MaterialName : String; posX, posY, sizeX, sizeY, scrollX, scrollY, scrollH : Integer; showScroller : Boolean) : Integer;
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
      [*] = ;   if (showScroller) then
      [*] = ;   begin
      [*] = ;      SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   SetGUIElementMaterial(elmVScroll, 'misc.blank.black.alpha.0');
      [*] = ;   Result := elmGuiLayer;
      [*] = ;end;
      [*] = ;
      [*] = ;SetGUIElementVisible(GetGUIElementIndexByNameParent('map_herorecruitpanel', top), true);
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElement('map_herorecruitpanel', top, 'halLeft', 'valBottomHeight', 0, 0, 0, 0, 0);
      [*] = ;_gui_RootWindowAddExt(elmParentHandle,cRootWindowActive,0,cRootWindowAttrScaleByY,'');
      [*] = ;
      [*] = ;var globalXOffset : Integer = 660-26;
      [*] = ;var elmBackgroundHandle : Integer = _gui_CreateDummy('recruitbck', elmParentHandle, 'halParentLeft', 'valParentBottomHeight', 0+globalXOffset+6, 78, 0, 0, 0);
      [*] = ;
      [*] = ;//Background + ADD layer
      [*] = ;posX := -645;
      [*] = ;posY := -1003;
      [*] = ;var elmImageHandle : Integer = _gui_CreateImage('', elmBackgroundHandle, 'map.heropanel.leftside.background', 'halParentLeft', 'valParentTop', posX, posY, 711, 925, 0);
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;
      [*] = ;posX := -614;
      [*] = ;posY := -947;
      [*] = ;elmImageHandle := _gui_CreateImage('' , elmBackgroundHandle, 'castle.hero.recruit.window.background', 'halParentLeft', 'valParentTop', posX, posY, 587, 845, 0);
      [*] = ;
      [*] = ;elmImageHandle := _gui_CreateImageSimple('', elmBackgroundHandle, 'element.header.strip.629', 'halParentLeft', 'valParentBottomHeight', posX-21, posY+37);
      [*] = ;
      [*] = ;//������� �� ������
      [*] = ;posX := -494;
      [*] = ;posY := -967;
      [*] = ;yOff := 331;
      [*] = ;var elmText : Integer = _gui_CreateText('', elmBackgroundHandle, GetLocaleTableListItemByID('gui', '47'), 'halParentLeft', 'valParentTop', posX, posY, 340, 32, 'halMiddle', 'valTop', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 0.8);
      [*] = ;
      [*] = ;var matName : String = 'element.strip.341';
      [*] = ;elmImageHandle := _gui_CreateImage('herolist_strip' , elmBackgroundHandle, matName, 'halParentLeft', 'valParentBottomHeight', -495, -601, GetGUITextureWidth(matName), GetGUITextureHeight(matName), 0);
      [*] = ;
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;posX := -389;
      [*] = ;posY := -967;
      [*] = ;elmText := _gui_CreateText('', elmBackgroundHandle, GetLocaleTableListItemByID('gui', '586'), 'halParentLeft', 'valParentTop', posX, posY+yOff, 140, 32, 'halMiddle', 'valTop', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 0.8);
      [*] = ;
      [*] = ;//����
      [*] = ;posX := -596;
      [*] = ;posY := -900;
      [*] = ;xOff := 138;
      [*] = ;
      [*] = ;var elmRecruitDummyHandle : Integer = _gui_CreateDummy('recruitdummy', elmBackgroundHandle, 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;
      [*] = ;
      [*] = ;var allowedHeroes : Integer = gGame.allowedHeroes;
      [*] = ;var bAllowed : Boolean;
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to 3 do
      [*] = ;begin
      [*] = ;   var portraitName : String;
      [*] = ;   case i of
      [*] = ;      0 : portraitName := 'map.hero.portrait.warrior.' + IntToStr(2);
      [*] = ;      1 : portraitName := 'map.hero.portrait.scout.' + IntToStr(1);
      [*] = ;      2 : portraitName := 'map.hero.portrait.commander.' + IntToStr(1);
      [*] = ;      3 : portraitName := 'map.hero.portrait.wizard.' + IntToStr(1);
      [*] = ;   end;
      [*] = ;   elmImageHandle := _gui_CreateImage('recruithero_portrait_class_' + IntToStr(i), elmRecruitDummyHandle, portraitName, 'halParentLeft', 'valParentTop', i*xOff+13, 22, 109, 109, 0);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;
      [*] = ;   var MaterialName : String = 'castle.hero.recruit.buttonframe';
      [*] = ;   tag := i + 1;
      [*] = ;
      [*] = ;   var elmRecruitHandle : Integer = _gui_CreateImage('recruithero_class_'+IntToStr(i), elmRecruitDummyHandle, 'castle.hero.recruit.buttonframe', 'halParentLeft', 'valParentTop', i*xOff, 0, 135, 207, 0);
      [*] = ;   SetGUIAllowEvents(elmRecruitHandle, True, False, False);
      [*] = ;
      [*] = ;   elmText := _gui_CreateText('recruithero_class_name_'+IntToStr(i), elmRecruitHandle, GetLocaleTableListItemByID('hero_class', IntToStr(i+1)), 'halParentLeft', 'valParentTop', 8, 1, 120, 28, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 0.8);
      [*] = ;   SetGUIAllowEvents(elmText, True, False, False);
      [*] = ;
      [*] = ;   //����
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('recruithero_btn_class_'+IntToStr(i), elmRecruitHandle, '', 'castle.hero.recruit.window.btn.recruit', 'halParentLeft', 'valParentTop', -1, 202, 136, 48, '', ''{'gui|47|MT'}, gc_gui_recruithero_btnRecruit);
      [*] = ;   SetGUIElementStringTag(elmBtnHandle, IntToStr(i+1));
      [*] = ;   elmText := _gui_CreateText('', elmBtnHandle, GetLocaleTableListItemByID('gui', '585'), 'halParentLeft', 'valParentTop', 24, 14, 88, 23, 'halMiddle', 'valMiddle', fontHandleB, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;   case i of
      [*] = ;      0 : bAllowed := ((allowedHeroes and $f) < $f);
      [*] = ;      1 : bAllowed := ((allowedHeroes and $f0) < $f0);
      [*] = ;      2 : bAllowed := ((allowedHeroes and $f00) < $f00);
      [*] = ;      3 : bAllowed := ((allowedHeroes and $f000) < $f000);
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := i+1;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetHeroPrice');
      [*] = ;   var gold : Integer = IntRegister1;
      [*] = ;   var gem : Integer = IntRegister2;
      [*] = ;
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   if bAllowed then
      [*] = ;   begin
      [*] = ;      var plHeroCount : Integer = _plr_GetNonBuriedHeroCount(plHandle);
      [*] = ;      if (plHeroCount<gc_MaxHeroesPerPlayer) then
      [*] = ;      begin
      [*] = ;         if (plGold<gold) or (plGem<gem) then
      [*] = ;         begin
      [*] = ;            SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            SetGUIElementHint(elmBtnHandle, 'gui|246');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         SetGUIElementHint(elmBtnHandle, 'gui|610');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;  
      [*] = ;   posX := 56;
      [*] = ;   posY := 135;
      [*] = ;   yOff := 32;
      [*] = ;
      [*] = ;   var elmTextHandle : Integer;
      [*] = ;   var colorR, colorG, colorB : Float;
      [*] = ;   if (plGold>=gold) or (gold=0) then
      [*] = ;   begin
      [*] = ;      colorR := gc_gui_fontcolor_YellowR;
      [*] = ;      colorG := gc_gui_fontcolor_YellowG;
      [*] = ;      colorB := gc_gui_fontcolor_YellowB;
      [*] = ;      elmTextHandle  := _gui_CreateText('recruithero_cost_gold', elmRecruitHandle, IntToStr(gold), 'halParentLeft', 'valParentTop', posX-35, posY-5, 60+35, 30, 'halLeft', 'valMiddle', fontHandleN, colorR, colorG, colorB, 0.8);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      colorR := gc_gui_fontcolor_RedR;
      [*] = ;      colorG := gc_gui_fontcolor_RedG;
      [*] = ;      colorB := gc_gui_fontcolor_RedB;
      [*] = ;      elmTextHandle  := _gui_CreateText('recruithero_cost_gold_not_enough', elmRecruitHandle, IntToStr(gold), 'halParentLeft', 'valParentTop', posX-35, posY-5, 60+35, 30, 'halLeft', 'valMiddle', fontHandleN, colorR, colorG, colorB, 0.8);
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmRecruitHandle, 'common.notenough.redline.cover', 'halParentLeft', 'valParentTop', 18, 127, 36, 36, 0);
      [*] = ;   end;
      [*] = ;   SetGUIElementTextAlign(elmTextHandle, 'halLeft', 'valMiddle', 35, 0);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;   if (plGem>=gem) or (gem=0) then
      [*] = ;   begin
      [*] = ;      colorR := gc_gui_fontcolor_YellowR;
      [*] = ;      colorG := gc_gui_fontcolor_YellowG;
      [*] = ;      colorB := gc_gui_fontcolor_YellowB;
      [*] = ;      elmTextHandle  := _gui_CreateText('recruithero_cost_gem', elmRecruitHandle, IntToStr(gem), 'halParentLeft', 'valParentTop', posX-35, posY+yOff-5, 60+35, 30, 'halLeft', 'valMiddle', fontHandleN, colorR, colorG, colorB, 0.8);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      colorR := gc_gui_fontcolor_RedR;
      [*] = ;      colorG := gc_gui_fontcolor_RedG;
      [*] = ;      colorB := gc_gui_fontcolor_RedB;
      [*] = ;      elmTextHandle  := _gui_CreateText('recruithero_cost_gem_not_enough', elmRecruitHandle, IntToStr(gem), 'halParentLeft', 'valParentTop', posX-35, posY+yOff-5, 60+35, 30, 'halLeft', 'valMiddle', fontHandleN, colorR, colorG, colorB, 0.8);
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmRecruitHandle, 'common.notenough.redline.cover', 'halParentLeft', 'valParentTop', 18, 127+yOff, 36, 36, 0);
      [*] = ;   end;
      [*] = ;   SetGUIElementTextAlign(elmTextHandle, 'halLeft', 'valMiddle', 35, 0);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;{var resCount : Integer = 0;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   var dead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;
      [*] = ;   if dead then
      [*] = ;      resCount := resCount + 1;
      [*] = ;end;}
      [*] = ;
      [*] = ;var sizeX, sizeY : Integer;
      [*] = ;posX := -595-8;
      [*] = ;posY := -603;
      [*] = ;sizeX := 531;
      [*] = ;const scrollLayerHeight = 469;
      [*] = ;var elmResurrectDummyHandle : Integer = CreateScrollerParentExt('scroll_layer', elmBackgroundHandle, 'halParentLeft', 'valParentTop', 'misc.blank.black.alpha.0', posX, posY, sizeX, scrollLayerHeight, sizeX, 0, scrollLayerHeight, true);
      [*] = ;
      [*] = ;//������ ������
      [*] = ;var xHeroListOff : Integer = 265-8;
      [*] = ;var yHeroListOff : Integer = 114;
      [*] = ;
      [*] = ;var j, k : Integer;
      [*] = ;var ind : Integer = 0;
      [*] = ;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;   begin
      [*] = ;      var dead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;   
      [*] = ;      const baseHeroUIDTag = 1000;
      [*] = ;      var uid : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;      tag := baseHeroUIDTag+uid;
      [*] = ;   
      [*] = ;      k := ind mod 2;
      [*] = ;      j := ind div 2;
      [*] = ;      var elmResurrectHandle : Integer = _gui_CreateDummy('', elmResurrectDummyHandle, 'halParentLeft', 'valParentTop', k*xHeroListOff, j*yHeroListOff, 259, 126, goHandle);
      [*] = ;      //portrait
      [*] = ;      var pHero : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var name : String = ParserGetValueByKeyByHandle(pHero, 'Name');
      [*] = ;      var portrait : String = ParserGetValueByKeyByHandle(pHero, 'Portrait');
      [*] = ;      var turns : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCastleDist);
      [*] = ;      if (dead) then
      [*] = ;         portrait := 'map.hero.portrait.small.dead';
      [*] = ;      elmImageHandle := _gui_CreateImage('herolist_portrait', elmResurrectHandle, portrait, 'halParentLeft', 'valParentTop', 46, 19, 70, 70, tag);
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('herolist_heroBtn', elmImageHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', -23, -3, 236, 100{70, 70}, 'map.EventHeroRecruitWindow', ''{'gui|668'}, tag);
      [*] = ;      //var elmActiveBtnHandle : Integer = _gui_CreateButton('heroBtn', elmImageHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', -32, 0, 236, 100, 'map.EventHeroRecruitWindow', ''{'gui|668'}, tag);
      [*] = ;   
      [*] = ;      var frameMat : String;
      [*] = ;      var bSelected : Boolean = (goHandle=GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID));
      [*] = ;      if (bSelected) then
      [*] = ;         frameMat := 'map.heroselection.yellowcircle'
      [*] = ;      else
      [*] = ;         frameMat := 'map.heroselection.browncircle';
      [*] = ;      var elmContextFrameHandle : Integer = _gui_CreateImage('contextframe', elmImageHandle, 'gamepanel01.herorecruit.list.frame', 'halParentLeft', 'valParentTop', -23, -3, 0, 0, tag);
      [*] = ;      var elmContentFrameBtnHandle : Integer = _gui_CreateButton('herolist_heroBtn_contextframe', elmContextFrameHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, 236, 100{GetGUIElementWidth(elmContextFrameHandle), GetGUIElementHeight(elmContextFrameHandle)}, 'map.EventHeroRecruitWindow', ''{'gui|668'}, tag);
      [*] = ;      //SetGUIAllowEvents(elmContextFrameHandle, True, False, False);
      [*] = ;      var elmPortraitFrameHandle : Integer = _gui_CreateImage('map_radialhero_frame', elmResurrectHandle, frameMat, 'halParentMiddle', 'valParentMiddle', -49, -10, 0, 0, 0);
      [*] = ;   
      [*] = ;      const btnDismissHero = 101;
      [*] = ;      const btnHeroInfo = 102;
      [*] = ;      const btnHeroResurrect = 103;
      [*] = ;   
      [*] = ;      elmBtnHandle := _gui_CreateButton('herolist_btn_dismiss', elmContextFrameHandle, 'dismiss', 'gamepanel01.herorecruit.list.btn.dismiss', 'halParentLeft', 'valParentTop', 0, 56, 0, 0, 'map.EventHeroRecruitWindow', '', btnDismissHero);
      [*] = ;      SetGUIElementHint(elmBtnHandle, 'gui|584');
      [*] = ;   
      [*] = ;      var hint : String = 'gui|618';
      [*] = ;      elmBtnHandle := _gui_CreateButton('herolist_btn_heroinfo', elmContextFrameHandle, '', 'gamepanel01.herorecruit.list.btn.heroinfo', 'halParentRight', 'valParentTop', -41, 56, 0, 0, 'map.EventHeroRecruitWindow', hint, btnHeroInfo);
      [*] = ;      //var elmResurrectHandle : Integer = _gui_CreateButton('', elmResurrectDummyHandle, '', MaterialName, 'halParentLeft', 'valParentTop', k*xHeroListOff, j*yHeroListOff, 259, 126, 'map.DoResurrectHero', '', goHandle);
      [*] = ;   
      [*] = ;      var gold, gem, plGold, plGem : Integer = 0;
      [*] = ;      if (dead) then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetResurrectPrice');
      [*] = ;         gold := IntRegister0;
      [*] = ;         gem := IntRegister1;
      [*] = ;         plGold := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         plGem := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   
      [*] = ;         elmBtnHandle := _gui_CreateButton('herolist_btn_resurrect', elmContextFrameHandle, '', 'gamepanel01.herorecruit.list.btn.resurrect', 'halParentLeft', 'valParentTop', 37, 56+15, 0, 0, 'map.EventHeroRecruitWindow', 'gui|665', btnHeroResurrect);
      [*] = ;         if (turns>0) then
      [*] = ;         begin
      [*] = ;            SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            SetGUIElementHint(elmBtnHandle, 'gui|667');
      [*] = ;         end;
      [*] = ;         if (plGold<gold) or (plGem<gem) then
      [*] = ;         begin
      [*] = ;            SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;            var hint : String = GetLocaleTableListItemByID('gui', '665')+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '608');
      [*] = ;            SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      {var elmResurrectBtnHandle : Integer;
      [*] = ;      var MaterialName : String = gc_gui_material_blank_0;
      [*] = ;      {if (dead) and (turns=0) then
      [*] = ;      elmResurrectBtnHandle := _gui_CreateButton(elmName, elmResurrectHandle, '', MaterialName, 'halParentLeft', 'valParentTop', 0, 0, 259, 126, 'map.DoResurrectHero', '', goHandle)
      [*] = ;      else}
      [*] = ;      {elmResurrectBtnHandle := _gui_CreateImage(elmName, elmResurrectHandle, MaterialName, 'halParentLeft', 'valParentTop', 0, 0, 259, 126, goHandle);
      [*] = ;      SetGUIElementVisibleProperties(elmResurrectBtnHandle, 'UpProperty', MaterialName, 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementVisibleProperties(elmResurrectBtnHandle, 'HoverProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementVisibleProperties(elmResurrectBtnHandle, 'DownProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementVisibleProperties(elmResurrectBtnHandle, 'DisableProperty', MaterialName, 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementVisibleProperties(elmResurrectBtnHandle, 'CheckOnProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);}
      [*] = ;   
      [*] = ;      var text : String;
      [*] = ;      //name
      [*] = ;      posX := 119+28-2;
      [*] = ;      posY := 35-8;
      [*] = ;      _hero_GetName(goHandle, text);
      [*] = ;      elmText := _gui_CreateText('herolist_name', elmResurrectHandle, text, 'halParentLeft', 'valParentTop', posX, posY, 172, 21, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB{gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB}, 1);
      [*] = ;      //SetGUIAllowEvents(elmText, True, False, False);
      [*] = ;      //class
      [*] = ;      posX := 119+28-2;
      [*] = ;      posY := 57-10;
      [*] = ;   
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetClass');
      [*] = ;      var classInd : Integer = IntRegister0;
      [*] = ;      text := GetLocaleTableListItemByID('hero_class', IntToStr(classInd));
      [*] = ;      elmText := _gui_CreateText('herolist_class', elmResurrectHandle, text, 'halParentLeft', 'valParentTop', posX, posY, 172, 21, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1); //gc_gui_fontcolor_YellowR,  gc_gui_fontcolor_YellowG,  gc_gui_fontcolor_YellowB
      [*] = ;      //SetGUIAllowEvents(elmText, True, False, False);
      [*] = ;   
      [*] = ;      //level
      [*] = ;      var level : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;      //text := GetLocaleTableListItemByID('gui', '605') + ' ' + IntToStr(level);
      [*] = ;      posX := 17;
      [*] = ;      posY := 102;
      [*] = ;   
      [*] = ;      var curExp : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iExp);
      [*] = ;      IntRegister0 := level;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetNeededExpForLevel');
      [*] = ;      var prevExp : Integer = IntRegister1;
      [*] = ;      IntRegister0 := level+1;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetNeededExpForLevel');
      [*] = ;      var nextExp : Integer = IntRegister1;
      [*] = ;      var meterValue : Integer = floor(((curExp - prevExp)/(nextExp - prevExp))*82);
      [*] = ;      if (meterValue>82) then
      [*] = ;      meterValue := 82;
      [*] = ;   
      [*] = ;      var elmExpBlockHandle : Integer = _gui_CreateImage('herolist_expblock', elmResurrectHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;      var elmHandle : Integer = _gui_CreateScrollLayer(elmExpBlockHandle, 'map.prov.herolist.buttonframe.meter.exp', 'halParentLeft', 'valParentTop', 45, 96, meterValue, 0);
      [*] = ;      if (meterValue<=0) then
      [*] = ;      SetGUIElementVisible(elmHandle, False);
      [*] = ;      var elmMeterHandle : Integer = _gui_CreateImage('', elmExpBlockHandle, 'gamepanel02.herorecruit.expmeter', 'halParentLeft', 'valParentTop', 34, 86, 0, 0, 0);
      [*] = ;      SetGUIElementHint(elmMeterHandle, 'gui|663');
      [*] = ;      SetGUIAllowEvents(elmMeterHandle, True, False, False);
      [*] = ;   
      [*] = ;      elmHandle := _gui_CreateImage('herolist_hero_level', elmMeterHandle, 'gamepanel02.herorecruit.expmeter.round', 'halParentLeft', 'valParentTop', -15, 0, 0, 0, 0);
      [*] = ;      SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;      elmText := _gui_CreateText('', elmHandle, IntToStr(level), 'halParentLeft', 'valParentTop', 1, 1, 27, 27, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;      //elmHandle := _gui_CreateImage('', elmResurrectHandle, 'gamepanel02.expicon', 'halParentLeft', 'valParentTop', 24, 63, 0, 0, 0);
      [*] = ;   
      [*] = ;      if (GetGUIElementUnderMouse<>0) and ((GetGUIElementNameByIndex(GetGUIElementUnderMouse))='herolist_heroBtn_contextframe') then
      [*] = ;      begin
      [*] = ;         if (not bSelected) then
      [*] = ;            SetGUIElementVisible(elmContextFrameHandle, False)
      [*] = ;         else
      [*] = ;            SetGUIElementVisible(elmExpBlockHandle, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      SetGUIElementVisible(elmContextFrameHandle, False);
      [*] = ;   
      [*] = ;      if (dead) then
      [*] = ;      begin
      [*] = ;         //posX := 40;
      [*] = ;         //posY := 6;
      [*] = ;         //elmImageHandle := _gui_CreateImage('herolist_hero_deadmark', elmResurrectHandle, 'battle.results.dead', 'halParentLeft', 'valParentTop', posX, posY, 81, 108, 0);
      [*] = ;         //SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;         if (turns=0) then
      [*] = ;         begin
      [*] = ;            SetGUIElementPressState(elmImageHandle, 'map.DoResurrectHero');
      [*] = ;            SetGUIElementCursorByName(elmImageHandle, 'crHand');
      [*] = ;   
      [*] = ;            posX := 141;
      [*] = ;            posY := 88;
      [*] = ;            xOff := 70;
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmResurrectHandle, 'icon.gold.20x20', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;            var colorR, colorG, colorB : Float;
      [*] = ;            if (plGold>=gold) then
      [*] = ;            begin
      [*] = ;               colorR := gc_gui_fontcolor_NormalR;
      [*] = ;               colorG := gc_gui_fontcolor_NormalG;
      [*] = ;               colorB := gc_gui_fontcolor_NormalB;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               colorR := gc_gui_fontcolor_RedR;
      [*] = ;               colorG := gc_gui_fontcolor_RedG;
      [*] = ;               colorB := gc_gui_fontcolor_RedB;
      [*] = ;               elmHandle := _gui_CreateImage('', elmImageHandle, 'common.notenough.redline.cover', 'halParentLeft', 'valParentTop', 3, 1, 18, 18, 0);
      [*] = ;            end;
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, IntToStr(gold), 'halParentLeft', 'valParentTop', posX-2, posY+2, xOff-2, 20, 'halLeft', 'valTop', fontHandleN, colorR, colorG, colorB, 1);
      [*] = ;            SetGUIElementTextAlign(elmText, 'halLeft', 'valTop', 25, 0);
      [*] = ;   
      [*] = ;            //SetGUIAllowEvents(elmText, True, False, False);
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmResurrectHandle, 'icon.gem.20x20', 'halParentLeft', 'valParentTop', posX+xOff, posY, 0, 0, 0);
      [*] = ;            if (plGem>=gem) then
      [*] = ;            begin
      [*] = ;               colorR := gc_gui_fontcolor_NormalR;
      [*] = ;               colorG := gc_gui_fontcolor_NormalG;
      [*] = ;               colorB := gc_gui_fontcolor_NormalB;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               colorR := gc_gui_fontcolor_RedR;
      [*] = ;               colorG := gc_gui_fontcolor_RedG;
      [*] = ;               colorB := gc_gui_fontcolor_RedB;
      [*] = ;               elmHandle := _gui_CreateImage('', elmImageHandle, 'common.notenough.redline.cover', 'halParentLeft', 'valParentTop', 3, 1, 18, 18, 0);
      [*] = ;            end;
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, IntToStr(gem), 'halParentLeft', 'valParentTop', posX-2+xOff, posY+2, xOff-2, 20, 'halLeft', 'valTop', fontHandleN, colorR, colorG, colorB, 1);
      [*] = ;            SetGUIElementTextAlign(elmText, 'halLeft', 'valTop', 25, 0);
      [*] = ;            //SetGUIAllowEvents(elmText, True, False, False);
      [*] = ;   
      [*] = ;            posX := 146;
      [*] = ;            posY := 74+1-9;
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, 'gui|670', 'halParentLeft', 'valParentTop', posX, posY, 172, 20, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 0.3);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            posX := 146;
      [*] = ;            posY := 74+1;
      [*] = ;            text := GetLocaleTableListItemByID('gui', IntToStr(313)) + ': ' + IntToStr(turns);
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, 'gui|666', 'halParentLeft', 'valParentTop', posX, posY, 172, 21, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 0.3);
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, text, 'halParentLeft', 'valParentTop', posX, posY+18, 172, 21, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB{gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB}, 1);
      [*] = ;   
      [*] = ;            {posX := 146;
      [*] = ;            posY := 74+18;
      [*] = ;            text := GetLocaleTableListItemByID('gui', IntToStr(313)) + ': ' + IntToStr(turns);
      [*] = ;            elmText := _gui_CreateText('herolist_hero_dead_turns', elmResurrectHandle, text, 'halParentLeft', 'valParentTop', posX, posY, 125, 20, 'halLeft', 'valTop', fontHandleH2, gc_gui_fontcolor_RedR, gc_gui_fontcolor_RedG, gc_gui_fontcolor_RedB, 1);
      [*] = ;            SetGUIAllowEvents(elmText, True, False, False);}
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var task : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask);
      [*] = ;         var targetDummyUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;         var goTargetHandle : Integer = GetGameObjectHandleByUniqueId(targetDummyUID);
      [*] = ;         var pStratHex : Integer = GetGameObjectIntValueIndByHandle(goTargetHandle, gc_map_GOStack_Province_iParserHandle);
      [*] = ;         var curDummyUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;         var goCurDummyUID : Integer = GetGameObjectHandleByUniqueId(curDummyUID);
      [*] = ;         var pCurStratHex : Integer = GetGameObjectIntValueIndByHandle(goTargetHandle, gc_map_GOStack_Province_iParserHandle);
      [*] = ;   
      [*] = ;         procedure GetProvinceName(pHex : Integer; var provName : String);
      [*] = ;         begin
      [*] = ;            IntRegister0 := pHex;
      [*] = ;            MapExecuteState('map.GetProvinceName');
      [*] = ;            provName := StringRegister0;
      [*] = ;         end;
      [*] = ;   
      [*] = ;         var textTarget : String = '';
      [*] = ;         if (task=0) then
      [*] = ;         begin
      [*] = ;            posX := 119+28-2;
      [*] = ;            posY := 74+1;
      [*] = ;            GetProvinceName(pStratHex, textTarget);
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, 'gui|664', 'halParentLeft', 'valParentTop', posX, posY-1, 172, 21, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_RedR, gc_gui_fontcolor_RedG, gc_gui_fontcolor_RedB, 0.5);
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, textTarget, 'halParentLeft', 'valParentTop', posX, posY+18, 172, 21, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            case task of
      [*] = ;               0 : begin
      [*] = ;               end;
      [*] = ;               1 :
      [*] = ;               begin //Go to province
      [*] = ;                  text := GetLocaleTableListItemByID('gui', '41');
      [*] = ;                  GetProvinceName(pStratHex, textTarget);
      [*] = ;               end;
      [*] = ;               2 :
      [*] = ;               begin //Explore
      [*] = ;                  text := GetLocaleTableListItemByID('gui', '42');
      [*] = ;                  GetProvinceName(pCurStratHex, textTarget);
      [*] = ;               end;
      [*] = ;               3 :
      [*] = ;               begin //Robber
      [*] = ;                  text := GetLocaleTableListItemByID('gui', '43');
      [*] = ;                  GetProvinceName(pCurStratHex, textTarget);
      [*] = ;               end;
      [*] = ;               4 :
      [*] = ;               begin //Go to site
      [*] = ;                  text := GetLocaleTableListItemByID('gui', '44');
      [*] = ;   
      [*] = ;                  var siteIndex : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;                  var pProvSites : Integer = ParserSelectByHandleByKey(pCurStratHex, 'Sites');
      [*] = ;                  var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, siteIndex);
      [*] = ;                  textTarget := GetLocaleTableListItemByID('site', IntToStr(ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID')));
      [*] = ;               end;
      [*] = ;               5 :
      [*] = ;               begin //Siege
      [*] = ;                  text := GetLocaleTableListItemByID('gui', '623');
      [*] = ;                  GetProvinceName(pCurStratHex, textTarget);
      [*] = ;               end;
      [*] = ;               6 :
      [*] = ;               begin //Attack own defender
      [*] = ;                  text := GetLocaleTableListItemByID('gui', '45');
      [*] = ;                  GetProvinceName(pCurStratHex, textTarget);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;   
      [*] = ;            posX := 119+28-2;
      [*] = ;            posY := 74+1;
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, text, 'halParentLeft', 'valParentTop', posX, posY, 172, 21, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;            elmText := _gui_CreateText('', elmResurrectHandle, textTarget, 'halParentLeft', 'valParentTop', posX, posY+18, 172, 21, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      ind := ind + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gTutorial.hero = 2 then
      [*] = ;begin
      [*] = ;   IntRegister0 := -2;
      [*] = ;   MapExecuteState('CheckTutorialProgress');
      [*] = ;end;
      [*] = ;
      [*] = ;//var lineCount : Integer = ((GetPlayerGameObjectsCountByHandle(plHandle)-1) div 2)+1;
      [*] = ;//SetGUIElementHeight(elmResurrectDummyHandle, lineCount*126+20);
   struct.end
section.end

