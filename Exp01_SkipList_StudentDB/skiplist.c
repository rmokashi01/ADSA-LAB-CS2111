#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skiplist.h"

static int randomLevel(void)
{
    int level = 0;
    while (((float)rand() / RAND_MAX) < P && level < MAX_LEVEL)
    {
        level++;
    }
    return level;
}

static Node *createNode(int level, int key, const char *name, float marks)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    node->key = key;
    strcpy(node->name, name);
    node->marks = marks;
    node->nodeLevel = level;

    for (int i = 0; i <= MAX_LEVEL; i++)
    {
        node->forward[i] = NULL;
    }

    return node;
}

void initSkipList(SkipList *list)
{
    srand((unsigned int)time(NULL));  // seed random

    list->level = 0;
    list->header = createNode(MAX_LEVEL, -1, "", 0.0f); // dummy header
}

Node *searchStudent(SkipList *list, int roll)
{
    Node *x = list->header;

    for (int i = list->level; i >= 0; i--)
    {
        while (x->forward[i] != NULL && x->forward[i]->key < roll)
        {
            x = x->forward[i];
        }
    }

    x = x->forward[0];

    if (x != NULL && x->key == roll)
    {
        return x;
    }

    return NULL;
}

void insertStudent(SkipList *list, int roll, const char *name, float marks)
{
    Node *update[MAX_LEVEL + 1];
    Node *x = list->header;

    for (int i = list->level; i >= 0; i--)
    {
        while (x->forward[i] != NULL && x->forward[i]->key < roll)
        {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];

    // If roll already exists, just update
    if (x != NULL && x->key == roll)
    {
        strcpy(x->name, name);
        x->marks = marks;
        printf("Roll %d already present, record updated.\n", roll);
        return;
    }

    int lvl = randomLevel();

    if (lvl > list->level)
    {
        for (int i = list->level + 1; i <= lvl; i++)
        {
            update[i] = list->header;
        }
        list->level = lvl;
    }

    Node *newNode = createNode(lvl, roll, name, marks);

    for (int i = 0; i <= lvl; i++)
    {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }

    printf("Student inserted successfully.\n");
}

int deleteStudent(SkipList *list, int roll)
{
    Node *update[MAX_LEVEL + 1];
    Node *x = list->header;

    for (int i = list->level; i >= 0; i--)
    {
        while (x->forward[i] != NULL && x->forward[i]->key < roll)
        {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];

    if (x == NULL || x->key != roll)
    {
        return 0; // not found
    }

    for (int i = 0; i <= list->level; i++)
    {
        if (update[i]->forward[i] != x)
            break;
        update[i]->forward[i] = x->forward[i];
    }

    free(x);

    while (list->level > 0 && list->header->forward[list->level] == NULL)
    {
        list->level--;
    }

    return 1; // deleted
}

void displayStudents(SkipList *list)
{
    Node *x = list->header->forward[0];

    if (x == NULL)
    {
        printf("No student records.\n");
        return;
    }

    printf("\nRoll\tName\t\tMarks\n");
    printf("--------------------------------------\n");

    while (x != NULL)
    {
        printf("%d\t%-15s\t%.2f\n", x->key, x->name, x->marks);
        x = x->forward[0];
    }

    printf("--------------------------------------\n");
}
