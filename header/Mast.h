/*! \addtogroup Mast
* \section sec0 How to use the module
*
* This module provides the required command to operate the Robotic Mast from executive level. The mast module has 4 Mode and In the start up, it will be initialized (or turned on) in STOWAGE mode

* -	\b Active: Mast is unlocked and users can command the mast to change its configuration.
* Mast will go to home configuration as soon as entering in this Mode. Home configuration will be defined in the initialization.
* -	\b Navigation: Mast is locked. As soon as going to locked position, the required action should be done to use the minimum energy.
* User does not have access to the operational functions to change the configuration of the mast in this mode.
* -	\b Stowage: Mast is locked. As soon as going to locked position, the required action should be done to use the minimum energy. 
* User does not have access to the operational functions to change the configuration of the mast in this mode.
* - \b Scan: Mast is unlocked and users can command the first and the second degree of freedom of the mast.
* Users have access to the first and the second degree of freedom. This mode is dedicated to be used in Teleoperation for scanning the ground for capturing UV/Visable image. 
* By calling this mode, the first and the second degree of freedom will become equal to the concerning home_pos value's. The second link of teh robotic arm will go automatically 
* to a configuration paralel to the first link. It provide a condition that the UV/Bumblebee camera can scan the ground easily.

* The following figures present the robot in each mode.

*  \image html "images/mast_stowage.jpg" "Mast Stowage Mode" width=5cm
*  \image html "images/mast_navigation.jpg" "Mast Navigation Mode" width=5cm
*  \image html "images/mast_active.jpg" "Mast Active Mode" width=5cm

*
* \subsection subsec1 Initialization 
*
* The Robotic Mast should be initialized before operation. All the following functions should be called to initialize the Mast module
* - Mast_SetBinPos(int binID, double x, double y, double z)
* - Mast_SetJointPara(int JointID, JOINT_PARA para)
* - Mast_SetMastRootPosition(double x, double y, double z, double roll, double pitch, double yaw)

* Then, by calling Mast_SelfTest(), a set of tests will be executed to verify the functionality of the hardware and the software.


For changing the mast mode, the following functions can be called:
    
* - Mast_SetMode( enum MAST_MODE mode)



* The users do not have access to the functions that change the configuration of the Mast except in \b Active and \b Scan mode. So, for any operation that required moving the Mast
* manually, users should call Mast_SetMode( enum MAST_MODE mode) and use SCAN or ACTIVE as input.
*
* \subsection subsec2 TeleOperation Functions
*
* Users can use the following functions in the module to operate the mast manually as follow:
*
* by calling Mast_SetMode( enum MAST_MODE mode) and going to ACTIVE mode, then: 
* - Mast_SetJointValues(MAST_CONFIG conf)
* - Mast_SetJointValue(int jointID, double value)
* - Mast_SetEndEffectorPos(END_EFFECTOR_POS pos)
* - Mast_Scoop()
* - Mast_Drop()
* - Mast_HaltAllJoints()
* - Mast_HaltJoint(int jointID)
* - Mast_HomeJoint(int jointID)
* - Mast_HomeAllJoints()
* - Mast_SampleRetrieve(double x, double y, double z)
* - ...(other functions in the list)
*
* or by calling Mast_SetMode( enum MAST_MODE mode) and going to SCAN mode, then: 
*   - Mast_TurnRight(double angle)
*   - Mast_TurnLeft(double angle)
*   - Mast_TurnDown(double angle)
*   - Mast_TurnUp(double angle)
     


* \subsection subsec3 Autonomous Functions
*
* Users (executive level) can use the following functions to command a task. The tasks are as follows:
*
* - \b Sample \b Retrieving:  Retrieving a sample by scooping an input location. There is a verification procedure in the loop to verify if there is sample in the scoop or no.
* - \b Scooping: Scooping an input location without any verification.
* - \b Sample \b Dumping: Dumping the retrieved sample in the sample bin.
*
* The following functions can be used to command the tasks:
* - Mast_SampleRetrieve(double x, double y, double z)
* - Mast_SampleDump(int binID)
*
        
* \subsection subsec4 Query Functions
*
* The query functions are used to get the required information from the module. The executive level will used these functions to communicate data to the base.

* - Mast_GetJointValues(MAST_CONFIG *pconf)
* - Mast_GetJointValue(int jointID, double *pvalue)
* - Mast_GetJointPara(int JointID, JOINT_PARA *ppara)
* - Mast_GetHomeConfig(MAST_CONFIG *pconf)
* - Mast_GetEndEffectorPos(END_EFFECTOR_POS *ppos)
* - Mast_GetMode(enum MAST_MODE *pmode)



*  @{
*/


