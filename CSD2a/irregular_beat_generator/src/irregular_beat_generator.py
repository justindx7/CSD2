import simpleaudio as sa
import click
import random
import playLoop
from midiutil import MIDIFile
def main():
    # Calculate amount of sixteen notes in the user input time signature
    def sigCalculator(a,b):
        c = a * 16 /b
        print("amount of sixteen notes per bar: ", c)  
        c = c * 0.25
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
    def createEvent(timestamp,sample,velocity,midiNote,midiDur,name):
        return {
            'timestamp': timestamp,
            'sample': sample,
            'velocity': velocity,
            'midi_note': midiNote,
            'midi_dur': midiDur,
            'name': name
        }

    events = []

    # load audio samples
    kick = sa.WaveObject.from_wave_file("../../../Samples/kick.wav")
    snare = sa.WaveObject.from_wave_file("../../../Samples/snare.wav")
    shaker = sa.WaveObject.from_wave_file("../../../Samples/shaker.wav")


    # choose time signature and calculate note lenghts
    while True:    
        try:
            x, y = input("Enter a time signature: ").split("/")
            x = int(x)
            y = int(y)            
        except:
            print("input was not correct try again")
            print("should be 'number1'/'number2'")
        else:
            if(x == 0 or y == 0):
                print("input cant be zero")
                continue
            if(x > 16 or y > 16):
                print("input cant be bigger than 16")
                continue
            print("time signature: ", x,"/",y)
            break

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
            try:
                bpm = int(input("BPM:"))
            except ValueError:
                print("Value was not correct syntax try again") 
            except:
                print("input was not correct try again") 
            else:
                if(bpm < 10):
                    print("bpm to low minimum bpm is 10")
                    continue
                if(bpm > 200):
                    print("bpm to low minimum bpm is 200")
                    continue
                print("BPM: ",bpm)
                break


    # create list with 16ths timestamps calculated in the function 
    timestamps16th = durationsToTimestamps16th(noteDurations)
    print("16TH:", timestamps16th)

    # create list with ms timestamps calculated in the function
    timeStamps = timestampsToDelay(timestamps16th, bpm)
    print("16TH Time stamp:", timeStamps)


    # For loop that makes the sound events  and puts them in a list. 
    for i in range(len(timeStamps)):

        if(noteDurations[i] >= 0.75):
            events.append(createEvent(timeStamps[i], kick, 127, 36,noteDurations[i],"kick"))

        if(noteDurations[i] == 0.5):
            events.append(createEvent(timeStamps[i], snare, 127, 40,noteDurations[i],"snare"))

        if(noteDurations[i] <= 0.25):
            events.append(createEvent(timeStamps[i], shaker, 127, 42,noteDurations[i], "shaker"))
        
    print("amount of events" ,len(events))
    thread1 = playLoop.playLoop(1,"Thread-playLoop",events)
    thread1.start()


    #https://pypi.org/project/MIDIUtil/
    #https://github.com/ciskavriezenga/CSD_21-22/blob/master/csd2a/theorie/6_midpoint_displacement.py
    #____create midi output____
    def createMIDI(tmpbpm):
        mf = MIDIFile(1)
        track = 0
        time = 0
        channel = 0
        volume = 60
        tempo = tmpbpm
        mf.addTrackName(track, time, "random generated drum rhythm")
        mf.addTempo(track, time, tempo)

        # add the notes from the note_sequence
        for i in events:
            print(i)
            dur = i["midi_dur"]
            mf.addNote(track, channel, i["midi_note"],
                        time, dur, volume)
            # increment time based on the duration of the added note
            time = time + dur
            print(time)

        with open("myDrumRhythm.mid",'wb') as outf:
            mf.writeFile(outf)
    print("typ help for command list")
    while True:
        userinput = input()
        if(userinput == "end"): 
            thread1.terminate()
            thread1.join
            print("terminated playLoop Thread")
        elif(userinput == "help"): 
            print("--help list--")
            print(" end: ends the drum loop") 
            print(" help: shows all commands") 
            print(" exit: stops program")
            print(" save: saves drum rhythm in midi file") 
            print(" restart: generates new drumloop")
        elif(userinput == "exit"):  
            thread1.terminate()
            thread1.join
            quit()
        elif(userinput == "save"):
            print("saving drum rhythm to midi")
            # write midifile to disk
            createMIDI(bpm)
            thread1.terminate()
            thread1.join()
        elif(userinput == "restart"):
            thread1.terminate()
            thread1.join            
            main()
        else:
            print("not a valid command, type help for a list")
            
main()


