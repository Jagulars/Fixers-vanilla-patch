section.begin
   Name = map.GUIUpdateResHUD
   Description : struct.begin
      [*] = ;Not just resource but all 2D information laid on top of the province
   struct.end
   Code : struct.begin
      [*] = ;const cEventPressHUDState = 'map.DoOnPressHUD';
      [*] = ;const cEventState = 'map.EventGUIResHUD';
      [*] = ;
      [*] = ;const cCenterOffsetY = -34;
      [*] = ;const cResProvTypeSeparationWidth = 26;
      [*] = ;const cIconSpaceHeight = 26;
      [*] = ;const cProvLevelSpaceHeight = 12;
      [*] = ;
      [*] = ;var pStratHexCell : Integer = IntRegister0;
      [*] = ;var hudCollection : Integer = GetGUIElementTopIndexByName('hudres');
      [*] = ;if hudCollection = 0 then
      [*] = ;   exit;
      [*] = ;
      [*] = ;var provIndex : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Index');
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;if (not GetGameObjectStateMachineActiveByHandle(dummyHandle)) or (not GetGameObjectVisibleByHandle(dummyHandle)) then
      [*] = ;   exit;
      [*] = ;
      [*] = ;var provinceType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;var provRace : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceRace');
      [*] = ;var provinceLevel : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceLevel');
      [*] = ;var resID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Resource');
      [*] = ;var provExplore : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Explored');
      [*] = ;var resExplore : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ResourceExplore');
      [*] = ;var resGuarded : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'ResourceGuarded');
      [*] = ;var sPlayer : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(sPlayer);
      [*] = ;var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;
      [*] = ;var pProvFog : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Fog');
      [*] = ;var fog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, gIntRegister_MapMyPlayerIndex);
      [*] = ;var elmSpotlightHandle : Integer = 0;
      [*] = ;
      [*] = ;// HUD button
      [*] = ;var hudHandle : Integer = GetGUIGroupHUDCollectionItemByGameObject(hudCollection, dummyHandle);
      [*] = ;var elmHandle : Integer;
      [*] = ;if (hudHandle = 0) then
      [*] = ;begin
      [*] = ;   hudHandle := GUIGroupHUDCollectionAddGameObject(hudCollection, dummyHandle);
      [*] = ;   elmHandle := AddNewElementParent('', 'btn', dummyHandle, hudHandle);
      [*] = ;   SetGUIElementPressState(elmHandle, cEventPressHUDState);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   elmHandle := GetGUIElementIndexByNameParent('btn', hudHandle);
      [*] = ;   SetGUIElementTag(elmHandle, dummyHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;var hudImage : Integer = GetGUIElementIndexByNameParent('hud_res_background', hudHandle);
      [*] = ;if hudImage <> 0 then
      [*] = ;   RemoveGUIElement(hudImage);
      [*] = ;
      [*] = ;if (fog = 2) and gGame.fog then
      [*] = ;exit;
      [*] = ;
      [*] = ;if (not gBoolRegister_ShowResourceOnProvince) then
      [*] = ;exit;
      [*] = ;
      [*] = ;var bShowHidden : Boolean = False;
      [*] = ;if (plHandle=GetPlayerHandleInterfaceIO) and (resID<>0) then
      [*] = ;begin
      [*] = ;   var terrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   IntRegister0 := 26;
      [*] = ;   IntRegister1 := terrainType;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'CheckInnerBuildAbilityByParam1');
      [*] = ;   bShowHidden := (IntRegister2>0);
      [*] = ;end;
      [*] = ;
      [*] = ;var bDrawProvType : Boolean = (gProfile.provhudflags and gc_gui_provhudflag_type) > 0;
      [*] = ;var bDrawResource : Boolean = (resID<>0) and ((provExplore>=resExplore) or bShowHidden);
      [*] = ;
      [*] = ;var posX, posY, sizeX, sizeY, offsetX, offsetY : Integer;
      [*] = ;var hint : String;
      [*] = ;
      [*] = ;SetGUIElementPressState(elmHandle, cEventPressHUDState);
      [*] = ;SetGUIAllowMouseButtons(elmHandle, True, True, False);
      [*] = ;SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;var elmMainHandle : Integer = _gui_CreateDummy('hud_res_background', hudHandle, 'halParentMiddle', 'valParentMiddle', 0, cCenterOffsetY, 0, 0, 0);
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;if bDrawResource then
      [*] = ;begin
      [*] = ;   var sHudImage : String = '';
      [*] = ;   
      [*] = ;   if (provExplore>=resExplore) then
      [*] = ;   begin
      [*] = ;      var resSuffix : String = '';
      [*] = ;      case resID of
      [*] = ;         0 : begin
      [*] = ;            resSuffix := '';
      [*] = ;            sHudImage := gc_gui_material_blank_0;
      [*] = ;         end;
      [*] = ;         1 : resSuffix := '.iron';
      [*] = ;         2 : resSuffix := '.wood';
      [*] = ;         3 : resSuffix := '.horses';
      [*] = ;         4 : resSuffix := '.mandragora';
      [*] = ;         5 : resSuffix := '.arcanite';
      [*] = ;         6 : resSuffix := '.marble';
      [*] = ;         7 : resSuffix := '.mithril';
      [*] = ;         8 : resSuffix := '.diony';
      [*] = ;         9 : resSuffix := '.blacklotus';
      [*] = ;      end;
      [*] = ;      offsetY := -4;
      [*] = ;      sizeX := 45;
      [*] = ;      sizeY := 45;
      [*] = ;      sHudImage := 'map.resource' + resSuffix;
      [*] = ;
      [*] = ;      IntRegister0 := resID;
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO, 'GetResCount');
      [*] = ;      var resCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;      if (resCount>0) then
      [*] = ;      hint := 'tooltip|castle_resource_'+IntToStr(resID)+'_yes'
      [*] = ;      else
      [*] = ;      hint := 'resource|'+IntToStr(resID);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (bShowHidden) then
      [*] = ;   begin
      [*] = ;      offsetX := -1;
      [*] = ;      sizeX := 52;
      [*] = ;      sizeY := 63;
      [*] = ;      hint := 'gui|ResourceUnknown';
      [*] = ;      sHudImage := 'map.prov.resource.unknown';
      [*] = ;   end;
      [*] = ;   
      [*] = ;   posY := 32;
      [*] = ;   
      [*] = ;   if bDrawProvType then
      [*] = ;      posX := cResProvTypeSeparationWidth
      [*] = ;   else
      [*] = ;      posX := 0;
      [*] = ;   
      [*] = ;   var elmResFrame : Integer = _gui_CreateImage('hud_res_frame', elmMainHandle, 'map.prov.resource.frame', 'halParentMiddle', 'valParentMiddle', posX, posY, 52, 63, 0);
      [*] = ;   SetGUIElementUserBlend(elmResFrame, 0.9);
      [*] = ;   var elmResHandle : Integer = _gui_CreateImage('hud_res', elmResFrame, sHudImage, 'halParentMiddle', 'valParentMiddle', offsetX, offsetY, sizeX, sizeY, 0);
      [*] = ;   SetGUIElementUserBlend(elmResHandle, 0.9);
      [*] = ;   SetGUIElementHint(elmResHandle, hint);
      [*] = ;   SetGUIElementPressState(elmResHandle, cEventPressHUDState);
      [*] = ;   SetGUIAllowEvents(elmResHandle, True, False, False);
      [*] = ;   SetGUIElementCursorByIndex(elmResHandle, -1);
      [*] = ;
      [*] = ;   if (resGuarded) and (provExplore>=resExplore) then
      [*] = ;   begin
      [*] = ;      var elmImage : Integer = _gui_CreateImage('hud_res_guard', elmResFrame, 'map.prov.resource.guarded', 'halParentMiddle', 'valParentMiddle', 0, 0, 52, 63, 0);
      [*] = ;      SetGUIElementUserBlend(elmImage, 0.65);
      [*] = ;      SetGUIElementUserBlend(elmResHandle, 1.0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;if bDrawProvType then
      [*] = ;begin
      [*] = ;   posY := 32;
      [*] = ;   
      [*] = ;   if bDrawResource then
      [*] = ;      posX := -cResProvTypeSeparationWidth
      [*] = ;   else
      [*] = ;      posX := 0;
      [*] = ;   
      [*] = ;   var elmProvType : Integer = _gui_CreateImage('hud_provtype_frame', elmMainHandle, 'map.prov.resource.frame', 'halParentMiddle', 'valParentMiddle', posX, posY, 52, 63, 0);
      [*] = ;   SetGUIElementUserBlend(elmProvType, 0.9);
      [*] = ;   
      [*] = ;   var sIcon : String = '';
      [*] = ;   if (sPlayer<>'') then
      [*] = ;   begin
      [*] = ;      if ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle') then
      [*] = ;      begin
      [*] = ;         var sProfile : String = '0';
      [*] = ;         if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer') then
      [*] = ;         begin
      [*] = ;            case gGame.gameType of
      [*] = ;               gc_GameTypeHotseat : sProfile := IntToStr(gArrHotseatProfiles[plIndex].avatar);
      [*] = ;               gc_GameTypeLanShard : sProfile := IntToStr(gLanShardGame.arrLanPlayers[plIndex].profile.avatar);
      [*] = ;               gc_GameTypeCampaign : begin
      [*] = ;                  if (gTutorial.map) then
      [*] = ;                     sProfile := '17'
      [*] = ;                  else
      [*] = ;                     sProfile := 'player';
      [*] = ;               end;
      [*] = ;               else sProfile := IntToStr(gProfile.avatar);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            sProfile := IntToStr(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile));
      [*] = ;         
      [*] = ;         if sProfile <> '0' then
      [*] = ;         begin
      [*] = ;            sizeX := 42;
      [*] = ;            sizeY := 42;
      [*] = ;            offsetX := 0;
      [*] = ;            offsetY := -4;
      [*] =              sIcon := 'astral.players.icon.small.'+sProfile;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            sizeX := 47;
      [*] = ;            sizeY := 47;
      [*] = ;            offsetX := -2;
      [*] = ;            offsetY := -3;
      [*] =              sIcon := 'map.infopanel.provincetype.7';
      [*] = ;         end;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetName');
      [*] = ;         hint := StringRegister0;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         sizeX := 46;
      [*] = ;         sizeY := 46;
      [*] = ;         offsetX := -1;
      [*] = ;         offsetY := -3;
      [*] = ;         var racePrefix : String = '';
      [*] = ;         case provRace of
      [*] = ;            0 : racePrefix := 'empty';
      [*] = ;            1 : racePrefix := 'human';
      [*] = ;            2 : racePrefix := 'elf';
      [*] = ;            3 : racePrefix := 'dwarf';
      [*] = ;            4 : racePrefix := 'goblin';
      [*] = ;            5 : racePrefix := 'orc';
      [*] = ;            6 : racePrefix := 'halfling';
      [*] = ;            7 : racePrefix := 'centaur';
      [*] = ;            8 : racePrefix := 'lizardman';
      [*] = ;         end;
      [*] =           sIcon := 'map.infopanel.race.'+racePrefix;
      [*] = ;         hint := 'races|'+IntToStr(provRace);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      sizeX := 47;
      [*] = ;      sizeY := 47;
      [*] = ;      offsetX := -2;
      [*] = ;      offsetY := -3;
      [*] =        sIcon := 'map.infopanel.provincetype.'+IntToStr(provinceType);
      [*] = ;      hint := 'tooltip|map_infopanel_province_type_'+IntToStr(provinceType);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var elmImage : Integer = _gui_CreateImage('hud_provtype', elmProvType, sIcon, 'halParentMiddle', 'valParentMiddle', offsetX, offsetY, sizeX, sizeY, 0);
      [*] = ;   //SetGUIElementUserBlend(elmImage, 0.9);
      [*] = ;   SetGUIElementHint(elmImage, hint);
      [*] = ;   SetGUIElementPressState(elmImage, cEventPressHUDState);
      [*] = ;   SetGUIAllowEvents(elmImage, True, False, False);
      [*] = ;   SetGUIElementCursorByIndex(elmImage, -1);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var iconIndex : Integer = 0;
      [*] = ;var provLevelMarks : Integer = 0;
      [*] = ;
      [*] = ;if (gProfile.provhudflags and gc_gui_provhudflag_level) > 0 then
      [*] = ;begin
      [*] = ;   if (provinceLevel > 2) and (provinceLevel <= 11) then
      [*] = ;      provLevelMarks := provinceLevel-2;
      [*] = ;end;
      [*] = ;
      [*] = ;if (fog<=1) or (not gGame.fog) then
      [*] = ;begin
      [*] = ;   // additional icons
      [*] = ;   // owner herb (banners)
      [*] = ;   var bHerb : Boolean = False;
      [*] = ;   if not _obj_CreationStateEnabled('ProvinceFlags') then // instead of creating a GameObject, draw a simple image on top of the province.
      [*] = ;   begin
      [*] = ;      if (sPlayer<>'') then
      [*] = ;      begin
      [*] = ;         var ipprofile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;         var name : String;
      [*] = ;         var sign : Integer;
      [*] = ;         var color1 : Integer;
      [*] = ;         var color2 : Integer;
      [*] = ;
      [*] = ;         if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer') then
      [*] = ;         begin
      [*] = ;            case gGame.gameType of
      [*] = ;               gc_GameTypeLanShard : begin
      [*] = ;                  sign := gLanShardGame.arrLanPlayers[plIndex].profile.sign;
      [*] = ;                  color1 := gLanShardGame.arrLanPlayers[plIndex].profile.color1;
      [*] = ;                  color2 := gLanShardGame.arrLanPlayers[plIndex].profile.color2;
      [*] = ;               end;
      [*] = ;               gc_GameTypeHotseat : begin
      [*] = ;                  sign := gArrHotseatProfiles[plIndex].sign;
      [*] = ;                  color1 := gArrHotseatProfiles[plIndex].color1;
      [*] = ;                  color2 := gArrHotseatProfiles[plIndex].color2;
      [*] = ;               end;
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  sign := gProfile.sign;
      [*] = ;                  color1 := gProfile.color1;
      [*] = ;                  color2 := gProfile.color2;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (ipProfile>0) then
      [*] = ;         begin
      [*] = ;            var pPlayers : Integer = gPrototypeData.players.handle;
      [*] = ;            var pPlayer : Integer = ParserSelectByHandleByIndex(pPlayers, ipprofile);
      [*] = ;            sign := ParserGetIntValueByKeyByHandle(pPlayer, 'Herb');
      [*] = ;            color1 := ParserGetIntValueByKeyByHandle(pPlayer, 'Color1');
      [*] = ;            color2 := ParserGetIntValueByKeyByHandle(pPlayer, 'Color2');
      [*] = ;            name := GetLocaleTableListItemByID('players', IntToStr(ipprofile));
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            // local lord
      [*] = ;            var lordInd : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;            sign := -2; // no sign
      [*] = ;            color1 := lordInd-1;
      [*] = ;            color2 := lordInd-1;
      [*] = ;            name := 'gui|323';
      [*] = ;         end;
      [*] = ;
      [*] = ;         if bDrawResource or bDrawProvType then
      [*] = ;            posY := -45
      [*] = ;         else
      [*] = ;            posY := -30;
      [*] = ;         elmHandle := _gui_CreateHerb('', elmMainHandle, sign, color1, color2, 'halParentMiddle', 'valParentTop', 0, posY);
      [*] = ;         SetGUIElementScale(elmHandle, 0.75, 0.75);
      [*] = ;
      [*] = ;         bHerb := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var under_siege,siege_turns : Integer;
      [*] = ;   var temp_str : String;
      [*] = ;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'vvk.GetSiegeParameters');
      [*] = ;   siege_turns := IntRegister1;
      [*] = ;   if BoolRegister0 and (IntRegister0 <> GetPlayerHandleInterfaceIO()) then
      [*] = ;   begin
      [*] = ;      if IntRegister0 <> 0 then
      [*] = ;         under_siege := 2
      [*] = ;      else
      [*] = ;         under_siege := 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      under_siege := 0;
      [*] = ;
      [*] = ;   var iconCount : Integer = 0;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to 1 do
      [*] = ;   begin
      [*] = ;      //if (i=1) and (iconCount=0) then
      [*] = ;      //break;
      [*] = ;      var bDraw : Boolean;
      [*] = ;      if (i=0) then
      [*] = ;      bDraw := False
      [*] = ;      else
      [*] = ;      bDraw := True;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;      var Mood : Integer = IntRegister0;
      [*] = ;
      [*] = ;      var moodPrefix : String;
      [*] = ;      if (mood<-5) then
      [*] = ;         moodPrefix := '.1'
      [*] = ;      else
      [*] = ;      if (mood>3) then
      [*] = ;         moodPrefix := '.9'
      [*] = ;      else
      [*] = ;      case mood of
      [*] = ;         -5 : moodPrefix := '.1';
      [*] = ;         -4 : moodPrefix := '.2';
      [*] = ;         -3 : moodPrefix := '.3';
      [*] = ;         -2 : moodPrefix := '.4';
      [*] = ;         -1 : moodPrefix := '.5';
      [*] = ;         0 : moodPrefix := '.6';
      [*] = ;         1 : moodPrefix := '.7';
      [*] = ;         2 : moodPrefix := '.8';
      [*] = ;         3 : moodPrefix := '.9';
      [*] = ;      end;
      [*] = ;
      [*] = ;      const cIconOffset = 26;
      [*] = ;      posX := 0;
      [*] = ;      posY := 16;
      [*] = ;      if bDrawResource or bDrawProvType then
      [*] = ;         posY := posY + 36;
      [*] = ;      
      [*] = ;      if (bDraw) {and (iconCount>0)} then
      [*] = ;      begin
      [*] = ;         posX := 0;
      [*] = ;         elmSpotlightHandle := _gui_CreateImage('spotlight', elmMainHandle, gc_gui_material_blank_0, 'halParentMiddle', 'valParentTop', -((iconCount*cIconOffset) div 2)-2, posY, 0, 0, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      posY := 0;
      [*] = ;   
      [*] = ;      if _misc_IsProvinceNeutral(pStratHexCell) then
      [*] = ;      begin
      [*] = ;         var pProvGuard : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Guard');
      [*] = ;         var pUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;         var bGuarded : Boolean = (ParserGetCountByHandle(pUnits)>0);
      [*] = ;
      [*] = ;         if (bDraw) then
      [*] = ;         begin
      [*] = ;            if (bGuarded) then
      [*] = ;            begin
      [*] = ;               posX := (iconIndex*cIconOffset);
      [*] = ;               elmHandle := _gui_CreateImage('provhud_neutral_guard', elmSpotlightHandle, 'map.provhud.neutral', 'halParentLeft', 'valParentTop', posX+1, -4, 28, 28, 0);
      [*] = ;               SetGUIElementUserBlend(elmHandle, 0.9);
      [*] = ;               hint := 'gui|710';
      [*] = ;            {end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               elmHandle := _gui_CreateImage('provhud_neutral_noguard', elmSpotlightHandle, 'map.provhud.neutral', 'halParentMiddle', 'valParentMiddle', posX, posY, GetGUITextureWidth('map.provhud.neutral') div 2, GetGUITextureHeight('map.provhud.neutral') div 2, 0);
      [*] = ;               SetGUIElementUserBlend(elmHandle, 0.3);
      [*] = ;               hint := 'gui|711';
      [*] = ;            end;}
      [*] = ;               SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;               SetGUIElementHint(elmHandle, hint);
      [*] = ;               SetGUIElementPressState(elmHandle, cEventState);
      [*] = ;               iconIndex := iconIndex+1;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         iconCount := iconCount+1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // mood
      [*] = ;      if (plHandle=GetPlayerHandleInterfaceIO) and ((gProfile.provhudflags and gc_gui_provhudflag_mood) > 0) then
      [*] = ;      begin
      [*] = ;         if (mood<0) then
      [*] = ;         begin
      [*] = ;            if (bDraw) then
      [*] = ;            begin
      [*] = ;               var shadowOff : Integer = 2;
      [*] = ;               posX := (iconIndex*cIconOffset);
      [*] = ;               elmHandle := _gui_CreateImage('provhud_mood', elmSpotlightHandle, 'map.infopanel.mood'+moodPrefix, 'halParentLeft', 'valParentTop', posX-shadowOff, posY-shadowOff+3, 22+shadowOff*2, 22+shadowOff*2, 0);
      [*] = ;               SetGUIElementUserColor(elmHandle, 0, 0, 0, 1);
      [*] = ;               SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;               elmHandle := _gui_CreateImage('provhud_mood', elmSpotlightHandle, 'map.infopanel.mood'+moodPrefix, 'halParentLeft', 'valParentTop', posX, posY+3, 22, 22, 0);
      [*] = ;               SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;               _gui_ft_AttachHint(elmHandle,'VVK.map.HintProvMoodCallback',IntToStr(dummyUID)+',tooltip|map_infopanel_mood'); // mood
      [*] = ;               SetGUIElementPressState(elmHandle, cEventState);
      [*] = ;               iconIndex := iconIndex+1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            iconCount := iconCount+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // unrest
      [*] = ;      if (plHandle=GetPlayerHandleInterfaceIO) and ((gProfile.provhudflags and gc_gui_provhudflag_unrest) > 0) then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerUnrest');
      [*] = ;         var Unrest : Integer = IntRegister0;
      [*] = ;         if ((Unrest/gc_MaxUnrest)>=0.8) and (mood<0) then
      [*] = ;         if (bDraw) then
      [*] = ;         begin
      [*] = ;            var shadowOff : Integer = 2;
      [*] = ;            posX := (iconIndex*cIconOffset);
      [*] = ;            elmHandle := _gui_CreateImage('provhud_mood', elmSpotlightHandle, 'map.infopanel.mood'+moodPrefix, 'halParentLeft', 'valParentTop', posX-shadowOff, posY-shadowOff+3, 22+shadowOff*2, 22+shadowOff*2, 0);
      [*] = ;            SetGUIElementUserColor(elmHandle, 0, 0, 0, 1);
      [*] = ;            SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;            elmHandle := _gui_CreateImage('provhud_uprising', elmSpotlightHandle, 'map.infopanel.uprising', 'halParentLeft', 'valParentTop', posX, posY+3, 22, 22, 0);
      [*] = ;            if not _map_CheckGenesisMode(gc_GM_ProvinceDetails) then
      [*] = ;               _gui_ft_AttachHint(elmHandle,'VVK.map.HintProvDetailsCallback',IntToStr(dummyUID)+',tooltip|map_infopanel_uprising_meter')
      [*] = ;            else
      [*] = ;               SetGUIElementHint(elmHandle, GetLocaleTableListItemByID('tooltip','map_infopanel_uprising_meter'));
      [*] = ;            SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;            SetGUIElementPressState(elmHandle, cEventState);
      [*] = ;            iconIndex := iconIndex+1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         iconCount := iconCount+1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // guard
      [*] = ;      if {(plHandle=GetPlayerHandleInterfaceIO) and} ((gProfile.provhudflags and gc_gui_provhudflag_guard) > 0) then
      [*] = ;      begin
      [*] = ;         var pProvDefender : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Defender');
      [*] = ;         var curDefenderID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;         if (curDefenderID<>0) then
      [*] = ;         begin
      [*] = ;            if (bDraw) then
      [*] = ;            begin
      [*] = ;               posX := (iconIndex*cIconOffset);
      [*] = ;               if (plHandle=GetPlayerHandleInterfaceIO) then
      [*] = ;               begin
      [*] = ;                  elmHandle := _gui_CreateImage('provhud_defender', elmSpotlightHandle, 'map.provhud.defender', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;                  SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;                  SetGUIElementHint(elmHandle, 'defender|'+IntToStr(curDefenderID)+'|256');
      [*] = ;                  SetGUIElementPressState(elmHandle, cEventState);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  elmHandle := _gui_CreateImage('provhud_defender', elmSpotlightHandle, 'map.provhud.enemydefender', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;                  SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;                  SetGUIElementHint(elmHandle, 'defender|'+IntToStr(curDefenderID)+'|256');
      [*] = ;                  SetGUIElementPressState(elmHandle, cEventState);
      [*] = ;               end;
      [*] = ;               iconIndex := iconIndex+1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            iconCount := iconCount+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // population limit
      [*] = ;      if (plHandle=GetPlayerHandleInterfaceIO) and ((gProfile.provhudflags and gc_gui_provhudflag_overpop) > 0) then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetGrow');
      [*] = ;         var provGrow : Integer = IntRegister0;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetLevel');
      [*] = ;         var oldLevel : Integer = IntRegister0;
      [*] = ;         IntRegister0 := oldLevel;
      [*] = ;         MapExecuteState('GetProvLevelParserByID');
      [*] = ;         var pProvLevel : Integer = IntRegister1;
      [*] = ;         var levelExplored : Integer = ParserGetIntValueByKeyByHandle(pProvLevel, 'Explored');
      [*] = ;         var bRooms : Boolean = False;
      [*] = ;         if (oldLevel<gc_MaxProvinceLevel) then
      [*] = ;         begin
      [*] = ;            if not ((provExplore>=levelExplored) or (provGrow<=0)) then
      [*] = ;            begin
      [*] = ;               if (bDraw) then
      [*] = ;               begin
      [*] = ;                  posX := (iconIndex*cIconOffset);
      [*] = ;                  elmHandle := _gui_CreateImage('provhud_poplimit', elmSpotlightHandle, 'map.provhud.noroom', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;                  SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;                  SetGUIElementHint(elmHandle, 'gui|702');
      [*] = ;                  SetGUIElementPressState(elmHandle, cEventState);
      [*] = ;                  iconIndex := iconIndex+1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               iconCount := iconCount+1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // sites : arenas, shops, lairs, temples
      [*] = ;      if (plHandle=GetPlayerHandleInterfaceIO()) then
      [*] = ;      begin
      [*] = ;         var pProvSites : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Sites');
      [*] = ;         var siteCount : Integer = 0;
      [*] = ;         var bArena, bShop, bLair, bTemple : Boolean = False;
      [*] = ;         var j : Integer;
      [*] = ;         for j:=0 to ParserGetCountByHandle(pProvSites)-1 do
      [*] = ;         begin
      [*] = ;            var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;            var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;            var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;            //var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;            //var guardID : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'GuardID');
      [*] = ;            //var pSites : Integer = gPrototypeData.sites.handle;
      [*] = ;            //var pSite : Integer = ParserSelectByHandleByIndex(pSites, siteID);
      [*] = ;            //var canEnter : Boolean = ParserGetBoolValueByKeyByHandle(pSite, 'CanEnter');
      [*] = ;
      [*] = ;            if (siteID>0) and (siteExplore <= provExplore) {and (not ((guardID = 0) and (not canEnter)))} then
      [*] = ;            begin
      [*] = ;               case siteID of
      [*] = ;                  32..40 : begin
      [*] = ;                     bShop := True;
      [*] = ;                     if (siteID=35) then
      [*] = ;                        bLair := True;
      [*] = ;                  end;
      [*] = ;                  41 : begin
      [*] = ;                     bArena := True;
      [*] = ;                  end;
      [*] = ;                  {35, }43, 44, 45 : bLair := True;
      [*] = ;                  27 : bTemple := True;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (bArena) and ((gProfile.provhudflags and gc_gui_provhudflag_arena) = 0) then
      [*] = ;            bArena := False;
      [*] = ;         if (bShop) and ((gProfile.provhudflags and gc_gui_provhudflag_shop) = 0) then
      [*] = ;            bShop := False;
      [*] = ;         if (bLair) and ((gProfile.provhudflags and gc_gui_provhudflag_lair) = 0) then
      [*] = ;            bLair := False;
      [*] = ;         if (bTemple) and ((gProfile.provhudflags and gc_gui_provhudflag_temple) = 0) then
      [*] = ;            bTemple := False;
      [*] = ;
      [*] = ;         for j:=0 to 3 do
      [*] = ;         begin
      [*] = ;            var elmName, matName, hint : String = '';
      [*] = ;            var bCheck : Boolean = False;
      [*] = ;            case j of
      [*] = ;               0 : begin
      [*] = ;                  elmName := 'provhud_arena';
      [*] = ;                  matName := 'map.provhud.arena';
      [*] = ;                  hint := 'gui|704';
      [*] = ;                  bCheck := bArena;
      [*] = ;               end;
      [*] = ;               1 : begin
      [*] = ;                  elmName := 'provhud_shop';
      [*] = ;                  matName := 'map.provhud.shops';
      [*] = ;                  hint := 'gui|703';
      [*] = ;                  bCheck := bShop;
      [*] = ;               end;
      [*] = ;               2 : begin
      [*] = ;                  elmName := 'provhud_lair';
      [*] = ;                  matName := 'map.provhud.lair';
      [*] = ;                  hint := 'gui|705';
      [*] = ;                  bCheck := bLair;
      [*] = ;               end;
      [*] = ;               3 : begin
      [*] = ;                  elmName := 'provhud_temple';
      [*] = ;                  matName := 'map.provhud.temple';
      [*] = ;                  hint := 'gui|706';
      [*] = ;                  bCheck := bTemple;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (bCheck) then
      [*] = ;            begin
      [*] = ;               if (bDraw) then
      [*] = ;               begin
      [*] = ;                  posX := (iconIndex*cIconOffset);
      [*] = ;                  elmHandle := _gui_CreateImage(elmName, elmSpotlightHandle, matName, 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;                  SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;                  SetGUIElementHint(elmHandle, hint);
      [*] = ;                  SetGUIElementPressState(elmHandle, cEventState);
      [*] = ;                  iconIndex := iconIndex+1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  iconCount := iconCount+1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         // siege
      [*] = ;         if under_siege <> 0 then
      [*] = ;         begin
      [*] = ;            if (bDraw) then
      [*] = ;            begin
      [*] = ;               posX := (iconIndex*cIconOffset);
      [*] = ;               elmHandle := _gui_CreateImage('provhud_siege', elmSpotlightHandle, 'map.provhud.siege.'+IntToStr(under_siege-1), 'halParentLeft', 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;               SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;               temp_str := StrReplace(GetLocaleTableListItemByID('tooltip', 'provhud_siege'),'%%',IntToStr(siege_turns));
      [*] = ;               SetGUIElementHint(elmHandle,temp_str);
      [*] = ;               iconIndex := iconIndex+1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               iconCount := iconCount+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gIntRegister_MapSelectedUID<>0) and ((gProfile.provhudflags and gc_gui_provhudflag_quest) > 0) then
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;         var heroParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;         var pQuests : Integer = ParserSelectByHandleByKey(heroParser, 'Quests');
      [*] = ;         var j : Integer;
      [*] = ;         for j:=0 to ParserGetCountByHandle(pQuests)-1 do
      [*] = ;         begin
      [*] = ;            var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, j);
      [*] = ;            var questComplete : Boolean = ParserGetBoolValueByKeyByHandle(pQuest, 'Complete');
      [*] = ;            var questProvIndex : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'ProvIndex');
      [*] = ;            if (provIndex=questProvIndex) then
      [*] = ;            begin
      [*] = ;               if (bDraw) then
      [*] = ;               begin
      [*] = ;                  posX := ((iconCount*cIconOffset) div 2);
      [*] = ;                  if (bHerb) then
      [*] = ;                  posY := -128
      [*] = ;                  else
      [*] = ;                  posY := -128+28;
      [*] = ;                  if bDrawResource or bDrawProvType then
      [*] = ;                  posY := posY-50;
      [*] = ;                  if (questComplete) then
      [*] = ;                  elmHandle := _gui_CreateImage('provhud_quests', elmSpotlightHandle, 'map.provhud.quest.done', 'halParentMiddle', 'valParentTop', posX, posY, round(0.75*GetGUITextureWidth('map.provhud.quest.done')), round(0.75*GetGUITextureHeight('map.provhud.quest.done')) 0)
      [*] = ;                  else
      [*] = ;                  elmHandle := _gui_CreateImage('provhud_quests', elmSpotlightHandle, 'map.provhud.quest.receaved', 'halParentMiddle', 'valParentTop', posX, posY, round(0.75*GetGUITextureWidth('map.provhud.quest.done')), round(0.75*GetGUITextureHeight('map.provhud.quest.done')), 0);
      [*] = ;               end;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if ((gProfile.provhudflags and gc_gui_provhudflag_name) > 0) and (ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType') > 0) then
      [*] = ;   begin
      [*] = ;      var pos : TRectangle;
      [*] = ;      var fontHandle,hint : String;
      [*] = ;
      [*] = ;      IntRegister0 := pStratHexCell;
      [*] = ;      MapExecuteState('map.GetProvinceName');
      [*] = ;      hint := StringRegister0;
      [*] = ;
      [*] = ;      const cDefaultOffSet = 16;
      [*] = ;      posY := cDefaultOffSet;
      [*] = ;
      [*] = ;      if bDrawResource or bDrawProvType then
      [*] = ;         posY := posY + 40;
      [*] = ;      
      [*] = ;      if iconIndex > 0 then
      [*] = ;         posY := posY + cIconSpaceHeight;
      [*] = ;      
      [*] = ;      if provLevelMarks > 0 then
      [*] = ;         posY := posY + cProvLevelSpaceHeight;
      [*] = ;
      [*] = ;     if posY = cDefaultOffSet then
      [*] = ;         posY := posY + 20;
      [*] = ;
      [*] = ;      var w, h : Integer;
      [*] = ;      _gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;      GetGUIElementFontTextFormatRect(fontHandle, hint, w, h);
      [*] = ;      _sys_FillRect(pos, 0, posY, w+10, h+10);
      [*] = ;      elmHandle := _gui_CreateScalableWindowExt_VVK('', elmMainHandle, gc_gui_align_parent_mt, pos, 'common_tooltip_dark', $50); 
      [*] = ;      var elmBkgHandle : Integer = GetGUIElementIndexByNameParent('background_tiles', elmHandle);
      [*] = ;      SetGUIElementUserBlend(elmBkgHandle, 0.7);
      [*] = ;      //elmHandle := _gui_CreateImage_VVK('',elmMainHandle,'misc.blank.black.alpha.1',gc_gui_align_parent_mt,pos);
      [*] = ;      //pos.pos.x := 0;
      [*] = ;      //pos.pos.y := 0;
      [*] = ;      elmHandle := _gui_CreateText_VVK('',elmMainHandle,hint,gc_gui_align_parent_mt,pos,gc_gui_align_middle,fontHandle,gc_gui_fontcolor_NormalWhite);
      [*] = ;   end;
      [*] = ;      
      [*] = ;   if provLevelMarks > 0 then
      [*] = ;   begin
      [*] = ;      posY := 12;
      [*] = ;      if bDrawResource or bDrawProvType then
      [*] = ;         posY := posY + 40;
      [*] = ;      
      [*] = ;      if iconIndex > 0 then
      [*] = ;         posY := posY + cIconSpaceHeight;
      [*] = ;
      [*] = ;      const cProvinceMarkOffset = 11;
      [*] = ;      posX := -((provLevelMarks*cProvinceMarkOffset) div 2) - 2;
      [*] = ;      
      [*] = ;      var elmLevel : Integer = _gui_CreateDummy('hud_prov_level', elmMainHandle, 'halParentLeft', 'valParentMiddle', posX, posY, 0, 0, 0);
      [*] = ;      
      [*] = ;      var markInd : Integer;
      [*] = ;      for markInd := 0 to provLevelMarks-1 do
      [*] = ;      begin
      [*] = ;         var extraPixels : Integer = markInd div 3;
      [*] = ;         elmHandle := _gui_CreateImage('map_infopanel_mark_'+IntToStr(provinceLevel), elmLevel, 'map.infopanel.growth.mark', gc_gui_align_parent_lt.h, gc_gui_align_parent_lt.v, 0 + markInd * cProvinceMarkOffset, -10 + (10 - extraPixels * 5), 12 + extraPixels * 4, 18 + extraPixels * 7, 0);
      [*] = ;         SetGUIAllowEvents(elmHandle, True, False, False); //hintbasis
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _console_GetIntVar('DebugShowExtraInfo') > 0 then
      [*] = ;begin
      [*] = ;   var pos : TRectangle;
      [*] = ;   var fontHandle,hint : String;
      [*] = ;
      [*] = ;   const cDefaultOffSet = 62;
      [*] = ;   posY := cDefaultOffSet;
      [*] = ;
      [*] = ;   if bDrawResource or bDrawProvType then
      [*] = ;      posY := posY + 24;
      [*] = ;      
      [*] = ;   if iconIndex > 0 then
      [*] = ;      posY := posY + cIconSpaceHeight;
      [*] = ;      
      [*] = ;   if provLevelMarks > 0 then
      [*] = ;      posY := posY + cProvLevelSpaceHeight;
      [*] = ;
      [*] = ;   if posY = cDefaultOffSet then
      [*] = ;      posY := posY + 20;
      [*] = ;      
      [*] = ;   var w,h : Integer;
      [*] = ;
      [*] = ;   hint := 'U:'+IntToStr(dummyUID)+',I:'+IntToStr(provIndex);
      [*] = ;   //hint := 'I:'+IntToStr(provIndex);
      [*] = ;   _gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_small,'',fontHandle);
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandle, hint, w, h);
      [*] = ;   _sys_FillRect(pos,0,posY,0,0);
      [*] = ;   _gui_CreateText_VVK('', elmMainHandle,hint,gc_gui_align_parent_mt,pos,gc_gui_align_middle,fontHandle,gc_gui_fontcolor_NormalWhite);
      [*] = ;end;
   struct.end
section.end

