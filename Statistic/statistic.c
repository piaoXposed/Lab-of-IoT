#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define a singly linked list node structure
struct Node {
    char data[100];
    int count;
    struct Node *next;
};

// Function to add a word or symbol to the linked list or update its count
void AddOrUpdate(struct Node **head, const char *data) {
    struct Node *current = *head;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }

    // If not found, add a new node to the list
    struct Node *NewNode = (struct Node *) malloc(sizeof(struct Node));
    strcpy(NewNode->data, data);
    NewNode->count = 1;
    NewNode->next = *head;
    *head = NewNode;
}

// Function to find the most frequent node in the linked list
struct Node *FindMostWord(struct Node *head) {
    struct Node *MaxNode = head;

    while (head != NULL) {
        if (head->count > MaxNode->count) {
            MaxNode = head;
        }
        head = head->next;
    }

    return MaxNode;
}


// Function to count occurrences of a specific word
int CountWord(struct Node *head, const char *target) {
    while (head != NULL) {
        if (strcmp(head->data, target) == 0)
            return head->count;
        head = head->next;
    }
    return 0; // Word not found
}

int Punctuation[266], CountPunctuation = 0;
char MostPunctuation;

// Function to find the most frequent punctuation and counts in the linked list
void FindMostPunctuation() {
    for (int i = 0; i < 265; i++) {
        if (Punctuation[i] > CountPunctuation) {
            CountPunctuation = Punctuation[i];
            MostPunctuation = (char) i;
        }
    }

}

int main() {
    FILE *InputFile = fopen("input.txt", "r");
    if (!InputFile) {
        fprintf(stderr, "Error opening input InputFile.\n");
        return 1;
    }

    char line[1000];

    struct Node *WordList = NULL; // Linked list for words
    struct Node *PunctuationList = NULL; // Linked list for Punctuations
    int TotalWords = 0, totalPunctuations = 0; // Total word and punctuations count

    while (fgets(line, sizeof(line), InputFile) != NULL) {
        char word[100];
        char *token = strtok(line, " \t\n");

        while (token != NULL) {
            // Clean and format the word
            char CleanedWord[100] = "";

            int i = 0, j = 0;
            for (; token[i] != '\0'; i++) {
                if (isalpha(token[i])) {
                    CleanedWord[j++] = tolower(token[i]);
                } else if (token[i] != ' ' && (token[i] < '0' || token[i] > '9')) {
                    Punctuation[(int) token[i]]++;
                    totalPunctuations++;
                }
            }
            CleanedWord[j] = '\0';

            if (strlen(CleanedWord) > 0) {
                AddOrUpdate(&WordList, CleanedWord);
                TotalWords++;
            }

            token = strtok(NULL, " \t\n");
        }
    }

    fclose(InputFile);

    // Find the most frequent word
    struct Node *MostWord = FindMostWord(WordList);
    FindMostPunctuation();

    // Print the results
    FILE *OutputFile = fopen("tongji.txt", "w");
    if (!OutputFile) {
        fprintf(stderr, "Error opening output InputFile.\n");
        return 1;
    }

    fprintf(OutputFile, "统计结果共英文单词%d个，其他符号%d个。\n", TotalWords, totalPunctuations);
    fprintf(OutputFile, "出现最多的英文单词为%s，出现次数%d。\n", MostWord->data, MostWord->count);
    fprintf(OutputFile, "出现最多的符号为%c，出现次数%d。\n", MostPunctuation, CountPunctuation);

    // User input and output for a specific word
    char UserWord[100];
    printf("Enter a word to get its count: ");
    scanf("%s", UserWord);

    // Clean and format the user input
    char CleanedUserWord[100] = "", userPunctuation = ' ';
    int k, l = 0;

    for (k = 0; UserWord[k] != '\0'; k++) {
        if (isalpha(UserWord[k])) {
            CleanedUserWord[l++] = tolower(UserWord[k]);
        } else if (UserWord[k] != ' ') {
            userPunctuation = UserWord[k];
        }
    }
    CleanedUserWord[l] = '\0';

    int UserWordCount = CountWord(WordList, CleanedUserWord);
    if (userPunctuation != ' ')
        fprintf(OutputFile, "Count of '%c': %d\n", userPunctuation, Punctuation[(int) userPunctuation]);
    else
        fprintf(OutputFile, "Count of '%s': %d\n", CleanedUserWord, UserWordCount);

    fclose(OutputFile);

    // Clean up the linked list
    while (WordList != NULL) {
        struct Node *temp = WordList;
        WordList = WordList->next;
        free(temp);
    }

    return 0;
}