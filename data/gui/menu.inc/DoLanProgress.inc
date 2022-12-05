section.begin
   Name = DoLanProgress
   Code : struct.begin
      [*] = ;if IsLanPublicServerMode then
      [*] = ;begin
      [*] = ;   var lastLanPing : Float = GetFloatValueByName('LastLanPing');
      [*] = ;   
      [*] = ;   if ((lastLanPing+gc_PingInterval)<GetCurrentTime) then
      [*] = ;   begin
      [*] = ;      LanPublicServerSendMessage(LanMyInfoID, '');
      [*] = ;      SetFloatValueByName('LastLanPing', GetCurrentTime)
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

