#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

int search_database(table *arr, char *string)
{
    // Convert input word to lowercase to match database
    char lower_word[100];
    strcpy(lower_word, string);
    for (int i = 0; lower_word[i]; i++)
        lower_word[i] = tolower(lower_word[i]);

    int i;
    // Find the index based on the first character of the word
    if (isalpha(lower_word[0]))
        i = lower_word[0] - 'a';
    else
        i = 26; // For non-alphabet characters

    if (arr[i].main_link == NULL) // Check if any word exists at this index
    {
        return DATA_NOT_FOUND; // No word found
    }

    word *main_temp = arr[i].main_link;  // Traverse the linked list to search for the word
    while (main_temp != NULL)
    {
        // If word is found
        if (strcmp(lower_word, main_temp->word) == 0)
        {
            // Print how many files contain this word
            printf("The given word '%s' is present in %d file(s):\n", main_temp->word, main_temp->filecount);

            // Print filename and word count for each file
            file *sub_temp = main_temp->sub_link;
            printf("Filename\t\tWordcount\n");
			printf("-------------------------------------------\n");
            while (sub_temp)
            {
                printf("%-15s\t\t%d\n", sub_temp->filename, sub_temp->wordcount);
                sub_temp = sub_temp->sub_link;
                printf("-------------------------------------------\n");
            }

            return SUCCESS; // Word found
        }
        main_temp = main_temp->main_link;  // Move to the next word in the list
    }

    return DATA_NOT_FOUND; // Word not found in any file
}
