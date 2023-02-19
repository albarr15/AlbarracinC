#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#define ENTER 13

void manageData();
void askPassword(int isValidPW, int *pisValidPW);


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

/* manageData allows the admin to add, edit, delete records, as well as import and export data after inputting the correct admin password
    @param <none>
    @return <none>
    Pre-condition: User has opened the program
*/
void
manageData()
{
	int isValidPW = 0;
	
    askPassword(isValidPW, &isValidPW);
    
    if (isValidPW == 1)
    {
    	printf("Managing Data ...\n");
	}
	else
	{
	}
}

/*
	askPassword requires the admin to user the correct admin password as well as masks the password with asterisks while it is being typed for additional security
	@param isValidPW is an integer variable where the validity of the password input is stored
		*ptr_isValidPW is a pointer to the variable 'isValidPW' in order for the manageData to check the validity of the password
	@return <none>
	Pre-condition: User has selected Manage Data from the menu, user cannot backspace or add spaces when entering the password
*/
void
askPassword(int isValidPW, int *ptr_isValidPW)
{
    const char sADMINPW[] = "Genquiz411";
    char sPWInput[11];
    char ch;
    int i = 0;
    int n = 0;
    
    printf("Please input admin password: ");
    
    // Mask password with asterisks
    
    // if character entered is NOT the enter key
    while ((ch = _getch()) != 13)
    {
		sPWInput[i] = ch;
    	printf("*");
    	i++;
	}
	
	// add null byte to specify end of string
    sPWInput[i] = '\0';
    printf("\n");
    
    // use only when editing in MacOS
    //scanf("%s", sPWInput);
    
    // if password is valid
    if (strcmp(sPWInput, sADMINPW) == 0)
    {
    	n = 1;
    	*ptr_isValidPW = n;
        printf("Accessing admin controls...\n");
    }
    // if input is 1, go back to main menu
    else if (strcmp(sPWInput, "1") == 0)
    {
        printf("Going back...\n");
    }
    // if incorrect password
    else if (strcmp(sPWInput, sADMINPW) != 0)
    {
        printf("Incorrect Password. Try again.\n");
        printf("[1] Go back to Main Menu\n\n");
        askPassword(isValidPW, &isValidPW);
    }
}

int main()
{
    int nInput;
    bool bQuit = 0;
    
    do
    {
    // display main menu GUI
    displayMenu();
    scanf("%d", &nInput);
        
        switch (nInput)
        {
            case 1:
                manageData();
                break;
                    
            case 2:
                printf("Playing ...\n");
                break;
                    
            case 3:
                printf("Exiting ...\n");
                bQuit = 1;
                break;
                    
            default:
                printf("Please select one of the options provided.\n");
                break;
        }
    
    }
    while (bQuit == 0);
    
    return 0;
}
