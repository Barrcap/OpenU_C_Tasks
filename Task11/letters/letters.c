#include <stdio.h>
#include <ctype.h>

/*
The program examines each character from the standart input until reaching EOF
The program is keeping track whether the currnt char is at a beginning of a sentance, at a middle of a sentane, or inside a quotation marks, and deals with the current character accordingly.
*/

enum status {SB, SEN, QM};
/* SB - sentance beginning, SEN - sentance, QM - quotation marks */

int main () {

 int c;
 int state = SB;

 printf("Please enter your FRESHEST text:\n\n");

 while ((c=getchar()) != EOF) {

   switch (state) {

	case SB: /* Beginning of sentance */
	 if (islower(c))
		c = toupper(c);
	 if (!isspace(c))
		state = SEN;
	 if (c == '\"')
		state = QM;
	 break;

	case QM: /* Inside quotation marks */
	 if (islower(c))
		c = toupper(c);
	 if (c == '\"')
		state = SEN;
	 break;

	case SEN: /* Inside a sentance */
	 if (isupper(c))
		c = tolower(c);
	 if (c == '\"')
		state = QM;
	 if (c == '.')
		state = SB;
	 break;
   }

   if (!isdigit(c))
	putchar(c);
 }

 return 0;
}
