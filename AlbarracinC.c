#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// #include <conio.h>

#define ENTER 13
#define SIZE1 150
#define SIZE2 30
#define SIZEE 50

// function declarations
void displayMenu();
void displaymanageData();
void inputWspaces(char *s, int LEN);
void addRecord();
void editRecord();
void deleteRecord();
void exportData();
void askPassword(int * ptr_isValidPW);
void playQuiz();
void viewScores();
void Play();

struct Data
{
    char sTopic[20];
    int nQNum;
    char sQuestion[SIZE1];
    char sChoice1[SIZE2];
    char sChoice2[SIZE2];
    char sChoice3[SIZE2];
    char sAnswer[SIZE2];
};


/*
 NOTES TO SELF:
 - In order to implement password masking, include conio.h and uncomment code in askPassword function
 - Add function descriptions when finished
 - apply fopen() and fclose() functions to read and write from txt file
 - change applicable variables to bool data type if applicable for better readability
 - maintain consistency in formats of variable names for better readability
 - restructure functions
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

/* displaymanageData shows the Graphic User Interface for the options in the Manage Data section of the program
 @param <none>
 @return <none>
 Pre-condition: User has selected Manage Data from the Main Menu
 */
void
displaymanageData()
{
    printf("[1] Add a record\n");
    printf("[2] Edit a record\n");
    printf("[3] Delete a record\n");
    printf("[4] Import data\n");
    printf("[5] Export data\n");
    printf("[6] Go back to MAIN MENU\n");
}

void inputWspaces(char *s, int LEN)
{
    int i = 0;
    char temp;
    char ch;
    
    // store dangling newline from previous input
    scanf("%c", &temp);
    
    do
    {
        scanf("%c", &ch);
        
        if (ch != '\n')
        {
            s[i] = ch;
            i++;
            s[i] = '\0';
        }
    } while (i < LEN && ch != '\n');
}

/*
 askPassword requires the admin to user the correct admin password as well as masks the password with asterisks while it is being typed for additional security
 @param isValidPW is an integer variable where the validity of the password input is stored
 *ptr_isValidPW is a pointer to the variable 'isValidPW' in order for the manageData to check the validity of the password
 @return <none>
 Pre-condition: User has selected Manage Data from the menu, user cannot backspace or add spaces when entering the password
 */
void askPassword(int * ptr_isValidPW)
{
    const char sADMINPW[] = "Genquiz411";
    char sPWInput[11];
    // char ch;
    // int i = 0;
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
    printf("%s\n", sPWInput);
    
    // if password is correct
    if (strcmp(sPWInput, sADMINPW) == 0)
    {
        printf("Accessing admin controls...\n");
        // set isValidPW to 1
        n = 1;
        *ptr_isValidPW = n;
    }
    // if input is 1,
    else if (strcmp(sPWInput, "1") == 0)
    {
        // go back to main menu
        printf("Going back...\n");
    }
    // if incorrect password
    else if (strcmp(sPWInput, sADMINPW) != 0)
    {
        printf("Incorrect Password. Try again.\n");
        printf("[1] Go back to Main Menu\n\n");
        // re-attempt to ask password
        askPassword(ptr_isValidPW);
    }
}

void addRecord()
{
    printf("Adding a record...\n");
}

void editRecord()
{
    printf("Editing a record...\n");
}

void deleteRecord()
{
    printf("Deleting a record...\n");
}

