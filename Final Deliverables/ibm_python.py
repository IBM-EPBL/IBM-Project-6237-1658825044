import wiotp.sdk.device
import time
import random
import requests

myConfig = {
    "identity": {
        "orgId": "10ilxy",
        "typeId": "temphum",
        "deviceId":"ticece"
    },
    "auth": {
        "token": "&1of4gQxPXz-JD(0?E"
    }
}

def myCommandCallback(cmd):
    print("Message received from IBM IoT Platform: %s" % cmd.data['command'])
    m=cmd.data['command']
random.random()
client = wiotp.sdk.device.DeviceClient(config=myConfig, logHandlers=None)
client.connect()

while True:
    BASE_URL = "https://api.openweathermap.org/data/2.5/weather?"
    CITY = "Coimbatore"
    API_KEY = "46faa4ab6fede1d9ae549b90d91253f2"
    URL = BASE_URL + "q=" + CITY + "&appid=" + API_KEY
    response = requests.get(URL)
    if response.status_code == 200:
        data = response.json()
        main = data['main']
        temp = round(main['temp'] - 273, 2)
        humy = main['humidity']
        pres = main['pressure']
        rept = data['weather']
        report = rept[0]['description']
    temp1=temp
    if(temp1 < 5):
        alert = "Snow fall may occur"
    hum=humy
    if(hum>85):
        alert = "Probablity of raining is high. Take rain coat with you"
    pre = pres
    wea = report
    if(wea == "clear sky"):
        wea_alt1 = "HAPPY JOURNEY!!!"
        spd_alt1 = "GO @ < 80Kmph!!!"
    elif(wea == "few clouds" or "haze"):
        wea_alt1 = "CLOUDY DAY :)"
        spd_alt1 = "GO @ < 60Kmph!!!"
    elif (wea == "overcast clouds"):
        wea_alt1 = "RAIN MAY COME!!"
        spd_alt1 = "GO @ < 30Kmph!!!"
    elif(wea == "shower rain"):
        wea_alt1 = "SLIPPERY ROAD :("
        spd_alt1 = "GO @ < 20Kmph!!!"
    elif(wea == "rain" or "moderate rain"):
        wea_alt1 = "SLIPPERY ROAD :("
        spd_alt1 = "GO @ < 20Kmph!!!"
    elif(wea == "thunderstorm"):
        wea_alt1 = "HEAVY RAIN!!!"
        spd_alt1 = "GO @ < 10Kmph!!!"
    elif (wea == "snow"):
        wea_alt1 = "SNOW ON ROAD!!!"
        spd_alt1 = "GO @ < 10Kmph!!!"
    elif(wea == "mist"):
        wea_alt1 = "TURN ON FOG LAMP"
        spd_alt1 = "GO @ < 20Kmph!!!"
    else:
        wea_alt1 = "HAPPY JOURNEY :)"
        spd_alt1 = "GO @ < 80Kmph!!!"
    xyz = time.ctime()
    ctime = int(xyz[11:13])
    if (ctime > 8 and ctime < 10) or (ctime > 15 and ctime < 18):
        me = 'SCHOOL TIMING GO SLOW SPEED LIMIT: 15Kmph'
        spd_alt1 = "GO @ < 15Kmph!!!"
    else:
        me = xyz[11:19]
    myData={'location':CITY,'temperature':temp, 'humidity':hum, 'pressure':pre,
            'weather_report':wea,'wea_alt':wea_alt1,'spd_alt':spd_alt1,'schl_tmg':me}
    client.publishEvent(eventId="status", msgFormat="json", data=myData, qos=0, onPublish=None)
    print("Published data Successfully: %s", myData)
    client.commandCallback = myCommandCallback
    time.sleep(1)
client.disconnect()