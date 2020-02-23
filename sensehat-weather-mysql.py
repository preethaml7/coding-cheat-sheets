#!/usr/bin/python
from sense_hat import SenseHat
import time
import sys
import mysql.connector

sense = SenseHat()
sense.clear()

def main(config):
    try:
        while True:
            output = []
            cnx = mysql.connector.connect(**config)
            cur = cnx.cursor()

              # Read Temperature, Humidity & Pressure Data from SenseHat

            temperature = sense.get_temperature()
            temperature = round(temperature, 1)

            humidity = sense.get_humidity()
            humidity = round(humidity, 1)

            pressure = sense.get_pressure()
            pressure = round(pressure, 1)

            weather = (temperature, humidity, pressure)
            stmt_insert = "INSERT INTO weather (temperature, humidity, pressure) VALUES (%s, %s, %s)"
            cur.execute(stmt_insert, weather)
            cnx.commit()
            time.sleep(1)

            cur.close()
            cnx.close()

    except KeyboardInterrupt:
      pass

sense.clear()

if __name__ == '__main__':

    config = {
        'host': 'localhost',
        'port': 3306,
        'database': 'test_gtfs',
        'user': 'root',
        'password': 'test@123',
    }

main(config)


###### ~~~~~~~~~~~~ DDL FOR MYSQL 'weather' table
#   USE test_gtfs;
#   DROP TABLE IF EXISTS weather;
#   CREATE TABLE `weather` (
#       temperature VARCHAR(20),
#       humidity VARCHAR(50),
#       pressure VARCHAR(50)
#    );
#   COMMIT;
