//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Midterm 14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    void cryptogramify(char * message);
    char message[56];

    //printf("Enter the Secret Code to be encoded! (less than 100 characters): ");
    //fgets(message,100,stdin);
    message[0]= 'D';
    message[1]= 'S';
    message[2]= 'V';
    message[3]= 'M';
    message[4]= ' ';
    message[5]= 'B';
    message[6]= 'L';
    message[7]= 'F';
    message[8]= ' ';
    message[9]= 'X';
    message[10]= 'L';
    message[11]= 'N';
    message[12]= 'V';
    message[13]= ' ';
    message[14]= 'G';
    message[15]= 'L';
    message[16]= ' ';
    message[17]= 'Z';
    message[18]= ' ';
    message[19]= 'U';
    message[20]= 'L';
    message[21]= 'I';
    message[22]= 'P';
    message[23]= ' ';
    message[24]= 'R';
    message[25]= 'M';
    message[26]= ' ';
    message[27]= 'G';
    message[28]= 'S';
    message[29]= 'V';
    message[30]= ' ';
    message[31]= 'I';
    message[32]= 'L';
    message[33]= 'Z';
    message[34]= 'W';
    message[35]= ',';
    message[36]= ' ';
    message[37]= 'G';
    message[38]= 'Z';
    message[39]= 'P';
    message[40]= 'V';
    message[41]= ' ';
    message[42]= 'R';
    message[43]= 'G';
    message[44]= '.';
    message[45]= ' ';
    message[46]= '-';
    message[47]= 'B';
    message[48]= 'L';
    message[49]= 'T';
    message[50]= 'R';
    message[51]= ' ';
    message[52]= 'Y';
    message[53]= 'V';
    message[54]= 'I';
    message[55]= 'I';
    message[56]= 'Z';
    cryptogramify(message);
    printf("Your Decoded Message:\n");
    printf(message);
    return 0;
}

void cryptogramify(char * message)
{
    for(; message[0] != '\0'; message++)
    {
        switch(message[0])
        {
            case 'a': message[0] = 'z'; break;
            case 'b': message[0] = 'y'; break;
            case 'c': message[0] = 'x'; break;
            case 'd': message[0] = 'w'; break;
            case 'e': message[0] = 'v'; break;
            case 'f': message[0] = 'u'; break;
            case 'g': message[0] = 't'; break;
            case 'h': message[0] = 's'; break;
            case 'i': message[0] = 'r'; break;
            case 'j': message[0] = 'q'; break;
            case 'k': message[0] = 'p'; break;
            case 'l': message[0] = 'o'; break;
            case 'm': message[0] = 'n'; break;
            case 'n': message[0] = 'm'; break;
            case 'o': message[0] = 'l'; break;
            case 'p': message[0] = 'k'; break;
            case 'q': message[0] = 'j'; break;
            case 'r': message[0] = 'i'; break;
            case 's': message[0] = 'h'; break;
            case 't': message[0] = 'g'; break;
            case 'u': message[0] = 'f'; break;
            case 'v': message[0] = 'e'; break;
            case 'w': message[0] = 'd'; break;
            case 'x': message[0] = 'c'; break;
            case 'y': message[0] = 'b'; break;
            case 'z': message[0] = 'a'; break;
//----------------------------------------------------------------------------------------------
            case 'A': message[0] = 'Z'; break;
            case 'B': message[0] = 'Y'; break;
            case 'C': message[0] = 'X'; break;
            case 'D': message[0] = 'W'; break;
            case 'E': message[0] = 'V'; break;
            case 'F': message[0] = 'U'; break;
            case 'G': message[0] = 'T'; break;
            case 'H': message[0] = 'S'; break;
            case 'I': message[0] = 'R'; break;
            case 'J': message[0] = 'Q'; break;
            case 'K': message[0] = 'P'; break;
            case 'L': message[0] = 'O'; break;
            case 'M': message[0] = 'N'; break;
            case 'N': message[0] = 'M'; break;
            case 'O': message[0] = 'L'; break;
            case 'P': message[0] = 'K'; break;
            case 'Q': message[0] = 'J'; break;
            case 'R': message[0] = 'I'; break;
            case 'S': message[0] = 'H'; break;
            case 'T': message[0] = 'G'; break;
            case 'U': message[0] = 'F'; break;
            case 'V': message[0] = 'E'; break;
            case 'W': message[0] = 'D'; break;
            case 'X': message[0] = 'C'; break;
            case 'Y': message[0] = 'B'; break;
            case 'Z': message[0] = 'A'; break;
        }
    }
}
