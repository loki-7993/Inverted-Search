#include<stdio.h>
#include<string.h>
#include "header.h"

int read_and_validate(int argc,char *argv[],node **head)
{
    // Iterate through each argument starting from index 1 (excluding program name)
    for(int i=1;i<argc;i++)
    {
        char * ptr=strstr(argv[i],".txt"); // Check if the current argument contains ".txt"
        if(ptr== NULL)
        {
            printf("The file does not present");
            return FAILURE; // If .txt is not found, return failure
        }
        if(strcmp(ptr,".txt")==SUCCESS)
        {
            FILE *fptr=fopen(argv[i],"r"); // Try to open the file in read mode
            if(fptr == NULL)
            {
                printf("File does not exists\n");
                return FAILURE; // If file opening fails, return failure
            }
            else
            {
                // Move file pointer to end to check if file is empty
                fseek(fptr,0,SEEK_END);
                if(!ftell(fptr))
                {
                    printf("File is empty\n");
                    return FAILURE;
                } 
                else
                {
                    // Check for duplicate file names in previous arguments
                    int dup=0; 
                    for(int j=0;j<i;j++)
                    {
                        if(strcmp(argv[j],argv[i])==0)
                        {
                            dup=1;
                            printf("Duplicate file name found\n");
                            break;

                        }
                    }
                    if(!dup) // If it's not a duplicate, add it to the linked list
                    {
                        node * new = malloc(sizeof(node)); // Allocate memory for new node
                        strcpy(new->filename,argv[i]); // Copy the filename into the node
                        new->link = NULL;
                        if(*head == NULL) // Insert the node at the end of the linked list
                        {
                             *head = new; // First node in the list
                        }
                        else{
                        node *temp= *head;
                        while(temp->link != NULL)
                        {   
                          temp=temp->link; 
                        }
                        
                        if(new == NULL)
                        {
                            return FAILURE; // Check for memory allocation failure
                        }
                        temp->link=new; // Append to the list
                        }
                    }
                }
            }
        }
        else
        {
            // If file extension is not valid, return failure
            printf("The file does not contain .txt extension\n");
            return FAILURE;


        }
    }
    return SUCCESS; // All validations passed
}

