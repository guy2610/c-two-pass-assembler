#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Header.h"
#include "util.h"
#include "label.h"

lbl* label_search(lbl* head, char* str)
{
	lbl* tmp = (lbl*)malloc(sizeof(lbl));
	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->symbole!=NULL&&strcmp(tmp->symbole, str)==0)
			return tmp;
		else
			tmp = tmp->next;
	}
	return tmp;

}
lbl* add_label(lbl* head, char* str, int* DC, symbol_type type)
{
	lbl* tmp;
	char *adr = malloc(5 * sizeof(char));
	adr[0] = '0' + ((*DC) / 1000);
	adr[1] = '0' + (((*DC) % 1000) / 100);
	adr[2] = '0' + (((*DC) % 100) / 10);
	adr[3] = '0' + ((*DC) % 10);
	adr[4] = '\0';
	tmp = head;

	if (tmp == NULL)
	{
		head = malloc(sizeof(lbl));
		head->symbole = malloc(MAX_LABEL_LEN * sizeof(char));
		head->address = malloc(5 * sizeof(char));
		strcpy(head->symbole, str);
		strcpy(head->address, adr);
		head->attribute = type;
		head->next=NULL;


	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(lbl));
		tmp = tmp->next;
		tmp->symbole = malloc(MAX_LABEL_LEN * sizeof(char));
		tmp->address = malloc(5 * sizeof(char));
		strcpy(tmp->symbole, str);
		strcpy(tmp->address, adr);
		tmp->attribute = type;
		tmp->next=NULL;


	}
	return head;
}
Bool valid_label_name(char* labelName)
{
    opcode op;
    funct fun;
    registers reg;

    if (labelName[0] && strlen(labelName) <= MAX_LABEL_LEN && isalpha((unsigned char)labelName[0]))
    {
        op_funct_code(labelName, &op, &fun);
        registerCod(labelName, &reg);

        if (op == NONE_OP && reg == NONE_REG && is_instruction(labelName) == F)
        {
            return T;
        }
    }

    return F;
}
void updateAdrresslabel(int ICF,lbl* head)
{

	int add = 0;
	char* temp;
	lbl *tmplbl;
	tmplbl=head;
	temp=(char*)malloc(5 * sizeof(char));
	while(tmplbl!=NULL)
	{
		if (tmplbl->attribute == DATA )
		{
			add = binToDecimal(tmplbl->address);
			bin(temp, ICF + add);
			strcpy(cmd_arr->address, temp);
		}
		tmplbl = tmplbl->next;
	}
	free(temp);
}
