#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum sleep

{

    NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3

} Sleep;

typedef struct fitbit

{
    char patient[10];

    char minute[9];

    double calories;

    double distance;

    unsigned int floors;

    unsigned int heartRate;

    unsigned int steps;

    Sleep sleepLevel;

} FitbitData;

void find_target(FILE* f, char* targetid);

void get_line(FILE* f, FitbitData* data, char* targetid, int size);

void delete_line(FILE* f, FitbitData* data, int size, char* targetid);

double total_calories(FitbitData data[], int size, double total);

double total_distance(FitbitData data[], int size, double total);

int total_floors(FitbitData data[], int size, int total);

double average_heartRate(FitbitData data[], int size, int total);

int total_steps(FitbitData data[], int size, int total);

int steps_Calculation(FitbitData data[], int* date, int size, int total);

int sleep_Calculation(FitbitData data[], int* endminute, int* startminute, int size);

void print_Result(FILE* f, FitbitData data[], int size);


//void print_Result(FitbitData data[], int );