/** MAST_MODE

* It defined the mode of the Mast
*/

enum MAST_MODE{
	ACTIVE, /**< Active mode */
	STOWAGE, /**< Stowage mode */
	SCAN, /**< Scan mode */
	NAVIGATION /**< Navigation mode */
	
}; 



/** Robotic Mast configuration

/* It includes the value of the Robotic Mast DOF.
*/

typedef struct
{
	double x ; /**< Coordination along x axis  */ 
	double y ; /**< Coordination along y axis  */ 
	double z ; /**< Coordination along z axis  */ 
	double theta ; /**< attack angle */ 
} END_EFFECTOR_POS;



/** Robotic Mast Test Report

* It includes OK or NOT_OK and a report on the tested software and hardware.

* To be defined (MAST_TEST): 
* -	The final report structure should be discussed. 
* -	The acceptance conditions
* -	MAST_TEST
*/

typedef struct 
{
 double pos_home ; // Home position of the joint, in radius
 double pos_max ; // Maximum position of the joint, in radius
 double pos_min ; // Minimum position of the joint, in radius
 double vel_max ; // Maximum velocity of the joint, in radius/second
 double acc_max ; // Maximum acceleration of the joint, in radius/second2
 double curr_max ; // Maximum current of the joint, in ampere
} JOINT_PARA;


// Operation Functions

/** It bring the Mast to one of the desired mode and return a proper status message. 
*  @param  mode : MAST_MODE which can be one of teh follwoing options:
*           
* \b ACTIVE: It brings the robotic arm to the home configuration. In this mode, users can move the arm by using the provided functions.   
*
* \b SCAN: It brings the first and the second degree of freedom of the mast the home configuration.
* In this mode, users can move the arm by commanding the first and the second joint value. The second link of the arm will be always parallel to first link. 
* It helps users to scan the ground by UV and bumblebee camera.
*
* \b NAVIGATION: Move the mast to the navigation Mode, so as to firm a solid tripod; return 0 when finished successfully or error code when fails
* Mast will be in the locked configuration in navigation Mode. users (executive level) does not have access to any function to move the mast.
*
* \b STOWAGE: Move the mast to stowage configuration, with the lowest center of gravity. 
* Mast will be in the locked configuration in stowage state. users (executive level) does not have access to any function to move the mast.
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SetMode( enum MAST_MODE mode); 

/** It returns the operation mode of the mast.

* @param   pmode : mast mode
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_GetMode(enum MAST_MODE *pmode);


/** It calls a list of tests to verify the concerning hardware and software.

Note: A test log should be stored for any further verification.
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SelfTest();

/** It request report from the mast control computer.

* @param  report : report
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_GetReport(char report[]);

/** It moves the specific joint to its home position.

* @param  jointID : Joint ID
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_HomeJoint(int jointID);

/** It moves all joints to its home position.

*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_HomeAllJoints();

/** It halt the specific joint, It is used in emergency situation or due to errors.

* @param  jointID : Joint ID
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_HaltJoint(int jointID);


/** It halt all joints, It is used in emergency situation

*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_HaltAllJoints();

/** It reset the specific joint.

* @param  jointID : Joint ID
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_ResetJoint(int jointID);


/** It reset all joints.

*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_ResetAllJoints();


/** It associate a releasing position to each sample bin ID. 

Note: The position is defined in the robot coordination.
Note: Calling this function is mandatory. Calling any other function should return error before initialization of at least one sample bin position.

*  @param  binID : An ID which defines each sample bin.
*  @param  x : scooping coordination
*  @param  y : scooping coordination
*  @param  z : scooping coordination
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SetBinPos(int binID, double x, double y, double z);

/** It sets the joint parameters

* @param JointID : Joint ID.
* @param para : Joint parameter.

* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SetJointPara(int JointID, JOINT_PARA para);

/** It get the joint parameters

* @param JointID : Joint ID.
* @param *ppara : Joint parameter.

* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_GetJointPara(int JointID, JOINT_PARA *ppara);

/** It sets a joint value.

* @param jointID : Joint ID
* @param value : Joint  value.

* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SetJointValue(int jointID, double value);

/** It return the joint value.

* @param jointID : Joint ID
* @param *pvalue : Joint  value.

* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_GetJointValue(int jointID, double *pvalue);

/** It returns the joint values (Mast configuration).

* @param conf : mast configuration
* @return   Mast current configuration.
*/
STATUS Mast_SetJointValues(MAST_CONFIG conf);

