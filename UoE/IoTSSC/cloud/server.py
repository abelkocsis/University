# File basis: tutorial code

from flask import Flask, make_response, jsonify, request, abort
from db_utils import add_data, get_entire_table, get_last_125_row, increase, get_sum_db, get_day, delete_not_important
from threading import Thread
from mbed_cloud import ConnectAPI
import json
from sklearn.preprocessing import StandardScaler
import joblib
import numpy as np
import time
import datetime
import requests
import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from create_ml import keepColumns, calculateFeatures, numOfSample, filterFeatures
from functools import wraps

webapp = Flask(__name__)

RESOURCE = "/3333/0/1"
DEVICE_ID = "01785b6b2614000000000001001091d4"
scaler = StandardScaler()
lastTime = time.time() - 20
isActive = False
milestones = [0, 20, 30, 40, 50, 60, 70, 200, 500, 9999999]

# Token to access to Firebase
firebaseServerToken = 'token'
# device Token in Firebase
deviceToken = 'token'
#Token which is required from the app side
appToken = '6#fJ5m9BBpjSM&r$heYbLS4GJqcqypjzLCcYLMqJ8M4qAgGLDpA*8&vb$8zNMH^uk8x@&tHDy$Yo5V9a$W&K6GDansQxW!9TjEW6du&4TKB3PsdP#mirTkvHXEm@ZAYQ'
classifier = KNeighborsClassifier(n_neighbors=7)

# Credit for the function: https://coderwall.com/p/4qickw/require-an-api-key-for-a-route-in-flask-using-only-a-decorator
def require_appkey(view_function):
    @wraps(view_function)
    # the new, post-decoration function. Note *args and **kwargs here.
    def decorated_function(*args, **kwargs):
        if request.headers.get('token') and request.headers.get('token') == appToken:
            return view_function(*args, **kwargs)
        else:
            abort(401)
    return decorated_function


# Used for testing
#@webapp.route('/history', methods=["GET"])
def history():
    table = get_entire_table()
    json_table = jsonify(table)
    resp = make_response(json_table, 200)
    return resp

# Returns the summary of each activity
@webapp.route("/getSum", methods=["GET"])
@require_appkey
def getSum():
    data = get_sum_db()
    if (len(data) == 0):
        data = [0,0,0,0,0,0,0]
    js = jsonify(data)
    resp = make_response(js, 200)
    return resp

# Predicts the current activity
def predict():
    lasts = get_last_125_row()
    df = pd.DataFrame(lasts, columns=keepColumns)
    features = calculateFeatures(df, 0)
    features.fillna(1, inplace=True)
    features = filterFeatures(features)
    feturesList = features.to_numpy()
    y_pred = classifier.predict(feturesList)
    predAsString = y_pred[0]
    print(predAsString)
    return predAsString

# Returns with a prediction
@webapp.route("/getPrediction", methods=["GET"])
@require_appkey
def getPrediction():
    predAsString = predict()
    resp = make_response(predAsString, 200)
    return resp

# Returns with daily statistics for a chosen activity
@webapp.route("/getDailyStats", methods=["GET"])
@require_appkey
def getDailyStats():
    activity = request.args.get('activity')
    if (activity != "run" and activity != "walk" and activity != "stair" and activity != "elevator"):
        return
    day = datetime.datetime.today()
    data = []
    for i in range(0,7):
        dailyData = get_day(day.strftime("%Y-%m-%d"), activity)
        if (dailyData == []):
            dailyData = [0]
        data += dailyData
        day = day - datetime.timedelta(days=1)
    data = data[::-1]
    js = jsonify(data)
    resp = make_response(js, 200)
    return resp

# Used for testing
#@webapp.route("/last_rows", methods=["GET"])
def latest_data():
    lasts = get_last_125_row()
    js = jsonify(lasts)
    resp = make_response(js, 200)
    return resp

# Returns with a boolean if the wearable device is active
@webapp.route("/isActive", methods=["GET"])
@require_appkey
def checkIsActive():
    global isActive
    global lastTime
    now = time.time()
    isActive = (now - lastTime) < 3
    resp = make_response(str(isActive), 200)
    return resp

# Returns with levels, previous and next milestones
@webapp.route("/getNextMilestonesAndLevels", methods=["GET"])
@require_appkey
def queryMilestonesLevels():
    js = jsonify(getMilestonesLevels())
    resp = make_response(js, 200)
    return resp

# Deletes unnecessary rows and notifies the app if necessary
def callUpdateAndNotify():
    global isActive
    global lastTime
    data = get_sum_db()
    if (data==[]):
        prevWalkLevel, prevRunLevel, prevStairLevel = 0, 0, 0
    else:
        walkTime = data[3]
        runTime = data[4]
        stairTime = data[5]
        prevWalkLevel = next(k for k, value in enumerate(milestones) if value > walkTime)
        prevRunLevel = next(k for k, value in enumerate(milestones) if value > runTime)
        prevStairLevel = next(k for k, value in enumerate(milestones) if value > stairTime)
    while True:
        now = time.time()
        isActive = (now - lastTime) < 3
        if (not isActive):
            time.sleep(3)
            continue
        data = get_last_125_row()
        if (len(data) < numOfSample):
            continue
        delete_not_important()
        data = get_sum_db()
        if (data!=[]):
            walkTime = data[3]
            runTime = data[4]
            stairTime = data[5]
            walkLevel = next(k for k, value in enumerate(milestones) if value > walkTime)
            runLevel = next(k for k, value in enumerate(milestones) if value > runTime)
            stairLevel = next(k for k, value in enumerate(milestones) if value > stairTime)
            if (walkLevel > prevWalkLevel):
                notify("walking", walkLevel)
                prevWalkLevel = walkLevel
            if (runLevel > prevRunLevel):
                notify("running", runLevel)
                prevRunLevel = runLevel
            if (stairLevel > prevStairLevel):
                notify("climbing stairs", stairLevel)
                prevStairLevel = stairLevel

