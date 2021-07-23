#include <stdio.h>
#include "set.h"


void read_set(set *set, char *setMembers)
{/*	recieves a valid stirng with set members and put them inside given set */
	int i;
	char *curr;
	int num;
	char mask;

	for (i=0;i<RANGE_BYTES;i++)
		(*set)[i] = 0;

	curr = strtok(setMembers,","); /* get first member */
	while (curr != NULL)
	{
		num = atoi(curr);
		if (num != -1)
		{
			mask = 1<<(num % BYTE_SIZE);
			(*set)[num/BYTE_SIZE] |= mask;
		}
		curr = strtok(NULL,","); /* get next member*/
	}
}

void print_set(set *set)
{/*	printing all set members in given set */
	int i,counter=0, addNewLine=0;
	char mask=0;

	for (i=0; i<RANGE_BYTES; i++)
		mask |= (*set)[i];

	if (mask == 0)
	{
		printf("The set is empty!\n");
		return;
	}

	printf("The set contains the members:\n");

	for (i=0; i<RANGE_BYTES*BYTE_SIZE; i++)
	{
		addNewLine = 0;
		mask = 1<<(i % BYTE_SIZE);
		if (( (*set)[i/BYTE_SIZE] & mask) != 0)
		{
			printf("%d ",i);
			counter ++;
			if (counter % MEMBERS_PER_LINE == 0)
				addNewLine = 1;
		}

		if (addNewLine)
			printf("\n");
	}

	if (addNewLine == 0)
		printf("\n");
}

void union_set(set *set1, set *set2, set *dest)
{/*	uniting set1 and set2, puts the result in dest */
	int i;

	for (i=0;i<RANGE_BYTES;i++)
		(*dest)[i] = (*set1)[i] | (*set2)[i];
}

void intersect_set(set *set1, set *set2, set *dest)
{/*	intersecting set1 and set2, puts the result in dest */
	int i;

	for (i=0;i<RANGE_BYTES;i++)
		(*dest)[i] = (*set1)[i] & (*set2)[i];
}

void sub_set(set *set1, set *set2, set *dest)
{/*	subtracting set2 from set1, puts the result in dest */
	int i;

	for (i=0;i<RANGE_BYTES;i++)
		(*dest)[i] = (*set1)[i] & ~((*set2)[i]);
}

void symdiff_set(set *set1, set *set2, set *dest)
{/*	calcilating symetric difference between set1 and set2, puts the result in dest */
	int i;

	for (i=0;i<RANGE_BYTES;i++)
		(*dest)[i] = ((*set1)[i] | (*set2)[i]) & ~((*set1)[i] & (*set2)[i]);
}