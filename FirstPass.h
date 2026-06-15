#include"util.h"
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100

lblb proceesLine(line , int* , int* , lbl* );/*this function gets a line , DC, IC ,the head of the label list and diagnosing the line, the second pass*/
Bool processString(line , int , int* );/*this function gets a line and string and process it ,help codeProcessing */
Bool dataProcessing(line, int* , int );/*this function gets a line and data and process it ,help codeProcessing */
Bool processData(line , int , int* );/*this function gets a line and data and process it ,help codeProcessing */
Bool codeProcessing(line ,lbl* head, int , int* );/*this function gets a line and index, a, head of label list and IC, and processing the line of the second pass*/
