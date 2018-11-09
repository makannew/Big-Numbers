#include "stdafx.h"
#include<iostream>
#include<string>

using namespace System;
class BigNumber 
{
private:
	//constants
	const std::string period = ".";
	const std::string minus_sign = "-";
	const std::string plus_sign = "+";
	const std::string valid_digits = "0123456789";
	const std::string default_value = "0";
	enum comparing{equal,bigger,smaller};
	//storage for a big number
	std::string digits_string;
	std::string::size_type dotplace;
	std::string::size_type integer_lenght;
	bool positive;
	bool is_valid;
	//functions
	comparing compare(BigNumber &b)
	{
		comparing result;
		//First check signs and number of digits for fast comparing
		if (BigNumber::positive && !b.positive) return bigger;//it is bigger than b
		if (!BigNumber::positive&&b.positive) return smaller;// it is smaller than b
		if (BigNumber::positive&&b.positive)//if both are positive
		{
			if (BigNumber::integer_lenght > b.integer_lenght) return bigger;
			if (BigNumber::integer_lenght < b.integer_lenght) return smaller;
		}
		else//both are negative
		{
			if (BigNumber::integer_lenght > b.integer_lenght) return smaller;
			if (BigNumber::integer_lenght < b.integer_lenght) return bigger;
		}
		//if signs and integer leghnts are same compare integer parts
		for (std::string::size_type i=0; i < b.integer_lenght; ++i)
		{
			if (BigNumber::positive&&b.positive)
			{
				if (BigNumber::digits_string[i] > b.digits_string[i])
				{
					return bigger;
				}
				if (BigNumber::digits_string[i] < b.digits_string[i])
				{
					return smaller;
				}
			}
			else
			{
				if (BigNumber::digits_string[i] > b.digits_string[i])
				{
					return smaller;
				}
				if (BigNumber::digits_string[i] < b.digits_string[i])
				{
					return bigger;
				}
			}

		}
		//compare numbers digits after period. At this point integer lenght of both numbers are same
		for (std::string::size_type i = 0; i < BigNumber::MaxDotplace(b); ++i)
		{
			if (i >= BigNumber::dotplace)
			{
				if (b.digits_string[b.integer_lenght + i] > 0) return smaller;
			}
			if (i >= b.dotplace)
			{
				if (BigNumber::digits_string[BigNumber::integer_lenght + i] > 0) bigger;
			}

			if (BigNumber::digits_string[BigNumber::integer_lenght + i] > b.digits_string[b.integer_lenght + i])
			{
				return bigger;
			}
			if (BigNumber::digits_string[BigNumber::integer_lenght + i] < b.digits_string[b.integer_lenght + i])
			{
				return smaller;
			}
		}
		//if it reaches up to here then they would be equal
		return equal;
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
		if (digits_string[0] == plus_sign[0])
			digits_string.erase(0, 1); // erase "+" sign 
		if (digits_string[0] == minus_sign[0])
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
		positive = true;
		digits_string = default_value;
		is_valid = true;
	}
	BigNumber BigNumber::add(BigNumber &b)
	{
		BigNumber result;
		std::string::size_type max_dotplace = MaxDotplace(b);
		std::string::size_type max_integer = MaxInteger(b);

		//reserve needed capacity+1 for result to improve performance
		result.digits_string.reserve(max_integer + max_dotplace + 1);

		//print
		std::cout << "Number a:" << BigNumber::digits_string << std::endl;
		std::cout << "Number b:" << b.digits_string << std::endl;
		std::cout << "Compare between a&b:" << compare(b) << std::endl;

		return result;
	}
	

};

int main(array<System::String ^> ^args)
{
	//int i = 2323;
	BigNumber a,b,c;
	a.set("3345.1123");
	//b.set(65.23333);
	//b.set(i);
	std::string x = "3.1415";
	//long double x = 33.5;
	while (x != "0")
	{
		std::cout << "Enter a number:";
		std::getline(std::cin, x);//getting line of string as input
		std::cout << std::endl;
		//std::cout << "original number:" << x << std::endl;
		b.set(x);
		a.add(b);
		//std::cout << "is valid:" << y.valid_number() << std::endl;

	}


    return 0;
}
