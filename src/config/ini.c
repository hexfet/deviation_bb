/* inih -- simple .INI file parser

inih is released under the New BSD license (see LICENSE.txt). Go to the project
home page for more info:

http://code.google.com/p/inih/

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "ini.h"

#define MAX_LINE 200
#define MAX_SECTION 50
#define MAX_NAME 50
//#define DEBUG_FGETS
#ifdef DEBUG_FGETS
    #define dbgini printf
#else
    #define dbgini if(0) printf
#endif
/* Strip whitespace chars off end of given string, in place. Return s. */
static char* rstrip(char* s)
{
    char* p = s + strlen(s);
    while (p > s && isspace((unsigned char)(*--p)))
        *p = '\0';
    return s;
}

/* Return pointer to first non-whitespace char in given string. */
static char* lskip(const char* s)
{
    while (*s && isspace((unsigned char)(*s)))
        s++;
    return (char*)s;
}

/* Return pointer to first char c or ';' comment in given string, or pointer to
   null at end of string if neither found. ';' must be prefixed by a whitespace
   character to register as a comment. */
static char* find_char_or_comment(const char* s, char c)
{
    int was_whitespace = 0;
    while (*s && *s != c && !(was_whitespace && *s == ';')) {
        was_whitespace = isspace((unsigned char)(*s));
        s++;
    }
    return (char*)s;
}

/* Version of strncpy that ensures dest (size bytes) is null-terminated. */
static char* strncpy0(char* dest, const char* src, size_t size)
{
    strncpy(dest, src, size);
    dest[size - 1] = '\0';
    return dest;
}

/* See documentation in header file. */
int ini_parse_file(FILE* file,
                   int (*handler)(void*, const char*, const char*,
                                  const char*),
                   void* user)
{
    /* Uses a fair bit of stack (use heap instead if you need to) */
    char data[MAX_LINE];
    char *line, *eol;
    char section[MAX_SECTION] = "";
    char prev_name[MAX_NAME] = "";

    char* start;
    char* end;
    char* name;
    char* value;
    int lineno = 0;
    int error = 0;
    int done = 0;
    int len = 0;

    /* Scan through file line by line */
    line = eol = data + sizeof(data);
    while (1) {
        dbgini("*Start: %d : '%s' LINE: %d, EOL: %d\n", len, eol, (int)(line - data), (int)(eol - line));
        if(done == -1)
            break;
        if (eol >= data + sizeof(data) -1) {
            if (eol == data + sizeof(data) -1) {
                dbgini("**Setting Last Char\n");
                //last character in data read is an eol
                line = eol;
            }
            if(data != line )
                //No end of line
                memmove(data, line, eol - line);
            eol = data + (eol - line);
            line = data;
            int bytes = fread(eol, 1, sizeof(data) - (eol - data), file);
            len = eol - data + bytes;
            dbgini("*Read: %d : '%s' LINE: %d, EOL: %d\n", len, line, (int)(line - data), (int)(eol -line));
        } else if(eol != data || *eol == '\0') {
            line = eol + 1;
        }
        if (line >= data + len || *line == '\0') {
            dbgini("**End of file\n");
            break;
        }
        for (eol = line; eol < data + len; eol++) {
            if(*eol == '\n') {
                *eol = '\0';
                break;
            }
        }
        dbgini("*Find EOL: %d : '%s' LINE: %d, EOL: %d\n", len, line, (int)(line - data), (int)(eol -line));
        if (eol == data + len) {
            continue;
        }
        //printf("%d: %s\n", lineno, line);
        lineno++;

        start = line;
#if INI_ALLOW_BOM
        if (lineno == 1 && (unsigned char)start[0] == 0xEF &&
                           (unsigned char)start[1] == 0xBB &&
                           (unsigned char)start[2] == 0xBF) {
            start += 3;
        }
#endif
        start = lskip(rstrip(start));

        if (*start == ';' || *start == '#') {
            /* Per Python ConfigParser, allow '#' comments at start of line */
        }
#if INI_ALLOW_MULTILINE
        else if (*prev_name && *start && start > line) {
            /* Non-black line with leading whitespace, treat as continuation
               of previous name's value (as per Python ConfigParser). */
            if (!handler(user, section, prev_name, start) && !error)
                error = lineno;
        }
#endif
        else if (*start == '[') {
            /* A "[section]" line */
            end = find_char_or_comment(start + 1, ']');
            if (*end == ']') {
                *end = '\0';
                strncpy0(section, start + 1, sizeof(section));
                *prev_name = '\0';
            }
            else if (!error) {
                /* No ']' found on section line */
                error = lineno;
            }
        }
        else if (*start && *start != ';') {
            /* Not a comment, must be a name[=:]value pair */
            end = find_char_or_comment(start, '=');
            if (*end != '=') {
                end = find_char_or_comment(start, ':');
            }
            if (*end == '=' || *end == ':') {
                *end = '\0';
                name = rstrip(start);
                value = lskip(end + 1);
                end = find_char_or_comment(value, '\0');
                if (*end == ';')
                    *end = '\0';
                rstrip(value);

                /* Valid name[=:]value pair found, call handler */
                strncpy0(prev_name, name, sizeof(prev_name));
                
                done = handler(user, section, name, value);
                if (done != 1 && !error)
                    error = lineno;
            }
            else if (!error) {
                /* No '=' or ':' found on name[=:]value line */
                error = lineno;
            }
        }
    }

    return error;
}

/* See documentation in header file. */
int ini_parse(const char* filename,
              int (*handler)(void*, const char*, const char*, const char*),
              void* user)
{
    FILE* file;
    int error;

    file = fopen(filename, "r");
    if (!file)
        return -1;
    error = ini_parse_file(file, handler, user);
    fclose(file);
    return error;
}
