section.begin
   Name = CreateControlPanel
   Code : struct.begin
      [*] = ;var top : integer = _gui_GetLayerI();
      [*] = ;var tag : integer = 0;
      [*] = ;const cIconSize : Integer = 52;
      [*] = ;
      [*] = ;//MainPanel
      [*] = ;var yOff : Integer = 2;
      [*] = ;var uid : Integer = gIntRegister_AstralSelectedShard;
      [*] = ;var plEnergy : Integer = gCampaign.arrCampPlayers[0].energy;
      [*] = ;
      [*] = ;var elmParentMainPanelHandle : integer = _gui_GetOrCreateElement('astral_mainpanel', top, 'halMiddle', 'valBottomHeight', 0, 0, GetViewerWidth, GetViewerHeight, Tag);
      [*] = ;SetGUIElementVisible(elmParentMainPanelHandle, true);
      [*] = ;
      [*] = ;var elmImageHandle : Integer = _gui_CreateImage('astral_mainpanel_left_blank', elmParentMainPanelHandle,  gc_gui_material_blank_0, 'halLeft', 'valBottomHeight', 0, 0, 279, 64, Tag);
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;elmImageHandle := _gui_CreateImage('astral_mainpanel_left', elmParentMainPanelHandle, 'astral.mainpanel.left', 'halLeft', 'valBottomHeight', 0, 0, 279, 123, Tag);
      [*] = ;const cBtnMenu = 102;
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButtonFromCollection('astral_mainpanel_btn_menu', elmParentMainPanelHandle, 'map.mainpanel.btn.menu', 'halLeft', 'valBottomHeight', 67, yOff, 'EventControlPanel', cBtnMenu);
      [*] = ;SetGUIElementHint(elmBtnHandle,'tooltip|astral_mainpanel_btn_menu|MT|0|0|astralshowmenu');
      [*] = ;var fontHandleH1, fontHandleT, fontHandleH2, fontHandleN : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_astral,'Text',gc_gui_fontsize_largest,'',fontHandleH1); // H2
      [*] = ;_gui_GetFont(gc_gui_fontsection_astral,'Text',gc_gui_fontsize_default,'',fontHandleT); // Simple text
      [*] = ;_gui_GetFont(gc_gui_fontsection_astral,'Numbers',gc_gui_fontsize_default,'',fontHandleN); // Numbers
      [*] = ;_gui_GetFont(gc_gui_fontsection_astral,'Text',gc_gui_fontsize_large,'',fontHandleH2); // H2
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('astral_energy_amount', elmParentMainPanelHandle, intToStr(plEnergy), 'halLeft', 'valBottomHeight', 178, 4, 80, 70, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;SetGUIElementTextAlign(elmTextHandle, 'halMiddle', 'valMiddle', 0, -10);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;elmImageHandle := _gui_CreateImage('astral_mainpanel_right_blank', elmParentMainPanelHandle, gc_gui_material_blank_0, 'halRight', 'valBottomHeight', -327, 0, 327, 64, Tag);
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;elmImageHandle := _gui_CreateImage('astral_mainpanel_right', elmParentMainPanelHandle, 'astral.mainpanel.right', 'halRight', 'valBottomHeight', -327, 0, 327, 123, Tag);
      [*] = ;elmBtnHandle   := _gui_CreateButtonFromCollection('astral_mainpanel_btn_zarr', elmParentMainPanelHandle, 'astral.mainpanel.btn.zarr', 'halRight', 'valBottomHeight', -299, yOff, '', gc_gui_astral_btnZarr);
      [*] = ;SetGUIElementHint(elmBtnHandle,'tooltip|astral_mainpanel_btn_zarr|MT|0|0|astraltalktozarr');
      [*] = ;if gBoolRegister_BtnZarrTalkBlink then
      [*] = ;   _gui_CreateBlinkElement('btnZarr', elmBtnHandle, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;
      [*] = ;elmBtnHandle   := _gui_CreateButtonFromCollection('astral_mainpanel_btn_statistics', elmParentMainPanelHandle, 'astral.mainpanel.btn.statistics', 'halRight', 'valBottomHeight', -247, yOff, '', gc_gui_astral_btnStatistics);
      [*] = ;SetGUIElementHint(elmBtnHandle,'tooltip|astral_mainpanel_btn_statistics|MT|0|0|astralshowjournal');
      [*] = ;if (gc_demoVersion=1) then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;if GetGUIElementEnabled(elmBtnHandle) and gBoolRegister_BtnAstralStatsBlink then
      [*] = ;   _gui_CreateBlinkElement('btnAstralStats', elmBtnHandle, gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;
      [*] = ;elmBtnHandle  := _gui_CreateButtonFromCollection('astral_mainpanel_btn_endturn', elmParentMainPanelHandle, 'map.mainpanel.btn.endturn', 'halRight', 'valBottomHeight', -177, yOff, '', gc_gui_astral_btnEndTurn);
      [*] = ;SetGUIElementHint(elmBtnHandle,'tooltip|astral_mainpanel_btn_endturn|MT|0|0|astralnextturn');
      [*] = ;
      [*] = ;var goHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;var shInd : Integer = _shard_GetShardByUID(uid);
      [*] = ;
      [*] = ;if (goHandle <> 0) {and (shInd >= 0)} then
      [*] = ;begin
      [*] = ;   var ownerInd : Integer = gShards[shInd].ipPlayer;
      [*] = ;   gIntRegister_CurrentCampPlayer := ownerInd;
      [*] = ;
      [*] = ;   var selectedShardMode : Integer = 0;//0 - no info, 1 - no owner shard, 2 - players shard, 3 - enemy player shard
      [*] = ;   if ownerInd < 0 then
      [*] = ;   selectedShardMode := 1
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if ownerInd = 0 then
      [*] = ;      selectedShardMode := 2
      [*] = ;      else
      [*] = ;      selectedShardMode := 3;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var shardName : String = GetLocaleTableListItemByID(gc_gui_LangTableIDMapProvinceInfo, gShards[shInd].namePrefix);
      [*] = ;   shardName := shardName + GetLocaleTableListItemByID(gc_gui_LangTableIDMapProvinceInfo, gShards[shInd].nameSuffix);
      [*] = ;
      [*] = ;   var shardX : Integer = gShards[shInd].map.x;
      [*] = ;   var shardSize : String = GetLocaleTableListItemByID('shard', IntToStr((shardX-6) div 2));
      [*] = ;
      [*] = ;   var talkButtonText : String = '';
      [*] = ;   var elmInfoPanelHandle : Integer = _gui_CreateDummy('astral_infopanel', elmParentMainPanelHandle, 'halMiddle', 'valBottomHeight', 0, 0, GetViewerWidth, GetViewerHeight, Tag);
      [*] = ;   if selectedShardMode = 1 then
      [*] = ;   begin
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_infopanel_shard_block' , elmInfoPanelHandle, gc_gui_material_blank_0, 'halRight', 'valBottomHeight', -375, -140, 350, 421, Tag);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;
      [*] = ;      var shardIncome : Integer = gShards[shInd].income;
      [*] = ;      var terrain : Integer = gShards[shInd].terrain;
      [*] = ;      var terrainType : String = '';
      [*] = ;      //case (terrain) of
      [*] = ;      //end;
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_terrain_type_'+IntToStr(terrain), elmInfoPanelHandle, 'shard.terraintype.'+IntToStr(terrain), 'halRight', 'valBottomHeight', -330, -360-26, 257, 128, Tag);
      [*] = ;      //SetGUIElementTag(elmImageHandle, 1); //for special fade out time
      [*] = ;      var hint : String;
      [*] = ;      if (terrain<6) then
      [*] = ;      hint := 'gui|'+IntToStr(terrain+334)
      [*] = ;      else
      [*] = ;      hint := 'gui|'+IntToStr((terrain-6)+683);
      [*] = ;      SetGUIElementHint(elmImageHandle, hint);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      talkButtonText := GetLocaleTableListItemByID('gui', '200');
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_infopanel_shard' , elmInfoPanelHandle, 'astral.infopanel.shard' , 'halRight', 'valBottomHeight', -375, -140, 350, 421, Tag);
      [*] = ;      //terrain
      [*] = ;      elmTextHandle := _gui_CreateText('astral_infopanel_shard_name', elmImageHandle, shardName, 'halRight', 'valBottomHeight', -325, -493, 248, 47, 'halMiddle', 'valMiddle', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_infopanel_energy_icon' , elmInfoPanelHandle, 'astral.energy.33x32' , 'halRight', 'valBottomHeight', -253, -327, 32, 33, Tag);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      elmTextHandle := _gui_CreateText('astral_infopanel_shard_income', elmImageHandle, '+'+IntToStr(shardIncome), 'halRight', 'valBottomHeight', -225, -327, 38, 32, 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;      SetGUIElementTextAlign(elmTextHandle, 'halMiddle', 'valMiddle', 0, 0);
      [*] = ;      SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;      if (gShards[shInd].worldrule<>0) then
      [*] = ;      begin
      [*] = ;         var elmStripHandle : Integer = _gui_CreateImage('astral_infopanel_shard_worldrule_strip', elmInfoPanelHandle, 'astral.shardinfo.worldrule.shadow'{gc_gui_material_blank_0}, 'halRight', 'valBottomHeight', -326, -384, 0, 0, 0);
      [*] = ;         var text : String = GetLocaleTableListItemByID('worldrule', IntToStr(gShards[shInd].worldRule));
      [*] = ;         elmTextHandle := _gui_CreateText('astral_infopanel_shard_worldrule', elmStripHandle, text, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmStripHandle), GetGUIElementHeight(elmStripHandle), 'halMiddle', 'valMiddle', fontHandleN, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB{gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB}, 1);
      [*] = ;         SetGUIElementTextAlign(elmTextHandle, 'halMiddle', 'valMiddle', 0, 0);
      [*] = ;         SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;         var hint : String = GetLocaleTableListItemByID('worldrule', IntToStr(gShards[shInd].worldRule)+'.legend')+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('worldrule', IntToStr(gShards[shInd].worldRule)+'.description');
      [*] = ;         SetGUIElementHint(elmTextHandle, hint);
      [*] = ;         var w, h : Integer;
      [*] = ;         GetGUIElementFontTextFormatRect(fontHandleN, text, w, h);
      [*] = ;         elmImageHandle := _gui_CreateImage('astral_infopanel_shard_worldrule_infoicon', elmTextHandle, 'astral.shardinfo.worldrule.details.icon'{gc_gui_material_blank_0}, 'halParentMiddle', 'valParentTop', 16+(w div 2), 10, 0, 0, 0);
      [*] = ;         SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;         SetGUIElementHint(elmImageHandle, hint);
      [*] = ;      end;
      [*] = ;      elmTextHandle := _gui_CreateText('astral_infopanel_shard_size', elmImageHandle, shardSize, 'halRight', 'valBottomHeight', -306, -369, 208, 27, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;      elmBtnHandle   := _gui_CreateButtonFromCollection('astral_infopanel_btn_attack', elmInfoPanelHandle, 'astral.infopanel.btn.talk', 'halRight', 'valBottomHeight', -324, -154, '', gc_gui_astral_btnAttack);
      [*] = ;      SetGUIElementHint(elmBtnHandle,'tooltip|astral_infopanel_btn_attack|MT|0|0|astralattackshard');
      [*] = ;      elmTextHandle  := _gui_CreateText('talk_button', elmBtnHandle, talkButtonText, 'halRight', 'valBottomHeight', -327, -154, 248, 47, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;      // cheat button capture shard
      [*] = ;      if (gc_demoVersion=1) then
      [*] = ;      begin
      [*] = ;         var text : String = GetLocaleTableListItemByID('gui', '612');
      [*] = ;         const captureShard = 100;
      [*] = ;         var posX, posY : Integer;
      [*] = ;         posX := 0;
      [*] = ;         posY := -49;
      [*] = ;         elmBtnHandle := _gui_CreateButtonFromCollection('astral_capture_shard', elmInfoPanelHandle, 'astral.infopanel.btn.talk', 'halMiddle', 'valBottom'{'valTop'}, posX, posY, 'EventControlPanel', captureShard);
      [*] = ;         SetGUIElementHint(elmBtnHandle, 'gui|614');
      [*] = ;         elmTextHandle := _gui_CreateText('', elmBtnHandle, text, 'halParentLeft', 'valParentTop', 0, 0, 248, 47, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;
      [*] = ;         ExecuteState('UpdateHUDRestict');
      [*] = ;      end;
      [*] = ;
      [*] = ;      //buildings
      [*] = ;      var i : Integer;
      [*] = ;      for i := 0 to gc_MaxShardBuild-1 do
      [*] = ;      begin
      [*] = ;         var shardBuildingID : Integer = gShards[shInd].arBuilding[i];
      [*] = ;         if shardBuildingID > 0 then
      [*] = ;         begin
      [*] = ;            var shardBuildingIcon : Integer = 0;
      [*] = ;
      [*] = ;            var pInnerBuilding : Integer = ParserSelectByHandleByIndex(gPrototypeData.innerBuildings.handle, shardBuildingID);
      [*] = ;            shardBuildingIcon := ParserGetIntValueByKeyByHandle(pInnerBuilding, 'Icon');
      [*] = ;
      [*] = ;            _gui_CreateImage('', elmImageHandle, 'icon.building.' + IntToStr(shardBuildingIcon), 'halRight', 'valBottomHeight', -311+(i*cIconSize+i*4), -265, cIconSize, cIconSize, 0);
      [*] = ;            elmBtnHandle := _gui_CreateButton('shard_building_icon', elmImageHandle, '', 'unitpanel.button.cover', 'halRight', 'valBottomHeight', -313+(i*cIconSize+i*4), -264, cIconSize+3, cIconSize+3, '', '', shardBuildingID);
      [*] = ;            _gui_ft_AttachHint_I2(elmBtnHandle,'VVK.FTooltipInnerBuilding',cFT_IBShardInfo,shardBuildingID);
      [*] = ;            //SetGUIElementHint(elmBtnHandle, shardBuildingHint);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //bonuses
      [*] = ;      for i := 0 to gc_MaxShardBonus-1 do
      [*] = ;      begin
      [*] = ;         var bonusID : Integer = gShards[shInd].arBonus[i][0];
      [*] = ;         var bonusValue : Integer = gShards[shInd].arBonus[i][1];
      [*] = ;
      [*] = ;         if bonusID > 0 then
      [*] = ;         begin
      [*] = ;            var pBonus : Integer = ParserSelectByHandleByIndex(gPrototypeData.shardBonuses.handle, bonusID);
      [*] = ;            var bonusHint : String = GetLocaleTableListItemByID('shard_bonus', IntToStr(bonusID))+': ';
      [*] = ;
      [*] = ;            var bonusIcon : String = '';
      [*] = ;            case (bonusID) of
      [*] = ;               1: begin
      [*] = ;                  bonusIcon := 'castle.building.icon.gold.big';
      [*] = ;                  bonusHint := bonusHint+' +'+IntToStr(bonusValue);
      [*] = ;               end;
      [*] = ;               2: begin
      [*] = ;                  bonusIcon := 'castle.building.icon.crystal.big';
      [*] = ;                  bonusHint := bonusHint+' +'+IntToStr(bonusValue);
      [*] = ;               end;
      [*] = ;               3: begin
      [*] = ;                  bonusIcon := 'icon.shardbonus.2';
      [*] = ;                  bonusHint := bonusHint+' +'+IntToStr(bonusValue);
      [*] = ;               end;
      [*] = ;               4: begin
      [*] = ;                  bonusIcon := 'icon.shardbonus.3';
      [*] = ;                  bonusHint := bonusHint+' +'+IntToStr(bonusValue);
      [*] = ;               end;
      [*] = ;               5: begin
      [*] = ;                  var itemID : Integer = bonusValue;
      [*] = ;                  bonusIcon := 'icon.item.'+IntToStr(itemID);
      [*] = ;                  _gui_ft_CreateHint_I6(bonusHint,'VVK.FTooltipItem',itemID,cFT_ItemPriceHide,-1,cFT_ItemHeroDefault,2,2);
      [*] = ;                  //bonusHint := bonusHint+gc_gui_BreakLine+GetLocaleTableListItemByID('item', IntToStr(itemID));
      [*] = ;               end;
      [*] = ;               6: begin
      [*] = ;                  bonusIcon := 'icon.shardbonus.4';
      [*] = ;                  var unitID : Integer = bonusValue;
      [*] = ;                  _gui_ft_CreateHint_I6(bonusHint,'VVK.FTooltipUnit',cFT_UnitTemplate,unitID,0,0,2,2);
      [*] = ;                  //bonusHint := bonusHint+gc_gui_BreakLine+GetLocaleTableListItemByID('unit', IntToStr(unitID));
      [*] = ;               end;
      [*] = ;               7: begin
      [*] = ;                  var buildID : Integer = bonusValue;
      [*] = ;                  var pInnerBuilding : Integer = ParserSelectByHandleByIndex(gPrototypeData.innerBuildings.handle, buildID);
      [*] = ;
      [*] = ;                  //var buildName : String = GetLocaleTableListItemByID('inner_build', IntToStr(BuildID));
      [*] = ;                  bonusIcon := 'icon.building.'+ParserGetValueByKeyByHandle(pInnerBuilding, 'Icon');
      [*] = ;                 _gui_ft_CreateHint_I2(bonusHint,'VVK.FTooltipInnerBuilding',cFT_IBShardInfo,buildID);
      [*] = ;                  //bonusHint := bonusHint+gc_gui_BreakLine+buildName;
      [*] = ;               end;
      [*] = ;               8: begin
      [*] = ;                  var pResources : Integer = gPrototypeData.resources.handle;
      [*] = ;                  var resID : Integer = bonusValue;
      [*] = ;                  var resName : String = GetLocaleTableListItemByID('resource', IntToStr(resID));
      [*] = ;                  var resIconID : Integer = resID;
      [*] = ;                  bonusHint := GetLocaleTableListItemByID('shard_bonus', IntToStr(bonusID))+' (10%): '+gc_gui_BreakLine+GetLocaleTableListItemByID('resource', IntToStr(resID))+'';
      [*] = ;                  //bonusHint := bonusHint+gc_gui_BreakLine+resName;
      [*] = ;                  resName := StrReplace(resName, 'Res.', '');
      [*] = ;                  resName := StrToLowerCase(resName);
      [*] = ;                  bonusIcon := 'map.resource.'+IntToStr(resIconID);
      [*] = ;               end;
      [*] = ;               9: begin
      [*] = ;                  bonusIcon := 'icon.shardbonus.5';
      [*] = ;                  var defenderID : Integer = bonusValue;
      [*] = ;                  var defenderName : String = GetLocaleTableListItemByID('defender', IntToStr(DefenderID));
      [*] = ;                  bonusHint := bonusHint+gc_gui_BreakLine+defenderName;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmImageHandle, bonusIcon, 'halRight', 'valBottomHeight', -311+(i*cIconSize+i*4), -209, cIconSize, cIconSize, 0);
      [*] = ;            if (bonusID = 6) or (bonusID = 5) then
      [*] = ;               elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop',0, 0, cIconSize, cIconSize, '', bonusHint, 0)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', gc_gui_material_blank_0 , 'halParentLeft', 'valParentTop',0, 0, cIconSize, cIconSize, '', bonusHint, 0);
      [*] = ;               SetGUIElementVisibleProperties(elmBtnHandle,'DisabledProperty',gc_gui_material_blank_0, 0, 0, 0, 0, 1, 1, 1, 1, 1);
      [*] = ;               SetGUIElementEnabled(elmBtnHandle,false);
      [*] = ;            end;
      [*] = ;            //SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //random buildings count - not ok, cause we don't know how many rand buildings are on this shard. this list generated in 'astral.AddHiddenBuildings', but with random, and it depends on what buildings player already have.
      [*] = ;      //elmImageHandle := _gui_CreateImage('', elmImageHandle, 'astral.bonus.random.icon', 'halRight', 'valBottomHeight', -311+(3*cIconSize+3*4), -209, cIconSize, cIconSize, 0);
      [*] = ;      //SetGUIElementHint(elmImageHandle, 'gui|754');
      [*] = ;      //SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if selectedShardMode = 2 then
      [*] = ;   begin
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_infopanel_player_block', elmInfoPanelHandle, gc_gui_material_blank_0, 'halRight', 'valBottomHeight', -375, -140, 350, 389, Tag);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_player_avatar', elmInfoPanelHandle, 'astral.players.icon.big.player'{'astral.players.icon.big.'+IntToStr(gProfile.avatar)}, 'halRight', 'valBottomHeight', -255, -343, 109, 109, Tag);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_infopanel_player', elmInfoPanelHandle, 'astral.infopanel.player', 'halRight', 'valBottomHeight', -375, -140, 350, 389, Tag);
      [*] = ;      elmTextHandle := _gui_CreateText('astral_player_name', elmImageHandle, gProfile.name, 'halRight', 'valBottomHeight', -325, -460, 248, 47, 'halMiddle', 'valMiddle', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;      var difficulty : Integer = gProfile.difficulty; //gCampaign.difficulty;
      [*] = ;      elmTextHandle := _gui_CreateText('astral_player_difficulty', elmImageHandle, 'difficulty|'+IntToStr(difficulty), 'halRight', 'valBottomHeight', -325, -298-1, 248, 40, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;      SetGUIElementHint(elmTextHandle, 'gui|660');
      [*] = ;      var karma : Integer = gCampaign.arrcampplayers[0].karma;
      [*] = ;      var rulerNickID : Integer = 0;
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to gPrototypeData.rulerNicks.number-1 do
      [*] = ;      begin
      [*] = ;         var pRulerNick : Integer = ParserSelectByHandleByIndex(gPrototypeData.rulerNicks.handle, j);
      [*] = ;         var min : Integer = ParserGetIntValueByKeyByHandle(pRulerNick, 'Min');
      [*] = ;         var max : Integer = ParserGetIntValueByKeyByHandle(pRulerNick, 'Max');
      [*] = ;         if (karma>=min) and (karma<max) then
      [*] = ;         begin
      [*] = ;            rulerNickID := ParserGetIntValueByKeyByHandle(pRulerNick, 'RulerNickID');
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (rulerNickID<>0) then
      [*] = ;      begin
      [*] = ;         elmTextHandle := _gui_CreateText('astral_player_title', elmImageHandle, 'ruler_nick|'+IntToStr(rulerNickID), 'halRight', 'valBottomHeight', -325+13, -250, 220, 40, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;         SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;         SetGUIElementHint(elmTextHandle, 'gui|661');
      [*] = ;      end;
      [*] = ;
      [*] = ;      var sign : Integer =  gProfile.sign;
      [*] = ;      var color1 : Integer = gProfile.color1;
      [*] = ;      var color2 : Integer = gProfile.color2;
      [*] = ;      elmImageHandle := _gui_CreateHerb('', elmInfoPanelHandle, sign, color1, color2, 'halRight', 'valBottomHeight', -323+97, -277+60+44);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if selectedShardMode = 3 then
      [*] = ;   begin
      [*] = ;      talkButtonText := GetLocaleTableListItemByID('gui', '350');
      [*] = ;      var attitude : Integer = _camp_player_GetAttitude(gCampaign.arrCampPlayers[ownerInd]);
      [*] = ;      //var attitude : Integer = gCampaign.arrcampplayers[ownerInd].arrattitude[0];
      [*] = ;      var attitudeID : Integer = 0;
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to gPrototypeData.attitudes.number-1 do
      [*] = ;      begin
      [*] = ;         var pAttitude : Integer = ParserSelectByHandleByIndex(gPrototypeData.attitudes.handle, j);
      [*] = ;         var min : Integer = ParserGetIntValueByKeyByHandle(pAttitude, 'Min');
      [*] = ;         var max : Integer = ParserGetIntValueByKeyByHandle(pAttitude, 'Max');
      [*] = ;         if (attitude>=min) and (attitude<=max) then
      [*] = ;         begin
      [*] = ;            attitudeID := ParserGetIntValueByKeyByHandle(pAttitude, 'AttitudeID');
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_infopanel_enemy_block', elmInfoPanelHandle, gc_gui_material_blank_0, 'halRight', 'valBottomHeight', -375, -140, 350, 389, Tag);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_master_portrait_'+IntToStr(ownerInd) , elmInfoPanelHandle, 'astral.players.icon.big.'+IntToStr(ownerInd), 'halRight', 'valBottomHeight', -255, -343, 109, 109, Tag);
      [*] = ;      SetGUIElementHint(elmImageHandle, 'players|'+IntToStr(ownerInd)+'.hint');
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      elmImageHandle := _gui_CreateImage('astral_infopanel_enemy', elmImageHandle, 'astral.infopanel.enemy' , 'halRight', 'valBottomHeight', -375, -140, 350, 389, Tag);
      [*] = ;      elmTextHandle := _gui_CreateText('astral_master_name_'+IntToStr(ownerInd), elmImageHandle, GetLocaleTableListItemByID('players', IntToStr(ownerInd)), 'halRight', 'valBottomHeight', -325, -460, 248, 47, 'halMiddle', 'valMiddle', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;      SetGUIElementHint(elmTextHandle, 'players|'+IntToStr(ownerInd)+'.hint');
      [*] = ;      elmBtnHandle := _gui_CreateButtonFromCollection('astral_infopanel_btn_talk'{DO NOT CHANGE NAME, CAUSE IT IS USED IN DOONCLICKGUI}, elmInfoPanelHandle, 'astral.infopanel.btn.talk', 'halRight', 'valBottomHeight', -324, -154, '', gc_gui_astral_btnTalk);
      [*] = ;      SetGUIElementHint(elmBtnHandle,'tooltip|astral_infopanel_btn_talk|MT|0|0|astraltalktomaster');
      [*] = ;      elmTextHandle := _gui_CreateText('talk_button', elmBtnHandle, talkButtonText, 'halRight', 'valBottomHeight', -324, -154, 248, 47, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;      elmTextHandle := _gui_CreateText('astral_player_attitude', elmImageHandle, 'attitude|'+IntToStr(attitudeID), 'halRight', 'valBottomHeight', -325+13, -277-20, 220, 40, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;      SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;      SetGUIElementHint(elmTextHandle, 'gui|659');
      [*] = ;
      [*] = ;      var pPlayers : Integer = gPrototypeData.players.handle;
      [*] = ;      var pPlayer : Integer = ParserSelectByHandleByIndex(pPlayers, ownerInd);
      [*] = ;      var sign : Integer = ParserGetIntValueByKeyByHandle(pPlayer, 'Herb');
      [*] = ;      var color1 : Integer = ParserGetIntValueByKeyByHandle(pPlayer, 'Color1');
      [*] = ;      var color2 : Integer = ParserGetIntValueByKeyByHandle(pPlayer, 'Color2');
      [*] = ;      elmImageHandle := _gui_CreateHerb('', elmInfoPanelHandle, sign, color1, color2, 'halRight', 'valBottomHeight', -323+97, -277+60);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

