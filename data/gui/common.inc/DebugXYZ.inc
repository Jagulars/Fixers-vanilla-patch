section.begin
   Name = DebugXYZ
   Code : struct.begin
      [*] = ;var cmd : String = StringRegister0;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var res : Integer;
      [*] = ;
      [*] = ;var attribute : Integer = StrToInt(StringRegister1);
      [*] = ;
      [*] = ;res := 2;
      [*] = ;if (cmd='debugxyz') then
      [*] = ;begin
      [*] = ;   if (mode = 0) then
      [*] = ;   begin
      [*] = ;      Log('attribute '+IntToStr(attribute));
      [*] = ;      case attribute of
      [*] = ;         1,7 : gIntRegister_dbgX := gIntRegister_dbgX-1;
      [*] = ;         2,8 : gIntRegister_dbgX := gIntRegister_dbgX+1;
      [*] = ;         3,9 : gIntRegister_dbgY := gIntRegister_dbgY-1;
      [*] = ;         4,10 : gIntRegister_dbgY := gIntRegister_dbgY+1;
      [*] = ;         5 : gIntRegister_dbgZ := gIntRegister_dbgZ-1;
      [*] = ;         6 : gIntRegister_dbgZ := gIntRegister_dbgZ+1;
      [*] = ;         13, 11, 12 : Log('xOffset=' + IntToStr(gIntRegister_dbgX) + ' YOffset=' + IntToStr(gIntRegister_dbgY) + ' dbgZ=' + IntToStr(gIntRegister_dbgZ));
      [*] = ;         14 : begin
      [*] = ;            gIntRegister_dbgX := 0;
      [*] = ;            gIntRegister_dbgY := 0;
      [*] = ;            gIntRegister_dbgZ := 0;
      [*] = ;            Log('xOffset=' + IntToStr(gIntRegister_dbgX) + ' YOffset=' + IntToStr(gIntRegister_dbgY) + ' dbgZ=' + IntToStr(gIntRegister_dbgZ));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;res := 0;
      [*] = ;
      [*] = ;IntRegister2 := res;
   struct.end
section.end

