#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// #include <conio.h>

#define TPC_SIZE 20
#define Q_SIZE 150
#define CA_SIZE 30
#define REC_SIZE 50

struct Data
{
    char sTopic[TPC_SIZE];
    int nQNum;
    char sQuestion[Q_SIZE];
    char sChoice1[CA_SIZE];
    char sChoice2[CA_SIZE];
    char sChoice3[CA_SIZE];
    char sAnswer[CA_SIZE];
};

// function declarations
void displayMenu();
void displaymanageData();
int * addRecord(struct Data * A, int * s);
void editRecord();
void deleteRecord();
int * importData(struct Data A[], int * ptr_isValidFile, int * s);
void exportData();
void askPassword(int * ptr_isValidPW);
void playQuiz();
void viewScores();
void Play();


/*
 NOTES TO SELF:
 - In order to implement password masking, include conio.h and uncomment code in askPassword function
 - Add function descriptions when finished
 - apply fopen() and fclose() functions to read and write from txt file
 - change applicable variables to bool data type if applicable for better readability
 - maintain consistency in formats of variable names for better readability
 - restructure functions
 
 ! - better to make user-defined function for the storing sentences with spaces (scanf temp, fgets, remove newline char copied)
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

int * addRecord(struct Data * A, int * s)
{
    char inputQuestion[Q_SIZE];
    char inputAnswer[CA_SIZE];
    int bRecorded = 0;
    int nExistingTopic = 1;
    int nStringLen;
    char temp;
    
    printf("Adding a record ...\n");
    
    // define last_index to determine where the added record will be placed in the struct array
    int last_index = (*s - 1);
    
    // ask user for the question and answer
    printf("Enter question: ");
    scanf("%c", &temp);
    fgets(inputQuestion, CA_SIZE, stdin);
    nStringLen = strlen(inputQuestion);
    inputQuestion[nStringLen - 1] = '\0';
    
    printf("Enter answer: ");
    scanf("%s", inputAnswer);
    
    // check if inputted Q&A are already listed in the records
    for (int i = 0; (i < *s) && (!bRecorded); i++)
    {
        if ((strcmp(A[i].sQuestion, inputQuestion) == 0) && (strcmp(A[i].sAnswer, inputAnswer) == 0))
        {
            printf("Record already listed.\n");
            
            // print record
            printf("Topic: %s\n", A[i].sTopic);
            printf("Question #: %d\n", A[i].nQNum);
            printf("Question: %s\n", A[i].sQuestion);
            printf("Choice 1: %s\n", A[i].sChoice1);
            printf("Choice 2: %s\n", A[i].sChoice2);
            printf("Choice 3: %s\n", A[i].sChoice3);
            printf("Answer: %s\n", A[i].sAnswer);
            
            bRecorded = 1;
        }
    }
    
    // if not yet recorded,
    if (!bRecorded)
    {
        // add the inputted Q&A to the records
        strcpy(A[last_index].sQuestion, inputQuestion);
        strcpy(A[last_index].sAnswer, inputAnswer);
        
        // ask user for input on the record's topic, choice 1, choice 2, and choice 3
        printf("Please input the remaining info needed for the record: \n");
        printf("Topic: ");
        scanf("%s", A[last_index].sTopic);
        
        printf("Choice 1: ");
        scanf("%s", A[last_index].sChoice1);
        printf("Choice 2: ");
        scanf("%s", A[last_index].sChoice2);
        printf("Choice 3: ");
        scanf("%s", A[last_index].sChoice3);
        
        // check if the inputted topic is already existing (the number of existing questions with the same topic will be used to define nQnum of the added record)
        for (int j = 0; (j < *s); j++)
        {
            // do not include j is at the last_index
            if (j != last_index)
            {
                if (strcmp(A[last_index].sTopic, A[j].sTopic) == 0)
                {
                    nExistingTopic++;
                }
            }
        }
        
        // assign nQNum
        A[last_index].nQNum = nExistingTopic;
        
        printf("Added successfully: ");
        printf("%s, %d, %s, %s, %s, %s, %s\n\n", A[last_index].sTopic, A[last_index].nQNum, A[last_index].sQuestion, A[last_index].sChoice1, A[last_index].sChoice2, A[last_index].sChoice3, A[last_index].sAnswer);
    }
    
    // add 1 to current struct array size
    *s = (*s + 1);
    return s;
}

void editRecord()
{
    printf("Editing a record...\n");
}

void deleteRecord()
{
    printf("Deleting a record...\n");
}

int * importData(struct Data A[], int * ptr_isValidFile, int * s)
{
    // initialize file pointer variable
    FILE * fp;
    
    // declare array for filename
    char sFilename[30];
    
    // declare temporary variables for scanned records from text file
    char sfTopic[TPC_SIZE];
    int nfQNum;
    char sfQuestion[Q_SIZE];
    char sfChoice1[CA_SIZE];
    char sfChoice2[CA_SIZE];
    char sfChoice3[CA_SIZE];
    char sfAnswer[CA_SIZE];
    char temp;
    
    int n = 0;
    
    int i = (*s - 1);
    
    int nStringLen;
    
    // ask user for filename
    printf("Input the filename: ");
    scanf("%s", sFilename);
    
    // if user inputted 1
    if (strcmp(sFilename, "1") == 0)
    {
        printf("Going back to Manage Data Menu ...\n");
        n = 1;
        *ptr_isValidFile = n;
    }
    
    // if filename does not exist
    else if ((fp = fopen(sFilename, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: %s does not exist.\n", sFilename);
        printf("[1] Go back to Manage Data Menu\n\n");
        importData(A, ptr_isValidFile, s);
    }
    // else, push through with importing data
    else
    {
        printf("Importing data from file ...\n");
        
        while ((fscanf(fp, "%s\n", sfTopic) == 1) && (!(strcmp(sfTopic, "\n") == 0)))
        {
            // get records
            fscanf(fp, "%d\n", &nfQNum);
            
            // add 1 to the scanned question number everytime there is a record with the same topic in the current record lsit
            for (int i = 0; (i < *s); i++)
            {
                if ((strcmp(A[i].sTopic, sfTopic) == 0)
                {
                    nfQNum++;
                }
            }
            
            // get the question, choice1, choice2, choice3, and the answer
            fgets(sfQuestion, Q_SIZE, fp);
            // remove newline copied by fgets
            nStringLen = strlen(sfQuestion);
            sfQuestion[nStringLen - 1] = '\0';
            
            fscanf(fp, "%s\n", sfChoice1);
            fscanf(fp, "%s\n", sfChoice2);
            fscanf(fp, "%s\n", sfChoice3);
            fscanf(fp, "%s\n", sfAnswer);
            
            // store scanned results from text file to program's array
            strcpy(A[i].sTopic, sfTopic);
            A[i].nQNum = nfQNum;
            strcpy(A[i].sQuestion, sfQuestion);
            strcpy(A[i].sChoice1, sfChoice1);
            strcpy(A[i].sChoice2, sfChoice2);
            strcpy(A[i].sChoice3, sfChoice3);
            strcpy(A[i].sAnswer, sfAnswer);
            
            *s = (*s + 1);
            // iterate
            i++;
            
            // FOR DEBUGGING ONLY
            /*
             printf("%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n", A[i].sTopic, A[i].nQNum, A[i].sQuestion, A[i].sChoice1, A[i].sChoice2, A[i].sChoice3, A[i].sAnswer);
             */
        }
    }
    return s;
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
void manageData(struct Data A[], int * s)
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
                    *s = *addRecord(A, s);
                    break;
                    
                case 2:
                    editRecord();
                    break;
                    
                case 3:
                    deleteRecord();
                    break;
                    
                case 4:
                    *s = *importData(A, &isValidFile, s);
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
    struct Data Records[REC_SIZE];
    int size = 1;
    
    do
    {
        // display main menu GUI
        displayMenu();
        scanf("%d", &nInput);
        
        switch (nInput)
        {
            case 1:
                manageData(&(Records[0]), &size);
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
    
    for (int i = 0; i < (size - 1); i++)
    {
        printf("%s, %d, %s, %s, %s, %s, %s\n\n", Records[i].sTopic, Records[i].nQNum, Records[i].sQuestion, Records[i].sChoice1, Records[i].sChoice2, Records[i].sChoice3, Records[i].sAnswer);
    }
    
    return 0;
}