/** It returns the joint values (Mast configuration).

* @param * pconf : mast configuration
* @return   Mast current configuration.
*/
STATUS Mast_GetJointValues(MAST_CONFIG *pconf);

/** It sets the end effector position in the coordination of the robot and the attack angle of the scoop.

Question: Where is the end effector? Is it the last joint before scoop or it is a center of the scoop?
Question: What is the attack angle? is it the value of the last joint?

*  @param  pos : scoop coordination
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SetEndEffectorPos(END_EFFECTOR_POS pos);

/** It returns the end effector position in the coordination of the robot and the attack angle of the scoop.

*  @param  *ppos : scoop coordination
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_GetEndEffectorPos(END_EFFECTOR_POS *ppos);


/** Retrieve the sample situated at position x,y and z. The location is defined in the robot local coordination.

*  @param  x : scooping coordination
*  @param  y : scooping coordination
*  @param  z : scooping coordination
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SampleRetrieve(double x, double y, double z);

/** Verify if the sample retrieval effort is successful or not.

*  @param  *img1 : first image
*  @param  *img2 : second image
*  @param  *success : success flag
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SampleVerify(string *img1, string *img2, bool *success);


/** It dump the samples in the selected bin.

Note: At the end of each function, the mast comes back to the home position. 

*  @param  binID : Bin ID
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SampleDump(int binID);

/** Inqure about the coordination of sample

*  @param  *x : scooping coordination
*  @param  *y : scooping coordination
*  @param  *z : scooping coordination
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_GetSampleCoor(double *x, double *y, double *z);

/** Forward the coordination of the sample to the mast computer

*  @param  *x : scooping coordination
*  @param  *y : scooping coordination
*  @param  *z : scooping coordination
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_ForwardSampleCoor(double *x, double *y, double *z);









//  These functions are not in the list of high level functions from Ryerson.

/** This function is used in initialization of the module to set the position and orientation of the Mast root cordination in the robot cordination. 
Note: Mast root cordination is the coordination that the mast developer considers for his comupation. (Mast coordination in the coordination of the robot)
Note: Calling this function is mandatory in initialization. Calling any other function should return error before setting the root position.

*  @param  x : Coordination along x axis
*  @param  y : Coordination along x axis
*  @param  z : Coordination along x axis
*  @param  roll : Rotation around x axis
*  @param  pitch : Rotation around x axis
*  @param  yaw : Rotation around x axis
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_SetMastRootPosition(double x, double y, double z, double roll, double pitch, double yaw);


//Queries

/** It returns the Home configuration of the mast..
* @param * pconf : mast configuration
*  @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_GetHomeConfig(MAST_CONFIG *pconf);


/** It scoops. 

* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_Scoop();

/** It release the scooped samples. 

* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Mast_Drop();


/** It truns the Arm right by using the first motor.
* @param   angle : Angle in Degree
* @return   STATUS : Error code or OK.
* Note: Mast should be in Scan Mode..
*/
STATUS Mast_TurnRight(double angle);

/** It truns the Arm left by using the first motor.
* @param   angle : Angle in Degree
* @return   STATUS : Error code or OK.
* Note: Mast should be in Scan Mode..
*/
STATUS Mast_TurnLeft(double angle);

/** It moves the Arm down by using the second motor.
* @param   angle : Angle in Degree
* @return   STATUS : Error code or OK.
*/
STATUS Mast_TurnDown(double angle);

/** It moves the Arm up by using teh second motor.
* @param   angle : Angle in Degree
* @return   STATUS : Error code or OK.
*/
STATUS Mast_TurnUp(double angle);

/*! @} */
