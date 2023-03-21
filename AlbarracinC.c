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

void displayRecord(struct Data A[], int i)
{
    printf("Topic: %s\n", A[i].sTopic);
    printf("Question #: %d\n", A[i].nQNum);
    printf("Question: %s\n", A[i].sQuestion);
    printf("Choice 1: %s\n", A[i].sChoice1);
    printf("Choice 2: %s\n", A[i].sChoice2);
    printf("Choice 3: %s\n", A[i].sChoice3);
    printf("Answer: %s\n", A[i].sAnswer);
}

void displayUniqTopics(struct Data A[], int s)
{
    for (int i = 0; i < s; i++)
    {
        // if the record with the index i has a question number 1 (meaning it is the first question for the given topic)
        if (A[i].nQNum == 1)
        {
            // print topic
            printf("%s\n", A[i].sTopic);
        }
    }
}

void getInput(char sentence[], int LEN)
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
            sentence[i] = ch;
            i++;
            sentence[i] = '\0';
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

int * addRecord(struct Data A[], int * s)
{
    char inputQuestion[Q_SIZE];
    char inputAnswer[CA_SIZE];
    bool bRecorded = 0;
    int nExistingTopic = 1;
    
    printf("Adding a record ...\n");
    
    // define last_index to determine where the added record will be placed in the struct array
    int last_index = (*s - 1);
    
    // ask user for the question and answer
    printf("Enter question: ");
    getInput(inputQuestion, CA_SIZE);
    
    printf("Enter answer: ");
    scanf("%s", inputAnswer);
    
    // check if inputted Q&A are already listed in the records
    for (int i = 0; (i < *s) && (!bRecorded); i++)
    {
        if ((strcmp(A[i].sQuestion, inputQuestion) == 0) && (strcmp(A[i].sAnswer, inputAnswer) == 0))
        {
            printf("Record already listed.\n");
            
            // print record
            displayRecord(A, i);
            
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
        
        // add 1 to current struct array size
        *s = (*s + 1);
    }
    
    // remove last newline character scanned from text file
    A[(*s - 1)].sTopic[0] = '\0';
    
    return s;
}


void editRecord(struct Data A[], int s)
{
    char sInputTopic[TPC_SIZE];
    int nRecord;
    int nIndex;
    int nInput;
    int nExistingTopic = 1;
    int bValid = 0;
    
    printf("Editing a record...\n");
    
    displayUniqTopics(A, s);
    
    printf("Enter the topic you want to edit: ");
    scanf("%s", sInputTopic);
    
    //print all questions with the topic
    for (int i = 0; i < s; i++)
    {
        // print and indicate that inputted topic is existing in the records
        if (strcmp(A[i].sTopic, sInputTopic) == 0)
        {
            printf("[%d] %s\n", A[i].nQNum, A[i].sQuestion);
            bValid = 1;
        }
    }
    
    // if inputted topic is not in records
    if (strcmp(sInputTopic, "1") == 0)
    {
        // exit
    }
    // if user opted to go back to main menu
    else if (!bValid)
    {
        printf("There are no records with the topic you entered.\n");
    }
    else
    {
        printf("Choose the record you want to edit: ");
        scanf("%d", &nRecord);
        
        // find the index of the selected record
        for (int j = 0; j < s; j++)
        {
            if ((strcmp(A[j].sTopic, sInputTopic) == 0) && (A[j].nQNum == nRecord))
            {
                nIndex = j;
            }
        }
        
        printf("\n");
        // display the current record to help guide user
        displayRecord(A, nIndex);
        
        printf("\nWhat field would you like to modify?\n");
        printf("[1] Topic\n");
        printf("[2] Question\n");
        printf("[3] Choice 1\n");
        printf("[4] Choice 2\n");
        printf("[5] Choice 3\n");
        printf("[6] Answer\n");
        
        scanf("%d", &nInput);
        
        switch (nInput) {
            case 1:
                printf("Enter new topic: ");
                scanf("%s", A[nIndex].sTopic);
                
                // check if the modified topic is already existing (the number of existing questions with the same topic will be used to define nQnum of the added record)
                for (int j = 0; (j < s); j++)
                {
                    // do not include j is at the last_index
                    if (j != nIndex)
                    {
                        if (strcmp(A[nIndex].sTopic, A[j].sTopic) == 0)
                        {
                            nExistingTopic++;
                        }
                    }
                }
                
                // assign nQNum
                A[nIndex].nQNum = nExistingTopic;
                break;
                
            case 2:
                printf("Enter new question: ");
                getInput(A[nIndex].sQuestion, Q_SIZE);
                break;
                
            case 3:
                printf("Enter new choice 1: ");
                scanf("%s", A[nIndex].sChoice1);
                break;
                
            case 4:
                printf("Enter new choice 2: ");
                scanf("%s", A[nIndex].sChoice2);
                break;
                
            case 5:
                printf("Enter new choice 3: ");
                scanf("%s", A[nIndex].sChoice3);
                break;
                
            case 6:
                printf("Enter new answer: ");
                scanf("%s", A[nIndex].sAnswer);
                break;
                
            default:
                break;
        }
        
        printf("\n[1] Go back to Main Menu\n\n");
        editRecord(A, s);
    }
}

void deleteRecord()
{
    printf("Deleting a record...\n");
}

int * importData(struct Data A[], int * ptr_isValidFile, int * s)
{
    // declare file pointer variable
    FILE * fp;
    
    // declare array for filename
    char sFilename[30];
    
    // declare temporary variables for scanned records from text file
    char sfTopic[TPC_SIZE];
    int nfQNum;
    char sfQuestion[Q_SIZE];
    
    int n = 0;
    int initialS = *s;
    int i = (*s - 1);
    
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
            
            // add 1 to the scanned question number everytime there is a record with the same topic in the current record list
            for (int i = 0; (i < (initialS - 1)); i++)
            {
                if ((strcmp(A[i].sTopic, sfTopic) == 0))
                {
                    nfQNum++;
                }
            }
            
            // get the question, choice1, choice2, choice3, and the answer
            
            fgets(sfQuestion, Q_SIZE, fp);
            // remove newline copied by fgets
            sfQuestion[strlen(sfQuestion) - 1] = '\0';
            
            // store data to program's record list
            strcpy(A[i].sTopic, sfTopic);
            A[i].nQNum = nfQNum;
            strcpy(A[i].sQuestion, sfQuestion);
            fscanf(fp, "%s\n", A[i].sChoice1);
            fscanf(fp, "%s\n", A[i].sChoice2);
            fscanf(fp, "%s\n", A[i].sChoice3);
            fscanf(fp, "%s\n", A[i].sAnswer);
            
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
    bool bQuit = 0;
    
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
                    editRecord(A, *s);
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
    bool bQuit = 0;
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
