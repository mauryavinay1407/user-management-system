#include <stdio.h>
#include<string.h>

#define MAX_USERS 20
#define CREDENTIAL_LIMIT 30

typedef struct {
    char username[CREDENTIAL_LIMIT];
    char password[CREDENTIAL_LIMIT];
} User;

User users[MAX_USERS];
int user_count = 0;

void register_user();
int login_user();
void fix_fgets_input(char*);

int main()
{
    int options;
    while (1)
    {
        printf("\nWelcome to User Management");
        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Exit");
        printf("\nSelect an option:");
        scanf("%d", &options);

        switch (options)
        {
        case 1:
            register_user();
            break;
        case 2:{
            int user_index = login_user();
            if(user_index >= 0)
                printf("\nLogin successful! Welcome, %s!",users[user_index].username);
            else
                printf("\nLogin failed! Incorrect username or password.\n");
            break;
        }
        case 3:
            printf("Exiting...\n");
            return 0;
            break;
        default:
            printf("You've selected invalid option.Please try again\n");
            break;
        }
    }
    return 0;
}

void register_user(){
    if(user_count == MAX_USERS){
        printf("\nMaximum user limit reached\n");
        return;
    }
    int new_index = user_count;
    printf("\nRegister a new user\n");
    printf("\nEnter username: ");
    fgets(users[new_index].username,CREDENTIAL_LIMIT,stdin); 
    fix_fgets_input(users[new_index].username);
    printf("\nRegistration successful!!!\n");
}

int login_user(){
    return -1;
}

void fix_fgets_input(char* str){
    int index = strcspn(str,"\n");
    str[index] = '\0';
}
