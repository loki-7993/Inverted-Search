#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

int create_database(node *head, table *arr)
{
    // Loop through each file in the linked list
    while (head != NULL)
    {
        FILE *fptr = fopen(head->filename, "r"); // Open the file for reading
        if (fptr == NULL)
        {
            // If file can't be opened, print error and go to next file
            printf("Error: Cannot open file %s\n", head->filename);
            head = head->link;
            continue;
        }

        char str[100];
        while (fscanf(fptr, "%s", str) != EOF)  // Read each word from the file
        {
            // Convert to lowercase
            for (int i = 0; str[i] != '\0'; i++)
            {
                if (isupper(str[i]))
                {
                    str[i] = tolower(str[i]);
                }
            }

            // Determine index
            int index;
            if (isalpha(str[0]))
            {
                index = tolower(str[0]) - 'a';  // a-z → 0-25
            }
            else
            {
                index = 26;  // For non-alphabetic starting characters
            }


            // Case 1: First word at this index
            if (arr[index].main_link == NULL)
            {
                // Create new word node
                word *new_word = malloc(sizeof(word));
                strcpy(new_word->word, str);
                new_word->filecount = 1;
                new_word->main_link = NULL;

                // Create new file node
                file *new_file = malloc(sizeof(file));
                strcpy(new_file->filename, head->filename);
                new_file->wordcount = 1;
                new_file->sub_link = NULL;

                new_word->sub_link = new_file;
                arr[index].main_link = new_word;
            }
            else
            {
                // Case 2: Word list exists at this index
                // Traverse word list to find if word exists
                word *temp_word = arr[index].main_link;
                word *prev_word = NULL;
                int word_found = 0;

                while (temp_word != NULL)
                {
                    if (strcmp(temp_word->word, str) == 0)
                    {
                        word_found = 1;
                        break;
                    }
                    prev_word = temp_word;
                    temp_word = temp_word->main_link;
                }

                if (word_found)
                {
                    // Word found, now check if filename already exists
                    file *temp_file = temp_word->sub_link;
                    file *prev_file = NULL;
                    int file_found = 0;

                    while (temp_file != NULL)
                    {
                        if (strcmp(temp_file->filename, head->filename) == 0)
                        {
                            // If word exists in this file, increase count
                            temp_file->wordcount++;
                            file_found = 1;
                            break;
                        }
                        prev_file = temp_file;
                        temp_file = temp_file->sub_link;
                    }

                    if (!file_found)
                    {
                        // If file not found, create a new file node
                        file *new_file = malloc(sizeof(file));
                        strcpy(new_file->filename, head->filename);
                        new_file->wordcount = 1;
                        new_file->sub_link = NULL;

                        // Add to end of sub list
                        if (prev_file)
                            prev_file->sub_link = new_file;
                        else
                            temp_word->sub_link = new_file;

                        temp_word->filecount++; // Increase file count for the word
                    }
                }
                else
                {
                    // Word not found: create new word node
                    word *new_word = malloc(sizeof(word));
                    strcpy(new_word->word, str);
                    new_word->filecount = 1;
                    new_word->main_link = NULL;

                    // Create new file node
                    file *new_file = malloc(sizeof(file));
                    strcpy(new_file->filename, head->filename);
                    new_file->wordcount = 1;
                    new_file->sub_link = NULL;

                    new_word->sub_link = new_file;  // Link file to word

                    // Add word to word list
                    if (prev_word)
                        prev_word->main_link = new_word;
                    else
                        arr[index].main_link = new_word;
                }
            }
        }

        fclose(fptr); // Close file and move to next in list
        head = head->link;
    }

    return 0;
}



