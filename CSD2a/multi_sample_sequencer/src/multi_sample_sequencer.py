import time
import click
import simpleaudio as sa

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

#function to handle events
def eventHandler(event):
    if event['velocity'] > 0:
        event['sample'].play()


# load audio sample
kick = sa.WaveObject.from_wave_file("../../../Samples/kick.wav")
snare = sa.WaveObject.from_wave_file("../../../Samples/snare.wav")
shaker = sa.WaveObject.from_wave_file("../../../Samples/shaker.wav")

bpm = 120
print("Default bpm: ",bpm)

noteDurations = [0.25, 0.5, 0.25, 0.5, 0.5, 1, 1]

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

for i in range(len(timeStamps)):
    events.append(createEvent(timeStamps[i], kick, 127))

    events.append(createEvent(timeStamps[i], snare, 127))

    events.append(createEvent(timeStamps[i], shaker, 127))
    
print("amount of events" ,len(events))

zero_time = time.time()


# the i is used to determine the time stamp that should be used
i = 0

# start a time counter and look if the timestamps list is equal to the current time 
while True:
    now = time.time() - zero_time
    #Read time stamp from event
    if(now >= float(events[i]['timestamp'])):
        eventHandler(events[i])
        i = i + 1
        # if the i is at the end of the given list stop the loop
        if i == len(events):
            break
    # update time
    time.sleep(0.001)
# wait until the last sample is done playing     
time.sleep(timeStamps[-1])

