section.begin
   Name = ToolQueryWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\TOOLQUERYWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cAstralTemplateName = 'query_dialog_style_astral';
      [*] = ;const cStrategyTemplateName = 'query_dialog_style_map';
      [*] = ;const cHintTemplateName = 'query_dialog_hint';
      [*] = ;const cAnswersTemplateName = 'query_dialog_answers';
      [*] = ;const cRewardsTemplateName = 'query_dialog_rewards';
      [*] = ;
      [*] = ;const cWindowName = 'queryWindow';
      [*] = ;
      [*] = ;const cLeftFrame = $1e;
      [*] = ;const cPortrait = $1d;
      [*] = ;const cLowerFrameOffset = $1c;
      [*] = ;const cUpperFrameOffset = $1b;
      [*] = ;const cRightFrameOffset = $1a;
      [*] = ;const cTextMinArea = $19;
      [*] = ;const cAdvicePos = $18;
      [*] = ;const cAnswersYPos_XOffs = $17;
      [*] = ;const cLeftFrameOffset = $16;
      [*] = ;const cBottomScreenOffset = $15;
      [*] = ;const cTextArea = $1;
      [*] = ;
      [*] = ;const cLeftCornerA = $1e;
      [*] = ;const cRightCornerA = $1d;
      [*] = ;const cBottomFrameA = $1c;
      [*] = ;const cLeftFrameA = $1b;
      [*] = ;const cRightFrameA = $1a;
      [*] = ;const cHoverAreaA = $19;
      [*] = ;const cTextAreaA = $3;
      [*] = ;
      [*] = ;const cMouseCursor = 'crHand';
      [*] = ;const cMouseCursorHoverIndex = 6; // !!
      [*] = ;const cMouseCursorDisabledIndex = 1; // !!
      [*] = ;const cMouseCursorItemHoverIndex = 1; // !!
      [*] = ;const cEventHandler = 'EventQueryWindow';
      [*] = ;const cEventHandlerStrategy = 'map.EventQueryWindow';
      [*] = ;const cEventModalQuery = 'EventQueryWindowModal';
      [*] = ;
      [*] = ;const cMaxAnswers = $20;
      [*] = ;const cMaxAnswersLines = $5;
      [*] = ;
      [*] = ;type InterfaceQueryAnswer = class
      [*] = ;   text : String;
      [*] = ;   tooltip : String;
      [*] = ;   tag : Integer;
      [*] = ;   id : String;
      [*] = ;   enabled : Boolean;
      [*] = ;   visible : Boolean;
      [*] = ;end;
      [*] = ;
      [*] = ;// 0-astral, 1-map
      [*] = ;function GetQueryStyle(query_style_str : String) : Integer;
      [*] = ;begin
      [*] = ;   if (query_style_str = '3') or (query_style_str = '5') or (query_style_str = '6') then
      [*] = ;      Result := 0
      [*] = ;   else
      [*] = ;      Result := 1;
      [*] = ;end;
      [*] = ;
      [*] = ;// astral level variables and functions
      [*] = ;function isCampaignEvent(eventID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if (eventID >= gc_query_CampEventMinIndex) and (eventID <= gc_query_CampEventMaxIndex) then
      [*] = ;      Result := true
      [*] = ;   else
      [*] = ;      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure st_RetrievePlayerHandles(var ph: Integer; var gh: Integer);
      [*] = ;begin
      [*] = ;   if gIntRegister_MapActiveHeroHandle <> 0 then
      [*] = ;   begin
      [*] = ;      gh := gIntRegister_MapActiveHeroHandle;
      [*] = ;      ph := GetGameObjectPlayerHandleByHandle(gh);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ph := _gv_GetCurrentPlayerHandle();
      [*] = ;      gh := GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, ph);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function st_RetrieveCastleParser(ph: Integer) : Integer;
      [*] = ;begin
      [*] = ;   if ph <> 0 then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(ph, 'GetCastleParser');
      [*] = ;      Result := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(IntRegister0, 'DummyUID'));
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;function isStrategyGameMode : Boolean;
      [*] = ;begin
      [*] = ;   if ((gIntRegister_CurGameMode = gc_GameModeStrategy) or (gIntRegister_CurGameMode = gc_GameModeTactics)) then
      [*] = ;      Result := True
      [*] = ;   else
      [*] = ;      Result := False;
      [*] = ;end;
      [*] = ;
      [*] = ;var event_type : Integer; // 0- no special event, 1 - event, 2 - encounter
      [*] = ;var answers_handle,answers_dy: Integer;
      [*] = ;var rewards_handle : Integer;
      [*] = ;var scroll_handle : Integer;
      [*] = ;var text_handle : Integer;
      [*] = ;var windowHandle : Integer;
      [*] = ;
      [*] = ;var txt_pos,pos : TRectangle;
      [*] = ;var scroll_canvas_size : TElementSize;
      [*] = ;
      [*] = ;var if_handle,if_answers_handle : Integer;
      [*] = ;var window_d,window_a_d,text_d,elem_d,elem2_d,elem_u_d,elem_l_d,elem_r_d : TInterfaceElementData;
      [*] = ;
      [*] = ;var queryID : String = GetValueByName('queryID');
      [*] = ;var bVisible : Boolean = False;
      [*] = ;
      [*] = ;var queryHandle : Integer = 0;
      [*] = ;var queryText : String = '';
      [*] = ;var queryIcon : String = '';
      [*] = ;var queryStyle : String = '';
      [*] = ;var resultsHandle : Integer = 0;
      [*] = ;var countResults : Integer = 0;
      [*] = ;var answers : array [0..cMaxAnswers] of InterfaceQueryAnswer;
      [*] = ;var i,j,no,ypos,w,h,rhd,lhd : Integer;
      [*] = ;var result_visible, result_enabled : Boolean;
      [*] = ;var phd1,phd2,param1,param2 : Integer;
      [*] = ;var query_id : Integer;
      [*] = ;var text,window_name : String;
      [*] = ;var max_w,max_h,answers_width,answers_text_width,tw,th : Integer;
      [*] = ;var plHandle, goHandle : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;st_RetrievePlayerHandles(plHandle, goHandle);
      [*] = ;
      [*] = ;if (queryID<>'') then
      [*] = ;   queryHandle := QueryMachineCustomQueryCreate(queryID)
      [*] = ;else
      [*] = ;   queryHandle := 0;
      [*] = ;
      [*] = ;query_id := StrToInt(queryID);
      [*] = ;
      [*] = ;if _log then _log_Gui('QueryID = '+queryID+', handle = '+IntToStr(queryHandle)+', game mode = '+IntToStr(gIntRegister_CurGameMode)+', player name = '+GetPlayerNameByHandle(plHandle));
      [*] = ;LogI(_log_name+' QueryID = ' + queryID);
      [*] = ;
      [*] = ;if (not isStrategyGameMode()) then
      [*] = ;begin
      [*] = ;   QueryMachineQueryDoCreateExecute(queryHandle); // returns new query id and force close flag in registers
      [*] = ;
      [*] = ;   if isCampaignEvent(query_id) then
      [*] = ;   begin
      [*] = ;      if BoolRegister0 then
      [*] = ;         queryHandle := 0;
      [*] = ;      if StringRegister0 <> '' then // redirect
      [*] = ;      begin
      [*] = ;         queryID := StringRegister0;
      [*] = ;         LogI(_log_name+' Campaign redirection to: '+queryID);
      [*] = ;
      [*] = ;         QueryMachineCustomQueriesClear;
      [*] = ;         queryHandle := QueryMachineCustomQueryCreate(queryID);
      [*] = ;         StateMachineSetIntValueByName(QueryMachineGetStateMachineHandle, 'CurrentQuestionPage', 0);
      [*] = ;         countResults := QueryMachineResultsCount(QueryMachineQueryGetResults(queryHandle));
      [*] = ;
      [*] = ;         if (countResults = 0) then
      [*] = ;         begin
      [*] = ;            queryHandle := 0;
      [*] = ;            SetGUIValue('QueryID', '');
      [*] = ;         end;
      [*] = ;
      [*] = ;         GUIExecuteState('RequestQueryWindow');
      [*] = ;         _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if queryHandle <> 0 then
      [*] = ;begin
      [*] = ;   queryText := QueryMachineQueryGetKey(queryHandle);
      [*] = ;   if (queryText='0') then
      [*] = ;      queryHandle := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;windowHandle := _gui_GetWindow(cWindowName);
      [*] = ;
      [*] = ;//if gIntRegister_CurGameMode = gc_GameModeAstral then
      [*] = ;gIntRegister_CurQueryHandle := queryHandle;
      [*] = ;
      [*] = ;if queryHandle = 0 then
      [*] = ;begin
      [*] = ;   if (windowHandle<>0) then
      [*] = ;      _gui_RootWindowRemoveWithFade(windowHandle,0);
      [*] = ;   SetBoolValueByName('queryWindowVisible', false);
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;resultsHandle := QueryMachineQueryGetResults(queryHandle);
      [*] = ;countResults := QueryMachineResultsCount(resultsHandle);
      [*] = ;
      [*] = ;queryText := '';
      [*] = ;query_id := StrToInt(QueryID);
      [*] = ;case query_id of
      [*] = ;   gc_gui_query_heroEnemyAttackProvince : begin
      [*] = ;      var provPlHandle,pProvince: Integer;
      [*] = ;      var tUID : Integer;
      [*] = ;
      [*] = ;      IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;      MapExecuteState('GetProvinceParserByUID');
      [*] = ;
      [*] = ;      pProvince := IntRegister1;
      [*] = ;      provPlHandle := GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player'));
      [*] = ;
      [*] = ;      if (provPlHandle = GetPlayerHandleInterfaceIO()) then
      [*] = ;      begin
      [*] = ;         var pGOParser : Integer;
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;
      [*] = ;         pGOParser := ParserSelectGameObject(goHandle);
      [*] = ;
      [*] = ;         IntRegister0 := pGOParser;
      [*] = ;         IntRegister1 := goHandle;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerArmy');
      [*] = ;
      [*] = ;         //var pOwnerArmy : Integer = IntRegister2;
      [*] = ;         //var heroHandle : Integer = IntRegister3;
      [*] = ;         //var count : Integer = IntRegister4;
      [*] = ;         var isGarrison : Boolean = BoolRegister0;
      [*] = ;         //var pArmyUnits : Integer = ParserSelectByHandleByKey(pOwnerArmy, 'Units');
      [*] = ;         //var armyCount : Integer = ParserGetCountByHandle(pArmyUnits);
      [*] = ;
      [*] = ;         gIntRegister_BattleAttackArmy := pGOParser;
      [*] = ;         gIntRegister_BattleAttackHeroHandle := goHandle;
      [*] = ;         gIntRegister_BattleAttackPlayer := plHandle;
      [*] = ;
      [*] = ;         var enCMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;         if isGarrison and SameText(enCMode, 'cmPC') then
      [*] = ;         begin
      [*] = ;            var nextQueryID : String = IntToStr(gc_gui_query_playerEnemyStartSiege);
      [*] = ;            var resultHandle : Integer;
      [*] = ;
      [*] = ;            for i := 0 to countResults-1 do
      [*] = ;            begin
      [*] = ;               resultHandle := QueryMachineResultsGetByIndex(resultsHandle, i);
      [*] = ;               QueryMachineResultSetOnSelect(resultHandle, '');
      [*] = ;               QueryMachineResultSetNextQuery(resultHandle, nextQueryID);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_gui_query_heroAttackProvDefender : begin
      [*] = ;      if gBoolRegister_QueryBribeGuard then
      [*] = ;      begin
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         if plGold >= gIntRegister_GoldCost then
      [*] = ;            QueryMachineResultSetVisible(QueryMachineResultsGetByIndex(resultsHandle, 2), true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   else begin
      [*] = ;      if goHandle <> 0 then
      [*] = ;      begin
      [*] = ;         if ((query_id > gc_query_GuardMinIndex) and (query_id <= gc_query_GuardMaxIndex)) or
      [*] = ;         ((query_id > gc_query_SiteMinIndex) and (query_id <= gc_query_SiteMaxIndex)) or
      [*] = ;         (query_id = gc_gui_query_heroAttackProvDefender) or
      [*] = ;         (query_id = gc_gui_query_heroAttackProvEnemyHero) or
      [*] = ;         (query_id = gc_gui_query_heroAttackSiegePlayer) or
      [*] = ;         (query_id = gc_gui_query_heroAttackSiegeRebel) then
      [*] = ;         begin
      [*] = ;            var skill : Integer;
      [*] = ;
      [*] = ;            IntRegister0 := gc_skill_scouting;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetSkillLevel');
      [*] = ;            skill := IntRegister1;
      [*] = ;
      [*] = ;            if skill > 0 then
      [*] = ;            begin
      [*] = ;               if skill >= 5 then
      [*] = ;                  gIntRegister_GoldCost := gc_ScoutingPrice div 2
      [*] = ;               else
      [*] = ;                  gIntRegister_GoldCost := gc_ScoutingPrice;
      [*] = ;
      [*] = ;               if gBoolRegister_IsQueryScout then
      [*] = ;               begin
      [*] = ;                  var pDefendUnits : Integer = ParserSelectByHandleByKey(gIntRegister_BattleDefendArmy, 'Units');
      [*] = ;
      [*] = ;                  gBoolRegister_IsQueryScout := false;
      [*] = ;                  IntRegister0 := pDefendUnits;
      [*] = ;                  MapExecuteState('map.GetArmyFullUnitsList');
      [*] = ;                  queryText := StringRegister0;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var resultHandle : Integer = QueryMachineResultsGetByIndex(resultsHandle, countResults-1);
      [*] = ;                  var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;
      [*] = ;                  if plGold < gIntRegister_GoldCost then
      [*] = ;                     QueryMachineResultSetVisible(resultHandle, false)
      [*] = ;                  else
      [*] = ;                     QueryMachineResultSetVisible(resultHandle, true);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var queryIDCut : Integer = StrToInt(SubStr(QueryID, 0, 5));
      [*] = ;if (queryIDCut >= 16100) and (queryIDCut < 17000) then  // diplomacy messages between players
      [*] = ;begin
      [*] = ;   if (gIntRegister_DiplomacyWindowMode > 0) and (gIntRegister_DiplomacyActivePlayerID >= 0) then // process differently when message received during open diplomacy window
      [*] = ;   begin
      [*] = ;      // temporarily remove blinking from diplomacy window buttons as they're distrubingly rendered on top of the query window.
      [*] = ;      var placeHolder : Boolean;
      [*] = ;      _gui_RemoveBlinkElement('btnPlayerOffer', placeHolder);
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;         _gui_RemoveBlinkElement('btnDiplomacyPlayer_'+IntToStr(i), placeHolder);
      [*] = ;
      [*] = ;      if (countResults > 1) then // add a "let me think about it" option on proposals.
      [*] = ;      begin
	  [*] = ;         var resultHandle : Integer = QueryMachineResultsAdd(resultsHandle);
      [*] = ;         QueryMachineResultSetOnSelect(resultHandle, '');
      [*] = ;         QueryMachineResultSetNextQuery(resultHandle, '');
	  [*] = ;         QueryMachineResultSetTable(resultHandle, 'map.event');
	  [*] = ;         QueryMachineResultSetKey(resultHandle, '110.2');
	  [*] = ;         countResults := countResults + 1;
      [*] = ;      end
      [*] = ;      else // if the message doesn't expect an answer, then a simple continue button without any processing.
      [*] = ;      begin
      [*] = ;         var resultHandle : Integer = QueryMachineResultsGetByIndex(resultsHandle, 0);
      [*] = ;         QueryMachineResultSetOnSelect(resultHandle, '');
      [*] = ;         QueryMachineResultSetNextQuery(resultHandle, '');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// eg
      [*] = ;if queryText = '' then
      [*] = ;   queryText := QueryMachineQueryGetKeyValue(queryHandle);
      [*] = ;if queryText = '' then
      [*] = ;   queryText := QueryMachineQueryGetTable(queryHandle) + ';' + QueryMachineQueryGetKey(queryHandle);
      [*] = ;queryIcon := QueryMachineQueryGetIcon(queryHandle);
      [*] = ;queryStyle := QueryMachineQueryGetStyle(queryHandle);
      [*] = ;
      [*] = ;if (queryStyle <> '3') and (queryStyle <> '6') then
      [*] = ;begin
      [*] = ;   if isStrategyGameMode() then
      [*] = ;      queryIcon := 'map.illustration' + '.' + queryIcon;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (queryIcon = '0') and isStrategyGameMode() then
      [*] = ;   begin
      [*] = ;      if query_id = gc_gui_query_heroBodyDeliveredToCastle then
      [*] = ;      begin
      [*] = ;         var pGOParser : Integer;
      [*] = ;
      [*] = ;         pGOParser := ParserSelectGameObject(gIntRegister_DeadHeroHandle);
      [*] = ;         queryIcon := ParserGetValueByKeyByHandle(pGOParser, 'Portrait');
      [*] = ;
      [*] = ;         var len : Integer = StrLength(queryIcon);
      [*] = ;         var len1 : Integer = StrLength('map.hero');
      [*] = ;         queryIcon := 'dialog' + SubStr(queryIcon, len1+1, len-len1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if gIntRegister_QueryPlayerIndex >= 0 then
      [*] = ;         begin
      [*] = ;
      [*] = ;            if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPC') then
      [*] = ;            begin
      [*] = ;               var profile : Integer = GetPlayerIntValueIndByHandle(GetPlayerHandleByIndex(gIntRegister_QueryPlayerIndex), gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;               if (profile > 0) then
      [*] = ;               begin
      [*] = ;                  queryIcon := 'astral.dialog.portrait.' + IntToStr(profile-1);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               case gGame.gameType of
      [*] = ;                  gc_GameTypeHotseat : begin
      [*] = ;                     if gArrHotseatProfiles[gIntRegister_QueryPlayerIndex].avatar > 0 then
      [*] = ;                        queryIcon := 'astral.dialog.portrait.' + IntToStr(gArrHotseatProfiles[gIntRegister_QueryPlayerIndex].avatar-1);
      [*] = ;                  end;
      [*] = ;                  gc_GameTypeLanShard : begin
      [*] = ;                     if gLanShardGame.arrLanPlayers[gIntRegister_QueryPlayerIndex].profile.avatar > 0 then
      [*] = ;                        queryIcon := 'astral.dialog.portrait.' + IntToStr(gLanShardGame.arrLanPlayers[gIntRegister_QueryPlayerIndex].profile.avatar-1);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (queryIcon = '0') then
      [*] = ;            queryIcon := 'astral.dialog.portrait.unknown';
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if GetQueryStyle(queryStyle) = 0 then
      [*] = ;begin
      [*] = ;   window_name := 'astral.dialog';
      [*] = ;   text := cAstralTemplateName;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   window_name := 'map.dialog';
      [*] = ;   text := cStrategyTemplateName;
      [*] = ;end;
      [*] = ;
      [*] = ;if_handle := _gui_GetInterfaceWindowHandle(text);
      [*] = ;_gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,window_d);
      [*] = ;if_answers_handle := _gui_GetInterfaceWindowHandle(cAnswersTemplateName);
      [*] = ;_gui_GetInterfaceElement(if_answers_handle,gc_gui_if_base_window_id,window_a_d);
      [*] = ;
      [*] = ;if windowHandle = 0 then
      [*] = ;begin
      [*] = ;   windowHandle := AddNewElementByClassNameParent(cWindowName, 'TOSWImageGuiControl', 0, _gui_GetLayerI());
      [*] = ;   SetGUIElementMaterial(windowHandle, gc_gui_material_blank_0);
      [*] = ;   SetGUIAllowEvents(windowHandle, False, False, False);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if GetGUIElementVisible(windowHandle) then
      [*] = ;      bVisible := True;
      [*] = ;   RemoveGUIChildren(windowHandle);
      [*] = ;end;
      [*] = ;SetGUIElementAlign(windowHandle, window_d.align.h, window_d.align.v);
      [*] = ;SetGUIElementAllPositionRect(windowHandle, window_d.p.pos.x, window_d.p.pos.y, window_d.p.size.w, window_d.p.size.h);
      [*] = ;
      [*] = ;if _log then _log_Gui(_log_name+' Current query ID = ' + queryID+', query style = '+queryStyle+', Advice = '+BoolToStr(gBoolRegister_ShowAdvice));
      [*] = ;
      [*] = ;answers_dy := 0;
      [*] = ;if (gBoolRegister_ShowAdvice) or (gBoolRegister_ShowPlayerHint) then
      [*] = ;begin
      [*] = ;   const cHintWindowPortraitFrame = $1e;
      [*] = ;   const cHintWindowPortrait = $1d;
      [*] = ;   const cHintWindowText = $2;
      [*] = ;   const cHintWindowName = $1;
      [*] = ;
      [*] = ;   var if_hint_handle : Integer = _gui_GetInterfaceWindowHandle(cHintTemplateName);
      [*] = ;   var hint_window_d : TInterfaceElementData;
      [*] = ;
      [*] = ;   _gui_GetInterfaceElement(if_hint_handle,gc_gui_if_base_window_id,hint_window_d);
      [*] = ;
      [*] = ;   gBoolRegister_ShowAdvice := False;
      [*] = ;
      [*] = ;   if (gBoolRegister_ShowPlayerHint) then
      [*] = ;   begin
      [*] = ;      var avatar : Integer;
      [*] = ;      var myPlName : String;
      [*] = ;      case gGame.gameType of
      [*] = ;         gc_GameTypeHotseat : begin
      [*] = ;            avatar := gArrHotseatProfiles[gIntRegister_MapMyPlayerIndex].avatar;
      [*] = ;            myPlName := gArrHotseatProfiles[gIntRegister_MapMyPlayerIndex].name;
      [*] = ;         end;
      [*] = ;         gc_GameTypeLanShard : begin
      [*] = ;            avatar := gLanShardGame.arrLanPlayers[gIntRegister_MapMyPlayerIndex].profile.avatar;
      [*] = ;            myPlName := gLanShardGame.arrLanPlayers[gIntRegister_MapMyPlayerIndex].profile.name;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            avatar := gProfile.avatar;
      [*] = ;            myPlName := gProfile.name;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //gBoolRegister_ShowPlayerHint := false;
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_hint_handle,gc_gui_if_base_window_id,hint_window_d);
      [*] = ;      _gui_GetInterfaceElement(if_hint_handle,cHintWindowText,elem_d);
      [*] = ;
      [*] = ;      //gStringRegister_EnemyPlayerName := name;
      [*] = ;      text := GetLocaleTableListItemByID('gui', '449');
      [*] = ;
      [*] = ;      StringRegister0 := text;
      [*] = ;      MapExecuteState('StringReplaceParams');
      [*] = ;      text := StringRegister1;
      [*] = ;
      [*] = ;      text := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,elem_d.p.size.w);
      [*] = ;      GetGUIElementFontTextFormatRect(elem_d.font_handle, text, w, h);
      [*] = ;      h := max(h,elem_d.p.size.h);
      [*] = ;      hint_window_d.p.size.h := (hint_window_d.p.size.h-elem_d.p.size.h)+h;
      [*] = ;
      [*] = ;      if _log then _log_Values('MapActiveHeroHandle|MapCurPlayerIndex|MapCurHeroIndex',gIntRegister_MapActiveHeroHandle,_gv_GetCurrentPlayer(),gIntRegister_MapCurHeroIndex,0,0,0);
      [*] = ;      answers_handle := _gui_CreateScalableWindow_VVK('hint',windowHandle,gc_gui_align_parent_lt,hint_window_d.p,'common_window');
      [*] = ;
      [*] = ;      var text_color : TColorRGBA;
      [*] = ;      _gui_GetInterfaceWindowColor(if_hint_handle,6,text_color);
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_hint_handle,cHintWindowText,elem_d);
      [*] = ;      _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,h);
      [*] = ;      _gui_CreateText_VVK('',answers_handle,text,gc_gui_align_parent_lt,pos,gc_gui_align_middle,elem_d.font_handle,text_color);
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_hint_handle,cHintWindowPortrait,elem_d);
      [*] = ;      _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;
      [*] = ;      if (avatar > 0) then
      [*] = ;         text := 'astral.players.icon.big.'+IntToStr(avatar)
      [*] = ;      else
      [*] = ;         text := 'astral.players.icon.big.0';
      [*] = ;      _gui_CreateImage_VVK('',answers_handle,text,gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_hint_handle,cHintWindowPortraitFrame,elem_d);
      [*] = ;      _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;      _gui_CreateImage_VVK('',answers_handle,'map.heroadvice.frame',gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_hint_handle,cHintWindowName,elem_d);
      [*] = ;      _gui_CreateText_VVK('',answers_handle,myPlName,gc_gui_align_parent_lt,elem_d.p,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;      answers_dy := GetGUIElementHeight(answers_handle);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;   // case result: answers handle - hint window handle GetGUIElementHeight(elmParentHandle);
      [*] = ;      case gIntRegister_CurGameMode of
      [*] = ;         gc_GameModeAstral : begin
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowText,elem_d);
      [*] = ;
      [*] = ;            text := GetLocaleTableListItemByID('message', '51.description'); // !!!
      [*] = ;            text := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,elem_d.p.size.w);
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle, text, elem_d.p.size.w, h);
      [*] = ;            h := max(h,elem_d.p.size.h);
      [*] = ;            hint_window_d.p.size.h := (hint_window_d.p.size.h-elem_d.p.size.h)+h;
      [*] = ;
      [*] = ;            answers_handle := _gui_CreateScalableWindow_VVK('hint',windowHandle,gc_gui_align_parent_lt,hint_window_d.p,'common_window');
      [*] = ;
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowPortrait,elem_d);
      [*] = ;            _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;            _gui_CreateImage_VVK('',answers_handle,'astral.players.icon.big.zarr',gc_gui_align_parent_lt,pos);
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowPortraitFrame,elem_d);
      [*] = ;            _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;            _gui_CreateImage_VVK('',answers_handle,'map.heroadvice.frame',gc_gui_align_parent_lt,pos);
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowName,elem_d);
      [*] = ;            _gui_CreateText_VVK('',answers_handle,'tutorial|91',gc_gui_align_parent_lt,elem_d.p,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowText,elem_d);
      [*] = ;            _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,w,h);
      [*] = ;            _gui_CreateText_VVK('',answers_handle,text,gc_gui_align_parent_lt,pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;            answers_dy := GetGUIElementHeight(answers_handle);
      [*] = ;         end;
      [*] = ;         gc_GameModeStrategy, gc_GameModeTactics: begin
      [*] = ;            const cMaxHeroAdvices = $20;
      [*] = ;
      [*] = ;            var hint_handle : Integer;
      [*] = ;            var nil_box : TRectangle;
      [*] = ;
      [*] = ;            var virtBattleResult : Integer = gIntRegister_VirtualBattleResult;
      [*] = ;            var count,background_delta: Integer;
      [*] = ;            var heroAdviceID : Integer = 0;
      [*] = ;            var pHeroAdvice : Integer;
      [*] = ;            var min,max : Integer;
      [*] = ;            var advices_ids : array [0..cMaxHeroAdvices] of Integer;
      [*] = ;            var text_color : TColorRGBA;
      [*] = ;
      [*] = ;            count := 0;
      [*] = ;            for i:=0 to gPrototypeData.heroAdvices.number-1 do
      [*] = ;            begin
      [*] = ;               pHeroAdvice := ParserSelectByHandleByIndex(gPrototypeData.heroAdvices.handle, i);
      [*] = ;               if (virtBattleResult>=ParserGetIntValueByKeyByHandle(pHeroAdvice, 'Min')) and (virtBattleResult<ParserGetIntValueByKeyByHandle(pHeroAdvice, 'Max')) then
      [*] = ;               begin
      [*] = ;                  advices_ids[count] := ParserGetIntValueByKeyByHandle(pHeroAdvice, 'HeroAdviceID');
      [*] = ;                  count := count+1;
      [*] = ;                  if count >= cMaxHeroAdvices then
      [*] = ;                     break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            text := GetLocaleTableListItemByID('hero_advice', IntToStr(advices_ids[Floor(Random()*count)]));
      [*] = ;            if (virtBattleResult < 60) then
      [*] = ;               _gui_GetInterfaceWindowColor(if_hint_handle,7,text_color)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (virtBattleResult < 110) then
      [*] = ;                  _gui_GetInterfaceWindowColor(if_hint_handle,6,text_color)
      [*] = ;               else
      [*] = ;                  _gui_GetInterfaceWindowColor(if_hint_handle,5,text_color);
      [*] = ;            end;
      [*] = ;
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,gc_gui_if_base_window_id,hint_window_d);
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowText,elem_d);
      [*] = ;
      [*] = ;            text := GetGUIWrappedTextFormatByFont(elem_d.font_handle,text,elem_d.p.size.w);
      [*] = ;            GetGUIElementFontTextFormatRect(elem_d.font_handle, text, w, h);
      [*] = ;            h := max(h,elem_d.p.size.h);
      [*] = ;            hint_window_d.p.size.h := (hint_window_d.p.size.h-elem_d.p.size.h)+h;
      [*] = ;
      [*] = ;            if _log then _log_Values('MapActiveHeroHandle|MapCurPlayerIndex|MapCurHeroIndex',gIntRegister_MapActiveHeroHandle,_gv_GetCurrentPlayer(),gIntRegister_MapCurHeroIndex,0,0,0);
      [*] = ;            answers_handle := _gui_CreateScalableWindow_VVK('hint',windowHandle,gc_gui_align_parent_lt,hint_window_d.p,'common_window');
      [*] = ;
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowText,elem_d);
      [*] = ;            _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,elem_d.p.size.w,h);
      [*] = ;            _gui_CreateText_VVK('',answers_handle,text,gc_gui_align_parent_lt,pos,gc_gui_align_middle,elem_d.font_handle,text_color);
      [*] = ;
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowPortrait,elem_d);
      [*] = ;            _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;
      [*] = ;            if goHandle <> 0 then
      [*] = ;               text := ParserGetValueByKeyByHandle(ParserSelectGameObject(goHandle), 'Portrait')
      [*] = ;            else
      [*] = ;               text := 'astral.players.icon.big.0';
      [*] = ;            _gui_CreateImage_VVK('',answers_handle,text,gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowPortraitFrame,elem_d);
      [*] = ;            _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;            _gui_CreateImage_VVK('',answers_handle,'map.heroadvice.frame',gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;            _gui_GetInterfaceElement(if_hint_handle,cHintWindowName,elem_d);
      [*] = ;            _gui_CreateText_VVK('',answers_handle,gStringRegister_MyHeroName,gc_gui_align_parent_lt,elem_d.p,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;            answers_dy := GetGUIElementHeight(answers_handle);
      [*] = ;         end;
      [*] = ;         else
      [*] = ;            answers_handle := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if answers_handle <> 0 then
      [*] = ;   begin
      [*] = ;      _gui_GetInterfaceElement(if_handle,cAdvicePos,elem_d);
      [*] = ;      SetGUIElementPositionX(answers_handle,elem_d.p.pos.x);
      [*] = ;      SetGUIElementPositionY(answers_handle,elem_d.p.pos.y-(GetGUIElementHeight(answers_handle)-hint_window_d.p.size.h));
      [*] = ;      if _log then _log_Gui('Showing advice. X: '+IntToStr(GetGUIElementPositionX(answers_handle))+', Y: '+IntToStr(GetGUIElementPositionY(answers_handle)));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// --- Query text ---
      [*] = ;StringRegister0 := queryText;
      [*] = ;MapExecuteState('StringReplaceParams');
      [*] = ;queryText := StringRegister1;
      [*] = ;
      [*] = ;{text := queryText;
      [*] = ;for i := 0 to 5 do
      [*] = ;text := text+gc_gui_BreakLine+queryText;
      [*] = ;queryText := text;}
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cTextMinArea,elem_d);
      [*] = ;_gui_GetInterfaceElement(if_handle,cTextArea,text_d);
      [*] = ;
      [*] = ;j := $20;
      [*] = ;max_w := text_d.p.size.w;
      [*] = ;max_h := text_d.p.size.h-GetGUIElementFontHeight(text_d.font_handle);
      [*] = ;
      [*] = ;for i:=0 to $80 do
      [*] = ;begin
      [*] = ;   text := GetGUIWrappedTextFormatByFont(text_d.font_handle,queryText,max_w);
      [*] = ;   GetGUIElementFontTextFormatRect(text_d.font_handle,text,w,h);
      [*] = ;   if (h > text_d.p.size.h) or (w < (elem_d.p.size.w+j)) then
      [*] = ;      break;
      [*] = ;   max_w := max_w-j;
      [*] = ;end;
      [*] = ;
      [*] = ;if w < elem_d.p.size.w then
      [*] = ;   w := elem_d.p.size.w;
      [*] = ;max_w := text_d.p.pos.x+w+(window_d.p.size.w-(text_d.p.pos.x+text_d.p.size.w));
      [*] = ;window_d.p.size.w := max_w;
      [*] = ;
      [*] = ;_sys_FillRect(pos,0,0,max_w,window_d.p.size.h);
      [*] = ;i := _gui_CreateImageSlice_VVK('',windowHandle,'common.window.background',gc_gui_align_parent_lt,pos);
      [*] = ;//if h < text_d.p.size.h then
      [*] = ;//   text_d.p.pos.y := text_d.p.pos.y + ((text_d.p.size.h-h) div 2);
      [*] = ;
      [*] = ;scroll_canvas_size.w := w;
      [*] = ;scroll_canvas_size.h := h;
      [*] = ;_sys_FillRect(pos,text_d.p.pos.x,text_d.p.pos.y,w,min(h,text_d.p.size.h));
      [*] = ;scroll_handle := _gui_CreateScrollableCanvas_VVK('query_text_scroll',windowHandle,text_d.align,pos,scroll_canvas_size,'map.dialog',true);
      [*] = ;SetGUIAllowEvents(scroll_handle, True, False, False);
      [*] = ;_sys_FillRect(pos,0,0,w,h);
      [*] = ;_gui_CreateText_VVK('',scroll_handle,text,gc_gui_align_parent_lt,pos,gc_gui_align_lt,text_d.font_handle,text_d.color);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cLeftFrameOffset,elem_d);
      [*] = ;if GetQueryStyle(queryStyle) = 0 then
      [*] = ;   text := 'map.dialog.window.new.portrait'
      [*] = ;else
      [*] = ;   text := 'map.dialog.window.new.illustration';
      [*] = ;tw := GetGUITextureWidth(text)-elem_d.p.size.w;
      [*] = ;window_d.p.pos.x := tw;
      [*] = ;_sys_FillRect(pos,-1*tw,window_d.p.size.h-elem_d.p.size.h,0,0);
      [*] = ;lhd := _gui_CreateImage_VVK('',windowHandle,text,elem_d.align,pos);
      [*] = ;//GUIElementSendToBack(lhd);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cLeftFrame,elem_d);
      [*] = ;_gui_GetInterfaceElement(if_handle,cPortrait,elem2_d);
      [*] = ;if _log then _log_Gui('Query Icon: '+queryIcon);
      [*] = ;_sys_FillRect(pos,elem2_d.p.pos.x-elem_d.p.pos.x+GetGUIElementPositionX(lhd),elem2_d.p.pos.y-elem_d.p.pos.y+GetGUIElementPositionY(lhd),elem2_d.p.size.w,elem2_d.p.size.h);
      [*] = ;i := _gui_CreateImage_VVK('',windowHandle,queryIcon,elem_d.align,pos);
      [*] = ;GUIElementSendToBack(i);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cRightFrameOffset,elem_d);
      [*] = ;_sys_FillRect(pos,max_w-elem_d.p.size.w,window_d.p.size.h-elem_d.p.size.h,0,0);
      [*] = ;rhd := _gui_CreateImage_VVK('',windowHandle,'map.dialog.window.new.frame.right',elem_d.align,pos);
      [*] = ;th := GetGUIElementWidth(rhd)-elem_d.p.size.w;
      [*] = ;window_d.p_raw.pos.x := th;
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cAnswersYPos_XOffs,elem_d);
      [*] = ;answers_width := max_w+tw+th-(elem_d.p.size.w*2);  // max answers dropdown width
      [*] = ;
      [*] = ;_sys_FillRect(pos,elem_d.p.size.w-tw,elem_d.p.pos.y,1,1);
      [*] = ;answers_handle := _gui_CreateImage_VVK('answers',windowHandle,gc_gui_material_blank_0,gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;h := GetGUIElementPositionX(lhd)+GetGUIElementWidth(lhd);
      [*] = ;w := GetGUIElementPositionX(rhd)-h;
      [*] = ;if not _gui_GetInterfaceElement(if_handle,cUpperFrameOffset,elem_d) then
      [*] = ;   elem_d.p.size.h := 0;
      [*] = ;_sys_FillRect(pos,h,elem_d.p.size.h-GetGUITextureHeight('map.dialog.window.new.frame.top'),w,0);
      [*] = ;_gui_CreateImageSlice_VVK('',windowHandle,'map.dialog.window.new.frame.top',gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;if not _gui_GetInterfaceElement(if_handle,cLowerFrameOffset,elem_d) then
      [*] = ;   elem_d.p.size.h := 0;
      [*] = ;_sys_FillRect(pos,h,window_d.p.size.h-elem_d.p.size.h,w,0);
      [*] = ;_gui_CreateImageSlice_VVK('',windowHandle,'map.dialog.window.new.frame.bottom',gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;event_type := 0;
      [*] = ;rewards_handle := 0;
      [*] = ;
      [*] = ;if isStrategyGameMode() then
      [*] = ;begin
      [*] = ;   if ((query_id > gc_query_EventMinIndex) and (query_id <= gc_query_EventMaxIndex)) or ((query_id > gc_query_ScenarioEventMinIndex) and (query_id <= gc_query_ScenarioCampEventMaxIndex)) then
      [*] = ;   begin
      [*] = ;      event_type := 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (query_id > gc_query_EncounterMinIndex) and (query_id <= gc_query_EncounterMaxIndex) then
      [*] = ;      begin
      [*] = ;         event_type := 2;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var cp : Integer = st_RetrieveCastleParser(plHandle);
      [*] = ;   var plGold, plGem : Integer;
      [*] = ;
      [*] = ;   plGold := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   plGem := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;   case query_id of
      [*] = ;      gc_gui_query_heroBodyDeliveredToCastle : begin
      [*] = ;         if _log then _log_gui('Player Gold = '+IntToStr(plGold)+', Player Gem = '+IntToStr(plGem));
      [*] = ;         GameObjectExecuteStateByHandle(cp, 'IsUnderSiege');
      [*] = ;
      [*] = ;         if (gIntRegister_GoldCost > plGold) or (gIntRegister_GemCost > plGem) or BoolRegister0 then
      [*] = ;         begin
      [*] = ;            QueryMachineResultsDelete(resultsHandle, 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_gui_query_heroMakeSabotage : begin
      [*] = ;         if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;         begin
      [*] = ;            PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'GetHeroHandle');
      [*] = ;            if IntRegister0 <> 0 then
      [*] = ;            begin
      [*] = ;               var mapPlHandle : Integer = GetGameObjectPlayerHandleByHandle(_unit_GetMapHeroHandle(IntRegister0));
      [*] = ;               if mapPlHandle <> 0 then
      [*] = ;                  plGold := GetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if _log then _log_gui('Player Gold = '+IntToStr(plGold)+', Player Gem = '+IntToStr(plGem));
      [*] = ;         
      [*] = ;         var resultHandle : Integer;
      [*] = ;         var sabotage_data : array [0..3] of Integer;
      [*] = ;
      [*] = ;         sabotage_data[0] := gIntRegister_FalseAlarmPrice;
      [*] = ;         sabotage_data[1] := gIntRegister_PoisonedWaterPrice;
      [*] = ;         sabotage_data[2] := gIntRegister_PanicPrice;
      [*] = ;
      [*] = ;         for i := 0 to 2 do
      [*] = ;         begin
      [*] = ;            resultHandle := QueryMachineResultsGetByIndex(resultsHandle, i);
      [*] = ;            if sabotage_data[i] < 0 then
      [*] = ;               QueryMachineResultSetVisible(resultHandle, false)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (plGold < sabotage_data[i]) and (sabotage_data[i] > 0) then
      [*] = ;                  QueryMachineResultSetEnable(resultHandle, false);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // should display rewards before answer choices
      [*] = ;   if (queryStyle='4') then
      [*] = ;   begin
      [*] = ;
      [*] = ;      const cRewardsResources = $1e;
      [*] = ;      //const cRewardsGoldArea = $1e;
      [*] = ;      //const cRewardsGemArea = $1d;
      [*] = ;      //const cRewardsGoldTextArea = $1c;
      [*] = ;      //const cRewardsGemTextArea = $1b;
      [*] = ;      const cRewardsItemArea = $1a;
      [*] = ;      const cRewardsItemInnerArea = $19;
      [*] = ;
      [*] = ;      var if_rewards_handle : Integer = _gui_GetInterfaceWindowHandle(cRewardsTemplateName);
      [*] = ;      var tmp_handle : Integer;
      [*] = ;      var nil_box : TRectangle;
      [*] = ;      var window_width,max_items,items_to_display : Integer;
      [*] = ;
      [*] = ;      var pItems, pItem, itemDurability, itemID : Integer;
      [*] = ;      var hint,iconName,temp_str,columns : String;
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_rewards_handle,gc_gui_if_base_window_id,elem_d);
      [*] = ;      _sys_FillRect(nil_box,0,0,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;      rewards_handle :=_gui_CreateImage_VVK('',answers_handle,gc_gui_material_blank_0,gc_gui_align_parent_lt,nil_box);
      [*] = ;      window_width := elem_d.p.size.w;
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_rewards_handle,cRewardsResources,elem_d);
      [*] = ;
      [*] = ;      elem_d.p.pos.y := (nil_box.size.h-(GetGUIElementFontHeight(elem_d.font_handle)*2+_gui_TableGetFrameHeight(gc_gui_TableStyleBorder)*3)) div 2;
      [*] = ;
      [*] = ;      columns := '';
      [*] = ;      i := GetGUIElementFontHeight(elem_d.font_handle)+_gui_TableGetFrameWidth(gc_gui_TableStyleBorder)*2;
      [*] = ;      _sa_AddAsInt(columns,i);
      [*] = ;      _sa_AddAsInt(columns,elem_d.p.size.w-(i+_gui_TableGetFrameWidth(gc_gui_TableStyleBorder)*3));
      [*] = ;
      [*] = ;      _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;      _gui_TableGetFrameString(columns,gc_gui_TableFrameTop,temp_str);
      [*] = ;      i:=_gui_CreateText_VVK('',rewards_handle,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;      pos.pos.y := pos.pos.y+GetGUIElementHeight(i);
      [*] = ;
      [*] = ;      _gui_TableFormatTextLine(elem_d.font_handle,columns,'^c'+gc_gui_GoldIconChar+'|^c'+IntToStr(gIntRegister_TreasureGoldReward),temp_str);
      [*] = ;      i:=_gui_CreateText_VVK('',rewards_handle,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,elem_d.font_handle,elem_d.color);
      [*] = ;      pos.pos.y := pos.pos.y+GetGUIElementHeight(i);
      [*] = ;
      [*] = ;      _gui_TableGetFrameString(columns,gc_gui_TableFrameCenter,temp_str);
      [*] = ;      i:=_gui_CreateText_VVK('',rewards_handle,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;      pos.pos.y := pos.pos.y+GetGUIElementHeight(i);
      [*] = ;
      [*] = ;      _gui_TableFormatTextLine(elem_d.font_handle,columns,'^c'+gc_gui_GemIconChar+'|^c'+IntToStr(gIntRegister_TreasureGemReward),temp_str);
      [*] = ;      i:=_gui_CreateText_VVK('',rewards_handle,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,elem_d.font_handle,elem_d.color);
      [*] = ;      pos.pos.y := pos.pos.y+GetGUIElementHeight(i);
      [*] = ;
      [*] = ;      _gui_TableGetFrameString(columns,gc_gui_TableFrameBottom,temp_str);
      [*] = ;      i:=_gui_CreateText_VVK('',rewards_handle,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;      //pos.pos.y := pos.pos.y+GetGUIElementHeight(i);
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_rewards_handle,cRewardsItemArea,elem_d);
      [*] = ;      elem_d.p.pos.y := (nil_box.size.h-elem_d.p.size.h) div 2;
      [*] = ;      max_items := (window_width-elem_d.p.pos.x) div (elem_d.p.size.w);
      [*] = ;
      [*] = ;      pItems := ParserSelectByHandleByKey(ParserSelectPlayer(GetPlayerHandleInterfaceIO()), 'EventItems');
      [*] = ;      if (ParserGetCountByHandle(pItems) = 0) then
      [*] = ;      begin
      [*] = ;         if goHandle <> 0 then
      [*] = ;            pItems := ParserSelectByHandleByKey(ParserSelectGameObject(goHandle),'SiteLootItems');
      [*] = ;      end;
      [*] = ;      items_to_display := ParserGetCountByHandle(pItems);
      [*] = ;
      [*] = ;      if items_to_display > max_items then
      [*] = ;         max_items := items_to_display;
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_rewards_handle,cRewardsItemInnerArea,text_d);
      [*] = ;
      [*] = ;      for i := 0 to max_items-1 do
      [*] = ;      begin
      [*] = ;         _gui_CreateImage_VVK('',rewards_handle,'icon.frame.item',gc_gui_align_parent_lt,elem_d.p);
      [*] = ;         tmp_handle := _gui_CreateImage_VVK('open',rewards_handle,'heropanel.icon.52x52.slot.empty',gc_gui_align_parent_lt,text_d.p);
      [*] = ;
      [*] = ;         if i < items_to_display then
      [*] = ;         begin
      [*] = ;            pItem := ParserSelectByHandleByIndex(pItems, i);
      [*] = ;            itemID := ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;            itemDurability := ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;            // hint := 'itemhint%|'+IntToStr(itemID)+'|'+IntToStr(3)+'|'+IntToStr(itemDurability); // !!
      [*] = ;
      [*] = ;            _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;
      [*] = ;            var pExtItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extitems.handle, itemID);
      [*] = ;            var itemType : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'ItemType');
      [*] = ;
      [*] = ;            if itemType = 14 then // building icon
      [*] = ;               _sys_FillRect(nil_box,0,0,52,52)
      [*] = ;            else
      [*] = ;               _sys_FillRect(nil_box,0,0,0,0);
      [*] = ;            _gui_CreateImage_VVK('',tmp_handle,iconName,gc_gui_align_parent_m,nil_box);
      [*] = ;
      [*] = ;            if (itemType=14) then // !!!
      [*] = ;            begin
      [*] = ;               var pItemAbility : Integer = ParserSelectByHandleByIndex(ParserSelectByHandleByKey(pExtItem, 'Abilities'), 0);
      [*] = ;               var power : Integer = ParserGetIntValueByKeyByHandle(pItemAbility, 'Power');
      [*] = ;               tmp_handle := _gui_CreateButton_VVK('innerbuild_reward_icon',rewards_handle,'','heropanel.icon.52x52.slot.cover',gc_gui_align_parent_lt,text_d.p,cEventHandlerStrategy,'',gc_gui_castle_buildings_btnBaseTag + power);
      [*] = ;               _gui_ft_AttachHint_I2(tmp_handle,'VVK.FTooltipInnerBuilding',cFT_IBBattleReward,power);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               tmp_handle := _gui_CreateButton_VVK('',rewards_handle,'','heropanel.icon.52x52.slot.cover',gc_gui_align_parent_lt,text_d.p,'','',0);
      [*] = ;               _gui_ft_AttachHint_I4_S2(tmp_handle,'VVK.FTooltipItem',itemID,cFT_ItemPriceBase,itemDurability,cFT_ItemHeroDefault,cEventHandlerStrategy,'3');
      [*] = ;            end;
      [*] = ;
      [*] = ;            SetGUIElementVisibleProperties(tmp_handle, 'HoverProperty', 'heropanel.icon.52x52.slot.cover.hover', 0, 0, 0, 0, cMouseCursorItemHoverIndex, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementVisibleProperties(tmp_handle, 'DownProperty', 'heropanel.icon.52x52.slot.cover.hover',  0, 0, 0, 0, cMouseCursorItemHoverIndex, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementStringTag(tmp_handle, 'Item');
      [*] = ;         end;
      [*] = ;
      [*] = ;         elem_d.p.pos.x := elem_d.p.pos.x + elem_d.p.size.w;
      [*] = ;         text_d.p.pos.x := text_d.p.pos.x + elem_d.p.size.w;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (query_id=gc_gui_query_campStartTutorial) and (not gProfile.finishtutorial) then // tutorial block result
      [*] = ;begin
      [*] = ;   QueryMachineResultSetVisible(QueryMachineResultsGetByIndex(resultsHandle, 3), false);
      [*] = ;end;
      [*] = ;
      [*] = ;// now answers array
      [*] = ;no := 0;
      [*] = ;
      [*] = ;var resultOnSelect, resultNextQuery : String;
      [*] = ;for i := 0 to countResults-1 do
      [*] = ;begin
      [*] = ;   answers[no].tag := QueryMachineResultsGetByIndex(resultsHandle, i);
      [*] = ;   answers[no].enabled := QueryMachineResultGetEnable(answers[no].tag);
      [*] = ;   answers[no].visible := QueryMachineResultGetVisible(answers[no].tag);
      [*] = ;   answers[no].id := QueryMachineResultGetID(answers[no].tag);
      [*] = ;   answers[no].tooltip := '';
      [*] = ;   resultOnSelect := QueryMachineResultGetOnSelect(answers[no].tag);
      [*] = ;   resultNextQuery := QueryMachineResultGetNextQuery(answers[no].tag);
      [*] = ;
      [*] = ;   // !!
      [*] = ;   if isStrategyGameMode() and (gc_demoVersion=1) and (SameText(resultOnSelect, 'query.LoadGame')) then
      [*] = ;      answers[no].enabled := False;
      [*] = ;
      [*] = ;   if (answers[no].visible) then
      [*] = ;   begin
      [*] = ;      result_visible := true;
      [*] = ;      result_enabled := answers[no].enabled;
      [*] = ;      if isCampaignEvent(query_id) then
      [*] = ;      begin
      [*] = ;         var astralEventParser : Integer = ParserSelectByHandleByIndex(gPrototypeData.campEvents.handle, query_id - gc_query_CampEventMinIndex);
      [*] = ;
      [*] = ;         phd1 := ParserSelectByHandleByKey(astralEventParser, 'AnswerConditionList');
      [*] = ;         for j := 0 to ParserGetCountByHandle(phd1)-1 do
      [*] = ;         begin
      [*] = ;            phd2 := ParserSelectByHandleByIndex(phd1, j);
      [*] = ;            if ParserGetIntValueByKeyByHandle(phd2, 'ResultIndex') = i+1 then
      [*] = ;            begin
      [*] = ;               param1 := ParserGetIntValueByKeyByHandle(phd2, 'Param1');
      [*] = ;               param2 := ParserGetIntValueByKeyByHandle(phd2, 'Param2');
      [*] = ;               case param1 of
      [*] = ;                  1 : begin
      [*] = ;                     result_visible := (gCampaign.arrCampPlayers[0].energy >= param2);
      [*] = ;                     gIntRegister_AstralEnergy := param2;
      [*] = ;                  end;
      [*] = ;                  2 : result_visible := (gCampaign.arrDialogs[param2] > 0);
      [*] = ;                  3 : result_visible := (gCampaign.arrItems[1] > 0);
      [*] = ;                  4 : result_visible := (gCampaign.arrItems[0] > 1);
      [*] = ;                  5 : result_visible := (gCampaign.arrDialogs[param2] = 0);
      [*] = ;               end;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var pResults : Integer;
      [*] = ;         case event_type of
      [*] = ;            1 : begin // event
      [*] = ;               var dummyHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_CurProvinceIndex, _map_GetProvincesPlayer());
      [*] = ;               var pProvince : Integer = GetGameObjectIntValueIndByHandle(dummyHandle, gc_map_GOStack_Province_iParserHandle);
      [*] = ;               var plGold, plGem : Integer;
      [*] = ;
      [*] = ;               if (pProvince<>gIntRegister_MapSelectedHex) then
      [*] = ;               begin
      [*] = ;                  SetCameraInfoSmoothingChange(True);
      [*] = ;                  _misc_SetCameraTarget(dummyHandle);
      [*] = ;               end;
      [*] = ;
      [*] = ;               gIntRegister_MapSelectedHex := pProvince;
      [*] = ;               gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;
      [*] = ;               plGold := GetPlayerIntValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_map_PLStack_MapUnit_iGold);
      [*] = ;               plGem := GetPlayerIntValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;               IntRegister0 := query_id;
      [*] = ;               MapExecuteState('GetEventParserByID');
      [*] = ;               pResults := ParserSelectByHandleByKey(IntRegister1, 'AnswerConditionList');
      [*] = ;
      [*] = ;               for j := 0 to ParserGetCountByHandle(pResults)-1 do
      [*] = ;               begin
      [*] = ;                  var pResult : Integer = ParserSelectByHandleByIndex(pResults, j);
      [*] = ;                  var resID : String = ParserGetValueByKeyByHandle(pResult, 'ResultID');
      [*] = ;                  if SameText(resID, answers[no].id) then
      [*] = ;                  begin
      [*] = ;                     var index : Integer = ParserGetIntValueByKeyByHandle(pResult, 'Param1');
      [*] = ;                     var param : Integer = ParserGetIntValueByKeyByHandle(pResult, 'Param2');
      [*] = ;                     case index of
      [*] = ;                        1 : begin
      [*] = ;                           if plGold < param then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(index)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        2 : begin
      [*] = ;                           if plGem < param then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(index)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        3 : begin
      [*] = ;                           IntRegister0 := 0;
      [*] = ;                           IntRegister1 := 0;
      [*] = ;                           GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerArmy');
      [*] = ;                           var pArmy : Integer = IntRegister2;
      [*] = ;                           var isGarrison : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;                           if (pArmy = 0) or isGarrison then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(index)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        4 : begin
      [*] = ;                           if param > 0 then
      [*] = ;                           begin
      [*] = ;                              if ((gIntRegister_ScenarioEventFlags and (1 shl (param-1))) = 0) then
      [*] = ;                                 result_visible := false;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              if ((gIntRegister_ScenarioEventFlags and (1 shl (-1*(param-1)))) <> 0) then
      [*] = ;                                 result_visible := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            2 : begin // encounter
      [*] = ;               SetCameraInfoSmoothingChange(True);
      [*] = ;               _misc_SetCameraTarget(goHandle);
      [*] = ;
      [*] = ;               var plGold, plGem : Integer;
      [*] = ;               plGold := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;               plGem := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;               IntRegister0 := query_id;
      [*] = ;               MapExecuteState( 'GetEncounterParserByID');
      [*] = ;               pResults := ParserSelectByHandleByKey(IntRegister1, 'AnswerConditionList');
      [*] = ;
      [*] = ;               for j := 0 to ParserGetCountByHandle(pResults)-1 do
      [*] = ;               begin
      [*] = ;                  var pResult : Integer = ParserSelectByHandleByIndex(pResults, j);
      [*] = ;                  var resID : String = ParserGetValueByKeyByHandle(pResult, 'ResultID');
      [*] = ;
      [*] = ;                  if SameText(resID, answers[no].id) then
      [*] = ;                  begin
      [*] = ;                     var param1 : Integer = ParserGetIntValueByKeyByHandle(pResult, 'Param1');
      [*] = ;                     var param2 : Integer = ParserGetIntValueByKeyByHandle(pResult, 'Param2');
      [*] = ;
      [*] = ;                     case param1 of
      [*] = ;                        1 : begin
      [*] = ;                           if plGold < param2 then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        2 : begin
      [*] = ;                           if plGem < param2 then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        3 : begin
      [*] = ;                           if plGold < Abs(gIntRegister_EncounterParam1) then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        4 : begin
      [*] = ;                           if plGem < Abs(gIntRegister_EncounterParam1) then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        5 : begin
      [*] = ;                           if plGold < Abs(gIntRegister_EncounterParam2) then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        6 : begin
      [*] = ;                           if plGem < Abs(gIntRegister_EncounterParam2) then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        7 :
      [*] = ;                        begin
      [*] = ;                           IntRegister0 := gc_skill_diplomacy;
      [*] = ;                           GameObjectExecuteStateByHandle(goHandle, 'GetSkillLevel');
      [*] = ;
      [*] = ;                           if IntRegister1 < param2 then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint');
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        8 :
      [*] = ;                        begin
      [*] = ;                           var cp : Integer = st_RetrieveCastleParser(plHandle);
      [*] = ;
      [*] = ;                           if cp <> 0 then
      [*] = ;                           begin
      [*] = ;                              IntRegister0 := param2;
      [*] = ;                              GameObjectExecuteStateByHandle(cp, 'CheckInnerBuilding');
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                              BoolRegister0 := false;
      [*] = ;                           if not BoolRegister0 then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint');
      [*] = ;                              if param2 = 0 then
      [*] = ;                                 answers[no].tooltip := StrReplace(answers[no].tooltip,'%inner_build%','')
      [*] = ;                              else
      [*] = ;                                 answers[no].tooltip := StrReplace(answers[no].tooltip,'%inner_build%', GetLocaleTableListItemByID('inner_build',IntToStr(param2)));
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        9 :
      [*] = ;                        begin
      [*] = ;                           IntRegister0 := param2;
      [*] = ;                           GameObjectExecuteStateByHandle(goHandle, 'GetFreeUnitSlot');
      [*] = ;                           if IntRegister2 < 0 then
      [*] = ;                           begin
      [*] = ;                              if StrLength(answers[no].tooltip) > 2 then answers[no].tooltip := answers[no].tooltip + gc_gui_BreakLine;
      [*] = ;                              answers[no].tooltip := answers[no].tooltip + StrReplace(GetLocaleTableListItemByID('gui', 'querywrongcondition'+IntToStr(100+param1)+'.hint'),'%slot_rank%', IntToStr(param2));
      [*] = ;                              result_enabled := false;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else begin // other
      [*] = ;               case query_id of
      [*] = ;                  gc_gui_query_heroMakeSabotage : begin
      [*] = ;                     answers[no].tooltip := GetLocaleTableListItemByID('gui', 'sabotage'+IntToStr(i)+'.hint');
      [*] = ;                  end;
      [*] = ;                  gc_gui_query_heroArenaMakeBet : begin
      [*] = ;                     if i < 3 then
      [*] = ;                     begin
      [*] = ;                        var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;
      [*] = ;                        if plGold < (i + 1) * 100 then
      [*] = ;                        begin
      [*] = ;                           answers[no].tooltip := GetLocaleTableListItemByID('gui', 'query9060.'+IntToStr(i+1)+'.disabled.hint');
      [*] = ;                           result_enabled := false;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  gc_gui_query_playerMyLose : begin
      [*] = ;                     if (i = 2) and (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;                        result_visible := false;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gTutorial.map and (i = 2) and (query_id > gc_query_GuardMinIndex) and (query_id <= gc_query_GuardMaxIndex) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;         MapExecuteState('GetProvinceParserByUID');
      [*] = ;         var pProvince : Integer = IntRegister1;
      [*] = ;         var provInd : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;         var provRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;         if (provInd = 15) or (provRace > 1) then
      [*] = ;            result_enabled := false;
      [*] = ;      end;
      [*] = ;
      [*] = ;      answers[no].enabled := result_enabled;
      [*] = ;      if result_visible then
      [*] = ;      begin
      [*] = ;         text := QueryMachineResultGetKeyValue(answers[no].tag);
      [*] = ;         if text = '' then
      [*] = ;            text := QueryMachineResultGetTable(answers[no].tag) + ';' + QueryMachineQueryGetKey(answers[no].tag);
      [*] = ;         StringRegister0 := text;
      [*] = ;         MapExecuteState('StringReplaceParams');
      [*] = ;         answers[no].text := StringRegister1;
      [*] = ;         if answers[no].tooltip <> '' then
      [*] = ;         begin
      [*] = ;            StringRegister0 := answers[no].tooltip;
      [*] = ;            MapExecuteState('StringReplaceParams');
      [*] = ;            answers[no].tooltip := StringRegister1;
      [*] = ;         end;
      [*] = ;         no := no + 1;
      [*] = ;         if no >= cMaxAnswers then
      [*] = ;            break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_answers_handle,cTextAreaA,text_d);
      [*] = ;_gui_GetInterfaceElement(if_answers_handle,cHoverAreaA,elem_d);
      [*] = ;
      [*] = ;answers_text_width := answers_width-(elem_d.p_raw.pos.x*2);
      [*] = ;
      [*] = ;h := round(abs(elem_d.p_raw.pos.x - text_d.p_raw.pos.x));
      [*] = ;w := round(abs(elem_d.p_raw.pos.y - text_d.p_raw.pos.y));
      [*] = ;ypos := elem_d.p.pos.y;
      [*] = ;
      [*] = ;if rewards_handle <> 0 then
      [*] = ;begin
      [*] = ;   SetGUIElementPositionX(rewards_handle,(answers_width-GetGUIElementWidth(rewards_handle)) div 2);
      [*] = ;   SetGUIElementPositionY(rewards_handle,ypos);
      [*] = ;   ypos := ypos + GetGUIElementHeight(rewards_handle) + h;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   text := GetGUIWrappedTextFormatByFont(text_d.font_handle,answers[i].text,answers_text_width);
      [*] = ;   GetGUIElementFontTextFormatRect(text_d.font_handle, text, tw, th);
      [*] = ;
      [*] = ;   text_handle := AddNewElementParent('map.dialog.mousetrack', 'query.result', answers[i].tag, answers_handle);
      [*] = ;   SetGUIElementStringTag(text_handle, answers[i].id);
      [*] = ;   SetGUIElementFont(text_handle,text_d.font_handle);
      [*] = ;   SetGUIElementTextAlign(text_handle,gc_gui_align_middle.h, gc_gui_align_middle.v, 0, 0);
      [*] = ;   SetGUIElementTextFormatted(text_handle,true);
      [*] = ;   SetGUIElementColor(text_handle,text_d.color.r,text_d.color.g,text_d.color.b,text_d.color.a);
      [*] = ;
      [*] = ;   //if _log then _log_Values('TH|YPOS|H|'+text_d.font_handle,th,ypos,h,1,0,0);
      [*] = ;   SetGUIElementAllPositionRect(text_handle,elem_d.p.pos.x,ypos-h,answers_text_width,th+h*2);
      [*] = ;   SetGUIElementAlign(text_handle,gc_gui_align_parent_lt.h,gc_gui_align_parent_lt.v);
      [*] = ;   SetGUIElementText(text_handle,text);
      [*] = ;   if answers[i].tooltip <> '' then
      [*] = ;      SetGUIElementHint(text_handle,answers[i].tooltip);
      [*] = ;   SetGUIAllowEvents(text_handle, True, False, False);
      [*] = ;   SetGUIElementCursorByName(text_handle,cMouseCursor);
      [*] = ;   if isStrategyGameMode() then
      [*] = ;      SetGUIElementPressState(text_handle, cEventHandlerStrategy)
      [*] = ;   else
      [*] = ;      SetGUIElementPressState(text_handle, cEventHandler);
      [*] = ;   SetGUIElementHoverEnabled(text_handle,answers[i].enabled);
      [*] = ;   SetGUIElementEnabled(text_handle,answers[i].enabled);
      [*] = ;
      [*] = ;   SetGUIElementVisibleProperties(text_handle, 'DownProperty', 'map.dialog.window.answer.hover', 0, 0, 0, 0, cMouseCursorHoverIndex, elem_d.color.r, elem_d.color.g, elem_d.color.b, elem_d.color.a);
      [*] = ;   SetGUIElementVisibleProperties(text_handle, 'CheckOnProperty', 'gui.empty.dummy', 0, 0, 0, 0, cMouseCursorHoverIndex, text_d.color.r, text_d.color.g, text_d.color.b, text_d.color.a);
      [*] = ;   SetGUIElementVisibleProperties(text_handle, 'UpProperty', 'gui.empty.dummy', 0, 0, 0, 0, cMouseCursorHoverIndex, text_d.color.r, text_d.color.g, text_d.color.b, text_d.color.a);
      [*] = ;   SetGUIElementVisibleProperties(text_handle, 'DisableProperty', 'gui.empty.dummy', 0, 0, 0, 0, cMouseCursorDisabledIndex, gc_gui_fontcolor_Gray.r, gc_gui_fontcolor_Gray.g, gc_gui_fontcolor_Gray.b, gc_gui_fontcolor_Gray.a);
      [*] = ;   SetGUIElementVisibleProperties(text_handle, 'HoverProperty', 'map.dialog.window.answer.hover', 0, 0, 0, 0, cMouseCursorHoverIndex, elem_d.color.r, elem_d.color.g, elem_d.color.b, elem_d.color.a);
      [*] = ;
      [*] = ;   ypos := ypos + th;
      [*] = ;   if i <> (no-1) then
      [*] = ;      ypos := ypos + (h*2);
      [*] = ;end;
      [*] = ;
      [*] = ;ypos := ypos + (window_a_d.p.size.h-(elem_d.p.pos.y+elem_d.p.size.h));
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_answers_handle,cLeftCornerA,elem_l_d);
      [*] = ;_gui_GetInterfaceElement(if_answers_handle,cRightCornerA,elem_r_d);
      [*] = ;
      [*] = ;_sys_FillRect(pos,0,0,answers_width,ypos);
      [*] = ;i := _gui_CreateImageSlice_VVK('bcg',answers_handle,'common.window.background',gc_gui_align_parent_lt,pos);
      [*] = ;GUIElementSendToBack(i);
      [*] = ;
      [*] = ;if (queryStyle='6') then // diplomacy offer from other master
      [*] = ;begin
      [*] = ;   IntRegister0 := i;
      [*] = ;   GUIExecuteState('map.DrawDiplomacyOfferCover');
      [*] = ;end;
      [*] = ;
      [*] = ;_sys_FillRect(pos,elem_l_d.p.size.w-GetGUITextureWidth('map.dialog.window.answers.new.corner.left'),ypos-elem_l_d.p.size.h,0,0);
      [*] = ;lhd := _gui_CreateImage_VVK('',answers_handle,'map.dialog.window.answers.new.corner.left',gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;_sys_FillRect(pos,answers_width-elem_r_d.p.size.w,ypos-elem_r_d.p.size.h,0,0);
      [*] = ;rhd := _gui_CreateImage_VVK('',answers_handle,'map.dialog.window.answers.new.corner.right',gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;if not _gui_GetInterfaceElement(if_answers_handle,cBottomFrameA,elem_d) then
      [*] = ;elem_d.p.size.h := 0;
      [*] = ;i := (GetGUIElementPositionX(lhd)+GetGUIElementWidth(lhd));
      [*] = ;_sys_FillRect(pos,i,ypos-elem_d.p.size.h,GetGUIElementPositionX(rhd)-i,0);
      [*] = ;_gui_CreateImageSlice_VVK('',answers_handle,'map.dialog.window.answers.new.frame.bottom',gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;if not _gui_GetInterfaceElement(if_answers_handle,cLeftFrameA,elem_d) then
      [*] = ;   elem_d.p.size.w := 0;
      [*] = ;i := GetGUIElementPositionY(lhd);
      [*] = ;if i > 0 then
      [*] = ;begin
      [*] = ;   _sys_FillRect(pos,elem_d.p.size.w-GetGUITextureWidth('map.dialog.window.answers.new.frame.left'),0,0,i);
      [*] = ;   _gui_CreateImageSlice_VVK('',answers_handle,'map.dialog.window.answers.new.frame.left',gc_gui_align_parent_lt,pos);
      [*] = ;end;
      [*] = ;
      [*] = ;if not _gui_GetInterfaceElement(if_answers_handle,cRightFrameA,elem_d) then
      [*] = ;   elem_d.p.size.w := 0;
      [*] = ;i := GetGUIElementPositionY(rhd);
      [*] = ;if i > 0 then
      [*] = ;begin
      [*] = ;   _sys_FillRect(pos,answers_width-elem_d.p.size.w,0,0,i);
      [*] = ;   _gui_CreateImageSlice_VVK('',answers_handle,'map.dialog.window.answers.new.frame.right',gc_gui_align_parent_lt,pos);
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _log_Gui('Number of valid answers: '+IntToStr(no)+', WH: '+IntToStr(windowHandle));
      [*] = ;
      [*] = ;case gIntRegister_CurGameMode of
      [*] = ;   gc_GameModeStrategy : _gv_SetMapLock($10001,_log_name);
      [*] = ;   gc_GameModeAstral : _gv_SetAstralLock(1,_log_name);
      [*] = ;end;
      [*] = ;
      [*] = ;lhd := GetGUIElementIndexByNameParent('answers',windowHandle);
      [*] = ;if lhd <> 0 then
      [*] = ;   GUIElementSendToBack(lhd);
      [*] = ;
      [*] = ;lhd := GetGUIElementIndexByNameParent('hint',windowHandle);
      [*] = ;if lhd <> 0 then
      [*] = ;   GUIElementSendToBack(lhd);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_answers_handle,cHoverAreaA,elem_d);
      [*] = ;i := elem_d.p.size.h*(cMaxAnswersLines-1)+window_a_d.p.size.h;
      [*] = ;if _log then _log_Values('ADY',i,0,0,0,0,0);
      [*] = ;h := window_d.p.size.h+i;
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_answers_handle,cBottomScreenOffset,elem2_d);
      [*] = ;th := GetViewerHeight()-elem2_d.p.size.h;
      [*] = ;if lhd <> 0 then
      [*] = ;begin
      [*] = ;   _gui_GetInterfaceElement(if_handle,cAdvicePos,elem_d);
      [*] = ;   w := elem_d.p.pos.y;
      [*] = ;   h := h-w;
      [*] = ;end;
      [*] = ;
      [*] = ;j := (GetViewerWidth() div 8)+window_d.p.pos.x;
      [*] = ;if ((j+window_d.p.size.w) >= GetViewerWidth()) then
      [*] = ;   j := (GetViewerWidth() - (window_d.p.pos.x+window_d.p.size.w)) div 2;
      [*] = ;SetGUIElementPositionX(windowHandle,j);
      [*] = ;
      [*] = ;i := (th-h) div 2;
      [*] = ;if i < 0 then
      [*] = ;   i := 0;
      [*] = ;if (queryStyle='6') then // diplomacy offer query style
      [*] = ;   i := i-68;
      [*] = ;SetGUIElementPositionY(windowHandle,i-w);
      [*] = ;if _log then _log_Values('X|Y|DX|DY|H|WX',j,i,window_d.p.size.w,h,th,window_d.p.pos.x);
      [*] = ;
      [*] = ;{if _log then _log_Values('WDY|AY|VY',window_dy,answers_dy,GetViewerHeight(),0,0,0);
      [*] = ;window_dy := window_dy+answers_dy;
      [*] = ;window_dy := ((GetViewerHeight()-(window_dy+50)) div 2);
      [*] = ;if _log then _log_Values('WDY|ADY|Y',window_dy,answers_dy,GetGUIElementPositionY(windowHandle),0,0,0);
      [*] = ;if ((window_dy+answers_dy) < GetGUIElementPositionY(windowHandle)) then
      [*] = ;SetGUIElementPositionY(windowHandle,window_dy+answers_dy-20);}
      [*] = ;
      [*] = ;// new solution, to prevent window jumping when answer count changes
      [*] = ;{var maxSizeHeight : Integer = 540;
      [*] = ;const cAdviceVisualHeight = 64;
      [*] = ;const cBottomPanelMargin = 74;
      [*] = ;const cStyle4Off = -72;
      [*] = ;var offY : Integer = ((GetViewerHeight-maxSizeHeight+cAdviceVisualHeight) div 2);//-cAdviceVisualHeight;
      [*] = ;if (queryStyle='4') then offY := offY+cStyle4Off;
      [*] = ;SetGUIElementPositionY(windowHandle,offY);
      [*] = ;
      [*] = ;answers_dy := ((((GetViewerWidth() div 3)*2)-GetGUIElementWidth(windowHandle)) div 2);
      [*] = ;if answers_dy < GetGUIElementPositionX(windowHandle) then
      [*] = ;SetGUIElementPositionX(windowHandle,answers_dy);}
      [*] = ;
      [*] = ;// show bottom right info panel of the province in question with hero encounters 
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   var pCurProvince : Integer = _misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;   gIntRegister_MapSelectedHex := pCurProvince;
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;end;
      [*] = ;
      [*] = ;// show hero info button
      [*] = ;if (gIntRegister_MapTurnIteration = 1) and ((gIntRegister_MapCurHeroIndex >= 0) or (gIntRegister_MapActiveHeroHandle <> 0)) and (gIntRegister_CurGameMode = gc_GameModeStrategy) then
      [*] = ;   _gui_CreateButton('btn_hero_window', windowHandle, '', 'map.mainpanel.btn.nexthero', 'halParentLeft', 'valParentTop', 430, -30, 0, 0, cEventHandlerStrategy, 'gui|618', 0);
      [*] = ;
      [*] = ;SetGUIElementVisible(windowHandle, True);
      [*] = ;
      [*] = ;_gui_RootWindowAddM(windowHandle);
      [*] = ;SetGUIElementPressState(windowHandle,cEventModalQuery);
      [*] = ;
      [*] = ;SetGUIValue('QueryWindowID', IntToStr(windowHandle));
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;SetIntValueByName('ElementHandle', GetGUIElementUnderMouse());
      [*] = ;if (gIntRegister_CurGameMode=gc_GameModeMenu) then
      [*] = ;   GUIExecuteState('OnMouseEnter')
      [*] = ;else
      [*] = ;   GUIExecuteState('DoOnMouseEnter');
      [*] = ;IntRegister0 := query_id;
      [*] = ;GUIExecuteState('VVK.GetAchievementFromQuery');
      [*] = ;if IntRegister0 <> 0 then
      [*] = ;   _achievement_Trigger(IntRegister0,'');
      [*] = ;IntRegister0 := windowHandle;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

