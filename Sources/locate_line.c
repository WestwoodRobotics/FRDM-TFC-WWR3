/*
 * locate_line.c
 *
 *  Created on: Sep 13, 2016
 *      Author: mswalker
 *      
 *      Determine center of line based on linescan camera input
 */
#include "TFC/TFC.h"
#include "math.h"

float locate_line() {
	
	int i = 0;
	float lineCtr = 0.0;
	int minPoint, maxN, maxP, DP, DN = -1;
	int valueChange, minValue, maxNChange, maxPChange = 0;
	int pixel[128];
	
	float sigChange = 500.0;   // threshold for seeing a line edge (probably 500 - 100 works)
	
	
						 
						 minValue = 5000.0;			// start at max intensity
						 
						 for(i=10;i<120;i++)  // ignore < 10 and > 120 
						 	 {
							 	 	 	 pixel[i] = (int)LineScanImage0[i];  // capture value
										 if (i > 2) {
											 valueChange = pixel[i] - pixel[i - 2];
										 } else {
											 // for edge, use 0 position pixel;
											 valueChange = pixel[i] - pixel[0];
										 }
										 
										 // look for significant change in value
										 if ((valueChange > 0 && valueChange > sigChange) || (valueChange < 0 && valueChange < -1*sigChange))
											{/*
											 
											 if (valueChange >= 0.0) {
												 DP = i;   // positive change
												 if (valueChange > maxPChange) {
													 maxPChange = valueChange;
													 maxP = i;
												 } 
												 else 
												 	 {
													 DN = i;
													 if (valueChange < maxNChange) {
														 maxNChange = valueChange;
														 maxN = i;
													 }
												 }
													 
											 }
											
										 */} // end if valueChange
										 
										 if (pixel[i] < minValue) {
											 minValue = pixel[i];
											 minPoint = i;
											// TERMINAL_PRINTF("minValue %d pixel %d i %d \r\n",minValue,pixel[i], i);
										 }
										 
								 }
		
	/*if ((maxP > 0) && (maxN > maxP))
		lineCtr = ((float)maxP + (float)maxN)/2.0;  // center of max positive and negative slope change
		else
		if (maxP > 0 && maxN < maxP)
			lineCtr = ((float)maxP + 127.0)/2.0; // at right edge
		else
			lineCtr = ((float)maxN/2.0);  // at left edge*/
	lineCtr = minPoint;
		
	//TERMINAL_PRINTF("lines %d  %d  %d %4.2f \r\n", minPoint, maxP, maxN, lineCtr);
	return lineCtr;
}


