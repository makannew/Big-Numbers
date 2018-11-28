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
 * BigNumber A,B,C;
 * A = "0.0000000000000000000000000000000000000000000000000000000001"
 * B = "100000000000000000000000000000000000000000000000000000000000"
 * C = A.add(B);
 * std::cout << C.get_string() << endl;
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
	*     * Zeros befor number will be ignored.
	* 
	* @param s the string of valid digits
	* @return void
	*
	* @see set(char *s)
	*/
	void set(string &s);

	/** @brief set BigNumber correspondent to input double or integer type
	*
	*     a member function initialize BigNumber from input double or integer
	*
	*     the number limit is limit of double of integer type
	*
	* @param n the input number with double or integer type
	* @return void
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
	


	
	


	/** @brief set BigNumber correspondent to input characters
	*
	*     a member function initialize BigNumber from input Char type with point to the valid digits
	*
	*     - Sign is defined by "+" or "-" in first character (there is no need to add sign for positive numbers).
	*
	*     - Integer part can separated with "." from fractional part.
	*
	*     * Zeros befor number will be ignored.
	*
	* @param s as char type point to valid digits
	* @return void
	* 
	* @see set()
	*/
	void set(char *s);
	


	void set_to_zero();

	string get_string();

	///get sign of the number True= positive, false= negative
	bool get_sign() const;

	BigNumber add(BigNumber &b);

	BigNumber mul(BigNumber &b);

private:
	//Member Variables

	//for comparing two numbers
	enum comp { equal, bigger, smaller };

	string period = ".";

	string negative_sign = "-";

	string positive_sign = "+";

	string zero_character = "0";

	string valid_digits = "0123456789";

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
