#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100
lblb SecondProceesLine(line , int* , int* , lbl* );/*this function gets a line , DC, IC ,the head of the label list and diagnosing the line, the second pass*/
Bool SecondCodeProcessing(line ,lbl *head, int , int* );/*this function gets a line and index, a, head of label list and IC, and processing the line of the second pass*/
void updateAdrressData(int ,int);/*this function update the data adderss in the array*/
