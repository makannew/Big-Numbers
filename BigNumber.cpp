//Function definitions
#include "stdafx.h"
#include "BigNumber.h"
#include <assert.h>


string BigNumber::same_pos_digits(BigNumber &b, string::size_type pos) const	{
		string result = "00";
		string::size_type max_dotplace = BigNumber::max_dotplace(b);
		string::size_type max_integer = BigNumber::max_integer(b);
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
					result[0] = BigNumber::digits_string[pos - (max_integer - BigNumber::integer_lenght)];
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
					result[1] = b.digits_string[pos - (max_integer - b.integer_lenght)];
				}
			}
		}
		else//here we are looking at fractional part
		{
			pos -= max_integer;
			if (BigNumber::dotplace == b.dotplace)
			{
				result[0] = BigNumber::digits_string[BigNumber::integer_lenght + pos];
				result[1] = b.digits_string[b.integer_lenght + pos];
			}
			else if (BigNumber::dotplace < max_dotplace)
			{
				if (pos >= BigNumber::dotplace)
				{
					result[0] = zero_character[0];
					result[1] = b.digits_string[b.integer_lenght + pos];
				}
				else
				{
					result[0] = BigNumber::digits_string[BigNumber::integer_lenght + pos];
					result[1] = b.digits_string[b.integer_lenght + pos];
				}
			}
			else if (b.dotplace < max_dotplace)
			{
				if (pos >= b.dotplace)
				{
					result[0] = BigNumber::digits_string[BigNumber::integer_lenght + pos];
					result[1] = zero_character[0];
				}
				else
				{
					result[0] = BigNumber::digits_string[BigNumber::integer_lenght + pos];
					result[1] = b.digits_string[b.integer_lenght + pos];
				}
			}
		}

		return result;
	}
//compare absolute values of two integers
BigNumber::comp BigNumber::absolute_compare(BigNumber &b) const	{
		string::size_type max_lenght;
		string s;
		//compare integer digits for fast comparing
		if (BigNumber::integer_lenght > b.integer_lenght) return bigger;
		if (BigNumber::integer_lenght < b.integer_lenght) return smaller;
		//
		max_lenght = BigNumber::max_integer(b) + BigNumber::max_dotplace(b);
		for (string::size_type i = 0; i < max_lenght; ++i)
		{
			s = BigNumber::same_pos_digits(b, i);
			if (s[0] < s[1]) return smaller;
			if (s[0] > s[1]) return bigger;
		}
		return equal;
	}
// compare two integers
BigNumber::comp BigNumber::compare(BigNumber &b) const {
		BigNumber::comp result;
		//First check signs and number of digits for fast comparing
		//it is bigger than b
		if (BigNumber::positive && !b.positive) return bigger;
		// it is smaller than b
		if (!BigNumber::positive&&b.positive) return smaller;
		//at this point two numbers definitely have same sign
		result = BigNumber::absolute_compare(b);
		//if two numbers are negative
		if (!BigNumber::positive && !b.positive)
		{
			if (result == bigger) result = smaller;
			if (result == smaller) result = bigger;
		}
		return result;
	}
string::size_type BigNumber::max_dotplace(BigNumber &b) const {
		//find out wich has bigger dotplace
		if (BigNumber::dotplace >= b.dotplace)
			return BigNumber::dotplace;
		else
			return b.dotplace;
	}
string::size_type BigNumber::max_integer(BigNumber &b) const	{
		//find out wich has bigger ineger part
		if (BigNumber::integer_lenght >= b.integer_lenght)
			return BigNumber::integer_lenght;
		else
			return b.integer_lenght;
	}
void BigNumber::read_string() {
		//find out the sign of the number
		if (digits_string[0] == positive_sign[0])
			digits_string.erase(0, 1); // erase "+" sign 
		if (digits_string[0] == negative_sign[0])
		{
			digits_string.erase(0, 1); // erase "-" sign 
			positive = false;
		}
		else
		{
			positive = true;
		}
		//remove zere from left
		if (digits_string.find_first_not_of(zero_character[0]) != std::string::npos)
		{
			digits_string.erase(0, digits_string.find_first_not_of(zero_character[0]));
		}
		else
		{
			BigNumber::set_to_zero();
			BigNumber::is_valid = false;
			return;
		}


		//find out the period place
		string::size_type p = digits_string.find(period);
		if (p != string::npos)
		{
			digits_string.erase(p, 1);
			if (digits_string.find_first_not_of(zero_character) != std::string::npos)
			{
				dotplace = digits_string.length() - p ;
			}
			else
			{
				BigNumber::set_to_zero();
				return;
			}
		}
		else
		{
			dotplace = 0;
		}
		if (digits_string == "") 
		{ 
			BigNumber::set_to_zero();
			BigNumber::is_valid = false;
			return;
		}
		//find out if it is a valid number or not
		is_valid = true; //initially assume it is a valid number
		string::iterator i;//accessing elements using iterator-based iterator
		for (i = digits_string.begin(); i != digits_string.end(); ++i)
		{
			if (valid_digits.find(*i) == string::npos)
			{
				is_valid = false;
				break;
			}
		}
		if (is_valid)
		{
			integer_lenght = BigNumber::digits_string.length() - BigNumber::dotplace;
		}
		else
		{
			BigNumber::set_to_zero();// if input string is not a valid number load it with zero
			BigNumber::is_valid = false;
		}
	}


