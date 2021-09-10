import simpleaudio as sa

print("how many times should the sample be played?")
x = input("")

i = 1

while i<=int(x):
    wave_obj = sa.WaveObject.from_wave_file("../Samples/kick.wav")
    play_object = wave_obj.play()
    play_object.wait_done()
    i=i+1