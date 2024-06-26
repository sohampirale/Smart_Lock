#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

void operatorMenu();
void nameset();
void read(char *name);
void overwrite(char *name);
void append(char *name);
void create(char *name);
void newpassset();
int gateway();

int main() { 
    int i = gateway();
    if(i == -1)
        return 0;
    operatorMenu();
    return 0;
}

void nameset(){
    FILE *n;
    n = fopen("name.txt", "w");
    printf("What's your name %s😉%s : ", CYAN, RESET);
    char name[20];
    fgets(name, 20, stdin);
    fprintf(n, "%s", name);
    system("clear");
    fclose(n);
    n = fopen("name.txt", "r");
}

void newpassset(){
    FILE *fptr;
    FILE *n;
    n = fopen("name.txt", "r");
    int ask; 
    FILE *newpa;
    fptr = fopen("password.txt", "w");
    char newpass[100], confirmpass[100];
    printf("Enter a password : ");
    scanf("%s", newpass);
    printf("Confirm your passsword : ");
    scanf("%s", confirmpass);
    int test = strcmp(newpass, confirmpass);
    if(test == 0){
        system("clear");
        printf("New password is : %s%s%s\n", GREEN, newpass, RESET);
        char c = newpass[2];
        int l = strlen(newpass);
        int t = 0, j = l;
        int l1 = l;
        for(int i = 0; i < l1 - 1; i += 3){
            t = i;
            for(j = l; j > t; j--){
                newpass[j] = newpass[j - 1];
            }
            l++;
            c = c + i;
            newpass[t] = c;
        }
        fprintf(fptr, "%s", newpass);
        int lengthofpass = strlen(newpass);
        fclose(fptr);
    } else {
        printf("%sBoth passwords do not match%s\nEnter again\n", RED, RESET);
        newpassset();
    }
}

int gateway(){
    FILE *fptr;
    FILE *n;
    int t = 0, ask, w = 1;
    char data[100];
    fptr = fopen("password.txt", "r"); 
    n = fopen("name.txt", "r");
    if(n == NULL){
        printf("Welcome to file operator program\n");
        printf("You have entered this program for the first time\n");
        nameset();
    }
    if(fptr == NULL){
        FILE *n;
        n = fopen("name.txt", "r");
        char name[20];
        fgets(name, 20, n);
        printf("Hello !! 😊 %s%s%s\nLet's set a password (max length of the password should be 10) : \n", CYAN, name, RESET);
        newpassset();
        printf("Do you want to access file operator now : \nPress\n(1 for Yes\n0 for No)\nYour option : ");
        scanf("%d", &ask);
        if(ask == 0)
            return -1;
    } 
    system("clear");
    fptr = fopen("password.txt", "r"); 
    fscanf(fptr, "%s", data);
    int passlength = strlen(data);
    int l = strlen(data);
    int j = l;
    int l1 = l;
    char user[100];
    for(w = 2; w > -1; w--){
        char user[100];
        FILE *n;
        n = fopen("name.txt", "r");
        printf("Welcome back ");
        char name[20];
        fgets(name, 20, n);
        fputs(name, stdout);
        printf("\nEnter password : "); 
        scanf("%s", user);
        int l2 = strlen(user);
        char c = user[2];
        int l = strlen(user);
        int t = 0, j = l;
        int l1 = l;
        for(int i = 0; i < l1 - 1; i += 3){
            t = i;
            for(j = l; j > t; j--){
                user[j] = user[j - 1];
            }
            l++;
            c = c + i;
            user[t] = c;
        }
        l2 = strlen(user);
        int l3 = strlen(data);   
        if(strcmp(data, user) == 0){
            system("clear");
            printf("%sCorrect password%s\n\n\n", GREEN, RESET);
            break;
        } else {
            system("clear");
            printf("%sIncorrect password..You have %d more tries%s\n", RED, w, RESET);
        }
    }
    return w;
}

void operatorMenu() {
    int operation;
    printf("Welcome to file operator : \n");
    printf("Enter what you want to do :\n1.Read a file\n2.Overwrite a file\n3.Write(append)in a file\n4.Create a new file\nEnter a no.(1-4) : ");
    scanf("%d", &operation);
    char name[50];
    printf("Enter name of the file : ");
    scanf("%s", &name[0]);
    switch (operation) {
    case 1:
        read(name);
        break;
    case 2:
        overwrite(name);
        break;
    case 3:
        append(name);
        break;
    case 4:
        create(name);
        break;
    default: {
        printf("%sInvalid input%s\n", RED, RESET);
        operatorMenu();
    }
    }
}

void read(char *name) {
    printf("\n\nContents of the file are :\n");
    FILE *fptr;
    fptr = fopen(name, "r");
    if (fptr == NULL) {
        printf("%sFile doesn't exists%s\n", RED, RESET);
        operatorMenu();
    }
    char c;
    while (c != EOF) {
        c = fgetc(fptr);
        printf("%c", c);
    }
    fclose(fptr);
}

void overwrite(char *name) {
    FILE *fptr;
    fptr = fopen(name, "w");
    if (fptr == NULL) {
        printf("%sError opening file%s\n", RED, RESET);
        return;
    }

    printf("Enter what you want to add in the file (enter ` to finish):\n");
    char input[1000];
    while (scanf("%s", input) == 1) {
        if (strcmp(input, "`") == 0) 
            break;

        fprintf(fptr, "%s ", input);
    }

    printf("%sData saved%s\n", GREEN, RESET);
    fclose(fptr);
}

void create(char *name) { 
    FILE *fptr;
    fptr = fopen(name, "w");
    printf("%sFile created successfully%s\n\n", GREEN, RESET);
    operatorMenu();
}

void append(char *name) {
    FILE *fptr;
    fptr = fopen(name, "a");
    char input[1000];
    printf("Enter what you want to add in the file line by line :\n");
    fgets(input, 100, stdin);
    for (int i = 0; 1; i++) {
        if (input[0] == '`')
            break;
        fputs(input, fptr);
        fgets(input, 1000, stdin);
        printf("line %d printed,Enter next line\n", i + 1);
    }
    printf("data saved\n");
}