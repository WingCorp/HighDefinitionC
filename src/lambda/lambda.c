#include "lambda.h"
#include "fail.h"

#include <string.h>
#include <stdlib.h>
#include <varargs.h>
#include <stdio.h>
#include <ctype.h>


#pragma region SCANNER

typedef enum _TokenType
{
    T_ARROW,  //=>
    T_LPAR,   //(
    T_RPAR,   //)
    T_VAR,    //\w+
    T_INT,    //\d+
    T_UINT,   //\d+u
    T_LONG,   //\d+l
    T_ULONG,  //\d+ul
    T_FLOAT, //\d+\.\d?f
    T_DOUBLE, //\d+\.\d?
    T_CHAR,   //'
    T_STRING, //"
    T_ADD,    //+
    T_SUB,    //-
    T_MUL,    //*
    T_DIV,    // \/
    T_MOD,    //%
    T_EQ,     //==
    T_NE,     //!=
    T_GT,     //>
    T_LT,     //<
    T_GEQ,    //>=
    T_LEQ,    //<=
    T_AND,    //&&
    T_OR,     //||
    T_NOT,    //!
    T_BAND,   //&
    T_BOR,    //|
    T_XOR,    //^
    T_COM,    //~
    T_LEFT,   //<<
    T_RIGHT,  //>>
    T_IF,     //?
    T_ELSE,   //:
    T_COMMA,  //,
    T_SC      //;
} TokenType;

typedef struct _Token
{
    TokenType type;
    char* var_name;
    Dynamic dyn_val;
} Token;

void check_suffix(char suffix, bool second, int pos)
{
    if (suffix != 'l' || (!second && (suffix != 'u' || suffix != 'f')))
    {
        char msg[255];
        sprintf(msg, "Unknown suffix at position %d\n", pos);
        failwith(msg);
    }
}

Token* scan(char* code)
{
    int len = strlen(code);
    Token* tokens = malloc(sizeof(Token) * len);
    int t = 0;
    int i;
    while (i < len)
    {
        char c1 = code[i];
        char c2 = code[i + 1];
        if (isblank(c1))
        {
            i++;
            continue;
        }
        if (c1 == '=' && c2 == '>')
        {
            tokens[t++] = (Token){.type = T_ARROW};
            i += 2;
            continue;
        }
        if (c1 == '(') 
        {
            tokens[t++] = (Token){.type = T_LPAR};
            i++;
            continue;
        }
        if (c1 == ')') {
            tokens[t++] = (Token){.type = T_RPAR};
            i++;
            continue;
        }
        if (isalpha(c1))
        {
            int c = 0;
            while(isalpha(code[i + c])) 
            {
                c++;
            }
            char* var = malloc((sizeof(char) * c) + 1);
            var[c] = '\0';
            int j;
            for(j = 0; j < c; j++)
            {
                var[j] = code[i + j];
            }
            tokens[t++] = (Token){.type = T_VAR, .var_name = var};
            i++;
            continue;
        }
        #pragma region MATCH_DIGIT
        if (isdigit(c1))
        {
            int d = 0;
            bool floating = false;
            while(isdigit(code[i + d]) || code[i + d] =='.')
            {
                if (code[i + d] == '.') {
                    floating = true;
                }
                d++;
            }
            char suffix = '\0';
            char suffix2 = '\0';
            if (i + d + 1 < len && isalpha(code[i + d + 1])) {
                suffix = code[i + d + 1];
                check_suffix(suffix, false, i + d + 1);
                
                if (i + d + 2 < len && isalpha(code[i + d + 2])) {
                    suffix2 = code[i + d + 1];
                    check_suffix(suffix2, true, i + d + 2);
                    d += 2;
                } else {
                    d += 1;
                }
            }
            char* number = malloc(sizeof(char) * d);
            int j;
            for(j = 0; j < d; j++)
            {
                number[j] = code[i + j];
            }
            
            if (floating)
            {
                tokens[t++] = (Token) {.type = T_FLOAT, .dyn_val = df64(atof(number))};
                i++;
                continue;
            }
            if (suffix == '\0' && suffix2 == '\0')
            {
                tokens[t++] = (Token) {.type = T_INT, .dyn_val = di32(atoi(number))};
                i++;
                continue;
            }
            if (suffix == 'u' && suffix2 == 'l')
            {
                tokens[t++] = (Token) {.type = T_ULONG, .dyn_val = dui64(atoll(number))};
                i++;
                continue;
            }
            if (suffix == 'u')
            {
                tokens[t++] = (Token) {.type = T_UINT, .dyn_val = dui32(atol(number))};
                i++;
                continue;
            }
            if (suffix == 'l')
            {
                tokens[t++] = (Token) {.type = T_LONG, .dyn_val = di64(atol(number))};
                i++;
                continue;
            }
            failwith("number format not recognized?");
        }
        #pragma endregion MATCH_DIGIT
        if (c1 == '\'')
        {
            tokens[t++] = (Token){.type = T_CHAR };
            i++;
            continue;
        }
        if (c1 == '"') {
            tokens[t++] = (Token){.type = T_CHAR };
            i++;
            continue;
        }
        if (c1 == '+') {
            tokens[t++] = (Token){.type = T_ADD };
            i++;
            continue;
        }
        if (c1 == '-') {
            tokens[t++] = (Token){.type = T_SUB };
            i++;
            continue;
        }
        if (c1 == '*') {
            tokens[t++] = (Token){.type = T_MUL };
            i++;
            continue;
        }
        if (c1 == '/') {
            tokens[t++] = (Token){.type = T_DIV };
            i++;
            continue;
        }
        if (c1 == '%') {
            tokens[t++] = (Token){.type = T_MOD };
            i++;
            continue;
        }
        if (c1 == '=' && c2 == '=') {
            tokens[t++] = (Token){.type = T_EQ };
            i += 2;
            continue;
        }
        if (c1 == '!' && c2 == '=') {
            tokens[t++] = (Token){.type = T_NE };
            i += 2;
            continue;
        }
        if (c1 == '>' && c2 == '=') {
            tokens[t++] = (Token){.type = T_GEQ };
            i += 2;
            continue;
        }
        if (c1 == '<' && c2 == '=') {
            tokens[t++] = (Token){.type = T_LEQ };
            i += 2;
            continue;
        }
        if (c1 == '>' && c2 == '>') {
            tokens[t++] = (Token){.type = T_RIGHT };
            i += 2;
            continue;
        }
        if (c1 == '<' && c2 == '<') {
            tokens[t++] = (Token){.type = T_LEFT };
            i += 2;
            continue;
        }
        if (c1 == '>') {
            tokens[t++] = (Token){.type = T_GT };
            i++;
            continue;
        }
        if (c1 == '<') {
            tokens[t++] = (Token){.type = T_LT };
            i++;
            continue;
        }
        if (c1 == '&' && c2 == '&') {
            tokens[t++] = (Token){.type = T_AND };
            i += 2;
            continue;
        }
        if (c1 == '|' && c2 == '|') {
            tokens[t++] = (Token){.type = T_OR };
            i += 2;
            continue;
        }
        if (c1 == '&') {
            tokens[t++] = (Token){.type = T_BAND };
            i++;
            continue;
        }
        if (c1 == '|') {
            tokens[t++] = (Token){.type = T_BOR };
            i++;
            continue;
        }
        if (c1 == '^') {
            tokens[t++] = (Token){.type = T_XOR };
            i++;
            continue;
        }
        if (c1 == '~') {
            tokens[t++] = (Token){.type = T_COM };
            i++;
            continue;
        }
        if (c1 == '?') {
            tokens[t++] = (Token){.type = T_IF };
            i++;
            continue;
        }
        if (c1 == ':') {
            tokens[t++] = (Token){.type = T_ELSE };
            i++;
            continue;
        }
        if (c1 == ',') {
            tokens[t++] = (Token){.type = T_COMMA };
            i++;
            continue;
        }
        if (c1 == ';') {
            tokens[t++] = (Token){.type = T_SC };
            i++;
            continue;
        }
    }
}

