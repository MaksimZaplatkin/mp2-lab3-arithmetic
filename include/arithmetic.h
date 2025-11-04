#include <string>
#include <vector>
#include <map>

class Lexem
{
    std::string name;
    int type;
public:
    Lexem(std::string nm, int tp)
    {
        name = nm;
        type = tp;
    }

    Lexem()
    {
        name = "";
        type = 0;
    }
    
    std::string GetName () const
    {
        return name;
    }
    int GetType () const
    {
        return type;
    }
};

class TArithExpres
{
    std::string infix;
    std::vector<Lexem> postfix;
    std::vector<Lexem> lexems;
    std::map<std::string, int> priority;
    std::map<char, double> operands;
    void Parse(std::string infx);
    void ToPostfix();
public:
    TArithExpres(std::string infx)
    {
        priority = { {"+", 1}, {"-" , 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"u+", 4}, {"u-", 4}, {"sin", 4}, {"cos", 4} };
        Parse(infx);
    }
    std::string GetInfix() const
    {
        return infix;
    }
    std::vector<Lexem> GetPostfix() const
    {
        return postfix;
    }
    int GetPriority(const Lexem& lexem)
    {
        
            std::string oper = lexem.GetName();
            if (oper == "+" || oper == "-")
            {
                return 1;
            }
            if (oper == "*" || oper == "/")
            {
                return 2;
            }
            if (oper == "^")
            {
                return 3;
            }
            if (oper == "u+" || oper == "u-")
            {
                return 4;
            }
            if (oper == "sin" || oper == "cos")
            {
                return 4;
            }
        return 0;
    }
    std::vector<char> GetOperands() const 
    {
        std::vector<char> operands;
        for (int i = 0; i < lexems.size(); i++)
        {
            if (lexems[i].GetType() == 0)
            {
                std::string name = lexems[i].GetName();
                if (name.length() == 1)
                {
                    char var = name[0];
                    if (std::isalpha(var))
                    {
                        bool found = false;
                        for (int j = 0; j < operands.size(); j++)
                        {
                            if (operands[j] == var)
                            {
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                        {
                            operands.push_back(var);
                        }
                    }
                }
            }
        }
        return operands;
    }
    std::vector<Lexem> GetLexems() const
    {
        return lexems;
    }
    double Calculate(const std::map<char, double>& values) ;
};