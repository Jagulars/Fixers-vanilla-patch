section.begin
   Name = VVK.FloatingTooltipsCore
   Description : struct.begin
      [*] = ;IntRegister0 - mode
      [*] = ;[0] - register by window name SR0 - window name, SR1 - state name
      [*] = ;[1] - unregister by window name SR0 - window name
      [*] = ;[2] - process timer event FR0 - current time, IR1 - mouse_x, IR2 - mouse_y
      [*] = ;[3] - update element position of window by name
      [*] = ;      SR0 - window name
      [*] = ;      IR1 - mouse_x
      [*] = ;      IR2 - mouse_y
      [*] = ;      RET: BR0 == true if x,y is inside tooltip
      [*] = ;[4] - show delayed tooltip (code from former VVK.ShowDelayedTooltip)
      [*] = ;   SR0 - object id string (split by | if necessary) or empty string if should remove this window
      [*] = ;   SR1 - name of window to replace
      [*] = ;   SR2 - name of the template (short created by adding '_short' suffix to it)
      [*] = ;                     '|' name of state that will be called after and during tooltip creation (OPTIONAL)
      [*] = ;   SR3 - timer string
      [*] = ;   //IntRegister0 - building/item/spell etc id or 0 to remove (should be in window tag)
      [*] = ;   //               if equals $1000000 then SR0 has object data (should be splitted by # sign)
      [*] = ;   IR1 - Mouse X
      [*] = ;   IR2 - Mouse Y
      [*] = ;   IR3 - Z Order of actual window
      [*] = ;   IR4 - tooltip's master element id (could be 0)
      [*] = ;   FR0 - delay before showing short info (-1 to skip it completely)
      [*] = ;   FR1 - delay before showing long info
      [*] = ;   RET: SR0 - Timer string
      [*] = ;[5] - process mouse move
      [*] = ;   IR1 - mouse over window handle
      [*] = ;   IR2 - x
      [*] = ;   IR3 - y
      [*] = ;   IR4 - element index in gArr_gui_float_tooltips array
      [*] = ;[6] - display simple tooltip window
      [*] = ;   IR1 - parent handle for tooltip
      [*] = ;   IR2 - target handle
      [*] = ;   SR0 - tooltip text
      [*] = ;   BR0 - display question mark
      [*] = ;   BR1 - display mouse icon
      [*] = ;
      [*] = ;   RET: IR0 - tooltip window handle
      [*] = ;[7] - unregister all handlers
      [*] = ;[8] - process on hint request
      [*] = ;   IR1 - window handle
      [*] = ;   BR0 - true for extended hint
      [*] = ;   SR0 - extended hint state name
      [*] = ;   FR0 - extended hint delay time
      [*] = ;
      [*] = ;   RET: BR0 - true if should skip parent hint request
      [*] = ;        if BR0 is false then
      [*] = ;         IR0&1 - should replace hint with string from SR0 and ext hint from SR1
      [*] = ;         IR0&2 - should display question icon
      [*] = ;         IR0&4 - should display mouse icon
      [*] = ;[8] - call callback with 'on hint' request
      [*] = ;   IR1 - window handle
      [*] = ;   BR0 - true for extended hint
      [*] = ;   SR0 - callback state name
      [*] = ;   SR1 - callback state args
      [*] = ;
      [*] = ;   RET: BR0 - true if should skip parent hint request
      [*] = ;        if BR0 is false then
      [*] = ;         IR0&1 - should replace hint with string from SR0 and ext hint from SR1
      [*] = ;         IR0&2 - should display question icon
      [*] = ;         IR0&4 - should display mouse icon
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;var _reg_log : Boolean = false;
      [*] = ;
      [*] = ;function IsInsideRectangle(rect : TRectangle; x,y : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   if (x >= rect.pos.x) and (y >= rect.pos.y) and (x < (rect.pos.x+rect.size.w)) and (y < (rect.pos.y+rect.size.h)) then
      [*] = ;      Result := True
      [*] = ;   else
      [*] = ;      Result := False;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Register(window_name,state_name : String);
      [*] = ;begin
      [*] = ;   var i,exists : Integer;
      [*] = ;
      [*] = ;   if _reg_log then _log_gui('FT_REGISTER: '+window_name+', '+state_name);
      [*] = ;   exists := -1;
      [*] = ;   for i := 0 to gc_gui_float_tooltips_max-1 do
      [*] = ;   begin
      [*] = ;      if (gArr_gui_float_tooltips[i].state = '') then
      [*] = ;         break;
      [*] = ;      if (gArr_gui_float_tooltips[i].state <> ' ') then
      [*] = ;      begin
      [*] = ;         if window_name = gArr_gui_float_tooltips[i].window_name then
      [*] = ;         begin
      [*] = ;            ErrorLog('FLOATING TOOLTIP WARNING: Window '+window_name+' already exists in handler');
      [*] = ;            exists := i;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if exists = -1 then
      [*] = ;   begin
      [*] = ;      for i := 0 to gc_gui_float_tooltips_max-1 do
      [*] = ;      begin
      [*] = ;         if (gArr_gui_float_tooltips[i].state = '') or (gArr_gui_float_tooltips[i].state = ' ') then
      [*] = ;            break;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      i := exists;
      [*] = ;
      [*] = ;   if i >= gc_gui_float_tooltips_max then
      [*] = ;   begin
      [*] = ;      if _reg_log then
      [*] = ;      begin
      [*] = ;         for i := 0 to gc_gui_float_tooltips_max-1 do
      [*] = ;            _log_gui('FT['+IntToStr(i)+']: '+gArr_gui_float_tooltips[i].state);
      [*] = ;      end;
      [*] = ;      ErrorLog('Too many floating tooltips');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if exists <> -1 then // should unregister previous instance
      [*] = ;      begin
      [*] = ;         IntRegister0 := cFloatTooltipUnRegister;
      [*] = ;         StringRegister0 := gArr_gui_float_tooltips[i].window_name;
      [*] = ;         GUIExecuteState(gArr_gui_float_tooltips[i].state);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gArr_gui_float_tooltips[i].state = '') then
      [*] = ;         gArr_gui_float_tooltips[i+1].state := '';
      [*] = ;      gArr_gui_float_tooltips[i].window_name := window_name;
      [*] = ;      gArr_gui_float_tooltips[i].state := state_name;
      [*] = ;      gArr_gui_float_tooltips[i].timer := '';
      [*] = ;      IntRegister0 := cFloatTooltipRegister;
      [*] = ;      StringRegister0 := window_name;
      [*] = ;      BoolRegister0 := true;
      [*] = ;      GUIExecuteState(state_name);
      [*] = ;      if not BoolRegister0 then
      [*] = ;         gArr_gui_float_tooltips[i].state := ' ';
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UnRegister(window_name : String);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   if _reg_log then _log_gui('FT_UNREGISTER: '+window_name);
      [*] = ;
      [*] = ;   for i := 0 to gc_gui_float_tooltips_max-1 do
      [*] = ;   begin
      [*] = ;      if (gArr_gui_float_tooltips[i].state = '') then
      [*] = ;         break;
      [*] = ;      if ((gArr_gui_float_tooltips[i].window_name = window_name) or (window_name = '')) and (gArr_gui_float_tooltips[i].state <> ' ') then
      [*] = ;      begin
      [*] = ;         IntRegister0 := cFloatTooltipUnRegister;
      [*] = ;         StringRegister0 := gArr_gui_float_tooltips[i].window_name;
      [*] = ;         GUIExecuteState(gArr_gui_float_tooltips[i].state);
      [*] = ;         gArr_gui_float_tooltips[i].state := ' ';
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if window_name = '' then
      [*] = ;      gArr_gui_float_tooltips[0].state := '';
      [*] = ;end;
      [*] = ;
      [*] = ;function UpdateTooltipElement(windowName : String; mouseX, mouseY, mhd : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var windowHandle : Integer;
      [*] = ;   var r : Integer = -1;
      [*] = ;
      [*] = ;   windowHandle := _gui_GetWindow(windowName);
      [*] = ;   if (windowHandle <> 0) and GetGUIElementVisible(windowHandle) then
      [*] = ;   begin
      [*] = ;      var hint_str : String;
      [*] = ;      var src_hd : Integer;
      [*] = ;//      var ehd : Integer = GetGUIElementIndexByNameParent(gc_gui_TooltipExtraArea, windowHandle);
      [*] = ;
      [*] = ;      src_hd := GetGUIElementTag(windowHandle);
      [*] = ;      hint_str := GetGUIElementHint(src_hd);
      [*] = ;      if SubStr(hint_str,1,1) = '#' then
      [*] = ;      begin
      [*] = ;         var state_name, state_args,s_ret : String;
      [*] = ;         var i_ret,res : Integer;
      [*] = ;
      [*] = ;         _sa_Get_D(hint_str,1,$23,state_name);
      [*] = ;         _sa_Get_D(hint_str,2,$23,state_args);
      [*] = ;         IntRegister0 := cFloatTooltipUpdatePos;
      [*] = ;         IntRegister1 := windowHandle;
      [*] = ;         IntRegister2 := mouseX;
      [*] = ;         IntRegister3 := mouseY;
      [*] = ;         IntRegister4 := mhd;
      [*] = ;         StringRegister0 := state_args;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         GUIExecuteState(state_name);
      [*] = ;         if BoolRegister0 then
      [*] = ;            r := 1
      [*] = ;         else
      [*] = ;            r := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (r=-1) then
      [*] = ;      begin
      [*] = ;         var ib_tooltip_pos : TRectangle;
      [*] = ;
      [*] = ;         GetGUIElementAlignPosition(windowHandle, ib_tooltip_pos.pos.x, ib_tooltip_pos.pos.y);
      [*] = ;         ib_tooltip_pos.size.w := GetGUIElementWidth(windowHandle);
      [*] = ;         ib_tooltip_pos.size.h := GetGUIElementHeight(windowHandle);
      [*] = ;         if (IsInsideRectangle(ib_tooltip_pos,mouseX,mouseY)) then
      [*] = ;            r := 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if r > 0 then
      [*] = ;      Result := true
      [*] = ;   else
      [*] = ;      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DisplayTooltip(idx,src_handle,mX,mY,z_order : Integer;obj_id,template,state : String; is_ext : Boolean);
      [*] = ;begin
      [*] = ;   var args : String = '';
      [*] = ;
      [*] = ;   if _log then _log_gui('FT_DISPLAY: '+obj_id+', '+template+', '+state);
      [*] = ;   if src_handle <> 0 then
      [*] = ;   begin
      [*] = ;      var temp_str : String = GetGUIElementHint(src_handle);
      [*] = ;
      [*] = ;      if _sa_GetNum_D(temp_str,$23) >2 then
      [*] = ;         _sa_Get_D(temp_str,2,$23,args);
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := cFloatTooltipDisplay;
      [*] = ;   IntRegister1 := src_handle;
      [*] = ;   IntRegister2 := mX;
      [*] = ;   IntRegister3 := mY;
      [*] = ;   IntRegister4 := z_order;
      [*] = ;   StringRegister0 := args;
      [*] = ;   StringRegister1 := obj_id;
      [*] = ;   StringRegister2 := template;
      [*] = ;   StringRegister3 := state;
      [*] = ;   BoolRegister0 := is_ext;
      [*] = ;   GUIExecuteState(gArr_gui_float_tooltips[idx].state);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ProcessTimerEntry(idx : Integer; game_time : Float;mx,my,mhd : Integer);
      [*] = ;begin
      [*] = ;   var timer_str : String;
      [*] = ;   var dc : Integer;
      [*] = ;
      [*] = ;   timer_str := gArr_gui_float_tooltips[idx].timer;
      [*] = ;   dc := _sa_GetNum_D(timer_str,gc_gui_ft_timer_str_char);
      [*] = ;   if dc >= 9 then
      [*] = ;   begin
      [*] = ;      var time1,time2 : Float;
      [*] = ;      var obj_id1,obj_id2 : String;
      [*] = ;      var oldMX,oldMY,whd,z_order,src_handle : Integer;
      [*] = ;      var short_template,long_template,state_name,state_args : String;
      [*] = ;      var mouse_over_tooltip : Boolean = False;
      [*] = ;
      [*] = ;      time1 := _sa_GetAsFloat_D(timer_str,0,gc_gui_ft_timer_str_char);
      [*] = ;      _sa_Get_D(timer_str,1,gc_gui_ft_timer_str_char,obj_id1);
      [*] = ;      time2 := _sa_GetAsFloat_D(timer_str,2,gc_gui_ft_timer_str_char);
      [*] = ;      _sa_Get_D(timer_str,3,gc_gui_ft_timer_str_char,obj_id2);
      [*] = ;      oldMX := _sa_GetAsInt_D(timer_str,4,gc_gui_ft_timer_str_char);
      [*] = ;      oldMY := _sa_GetAsInt_D(timer_str,5,gc_gui_ft_timer_str_char);
      [*] = ;      _sa_Get_D(timer_str,6,gc_gui_ft_timer_str_char,short_template);
      [*] = ;      _sa_Get_D(timer_str,7,gc_gui_ft_timer_str_char,long_template);
      [*] = ;      _sa_Get_D(timer_str,8,gc_gui_ft_timer_str_char,state_name);
      [*] = ;      z_order := _sa_GetAsInt_D(timer_str,9,gc_gui_ft_timer_str_char);
      [*] = ;      src_handle := _sa_GetAsInt_D(timer_str,10,gc_gui_ft_timer_str_char);
      [*] = ;
      [*] = ;      if UpdateTooltipElement(gArr_gui_float_tooltips[idx].window_name,mX,mY,mhd) then
      [*] = ;         mouse_over_tooltip := true;
      [*] = ;
      [*] = ;      if ((Abs(oldMX-mX) < 2) and (Abs(oldMY-mY) < 2)) or (mouse_over_tooltip) then
      [*] = ;      begin
      [*] = ;         if (time2 <> -1) then
      [*] = ;         begin
      [*] = ;            if time1 <> -1 then // short tooltip
      [*] = ;            begin
      [*] = ;               if game_time > time1 then
      [*] = ;               begin
      [*] = ;                  DisplayTooltip(idx,src_handle,mx,my,z_order,obj_id1,short_template,state_name,false);
      [*] = ;                  timer_str := '';
      [*] = ;                  _sa_AddAsFloat_D(timer_str,-1,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_Add_D(timer_str,'',gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_AddAsFloat_D(timer_str,time2,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_Add_D(timer_str,obj_id2,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_AddAsInt_D(timer_str,mX,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_AddAsInt_D(timer_str,mY,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_Add_D(timer_str,short_template,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_Add_D(timer_str,long_template,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_Add_D(timer_str,state_name,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_AddAsInt_D(timer_str,z_order,gc_gui_ft_timer_str_sym);
      [*] = ;                  _sa_AddAsInt_D(timer_str,src_handle,gc_gui_ft_timer_str_sym);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if game_time > time2 then
      [*] = ;               begin
      [*] = ;                  DisplayTooltip(idx,src_handle,mx,my,z_order,obj_id2,long_template,state_name,true);
      [*] = ;                  timer_str := '';
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gArr_gui_float_tooltips[idx].timer := timer_str;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            gArr_gui_float_tooltips[idx].timer := '';
      [*] = ;      end
      [*] = ;      else
      [*] = ;         gArr_gui_float_tooltips[idx].timer := '';
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ProcessTimer(game_time : Float;mouse_x,mouse_y : Integer);
      [*] = ;begin
      [*] = ;   if game_time > gArr_gui_float_tooltips_check_time then
      [*] = ;   begin
      [*] = ;      var i,mhd,windowHandle,src_hd : Integer;
      [*] = ;
      [*] = ;      gArr_gui_float_tooltips_check_time := game_time+gc_gui_float_tooltips_timer_delta;
      [*] = ;      mhd := GetGUIElementUnderMouse();
      [*] = ;
      [*] = ;      for i := 0 to gc_gui_float_tooltips_max-1 do
      [*] = ;      begin
      [*] = ;         if gArr_gui_float_tooltips[i].state = '' then
      [*] = ;            break;
      [*] = ;
      [*] = ;         if gArr_gui_float_tooltips[i].state <> ' ' then
      [*] = ;         begin
      [*] = ;            ProcessTimerEntry(i,game_time,mouse_x,mouse_y,mhd);
      [*] = ;            windowHandle := _gui_GetWindow(gArr_gui_float_tooltips[i].window_name);
      [*] = ;            if windowHandle <> 0 then
      [*] = ;            begin
      [*] = ;               src_hd := GetGUIElementTag(windowHandle);
      [*] = ;               if not IsElementByHandle(src_hd) then
      [*] = ;               begin
      [*] = ;                  SetGUIElementTag(windowHandle,0);
      [*] = ;                  _gui_ft_ProcessMouseMove(mhd,mouse_x,mouse_y);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            IntRegister0 := cFloatTooltipOnTimer;
      [*] = ;            IntRegister1 := mhd;
      [*] = ;            IntRegister2 := mouse_x;
      [*] = ;            IntRegister3 := mouse_y;
      [*] = ;            IntRegister4 := windowHandle;
      [*] = ;            StringRegister0 := gArr_gui_float_tooltips[i].window_name;
      [*] = ;            FloatRegister0 := game_time;
      [*] = ;            GUIExecuteState(gArr_gui_float_tooltips[i].state);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure _HideTooltip(windowName : String);
      [*] = ;begin
      [*] = ;   var windowHandle : Integer = _gui_GetWindow(windowName);
      [*] = ;
      [*] = ;   if windowHandle <> 0 then
      [*] = ;   begin
      [*] = ;      StringRegister0 := windowName;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      GUIExecuteState('VVK.CloseCommonTooltip');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ShowDelayedTooltip(objectID,windowName,states,timer_in : String; mx,my,z_order,srcHandle : Integer;delay1,delay2 : Float;var dst_timer_str : String);
      [*] = ;begin
      [*] = ;   var templateName,stateName,temp_str,timer_str : String;
      [*] = ;   var dc,if_handle : Integer;
      [*] = ;   var same_object : Boolean;
      [*] = ;
      [*] = ;   timer_str := timer_in;
      [*] = ;   dc := _sa_GetNum_D(states,gc_gui_ft_timer_str_char);
      [*] = ;   if dc = 1 then
      [*] = ;   begin
      [*] = ;      templateName := states;
      [*] = ;      stateName := '';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      _sa_Get_D(states,0,gc_gui_ft_timer_str_char,templateName);
      [*] = ;      _sa_Get_D(states,1,gc_gui_ft_timer_str_char,stateName);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _log_gui('BD_OBJID: '+objectID);
      [*] = ;   if _log then _log_gui('STATES_STR: '+states);
      [*] = ;   if _log then _log_gui('GT: '+FloatToStr(GetGameTime())+', DT: '+FloatToStr(gArr_gui_float_tooltips_check_time));
      [*] = ;   if objectID = '' then
      [*] = ;   begin
      [*] = ;      dst_timer_str := '';
      [*] = ;      _HideTooltip(windowName);
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _gui_GetWindow(windowName) <> 0 then
      [*] = ;      same_object := _gui_ft_IsSameObjectID(windowName,objectID,srcHandle)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      same_object := false;
      [*] = ;      if (delay1 <> 0) and (delay2 <> 0) then
      [*] = ;      begin
      [*] = ;         dc := _sa_GetNum_D(timer_str,gc_gui_ft_timer_str_char);
      [*] = ;         if dc > 9 then
      [*] = ;         begin
      [*] = ;            _sa_Get_D(timer_str,1,gc_gui_ft_timer_str_char,temp_str);
      [*] = ;            if temp_str = '' then
      [*] = ;               _sa_Get_D(timer_str,3,gc_gui_ft_timer_str_char,temp_str);
      [*] = ;            if temp_str = objectID then
      [*] = ;               same_object := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if same_object then
      [*] = ;   begin
      [*] = ;      if _log then _log_gui('SAME_OBJECT: '+objectID);
      [*] = ;      dst_timer_str := timer_in;
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _HideTooltip(windowName);
      [*] = ;
      [*] = ;   timer_str := '';
      [*] = ;   if_handle := _gui_GetInterfaceWindowHandle(templateName+'_short');
      [*] = ;   if (delay1 < 0) or (delay2 = 0) or (if_handle = -1) then
      [*] = ;      _sa_AddAsFloat_D(timer_str,-1,gc_gui_ft_timer_str_sym)
      [*] = ;   else
      [*] = ;      _sa_AddAsFloat_D(timer_str,GetGameTime()+delay1,gc_gui_ft_timer_str_sym);
      [*] = ;
      [*] = ;   _sa_Add_D(timer_str,objectID,gc_gui_ft_timer_str_sym);
      [*] = ;   if (delay2 < 0) then
      [*] = ;      _sa_AddAsFloat_D(timer_str,-1,gc_gui_ft_timer_str_sym)
      [*] = ;   else
      [*] = ;      _sa_AddAsFloat_D(timer_str,GetGameTime()+delay2,gc_gui_ft_timer_str_sym);
      [*] = ;   _sa_Add_D(timer_str,objectID,gc_gui_ft_timer_str_sym);
      [*] = ;   _sa_AddAsInt_D(timer_str,mX,gc_gui_ft_timer_str_sym);
      [*] = ;   _sa_AddAsInt_D(timer_str,mY,gc_gui_ft_timer_str_sym);
      [*] = ;   _sa_Add_D(timer_str,templateName+'_short',gc_gui_ft_timer_str_sym);
      [*] = ;   _sa_Add_D(timer_str,templateName,gc_gui_ft_timer_str_sym);
      [*] = ;   _sa_Add_D(timer_str,stateName,gc_gui_ft_timer_str_sym);
      [*] = ;   _sa_AddAsInt_D(timer_str,z_order,gc_gui_ft_timer_str_sym);
      [*] = ;   _sa_AddAsInt_D(timer_str,srcHandle,gc_gui_ft_timer_str_sym);
      [*] = ;   dst_timer_str := timer_str;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ProcessMouseMove(whd,mx,my,idx : Integer);
      [*] = ;begin
      [*] = ;   var hint_str,args : String;
      [*] = ;   var mhd : Integer = whd;
      [*] = ;
      [*] = ;   hint_str := '';
      [*] = ;   args := '';
      [*] = ;   if whd <> 0 then
      [*] = ;      hint_str := GetGUIElementHint(whd);
      [*] = ;
      [*] = ;   if (hint_str <> '') and (SubStr(hint_str,1,1)='#') then
      [*] = ;   begin
      [*] = ;      var st : String;
      [*] = ;
      [*] = ;      _sa_Get_D(hint_str,1,$23,st);
      [*] = ;      if SameText(st,gArr_gui_float_tooltips[idx].state) then
      [*] = ;         _sa_Get_D(hint_str,2,$23,args)
      [*] = ;      else
      [*] = ;         whd := 0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      whd := 0;
      [*] = ;
      [*] = ;   if _log and (whd <>0) then _log_Values(gArr_gui_float_tooltips[idx].state+'|MX|MY',whd,mx,my,0,0,0);
      [*] = ;   IntRegister5 := _gui_GetWindow(gArr_gui_float_tooltips[idx].window_name);
      [*] = ;   IntRegister0 := cFloatTooltipMouseMove;
      [*] = ;   IntRegister1 := whd;
      [*] = ;   IntRegister2 := mx;
      [*] = ;   IntRegister3 := my;
      [*] = ;   IntRegister4 := mhd;
      [*] = ;   StringRegister0 := args;
      [*] = ;   StringRegister1 := gArr_gui_float_tooltips[idx].window_name;
      [*] = ;   GUIExecuteState(gArr_gui_float_tooltips[idx].state);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateCommonTooltip(layer, targetHandle : Integer;wnd_name,text : String; displayQ,displayB : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   const cTooltipBorders = $1c;
      [*] = ;
      [*] = ;   const cTooltipText = $1e;
      [*] = ;   const cIconsPos = $1d;
      [*] = ;   const cMinWindowSize = $1;
      [*] = ;
      [*] = ;   var pos,txt_pos : TRectangle;
      [*] = ;   var elem_d,window_d,icon_d,border_d : TInterfaceElementData;
      [*] = ;   var temp_str,textTooltip : String;
      [*] = ;   var if_handle,windowHandle,i,w,h : Integer;
      [*] = ;
      [*] = ;   _sys_FillRect(pos,0,0,0,0);
      [*] = ;   if_handle := _gui_GetInterfaceWindowHandle('tooltip_window');
      [*] = ;   _gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,window_d);
      [*] = ;   _gui_GetInterfaceElement(if_handle,cTooltipText,elem_d);
      [*] = ;   _gui_GetInterfaceElement(if_handle,cMinWindowSize,icon_d);
      [*] = ;
      [*] = ;   textTooltip := GetGUIWrappedTextFormatByFont(elem_d.font_handle, text, elem_d.p.size.w);
      [*] = ;   GetGUIElementFontTextFormatRect(elem_d.font_handle, textTooltip, w, h);
      [*] = ;   w := max(icon_d.p.size.w,w);
      [*] = ;
      [*] = ;   pos.size.w := w+((elem_d.p_raw.pos.x)*2);
      [*] = ;   if (displayQ) or (displayB) then
      [*] = ;   begin
      [*] = ;      _gui_GetInterfaceElement(if_handle,cIconsPos,icon_d);
      [*] = ;      pos.size.h := h+(elem_d.p_raw.pos.y)+icon_d.p.size.h;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      pos.size.h := h+((elem_d.p_raw.pos.y)*2);
      [*] = ;
      [*] = ;   if _log then _log_Values('W|H|TW|TH',w,h,pos.size.w,pos.size.h,0,0);
      [*] = ;   windowHandle := _gui_CreateScalableWindow_VVK(wnd_name,layer,gc_gui_align_parent_lt,pos,'common_tooltip');
      [*] = ;   _gui_SetScaleableWindowBkgBlend(windowHandle,0.9);
      [*] = ;
      [*] = ;   i := _gui_GetInterfaceWindowHandle('common_tooltip_offsets');
      [*] = ;   if _gui_GetInterfaceElement(i,cTooltipBorders,border_d) then
      [*] = ;   begin
      [*] = ;      temp_str := '';
      [*] = ;      _sa_AddAsInt(temp_str,border_d.p.size.w);
      [*] = ;      _sa_AddAsInt(temp_str,border_d.p.size.h);
      [*] = ;      _sa_AddAsInt(temp_str,pos.size.w);
      [*] = ;      _sa_AddAsInt(temp_str,pos.size.h);
      [*] = ;      _sys_FillRect(txt_pos,0,0,1,1);
      [*] = ;      i := _gui_CreateImage_VVK(gc_gui_TooltipRealArea,windowHandle,'misc.blank.black.alpha.0',gc_gui_align_parent_lt,txt_pos);
      [*] = ;      SetGUIElementStringTag(i,temp_str);
      [*] = ;      SetGUIElementVisible(i,false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   _sys_FillRect(txt_pos,elem_d.p_raw.pos.x,elem_d.p_raw.pos.y,w,h);
      [*] = ;   _gui_CreateText_VVK('text',windowHandle,textTooltip,elem_d.align,txt_pos,gc_gui_align_lt,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;   if (displayQ) or (displayB) then
      [*] = ;   begin
      [*] = ;      w := pos.size.w-elem_d.p_raw.pos.x;
      [*] = ;      h := pos.size.h-icon_d.p.size.h;
      [*] = ;      if displayB then
      [*] = ;      begin
      [*] = ;         temp_str := 'mouse.right.btn.icon.11x13';
      [*] = ;         _sys_FillRect(pos,w,h+((icon_d.p.size.h-GetGUITextureHeight(temp_str)) div 2),0,0);
      [*] = ;         _gui_CreateImage_VVK('',windowHandle,temp_str,gc_gui_align_parent_lt,pos);
      [*] = ;         temp_str := 'question.icon.6x11';
      [*] = ;         w := w-(GetGUITextureWidth(temp_str)*3) div 2;
      [*] = ;      end;
      [*] = ;      if displayQ then
      [*] = ;      begin
      [*] = ;         temp_str := 'question.icon.6x11';
      [*] = ;         _sys_FillRect(pos,w,h+((icon_d.p.size.h-GetGUITextureHeight(temp_str)) div 2),0,0);
      [*] = ;         _gui_CreateImage_VVK('',windowHandle,temp_str,gc_gui_align_parent_lt,pos);
      [*] = ;         //w := w-GetGUITextureWidth(temp_str);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _gui_FadeWindow_VVK(windowHandle,0.05,0);
      [*] = ;   _gui_AlignWindowByCursor_VVK(windowHandle);
      [*] = ;   Result := windowHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessHintCallback(whd : Integer;ext : Boolean;state_name,state_args, ext_state : String; ext_delay : Float;var ret_i : Integer; var ret_s : String; var rete_s : String ) : Boolean ;
      [*] = ;begin
      [*] = ;   var textTooltip,s_ret,s_rete : String;
      [*] = ;   var i_ret,res,x,y : Integer;
      [*] = ;
      [*] = ;   Result := false;
      [*] = ;   ret_i := 0;
      [*] = ;   ret_s := '';
      [*] = ;   rete_s := '';
      [*] = ;
      [*] = ;   GetGUICurrentMouseCoord(x,y);
      [*] = ;   res := _gui_ft_OnHint(state_name,state_args,ext,whd,x,y,i_ret,s_ret,s_rete);
      [*] = ;   if _log then _log_Values('IR0|IR1',res,i_ret,0,0,0,0);
      [*] = ;   if (res = 1) or (res = 2) then
      [*] = ;   begin
      [*] = ;      if (not ext) and (res = 2) and (ext_state <> '') then
      [*] = ;      begin
      [*] = ;         SetIntValueByName('HintElmHandle', whd);
      [*] = ;         _gui_DelayExecuteStateOneInstance(ext_state,ext_delay);
      [*] = ;      end;
      [*] = ;      Result := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if res = 3 then
      [*] = ;      begin
      [*] = ;         ret_i := i_ret xor 1;
      [*] = ;         if ((ret_i and 1) <> 0) then
      [*] = ;         begin
      [*] = ;            ret_s := s_ret;
      [*] = ;            rete_s := s_rete;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessHintRequest(whd : Integer;ext : Boolean; ext_state : String; ext_delay : Float;var ret_i : Integer; var ret_s : String; var rete_s : String ) : Boolean ;
      [*] = ;begin
      [*] = ;   var textTooltip : String;
      [*] = ;
      [*] = ;   Result := false;
      [*] = ;   ret_i := 0;
      [*] = ;   ret_s := '';
      [*] = ;   rete_s := '';
      [*] = ;
      [*] = ;   textTooltip := GetGUIElementHint(whd);
      [*] = ;   if SubStr(textTooltip,1,1) = '#' then
      [*] = ;   begin
      [*] = ;      var state_name,state_args : String;
      [*] = ;
      [*] = ;      _sa_Get_D(textTooltip,1,$23,state_name);
      [*] = ;      _sa_Get_D(textTooltip,2,$23,state_args);
      [*] = ;      Result := ProcessHintCallback(whd,ext,state_name,state_args,ext_state,ext_delay,ret_i,ret_s,rete_s);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;
      [*] = ;case mode of
      [*] = ;   0 : Register(StringRegister0,StringRegister1);
      [*] = ;   1 : UnRegister(StringRegister0);
      [*] = ;   2 : ProcessTimer(FloatRegister0,IntRegister1,IntRegister2);
      [*] = ;   3 : BoolRegister0 := UpdateTooltipElement(StringRegister0,IntRegister1,IntRegister2,IntRegister3);
      [*] = ;   4 : begin
      [*] = ;      var ret_str : String = '';
      [*] = ;      ShowDelayedTooltip(StringRegister0,StringRegister1,StringRegister2,StringRegister3,IntRegister1,IntRegister2,IntRegister3,IntRegister4,FloatRegister0,FloatRegister1,ret_str);
      [*] = ;      StringRegister0 := ret_str;
      [*] = ;   end;
      [*] = ;   5 : ProcessMouseMove(IntRegister1,IntRegister2,IntRegister3,IntRegister4);
      [*] = ;   6 : IntRegister0 := CreateCommonTooltip(IntRegister1,IntRegister2, 'hintWindow', StringRegister0, BoolRegister0, BoolRegister1);
      [*] = ;   7 : UnRegister('');
      [*] = ;   8 : begin
      [*] = ;      var ret_s,rete_s : String;
      [*] = ;      var ret_i : Integer;
      [*] = ;      BoolRegister0 := ProcessHintRequest( IntRegister1, BoolRegister0, StringRegister0, FloatRegister0, ret_i, ret_s, rete_s);
      [*] = ;      StringRegister0 := ret_s;
      [*] = ;      StringRegister1 := rete_s;
      [*] = ;      IntRegister0 := ret_i;
      [*] = ;   end;
      [*] = ;   9 : begin
      [*] = ;      var ret_s,rete_s : String;
      [*] = ;      var ret_i : Integer;
      [*] = ;      BoolRegister0 := ProcessHintCallback( IntRegister1, BoolRegister0, StringRegister0, StringRegister1,'',0, ret_i, ret_s, rete_s);
      [*] = ;      StringRegister0 := ret_s;
      [*] = ;      StringRegister1 := rete_s;
      [*] = ;      IntRegister0 := ret_i;
      [*] = ;   end;
      [*] = ;   10 : IntRegister0 := CreateCommonTooltip(IntRegister1,IntRegister2, StringRegister1, StringRegister0, BoolRegister0, BoolRegister1);
      [*] = ;end;
   struct.end
section.end

