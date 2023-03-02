#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// #include <conio.h>

#define ENTER 13

void manageData();
void askPassword(int isValidPW, int *ptr_isValidPW);

/*
 NOTES TO SELF:
 - In order to implement password masking, include conio.h and uncomment code in askPassword function
 - Try out all possible routes of the program to recheck inappropriate exits
 - Add function descriptions when finished
 */






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

void addRecords()
{
    printf("Adding a record...\n");
}

void editRecords()
{
    printf("Editing a record...\n");
}

void deleteRecords()
{
    printf("Deleting a record...\n");
}

void importData()
{
    printf("Importing data...\n");
}

void exportData()
{
    printf("Exporting data...\n");
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
    int nInput;
    int bQuit = 0;
	
    // ask for the admin password
    askPassword(isValidPW, &isValidPW);
    
    if (!isValidPW)
    {
        bQuit = 1;
	}
    else
    {
        printf("Managing Data ...\n");
        
        // display manageData options
        printf("[1] Add a record\n");
        printf("[2] Edit a record\n");
        printf("[3] Delete a record\n");
        printf("[4] Import data\n");
        printf("[5] Export data\n");
        printf("[6] Go back to MAIN MENU\n");
        
        scanf("%d", &nInput);
        while (bQuit == 0)
        {
            switch (nInput)
            {
                case 1:
                    addRecords();
                    break;
                    
                case 2:
                    editRecords();
                    break;
                    
                case 3:
                    deleteRecords();
                    break;
                    
                case 4:
                    importData();
                    break;
                    
                case 5:
                    exportData();
                    break;
                    
                case 6:
                    printf("Going back to MAIN MENU...\n");
                    break;
                    
                default:
                    printf("Please select one of the options provided.\n");
                    break;
            }
            bQuit = 1;
        }
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
    
    /*
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
     */
    
    // use only when editing in MacOS
    scanf("%s", sPWInput);
    
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
        *ptr_isValidPW = 0;
    }
    // if incorrect password
    else if (strcmp(sPWInput, sADMINPW) != 0)
    {
        printf("Incorrect Password. Try again.\n");
        printf("[1] Go back to Main Menu\n\n");
        askPassword(isValidPW, &isValidPW);
    }
}

void playQuiz()
{
    printf("Playing quiz...\n");
}

void viewScores()
{
    printf("Viewing scores...\n");
}

void Play()
{
    int bQuit = 0;
    int nInput;
    
    printf("Playing ...\n\n");
    
    // display playQuiz options
    printf("[1] Play\n");
    printf("[2] View Scores\n");
    printf("[3] Go back to MAIN MENU\n");
    
    scanf("%d", &nInput);
    
    while (bQuit == 0)
    {
        switch (nInput)
        {
            case 1:
                playQuiz();
                break;
                
            case 2:
                viewScores();
                break;
                
            case 3:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Please select one of the options provided.\n");
                break;
        }
        bQuit = 1;
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
                Play();
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