BigNumber::BigNumber() {
	}

BigNumber::BigNumber(string s) {
	BigNumber::set(s);
}

BigNumber::BigNumber(char * s) {
	BigNumber::set(s);
}

BigNumber::BigNumber(int n) {
	BigNumber::set(n);
}

BigNumber::BigNumber(long int n) {
	BigNumber::set(n);
}

BigNumber::BigNumber(long long int n) {
	BigNumber::set(n);
}

BigNumber::BigNumber(double n) {
	BigNumber::set(n);
}

BigNumber::BigNumber(long double n) {
	BigNumber::set(n);
}


void BigNumber::set(string &s) {
	digits_string.assign(s); //copy s content into digits_string for further processing
	BigNumber::read_string();
}

void BigNumber::set(char *s) {
	digits_string.assign(s);
	BigNumber::read_string();
}

void BigNumber::set(int n) {
	BigNumber::set(to_string(n));
}

void BigNumber::set(long int n) {
	BigNumber::set(to_string(n));
}

void BigNumber::set(long long int n) {
	BigNumber::set(to_string(n));
}

void BigNumber::set(double n) {
	BigNumber::set(to_string(n));
}


void BigNumber::set(long double n) {
		BigNumber::set(to_string(n));
	}
void BigNumber::set(unsigned long int n) {
	BigNumber::set(to_string(n));
}


	
void BigNumber::set_to_zero() {
		dotplace = 0;
		integer_lenght = 1;
		positive = true;
		digits_string = zero_character[0];
		is_valid = true;
	}
string BigNumber::get_string()	{
		string result;
		result = BigNumber::digits_string;
		if (BigNumber::dotplace != 0) result.insert(result.length() - BigNumber::dotplace, BigNumber::period);
		if (result[0] == period[0]) result.insert(0, zero_character);
		if (!BigNumber::positive) result = negative_sign + result;
		return result;
	}
