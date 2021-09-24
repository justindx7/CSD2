from time import time
import click
bpm = 120

quarterNoteDuration = 60 / bpm
sixteenthNoteDuration = quarterNoteDuration / 4.0

timeStamps = []
print("Default bpm: ",bpm)
noteDurations = [0.25, 0.5, 0.25, 0.5, 0.5, 1, 1]

timestamps16th = []


def durationsToTimestamps16th():
    sum = 0
    for i in noteDurations:
        timestamps16th.append(sum)
        sum = sum + i * 4


durationsToTimestamps16th()
print("16TH:", timestamps16th)

def timestampsToDelay():
   for i in timestamps16th:
       timeStamps.append(i * sixteenthNoteDuration)
    
  
timestampsToDelay()
print("16TH Time stamp:", timeStamps)

if click.confirm('Do you want to edit the bpm?', default=True):
    while True:
        bpm = input("")
        try:
            val = int(bpm)
            print("BPM: ",bpm)
            break
        except ValueError:
            print("Value was not correct syntax try again")        

i = 1
while i < len(timeStamps):
    time = timeStamps[i] - timeStamps[i-1]
    print("time: ", time)
    i += 1     
