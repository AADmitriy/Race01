#include <stdlib.h>

#include "minilibmx.h"

char *mx_concat_words(char **words) {
    if (words == NULL || words[0] == NULL) {
        return NULL;
    }

    char *result_sentence = mx_strdup(words[0]);

    for (int i = 1; words[i] != NULL; i++) {
        char *temp = result_sentence;

        result_sentence = mx_strjoin(result_sentence, " ");
        mx_strdel(&temp);

        temp = result_sentence;
        result_sentence = mx_strjoin(result_sentence, words[i]); 
        mx_strdel(&temp);
    }

    return result_sentence;
}

