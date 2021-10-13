import simpleaudio as sa
import click
import time
import random
import threading
import playLoop

# Calculate amount of sixteen notes in the user input time signature
def sigCalculator(a,b):
    if b == 4:
        c = a * b

    elif b == 8:
        c = a * 2
    
    c = c * 0.25
    print("amount of sixteen notes per bar: ", c)  
    return c

# function to turn noteDurations into 16ths timestamps (make a 16th grid)
def durationsToTimestamps16th(note_Durations):
    timestamps_16th = []
    sum = 0 
    for i in note_Durations:
        timestamps_16th.append(sum)
        sum = sum + i * 4
    return timestamps_16th

# function to convert the 16ths timestamps into ms
def timestampsToDelay(timestamps_16th, _BPM):
    quarterNoteDuration = 60 / int(_BPM)
    sixteenthNoteDuration = quarterNoteDuration / 4.0
    time_Stamps = []
    for i in timestamps_16th:
       time_Stamps.append(i * sixteenthNoteDuration)
    return time_Stamps

# function to create an event
def createEvent(timestamp,sample,velocity):
    return {
        'timestamp': timestamp,
        'sample': sample,
        'velocity': velocity
    }

events = []

# load audio samples
kick = sa.WaveObject.from_wave_file("../../../Samples/kick.wav")
snare = sa.WaveObject.from_wave_file("../../../Samples/snare.wav")
shaker = sa.WaveObject.from_wave_file("../../../Samples/shaker.wav")


# choose 2 time signatures and calculate note lenghts
while True:
    x, y = input("Enter a time signature: ").split("/")
    try:
        val = int(x)
        val = int(y)
        print("time signature: ", x,"/",y)
        break
    except ValueError:
        print("Value was not correct syntax try again")

totalAmount = sigCalculator(int(x),int(y))
amount = totalAmount - 1

#fill noteDurations with random notes that fit in the Time signature
noteDurations = []
tmp = 0
while True:
    rnd = random.randrange(25, 100, 25) / 100
    tmp = tmp + rnd
    noteDurations.append(rnd)
    print(tmp)
    if(tmp >= amount):
        noteDurations.append(totalAmount - tmp)
        break
    
print(noteDurations)


# do bmp stuff like calculating note times
bpm = 120
print("Default bpm: ",bpm)

# [Y/n] question to change bpm
if click.confirm('Do you want to edit the bpm?', default=True):
    while True:
        bpm = input("")
        try:
            val = int(bpm)
            print("BPM: ",bpm)
            break
        except ValueError:
            print("Value was not correct syntax try again")  

# create list with 16ths timestamps calculated in the function 
timestamps16th = durationsToTimestamps16th(noteDurations)
print("16TH:", timestamps16th)

# create list with ms timestamps calculated in the function
timeStamps = timestampsToDelay(timestamps16th, bpm)
print("16TH Time stamp:", timeStamps)


# For loop that makes the sound events  and puts them in a list.
for i in range(len(timeStamps)):

    if(noteDurations[i] >= 0.75):
        events.append(createEvent(timeStamps[i], kick, 127))

    if(noteDurations[i] == 0.5):
        events.append(createEvent(timeStamps[i], snare, 127))

    if(noteDurations[i] <= 0.25):
        events.append(createEvent(timeStamps[i], shaker, 127))
    
print("amount of events" ,len(events))
thread1 = playLoop.playLoop(1,"Thread-playLoop",events)
thread1.start()




