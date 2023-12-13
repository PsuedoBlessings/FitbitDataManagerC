#include "Header.h"

/*************************************************************
 * Function: find_target ()                                  *
 * Date Created:1/23/2022                                    *
 * Date Last Modified: 1/24/2022                             *
 * Description: This finds the target/patient id             *
 * Input parameters: FILE* f, char* targetid                 *
 * Returns:                                                  *
 * Preconditions: an empty character array to allocate the   *
 * target id and an input file                               *
 * Postconditions: targetid will be assaigned a string       *
 *************************************************************/

void find_target(FILE* f, char* targetid)
{
	char line[100] = "";
	fgets(line, 100, f);
	strcpy(targetid, strtok(line, ","));
	strcpy(targetid, strtok(NULL, ","));
	fgets(line, 100, f);
}

/*************************************************************
 * Function: get_line ()                                     *
 * Date Created: 1/25/2022                                   *
 * Date Last Modified: 1/25/2022                             *
 * Description: Gets the line from the input file and assigns*
 * them to a slot within the FitbitData. It also checks if   *
 * any values within the file that is empty and puts a       *
 * invalid data to the array                                 *
 * Input parameters: FILE* f, FitbitData* data,              *
 * char* targetid, int size                                  *
 * Returns:                                                  *
 * Preconditions: requires an input file and an array and a  *
 * target id                                                 *
 * Postconditions: A line from the file that's cleans        *
 *************************************************************/

void get_line(FILE* f, FitbitData* data, char* targetid, int size)
{
	int counter = 0;

	char line[100] = "";

	fgets(line, 100, f);
	
	for (int index = 0; line[index] != '\0'; index++)
	{
		if (line[index] == ',')
		{
			counter++;
		}
		if (line[index] == ',' && line[index + 1] == ',')
		{
			if (counter == 2)
			{
				data[size].calories = -1;
			}
			else if (counter == 3)
			{
				data[size].distance = -1;
			}
			else if (counter == 4)
			{
				data[size].floors = -1;
			}
			else if (counter == 5)
			{
				data[size].heartRate = -1;
			}
			else if (counter == 6)
			{
				data[size].steps = -1;
			}
			break;
		}
	}
	
	strcpy(data[size].patient, strtok(line, ","));

	if (strcmp(targetid, data[size].patient) != 0)
	{
		strcpy(data[size].patient, "-1");
		return;
	}
	
		strcpy(data[size].minute, strtok(NULL, ","));

		if (strcmp(data[size - 1].minute, data[size].minute) == 0)
		{
			strcpy(data[size].minute, "-1");
			return;
		}

		if (data[size].calories != -1)
		{
			data[size].calories = atof(strtok(NULL, ","));
		}
		if (data[size].distance != -1)
		{
			data[size].distance = atof(strtok(NULL, ","));
		}
		if (data[size].floors != -1)
		{
			data[size].floors = atoi(strtok(NULL, ","));
		}
		if (data[size].heartRate != -1)
		{
			data[size].heartRate = atoi(strtok(NULL, ","));
		}
		if (data[size].steps != -1)
		{
			data[size].steps = atoi(strtok(NULL, ","));
		}
		data[size].sleepLevel = atoi(strtok(NULL, ","));
	
}

/*************************************************************
 * Function: delete_line ()                                  *
 * Date Created: 1/26/2022                                   *
 * Date Last Modified: 1/28/2022                             *
 * Description: This detects if the line is a dupilicate or  *
 * an invalid patient then it will delete the line           *
 * Input parameters: FILE* f, FitbitData *data, int size,    *
 * char* targetid											 *
 * Returns:                                                  *
 * Preconditions: It requires a target for the patient id and*
 * the input file that contains the data					 *
 * Postconditions: The data within the Fitbitdata will be rid*
 * of duplicates and invalid patients                        *
 *************************************************************/

void delete_line(FILE* f, FitbitData *data, int size, char* targetid)
{
	for (int arrsize = 0; arrsize != size; arrsize++)
	{
		get_line(f, data, targetid, arrsize);
		if ((strcmp(data[arrsize].patient, "-1") == 0) || (strcmp(data[arrsize].minute, "-1") == 0))
		{
			arrsize--;
		}
	}
}

