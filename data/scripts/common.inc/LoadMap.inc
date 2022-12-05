section.begin
   Name = LoadMap
   Description : struct.begin
   [*] = ;StringRegister0 - map file name
   struct.end
   Code : struct.begin
      [*] = ;var map_file_name : String = StringRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\LOADMAP';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var i : Integer;
      [*] = ;var fnm,temp_str,lan_postfix : String;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+map_file_name+']',_log_trace);
      [*] = ;
      [*] = ;_prof_GetProfileFolder(temp_str,True);
      [*] = ;fnm := temp_str+'\'+gc_TempMap_FileName;
      [*] = ;
      [*] = ;if _misc_GetSaveNameLanPostFix(lan_postfix) then
      [*] = ;   map_file_name := map_file_name+lan_postfix;
      [*] = ;
      [*] = ;if IsFileExists(fnm+'.map') then DeleteFileStream(fnm+'.map');
      [*] = ;if IsFileExists(fnm+'.dat') then DeleteFileStream(fnm+'.dat');
      [*] = ;
      [*] = ;if IsFileExists(gStringRegister_ProfileSavesFolderLast+map_file_name+'.map') then
      [*] = ;begin
      [*] = ;   _init_DefaultGame();
      [*] = ;   
      [*] = ;   _prof_CreateZIPCommandsFile(map_file_name);
      [*] = ;   i := SteamAPPTriggerAchievements('-4|1',gc_gui_DelimiterChar,gc_gui_QuoteChar);
      [*] = ;   if i = 0 then
      [*] = ;      CopyFileStream(gStringRegister_ProfileSavesFolderLast+map_file_name+'.map',fnm+'.map');
      [*] = ;
      [*] = ;   SetUserProfileCustomsRoot('\..\');
      [*] = ;   UserProfileRefreshCustomsList();
      [*] = ;   UserProfileLoadCustom(gc_TempMap_FileName);
      [*] = ;end
      [*] = ;else
      [*] = ;   ErrorLogI(_log_name+' Map file '+gStringRegister_ProfileSavesFolderLast+map_file_name+'.map not found');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

