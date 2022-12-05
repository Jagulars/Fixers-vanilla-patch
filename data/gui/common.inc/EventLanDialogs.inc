section.begin
   Name = EventLanDialogs
   Code : struct.begin
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;
      [*] = ;if (status='shortcut') then
      [*] = ;begin
      [*] = ;   var cmd : String = StringRegister0;
      [*] = ;   //var cmd_attr : String = StringRegister1;
      [*] = ;   //var reg_attr : String = StringRegister2;
      [*] = ;   //var user_attr : String = StringRegister3;
      [*] = ;   //var mode : Integer = IntRegister0;
      [*] = ;
      [*] = ;   if StrExists(cmd,'battleshowmenu') then
      [*] = ;      IntRegister2 := 0
      [*] = ;   else
      [*] = ;      IntRegister2 := 2;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (status='button') then
      [*] = ;begin
      [*] = ;   var sPress  : String = GetValueByName('Press');
      [*] = ;   var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;   const cBtnGameTerminate = 110;
      [*] = ;
      [*] = ;   if (sPress='c') then
      [*] = ;   begin
      [*] = ;      case tag of
      [*] = ;         gc_lt_cancel_base_tag+gc_lt_loading,
      [*] = ;         gc_lt_cancel_base_tag+gc_lt_placement,
      [*] = ;         gc_lt_cancel_base_tag+gc_lt_restart_session,
      [*] = ;         cBtnGameTerminate: 
      [*] = ;         begin
      [*] = ;            _lan_stimer_Reset(gc_lt_ALL, true);
      [*] = ;            if GetLanMode >= 2 then
      [*] = ;               LanPublicServerCloseSession();
      [*] = ;            LanTerminateGame();
      [*] = ;            _misc_ParserGetOrCreateByKey('LanSync', true);
      [*] = ;            _run_DoCreateMenu();
      [*] = ;         end;
      [*] = ;         //gc_lt_cancel_base_tag+gc_lt_end_turn: begin
      [*] = ;         //end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   exit;
      [*] = ;end;
   struct.end
section.end

