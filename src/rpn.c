//
// Created by Wull Harm on 08.07.2023.
//
#include "rpn.h"

#include <math.h>
#include <stdio.h>

#include "list.h"
int isOperator(char c);
int per(char c);
double doOperation(char t, double a, double b);
struct list* getToken() {
    int br = 0;
    int error = 0;
    double x;
    struct list* res = 0;
    char prev = '(';
    while (br == 0) {
        char c;
        while (scanf("%c", &c) == 1 && c == ' ')
            ;
        if (c < 32) {
            br = 1;
        } else if (c == '.' || (c >= '0' && c <= '9')) {
            ungetc(c, stdin);
            scanf("%lf", &x);
            struct data d = {'0', x};
            res = listAdd(res, d);
            prev = d.type;
        } else if (isOperator(c) || c == '(' || c == ')') {
            if (c == '-') {
                if (prev == '(' || isOperator(prev)) {
                    struct data d = {UNMINUS, 0};
                    res = listAdd(res, d);
                }
            }
            struct data d = {c, 0};
            res = listAdd(res, d);
        } else if (c == 't' && scanf("%c", &c) == 1 && c == 'g') {
            struct data d = {TANG, 0};
            res = listAdd(res, d);
            prev = d.type;
        } else if (c == 'x') {
            struct data d = {c, 0};
            res = listAdd(res, d);
            prev = d.type;
        } else if (c == 's') {
            if (scanf("%c", &c) == 1) {
                if (c == 'i' && scanf("%c", &c) == 1 && c == 'n') {
                    struct data d = {SIN, 0};
                    res = listAdd(res, d);
                    prev = d.type;
                } else if (c == 'q' && scanf("%c", &c) == 1 && c == 'r' && scanf("%c", &c) == 1 && c == 't') {
                    struct data d = {Sqrt, 0};
                    res = listAdd(res, d);
                    prev = d.type;
                }
            }

        } else if (c == 'c') {
            if (scanf("%c", &c) == 1) {
                if (c == 'o' && scanf("%c", &c) == 1 && c == 's') {
                    struct data d = {COS, 0};
                    res = listAdd(res, d);
                    prev = d.type;
                } else if (c == 't' && scanf("%c", &c) == 1 && c == 'g') {
                    struct data d = {CTG, 0};
                    res = listAdd(res, d);
                    prev = d.type;
                }
            }

        } else if (c == 'l' && scanf("%c", &c) == 1 && c == 'n') {
            struct data d = {LN, 0};
            res = listAdd(res, d);
            prev = d.type;
        } else {
            error = 1;
            res = 0;
        }
        if (error) {
            listDestroy(res);
        }
    }
    return res;
}
int isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }
struct list* getPRN(struct list* string) {
    struct list* outputString = 0;
    struct list* stack = 0;
    while (string != 0) {
        char type = string->x.type;
        double value = string->x.value;
        struct data d = {type, value};
        if (type == '0' || type == 'x') {
            outputString = listAdd(outputString, d);
        } else if (type == '(') {
            stack = listPush(stack, d);
        } else if (type == ')') {
            while (stack != 0 && stack->x.type != '(') {
                outputString = listAdd(outputString, stack->x);
                stack = listPop(stack);
            }
        } else {
            while (stack != 0 && per(stack->x.type) >= per(type)) {
                outputString = listAdd(outputString, stack->x);
                stack = listPop(stack);
            }
            stack = listPush(stack, d);
        }
        string = listPop(string);
    }
    while (stack != 0) {
        outputString = listAdd(outputString, stack->x);
        stack = listPop(stack);
    }
    return outputString;
}
int per(char c) {
    int res = 0;
    switch (c) {
        case COS:
            res = 4;
            break;
        case CTG:
            res = 4;
            break;
        case SIN:
            res = 4;
            break;
        case Sqrt:
            res = 4;
            break;
        case TANG:
            res = 3;
            break;
        case UNMINUS:
            res = 5;
            break;
        case '(':
            res = 0;
            break;
        case ')':
            res = 0;
            break;
        case '+':
            res = 1;
            break;
        case '-':
            res = 1;
            break;
        case '*':
            res = 2;
            break;
        case '/':
            res = 2;
            break;
        case '^':
            res = 4;
            break;
    }
    return res;
}
double f(struct list* rpn, double x) {
    struct list* stack = 0;
    while (rpn != 0) {
        struct data d = rpn->x;
        if (d.type == '0') {
            stack = listPush(stack, d);
        } else if (rpn->x.type == 'x') {
            d.value = x;
            stack = listPush(stack, d);
        } else if (d.type == '+' || d.type == '-' || d.type == '*' || d.type == '/' || d.type == '^') {
            double b = stack->x.value;
            stack = listPop(stack);
            double a = stack->x.value;
            stack = listPop(stack);
            double r = doOperation(d.type, a, b);
            struct data y = {'0', r};
            stack = listPush(stack, y);
        } else if (d.type == '(' || d.type == ')') {
        } else {
            double a = stack->x.value;
            stack = listPop(stack);
            double r = doOperation(d.type, a, 0);
            struct data y = {'0', r};
            stack = listPush(stack, y);
        }
        rpn = rpn->next;
    }
    double res = 0.0;
    if (stack != NULL) {
        res = stack->x.value;
    }
    listDestroy(stack);
    return res;
}
double doOperation(char t, double a, double b) {
    double res = 0;
    if (t == UNMINUS) res = -a;
    if (t == '+') res = a + b;
    if (t == '-') res = a - b;
    if (t == '*') res = a * b;
    if (t == '/') res = a / b;
    if (t == '^') res = pow(a, b);
    if (t == TANG) res = tan(a);
    if (t == SIN) res = sin(a);
    if (t == COS) res = cos(a);
    if (t == Sqrt) res = sqrt(a);
    if (t == LN) res = log(a);
    if (t == CTG) res = 1 / tan(a);
    return res;
}