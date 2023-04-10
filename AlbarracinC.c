/*********************************************************************************************************
 This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other students and/or persons.
 Clarissa M. Albarracin, DLSU ID# 12206563 *********************************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// #include <conio.h>

#define TPC_SIZE 20
#define Q_SIZE 150
#define CA_SIZE 30
#define REC_SIZE 50
#define FN_SIZE 30
#define NAME_SIZE 21

struct RecordTag
{
    char sTopic[TPC_SIZE];
    int nQNum;
    char sQuestion[Q_SIZE];
    char sChoice1[CA_SIZE];
    char sChoice2[CA_SIZE];
    char sChoice3[CA_SIZE];
    char sAnswer[CA_SIZE];
};

struct CurrentPlayTag
{
    char sCP_Name[NAME_SIZE];
    char sCP_Question[Q_SIZE];
    char sCP_Answer[CA_SIZE];
    char sCP_Choice1[CA_SIZE];
    char sCP_Choice2[CA_SIZE];
    char sCP_Choice3[CA_SIZE];
    int nCP_Score;
};

// function prototypes
void displayMenu();
void displaymanageData();
void displayRecord(struct RecordTag Records[], int i);
void displayUniqueTopics(struct RecordTag Records[], int nSize);
void getInput(char sentence[], int nLength);
void askPassword(int * ptr_isValidPW);
int isQandA_Existing(struct RecordTag Records[], int * nSize, char Question[Q_SIZE], char Answer[CA_SIZE]);

int * addRecord(struct RecordTag Records[], int * nSize);
void editRecord(struct RecordTag Records[], int nSize);
int * deleteRecord(struct RecordTag Records[], int * nSize);
int * importData(struct RecordTag Records[], int * ptr_isValidFile, int * nSize, int isPlay);
void exportData(struct RecordTag Records[], int nSize);
void updateMasterFile(struct RecordTag Records[], int nSize, char mode);
int * backMenu(struct RecordTag Records[], int * nSize);
void manageData(struct RecordTag Records[], int * nSize);

void playQuiz(struct RecordTag Records[], struct CurrentPlayTag *CurrentPlayRec, int * nSize);
void viewScores();
void QuizGame(struct RecordTag Records[], struct CurrentPlayTag *CurrentPlayRec, int nSize);


/*
 NOTES TO SELF:
 - In order to implement password masking, include conio.h and uncomment code in askPassword function
 - Add function descriptions when finished
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
    printf("\n\n-----GENERAL KNOWLEDGE QUIZ GAME-----\n\n");
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

/* displayRecord shows the record with the index i's topic, question number, question, choice 1, 2, and 3, as well as the answer
 @param Records is an array of structures which stores the records
 i is the index of the array which will be displayed
 @return <none>
 Pre-condition: Said record should already be existing either by importing data or adding a record
 */
void
displayRecord(struct RecordTag Records[], int i)
{
    printf("Topic: %s\n", Records[i].sTopic);
    printf("Question #: %d\n", Records[i].nQNum);
    printf("Question: %s\n", Records[i].sQuestion);
    printf("Choice 1: %s\n", Records[i].sChoice1);
    printf("Choice 2: %s\n", Records[i].sChoice2);
    printf("Choice 3: %s\n", Records[i].sChoice3);
    printf("Answer: %s\n", Records[i].sAnswer);
}

/* displayUniqueTopics shows all current records' topics without duplicates
 @param Records is an array of structures which stores the records
 i is the index of the array which will be displayed
 @return <none>
 Pre-condition: <none>
 */
void
displayUniqueTopics(struct RecordTag Records[], int s)
{
    for (int i = 0; i < s; i++)
    {
        // if the record with the index i has a question number 1 (meaning it is the first question for the given topic)
        if (Records[i].nQNum == 1)
        {
            // print topic
            printf("%s\n", Records[i].sTopic);
        }
    }
}

/*
 getInput allows for sentence inputs wherein all characters before the newline character is stored in the array
 @param sentence is a string where all characters before newline is stored
 nLength is the maximum size the sentence can have
 @return <none>
 Pre-condition: <none>
 */
void
getInput(char sentence[], int nLength)
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
    } while (i < nLength && ch != '\n');
}

/*
 askPassword requires the admin to input the correct admin password while masking the password with asterisks as it is typed for additional security
 *ptr_isValidPW is a pointer to the variable 'isValidPW' in order for the manageData to check the validity of the password
 @return <none>
 Pre-condition: User has selected Manage Data from the menu, user cannot backspace or add spaces when entering the password
 */
