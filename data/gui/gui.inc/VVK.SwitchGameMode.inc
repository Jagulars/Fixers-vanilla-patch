section.begin
   Name = VVK.SwitchGameMode
   Description : struct.begin
      [*] = ;IntRegister0 - new mode: gc_gui_ModeXXX constants
      [*] = ;FloatRegister0 - time delay before switch
      [*] = ;StringRegister0 - parameters, separated by '|' - mode specific:
      [*] = ;gc_gui_ModeMap - action to perform (see state for details)
      [*] = ;gc_gui_ModeCastle - castle mode to activate + 1 (negative - should bring up hire hero panel if no heroes are present)
      [*] = ;gc_gui_ModeBattle - none so far
      [*] = ;RETURN:
      [*] = ;   BoolRegister0 - true if game was already in this mode
      [*] = ;   BoolRegister1 - true if switch occured during another switch
      [*] = ;   BoolRegister2 - true if switch was cancelled
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var state_params,switch_str : String;
      [*] = ;var new_mode,mode,dc : Integer;
      [*] = ;var was_in_transition : Boolean;
      [*] = ;var time_to_switch : Float;
      [*] = ;
      [*] = ;state_params := StringRegister0;
      [*] = ;new_mode := IntRegister0;
      [*] = ;switch_str := GetValueByName(cGUISwitchModeTimerName);
      [*] = ;if _log then _log_Gui('[REQ_STR] '+switch_str);
      [*] = ;
      [*] = ;if FloatRegister0 = 0 then
      [*] = ;   time_to_switch := 1.0
      [*] = ;else
      [*] = ;   time_to_switch := FloatRegister0;
      [*] = ;
      [*] = ;if _log then _log_Gui('[REQ_SM] Current: '+IntToStr(gIntRegister_GUIShardGameMode)+', New: '+IntToStr(new_mode)+', Time: '+FloatToStr(time_to_switch)+', Params: '+state_params);
      [*] = ;
      [*] = ;if switch_str <> '' then
      [*] = ;begin
      [*] = ;// switch is in progress already, just replace destinataion
      [*] = ;   was_in_transition := true;
      [*] = ;   dc := _sa_GetNum(switch_str);
      [*] = ;   mode := _sa_GetAsInt(switch_str,0);
      [*] = ;   if mode = new_mode then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := true;
      [*] = ;      BoolRegister1 := was_in_transition;
      [*] = ;      exit;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      Log('Nested mode switch attempted from mode '+IntToStr(gIntRegister_GUIShardGameMode)+' to mode '+IntToStr(new_mode)+', stored mode was '+IntToStr(mode));
      [*] = ;      BoolRegister0 := true;
      [*] = ;      BoolRegister2 := true;
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;   //if dc > 2 then
      [*] = ;   //   time_to_switch := _sa_GetAsInt(switch_str,2);
      [*] = ;end
      [*] = ;else
      [*] = ;   was_in_transition := false;
      [*] = ;
      [*] = ;if new_mode = gIntRegister_GUIShardGameMode then
      [*] = ;   time_to_switch := 0;
      [*] = ;
      [*] = ;switch_str := '';
      [*] = ;_sa_AddAsInt(switch_str,new_mode);
      [*] = ;_sa_AddAsFloat(switch_str,GetGameTime()+time_to_switch);
      [*] = ;_sa_AddAsFloat(switch_str,time_to_switch);
      [*] = ;_sa_Add(switch_str,state_params);
      [*] = ;
      [*] = ;IntRegister0 := 4;
      [*] = ;IntRegister1 := gIntRegister_GUIShardGameMode;
      [*] = ;IntRegister2 := new_mode;
      [*] = ;StringRegister0 := state_params;
      [*] = ;FloatRegister0 := time_to_switch;
      [*] = ;GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;
      [*] = ;if (not BoolRegister0) then
      [*] = ;begin
      [*] = ;   BoolRegister2 := true;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetValueByName(cGUISwitchModeTimerName,switch_str);
      [*] = ;
      [*] = ;   if (new_mode <> gIntRegister_GUIShardGameMode) or (was_in_transition) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 0;
      [*] = ;      IntRegister1 := gIntRegister_GUIShardGameMode;
      [*] = ;      IntRegister2 := new_mode;
      [*] = ;      StringRegister0 := state_params;
      [*] = ;      FloatRegister0 := time_to_switch;
      [*] = ;      GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;      BoolRegister0 := false;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      BoolRegister0 := true;
      [*] = ;   BoolRegister2 := false;
      [*] = ;end;
      [*] = ;BoolRegister1 := was_in_transition;
   struct.end
section.end

