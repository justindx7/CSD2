import simpleaudio as sa

wave_obj = sa.WaveObject.from_wave_file("patch/to/file.wav")
play_object = wave_obj.play()
play_object.wait_done()