#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_WORD_COUNT 2000
#define MAX_WORD_SIZE 20
#define MAX_VEKTOR_SIZE 400
#define MAX_DICT_SIZE 300000
#define MAX_LINE_SIZE 10000
#define MAX_INPUT_TEXT_SIZE 200000
#define MAX_USER_INPUT_SIZE 100
#define MAX_USER_INPUT_WORD 10
#define dict_file "dictionary.txt"

char *mystrcpy(char *destination, const char *source);
int mystrlen(const char* str);
void remove_punctuation(char *word);
int findOccurrences(const char* word, const char words[][MAX_WORD_SIZE]);
int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]);
int read_text(const char * text_file, const char * ignore_file, char words[][MAX_WORD_SIZE]);
double dissimilarity(char * w1, char * w2, const char * file_name);
int histogram(const int occurrences[]);

int main() {
    // calling read_dict
    char dictionary[MAX_WORD_COUNT][MAX_WORD_SIZE];
    int numWords = read_dict("dictionary.txt", dictionary);
    if (numWords < 0) {
        printf("Error at reading dictionary");
    } else {
        printf("Number of words read: %d\n", numWords);
    }
    // calling read_text
    char input_text[MAX_INPUT_TEXT_SIZE][MAX_WORD_SIZE];
    int numText = read_text("input.txt", "ignore.txt", input_text);
    if (numText < 0) {
        printf("Error at reading dictionary");
    } else {
        printf("Number of words read: %d\n", numText);
    }
    // taking input from user and count the words
    int word_count = 1;
    char user_input[MAX_USER_INPUT_SIZE];
    printf("Enter word(s): ");
    scanf("%[^\n]", user_input); // take from start to \n
    for (int i = 0; i < mystrlen(user_input); i++) {
        if (user_input[i] == ' ') {
            word_count++;
        }
    }

    if (word_count == 1) { 
        int occurrences = findOccurrences(user_input, input_text);
        if (occurrences != 0) {
            printf("“%s” appears in “input.txt” %d times.\n", user_input, occurrences);
        } else {
            double temp = 0.0;
            int k = -1; // Initialize k to -1
            for (int i = 0; strcmp(dictionary[i], "-") != 0; i++) {
                if (temp < dissimilarity(user_input, dictionary[i], dict_file) && dissimilarity(user_input, dictionary[i], dict_file) != INFINITY) {
                    temp = dissimilarity(user_input, dictionary[i], dict_file);
                    k = i;
                }
            }
            if (k != -1) { // Check if a closest word is found
                int sim_occurrences = findOccurrences(dictionary[k], input_text);
                if (sim_occurrences != 0) {
                    printf("“%s” doesn’t appear in “input.txt” but “%s” appears %d times.\n", user_input, dictionary[k], sim_occurrences);
                } else {
                    printf("“%s” doesn’t appear in “input.txt”.\n", user_input);
                }
            } else {
                printf("No closest word found for “%s”.\n", user_input);
            }
        }
    } else if (word_count > 1) {
        char user_input_ar[MAX_USER_INPUT_WORD][MAX_USER_INPUT_SIZE];
        int word_index = 0;
        int j=0;
        for (int i = 0; i < mystrlen(user_input); i++) {
            if (user_input[i] == ' ') {
                user_input_ar[word_index][j] = '\0'; // Add null terminator to mark the end of the word
                word_index++;
                j = 0;
            } else {
                user_input_ar[word_index][j] = user_input[i];
                j++;
            }
        }
        user_input_ar[word_index][j] = '\0'; // Add null terminator to mark the end of the last word

        int occurrences_ar[MAX_USER_INPUT_WORD]; // Array to store the occurrences for each word
        for (int i = 0; i < word_count; i++) {
            occurrences_ar[i] = 0;
        }
        for (int i = 0; i < word_count; i++) {
            if (findOccurrences(user_input_ar[i], input_text) == 0) {
                double temp = 0.0;
                int k = -1;
                for (int j = 0; strcmp(dictionary[j], "-") != 0; j++) {
                    if (temp < dissimilarity(user_input_ar[i], dictionary[j], dict_file) && dissimilarity(user_input_ar[i], dictionary[j], dict_file) != INFINITY) {
                        temp = dissimilarity(user_input_ar[i], dictionary[j], dict_file);
                        k = j;
                    }
                }
                if (k != -1) {
                    occurrences_ar[i] = -findOccurrences(dictionary[k], input_text);
                }
            } else {
                occurrences_ar[i] = findOccurrences(user_input_ar[i], input_text);
            }
    }

        // Determine the scale using the histogram function
        int scale = histogram(occurrences_ar);
        printf("Scale: %d\n\n", scale);
        // Print the histogram
        for (int i = 0; i <= word_index; i++) {
            if (occurrences_ar[i] > 0) {
                printf("%-15s", user_input_ar[i]);
                for (int j = 0; j < occurrences_ar[i] / scale; j++) {
                    printf("*");
                }
                printf("\n");
            } else if (occurrences_ar[i] < 0) {
                printf("%s->\n", user_input_ar[i]);
                double temp = 0.0;
                int k = -1;
                for (int j = 0; strcmp(dictionary[j], "-") != 0; j++) {
                    if (temp < dissimilarity(user_input_ar[i], dictionary[j], dict_file) && dissimilarity(user_input_ar[i], dictionary[j], dict_file) != INFINITY) {
                        temp = dissimilarity(user_input_ar[i], dictionary[j], dict_file);
                        k = j;
                    }
                }
                int sim_occurrences = -occurrences_ar[i];
                if (sim_occurrences != 0) {
                    printf("%-15s", dictionary[k]);
                    for (int j = 0; j < sim_occurrences / scale; j++) {
                        printf("+");
                    }
                    printf("\n");
                }
            } else {
                printf("%-15s", user_input_ar[i]);
                printf("NO MATCH\n");
            }
        }
    }
    return 0;
}
char *mystrcpy(char *destination, const char *source) {
    char *ptr = destination;
    while (*source != '\0') {
        *ptr = *source;
        ptr++;
        source++;
    }
    *ptr = '\0';  // Append null character at the end
    return destination;
}
int mystrlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
void remove_punctuation(char *word) {
    // Remove punctuation characters from a word
    int len = mystrlen(word);
    int i, j;
    for (i = 0, j = 0; i < len; i++) {
        if (!ispunct((unsigned char)word[i])) {
            word[j++] = (unsigned char)word[i];
        }
    }
    word[j] = '\0';
}
int findOccurrences(const char* word, const char words[][MAX_WORD_SIZE]) {
    int count = 0;
    for (int i = 0; strcmp(words[i], "-") != 0; i++) {
        if (strcmp(word, words[i]) == 0) {
            count++;
        }
    }
    return count;
}

