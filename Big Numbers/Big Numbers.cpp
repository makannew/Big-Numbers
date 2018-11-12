#include "stdafx.h"
#include<iostream>
#include<string>


using namespace System;
class BigNumber 
{
private:
	enum comp { equal, bigger, smaller };
	//store big number as string of digits
	std::string digits_string;
	//fraction part of the number will define by dotplace
	std::string::size_type dotplace;
	//integer part of the number will define by integer_lenght
	std::string::size_type integer_lenght;

	//functionst
	std::string same_pos_digits(BigNumber &b,std::string::size_type pos)
	{
		std::string result="00";
		std::string::size_type max_dotplace = MaxDotplace(b);
		std::string::size_type max_integer = MaxInteger(b);
		if (pos < max_integer)//it means we are looking at integer part
		{
			if (BigNumber::integer_lenght == b.integer_lenght)
			{
				result[0] = BigNumber::digits_string[pos];
				result[1] = b.digits_string[pos];
			}
			else if (BigNumber::integer_lenght < max_integer)
			{
				if (pos < (max_integer - BigNumber::integer_lenght))
				{
					result[0] = zero_character[0];
					result[1] = b.digits_string[pos];
				}
				else
				{
					result[0] = BigNumber::digits_string[pos-(max_integer - BigNumber::integer_lenght)];
					result[1] = b.digits_string[pos];
				}
			}
			else if (b.integer_lenght < max_integer)
			{
				if (pos < (max_integer - b.integer_lenght))
				{
					result[0] = BigNumber::digits_string[pos];
					result[1] = zero_character[0];
				}
				else
				{
					result[0] = BigNumber::digits_string[pos];
					result[1] = b.digits_string[pos-(max_integer - b.integer_lenght)];
				}
			}
		}
		else//here we are looking at fractional part
		{
			pos -= max_integer;
			if (BigNumber::dotplace == b.dotplace)
			{
				result[0] = BigNumber::digits_string[BigNumber::integer_lenght+pos];
				result[1] = b.digits_string[b.integer_lenght+pos];
			}
			else if (BigNumber::dotplace < max_dotplace)
			{
				if (pos >= BigNumber::dotplace)
				{
					result[0] = zero_character[0];
					result[1] = b.digits_string[b.integer_lenght+pos];
				}
				else
				{
					result[0] = BigNumber::digits_string[BigNumber::integer_lenght+pos];
					result[1] = b.digits_string[b.integer_lenght+pos];
				}
			}
			else if (b.dotplace < max_dotplace)
			{
				if (pos>= b.dotplace)
				{
					result[0] = BigNumber::digits_string[BigNumber::integer_lenght+pos];
					result[1] = zero_character[0];
				}
				else
				{
					result[0] = BigNumber::digits_string[BigNumber::integer_lenght + pos];
					result[1] = b.digits_string[b.integer_lenght+pos];
				}
			}
		}
		
		return result ;
	}
	comp absolute_compare(BigNumber &b)//compare absolute values of two integers
	{
		std::string::size_type max_lenght;
		std::string s;
		//compare integer digits for fast comparing
		if (BigNumber::integer_lenght > b.integer_lenght) return bigger;
		if (BigNumber::integer_lenght < b.integer_lenght) return smaller;
		//
		max_lenght = BigNumber::MaxInteger(b) + BigNumber::MaxDotplace(b);
		for (std::string::size_type i = 0; i < max_lenght; ++i)
		{
			s = same_pos_digits(b, i);
			if (s[0] < s[1]) return smaller;
			if (s[0] > s[1]) return bigger;
		}
		return equal;
	}
	comp compare(BigNumber &b)// compare two integers
	{
		comp result;
		//First check signs and number of digits for fast comparing
		if (BigNumber::positive && !b.positive) return bigger;//it is bigger than b
		if (!BigNumber::positive&&b.positive) return smaller;// it is smaller than b
		//at this point two numbers definitely have same sign
		result = BigNumber:: absolute_compare(b);
		//if two numbers are negative
		if (!BigNumber::positive && !b.positive)
		{
			if (result == bigger) result = smaller;
			if (result == smaller) result = bigger;
		}
		return result;
	}
	std::string::size_type MaxDotplace(BigNumber &b)
	{
		//find out wich has bigger dotplace
		if (BigNumber::dotplace >= b.dotplace)
			return BigNumber::dotplace;
		else
			return b.dotplace;
	}
	std::string::size_type MaxInteger(BigNumber &b)
	{
		//find out wich has bigger ineger part
		if (BigNumber::integer_lenght >= b.integer_lenght)
			return BigNumber::integer_lenght;
		else
			return b.integer_lenght;
	}
	void BigNumber::read_string()
	{
		//int sub_end;
		//int sub_lenght;
		//find out the sign of the number
		if (digits_string[0] == positive_sign[0])
			digits_string.erase(0, 1); // erase "+" sign 
		if (digits_string[0] == negative_sign[0])
		{
			digits_string.erase(0, 1); // erase "-" sign 
			positive = false;
		}
		else
			positive = true;
		//find out the period place
		std::string::size_type p = digits_string.find(period);// using index-based iterator for practice
		if (p != std::string::npos)
		{
			dotplace = digits_string.length() - p - 1;
			digits_string.erase(p, 1);
		}
		else dotplace = 0;
		//find out if it is a valid number or not
		is_valid = true; //initially assume it is a valid number
		std::string::iterator i;//accessing elements using iterator-based iterator for practice
		for (i = digits_string.begin(); i != digits_string.end(); ++i)
		{
			if (valid_digits.find(*i) == std::string::npos)
			{
				is_valid = false;
				break;
			}
		}
		if (is_valid)  
			integer_lenght= BigNumber::digits_string.length() - BigNumber::dotplace;
		else
			set_to_zero();// if input string is not a valid number load it with zero
	}
public:
	std::string period = ".";
	std::string negative_sign = "-";
	std::string positive_sign = "+";
	std::string zero_character = "0";
	std::string valid_digits = "0123456789";

