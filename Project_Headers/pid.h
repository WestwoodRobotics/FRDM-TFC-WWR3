/************************************************************
File: pid.h

Description: Header File for the pid module

Authors: Dakota Bassett and Amar Bhatt

Created: 11/20/2015

Last Edited: 12/9/2015

Modified: msw 9/17/16 for test
************************************************************/


#ifndef PID_H_
#define PID_H_


/************************************************************
 Library and Header File Includes
************************************************************/
#include "derivative.h"
#include "TFC/TFC.h"



/************************************************************
 Global Scope Function prototypes
************************************************************/
int processCamData(uint16_t*);
int errorCalc(void);

#endif /* PID_H_ */

/* End of File */
