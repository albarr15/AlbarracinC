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
void editRecords();
void deleteRecords();
void importData();
void exportData();
void askPassword(int * ptr_isValidPW);
void playQuiz();
void viewScores();
void Play();

struct Data
{
    char sTopic[20];
    int nQNum;
    char question[SIZE1];
    char choice1[SIZE2];
    char choice2[SIZE2];
    char choice3[SIZE2];
    char answer[SIZE2];
};


/*
 NOTES TO SELF:
 - In order to implement password masking, include conio.h and uncomment code in askPassword function
 - Add function descriptions when finished
 - fix iterations in addRecords
 - apply fopen() and fclose() functions to read and write from txt file
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


void addRecords(struct Data * A[])
{
    char sQuestion[SIZE1];
    char sAnswer[SIZE2];
    int i = 0;
    int isRecorded = 0;
    int index = 0;
    int bFOUND = 0;
    
    printf("Adding a record...\n");
    
    printf("Enter a question: ");
    inputWspaces(sQuestion, SIZE1);
    printf("Enter the answer: ");
    scanf("%s", sAnswer);
    
    // find index of last Q&A in the array
    for (int j = 0; (j < (SIZEE - 1)); j++)
    {
        if (!bFOUND)
        {
            if ((strcmp(A[j]->sTopic, "\0")) == 0)
            {
                bFOUND = 1;
                index = j;
            }
        }
    }
    
    printf("Index of last q&a found: %d\n", index);
    
    /*
    // check if q&a are already in records
    for (int i = 0; ((i < (SIZEE - 1)) || (!isRecorded)); i++)
    {
        if ((strcmp(sQuestion, A[i]->question) == 0) && (strcmp(sAnswer, A[i]->answer)))
        {
            printf("Q & A are already listed in the records.\n");
            printf("%s, %d, %s, %s, %s, %s, %s\n\n", A[i]->sTopic, A[i]->nQNum, A[i]->question, A[i]->choice1, A[i]->choice2, A[i]->choice3, A[i]->answer);
            
            isRecorded = 1;
            if (strcpy(A[i + 1]->question, "\0"))
            {
                break;
            }
        }
    }*/
    
    if (!isRecorded)
    {
        // assign input Q&A to array struct
        strcpy(A[i]->question, sQuestion);
        strcpy(A[i]->answer, sAnswer);
        
        printf("Question: %s\n", sQuestion);
        printf("Answer: %s\n\n", sAnswer);
        
        printf("Please enter the remaining input needed: \n");
        printf("Topic: ");
        scanf("%s", A[i]->sTopic);
        printf("Choice 1: ");
        scanf("%s", A[i]->choice1);
        printf("Choice 2: ");
        scanf("%s", A[i]->choice2);
        printf("Choice 3: ");
        scanf("%s", A[i]->choice3);
        
        // count how many questions are already assigned in the Topic
        int nFlag = 0;
        for (int k = 0; k < 1; k++)
        {
            if (strcmp(A[i]->sTopic, A[k]->sTopic) == 0)
            {
                nFlag++;
            }
        }
        // assign number of times the topic is found in the records to the question number
        A[i]->nQNum = nFlag;
    }
}
    

/* manageData allows the admin to add, edit, delete records, as well as import and export data after inputting the correct admin password
    @param <none>
    @return <none>
    Pre-condition: User has selected Manage Data from the Main Menu and has not yet opted to go back to Main Menu
*/
void manageData(struct Data A[])
{
	int isValidPW = 0;
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
                    addRecords(&A);
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
                    bQuit = 1;
                    break;
                    
                default:
                    printf("Please select one of the options provided.\n");
                    break;
            }
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
        
        printf("%d\n", *ptr_isValidPW);
    }
    // if input is 1,
    else if (strcmp(sPWInput, "1") == 0)
    {
        // go back to main menu
        printf("Going back...\n");
        printf("%d\n", *ptr_isValidPW);
    }
    // if incorrect password
    else if (strcmp(sPWInput, sADMINPW) != 0)
    {
        printf("Incorrect Password. Try again.\n");
        printf("[1] Go back to Main Menu\n\n");
        printf("%d\n", *ptr_isValidPW);
        // re-attempt to ask password
        askPassword(ptr_isValidPW);
    }
}


void
inputWspaces(char *s, int LEN)
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


void editRecords()
{
    printf("Editing a record...\n");
}

void deleteRecords()
{
    printf("Deleting a record...\n");
}

void importData(FILE * ptr_file)
{
    /*
     INITIAL CODE
     
     void readRecords(struct Data * A)
     {
         char temp;
         char temp1;
         int i = 0;
         
         for (int i = 0; (i < SIZEE); i++)
         {
                 scanf("%s", A[i].sTopic);
                 scanf("%d", &A[i].nQNum);
                 inputWspaces(A[i].question, SIZE1);
                 scanf("%s", A[i].choice1);
                 scanf("%s", A[i].choice2);
                 scanf("%s", A[i].choice3);
                 scanf("%s", A[i].answer);
             
                 // store newline
                 scanf("%ch", &temp);
         }
     }
     */
    
    printf("Importing data...\n");
}

void exportData(FILE * ptr_file)
{
    printf("Exporting data...\n");
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

void playQuiz()
{
    printf("Playing quiz...\n");
}

void viewScores()
{
    printf("Viewing scores...\n");
}

int main()
{
    int nInput;
    bool bQuit = 0;
    struct Data Records[SIZEE];
    // FILE * ptr_file = NULL;
    
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
    
     // USED FOR DEBUGGING ONLY (prints out records)
     /*
      for (int i = 0; i < 5; i++)
      {
          printf("%s, %d, %s, %s, %s, %s, %s\n\n", Records[i].sTopic, Records[i].nQNum, Records[i].question, Records[i].choice1, Records[i].choice2, Records[i].choice3, Records[i].answer);
      }
      */
    
    return 0;
}
