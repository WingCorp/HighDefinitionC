#include "lambda.h"
#include "fail.h"

#include <string.h>
#include <stdlib.h>
#include <varargs.h>
#include <stdio.h>
#include <ctype.h>

#pragma region INTERPRETER

char** get_words(char* code, int* out_counter)
{
    size_t len = strlen(code);

    if (len <= 4)
    {
        //Sounds crazy, but the shortest possible lambda, the id lambda is 'x => x'
        failwith("Cannot create a Lambda with a body shorter than 4 characters.\n");
    }
    
    
    int word_count = 1;
    int c;
    for (c = 0; c < len; c++) 
    {
        if (code[c] == ' ')
        {
            word_count++;
        }
    }

    char** words = malloc(sizeof(char*) * word_count);
    //Tokens:
    int saved_words = 0;
    int latest_word_pos = 0;    
    for (c = 0; c < len; c++)
    {
        if (code[c] == ' ')
        {
            int t;
            char* word = malloc(sizeof(char) * c);
            for (t = c - 1; t >= latest_word_pos; t--)
            {
                word[t - latest_word_pos] = code[t];
            }
            words[saved_words++] = word;
            latest_word_pos = c + 1;
        }
    }
    out_counter[0] = word_count;
    return words;
}

char** get_parameters(char** words, int word_count, int* out_counter)
{
    int arrow_index = -1;
    int i;
    for (i = 0; i < word_count; i++)
    {
        if (strcmp(words[i], "=>") == 0)
        {
            arrow_index = i;
            break;
        }
    }
    if (arrow_index)
    {
        failwith("No arrow present in Lambda code");
    }
    char** parameters = malloc(sizeof(char*) * arrow_index);
    for (i = 0; i < arrow_index; i++)
    {
        parameters[i] = words[i];
    }
    return parameters;
}

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

#pragma region MATCHERS

bool is_binop(char* word)
{
    // ADD,    //+
    if (strcmp(word, "+") == 0)
    {
        return true;
    }
    // SUB,    //-
    if (strcmp(word, "-") == 0)
    {
        return true;
    }
    // MUL,    //*
    if (strcmp(word, "-") == 0)
    {
        return true;
    }
    // DIV,    //'/'
    if (strcmp(word, "/") == 0)
    {
        return true;
    }
    // MOD,    //%
    if (strcmp(word, "%") == 0)
    {
        return true;
    }
    // EQ,     //==
    if (strcmp(word, "==") == 0)
    {
        return true;
    }
    // NE,     //!=
    if (strcmp(word, "!=") == 0)
    {
        return true;
    }    
    // GT,     //>
    if (strcmp(word, ">") == 0)
    {
        return true;
    }
    // LT,     //<
    if (strcmp(word, "<") == 0)
    {
        return true;
    }
    // GEQ,    //>=
    if (strcmp(word, ">=") == 0)
    {
        return true;
    }
    // LEQ,    //<=
    if (strcmp(word, "<=") == 0)
    {
        return true;
    }
    // AND,    //&&
    if (strcmp(word, "&&") == 0)
    {
        return true;
    }
    // OR,     //||
    if (strcmp(word, "||") == 0)
    {
        return true;
    }
    // BAND,   //&
    if (strcmp(word, "&") == 0)
    {
        return true;
    }
    // BOR,    //|
    if (strcmp(word, "|") == 0)
    {
        return true;
    }
    // XOR,    //^
    if (strcmp(word, "^") == 0)
    {
        return true;
    }
    // LEFT,   //<<
    if (strcmp(word, "<<") == 0)
    {
        return true;
    }
    // RIGHT,  //>>
    if (strcmp(word, ">>") == 0)
    {
        return true;
    }
    return false;
}

bool is_unop(char* word)
{
    // NOT,    //!
    if (word[0] == "!") 
    {
        return true;
    }
    // COM,    //~
    if (word[0] == "~")
    {
        return true;
    }
    return false;
}

bool is_term(char* word, int par_lvl)
{
    int len = strlen(word);
    char first = word[0];
    bool number = 
        first == '+' || first == '-' || isdigit(first);
    char last = word[len - 1];
    if (number) 
    {
        return last == 'f' || last == 'l' || last == 'u';
    }
    if (word[len - par_lvl - 1] == ')')
    {
        return true; //It is a call.
    }
    return !is_binop && !is_unop; //It might be a variable.
}

#pragma endregion MATCHERS

Expr* parse(int start, int end, int par_lvl, char** words)
{
    Expr* expr = malloc(sizeof(Expr));
    int w;
    Expr* previous;
    for (w = 0; w < end; w++)
    {
        char* word = words[w];
        int len = strlen(word);
        bool begin_par = word[0] == '(';
        int ws = 0;
        if (begin_par) {
            ws++;
            par_lvl++;
        }

        Expr* current = malloc(sizeof(Expr));
        if (is_term(word + ws, par_lvl))
        {
            char last = word[len - 1];
            if (word[0] == '+' || word[0] == '-' || isdigit(last)) 
            {
                current->type = DYN;
                if (word[len - 2] == 'u' && last == 'l')
                {
                    unsigned long val = atoll(word);
                    current->e = (ExprInstance) { .dyn = dui64(val) };
                    
                }
                else if (last == 'f')
                {
                    double val = atof(word);
                    current->e = (ExprInstance) { .dyn = df64(val) };
                }
                else if (last == 'l')
                {
                    long val = atol(word);
                    current->e = (ExprInstance) {.dyn = di64(val)};
                }
                else if (last == 'u')
                {
                    unsigned int val = atol(word);
                    current->e = (ExprInstance) {.dyn = dui32(val)};
                }
                else
                {
                    int val = atoi(word);
                    current->e = (ExprInstance) {.dyn = di32(val)};
                }
            }
            else if (word[len - par_lvl - 1] == ')') 
            {
                //It's a call
                current->type = CALL;
                //Find the start of the parentheses, parse the parameters.

            }
            else
            {
                current->type = VAR;
                //Deal with parentheses somehow.
                current->e = (ExprInstance) {.var = word};
            } 
        }
        if (is_unop(word + ws))
        {
            //create the unop
            current->type = UNOP;            
            char operator = word[ws];
            bool in_par = word[ws + 1] == '(';
            Expr* operand = parse(w + 1, end, in_par, words);
            Unop unop = (Unop) { .operator = operator, .operand = operand };
            current->e = (ExprInstance){ .unop = unop};
            previous = current;
            continue;
        }
        
    }
}

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

#pragma endregion INTERPRETER

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