section.begin
   Name = VVK.map.HintProvDetailsCallback
   Description : struct.begin
      [*] = ;See VVK.ProcessHintGUI for details
      [*] = ;mood value+','+usual tt text
   struct.end
   Code : struct.begin
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var ext : Boolean = BoolRegister0;
      [*] = ;//var windowHandle : Integer = IntRegister1;
      [*] = ;//var mx : Integer = IntRegister2;
      [*] = ;//var my : Integer = IntRegister3;
      [*] = ;var pars : String = StringRegister0;
      [*] = ;var r : Integer = 0;
      [*] = ;var f : Integer = 0;
      [*] = ;var text : String = '';
      [*] = ;var text_e : String = '';
      [*] = ;
      [*] = ;if (mode=cFloatTooltipOnHint) then
      [*] = ;begin
      [*] = ;   gIntRegister_MoodDummyUID := _sa_GetAsInt_D(pars,0,$2c);
      [*] = ;   _sa_Get_D(pars,1,$2c,text);
      [*] = ;   r := 3;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := r;
      [*] = ;IntRegister1 := f;
      [*] = ;StringRegister0 := text;
      [*] = ;StringRegister1 := text_e;
   struct.end
section.end

