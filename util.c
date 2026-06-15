#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"
#include "util.h"
#include "label.h"
#include "data.h"
Bool ifItInt(char* string)
{
	int i = 0;

	if (string[0] == '-' || string[0] == '+') string++;
	for (; string[i]; i++)
		if (!isdigit(string[i]))
		{
			return F;
		}
	if (i > 0)return T;
	else return F;
}
int moveToNotWhiteSpace(line l, int i)
{
	while (isspace(l.info[i])&&(i<80))i+=1;
	return i;
}
int countOperands(line l, int i)
{
	int count = 0;
	while (i<80&&i<(strlen(l.info)-1))
	{
		i = moveToNotWhiteSpace(l, i);
		while (isspace(l.info[i]) == 0&&l.info[i] != ',')
        {
            i+= 1;
        }
		//if(l.info[i]!='\n')
            count += 1;
		i = moveToNotWhiteSpace(l, i);
		if (l.info[i] == ',') i += 1;
		i = moveToNotWhiteSpace(l, i);
	}
	return count;
}
Bool rightOperans(opcode op, int number)
{
	if (op<5)
	{
		return((number== 2)?(T):(F));
	}
	if (op < 14)
	{
		return((number == 1)?(T):(F));
	}
	if (op < 16)
	{
		return ((number == 0)?(T):(F));
	}
	else
	{
		return F;
	}
}
void extraWord(line lineCode,lbl *head, int i, int* IC)
{
    int k;
	Wrd* newWord = (Wrd*)malloc(sizeof(Wrd));
	addres_type src_address = IMMEDIATE;
	addres_type dest_address = IMMEDIATE;

	char *tempExW=(char*)malloc(MAX_LINE_LENGTH * sizeof(char));;
    for (k = 0;lineCode.info[i] && lineCode.info[i] != ' ' && lineCode.info[i] != '\n' && lineCode.info[i] != '\t' && lineCode.info[i] != ',' && lineCode.info[i] != EOF;i += 1, k += 1)
		{
			tempExW[k] = lineCode.info[i];
		}
		tempExW[k]='\0';
		dest_address = addressing_type(head,tempExW);
	if (dest_address == REGISTER)
	{

		registerCod_bilder(tempExW,newWord);

		cmd_input_arr(*newWord, 'A', IC);
	}
	if (dest_address == DIRECT)
	{
		newWord = (Wrd *)cmd_builder(MOV_OP, MOV_FUNCT, src_address, dest_address);
		cmd_input_arr(*newWord, '?', IC);
	}
	if (dest_address == IMMEDIATE)
	{

		Wrd binary;
		numberCod(tempExW, binary.code);
		cmd_input_arr(binary, 'A', IC);
        tempExW=NULL;
	}
	if (dest_address == RELATIVE)
	{
		 newWord = (Wrd *)cmd_builder(MOV_OP, MOV_FUNCT, src_address, dest_address);
		cmd_input_arr(*newWord, '?', IC);
	}

}
void bin(char* y, int x)/*converts to binary number */
{

	int i, j;
	j = strlen(y);
	i = 0;
	while (x > 0)
	{
		y[j - 1 - i] = (x % 2) + '0';
		x = x / 2;
		i++;
	}
}
int binToDecimal(char* bin)
{
    int x = 0;
	int i = 0;
	int j;
	for (j = strlen(bin)-1;j >=0 ; j -= 1)
		{

			if (bin[i] == '1')
			{
				x += (1 << j);

			}
			i += 1;
		}
    return x;
}
char* HexaNumber(char* number)
{
	char* hexaNum = (char*)malloc(WRD_ARR_BITS_LEN * sizeof(char));
	int i = 0;
	int j, count = 0;
	int sum = 0;
	static char* hex = "0123456789ABCDEF";
	while (count <=2)
	{
		for (j = 3;j >=0 ; j -= 1)
		{

			if (number[i] == '1')
			{
				sum += (1 << j);

			}
			i += 1;
		}

		hexaNum[count] = hex[sum];
		sum = 0;

		count += 1;
	}
	hexaNum[3] = '\0';
	return hexaNum;
}
void AsciNumber(char* word, char asci)
{
	unsigned short int sing = 1;

	int j = WRD_ARR_BITS_LEN - 1;
	while (j >= 0)
	{
		if (asci & sing)
		{
			word[j] = '1';
		}
		else
		{
			word[j] = '0';
		}
		sing <<= 1;
		j -= 1;
	}
	word[WRD_ARR_BITS_LEN] = '\0';
}
void registerCod_bilder(char* code,Wrd* reg)
{

    int i =0;
    while(i<WRD_ARR_BITS_LEN)
    {
        reg->code[i]='0';
        i+=1;
    }
	 i = code[1] - '0' ;
	char c = code[2];
	if (code[0] == 'r' && ((code[1]-'0' )>= 0 && (code[1] - '0') <= 7) && code[2] == '\0')
	{

		switch (code[1])
		{
		case '0':  reg->code[WRD_ARR_BITS_LEN-1-0] = '1'; return;
		case '1':  reg->code[WRD_ARR_BITS_LEN-1-1] = '1'; return;
		case '2':  reg->code[WRD_ARR_BITS_LEN-1-2] = '1'; return;
		case '3':  reg->code[WRD_ARR_BITS_LEN-1-3] = '1'; return;
		case '4':  reg->code[WRD_ARR_BITS_LEN-1-4] = '1'; return;
		case '5':  reg->code[WRD_ARR_BITS_LEN-1-5] = '1'; return;
		case '6':  reg->code[WRD_ARR_BITS_LEN-1-6] = '1'; return;

		case '7':  reg->code[WRD_ARR_BITS_LEN-1-7] = '1'; return;

		}
			reg->code[WRD_ARR_BITS_LEN]='\0';

	}


}
void registerCod(char* code, registers* reg)
{
	int i = code[1] - '0' ;
	char c = code[2];
	if (code[0] == 'r' && ((code[1]-'0' )>= 0 && (code[1] - '0') <= 7) && code[2] == '\0')
	{

		switch (code[1])
		{
		case '0':  *reg = R0;return;
		case '1':  *reg = R1; return;
		case '2':  *reg = R2; return;
		case '3':  *reg = R3; return;
		case '4':  *reg = R4; return;
		case '5':  *reg = R5; return;
		case '6':  *reg = R6; return;
		case '7':  *reg = R7; return;

		}

	}
	else
	{
		*reg = NONE_REG;
	}
}
void numberCod(char *num, char *binary)
{
	Bool positve = T;
	int i = 0;
	unsigned int sum = 0;
	unsigned int number = 1;
    if(num[0]=='-')
    {
        positve=F;
        i++;
    }
	while (num[i] != '\0')
	{
		sum *= 10;

		sum += ((int)(num[i]) - 48);

		i += 1;
	}
	i = WRD_ARR_BITS_LEN - 1;
	if (positve==T)
	{
		while (i >=0)
		{
			if (number & sum)
			{
				binary[i] = '1';
			}
			else
			{
				binary[i] = '0';
			}
			number <<= 1;
			i -= 1;
		}
	}
	else
	{
		while (i >=0 )
		{
			if (!positve)
			{
				if (number & sum)
				{
					binary[i] = '1';
					positve = T;
				}
				else
				{
					binary[i] = '0';
				}
			}
			else
			{
				if (number & sum)
				{
					binary[i] = '0';

				}
				else
				{
					binary[i] = '1';
				}
			}
			number <<= 1;
			i -= 1;
		}

	}
	binary[WRD_ARR_BITS_LEN] = '\0';
}
addres_type  addressing_type(lbl* head,char* num)
{
	if (num[0] == '#' && ifItInt(num + 1)==T)
	{
		return IMMEDIATE;
	}
	else if (label_search(head,num)!=NULL)
	{
		return DIRECT;
	}
	else if (num[0] == '%' && label_search(head,++num) != NULL)
	{
		return RELATIVE;
	}
	else if (num[0] == 'r' && num[1] >= '0' && num[1] <= '7' && ((num[2] == '\0'||num[2]==' '||num[2]==',')))
	{
		return REGISTER;
	}
	else
	{
		return NONE_ADDR;
	}
}
void op_funct_code(char* key, opcode* op, funct* fun)
{
	int i;
	*op = NONE_OP;
	*fun = STOP_FUNCT;
	for (i = 0; i < TABLE_SIZE; i++) {
		code sym = lookuptable[i];
		if (strcmp(sym.string, key) == 0)
		{
			*op = sym.op_table;
			*fun = sym.funct_table;
		}
	}
}
void data_free_arr()
{
    int c=0;
    while(c<MAX_ARR_LEN)
    {
        free(data_arr[c].address);
        c++;
    }
}
void cmd_free_arr()
{
    int c=0;
    while(c<MAX_ARR_LEN)
    {
        free(cmd_arr[c].address);
        c++;
    }
}
void label_free(lbl *head)
{
    lbl *tmp;
    tmp=head;
    while(tmp!=NULL)
    {
        free(tmp->symbole);
        free(tmp->address);
        tmp=tmp->next;
    }
    free(head);
}
char *intToString(int k)
{
    int len = snprintf(NULL, 0, "%d", k);
    char *x = malloc((size_t)len + 1);
    if (!x)
    {
        return NULL;
    }

    snprintf(x, (size_t)len + 1, "%d", k);
    return x;
}

