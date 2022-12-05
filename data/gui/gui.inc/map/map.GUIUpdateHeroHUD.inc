section.begin
   Name = map.GUIUpdateHeroHUD
   Code : struct.begin
      [*] = ;function GUICreateDummy(elementName : String; parent : Integer; hAlign, vAlign : String; posX, posY : Integer; width, height : Integer; tag : Integer) : integer;
      [*] = ;begin
      [*] = ;   var funcElementHandle : integer = AddNewElementByClassNameParent(elementName, 'TOSWDummyGuiControl', tag, parent);
      [*] = ;   SetGUIElementAlign(FuncElementHandle, hAlign, vAlign);
      [*] = ;   SetGUIElementAllPositionRect(FuncElementHandle, posX, posY, width, height);
      [*] = ;   Result := FuncElementHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;const cEventPressHeroHUDState = 'map.DoOnPressHeroHUD';
      [*] = ;
      [*] = ;var hudCollection : Integer = GetGUIElementTopIndexByName('hudhero');
      [*] = ;if hudCollection = 0 then exit;
      [*] = ;
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;var goUID : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;
      [*] = ;if GetGameObjectPlayerHandleByHandle(goHandle) <> plHandle then
      [*] = ;exit;
      [*] = ;
      [*] = ;// HUD button
      [*] = ;var hudHandle : Integer = GetGUIGroupHUDCollectionItemByGameObject(hudCollection, goHandle);
      [*] = ;var dead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;if (dead) then
      [*] = ;begin
      [*] = ;   if (hudHandle <> 0) then
      [*] = ;   begin
      [*] = ;      var elmHandle : Integer;
      [*] = ;      elmHandle := GetGUIElementIndexByNameParent('btn', hudHandle);
      [*] = ;      SetGUIElementTag(elmHandle, goHandle);
      [*] = ;
      [*] = ;      elmHandle := GetGUIElementIndexByNameParent('map_radialhero_maincircle_dummy', hudHandle);
      [*] = ;      RemoveGUIChildren(hudHandle);
      [*] = ;   end;
      [*] = ;   GUIExecuteState('map.DrawGroupDataViewer');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (GetGameObjectPlayableObjectByHandle(goHandle)) and (GetGameObjectStateMachineActiveByHandle(goHandle)) then
      [*] = ;begin
      [*] = ;   var elmHandle,life,max_life : Integer;
      [*] = ;   var hero_hint : String;
      [*] = ;
      [*] = ;   if (hudHandle = 0) then
      [*] = ;   begin
      [*] = ;      hudHandle := GUIGroupHUDCollectionAddGameObject(hudCollection, goHandle);
      [*] = ;      elmHandle := AddNewElementParent('', 'btn', goHandle, hudHandle);
      [*] = ;      SetGUIElementPressState(elmHandle, cEventPressHeroHUDState);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      elmHandle := GetGUIElementIndexByNameParent('btn', hudHandle);
      [*] = ;      SetGUIElementTag(elmHandle, goHandle);
      [*] = ;
      [*] = ;      elmHandle := GetGUIElementIndexByNameParent('map_radialhero_maincircle_dummy', hudHandle);
      [*] = ;      RemoveGUIChildren(hudHandle);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // HUD button
      [*] = ;   var elmImageHandle : Integer;
      [*] = ;   var Tag : Integer = goHandle;
      [*] = ;   var task : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask);
      [*] = ;   var heroParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   var portrait : String = ParserGetValueByKeyByHandle(heroParser, 'Portrait');
      [*] = ;   var elmPortraitDummy : Integer = _gui_CreateDummy('map_radialhero_portrait_dummy' , hudHandle, 'halParentMiddle', 'valParentMiddle', 0, 0, 0, 0, Tag);
      [*] = ;   elmImageHandle := _gui_CreateImage('map_radialhero_portrait_image', elmPortraitDummy, portrait, 'halParentMiddle', 'valParentMiddle', 0, 0, 70, 70, 0);
      [*] = ;
      [*] = ;   var posX, posY : Integer;
      [*] = ;   posX := 0;
      [*] = ;   posY := 0;
      [*] = ;   var frame : String = 'map.heroselection.browncircle';
      [*] = ;   var elmPortraitFrameHandle : Integer = _gui_CreateImage('map_radialhero_frame', elmImageHandle, frame, 'halParentMiddle', 'valParentMiddle', posX, posY, 0, 0, 0);
      [*] = ;   if (gIntRegister_MapSelectedUID<>goUID) then
      [*] = ;   begin
      [*] = ;      frame := 'map.heroselection.browncircle';
      [*] = ;      posX := 0;
      [*] = ;      posY := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var portraitTaskHandle : Integer = _gui_CreateImage('map_radialhero_portrait_task', hudHandle, 'map.herohud.withtask', 'halParentMiddle', 'valParentMiddle', 98, -1, 0, 0, 0);
      [*] = ;   var elmMainCircle : Integer = _gui_CreateDummy('map_radialhero_maincircle_dummy' , hudHandle, 'halParentMiddle', 'valParentMiddle', 0, 0, 0, 0, Tag);
      [*] = ;
      [*] = ;   var radialMatName : String;
      [*] = ;   var sizeX, sizeY : Integer;
      [*] = ;   if task = 0 then
      [*] = ;   begin
      [*] = ;      posX := 0;
      [*] = ;      posY := 0;
      [*] = ;      radialMatName := 'map.radialhero.maincircle';
      [*] = ;      sizeX := 192;
      [*] = ;      sizeY := 192;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      posX := 71;
      [*] = ;      posY := -4;
      [*] = ;      radialMatName := 'map.radialhero.maincircle.withtask';
      [*] = ;      sizeX := 327;
      [*] = ;      sizeY := 191;
      [*] = ;   end;
      [*] = ;
      [*] = ;   elmImageHandle := _gui_CreateImage('map_radialhero_maincircle', elmMainCircle, radialMatName, 'halParentMiddle', 'valParentMiddle', posX, posY, sizeX, sizeY, Tag);
      [*] = ;   //var portraitTaskHandle : Integer = _gui_CreateImage('map_radialhero_portrait_task', hudHandle, 'map.herohud.withtask', 'halParentMiddle', 'valParentMiddle', 101, -9, 0, 0, 0);
      [*] = ;   var portraitTaskTextHandle : Integer = _gui_CreateDummy('map_radialhero_portrait_task_text', hudHandle, 'halParentMiddle', 'valParentMiddle', 101, -9, 273, 140, 0);
      [*] = ;
      [*] = ;   var elmMultiHUDDummy : Integer = GUICreateDummy('map_radialhero_multihud_dummy' , hudHandle, 'halParentMiddle', 'valParentMiddle', 0, 0, 0, 0, Tag);
      [*] = ;   //dont use _gui_CreateDummy, cause it use other class that clear element on fadeout
      [*] = ;
      [*] = ;   posX := 0;
      [*] = ;   posY := 0;
      [*] = ;   elmImageHandle := _gui_CreateImage('map_radialhero_frame_selection', hudHandle, 'map.heroselection.yellowcircle', 'halParentMiddle', 'valParentMiddle', posX, posY, 75, 75, 0);
      [*] = ;   if (gIntRegister_MapSelectedUID=GetGameObjectUniqueIdByHandle(goHandle)) then
      [*] = ;      SetGUIElementVisible(elmImageHandle, True)
      [*] = ;   else
      [*] = ;      SetGUIElementVisible(elmImageHandle, False);
      [*] = ;
      [*] = ;   var elmPortraitHandle : Integer = _gui_CreateButton('map_radialhero_portrait', elmPortraitDummy, '', 'map.heroselection.button', 'halParentMiddle', 'valParentMiddle', 0, 0, 69, 69, 'map.DoOnPressHud', '', goHandle);
      [*] = ;   //SetGUIElementVisibleProperties(elmPortraitHandle, 'HoverProperty', 'map.heroselection.button.normal', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1); //swaped
      [*] = ;   //SetGUIElementVisibleProperties(elmPortraitHandle, 'DownProperty', 'map.heroselection.button.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1); //swaped
      [*] = ;   SetGUIElementVisibleProperties(elmPortraitHandle, 'HoverProperty', 'map.heroselection.button.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1); //swaped
      [*] = ;   SetGUIElementVisibleProperties(elmPortraitHandle, 'DownProperty', 'map.heroselection.button.normal', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1); //swaped
      [*] = ;   SetGUIElementStringTag(elmPortraitHandle, 'hudhero');
      [*] = ;   IntRegister0 := gc_map_hero_iLife;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;   max_life := IntRegister1;
      [*] = ;   life := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurHP);
      [*] = ;   _hero_GetName(goHandle,hero_hint);
      [*] = ;   hero_hint := hero_hint+'. '+GetLocaleTableListItemByID('gui','685')+': '+IntToStr(life)+'/'+IntToStr(max_life);
      [*] = ;   SetGUIElementHint(elmPortraitHandle,hero_hint);
      [*] = ;
      [*] = ;   var cButtonDist : Float = 58;
      [*] = ;   var cButtonAngle : Float = 15+62;
      [*] = ;   var vecX : Float = cButtonDist;
      [*] = ;   var vecY : Float = 0;
      [*] = ;   var vecZ : Float = 0;
      [*] = ;
      [*] = ;   VectorRotateY(vecX, vecY, vecZ, cButtonAngle+360/7);
      [*] = ;   //var hint : String = 'gui|618';
      [*] = ;   //var elmBtnHandle : Integer = _gui_CreateButton('map_radialhero_btn_heroinfo', elmMainCircle, '', 'map.radialhero.btn.info', 'halParentMiddle', 'valParentMiddle', round(vecX)-1, round(vecZ), 49, 49, cEventPressHeroHUDState, hint, gc_gui_radialherohud_btnHeroInfo);
      [*] = ;
      [*] = ;   // Hero exchange button
      [*] = ;   // Change hero arrows, if there is more than 1 hero in province
      [*] = ;   var heroCount : Integer = 0;
      [*] = ;   var curProvUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   var heroCurUID : Integer;
      [*] = ;   var skipUID : Integer;
      [*] = ;   var side : Integer;
      [*] = ;
      [*] = ;   heroCurUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;   skipUID := gIntRegister_GUIActiveHeroUID2;
      [*] = ;   side := 0;
      [*] = ;
      [*] = ;   var heroPrevUID : Integer = 0;
      [*] = ;   var heroNextUID : Integer = 0;
      [*] = ;   var tmpPrevUID : Integer = 0;
      [*] = ;   var heroFirstUID, heroLastUID : Integer = 0;
      [*] = ;   var bFirst, bLast : Boolean = False;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;   begin
      [*] = ;      var tmpGoHnd : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      var tmpGoUID : Integer = GetGameObjectUniqueIdByHandle(tmpGoHnd);
      [*] = ;      var dead : Boolean = GetGameObjectBoolValueIndByHandle(tmpGoHnd, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;      var curUID : Integer = GetGameObjectIntValueIndByHandle(tmpGoHnd, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;      if (not dead) and (curUID=curProvUID) then
      [*] = ;      begin
      [*] = ;         heroCount := heroCount+1;
      [*] = ;         if (tmpGoUID<>skipUID) then
      [*] = ;         begin
      [*] = ;            if (heroFirstUID=0) then
      [*] = ;               heroFirstUID := tmpGoUID;
      [*] = ;            heroLastUID := tmpGoUID;
      [*] = ;
      [*] = ;            if (tmpGoUID<>heroCurUID) then
      [*] = ;            begin
      [*] = ;               if (heroNextUID=0) and ((heroPrevUID<>0) or (bFirst)) then
      [*] = ;                  heroNextUID := tmpGoUID
      [*] = ;               else
      [*] = ;                  tmpPrevUID := tmpGoUID;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (tmpPrevUID<>0) then
      [*] = ;                  heroPrevUID := tmpPrevUID
      [*] = ;               else
      [*] = ;                  bFirst := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (heroLastUID=heroCurUID) then
      [*] = ;      bLast := True;
      [*] = ;
      [*] = ;   if (bFirst) then
      [*] = ;      heroPrevUID := heroLastUID
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (bLast) then
      [*] = ;         heroNextUID := heroFirstUID;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var bAllowHeroExchange : Boolean = (((gIntRegister_GUIActiveHeroUID2<>0) and (heroCount>2)) or ((gIntRegister_GUIActiveHeroUID2=0) and (heroCount>1)));
      [*] = ;   var goHandleExchange : Integer = GetGameObjectHandleByUniqueId(heroNextUID);
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('map_radialhero_btn_heroexchange', elmMainCircle, '', 'heropanel.btn.heroexchange', 'halParentMiddle', 'valParentMiddle', round(vecX)-1, round(vecZ), 49, 49, 'map.DoHeroExchange', 'gui|676', goHandleExchange);
      [*] = ;   if (not bAllowHeroExchange) or (not gBoolRegister_MapTurnFinished) then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;   var dummyUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;   var f : Integer;
      [*] = ;   var isGarr, isShop, isLibrary, enabled : Boolean = False;
      [*] = ;   var hero_flags : Integer;
      [*] = ;   var hint,temp_str,uid_str : String;
      [*] = ;
      [*] = ;   uid_str := '';
      [*] = ;   _sa_AddAsInt(uid_str,1);
      [*] = ;   _sa_AddAsInt(uid_str,goUID);
      [*] = ;
      [*] = ;   hero_flags := _cmd_CheckExtNF('herocancelorder','',uid_str,temp_str);
      [*] = ;   if (hero_flags <> 1) then  hero_flags := 0
      [*] = ;   else hero_flags := _sa_GetAsInt(temp_str,0);
      [*] = ;   // garrison: & 0x10041 == 0x10001
      [*] = ;   if ((hero_flags and $10041) = $10001) then isGarr := true;
      [*] = ;   // library: & 0x10044 == 0x10004
      [*] = ;   // shop: & 0x10042 == 0x10002
      [*] = ;   if ((hero_flags and $10042) = $10002) then isShop := true;
      [*] = ;   f := _cmd_CheckNF('herospellbook','',uid_str);
      [*] = ;   if (f = 1) then isLibrary := true;
      [*] = ;
      [*] = ;   VectorRotateY(vecX, vecY, vecZ, 360/7);
      [*] = ;   elmBtnHandle := _gui_CreateButton('map_radialhero_btn_garrison', elmMainCircle, '', 'hero.btn.hiretroops'{'map.radialhero.btn.garrison'}, 'halParentMiddle', 'valParentMiddle', round(vecX), round(vecZ), 49, 49, cEventPressHeroHUDState, 'hint|4', gc_gui_radialherohud_btnSquad);
      [*] = ;   if not isGarr then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if gBoolRegister_BtnGarrisonBlink then
      [*] = ;         _gui_CreateBlinkElement('btnGarrison', elmBtnHandle, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   VectorRotateY(vecX, vecY, vecZ, 360/7);
      [*] = ;   elmBtnHandle := _gui_CreateButton('map_radialhero_btn_treasury', elmMainCircle, '', 'hero.btn.equipitems'{'map.radialhero.btn.treasury'}, 'halParentMiddle', 'valParentMiddle', round(vecX), round(vecZ), 49, 49, cEventPressHeroHUDState, 'hint|33', gc_gui_radialherohud_btnInventory);
      [*] = ;   if not isShop then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if gBoolRegister_BtnShopBlink then
      [*] = ;         _gui_CreateBlinkElement('btnShop', elmBtnHandle, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   VectorRotateY(vecX, vecY, vecZ, 360/7);
      [*] = ;   elmBtnHandle   := _gui_CreateButton('map_radialhero_btn_magic', elmMainCircle, '', 'hero.btn.learnspell'{'map.radialhero.btn.magic'}, 'halParentMiddle', 'valParentMiddle', round(vecX), round(vecZ), 49, 49, cEventPressHeroHUDState, 'gui|318', gc_gui_radialherohud_btnSpellbook);
      [*] = ;   if not isLibrary then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if gBoolRegister_BtnLibraryBlink then
      [*] = ;         _gui_CreateBlinkElement('btnLibrary', elmBtnHandle, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if task = 0 then
      [*] = ;   begin
      [*] = ;      VectorRotateY(vecX, vecY, vecZ, 360/7);
      [*] = ;
      [*] = ;      f := _cmd_CheckNF('heroattackguard','',uid_str);
      [*] = ;      if (f = 1) then
      [*] = ;         elmBtnHandle := _gui_CreateButton('map_radialhero_btn_attackguard', elmMainCircle, '', 'map.radialhero.btn.attackguard', 'halParentMiddle', 'valParentMiddle', round(vecX), round(vecZ), 49, 49, cEventPressHeroHUDState, 'gui|45', gc_gui_radialherohud_btnAttackGuard)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmBtnHandle   := _gui_CreateButton('map_radialhero_btn_robber', elmMainCircle, '', 'map.radialhero.btn.robber', 'halParentMiddle', 'valParentMiddle', round(vecX), round(vecZ), 49, 49, cEventPressHeroHUDState, 'gui|43', gc_gui_radialherohud_btnRobber);
      [*] = ;         f := _cmd_CheckNF('heroplunder','',uid_str);
      [*] = ;         if (f <> 1) then
      [*] = ;            SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      //_log_values('F',hero_flags,0,0,0,0,0);
      [*] = ;      VectorRotateY(vecX, vecY, vecZ, (360/7)*3);
      [*] = ;      elmBtnHandle := _gui_CreateButton('map_radialhero_btn_cancelorder', elmMainCircle, '', 'map.radialhero.btn.cancel', 'halParentMiddle', 'valParentMiddle', round(vecX)-2, round(vecZ), 49, 49, cEventPressHeroHUDState, 'gui|101', gc_gui_radialherohud_btnCancelOrder);
      [*] = ;      if ((hero_flags and $10040) = $10040) or (hero_flags = 0) then
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if task = 0 then
      [*] = ;   begin
      [*] = ;      var dummyUID : Integer = GetGameObjectIntValueIndByHandle(goHandle,  gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;      var pStratHexCell,explored,siteCount : Integer;
      [*] = ;      var temp_str : String;
      [*] = ;
      [*] = ;      IntRegister0 := dummyUID;
      [*] = ;      MapExecuteState('GetProvinceParserByUID');
      [*] = ;      pStratHexCell := IntRegister1;
      [*] = ;
      [*] = ;      temp_str := '';
      [*] = ;      _sa_AddAsInt(temp_str,1);
      [*] = ;      _sa_AddAsInt(temp_str,pStratHexCell);
      [*] = ;      _sa_AddAsInt(temp_str,goHandle);
      [*] = ;      explored := _cmd_CheckExtNF('provincesiteslist','',temp_str,temp_str);
      [*] = ;      siteCount := _sa_GetAsInt(temp_str,2);
      [*] = ;      if (explored = 1) and (siteCount > 0) then
      [*] = ;         enabled := true
      [*] = ;      else
      [*] = ;         enabled := false;
      [*] = ;      explored := _sa_GetAsInt(temp_str,1);
      [*] = ;
      [*] = ;      VectorRotateY(vecX, vecY, vecZ, 360/7);
      [*] = ;      elmBtnHandle := _gui_CreateButton('map_radialhero_btn_site', elmMainCircle, '', 'map.radialhero.btn.site', 'halParentMiddle', 'valParentMiddle', round(vecX)-1, round(vecZ), 49, 49, cEventPressHeroHUDState, 'gui|654', gc_gui_radialherohud_btnSite);
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, enabled);
      [*] = ;      if enabled and gBoolRegister_BtnEnterSiteBlink then
      [*] = ;         _gui_CreateBlinkElement('btnEnterSite', elmBtnHandle, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;
      [*] = ;      VectorRotateY(vecX, vecY, vecZ, 360/7);
      [*] = ;      elmBtnHandle := _gui_CreateButton('map_radialhero_btn_explore', elmMainCircle, '', 'map.radialhero.btn.explore', 'halParentMiddle', 'valParentMiddle', round(vecX)-2, round(vecZ), 49, 49, cEventPressHeroHUDState, 'gui|42', gc_gui_radialherohud_btnExplore);
      [*] = ;      siteCount := _cmd_CheckNF('heroexplore','',uid_str);
      [*] = ;      if (siteCount <> 1) or (explored >= 100) then enabled := false
      [*] = ;      else enabled := true;
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, enabled);
      [*] = ;      if enabled and gBoolRegister_BtnExploreBlink then
      [*] = ;         _gui_CreateBlinkElement('btnExplore', elmBtnHandle, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetGUIElementVisible(elmMainCircle, false);
      [*] = ;
      [*] = ;   IntRegister0 := goHandle;
      [*] = ;   GUIExecuteState('map.HeroHUDControlTask');
      [*] = ;   GUIExecuteState('map.DrawGroupDataViewer');
      [*] = ;end;
   struct.end
section.end