# Calls the ML in every second and increases the databases
def callML():
    global isActive
    global lastTime
    lastMlTime = 0
    while True:
        sl = 1 - lastMlTime
        if (sl > 0):
            time.sleep(sl)
        startTime = round(time.time() * 1000)
        if (not isActive):
            time.sleep(3)
            lastMlTime = 0
            continue
        data = get_last_125_row()
        if (len(data) < numOfSample):
            continue
        activity = predict()
        increase(1, activity)
        endTime = round(time.time() * 1000)
        lastMlTime = (endTime - startTime) / 1000
        print("MLTIME: ", lastMlTime)

# Returns with the levels, previous and next milestones
def getMilestonesLevels():
    data = get_sum_db()
    if (data==[]):
        return [0, milestones[0], 0, milestones[0], 0, milestones[0]]
    walkTime = data[3]
    runTime = data[4]
    stairTime = data[5]

    walkLevel = next(k for k, value in enumerate(milestones) if value > walkTime)
    walkPrevMilestone = milestones[walkLevel-1]
    walkNextMilestone = milestones[walkLevel]

    runLevel = next(k for k, value in enumerate(milestones) if value > runTime)
    runPrevMilestone = milestones[runLevel-1]
    runNextMilestone = milestones[runLevel]

    stairLevel = next(k for k, value in enumerate(milestones) if value > stairTime)
    stairPrevMilestone = milestones[stairLevel-1]
    stairNextMilestone = milestones[stairLevel]
    
    return [walkLevel, walkPrevMilestone, walkNextMilestone, runLevel, runPrevMilestone, runNextMilestone, stairLevel, stairPrevMilestone, stairNextMilestone]

# Precoesses a new value
def processData(value):
    global lastTime
    global scaler
    lastTime = time.time()
    #print("allValue: ", value)
    allStrings = value.decode('UTF-8').split("|")
    for s in allStrings:
        if (s == "\x00"):
            break
        parts = s.split(";")
        magnetos = parts[1].split(",")
        magnetoX, magnetoY, magnetoZ = int(magnetos[0]), int(magnetos[1]), int(magnetos[2])
        gyros = parts[2].split(",")
        gyroX, gyroY, gyroZ = float(gyros[0]), float(gyros[1]), float(gyros[2])
        acceleros = parts[3].split(",")
        acceleroX, acceleroY, acceleroZ = int(acceleros[0]), int(acceleros[1]), int(acceleros[2])
        currId = parts[0]
        row = [[acceleroX, acceleroY, acceleroZ, gyroX, gyroY, gyroZ, magnetoX, magnetoY, magnetoZ]]
        row = scaler.transform(row)[0]
        acceleroX, acceleroY, acceleroZ, gyroX, gyroY, gyroZ, magnetoX, magnetoY, magnetoZ = row
        add_data(currId, magnetoX, magnetoY, magnetoZ, gyroX, gyroY, gyroZ, acceleroX, acceleroY, acceleroZ)

# Replaces the notification token
@webapp.route("/replaceNotificationToken", methods=["GET"])
@require_appkey
def replaceToken():
    global deviceToken
    newtoken = request.args.get('token')
    print(newtoken)
    if (newtoken == ""):
        return
    deviceToken = newtoken
    resp = make_response("ok", 200)
    return resp

# For testing
#@webapp.route("/notify", methods=["GET"])
def callNotify():
    notify("test-activity", 99)
    resp = make_response("ok", 200)
    return resp

# Notify abour ne level
def notify(activity, level):
    print("Sending notification")
    headers = {
        'Content-Type': 'application/json',
        'Authorization': 'key=' + firebaseServerToken,
    }

    message = "You reached level %i in %s!" %  (level, activity)

    body = {
          'notification': {'title': 'Level up!',
                            'body': message
                            },
          'to':
              deviceToken,
          'priority': 'high',
        }
    response = requests.post("https://fcm.googleapis.com/fcm/send",headers = headers, data=json.dumps(body))
    print(response.status_code)
    print(response.json())

# Handle new resource values
def _subscription_handler(device_id, path, value):
    t = Thread(target=processData, args=(value,))
    t.start()

# Connects to the device and subscribes to the resource, reconnects if needed
def receiveData():
    print("Trying to connect...")
    api = ConnectAPI()
    
    global isActive
    global lastTime
    try:
        api.start_notifications()
        time.sleep(0.5)
        value = api.get_resource_value(DEVICE_ID, RESOURCE, timeout=4)
        isActive = True
        lastTime = time.time()
        api.delete_subscriptions()
        api.add_resource_subscription_async(DEVICE_ID, RESOURCE, _subscription_handler)
        print("Connected")
        while isActive:
            pass
        api.delete_subscriptions()
        print("Disconnected")
        api.stop_notifications()
        time.sleep(1)
        receiveData()
    except:
        print("Connection failed")
        api.stop_notifications()
        time.sleep(3)
        receiveData()
    

if __name__ == "__main__":
    scaler = joblib.load('scaler2.bin')
    classifier = joblib.load('classifier6.bin')
    t = Thread(target=receiveData)
    t.start()
    t2 = Thread(target=callML)
    t2.start()
    t3 = Thread(target=callUpdateAndNotify)
    t3.start()
    webapp.run('0.0.0.0', port=2333) #ssl_context=('cert.pem', 'key.pem')