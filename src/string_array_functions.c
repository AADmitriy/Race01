#include <stdlib.h>
#include <string.h>

#include "minilibmx.h"

void mx_del_strarr(char ***arr) {
    if (arr == NULL || *arr == NULL) {
        return;
    }

    char **temp = *arr;

    for (int i = 0; temp[i] != NULL; i++) {
        mx_strdel(&temp[i]);
    }

    free(*arr);

    *arr = NULL;
}

int mx_find_array_length(char **arr) {
    int length = 0;

    while (arr[length] != NULL) {
        length++;
    }

    return length;
}

char **duplicate_string_array(char **arr) {
    if (arr == NULL) {
        return NULL;
    }

    int length = mx_find_array_length(arr);

    char **duplicate_arr = (char **)malloc((length + 1) * sizeof(char *));
    if (duplicate_arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        char *str_dup = mx_strdup(arr[i]);
        
        if (str_dup == NULL) {
            duplicate_arr[i] = NULL;
            mx_del_strarr(&duplicate_arr);

            return NULL;
        }

        duplicate_arr[i] = str_dup;
    }

    duplicate_arr[length] = NULL;

    return duplicate_arr;
}

char **mx_join_string_arrays(char **arr1, char **arr2) {
    if (arr1 == NULL && arr2 == NULL) {
        return NULL;
    }

    if (arr1 == NULL) {
        char **dupl_arr = duplicate_string_array(arr2);
        if (dupl_arr == NULL) {
            return NULL;
        }

        mx_del_strarr(&arr2);

        return dupl_arr;
    }

    if (arr2 == NULL) {
        char **dupl_arr = duplicate_string_array(arr1);
        if (dupl_arr == NULL) {
            return NULL;
        }

        mx_del_strarr(&arr1);

        return dupl_arr;
    }

    int len1 = mx_find_array_length(arr1);
    int len2 = mx_find_array_length(arr2);

    char **joined_array = (char **)malloc(sizeof(char *) * (len1 + len2 + 1));
    if (joined_array == NULL) {
        return NULL;
    }

    for (int i = 0; i < len1; i++) {
        joined_array[i] = mx_strdup(arr1[i]);
    }

    for (int i = 0; i < len2; i++) {
        joined_array[len1 + i] = mx_strdup(arr2[i]);
    }

    joined_array[len1 + len2] = NULL;

    mx_del_strarr(&arr1);
    mx_del_strarr(&arr2);

    return joined_array;
}

