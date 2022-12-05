section.begin
   Name = DoBlendLighting
   Code : struct.begin
      [*] = ;function GetRandomIndexLightPattern : Integer;
      [*] = ;begin
      [*] = ;   var ind : Integer = floor(Random*(gc_BlendLighting_PatternCount)+1);
      [*] = ;   if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;   begin
      [*] = ;      case _worldrule_GetWorldRuleVisualParams(3, 1) of
      [*] = ;         4 : ind := 2;
      [*] = ;         5 : ind := 2;
      [*] = ;         6 : ind := 2;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := ind;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetCurrentDelayTime : Integer;
      [*] = ;begin
      [*] = ;   if gIntRegister_CurGameMode=gc_GameModeTactics then
      [*] = ;   Result := gc_BlendLighting_Tactics_DelayTime
      [*] = ;   else
      [*] = ;   //if gIntRegister_CurGameMode=gc_GameModeStrategy then
      [*] = ;   Result := gc_BlendLighting_Strategy_DelayTime;
      [*] = ;
      [*] = ;   if (gProfile.lightchange=1) then //long
      [*] = ;   Result := Result*gc_BlendLighting_DelayTimeLongModifier;
      [*] = ;end;
      [*] = ;
      [*] = ;var gameTime : Float = GetGameTime;
      [*] = ;var lightTime : Float = GetMapFloatValue('LightTime');
      [*] = ;
      [*] = ;var lightID : Integer;
      [*] = ;if (gProfile.lightchange>2) then
      [*] = ;begin
      [*] = ;   if (lightTime=0) then
      [*] = ;   begin
      [*] = ;      ResetBlendToLightPattern;
      [*] = ;      lightID := gProfile.lightchange-2;
      [*] = ;      SetLightPattern(gc_BlendLighting_PatternPrefix+IntToStr(lightID));
      [*] = ;      SetMapFloatValue('LightTime', gameTime);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   lightID := GetRandomIndexLightPattern;
      [*] = ;   if (lightTime=0) then
      [*] = ;   begin
      [*] = ;      lightTime := gameTime;
      [*] = ;      SetMapFloatValue('LightTime', lightTime);
      [*] = ;      SetLightPattern(gc_BlendLighting_PatternPrefix+IntToStr(lightID));
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (gameTime-lightTime>GetCurrentDelayTime) or (lightTime>gameTime) then
      [*] = ;   begin
      [*] = ;      SetMapFloatValue('LightTime', gameTime);
      [*] = ;      //if gProfile.settingslowest then
      [*] = ;      //SetLightPattern(gc_BlendLighting_PatternPrefix+IntToStr(lightID))
      [*] = ;      //else
      [*] = ;      begin
      [*] = ;         SetBlendToLightPatternInterval(gc_BlendLighting_Interval);
      [*] = ;         SetBlendToLightPattern(gc_BlendLighting_PatternPrefix+IntToStr(lightID));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

