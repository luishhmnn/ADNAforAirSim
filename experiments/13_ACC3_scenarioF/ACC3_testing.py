"""
@author: Luis Hohmann

This script runs scenario F of ACC1 100 times.

IMPORTANT NOTES:
- Before you start the script, make sure you start it inside its
  directory! Otherwise, the log files are stored elsewhere.
- You have to install the third-party package pyautogui. You can
  do this by running `pip install pyautogui` in a command prompt.
- Make sure that AirSim always starts in a window. You can toggle
  between window and full screen mode by pressing 'Alt+Enter'.
"""

import os
import time
import glob
import pathlib

import pyautogui

import airsim

# Paths & file names
dir_path = pathlib.Path(__file__).parent.resolve()     # Directory path of this script

airsim_settings_file_name = '13_ACC3_scenarioF.json'    # Name of the AirSim settings .json
airsim_settings_path = os.path.join(dir_path,
                        airsim_settings_file_name)     # Path of the AirSim settings .json

# Run AirSim (CityEnviron.exe)
run_command_airsim = f"""start "AirSim CityEnviron" "{dir_path}\\..\\..\\AirSimServer\\CityEnviron\\WindowsNoEditor\\CityEnviron.exe" --settings "{airsim_settings_path}" """
os.system(run_command_airsim)

print("Plese wait until AirSim started up...")
time.sleep(3)

while True:
    mode = None
    while True:
        user_input = input("Press S to start the simulation. Press M to drive manually. (S/M)?")
        if user_input.upper() == "S":
            mode = 0
            break
        if user_input.upper() == "M":
            mode = 1
            break

    if mode ==0:
        client = airsim.CarClient()
        client.confirmConnection()
        client.enableApiControl(True, "Car1")

        # create default car controls
        car_controls_ego_car = airsim.CarControls()
        car_controls_target_car = airsim.CarControls()

        # Accelerate
        # ego
        #car_controls_ego_car.throttle = 1.0
        #car_controls_ego_car.steering = 0.0
        #client.setCarControls(car_controls_ego_car, "Car")
        # target
        print("Accelerate (Full Throttle)...")
        car_controls_target_car.throttle = 1.0
        car_controls_target_car.steering = 0.0
        client.setCarControls(car_controls_target_car, "Car1")
        time.sleep(5)


        # ego
        #car_controls_ego_car.throttle = 0.7
        #car_controls_ego_car.steering = 0.0
        #client.setCarControls(car_controls_ego_car, "Car")
        # target
        print("Accelerate (Throttle = 0.7)...")
        car_controls_target_car.throttle = 0.7
        car_controls_target_car.steering = 0.0
        client.setCarControls(car_controls_target_car, "Car1")
        time.sleep(5)

        # slow down
        print("Slow down...")
        # ego
        #car_controls_ego_car.throttle = 0.6
        #car_controls_ego_car.brake = 0.0
        #client.setCarControls(car_controls_ego_car, "Car")
        # target
        car_controls_target_car.throttle = 0.6
        car_controls_target_car.brake = 0.0
        client.setCarControls(car_controls_target_car, "Car1")
        time.sleep(10)

        # slow down
        print("Slow down...")
        # ego
        #car_controls_ego_car.throttle = 0.3
        #car_controls_ego_car.brake = 0.0
        #client.setCarControls(car_controls_ego_car, "Car")
        # target
        car_controls_target_car.throttle = 0.3
        car_controls_target_car.brake = 0.0
        client.setCarControls(car_controls_target_car, "Car1")
        time.sleep(2)

        # standstill
        print("Standstill...")
        # ego
        #car_controls_ego_car.throttle = 0.0
        #car_controls_ego_car.brake = 0.1
        #client.setCarControls(car_controls_ego_car, "Car")
        # target
        car_controls_target_car.throttle = 0.0
        car_controls_target_car.brake = 0.1
        client.setCarControls(car_controls_target_car, "Car1")
        time.sleep(4)

        # relase brakes and accelerate again
        print("Relase brakes and accelerate again...")
        # ego
        #car_controls_ego_car.throttle = 0.9
        #car_controls_ego_car.brake = 0.0
        #client.setCarControls(car_controls_ego_car, "Car")
        # target
        car_controls_target_car.throttle = 0.9
        car_controls_target_car.brake = 0.0
        client.setCarControls(car_controls_target_car, "Car1")
        time.sleep(15)

        # emergency braking
        print("Emergency braking...")
        # ego
        #car_controls_ego_car.throttle = 0.0
        #car_controls_ego_car.brake = 1.0
        #client.setCarControls(car_controls_ego_car, "Car")
        # target
        car_controls_target_car.throttle = 0.0
        car_controls_target_car.brake = 1.0
        client.setCarControls(car_controls_target_car, "Car1")
        time.sleep(7)


        client.enableApiControl(False, "Car1")

    if mode==1:
        client = airsim.CarClient()
        client.confirmConnection()
        client.enableApiControl(True, "Car1")
        client.enableApiControl(False, "Car1")

    restart = None
    while True:
        user_input = input("Press R to reset and restart AirSim. Press Q to quit this program. (R/Q)?")
        if user_input.upper() == "R":
            restart = 1
            break
        if user_input.upper() == "Q":
            restart = 0
            break

    if restart:
        client.reset()
        continue
    else:
        break