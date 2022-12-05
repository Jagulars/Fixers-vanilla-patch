section.begin
   Name = battle.CreateTooltip
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.CREATETOOLTIP';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;
      [*] = ;procedure FormatHitText(min_damage,max_damage,death : Integer;var txt : String);
      [*] = ;begin
      [*] = ;   var textHeader : String;
      [*] = ;
      [*] = ;   textHeader := GetLocaleTableListItemByID('gui', '696')+': ';
      [*] = ;   if (min_damage<>max_damage) then
      [*] = ;      textHeader := textHeader+IntToStr(min_damage)+'-'+IntToStr(max_damage)
      [*] = ;   else
      [*] = ;      textHeader := textHeader+IntToStr(min_damage);
      [*] = ;
      [*] = ;   if (death = 100) then
      [*] = ;      textHeader := textHeader+' ('+GetLocaleTableListItemByID('gui', '697')+')'
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (death > 0) then
      [*] = ;         textHeader := textHeader+' ('+GetLocaleTableListItemByID('gui', '698')+')';
      [*] = ;   end;
      [*] = ;   txt := textHeader;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FormatSpellHitText(min_damage,max_damage,death,duration,power : Integer; negative : Boolean;var txt : String);
      [*] = ;begin
      [*] = ;   var textHeader : String;
      [*] = ;
      [*] = ;   if min_damage <> -1 then
      [*] = ;   begin
      [*] = ;      if max_damage <> -1 then
      [*] = ;      begin
      [*] = ;         if not negative then
      [*] = ;            textHeader := GetLocaleTableListItemByID('glossary', 'skill.39')+': '+IntToStr(min_damage)
      [*] = ;         else
      [*] = ;            FormatHitText(min_damage,max_damage,death,textHeader);
      [*] = ;      end
      [*] = ;      else // duration
      [*] = ;         textHeader := GetLocaleTableListItemByID('gui', '86')+': '+IntToStr(duration);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      textHeader := '';
      [*] = ;   //textHeader :=IntToStr(min_damage)+','+IntToStr(max_damage)+','+IntToStr(death)+','+IntToStr(duration)+','+IntToStr(power)+','+BoolToStr(negative);
      [*] = ;   txt := textHeader;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure IncludeTerrainInfo(src_txt,th,tt : String;var text : String);
      [*] = ;begin
      [*] = ;   if th='' then
      [*] = ;      text := src_txt
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var temp_str : String;
      [*] = ;
      [*] = ;      if src_txt <> '' then
      [*] = ;         temp_str := src_txt+gc_gui_BreakLine+gc_gui_BreakLine+'%color(8E190D)%'+th+'%color(default)%'
      [*] = ;      else
      [*] = ;         temp_str := '%color(8E190D)%'+th+'%color(default)%';
      [*] = ;      if tt <> '' then
      [*] = ;         temp_str := temp_str+gc_gui_BreakLine+tt;
      [*] = ;      text := temp_str;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetTargetSector(tGOHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var angle, x, y, z, enX, enZ, enDirX, enDirY,enDirZ : Float;
      [*] = ;
      [*] = ;   GetTrackNodePositionByHandle(gIntRegister_BeforeEndTrackNode, x, y, z);
      [*] = ;
      [*] = ;   enX := GetGameObjectPositionXByHandle(tGOHandle) - x;
      [*] = ;   enZ := GetGameObjectPositionZByHandle(tGOHandle) - z;
      [*] = ;   enDirX := GetGameObjectTransformedVirtualDirectionXByHandle(tGOHandle);
      [*] = ;   enDirY := GetGameObjectTransformedVirtualDirectionYByHandle(tGOHandle);
      [*] = ;   enDirZ := GetGameObjectTransformedVirtualDirectionZByHandle(tGOHandle);
      [*] = ;
      [*] = ;   angle := VectorAngle(enX, 0, enZ, enDirX, enDirY, enDirZ);
      [*] = ;   Result := Round(Abs(angle / 60));
      [*] = ;   _log_Values('Angle|Side',Round(angle),Result,0,0,0,0);
      [*] = ;end;
      [*] = ;
      [*] = ;function DoBuildTooltip(const pEndHexCell, selectedUID, endHexUID : Integer; extended : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   if (pEndHexCell<>0) then
      [*] = ;   begin
      [*] = ;      var goSelHandle, goEndHandle, plEndHandle : Integer = 0;
      [*] = ;      var goEndName, textHeader, text : String = '';
      [*] = ;      var enemy : Boolean = False;
      [*] = ;      var terrHeader, terrText, tmp_text : String;
      [*] = ;      goSelHandle := GetGameObjectHandleByUniqueId(selectedUID);
      [*] = ;      var actAbility : Integer = GetGameObjectIntValueIndByHandle(goSelHandle, gc_stack_unit_iActiveAbility);
      [*] = ;
      [*] = ;      IntRegister0 := ParserGetIntValueByKeyByHandle(pEndHexCell, 'Type');
      [*] = ;      MapExecuteState('GetBFObjectParserByID');
      [*] = ;      var pBFObject : Integer = IntRegister1;
      [*] = ;      var moveCost : Integer = ParserGetIntValueByKeyByHandle(pBFObject, 'MoveCost');
      [*] = ;      var stamCost : Integer = ParserGetIntValueByKeyByHandle(pBFObject, 'StamCost');
      [*] = ;      var counterAttack : Integer = ParserGetIntValueByKeyByHandle(pBFObject, 'CounterAttack');
      [*] = ;      var defence : Integer = ParserGetIntValueByKeyByHandle(pBFObject, 'Defence');
      [*] = ;      var rangedDefence : Integer = ParserGetIntValueByKeyByHandle(pBFObject, 'RangedDefence');
      [*] = ;      var shootingRange : Integer = ParserGetIntValueByKeyByHandle(pBFObject, 'ShootingRange');
      [*] = ;      var rangedAttack : Integer = ParserGetIntValueByKeyByHandle(pBFObject, 'RangedAttack');
      [*] = ;
      [*] = ;      var maxLife, curLife, curStam, curMoral : Integer = 0;
      [*] = ;      if (endHexUID<>0) then
      [*] = ;      begin
      [*] = ;         goEndHandle := GetGameObjectHandleByUniqueId(endHexUID);
      [*] = ;         plEndHandle := GetGameObjectPlayerHandleByHandle(goEndHandle);
      [*] = ;         goEndName := GetLocaleTableListItemByID('unit', IntToStr(GetGameObjectIntValueIndByHandle(goEndHandle, gc_stack_unit_iUnitID)));
	  [*] = ;         if GetGameObjectBoolValueIndByHandle(goEndHandle, gc_stack_unit_bIsHero) then
	  [*] = ;         begin
	  [*] = ;            var mapHeroUID : Integer = GetGameObjectIntValueIndByHandle(goEndHandle, gc_stack_unit_iHeroUID);
	  [*] = ;            var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(mapHeroUID);
	  [*] = ;            var classIndex : Integer = _hero_GetHeroClassIndex(mapHeroHandle);
	  [*] = ;            goEndName := GetLocaleTableListItemByID('hero_class', IntToStr(classIndex));
	  [*] = ;         end;
      [*] = ;         goEndName := goEndName +'  ('+GetLocaleTableListItemByID('glossary', 'skill.1')+' '+IntToStr(GetGameObjectIntValueIndByHandle(goEndHandle, gc_stack_unit_iLevel))+')';
      [*] = ;         if (plEndHandle<>GetPlayerHandleInterfaceIO()) then
      [*] = ;            enemy := True;
      [*] = ;         maxLife := _unit_GetProperty(goEndHandle, gc_battle_unit_iMaxLife);
      [*] = ;         curLife := _unit_GetProperty(goEndHandle, gc_battle_unit_iCurLife);
      [*] = ;         curStam := _unit_GetProperty(goEndHandle, gc_battle_unit_iCurStamina);
      [*] = ;         curMoral := _unit_GetProperty(goEndHandle, gc_battle_unit_iCurMoral);
      [*] = ;      end;
      [*] = ;
      [*] = ;      begin
      [*] = ;         var lineCount : Integer = 0;
      [*] = ;
      [*] = ;         IntRegister0 := ParserGetIntValueByKeyByHandle(pEndHexCell, 'Type');
      [*] = ;         GUIExecuteState('battle.GetTerrainInfoByType');
      [*] = ;         textHeader := GetLocaleTableListItemByID(StringRegister0, IntToStr(IntRegister1));
      [*] = ;
      [*] = ;         if (not gBoolRegister_BattlePlaceMode) then
      [*] = ;         begin
      [*] = ;            if (moveCost>0) then text := GetLocaleTableListItemByID('gui', '689')+': '+IntToStr(moveCost);
      [*] = ;            if (stamCost>0) then text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '690')+': '+IntToStr(stamCost);
      [*] = ;         end;
      [*] = ;         if (counterAttack<>0) then lineCount := lineCount+1;
      [*] = ;         if (defence<>0) then lineCount := lineCount+1;
      [*] = ;         if (rangedDefence<>0) then lineCount := lineCount+1;
      [*] = ;         if (shootingRange<>0) then lineCount := lineCount+1;
      [*] = ;         if (rangedAttack<>0) then lineCount := lineCount+1;
      [*] = ;         if (lineCount>0) then
      [*] = ;         begin
      [*] = ;            if (text<>'') then
      [*] = ;               text := text+gc_gui_BreakLine+gc_gui_BreakLine;
      [*] = ;
      [*] = ;            if (counterAttack<>0) then begin
      [*] = ;               text := text+GetLocaleTableListItemByID('gui', '691')+': ';
      [*] = ;               if (counterAttack>0) then text := text+'+';
      [*] = ;               text := text+IntToStr(counterAttack);
      [*] = ;               if (lineCount>1) then
      [*] = ;               begin
      [*] = ;                  text := text+gc_gui_BreakLine;
      [*] = ;                  lineCount := lineCount-1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (defence<>0) then begin
      [*] = ;               text := text+GetLocaleTableListItemByID('gui', '692')+': ';
      [*] = ;               if (defence>0) then text := text+'+';
      [*] = ;               text := text+IntToStr(defence);
      [*] = ;               if (lineCount>1) then
      [*] = ;               begin
      [*] = ;                  text := text+gc_gui_BreakLine;
      [*] = ;                  lineCount := lineCount-1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (rangedDefence<>0) then begin
      [*] = ;               text := text+GetLocaleTableListItemByID('gui', '693')+': ';
      [*] = ;               if (rangedDefence>0) then text := text+'+';
      [*] = ;               text := text+IntToStr(rangedDefence);
      [*] = ;               if (lineCount>1) then
      [*] = ;               begin
      [*] = ;                  text := text+gc_gui_BreakLine;
      [*] = ;                  lineCount := lineCount-1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (shootingRange<>0) then
      [*] = ;            begin
      [*] = ;               text := text+GetLocaleTableListItemByID('gui', '694')+': ';
      [*] = ;               if (shootingRange>0) then text := text+'+';
      [*] = ;               text := text+IntToStr(shootingRange);
      [*] = ;               if (lineCount>1) then
      [*] = ;               begin
      [*] = ;                  text := text+gc_gui_BreakLine;
      [*] = ;                  lineCount := lineCount-1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (rangedAttack<>0) then
      [*] = ;            begin
      [*] = ;               text := text+GetLocaleTableListItemByID('gui', '695')+': ';
      [*] = ;               if (rangedAttack>0) then text := text+'+';
      [*] = ;               text := text+IntToStr(rangedAttack);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         terrHeader := textHeader;
      [*] = ;         terrText := text;
      [*] = ;         textHeader := '';
      [*] = ;         text := '';
      [*] = ;      end;
      [*] = ;
	  [*] = ;      
      [*] = ;	   if (actAbility = gc_ability_healing) or (actAbility = gc_ability_repair) then
	  [*] = ;      begin
      [*] = ;         if actAbility = gc_ability_healing then
      [*] = ;         begin
	  [*] = ;            textHeader := GetLocaleTableListItemByID('glossary', 'skill.39');
      [*] = ;            IntRegister0 := 0;
      [*] = ;         end
      [*] = ;         else begin
	  [*] = ;            textHeader := GetLocaleTableListItemByID('ability', '68');
      [*] = ;            IntRegister0 := 1;
      [*] = ;         end;
      [*] = ;         GameObjectExecuteStateByHandle(goEndHandle, 'IsHealTarget');
      [*] = ;         if (IntRegister1 = 2) and (endHexUID<>0) and (GetGameObjectPlayerHandleByHandle(goEndHandle)=GetGameObjectPlayerHandleByHandle(goSelHandle)) then
	  [*] = ;         begin
      [*] = ;            var healHP : Integer;
      [*] = ;            if actAbility = gc_ability_healing then
      [*] = ;               healHP := _unit_CheckAbility(goSelHandle, gc_ability_healing)
      [*] = ;            else
      [*] = ;               healHP := _unit_CheckAbility(goSelHandle, gc_ability_repair);
      [*] = ;
      [*] = ;            var lostHP : Integer = maxLife - curLife;
      [*] = ;
      [*] = ;            var min_heal : Integer = min(healHP - 1, lostHP);
      [*] = ;            var max_heal : Integer = min(healHP + 1, lostHP);
      [*] = ;
      [*] = ;            textHeader := textHeader + ': ';
      [*] = ;            if (min_heal < max_heal) then
      [*] = ;               textHeader := textHeader+IntToStr(min_heal)+'-'+IntToStr(max_heal)
      [*] = ;            else
      [*] = ;               textHeader := textHeader+IntToStr(min_heal);
	  [*] = ;         end;
      [*] = ;
      [*] = ;         if (extended) then
      [*] = ;         begin
      [*] = ;            text := GetLocaleTableListItemByID('gui', '685')+': '+IntToStr(curLife)+'/'+IntToStr(maxLife);
      [*] = ;            text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '686')+': '+IntToStr(curStam);
      [*] = ;            text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '687')+': '+IntToStr(curMoral);
      [*] = ;         end;
      [*] = ;            
      [*] = ;         tmp_text := text;
      [*] = ;         IncludeTerrainInfo(tmp_text,terrHeader,terrText,text);
	  [*] = ;      end
      [*] = ;      else
      [*] = ;      if (gIntRegister_CurSpell>0) then
      [*] = ;      begin
      [*] = ;         textHeader := '';
      [*] = ;         if (endHexUID<>0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := endHexUID;
      [*] = ;            IntRegister1 := gIntRegister_CurSpell;
      [*] = ;            GameObjectExecuteStateByHandle(GetGameObjectHandleByUniqueId(selectedUID),'GetPossibleSpellHit');
      [*] = ;            FormatSpellHitText( IntRegister0, IntRegister1, IntRegister2, IntRegister3, IntRegister4, BoolRegister0, textHeader);
      [*] = ;
      [*] = ;            if textHeader = '' then
      [*] = ;               textHeader := GetLocaleTableListItemByID('spell', IntToStr(gIntRegister_CurSpell))
      [*] = ;            else
      [*] = ;               textHeader := GetLocaleTableListItemByID('spell', IntToStr(gIntRegister_CurSpell))+gc_gui_BreakLine+textHeader;
      [*] = ;            if (extended) then
      [*] = ;            begin
      [*] = ;               text := GetLocaleTableListItemByID('gui', '685')+': '+IntToStr(curLife)+'/'+IntToStr(maxLife);
      [*] = ;               text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '686')+': '+IntToStr(curStam);
      [*] = ;               text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '687')+': '+IntToStr(curMoral);
      [*] = ;               {if (enemy) then
      [*] = ;               begin
      [*] = ;                  var resist : Integer = _unit_GetProperty(goEndHandle, gc_battle_unit_iResist);
      [*] = ;                  text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '688')+': '+IntToStr(resist);
      [*] = ;               end;}
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         //if (text<>'') then
      [*] = ;         //   text := text+gc_gui_BreakLine+gc_gui_BreakLine;
      [*] = ;         //text := text+GetLocaleTableListItemByID('spell', IntToStr(gIntRegister_CurSpell));
      [*] = ;         //var textSpell : String = GetLocaleTableListItemByID('spell', IntToStr(gIntRegister_CurSpell)+'.description');
      [*] = ;
      [*] = ;         {const cDelimiterChar = 13; // 46 == .
      [*] = ;         const cQuoteChar = 34; // 34 == "
      [*] = ;         if IsDelimiterCharExists(textSpell, cDelimiterChar) then
      [*] = ;         begin
      [*] = ;            if GetDelimiterStringCount(textSpell, cDelimiterChar, cQuoteChar) > 2 then
      [*] = ;            begin
      [*] = ;               var pos : Integer = StrPos(gc_gui_BreakLine, textSpell);
      [*] = ;               var t1 : String = SubStr(textSpell, 0, pos+1);;
      [*] = ;               textSpell := StrReplace(textSpell, t1, '');
      [*] = ;
      [*] = ;               pos := StrPos(gc_gui_BreakLine, textSpell);
      [*] = ;               t1 := SubStr(textSpell, 0, pos+1);;
      [*] = ;               textSpell := StrReplace(textSpell, t1, '');
      [*] = ;            end;
      [*] = ;         end;}
      [*] = ;         //if (textHeader<>'') and (not extended) then
      [*] = ;         //   text := text+gc_gui_BreakLine;
      [*] = ;         tmp_text := text; //{+gc_gui_BreakLine}+GetLocaleTableListItemByID('spell', IntToStr(gIntRegister_CurSpell))+gc_gui_BreakLine+textSpell;
      [*] = ;         IncludeTerrainInfo(tmp_text,terrHeader,terrText,text);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (endHexUID=0) then
      [*] = ;      begin
      [*] = ;         text := terrText;
      [*] = ;         textHeader := terrHeader;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         textHeader := goEndName;
      [*] = ;         if (extended) then
      [*] = ;         begin
      [*] = ;            text := GetLocaleTableListItemByID('gui', '685')+': '+IntToStr(curLife)+'/'+IntToStr(maxLife);
      [*] = ;            text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '686')+': '+IntToStr(curStam);
      [*] = ;            text := text+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '687')+': '+IntToStr(curMoral);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (selectedUID<>0) then
      [*] = ;         begin
      [*] = ;            if (enemy) and (not gBoolRegister_BattlePlaceMode) then
      [*] = ;            begin
      [*] = ;               var bCanAct : Boolean = GetGameObjectBoolValueIndByHandle(goSelHandle, gc_stack_unit_bCanAct);
      [*] = ;               var hit_stats : array [0..3] of Integer;
      [*] = ;               var isShoot, isShootable : Boolean;
      [*] = ;               var range : Integer = _unit_GetProperty(goSelHandle, gc_battle_unit_iShootingRange);
      [*] = ;               var rangedAttack : Integer = _unit_GetProperty(goSelHandle, gc_battle_unit_iRangedAttack);
      [*] = ;               var ammo : Integer = _unit_GetProperty(goSelHandle, gc_battle_unit_iCurAmmo);
      [*] = ;               var maxAmmo : Integer = _unit_GetProperty(goSelHandle, gc_battle_unit_iMaxAmmo);
      [*] = ;               _unit_IsMyShootEndPoint(goSelHandle, gIntRegister_EndTrackNode, gBoolRegister_BattlePlaceMode, isShoot, isShootable);
      [*] = ;               if (isShoot) and (not GetBoolValueByName('KeyPressedCtrl')) then
      [*] = ;               begin
      [*] = ;                  if (bCanAct) and GetGameObjectBoolValueIndByHandle(goSelHandle, gc_stack_unit_bCanShoot) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := GetGameObjectUniqueIdByHandle(goEndHandle);
      [*] = ;                     GameObjectExecuteStateByHandle(goSelHandle,'GetPossibleRangedHit');
      [*] = ;                     FormatHitText( IntRegister0, IntRegister1, IntRegister2, textHeader);
      [*] = ;
      [*] = ;                     if (extended) then
      [*] = ;                        text := text+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '699')+': '+IntToStr(ammo)+'/'+IntToStr(maxAmmo);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var endPointValid : Boolean;
      [*] = ;                  var goEnemyUID : Integer;
      [*] = ;                  _unit_IsValidEndPoint(goSelHandle, gIntRegister_EndTrackNode, true, false, endPointValid, goEnemyUID);
      [*] = ;                  if (endPointValid) then
      [*] = ;                  begin
      [*] = ;                     var bCanMelee : Boolean = GetGameObjectBoolValueIndByHandle(goSelHandle, gc_stack_unit_bCanMelee);
      [*] = ;                     if bCanMelee and bCanAct and (_unit_CheckAbility(goSelHandle, gc_ability_does_not_fight) = 0) then
      [*] = ;                     begin
      [*] = ;                        var wX, wY, wZ : Float;
      [*] = ;                        var pHexHandle : Integer;
      [*] = ;
      [*] = ;                        GetCurrentMouseWorldCoord(wX, wY, wZ);
      [*] = ;                        pHexHandle := _map_GetHexByTNHandle(GetNearestTrackNodeHandle(wX, wZ, -1));
      [*] = ;
      [*] = ;                        IntRegister0 := GetGameObjectUniqueIdByHandle(goEndHandle);
      [*] = ;                        IntRegister1 := ParserGetIntValueByKeyByHandle(pHexHandle,'X');
      [*] = ;                        IntRegister2 := ParserGetIntValueByKeyByHandle(pHexHandle,'Y');
      [*] = ;                        IntRegister3 := GetTargetSector(goEndHandle);
      [*] = ;                        GameObjectExecuteStateByHandle(goSelHandle,'GetPossibleMeleeHit');
      [*] = ;                        FormatHitText( IntRegister0, IntRegister1, IntRegister2, textHeader);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                        textHeader := GetLocaleTableListItemByID('gui', '700');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if (extended) then
      [*] = ;                        textHeader := goEndName;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         tmp_text := text;
      [*] = ;         IncludeTerrainInfo(tmp_text,terrHeader,terrText,text);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (text <> '') or (textHeader <> '') then
      [*] = ;      begin
      [*] = ;         if gc_RecycleGUI then
      [*] = ;         begin
      [*] = ;            var elmTooltip : Integer = _gui_GetWindow('battle_tooltip');
      [*] = ;            if (elmTooltip <> 0) then
      [*] = ;               _gui_Show(elmTooltip, false);
      [*] = ;         end;
      [*] = ;         Result := _gui_CreateCommonWindow(textHeader,text,'battle_tooltip','halLeft','valTop',0,0,0,0,false,false,false,6,false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoRestrictOffsetTooltip(elmHandle : Integer);
      [*] = ;begin
      [*] = ;   var bnd_box : TRectangle;
      [*] = ;   var p : Integer;
      [*] = ;
      [*] = ;   _sys_FillRect(bnd_box,0,0,GetViewerWidth(),GetViewerHeight());
      [*] = ;   p := _gui_GetWindow(gc_gui_CPBottomName+'.safe_area');
      [*] = ;   if p <> 0 then
      [*] = ;      bnd_box.size.h := bnd_box.size.h-GetGUIElementHeight(p)
      [*] = ;   else
      [*] = ;      bnd_box.size.h := bnd_box.size.h-40;
      [*] = ;
      [*] = ;   _gui_AlignWindowByCursorExt_VVK(elmHandle,bnd_box);
      [*] = ;end;
      [*] = ;
      [*] = ;{procedure DoRestrictOffsetTooltip(elmHandle : Integer);
      [*] = ;begin
      [*] = ;   var sizeElmHnd : Integer = GetGUIElementIndexByNameParent('size_dummy', elmHandle);
      [*] = ;
      [*] = ;   if (sizeElmHnd<>0) then
      [*] = ;   begin
      [*] = ;      var mX, mY : Integer;
      [*] = ;      var xOff, yOff : Integer = 0;
      [*] = ;      GetGUICurrentMouseCoord(mX, mY);
      [*] = ;      case GetGUICursorByIndex() of
      [*] = ;         3, 7 : begin
      [*] = ;            xOff := 2;
      [*] = ;            yOff := 48;
      [*] = ;         end;
      [*] = ;         2, 5 : begin
      [*] = ;            xOff := 2;
      [*] = ;            yOff := 50;
      [*] = ;         end;
      [*] = ;         6 : begin
      [*] = ;            xOff := 7;
      [*] = ;            yOff := 48;
      [*] = ;         end;
      [*] = ;         4 : begin
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
      [*] = ;         restrictBottomOff := GetViewerHeight-(mY+yOff+realH)-8;
      [*] = ;      var restrictXOff, restrictYOff : Integer = 0;
      [*] = ;      if (restrictRightOff<0) then
      [*] = ;         restrictXOff := restrictRightOff;
      [*] = ;      if (restrictBottomOff<0) then
      [*] = ;         restrictYOff := restrictBottomOff;
      [*] = ;      if (restrictLeftOff<0) then
      [*] = ;         restrictXOff := -restrictLeftOff;
      [*] = ;
      [*] = ;      SetGUIElementPositionX(elmHandle, mX+xOff+restrictXOff);
      [*] = ;      SetGUIElementPositionY(elmHandle, mY+yOff+restrictYOff);
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;// Selected unit
      [*] = ;// Unit undermouse
      [*] = ;// Terrain undermouse
      [*] = ;var pEndHexCell : Integer = gIntRegister_EndHexCell;
      [*] = ;var selectedUID : Integer = gIntRegister_SelectedUID;
      [*] = ;var endHexUID : Integer = gIntRegister_EndHexUID;
      [*] = ;var hoverGOHandle : Integer = GetGameObjectHandleByUniqueId(endHexUID);
      [*] = ;var elmTooltip : Integer = _gui_GetWindow('battle_tooltip.common_window');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(pEndHexCell)+','+IntToStr(elmTooltip)+','+BoolToStr(gBoolRegister_ShowBattleExtendedHint)+']',_log_trace);
      [*] = ;
      [*] = ;if (hoverGOHandle <> 0) and (not GetGameObjectVisibleByHandle(hoverGOHandle)) then
      [*] = ;   endHexUID := 0;
      [*] = ;
      [*] = ;if (pEndHexCell=0) or (GetGUIElementUnderMouse()<>0) then
      [*] = ;begin
      [*] = ;   if elmTooltip <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_RecycleGUI then
      [*] = ;         _gui_Show(_gui_GetWindow('battle_tooltip'), false)
      [*] = ;      else
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('battle_tooltip'),0);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (elmTooltip = 0) or (gIntRegister_EndHexCell<>gIntRegister_GUIBattleTooltipLastEndHexCell) then
      [*] = ;      elmTooltip := DoBuildTooltip(pEndHexCell,selectedUID,endHexUID,gBoolRegister_ShowBattleExtendedHint);
      [*] = ;   if elmTooltip <> 0 then
      [*] = ;      DoRestrictOffsetTooltip(elmTooltip);
      [*] = ;   if (not gBoolRegister_ShowBattleExtendedHint) then
      [*] = ;      _gui_DelayExecuteStateOneInstance('battle.CreateTooltipExt', gProfile.exthintdelay)
      [*] = ;   else
      [*] = ;      gBoolRegister_ShowBattleExtendedHint := False;
      [*] = ;end;
      [*] = ;gIntRegister_GUIBattleTooltipLastEndHexCell := pEndHexCell;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

