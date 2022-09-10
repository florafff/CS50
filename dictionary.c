    //Dictionary
    // Implements a dictionary's functionality

    #include <ctype.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <cs50.h>
    #include <strings.h>

    #include "dictionary.h"

    int sumcount;
    // Represents a node in a hash table
    typedef struct node
    {
        char word[LENGTH + 1];
        struct node *next;
    }
    node;
    void free_link(node *p);
    // TODO: Choose number of buckets in hash table
    const unsigned int N = 26;

    // Hash table
    node *table[N];

    // Returns true if word is in dictionary, else false
    bool check(const char *word)
    {
        // TODO
        if(table[hash(word)]==NULL)
        {
            return false;
        }
        node *n = table[hash(word)];
        while(n != NULL)
        {
            if(strcasecmp(n->word,word) == 0)
            {
                return true;
            }
                n=n->next;
        }
        return false;
    }

    // Hashes word to a number
    unsigned int hash(const char *word)
    {
        // TODO: Improve this hash function
        return toupper(word[0]) - 'A';
    }

    // Loads dictionary into memory, returning true if successful, else false
    bool load(const char *dictionary)
    {
        // TODO
        FILE *file = fopen(dictionary,"r");
        char c;
        int index = 0;
        node *n = NULL;
        while (fread(&c, sizeof(char), 1, file))
        {
            if(index==0 && isalpha(c))
            {
            n = malloc(sizeof(node));
            if(n == NULL)
            {
                return false;
            }
            n->word[index]=c;
            index++;
            }
            else if(index>0 && c == '\n')
            {
                n->word[index] = '\0';
                index=0;
                sumcount++;
                if(table[hash(n->word)]==NULL)
                {
                    table[hash(n->word)]=n;
                    n->next=NULL;
                }
                else
                {
                    n->next=table[hash(n->word)];
                    table[hash(n->word)]=n;
                }
            }
            else
            {
            n->word[index]=c;
            index++; 
            }  
        }
        fclose(file);
        return true;
    }

    // Returns number of words in dictionary if loaded, else 0 if not yet loaded
    unsigned int size(void)
    {
        // TODO
        return sumcount;
    }

    // Unloads dictionary from memory, returning true if successful, else false
    bool unload(void)
    {
        // TODO
        for(int i=0;i<26;i++)
        {
            free_link(table[i]);
        }
        return true;
    }
    void free_link(node *p)
    {
            if(p == NULL)
        {
            return;
        }
            if(p->next!=NULL)
            {
                free_link(p->next);
            }
            free(p);
    }
