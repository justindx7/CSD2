import simpleaudio as sa

noteTimes = []
kick = sa.WaveObject.from_wave_file("../Samples/kick.wav")


print("how many times should the sample be played?")
numPlaybackTimes = input("")


print("Enter " + numPlaybackTimes + " note times")
i = 1
while i<=int(numPlaybackTimes):
    y = input("")
    noteTimes.append(y)
    i=i+1

print(noteTimes)
print("BPM:")
bpm = input("")



