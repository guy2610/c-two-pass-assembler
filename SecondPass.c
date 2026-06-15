#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"
#include "util.h"
#include "ScondPass.h"
#include "data.h"
#include "FirstPass.h"


lblb SecondProceesLine(line currLine, int* DC, int* IC, lbl* head)
{
	int i = 0;
	int j;
	lblb bhead;
	char temp[MAX_LINE_LENGTH];
	i = moveToNotWhiteSpace(currLine, i);
	if (i > MAX_LINE_LENGTH)
	{
		bhead.head=head;
        bhead.b=T;
		return bhead;

	}
	for (j = 0;currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF &&i<MAX_LINE_LENGTH;i += 1, j += 1)
	{
		temp[j] = currLine.info[i];
	}
	if (temp[j - 1] == ':')
	{

		i = moveToNotWhiteSpace(currLine, i);


	}
	else
	{
		i = moveToNotWhiteSpace(currLine, 0);

	}
	if (currLine.info[i] == '.')
	{
		char directive[MAX_LINE_LENGTH];
		char labelName[MAX_LINE_LENGTH];
		lbl *lblTmp;
		int start = i;

		for (j = 0; currLine.info[i] &&
		             currLine.info[i] != ' ' &&
		             currLine.info[i] != '\n' &&
		             currLine.info[i] != '\t' &&
		             j < MAX_LINE_LENGTH - 1; i++, j++)
		{
			directive[j] = currLine.info[i];
		}
		directive[j] = '\0';

		if (strcmp(directive, ".entry") == 0)
		{
			i = moveToNotWhiteSpace(currLine, i);

			for (j = 0; currLine.info[i] &&
			             currLine.info[i] != ' ' &&
			             currLine.info[i] != '\n' &&
			             currLine.info[i] != '\t' &&
			             j < MAX_LINE_LENGTH - 1; i++, j++)
			{
				labelName[j] = currLine.info[i];
			}
			labelName[j] = '\0';

			lblTmp = head;
			while (lblTmp != NULL)
			{
				if (strcmp(lblTmp->symbole, labelName) == 0)
				{
					lblTmp->attribute = ENTRY;
					bhead.head = head;
					bhead.b = T;
					return bhead;
				}
				lblTmp = lblTmp->next;
			}

			printf("Error In %s: %ld : entry label '%s' was not defined\n",
			       currLine.file_name, currLine.line_number, labelName);
			bhead.head = head;
			bhead.b = F;
			return bhead;
		}

		(void)start;
	    bhead.head=head;
        bhead.b=T;
		return bhead;
	}
	else
	{
        bhead.head=head;
        bhead.b=SecondCodeProcessing(currLine,head, i, IC);//codeProcessing
		return bhead;

	}

}
Bool SecondCodeProcessing(line lineCode,lbl *head, int i, int* IC)
{
	int j,k,m;
	int operandsNum;
	char* operecion = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
	opcode* op = (opcode*)malloc(sizeof(opcode));
	funct* fun = (funct*)malloc(sizeof(funct));
	addres_type src_address = IMMEDIATE;
	addres_type dest_address = IMMEDIATE;
	i = moveToNotWhiteSpace(lineCode, i);
	for (j = 0; lineCode.info[i] != '\n' && lineCode.info[i] != ' ' && lineCode.info[i] != '\t' && lineCode.info[i] != EOF && j < 6;j++)
	{
		operecion[j] = lineCode.info[i];
		i += 1;
	}
	operecion[j] = '\0';
	op_funct_code(operecion, op, fun);
	if ((*op) == NONE_OP)
	{
		printf("Error In %s: %ld : ", lineCode.file_name, lineCode.line_number);
		printf("Unknown instruction word\n");
		return F;
	}
	operandsNum = countOperands(lineCode, i);
	if (rightOperans(*op, operandsNum)==F)
	{
		printf("Error In %s: %ld : ", lineCode.file_name, lineCode.line_number);
		printf("invalid number of operands\n");
		return F;
	}
	if (operandsNum == 0)
	{

		Wrd *newWord=cmd_builder(*op,*fun, src_address, dest_address);
		cmd_input_arr(*newWord, 'A', IC);
	}
	if (operandsNum == 1)
	{
		i = moveToNotWhiteSpace(lineCode, i);
		char *temp= (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
		for (j = 0,k=i;lineCode.info[i] && lineCode.info[i] != ' ' && lineCode.info[i] != '\n' && lineCode.info[i] != '\t' && lineCode.info[i] != ',' && lineCode.info[i] != EOF;i += 1, j += 1)
		{
			temp[j] = lineCode.info[i];
		}
		temp[j] = '\0';
		dest_address = addressing_type(head,temp);
		Wrd* newWord = cmd_builder(*op ,*fun, src_address, dest_address);
		cmd_input_arr(*newWord, 'R', IC);
		extraWord(lineCode,head, k, IC);

	}
	if (operandsNum == 2)
	{
		i = moveToNotWhiteSpace(lineCode, i);
		char *temp= (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
		for (j = 0,k=i;lineCode.info[i] && lineCode.info[i] != ' ' && lineCode.info[i] != '\n' && lineCode.info[i] != '\t' && lineCode.info[i] != ',' && lineCode.info[i] != EOF;i += 1, j += 1)
		{
			temp[j] = lineCode.info[i];
		}
		temp[j] = '\0';
		src_address = addressing_type(head,temp);
		while (isspace(lineCode.info[i]) == 0&&lineCode.info[i] != ',')	i += 1;
		i = moveToNotWhiteSpace(lineCode, i);
		if (lineCode.info[i] == ',')i += 1;
		else return F;
		i = moveToNotWhiteSpace(lineCode, i);
		for (j = 0,m=i;lineCode.info[i] && lineCode.info[i] != ' ' && lineCode.info[i] != '\n' && lineCode.info[i] != '\t'  && lineCode.info[i] != EOF;i += 1, j += 1)
		{
			temp[j] = lineCode.info[i];
		}
		temp[j] = '\0';
		dest_address = addressing_type(head,temp);
		Wrd *newWord = cmd_builder(*op, *fun, src_address, dest_address);
		cmd_input_arr(*newWord, 'R', IC);
        extraWord(lineCode,head, k, IC);
        extraWord(lineCode,head, m, IC);
	}

		return T;

}
void updateAdrressData(int ICF, int DCF)
{

	int i,j;
	char* temp = (char*)malloc(5 * sizeof(char));
	if(!temp)
    {

        printf("eror");
        free(temp);
        return;
    }
    else{
	for (i = 0;i < DCF;i += 1)
	{



		for (j = 0;j < 4;j++)
        {
            temp[j] = '0';
        }
        temp[j]='\0';
		bin(temp,ICF+i+1);
		printf("%s\n",data_arr[i].address);
		strcpy(data_arr[i].address, temp);
	}
    }
	free(temp);
}
