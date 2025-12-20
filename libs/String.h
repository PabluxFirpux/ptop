//
// Created by pabluxfirpux on 12/20/25.
//

#ifndef CLIBS_STRING_H
#define CLIBS_STRING_H

#include <stdbool.h>

typedef struct {
    char* characters;
    size_t length;
} String;

String* STRING_newString(char* chars);
void STRING_delete(String* pstring);
String *STRING_concatenate(String* pstring1, char* chars);
char STRING_charAt(String* pstring, int index);
bool STRING_equals(String* pstring1, String* pstring2);

#endif //CLIBS_STRING_H