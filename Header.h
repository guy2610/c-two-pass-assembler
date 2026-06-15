#pragma once
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100
typedef enum symbol_type {/*kinds of the symbole type*/
	CODE=0,
	DATA,
	EXTERNAL,
	ENTRY
} symbol_type;
typedef enum {F,T} Bool;/*boolean expression*/
typedef struct Label {/*structure of a list*/
	char* symbole;
	char* address;
	symbol_type attribute;
	struct Label* next;
}lbl;
typedef struct Boolh {/*structure of a head list and boolean*/
	Bool b;
	lbl *head;
}lblb;
typedef struct Word {/*structure of a word*/
	char code[WRD_ARR_BITS_LEN + 1];
}Wrd;
typedef struct Command {/*structure of a command */
	char* address;
	Wrd word;
	char tag;
}Cmd;
typedef struct Data {/*structure of a data */
	char* address;
	Wrd word;
}Data;
typedef enum opcodes {/*kinds of given opcodes*/
	MOV_OP = 0,
	CMP_OP = 1,
	ADD_OP = 2,
	SUB_OP = 2,
	LEA_OP = 4,
	CLR_OP = 5,
	NOT_OP = 5,
	INC_OP = 5,
	DEC_OP = 5,
	JMP_OP = 9,
	BNE_OP = 9,
	JSR_OP = 9,
	RED_OP = 12,
	PRN_OP = 13,
	RTS_OP = 14,
	STOP_OP = 15,
	NONE_OP = -1
} opcode;
typedef enum funct {/*kinds of given functs*/
	MOV_FUNCT = 0,
	CMP_FUNCT = 0,
	ADD_FUNCT = 10,
	SUB_FUNCT = 11,
	LEA_FUNCT = 0,
	CLR_FUNCT = 10,
	NOT_FUNCT = 11,
	INC_FUNCT = 12,
	DEC_FUNCT = 13,
	JMP_FUNCT = 10,
	BNE_FUNCT = 11,
	JSR_FUNCT = 12,
	RED_FUNCT = 0,
	PRN_FUNCT = 0,
	RTS_FUNCT = 0,
	STOP_FUNCT = 0


} funct;

typedef struct line {/*structure of a line*/
	char* file_name;
	long line_number;
	char* info;
} line;
typedef enum addres_type {/*kinds of given address*/

	IMMEDIATE = 0,

	DIRECT = 1,

	RELATIVE = 2,

	REGISTER = 3,

	NONE_ADDR = -1
} addres_type;
typedef enum registers {/*kinds of given registers*/
	R0 = 0,
	R1=1,
	R2=2,
	R3=3,
	R4=4,
	R5=5,
	R6=6,
	R7=7,
	NONE_REG = -1
} registers;
typedef enum instruction {/*kinds of given instructions*/
	DAT,
	EXTERN,
	ENTR,
	STRING,
	NONE,
	ERROR_INST
} instruction;
typedef struct code {/*structure of a code with name ,opcode and funct*/
	char* string;
	opcode op_table;
	funct funct_table;
}code;
static code lookuptable[] = {/*table of structures of a code with name ,opcode and funct*/
	{"mov", MOV_OP, MOV_FUNCT},{"cmp",CMP_OP, CMP_FUNCT},{"add",ADD_OP, ADD_FUNCT},{"sub",SUB_OP, SUB_FUNCT},{"lea",LEA_OP, LEA_FUNCT},
	{"clr",CLR_OP, CLR_FUNCT},{"not",NOT_OP, NOT_FUNCT},{"inc",INC_OP, INC_FUNCT},{"dec",DEC_OP, DEC_FUNCT},{"jmp",JMP_OP, JMP_FUNCT},
	{"bne",BNE_OP, BNE_FUNCT},{"jsr",JSR_OP, JSR_FUNCT},{"red",RED_OP, RED_FUNCT},{"prn",PRN_OP, PRN_FUNCT},{"rts",RTS_OP, RTS_FUNCT},
	{"stop",STOP_OP, STOP_FUNCT}
};

Cmd cmd_arr[MAX_ARR_LEN];/*commands array*/
Data data_arr[MAX_ARR_LEN];/*data array*/


