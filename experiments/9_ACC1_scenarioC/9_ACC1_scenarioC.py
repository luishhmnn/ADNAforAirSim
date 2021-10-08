"""
@author: Luis Hohmann

This script runs scenario A of LCA1 100 times.

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


# 1. Settings --------------------------------------------------------------------------------
simulations = 100                                      # Number of simulations
duration = 14                                          # Duration of simulation in sec
number_of_processors = 3                               # Number of GeneralPurposeProcessors
log_level = 4                                          # Log level of GeneralPurposeProcessors

# Paths & file names
dir_path = pathlib.Path(__file__).parent.resolve()     # Directory path of this script
cwd = os.getcwd()                                      # current working directory (pwd)

dna_file_name = '0_environment_testing'                # Name of the DNA file (without .dna!)
dna_path = os.path.join(dir_path, dna_file_name)       # Path of the DNA file

airsim_settings_file_name = '0_environment_testing.json'  # Name of the AirSim settings .json
airsim_settings_path = os.path.join(dir_path,
                        airsim_settings_file_name)     # Path of the AirSim settings .json

pyautogui.FAILSAFE = False # deactivate fail-save because it stops execution if mouse moves

# 2. Check working directory -----------------------------------------------------------------
if str(dir_path) != cwd:
  print(f'Please change your working directory to `{dir_path}` before you run this script!')
  exit()


for j in range(simulations):
    print(f'Running simulation {j+1} of {simulations}...')

    # 3. Starting the executables ----------------------------------------------------------------
    # Run AirSim (CityEnviron.exe)
    run_command_airsim = f"""start "AirSim CityEnviron" "{dir_path}\\..\\..\\AirSimServer\\CityEnviron\\WindowsNoEditor\\CityEnviron.exe" --settings "{airsim_settings_path}" """
    os.system(run_command_airsim)
    time.sleep(10)

    # Run GeneralPurposeProcessor.exe
    for i in range(1, number_of_processors+1):
        run_command_gpp = f"""start "GPP {i}" "{dir_path}\\0_GeneralPurposeProcessor.exe" /DNA:{dna_path} /L:{log_level} {i} """
        os.system(run_command_gpp)
    time.sleep(5)

    # Run ADNAAirSimClient.exe
    run_command_client = f"""start "ADNAforAirSim" "{dir_path}\\..\\..\\Client\\build\\x64\\Debug\\ADNAAirSimClient.exe" """
    os.system(run_command_client)
    time.sleep(5)

    # 4. Establish connection and start the simulation -------------------------------------------
    # open `Control` menu and select `Connect to AirSim`
    pyautogui.hotkey('alt', 'C')
    pyautogui.press('C')
    time.sleep(5)
    # open `Control` menu and select `Wake System`
    pyautogui.hotkey('alt', 'C')
    pyautogui.press('W')

    # 5. Wait while simulation runs ---------------------------------------------------------------
    time.sleep(duration)

    # 6. Stop the simulation ----------------------------------------------------------------------
    # Send AHS to sleep
    pyautogui.hotkey('alt', 'C')
    pyautogui.press('S')
    time.sleep(1)

    # Kill all running programs
    os.system("taskkill /im ADNAAirSimClient.exe")
    os.system("taskkill /im 0_GeneralPurposeProcessor.exe")
    os.system("taskkill /im CityEnviron.exe")

    # 7. Copy AHS logs ----------------------------------------------------------------------------
    # Create directory name for AHS log files
    current_timestamp = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime())
    ahs_log_dir_path = f'AHSlog-{current_timestamp}'
    # Get names of all general purpose processor log files
    ahs_log_file_names = glob.glob("AHSLogNet0Processor*.txt")
    # Create a new directory
    os.makedirs(ahs_log_dir_path)

    # Copy the files into  the new directory
    for file_name in ahs_log_file_names:
        src = os.path.join(dir_path, file_name)
        dest = os.path.join(dir_path, ahs_log_dir_path, file_name)
        os.rename(src, dest)

print(f'Done!')