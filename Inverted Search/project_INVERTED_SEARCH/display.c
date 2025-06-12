#include <stdio.h>
#include "header.h"

int display_database(table *arr, int size)
{
    printf("----------------------------------------------------------------------\n");
    printf("Index\t\tWord\t\tFileCount\tFilename\tWordCount\n");
    printf("----------------------------------------------------------------------\n");

    // Loop through each index of the table
    for (int i = 0; i < size; i++)
    {
        word *main_temp = arr[i].main_link;  // Pointer to the first word at current index
        while (main_temp != NULL)   // Go through all words in the list
        {
            // Pointer to the file list for the current word
            file *sub_temp = main_temp->sub_link;
            int first = 1;  // Flag to print word details only once

            while (sub_temp != NULL) // Go through all files for the current word
            {
                if (first)
                {
                    // Print full details for the first file entry
                    printf("[%d]\t\t%-15s\t%-10d\t%-15s\t%d\n",
                    i, main_temp->word, main_temp->filecount, sub_temp->filename, sub_temp->wordcount);
                    first = 0;  // Set flag to false after first print
                }
                else
                {
                    // For remaining files, only print filename and word count
                    printf("\t\t\t\t\t\t%-15s\t%d\n",
                    sub_temp->filename, sub_temp->wordcount);
                }

                sub_temp = sub_temp->sub_link; // Move to the next file node
            }

            main_temp = main_temp->main_link;  // Move to the next word in the list
            printf("----------------------------------------------------------------------\n");

        }
    }

    return SUCCESS; // Return success after displaying everything
}

