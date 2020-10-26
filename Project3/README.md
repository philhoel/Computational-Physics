# Project 3 - Solar System Model

## Written by Philip Hoel, Theo G. Halvorsen and Elakkyen Pathmanathan

Code:

    C++ for main
    Python for additional functions and plotting

Structs:

    CelestBody - Creates a Celestial Body

Classes:
    SolarSystem - Main class where all methods lie

Running program:

    To run program, use run_script.py
    
    Python3 run_script.py -default -plot -method

    -default:
        "yes" or "no"
        Wether to run default program or not
        if no, program will run a new function asking for other values to put in

    -plot:
        "2d" or "3d"

    -method:
        "euler" or "verlet"

    If default is no, program will ask for:

        -n:
            integration points

        -T:
            Time period (in years)

        -mass:
            mass of Jupiter
        
        -beta:
            Value of beta

        -assignment:
            "a", "b" or "c"
            Some default settings are set up in main.cpp
            a will run Earth-Sun
            b will run Earth-Jupiter-Sun
            c will run all planets
        
