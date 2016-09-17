/*
 * main implementation: use this 'C' sample to create your own application
 *
 * 12 Sept 2016 - develop Freescale Car demo
 * Westwood Robotics
 * Mark S Walker
 * 
 * Based on TFC Example code from Eli Hughes
 * 
 */
#include "derivative.h" /* include peripheral declarations */
#include "TFC/TFC.h"    /* include TFC driver library */
#include "wwr.h"        /* wwr specific headers */
#include "pid.h"

#define MAXPGM 10

int main(void)
{
	
	uint16_t DEBUG = 1;
	uint16_t go = 0;    // controls main look
	uint16_t firstPass = 1; // controls initialization of main loop
	
	static double error = 0;
	static int prev_error = 0;
	static int old_prev_error = 0;
	int run_line = 1;
	double serv_dc;
	
	/*
	 * Set up parameters to start on button A push or DIP 4 on/off cycle
	 */
	volatile uint8_t activate = 0, dipVal = 0;
	
	uint32_t t=0;
	float linePos = 0.0;
	//uint32_t driveState = 0;  // set up different modes for driving
	double motorSpeed = 1.0;
	
	
	
	struct pDrive {
		double steerPot;
		double leftMotor;
		double rtMotor;
		uint16_t pDuration;
	} driveProgram[] = {
			{0.0, 1.0, 1.0, 1000},
			{0.40, .7, .7, 1000},
			{0.0, 1.0, 1.0, 800},
			{0.40, .5, .5,1000},
			{0.0, .8, .8, 1000},
			{0.40, .5, .5,1000},
			{0.0, .8, .8, 800},
			{0.0, 0.0, 0.0, 0}      // stop for a while
			}		
			;
	
	double revRt = 1.0;   // left motor is opposite signal from left
	double revLt = -1.0;  //
	double setSpeed = 0.0;
	uint16_t junk = 0;
		
	TFC_Init();  // Initialize TFC drivers
		
for(;;) {		
		/* wait for button 0 to be pressed before anything starts
			 * 
			 */
			while (activate < 2) 
			{
				if (TFC_PUSH_BUTTON_0_PRESSED)
					activate = 2;		// go on button a push
				
				for (junk=0;junk<20;junk++) {
					dipVal = TFC_GetDIP_Switch()&0x08;  // debounce switch
				}
				if (DEBUG) TERMINAL_PRINTF("dip=%d  ", dipVal);
				
				if (dipVal == 8) {		// first step - switch to on
					activate = 1;
					}
					else
					{	
					if ((dipVal == 0) && (activate ==  1) ) // after on/ if goes off, start
						activate = 2;
					}
			}
			
			activate = 0; // reset for next pass
			
			go = 1;
			firstPass = 1;
			uint16_t pNext = 0;  // timers for programmed driving in mode 2
			uint16_t iCmd = 0;         // command number to load
			uint8_t setAction = 0;  // flag to act or not
			double dSteer, dLM, dRM = 0.0;   // set up control parameters 
			setSpeed = motorSpeed * (TFC_ReadPot(1)+1.0/2);
		
	while(go) {	  
	   
	   	//TFC_Task must be called in your main loop.  This keeps certain processing happy (I.E. Serial port queue check)
	   				TFC_Task();

	   				//This Demo program will look at the middle 2 switch to select one of 4 demo modes.
	   				//Let's look at the middle 2 switches
	   				switch((TFC_GetDIP_Switch()>>1)&0x03)
	   				{
	   				default:
	   				case 0 :
	   					//Demo mode 0 just tests the switches and LED's
	   					if(TFC_PUSH_BUTTON_0_PRESSED)
	   						TFC_BAT_LED0_ON;
	   					else
	   						TFC_BAT_LED0_OFF;
	   					
	   					if(TFC_PUSH_BUTTON_1_PRESSED)
	   						TFC_BAT_LED3_ON;
	   					else
	   						TFC_BAT_LED3_OFF;
	   					
	   								
	   					if(TFC_GetDIP_Switch()&0x01)
	   						TFC_BAT_LED1_ON;
	   					else
	   						TFC_BAT_LED1_OFF;
	   					
	   					if(TFC_GetDIP_Switch()&0x08)
	   						TFC_BAT_LED2_ON;
	   					else
	   						TFC_BAT_LED2_OFF;
	   					
	   					break;
	   						
	   				case 1:
	   					
	   					//Demo mode 1 will just move the servos with the on-board potentiometers
	   					if(TFC_Ticker[0]>=20)
	   					{
	   						TFC_Ticker[0] = 0; //reset the Ticker
	   						//Every 20 mSeconds, update the Servos
	   						TFC_SetServo(0,TFC_ReadPot(0));
	   						TFC_SetServo(1,TFC_ReadPot(1));
	   					}
	   					//Let's put a pattern on the LEDs
	   					if(TFC_Ticker[1] >= 125)
	   					{
	   						TFC_Ticker[1] = 0;
	   						t++;
	   						if(t>4)
	   						{
	   							t=0;
	   						}			
	   						TFC_SetBatteryLED_Level(t);
	   					}
	   					
	   					TFC_SetMotorPWM(0,0); //Make sure motors are off
	   					TFC_HBRIDGE_DISABLE;
	   				

	   					break;
	   					
	   				case 2:
	   					// Programmed drive mode - follows set program
	   					// Sense - we aren't sensing
	   					
	   					// calculate
	   					// use TFC_Ticker[3]
	   					// see if next event should be loaded
	   					
	   					if (firstPass) TFC_HBRIDGE_ENABLE;
	   					
	   					//if (DEBUG) TERMINAL_PRINTF("MODE 2 %d %d %d \r\n", TFC_Ticker[3], pNext, setAction);
	   					
	   					if (TFC_Ticker[3] > pNext)
	   					{ // set parameter for driving
	   						dSteer = driveProgram[iCmd].steerPot+TFC_ReadPot(0);  // pot 0 is considered "centered" value
	   						dLM = driveProgram[iCmd].leftMotor*setSpeed*revLt;			// relative to set motor speed
	   						dRM = driveProgram[iCmd].rtMotor*setSpeed*revRt;
	   						pNext = driveProgram[iCmd].pDuration;
	   						// reset timer
	   						TFC_Ticker[3] = 0;
	   						iCmd++;			// increment command
	   						
	   						setAction = 1;
	   					} 
	   					
	   					if ((driveProgram[iCmd-1].pDuration == 0))
	   						{
	   						TFC_HBRIDGE_DISABLE;
	   						setAction = 0;
	   						go = 0;
	   						}
	   					
	   				
	   					// take action
	   					if (setAction)
	   					{
	   						TFC_SetServo(0,dSteer);
	   						TFC_SetMotorPWM(dLM,dRM);
	   						setAction = 0;              // action taken
	   					}
	   					
	   					break;
	   					
	   				case 4:
	   					/*
	   					 * Copied from internet see pid.c
	   					 */
	   					if(run_line)
	   								{
	   									// Get the Raw Camera Data
	   									//read_camera(cameradata);
	   									
	   									// Save the previous errors
	   									old_prev_error = prev_error;
	   									prev_error = error;
	   									
	   									// Get the current error of the cars location and clip it
	   									// to between 25 and -25
	   									error = processCamData( LineScanImage0 );
	   									if(error > 25)
	   									{
	   										error = 25;
	   										
	   									}
	   									else if(error < -25)
	   									{
	   										error = -25;
	   									}
	   									
	   									// Use PD Controller to get the new duty cycle for the servo
	   									// P  - Error
	   									// D  - error - 2*prev_error + old_prev_error
	   									// Kp - 0.40
	   									// Kd - 0.25
	   									serv_dc = (0.40*error) + (0.25*(error - 2*prev_error + old_prev_error)) + 75;
	   									TFC_SetServo(0,serv_dc);
	   									
	   									// Reset run main flag
	   									run_line = 1;
	   								}
	   					
	   					break;
	   					
	   				case 3:
	   					
	   					// sense data
	   					
	   					if(TFC_Ticker[0]>100 && LineScanImageReady==1)
	   					{
	   						TFC_Ticker[0] = 0;			// process every 100 ms if line image ready
	   						LineScanImageReady=0;
	   						
	   						// find line center every 100 ms if ready
	   						linePos = locate_line();
	   					
	   					if (DEBUG) TERMINAL_PRINTF("c: %4.2f \n\r",linePos);
	   					}
	   					
	   					break;
	   					
	   				}
	}  // end while go loop
} // end for
	return 0;
}