void
askPassword(int * ptr_isValidPW)
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
        printf("Accessing admin controls...\n\n");
        // set isValidPW to 1
        n = 1;
        *ptr_isValidPW = n;
    }
    // if input is 1,
    else if (strcmp(sPWInput, "0") == 0)
    {
        // go back to main menu
    }
    // if incorrect password
    else if (strcmp(sPWInput, sADMINPW) != 0)
    {
        printf("Incorrect Password. Try again.\n");
        printf("[0] Go back to Main Menu\n\n");
        // re-attempt to ask password
        askPassword(ptr_isValidPW);
    }
}

/*
 isQandA_Existing checks whether or not the parameter Question and Answer are existing in the Records
 @param Records is an array of structures which stores the records
        *nSize is a pointer to the variable nSize which indicates the current number of non-empty elements of the array Records
        Question is a character array which stores the question to be checked
        Answer is a character array which stores the answer to be checked
 @return 1 if it is already existing,
        -1 if not yet existing
 Pre-condition: The answer must be the same as only one of Choice1, Choice2, or Choice3.
 */
int
isQandA_Existing(struct RecordTag Records[], int * nSize, char Question[Q_SIZE], char Answer[CA_SIZE])
{
    bool bIsRecorded = 0;
    
    // check if inputted Q&A are already listed in the records
    for (int i = 0; (i < *nSize) && (!bIsRecorded); i++)
    {
        if ((strcmp(Records[i].sQuestion, Question) == 0) && (strcmp(Records[i].sAnswer, Answer) == 0))
        {
            // print record
            displayRecord(Records, i);
            bIsRecorded = 1;
            return 1;
        }
    }
    
    // if not existing,
    if (!bIsRecorded)
    {
        return -1;
    }
    
    return -1;
}



/*
 addRecord allows the admin to create a new record given that the question and answer are not yet existing (If it is existing, there will be a message displayed to inform admin)
 @param Records is an array of structures which stores the records
 *nSize is a pointer to the variable nSize which indicates the current number of non-empty elements of the array Records
 @return nSize wherein nSize will be iterated by 1 if addition of record is successful
 Pre-condition: The answer to be inputted by the user must be the same as only one of Choice1, Choice2, or Choice3.
 */
int *
addRecord(struct RecordTag Records[], int * nSize)
{
    char inputQuestion[Q_SIZE];
    char inputAnswer[CA_SIZE];
    int nExistingTopics = 1;
    
    printf("----- Add Record -----\n\n");
    
    // define last_index to determine where the added record will be placed in the struct array
    int last_index = (*nSize - 1);
    
    if (*nSize == 1)
    {
        last_index = 0;
    }
    
    // ask user for the question and answer
    printf("Enter question: ");
    getInput(inputQuestion, Q_SIZE);
    
    printf("Enter answer: ");
    scanf("%s", inputAnswer);
    
    int nResult = isQandA_Existing(Records, nSize, inputQuestion, inputAnswer);
    
    if (nResult == 1)
    {
        printf("Q and A are already existing.\n");
    }
    
    // if not yet recorded,
    else if (nResult == -1)
    {
        // add the inputted Q&A to the records
        strcpy(Records[last_index].sQuestion, inputQuestion);
        strcpy(Records[last_index].sAnswer, inputAnswer);
        
        // ask user for input on the record's topic, choice 1, choice 2, and choice 3
        printf("Topic: ");
        scanf("%s", Records[last_index].sTopic);
        printf("Choice 1: ");
        scanf("%s", Records[last_index].sChoice1);
        printf("Choice 2: ");
        scanf("%s", Records[last_index].sChoice2);
        printf("Choice 3: ");
        scanf("%s", Records[last_index].sChoice3);
        
        // check if the inputted topic is already existing (the number of existing questions with the same topic will be used to define nQNum of the added record)
        for (int j = 0; (j < *nSize); j++)
        {
            // do not include j is at the last_index
            if (j != last_index)
            {
                if (strcmp(Records[last_index].sTopic, Records[j].sTopic) == 0)
                {
                    nExistingTopics++;
                }
            }
        }
        
        // assign nQNum
        Records[last_index].nQNum = nExistingTopics;
        
        printf("\n----- Addition successful -----\n\n");
        displayRecord(Records, last_index);
        printf("\n");
        // printf("%s, %d, %s, %s, %s, %s, %s\n\n", Records[last_index].sTopic, Records[last_index].nQNum, Records[last_index].sQuestion, Records[last_index].sChoice1, Records[last_index].sChoice2, Records[last_index].sChoice3, Records[last_index].sAnswer);
        
        // add 1 to current struct array size
        *nSize = (*nSize + 1);
    }
    
    // remove last newline character scanned from text file
    Records[(*nSize - 1)].sTopic[0] = '\0';
    
    return nSize;
}

