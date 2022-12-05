section.begin
   Name = DoInitSound
   Code : struct.begin
      [*] = ;//var threadHandle : Integer = GetSndAmbientThreadHandleByName('music');
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;//const cMaxTracksPerThread = 2;
      [*] = ;
      [*] = ;var threadName : String;
      [*] = ;var threadHandle : Integer;
      [*] = ;
      [*] = ;// clear the ambient thread used in non-patched game.
      [*] = ;threadHandle := GetSndAmbientThreadHandleByName('music');
      [*] = ;if threadHandle <> 0 then
      [*] = ;begin
      [*] = ;   SetSndAmbientThreadSetPlaying(False, threadHandle);
      [*] = ;   UnloadAmbientThread(threadHandle);
      [*] = ;end;
      [*] = ;
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
      [*] = ;threadName := 'old'; // we will use only this until new music system is fully implemented. 
      [*] = ;
      [*] = ;threadHandle := GetSndAmbientThreadHandleByName(threadName);
      [*] = ;if (threadHandle = 0) then
      [*] = ;begin
      [*] = ;   threadHandle := SndGetOrCreateAmbientThread(threadName);
      [*] = ;   //AmbientThreadListImportFile('.\data\sounds\ambient\'+threadName+'.cfg');
      [*] = ;   
      [*] = ;   //var trackName : String = 'track'+IntToStr(_sound_PickMusicTrack);
      [*] = ;   
      [*] = ;   //if _log then _log_Gui('DOINITSOUND, Ambient thread name: '+threadName+', Ambient thread handle: '+IntToStr(threadHandle)+' Picked music: '+trackName);
      [*] = ;   //SetSndAmbientThreadActiveSoundByName(trackName, threadHandle);
      [*] = ;
      [*] = ;   //if (GetSndAmbientThreadSoundHandleByName('track1',threadHandle) = 0) then
      [*] = ;   // AddSndAmbientThreadSound('track1',threadHandle);
      [*] = ;   //SetSndAmbientThreadSetPlaying(True, threadHandle);
      [*] = ;   //SetSndAmbientThreadLoop(False, threadHandle);
      [*] = ;   
      [*] = ;   
      [*] = ;   //SetSndAmbientThreadSetPlayingFade2(threadHandle, 2, 'music', 1);
      [*] = ;   //SetSndAmbientThreadSoundDelay(3, GetSndAmbientThreadSoundHandleByName(trackName, threadHandle)); 
      [*] = ;   //log('sound delay '+FloatToStr(GetSndAmbientThreadSoundDelay(threadHandle))); 
      [*] = ;   //log('trackname '+IntToStr(GetSndAmbientThreadSoundHandleByName(trackName, threadHandle)));
      [*] = ;   //CopyFileStream('.\data\sounds\ambient\08-Memories-M.ogg','.\data\sounds\ambient\current.ogg');
      [*] = ;end;//
      [*] = ;
      [*] = ;//if GetSndAmbientThreadLoop(threadHandle) then
      [*] = ;begin
      [*] = ;   if _log then _log_Gui('[COMMON.INC\DOINITSOUND.INC] Thread is looping. Stop playing, disable looping and unload the thread.');
      [*] = ;   SetSndAmbientThreadSetPlaying(False, threadHandle);
      [*] = ;   SetSndAmbientThreadLoop(False, threadHandle); // when thread is finished, we unload it and randomize a new set of tracks. Therefore, only a limited amount of tracks exist in memory concurrently and consequently memory should be saved.
      [*] = ;   UnloadAmbientThread(threadHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;{if (not GetSndAmbientThreadSetPlaying(threadHandle)) then
      [*] = ;begin
      [*] = ;   if _log then _log_Gui('Randomize a new set of music tracks');
      [*] = ;   _sound_RandomizeNewTracks(threadHandle, cMaxTracksPerThread);
      [*] = ;end;}
      [*] = ;
      [*] = ;SetSoundManagerMuteMode('svgInterface', (gProfile.sndmute=1));
      [*] = ;SetSoundManagerMuteMode('svgAmbient', (gProfile.sndmute=1));
      [*] = ;SetSoundManagerMuteMode('svgMusic', (gProfile.sndmute=1));
      [*] = ;SetSoundManagerMuteMode('svgSFX', (gProfile.sndmute=1));
      [*] = ;SetSoundManagerMuteMode('svgVoice', (gProfile.sndmute=1));
      [*] = ;
      [*] = ;SetProjectOptionAsFloat('Sound.Master', gProfile.sndmaster);
      [*] = ;SetProjectOptionAsFloat('svgMusic', gProfile.sndmusic);
      [*] = ;SetProjectOptionAsFloat('svgAmbient', gProfile.sndambient);
      [*] = ;SetProjectOptionAsFloat('svgSFX', gProfile.sndfx);
      [*] = ;//SetProjectOptionAsFloat('svgVoice', gProfile.sndvoice);
      [*] = ;SetProjectOptionAsFloat('svgInterface', gProfile.sndinterface);
      [*] = ;
   struct.end
section.end

