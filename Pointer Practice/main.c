#include <stdio.h>
#include <stdlib.h>

int main()
{

    int var_array[10] = {12,15,22,37,45,52,58,87,89,101};
    int index;

    printf("1. First array value: %d \n", var_array[0]);

    printf("2. All values in the array:");
        for(index = 0; index < 10; index++)
        {
            printf(" %d", var_array[index]);
        }
        printf("\n\n");

//---------------------------------------------------------//

    int var_number = 5;
    int * pointer_var;
    pointer_var = &var_number;

    printf("3. The integer variable: %d \n", var_number);
    printf("4. The pointer variable: %p \n", pointer_var); //This is the memory location of of the integer variable
    printf("5. The dereferenced pointer variable: %d \n\n", *pointer_var); //this is the value at the memory address held by the pointer variable

    printf("5. The dereferenced pointer variable after adding one: %d \n", *pointer_var + 1); //adds one to the value of the memory location pointed at by the pointer variable
    printf("6. The pointer variable after adding one: %p \n\n", pointer_var + 1); //adds one to the memory location of the pointer variable (compare to #4)

//---------------------------------------------------------//

    printf("7. The third value in the array by calling it from the array: %d \n", var_array[2]); //calling 3rd value from array
    printf("8. The third value in the array using pointer arithmetic: %d \n\n", *(var_array+2)); //this is the value of the memory location 2 spaces dowb from the original memory location

//---------------------------------------------------------//

    pointer_var = var_array; //making the pointer point to the array

    printf("9. The value of the dereferenced array after adding three: %d \n", *(var_array +3)); //the value of the original memory location + 3. this is the same as var_array[3]
    printf("10. The value of the array using pointer arithmetic: %d \n\n", *(pointer_var +3)); //the value of the original memory location + 3. this is the same as pointer_var[3]

    printf("11. The first value in the array: %d \n", pointer_var[0]); //the value from the array at the memory location pointed to by pointer variable
    printf("12. The value of the dereferenced pointer variable: %d \n\n", *pointer_var); //the value of the memory location pointed to by pointer variable

    //-----

    pointer_var++; //moving the pointer to the next space in memory

    printf("13. The value of the dereferenced pointer variable after incrementing it: %d \n", pointer_var[0]); //the value of the array pointed to by pointer variable, after incrementing the pointer variable
    printf("14. The value before the dereferenced pointer variable in memory: %d \n\n", pointer_var[-1]); //the first value of the array which is now before the value pointed to by pointer variable

    //-----

    printf("15. The value of the dereferenced pointer variable: %d \n", *pointer_var); // the value of the memory location being pointed to by the pointer variable

    *pointer_var = *(pointer_var + 1); //the value of the memory location becomes the value at the memory location after the current memory location

    printf("16. The same memory location's value after being changed to the value of the next memory location: %d \n", *pointer_var); // the same value incremented
    printf("17. All values in the array after changes:");
        for(index = 0; index < 10; index++)
        {
            printf(" %d", var_array[index]);
        }
        printf("\n\n");

//---------------------------------------------------------//

     printf("18. The size of the array: %ld \n", sizeof var_array); //size in bytes of the entire array
     printf("19. The size of the pointer variable: %ld \n", sizeof pointer_var); //size in bytes of pointer variable (holds an int)
     printf("20. The size of the dereferenced array: %ld \n", sizeof *var_array); //size in bytes of the first value of the array
     printf("21. The size of the dereferenced pointer variable: %ld \n", sizeof *pointer_var); //size in bytes of the value of the memory location pointed at by the array


}
