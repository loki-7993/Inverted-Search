#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SUCCESS 0
#define FAILURE 1
#define DATA_NOT_FOUND -2

typedef struct main_node
{
    char word[100];
    int filecount;
    struct sub_node *sub_link;
    struct main_node *main_link;

}word;

typedef struct sub_node
{
    char filename[100];
    int wordcount;
    struct sub_node *sub_link;
}file;

typedef struct hash_table
{
    int key;
    struct main_node *main_link;
}table;

typedef struct Node
{
    char filename[100];
    struct Node *link;
}node;

void create_HT(table *HT, int size);
int read_and_validate(int argc,char *argv[],node **head);
int create_database(node *head,table *arr);
int display_database(table *arr,int size);
int save_database(table *arr,char *file);
int search_database(table *arr, char *word);
int update_database(table *arr );
int backup_validate( char *file );
#endif


