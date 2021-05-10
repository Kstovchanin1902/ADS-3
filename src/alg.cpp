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
                std::cout << "////" << std::endl;
                std::cout << "frst = " << frst << " scnd = " << scnd << std::endl;  
                scnd /= frst;
                std::cout << "scnd = " << scnd << std::endl;
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
    for (int i = 0; i < source.length(); i++)
    {
       ch = source[i];
       chPrv = stack1.get();
       if (ch >= '0' && ch <= '9')
        {
           result.push_back (ch);
        }
       else
        {
            std::cout << "0" << std::endl;
           prior = priority (ch);
           priorTop = priority (chPrv);
           std::cout << "ch = " << ch << " prior = " << prior << std::endl;
           if ((stack1.isEmpty() ||  prior > priorTop || !prior) && prior != 1)
               stack1.push(ch);
           else
           {
               if (prior == 1)
               {
                   while (stack1.get() != '(')
                   {
                       std::cout << "1" << std::endl;
                       result.push_back(stack1.get());
                       stack1.pop();
                   }
                   stack1.pop();
               }
               else
               {
                   if (prior <= priorTop && prior > 1)
                   {
                       while (!stack1.isEmpty() && stack1.get() != '(')
                       {
                           std::cout << "2" << std::endl;
                           std::cout << "stack1.get() = " << stack1.get() << std::endl;
                           result.push_back(stack1.get());
                           stack1.pop();
                       }
                       stack1.push(ch);
                   }
               }
           }
        }

    }
    while (!stack1.isEmpty ())
    {
        std::cout << "3" << std::endl;
        result.push_back(stack1.get());
        stack1.pop();
    }
    return result;
}

int eval(std::string pst) {
  int result = 0;
    TStack<char> stack1;
    TStack<int> stack2;
    int prior = 0, priorPrv = 0;
    int frst = 0, scnd = 0;
    char ch = ' ';
    char chPrv = ' ';
    for (int i = 0; i < source.length(); i++)
    {
        ch = source[i];
        std::cout << "ch = " << ch << std::endl;
        if (ch >= '0' && ch <= '9')
        {
            std::cout << "stack2.get (): "<< stack2.get () << std::endl;
            stack2.push (ch - 48);
        }
        else
        {
            frst = stack2.get ();
            stack2.pop ();
            scnd = stack2.get ();
            stack2.pop ();
            scnd = math (frst, scnd, ch);
            stack2.push (scnd);
        }
    }
    return stack2.get ();
}
