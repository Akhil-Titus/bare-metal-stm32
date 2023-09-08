# STM32CubeF1 Setup Instructions

This guide will walk you through setting up the STM32CubeF1 project and configuring your development environment.

## Clone the Repository

Clone the STM32CubeF1 repository from GitHub and make sure to include submodules recursively:

```bash
git clone --recursive https://github.com/STMicroelectronics/STM32CubeF1.git
```
Removing Unnecessary Files
Navigate to the /STM32CubeF1/Drivers/ directory and delete all files except for the CMSIS directory.

Within the CMSIS directory, delete all files and folders except for the `/Device` and `/Include` directories. (Refer `/chip_headers`) 

## Setting Up Include Paths

- In Cube IDE, right-click on your project directory and go to `Properties`.

- Navigate to `Paths and Symbols`.

- Under `Includes`, click `Add` and then select `File system`.

- Navigate to the following paths:
```bash
/CMSIS/Device/ST/STM32F1xx/Include
/CMSIS/Include
```
Configuring main.c
In your main.c file, make sure to define the appropriate STM32 microcontroller model and include the necessary header file for your development board. `Replace STM32F103x6` with your chosen microcontroller model and update the #include statement accordingly.

For example:

```c
#define STM32F103x6 // Chosen microcontroller model
#include "stm32f1xx.h"
```
These steps should help you set up the STM32CubeF1 project and configure your development environment.