#include <stdio.h>
#include <string.h>

#define MAX 100

char undoStack[MAX][50];
char redoStack[MAX][50];
int topUndo = -1, topRedo = -1;

/*--------- STACK OPERATIONS ----------*/
void pushUndo(char action[]) {
    strcpy(undoStack[++topUndo], action);
}

void pushRedo(char action[]) {
    strcpy(redoStack[++topRedo], action);
}

char* popUndo() {
    if (topUndo == -1) return NULL;
    return undoStack[topUndo--];
}

char* popRedo() {
    if (topRedo == -1) return NULL;
    return redoStack[topRedo--];
}

void clearRedo() {
    topRedo = -1;
}

/*------------ APPLICATION FUNCTIONS ---------------*/

// Perform new action
void doAction(char action[]) {
    printf("Performing: %s\n", action);
    pushUndo(action);
    clearRedo();   // redo is cleared after new action
}

// Undo last action
void undoAction() {
    if (topUndo == -1) {
        printf("Nothing to undo!\n");
        return;
    }

    char* action = popUndo();
    printf("Undo: %s\n", action);
    pushRedo(action);
}

// Redo last undone action
void redoAction() {
    if (topRedo == -1) {
        printf("Nothing to redo!\n");
        return;
    }

    char* action = popRedo();
    printf("Redo: %s\n", action);
    pushUndo(action);
}

/*------------ DISPLAY STACKS --------------------*/
void showStacks() {
    printf("\nUndo Stack: ");
    if (topUndo == -1) printf("empty");
    else {
        for (int i = 0; i <= topUndo; i++)
            printf("[%s] ", undoStack[i]);
    }

    printf("\nRedo Stack: ");
    if (topRedo == -1) printf("empty");
    else {
        for (int i = 0; i <= topRedo; i++)
            printf("[%s] ", redoStack[i]);
    }
    printf("\n");
}

/*---------------- MAIN MENU --------------------*/
int main() {
    int choice;
    char action[50];

    while (1) {
        printf("\n=========== UNDO / REDO SIMULATION ===========\n");
        printf("1. Perform Action\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Show Stacks\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter action (e.g., Type A, Delete B): ");
                gets(action);
                doAction(action);
                break;

            case 2:
                undoAction();
                break;

            case 3:
                redoAction();
                break;

            case 4:
                showStacks();
                break;

            case 5:
                return 0;

            default:
                printf("Invalid Option!\n");
        }
    }
}
