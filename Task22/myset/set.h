#include <stdlib.h>
#include <string.h>

#define BYTE_SIZE 8
#define RANGE_BYTES 16 /* (= lenght of range / lenght of byte) */
#define MEMBERS_PER_LINE 16 /* how many set members to print per line at print function */

typedef char set[RANGE_BYTES];
/* each bit represents number between [0...127], and whether is exists in set */

typedef struct sets
{
	char *name;
	set *set;
} sets;

typedef struct cmd
{
	char *name;
	void (*func)(set*, set*, set*);
} cmd;

void print_set(set *set);
void read_set(set *set, char *setMembers);
void union_set(set *set1, set *set2, set *dest);
void intersect_set(set *set1, set *set2, set *dest);
void sub_set(set *set1, set *set2, set *dest);
void symdiff_set(set *set1, set *set2, set *dest);