/*! \addtogroup IRcamera
* This module provides the required function to communicate with the IR Camera and takes the required images.
*
* The IR Camera should be initialized by the following function:
*
* - TurnOn()
*
* After turning the camera on, a defined test procedure, RunTest(), should be executed to verify the functionalities of the concerning hardware and software.
* Then, the executive level will call the required function. 
* 
* At the end, the following function should be called to turn off the camera.
*
* - TurnOff()
*
* The module has a shrared memory to keep the captured image and share it with any other module.
*  @{
*/


/** Camera IR Test Report

* It includes OK or NOT_OK and a report on the tested software and hardware.

* To be defined (CAMERA_IR_TEST): 
* -	The final report structure should be discussed. 
* -	The acceptance conditions
* -	CAMERA_IR_TEST
*/

typedef struct 
{
	STATUS status ; /**< OK or NOT_OK  */ 
	REPORT message1; /**< Should be defined */
	REPORT message2; /**< Should be defined */
	REPORT message3; /**< Should be defined */
} CAMERA_IR_TEST;



/** It turns the camera on.
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS TurnOn();

/** It turns the camera off.
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS TurnOff();

/** It calls a list of tests to verify the concerning hardware and software and return a CAMERA_IR_TEST_REPORT.

Note: A test log should be stored for any further verification.

* @return  IR Camera test report includes OK or NOT_OK and a report on all tested functions. 
*/
CAMERA_IR_TEST RunTest();

/** It sets the exposure.
* @param time : Exposure time in ms
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS SetExposure(int time);

/** It sets the number of images that should be captured.
* @param number : number of images
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS SetAverage(int number);


/** It Sets IR filter to the defined filter ID.

* @param filter_id : It can be an integer between 0 and 7
* @return  Code of the first error encountered, otherwise OK 
*/
 STATUS SetFilter(Int filter_id);

/** It captures an image. Image will become accessible in a shared memory. 
* @return  Code of the first error encountered, otherwise OK 
*/
STATUS Capture();

/** It saves the captured image available in the shared memory.
* @return  Code of the first error encountered, otherwise OK 
*/
string Save();

/** It captures an image.
* @return  A reference to the saved image 
*/
string CaptureSave();

/** It returns a referenced image. Image will become accessible in a shared memory. 
* @param ref : A reference to the name of the saved image
* @return  status  
*/
STATUS GetImage(string ref);

/** It returns the saved images' references.
* @return  Reference list 
*/
string GetRefList();

/** It deletes an image by using its reference. 
* @param ref : A reference to the name of the saved image
* @return  status  
*/
STATUS DeleteImage(string ref);

/** It erases all the images and the clear the ref list.
* @return  Code of the first error encountered, otherwise OK 
*/
 STATUS DeleteAll();
/*! @} */
