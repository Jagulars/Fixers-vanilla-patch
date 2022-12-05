section.begin
   Name = ShowBeforeBattleWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'ASTRAL.INC\SHOWBEFOREBATTLEWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;
      [*] = ;procedure SortParserByValueOrder(pSorts : Integer);
      [*] = ;begin
      [*] = ;   var pAfterSorts : Integer = _misc_ParserGetOrCreateByKey('pAfterSorts',true);
      [*] = ;
      [*] = ;   var i, j : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pSorts)-1 do
      [*] = ;   begin
      [*] = ;      var pSort : Integer = ParserSelectByHandleByIndex(pSorts, i);
      [*] = ;      var bonusType : String = ParserGetValueByKeyByHandle(pSort, 'Type');
      [*] = ;      var bonusID : Integer = ParserGetIntValueByKeyByHandle(pSort, 'BonusID');
      [*] = ;      var valueID : Integer = ParserGetIntValueByKeyByHandle(pSort, 'Value');
      [*] = ;      var energyCost : Integer = ParserGetIntValueByKeyByHandle(pSort, 'EnergyCost');
      [*] = ;      var pAfterSortNew : Integer = ParserAddChildByIndex(pAfterSorts, '*');
      [*] = ;
      [*] = ;      ParserSetValueByKeyByHandle(pAfterSortNew, 'Type', bonusType);
      [*] = ;      ParserSetIntValueByKeyByHandle(pAfterSortNew, 'BonusID', bonusID);
      [*] = ;      ParserSetIntValueByKeyByHandle(pAfterSortNew, 'Value', valueID);
      [*] = ;      ParserSetIntValueByKeyByHandle(pAfterSortNew, 'EnergyCost', energyCost);
      [*] = ;
      [*] = ;      for j:=ParserGetCountByHandle(pAfterSorts)-2 downto 0 do
      [*] = ;      begin
      [*] = ;         var pAfterSort : Integer = ParserSelectByHandleByIndex(pAfterSorts, j);
      [*] = ;         var tmpBonusType : String = ParserGetValueByKeyByHandle(pAfterSort, 'Type');
      [*] = ;         var tmpBonusID : Integer = ParserGetIntValueByKeyByHandle(pAfterSort, 'BonusID');
      [*] = ;         var tmpValueID : Integer = ParserGetIntValueByKeyByHandle(pAfterSort, 'Value');
      [*] = ;         var tmpEnergyCost : Integer = ParserGetIntValueByKeyByHandle(pAfterSort, 'EnergyCost');
      [*] = ;         if (energyCost<tmpEnergyCost) then
      [*] = ;         begin
      [*] = ;            ParserSetValueByKeyByHandle(pAfterSort, 'Type', bonusType);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSort, 'BonusID', bonusID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSort, 'Value', valueID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSort, 'EnergyCost', energyCost);
      [*] = ;
      [*] = ;            ParserSetValueByKeyByHandle(pAfterSortNew, 'Type', tmpBonusType);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSortNew, 'BonusID', tmpBonusID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSortNew, 'Value', tmpValueID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSortNew, 'EnergyCost', tmpEnergyCost);
      [*] = ;
      [*] = ;            pAfterSortNew := pAfterSort;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            ParserSetValueByKeyByHandle(pAfterSortNew, 'Type', bonusType);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSortNew, 'BonusID', bonusID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSortNew, 'Value', valueID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pAfterSortNew, 'EnergyCost', energyCost);
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserClearByHandle(pSorts);
      [*] = ;   ParserSelectByHandle(pAfterSorts);
      [*] = ;   ParserCopyToByHandle(pSorts);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetUnitEnergy(unitID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;   var goldPrice : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'GoldPrice');
      [*] = ;   var gemPrice : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'GemPrice');
      [*] = ;   Result := (goldPrice+(gemPrice*5) div 2)*2;
      [*] = ;
      [*] = ;   var pResources : Integer = ParserSelectByHandleByKey(pUnit, 'Resources');
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pResources)-1 do
      [*] = ;   begin
      [*] = ;      var pResource : Integer = ParserSelectByHandleByIndex(pResources, i);
      [*] = ;      var resourceID : Integer = ParserGetIntValueByKeyByHandle(pResource, 'ResourceID');
      [*] = ;      if (resourceID<>0) then
      [*] = ;      begin
      [*] = ;         var pVarResourceID : Integer = ParserSelectByHandleByIndex(gPrototypeData.resources.handle, resourceID);
      [*] = ;         var resourceGoldPrice : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Gold');
      [*] = ;         var resourceGemPrice : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Gem');
      [*] = ;         Result := Result+(resourceGoldPrice+(resourceGemPrice*5) div 2) div 2;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (unitID>12) then
      [*] = ;      Result := Result+(Result div 2);
      [*] = ;   Result := _misc_RoundUp((Result*0.25)/5)*5;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetItemEnergy(itemID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.items.handle, itemID);
      [*] = ;   var goldPrice : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GoldCost');
      [*] = ;   var gemPrice : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GemCost');
      [*] = ;   var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;   Result := (goldPrice+(gemPrice*5) div 2)*2 + (shopLevel-1)*10;
      [*] = ;
      [*] = ;   var pResources : Integer = ParserSelectByHandleByKey(pItem, 'Resources');
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pResources)-1 do
      [*] = ;   begin
      [*] = ;      var pResource : Integer = ParserSelectByHandleByIndex(pResources, i);
      [*] = ;      var resourceID : Integer = ParserGetIntValueByKeyByHandle(pResource, 'Resource');
      [*] = ;      if (resourceID<>0) then
      [*] = ;      begin
      [*] = ;         var pVarResourceID : Integer = ParserSelectByHandleByIndex(gPrototypeData.resources.handle, resourceID);
      [*] = ;         var resourceGoldPrice : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Gold');
      [*] = ;         var resourceGemPrice : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Gem');
      [*] = ;         Result := Result+(resourceGoldPrice+(resourceGemPrice*5) div 2) div 3;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := _misc_RoundUp((Result*0.2)/5)*5;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetBuildEnergy(buildID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pBuild : Integer = ParserSelectByHandleByIndex(gPrototypeData.innerbuildings.handle, buildID);
      [*] = ;   var goldPrice : Integer = ParserGetIntValueByKeyByHandle(pBuild, 'GoldPrice');
      [*] = ;   var gemPrice : Integer = ParserGetIntValueByKeyByHandle(pBuild, 'GemPrice');
      [*] = ;   Result := (goldPrice+(gemPrice*5) div 2)*2;
      [*] = ;
      [*] = ;   var pResources : Integer = ParserSelectByHandleByKey(pBuild, 'Resources');
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pResources)-1 do
      [*] = ;   begin
      [*] = ;      var pResource : Integer = ParserSelectByHandleByIndex(pResources, i);
      [*] = ;      var resourceID : Integer = ParserGetIntValueByKeyByHandle(pResource, 'ResourceID');
      [*] = ;      if (resourceID<>0) then
      [*] = ;      begin
      [*] = ;         var resCount : Integer = ParserGetIntValueByKeyByHandle(pResource, 'Count');
      [*] = ;         var pVarResourceID : Integer = ParserSelectByHandleByIndex(gPrototypeData.resources.handle, resourceID);
      [*] = ;         var resourceGoldPrice : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Gold');
      [*] = ;         var resourceGemPrice : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Gem');
      [*] = ;         Result := Result+resCount*(resourceGoldPrice+(resourceGemPrice*5) div 2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := _misc_RoundUp((Result*0.175)/5)*5;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetDefenderEnergy(defenderID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pDefender : Integer = ParserSelectByHandleByIndex(gPrototypeData.defenders.handle, defenderID);
      [*] = ;   var goldPrice : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'GoldCost');
      [*] = ;   var gemPrice : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'GemCost');
      [*] = ;   Result := (goldPrice+(gemPrice*5) div 2)*2+10;
      [*] = ;
      [*] = ;   var pResources : Integer = ParserSelectByHandleByKey(pDefender, 'Resources');
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pResources)-1 do
      [*] = ;   begin
      [*] = ;      var pResource : Integer = ParserSelectByHandleByIndex(pResources, i);
      [*] = ;      var resourceID : Integer = ParserGetIntValueByKeyByHandle(pResource, 'ResourceID');
      [*] = ;      if (resourceID<>0) then
      [*] = ;      begin
      [*] = ;         var pVarResourceID : Integer = ParserSelectByHandleByIndex(gPrototypeData.resources.handle, resourceID);
      [*] = ;         var resourceGoldPrice : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Gold');
      [*] = ;         var resourceGemPrice : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Gem');
      [*] = ;         Result := Result+(resourceGoldPrice+(resourceGemPrice*5) div 2) div 3;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := _misc_RoundUp((Result*0.3)/5)*5;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetResourceEnergy(resourceID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pVarResourceID : Integer = ParserSelectByHandleByIndex(gPrototypeData.resources.handle, resourceID);
      [*] = ;   var resourceRarity : Integer = ParserGetIntValueByKeyByHandle(pVarResourceID, 'Rarity');
      [*] = ;   Result := 10+resourceRarity*5;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = _gui_GetWindow('AstralBeforeBattle');
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;var headerText : String;
      [*] = ;var uid : Integer = gIntRegister_AstralSelectedShard;
      [*] = ;var shInd : Integer = _shard_GetShardByUID(uid);
      [*] = ;var ipProfile : Integer = gShards[shInd].ipPlayer;
      [*] = ;var shardName : String = GetLocaleTableListItemByID(gc_gui_LangTableIDMapProvinceInfo, gShards[shInd].namePrefix);
      [*] = ;shardName := shardName + GetLocaleTableListItemByID(gc_gui_LangTableIDMapProvinceInfo, gShards[shInd].nameSuffix);
      [*] = ;if (ipProfile<0) then
      [*] = ;   headerText := GetLocaleTableListItemByID('gui', '340')+' '+shardName
      [*] = ;else
      [*] = ;begin
      [*] = ;   gStringRegister_EnemyPlayerName := GetLocaleTableListItemByID('players', IntToStr(ipProfile));
      [*] = ;   headerText := GetLocaleTableListItemByID('gui', '440');
      [*] = ;   StringRegister0 := headerText;
      [*] = ;   MapExecuteState('StringReplaceParams');
      [*] = ;   headerText := StringRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;var fontHandle, fontHandle2, fontHandle3: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandle3); // HeaderM
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'AstralBeforeBattle', 'halParentMiddle', 'valParentMiddle', 0, 0, 978, 801, true);
      [*] = ;_gui_RootWindowAddExt(elmParentHandle,cRootWindowModal,0,cRootWindowAttrScaleByY,'');
      [*] = ;
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.65);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.75);
      [*] = ;//var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;if (elmHeaderHandle<>0) then
      [*] = ;begin
      [*] = ;   SetGUIElementMaterial(elmHeaderHandle, 'element.header.strip.629');
      [*] = ;   SetGUIElementAllPositionRect(elmHeaderHandle, 0, -53, 629, 90);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, headerText, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;// Body start
      [*] = ;const cEventState = 'EventBeforeBattleWindow';
      [*] = ;
      [*] = ;var elmHandle : Integer;
      [*] = ;// Лента, подпись, иконка бонуса, ползунки, иконка энергии, значение, ввод значения вручную.
      [*] = ;
      [*] = ;// Лента, воин в гарнизоне, кнопки с юнитом + стоимость в энергии
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.341', 'halParentMiddle', 'valParentTop', 0, 176-3, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHandle, 'shard_bonus|6', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;// Лента, предмет в сокровищнице, кнопки с предметом + стоимость в энергии
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.341', 'halParentMiddle', 'valParentTop', 0, 176+171-2, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHandle, 'shard_bonus|5', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;// Лента, постройка в замке, кнопки с постройкой + стоимость в энергии
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.341', 'halParentMiddle', 'valParentTop', 0, 176+171+127, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHandle, 'shard_bonus|7', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;// Лента, прочие преимущества (удешивить ресурс, договор со стражой, и т.п.), кнопки с бонусом + стоимость в энергии
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.341', 'halParentMiddle', 'valParentTop', 0, 176+171+127*2, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHandle, 'gui|341', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;var bParsersExists : Boolean = False;
      [*] = ;var pBonusUnits : Integer = _misc_ParserGetOrCreateByKey('pBonusUnits',false);
      [*] = ;if (ParserGetCountByHandle(pBonusUnits)<>0) then
      [*] = ;   bParsersExists := true;
      [*] = ;
      [*] = ;var pBonusItems : Integer = _misc_ParserGetOrCreateByKey('pBonusItems',false);
      [*] = ;if (not bParsersExists) and (ParserGetCountByHandle(pBonusItems)<>0) then
      [*] = ;   bParsersExists := True;
      [*] = ;
      [*] = ;var pBonusBuildings : Integer = _misc_ParserGetOrCreateByKey('pBonusBuildings',false);
      [*] = ;if  (not bParsersExists) and (ParserGetCountByHandle(pBonusBuildings)<>0) then
      [*] = ;   bParsersExists := True;
      [*] = ;
      [*] = ;var pBonusOthers : Integer = _misc_ParserGetOrCreateByKey('pBonusOthers',false);
      [*] = ;if  (not bParsersExists) and (ParserGetCountByHandle(pBonusOthers)<>0) then
      [*] = ;   bParsersExists := True;
      [*] = ;
      [*] = ;var plEnergy : Integer = gCampaign.arrCampPlayers[0].energy;
      [*] = ;var energySpent : Integer = 0;
      [*] = ;var goldReserve, gemReserve, goldIncome, gemIncome : Integer = 0;
      [*] = ;if (not bParsersExists) then
      [*] = ;begin
      [*] = ;   for shInd:=0 to gc_MaxShards-1 do
      [*] = ;   begin
      [*] = ;      var ipplayer : Integer = gShards[shInd].ipplayer;
      [*] = ;      if (ipplayer=0) then // 0 - captured by human
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to gc_MaxShardBonus-1 do
      [*] = ;         begin
      [*] = ;            var bonusID : Integer = gShards[shInd].arBonus[i][0];
      [*] = ;            var bonusValue : Integer = gShards[shInd].arBonus[i][1];
      [*] = ;
      [*] = ;            if (bonusID>0) then
      [*] = ;            begin
      [*] = ;               var bonusIcon : String = '';
      [*] = ;               case (bonusID) of
      [*] = ;                  1 : begin
      [*] = ;                     goldReserve := goldReserve+bonusValue;
      [*] = ;                  end;
      [*] = ;                  2 : begin
      [*] = ;                     gemReserve := gemReserve+bonusValue;
      [*] = ;                  end;
      [*] = ;                  3 : begin
      [*] = ;                     goldIncome := goldIncome+bonusValue;
      [*] = ;                  end;
      [*] = ;                  4 : begin
      [*] = ;                     gemIncome := gemIncome+bonusValue;
      [*] = ;                  end;
      [*] = ;                  5 : begin
      [*] = ;                     var itemID : Integer = bonusValue;
      [*] = ;                     var energyCost : Integer = GetItemEnergy(itemID);
      [*] = ;                     var pBonus : Integer = ParserAddChildByIndex(pBonusItems, '*');
      [*] = ;                     ParserSetValueByKeyByHandle(pBonus, 'Type', 'Item');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'BonusID', bonusID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'Value', itemID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'EnergyCost', energyCost);
      [*] = ;                  end;
      [*] = ;                  6 : begin
      [*] = ;                     var unitID : Integer = bonusValue;
      [*] = ;                     var energyCost : Integer = GetUnitEnergy(unitID);
      [*] = ;                     var pBonus : Integer = ParserAddChildByIndex(pBonusUnits, '*');
      [*] = ;                     ParserSetValueByKeyByHandle(pBonus, 'Type', 'Unit');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'BonusID', bonusID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'Value', unitID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'EnergyCost', energyCost);
      [*] = ;                  end;
      [*] = ;                  7 : begin
      [*] = ;                     var buildID : Integer = bonusValue;
      [*] = ;                     var energyCost : Integer = GetBuildEnergy(buildID);
      [*] = ;                     var pBonus : Integer = ParserAddChildByIndex(pBonusBuildings, '*');
      [*] = ;                     ParserSetValueByKeyByHandle(pBonus, 'Type', 'Build');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'BonusID', bonusID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'Value', buildID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'EnergyCost', energyCost);
      [*] = ;                  end;
      [*] = ;                  8 : begin
      [*] = ;                     var resID : Integer = bonusValue;
      [*] = ;                     var energyCost : Integer = GetResourceEnergy(resID);
      [*] = ;                     var pBonus : Integer = ParserAddChildByIndex(pBonusOthers, '*');
      [*] = ;                     ParserSetValueByKeyByHandle(pBonus, 'Type', 'Resource');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'BonusID', bonusID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'Value', resID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'EnergyCost', energyCost);
      [*] = ;                  end;
      [*] = ;                  9 : begin
      [*] = ;                     var defenderID : Integer = bonusValue;
      [*] = ;                     var energyCost : Integer = GetDefenderEnergy(defenderID);
      [*] = ;                     var pBonus : Integer = ParserAddChildByIndex(pBonusOthers, '*');
      [*] = ;                     ParserSetValueByKeyByHandle(pBonus, 'Type', 'Defender');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'BonusID', bonusID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'Value', defenderID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pBonus, 'EnergyCost', energyCost);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               //elmHandle := _gui_CreateImage('', elmParentHandle, bonusIcon, 'halRight', 'valBottomHeight', -311+(i*56+i*4), -209, 56, 56, 0);
      [*] = ;               //elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'unitpanel.button.cover', 'halRight', 'valBottomHeight', -313+(i*cIconSize+i*4), -264, cIconSize+3, cIconSize+3, '', '', shardBuildingID);
      [*] = ;               //SetGUIElementHint(elmHandle, bonusHint);
      [*] = ;               //SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SortParserByValueOrder(pBonusUnits);
      [*] = ;   SortParserByValueOrder(pBonusItems);
      [*] = ;   SortParserByValueOrder(pBonusBuildings);
      [*] = ;   SortParserByValueOrder(pBonusOthers);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   for shInd:=0 to gc_MaxShards-1 do
      [*] = ;   begin
      [*] = ;      var ipplayer : Integer = gShards[shInd].ipplayer;
      [*] = ;      if (ipplayer=0) then // 0 - captured by human
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to gc_MaxShardBonus-1 do
      [*] = ;         begin
      [*] = ;            var bonusID : Integer = gShards[shInd].arBonus[i][0];
      [*] = ;            var bonusValue : Integer = gShards[shInd].arBonus[i][1];
      [*] = ;
      [*] = ;            if (bonusID>0) then
      [*] = ;            begin
      [*] = ;               var bonusIcon : String = '';
      [*] = ;               case (bonusID) of
      [*] = ;                  1 : begin
      [*] = ;                     goldReserve := goldReserve+bonusValue;
      [*] = ;                  end;
      [*] = ;                  2 : begin
      [*] = ;                     gemReserve := gemReserve+bonusValue;
      [*] = ;                  end;
      [*] = ;                  3 : begin
      [*] = ;                     goldIncome := goldIncome+bonusValue;
      [*] = ;                  end;
      [*] = ;                  4 : begin
      [*] = ;                     gemIncome := gemIncome+bonusValue;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;for i:=0 to 3 do
      [*] = ;begin
      [*] = ;   var posX : Integer = -352;
      [*] = ;   var posY : Integer = 43;
      [*] = ;   var xOff : Integer = 235;
      [*] = ;   var addX, addY, tag, maxValue : Integer;
      [*] = ;   var text, icon, addicon, sliderID, sliderHint : String;
      [*] = ;   case i of
      [*] = ;      0 : begin // Запас золота
      [*] = ;         text := 'shard_bonus|1';
      [*] = ;         icon := 'astral.gold.icon.46x50';
      [*] = ;         addicon := 'astral.beforebattle.goldstartamount.sign';
      [*] = ;         addX := -21;
      [*] = ;         addY := 15;
      [*] = ;         sliderID := 'goldstartamount';
      [*] = ;         maxValue := goldReserve;
      [*] = ;      end;
      [*] = ;      1 : begin // Запас кристаллов
      [*] = ;         text := 'shard_bonus|2';
      [*] = ;         icon := 'astral.gem.icon.47x50';
      [*] = ;         addicon := 'astral.beforebattle.gemstartamount.sign';
      [*] = ;         addX := -21;
      [*] = ;         addY := 15;
      [*] = ;         sliderID := 'gemstartamount';
      [*] = ;         maxValue := gemReserve;
      [*] = ;      end;
      [*] = ;      2 : begin // Доход золота
      [*] = ;         text := 'shard_bonus|3';
      [*] = ;         //icon := 'icon.shardbonus.2';
      [*] = ;         icon := 'astral.gold.icon.46x50';
      [*] = ;         addicon := 'astral.beforebattle.incomeplus.sign';
      [*] = ;         addX := -16;
      [*] = ;         addY := 15;
      [*] = ;         sliderID := 'goldincome';
      [*] = ;         maxValue := goldIncome;
      [*] = ;      end;
      [*] = ;      3 : begin // Доход кристаллов
      [*] = ;         text := 'shard_bonus|4';
      [*] = ;         //icon := 'icon.shardbonus.3';
      [*] = ;         icon := 'astral.gem.icon.47x50';
      [*] = ;         addicon := 'astral.beforebattle.incomeplus.sign';
      [*] = ;         addX := -20;
      [*] = ;         addY := 14;
      [*] = ;         sliderID := 'gemincome';
      [*] = ;         maxValue := gemIncome;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   posX := posX+i*xOff;
      [*] = ;
      [*] = ;   arrChosenBonuses[i][0] := i+1; // BonusID
      [*] = ;   var value : Integer = arrChosenBonuses[i][1];
      [*] = ;      
      [*] = ;   var valueText : String = IntToStr(value);
      [*] = ;   if (value > 0) then
      [*] = ;   valueText := '+'+valueText;
      [*] = ;
      [*] = ;   var elmSliderHandle : Integer = _gui_CreateSlider(sliderID, (arrChosenBonuses[i][1]/maxValue), valueText, elmParentHandle, 'halParentMiddle', 'valParentTop', posX+368, 75, cEventState, sliderHint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementTag(elmSliderHandle, maxValue);
      [*] = ;
      [*] = ;   elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentMiddle', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;   elmTextHandle := _gui_CreateText('', elmHandle, text, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   var elmHandle1 : Integer = _gui_CreateImage('', elmParentHandle, icon, 'halParentMiddle', 'valParentTop', posX-91-1, posY+35+34+2, 0, 0, 0);
      [*] = ;   var elmHandle2 : Integer = _gui_CreateImage('', elmParentHandle, addicon, 'halParentMiddle', 'valParentTop', posX-91+addX-1, posY+34+35+addY+2, 0, 0, 0);
      [*] = ;
      [*] = ;   elmHandle := _gui_CreateImage('astral_infopanel_energy_icon', elmParentHandle, 'astral.energy.33x32', 'halParentMiddle', 'valParentTop', posX-39-14-1, posY+79+4, 32, 33, 0);
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;
      [*] = ;   var pProtBonus : Integer = ParserSelectByHandleByIndex(gPrototypeData.shardBonuses.handle, i+1);
      [*] = ;   if (pProtBonus<>0) then
      [*] = ;   begin
      [*] = ;      var energyCost : Integer = _misc_RoundUp(ParserGetFloatValueByKeyByHandle(pProtBonus, 'Price')*value);
      [*] = ;      elmTextHandle := _gui_CreateText('energyCost', elmSliderHandle, IntToStr(energyCost), 'halParentMiddle', 'valParentTop', -29+12, posY-75+90, 40, 21, 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      energySpent := energySpent+energyCost;
      [*] = ;      //if (value=0) then
      [*] = ;      //   SetGUIElementVisible(elmTextHandle, False);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (maxValue=0) then
      [*] = ;   begin
      [*] = ;      var elmSliderBtnHandle : Integer = GetGUIElementIndexByNameParent('btnSlider', elmSliderHandle);
      [*] = ;      //SetGUIElementVisible(elmSliderBtnHandle, False);
      [*] = ;      SetGUIElementEnabled(elmSliderBtnHandle, False);
      [*] = ;      var elmSliderLineHandle : Integer = GetGUIElementIndexByNameParent('lineSlider', elmSliderHandle);
      [*] = ;      //SetGUIElementVisible(elmSliderLineHandle, False);
      [*] = ;      SetGUIElementEnabled(elmSliderLineHandle, False);
      [*] = ;      SetGUIElementUserBlend(elmSliderBtnHandle, 0.75);
      [*] = ;      SetGUIElementUserBlend(elmHandle1, 0.25);
      [*] = ;      SetGUIElementUserBlend(elmHandle2, 0.25);
      [*] = ;      SetGUIElementUserBlend(elmHandle, 0.25);
      [*] = ;      //var elmSliderTextHandle : Integer = GetGUIElementIndexByNameParent('textSlider', elmSliderHandle);
      [*] = ;      //SetGUIElementVisible(elmSliderTextHandle, False);
      [*] = ;      var elmSliderTextHandle : Integer = GetGUIElementIndexByNameParent('energyCost', elmSliderHandle);
      [*] = ;      SetGUIElementVisible(elmSliderTextHandle, False);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;const cBtnUnitsScrollLeft = 200;
      [*] = ;const cBtnUnitsScrollRight = 201;
      [*] = ;const cBtnItemsScrollLeft = 202;
      [*] = ;const cBtnItemsScrollRight = 203;
      [*] = ;const cBtnBuildingsScrollLeft = 204;
      [*] = ;const cBtnBuildingsScrollRight = 205;
      [*] = ;const cBtnOthersScrollLeft = 206;
      [*] = ;const cBtnOthersScrollRight = 207;
      [*] = ;
      [*] = ;const cBtnUnitsBonusBaseTag = 1000;
      [*] = ;const cBtnItemsBonusBaseTag = 2000;
      [*] = ;const cBtnBuildingsBonusBaseTag = 3000;
      [*] = ;const cBtnOthersBonusBaseTag = 4000;
      [*] = ;
      [*] = ;var scrollPosUnits, scrollPosItems, scrollPosBuildings, scrollPosOthers : Integer = 0;
      [*] = ;var pScrollPosTmp : Integer = _misc_ParserGetOrCreateByKey('pScrollPosTmp',false);
      [*] = ;if (ParserGetCountByHandle(pScrollPosTmp)=0) then
      [*] = ;begin
      [*] = ;   ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits', scrollPosUnits);
      [*] = ;   ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems', scrollPosItems);
      [*] = ;   ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosBuildings', scrollPosBuildings);
      [*] = ;   ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosOthers', scrollPosOthers);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   scrollPosUnits := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits');
      [*] = ;   scrollPosItems := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems');
      [*] = ;   scrollPosBuildings := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosBuildings');
      [*] = ;   scrollPosOthers := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosOthers');
      [*] = ;end;
      [*] = ;
      [*] = ;var curScrollPos : Integer = scrollPosUnits;
      [*] = ;var maxScrollCount : Integer = 11;
      [*] = ;var count : Integer = ParserGetCountByHandle(pBonusUnits);
      [*] = ;var startInd : Integer = curScrollPos;
      [*] = ;var endInd : Integer = maxScrollCount+curScrollPos;
      [*] = ;var visualIndex : Integer;
      [*] = ;var elmBtnArrowLeftHandle : Integer = _gui_CreateButton('arrowLeft', elmParentHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', 5, 239, 0, 0, cEventState, '', cBtnUnitsScrollLeft);
      [*] = ;if (curScrollPos<=0) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.4);
      [*] = ;   SetGUIElementEnabled(elmBtnArrowLeftHandle, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.8);
      [*] = ;end;
      [*] = ;var elmBtnArrowRightHandle : Integer = _gui_CreateButton('arrowRight', elmParentHandle, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', 933, 239, 0, 0, cEventState, '', cBtnUnitsScrollRight);
      [*] = ;if ((count-curScrollPos)<=maxScrollCount) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.4);
      [*] = ;   SetGUIElementEnabled(elmBtnArrowRightHandle, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.8);
      [*] = ;end;
      [*] = ;var elmBonusParentHandle : Integer = _gui_CreateImage('', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 432, 217, 0, 0, 0);
      [*] = ;for i:=0 to count-1 do
      [*] = ;begin
      [*] = ;   if (visualIndex<maxScrollCount) then
      [*] = ;   begin
      [*] = ;      if (i>=startInd) and (i<endInd) then
      [*] = ;      begin
      [*] = ;         var cSize : Integer = 74;
      [*] = ;         var tmpCount : Integer;
      [*] = ;         if (count>maxScrollCount) then
      [*] = ;            tmpCount := maxScrollCount
      [*] = ;         else
      [*] = ;            tmpCount := count;
      [*] = ;         var posX : Integer = 61-(tmpCount*(cSize div 2));
      [*] = ;
      [*] = ;         var pBonus : Integer = ParserSelectByHandleByIndex(pBonusUnits, i);
      [*] = ;         var bonusType : String = ParserGetValueByKeyByHandle(pBonus, 'Type');
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'Value');
      [*] = ;         var energyCost : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'EnergyCost');
      [*] = ;         var bChecked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;         if (bChecked) then
      [*] = ;         energySpent := energySpent+energyCost;
      [*] = ;
      [*] = ;         var tag : Integer = cBtnUnitsBonusBaseTag+i;
      [*] = ;         var unitID : Integer = value;
      [*] = ;         var hint : String;
      [*] = ;         var elmBonusHandle : Integer = _gui_CreateImage('', elmBonusParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX+visualIndex*cSize, 1, 0, 0, 0);
      [*] = ;         if (bChecked) then
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'heropanel.unit.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'astral.bonus.unit.frame', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'icon.unit.'+IntToStr(unitID), 'halParentLeft', 'valParentTop', 0, 0, 70, 93, 0);
      [*] = ;         var elmBtnHandle : Integer = _gui_CreateButton('bonusunit', elmBonusHandle, '', 'heropanel.unit.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 70, 93, '', '', tag);
      [*] = ;         _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipUnit',cFT_UnitTemplate,unitID,0,0,cEventState,'2');
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'astral.bonus.unit.energycost.cover', 'halParentLeft', 'valParentTop', -4, 95, 0, 0, 0);
      [*] = ;         if (bChecked) then
      [*] = ;         SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;         elmHandle := _gui_CreateImage('astral_infopanel_energy_icon', elmBonusHandle, 'astral.energy.27x27', 'halParentLeft', 'valParentTop', 3, 95, 0, 0, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.5);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         var cR, cG, cB : Float;
      [*] = ;         if (bChecked) then
      [*] = ;         begin
      [*] = ;            cR := gc_gui_fontcolor_NormalWhiteR;
      [*] = ;            cG := gc_gui_fontcolor_NormalWhiteG;
      [*] = ;            cB := gc_gui_fontcolor_NormalWhiteB;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            cR := gc_gui_fontcolor_NormalR;
      [*] = ;            cG := gc_gui_fontcolor_NormalG;
      [*] = ;            cB := gc_gui_fontcolor_NormalB;
      [*] = ;         end;
      [*] = ;         elmTextHandle := _gui_CreateText('', elmBonusHandle, IntToStr(energyCost), 'halParentLeft', 'valParentTop', 26, 99, 36, 21, 'halMiddle', 'valMiddle', fontHandle2, cR, cG, cB, 1);
      [*] = ;         if (not bChecked) then
      [*] = ;            SetGUIElementUserBlend(elmTextHandle, 0.6);
      [*] = ;         visualIndex := visualIndex+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;curScrollPos := scrollPosItems;
      [*] = ;maxScrollCount := 15;
      [*] = ;count := ParserGetCountByHandle(pBonusItems);
      [*] = ;startInd := curScrollPos;
      [*] = ;endInd := maxScrollCount+curScrollPos;
      [*] = ;elmBtnArrowLeftHandle := _gui_CreateButton('arrowLeft', elmParentHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', 5, 239+149+7, 0, 0, cEventState, '', cBtnItemsScrollLeft);
      [*] = ;if (curScrollPos<=0) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.4);
      [*] = ;   SetGUIElementEnabled(elmBtnArrowLeftHandle, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.8);
      [*] = ;end;
      [*] = ;elmBtnArrowRightHandle := _gui_CreateButton('arrowRight', elmParentHandle, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', 933, 239+149+7, 0, 0, cEventState, '', cBtnItemsScrollRight);
      [*] = ;if ((count-curScrollPos)<=maxScrollCount) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.4);
      [*] = ;   SetGUIElementEnabled(elmBtnArrowRightHandle, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.8);
      [*] = ;end;
      [*] = ;elmBonusParentHandle := _gui_CreateImage('', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 432+59, 217+149+23, 0, 0, 0);
      [*] = ;visualIndex := 0;
      [*] = ;for i:=0 to count-1 do
      [*] = ;begin
      [*] = ;   if (visualIndex<maxScrollCount) then
      [*] = ;   begin
      [*] = ;      if (i>=startInd) and (i<endInd) then
      [*] = ;      begin
      [*] = ;         var cSize : Integer = 56;
      [*] = ;         var tmpCount : Integer;
      [*] = ;         if (count>maxScrollCount) then
      [*] = ;            tmpCount := maxScrollCount
      [*] = ;         else
      [*] = ;            tmpCount := count;
      [*] = ;         var posX : Integer = -(tmpCount*(cSize div 2));
      [*] = ;
      [*] = ;         var pBonus : Integer = ParserSelectByHandleByIndex(pBonusItems, i);
      [*] = ;         var bonusType : String = ParserGetValueByKeyByHandle(pBonus, 'Type');
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'Value');
      [*] = ;         var energyCost : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'EnergyCost');
      [*] = ;         var bChecked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;         if (bChecked) then
      [*] = ;            energySpent := energySpent+energyCost;
      [*] = ;
      [*] = ;         var tag : Integer = cBtnItemsBonusBaseTag+i;
      [*] = ;         var itemID : Integer = value;
      [*] = ;         var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.items.handle, itemID);
      [*] = ;         var maxDurability : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;         //var hint : String = 'itemhint%|'+IntToStr(itemID)+'|'+IntToStr(0)+'|'+IntToStr(maxDurability);
      [*] = ;         var elmBonusHandle : Integer = _gui_CreateImage('', elmBonusParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX+visualIndex*cSize, 1, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'icon.item.'+IntToStr(itemID), 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;         if (bChecked) then
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmBonusHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;         end;
      [*] = ;         var elmBtnHandle : Integer = _gui_CreateButton('bonusitem', elmBonusHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', '', tag);
      [*] = ;         _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceHide,maxDurability,cFT_ItemHeroDefault,cEventState,'2');
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'astral.bonus.item.energycost.cover', 'halParentLeft', 'valParentTop', -4, 55, 0, 0, 0);
      [*] = ;         if (bChecked) then
      [*] = ;            SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;         elmHandle := _gui_CreateImage('astral_infopanel_energy_icon', elmBonusHandle, 'astral.energy.27x27', 'halParentLeft', 'valParentTop', 0, 55, 0, 0, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.5);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         var cR, cG, cB : Float;
      [*] = ;         if (bChecked) then
      [*] = ;         begin
      [*] = ;            cR := gc_gui_fontcolor_NormalWhiteR;
      [*] = ;            cG := gc_gui_fontcolor_NormalWhiteG;
      [*] = ;            cB := gc_gui_fontcolor_NormalWhiteB;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            cR := gc_gui_fontcolor_NormalR;
      [*] = ;            cG := gc_gui_fontcolor_NormalG;
      [*] = ;            cB := gc_gui_fontcolor_NormalB;
      [*] = ;         end;
      [*] = ;         elmTextHandle := _gui_CreateText('', elmBonusHandle, IntToStr(energyCost), 'halParentLeft', 'valParentTop', 26, 104-44, 25, 21, 'halMiddle', 'valMiddle', fontHandle2, cR, cG, cB, 1);
      [*] = ;         if (not bChecked) then
      [*] = ;            SetGUIElementUserBlend(elmTextHandle, 0.6);
      [*] = ;         visualIndex := visualIndex+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;curScrollPos := scrollPosBuildings;
      [*] = ;maxScrollCount := 15;
      [*] = ;count := ParserGetCountByHandle(pBonusBuildings);
      [*] = ;startInd := curScrollPos;
      [*] = ;endInd := maxScrollCount+curScrollPos;
      [*] = ;elmBtnArrowLeftHandle := _gui_CreateButton('arrowLeft', elmParentHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', 5, 239+149+7+126, 0, 0, cEventState, '', cBtnBuildingsScrollLeft);
      [*] = ;if (curScrollPos<=0) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.4);
      [*] = ;   SetGUIElementEnabled(elmBtnArrowLeftHandle, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.8);
      [*] = ;end;
      [*] = ;elmBtnArrowRightHandle := _gui_CreateButton('arrowRight', elmParentHandle, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', 933, 239+149+7+126, 0, 0, cEventState, '', cBtnBuildingsScrollRight);
      [*] = ;if ((count-curScrollPos)<=maxScrollCount) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.4);
      [*] = ;   SetGUIElementEnabled(elmBtnArrowRightHandle, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.8);
      [*] = ;end;
      [*] = ;elmBonusParentHandle := _gui_CreateImage('', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 432+59, 217+149+23+126, 0, 0, 0);
      [*] = ;visualIndex := 0;
      [*] = ;for i:=0 to count-1 do
      [*] = ;begin
      [*] = ;   if (visualIndex<maxScrollCount) then
      [*] = ;   begin
      [*] = ;      if (i>=startInd) and (i<endInd) then
      [*] = ;      begin
      [*] = ;         var cSize : Integer = 56;
      [*] = ;         var tmpCount : Integer;
      [*] = ;         if (count>maxScrollCount) then
      [*] = ;            tmpCount := maxScrollCount
      [*] = ;         else
      [*] = ;            tmpCount := count;
      [*] = ;         var posX : Integer = -(tmpCount*(cSize div 2));
      [*] = ;
      [*] = ;         var pBonus : Integer = ParserSelectByHandleByIndex(pBonusBuildings, i);
      [*] = ;         var bonusType : String = ParserGetValueByKeyByHandle(pBonus, 'Type');
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'Value');
      [*] = ;         var energyCost : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'EnergyCost');
      [*] = ;         var bChecked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;         if (bChecked) then
      [*] = ;            energySpent := energySpent+energyCost;
      [*] = ;
      [*] = ;         var tag : Integer = cBtnBuildingsBonusBaseTag+i;
      [*] = ;         var BuildingID : Integer = value;
      [*] = ;         var hint : String = '';
      [*] = ;         //var hint : String = 'inner_build|'+IntToStr(BuildingID);
      [*] = ;         IntRegister0 := BuildingID;
      [*] = ;         MapExecuteState('GetInnerBuildParserByID');
      [*] = ;         var pInnerBuilding : Integer = IntRegister1;
      [*] = ;         var buildIcon : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'Icon');
      [*] = ;
      [*] = ;         var elmBonusHandle : Integer = _gui_CreateImage('', elmBonusParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX+visualIndex*cSize, 1, 0, 0, BuildingID);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'icon.building.'+IntToStr(buildIcon), 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 0);
      [*] = ;         if (bChecked) then
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmBonusHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;         end;
      [*] = ;         var elmBtnHandle : Integer = _gui_CreateButton('bonusbuilding', elmBonusHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, cEventState, '', tag);
      [*] = ;         _gui_ft_AttachHint_I2(elmBtnHandle,'VVK.FTooltipInnerBuilding',cFT_IBShardAttack,buildingID);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'astral.bonus.item.energycost.cover', 'halParentLeft', 'valParentTop', -4, 55, 0, 0, 0);
      [*] = ;         if (bChecked) then
      [*] = ;            SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;         elmHandle := _gui_CreateImage('astral_infopanel_energy_icon', elmBonusHandle, 'astral.energy.27x27', 'halParentLeft', 'valParentTop', 0, 55, 0, 0, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.5);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         var cR, cG, cB : Float;
      [*] = ;         if (bChecked) then
      [*] = ;         begin
      [*] = ;            cR := gc_gui_fontcolor_NormalWhiteR;
      [*] = ;            cG := gc_gui_fontcolor_NormalWhiteG;
      [*] = ;            cB := gc_gui_fontcolor_NormalWhiteB;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            cR := gc_gui_fontcolor_NormalR;
      [*] = ;            cG := gc_gui_fontcolor_NormalG;
      [*] = ;            cB := gc_gui_fontcolor_NormalB;
      [*] = ;         end;
      [*] = ;         elmTextHandle := _gui_CreateText('', elmBonusHandle, IntToStr(energyCost), 'halParentLeft', 'valParentTop', 26, 104-44, 25, 21, 'halMiddle', 'valMiddle', fontHandle2, cR, cG, cB, 1);
      [*] = ;         if (not bChecked) then
      [*] = ;            SetGUIElementUserBlend(elmTextHandle, 0.6);
      [*] = ;         visualIndex := visualIndex+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;gIntRegister_AstralEnergySpend := energySpent;
      [*] = ;
      [*] = ;curScrollPos := scrollPosOthers;
      [*] = ;maxScrollCount := 15;
      [*] = ;count := ParserGetCountByHandle(pBonusOthers);
      [*] = ;startInd := curScrollPos;
      [*] = ;endInd := maxScrollCount+curScrollPos;
      [*] = ;elmBtnArrowLeftHandle := _gui_CreateButton('arrowLeft', elmParentHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', 5, 239+149+7+126*2, 0, 0, cEventState, '', cBtnOthersScrollLeft);
      [*] = ;if (curScrollPos<=0) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.4);
      [*] = ;   SetGUIElementEnabled(elmBtnArrowLeftHandle, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.8);
      [*] = ;end;
      [*] = ;elmBtnArrowRightHandle := _gui_CreateButton('arrowRight', elmParentHandle, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', 933, 239+149+7+126*2, 0, 0, cEventState, '', cBtnOthersScrollRight);
      [*] = ;if ((count-curScrollPos)<=maxScrollCount) then
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.4);
      [*] = ;   SetGUIElementEnabled(elmBtnArrowRightHandle, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.8);
      [*] = ;end;
      [*] = ;elmBonusParentHandle := _gui_CreateImage('', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 432+59, 217+149+23+126*2, 0, 0, 0);
      [*] = ;visualIndex := 0;
      [*] = ;for i:=0 to count-1 do
      [*] = ;begin
      [*] = ;   if (visualIndex<maxScrollCount) then
      [*] = ;   begin
      [*] = ;      if (i>=startInd) and (i<endInd) then
      [*] = ;      begin
      [*] = ;         var cSize : Integer = 56;
      [*] = ;         var tmpCount : Integer;
      [*] = ;         if (count>maxScrollCount) then
      [*] = ;            tmpCount := maxScrollCount
      [*] = ;         else
      [*] = ;            tmpCount := count;
      [*] = ;         var posX : Integer = -(tmpCount*(cSize div 2));
      [*] = ;
      [*] = ;         var pBonus : Integer = ParserSelectByHandleByIndex(pBonusOthers, i);
      [*] = ;         var bonusType : String = ParserGetValueByKeyByHandle(pBonus, 'Type');
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'Value');
      [*] = ;         var energyCost : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'EnergyCost');
      [*] = ;         var bChecked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;         if (bChecked) then
      [*] = ;            energySpent := energySpent+energyCost;
      [*] = ;
      [*] = ;         var icon, hint, elmName : String = '';
      [*] = ;         case bonusType of
      [*] = ;            'Resource' : begin
      [*] = ;               icon := 'map.resource.'+IntToStr(value);
      [*] = ;               hint := GetLocaleTableListItemByID('shard_bonus', '8')+' (10%): '+gc_gui_BreakLine+GetLocaleTableListItemByID('resource', IntToStr(value))+'';
      [*] = ;               elmName := 'bonusother';
      [*] = ;            end;
      [*] = ;            'Defender' : begin
      [*] = ;               icon := 'icon.defender.'+IntToStr(value);
      [*] = ;               _gui_ft_CreateHint_I4_S2(hint,'VVK.FTooltipDefender',value,cFT_DefenderTypeTemplate,1,1,cEventState,'');
      [*] = ;               elmName := '';
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         var tag : Integer = cBtnOthersBonusBaseTag+i;
      [*] = ;
      [*] = ;         var elmBonusHandle : Integer = _gui_CreateImage('', elmBonusParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX+visualIndex*cSize, 1, 0, 0, value);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', -5, -5, 0, 0, 0);
      [*] = ;         elmHandle := _gui_CreateImage('', elmBonusHandle, icon, 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 0);
      [*] = ;         if (bChecked) then
      [*] = ;         begin
      [*] = ;            elmHandle := _gui_CreateImage('', elmBonusHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;         end;
      [*] = ;         var elmBtnHandle : Integer = _gui_CreateButton(elmName, elmBonusHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', hint, tag);
      [*] = ;         if elmName <> '' then SetGUIElementPressState(elmBtnHandle,cEventState);
      [*] = ;            elmHandle := _gui_CreateImage('', elmBonusHandle, 'astral.bonus.item.energycost.cover', 'halParentLeft', 'valParentTop', -4, 55, 0, 0, 0);
      [*] = ;         if (bChecked) then
      [*] = ;            SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;         elmHandle := _gui_CreateImage('astral_infopanel_energy_icon', elmBonusHandle, 'astral.energy.27x27', 'halParentLeft', 'valParentTop', 0, 55, 0, 0, 0);
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.5);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;         var cR, cG, cB : Float;
      [*] = ;         if (bChecked) then
      [*] = ;         begin
      [*] = ;            cR := gc_gui_fontcolor_NormalWhiteR;
      [*] = ;            cG := gc_gui_fontcolor_NormalWhiteG;
      [*] = ;            cB := gc_gui_fontcolor_NormalWhiteB;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            cR := gc_gui_fontcolor_NormalR;
      [*] = ;            cG := gc_gui_fontcolor_NormalG;
      [*] = ;            cB := gc_gui_fontcolor_NormalB;
      [*] = ;         end;
      [*] = ;         elmTextHandle := _gui_CreateText('', elmBonusHandle, IntToStr(energyCost), 'halParentLeft', 'valParentTop', 26, 104-44, 25, 21, 'halMiddle', 'valMiddle', fontHandle2, cR, cG, cB, 1);
      [*] = ;         if (not bChecked) then
      [*] = ;            SetGUIElementUserBlend(elmTextHandle, 0.6);
      [*] = ;         visualIndex := visualIndex+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// Запас энергии
      [*] = ;elmHandle := _gui_CreateImage('astral_infopanel_energy_icon', elmParentHandle, 'astral.energy.33x32', 'halParentMiddle', 'valParentTop', -354+2+25, 767-3, 32, 33, 0);
      [*] = ;SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'astral.beforebattle.curenergy.sign', 'halParentMiddle', 'valParentTop', -354, 768, 0, 0, 0);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentMiddle', 'valParentTop', -290, 729, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHandle, 'gui|342', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHandle, IntToStr(plEnergy), 'halParentLeft', 'valParentTop', 26+63, 104-44-19-2, 52, 26, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;// Затраты энергии
      [*] = ;elmHandle := _gui_CreateImage('astral_infopanel_energy_icon', elmParentHandle, 'astral.energy.33x32', 'halParentMiddle', 'valParentTop', -358+580+10+25, 767-3, 32, 33, 0);
      [*] = ;SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'astral.beforebattle.spentenergy.sign', 'halParentMiddle', 'valParentTop', -358+580+10, 767, 0, 0, 0);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'astral.beforebattle.spentenergy.sign', 'halParentMiddle', 'valParentTop', -358+580+10, 767, 0, 0, 0);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentMiddle', 'valParentTop', -290+580, 729, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHandle, 'gui|343', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;if (energySpent>plEnergy) then
      [*] = ;   elmTextHandle := _gui_CreateText('', elmHandle, IntToStr(energySpent), 'halParentLeft', 'valParentTop', 26+63+2, 104-44-19-2, 52, 26, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_RedR, gc_gui_fontcolor_RedG, gc_gui_fontcolor_RedB, 1)
      [*] = ;else
      [*] = ;   elmTextHandle := _gui_CreateText('', elmHandle, IntToStr(energySpent), 'halParentLeft', 'valParentTop', 26+63+2, 104-44-19-2, 52, 26, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;// Кнопки
      [*] = ;const cBtnStartBattleTag = 100;
      [*] = ;const cBtnCancelTag = 101;
      [*] = ;const cBtnAstralHeroTag = 102;
      [*] = ;elmHandle := _gui_CreateImage('start_battle_frame', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', -57, -32, 0, 0, 0);
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('start_battle', elmHandle, '', 'astral.beforebattle.btn.startbattle', 'halParentLeft', 'valParentTop', 39+2, 2, 0, 0, cEventState, 'gui|200', cBtnStartBattleTag);
      [*] = ;var enabled : Boolean = true;
      [*] = ;if (energySpent>plEnergy) then
      [*] = ;begin
      [*] = ;   SetGUIElementHint(elmBtnHandle, 'gui|673');
      [*] = ;   enabled := false;
      [*] = ;end;
      [*] = ;enabled := enabled and gBoolRegister_BtnAttackShardEnabled;
      [*] = ;SetGUIElementEnabled(elmBtnHandle, enabled);
      [*] = ;
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 57, -32, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'gui|135', cBtnCancelTag);
      [*] = ;
      [*] = ;// astral hero
      [*] = ;elmBtnHandle := _gui_CreateButton('astral_hero', elmParentHandle, '', 'map.mainpanel.btn.nexthero', 'halParentMiddle', 'valParentBottom', 0, -72, 0, 0, cEventState, '', cBtnAstralHeroTag);
      [*] = ;if gCampMapHero.units_no = 0 then
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;else
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, true);
      [*] = ;
      [*] = ;if gCampMapHero.units_no = 0 then
      [*] = ;   headerText := 'gui|astral_no_map_hero_available_tooltip'
      [*] = ;else
      [*] = ;   headerText := GetLocaleTableListItemByID('tutorial','70') +' '+ GetLocaleTableListItemByID('menu','201');
      [*] = ;
      [*] = ;SetGUIAllowEvents(elmBtnHandle, True, False, False);
      [*] = ;SetGUIElementHint(elmBtnHandle, headerText);
      [*] = ;
      [*] = ;// Body finish
      [*] = ;
      [*] = ;GUIExecuteState('DoFadeOutInfoPanel');
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;_gui_RootWindowAddM(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

