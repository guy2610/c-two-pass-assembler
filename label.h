#include <stdio.h>
#include "util.h"
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100
lbl* label_search(lbl* , char* );/*this function gets the head the label list and a string and search if it exist if true it return the label*/
lbl * add_label(lbl* , char* , int *, symbol_type );/*this function gets the head the label list and a string, DC ,symbole type and add to the label list and return the head*/

Bool valid_label_name(char* labelName);/*this function gets a name and check if it is a valid name*/
void updateAdrresslabel(int ,lbl* );/*this function update the address in label list*/