/*************************************************************
 * Function: total_calories ()                               *
 * Date Created: 1/26/2022                                   *
 * Date Last Modified: 1/28/2022                             *
 * Description: This calculates the total calories within the*
 * FitbitData array                                          *
 * Input parameters: FitbitData data[], int size, int total  *
 * Returns: int total                                        *
 * Preconditions: It requires the calories within the        *
 * FitbitData to have values                                 *
 * Postconditions: The integer number of the total calories  *
 *************************************************************/

double total_calories(FitbitData data[], int size, double total)
{

	if (size < 0)
	{
		return total;
	}

	if (data[size].calories < 0)
	{
		data[size].calories = 0;
	}

	total_calories(data, size - 1, (total + data[size].calories));
}

/*************************************************************
 * Function: total_distanace ()                              *
 * Date Created: 1/26/2022                                   *
 * Date Last Modified: 1/28/2022                             *
 * Description: This calculates the total distance within the*
 * FitbitData array                                          *
 * Input parameters: FitbitData data[], int size, int total  *
 * Returns: int total                                        *
 * Preconditions: It requires the distance within the        *
 * FitbitData to have values                                 *
 * Postconditions: The integer number of the total distance  *
 *************************************************************/

double total_distance(FitbitData data[], int size, double total)
{

	if (size < 0)
	{
		return total;
	}

	if (data[size].distance < 0)
	{
		data[size].distance = 0;
	}


	total_distance(data, size-1, (total + data[size].distance));
}

/*************************************************************
 * Function: total_floors ()                                 *
 * Date Created: 1/26/2022                                   *
 * Date Last Modified: 1/28/2022                             *
 * Description: This calculates the total floors within the  *
 * FitbitData array                                          *
 * Input parameters: FitbitData data[], int size, int total  *
 * Returns: int total                                        *
 * Preconditions: It requires the floors within the          *
 * FitbitData to have values                                 *
 * Postconditions: The integer number of the total floors    *
 *************************************************************/

int total_floors(FitbitData data[], int size, int total)
{

	if (size < 0)
	{
		return total;
	}

	if (data[size].floors == 4294967295)
	{
		data[size].floors = 0;
	}

	total_floors(data, size - 1, (total + data[size].floors));
}

/*************************************************************
 * Function: average_heartRate ()                            *
 * Date Created: 1/26/2022                                   *
 * Date Last Modified: 1/28/2022                             *
 * Description: This calculates the total heartrate within   *
 * the FitbitData array and the average heartrate            *
 * Input parameters: FitbitData data[], int size, int total  *
 * Returns: int total / 1440                                 *
 * Preconditions: It requires the heartrate within the       *
 * the FitbitData to have values                             *
 * Postconditions: The double number of the average heartrate*
 *************************************************************/

double average_heartRate(FitbitData data[], int size, int total)
{
	
	if (size > 0)
	{
		if (data[size].heartRate == 4294967295)
		{
			data[size].heartRate = 0;
		}
		
		return average_heartRate(data, size - 1, (total + data[size].heartRate));
	}

	return ((double)total / 1440);
}

/*************************************************************
 * Function: total_steps ()                                  *
 * Date Created: 1/26/2022                                   *
 * Date Last Modified: 1/28/2022                             *
 * Description: This calculates the total steps within the   *
 * FitbitData array                                          *
 * Input parameters: FitbitData data[], int size, int total  *
 * Returns: int total                                        *
 * Preconditions: It requires the steps within the           * 
 * the FitbitData to have values                             *
 * Postconditions: The integer number of the total steps     *
 *************************************************************/

int total_steps(FitbitData data[], int size, int total)
{

	if (size < 0)
	{
		return total;
	}

	if (data[size].steps == 4294967295)
	{
		data[size].steps = 0;
	}

	total_steps(data, size-1, (total + data[size].steps));
}

/*************************************************************
 * Function: steps_Calculation ()                            *
 * Date Created: 1/27/2022                                   *
 * Date Last Modified: 1/28/2022                             *
 * Description: It finds the max step and calculates the     *
 * total of steps                                            *
 * Input parameters: FitbitData data[], int* mm, int size,   *
 * int total                                                 *
 * Returns: total_steps(data, size-1, total)                 *
 * Preconditions: It requires the steps within the           * 
 * the FitbitData to have values                             *
 * Postconditions: mm gets the index of where the max step is*
 * located within the FitbitData array                       *
 *************************************************************/

