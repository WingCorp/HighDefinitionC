#include "lambda.h"
#include "./../fail/fail.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*
    You can bet that I started missing my buggy list implementation when I got to this part.
 */

#pragma region SCANNER

typedef enum _TokenType
{
    T_ARROW,  //=>
    T_LPAR,   //(
    T_RPAR,   //)
    T_NAME,   //\w+
    T_NUMBER,
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
    char* name;
    char* string;
    char single_char;
    Dynamic dyn;
} Token;

void checkSuffix(char suffix, bool second, int pos)
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
        if (c1 == '\'')
        {
            tokens[t++] = (Token){.type = T_CHAR, .single_char = c2 };
            if(code[c2 + 1] != '\'')
            {
                failwith("`char` values must consist of a single char");
            }
            i += 3; //Skip the char and the closing char sign.
            continue;
        }
        if (c1 == '"') {
            int len = 0;
            while(isalpha(code[c2 + len])){
                len++;
            }
            if (len == 0)
            {
                tokens[t++] = (Token){.type = T_STRING, .string = ""};
                i++;
                continue;
            }
            char* string = malloc(sizeof(char) * len);
            int i;
            for (i = 0; i < len; i++)
            {
                string[i] = code[c2 + i];
            }
            tokens[t++] = (Token){.type = T_STRING, .string = string };
            i += len + 1; //Remember to skip the " at the end.
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
            tokens[t++] = (Token){.type = T_NAME, .name = var};
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
                checkSuffix(suffix, false, i + d + 1);
                
                if (i + d + 2 < len && isalpha(code[i + d + 2])) {
                    suffix2 = code[i + d + 1];
                    checkSuffix(suffix2, true, i + d + 2);
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
                tokens[t++] = (Token) {.type = T_NUMBER, .dyn = df64(atof(number))};
                i++;
                continue;
            }
            if (suffix == '\0' && suffix2 == '\0')
            {
                tokens[t++] = (Token) {.type = T_NUMBER, .dyn = di32(atoi(number))};
                i++;
                continue;
            }
            if (suffix == 'u' && suffix2 == 'l')
            {
                tokens[t++] = (Token) {.type = T_NUMBER, .dyn = dui64(atoll(number))};
                i++;
                continue;
            }
            if (suffix == 'u')
            {
                tokens[t++] = (Token) {.type = T_NUMBER, .dyn = dui32(atol(number))};
                i++;
                continue;
            }
            if (suffix == 'l')
            {
                tokens[t++] = (Token) {.type = T_NUMBER, .dyn = di64(atol(number))};
                i++;
                continue;
            }
            failwith("number format not recognized?");
        }
        #pragma endregion MATCH_DIGIT
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
        i++;
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
    int parameter_count;
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

bool topExpr(Expr* topExpr, Token* tokens, int* pos);

bool atExpr(Expr* outExpr, Token* tokens, int* pos)
{
    Token token = tokens[*pos];
    TokenType t = token.type;
    if (t == T_NUMBER)
    {
        outExpr->type = DYN;
        outExpr->e = (ExprInstance) {.dyn = token.dyn};
        (*pos)++;
        return true;
    }
    if (t == T_CHAR)
    {
        outExpr->type = DYN;
        outExpr->e = (ExprInstance){.dyn = dchr(token.single_char)};
        (*pos)++;
        return true;
    }
    if (t == T_STRING)
    {
        outExpr->type = DYN;
        outExpr->e = (ExprInstance){.dyn = dref(token.string)};
        (*pos)++;
        return true;
    }
    Token next = tokens[(*pos) + 1];
    if (t == T_NAME && next.type == T_LPAR) //This is a CALL!
    {
        int p = 1;
        int depth = 0;
        while (true)
        {
            Token n = tokens[(*pos) + p];
            if (n.type == T_LPAR && depth == 0)
            {
                break;
            } 
            else 
            {
                depth++;
            }
            if (n.type == T_COMMA)
            {
                continue;
            }
            p++;
        }
        Expr* parameters = malloc(sizeof(Expr) * (p) - 1);        
        int pc;
        int* ahead = malloc(sizeof(int));
        for (pc = 1; pc <= p; pc++)
        {
            Token n = tokens[(*pos) + p];
            if (n.type == T_COMMA || n.type == T_LPAR || n.type == T_RPAR) 
            {
                continue;
            }
            *ahead = (*pos) + pc;
            topExpr(&(parameters[pc - 1]), tokens, ahead);
        }
        outExpr->type = CALL;
        outExpr->e = (ExprInstance) 
        { 
            .call = (Call)
            {   
                .name = token.name,
                .parameter_count = p,
                .parameters = parameters
            } 
        };
        (*pos) = (*ahead);
        free(ahead);
        return true;
    }
    if (t == T_NAME)
    {
        outExpr->type = VAR;
        outExpr->e = (ExprInstance) {.var = token.name};
        (*pos)++;
        return true;
    }
    if (t == T_LPAR)
    {
        int* ahead = malloc(sizeof(int));
        *ahead = (*pos) + 1;
        topExpr(outExpr, tokens, ahead);
        (*pos) += 2; //Skip the (last) RPAR
        free(ahead);
        return true;
    }
    return false;
}

