import time
import simpleaudio as sa

noteTimes = []
kick = sa.WaveObject.from_wave_file("../Samples/kick.wav")


print("how many times should the sample be played?")
numPlaybackTimes = input("")

print("Enter " + numPlaybackTimes + " note times")

# read playback times 
i = 1
while i<=int(numPlaybackTimes):
    y = input("")
    noteTimes.append(y)
    i+=1

print(noteTimes)

print("BPM:")
bpm = input("")

# calculate sample length
ms = 60/int(bpm)

# play samples
for t in noteTimes:
    kick.play()
    time.sleep(float(t) * float(ms))