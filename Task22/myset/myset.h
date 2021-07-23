#define COMMAND_LENGTH 15
#define OPERANDS_LENGTH 65


void removeWhites(char *operands);
int validateCommas(char *operands);
int validateSetMembers(char *setMembers);
void launchCommand(char *command, char *operands, sets *allSets);
int setNameToIndex(char *setName, sets *allSets);