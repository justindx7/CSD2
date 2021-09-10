import simpleaudio as sa

wave_obj = sa.WaveObject.from_wave_file("../Samples/kick.wav")
play_object = wave_obj.play()
play_object.wait_done()