int steps_Calculation(FitbitData data[], int* mm, int size, int total)
{
	int maxStep = 0;
	
	for (int index = 0; index < size; index++)
	{
		if (data[index].steps == 4294967295)
		{
			data[index].steps = 0;
		}

		if (maxStep <= data[index].steps)
		{
			maxStep = data[index].steps;
			*mm = index;
		}
	}
	
	return total_steps(data, size-1, total);
}

/*************************************************************
 * Function: sleep_Calculation ()                            *
 * Date Created: 1/27/2022                                   *
 * Date Last Modified: 1/28/2022                             *
 * Description: Calculates the poorest sleep and determines  *
 * the range the poorest sleep happened                      *
 * Input parameters: FitbitData data[], int* endminute,      *
 * int* startminute, int size								 *
 * Returns: int sumSleepWorse                                *
 * Preconditions: Nothing                                    *
 * Postconditions: the start of the worse sleep range and the*
 * end of the worse sleep range gets assigned to startminute *
 * and endminute respectively                                *
 *************************************************************/

int sleep_Calculation(FitbitData data[], int* endminute, int* startminute, int size)
{
	int sumSleepCur = 0;
	int sumSleepWorse = 0;
	int worseStart = 0;
	int worseEnd = 0;
	int startCur = 0;
	for (int index = 0; index <= size; index++)
	{
		if (data[index].sleepLevel > 1)
		{
			startCur = index;
			sumSleepCur = data[index].sleepLevel;
			index++;
			while (data[index].sleepLevel > 1)
			{
				sumSleepCur = sumSleepCur + data[index].sleepLevel;
				index++;
			}
			if (sumSleepCur >= sumSleepWorse)
			{
				worseStart = startCur;
				worseEnd = index-1;
				sumSleepWorse = sumSleepCur;
			}
		}
	}

	*endminute = worseEnd;
	*startminute = worseStart;
	return sumSleepWorse;

}

/*************************************************************
 * Function: print_Result()                                  *
 * Date Created: 1/29/2022                                   *
 * Date Last Modified: 1/29/2022                             *
 * Description: Prints the FitbitData array to console &     *
 * Result.csv												 *
 * Input parameters: FILE* f,FitbitData data[], int size     *
 * Returns: Nothing                                          *
 * Preconditions: Data from the FitbitData array should have *
 * duplicates removed and any non vailid data be 0           *
 * Postconditions: Prints out the results, totals, and max of*
 * each values                                               *
 *************************************************************/

void print_Result(FILE* f,FitbitData data[], int size)
{
	int maxStepIndex = 0;

	int startRangeSleep = 0;

	int endRangeSleep = 0;
	
	// initialize the ranges for the worse sleep
	
	sleep_Calculation(data, &endRangeSleep, &startRangeSleep, size);
	
	/***************************************PRINTING TO CONSOLE********************************************************/
	
	printf("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	
	printf("%lf, %lf, %d, %d, %lf, %d, %s : %s\n", total_calories(data, size - 1, 0), total_distance(data, size - 1, 0),
		total_floors(data, size - 1, 0), steps_Calculation(data, &maxStepIndex, size, 0), average_heartRate(data, size - 1, 0),
		data[maxStepIndex].steps, data[startRangeSleep].minute, data[endRangeSleep].minute);
	
	/***************************************PRINTING TO CSV FILE********************************************************/
	
	fprintf(f, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");

	fprintf(f, "%lf, %lf, %d, %d, %lf, %d, %s : %s\n", total_calories(data, size - 1, 0), total_distance(data, size - 1, 0),
		total_floors(data, size - 1, 0), steps_Calculation(data, &maxStepIndex, size, 0), average_heartRate(data, size - 1, 0),
		data[maxStepIndex].steps, data[startRangeSleep].minute, data[endRangeSleep].minute);
	
	for (int arrsize = 0; arrsize != size; arrsize++)
	{
		fprintf(f, "%s,%s,%lf,%lf,%d,%d,%d,%d\n", data[arrsize].patient, data[arrsize].minute, data[arrsize].calories,
			data[arrsize].distance, data[arrsize].floors, data[arrsize].steps, data[arrsize].heartRate,
			data[arrsize].sleepLevel);

		printf("%s,%s,%lf,%lf,%d,%d,%d,%d\n", data[arrsize].patient, data[arrsize].minute, data[arrsize].calories,
			data[arrsize].distance, data[arrsize].floors, data[arrsize].steps, data[arrsize].heartRate,
			data[arrsize].sleepLevel);
	}
}