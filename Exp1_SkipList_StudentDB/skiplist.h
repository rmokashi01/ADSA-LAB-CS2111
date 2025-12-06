#ifndef SKIPLIST_H
#define SKIPLIST_H

#define MAX_LEVEL 6
#define P 0.5f

typedef struct Node Node;
typedef struct SkipList SkipList;

struct Node
{
    int key;                 // roll number
    char name[50];
    float marks;
    Node *forward[MAX_LEVEL + 1];
    int nodeLevel;
};

struct SkipList
{
    int level;
    Node *header;
};

void initSkipList(SkipList *list);
Node *searchStudent(SkipList *list, int roll);
void insertStudent(SkipList *list, int roll, const char *name, float marks);
int deleteStudent(SkipList *list, int roll);
void displayStudents(SkipList *list);

#endif
