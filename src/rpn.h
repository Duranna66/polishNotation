//
// Created by Wull Harm on 09.07.2023.
//

#ifndef P03D20_1_RPN_H
#define P03D20_1_RPN_H
//
// Created by Wull Harm on 08.07.2023.
//
#define TANG 'T'
#define SIN 'S'
#define Sqrt 's'
#define UNMINUS '~'
#define COS 'C'
#define LN 'L'
#define CTG 'c'
struct list* getToken();
int isOperator(char c);
struct list* getPRN(struct list* tokens);
int priority(char c);
double f(struct list* rpn, double x);
double doOperation(char t, double a, double b);

#endif  // P03D20_1_RPN_H
