#pragma once

#include <string>
#include <vector>
#include "Transaction.h"
#include "defs.h"

using namespace std;

class Transaction;	// Forward declaration due to circular includes

/**
*  A class used to represent a client. 
*  Each client object has a name and a nif (from the portuguese "Numero de Identificação Fiscal").
*/

class Client
{
	string name;	/**< string name. The client's name. */
	nif_t nif;		/**< nif_t nif. The client's NIF. */

public:

	/**
	* A default constructor.
	*/
	Client() = default;

	/**
	* A constructor.
	* The construtor creates a Client object, reading the data from the input stream passed as argument.
	* @param in The input stream to read from in order to build the client object.
	*/
	Client(ifstream& in); 

	/**
	* A constructor.
	* The construtor creates a client object with the data passed as arguments.
	* @param name The client's name.
	* @param nif  The client's NIF. 
	*/
	Client(string name, nif_t nif);

	/**
	* A const member function with no arguments to get the client's name.
	* @return A string, the client's name.
	*/
	string getName() const;

	/**
	* A const member function with no arguments to get the client's NIF.
	* @return A nif_t, the client's NIF.
	*/
	nif_t getNIF() const;

	/**
	* A const member function that writes the client's info to the output stream.
	* Generally used to save the client's attributes to a file.
	* @param out The output stream to write the client's information.
	*/
	void saveChanges(ofstream& out) const;

	/**
	*  A class used to represent an exception.
	*  The exception object contains the invalid NIF
	*/
	class InvalidNIF
	{
		nif_t nif;
	public:
		/**
		* A constructor.
		* The construtor creates an InvalidNIF object with the supplied NIF.
		* @param nif	The nif in question.
		*/
		InvalidNIF(nif_t nif) : nif(nif) {}

		/**
		* A const member function with no arguments to get the object's NIF.
		* @return A nif_t, the NIF that originated the creation of this object.
		*/
		nif_t getNIF() const {
			return nif;
		}
	};
};


/**
* Overload of Operator << for class Client.
* Prints the specified Client (2nd argument) to the outstream passed as 1st argument.
* @param out The outstream to write to.
* @param c The client to be written.
* @return Returns the output stream to allow chainning
*/
ostream& operator<<(ostream& out, const Client& c);