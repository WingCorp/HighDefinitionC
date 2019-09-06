/**
 * @file comparable.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-01
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include <stdio.h>

#include "./../dynamic/dynamic.h"
#include "./../fail/fail.h"
#include "comparable.h"
#include <string.h>

Comparable comparable(Dynamic dynamic)
{
    switch(dynamic.type)
    {
        case BOOL:
            failwith("Cannot construct comparable from a BOOL value.\n");
            break;
        case REFERENCE:
            failwith("Cannot construct comparable from a REFERENCE value.\n");
            break;
        default:
            break;
    }
    return (Comparable) { .value = dynamic};
}

int compare(Comparable a, Comparable b)
{
    if(a.value.type != b.value.type)
    {
        failwith("Cannot compare comparables of different dynamic types!\n");
    }
    Dynamic aVal = a.value;
    Dynamic bVal = b.value;

    switch(a.value.type)
    {
        case CHAR:
            if (chr(aVal) == chr(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (chr(aVal)) > (chr(bVal)) ? 1 : -1;
            }
        case INT:
            if (i32(aVal) == i32(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (i32(aVal)) > (i32(bVal)) ? 1 : -1;
            }
        case FLOAT:
            if (f32(aVal) == f32(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (f32(aVal)) > (f32(bVal)) ? 1 : -1;
            }
        
        case DOUBLE:
            if (f64(aVal) == f64(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (f64(aVal)) > (f64(bVal)) ? 1 : -1;
            }

        case LONG:
            if (i64(aVal) == i64(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (i64(aVal)) > (i64(bVal)) ? 1 : -1;
            }
        case STRING:
            return strcmp(str(aVal), str(bVal));
        default:
            failwith("Cannot create comparable from unknown dynamic type!\n");
            break;
    }
    int f = 0;
    return 0 / f; //So, we have to return an integer, but we should not.
    //We should never reach these statements, but if we do, I've made a terrible mistake somewhere.
}

