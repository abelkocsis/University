# Basis: tutorial code

import numpy as np
import datetime
import pymysql
from create_ml import numOfSample

select_all = '''select * from d1; '''
add_row = ''' insert into d1 (timestamp, magnetoX, magnetoY, magnetoZ, gyroX, gyroY, gyroZ, acceleroX, acceleroY, acceleroZ) values ("%s", %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f)'''
select_last_125_row = '''select magnetoX, magnetoY, magnetoZ, gyroX, gyroY, gyroZ, acceleroX, acceleroY, acceleroZ from (select * from d1 order by id DESC limit %i) sub order by id ASC; '''

def add_data(currId, magnetoX, magnetoY, magnetoZ, gyroX, gyroY, gyroZ, acceleroX, acceleroY, acceleroZ):
    conn = pymysql.connect(host="localhost", user="d1_user", password='R4EzqtcqY4Nz669sSmjja2d8tCyTNu', database="deviceData")
    #timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H-%M-%S")
    with conn.cursor() as cursor:
        cursor.execute(add_row % (currId, magnetoX, magnetoY, magnetoZ, gyroX, gyroY, gyroZ, acceleroX, acceleroY, acceleroZ))
    conn.commit()
    #print("row added")

def get_entire_table():
    conn = pymysql.connect(host="localhost", user="d1_user", password='R4EzqtcqY4Nz669sSmjja2d8tCyTNu', database="deviceData")
    with conn.cursor() as cursor:
        cursor.execute(select_all)
        table = cursor.fetchall()
        #print(table)
        return table


def get_last_125_row():
    conn = pymysql.connect(host="localhost", user="d1_user", password='R4EzqtcqY4Nz669sSmjja2d8tCyTNu', database="deviceData")
    with conn.cursor() as cursor:
        cursor.execute(select_last_125_row % numOfSample)
        lasts = cursor.fetchall()
        return lasts

def get_sum_db():
    conn = pymysql.connect(host="localhost", user="d1_user", password='R4EzqtcqY4Nz669sSmjja2d8tCyTNu', database="deviceData")
    with conn.cursor() as cursor:
        cursor.execute("SELECT * FROM activitySum")
        data = cursor.fetchall()
        if len(data) == 0:
            return []
        return data[0]

def get_day(activityDate, activityType):
    conn = pymysql.connect(host="localhost", user="d1_user", password='R4EzqtcqY4Nz669sSmjja2d8tCyTNu', database="deviceData")
    with conn.cursor() as cursor:
        query = "SELECT %s FROM dailyActivity WHERE activityDate = '%s'" % (activityType, activityDate)
        cursor.execute(query)
        data = cursor.fetchall()
        if (len(data) > 0):
            return data[0]
        return []

def delete_not_important():
    conn = pymysql.connect(host="localhost", user="d1_user", password='R4EzqtcqY4Nz669sSmjja2d8tCyTNu', database="deviceData")
    with conn.cursor() as cursor:
        query = "SELECT COUNT(*) FROM d1;"
        cursor.execute(query)
        data = cursor.fetchall()
        rowCount = int(data[0][0])
        if (rowCount > 250):
            query = "DELETE FROM d1 ORDER BY id ASC limit %s;" % str(rowCount - 250)
            cursor.execute(query)
            conn.commit()

        

def increase(second, activity):
    conn = pymysql.connect(host="localhost", user="d1_user", password='R4EzqtcqY4Nz669sSmjja2d8tCyTNu', database="deviceData")
    date = datetime.datetime.now().strftime("%Y-%m-%d")
    with conn.cursor() as cursor:
        cursor.execute("SELECT * FROM dailyActivity WHERE activityDate = %s", date)
        if (cursor.rowcount == 0):
            cursor.execute("INSERT INTO dailyActivity (activityDate, idle, walk, run, stair, elevator) VALUES (%s, 0, 0, 0, 0, 0)", date)
            conn.commit()
        cursor.execute("SELECT * FROM activitySum")
        if (cursor.rowcount == 0):
            cursor.execute("INSERT INTO activitySum (idle, walk, run, stair, elevator) VALUES (0, 0, 0, 0, 0)")
            conn.commit()
        cursor.execute("SELECT * FROM dailyActivity WHERE activityDate = %s", date)
        data = cursor.fetchall()
        cursor.execute("SELECT * FROM activitySum")
        dataSum = cursor.fetchall()

        idle, walk, run, stair, elevator = data[0][3:]
        idleSum, walkSum, runSum, stairSum, elevatorSum = dataSum[0][2:]
        if (activity == "IDLE"):
            idle = idle+second
            idleSum = idleSum+second
        if (activity == "WALK"):
            walk = walk+second
            walkSum = walkSum + second
        if (activity == "RUN"):
            run = run+second
            runSum = runSum + second
        if (activity == "STAIR"):
            stair = stair+second
            stairSum = stairSum + second
        if (activity == "ELEVATOR"):
            elevator = elevator+second
            elevatorSum = elevatorSum + second
        update_row = "UPDATE dailyActivity SET idle = %i, walk = %i, run = %i, stair = %i, elevator = %i WHERE activityDate = '%s'" % (idle, walk, run, stair, elevator, date)
        cursor.execute(update_row)

        update_row = "UPDATE activitySum SET idle = %i, walk = %i, run = %i, stair = %i, elevator = %i" % (idleSum, walkSum, runSum, stairSum, elevatorSum)
        cursor.execute(update_row)

    conn.commit()


if __name__ == "__main__":
    get_entire_table()