	//positive=true means number's sign is positive and if it is false means sign is negative
	bool positive;
	//if invalid string of data feed to make a big number is_valid will be false
	bool is_valid;
	//empty constructor
	BigNumber::BigNumber() 
	{
		set_to_zero();
	}
	//constructor for string input
	BigNumber::BigNumber(std::string s)
	{
		set(s);
	}
	//constructor for long double input
	BigNumber::BigNumber(long double n)
	{
		set(n);
	}
	//set by string type
	void BigNumber::set(std::string &s)
	{
		digits_string.assign(s); //copy s content into digits_string for further processing
		read_string();
	}
	//set by int and double type
	void BigNumber::set(long double n)
	{
		digits_string.assign(std::to_string(n));
		read_string();
	}
	//set by char type
	void BigNumber::set(char *s)
	{
		digits_string.assign(s);
		read_string();
	}
	void BigNumber::set_to_zero()
	{
		dotplace = 0;
		integer_lenght = 1;
		positive = true;
		digits_string = zero_character[0];
		is_valid = true;
	}
	std::string get_string()
	{
		std::string result;
		if (!BigNumber::positive) result = negative_sign;
		result.append(BigNumber::digits_string, 0, BigNumber::integer_lenght);
		if (BigNumber::dotplace > 0)
		{
			result.push_back(BigNumber::period[0]);
			result.append(BigNumber::digits_string, BigNumber::integer_lenght);
		}
		return result;
	}
	BigNumber BigNumber::add(BigNumber &b)
	{
		BigNumber result;
		std::string::size_type max_dotplace = MaxDotplace(b);
		std::string::size_type max_lenght = max_dotplace+ MaxInteger(b);
		std::string::size_type result_lenght = max_lenght+1;
		bool first_non_zero = false;
		bool scalar_sub = false;
		result.dotplace = max_dotplace;
		std::string s;
		int sum_result;
		int sum_flag=0;
		//reserve maximum capacity for result to improve performance
		//depends on the number values this reserve capacity may be used
		//for example sum of two huge numbers may equals to 0 but here we consider worse case senario
		result.digits_string.assign(result_lenght, zero_character[0]);
		//
		comp compare_result = absolute_compare(b);
		if (BigNumber::positive&&b.positive) result.positive = true;
		else if (!BigNumber::positive && !b.positive) result.positive = false;
		else if (compare_result == bigger) { result.positive = BigNumber::positive; scalar_sub = true; }
		else if (compare_result == smaller) {result.positive = b.positive; scalar_sub = true;}
		else if (compare_result == equal)
		{
			result.set_to_zero();
			return result;
		}
		for (std::string::size_type i = max_lenght;i>0; --i)
		{
			s = same_pos_digits(b, i-1);
			if (scalar_sub)
			{
				if (compare_result == bigger)
					sum_result = valid_digits.find(s[0]) - valid_digits.find(s[1]) - sum_flag;
				else
					sum_result = valid_digits.find(s[1]) - valid_digits.find(s[0]) - sum_flag;

					if (sum_result < 0)
					{
						sum_result += 10;
						sum_flag = 1;
					}
					else
					{
						sum_flag = 0;

					}
			}
			else
			{
				sum_result = valid_digits.find(s[0]) + valid_digits.find(s[1]) + sum_flag;
				if (sum_result > 9)
				{
					sum_result -= 10;
					sum_flag = 1;
				}
				else
				{
					sum_flag = 0;
				}
			}
			if ((!first_non_zero) && (sum_result != 0) || ((max_lenght - i) >= max_dotplace))
			{
				first_non_zero = true;

			}
		
			if (first_non_zero)
			{
				--result_lenght;
				result.digits_string[result_lenght] = valid_digits[sum_result];
			}
			else
			{
				--result.dotplace;
				if ((max_lenght - i) >= max_dotplace)
				{
					result.dotplace = 0;
				}
			}
		}
		if (sum_flag != 0)
		{
			--result_lenght;
			result.digits_string[result_lenght] = valid_digits[sum_flag];
		}
		//remove zero from left
		while (result.digits_string[result_lenght] == zero_character[0] && result_lenght<result.digits_string.length())
		{
			++result_lenght;
		}
		if (result_lenght>0) result.digits_string.erase(0, result_lenght);
		result.integer_lenght = result.digits_string.length() - result.dotplace;
		return result;
	}
};

int main(array<System::String ^> ^args)
{

	BigNumber A,B,C;
	std::string x;

	while (x != "3.14")
	{
		std::cout << "Enter first number:";
		std::getline(std::cin, x);//getting line of string as input
		//std::cout << std::endl;
		 A.set(x);
		 std::cout << "Enter second number:";
		 std::getline(std::cin, x);//getting line of string as input
		 //std::cout << std::endl;
		 B.set(x);
		 C = A.add(B);
		 std::cout << C.get_string() << std::endl;
		

	}


    return 0;
}
