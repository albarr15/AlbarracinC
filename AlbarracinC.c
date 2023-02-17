#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void manageData();

/* displayMenu shows the Graphic User Interface for the menu of the General Knowledge Quiz Game
    @param <none>
    @return <none>
    Pre-condition: User has opened the program
*/
void
displayMenu()
{
    printf("GENERAL KNOWLEDGE QUIZ GAME\n\n");
    printf("[1] Manage Data\n");
    printf("[2] Play\n");
    printf("[3] Exit\n");
}


void
askPassword()
{
    const char sADMINPW[] = "Genquiz0411";
    char sPWInput[12];
    char current_charac;
    int i = 0;
    
    printf("Please input admin password: ");
    
    scanf("%s", sPWInput);
    
    if (strcmp(sPWInput, sADMINPW) == 0)
    {
        printf("Accessing admin controls...\n");
    }
    else if (strcmp(sPWInput, "1") == 0)
    {
        printf("Going back...\n");
    }
    else if (strcmp(sPWInput, sADMINPW) != 0)
    {
        printf("Incorrect Password. Try again.\n");
        printf("[1] Go back to Main Menu\n\n");
        askPassword();
    }
}

/* ManageData allows the admin to add, edit, delete records, as well as import and export data after inputting the correct admin password
    @param <none>
    @return <none>
    Pre-condition: User has opened the program
*/
void
manageData()
{
    askPassword();
    
    
}
/* askPassword asks for the correct admin password and verifies if it is correct. If correct, the admin may then proceed to the admin controls
    @param <none>
    @return 1 if password inputted is correct
    Pre-condition: Admin had selected manageData from the main menu
*/

int main()
{
    int nInput;
    bool bQuit = 0;
    
    do
    {
    displayMenu();
    scanf("%d", &nInput);
        
        switch (nInput)
        {
            case 1:
                printf("Managing Data ...\n");
                manageData();
                break;
                    
            case 2:
                printf("Playing ...\n");
                break;
                    
            case 3:
                printf("Exiting ...\n");
                return 0;
                break;
                    
            default:
                printf("Please select one of the options provided.\n");
                break;
        }
    
    }
    while (bQuit == 0);
    
    return 0;
}
