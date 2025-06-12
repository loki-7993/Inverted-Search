/* Documentation:
   Name: Lokeswari Talari
   Date: 28-05-2025
   Description: Inverted Search
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

int main(int argc,char *argv[])
{
    int size=27;           // Size of the hash table (likely 26 for a-z + 1 for special/others)
    node* head= NULL;      // Head of the linked list to store file contents
    table arr[size];       // Hash table array of size 27
    create_HT(arr,size);   // Initialize the hash table
    int create_flag=0;
    int update_flag=0;
    int res=0;
    char words[100];      // Buffer to hold user input

    // Check if sufficient arguments are passed
    if(argc <=1)
    {
        printf("INFO:Please enter more than one arguments\n");
    }

     // If arguments are passed, proceed
    if(argc > 1)
    {
         // Validate arguments and read data into linked list
        if(read_and_validate(argc,argv,&head)== SUCCESS)
        {
            printf("Arguments validated successfully\n");
            int option;
         
            while(1)
            {   
            printf("1.Create DataBase\n2.Search DataBase\n3.Display DataBase\n4.Save DataBase\n5.Update DataBase\n6.Exit\n");
            printf("Select one option: ");
            scanf("%d",&option);
                switch(option)
                {
                    case 1: if(create_flag == 0)  // Create database from linked list data
                            {
                                if(create_database(head,arr)== SUCCESS)
                                {
                                    printf("DataBase Created Successfully!\n");
                                    create_flag=1;
                                }
                                else
                                {
                                    printf("INFO:Error occured while creating database\n");
                                }

                            }
                            else if(create_flag == 1)
                            {
                                printf("INFO:Data already created.Cannot create again.\n");
                            }
                            break;

                   case 2:  printf("Enter the word to search: ");    // Search for a word in the hash table
		                    scanf("%s", words);
                            if(search_database(arr,words)== DATA_NOT_FOUND)
                            {
                                printf("INFO:Given word is not present \n");    
                            }       
                            break;

                    case 3: if(create_flag == 1)  // Display the contents of the hash table
                            {
                                if(display_database(arr,size)==SUCCESS)
                                {
                                    printf("Database displayed successfully\n");
                                }
                                else
                                {
                                    printf("INFO:Data not found\n");
                                }
                            }
                            else
                            {
                                printf("INFO:Database not created.Cannot dispaly\n");
                            }
                            break;

                    case 4: //if(create_flag == 1)     // Save database to a file
                            //{
                                printf("Enter the file name : ");
                                scanf("%s", words);
                                if(strstr(words, ".txt") != NULL)
                                {
                                    if(save_database( arr , words ) == FAILURE)
                                    {
                                        printf("Saving database failure\n");
			                        }
			                        else
			                        {
                                        printf("Data base saved succesfully\n");
			                        }
			                    }
			                    else
			                        printf("INFO:Enter .txt file\n"); 
		                    // }
		                    // else
                            // {
                            //    printf("INFO:Data base is not created.No Data present in database to save\n");
                            // }
		                    break; 

                    case 5: if(create_flag==1 && update_flag == 0)   // Update database from a backup file
                            {
                                printf("INFO:Database already created. Cannot update again.\n");
                            }
                            else if(update_flag == 0)
		                    {
                                if((res = update_database( arr )) == SUCCESS )
                                {
                                    printf("Data Restored succesfully\n");
			                        update_flag = 1;
			                    }
			                    else if( res == DATA_NOT_FOUND )
			                    {
                                    printf("Enter the backup file containg backup data:\n");
			                    }
			                    else
			                    {
                                    printf("INFO:Restoring database failure\n");
                                    printf("INFO:Due to the some other extension other than .txt\n");
			                    }
		                    }
		                    else if(update_flag == 1)
                            {
                                printf("INFO:Database already updated. Cannot update again.\n");
                            }
		                    break;        

                    case 6: return SUCCESS;
                    
                    default: printf("INFO:Please!Enter the correct option\n");
                }

            }
        }

    }
}