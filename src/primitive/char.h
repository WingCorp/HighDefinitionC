/**
 * @brief Structs for wrapping char and char pointers
 * 
 * @file char.h
 * @author WingCorp
 * @date 2018-06-15
 */

typedef struct _Char {
    char val;
} Char;

typedef struct _String {
    char* val;
    int length;
} String;