/*
 editRecord allows the admin to edit a field in an existing record
 @param Records is an array of structures which stores the records
        nSize indicates the current number of non-empty elements of the array Records
 @return <none>
 Pre-condition: When editing topic, the new topic must not be the same as previous one
 */
void
editRecord(struct RecordTag Records[], int nSize)
{
    char sInputTopic[TPC_SIZE];
    int nRecord;
    int nIndex;
    int nInput;
    int nExistingTopics = 1;
    int bValid = 0;
    
    printf("----- Edit Record -----\n\n");
    
    displayUniqueTopics(Records, nSize);
    
    printf("Enter the topic you want to edit: ");
    scanf("%s", sInputTopic);
    
    // print all questions with the topic along with its question number
    for (int i = 0; i < nSize; i++)
    {
        // print and indicate that inputted topic is existing in the records
        if (strcmp(Records[i].sTopic, sInputTopic) == 0)
        {
            printf("[%d] %s\n", Records[i].nQNum, Records[i].sQuestion);
            bValid = 1;
        }
    }
    
    // if user opted to go back to main menu
    if (strcmp(sInputTopic, "0") == 0)
    {
        // exit
    }
    // if inputted topic is not in records
    else if (!bValid)
    {
        printf("There are no records with the topic you entered.\n");
    }
    else // if inputted topic is in records
    {
        printf("Choose the record you want to edit: ");
        scanf("%d", &nRecord);
        
        // find the index of the selected record
        for (int j = 0; j < nSize; j++)
        {
            if ((strcmp(Records[j].sTopic, sInputTopic) == 0) && (Records[j].nQNum == nRecord))
            {
                nIndex = j;
            }
        }
        
        printf("\n");
        
        
        // display the current record to help guide user
        displayRecord(Records, nIndex);
        
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
                // re-adjust nQNum of those within the same topic
                for (int j = 0; j < (nSize - 1); j++)
                {
                    if (j != nIndex)
                    {
                        if ((strcmp(Records[nIndex].sTopic, Records[j].sTopic) == 0) && (Records[nIndex].nQNum < Records[j].nQNum))
                        {
                            Records[j].nQNum = Records[j].nQNum - 1;
                        }
                    }
                }
                
                printf("Enter new topic: ");
                scanf("%s", Records[nIndex].sTopic);
                
                // check if the modified topic is already existing (the number of existing questions with the same topic will be used to define nQNum of the added record)
                for (int k = 0; (k < nSize); k++)
                {
                    if (k != nIndex)
                    {
                        // do not include j is at the last_index
                        if (strcmp(Records[nIndex].sTopic, Records[k].sTopic) == 0)
                        {
                            nExistingTopics++;
                        }
                    }
                }
                
                // assign nQNum
                Records[nIndex].nQNum = nExistingTopics;
                break;
                
            case 2:
                printf("Enter new question: ");
                getInput(Records[nIndex].sQuestion, Q_SIZE);
                break;
                
            case 3:
                printf("Enter new choice 1: ");
                scanf("%s", Records[nIndex].sChoice1);
                break;
                
            case 4:
                printf("Enter new choice 2: ");
                scanf("%s", Records[nIndex].sChoice2);
                break;
                
            case 5:
                printf("Enter new choice 3: ");
                scanf("%s", Records[nIndex].sChoice3);
                break;
                
            case 6:
                printf("Enter new answer: ");
                scanf("%s", Records[nIndex].sAnswer);
                break;
                
            default:
                break;
        }
        printf("----- Edit successful -----\n");
        printf("\n[0] Go back to Main Menu\n\n");
        editRecord(Records, nSize);
    }
}

/*
 deleteRecord allows the admin to remove a selected record
 @param Records is an array of structures which stores the records
 *nSize is a pointer to the variable nSize which indicates the current number of non-empty elements of the array Records
 @return nSize wherein nSize will be deducted by 1 if deletion of record is successful
 Pre-condition: <none>
 */