int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error opening dictionory file!\n");
        return -1;
    }
    int count = 0;
    char line[MAX_LINE_SIZE]; // Maximum line size
    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (count >= MAX_WORD_COUNT) {
            fclose(fp);
            return -2; // Exceeded maximum word count
        }
        char word[MAX_WORD_SIZE];
        if (sscanf(line, "%s", word) != 1) {
            fclose(fp);
            return -3; // Error reading word
        }
        sscanf(line, "%s", word);
        mystrcpy(dict[count], word); // copy to array
        count++;
    }
    mystrcpy(dict[count], "-"); // add sentinel value "-"
    fclose(fp);
    return count;
}
int read_text(const char * text_file, const char * ignore_file, char words[][MAX_WORD_SIZE]) {
    FILE *fp = fopen(text_file, "r");
    if (fp == NULL) {
        printf("Error opening text file!\n");
        return -1;
    }
    FILE *ignore_fp = fopen(ignore_file, "r");
    if (ignore_fp == NULL) {
        printf("Error opening ignore file!\n");
        fclose(fp);
        return -2;
    }
    // Make the ignore list 
    char ignore_words[MAX_WORD_COUNT][MAX_WORD_SIZE];
    int ignore_count = 0;
    while (fscanf(ignore_fp, "%s", ignore_words[ignore_count]) == 1) {
        ignore_count++;
        if (ignore_count >= MAX_WORD_COUNT) break;
    }
    fclose(ignore_fp);
    int word_count = 0;
    char word[MAX_WORD_SIZE];
    while (fscanf(fp, "%s", word) == 1) {
        remove_punctuation(word);
        // Check if word is in the ignore list
        int ignore = 0;
        for (int i = 0; i < ignore_count; i++) {
            if (strcmp(word, ignore_words[i]) == 0) {
                ignore = 1;
                break;
            }
        }
        if (!ignore) {
            mystrcpy(words[word_count], word);
            word_count++;
        }
    }
    mystrcpy(words[word_count], "-"); // Append sentinel value
    fclose(fp);
    return word_count;
}
double dissimilarity(char * w1, char * w2, const char * file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error opening dictionory file!\n");
        return -1;
    }
    double vector_w1[MAX_VEKTOR_SIZE], vector_w2[MAX_VEKTOR_SIZE];
    char line[MAX_LINE_SIZE], word[MAX_WORD_SIZE];
    int v1_counter = 0;
    // take vectors of w1 
    while (fgets(line, sizeof(line), fp) != NULL) {
        fscanf(fp, "%s", word);
        if (strcmp(w1, word) == 0) {
            while (fscanf(fp, "%lf", &vector_w1[v1_counter]) == 1) {
                v1_counter++;
                if (v1_counter >= MAX_VEKTOR_SIZE) break;
            }
            break;
        }
    }
    int v2_counter = 0;
    rewind(fp); // start from beginning again
    // take vectors of w2
    while (fgets(line, sizeof(line), fp) != NULL) {
        fscanf(fp, "%s", word);
        if (strcmp(w2, word) == 0) {
            while (fscanf(fp, "%lf", &vector_w2[v2_counter]) == 1) {
                v2_counter++;
                if (v2_counter >= MAX_VEKTOR_SIZE) break;
            }
            break;
        }
    }
    fclose(fp);
    double disim = 0.0;
    // calculate the dissimilarity using w1 and w2 vectors
    for (int i=0; i < v1_counter && i < v2_counter; i++) {
        disim += pow((vector_w1[i]-vector_w2[i]), 2);
    }
    return 1.0/disim; // return the similarity (inverse of disim.)
}
int histogram(const int occurrences[]) {
    int max_occurrences = 0;
    // Find the maximum number of occurrences
    for (int i = 0; i < MAX_USER_INPUT_WORD; i++) {
        if (occurrences[i] > max_occurrences) {
            max_occurrences = occurrences[i];
        }
    }
    // Determine the scale based on the maximum number of occurrences
    double scale = max_occurrences / 20; 
    return scale+1; // return the scale for printing the histogram
}