bool BigNumber::get_sign() const {
	return positive;
}
BigNumber BigNumber::add(BigNumber &b) {
		BigNumber result;
		string::size_type max_dotplace = BigNumber::max_dotplace(b);
		string::size_type max_lenght = max_dotplace + BigNumber::max_integer(b);
		string::size_type result_lenght = max_lenght + 1;
		bool first_non_zero = false;
		bool scalar_sub = false;
		result.dotplace = max_dotplace;
		string s;
		int sum_result;
		int sum_flag = 0;
		//reserve maximum capacity for result to improve performance
		//depends on the number values this reserve capacity may be used
		//for example sum of two huge numbers may equals to 0 but here we consider worse case senario
		result.digits_string.assign(result_lenght, zero_character[0]);
		//
		BigNumber::comp compare_result = absolute_compare(b);
		if (BigNumber::positive&&b.positive) result.positive = true;
		else if (!BigNumber::positive && !b.positive) result.positive = false;
		else if (compare_result == bigger) { result.positive = BigNumber::positive; scalar_sub = true; }
		else if (compare_result == smaller) { result.positive = b.positive; scalar_sub = true; }
		else if (compare_result == equal)
		{
			result.set_to_zero();
			return result;
		}
		for (string::size_type i = max_lenght; i > 0; --i)
		{
			s = BigNumber::same_pos_digits(b, i - 1);
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

		result_lenght = 0;
		//remove zero from left
		
		while (result.digits_string[result_lenght] == zero_character[0] && (result_lenght + result.dotplace ) < result.digits_string.length())
		{
			++result_lenght;
		}
		if (result_lenght > 0) result.digits_string.erase(0, result_lenght);

		
		result.integer_lenght = result.digits_string.length() - result.dotplace;
		return result;
	}
BigNumber BigNumber::mul(BigNumber &b) {
	// first detect rouphly bigger and smaller number to always mul smaller one to bigger one
	// to cause less addition which it is more expensive
	BigNumber * bigger_number;
	BigNumber * smaller_number;
	if ((BigNumber::integer_lenght + BigNumber::dotplace) < (b.integer_lenght + b.dotplace))
	{
		smaller_number = this;
		bigger_number = &b;
	}
	else
	{
		smaller_number = &b;
		bigger_number = this;
	}

	// unsigned long int can safely add two numbers, each one up to 8 decimal digits
	// so each time we multiply two numbers with 4 digits to make sure the results are within the limits
	// it can shows 0 to 4,294,967,295. In this way we can bnefit from 32bit ALU hardware mutiplication
	unsigned long int x(0);
	unsigned long int y(0);
	unsigned long int carrier(0);
	std::string temp_string;
	std::string each_product;
	std::string::size_type mul_digits_step (4);// multiply 4 digits each time
	std::string digits_step_zeros = "0000";
	std::string shift_zeros = "";
	std::string::size_type smaller_number_iterator = smaller_number->integer_lenght + smaller_number->dotplace ;
	std::string::size_type bigger_number_iterator = bigger_number->integer_lenght + bigger_number->dotplace ;
	std::string::size_type final_dotplace;
	BigNumber result = zero_character;
	BigNumber temp_result = zero_character;
	//check if one of them is zero
	if (smaller_number->digits_string == zero_character || bigger_number->digits_string == zero_character) return result;
	//
	while (smaller_number_iterator > 0)
	{
		if (smaller_number_iterator <= mul_digits_step)
		{
			x = std::stoul(smaller_number->digits_string.substr(0,smaller_number_iterator), nullptr, base_radix);
			smaller_number_iterator = 0;
		}
		else
		{
			smaller_number_iterator -= mul_digits_step;
			x = std::stoul(smaller_number->digits_string.substr(smaller_number_iterator  , mul_digits_step), nullptr, base_radix);
		}
		each_product = shift_zeros;
		shift_zeros += digits_step_zeros;
		bigger_number_iterator = bigger_number->integer_lenght + bigger_number->dotplace;
		carrier = 0;
		while (bigger_number_iterator > 0)
		{
			if (bigger_number_iterator <= mul_digits_step)
			{
				y = std::stoul(bigger_number->digits_string.substr(0, bigger_number_iterator), nullptr, base_radix);
				bigger_number_iterator = 0;
			}
			else
			{
				bigger_number_iterator -= mul_digits_step;
				y = std::stoul(bigger_number->digits_string.substr(bigger_number_iterator, mul_digits_step), nullptr, base_radix);
			}
			y = (x * y) + carrier;
			temp_string = std::to_string(y);
			if (temp_string.length() > mul_digits_step)
			{
				carrier = std::stoul(temp_string.substr(0,temp_string.length () - mul_digits_step), nullptr, base_radix);
				temp_string.erase(0 , temp_string.length() - mul_digits_step);
			}
			else
			{
				carrier = 0;
			}
			while (temp_string.length() < mul_digits_step)
			{
				temp_string.insert(0, zero_character);
			}
			each_product.insert(0, temp_string);

		}
		if (carrier != 0)
		{
			each_product.insert(0, std::to_string(carrier));
		}
		//
		final_dotplace = smaller_number->dotplace + bigger_number->dotplace;
		while (each_product.length() < final_dotplace)
		{
			each_product.insert(0, zero_character);
		}
		each_product.insert(each_product.length() - final_dotplace, period);

		temp_result.set(each_product);

		
		result = result.add(temp_result);


	}
	if (bigger_number->positive != smaller_number->positive) result.positive = false;
	
	
	return result;

}
BigNumber BigNumber::sub(BigNumber &b)
{
	BigNumber result;
	b.positive = !b.positive;
	result = add(b);
	b.positive = !b.positive;
	return result;
}
BigNumber BigNumber::div(BigNumber &b)
{
	// unsigned long int can safely use for dividing two numbers, each one up to 9 decimal digits
	// it can shows 0 to 4,294,967,295. In this way we can bnefit from 32bit ALU hardware division
	unsigned long int q,n,d;
	BigNumber result, n_temp, d_temp, q_temp, temp;
	std::string::size_type d_extra_digits, n_extra_digits, largest_dotplace, d_max_digits, n_max_digits, final_dotplace;
	//initial values
	d_max_digits = 8;
	d_temp = b;
	temp = 0;
	result = 0;
	final_dotplace = 0;
		
	// check divide by zero
	assert(b != temp && "cannot divide by zero");
	// check if numerator is zero
	if (BigNumber::compare(temp) == equal)
	{
		return temp;
	}
	//convert nominator and divisor to integers
	if (BigNumber::dotplace > d_temp.dotplace)
	{
		largest_dotplace = BigNumber::dotplace;
	}
	else
	{
		largest_dotplace = d_temp.dotplace;

	}
	n_temp.set(BigNumber::get_string());
	n_temp.mul_10(largest_dotplace);
	d_temp.mul_10(largest_dotplace);
	//make them positive numbers
	n_temp.abs();
	d_temp.abs();

	d = std::stoul(d_temp.digits_string.substr(0,d_max_digits), nullptr, base_radix);
	if (d_temp.digits_string.length() > d_max_digits)
	{
		d_extra_digits = d_temp.digits_string.length() - d_max_digits;
	}
	else
	{
		d_extra_digits = 0;
	}


	while (final_dotplace <= max_div_digits && n_temp.digits_string != zero_character)
	{
		//make nominator bigger than divisor 
		while (n_temp < d_temp)
		{
			++final_dotplace;
			n_temp.mul_10();
			result.mul_10();
		}
		// assign n as enough digits from left of nominator to make sure it is bigger than d
		n_max_digits = d_max_digits;
		n = std::stoul(n_temp.digits_string.substr(0, n_max_digits), nullptr, base_radix);
		if (n < d)
		{
			++n_max_digits;
			n = std::stoul(n_temp.digits_string.substr(0, n_max_digits), nullptr, base_radix);
		}
		//calculate nominator excessive lenght than maximum arithmatic digits
		if (n_temp.digits_string.length() > n_max_digits)
		{
			n_extra_digits = n_temp.digits_string.length() - n_max_digits;
		}
		else
		{
			n_extra_digits = 0;
		}
		//arithmetic integer division
		q = n / d;
		//set q_temp as BigNumber type of q
		q_temp.set(q);
		//mul temp by enough 10 
		q_temp.mul_10(n_extra_digits - d_extra_digits);
		temp = d_temp * q_temp;
		while (temp > n_temp)
		{
			--q;
			//set q_temp as BigNumber type of q
			q_temp.set(q);
			//mul temp by enough 10 
			q_temp.mul_10(n_extra_digits - d_extra_digits);
			temp = d_temp * q_temp;
		}
		n_temp = n_temp - temp;
		result = result + q_temp;

	}
	//
	result.dotplace = final_dotplace;
	while(final_dotplace > result.digits_string.length())
	{
		result.digits_string.insert(0, zero_character);
	}
	result.integer_lenght = result.digits_string.length() - final_dotplace;
	//define result sign
	if ((BigNumber::positive && !b.positive)|| (!BigNumber::positive && b.positive))
	{
		result.positive = false;
	}
	return result;
}


void BigNumber::mul_10(std::string::size_type i) {

	if (BigNumber::digits_string != zero_character)
	{
		while (i > 0)
		{
			if (BigNumber::dotplace > 0)
			{
				--BigNumber::dotplace;
				if (BigNumber::integer_lenght > 0)
				{
					++BigNumber::integer_lenght;
				}
				else
				{
					if (BigNumber::digits_string[0] == zero_character[0]) 
					{ 
						BigNumber::digits_string.erase(0, 1);
					}
					else
					{
						++BigNumber::integer_lenght;

					}

				}
			}
			else
			{
				BigNumber::digits_string.push_back(zero_character[0]);
				++BigNumber::integer_lenght;
			}
			--i;
		}
	}
}

void BigNumber::dec() {
	BigNumber big_one;
	big_one.set(1);
	*this =  sub(big_one);
}

void BigNumber::inc() {
	BigNumber big_one;
	big_one.set(1);
	*this = add(big_one);
}

void BigNumber::abs() {
	if (!BigNumber::positive) BigNumber::positive = true;
}

bool BigNumber::operator != (BigNumber &b) {
	if (BigNumber::compare(b) == equal)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool BigNumber::operator == (BigNumber &b) {
	if (BigNumber::compare(b) == equal)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool BigNumber::operator > (BigNumber &b) {
	if (BigNumber::compare(b) == bigger)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BigNumber::operator < (BigNumber &b) {
	if (BigNumber::compare(b) == smaller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BigNumber::operator >= (BigNumber &b) {
	if (BigNumber::compare(b) == bigger || BigNumber::compare(b) == equal)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BigNumber::operator <= (BigNumber &b) {
	if (BigNumber::compare(b) == smaller || BigNumber::compare(b) == equal)
	{
		return true;
	}
	else
	{
		return false;
	}
}
BigNumber BigNumber::operator + (BigNumber &b) {
	return add(b);
}
BigNumber BigNumber::operator - (BigNumber &b) {
	return sub(b);
}
BigNumber BigNumber::operator / (BigNumber &b) {
	return div(b);
}
BigNumber BigNumber::operator * (BigNumber &b) {
	return mul(b);
}

void BigNumber::operator -- () {
	BigNumber::dec();
}

void BigNumber::operator ++ () {
	BigNumber::inc();
}
ostream & operator << (ostream & os, BigNumber &b) {
	os << b.get_string();
	return os;
}