int *
deleteRecord(struct RecordTag Records[], int * nSize)
{
    char sInputTopic[TPC_SIZE];
    bool bValid = 0;
    int nRecord;
    int nIndex;
    char cInput;
    char temp;
    int i;
    
    
    printf("----- Delete Record -----\n\n");
    
    // display unique topics
    displayUniqueTopics(Records, *nSize);
    
    printf("Enter the topic you want to delete: ");
    scanf("%s", sInputTopic);
    
    // print all questions with the topic
    for (i = 0; i < *nSize; i++)
    {
        // print and indicate that inputted topic is existing in the records
        if (strcmp(Records[i].sTopic, sInputTopic) == 0)
        {
            printf("[%d] %s\n", Records[i].nQNum, Records[i].sQuestion);
            bValid = 1;
        }
    }
    
    // if user opted to go back to main menu
    if (strcmp(sInputTopic, "0") == 0)
    {
        // exit
    }
    // if inputted topic is not in records
    else if (!bValid)
    {
        printf("There are no records with the topic you entered.\n");
    }
    else
    {
        printf("Choose the record you want to delete: ");
        scanf("%d", &nRecord);
        
        // find the index of the selected record
        for (int j = 0; j < *nSize; j++)
        {
            if ((strcmp(Records[j].sTopic, sInputTopic) == 0) && (Records[j].nQNum == nRecord))
            {
                nIndex = j;
            }
        }
        
        printf("\n");
        // display the current record to help guide user
        displayRecord(Records, nIndex);
        
        printf("Are you sure you want to delete the record? (y/n)\n");
        scanf("%c", &temp);
        scanf("%c", &cInput);
        
        if (cInput == 'y')
        {
            // re-adjust array values to compensate from deleted index
            for (int pos = nIndex; pos < (*nSize - 1); pos++)
            {
                strcpy(Records[pos].sTopic, Records[pos + 1].sTopic);
                
                // adjust question number for those under the same topic
                if ((strcmp(Records[pos].sTopic, Records[pos + 1].sTopic) == 0) && (Records[pos].nQNum < Records[pos + 1].nQNum))
                {
                    Records[pos].nQNum = (Records[pos + 1].nQNum - 1);
                }
                
                strcpy(Records[pos].sQuestion, Records[pos + 1].sQuestion);
                strcpy(Records[pos].sChoice1, Records[pos + 1].sChoice1);
                strcpy(Records[pos].sChoice2, Records[pos + 1].sChoice2);
                strcpy(Records[pos].sChoice3, Records[pos + 1].sChoice3);
                strcpy(Records[pos].sAnswer, Records[pos + 1].sAnswer);
            }
            *nSize = (*nSize - 1);
            printf("----- Delete successful -----\n");
            
            printf("\nDo you want to delete another record? (y/n)\n\n");
            scanf("%s", &cInput);
            
            if (cInput == 'y')
            {
                *nSize = *deleteRecord(Records, nSize);
            }
        }
    }
    return nSize;
}

/*
 importData allows the admin to store the data from a text file to the program's records
 @param Records is an array of structures which stores the records
 *ptr_isValidFile points to the variable isValidFile
 *nSize is a pointer to the variable nSize which indicates the current number of non-empty elements of the array Records
 isPlay indicates whether or not the importData function is used in the Play part of the program or not
 @return nSize wherein nSize will be added depending on the number of records added through importing
 Pre-condition: the file's content must be in correct format
 */
