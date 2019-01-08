//
//  wordcount.c
//  C_Assignment_2
//
//  Created by Sebastian Pineda on 22/11/2018.
//  Copyright © 2018 Sebastian Pineda. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
 STRUCTURE DEFINITION
 */
typedef struct word
{
    char *uniword;          // unique word
    int freq;               // frequency of unique word
    struct word *pNext;     // pointer to next word
} words;

/*
 Global Variables
 */
words *pStart = NULL;        // Pointer to header of list


/*
 FUNCTIONS DECLARATIONS
 */
int getWord(FILE *file, char *buff, int buffsize);  // Given function to get words
void insertWord(char *tempword);                    // Adds a word to the list or updates exisiting word
void print(words *pWordCount);                      // Outputs a word and its count of occurrences
words* wordNode(char *word);                        // Creates a new WordCounter structure node
void sortedInsert(struct word**, struct word*);     // Function to insert in sorted manor to new list
void insertionSort(struct word **head_ref);         // Function that uses sortedInsert and reasigns header to new sorted list.

/*
 MAIN
 */
int main (int argc, char *argv[])
{
    int i;
    
    for (i = 1; i < argc; i++)
    {
        // File open setup.
        FILE *file;
        file = fopen(argv[i], "r");
        
        // Pointer to list.
        words *pNode = NULL;
        
        // Setup.
        char buff [100];        // max characters in word.
        int buffsize = 10000;   // max text overall.
        
        // Check if file input is correct.
        if (argc < 2)
        {
            printf("Filename '%s' is invalid", argv[i]);
            exit(1);               //  terminates program
        }
        
        else
        {
            // Check file is not NULL.
            file = fopen(argv[i], "r");
            if (file == NULL)
            {
                printf("Couldn't open file\n");
                exit(1);   // terminates program
            }
            else
            {
                // Read words & insert to linked list.
                while (getWord(file, buff, buffsize))
                {
                    // Insert correct word to final structure.
                    insertWord(buff);
                }
                
                // Insert sort nodes to new list
                insertionSort(&pStart);
                
                // Print Nodes.
                pNode = pStart;
                while(pNode != NULL)
                {
                    print(pNode);
                    pNode = pNode->pNext;
                }
                printf("\n");
                
                // Free memory.
                pNode = pStart;
                while(pNode != NULL)
                {
                    free(pNode->uniword);
                    pStart = pNode;
                    pNode = pNode->pNext;
                    free(pStart);
                }
                
                // Close file.
                fclose(file);
                return 0;
            }
        }
    }
}
    


/*
 FUNCTIONS
*/


// Initialize word node
words* wordNode(char *word)
{
    words *pWordCount = NULL;
    pWordCount = (words*)malloc(sizeof(words));
    pWordCount->uniword = (char*)malloc(strlen(word)+1);    // Allocate memory
    strcpy(pWordCount->uniword, word);                      // Copy word to node
    pWordCount->freq = 1;                                   // Set frequency to 1
    pWordCount->pNext = NULL;
    return pWordCount;
}


// Insert function
void insertWord(char *tempword)
{
    words *wordcount = NULL;
    words *pLast = NULL;
    
    // Start list if empty.
    if(pStart == NULL)
    {
        pStart = wordNode(tempword);
        return;
    }
    
    // If tempword is same as uniword in list, increase frequency by 1.
    wordcount = pStart;
    while(wordcount != NULL)
    {
        if(strcmp(tempword, wordcount->uniword) == 0)
        {
            ++wordcount->freq;
            
            return;
        }
        
        pLast = wordcount;
        wordcount = wordcount->pNext;   // Next word
        
    }

    // Word is not in the list, add it
    pLast->pNext = wordNode(tempword);

}


// Print function
void print(words *pWordCount)
{
    /* output the word and it's count */
    printf("%13s\t%1d\n", pWordCount->uniword,pWordCount->freq);
    
}


// Read words in file
int getWord(FILE *file, char *buff, int buffsize)
{
    char *p = buff;
    char c = '\0';
    
    // Skip all non-word characters
    while (!isalpha(c))
    {
        c = fgetc(file);
        if (c == EOF)
            return 0;
    }
    
    // Read word chars
    while (isalpha(c))
    {
        if (p - buff < buffsize - 1)
            *p++ = tolower(c);
        c = fgetc(file);
    }
    
    // Finalize word
    *p = '\0';
    return 1;
    }


// Function to sort a singly linked list using insertion sort function.
void insertionSort(struct word **head_ref)
{
    // Initialize sorted linked list
    struct word *sorted = NULL;
    
    // Traverse the given linked list and insert every node to sorted list.
    struct word *current = *head_ref;
    while (current != NULL)
    {
        // Store next for next iteration.
        struct word *next = current->pNext;
        
        // Insert current in sorted linked list.
        sortedInsert(&sorted, current);
        
        // Update current
        current = next;
    }
    
    // Update head_ref to point to sorted linked list
    *head_ref = sorted;
}


// Function to insert a new_node in a list. Note that this
// function expects a pointer to head_ref as this can modify the
// head of the input linked list
void sortedInsert(struct word** head_ref, struct word* new_node)
{
    
    struct word* current;
    // Special case for the head end
    if (*head_ref == NULL || strcmp((*head_ref)->uniword, new_node->uniword) > 0)
    {
        new_node->pNext = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        // Locate the node before the point of insertion
        current = *head_ref;
        while (current->pNext!=NULL &&
               strcmp(current->pNext->uniword, new_node->uniword) < 0)
        {
            current = current->pNext;
        }
        new_node->pNext = current->pNext;
        current->pNext = new_node;
    }
}
