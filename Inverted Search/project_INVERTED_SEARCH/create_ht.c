#include<stdio.h>
#include "header.h"

void create_HT(table *arr, int size)
{
    // Loop through each index of the hash table
    for(int i=0;i<size;i++)
    {
        arr[i].key=i;             // Assign key as the index (0 to size-1)
        arr[i].main_link= NULL;   // Initialize the linked list head pointer to NULL
    }
}