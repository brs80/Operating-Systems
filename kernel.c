/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:____Bradley Snyder__________________ Date:____2/4/19____        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.01, Spring 2018.             */

void handleInterrupt21(int,int,int,int);
void printString(char* string);
void readString(char* buffer);
void writeInt(int);
void readInt(int *);
void printLogo(); 

void main() 
{
   makeInterrupt21();
   printLogo();
   interrupt(33,0,"Hello world from Brad.\r\n\0",1,0); 
   while(1);
}

void printString(char* string, int x) {
	int index = 0; 
	char c = string[index];
	if(x == 1) { 
		while(c != 0) { 
			interrupt(0x10, 0xE * 256 + c, 0, 0, 0);
			c = string[++index];
		}
	} else { 
		while(c != 0) { 
			interrupt(0x17, 0xE * 256 + c, 0, 0, 0);
			c = string[++index];
		}
	}
}

void readString(char* string) {
	int index = 0;
	char c = 0;
	while (1) {
		c = interrupt(0x16, 0, 0, 0, 0);
		interrupt(0x10, 0xE * 256 + c, 0, 0, 0);
		if (c == 0xD) break;
		string[index] = c;
		++index;
	}
	string[index] = '\n';
	string[index + 1] = 0;
}

void readInt(int *number) {
  int temp = 0;
  int i = 0;
  char line[6];
  readString(line);
  while (line[i] != '\0') {
    temp = temp * 10 + line[i++] - '0';
  }
  *number = temp;
}

void writeInt(int x) {
  char number[6], *d;
  int q = x, r;
  if (x < 1) {
    d = number;
    *d = 0x30;
    d++;
    *d = 0x0;
    d--;
  } else {
    d = number + 5;
    *d = 0x0;
    d--;
    while (q > 0) {
      r = mod(q, 10);
      q = div(q, 10);
      *d = r + 48;
      d--;
    }
    d++;
  }
  printString(d);
}

int mod(int a, int b) {
  int x = a;
  while (x >= b)
    x = x - b;
  return x;
}

int div(int a, int b) {
  int q = 0;
  while (q * b <= a)
    q++;
  return (q - 1);
}

void handleInterrupt21(int ax, int bx, int cx, int dx) {
    switch(ax) {  
    	/*return;*/ 
        case 0: printString(bx,cx); break; 
        case 1: readString(bx); break; 
        case 13: writeInt(bx,cx); break; 
        case 14: readInt(bx); break; 
        default: printString("General BlackDOS error.\r\n\0");
  }
}