bool unop(Expr* expr, char operator, Token* tokens, int* pos)
{
    int* ahead = malloc(sizeof(int));
    *ahead = (*pos) + 1;
    Expr* operand = malloc(sizeof(Expr));
    topExpr(operand, tokens, ahead);
    expr = malloc(sizeof(Expr));
    expr->type = UNOP;
    expr->e = (ExprInstance) { .unop = (Unop) { .operator = operator, .operand = operand } };
    free(ahead);
    return true;
}

bool binop(Expr* expr, char operator, Token* tokens, int* pos)
{
    int* ahead = malloc(sizeof(int));
    *ahead = (*pos) - 1;
    Expr* left = malloc(sizeof(Expr));
    topExpr(left, tokens, ahead);
    //FUCK, I can't go back.
    return false;
}

bool topExpr(Expr* expr, Token* tokens, int* pos)
{
    Token token = tokens[*pos];
    TokenType t = token.type;
    while(t != T_SC) {
        Expr* parsedExpr = malloc(sizeof(Expr));
        if (atExpr(parsedExpr, tokens, pos))
        {
            expr = parsedExpr;
            return true;
        }
        //ELSE, PEEK AHEAD.
        //WE NEED A PEEK FUNCTION
        else if (t == T_IF) //Parse ternary expression
        {
            Expr* boolExpr = malloc(sizeof(Expr));
            Expr* trueExpr = malloc(sizeof(Expr));
            Expr* falseExpr = malloc(sizeof(Expr));
            int* ahead = malloc(sizeof(int));
            *ahead = (*pos) + 1;
            topExpr(boolExpr, tokens, ahead);
            *ahead = (*ahead) + 2; //Skip the ':'
            topExpr(trueExpr, tokens, ahead);
            *ahead = (*ahead) + 1;
            topExpr(falseExpr, tokens, ahead);
            expr->type = TERN;
            expr->e = (ExprInstance) { .tern = (Tern) { .bExpr = boolExpr, .trueExpr = trueExpr, .falseExpr = falseExpr } };
            free(ahead);
            return true;
        }
        else if (t == T_SUB && unop(expr, '-', tokens, pos))
        {
            return true;
        }
        else if (t == T_OR && binop) {
            
        }
    }
    return expr;
}

Expr* parse(Token* tokens)
{
    checkTokens(tokens);
    Expr* expr = malloc(sizeof(Expr));
    int* pos = malloc(sizeof(int));
    pos[0] = 0;
    if (topExpr(expr, tokens, pos)) {
        return expr;
    }
    failwith("Unknown parser error.");
} 

#pragma endregion PARSER

#pragma region INTERPRETER

#pragma endregion INTERPRETER

typedef struct _Lambda
{
    Expr* expression;
    int param_count;
    char** parameters;
    Dict* environment;
} Lambda;

Dynamic go(Lambda* lambda, Dynamic param, ...)
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
    //Add dynamic methods:
    dict_put_s(env, "i32", dref(i32));
    dict_put_s(env, "i64", dref(i64));
    dict_put_s(env, "f32", dref(f64)); //I'm so sorry for lying.
    dict_put_s(env, "f64", dref(f64));
    dict_put_s(env, "ui32", dref(ui32));
    dict_put_s(env, "ui64", dref(ui64));
    dict_put_s(env, "bol", dref(bol));
    dict_put_s(env, "chr", dref(chr));
    dict_put_s(env, "ref", dref(ref));
    dict_put_s(env, "di32", dref(di32));
    dict_put_s(env, "di64", dref(di64));
    dict_put_s(env, "df32", dref(df64)); //I'm still sorry.
    dict_put_s(env, "df64", dref(df64));
    dict_put_s(env, "dui32", dref(dui32));
    dict_put_s(env, "dui64", dref(dui64));
    dict_put_s(env, "dbol", dref(dbol));
    dict_put_s(env, "dchr", dref(dchr));
    dict_put_s(env, "dref", dref(dref));

    va_end(args);
}

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