#include "Header.h"

/*******************************************************************************
 * Programmer: Zvikomborero Masike                                             *
 * Class: CptS 122; Lab Section 4                                              *
 * Programming Assignment: 1                                                   *
 * Date: 1/29/2022                                                             *
 *                                                                             *
 * Description: This program read, clean, and prints out FitbitData            *
 *                                                                             *
 *                                                                             *
 * Relevant Formulas: Refer to each function definition.                       *
 *                                                                             *
 * Format of record in input file (FitbitData.csv):                            *
 *										       "12ab3" (ID char)               *
 *                                             "23:24:00" (minute char)        *
 *									           0.982492 (calories double)      *
 *									           0.312244 (distance double)      *
 *                                             4 (floors int)                  *
 *                                             63 (heartRate int)              *
 *                                             40 (steps int)                  *
 *                                             0-4 (sleepLevel int)            *
 * Format of output file (Result.cvs): See problem specification.              *
 ******************************************************************************/

int main(void)
{
	FILE* infile = fopen("FitbitData.csv", "r");

	FILE* outfile = fopen("Result.csv", "w");

	FitbitData fbdarray[1440] = { {"","",0.0,0.0,0,0,0} };

	char targetid[9] = "";

	int size = 1440;
	
	if (infile != NULL)
	{
		//succeeds at reading the file

		find_target(infile, targetid);

		delete_line(infile, fbdarray, size, targetid);

		print_Result(outfile, fbdarray, size);

		fclose(infile);
		fclose(outfile);
	}
	
		/*	Testing Function
	sleep_Calculation(fbdarray, &endRangeSleep, &startRangeSleep, size);
	
	steps_Calculation(fbdarray, &maxStepIndex, size, 0);
	
	total_calories(fbdarray, size-1, 0);

	total_distance(fbdarray, size-1, 0);

	total_heartRate(fbdarray, size-1, 0);
	
	total_floors(fbdarray, size-1, 0);
	*/

	return 0;
}