#pragma endregion SCANNER

#pragma region PARSER

typedef enum _ExprType
{
    DYN,
    VAR,
    CALL,   //<name>(<params>)
    BINOP,
    UNOP,
    // ADD,    //+
    // SUB,    //-
    // MUL,    //*
    // DIV,    //'/'
    // MOD,    //%
    // EQ,     //==
    // NE,     //!=
    // GT,     //>
    // LT,     //<
    // GEQ,    //>=
    // LEQ,    //<=
    // AND,    //&&
    // OR,     //||
    // NOT,    //!
    // BAND,   //&
    // BOR,    //|
    // XOR,    //^
    // COM,    //~
    // LEFT,   //<<
    // RIGHT,  //>>
    TERN, //(_) ? _ : _
} ExprType;

typedef struct _Expr Expr;

typedef struct _Call
{
    char* name;
    Expr* parameters;
} Call;

typedef struct _Binop
{
    char operator;
    Expr* left;
    Expr* right;
} Binop;

typedef struct _Unop
{
    char operator;
    Expr* operand;
} Unop;

typedef struct _Tern
{
    Expr* bExpr;
    Expr* trueExpr;
    Expr* falseExpr;
} Tern;

typedef union _ExprInstance
{
    Dynamic dyn;
    char* var;
    Call call;
    Binop binop;
    Unop unop;
    Tern tern;
} ExprInstance;

typedef struct _Expr
{
    ExprType type;
    ExprInstance e;
} Expr;

//Nothing here, since we're redesigning the flow to scan -> parse -> compile.

#pragma endregion PARSER

#pragma region INTERPRETER

#pragma endregion INTERPRETER


Dynamic apply(Lambda* lambda, Dynamic param, ...)
{
    va_list args;
    va_start(args, param);
    char** parameters = lambda->parameters;
    
    //Tokenize the body, aka everything past the param_count.
    Dict* env = lambda->environment;
    int i;
    
    dict_put_s(env, parameters[0], param);
    for(i = 1; i < lambda->param_count; i++)
    {
        dict_put_s(env, parameters[i], va_arg(args, Dynamic));
    }

    va_end(args);
}


typedef struct _Lambda
{
    Expr* expression;
    int param_count;
    char** parameters;
    Dict* environment;
} Lambda;

Lambda* lambda(char* code, Dict* environment)
{
    Lambda* l = malloc(sizeof(Lambda));
    l->environment = environment;
    int word_count[1];
    char** words = get_words(code, word_count);
    int param_count[1];
    char** parameters = get_parameters(words, word_count[0], param_count);
    l->parameters = parameters;
    l->param_count = param_count;
    int words_in_body = word_count[0] - param_count[0] - 1;
    char** body = words + param_count[0] + 1;
    l->expression = parse(0, words_in_body, 0, body);
    return l;
}