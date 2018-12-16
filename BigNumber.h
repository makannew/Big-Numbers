/**
 * @file BigNumber.h
 * @brief BigNumber class declarations
 * @mainpage  
 * This class can strore and do math operations with realy big numbers.
 *
 * The numbers could be integer or fractional with thausands of digits.
 * It uses string as data containers, so the limitation of how big they can be will defined 
 * by limitaion of std::string class which it will be limited by hardware resources
 *
 * The example below shows how to use this class
 *@code
 * #include "BigNumber.h"
 * #include <iostream>
 * #include <string>
 *
 * int main() {
 * BigNumber i,j,k;
 * i = "0.0000000000000000000000000000000000000000000000000000000001"
 * j = "-100000000000000000000000000000000000000000000000000000000000"
 * 
 * std::cout << i + j << std::endl;
 * std::cout << i - j << std::endl;
 * std::cout << i * j << std::endl;
 * std::cout << i / j << std::endl;
 * if (i == j) std::cout << "i = j";
 * if (i > j) std::cout << "i > j"; 
 * if (i < j) std::cout << "i = j";
 * {
 * @endcode
 *    
 * @author Makan Edrisi
 * @version 1.1
 * @date Nov 2018
*/

#include<iostream>
#include<string>
using namespace std;

#ifndef BigNumber_H
#define BigNumber_H
class BigNumber {
public:
	/// default constructor.
	BigNumber();

	/// Overload contructor for string input.
	BigNumber(string s);

	///constructor char type
	BigNumber(char * s);

	///constructor int type
	BigNumber(int n);

	///constructor  long int type
	BigNumber(long int n);

	///constructor long long int type
	BigNumber(long long int n);

	///constructor double type
	BigNumber(double n);

	///constructor long double type
	BigNumber(long double n);



	/** @brief set BigNumber correspondent to input string
	*
	*     a member function initialize BigNumber from input string of valid digits.
	*
	*     - Sign is defined by "+" or "-" in first character (there is no need to add sign for positive numbers).
	*
	*     - Integer part can separated with "." from fractional part.
	*
	*     - Zeros befor number will be ignored.
	* 
	* @param s the string of valid digits
	* @return void
	*
	* @see set(char *s)
	*/
	void set(string &s);

	/** @brief set BigNumber correspondent to input integer type
	*
	*     a member function initialize BigNumber from input an integer
	*
	*     the number limit is limit of integer type
	*
	* @param n the input number with double or integer type
	* @return void
	*
	* @see set(char *s) 
	*/
	void set(int n);

	///@see set(int n)
	void set(long int n);
	///@see set(int n)
	void set(long long int n);
	///@see set(int n)
	void set(double n);
	///@see set(int n)
	void set(long double n);
	///@see set(int n)
	void set(unsigned long int n);
	


	
	


	/** @brief set BigNumber correspondent to input characters
	*
	*     a member function initialize BigNumber from input Char type with point to the valid digits
	*
	*     - Sign is defined by "+" or "-" in first character (there is no need to add sign for positive numbers).
	*
	*     - Integer part can separated with "." from fractional part.
	*
	*     - Zeros befor number will be ignored.
	*
	* @param s as char type point to valid digits
	* @return void
	* 
	* @see set()
	*/
	void set(char *s);
	

	/** @brief set BigNumber equal to zero
	*
	* @param no need
	* @return void
	*
	* @see set()
	*/
	void set_to_zero();

	/** @brief get BigNumber as a string
	*
	*	it will generate a string to show a BigNumber value
	*
	* @param no need
	* @return void
	*
	*/
	string get_string();

	///get sign of the number True= positive, false= negative
	bool get_sign() const;


	/** @brief add a BigNumber to this BigNumber
	*
	*	overloaded operator + also can be used 
	*
	*@code
	* #include "BigNumber.h"
	* #include <iostream>
	* #include <string>
	*
	* int main() {
	* BigNumber i = "517625387123871628"
	* BigNumber j = "0.00982398"
	* BigNumber k;
	* k = i + j; 
	* std::cout << i + j << std::endl;
	 * std::cout << k << std::endl;
	* {
	* @endcode
	*
	* @param b is a BigNumber that would be add
	* @return void
	*
	* @see sub()
	* @see mul()
	* @see div()
	* @see mul_10()
	*/
	BigNumber add(BigNumber &b);

	BigNumber mul(BigNumber &b);

	BigNumber sub(BigNumber &b);

	BigNumber div(BigNumber &b);

	void mul_10(std::string::size_type = 1); // default mul by 10

	void dec();

	void inc();

	void abs();

	bool operator != (BigNumber &b);
	bool operator == (BigNumber &b);
	bool operator > (BigNumber &b);
	bool operator < (BigNumber &b);
	bool operator >= (BigNumber &b);
	bool operator <= (BigNumber &b);
	BigNumber operator + (BigNumber &b);
	BigNumber operator - (BigNumber &b);
	BigNumber operator / (BigNumber &b);
	BigNumber operator * (BigNumber &b);
	void operator -- ();
	void operator ++ ();
	
	friend ostream & operator << (ostream & os, BigNumber &b);

private:
	//Member Variables

	//for comparing two numbers
	enum comp { equal, bigger, smaller };

	string period = ".";

	string negative_sign = "-";

	string positive_sign = "+";

	string zero_character = "0";

	string valid_digits = "0123456789";

	//maximum digits of fraction part during dividing
	string::size_type max_div_digits = 100;

	//store big number as string of digits
	string digits_string="0";

	//fraction part of the number will define by dotplace
	string::size_type dotplace=0;

	//integer part of the number will define by integer_lenght
	string::size_type integer_lenght=1;

	//radix or base for number interpretation
	int base_radix = 10;



	//positive=true means number's sign is positive and if it is false means sign is negative
	bool positive=true;

	//if invalid string of data feed to make a big number is_valid will be false
	bool is_valid=true;

	//Member private functions
	string same_pos_digits(BigNumber &b, string::size_type pos) const;

	comp absolute_compare(BigNumber &b) const;

	comp compare(BigNumber &b) const;

	string::size_type max_dotplace(BigNumber &b) const;

	string::size_type max_integer(BigNumber &b) const;

	void read_string();
	
};

#endif 
