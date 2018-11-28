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

// Change amounts of unique words to print here (Max 1000).
#define PRINTMAX 20

// Define final structure
typedef struct _word
{
    char uniword [1000];    // unique words, up to 1000 max.
    int freq;               // frequency of unique word
} word;

/*
 Function to insert scanned word into final list of words.
 If already in list increment frequency counter by 1.
 If not in list, insert and set frequency to 1.
*/
void insert_word (word *wordcount, int *n, char *tempword)
{
    int i;
    
    // Search array for word
    for (i = 0; i < *n; i++) if (strcmp (tempword, wordcount[i].uniword) == 0)
    {
        // If tempword is same as uniword in array, increase frequency by 1.
        wordcount[i].freq++;
        return;
    }
    
    // Copy tempword into structure and set frequency count for word to 1.
    strcpy (wordcount[*n].uniword, tempword);
    wordcount[*n].freq = 1;
    // Next word
    (*n)++;
}

// Function to remove specific character from string. Used in conjunction with remove_nonalpha.
void remove_char (char *s, int i)
{
    while (s[i])
    {
        i++;
        s[i-1] = s[i];
    }
}

// Identify if character is nonalpha, if not uses remove_char function to remove it.
void remove_nonalpha (char *s)
{
    int    i;
    for (i=0; s[i]; i++)
    {
        if (!isalpha(s[i]))
        {
            remove_char (s, i);
        }
    }
}

// Main program initilization.
int main (int argc, char *argv[])
{
    word words [1000];
    char buff [100];
    int i, m;
    int n = 0;
    
    for (i = 1; i < argc; i++)
    {
        FILE *file;
        file = fopen(argv[i], "r");
        
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
                // Read words in file till end of file using fscanf, place in buffer (with nonalpha characters).
                while ((fscanf(file, "%s", buff)) != EOF)
                {
                    // Subject only 'alpha words' to functons in buffer.
                    if (isalpha(*buff))
                    {
                        // Remove non-alpha characters from buffer.
                        remove_nonalpha (buff);
                        // Insert correct word to final structure.
                        insert_word (words, &n, buff);
                    }
                }
            }
        }
    }
    
    // Setting for amount of words that will print, change via define at top of file.
    if (n < PRINTMAX)
    {
        m = n;
    }
    else
    {
        m = PRINTMAX;
    }
    
    // Print words up to set max with corresponding frequency, formated.
    for (i=0; i<m; i++)
    {
        printf ("%11s\t%1d\n", words[i].uniword, words[i].freq);
    }
}
