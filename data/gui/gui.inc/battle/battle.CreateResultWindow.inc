section.begin
   Name = battle.CreateResultWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.CREATERESULTWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cItemWidth = 52;
      [*] = ;const cItemHeight = 52;
      [*] = ;const cItemOffset = 4;
      [*] = ;
      [*] = ;var plHndAttack : Integer = GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;var plHndDefend : Integer = GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;
      [*] = ;var elmImageHandle  : Integer;
      [*] = ;var elmBtnHandle    : Integer;
      [*] = ;var elmTextHandle   : Integer;
      [*] = ;var tag : Integer = 0;
      [*] = ;var posX, posY : Integer;
      [*] = ;var xOff, yOff : Integer;
      [*] = ;var sizeX, sizeY : Integer;
      [*] = ;var width, height : Integer;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElement('battle_results', _gui_GetLayerI(), 'halLeft', 'valTop', 0, 0, GetViewerWidth, GetViewerHeight, Tag);
      [*] = ;
      [*] = ;_gui_RootWindowAddM(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle,'EventQueryWindowModal');
      [*] = ;SetGUIElementVisible(elmParentHandle, true);
      [*] = ;
      [*] = ;//Background
      [*] = ;posX := 0;
      [*] = ;posY := 0;
      [*] = ;sizeX := 850;
      [*] = ;sizeY := 565;
      [*] = ;var elmBackgroundHandle : Integer = _gui_CreateImage('battle_results_background', elmParentHandle, 'battle.results', 'halParentMiddle', 'valParentMiddle'{'valBottomHeight'}, posX, posY, sizeX, sizeY, Tag);
      [*] = ;SetGUIAllowEvents(elmBackgroundHandle, true, false, false);
      [*] = ;
      [*] = ;var batRes : Integer;
      [*] = ;var mapPlHandle : Integer;
      [*] = ;
      [*] = ;MapExecuteState('bat.GetWinPlayerHandle');
      [*] = ;var winPlHandle : Integer = IntRegister0;
      [*] = ;var losePlHandle : Integer = IntRegister1;
      [*] = ;if BoolRegister0 then
      [*] = ;   batRes := 1
      [*] = ;else
      [*] = ;begin
      [*] = ;   if BoolRegister1 then
      [*] = ;      batRes := -1
      [*] = ;   else
      [*] = ;      batRes := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;//Header Main
      [*] = ;var fontHandleH1, fontHandleH2, fontHandleL, fontHandleN : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_largest,'',fontHandleH1);
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_large,'',fontHandleH2);
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'LevelValue',gc_gui_fontsize_default,'',fontHandleL);
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Numbers',gc_gui_fontsize_default,'',fontHandleN);
      [*] = ;var text : String = '';
      [*] = ;
      [*] = ;if batRes <> 0 then
      [*] = ;begin
      [*] = ;   PlayerExecuteStateByHandle(winPlHandle, 'GetMapPlayerHandle');
      [*] = ;   mapPlHandle := IntRegister0;
      [*] = ;   PlayerExecuteStateByHandle(losePlHandle, 'GetMapPlayerHandle');
      [*] = ;   var loseMapPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   if (gGame.gameType = gc_GameTypeHotSeatBattle) or SameText(GetPlayerControlModeByHandle(loseMapPlHandle), 'cmPC') then
      [*] = ;      batRes := 1
      [*] = ;   else
      [*] = ;   if GetPlayerIndexByHandle(mapPlHandle) = gIntRegister_MapMyPlayerIndex then
      [*] = ;   begin
      [*] = ;      if GetPlayerIndexByHandle(loseMapPlHandle) <> gIntRegister_MapMyPlayerIndex then
      [*] = ;         batRes := 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      batRes := -1;
      [*] = ;end;
      [*] = ;if _log then _Log_values('WIN_HANDLE|MAP_WIN_HANDLE|RESULT|ATTACK_M|DEFEND_M',winPlHandle,mapPlHandle,batRes,gIntRegister_BattleAttackPlayer,gIntRegister_BattleDefendPlayer,0);
      [*] = ;
      [*] = ;case batRes of
      [*] = ;   0 : begin
      [*] = ;      text := GetLocaleTableListItemByID('gui', '49')
      [*] = ;   end;
      [*] = ;   1 : begin
      [*] = ;      text := GetLocaleTableListItemByID('gui', '22');
      [*] = ;      _gui_PlaySound('interface', 'victory');
      [*] = ;   end;
      [*] = ;   -1: begin
      [*] = ;      text := GetLocaleTableListItemByID('gui', '23');
      [*] = ;      _gui_PlaySound('interface', 'defeat');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// achievements
      [*] = ;if batRes = 1 then
      [*] = ;begin
      [*] = ;   var af : Integer = GetPlayerIntValueByHandle(mapPlHandle,gc_map_PLStack_MapUnit_nAchievemntsFlags);
      [*] = ;   _achievement_Trigger(gc_achiev_tactical_battle_won,'');
      [*] = ;   //_log_Values('AF',af,0,0,0,0,0);
      [*] = ;   if ((af and 1) <> 0) then
      [*] = ;      _achievement_Trigger(gc_achiev_shop_captured,'');
      [*] = ;   af := (af and $fffffffe);
      [*] = ;   SetPlayerIntValueByHandle(mapPlHandle, gc_map_PLStack_MapUnit_nAchievemntsFlags, af);
      [*] = ;end;
      [*] = ;//
      [*] = ;posX := 425;
      [*] = ;posY := 48;
      [*] = ;GetGUIElementFontTextFormatRect(fontHandleH1, text, width, height);
      [*] = ;width := width+40;
      [*] = ;height := height+10;
      [*] = ;elmTextHandle := _gui_CreateText('battle_result_header', elmBackgroundHandle, text, 'halParentLeft', 'valParentTop', posX-(width div 2), posY-(height div 2), width, height, 'halMiddle', 'valMiddle', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;//Header Left
      [*] = ;text := GetLocaleTableListItemByID('gui', '18');
      [*] = ;posX := 75;
      [*] = ;posY := 90;
      [*] = ;elmTextHandle := _gui_CreateText('battle_result_strip_yourparty', elmBackgroundHandle, text, 'halParentLeft', 'valParentTop', posX, posY+2, 230, 35, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;//Header Right
      [*] = ;text := GetLocaleTableListItemByID('gui', '19');
      [*] = ;posX := 654;
      [*] = ;posY := 107;
      [*] = ;elmTextHandle := _gui_CreateText('battle_result_strip_enemyparty', elmBackgroundHandle, text, 'halParentLeft', 'valParentTop', posX, posY+2, 0, 0, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;//Header Middle small
      [*] = ;text := GetLocaleTableListItemByID('gui', '20');
      [*] = ;posX := 425;
      [*] = ;posY := 146;
      [*] = ;elmTextHandle := _gui_CreateText('battle_result_strip_loot', elmBackgroundHandle, text, 'halParentLeft', 'valParentTop', posX, posY+2, 0, 0, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;
      [*] = ;//Left & Right army block
      [*] = ;var elmIconHandle : Integer;
      [*] = ;var armyXOffset : Integer;
      [*] = ;var ind : Integer;
      [*] = ;
      [*] = ;function FillPlayerArmy(plHandle, side : Integer) : Integer; // &1-  hero survived and at least one unit was dead, &2 - if dragon was slain
      [*] = ;begin
      [*] = ;   if (side=0) then
      [*] = ;      armyXOffset := 0
      [*] = ;   else
      [*] = ;      armyXOffset := 462;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   var ind : Integer = -1;
      [*] = ;   var hero_alive : Boolean = false;
      [*] = ;   var units_dead : Integer = 0;
      [*] = ;   var units_alive : Integer = 0;
      [*] = ;   var res : Integer = 0;
      [*] = ;   var dragon_slain : Boolean = false;
      [*] = ;
      [*] = ;   for i := 0 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      var isHero : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bIsHero);
      [*] = ;      var unitID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;      var heroUID : Integer = 0;
      [*] = ;      var heroHandle : Integer = 0;
      [*] = ;      if (isHero) then
      [*] = ;      begin
      [*] = ;         heroUID := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iHeroUID);
      [*] = ;         heroHandle := GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var isSummoned : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bSummoned);
      [*] = ;      if isSummoned or (unitID = gc_unit_type_spideregg) then
      [*] = ;         continue;
      [*] = ;
      [*] = ;      ind := ind + 1;
      [*] = ;      var j,k : Integer = 0;
      [*] = ;      k := ind;
      [*] = ;      if ind>=12 then
      [*] = ;      begin
      [*] = ;         j := 3;
      [*] = ;         k := ind-12;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if ind>=8 then
      [*] = ;      begin
      [*] = ;         j := 2;
      [*] = ;         k := ind-8;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if ind>=4 then
      [*] = ;      begin
      [*] = ;         j := 1;
      [*] = ;         k := ind-4;
      [*] = ;      end;
      [*] = ;
      [*] = ;      posX := 43+armyXOffset;
      [*] = ;      posY := 120;
      [*] = ;      xOff := 74*k;
      [*] = ;      yOff := 97*j;
      [*] = ;
      [*] = ;      //Icon image
      [*] = ;      sizeX := 70+16;
      [*] = ;      sizeY := 93+16;
      [*] = ;      elmIconHandle := _gui_CreateImage('', elmBackgroundHandle, 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', posX+xOff, posY+yOff, sizeX, sizeY, Tag);
      [*] = ;      posX := 6;
      [*] = ;      posY := 9;
      [*] = ;      sizeX := 0;
      [*] = ;      sizeY := 0;
      [*] = ;
      [*] = ;      var iconName : String = 'icon.unit.'+IntToStr(unitID);
      [*] = ;      if (isHero) then
      [*] = ;      begin
      [*] = ;         var portrait : String = ParserGetValueByKeyByHandle(ParserSelectGameObject(heroHandle),'Portrait');
      [*] = ;         if (portrait<>'') then
      [*] = ;            iconName := StrReplace(portrait,'map.hero.portrait.','info.portrait.');
      [*] = ;      end;
      [*] = ;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmIconHandle, iconName, 'halParentLeft', 'valParentTop', posX, posY, sizeX, sizeY, Tag);
      [*] = ;      {//Medal icon
      [*] = ;      posX := 2;
      [*] = ;      posY := 75;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmIconHandle, 'unitpanel.medal.1', 'halParentLeft', 'valParentTop', posX, posY, 21, 27, Tag);}
      [*] = ;      //Death mask
      [*] = ;      var isDead : Boolean = (GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife) <= 0);
      [*] = ;      if isDead then
      [*] = ;      begin
      [*] = ;         units_dead := units_dead + 1;
      [*] = ;         posX := 0;
      [*] = ;         posY := 0;
      [*] = ;         sizeX := 81;
      [*] = ;         sizeY := 108;
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmIconHandle, 'misc.blank.black.alpha.1', 'halParentLeft', 'valParentTop', posX+7, posY+10, 70, 93, Tag);
      [*] = ;         SetGUIElementUserBlend(elmImageHandle, 0.55);
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmIconHandle, 'battle.results.dead', 'halParentLeft', 'valParentTop', posX, posY, sizeX, sizeY, Tag);
      [*] = ;         if unitID = 60 then // !!!
      [*] = ;            dragon_slain := true;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if isHero then
      [*] = ;            hero_alive := true
      [*] = ;         else
      [*] = ;            units_alive := units_alive + 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //Icon button
      [*] = ;      posX := 6;
      [*] = ;      posY := 9;
      [*] = ;      //tag := 16 * GetPlayerIndexByHandle(plHandle) + i;
      [*] = ;      elmBtnHandle := _gui_CreateButton('', elmIconHandle, '', 'heropanel.unit.slot.cover', 'halParentLeft', 'valParentTop', posX, posY, 70, 93, '', '', 0);
      [*] = ;      _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipUnit',cFT_UnitBattle,GetGameObjectUniqueIdByHandle(GetGameObjectHandleByIndex(i,plHandle)),0,0,'4','4'); // right button - battle mode
      [*] = ;
      [*] = ;      //Life meter
      [*] = ;      posX := 7+1;
      [*] = ;      posY := -28;
      [*] = ;      IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := gc_battle_unit_iCurLife;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      var curLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;      sizeX := 3;
      [*] = ;      sizeY := round(70*(curLife/maxLife));
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmIconHandle, 'battle.results.meter.life', 'halParentLeft', 'valParentBottomHeight', posX, posY, sizeX, sizeY, Tag);
      [*] = ;      if (sizeY=0) then
      [*] = ;      SetGUIElementVisible(elmImageHandle, False);
      [*] = ;      elmImageHandle := _gui_CreateImage('battle_result_unit_life_meter', elmIconHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', posX-1, posY, sizeX+2, sizeY, Tag);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;
      [*] = ;      var unitLevel : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLevel);
      [*] = ;      var minExp : Integer = 0;
      [*] = ;      var maxExp : Integer = 0;
      [*] = ;
      [*] = ;      if isHero then
      [*] = ;      begin
      [*] = ;         if heroHandle <> 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := unitLevel;
      [*] = ;            GameObjectExecuteStateByHandle(heroHandle ,'GetNeededExpForLevel');
      [*] = ;            minExp := IntRegister1;
      [*] = ;
      [*] = ;            IntRegister0 := unitLevel+1;
      [*] = ;            GameObjectExecuteStateByHandle(heroHandle ,'GetNeededExpForLevel');
      [*] = ;            maxExp := IntRegister1;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := unitID;
      [*] = ;         IntRegister1 := unitLevel;
      [*] = ;         MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;         minExp := IntRegister2;
      [*] = ;
      [*] = ;         IntRegister0 := unitID;
      [*] = ;         IntRegister1 := unitLevel+1;
      [*] = ;         MapExecuteState('GetUnitNeededExpForLevel');
      [*] = ;         maxExp := IntRegister2;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var curExp : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iExperience);
      [*] = ;      if (curExp>maxExp) then
      [*] = ;         curExp := maxExp;
      [*] = ;      var expPerc : Float = (curExp-minExp)/(maxExp-minExp);
      [*] = ;
      [*] = ;      //Exp meter
      [*] = ;      posX := 72-1;
      [*] = ;      posY := -28;
      [*] = ;      sizeX := 3;
      [*] = ;      sizeY := round(70*expPerc);
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmIconHandle, 'battle.results.meter.exp', 'halParentLeft', 'valParentBottomHeight', posX, posY, sizeX, sizeY, Tag);
      [*] = ;      if (sizeY<=0) then
      [*] = ;         SetGUIElementVisible(elmImageHandle, False);
      [*] = ;      elmImageHandle := _gui_CreateImage('battle_result_unit_exp_meter', elmIconHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentBottomHeight', posX-1, posY, sizeX+2, sizeY, Tag);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;      //Meters background
      [*] = ;      posX := -1+5;
      [*] = ;      posY := 2+6;
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmIconHandle, 'battle.results.meter.background.enemy', 'halParentLeft', 'valParentTop', posX, posY, 0, 0, Tag);
      [*] = ;      SetGUIAllowEvents(elmImageHandle, False, False, False);
      [*] = ;
      [*] = ;      //Unit level
      [*] = ;      text := IntToStr(unitLevel);
      [*] = ;      posX := 54-1;
      [*] = ;      posY := 85-4;
      [*] = ;      elmTextHandle := _gui_CreateText('battle_result_unit_level', elmIconHandle, text, 'halParentLeft', 'valParentTop', posX-3, posY-3, 22, 22, 'halMiddle', 'valMiddle', fontHandleL, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;      SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;   end;
      [*] = ;   if (hero_alive) and (units_dead > 0) and (units_alive=0) then
      [*] = ;      res := 1
      [*] = ;   else
      [*] = ;      res := 0;
      [*] = ;   if dragon_slain then
      [*] = ;      res := res or 2;
      [*] = ;   Result := res;
      [*] = ;end;
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(plHndAttack, 'GetMapPlayerHandle');
      [*] = ;var mapAttPlHandle : Integer = IntRegister0;
      [*] = ;var ba1,ba2: Integer;
      [*] = ;
      [*] = ;//if (plHndAttack=GetPlayerHandleInterfaceIO) then
      [*] = ;if GetPlayerIndexByHandle(mapAttPlHandle) = gIntRegister_MapMyPlayerIndex then
      [*] = ;begin
      [*] = ;   ba1 := FillPlayerArmy(plHndAttack, 0);
      [*] = ;   ba2 := FillPlayerArmy(plHndDefend, 1);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   ba2 := FillPlayerArmy(plHndAttack, 1);
      [*] = ;   ba1 := FillPlayerArmy(plHndDefend, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;// achievements
      [*] = ;if ((ba1 and 1) <> 0) then
      [*] = ;   _achievement_Trigger(gc_achiev_battle_hero_left_alone,'');
      [*] = ;if ((ba2 and 2) <> 0) then
      [*] = ;   _achievement_Trigger(gc_achiev_dragon_slain,'');
      [*] = ;//
      [*] = ;//Trophy Gold | Crystals
      [*] = ;var GoldTrophy : Integer = 0;
      [*] = ;var GemTrophy : Integer = 0;
      [*] = ;var heroParser : Integer = 0;
      [*] = ;
      [*] = ;if winPlHandle <> 0 then
      [*] = ;begin
      [*] = ;   PlayerExecuteStateByHandle(winPlHandle, 'GetHeroHandle');
      [*] = ;   var winHeroHandle : Integer = IntRegister0;
      [*] = ;   heroParser := ParserSelectGameObject(winHeroHandle);
      [*] = ;
      [*] = ;   GoldTrophy := ParserGetIntValueByKeyByHandle(heroParser, 'BattleGold');
      [*] = ;   GemTrophy := ParserGetIntValueByKeyByHandle(heroParser, 'BattleGem');
      [*] = ;end;
      [*] = ;
      [*] = ;//if GoldTrophy > 0 then
      [*] = ;//begin
      [*] = ;   posX := 369;
      [*] = ;   posY := 289;
      [*] = ;   xOff := 43;
      [*] = ;   elmImageHandle := _gui_CreateImage('battle_result_loot_gold', elmBackgroundHandle, 'map.infopanel.gold', 'halParentLeft', 'valParentTop', posX, posY, 42, 42, Tag);
      [*] = ;   if (GoldTrophy=0) then
      [*] = ;   begin
      [*] = ;      text := '';
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.1);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   text := IntToStr(GoldTrophy);
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandleN, text, width, height);
      [*] = ;   elmTextHandle := _gui_CreateText('battle_result_loot_gold', elmBackgroundHandle, text, 'halParentLeft', 'valParentTop', posX+xOff-40, posY+7-8, width+44, 42, 'halLeft', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;   SetGUIElementTextAlign(elmTextHandle, 'halLeft', 'valMiddle', 40, 0);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;//end;
      [*] = ;//if GemTrophy > 0 then
      [*] = ;//begin
      [*] = ;   posX := 366;
      [*] = ;   posY := 337;
      [*] = ;   xOff := 45;
      [*] = ;   elmImageHandle := _gui_CreateImage('battle_result_loot_gem', elmBackgroundHandle, 'map.infopanel.crystals', 'halParentLeft', 'valParentTop', posX, posY, 42, 42, Tag);
      [*] = ;   if (GemTrophy=0) then
      [*] = ;   begin
      [*] = ;      text := '';
      [*] = ;      SetGUIElementUserBlend(elmImageHandle, 0.1);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   text := IntToStr(GemTrophy);
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandleN, text, width, height);
      [*] = ;   elmTextHandle := _gui_CreateText('battle_result_loot_gem', elmBackgroundHandle, text, 'halParentLeft', 'valParentTop', posX+xOff-40, posY+7-8, width+44, 42, 'halLeft', 'valMiddle', fontHandleN, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;   SetGUIElementTextAlign(elmTextHandle, 'halLeft', 'valMiddle', 40, 0);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;//end;
      [*] = ;
      [*] = ;//Trophy Items
      [*] = ;if heroParser <> 0 then
      [*] = ;begin
      [*] = ;   var pBattleItems : Integer = ParserSelectByHandleByKey(heroParser, 'BattleLootItems');
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pBattleItems)-1 do
      [*] = ;   begin
      [*] = ;      var pBattleItem : Integer = ParserSelectByHandleByIndex(pBattleItems, i);
      [*] = ;      var itemID : Integer = ParserGetIntValueByKeyByHandle(pBattleItem, 'ItemID');
      [*] = ;
      [*] = ;      if (itemID>0) then
      [*] = ;      begin
      [*] = ;         var x : Integer = i mod 2;
      [*] = ;         var y : Integer = i div 2;
      [*] = ;
      [*] = ;         posX := 371 + x * (cItemWidth + cItemOffset);
      [*] = ;         posY := 170 + y * (cItemHeight + cItemOffset);
      [*] = ;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         var pItem : Integer = IntRegister1;
      [*] = ;         var itemDurability : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;         //var hint : String = 'itemhint%|'+IntToStr(itemID)+'|'+IntToStr(3)+'|'+IntToStr(itemDurability);
      [*] = ;         var hint : String;
      [*] = ;         var iconName : String;
      [*] = ;         _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;         elmImageHandle := _gui_CreateImage('battle_result_loot_item', elmBackgroundHandle, iconName, 'halParentLeft', 'valParentTop', posX, posY, cItemWidth, cItemHeight, 0);
      [*] = ;         elmBtnHandle := _gui_CreateButton('', elmImageHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', 0);
      [*] = ;         _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBase,itemDurability,cFT_ItemHeroDefault,'4','4');
      [*] = ;         //SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.cover.hover', 0, 0, 0, 0, 1, 0.5, 0.5, 0.5, 1);
      [*] = ;         //SetGUIElementVisibleProperties(elmBtnHandle, 'DownProperty', 'heropanel.icon.52x52.slot.cover.hover',  0, 0, 0, 0, 1, 0.5, 0.5, 0.5, 1);
      [*] = ;         //SetGUIElementStringTag(elmBtnHandle, 'Item');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//Accept button
      [*] = ;begin
      [*] = ;   var button : String;
      [*] = ;   var pos : TRectangle;
      [*] = ;
      [*] = ;   button := 'map.radialhero.btn.move.cancel';
      [*] = ;   const cAcceptBtnTag = 10001;
      [*] = ;   _sys_FillRect(pos,402,-1*(58),0,0);
      [*] = ;   _gui_CreateButton_VVK('',elmBackgroundHandle,'',button,gc_gui_align_parent_lb,pos,'battle.EventResultWindow','menu|47',cAcceptBtnTag);
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;if gIntRegister_TutorialCurrentHint <> 0 then
      [*] = ;   GUIExecuteState('DestroyTutorial');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