void importData(struct Data A[], int * ptr_isValidFile)
{
    // initialize file pointer variable
    FILE * fp;
    
    // declare array for filename
    char sFilename[30];
    
    // declare temporary variables for scanned records from text file
    char sfTopic[20];
    int nfQNum;
    char sfQuestion[SIZE1];
    char sfChoice1[SIZE2];
    char sfChoice2[SIZE2];
    char sfChoice3[SIZE2];
    char sfAnswer[SIZE2];
    
    int n = 0;
    int i = 0;
    int nStringLen;
    
    printf("Input the filename: ");
    scanf("%s", sFilename);
    
    if (strcmp(sFilename, "1") == 0)
    {
        printf("Going back to Manage Data Menu ...\n");
        n = 1;
        *ptr_isValidFile = n;
    }
    else if ((fp = fopen(sFilename, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: %s does not exist.\n", sFilename);
        printf("[1] Go back to Manage Data Menu\n\n");
        importData(A, ptr_isValidFile);
    }
    else
    {
        printf("Importing data from file ...\n");
        
        while (fscanf(fp, "%s\n", sfTopic) == 1)
        {
            // get records
            fscanf(fp, "%d\n", &nfQNum);
            fgets(sfQuestion, SIZE1, fp);
            fgets(sfChoice1, SIZE2, fp);
            fgets(sfChoice2, SIZE2, fp);
            fgets(sfChoice3, SIZE2, fp);
            fscanf(fp, "%s\n", sfAnswer);
            
            // remove newline characters copied by fgets
            nStringLen = strlen(sfQuestion);
            sfQuestion[nStringLen - 1] = '\0';
            nStringLen = strlen(sfChoice1);
            sfChoice1[nStringLen - 1] = '\0';
            nStringLen = strlen(sfChoice2);
            sfChoice2[nStringLen - 1] = '\0';
            nStringLen = strlen(sfChoice3);
            sfChoice3[nStringLen - 1] = '\0';
            
            // store scanned results from text file to program's array
            strcpy(A[i].sTopic, sfTopic);
            A[i].nQNum = nfQNum;
            strcpy(A[i].sQuestion, sfQuestion);
            strcpy(A[i].sChoice1, sfChoice1);
            strcpy(A[i].sChoice2, sfChoice2);
            strcpy(A[i].sChoice3, sfChoice3);
            strcpy(A[i].sAnswer, sfAnswer);
            
            // iterate
            i++;
            
            // FOR DEBUGGING ONLY
            /*
             printf("%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n", A[i].sTopic, A[i].nQNum, A[i].sQuestion, A[i].sChoice1, A[i].sChoice2, A[i].sChoice3, A[i].sAnswer);
             */
        }
    }
}

void exportData()
{
    printf("Exporting data...\n");
}

/* manageData allows the admin to add, edit, delete records, as well as import and export data after inputting the correct admin password
 @param <none>
 @return <none>
 Pre-condition: User has selected Manage Data from the Main Menu and has not yet opted to go back to Main Menu
 */
void manageData(struct Data A[])
{
    int isValidPW = 0;
    int isValidFile = 0;
    int nInput;
    int bQuit = 0;
    
    // ask for the admin password
    askPassword(&isValidPW);
    
    // if valid password
    if (isValidPW)
    {
        while (bQuit == 0)
        {
            printf("Managing Data ...\n");
            
            displaymanageData();
            scanf("%d", &nInput);
            
            switch (nInput)
            {
                case 1:
                    addRecord();
                    break;
                    
                case 2:
                    editRecord();
                    break;
                    
                case 3:
                    deleteRecord();
                    break;
                    
                case 4:
                    importData(A, &isValidFile);
                    break;
                    
                case 5:
                    exportData();
                    break;
                    
                case 6:
                    printf("Going back to MAIN MENU...\n");
                    bQuit = 1;
                    break;
                    
                default:
                    printf("Please select one of the options provided.\n");
                    break;
            }
        }
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

/* Play allows the user to play the quiz, view the scores, as well as go back to the Main Menu
 @param <none>
 @return <none>
 Pre-condition: User has selected Play from the Main Menu and has not yet opted to go back to Main Menu
 */
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
    struct Data Records[SIZEE];
    
    do
    {
        // display main menu GUI
        displayMenu();
        scanf("%d", &nInput);
        
        switch (nInput)
        {
            case 1:
                manageData(&(Records[0]));
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
    
    //USED FOR DEBUGGING ONLY (prints out records)
    
    for (int i = 0; i < 5; i++)
    {
        printf("%s, %d, %s, %s, %s, %s, %s\n\n", Records[i].sTopic, Records[i].nQNum, Records[i].sQuestion, Records[i].sChoice1, Records[i].sChoice2, Records[i].sChoice3, Records[i].sAnswer);
    }
    
    return 0;
}
