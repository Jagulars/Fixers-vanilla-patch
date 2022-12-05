section.begin
   Name = map.CreateInfoPanel
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CREATEINFOPANEL';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;const cButtonsPanel = $1e;
      [*] = ;const cButtonsDX = $1d;
      [*] = ;const cInfopanelBackground = $1c;
      [*] = ;const cLastButton = $7;
      [*] = ;const cFirstButton = $4;
      [*] = ;
      [*] = ;var dummyUID,dummyHandle,fog,if_handle,bkg_dy,prevUID : Integer;
      [*] = ;var isPlayable : Boolean = False;
      [*] = ;var elmHandle : Integer = _gui_GetWindow('map_infopanel');
      [*] = ;var hudHeroCollection : Integer = GetGUIElementTopIndexByName('hudhero');
      [*] = ;var elem_d : TInterfaceElementData;
      [*] = ;var tmp_pos : TRectangle;
      [*] = ;var fontHandleT, fontHandleH2, fontHandleN: String;
      [*] = ;var ProvinceTypeID : String;
      [*] = ;
      [*] = ;var curHex : Integer = gIntRegister_MapSelectedHex; //Эксперимент, обновлять инфопанель при наведении на провинцию
      [*] = ;//var curHex : Integer = gIntRegister_MapUnderCursorHex; //Эксперимент, обновлять инфопанель при наведении на провинцию
      [*] = ;
      [*] = ;if elmHandle <> 0 then
      [*] = ;   prevUID := GetGUIElementTag(elmHandle)
      [*] = ;else
      [*] = ;   prevUID := 0;
      [*] = ;if curHex <> 0 then
      [*] = ;begin
      [*] = ;   fog := ParserGetIntValueByIndexByHandle(ParserSelectByHandleByKey(curHex, 'Fog'),gIntRegister_MapMyPlayerIndex);
      [*] = ;   dummyUID := ParserGetIntValueByKeyByHandle(curHex, 'DummyUID');
      [*] = ;   dummyHandle := GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;   if dummyHandle <> 0 then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'IsPlayable');
      [*] = ;      isPlayable := BoolRegister0;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   dummyUID := 0;
      [*] = ;   dummyHandle := 0;
      [*] = ;   fog := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;//_log_values('P|C',prevUID,dummyUID,0,0,0,0);
      [*] = ;if prevUID = dummyUID then
      [*] = ;begin
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;const cHeroRadSize = 110; //54
      [*] = ;SetGUIElementAlign(hudHeroCollection, 'halLeft', 'valTop');
      [*] = ;SetGUIElementAllPositionRect(hudHeroCollection, 0, 0, GetViewerWidth(), GetViewerHeight());
      [*] = ;GUIGroupHUDRestrictLinesClear(hudHeroCollection);
      [*] = ;SetGUIGroupHUDRestrictLinesAddTop(hudHeroCollection, 0, GetViewerWidth, 36+cHeroRadSize);
      [*] = ;SetGUIGroupHUDRestrictLinesAddBottom(hudHeroCollection, 0, GetViewerWidth, GetViewerHeight-100-cHeroRadSize);
      [*] = ;SetGUIGroupHUDRestrictLinesAddLeft(hudHeroCollection, 0, GetViewerHeight, 36+cHeroRadSize);
      [*] = ;SetGUIGroupHUDRestrictLinesAddRight(hudHeroCollection, 0, GetViewerHeight, GetViewerWidth-36-cHeroRadSize);
      [*] = ;
      [*] = ;_gui_RootWindowRemoveWithFade(elmHandle,0);
      [*] = ;if (curHex=0) or ((fog > 1) and gGame.fog) or (not isPlayable) then
      [*] = ;begin
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[UID:'+IntToStr(dummyUID)+']',_log_trace);
      [*] = ;SetGUIGroupHUDRestrictLinesAddTop(hudHeroCollection, 0, GetViewerWidth(), 36+cHeroRadSize);
      [*] = ;SetGUIGroupHUDRestrictLinesAddRight(hudHeroCollection, GetViewerHeight(), GetViewerHeight()-530, GetViewerWidth()-362-cHeroRadSize);
      [*] = ;
      [*] = ;if_handle := _gui_GetInterfaceWindowHandle('map_infopanel');
      [*] = ;_gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,elem_d);
      [*] = ;bkg_dy := -1*_gui_ie_GetOffsetY(if_handle,cInfopanelBackground,cInfopanelBackground,true);
      [*] = ;
      [*] = ;//Data grabber
      [*] = ;var Player : String = ParserGetValueByKeyByHandle(curHex, 'Player');
      [*] = ;var ProvinceType : Integer = ParserGetIntValueByKeyByHandle(curHex, 'ProvinceType');
      [*] = ;var ProvinceRace : Integer = ParserGetIntValueByKeyByHandle(curHex, 'ProvinceRace');
      [*] = ;var ProvinceLevel : Integer = ParserGetIntValueByKeyByHandle(curHex, 'ProvinceLevel');
      [*] = ;var Population : Integer = ParserGetIntValueByKeyByHandle(curHex, 'Population');
      [*] = ;var Explored : Integer = ParserGetIntValueByKeyByHandle(curHex, 'Explored');
      [*] = ;var Resource : Integer = ParserGetIntValueByKeyByHandle(curHex, 'Resource');
      [*] = ;var TerrainType : Integer = ParserGetIntValueByKeyByHandle(curHex, 'TerrainType');
      [*] = ;var resExplore : Integer = ParserGetIntValueByKeyByHandle(curHex, 'ResourceExplore');
      [*] = ;var isNeutral : Boolean = _misc_IsProvinceNeutral(curHex);
      [*] = ;var pProvGuard : Integer = ParserSelectByHandleByKey(curHex, 'Guard');
      [*] = ;var pUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;var bGuarded : Boolean = (ParserGetCountByHandle(pUnits)>0);
      [*] = ;var goldInc,gemInc : Integer;
      [*] = ;var goldStr,gemStr : String;
      [*] = ;var goldIncF,gemIncF : Float;
      [*] = ;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Numbers',gc_gui_fontsize_default,'',fontHandleN);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandleT);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_large,'',fontHandleH2); // NormalL
      [*] = ;      
      [*] = ;var bDisplayDetails : Boolean = not _map_CheckGenesisMode(gc_GM_ProvinceDetails);
      [*] = ;
      [*] = ;IntRegister1 := _gv_GetIOHandle();
      [*] = ;IntRegister0 := 7;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;GoldInc := IntRegister0;
      [*] = ;GemInc := IntRegister1;
      [*] = ;GoldIncF := FloatRegister0;
      [*] = ;GemIncF := FloatRegister1;
      [*] = ;GoldStr := StringRegister0;
      [*] = ;GemStr := StringRegister1;
      [*] = ;
      [*] = ;IntRegister0 := ProvinceType;
      [*] = ;MapExecuteState( 'GetProvTypeParserByID');
      [*] = ;var pProvinceType : Integer = IntRegister1;
      [*] = ;var provTypeName : String = ParserGetValueByKeyByHandle(pProvinceType, 'Name');
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerUnrest');
      [*] = ;var Unrest : Integer = IntRegister0;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;var Mood : Integer = IntRegister0;
      [*] = ;
      [*] = ;var terrainTypePrefix : String = '';
      [*] = ;case TerrainType of
      [*] = ;   gc_PlainTerrainType    : terrainTypePrefix := 'plain';
      [*] = ;   gc_ForestTerrainType   : terrainTypePrefix := 'forest';
      [*] = ;   gc_HillTerrainType     : terrainTypePrefix := 'hill';
      [*] = ;   gc_SwampTerrainType    : terrainTypePrefix := 'swamp';
      [*] = ;   gc_DesertTerrainType   : terrainTypePrefix := 'desert';
      [*] = ;   gc_DeadLandTerrainType : terrainTypePrefix := 'deadland';
      [*] = ;end;
      [*] = ;
      [*] = ;if (Player<>'') then
      [*] = ;   ProvinceTypeID := ''
      [*] = ;else
      [*] = ;   ProvinceTypeID := IntToStr(ProvinceType);
      [*] = ;if _log then _Log_Values(ProvinceTypeID,ProvinceType,0,0,0,0,0);
      [*] = ;
      [*] = ;var racePrefix : String = '';
      [*] = ;if ProvinceTypeID = '' then
      [*] = ;begin
      [*] = ;   case ProvinceRace of
      [*] = ;      0 : racePrefix := 'empty';
      [*] = ;      1 : racePrefix := 'human';
      [*] = ;      2 : racePrefix := 'elf';
      [*] = ;      3 : racePrefix := 'dwarf';
      [*] = ;      4 : racePrefix := 'goblin';
      [*] = ;      5 : racePrefix := 'orc';
      [*] = ;      6 : racePrefix := 'halfling';
      [*] = ;      7 : racePrefix := 'centaur';
      [*] = ;      8 : racePrefix := 'lizardman';
      [*] = ;      else ProvinceTypeID := '0';
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var resourcePrefix : String = '';
      [*] = ;case Resource of
      [*] = ;   1 : resourcePrefix := 'iron';
      [*] = ;   2 : resourcePrefix := 'wood';
      [*] = ;   3 : resourcePrefix := 'horses';
      [*] = ;   4 : resourcePrefix := 'mandragora';
      [*] = ;   5 : resourcePrefix := 'arcanite';
      [*] = ;   6 : resourcePrefix := 'marble';
      [*] = ;   7 : resourcePrefix := 'mithril';
      [*] = ;   8 : resourcePrefix := 'diony';
      [*] = ;   9 : resourcePrefix := 'blacklotus';
      [*] = ;end;
      [*] = ;
      [*] = ;var iProvinceMarkCount : Integer;
      [*] = ;var sProvinceMarkType : String;
      [*] = ;if ProvinceLevel <= 2 then
      [*] = ;   sProvinceMarkType  := 'map.infopanel.growth.mark.red'
      [*] = ;else
      [*] = ;   sProvinceMarkType := 'map.infopanel.growth.mark';
      [*] = ;
      [*] = ;if (ProvinceLevel < 4) and (ProvinceLevel > 0) then
      [*] = ;begin
      [*] = ;   if ProvinceLevel = 1 then
      [*] = ;      iProvinceMarkCount := 2
      [*] = ;   else
      [*] = ;      iProvinceMarkCount := 1;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (ProvinceLevel <= 0) or (ProvinceLevel > 11) then
      [*] = ;      iProvinceMarkCount := 0
      [*] = ;   else
      [*] = ;      iProvinceMarkCount := ProvinceLevel-2;
      [*] = ;end;
      [*] = ;
      [*] = ;var textGoldInc, textGemInc : String;
      [*] = ;if (GoldInc>0) then
      [*] = ;   textGoldInc := '+' + IntToStr(GoldInc)
      [*] = ;else
      [*] = ;   textGoldInc := IntToStr(GoldInc);
      [*] = ;if (GemInc>0) then
      [*] = ;   textGemInc := '+' + IntToStr(GemInc)
      [*] = ;else
      [*] = ;   textGemInc := IntToStr(GemInc);
      [*] = ;
      [*] = ;IntRegister0 := curHex;
      [*] = ;MapExecuteState('map.GetProvinceName');
      [*] = ;var textProvinceName : String = StringRegister0;
      [*] = ;
      [*] = ;//maxPopulation
      [*] = ;var pProvinceLevel : Integer = ParserSelectByHandleByIndex(gPrototypeData.provinceLevels.handle, ProvinceLevel);
      [*] = ;var maxPopulation : Integer = ParserGetIntValueByKeyByHandle(pProvinceLevel, 'MaxPopulation');
      [*] = ;
      [*] = ;//InfoPanel
      [*] = ;var elmImageHandle : Integer;
      [*] = ;_sys_FillRect(tmp_pos,0,0,elem_d.p.size.w,bkg_dy);
      [*] = ;tmp_pos.pos.x := GetViewerWidth()-tmp_pos.size.w;
      [*] = ;tmp_pos.pos.y := GetViewerHeight()-elem_d.p.size.h;
      [*] = ;var elmParentInfoPanelHandle : Integer = _gui_CreateImage_VVK('map_infopanel',_gui_GetLayerI(),gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;SetGUIAllowEvents(elmParentInfoPanelHandle, True, False, False); //hintbasis
      [*] = ;SetGUIElementTag(elmParentInfoPanelHandle,dummyUID);
      [*] = ;//SetGUIElementVisible(elmParentInfoPanelHandle, true);
      [*] = ;//SetGUIElementMaterial(elmParentInfoPanelHandle,'aaa');
      [*] = ;
      [*] = ;//var elmImageHandle : Integer = _gui_CreateImage('blank', elmParentInfoPanelHandle, 'misc.blank.black.alpha.0', gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, 0, 0, elem_d.p.size.w, bkg_dy, 0);
      [*] = ;//SetGUIAllowEvents(elmImageHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;elmImageHandle := _gui_CreateImage('map_infopanel_terraintype_background', elmParentInfoPanelHandle, 'map.infopanel.terraintype.background', gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, (elem_d.p.size.w-261) div 2, 30, 261, 126, 0);
      [*] = ;elmImageHandle := _gui_CreateImage('map_infopanel_terraintype_'+terrainTypePrefix, elmParentInfoPanelHandle, 'map.infopanel.terraintype.' + terrainTypePrefix, gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, (elem_d.p.size.w-257) div 2, 50, 257, 127, 0);
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False); //hintbasis
      [*] = ;if ProvinceTypeID <> '' then
      [*] = ;begin
      [*] = ;   elmImageHandle := _gui_CreateImage('map_infopanel_type', elmParentInfoPanelHandle, 'map.infopanel.provincetype.'+ProvinceTypeID, gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, ((elem_d.p.size.w-64) div 2)-2, 64-6, 64, 64, 0);
      [*] = ;   if ProvinceTypeID <> '0' then
      [*] = ;   begin
      [*] = ;      SetGUIElementHint(elmImageHandle,'tooltip|map_infopanel_province_type_'+ProvinceTypeID);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   elmImageHandle := _gui_CreateImage('map_infopanel_race_'+racePrefix, elmParentInfoPanelHandle, 'map.infopanel.race.' + racePrefix, gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, ((elem_d.p.size.w-64) div 2)-2, 64-6, 64, 64, 0);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmInfoPanelBackground : Integer = _gui_CreateImage('map_infopanel_background', elmParentInfoPanelHandle, 'map.infopanel.background', gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, 0 0, elem_d.p.size.w, bkg_dy, 0);
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('map_infopanel_province_name', elmInfoPanelBackground, textProvinceName, 'halParentMiddle', 'valParentMiddle', 0, -125, 200, 32, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;if (Player<>'') or ((isNeutral) and (not bGuarded)) then
      [*] = ;begin
      [*] = ;   var textProvinceExplored : String = GetLocaleTableListItemByID('message', '30') + ' ' + IntToStr(Explored) + '%';
      [*] = ;
      [*] = ;   var fColorR, fColorG, fColorB : Float;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetGrow');
      [*] = ;   var provGrow : Integer = IntRegister0;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetLevel');
      [*] = ;   var oldLevel : Integer = IntRegister0;
      [*] = ;   IntRegister0 := oldLevel;
      [*] = ;   MapExecuteState('GetProvLevelParserByID');
      [*] = ;   var pProvLevel : Integer = IntRegister1;
      [*] = ;   var levelExplored : Integer = ParserGetIntValueByKeyByHandle(pProvLevel, 'Explored');
      [*] = ;   var bRooms : Boolean = False;
      [*] = ;   if (oldLevel<gc_MaxProvinceLevel) then
      [*] = ;   begin
      [*] = ;      if (explored>=levelExplored) or (provGrow<=0) then
      [*] = ;      bRooms := True;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (bRooms) or (explored>=70) then
      [*] = ;   begin
      [*] = ;      fColorR := gc_gui_fontcolor_HeaderR;
      [*] = ;      fColorG := gc_gui_fontcolor_HeaderG;
      [*] = ;      fColorB := gc_gui_fontcolor_HeaderB;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      fColorR := gc_gui_fontcolor_RedR;
      [*] = ;      fColorG := gc_gui_fontcolor_RedG;
      [*] = ;      fColorB := gc_gui_fontcolor_RedB;
      [*] = ;   end;
      [*] = ;
      [*] = ;   elmTextHandle := _gui_CreateText('map_infopanel_province_explored', elmInfoPanelBackground, textProvinceExplored, 'halParentMiddle', 'valParentMiddle', 0, 40, 200, 32, 'halMiddle', 'valMiddle', fontHandleT, fColorR, fColorG, fColorB, 1);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var textProvinceType : String = GetLocaleTableListItemByID(gc_gui_LangTableIDMapProvinceInfo, provTypeName);
      [*] = ;   elmTextHandle := _gui_CreateText('map_infopanel_province_type_'+IntToStr(ProvinceType), elmInfoPanelBackground, textProvinceType, 'halParentMiddle', 'valParentMiddle', 0, 40, 200, 32, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;// Province Income
      [*] = ;elmImageHandle := _gui_CreateImage('map_infopanel_gold', elmInfoPanelBackground, 'map.infopanel.gold', 'halParentRightWidth', 'valParentBottomHeight', -231, -50, 42, 42, 0);
      [*] = ;elmTextHandle := _gui_CreateText('_map_infopanel_province_gold_income', elmInfoPanelBackground, textGoldInc, 'halParentLeft', 'valParentTop', 83-45, 245-15, 80, 41, 'halLeft', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;SetGUIElementTextAlign(elmTextHandle, 'halLeft', 'valMiddle', 40, -3);
      [*] = ;if (GoldInc=0) then
      [*] = ;   SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;
      [*] = ;if GoldStr <> '' then
      [*] = ;begin
      [*] = ;   IntRegister0 := 0;
      [*] = ;   FloatRegister0 := goldIncF;
      [*] = ;   StringRegister0 := goldStr;
      [*] = ;   GUIExecuteState('vvk.map.CreateProvinceIncomeTooltip');
      [*] = ;   SetGUIElementHint(elmTextHandle, StringRegister0);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;elmImageHandle := _gui_CreateImage('_map_infopanel_gem', elmInfoPanelBackground, 'map.infopanel.crystals', 'halParentRightWidth', 'valParentBottomHeight', -78, -53, 42, 42, 0);
      [*] = ;if (GemInc=0) then
      [*] = ;   SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;elmTextHandle := _gui_CreateText('map_infopanel_province_gem_income', elmInfoPanelBackground, textGemInc, 'halParentLeft', 'valParentTop', 239-45, 245-15, 80, 41, 'halLeft', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;SetGUIElementTextAlign(elmTextHandle, 'halLeft', 'valMiddle', 40, -3);
      [*] = ;if GemStr <> '' then
      [*] = ;begin
      [*] = ;   IntRegister0 := 1;
      [*] = ;   FloatRegister0 := gemIncF;
      [*] = ;   StringRegister0 := gemStr;
      [*] = ;   GUIExecuteState('vvk.map.CreateProvinceIncomeTooltip');
      [*] = ;   SetGUIElementHint(elmTextHandle, StringRegister0);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;// Draw Resource Icon
      [*] = ;if (Resource > 0) and (Explored >= resExplore) then
      [*] = ;begin
      [*] = ;   elmImageHandle := _gui_CreateImage('map_infopanel_resource_'+resourcePrefix, elmParentInfoPanelHandle, 'map.resource.' + resourcePrefix, gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, (elem_d.p.size.w-45) div 2, 115+90+20, 45, 45, 0);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False); //hintbasis
      [*] = ;end;
      [*] = ;
      [*] = ;// Population Meter
      [*] = ;var minPopulation : Integer;
      [*] = ;if ProvinceLevel > 0 then
      [*] = ;begin
      [*] = ;   var pPrevProvinceLevel : Integer = ParserSelectByHandleByIndex(gPrototypeData.provinceLevels.handle, ProvinceLevel-1);
      [*] = ;   minPopulation := ParserGetIntValueByKeyByHandle(pPrevProvinceLevel, 'MaxPopulation');
      [*] = ;end
      [*] = ;else
      [*] = ;   minPopulation := 0;
      [*] = ;
      [*] = ;var meterValue : Integer = Floor(117 * (population - minPopulation) / (maxPopulation - minPopulation));
      [*] = ;var hint : String;
      [*] = ;if (meterValue>117) then
      [*] = ;   meterValue := 117;
      [*] = ;elmImageHandle := _gui_CreateImage('map_infopanel_growth_progress', elmInfoPanelBackground, 'map.infopanel.growth.meter', 'halParentLeft', 'valParentBottomHeight', 29, -159, meterValue, 12, 0);
      [*] = ;if (meterValue<=0) then
      [*] = ;   SetGUIElementUserBlend(elmImageHandle, 0);
      [*] = ;elmImageHandle := _gui_CreateImage('map_infopanel_growth_meter', elmImageHandle, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', -2, -1, 119, 14, 0);
      [*] = ;if bDisplayDetails then
      [*] = ;begin
      [*] = ;   hint := IntToStr(dummyUID)+',||512|tooltip|map_infopanel_mood.ext';
      [*] = ;   _gui_ft_AttachHint(elmImageHandle,'VVK.map.HintProvDetailsCallback',hint);  //mood
      [*] = ;end
      [*] = ;else
      [*] = ;   SetGUIElementHint(elmImageHandle, GetLocaleTableListItemByID('tooltip','map_infopanel_growth_meter'));
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;// Province Marks (levels)
      [*] = ;if iProvinceMarkCount > 0 then
      [*] = ;begin
      [*] = ;   const cProvinceMarkOffset = 11;
      [*] = ;   var elmParentInfoPanelProvinceLevelHandle : Integer = _gui_CreateDummy('map_infopanel_provincelevel', elmParentInfoPanelHandle, gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, (elem_d.p.size.w div 4)-((iProvinceMarkCount*cProvinceMarkOffset) div 2)+8{+6}, 111+22, 1, 1, 0);
      [*] = ;   var markInd : Integer;
      [*] = ;   for markInd := 0 to iProvinceMarkCount-1 do
      [*] = ;   begin
      [*] = ;      var extraPixels : Integer = markInd div 3;
      [*] = ;      elmImageHandle := _gui_CreateImage('map_infopanel_mark_'+IntToStr(ProvinceLevel), elmParentInfoPanelProvinceLevelHandle, sProvinceMarkType, gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, 0 + markInd * cProvinceMarkOffset, -10 + (10 - extraPixels * 5), 12 + extraPixels * 4, 18 + extraPixels * 7, 0);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False); //hintbasis
      [*] = ;      //if (ProvinceLevel>2) and (markInd >= ProvinceLevel-2) then
      [*] = ;       //  SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// mood and unrest
      [*] = ;var moodPrefix : String;
      [*] = ;if (mood<-5) then
      [*] = ;   moodPrefix := '.1'
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (mood>3) then
      [*] = ;      moodPrefix := '.9'
      [*] = ;   else
      [*] = ;      moodPrefix := '.'+IntToStr(mood+6);
      [*] = ;end;
      [*] = ;
      [*] = ;elmImageHandle := _gui_CreateImage('map_infopanel_mood', elmParentInfoPanelHandle, 'map.infopanel.mood' + moodPrefix, gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, (elem_d.p.size.w div 2)+(36-22), 109+22, 22, 22, 0);
      [*] = ;hint := IntToStr(dummyUID)+',||512|tooltip|map_infopanel_mood.ext';
      [*] = ;_gui_ft_AttachHint(elmImageHandle,'VVK.map.HintProvMoodCallback',hint);  // mood
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False); //hintbasis
      [*] = ;if (mood=0) then
      [*] = ;   SetGUIElementUserBlend(elmImageHandle, 0.7);
      [*] = ;
      [*] = ;if ((Unrest/gc_MaxUnrest)<0.8) or (mood>=0) then
      [*] = ;begin
      [*] = ;   elmImageHandle := _gui_CreateImage('map_infopanel_uprising_no', elmParentInfoPanelHandle, 'map.infopanel.uprising', gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, (elem_d.p.size.w div 2)+(36-22)+89, 109+22, 22, 22, 0);
      [*] = ;   SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;end
      [*] = ;else
      [*] = ;   elmImageHandle := _gui_CreateImage('map_infopanel_uprising', elmParentInfoPanelHandle, 'map.infopanel.uprising', gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v,  (elem_d.p.size.w div 2)+(36-22)+89, 109+22, 22, 22, 0);
      [*] = ;_gui_ft_AttachHint_I1(elmImageHandle,'VVK.map.HintProvMoodCallback',dummyUID);
      [*] = ;
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False); //hintbasis
      [*] = ;// unrest meter
      [*] = ;if (Unrest>gc_MaxUnrest) then
      [*] = ;begin
      [*] = ;   ErrorLog(_log_name+' Unrest>gc_MaxUnrest see gui.aix Unrest = '+IntToStr(Unrest));
      [*] = ;   Unrest := gc_MaxUnrest;
      [*] = ;end;
      [*] = ;meterValue := Floor(117 * Unrest / gc_MaxUnrest);
      [*] = ;elmImageHandle := _gui_CreateImage('map_infopanel_uprising_progress', elmInfoPanelBackground, 'map.infopanel.uprising.meter', 'halParentLeft', 'valParentBottomHeight', 164+2, -159, meterValue, 12, 0);
      [*] = ;if (meterValue<=0) then
      [*] = ;   SetGUIElementUserBlend(elmImageHandle, 0);
      [*] = ;elmImageHandle := _gui_CreateImage('map_infopanel_uprising_meter', elmInfoPanelBackground, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentBottomHeight', 164, -158, 119, 14, 0);
      [*] = ;if bDisplayDetails then
      [*] = ;   _gui_ft_AttachHint_I1(elmImageHandle,'VVK.map.HintProvDetailsCallback',dummyUID)
      [*] = ;else
      [*] = ;   SetGUIElementHint(elmImageHandle, GetLocaleTableListItemByID('tooltip','map_infopanel_uprising_meter'));
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False); //hint basis
      [*] = ;if (mood>0) and (Unrest>0) then
      [*] = ;   elmImageHandle := _gui_CreateImage('map_infopanel_uprising_direction_down', elmInfoPanelBackground, 'map.infopanel.uprising.down', 'halParentLeft', 'valParentBottomHeight', 193, -173, 66, 15, 0)
      [*] = ;else
      [*] = ;if (mood<0) then
      [*] = ;   elmImageHandle := _gui_CreateImage('map_infopanel_uprising_direction_up', elmInfoPanelBackground, 'map.infopanel.uprising.up', 'halParentLeft', 'valParentBottomHeight', 192, -173, 66, 15, 0);
      [*] = ;SetGUIAllowEvents(elmImageHandle, True, False, False); //hintbasis
      [*] = ;
      [*] = ;// owner herb
      [*] = ;if (Player<>'') then
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName(Player);
      [*] = ;   var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;   var ipprofile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;   var name : String;
      [*] = ;   var sign : Integer;
      [*] = ;   var color1 : Integer;
      [*] = ;   var color2 : Integer;
      [*] = ;
      [*] = ;   if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      case gGame.gameType of
      [*] = ;         gc_GameTypeHotseat : begin
      [*] = ;            sign := gArrHotseatProfiles[plIndex].sign;
      [*] = ;            color1 := gArrHotseatProfiles[plIndex].color1;
      [*] = ;            color2 := gArrHotseatProfiles[plIndex].color2;
      [*] = ;         end;
      [*] = ;         gc_GameTypeLanShard : begin
      [*] = ;            sign := gLanShardGame.arrLanPlayers[plIndex].profile.sign;
      [*] = ;            color1 := gLanShardGame.arrLanPlayers[plIndex].profile.color1;
      [*] = ;            color2 := gLanShardGame.arrLanPlayers[plIndex].profile.color2;
      [*] = ;         end
      [*] = ;         else begin
      [*] = ;            sign := gProfile.sign;
      [*] = ;            color1 := gProfile.color1;
      [*] = ;            color2 := gProfile.color2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (ipProfile>0) then
      [*] = ;   begin
      [*] = ;      var pPlayers : Integer = gPrototypeData.players.handle;
      [*] = ;      var pPlayer : Integer = ParserSelectByHandleByIndex(pPlayers, ipprofile);
      [*] = ;      sign := ParserGetIntValueByKeyByHandle(pPlayer, 'Herb');
      [*] = ;      color1 := ParserGetIntValueByKeyByHandle(pPlayer, 'Color1');
      [*] = ;      color2 := ParserGetIntValueByKeyByHandle(pPlayer, 'Color2');
      [*] = ;      name := GetLocaleTableListItemByID('players', IntToStr(ipprofile));
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      // local lord
      [*] = ;      var lordInd : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;      sign := -2; // no sign
      [*] = ;      color1 := lordInd-1;
      [*] = ;      color2 := lordInd-1;
      [*] = ;      name := 'gui|323';
      [*] = ;   end;
      [*] = ;
      [*] = ;   elmImageHandle := _gui_CreateHerb('', elmInfoPanelBackground, sign, color1, color2, 'halParentLeft', 'valParentTop', 136, 272);
      [*] = ;   SetGUIElementScale(elmImageHandle, 0.75, 0.75);
      [*] = ;end;
      [*] = ;
      [*] = ;if (Player<>'') and (GetPlayerHandleByName(Player)=GetPlayerHandleInterfaceIO()) then
      [*] = ;begin
      [*] = ;   var windowHandle,windowHandle_h,i,f,n,dx,ehd,active_hero : Integer;
      [*] = ;   var temp_str,hint : String;
      [*] = ;
      [*] = ;   _gui_GetInterfaceElement(if_handle,cButtonsPanel,elem_d);
      [*] = ;   _sys_FillRect(tmp_pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;   windowHandle := _gui_CreateImage_VVK('buttons',elmParentInfoPanelHandle,'map.infopanel.buttons.background',gc_gui_align_parent_lt,tmp_pos);
      [*] = ;   GUIElementSendToBack(windowHandle);
      [*] = ;   windowHandle_h := _gui_CreateImage_VVK('buttons_h',elmParentInfoPanelHandle,gc_gui_material_blank_0,gc_gui_align_parent_lt,tmp_pos);
      [*] = ;
      [*] = ;   _gui_GetInterfaceElement(if_handle,cFirstButton,elem_d);
      [*] = ;   tmp_pos.pos.x := _gui_ie_GetOffsetX(if_handle,cFirstButton,cButtonsPanel,false);
      [*] = ;   tmp_pos.pos.y := _gui_ie_GetOffsetY(if_handle,cFirstButton,cButtonsPanel,false);
      [*] = ;   tmp_pos.size.w := elem_d.p.size.w;
      [*] = ;   tmp_pos.size.h := elem_d.p.size.h;
      [*] = ;   dx := tmp_pos.size.w+(-1*_gui_ie_GetOffsetX(if_handle,cButtonsDX,cButtonsDX,true));
      [*] = ;   SetGUIElementTag(windowHandle,dummyHandle);
      [*] = ;
      [*] = ;   active_hero := 0;
      [*] = ;   IntRegister0 := GetPlayerHandleInterfaceIO();
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetHeroesData');
      [*] = ;   if IntRegister2 > 0 then
      [*] = ;   begin
      [*] = ;      temp_str := StringRegister0;
      [*] = ;      active_hero := IntRegister1;
      [*] = ;      for i := 0 to IntRegister2-1 do
      [*] = ;      begin
      [*] = ;         f := _sa_GetAsInt(temp_str,i);
      [*] = ;         n := GetGameObjectIntValueIndByHandle(f,gc_map_GOStack_MapUnit_iTask);
      [*] = ;         if (n = 0) or (n = 6) then
      [*] = ;         begin
      [*] = ;            active_hero := f;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   SetGUIElementTag(windowHandle_h,active_hero);
      [*] = ;
      [*] = ;   for i := cFirstButton to cLastButton do
      [*] = ;   begin
      [*] = ;      case i of
      [*] = ;         cFirstButton: begin // site
      [*] = ;            hint := '';
      [*] = ;            _sa_AddAsInt(hint,1);
      [*] = ;            _sa_AddAsInt(hint,curHex);
      [*] = ;            f := _cmd_CheckExtNF('provincesiteslist','2',hint,temp_str);
      [*] = ;            if (f > 0) then f := _sa_GetAsInt(temp_str,2);
      [*] = ;
      [*] = ;            hint := 'gui|118|0';
      [*] = ;            if (f>0) then hint := hint+'|" (' + IntToStr(f) + ')"';
      [*] = ;
      [*] = ;            if active_hero <> 0 then
      [*] = ;               ehd := _gui_CreateButton_VVK('infopanel_site_button',windowHandle_h, '','map.radialhero.btn.site',elem_d.align,tmp_pos,'map.DoOnPressHeroHUD','gui|654',gc_gui_radialherohud_btnSite)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               ehd := _gui_CreateButton_VVK('infopanel_site_button',windowHandle, '','map.radialprovince.btn.site',elem_d.align,tmp_pos,'','',gc_gui_radialprovince_btnSite);
      [*] = ;               _gui_ft_AttachHint(ehd,'VVK.map.HintProvRadialCallback',hint);
      [*] = ;            end;
      [*] = ;            if (f <= 0) then
      [*] = ;               SetGUIElementEnabled(ehd, false)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if gBoolRegister_BtnEnterSiteBlink then
      [*] = ;                  _gui_CreateBlinkElement('btnEnterSite', ehd, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cFirstButton+1: begin // build
      [*] = ;            temp_str := 'map.radialprovince.btn.build';
      [*] = ;
      [*] = ;            hint := '';
      [*] = ;            _sa_AddAsInt(hint,1);
      [*] = ;            _sa_AddAsInt(hint,curHex);
      [*] = ;            _cmd_CheckExt('provincebuild','',hint,hint);
      [*] = ;            f := _sa_GetAsInt(hint,0);
      [*] = ;            if((f and 8) <> 0) then
      [*] = ;            begin
      [*] = ;               f := _cmd_Check('castlebuild','','1');
      [*] = ;
      [*] = ;               if ((f and $ff) = 1) and ((f and $100) <> 0)then
      [*] = ;               begin
      [*] = ;                  temp_str := 'radialprovince.btn.build.marked';
      [*] = ;                  hint := 'message|2|256|0|0|castlebuild';
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  hint := 'gui|558|0|0|0|castlebuild';
      [*] = ;
      [*] = ;               ehd := _gui_CreateButton_VVK('infopanel_build_button',windowHandle, '',temp_str,elem_d.align,tmp_pos,'',hint,gc_gui_castlepanel_tabs_btnBuild);
      [*] = ;               if ((f and $ff) <> 1) then
      [*] = ;                  SetGUIElementEnabled(ehd, False)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if gBoolRegister_BtnCastleBuildBlink then
      [*] = ;                     _gui_CreateBlinkElement('btnCastleBuild', ehd, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               n := _sa_GetAsInt(hint,1)-_sa_GetAsInt(hint,2);
      [*] = ;               if ((f and 2) <> 0) then
      [*] = ;               begin
      [*] = ;                  temp_str := 'radialprovince.btn.build.marked';
      [*] = ;                  hint := 'message|2|1';
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  hint := 'gui|93|0';
      [*] = ;
      [*] = ;               if n > 0 then
      [*] = ;                  hint := hint+'|" (' + IntToStr(n) + ')"';
      [*] = ;
      [*] = ;               ehd := _gui_CreateButton_VVK('infopanel_site_button',windowHandle, '',temp_str,elem_d.align,tmp_pos,'','',gc_gui_radialprovince_btnBuild);
      [*] = ;               _gui_ft_AttachHint(ehd,'VVK.map.HintProvRadialCallback',hint);
      [*] = ;               if ((f and $10) = 0) or ((f and $9) <> 0) then
      [*] = ;                  SetGUIElementEnabled(ehd, False)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if gBoolRegister_BtnOuterBuildBlink then
      [*] = ;                     _gui_CreateBlinkElement('btnOuterBuild', ehd, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cFirstButton+2: begin // garrison
      [*] = ;            var enabled : Boolean;
      [*] = ;
      [*] = ;            hint := 'gui|94|0';
      [*] = ;            temp_str := '';
      [*] = ;            _sa_AddAsInt(temp_str,1);
      [*] = ;            _sa_AddAsInt(temp_str,curHex);
      [*] = ;            f := _cmd_CheckExtNF('provincegarrison','',temp_str,temp_str);
      [*] = ;            enabled := false;
      [*] = ;            if (f = 1) then
      [*] = ;            begin
      [*] = ;               f := _sa_GetAsInt(temp_str,0);
      [*] = ;               if ((f and $13) = $12) then
      [*] = ;               begin
      [*] = ;                  n := _sa_GetAsInt(temp_str,2);
      [*] = ;                  if n > 0 then
      [*] = ;                     hint := hint+'|" ('+IntToStr(round(100*_sa_GetAsInt(temp_str,1)/n))+'%)"';
      [*] = ;                  enabled := true;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if active_hero <> 0 then
      [*] = ;               ehd := _gui_CreateButton_VVK('infopanel_garrison_button',windowHandle_h, '','hero.btn.hiretroops',elem_d.align,tmp_pos,'map.DoOnPressHeroHUD','hint|4',gc_gui_radialherohud_btnSquad)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               ehd := _gui_CreateButton_VVK('infopanel_garrison_button',windowHandle, '','map.radialprovince.btn.garrison',elem_d.align,tmp_pos,'','',gc_gui_radialprovince_btnGarrison);
      [*] = ;               _gui_ft_AttachHint(ehd,'VVK.map.HintProvRadialCallback',hint);
      [*] = ;            end;
      [*] = ;            SetGUIElementEnabled(ehd,enabled);
      [*] = ;
      [*] = ;            if enabled and gBoolRegister_BtnGarrisonBlink and (active_hero <> 0) then
      [*] = ;               _gui_CreateBlinkElement('btnGarrison', ehd, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;         end;
      [*] = ;         cFirstButton+3: begin // guard
      [*] = ;            hint := '';
      [*] = ;            _sa_AddAsInt(hint,1);
      [*] = ;            _sa_AddAsInt(hint,curHex);
      [*] = ;            f := _cmd_CheckExtNF('provincehireguard','',hint,hint);
      [*] = ;            if f <> 0 then f := _sa_GetAsInt(hint,0);
      [*] = ;
      [*] = ;            if ((f and 4) <> 0) then
      [*] = ;            begin
      [*] = ;               temp_str := 'radialprovince.btn.guard.marked';
      [*] = ;               hint := 'message|7|1';
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               temp_str := 'map.radialprovince.btn.guard';
      [*] = ;               hint := 'gui|92|0';
      [*] = ;            end;
      [*] = ;
      [*] = ;            ehd := _gui_CreateButton_VVK('infopanel_guard_button',windowHandle, '',temp_str,elem_d.align,tmp_pos,'','',gc_gui_radialprovince_btnGuard);
      [*] = ;
      [*] = ;            if ((f and $b) <> 0) then
      [*] = ;            begin
      [*] = ;               if ((f and 3) <> 0) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := ParserSelectByHandleByKey(curHex, 'Defender');
      [*] = ;                  MapExecuteState('map.GetDefenderArmyLifePercent');
      [*] = ;                  hint := hint+'|" ('+IntToStr(IntRegister1)+'%)"';
      [*] = ;               end;
      [*] = ;               if gBoolRegister_BtnDefenderBlink then
      [*] = ;                  _gui_CreateBlinkElement('btnDefender', ehd, gc_gui_material_blink_btn_round, true, 0, 0, 0, 0);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               SetGUIElementEnabled(ehd, False);
      [*] = ;
      [*] = ;            _gui_ft_AttachHint(ehd,'VVK.map.HintProvRadialCallback',hint);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      tmp_pos.pos.x := tmp_pos.pos.x + dx;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

