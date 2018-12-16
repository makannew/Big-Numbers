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
 * To limit divition digits member variable max_div_digits can be set
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
 * j = "-300000000000000000000000000000000000000000000000000000000000"
 * 
 * std::cout << i + j << std::endl;
 * std::cout << i - j << std::endl;
 * std::cout << i * j << std::endl;
 * max_div_digits = 1000;
 * std::cout << i / j << std::endl;
 * if (i == j) std::cout << "i = j";
 * if (i > j) std::cout << "i > j"; 
 * if (i < j) std::cout << "i = j";
 * {
 * @endcode
 *    
 * @author Makan Edrisi
 * @version 1.1
 * @date Dec 2018
 *
 * Souce code can be found at <https://github.com/makannew/Big-Numbers>
*/

#include<iostream>
#include<string>
using namespace std;

#ifndef BigNumber_H
#define BigNumber_H
class BigNumber {
public:
	///maximum digits of fraction part during dividing
	string::size_type max_div_digits = 100;
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
	* i.add(j);
	* std::cout << i << std::endl;
	* std::cout << k << std::endl;
	* {
	* @endcode
	*
	* @param b is the BigNumber that will added to this BigNumber
	* @return BigNumber
	*
	* @see sub()
	* @see mul()
	* @see div()
	* @see mul_10()
	*/
	BigNumber add(BigNumber &b);

/** @brief multiply a BigNumber to this BigNumber
*
*	overloaded operator * also can be used
*
*@code
* #include "BigNumber.h"
* #include <iostream>
* #include <string>
*
* int main() {
* BigNumber i = "30"
* BigNumber j = "0.2"
* BigNumber k;
* k = i * j;
* i.mul(j);
* std::cout << i << std::endl;
* std::cout << k << std::endl;
* {
* @endcode
*
* @param b is the BigNumber that multiply to this BigNumber
* @return BigNumber
*
* @see add()
* @see sub()
* @see div()
* @see mul_10()
*/
	BigNumber mul(BigNumber &b);

/** @brief Subtract a BigNumber from this BigNumber
*
*	overloaded operator - also can be used
*
*@code
* #include "BigNumber.h"
* #include <iostream>
* #include <string>
*
* int main() {
* BigNumber i = "350"
* BigNumber j = "200"
* BigNumber k;
* k = i - j;
* i.sub(j);
* std::cout << i << std::endl;
* std::cout << k << std::endl;
* {
* @endcode
*
* @param b is the BigNumber that subtract from this BigNumber
* @return BigNumber
*
* @see add()
* @see mul()
* @see div()
* @see mul_10()
*/
	BigNumber sub(BigNumber &b);

/** @brief divide a BigNumber to this BigNumber
*
*	overloaded operator / also can be used
*
*@code
* #include "BigNumber.h"
* #include <iostream>
* #include <string>
*
* int main() {
* BigNumber i = "10"
* BigNumber j = "3"
* i.max_div_digits = 100; //continue dividing up to 100 fractional digits
* BigNumber k;
* k = i / j;
* i.div(j);
* std::cout << i << std::endl;
* std::cout << k << std::endl;
* {
* @endcode
*
* @param b is the BigNumber as divisor
* @return BigNumber
*
* @see add()
* @see sub()
* @see dmul()
* @see mul_10()
*/
	BigNumber div(BigNumber &b);

	/** @brief multiply a BigNumber by 10 ^ b
	*
	*
	*@code
	* #include "BigNumber.h"
	* #include <iostream>
	* #include <string>
	*
	* int main() {
	* BigNumber i = "3.14"
	* i.mul_10();
	* std::cout << i << std::endl;
	* i.mul_10(3);
	* std::cout << i << std::endl;
	* {
	* @endcode
	*
	* @param unsigned size_type is the number of 10 that multiply to this BigNumber (Default = 1)
	* @return BigNumber
	*
	* @see add()
	* @see mul()
	* @see div()
	* @see sub()
	*/
	void mul_10(std::string::size_type = 1); // default mul by 10

/** @brief decrease this BigNumber by 1
*
*	overloaded operator -- also can be used
*
*@code
* #include "BigNumber.h"
* #include <iostream>
* #include <string>
*
* int main() {
* BigNumber i = "1000"
* i.dec();
* std::cout << i << std::endl;
* --i;
* std::cout << i << std::endl;
* {
* @endcode
*
* @param no need
* @return void
*
* @see inc()
* @see add()
* @see sub()
* @see mul()
* @see div()
* @see mul_10()
*/
	void dec();

/** @brief increase this BigNumber by 1
*
*	overloaded operator ++ also can be used
*
*@code
* #include "BigNumber.h"
* #include <iostream>
* #include <string>
*
* int main() {
* BigNumber i = "1000"
* i.inc();
* std::cout << i << std::endl;
* ++i;
* std::cout << i << std::endl;
* {
* @endcode
*
* @param no need
* @return void
*
* @see dec()
* @see add()
* @see sub()
* @see mul()
* @see div()
* @see mul_10()
*/
	void inc();

/** @brief convert this BigNumber to absolute value
*
*	Disregard to the sign of the BigNumber it will always set to positive sign
*
*@code
* #include "BigNumber.h"
* #include <iostream>
* #include <string>
*
* int main() {
* BigNumber i = "-1"
* i.abs();
* std::cout << i << std::endl;
* {
* @endcode
*
* @param no need
* @return void
*
* @see dec()
* @see add()
* @see sub()
* @see mul()
* @see div()
* @see mul_10()
*/
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
	///Member Variables

	///for comparing two numbers
	enum comp { equal, bigger, smaller };
	///Default character for separating integer part from fractional part
	string period = ".";

	///Default negative sign charachter
	string negative_sign = "-";

	///Default positive sign chaacter
	string positive_sign = "+";

	///Default zero character
	string zero_character = "0";

	///Valid characters to represent decimal digits
	string valid_digits = "0123456789";



	///store big number as string of digits
	string digits_string="0";

	///fraction part of the number will define by dotplace
	string::size_type dotplace=0;

	///integer part of the number will define by integer_lenght
	string::size_type integer_lenght=1;

	///radix or base for numbers value interpretation
	int base_radix = 10;



	//positive=true means number's sign is positive and if it is false means sign is negative
	bool positive=true;

	//if invalid string of data feed to make a big number is_valid will be false
	bool is_valid=true;

	//Private functions
	string same_pos_digits(BigNumber &b, string::size_type pos) const;

	comp absolute_compare(BigNumber &b) const;

	comp compare(BigNumber &b) const;

	string::size_type max_dotplace(BigNumber &b) const;

	string::size_type max_integer(BigNumber &b) const;

	///Convert string to BigNumber
	void read_string();
	
};

#endif 
