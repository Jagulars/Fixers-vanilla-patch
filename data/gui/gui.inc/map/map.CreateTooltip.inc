section.begin
   Name = map.CreateTooltip
   Code : struct.begin
      [*] = ;function DoBuildTooltip(const ritualID, pStratHex : Integer; extended : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   if (pStratHex<>0) then
      [*] = ;   begin
      [*] = ;      var textHeader, text : String = '';
      [*] = ;      if (ritualID>0) then
      [*] = ;      begin
      [*] = ;         var pRitual : Integer = ParserSelectByHandleByIndex(gPrototypeData.rituals.handle, ritualID);
      [*] = ;         var bOnAlly : Boolean = ParserGetBoolValueByKeyByHandle(pRitual, 'OnAlly');
      [*] = ;         var bOnEnemy : Boolean = ParserGetBoolValueByKeyByHandle(pRitual, 'OnEnemy');
      [*] = ;         var bOnHero : Boolean = ParserGetBoolValueByKeyByHandle(pRitual, 'OnHero');
      [*] = ;
      [*] = ;         if (bOnHero) then
      [*] = ;         textHeader := GetLocaleTableListItemByID('gui', '721')
      [*] = ;         else
      [*] = ;         if (bOnAlly) and (bOnEnemy) then
      [*] = ;         textHeader := GetLocaleTableListItemByID('gui', '722')
      [*] = ;         else
      [*] = ;         if (bOnEnemy) then
      [*] = ;         textHeader := GetLocaleTableListItemByID('gui', '723')
      [*] = ;         else
      [*] = ;         textHeader := GetLocaleTableListItemByID('gui', '724');
      [*] = ;
      [*] = ;         var textRitual : String = GetLocaleTableListItemByID('ritual', IntToStr(ritualID)+'.description');
      [*] = ;         text := GetLocaleTableListItemByID('ritual', IntToStr(ritualID));
      [*] = ;         text := text+gc_gui_BreakLine+textRitual;
      [*] = ;
      [*] = ;         {if (bOnHero) then
      [*] = ;         text := text+gc_gui_BreakLine+gc_gui_BreakLine+'”кажите геро€ дл€ ритуала'
      [*] = ;         else
      [*] = ;         if (bOnAlly) and (bOnEnemy) then
      [*] = ;         text := text+gc_gui_BreakLine+gc_gui_BreakLine+'”кажите провинцию дл€ ритуала'
      [*] = ;         else
      [*] = ;         if (bOnEnemy) then
      [*] = ;         text := text+gc_gui_BreakLine+gc_gui_BreakLine+'”кажите вражескую провинцию дл€ ритуала'
      [*] = ;         else
      [*] = ;         text := text+gc_gui_BreakLine+gc_gui_BreakLine+'”кажите вашу провинцию дл€ ритуала';}
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gc_RecycleGUI then
      [*] = ;      begin
      [*] = ;         var elmTooltip : Integer = _gui_GetWindow('map_tooltip');
      [*] = ;         if (elmTooltip <> 0) then
      [*] = ;            _gui_Show(elmTooltip, false);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (text='') and (textHeader='') then
      [*] = ;         Result := 0
      [*] = ;      else
      [*] = ;         Result := _gui_CreateCommonWindow(textHeader,text,'map_tooltip','halLeft','valTop',0,0,0,0,false,false,false,6,false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoRestrictOffsetTooltip(elmHandle : Integer);
      [*] = ;begin
      [*] = ;   var sizeElmHnd : Integer = GetGUIElementIndexByNameParent('size_dummy', elmHandle);
      [*] = ;
      [*] = ;   if (sizeElmHnd<>0) then
      [*] = ;   begin
      [*] = ;      var mX, mY : Integer;
      [*] = ;      var xOff, yOff : Integer = 0;
      [*] = ;      GetGUICurrentMouseCoord(mX, mY);
      [*] = ;      case GetGUICursorByIndex of
      [*] = ;         3, 7 :
      [*] = ;         begin
      [*] = ;            xOff := 2;
      [*] = ;            yOff := 48;
      [*] = ;         end;
      [*] = ;         2, 5 :
      [*] = ;         begin
      [*] = ;            xOff := 2;
      [*] = ;            yOff := 50;
      [*] = ;         end;
      [*] = ;         6 :
      [*] = ;         begin
      [*] = ;            xOff := 7;
      [*] = ;            yOff := 48;
      [*] = ;         end;
      [*] = ;         4 :
      [*] = ;         begin
      [*] = ;            xOff := 2;
      [*] = ;            yOff := 48;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            xOff := 2;
      [*] = ;            yOff := 40;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var realW : Integer = GetGUIElementWidth(sizeElmHnd);
      [*] = ;      var realH : Integer = GetGUIElementHeight(sizeElmHnd);
      [*] = ;      var restrictLeftOff : Integer = 16;
      [*] = ;      var restrictRightOff : Integer = GetViewerWidth-(mX+xOff+realW)-8;
      [*] = ;      var restrictBottomOff : Integer;
      [*] = ;
      [*] = ;      if (mY+yOff+realH>(GetViewerHeight-64)) then
      [*] = ;      restrictBottomOff := GetViewerHeight-(mY+yOff+realH)-8;
      [*] = ;      var restrictXOff, restrictYOff : Integer = 0;
      [*] = ;      if (restrictRightOff<0) then
      [*] = ;      restrictXOff := restrictRightOff;
      [*] = ;      if (restrictBottomOff<0) then
      [*] = ;      restrictYOff := restrictBottomOff;
      [*] = ;      if (restrictLeftOff<0) then
      [*] = ;      restrictXOff := -restrictLeftOff;
      [*] = ;
      [*] = ;      SetGUIElementPositionX(elmHandle, mX+xOff+restrictXOff);
      [*] = ;      SetGUIElementPositionY(elmHandle, mY+yOff+restrictYOff);
      [*] = ;      //SetGUIElementPositionX(elmHandle, 1024);
      [*] = ;      //SetGUIElementPositionY(elmHandle, 1033-realH);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// Selected unit
      [*] = ;// Unit undermouse
      [*] = ;// Terrain undermouse
      [*] = ;var curHex : Integer = gIntRegister_MapUnderCursorHex; //Ёксперимент, обновл€ть инфопанель при наведении на провинцию
      [*] = ;
      [*] = ;var pProvFog : Integer = ParserSelectByHandleByKey(gIntRegister_MapUnderCursorHex, 'Fog');
      [*] = ;var fog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var isPlayable : Boolean = False;
      [*] = ;if (curHex<>0) then
      [*] = ;begin
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(curHex, 'DummyUID'); //For non hex castle
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;   if dummyHandle <> 0 then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'IsPlayable');
      [*] = ;      isPlayable := BoolRegister0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var ritualID : Integer =  gIntRegister_MapPickedRitualID;
      [*] = ;
      [*] = ;var elmTooltip : Integer = _gui_GetWindow('map_tooltip');
      [*] = ;if (ritualID = 0) or ((curHex = 0) or ((fog > 0) and gGame.fog) or (not isPlayable)) then
      [*] = ;begin
      [*] = ;   if elmTooltip <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_RecycleGUI then
      [*] = ;         _gui_Show(elmTooltip,false)
      [*] = ;      else
      [*] = ;         _gui_RootWindowRemoveWithFade(elmTooltip,0);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   elmTooltip := DoBuildTooltip(ritualID, gIntRegister_MapUnderCursorHex, gBoolRegister_ShowMapExtendedHint);
      [*] = ;   if elmTooltip <> 0 then
      [*] = ;      DoRestrictOffsetTooltip(elmTooltip);
      [*] = ;   if (not gBoolRegister_ShowMapExtendedHint) then
      [*] = ;      _gui_DelayExecuteStateOneInstance('map.CreateTooltipExt', 0.875)
      [*] = ;   else
      [*] = ;      gBoolRegister_ShowMapExtendedHint := False;
      [*] = ;end;
   struct.end
section.end

