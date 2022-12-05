section.begin
   Name = VVK.DoProgressGUI
   Code : struct.begin
      [*] = ;var whd,mx,my : Integer;
      [*] = ;
      [*] = ;GetGUICurrentMouseCoord(mX, mY);
      [*] = ;
      [*] = ;var curTime : Float = GetGameTime;
      [*] = ;_gui_ft_ProcessTimer(curTime,mx,my);
      [*] = ;
      [*] = ;// show achievement window on bottom right
      [*] = ;if _achievement_IsPending() then
      [*] = ;   _cmd_Post('.generalshowachievements','','');
      [*] = ;
      [*] = ;// fade achievement window on bottom right
      [*] = ;whd := _gui_GetWindow(cBaseAchievWindowName);
      [*] = ;if GetGUIElementVisible(whd) then
      [*] = ;begin
      [*] = ;   var fnd,k,ehd : Integer;
      [*] = ;   var time : Float;
      [*] = ;
      [*] = ;   fnd := 0;
      [*] = ;   for k := 0 to GetGUIElementChildrenCount(whd)-1 do
      [*] = ;   begin
      [*] = ;      ehd := GetGUIElementChildrenByIndex(whd,k);
      [*] = ;      if SubStr(GetGUIElementNameByIndex(ehd),1,4) = 'ach_' then
      [*] = ;      begin
      [*] = ;         time := StrToFloat(GetGUIElementStringTag(ehd));
      [*] = ;         if curTime > time then
      [*] = ;            _gui_FadeWindow_VVK(ehd,gc_gui_FadeTime0_2,2)
      [*] = ;         else
      [*] = ;            fnd := 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if fnd = 0 then
      [*] = ;   begin
      [*] = ;      _gui_RootWindowRemoveWithFade(whd,gc_gui_FadeTime0_2);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeNone then
      [*] = ;begin
      [*] = ;   // switch advertisements
      [*] = ;   whd := _gui_GetWindow(cBaseAdsWindowName);
      [*] = ;   if GetGUIElementVisible(whd) then
      [*] = ;   begin
      [*] = ;      var temp_str : String;
      [*] = ;      var time : Float;
      [*] = ;
      [*] = ;      temp_str := GetGUIElementStringTag(whd);
      [*] = ;      time := _sa_GetAsFloat(temp_str,1);
      [*] = ;      if curTime > time then
      [*] = ;         _cmd_Post('.menushowbanner','',IntToStr($ffff));
      [*] = ;   end;
      [*] = ;   
      [*] = ;   // smooth sliding entrance at startup
      [*] = ;   whd := _gui_GetWindow(cListMenuHeaderWindowName);
      [*] = ;   if GetGUIElementVisible(whd) then
      [*] = ;   begin
      [*] = ;      procedure LerpPosition(elmHandle : Integer);
      [*] = ;      begin
      [*] = ;         var stringTag : String = GetGUIElementStringTag(elmHandle);
      [*] = ;         if stringTag <> '' then
      [*] = ;         begin
      [*] = ;            var startY : Float = _sa_GetAsInt(stringTag, 0);
      [*] = ;            var endY : Float = _sa_GetAsInt(stringTag, 1);
      [*] = ;            var startTime : Float = _sa_GetAsFloat(stringTag, 2);
      [*] = ;            var transitionTime : Float = _sa_GetAsFloat(stringTag, 3);
      [*] = ;            var lerpFactor : Float = (curTime-startTime) / transitionTime;
      [*] = ;            if lerpFactor > 1 then
      [*] = ;            begin
      [*] = ;               lerpFactor := 1;
      [*] = ;               SetGUIElementStringTag(elmHandle, '');
      [*] = ;            end;
      [*] = ;            SetGUIElementPositionY(elmHandle, Floor(Lerp(startY, endY, lerpFactor)));
      [*] = ;            
      [*] = ;            var scale : Float = GetGUIElementScaleX(elmHandle);
      [*] = ;            if scale > 1.0001 then
      [*] = ;               SetGUIElementScale(elmHandle, 1.5 - lerpFactor / 2, 1.5 - lerpFactor / 2);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      LerpPosition(GetGUIElementIndexByNameParent('logo', whd));
      [*] = ;      LerpPosition(GetGUIElementIndexByNameParent('dragon', whd));
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

