//****************************************************************************  
// MIT Media Lab - Biomechatronics  
// Jean-Francois (Jeff) Duval  
// jfduval -at- media.mit.edu  
// 02/2016  
//****************************************************************************  
// FlexSEA: Flexible & Scalable Electronics Architecture  
//****************************************************************************  
  
As of 02/10/2016, the best sources of documentation are:  

- my master's thesis http://jfduval.ca/flexsea/JFDuval_Thesis_FlexSEA_Final.pdf  
- my entry for the Hackaday Prize 2015 https://hackaday.io/project/5765-flexsea-wearable-robotics-toolkit  

Two papers describing the system have been submitted to an IEEE Conference. Links will be added when available.  

- "FlexSEA: Flexible, Scalable Electronics Architecture for Wearable Robotic Applications"  
- "FlexSEA-Execute: Advanced Motion Controller for Wearable Robotic Applications"  
  
**Do not hesitate to contact me if you want to know more about the project.**  

'flexsea-comm': generic communication stack, can be used by any project.
All it "knows" is that if you receive command code 22, you can a function named flexsea_payload_22

2'flexsea-system': wraps around the communication stack, and provides project-specific names,
functions, etc. It has nicknames for function like flexsea_payload_22; it's re-defined as rx_cmd_data_read_all
(Receive Command from the Data functions to Read All variables)

'plan-gui': Qt GUI code (the old version with horrible code (but it works!), new stuff isn't public yet)

// Hardware Naming Convention:  
// ================================  
- Plan: Embedded Computer  
    - Complex algorithms, data-logging, user interfaces, ...  
    - Hard/soft: BeagleBone Black running Linux. C, Python, Matlab.  
- Manage: Data acquisition and mid-level computing  
    - Connected to Plan. Gathers sensor data, connect to slaves  
    - Hard/soft: STM32F4 Cortex-M4. C.  
- Execute: Advanced Motion Controller  
    - Everything linked to motion control.  
    - Hard/soft: Programmable System on Chip (PSoC). C, HDL, graphical.  
  
// Directories (alphabetical order):  
// ================================  
- batt: "FlexSEA-Battery" project, power analysis and datalogging.  
    - Intern project, never fully completed. Use with care.  
- common: Communication stack for all the boards.  
- execute-cop: code for the PSoC 4 co-processor found on FlexSEA-Execute  
- execute-gui-1: Qt C++ GUI to be used with FlexSEA-Execute  
- execute: PSoC 5LP code for FlexSEA-Execute (motor driver)  
- manage: STM32F4 Eclipse project for FlexSEA-Manage  
- misc: BeagleBone Black config files, some python scripts, ...  
- plan: Eclipse C project to control a FLexSEA network. Can be compiled for the	BeagleBone Black or for a native Linux machine. Note that FlexSEA-GUI is based on this project.  
