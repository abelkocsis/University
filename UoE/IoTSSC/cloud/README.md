# Readme

This code was tested on a Mac and a Debian machine.

## Files

- .env: environment variable for the Pelion Cloud 
- classifier6.bin: binary of the pretrained KNN classifier
- create_ml.py: script for training a new ML and fitting a scaler
- db_utils.py: script for accessing the mySQL database
- init.sql: commands to initialize the mySQL database
- scaler6.bin: binary of the pre-fitted scaler
- serper.py: the code of the server. Run this for a Flask server

## Requirements

- pandas
- numpy
- sklearn
- joblib
- math
- antropy
- flask
- threading
- mbed_cloud
- time
- datetime
- requests
- functools
- pymysql
