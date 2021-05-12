// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"
int math (int &frst, int &scnd, char &smb)
{
    switch (smb)
    {
        case '*':
            {
                scnd *= frst;
                return scnd;
            }
        case '/':
            {
                scnd /= frst;
                return scnd;
            }
        case '+':
            {
                scnd += frst;
                return scnd;
            }
        case '-':
            {
                scnd -= frst;
                return scnd;
            }
        default:
            break;
    }
    return scnd;
}
int priority (char &ch)
{
    int prior = 0;
    if (ch == '(') 
        prior = 0;

    if (ch == ')')
        prior = 1;
    if (ch == '+' || ch == '-')
        prior = 2;
    if (ch == '*' || ch == '/')
        prior = 3; 
    return prior;

}
std::string infx2pstfx(std::string inf) {
    TStack<char> stack1;
    std::string result;
    int prior = -1;
    int priorTop = 0;
    char ch = ' ';
    char chPrv = ' ';
    bool firstNum = 0;
    for (int i = 0; i < inf.length(); i++) {
       ch = inf[i];
       chPrv = stack1.get();
       if (ch >= '0' && ch <= '9') {
           if (!firstNum) {
                firstNum = true;   
           }
           else {
               result.push_back(' ');
           }
           result.push_back (ch);
        }
       else {
           prior = priority (ch);
           priorTop = priority (chPrv);
           if ((stack1.isEmpty() ||  prior > priorTop || !prior) && prior != 1)
               stack1.push(ch);
           else {
               if (prior == 1) {
                   while (stack1.get() != '(') {
                       result.push_back (' ');
                       result.push_back(stack1.get());
                       stack1.pop();
                   }
                   stack1.pop();
               }
               else {
                   if (prior <= priorTop && prior > 1) {
                       while (!stack1.isEmpty() && stack1.get() != '(') {
                           result.push_back (' ');
                           result.push_back(stack1.get());
                           stack1.pop();
                       }
                       stack1.push(ch);
                   }
               }
           }
        }

    }
    while (!stack1.isEmpty ()) {
        result.push_back (' ');
        result.push_back(stack1.get());
        stack1.pop();
    }
    return result;
}
int eval (std::string &pst)
{
    int result = 0;
    TStack<char> stack1;
    TStack<int> stack2;
    int prior = 0, priorPrv = 0;
    int frst = 0, scnd = 0;
    char ch = ' ';
    char chPrv = ' ';
    for (int i = 0; i < pst.length(); i++) {
        ch = pst[i];
        if (ch != ' ') {
            if (ch >= '0' && ch <= '9') {
                stack2.push (ch - 48);
            }
            else {
                frst = stack2.get ();
                stack2.pop ();
                scnd = stack2.get ();
                stack2.pop ();
                scnd = math (frst, scnd, ch);
                stack2.push (scnd);
            }
        }
    }
    return stack2.get ();
}
