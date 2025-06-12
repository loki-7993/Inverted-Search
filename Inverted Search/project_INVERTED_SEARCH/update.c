#include"header.h"

int update_database(table *arr)
{
    char file_name[20];
    printf("Enter file name to backup: ");
    scanf("%s", file_name);

    int res = backup_validate(file_name);
    if (res == FAILURE)
        return FAILURE;
    else if (res == DATA_NOT_FOUND)
        return DATA_NOT_FOUND;

    FILE *fptr = fopen(file_name, "r");
    if (!fptr)
        return FAILURE;

    char str[50];
    while (fscanf(fptr, "%s", str) != EOF)
    {
        int index = atoi(strtok(str, "#;"));

        word *mnew = malloc(sizeof(word));
        if (mnew == NULL)
            return FAILURE;

        strcpy(mnew->word, strtok(NULL, "#;"));
        mnew->filecount = atoi(strtok(NULL, "#;"));
        mnew->main_link = NULL;
        mnew->sub_link = NULL;

        if (arr[index].main_link == NULL)
        {
            arr[index].main_link = mnew;
        }
        else
        {
            word *mtemp = arr[index].main_link;
            while (mtemp->main_link != NULL)
            {
                mtemp = mtemp->main_link;
            }
            mtemp->main_link = mnew;
        }

        for (int i = 1; i <= mnew->filecount; i++)
        {
            file *snew = malloc(sizeof(file));
            if (!snew)
                return FAILURE;

            strcpy(snew->filename, strtok(NULL, "#;"));
            snew->wordcount = atoi(strtok(NULL, "#;"));
            snew->sub_link = NULL;

            if (i == 1)
            {
                mnew->sub_link = snew;
            }
            else
            {
                file *stemp = mnew->sub_link;
                while(stemp->sub_link != NULL)
                {
                    stemp = stemp->sub_link;
                }
                stemp->sub_link = snew;
            }
        }
    }

    fclose(fptr);
    return SUCCESS;
}

/*int update_database(table *arr)
{
    char file_name[20];
    printf("Enter file name to backup: ");
    scanf("%s", file_name);

    // Validate the file before proceeding
    int res = backup_validate(file_name);
    if (res == FAILURE)
        return FAILURE;
    else if (res == DATA_NOT_FOUND)
        return DATA_NOT_FOUND;

    FILE *fptr = fopen(file_name, "r");
    if (!fptr)
        return FAILURE;

    char line[100];
    while (fscanf(fptr, "%s", line) != EOF)
    {
        // Tokenize the line
        int index = atoi(strtok(line, "#;")); // Get index
        char *word_str = strtok(NULL, "#;");
        int filecount = atoi(strtok(NULL, "#;"));

        // Create new main node
        word *mnew = malloc(sizeof(word));
        if (!mnew)
            return FAILURE;

        strcpy(mnew->word, word_str);
        mnew->filecount = filecount;
        mnew->main_link = NULL;
        mnew->sub_link = NULL;

        // Insert main node into hash table
        if (arr[index].main_link == NULL)
        {
            arr[index].main_link = mnew;
        }
        else
        {
            word *temp = arr[index].main_link;
            while (temp->main_link)
                temp = temp->main_link;
            temp->main_link = mnew;
        }
        printf("Inserting word: %s at index %d\n", mnew->word, index);

        // Create subnodes (file nodes)
        for (int i = 0; i < filecount; i++)
        {
            char *filename = strtok(NULL, "#;");
            int wordcount = atoi(strtok(NULL, "#;"));

            file *snew = malloc(sizeof(file));
            if (!snew)
                return FAILURE;

            strcpy(snew->filename, filename);
            snew->wordcount = wordcount;
            snew->sub_link = NULL;

            if (i == 0)
            {
                mnew->sub_link = snew;
            }
            else
            {
                file *ftemp = mnew->sub_link;
                while (ftemp->sub_link)
                    ftemp = ftemp->sub_link;
                ftemp->sub_link = snew;
            }
             printf("   -> Linked to file: %s with count: %d\n", snew->filename, snew->wordcount);
        }
    }

    fclose(fptr);
    return SUCCESS;
}*/

int backup_validate(char *files)
{
    // Check if file ends with .txt
    if(strstr(files, ".txt") == NULL)
    {

	    return FAILURE;
    }
    FILE *fptr = fopen( files ,"r" );
    if(fptr == NULL)
    {

	    return DATA_NOT_FOUND;
    }

    fseek(fptr, 0, SEEK_END);

    if(ftell(fptr) != 0)
    {
	char ch;
	fseek(fptr, 0 , SEEK_SET);
	if((ch = fgetc(fptr)) == '#')
	{
	    fseek(fptr, -2 , SEEK_END);
	    ch = fgetc(fptr);
	    if(ch != '#')
	    {
		return DATA_NOT_FOUND;
	    }
	}
	else
	{
	    return DATA_NOT_FOUND;
	}
	fclose(fptr);
    }
    else
    {
	printf("ERROR: File is empty\n");
	return FAILURE;
    }
}
