//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 4
/*
Write a simple C-Language function called void crypt(char * message, int length, char * key) that
accepts a character pointer to the message to be encrypted and a character pointer to the encryption key.
The function, upon return, will have modified the message in-place.
Write a main program that will prompt for and accept a message as input from the user and then prompt for
and accept an encryption key input from the user. The program will then encrypt the message using the
crypt function, display the encrypted result on the screen, decrypt the message, and display the decrypted
result. Note that the decrypted result should be the same as the original message that was entered.
int main( )
{
 //code to allow input of message string.
//code to allow input of key string.
//code to encrypt message.
//code to display encrypted message.
//code to decrypt message.
//code to display decrypted message.
}
void crypt( char * message, int length, char * key)
{
 // code to encrypt the message using XOR with the key string.
}
Your program should compile and execute without any warnings or errors
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int key_length = 0;

int main()
{
    char message[100];
    char key[100];
    int message_length = 0;
    void crypt(char * message, int length, char * key);

    printf("Enter a word you would like to be encrypted (Less than 100 characters):\n");
    fgets(message,100,stdin);
    message_length = (strlen(message)-1);//Keeping the \0 at the end

    printf("Enter a word you would like to use as the encryption key:\n");
    fgets(key,100,stdin);
    key_length =  (strlen(key)-1);// keeping the \0 at the end

    printf("\nThis message is %d characters long. \n", (message_length) );
    printf("The encryption key is %d characters long. \n", (key_length) );

    crypt(message,message_length,key);

    printf("\nMessage Array when encrypted:\n");
    printf(message);

    crypt(message,message_length,key);

    printf("\n\nMessage Array when decrypted:\n");
    printf(message);
}

void crypt(char * message, int message_length, char * key)
{
    int j = 0, i;
    int encrypt = 0;
    for(i=0; i < message_length; i++,j++)
    {
        encrypt = (message[i]^=key[j]);

        message[i] = encrypt;//printf("%d, ", encrypt);//chanGing to rewrite the message[]

        if(j == (key_length-1))// the -1 is because the fget procedure always has the two elements: \n, \0 at the end of the array. The \0 was taken off earlier
        {
            j = -1;
        }
    }
}
