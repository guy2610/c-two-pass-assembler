#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "data.h"


void data_input_arr(Wrd word_in, int* DC)/*הכנסה למערך נתונים*/
{


    char const digit[] = "0123456789";
	int i,f;
	f=(*DC);
	for(i=0;i<WRD_ARR_BITS_LEN;i++)
	    data_arr[f].word.code[i]= word_in.code[i];
	data_arr[f].address[0]=digit[(f / 1000)];
    data_arr[f].address[1]=digit[((f % 1000) / 100)];
    data_arr[f].address[2]=digit[((f % 100) / 10)];
    data_arr[f].address[3]=digit[(f % 10)];
    data_arr[f].address[4]='\0';
     (*DC) =(*DC)+  1;

}
void cmd_input_arr(Wrd word_in, char tag_in, int* IC)
{
    char const digit[] = "0123456789";
	int i,f;
    f=((*IC)-100);
    for(i=0;i<WRD_ARR_BITS_LEN;i++)
	    cmd_arr[f].word.code[i]= word_in.code[i];
	cmd_arr[f].tag = tag_in;
	cmd_arr[f].address[0]=digit[((*IC)/ 1000)];
    cmd_arr[f].address[1]=digit[(((*IC) % 1000) / 100)];
    cmd_arr[f].address[2]=digit[(((*IC) % 100) / 10)];
    cmd_arr[f].address[3]=digit[((*IC) % 10)];
    cmd_arr[f].address[4]='\0';
	(*IC) = ((*IC)+1);

}
void init_cmd_array(void)
{
	int i, j;
	i = j = 0;
	while (i < MAX_ARR_LEN)
	{
	    cmd_arr[i].address=(char *)malloc(5 * sizeof(char));
		strcpy(cmd_arr[i].address,"0100");
		for (j=0;j < WRD_ARR_BITS_LEN;j++)
			cmd_arr[i].word.code[j] = '0';
		cmd_arr[i].tag = 'A';
		i++;
	}

}

void init_data_array(void)
{
	int i, j;
	i = j = 0;
	while (i < MAX_ARR_LEN)
	{
	    data_arr[i].address=malloc(5 * sizeof(char));
		strcpy(data_arr[i].address ,"0000");
		for (j=0;j < WRD_ARR_BITS_LEN;j++)
		    data_arr[i].word.code[j] = '0';
		i++;
	}
}
Wrd* cmd_builder( opcode  op , funct fun, addres_type src_address, addres_type dest_address)/*use "bin" to input the binary code in the array,look at the Wrd array in left to right** when we paste we need to paste in reverse*/
{
	int i;
	Wrd *word = (Wrd*) malloc(sizeof(Wrd));
	char* op_code;
	char* funct_b;
	char* srcAddress;
	char* destAddress;
	op_code = malloc(5 * sizeof(char));
	funct_b = malloc(5 * sizeof(char));
	srcAddress = malloc(3 * sizeof(char));
	destAddress = malloc(3 * sizeof(char));
	for (i = 0;i < 4;i++)
	{
		op_code[i] = '0';
		funct_b[i] = '0';
	}
	op_code[i] = '\0';
    funct_b[i] = '\0';
	for (i = 0;i < 2;i++)
	{
		srcAddress[i] = '0';
		destAddress[i] = '0';
	}
	srcAddress[i] = '\0';
    destAddress[i] = '\0';
	bin(op_code, op);
	bin(funct_b, fun);
	bin(srcAddress, src_address);
	bin(destAddress, dest_address);
	i = 0;
	while (i < 4)
	{
		word->code[i + 4] = funct_b[i];
		word->code[i] = op_code[i];
		i++;
	}
	i = 0;
	while (i < 2)
	{
		word->code[i+10] = destAddress[i];
		word->code[i + 8] = srcAddress[i];
		i++;
	}
	free(op_code);
	free(funct_b);
	free(srcAddress);
	free(destAddress);
	return word;
}


