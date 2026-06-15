#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"
#include "util.h"
#include "FirstPass.h"
#include "data.h"
#include "label.h"
lblb proceesLine(line currLine, int* DC, int* IC, lbl* head)
{
	int i = 0;
	int j;
	Bool addLabel = F;
	lblb bhead;
	bhead.head = head;
	bhead.b = T;
	char* lableName = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
	char *temp= (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
	lbl* labelWord = ((lbl*)malloc(sizeof(lbl)));
	Bool proceesSuccessful = T;
	i = moveToNotWhiteSpace(currLine, i);
	if (i > MAX_LINE_LENGTH)
	{
		bhead.head=head;
        bhead.b=T;
		return bhead;
	}
	for (j = 0;currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF && j < MAX_LINE_LENGTH - 1;i += 1, j += 1)
	{
		temp[j] = currLine.info[i];

	}
	temp[j] = '\0';
	if (j > 0 && temp[j - 1] == ':')
	{
		strcpy(lableName, temp);
		lableName[j - 1] = '\0';
		labelWord = label_search(head,lableName);
		if (labelWord == NULL || labelWord->attribute == ENTRY|| valid_label_name(lableName))
		{
			addLabel = T;
			i = moveToNotWhiteSpace(currLine, i);
		}
		else
		{
			printf("Error In %s: %ld : ", currLine.file_name, currLine.line_number);
			printf(" Attempt to define an existing label \n");

            bhead.head=head;
            bhead.b=F;
            return bhead;
		}
	}
	else
	{
		i = moveToNotWhiteSpace(currLine, 0);

	}
	if (currLine.info[i] == '.')
	{
        free(temp);
		i += 1;
		char *temp=(char*)malloc((MAX_LINE_LENGTH-i) * sizeof(char));
		for (j = 0;currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF;i += 1, j += 1)
		{
			temp[j] = currLine.info[i];
		}
		temp[j] = '\0';
		if (strcmp(temp, "data")==0)
		{
		    if (addLabel==T)
			{
				head=add_label(head, lableName, IC, DATA);
				bhead.head=head;
                bhead.b=T;
                addLabel=F;

			}
			i = moveToNotWhiteSpace(currLine, i);
			proceesSuccessful = processData(currLine, i, DC);
			bhead.head = head;
			bhead.b = proceesSuccessful;
			free(temp);
            return bhead;
	    }
		else if (strcmp(temp, "string")==0)
		{
			if (addLabel==T)
			{
				head=add_label(head, lableName, IC, DATA);
				bhead.head=head;
                bhead.b=T;
                addLabel=F;
			}
			i = moveToNotWhiteSpace(currLine, i);
			proceesSuccessful = processString(currLine, i, DC);
			bhead.head = head;
			bhead.b = proceesSuccessful;
			free(temp);
			return bhead;
		}


		else if (strcmp(temp, "entry")==0)
		{
			i = moveToNotWhiteSpace(currLine, i);
			j=0;
			while (currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF)
			{
			    //lableName[j]=currLine.info[i];
				//j++;
				i++;
			}
			lableName[j] = '\0';
			i = moveToNotWhiteSpace(currLine, i);
			if (i >= MAX_LINE_LENGTH)
			{
				printf("Error In %s: %ld : ", currLine.file_name, currLine.line_number);
				printf(" invalid entry label\n");
				bhead.head=head;
                bhead.b=F;
                free(temp);
                return bhead;
			}
			else
			{
				bhead.head=head;
                bhead.b=T;
                free(temp);
                return bhead;

			}

		}
		else if (strcmp(temp, "extern")==0)///....like above
		{
		    int zero=0;
			i = moveToNotWhiteSpace(currLine, i);
			for (j = 0;currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF;i += 1, j += 1)
			{
				lableName[j] = currLine.info[i];
			}
			lableName[j] = '\0';
			head=add_label(head, lableName, &zero, EXTERNAL);
			bhead.head=head;
            bhead.b=T;
            free(temp);
            return bhead;
		}
	}
	else
	{
		if (addLabel==T)
		{
			head = add_label(head, lableName, IC, CODE);
			addLabel=F;
		}
        bhead.head=head;
        bhead.b=codeProcessing(currLine,head, i, IC);
        return bhead;

	}
    bhead.head = head;
    bhead.b = F;
    return bhead;
}
Bool processString(line lineString, int i, int* DC)
{
	int j;
	char *temp= (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
	char* endQuotationMarks;
	Wrd * wordChar;
	i = moveToNotWhiteSpace(lineString, i);
	if (lineString.info[i] != '\"')
	{
		printf("Error In %s: %ld : ", lineString.file_name, lineString.line_number);
		printf("Missing opening quote of string\n");
		return F;

	}
	endQuotationMarks = strrchr(lineString.info, '\"');
	if (endQuotationMarks == &lineString.info[i])
	{

		printf("Error In %s: %ld : ", lineString.file_name, lineString.line_number);
		printf("Missing closing quote of string\n");
		return F;
	}
	else
	{

        i++;
		for (j = 0;lineString.info[i] && lineString.info[i] != EOF && lineString.info[i] != '\n' && lineString.info[i] != '\"';i += 1, j += 1)
		{
			temp[j] = lineString.info[i];
		}

		temp[j] = '\0';

		i += 1;
		wordChar=(Wrd*)malloc(sizeof(Wrd));
		for (j = 0;temp[j] != EOF && temp[j] != '\0';j += 1)
		{

			AsciNumber(wordChar->code, temp[j]);
			data_input_arr(*wordChar, DC);

		}
		AsciNumber(wordChar->code, '\0');
        data_input_arr(*wordChar, DC);
        free(wordChar);

	}
    free(temp);
	return T;
}
Bool dataProcessing(line lineData, int* DC, int i)
{
	int j;
	char temp[MAX_LINE_LENGTH];
	i = moveToNotWhiteSpace(lineData, i);
	if (lineData.info[i] != '.')
	{

		return F;
	}
	else i += 1;
	for (j = 0;lineData.info[i] && lineData.info[i] != ' ' && lineData.info[i] != '\n' && lineData.info[i] != '\t';i += 1, j += 1)
	{
		temp[j] = lineData.info[i];
	}
	temp[j] = '\0';
	if (strcmp(temp, "data") == 0)
		return processData(lineData, i, DC);
	if (strcmp(temp, "string") == 0)
		return processString(lineData, i, DC);
	return T;


}
Bool processData(line lineData, int i, int* DC)
{

	int j;
	Wrd * number=(Wrd*)malloc(sizeof(Wrd));
    char *temp= (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
	i = moveToNotWhiteSpace(lineData, i);
	while (lineData.info[i] && lineData.info[i] != ' ' && lineData.info[i] != '\n' && lineData.info[i] != '\t')
	{
		for (j = 0;lineData.info[i] && lineData.info[i] != ' ' && lineData.info[i] != '\n' && lineData.info[i] != '\t' && lineData.info[i] != ',';i += 1, j += 1)
		{
			temp[j] = lineData.info[i];
		}
		temp[j]='\0';
		if (ifItInt(temp) == F)
		{
			printf("Error In %s: %ld : ", lineData.file_name, lineData.line_number);
			printf("Expected integer for .data instruction\n");
			return F;

		}
		if (ifItInt(temp) == T)
		{

			numberCod(temp, number->code);
			data_input_arr(*number, DC);
		}
		i = moveToNotWhiteSpace(lineData, i);
		if (lineData.info[i] == ',')i += 1;
		i = moveToNotWhiteSpace(lineData, i);
	}
	if (lineData.info[i - 1] == ',')
	{
		printf("Error In %s: %ld : ", lineData.file_name, lineData.line_number);
		printf("Expected integer for .data instruction\n");
		return F;
	}
	free(number);
	return T;
}
Bool codeProcessing(line lineCode,lbl *head, int i, int* IC)
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
	if (*op == NONE_OP)
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

		Wrd *newWord = cmd_builder(*op, *fun, src_address, dest_address);
		cmd_input_arr(*newWord, 'A', IC);
		return T;
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
		if(dest_address!=-1)
		{
		    Wrd *newWord = cmd_builder(*op, *fun, src_address, dest_address);
            cmd_input_arr(*newWord, 'A', IC);
            extraWord(lineCode,head, k, IC);
		}
        return T;
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
		if(dest_address!=-1&&src_address!=-1)
		{
            Wrd *newWord = cmd_builder(*op, *fun, src_address, dest_address);
            cmd_input_arr(*newWord, 'A', IC);
		}

         if(src_address!=-1)
            extraWord(lineCode,head, k, IC);
         if(dest_address!=-1)
            extraWord(lineCode,head, m, IC);

        return T;
	}

	return F;
}
