/*! \mainpage MAIN PAGE

* \section sec1 Introduction
* 
* This document presents the preliminary approach to answer to all requirements which are reflected in the Software Requirement Document. On the one hand, this document presents the overall architecture of the software platform and on the other hand, it presents the required module. Each Module in this document should address one or several requirements of the Software Requirement Document.
* The required functions and data structure for each module have not been finalized yet. It is required that this document be reviewed by the developers in order to finalize this document.
* 
* \section sec2 Software Development
* A modular software framework is proposed to facilitate the software interaction on the system system. The advantages of this approach are providing free access of all users to all sensors, algorithms and shared data in the framework. Moreover, this approach can be extended easily without modifying the previously developed software.
* This framework consists of three layers of development to separate computational, executive and decision levels. Following figure illustrates different layers of this framework:
*
*  \image html "images/software50.jpg" "Software Development Architecture Diagram" width=8cm
*
* \subsection sub4 Physical Level
* This level includes all the sensors and actuators. It communicates with the functional level to send data or receive commands.
*
* \subsection subsec1 Functional Level
* All the main processing algorithms will be developed at this level in a modular fashion. Each module provides us with a number of functions (Requests) to communicate with the module.  Each module can receive some predefined Requests and can return a Report at the end of processing the Request. Each Request contains a Command and an array of arguments as the input to the associated algorithm. Each Report contains a success flag (OK or Not_OK) and an array of return arguments. 
*
* The required modules are presented in the Module Page.
*
* \subsection subsec2 Executive Control Level
* This level contains several scripts to call the Requests of the Functional Level Modules.  The robot is supposed to be controlled based on the state machine approach. This level consists of the required scripts to transit between states or keeps the robot in a specific state.
* The executive level has access to all the presented functions and calls to execute any task. 
*
* The Executive level is currently under development.
*
* \subsection subsec3 Decision Level
* Decision level translates the high level requests of users or a mission planner to a command to call one or several scripts of Executive Level. Based on the user request, a piece of script will be selected at this level and will be run to call the Requests of the Functional Level.  
* 
* The Decision level is currently under development.
*
*
* \section sec3 Housekeeping
* From the House Keeping Machine point of view, the robot (The functional level and the physical level) has three Modes as follow:
*
* - Off Mode
* - Active Mode
* - Sleep Mode
* 
* These Modes and transition between them can be controlled by House Keeping Machine.
* Housekeeping computer communicates with the central computer in order to:

* -	Change the system mode (OFF MODE, ACTIVE MODE, and SLEEP MODE)
* -	Temperature Report
* -	Power report
* -	(To be defined)





*/
