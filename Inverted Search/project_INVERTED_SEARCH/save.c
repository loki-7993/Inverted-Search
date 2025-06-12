#include "header.h"

int save_database(table *arr, char *file_name)
{
    FILE *fptr = fopen(file_name, "w"); // Open the file to write the database
    if (fptr == NULL)
    {
        printf("Error: Could not open file to save.\n"); // If file can't be opened, show error and return failure
        return FAILURE;
    }

    for (int i = 0; i < 27; i++) // Go through each index in the table (0 to 26)
    {
        word *temp_main = arr[i].main_link; // Get the first word at this index

        while (temp_main != NULL) // Go through all words at this index
        {
            // Write index, word, and file count
            fprintf(fptr, "#%d;%s;%d;", i, temp_main->word, temp_main->filecount);

            // Traverse the file sublink list
            file *temp_sub = temp_main->sub_link;
            while (temp_sub != NULL)
            {
                fprintf(fptr, "%s;%d;", temp_sub->filename, temp_sub->wordcount);
                temp_sub = temp_sub->sub_link; // Move to next file
            }

            //fprintf(fptr, "\n"); // new word on a new line
            fprintf(fptr, "#\n");
            temp_main = temp_main->main_link; // Move to the next word
        }
    }

    //fprintf(fptr, "#"); // mark end of file
    fclose(fptr); // Close the file after saving everything
    return SUCCESS;
}




