#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include <termios.h>

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
void input_credentials(char* , char*);

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
        getchar();

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
            printf("\nExiting...\n");
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
    printf("\nRegister a new user");
    input_credentials(users[new_index].username, users[new_index].password);
    user_count++;
    printf("\nRegistration successful!!!\n");
}

int login_user(){
    char username[CREDENTIAL_LIMIT];
    char password[CREDENTIAL_LIMIT];

    input_credentials(username, password);

    for(int i=0; i<user_count;i++){
        if(strcmp(username,users[i].username) == 0 && strcmp(password, users[i].password)==0)
            return i;
    }

    return -1;
}

void fix_fgets_input(char* str){
    int index = strcspn(str,"\n");
    str[index] = '\0';
}

void input_credentials(char* username, char* password){
    printf("\nEnter username: ");
    fgets(username,CREDENTIAL_LIMIT,stdin);
    fix_fgets_input(username);
    printf("Enter password (masking enabled): ");
    fflush(stdout);
    
    // for the masked properties
    struct termios old_props,new_props;
    tcgetattr(STDIN_FILENO, &old_props);
    new_props = old_props;
    // to disable the default terminal behaviour
    new_props.c_lflag &= ~(ECHO | ICANON); 
    tcsetattr(STDIN_FILENO,TCSANOW,&new_props);
    
    char ch;
    int i = 0;
    while((ch = getchar()) != '\n' && ch != EOF){
        if (ch== '\b' || ch == 127) // ASCII of DEL = 127
        {
            if(i > 0){
            i--;
            printf("\b \b");
            }
        }
        else{
            password[i++] = ch;
            printf("*");
        }
        
    }
    password[i] = '\0';
    // assigning back the old default behaviour to terminal
    tcsetattr(STDIN_FILENO,TCSANOW,&old_props);

}