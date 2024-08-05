#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void dochild(int choice);
void runlist(char *cmd);
void runprog(char *cmd, char *input, int args);


int main(int argc, char *argv[]) {
    int choice;
    int pid;
    
    
    while(1) {
        printf("\n------------Database Menu------------\n");
        printf("Type Numbers Representing Programs:\n");
        printf("1: List all items (cclist)\n");
        printf("2: View item details (ccitem)\n");
        printf("3: Add a new item (ccadd)\n");
        printf("4: Edit an item (ccedit)\n");
        printf("5: Delete an item (ccdel)\n");
        printf("6: Find items matching a string (ccmatch)\n");
        printf("7: List items by year range (ccyear)\n");
        printf("8: Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        if (choice == 8) {
            printf("Quitting.\n");
            return 0; 
            break;
        }
        else {
            pid = fork();
            if (pid == 0) {
                dochild(choice);
                return 0;
            } else {
                wait(NULL);
            }
        }
    }
    return 0;
}



void 
dochild(int choice) {
    char input[1000];

    switch(choice) {
        case 1:
            runlist("./cclist");
            break;
        case 2:
            printf("Enter the item id: ");
            fgets(input, sizeof(input), stdin);
            runprog("./ccitem", input, 3);
            break;
        case 3:
            printf("Enter Computer with format: ID maker model year cpu memory description\n");
            fgets(input, sizeof(input), stdin);
            runprog("./ccadd", input, 8);
            break;
        case 4:
            printf("Enter the item id: ");
            fgets(input, sizeof(input), stdin);
            runprog("./ccedit", input, 3);
            break;
        case 5:
            printf("Enter the item id: ");
            fgets(input, sizeof(input), stdin);
            runprog("./ccdel", input, 3);
            break;
        case 6:
            printf("Enter the string to be searched: ");
            fgets(input, sizeof(input), stdin);
            runprog("./ccmatch", input, 3);
            break;
        case 7:
            printf("Enter the range of years: ");
            fgets(input, sizeof(input), stdin);
            runprog("./ccyear", input, 4);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}


void
runlist(char *cmd) {
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;
    execvp(argv[0], argv);
    perror("exec");
    exit(0);
}


void
runprog(char *cmd, char *input, int args) {
	char *argv[args];
    char *string;
    int i;

	argv[0] = cmd;
    string = strtok(input, " ");
    i = 1;
    while(string != NULL && i < args) {
        argv[i++] = string;
        string = strtok(NULL, " ");
    }
    argv[i] = NULL;

    execvp(argv[0], argv);
    perror("exec");
    exit(0);
}
