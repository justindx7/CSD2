import time
import click
import simpleaudio as sa

# load audio sample
kick = sa.WaveObject.from_wave_file("../../../Samples/kick.wav")

bpm = 120


print("Default bpm: ",bpm)
noteDurations = [0.25, 0.5, 0.25, 0.5, 0.5, 1, 1]


if click.confirm('Do you want to edit the bpm?', default=True):
    while True:
        bpm = input("")
        try:
            val = int(bpm)
            print("BPM: ",bpm)
            break
        except ValueError:
            print("Value was not correct syntax try again")  

quarterNoteDuration = 60 / int(bpm)
sixteenthNoteDuration = quarterNoteDuration / 4.0


def durationsToTimestamps16th(note_Durations):
    timestamps_16th = []
    sum = 0 
    for i in note_Durations:
        timestamps_16th.append(sum)
        sum = sum + i * 4
    return timestamps_16th

timestamps16th = durationsToTimestamps16th(noteDurations)
print("16TH:", timestamps16th)

def timestampsToDelay(timestamps_16th, _BPM):
    time_Stamps = []
    for i in timestamps_16th:
       time_Stamps.append(i * sixteenthNoteDuration)
    return time_Stamps
    
timeStamps = timestampsToDelay(timestamps16th, bpm)
print("16TH Time stamp:", timeStamps)

  

zero_time = time.time()
i = 0
while True:
    now = time.time() - zero_time
    if(now >= float(timeStamps[i])):
        kick.play()
        print("kick", i)
        i = i + 1
        if i == len(timeStamps):
            break
    time.sleep(0.001)
     
time.sleep(timeStamps[-1])

