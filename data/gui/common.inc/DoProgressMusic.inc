section.begin
   Name = DoProgressMusic
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;var threadName : String;
      [*] = ;
      [*] = ; //  log('current ogg exists '+BoolToStr(IsFileExists('.\data\sounds\ambient\current.ogg'))); 
      [*] = ;//SoundManagerUnloadAmbientThreads;
      [*] = ;case gIntRegister_CurGameMode of
      [*] = ;   gc_GameModeMenu : 
      [*] = ;   begin
      [*] = ;      threadName := 'menu';
      [*] = ;   end;
      [*] = ;   gc_GameModeAstral : 
      [*] = ;   begin
      [*] = ;      threadName := 'astral';
      [*] = ;   end;
      [*] = ;   gc_GameModeStrategy,gc_GameModeTactics : 
      [*] = ;   begin
      [*] = ;      threadName := 'shard';
      [*] = ;   end;
      [*] = ;   {gc_GameModeTactics : 
      [*] = ;   begin
      [*] = ;      threadName := 'battle';
      [*] = ;   end;}
      [*] = ;end;
      [*] = ;      threadName := 'old';
      [*] = ;var threadHandle : Integer = GetSndAmbientThreadHandleByName(threadName);
      [*] = ;//if (GetCurrentTime > 15) and (GetCurrentTime < 16) then begin
      [*] = ;  // SoundManagerUnloadAmbientThreads;
      [*] = ;   //UnloadAmbientThread(threadHandle);
      [*] = ;   //SetSndAmbientThreadActiveSoundByName('track58',threadHandle);
      [*] = ;   //AmbientThreadListImportFile('.\data\sounds\ambient\ambient2.cfg');
      [*] = ;//end;
      [*] = ;//if GetCurrentTime > 20 then
      [*] = ;//   PreloadAmbientThread(threadHandle);
      [*] = ;{log('threadHandle '+IntToStr(threadHandle)); 
      [*] = ;log('playing '+BoolToStr(GetSndAmbientThreadSetPlaying(threadHandle))); 
      [*] = ;log('soundHandle -1: '+IntToStr(GetSndAmbientThreadSoundHandleByIndex(-1, threadHandle))); 
      [*] = ;log('soundHandle 0: '+IntToStr(GetSndAmbientThreadSoundHandleByIndex(0, threadHandle))); 
      [*] = ;log('soundHandle 1: '+IntToStr(GetSndAmbientThreadSoundHandleByIndex(1, threadHandle))); 
      [*] = ;log('soundHandle 2: '+IntToStr(GetSndAmbientThreadSoundHandleByIndex(2, threadHandle))); 
      [*] = ;log('soundHandle 3: '+IntToStr(GetSndAmbientThreadSoundHandleByIndex(3, threadHandle))); 
      [*] = ;log('soundHandle name 10: '+IntToStr(GetSndAmbientThreadSoundHandleByName('track10', threadHandle))); 
      [*] = ;log('soundHandle name 20: '+IntToStr(GetSndAmbientThreadSoundHandleByName('track20', threadHandle))); }
      [*] = ;
      [*] = ;      if _log then _log_Gui('DoProgressMusic '+threadName);
      [*] = ;// check if music track has finished
      [*] = ;if (threadHandle <> 0) then 
      [*] = ;begin
      [*] = ;   //if _log then _log_Gui('Thread handle: '+IntToStr(threadHandle));
      [*] = ;      if _log then _log_Gui('Looping: '+BoolToStr(GetSndAmbientThreadLoop(threadHandle)));
      [*] = ;      if _log then _log_Gui('Playing: '+BoolToStr(GetSndAmbientThreadSetPlaying(threadHandle)));
      [*] = ;   //if (GetSndAmbientThreadSoundHandleByName('track59', threadHandle) = 0) then 
      [*] = ;   {if (GetSndAmbientThreadSoundHandleByIndex(0, threadHandle) = 0) then 
      [*] = ;   begin
      [*] = ;      if _log then _log_Gui('Make a new music set...');
      [*] = ;      GUIExecuteState('DoInitSound'); // randomize a new set
      [*] = ;   end
      [*] = ;   else}
      [*] = ;   if (not GetSndAmbientThreadLoop(threadHandle)) and (not GetSndAmbientThreadSetPlaying(threadHandle)) then 
      [*] = ;   begin
      [*] = ;      _log_Gui('Randomize a new set of music tracks');
      [*] = ;      UnloadAmbientThread(threadHandle);
      [*] = ;      
      [*] = ;      const cMaxTracksPerThread = 3;
      [*] = ;      _misc_ArrayGetRandomIndices(cMaxTracksPerThread, 1, 19, False);
      [*] = ;      
      [*] = ;      var trackName : String;
      [*] = ;      var i, trackIndex : Integer;
      [*] = ;      for i := 0 to ArrayGetCount-1 do
      [*] = ;      begin
      [*] = ;         trackIndex := ArrayGetValueByIndex(i);
      [*] = ;         trackName := 'track'+IntToStr(trackIndex);
      [*] = ;         _log_gui('track randomized: '+trackName);
      [*] = ;         //SetSndAmbientThreadActiveSoundByName(trackName, threadHandle);
      [*] = ;         AddSndAmbientThreadSound('track'+IntToStr(trackIndex), threadHandle);
      [*] = ;      end;
      [*] = ;      ArrayClear();
      [*] = ;      
      [*] = ;      SetSndAmbientThreadSetPlaying(True, threadHandle);
      [*] = ;      SetSndAmbientThreadLoop(False, threadHandle);
      [*] = ;      //UnloadAmbientThread(threadHandle);
      [*] = ;      //_sound_RandomizeNewTracks(threadHandle, cMaxTracksPerThread);
      [*] = ;      {var trackName : String = 'track'+IntToStr(_sound_PickMusicTrack);
      [*] = ;      SetSndAmbientThreadSoundDelay(10, GetSndAmbientThreadSoundHandleByName(trackName, threadHandle));
      [*] = ;      if _log then _log_Gui('Music finished. New Music: '+trackName);
      [*] = ;      SetSndAmbientThreadActiveSoundByName(trackName, threadHandle);
      [*] = ;      //SetSndAmbientThreadActiveSoundByName('track'+IntToStr(Floor(Random*51)+1), threadHandle);
      [*] = ;      SetSndAmbientThreadSetPlaying(True, threadHandle);}
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

