section.begin
   Name = OnMouseWheel
   Code : struct.begin
      [*] = ;procedure UpdateListBoxScrollerPos(elmHandle : Integer);
      [*] = ;begin
      [*] = ;   var count : Integer = GetGUIListBoxItemsCount(elmHandle);
      [*] = ;   var topIndex  : Integer = GetGUIListBoxTopIndex(elmHandle);
      [*] = ;   var elmScrollHandle : Integer = GetGUIListBoxScrollerHandle(elmHandle);
      [*] = ;   var rowheight : Integer = GetGUIListBoxRowHeight(elmHandle);
      [*] = ;   var step : Float = ((GetGUIElementHeight(elmHandle)-rowheight)/rowheight);
      [*] = ;   SetGUIScrollBarPosition(elmScrollHandle, (topIndex/(count-step)));
      [*] = ;end;
      [*] = ;
      [*] = ;function IsInsideRectangleExt(pX, pY, elmX, elmY, width, height : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if (pX >= elmX) and (pY >= elmY) and (pX < (elmX+width)) and (pY < (elmY+height)) then
      [*] = ;   Result := True
      [*] = ;   else
      [*] = ;   Result := False;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsInsideRectangle(rect : TRectangle; x,y : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if (x >= rect.pos.x) and (y >= rect.pos.y) and (x < (rect.pos.x+rect.size.w)) and (y < (rect.pos.y+rect.size.h)) then
      [*] = ;   Result := True
      [*] = ;   else
      [*] = ;   Result := False;
      [*] = ;end;
      [*] = ;
      [*] = ;function ClampToStep(value, step : Float) : Float;
      [*] = ;begin
      [*] = ;   var count : Integer;
      [*] = ;   count := round(value/step);
      [*] = ;   Result := count*step;
      [*] = ;end;
      [*] = ;
      [*] = ;function FindElementScrollLayerHandle(elmHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var className : String = GetObjectClassNameByHandle(elmHandle);
      [*] = ;   if (SameText(className, 'TXGuiLayer') or SameText(className, 'TXGuiListBox')) then
      [*] = ;   Result := elmHandle
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var elmParentHnd : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      if (elmParentHnd<>0) and IsElementByHandle(elmParentHnd) then
      [*] = ;      begin
      [*] = ;         Result := FindElementScrollLayerHandle(elmParentHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function FindElementScrollLayerChildHandle(elmHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var className : String = GetObjectClassNameByHandle(elmHandle);
      [*] = ;   var bFound : Boolean = False;
      [*] = ;   if (SameText(className, 'TXGuiLayer')) then
      [*] = ;   begin
      [*] = ;      var mX, mY, elmX, elmY, width, height : Integer = 0;
      [*] = ;      GetGUICurrentMouseCoord(mX, mY);
      [*] = ;      GetGUIElementAlignPosition(elmHandle, elmX, elmY);
      [*] = ;      width := GetGUIElementWidth(elmHandle);
      [*] = ;      height := GetGUIElementHeight(elmHandle);
      [*] = ;      //Log('mX: '+IntToStr(mX)+' mY: '+IntToStr(mY)+' elmX: '+IntToStr(elmX)+' elmY: '+IntToStr(elmY)+' width: '+IntToStr(width)+' height: '+IntToStr(height));
      [*] = ;
      [*] = ;      bFound := (GetGUIElementVisible(GetGUIElementVScroll(elmHandle))) and (IsInsideRectangleExt(mX, mY, elmX, elmY, width, height));
      [*] = ;   end;
      [*] = ;   //Log('bFound ' +BoolToStr(bFound));
      [*] = ;   if (bFound) then
      [*] = ;   Result := elmHandle
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to GetGUIElementChildrenCount(elmHandle)-1 do
      [*] = ;      begin
      [*] = ;         var elmChildHnd : Integer = GetGUIElementChildrenByIndex(elmHandle, i);
      [*] = ;         Result := FindElementScrollLayerChildHandle(elmChildHnd);
      [*] = ;         if (Result<>0) then
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//var lan_game : Boolean = true;
      [*] = ;var lan_game : Boolean = IsLanGame();
      [*] = ;
      [*] = ;SetCameraControlMouseWheelDistance(true);
      [*] = ;
      [*] = ;var underMouse : Integer = GetGUIElementUnderMouse();
      [*] = ;var topmost : Integer = _gui_RootWindowGetTopmost(cRootWindowAllTypes xor cRootWindowTop);
      [*] = ;{Log('topmost class: '+GetObjectClassNameByHandle(topmost));
      [*] = ;Log('topmost name: '+GetGUIElementNameByIndex(topmost));
      [*] = ;Log('topmost index: '+IntToStr(topmost));
      [*] = ;Log('underMouse Class: '+GetObjectClassNameByHandle(underMouse));
      [*] = ;Log('undermouse name: '+GetGUIElementNameByIndex(underMouse));
      [*] = ;Log('undermouse index: '+IntToStr(underMouse));}
      [*] = ;
      [*] = ;if SameText(GetObjectClassNameByHandle(underMouse), 'TXGuiListBox') then
      [*] = ;begin
      [*] = ;   //Log('Cursor: '+GetGUIElementNameByIndex(underMouse));
      [*] = ;   var elmHandle : Integer = underMouse;
      [*] = ;   var elmScrollHandle : Integer = GetGUIListBoxScrollerHandle(elmHandle);
      [*] = ;   var pos : Float = GetGUIScrollBarPosition(elmScrollHandle);
      [*] = ;   var wheelDelta : Float = GetGUIEventMouseWheelDelta;
      [*] = ;         
      [*] = ;   var topIndex  : Integer = GetGUIListBoxTopIndex(elmHandle);
      [*] = ;   if (wheelDelta>0) then
      [*] = ;      topIndex := topIndex-1
      [*] = ;   else
      [*] = ;      topIndex := topIndex+1;
      [*] = ;   var count : Integer = GetGUIListBoxItemsCount(elmHandle);
      [*] = ;   if topIndex>=count then
      [*] = ;      topIndex := count-1
      [*] = ;   else
      [*] = ;   if topIndex<0 then
      [*] = ;      topIndex := 0;
      [*] = ;   SetGUIListBoxTopIndex(elmHandle, topIndex);
      [*] = ;         
      [*] = ;   UpdateListBoxScrollerPos(elmHandle);
      [*] = ;end
      [*] = ;else
      [*] = ;if ((topmost<>0) and (underMouse<>0)) or (GetGUIElementVisible(_gui_GetLayer(cChatLayer))) or ((lan_game) and (GetGUIElementVisible(_gui_GetLayerExt(cLanChatLayer,0)))) then
      [*] = ;begin
      [*] = ;   //Log('Topmost: '+GetGUIElementNameByIndex(topmost)+', Cursor: '+GetGUIElementNameByIndex(underMouse));
      [*] = ;   if GetGUIElementVisible(_gui_GetLayer(cChatLayer)) then
      [*] = ;   begin
      [*] = ;      topmost := GetGUIElementIndexByNameParent('status_canvas',_gui_GetLayer(cChatLayer));
      [*] = ;      //Log('cChatLayer');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (lan_game) and GetGUIElementVisible(_gui_GetLayerExt(cLanChatLayer,0)) then
      [*] = ;      begin
      [*] = ;         //Log('cLanChatLayer');
      [*] = ;         var temp_str : String = GetValueByName('Status');
      [*] = ;         var pos : TRectangle;
      [*] = ;         var cx,cy : Integer;
      [*] = ;         
      [*] = ;         topmost := GetGUIElementIndexByNameParent('history_canvas',_gui_GetLayer(cLanChatLayer));
      [*] = ;         GetGUIElementAlignPosition(topmost,pos.pos.x,pos.pos.y);
      [*] = ;         pos.size.w := GetGUIElementWidth(topmost);
      [*] = ;         pos.size.h := GetGUIElementHeight(topmost);
      [*] = ;         GetGUICurrentMouseCoord(cx,cy);
      [*] = ;         if IsInsideRectangle(pos,cx,cy) then
      [*] = ;         begin
      [*] = ;            SetValueByName('Status','lan_console_delay_fade');
      [*] = ;            GUIExecuteState('VVK.OnLanEventChat');
      [*] = ;            SetValueByName('Status',temp_str);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         topmost := 0;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if GetGUIElementNameByIndex(topmost) = 'queryWindow' then
      [*] = ;         topmost := GetGUIElementIndexByNameParent('query_text_scroll',topmost);////
      [*] = ;         //else
      [*] = ;         ///topmost := GetGUIElementUnderMouse();
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //Log('topmost2 '+IntToStr(topmost));
      [*] = ;   //Log('topmostclass2 '+GetObjectClassNameByHandle(topmost));
      [*] = ;   if topmost <> 0 then
      [*] = ;   SetCameraControlMouseWheelDistance(false);
      [*] = ;   var elmHandle : Integer = FindElementScrollLayerChildHandle(topmost);
      [*] = ;   //if elmHandle <> 0  then   Log('FOUND');
      [*] = ;   if (elmHandle=0) then
      [*] = ;   elmHandle := FindElementScrollLayerHandle(topmost);
      [*] = ;   if (elmHandle<>0) then
      [*] = ;   begin
      [*] = ;      //Log('elmHandle '+IntToStr(elmHandle));
      [*] = ;      //Log('elmHandleName '+GetGUIElementNameByIndex(elmHandle));
      [*] = ;      //Log('elmclass '+GetObjectClassNameByHandle(elmHandle));
      [*] = ;      var className : String = GetObjectClassNameByHandle(elmHandle);
      [*] = ;      var elmScrollHandle : Integer = 0;
      [*] = ;      if SameText(className, 'TXGuiLayer') or SameText(className, 'TXGuiVScroll') then
      [*] = ;      begin
      [*] = ;         elmScrollHandle := GetGUIElementVScroll(elmHandle);
      [*] = ;         //Log('elmScrollHandle '+IntToStr(elmScrollHandle));
      [*] = ;         
      [*] = ;         if (elmScrollHandle=0) then
      [*] = ;         begin
      [*] = ;            elmScrollHandle := GetGUIElementHScroll(elmHandle);
      [*] = ;            if (elmScrollHandle<>0) then
      [*] = ;               Log('No VScroll on mouse wheel, but HScroll found');
      [*] = ;         end;
      [*] = ;         
      [*] = ;         if (elmScrollHandle<>0) then
      [*] = ;         begin
      [*] = ;            var pos : Float = GetGUIScrollBarPosition(elmScrollHandle);
      [*] = ;            var wheelDelta : Float = GetGUIEventMouseWheelDelta;
      [*] = ;           // Log('wheelDelta '+FloatToStr(wheelDelta));
      [*] = ;            
      [*] = ;           // Log('pos '+FloatToStr(pos));
      [*] = ;            var layerHeight : Integer = GetGUIElementHeight(elmHandle);
      [*] = ;           // Log('layerHeight '+IntToStr(layerHeight));
      [*] = ;            var scrollHeight : Integer = GetGUIElementHeight(elmScrollHandle);
      [*] = ;           // Log('scrollHeight '+IntToStr(scrollHeight));
      [*] = ;            if (layerHeight<>0) and (layerHeight<>scrollHeight) then
      [*] = ;            begin
      [*] = ;               var elmName : String = GetGUIElementNameByIndex(elmHandle);
      [*] = ;               var elmParentName : String = GetGUIElementNameByIndex(GetGUIElementParentByIndex(elmHandle));
      [*] = ;              // Log('elmName '+elmName);
      [*] = ;              // Log('elmParentName '+elmParentName);
      [*] = ;               var custom : Float;
      [*] = ;               var step : Float = 0;
      [*] = ;               var bUpdate : Boolean = False;
      [*] = ;               // custom scroll speed
      [*] = ;               case elmName of
      [*] = ;                  'unit_descr_scroll' : begin
      [*] = ;                     var fontHandle : String;
      [*] = ;                     _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'', fontHandle);
      [*] = ;                     var chatLineHeight : Integer = GetGUIElementFontHeight(fontHandle);
      [*] = ;                     step := chatLineHeight;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (step=0) then
      [*] = ;               case elmParentName of
      [*] = ;                  'dynamic' : step := 22;
      [*] = ;                  'provincelist_scrollLayer' : step := 87;
      [*] = ;                  'unitinfo_background' : custom := 1.5; //step := 0;
      [*] = ;                  'map_shoppanel_items', 'shop' : step := 56;
      [*] = ;                  'filelist' : step := 28;
      [*] = ;                  'profilelist' : step := 28;
      [*] = ;                  'queryWindow' : begin
      [*] = ;                     var fontHandle : String;
      [*] = ;                     _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'', fontHandle);
      [*] = ;                     var chatLineHeight : Integer = GetGUIElementFontHeight(fontHandle);
      [*] = ;                     step := chatLineHeight;
      [*] = ;                  end;
      [*] = ;                  'history' : begin
      [*] = ;                     {var fontHandle2 : String;
      [*] = ;                     _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'', fontHandle2);
      [*] = ;                     var chatFontHandle : String = fontHandle2;
      [*] = ;                     var chatLineHeight : Integer = GetGUIElementFontHeight(chatFontHandle);
      [*] = ;                     step := chatLineHeight;}
      [*] = ;                  end;
      [*] = ;                  'dip_background' : begin
      [*] = ;                     step := 56;
      [*] = ;                  end;
      [*] = ;                  'map_province_site', 'map_province_outer_build', 'map_province_defender', 'map_ritual' : begin
      [*] = ;                     step := 54;
      [*] = ;                     bUpdate := True;
      [*] = ;                  end;
      [*] = ;                  else
      [*] = ;                  step := 28;
      [*] = ;               end;
      [*] = ;               if (step=0) then
      [*] = ;               begin
      [*] = ;                  ErrorLog(elmParentName+' layerHeight = '+IntToStr(layerHeight)+' scrollHeight = '+IntToStr(scrollHeight)+' delta = '+IntToStr(layerHeight-scrollHeight)+' GetGUIElementChildrenCount = '+IntToStr(GetGUIElementChildrenCount(elmHandle)));
      [*] = ;                  var koef : Float = (0.15+gProfile.wheelspeed*0.75)*3*custom*scrollHeight/(layerHeight-scrollHeight);
      [*] = ;                  var posDelta : Float = (koef*wheelDelta/2000);
      [*] = ;                  pos := pos-posDelta;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var koef : Float = step/(layerHeight-scrollHeight);
      [*] = ;                  if (wheelDelta<0) then
      [*] = ;                  pos := pos+koef
      [*] = ;                  else
      [*] = ;                  pos := pos-koef;
      [*] = ;                  
      [*] = ;                  pos := ClampToStep(pos, koef);
      [*] = ;               end;
      [*] = ;               
      [*] = ;               pos := Clamp(pos, 0, 1);
      [*] = ;               SetGUIScrollBarPosition(elmScrollHandle, pos);
      [*] = ;               
      [*] = ;               if (bUpdate) then
      [*] = ;               begin
      [*] = ;                  ViewerBufferRender;
      [*] = ;                  GUIUpdateElementUnderMouse;
      [*] = ;                  GUIInternalMouseEnter(GetGUIElementUnderMouse);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if SameText(className, 'TXGuiListBox') then
      [*] = ;      begin
      [*] = ;         elmScrollHandle := GetGUIListBoxScrollerHandle(elmHandle);
      [*] = ;         var pos : Float = GetGUIScrollBarPosition(elmScrollHandle);
      [*] = ;         var wheelDelta : Float = GetGUIEventMouseWheelDelta;
      [*] = ;         
      [*] = ;         var topIndex  : Integer = GetGUIListBoxTopIndex(elmHandle);
      [*] = ;         if (wheelDelta>0) then
      [*] = ;         topIndex := topIndex-1
      [*] = ;         else
      [*] = ;         topIndex := topIndex+1;
      [*] = ;         var count : Integer = GetGUIListBoxItemsCount(elmHandle);
      [*] = ;         if topIndex>=count then
      [*] = ;         topIndex := count-1
      [*] = ;         else
      [*] = ;         if topIndex<0 then
      [*] = ;         topIndex := 0;
      [*] = ;         SetGUIListBoxTopIndex(elmHandle, topIndex);
      [*] = ;         
      [*] = ;         UpdateListBoxScrollerPos(elmHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;//else
      [*] = ;//if (topmost <> 0) and (GetGUIElementUnderMouse()=0) then
      [*] = ;//Log('OnMouseWheel, (topmost<>0) and (GetGUIElementUnderMouse=0)');
      [*] = ;//Log('    ');
   struct.end
section.end