int *
importData(struct RecordTag Records[], int * ptr_isValidFile, int * nSize, int isPlay)
{
    // declare file pointer variable
    FILE * fp;
    
    // declare array for filename
    char sFilename[FN_SIZE];
    
    // declare temporary variables for scanned records from text file
    char sfTopic[TPC_SIZE];
    int nfQNum;
    char sfQuestion[Q_SIZE];
    char sfAnswer[CA_SIZE];
    char sfChoice1[CA_SIZE];
    char sfChoice2[CA_SIZE];
    char sfChoice3[CA_SIZE];
    
    int n = 0;
    int initialS = *nSize;
    int i = (*nSize - 1);
    
    if (isPlay)
    {
        strcpy(sFilename, "stored-records.txt");
    }
    else
    {
        // ask user for filename
        printf("Input the filename: ");
        scanf("%s", sFilename);
    }
    
    // if user inputted 1
    if (strcmp(sFilename, "1") == 0)
    {
        n = 1;
        *ptr_isValidFile = n;
    }
    
    // if filename does not exist
    else if ((fp = fopen(sFilename, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: %s does not exist.\n", sFilename);
        printf("[1] Go back to Manage Data Menu\n\n");
        importData(Records, ptr_isValidFile, nSize, 0);
    }
    // else, push through with importing data
    else
    {
        if (!isPlay)
            printf("----- Importing Data -----\n\n");
        
        while ((fscanf(fp, "%s\n", sfTopic) == 1) && (!(strcmp(sfTopic, "\n") == 0)))
        {
            // get records
            fscanf(fp, "%d\n", &nfQNum);
            
            // add 1 to the scanned question number everytime there is a record with the same topic in the current record list
            for (int i = 0; (i < (initialS - 1)); i++)
            {
                if ((strcmp(Records[i].sTopic, sfTopic) == 0))
                {
                    nfQNum++;
                }
            }
            
            // get the question, choice1, choice2, choice3, and the answer
            fgets(sfQuestion, Q_SIZE, fp);
            // remove newline copied by fgets
            sfQuestion[strlen(sfQuestion) - 1] = '\0';
            
            fscanf(fp, "%s\n", sfChoice1);
            fscanf(fp, "%s\n", sfChoice2);
            fscanf(fp, "%s\n", sfChoice3);
            fscanf(fp, "%s\n", sfAnswer);
            
            if (isQandA_Existing(Records, nSize, sfQuestion, sfAnswer) == 1)
            {
                printf("The said record is existing already. (Import unsuccessful) \n\n");
            }
            else if (isQandA_Existing(Records, nSize, sfQuestion, sfAnswer) == -1)
            {
                // store data to program's record list
                strcpy(Records[i].sTopic, sfTopic);
                Records[i].nQNum = nfQNum;
                strcpy(Records[i].sQuestion, sfQuestion);
                strcpy(Records[i].sAnswer, sfAnswer);
                strcpy(Records[i].sChoice1, sfChoice1);
                strcpy(Records[i].sChoice2, sfChoice2);
                strcpy(Records[i].sChoice3, sfChoice3);
                
                *nSize = (*nSize + 1);
                // iterate
                i++;
            }
        }
    }
    return nSize;
}

/*
 exportData allows the admin to store the data from the program's records to both a filename inputted by the admin, and the masterfile named "stored-records.txt"
 @param Records is an array of structures which stores the records
 nSize indicates the current number of non-empty elements of the array Records
 @return <none>
 Pre-condition: <none>
 */
void
exportData(struct RecordTag Records[], int nSize)
{
    printf("----- Exporting Data -----\n\n");
    
    // declare file pointer variable
    FILE * fp1;
    
    // declare array for filename
    char sFilename[FN_SIZE];
    
    bool bKeep_Reading = 1;
    
    // ask user for filename
    printf("Input the filename: ");
    scanf("%s", sFilename);
    
    // open file named sFilename in writing mode
    fp1 = fopen(sFilename, "w");
    
    // iterate over all elements of array Records unless it is at the end of file
    for (int i = 0; (i < (nSize - 1)) && (bKeep_Reading); i++)
    {
        if (feof(fp1))
        {
            // exit loop
            bKeep_Reading = 0;
        }
        else
        {
            // print all information
            fprintf(fp1, "%s\n", Records[i].sTopic);
            fprintf(fp1, "%d\n", Records[i].nQNum);
            fprintf(fp1, "%s\n", Records[i].sQuestion);
            fprintf(fp1, "%s\n", Records[i].sChoice1);
            fprintf(fp1, "%s\n", Records[i].sChoice2);
            fprintf(fp1, "%s\n", Records[i].sChoice3);
            fprintf(fp1, "%s\n\n", Records[i].sAnswer);
        }
    }
    
    // close file
    fclose(fp1);
    
    updateMasterFile(Records, nSize, 'a');
}

/*
 updateMasterFile allows the admin to either append current records or clear all existing information on the masterfile
 depending on the mode inputted on the parameter mode
 @param Records is an array of structures which stores the records
 nSize indicates the current number of non-empty elements of the array Records
 char mode indicates whether or not the masterfile will be opened in append or write mode
 @return <none>
 Pre-condition: masterfile is already existing in computer's files
 */
void
updateMasterFile(struct RecordTag Records[], int nSize, char mode)
{
    // export data to the file "stored-records.txt" (this will be the master file for all records)
    FILE * fp2 = NULL;
    
    // declare array for filename
    char sFilename[FN_SIZE];
    
    bool bKeep_Reading = 1;
    
    strcpy(sFilename, "stored-records.txt");
    if (mode == 'a')
    {
        fp2 = fopen(sFilename, "a");
        
        // iterate over all elements of array Records unless it is at the end of file
        for (int i = 0; (i < (nSize - 1)) && (bKeep_Reading); i++)
        {
            if (feof(fp2))
            {
                // exit loop
                bKeep_Reading = 0;
            }
            else
            {
                // print all information
                fprintf(fp2, "%s\n", Records[i].sTopic);
                fprintf(fp2, "%d\n", Records[i].nQNum);
                fprintf(fp2, "%s\n", Records[i].sQuestion);
                fprintf(fp2, "%s\n", Records[i].sChoice1);
                fprintf(fp2, "%s\n", Records[i].sChoice2);
                fprintf(fp2, "%s\n", Records[i].sChoice3);
                fprintf(fp2, "%s\n\n", Records[i].sAnswer);
            }
        }
    }
    else if (mode == 'w')
    {
        fp2 = fopen(sFilename, "w");
        
        // iterate over all elements of array Records unless it is at the end of file
        for (int i = 0; (i < (nSize - 1)) && (bKeep_Reading); i++)
        {
            if (feof(fp2))
            {
                // exit loop
                bKeep_Reading = 0;
            }
            else
            {
                // print all information
                fprintf(fp2, "%s\n", Records[i].sTopic);
                fprintf(fp2, "%d\n", Records[i].nQNum);
                fprintf(fp2, "%s\n", Records[i].sQuestion);
                fprintf(fp2, "%s\n", Records[i].sChoice1);
                fprintf(fp2, "%s\n", Records[i].sChoice2);
                fprintf(fp2, "%s\n", Records[i].sChoice3);
                fprintf(fp2, "%s\n\n", Records[i].sAnswer);
            }
        }
    }
    
    // close file
    fclose(fp2);
}

/*
 backMenu allows the admin to go back to the menu and clear all information on records
 @param Records is an array of structures which stores the records
 nSize indicates the current number of non-empty elements of the array Records
 @return nSize wherein it will be set to 1 (indicating an empty record set)
 Pre-condition: <none>
 */
int *
backMenu(struct RecordTag Records[], int * nSize)
{
    for (int i = 0; i < (*nSize - 1); i++)
    {
        strcpy((Records[i]).sTopic, "");
        (Records[i]).nQNum = 0;
        strcpy((Records[i]).sChoice1, "");
        strcpy((Records[i]).sChoice2, "");
        strcpy((Records[i]).sChoice3, "");
        strcpy((Records[i]).sAnswer, "");
    }
    
    *nSize = 1;
    return nSize;
}

/* manageData allows the admin to add, edit, delete records, as well as import and export data after inputting the correct admin password
 @param Records is an array of structures which stores the records
 *nSize is a pointer to the variable nSize which indicates the current number of non-empty elements of the array Records
 @return <none>
 Pre-condition: User has selected Manage Data from the Main Menu and has not yet opted to go back to Main Menu
 */
void
manageData(struct RecordTag Records[], int * nSize)
{
    int isValidPW = 0;
    int isValidFile = 0;
    int nInput;
    bool bIsQuit = 0;
    
    // ask for the admin password
    askPassword(&isValidPW);
    
    // if valid password
    if (isValidPW)
    {
        while (bIsQuit == 0)
        {
            printf("----- Manage Data -----\n\n");
            
            displaymanageData();
            scanf("%d", &nInput);
            
            switch (nInput)
            {
                case 1:
                    *nSize = *addRecord(Records, nSize);
                    break;
                    
                case 2:
                    editRecord(Records, *nSize);
                    break;
                    
                case 3:
                    *nSize = *deleteRecord(Records, nSize);
                    break;
                    
                case 4:
                    *nSize = *importData(Records, &isValidFile, nSize, 0);
                    break;
                    
                case 5:
                    exportData(Records, *nSize);
                    break;
                    
                case 6:
                    *nSize = *backMenu(Records, nSize);
                    bIsQuit = 1;
                    break;
                    
                default:
                    printf("Please select one of the options provided.\n");
                    break;
            }
        }
    }
}



/*
 exportScore adds the current score of the current player in score.txt
 @param *CurrentPlayRec is a pointer to the struct CurrentPlayRec wherein the name and score is stored
 @return <none>
 Pre-condition: score.txt is already existing in the computer
 */
void
exportScore(struct CurrentPlayTag * CurrentPlayRec)
{
    // export data to the file "stored-records.txt" (this will be the master file for all records)
    FILE * fp3 = NULL;
    
    // declare array for filename
    char sFilename[FN_SIZE];
    
    strcpy(sFilename, "score.txt");
    fp3 = fopen(sFilename, "a");
    
    // print all information
    fprintf(fp3, "%s\n", CurrentPlayRec->sCP_Name);
    fprintf(fp3, "%d\n", CurrentPlayRec->nCP_Score);
    fprintf(fp3, "\n");
    
    // close file
    fclose(fp3);
}

/* playQuiz allows the user to play the quiz game which contains all records that have been exported
 @param Records is an array of structures which stores the records
 *CurrentPlayRec is a pointer to the struct CurrentPlayRec wherein the name and score is stored
 *nSize is a pointer to the variable nSize which indicates the current number of non-empty elements of the array Records
 @return <none>
 Pre-condition: <none>
 */
void
playQuiz(struct RecordTag Records[], struct CurrentPlayTag *CurrentPlayRec, int * nSize)
{
    char sInputTopic[TPC_SIZE];
    char sInputAnswer[CA_SIZE];
    char sQuesArray[REC_SIZE][Q_SIZE];
    int i, j;
    bool isPlaying = 1;
    bool bIsStored = 0;
    bool bIsEmpty = 0;
    int isValidFile = 0;
    int isFound = 0;
    
    printf("----- Play Quiz -----\n\n");
    
    // initialize number of non-empty elements in sQuesArray
    int nQues = 0;
    
    // import records data
    *nSize = *importData(Records, &isValidFile, nSize, 1);
    
    if (*nSize == 1)
    {
        printf("There are currently no records available to play.\n");
        isPlaying = 0;
        bIsEmpty = 1;
    }
    else
    {

        // Enter player name
        printf("Enter your name: ");
        
        // store value to struct array
        scanf("%s", CurrentPlayRec->sCP_Name);
        
        // initialize score of player to zero
        CurrentPlayRec->nCP_Score = 0;
        
    }
    
    while (isPlaying)
    {
        if (*nSize == 1)
        {
            printf("There are currently no records available to play.\n");
            isPlaying = 0;
        }
        else
        {
            nQues = 0;
            
            displayUniqueTopics(Records, *nSize);
            
            printf("Enter the topic you want to focus on: ");
            scanf("%s", sInputTopic);
            
            
            if (strcmp(sInputTopic, "0") == 0)
            {
                isPlaying = 0;
            }
            else if (!isFound)
            {
                for (i = 0; (i < (*nSize - 1)) && (!isFound); i++)
                {
                    if (strcmp(sInputTopic, Records[i].sTopic) == 0)
                    {
                        isFound = 1;
                    }
                }
                
                if (!isFound)
                {
                    printf("There are no topics with the name: %s\n", sInputTopic);
                }
            }
            
            
            if (isFound)
            {
                if (strcmp(sInputTopic, "0") == 0)
                {
                    isPlaying = 0;
                }
                else
                {
                    printf("You have selected : %s\n", sInputTopic);
                    
                    // find
                    for (i = 0; i < (*nSize - 1); i++)
                    {
                        if (strcmp(Records[i].sTopic, sInputTopic) == 0)
                        {
                            strcpy(sQuesArray[nQues], Records[i].sQuestion);
                            nQues++;
                        }
                    }
                    
                    // print current score
                    printf("----- SCORE : %d -----\n\n", CurrentPlayRec->nCP_Score);
                    
                    // randomize questions under the topic
                    srand(time(0));
                    int num = (rand() % nQues);
                    strcpy(CurrentPlayRec->sCP_Question, sQuesArray[num]);
                    printf("%d.) %s\n", num + 1, CurrentPlayRec->sCP_Question);
                    
                    // store answers and choices in currentplay array
                    for (j = 0; (j < (*nSize - 1)) || (!bIsStored); j++)
                    {
                        if (strcmp(CurrentPlayRec->sCP_Question, Records[j].sQuestion) == 0)
                        {
                            strcpy(CurrentPlayRec->sCP_Answer, Records[j].sAnswer);
                            strcpy(CurrentPlayRec->sCP_Choice1, Records[j].sChoice1);
                            strcpy(CurrentPlayRec->sCP_Choice2, Records[j].sChoice2);
                            strcpy(CurrentPlayRec->sCP_Choice3, Records[j].sChoice3);
                            
                            // print choices
                            printf("- %s\n", Records[j].sChoice1);
                            printf("- %s\n", Records[j].sChoice2);
                            printf("- %s\n\n", Records[j].sChoice3);
                            
                            bIsStored = 1;
                        }
                    }
                    
                    // get input answer from user
                    scanf("%s", sInputAnswer);
                    
                    if (strcmp(sInputAnswer, CurrentPlayRec->sCP_Answer) == 0)
                    {
                        CurrentPlayRec->nCP_Score++;
                        printf("\n[0] Go back to menu\n");
                    }
                    else
                    {
                        printf("Sorry, incorrect answer. | ");
                        printf("Correct: %s\n", CurrentPlayRec->sCP_Answer);
                        printf("\n[0] Go back to menu\n");
                    }
                }
            }
            printf("----- SCORE : %d -----\n\n", CurrentPlayRec->nCP_Score);
        }
    }
    if (!bIsEmpty)
        exportScore(CurrentPlayRec);
    *nSize = *backMenu(Records, nSize);
}

/* viewScores shows all current scores inside the file "score.txt"
 @param <none>
 @return <none>
 Pre-condition: score.txt is existing
 */
void
viewScores()
{
    printf("----- Viewing Scores -----\n\n");
    
    int nRow = 1;
    // declare file pointer variable
    FILE * fp;
    
    fp = fopen("score.txt", "r");
    
    // declare temporary variables for scanned names and scores from text file
    char sfName[51];
    int nfScore;
    
    printf("Row #\t");
    printf("Player Name\t");
    printf("Score\t\n");
    
    while ((fscanf(fp, "%s\n", sfName) == 1) && (!feof(fp)))
    {
        printf("%d\t", nRow);
        nRow++;
        printf("%s\t\t", sfName);
        // get score
        fscanf(fp, "%d\n", &nfScore);
        printf("%d\t\n", nfScore);
    }
    
    if (strcmp(sfName, "") == 0)
    {
        printf("There are currently no scores available.\n");
    }
    
    printf("\n");
    
    fclose(fp);
}

/* QuizGame allows the user to play the quiz, view the scores, as well as go back to the Main Menu
 @param Records is an array of structures which stores the records
 *CurrentPlayRec is a pointer to the struct CurrentPlayRec wherein the name and score is stored
 nSize is an integer which indicates the current number of non-empty elements of the array Records
 @return <none>
 Pre-condition: User has selected Play from the Main Menu and has not yet opted to go back to Main Menu
 */
void
QuizGame(struct RecordTag Records[], struct CurrentPlayTag *CurrentPlayRec, int nSize)
{
    bool bIsQuit = 0;
    int nInput;
    
    printf("----- Quiz Game -----\n\n");
     
    while (bIsQuit == 0)
    {
        // display playQuiz options
        printf("[1] Play\n");
        printf("[2] View Scores\n");
        printf("[3] Go back to MAIN MENU\n");
        
        scanf("%d", &nInput);
        
        switch (nInput)
        {
            case 1:
                playQuiz(Records, CurrentPlayRec, &nSize);
                break;
                
            case 2:
                viewScores();
                break;
                
            case 3:
                printf("Exiting...\n");
                bIsQuit = 1;
                break;
                
            default:
                printf("Please select one of the options provided.\n");
                break;
        }
    }
}



int
main()
{
    bool bIsQuit = 0;
    int nInput;
    
    int nSize = 1;
    struct RecordTag Records[REC_SIZE];
    struct CurrentPlayTag CurrentPlayRec;
    
    // clear previous contents of masterfile
    updateMasterFile(Records, nSize, 'w');
    
    do
    {
        // display main menu GUI
        displayMenu();
        scanf("%d", &nInput);
        
        switch (nInput)
        {
            case 1:
                manageData(&(Records[0]), &nSize);
                break;
                
            case 2:
                QuizGame(&(Records[0]), &CurrentPlayRec, nSize);
                break;
                
            case 3:
                printf("Exiting ...\n");
                bIsQuit = 1;
                break;
                
            default:
                printf("Please select one of the options provided.\n");
                break;
        }
        
    }
    while (bIsQuit == 0);
    
    // USED FOR DEBUGGING ONLY (prints out records)
    for (int i = 0; i < (nSize - 1); i++)
    {
        printf("%s, %d, %s, %s, %s, %s, %s\n\n", Records[i].sTopic, Records[i].nQNum, Records[i].sQuestion, Records[i].sChoice1, Records[i].sChoice2, Records[i].sChoice3, Records[i].sAnswer);
    }
    
    return 0;
}
