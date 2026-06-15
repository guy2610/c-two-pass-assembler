#define MAX_LABEL_LEN 31/*max label length*/
#define MAX_ARR_LEN 150/*max arrray length*/
#define WRD_ARR_BITS_LEN 12/*max word length*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))/**/
#define MAX_LINE_LENGTH 80/*max line input length*/
#define IcStart 100/* IC initial*/
#include "Header.h"
Bool ifItInt(char* );/*this function gets a string and returns boolean if the string is capable of converting to integer*/
int moveToNotWhiteSpace(line , int );/*this function gets a line and an index and returns the next index which is not a white-space character*/
int countOperands(line , int );/*this function gets a line and an index after a known opcode and returns the number of the operands it has in the line*/
Bool rightOperans(opcode , int );/*this function gets an opcode and the number of operands and returns a boolean if the number of operands is exactly the same as in the opcode's settings*/
void extraWord(line ,lbl *head , int , int* );/*this function gets line, head of the label list, index in the line and IC and adds a word to the command's array*/
void bin(char* , int );/*this function gets a integer and return the binary number using a string*/
int binToDecimal(char* );/*this function gets a binary number as a string and returns its decimal number as an integer format*/
Bool is_instruction(char* str);/*this function gets a string and check if it is an opcode*/
char* HexaNumber(char* number);/*this function gets a number in string and convert it to hexa base*/
void AsciNumber(char* word, char asci);/*this function gets a code and the word of the register */
void registerCod_bilder(char* code,Wrd* reg);/*this function gets a word of the register and builds a code of it by turn the right bit of the register */
void registerCod(char* code, registers* reg);/*this function checks if it is a register in the text*/
void numberCod(char *num, char *binary);/*this function gets a number in string and return the binary code in string format*/
addres_type  addressing_type(lbl *head,char* num);/*this function gets the head of the label list and a string and return the right addressing type*/
void op_funct_code(char* key, opcode* op, funct* fun);/*this function gets string and puts the opcode value and funct value in the pointers*/
void data_free_arr();/*this function free the dynamic memory in the data array*/
void cmd_free_arr();/*this function free the dynamic memory in the command array*/
void label_free(lbl *head);/*this function free the dynamic memory of the label list*/
char *intToString(int k);/*this function gets a integer and returns in string format*/
Bool checkingEntry(lbl *head);/*this function gets the head of the label list and return if there is word with entry attribute*/
Bool checkingExternal(lbl *head);/*this function gets the head of the label list and return if there is word with external attribute*/
void printing_to_files(char* fileName,lbl *head ,int ICF,int DCF);/*this function printing the output two the files formats ob,ent,ext */
