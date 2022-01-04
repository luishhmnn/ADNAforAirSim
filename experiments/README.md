# Experiments
This directory contains batch and config files to run simulations. There is one folder for each experiment.

To run an experiment one time:  
1. Choose a batch file and double-click it. AirSim.exe, ADNAforAirSim.exe and some instances of GeneralPurposeProcessor.exe will start up.
2. Wait until all programs are running.
3. In the ADNAforAirSim.exe menu, choose _Control_ > _Connect to AirSim_ to establish a connection.
4. In the ADNAforAirSim.exe menu, choose _Control_ > _Wake AHS_ to start the simulation.



Notes:
- Before you can run a simulation you must install AirSim to `ADNAforAirSim\AirSimServer\CityEnviron`. If you have not installed it yet, go to this directory. There you will find installation instructions.
- Unfortunately, AirSim's settings.json does not allow relative paths. Please change the path in settings.json to fit your system.
- To run multiple simulations automated you can use the Python scripts.
