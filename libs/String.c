//
// Created by pabluxfirpux on 12/20/25.
//
#include <stdio.h>
#include "String.h"

#include <stdlib.h>
#include <string.h>

String *STRING_newString(char* chars) {
    String *pstring = (String *)malloc(sizeof(String));
    pstring->length = strlen(chars);
    pstring->characters = chars;
    return pstring;
}

void STRING_delete(String* pstring) {
    free(pstring);
}

String* STRING_concatenate(String* pstring1, char* chars) {
    int size = pstring1->length + strlen(chars);
    char* result = malloc( size * sizeof(char));
    for (int i = 0; i < size; i++) {
        if (i < pstring1->length) {
            result[i] = pstring1->characters[i];
        } else {
            result[i] = chars[i - pstring1->length];
        }
    }

    String *pstring2 = malloc(sizeof(String));
    pstring2->length = size;
    pstring2->characters = result;
    return pstring2;
}

char STRING_charAt(String* pstring, int index) {
    if (index < 0 || index >= pstring->length) {
        printf("index of array out of bounds\n");
        exit(1);
    }
    return pstring->characters[index];
}

bool STRING_equals(String* pstring1, String* pstring2) {
    if (pstring1->length != pstring2->length) {
        return false;
    }
    for (int i = 0; i < pstring1->length; i++) {
        if (pstring1->characters[i] != pstring2->characters[i]) {
            return false;
        }
    }
    return true;
}
