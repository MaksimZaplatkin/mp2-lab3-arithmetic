#include "arithmetic.h"
#include "stack.h"
#include <stdexcept>
#include <cmath>

void TArithExpres::Parse(std::string infix)
{
	
	lexems.clear();
	int bracketBalance = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		bool muldot = false;
		if (infix[i] == ' ')
		{
			continue;
		}
		if ((infix[i] == '+' || infix[i] == '-') && (lexems.empty() || lexems.back().GetName() == "(" || lexems.back().GetType() == 1||lexems.back().GetType()==3))
		{
			std::string unar;
			if (infix[i] == '+')
			{
				unar="u+";
			}
			else
			{
				unar = "u-";
			}
			lexems.push_back(Lexem(unar, 1));
			continue;
		}
		if (infix[i] == '(' && i + 1 < infix.size() && infix[i + 1] == ')')
		{
			throw std::invalid_argument("empty_brackets");
		}
		if (infix[i] == '(' && i + 2 < infix.size() && infix[i+1]==' ' && infix[i + 2] == ')')
		{
			throw std::invalid_argument("empty_brackets");
		}
		if (std::isalpha(infix[i]))
		{
			std::string tmp;
			while (i < infix.length() && std::isalpha(infix[i]))
			{
				tmp += infix[i];
				i++;
			}
			i--;
			if (tmp == "sin" || tmp == "cos")
			{
				lexems.push_back(Lexem(tmp, 3));
			}
			else if (tmp.length() == 1)
			{
				lexems.push_back(Lexem(tmp, 0));
			}
			else
			{
				throw std::invalid_argument("non_exist_function");
			}
		}
		else if (std::isdigit(infix[i]) || infix[i] == '.')
		{
			std::string numer;
			while (i < infix.length() && (std::isdigit(infix[i]) || infix[i] == '.'))
			{
				if (infix[i] == '.')
				{
					if (muldot)
					{
						throw std::invalid_argument("multiple_dot_double");
					}
					muldot = true;
				}
				numer += infix[i];
				i++;
			}
			i--;
			if (!numer.empty() && numer != "." && numer.find(".") != 0 && numer.find(".")!=numer.size()-1)
			{
				lexems.push_back(Lexem(numer, 0));
			}
			else
			{
				throw std::invalid_argument("non_valid_number");
			}
		}
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/'|| infix[i] == '^')
		{
			lexems.push_back(Lexem(std::string(1, infix[i]), 1));
		}
		else if (infix[i] == '(' )
		{
			bracketBalance++;
			lexems.push_back(Lexem(std::string(1, infix[i]), 2));
		}
		else if (infix[i] == ')')
		{
			bracketBalance--;
			if (bracketBalance < 0)
			{
				throw std::invalid_argument("too_much_closed");
			}
			lexems.push_back(Lexem(std::string(1, infix[i]), 2));
		}
		else
		{
			throw std::invalid_argument("non_exist_command");
		}
		
	}
	if (bracketBalance  > 0)
	{
		throw std::invalid_argument("too_much_opened");
	}
	for (int i = 0; i < lexems.size() - 1; i++)
	{
		if (lexems[i].GetName() == "(" && lexems[i + 1].GetName() == ")")
		{
			throw std::invalid_argument("empty_brackets");
		}
	}
	if (lexems.size() == 0)
	{
		throw std::logic_error("void_string");
	}
	ToPostfix();
}

void TArithExpres::ToPostfix()
{
	postfix.clear();
	Stack<Lexem> PoSt(lexems.size() + 1);
	for (int i = 0; i < lexems.size(); i++)
	{
		if (lexems[i].GetType() == 0)
		{
			postfix.push_back(lexems[i]);
		}
		else if (lexems[i].GetType() == 3)
		{
			PoSt.Push(lexems[i]);
		}
		else if (lexems[i].GetName() == "(")
		{
			PoSt.Push(lexems[i]);
		}
		else if (lexems[i].GetName() == ")")
		{
			while (!PoSt.Is_Empty() && PoSt.Top().GetName() != "(")
			{
				postfix.push_back(PoSt.Top());
				PoSt.Pop();
			}
			if (!PoSt.Is_Empty() && PoSt.Top().GetName() == "(")
			{
				PoSt.Pop();
			}
			if (!PoSt.Is_Empty() && PoSt.Top().GetType() == 3)
			{
				postfix.push_back(PoSt.Top());
				PoSt.Pop();
			}
		}
		else if (lexems[i].GetType() == 1)
		{
			if (!PoSt.Is_Empty()&&(PoSt.Top().GetName() == "u+" || PoSt.Top().GetName() == "u-"))
			{
				PoSt.Push(lexems[i]);
			}
			else
			{
				while (!PoSt.Is_Empty() && PoSt.Top().GetType() != 2 && PoSt.Top().GetName() != "(" && GetPriority(PoSt.Top()) >= GetPriority(lexems[i]))
				{
					postfix.push_back(PoSt.Top());
					PoSt.Pop();
				}
				PoSt.Push(lexems[i]);
			}
		}
	}
	while (!PoSt.Is_Empty())
	{
		if (PoSt.Top().GetName() == "(")
		{
			throw std::invalid_argument("odd_brackets");
		}
		postfix.push_back(PoSt.Top());
		PoSt.Pop();
	}
}

double TArithExpres::Calculate(const std::map<char, double>& values)
{
	Stack<double> stack(100);
	for (int i = 0; i < postfix.size(); i++)
	{
		Lexem lexem = postfix[i];
		int type = lexem.GetType();
		std::string name = lexem.GetName();
		if (type == 0)
		{
			if (std::isdigit(name[0]) || name[0] == '.')
			{
				double num = std::stod(name);
				stack.Push(num);
			}
			else
			{
				char var = name[0];
				if (values.count(var) == 0)
				{
					throw std::invalid_argument("non_exist_variable");
				}
				stack.Push(values.at(var));
			}
		}
		else if (type == 1)
		{
			if (name == "u+" || name == "u-")
			{
				if (stack.How_Many_Elem() < 1)
				{
					throw std::invalid_argument("too_short1");
				}
				double a = stack.Top();
				stack.Pop();
				double result;
				if (name == "u+"||a==0)
				{
					result = a;
				}
				else
				{
					result = -a;
				}
				stack.Push(result);
			}
			else
			{
				if (stack.How_Many_Elem() < 2)
				{
					throw std::invalid_argument("too_short2");
				}
				double b = stack.Top();
				stack.Pop();
				double a = stack.Top();
				stack.Pop();
				double result;
				if (name == "+")
				{
					result = a + b;
				}
				else if (name == "-")
				{
					result = a - b;
				}
				else if (name == "*")
				{
					result = a * b;
				}
				else if (name == "/")
				{
					if (abs(b) < 1e-12)
					{
						throw std::invalid_argument("Div_by_zero");
					}
					result = a / b;
				}
				else if (name == "^")
				{
					result = pow(a, b);
				}
				else
				{
					throw std::invalid_argument("Non_operand");
				}
				stack.Push(result);
			}
		}
		else if (type == 3)
		{
			if (stack.How_Many_Elem() < 1)
			{
				throw std::invalid_argument("too_short3");
			}
			double x = stack.Top();
			stack.Pop();
			double result;
			if (name == "sin")
			{
				result = sin(x);
			}
			else if (name == "cos")
			{
				result = cos(x);
			}
			else
			{
				throw std::invalid_argument("Non_function");
			}
			stack.Push(result);
		}
	}
	if (stack.How_Many_Elem() != 1)
	{
		throw std::invalid_argument("strange_expr");
	}
	return stack.Top();
}