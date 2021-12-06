import os
import time
import glob
import pathlib
import subprocess

import pyautogui 


# 1. Settings --------------------------------------------------------------------------------
simulations = 100                                      # Number of simulations
duration = 28                                          # Duration of simulation in sec
number_of_processors = 3                               # Number of GeneralPurposeProcessors
number_of_backup_processors = 3                        # GeneralPurposeProcessors for backup
log_level = 4                                          # Log level of GeneralPurposeProcessors

timed_shutdown = 13000                                 # Timed shutdown [ms]

# Paths & file names
dir_path = pathlib.Path(__file__).parent.resolve()     # Directory path of this script
cwd = os.getcwd()                                      # current working directory (pwd)

dna_file_name = '15_LCA3_scenarioA_fail'                     # Name of the DNA file (without .dna!)
dna_path = os.path.join(dir_path, dna_file_name)       # Path of the DNA file

airsim_settings_file_name = '15_LCA3_scenarioA_fail.json'    # Name of the AirSim settings .json
airsim_settings_path = os.path.join(dir_path,
                        airsim_settings_file_name)     # Path of the AirSim settings .json

pyautogui.FAILSAFE = False # deactivate fail-save because it stops execution if mouse moves


print("start")
i = 1
process = subprocess.Popen(f"15_GeneralPurposeProcessor.exe /DNA:{dna_path} /L:{log_level} /K:{timed_shutdown} {i} ")

print(process.pid)