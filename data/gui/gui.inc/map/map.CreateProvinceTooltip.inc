section.begin
   Name = map.CreateProvinceTooltip
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CREATEPROVINCETOOLTIP';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;var cColorRed : String = '%color('+FormatColorToHex3(gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB)+')%';
      [*] = ;var cColorGreen : String = '%color('+FormatColorToHex3(gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedB)+')%';
      [*] = ;var cColorDef : String = '%color(default)%';
      [*] = ;
      [*] = ;var fog,elmProvDefenderTooltip : Integer;
      [*] = ;procedure GetRitualsString(const pProvince : Integer; var r_str : String; const bMyProvince : Boolean);
      [*] = ;begin
      [*] = ;   // provRituals
      [*] = ;   var text,text1 : String = '';
      [*] = ;   var p,k,pr,i : Integer;
      [*] = ;
      [*] = ;   for k := 0 to 1 do
      [*] = ;   begin
      [*] = ;      if k = 0 then p := ParserSelectByHandleByKey(pProvince, 'Rituals')
      [*] = ;      else p := ParserSelectByHandleByKey(pProvince, 'CastedRituals');
      [*] = ;
      [*] = ;      for i:=0 to ParserGetCountByHandle(p)-1 do
      [*] = ;      begin
      [*] = ;         pr := ParserSelectByHandleByIndex(p,i);
      [*] = ;         text1 := cColorRed + GetLocaleTableListItemByID('ritual', IntToStr(ParserGetIntValueByKeyByHandle(pr, 'RitualID')));
      [*] = ;         if bMyProvince then
      [*] = ;            text1 := text1+' ('+IntToStr(ParserGetIntValueByKeyByHandle(pr, 'Time')+1)+')';
      [*] = ;         
      [*] = ;         text1 := text1 + cColorDef;
      [*] = ;         
      [*] = ;         if text = '' then
      [*] = ;            text := GetLocaleTableListItemByID('gui', '398')+': '+text1
      [*] = ;         else
      [*] = ;            text := text+', '+gc_gui_BreakLine+text1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   r_str := text;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetSitesString(const pProvince : Integer; var r_str : String);
      [*] = ;begin
      [*] = ;   var hint : String = '';
      [*] = ;   var temp_str : String;
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   _sa_AddAsInt(hint,1);
      [*] = ;   _sa_AddAsInt(hint,pProvince);
      [*] = ;   i := _cmd_CheckExtNF('provincesiteslist','2',hint,temp_str);
      [*] = ;   if (i > 0) then
      [*] = ;      i := _sa_GetAsInt(temp_str,2);
      [*] = ;   r_str := GetLocaleTableListItemByID('gui', '753')+': '+cColorRed+IntToStr(i)+cColorDef;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetFortString(const pProvince : Integer; var r_str : String);
      [*] = ;begin
      [*] = ;   // provFortifications
      [*] = ;   var provFortifications : String = '';
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetWallPercent');
      [*] = ;   if IntRegister0 > 0 then
      [*] = ;   begin
      [*] = ;      var wall,j,twr,towers : Integer;
      [*] = ;
      [*] = ;      wall := IntRegister0;
      [*] = ;      IntRegister0 := 0;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'GetTowersData');
      [*] = ;      twr := IntRegister1;
      [*] = ;      towers := IntRegister2;
      [*] = ;
      [*] = ;      for j := 0 to gc_battle_GridSize-1 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := j;
      [*] = ;         MapExecuteState('vvk.bat.GetWallTowerDataByIndex');
      [*] = ;         if (wall > IntRegister0) and (IntRegister1 > 0) and (twr >= IntRegister1) then
      [*] = ;            towers := towers + 1;
      [*] = ;      end;
      [*] = ;      if wall = 0 then
      [*] = ;         j := 7
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if wall >= 99 then
      [*] = ;            j := 0
      [*] = ;         else
      [*] = ;            j := 7-round(wall/(100/7));
      [*] = ;      end;
      [*] = ;      provFortifications := GetLocaleTableListItemByID('gui', '35')+': '+cColorRed+IntToStr(wall)+'%'+cColorDef;
      [*] = ;      provFortifications := provFortifications+gc_gui_BreakLine+'   '+GetLocaleTableListItemByID('gui', '36')+': '+cColorRed+GetLocaleTableListItemByID('gui', IntToStr(27+j))+cColorDef;
      [*] = ;      provFortifications := provFortifications+gc_gui_BreakLine+'   '+GetLocaleTableListItemByID('gui', '37')+': '+cColorRed+IntToStr(towers)+cColorDef;
      [*] = ;   end;
      [*] = ;   r_str := provFortifications;
      [*] = ;end;
      [*] = ;
      [*] = ;function DoBuildProvinceHint() : Integer;
      [*] = ;begin
      [*] = ;   var pProvince : Integer = gIntRegister_MapUnderCursorHex;
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;   var textHeader : String = '';
      [*] = ;   var textDefender : String = '';
      [*] = ;   var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;   var defenderID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;   var sPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;   var defender_hp : Integer = 0;
      [*] = ;   var bMyProvince : Boolean = SameText(GetPlayerNameInterfaceIO(), sPlayer) or gMapEditor.enabled;
      [*] = ;   var provLevel : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;   var bNeutral : Boolean = (sPlayer='') or _misc_IsProvinceNeutral(pProvince);
      [*] = ;
      [*] = ;   if defenderID <> 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvDefender;
      [*] = ;      MapExecuteState('map.GetDefenderArmyLifePercent');
      [*] = ;      defender_hp := IntRegister1;
      [*] = ;   end;
      [*] = ;   if (not bNeutral) then
      [*] = ;   begin
      [*] = ;      if (defenderID<>0) then
      [*] = ;      begin
      [*] = ;         textHeader := GetLocaleTableListItemByID('gui', '420');
      [*] = ;         textDefender := GetLocaleTableListItemByID('defender', IntToStr(defenderID))+' ('+IntToStr(defender_hp)+'%)';
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         textDefender := GetLocaleTableListItemByID('gui', 'DefenderSlotIsFree');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceType');
      [*] = ;      if (IntRegister0 <> 0) then
      [*] = ;      begin
      [*] = ;         MapExecuteState('GetProvTypeParserByID');
      [*] = ;         var provTypeName : String = ParserGetValueByKeyByHandle( IntRegister1, 'Name');
      [*] = ;
      [*] = ;         textHeader := GetLocaleTableListItemByID('message', '33');
      [*] = ;         textDefender := GetLocaleTableListItemByID(gc_gui_LangTableIDMapProvinceInfo, provTypeName);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //if (textDefender='') then
      [*] = ;   //   Result := 0
      [*] = ;   //else
      [*] = ;   begin
      [*] = ;      var text : String;
      [*] = ;      
      [*] = ;      // hero moves
      [*] = ;      var heroMoves : String = '';
      [*] = ;      if gIntRegister_MapSelectedUID <> 0 then
      [*] = ;      begin
      [*] = ;         var moveMap : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;         if moveMap > 0 then
      [*] = ;            heroMoves := GetLocaleTableListItemByID('gui', '313')+': '+cColorRed+IntToStr(moveMap)+cColorDef+gc_gui_BreakLine+gc_gui_BreakLine;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // provName
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      MapExecuteState('map.GetProvinceName');
      [*] = ;      var provName : String = StringRegister0;
	   [*] = ;      
      [*] = ;      // provBuildings
	   [*] = ;      var provBuildStr : String = '';
	   [*] = ;      if bMyProvince then
	   [*] = ;      begin
	   [*] = ;         var pOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;         var provBuildingsCount, i : Integer = 0; 
	   [*] = ;         for i := 0 to ParserGetCountByHandle(pOuterBuildings)-1 do
	   [*] = ;         begin
      [*] = ;            var pOuterBuilding : Integer = ParserSelectByHandleByIndex(pOuterBuildings, i);
      [*] = ;            if (ParserGetIntValueByKeyByHandle(pOuterBuilding, 'OuterBuildID') > 0) then
      [*] = ;               provBuildingsCount := provBuildingsCount + 1;
	   [*] = ;         end;
      [*] = ;         PlayerExecuteStateByHandle(GetPlayerHandleByName(sPlayer), 'GetCastleParser');
	   [*] = ;         if ((provLevel > 2) or (pProvince = IntRegister0)) then
	   [*] = ;         begin
	   [*] = ;            if pProvince = IntRegister0 then
	   [*] = ;               provBuildStr := gc_gui_BreakLine+GetLocaleTableListItemByID('message', '2')+': '+cColorRed+IntToStr(ParserGetCountByHandle(ParserSelectByHandleByKey(pProvince, 'InnerBuildings')))+cColorDef
	   [*] = ;            else
	   [*] = ;               provBuildStr := gc_gui_BreakLine+GetLocaleTableListItemByID('message', '2')+': '+cColorRed+IntToStr(provBuildingsCount)+'/'+IntToStr(3)+cColorDef;
	   [*] = ;         end;
	   [*] = ;      end;
	   [*] = ;      
	   [*] = ;      
      [*] = ;      // provTypeName
      [*] = ;      IntRegister0 := ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceType');
      [*] = ;      MapExecuteState('GetProvTypeParserByID');
      [*] = ;      var provTypeKey : String = ParserGetValueByKeyByHandle( IntRegister1, 'Name');
      [*] = ;      var provTypeName : String = GetLocaleTableListItemByID(gc_gui_LangTableIDMapProvinceInfo, provTypeKey);
      [*] = ;
      [*] = ;      // provDefender
      [*] = ;      var provDefender : String;
      [*] = ;      if (defenderID<>0) then
      [*] = ;         provDefender := GetLocaleTableListItemByID('defender', IntToStr(defenderID)) +' ('+IntToStr(defender_hp)+'%)'
      [*] = ;      else
      [*] = ;         provDefender := GetLocaleTableListItemByID('gui', 'DefenderSlotIsFree');
      [*] = ;
      [*] = ;      text := heroMoves + GetLocaleTableListItemByID('gui', '750')+': '+cColorRed + provName + cColorDef + provBuildStr;
      [*] = ;      if (bNeutral) then
      [*] = ;         text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '751')+': '+cColorRed+provTypeName+cColorDef
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (defenderID<>0) then
      [*] = ;            text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '752')+': '+cColorRed+provDefender+cColorDef;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gBoolRegister_ShowProvinceExtendedHint) then
      [*] = ;      begin
      [*] = ;         var temp_str : String;
      [*] = ;
      [*] = ;         GetFortString(pProvince,temp_str);
      [*] = ;         if (temp_str<>'') then
      [*] = ;            text := text+gc_gui_BreakLine+temp_str;
      [*] = ;
      [*] = ;         var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;         var pUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;         var bGuarded : Boolean = (ParserGetCountByHandle(pUnits)>0);
      [*] = ;         if bMyProvince or (bNeutral and (not bGuarded)) then
      [*] = ;         begin
      [*] = ;            GetSitesString(pProvince,temp_str);
      [*] = ;            if (temp_str<>'') then
      [*] = ;               text := text+gc_gui_BreakLine+temp_str;
      [*] = ;         end;
      [*] = ;
      [*] = ;         GetRitualsString(pProvince, temp_str, bMyProvince);
      [*] = ;         if (temp_str<>'') then
      [*] = ;            text := text+gc_gui_BreakLine+temp_str;
	   [*] = ;         
	   [*] = ;         // terrain type
	   [*] = ;         text := text + gc_gui_BreakLine + GetLocaleTableListItemByID('hint', '20')+': '+cColorRed;
	   [*] = ;         var terrID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType');
	   [*] = ;         case terrID of
      [*] = ;            1 : text := text+GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_plain');
      [*] = ;            2 : text := text+GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_forest');
      [*] = ;            3 : text := text+GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_hill');
      [*] = ;            4 : text := text+GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_swamp');
      [*] = ;            5 : text := text+GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_desert');
      [*] = ;            6 : text := text+GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_deadLand');
      [*] = ;         end;
	   [*] = ;         text := text+cColorDef;
      [*] = ;      end;
      [*] = ;
      [*] = ;      {if (_console_GetIntVar('DebugShowExtraInfo') > 0) and (gIntConsoleStateMachineHandle <> 0) then
      [*] = ;      begin
      [*] = ;         if (gBoolRegister_ShowProvinceExtendedHint) then
      [*] = ;         begin
      [*] = ;            StringRegister0 := '-1 1';
      [*] = ;            StringRegister1 := 'cc.provinfo -1 1';
      [*] = ;            IntRegister1 := 2;
      [*] = ;            StringRegister2 := '-1|1';
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            StringRegister0 := '';
      [*] = ;            StringRegister1 := 'cc.provinfo';
      [*] = ;            IntRegister1 := 0;
      [*] = ;            StringRegister2 := '';
      [*] = ;         end;
      [*] = ;         IntRegister0 := -1;
      [*] = ;         FloatRegister0 := -1;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         BoolRegister1 := false;
      [*] = ;         StateMachineExecuteState(gIntConsoleStateMachineHandle,'cc.provinfo',0);
      [*] = ;         text := text+gc_gui_BreakLine+StringRegister0;
      [*] = ;      end;}
      [*] = ;
      [*] = ;      if gc_RecycleGUI then
      [*] = ;      begin
      [*] = ;         var elmTooltip : Integer = _gui_GetWindow('prov_defender_tooltip');
      [*] = ;         if (elmTooltip <> 0) then
      [*] = ;            _gui_Show(elmTooltip, false);
      [*] = ;      end;
      [*] = ;      Result := _gui_ft_DisplayCommonTooltipExt(_gui_GetLayerI(),0,'prov_defender_tooltip',text,(not gBoolRegister_ShowProvinceExtendedHint),bMyProvince);
      [*] = ;      SetGUIElementTag(Result,gIntRegister_MapUnderCursorHex);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoRestrictOffsetProvinceDefenderHint(elmHandle : Integer);
      [*] = ;begin
      [*] = ;   var bnd_box : TRectangle;
      [*] = ;   var p : Integer;
      [*] = ;
      [*] = ;   _sys_FillRect(bnd_box,0,0,GetViewerWidth(),GetViewerHeight());
      [*] = ;   p := _gui_GetWindow(gc_gui_CPBottomName+'.safe_area');
      [*] = ;   if p <> 0 then
      [*] = ;      bnd_box.size.h := bnd_box.size.h-GetGUIElementHeight(p);
      [*] = ;
      [*] = ;   _gui_AlignWindowByCursorExt_VVK(elmHandle,bnd_box);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var curHex : Integer = gIntRegister_MapUnderCursorHex; //Эксперимент, обновлять инфопанель при наведении на провинцию
      [*] = ;var isPlayable : Boolean = False;
      [*] = ;
      [*] = ;//PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'GetCastleParser');
      [*] = ;//var pCastle : Integer = IntRegister0;
      [*] = ;
      [*] = ;if (curHex <> 0) and (gGame.fog) then
      [*] = ;   fog := ParserGetIntValueByIndexByHandle(ParserSelectByHandleByKey(curHex, 'Fog'), gIntRegister_MapMyPlayerIndex)
      [*] = ;else
      [*] = ;   fog := 0;
      [*] = ;
      [*] = ;if (fog = 0) and (curHex<>0) then
      [*] = ;begin
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(curHex, 'DummyUID'));
      [*] = ;   if dummyHandle <> 0 then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'IsPlayable');
      [*] = ;      isPlayable := BoolRegister0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;elmProvDefenderTooltip := _gui_GetWindow('prov_defender_tooltip');
      [*] = ;
      [*] = ;if (curHex=0) or (fog > 0) or (not isPlayable) then
      [*] = ;begin
      [*] = ;   if gc_RecycleGUI then
      [*] = ;      _gui_Show(elmProvDefenderTooltip,false)
      [*] = ;   else
      [*] = ;      _gui_RootWindowRemoveWithFade(elmProvDefenderTooltip,0);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var tag : Integer = -1;
      [*] = ;
      [*] = ;   if elmProvDefenderTooltip <> 0 then
      [*] = ;      tag := GetGUIElementTag(elmProvDefenderTooltip);
      [*] = ;   if (tag <> gIntRegister_MapUnderCursorHex) or (gBoolRegister_ShowProvinceExtendedHint) then
      [*] = ;      elmProvDefenderTooltip := DoBuildProvinceHint();
      [*] = ;   if elmProvDefenderTooltip <> 0 then
      [*] = ;      DoRestrictOffsetProvinceDefenderHint(elmProvDefenderTooltip);
      [*] = ;
      [*] = ;   if (not gBoolRegister_ShowProvinceExtendedHint) then
      [*] = ;      _gui_DelayExecuteStateOneInstance('map.CreateProvinceTooltipExt', gProfile.exthintdelay)
      [*] = ;   else
      [*] = ;      gBoolRegister_ShowProvinceExtendedHint := False;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

