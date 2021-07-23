#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "set.h"
#include "myset.h"

/*
This program is a pocket calculator that performs actions on sets.
The program reads commands from user, validates them, and perform them.
*/

int main()
{
	char command[COMMAND_LENGTH] = {0};
	char operands[OPERANDS_LENGTH] = {0};
	char c;
	int running=1;
	set SETA={0},SETB={0},SETC={0},SETD={0},SETE={0},SETF={0};
	sets allSets[] ={
		{"SETA",NULL},
		{"SETB",NULL},
		{"SETC",NULL},
		{"SETD",NULL},
		{"SETE",NULL},
		{"SETF",NULL},
		{"#",NULL}
	};

	allSets[0].set = &SETA;
	allSets[1].set = &SETB;
	allSets[2].set = &SETC;
	allSets[3].set = &SETD;
	allSets[4].set = &SETE;
	allSets[5].set = &SETF;
	
	


	printf("Welcome to Barr's interactive pocket calculator!\n\n");
	
	while(running)
	{
		printf("Enter command:\n");
		if (scanf("%s",command) != 1)
		{
			printf("OH SNAP! the program terminated not via 'stop' command!\n");
			return 1;
		}
		fgets(operands, OPERANDS_LENGTH, stdin);
		printf("You entered:\n%s%s",command,operands);

		if (strcmp(command,"stop") == 0)
			running = 0;
		else if (operands[strlen(operands)-1] != '\n')
		{/* fgets recieved input longer than its buffer */
			printf("\nintput too long!\n");
			while ((c=(getchar())) != '\n')
				if (c == EOF)
				{
					printf("OH SNAP! the program terminated not via 'stop' command!\n");
					return 2;
				}
		}		
		else
			launchCommand(command, operands, allSets);

	}



	return 0;
}

void launchCommand(char *command, char *operands, sets *allSets)
{	/* validate user's input and print error massage or lanuches relevant command */

	int operandQuantity, setNum;
	int i;
	set *set1, *set2, *set3;
	char *opr;
	char setMembers[OPERANDS_LENGTH] = {0};

	cmd threeSetsFuncs[] = {
		{"union_set",union_set},
		{"intersect_set",intersect_set},
		{"sub_set",sub_set},
		{"symdiff_set",symdiff_set},
		{"not_valid", NULL}
	};


	if (strcmp(command,"print_set") == 0)
		operandQuantity = 1;
	else if (strcmp(command,"read_set") == 0)
		operandQuantity = 2;
	else
	{
		i=0;
		for (i=0; threeSetsFuncs[i].func!=NULL; i++)
		{
			if (strcmp(command,threeSetsFuncs[i].name) == 0)
			{
				operandQuantity = 3;
				/* threeSetsFuncs[i].func is now the desired function */
				break;
			}
		}

		if (threeSetsFuncs[i].func == NULL)
		{
			printf("Undefined command name!\n");
			return;
		}
	}


	removeWhites(operands);
	if (validateCommas(operands))
		return;

	opr = strtok(operands,","); /* Get first operand */

	if (opr == NULL)
	{
		printf("Missing parameter!\n");
		return;
	}
	setNum = setNameToIndex(opr, allSets);
	if (setNum == -1)
	{
		printf("Undefined set name!\n");
		return;
	}
	set1 = allSets[setNum].set;


	switch (operandQuantity)
	{
		case 1:
		/* print set is the only command with 1 operand */
			if (strtok(NULL,",") != NULL) 
			{	/* make sure 2nd operand doesnt exist */
				printf("Extraneous text after end of command\n");
				return;
			}

			print_set(set1);
			break;

		case 2:
		/*	read set is the only command with 2 operands
			next operands should be list of set members */

			/* extracting all set members from operand string */
			strcpy(setMembers,operands+strlen(opr)+1);
			if (setMembers == NULL)
			{
				printf("Missing set members after read_set command!\n");
				return;
			}

			/* validate set members by strtok on operands */
			if (validateSetMembers(operands+strlen(opr)+1))
				return;

			read_set(set1,setMembers);
			break;


		case 3:
		/*	all commands with 3 operands are in threeSetsFuncs and threeSetsFuncs[i].func
			is the desired function. Next two opreands should be 2nd and 3rd set */
			opr = strtok(NULL,","); /* Get second operand */
			if (opr == NULL)
			{
				printf("Missing parameter!\n");
				return;
			}
			setNum = setNameToIndex(opr, allSets);
			if (setNum == -1)
			{
				printf("Undefined set name!\n");
				return;
			}
			set2 = allSets[setNum].set;

			opr = strtok(NULL,","); /* Get third operand */
			if (opr == NULL)
			{
				printf("Missing parameter!\n");
				return;
			}
			setNum = setNameToIndex(opr, allSets);
			if (setNum == -1)
			{
				printf("Undefined set name!\n");
				return;
			}
			set3 = allSets[setNum].set;

			if (strtok(NULL,",") != NULL) 
			{	/* make sure 4th operand doesnt exist */
				printf("Extraneous text after end of command\n");
				return;
			}

			(*threeSetsFuncs[i].func)(set1, set2, set3);
			break;

	}

}


int setNameToIndex(char *setName, sets *allSets)
{/* returns set's index in allSet, or -1 if name doesn't exist*/
	int i;

	for (i=0; allSets[i].set != NULL; i++)
		if(strcmp(setName,allSets[i].name)==0)
			return i;

	return -1;
}

void removeWhites(char *operands)
{/*	removes white notes from string.
	including \n at the end of string, which exist because string came from fgets */
	int i,j;

	for (i=0,j=0; operands[j]!=0;j++)
	{
		if (!isspace(operands[j]))
		{
			operands[i] = operands[j];
			i++;
		}
		operands[i] = 0;
	}
}

int validateCommas(char *operands)
{/* validate there are no extra commas. prints error and return !0 if validation fails*/
	enum status{COMMA,NOTCOMMA} lastRead;
	int i;

	if (operands[0] == ',')
	{
		printf("Illegal comma after command!\n");
		return 1;
	}
	else
		lastRead = NOTCOMMA;

	for (i=1; operands[i]!=0; i++)
	{
		if (operands[i] == ',')
			if (lastRead == COMMA)
			{
				printf("Multiple consecutive commas!\n");
				return 2;
			}
			else
				lastRead = COMMA;

		else /* current character is not ',' */
			lastRead = NOTCOMMA;
	}

	if (lastRead == COMMA)
	{
		printf("Illegal comma at end of input!\n");
		return 3;
	}

	return 0;
}

int validateSetMembers(char *setMembers)
{/*	make sure all set members are integers, not exceeding the range, and terminated correctly */
	char *curr, *p;
	int foundLastMember=0;
	long int num;

	curr = strtok(setMembers,",");
	while (curr != NULL)
	{
		if (foundLastMember)
		{
			printf("List of set members not terminated correctly!\n");
			return 1;
		}

		num = strtol(curr,&p,10);

		if (strcmp(curr,"-1") == 0)
		{
			foundLastMember = 1;
			curr += 1;
		}
		else if ((num == 0 && strcmp(curr,"0")!=0) || p[0]!=0)
		{
			printf("Invalid set member - not an integer!\n");
			return 2;
		}
		else if (num < 0 || num >= RANGE_BYTES*BYTE_SIZE)
		{
			printf("Invalid set member - value out of range!\n");
			return 3;
		}

		curr = strtok(NULL,",");

	}
	if (!foundLastMember)
	{
		printf("List of set members not terminated correctly!\n");
		return 4;
	}


	return 0;
}