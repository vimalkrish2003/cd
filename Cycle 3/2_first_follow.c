#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODS 50
#define MAX_LEN 50

int n;
char prods[MAX_PRODS][MAX_LEN];
char firsts[26][MAX_LEN];
int is_first_done[26];
char follows[26][MAX_LEN];
int is_follow_done[26];

int isTerminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

void addToSet(char* set, char ch, int* index) {
    // Check if character already exists in set
    for(int i = 0; set[i] != '\0'; i++) {
        if(set[i] == ch) return;
    }
    if(*index < MAX_LEN - 1) {
        set[(*index)++] = ch;
    }
}

void first(char nonterm) {
    if (is_first_done[nonterm - 'A']) {
        return;
    }
    is_first_done[nonterm - 'A'] = 1;

    int index = 0;
    char curr_firsts[MAX_LEN] = {0};

    for (int i = 0; i < n; i++) {
        if (prods[i][0] == nonterm) {
            int curr_index = 2;
            int added_epsilon = 0;
            
            while (prods[i][curr_index] != '\0' && index < MAX_LEN - 1) {
                if (isTerminal(prods[i][curr_index])) {
                    addToSet(curr_firsts, prods[i][curr_index], &index);
                    break;
                }

                first(prods[i][curr_index]);
                int has_epsilon = 0;
                
                for (int k = 0; firsts[prods[i][curr_index] - 'A'][k] != '\0'; k++) {
                    if (firsts[prods[i][curr_index] - 'A'][k] == 'e') {
                        has_epsilon = 1;
                    } else {
                        addToSet(curr_firsts, firsts[prods[i][curr_index] - 'A'][k], &index);
                    }
                }
                
                if (!has_epsilon) break;
                if (prods[i][curr_index + 1] == '\0' && !added_epsilon) {
                    addToSet(curr_firsts, 'e', &index);
                    added_epsilon = 1;
                }
                curr_index++;
            }
            
            if (curr_index == 2 && prods[i][curr_index] == 'e') {
                addToSet(curr_firsts, 'e', &index);
            }
        }
    }
    curr_firsts[index] = '\0';
    strncpy(firsts[nonterm - 'A'], curr_firsts, MAX_LEN - 1);
    firsts[nonterm - 'A'][MAX_LEN - 1] = '\0';
}

void follow(char nonterm) {
    if (is_follow_done[nonterm - 'A']) {
        return;
    }
    is_follow_done[nonterm - 'A'] = 1;

    int index = 0;
    char curr_follows[MAX_LEN] = {0};

    if (nonterm == prods[0][0]) {
        addToSet(curr_follows, '$', &index);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 2; prods[i][j] != '\0'; j++) {
            if (prods[i][j] == nonterm) {
                if (prods[i][j + 1] != '\0') {
                    int k = j + 1;
                    int should_add_follow = 1;
                    
                    while (prods[i][k] != '\0' && should_add_follow) {
                        if (isTerminal(prods[i][k])) {
                            addToSet(curr_follows, prods[i][k], &index);
                            should_add_follow = 0;
                        } else {
                            int has_epsilon = 0;
                            for (int m = 0; firsts[prods[i][k] - 'A'][m] != '\0'; m++) {
                                if (firsts[prods[i][k] - 'A'][m] == 'e') {
                                    has_epsilon = 1;
                                } else {
                                    addToSet(curr_follows, firsts[prods[i][k] - 'A'][m], &index);
                                }
                            }
                            if (!has_epsilon) {
                                should_add_follow = 0;
                            }
                        }
                        k++;
                    }
                    
                    if (should_add_follow && prods[i][0] != nonterm) {
                        follow(prods[i][0]);
                        for (k = 0; follows[prods[i][0] - 'A'][k] != '\0'; k++) {
                            addToSet(curr_follows, follows[prods[i][0] - 'A'][k], &index);
                        }
                    }
                } else if (prods[i][0] != nonterm) {
                    follow(prods[i][0]);
                    for (int k = 0; follows[prods[i][0] - 'A'][k] != '\0'; k++) {
                        addToSet(curr_follows, follows[prods[i][0] - 'A'][k], &index);
                    }
                }
            }
        }
    }

    curr_follows[index] = '\0';
    strncpy(follows[nonterm - 'A'], curr_follows, MAX_LEN - 1);
    follows[nonterm - 'A'][MAX_LEN - 1] = '\0';
}

int main() {
    printf("Enter the number of productions\n");
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_PRODS) {
        printf("Invalid number of productions\n");
        return 1;
    }

    printf("Enter productions: \n");
    for (int i = 0; i < n; i++) {
        scanf("%49s", prods[i]);
    }

    memset(is_first_done, 0, sizeof(is_first_done));
    memset(is_follow_done, 0, sizeof(is_follow_done));
    memset(firsts, 0, sizeof(firsts));
    memset(follows, 0, sizeof(follows));

    for (int i = 0; i < n; i++) {
        if (!is_first_done[prods[i][0] - 'A']) {
            first(prods[i][0]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (!is_follow_done[prods[i][0] - 'A']) {
            follow(prods[i][0]);
        }
    }

    printf("\nFIRST Sets:\n");
    for (int i = 0; i < 26; i++) {
        if (is_first_done[i]) {
            printf("FIRST(%c) = {%s}\n", i + 'A', firsts[i]);
        }
    }

    printf("\nFOLLOW Sets:\n");
    for (int i = 0; i < 26; i++) {
        if (is_follow_done[i]) {
            printf("FOLLOW(%c) = {%s}\n", i + 'A', follows[i]);
        }
    }

    return 0;
}