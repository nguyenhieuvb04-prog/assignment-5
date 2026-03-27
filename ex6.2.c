#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101

typedef struct node {
    char *word;
    int count;
    struct node *next;
} Node;

Node *hashtab[HASHSIZE];

// Hash function
unsigned hash(char *s) {
    unsigned hashval = 0;
    while (*s)
        hashval = *s++ + 31 * hashval;
    return hashval % HASHSIZE;
}

// Lookup
Node *lookup(char *s) {
    Node *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->word) == 0)
            return np;
    }
    return NULL;
}

// Insert
Node *insert(char *s) {
    Node *np;
    unsigned hashval;

    if ((np = lookup(s)) == NULL) {
        np = (Node *)malloc(sizeof(*np));
        if (np == NULL) return NULL;

        np->word = strdup(s);
        np->count = 1;

        hashval = hash(s);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        np->count++;
    }
    return np;
}

// Xóa bảng
void cleartable() {
    for (int i = 0; i < HASHSIZE; i++) {
        Node *curr = hashtab[i];
        while (curr != NULL) {
            Node *temp = curr;
            curr = curr->next;
            free(temp->word);
            free(temp);
        }
        hashtab[i] = NULL;
    }
}

// In bảng
void print_table() {
    for (int i = 0; i < HASHSIZE; i++) {
        Node *np = hashtab[i];
        while (np != NULL) {
            printf("%s: %d\n", np->word, np->count);
            np = np->next;
        }
    }
}

// Chuẩn hóa word (lowercase)
void normalize(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] = tolower(s[i]);
    }
}

int main() {
    FILE *fp = fopen("book.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file!\n");
        return 1;
    }

    char word[100];

    while (fscanf(fp, "%99s", word) == 1) {
        normalize(word);
        insert(word);
    }

    fclose(fp);

    printf("Word Frequency:\n");
    print_table();

    cleartable();
    return 0;
}