Bool checkingEntry(lbl *head)
{
    lbl *lblTmp;
    lblTmp=head;
    while(lblTmp!=NULL)
	    {
	     if(lblTmp->attribute==ENTRY)
	         return T;
	     lblTmp=lblTmp->next;
	    }
	    return F;
}
Bool checkingExternal(lbl *head)
{
    lbl *lblTmp;
    lblTmp=head;
    while(lblTmp!=NULL)
	    {
	     if(lblTmp->attribute==EXTERNAL)
	         return T;
	     lblTmp=lblTmp->next;
	    }
	    return F;
}
Bool is_instruction(char* str)
{
    if (strcmp(str, "data") == 0 ||
        strcmp(str, "string") == 0 ||
        strcmp(str, "extern") == 0 ||
        strcmp(str, "entry") == 0 ||
        strcmp(str, ".data") == 0 ||
        strcmp(str, ".string") == 0 ||
        strcmp(str, ".extern") == 0 ||
        strcmp(str, ".entry") == 0)
    {
        return T;
    }

    return F;
}

void printing_to_files(char* fileName,lbl *head ,int ICF,int DCF)
{
    printf("IC:%d , DC:%d",ICF,DCF);
    FILE *obFile, *entFile, *extFile;
	char *obFileName, *entFileName, *extFileName;
	lbl *lblTmp;
	int i=0;
	obFileName=malloc(strlen(fileName) + strlen(".ob") + 1);
	strcpy(obFileName, fileName);
	strcat(obFileName,".ob");
	obFile=fopen(obFileName,"w");
	fputs("    ",obFile);
	fputs(intToString(ICF),obFile);
	fputc(' ',obFile);
	fputs(intToString(DCF),obFile);
	fputc('\n',obFile);
	while(i<(ICF))
	{
	    fputs(cmd_arr[i].address,obFile);
	    fputc(' ',obFile);
	    fputs(HexaNumber(cmd_arr[i].word.code),obFile);
	    fputc(' ',obFile);
	    fputc(cmd_arr[i].tag,obFile);
	    fputc('\n',obFile);
	    i++;
	}
	i=0;
	while(i<(DCF))
	{
	    fputs(data_arr[i].address,obFile);
	    fputc(' ',obFile);
	    fputs(HexaNumber(data_arr[i].word.code),obFile);
	    fputc(' ',obFile);
	    fputc('A',obFile);
	    fputc('\n',obFile);
	    i++;
	}
	fclose(obFile);
	free(obFileName);
	if(checkingEntry(head)==T)
	{
	    entFileName=malloc(strlen(fileName) + strlen(".ent") + 1);
	    strcpy(entFileName, fileName);
	    strcat(entFileName,".ent");
	    entFile=fopen(entFileName,"w");
	    lblTmp=head;
	    while(lblTmp!=NULL)
	    {
	     if(lblTmp->attribute==ENTRY)
	     {
	         fputs(lblTmp->symbole,entFile);
	         fputc(' ',entFile);
	         fputs(lblTmp->address,entFile);
	         fputc('\n',entFile);
	     }
	     lblTmp=lblTmp->next;
	    }
	   fclose(entFile);
	   free(entFileName);
	}
	if(checkingExternal(head)==T)
	{
	    extFileName=malloc(strlen(fileName) + strlen(".ext") + 1);
	    strcpy(extFileName, fileName);
	    strcat(extFileName,".ext");
	    extFile=fopen(extFileName,"w");
	    lblTmp=head;
	    while(lblTmp!=NULL)
	    {
	     if(lblTmp->attribute==EXTERNAL)
	     {
	         fputs(lblTmp->symbole,extFile);
	         fputc(' ',extFile);
	         fputs(lblTmp->address,extFile);
	         fputc('\n',extFile);
	     }
	     lblTmp=lblTmp->next;
	    }
	    free(extFileName);
	    fclose(extFile);
	}
}
