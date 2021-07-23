#include <stdio.h>
#include <stdlib.h>
#define SIZE 60

enum status {SINGLE_BUFFER, LINKED_LIST};

/* Stracture that supports both data structure types */
struct Data{
	char *buffer;
	struct Data *next;	/* relevant only for linked list */
	int size;			/* relevant only for single buffer */
};

typedef struct Data Data;

int readText(int type, Data *data);
void printText(int type, Data *data);
void freeMem(int type, Data *data);
int expandSingleBuffer(Data *data);


int main ()
{
	int type; /* data stracture type for user to pick */
	int errorCode = 0;
	Data *data;

	do
	{
		printf("Please choose data scrtucture method:\n");
		printf("0 for single buffer\n");
		printf("1 for linked list\n");
		scanf("%d",&type);

		if(type!=SINGLE_BUFFER && type!=LINKED_LIST)
			printf("Plese enter only 0 or 1!\n\n");

	}while(type!=SINGLE_BUFFER && type!=LINKED_LIST);
	
/*	create first data block, with a 'SIZE' long buffer */
	data = (Data*) calloc(1,sizeof(Data));
	data->buffer = (char*) calloc(SIZE,sizeof(char));
	if (!data->buffer)
	{
		printf("Error! failed to allocate memory!\n");
		return 1;
	}

	printf("Please enter your text:\n");
	errorCode = readText(type, data);

	printf("\nProcced text:\n");
	printText(type, data);
	freeMem(type, data);

	if (errorCode != 0)
	{
		printf("\nError! failed to expand memory!\n");
		return 2;
	}

	return 0;
}




int readText(int type, Data *data)
{	/* The function is using the data stracture according to the user's pick */
	int c;
	int i=0; /* Running index in buffer */
	/* relevant to linked list case: */
	Data *currLink;
	Data *newLink;
	currLink = data;

	switch (type)
	{
		case SINGLE_BUFFER:
		/* Single buffer case, we are using only one data block.
		when block's buffer run out of space, we expand it */

			data->size = SIZE;
			while ((c=getchar()) != EOF)
			{
				if (c!='\n')
				{

					if (i >= (data->size))	/* went out of buffer, expanding buffer */
						if (expandSingleBuffer(data) == 1)
							return 1;

					*(data->buffer+i) = (char)c;
					i++;
				}
			}

			break;

		case LINKED_LIST:
		/* Linked list case, each data block has 'SIZE' long buffer.
		when current block's buffer run out of space, we create a new data block */

			while ((c=getchar()) != EOF)
			{
				if (c!='\n')
				{
					if (i>=SIZE)
					{ /* current link's buffer is full, create new link */
						newLink = (Data*) calloc(1,sizeof(Data));
						newLink->buffer = (char*)calloc(SIZE,sizeof(char));
						if (newLink == NULL || newLink->buffer == NULL)
							return 1;
						currLink->next = newLink;
						currLink = newLink;
						/* new link with new buffer created.
						currLink is now pointing on new link */
						i=0;
					}

					*(currLink->buffer+i) = (char)c;
					i++;
				}
			}

			break;
	} /* swtich end */

	return 0;
}


void printText(int type, Data *data)
{	/* The function is using the data stracture according to the user's pick
	'dataExist' flag is true as long we still have unprinted characters  */
	int i = 0; /* Running index in buffer */
	int dataExist = (*(data->buffer)!=0); /* checks if value exist at first cell in buffer */
	switch (type)
	{
		case SINGLE_BUFFER:
		/* runs on our single buffer until reaching NULL value in buffer or end of buffer */
			while (dataExist)
			{
				putchar(*(data->buffer + i));
				i++;
				if (i % SIZE == 0)
					printf("\n");

				dataExist = (i < data->size && *(data->buffer+i) != 0);
			}
			break;

		case LINKED_LIST:
		/* runs on each block's buffer until reaching NULL in buffer or end of last link's buffer */
			while (dataExist)
			{
				putchar(*(data->buffer+i));

				i++;
				if (i>=SIZE)
				{ /* end of current buffer */
					if (data->next == NULL)
				 		dataExist = 0;
				 	else
				 	{ /* move to next link */
				 		data = data->next;
				 		i=0;
				 	}
				 	printf("\n");
				}

				if (*(data->buffer+i)==0)
					dataExist = 0;
			}

			break;
	} /* swtich end */
}

void freeMem(int type, Data *data)
{
	/* free each link's buffer and then link's data itself */
	Data *nextLink;

	while (data)
	{
		free(data->buffer);
		nextLink = data->next;
		free (data);
		data = nextLink;
	}
}


int expandSingleBuffer(Data *data)
{
	/* expanding buffer, returns 0 on success and 1 on failure */
	char *temp;
	data->size += SIZE;
	temp = (char*)realloc(data->buffer,(data->size) * sizeof(char));
	if (temp == NULL)
		return 1;
	data->buffer = temp;

	return 0;
}