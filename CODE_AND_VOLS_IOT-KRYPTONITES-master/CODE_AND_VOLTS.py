import speech_recognition as sr
#pyaudio
from firebase import firebase
from time import sleep
from win10toast import ToastNotifier
toaster =ToastNotifier()
name="switch on the light"
name1="switch on the fan"
name2="switch off the fan"
name3="switch off the light"
def firebase1(COMPONENT):
    fb = firebase.FirebaseApplication("https://kryptonites-home-automation-default-rtdb.firebaseio.com/", None)
    result = fb.put("",COMPONENT,"ON")
    print(result)
def firebase2(COMPONENT):
    fb = firebase.FirebaseApplication("https://kryptonites-home-automation-default-rtdb.firebaseio.com/", None)
    result = fb.put("",COMPONENT,"OFF")
    print(result)
def notifier(MESSAGE,COMPONENT,STATUS):
        print(44444444444)
        toaster.show_toast("speech_reg",MESSAGE,duration=10)
        if STATUS=="ON":
            firebase1(COMPONENT)
            sleep(2)
        elif STATUS=="OFF":
            firebase2(COMPONENT)
            sleep(2) 
def speech_reg():
    while 1:  
        r = sr.Recognizer()
        with sr.Microphone() as source:
            print("listening")
            r.energy_threshold=1000
            r.pause_threshold = 0.6
            audio = r.listen(source)   
            try:
                print("recognising...")
                print(55555555555)
                query = r.recognize_google(audio,language='en-in')
                if name in query:
                    notifier("LIGHTS ARE BEEN ON","LED_STATUS","ON")
                elif name1 in query:
                    notifier("FAN IS BEEN ON","FAN_STATUS","ON")
                elif name2 in query:
                    notifier("FAN IS BEEN OFF","FAN_STATUS","OFF")
                elif name3 in query:
                    notifier("LIGHTS ARE BEEN OFF","LED_STATUS","OFF")
                print(type(query))
                print("user said:",query)
            except Exception as e:
                print("say that again please...")
    return None
speech_reg()