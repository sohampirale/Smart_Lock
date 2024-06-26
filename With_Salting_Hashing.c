#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void operator();
void nameset();
void read(char *name);
void overwrite(char *name);
void append(char *name);
void create(char *name);
void newpassset();
int gateway();
int main() { 
  int i = gateway();
  if(i == -1) return 0;
  operator();
}

void hash_password(const char *password, const char *salt, unsigned char *outputBuffer) {
    int iterations = 1000;
    int outputLength = 20;

    PKCS5_PBKDF2_HMAC(password, strlen(password), (unsigned char *)salt, strlen(salt), iterations, EVP_sha256(), outputLength, outputBuffer);
}

void nameset(){
  FILE *n;
  n = fopen("name.txt", "w");
  printf("What's your \033[1;32mname\033[0m 😉 : ");
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

  printf("Enter a \033[1;32mpassword\033[0m : ");
  scanf("%s", newpass);
  printf("Confirm your \033[1;32mpassword\033[0m : ");
  scanf("%s", confirmpass);
  int test = strcmp(newpass, confirmpass);
  if(test == 0){
    system("clear");
    printf("New \033[1;32mpassword\033[0m is : %s\n", newpass);
    char c = newpass[2];

    //HASHING

    char salt[] = "random_salt";

    unsigned char hash[20];
    hash_password(newpass, salt, hash);

    printf("\n\n\033[1;32mHash\033[0m : ");

    fprintf(fptr, "%s", hash);
    fclose(fptr);
  } else {
    printf("\033[1;31mBoth passwords do not match\033[0m. Enter again.\n");
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
    printf("Hello !! 😊 \033[1;32m%s\033[0m\nLet's set a \033[1;32mpassword\033[0m (max length of the \033[1;32mpassword\033[0m should be 10) : \n", name);
    newpassset();
    printf("Do you want to access file operator now : \nPress\n(1 for Yes\n0 for No)\nYour option : ");
    scanf("%d", &ask);
    if(ask == 0) return -1;
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
    printf("\nEnter \033[1;32mpassword\033[0m : "); 
    scanf("%s", user);

    char salt[] = "random_salt";

    unsigned char hash[20];
    hash_password(user, salt, hash);

    if(strcmp(data, (char *)hash) == 0){
      system("clear");
      printf("\033[1;32mCorrect password\033[0m\n\n\n");
      break;
    }
    else {
      system("clear");
      printf("\033[1;31mIncorrect password\033[0m..You have %d more tries\n", w);

      memset(user, '\0', strlen(user));
    }
  }
  return w;
}

void operator() {
  int operation;
  printf("Welcome to file operator : \n");
  printf("Enter what you want to do :\n1.Read a file\n2.Overwrite a file\n3.Write(append) in a file\n4.Create a new file\nEnter a no.(1-4) : ");
  scanf("%d", &operation);
  char name[50];
  printf("Enter \033[1;32mname\033[0m of the file : ");
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
      printf("Invalid input");
      operator();
    }
  }
}

void read(char *name) {
  printf("\n\nContents of the file are :\n");
  FILE *fptr;
  fptr = fopen(name, "r");
  if (fptr == NULL) {
    printf("\033[1;31mFile doesn't exists\033[0m\n");
    operator();
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
        printf("\033[1;31mError opening file.\033[0m\n");
        return;
    }

    printf("Enter what you want to add in the file (enter ` to finish):\n");
    char input[1000];
    while (scanf("%s", input) == 1) {
        if (strcmp(input, "`") == 0) 
            break;

        fprintf(fptr, "%s ", input);
    }

    printf("\033[1;32mData saved.\033[0m\n");
    fclose(fptr);
}

void create(char *name) { 
    FILE *fptr;
    fptr = fopen(name, "w");
    char input[1000];
    printf("\033[1;32mFile created successfully.\n\n\033[0m");
    operator();
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
  printf("\033[1;32mData saved\033[0m");
}
