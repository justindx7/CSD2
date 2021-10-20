import threading
import time
import simpleaudio


class playLoop(threading.Thread):
    def __init__(self,threadID,name,eventList):
        threading.Thread.__init__(self)
        self._running = True
        self.threadID = threadID
        self.name = name
        self.eventList = eventList
        self.on = True
    
    def terminate(self):
        self.on = False

    
    #_____ALL TIME STUFF IS DONE HERE_____
    def run(self):
        self.on = True
        print("Starting " + self.name)
        zeroTime = time.time()

        # the i is used to determine the time stamp that should be used
        i = 0

        # start a time counter and look if the timestamps list is equal to the current time 
        while self.on:
            now = time.time() - zeroTime
            #Read time stamp from event
            if(now >= self.eventList[i]['timestamp']):
                self.eventHandler(self.eventList[i])
                i = i + 1
                # if the i is at the end of the given list reset i and zero_time
                if i == len(self.eventList):
                    i = 0
                    zeroTime = time.time()            
            # update time
            time.sleep(0.001)
        # wait until the last sample is done playing   
    #function to handle events
    def eventHandler(self,event):
        if event['velocity'] > 0:
            event.get('sample').play()  

