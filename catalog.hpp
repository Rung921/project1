// catalog.hpp
// CSUF CPSC 131, Fall 2016, Project 1
//
// Classes that define a catalog of supermarket products.
//
// Name: Richard Ung
// Due:  October 11, 2016

#ifndef CATALOG_HPP
#define CATALOG_HPP

#include <stdexcept>
#include <string>
#include <vector>

// A product represents one particular kind of product, such as apples
// or cereal.
class Product {
public:
	// Create a product with a given code, name, and price.
	//
	// code is intended to be a UPC code (bar code) or PLU code in a
	// string.
	//
	// name may be any string.
	//
	// price is in units of dollars. It must be positive, or else this
	// function throws std::invalid_argument.
	Product(const std::string& code, const std::string& name, double price) :
		_code(code),
		_name(name)
	{
		// Checks for valid price. If not valid, throw an exception.
		if (price <= 0.0) throw std::invalid_argument("invalid price");
		_price = price;
	}

	~Product() {}

	// Accessors.
	const std::string& getCode() const { return _code; }
	const std::string& getName() const { return _name; }
	double getPrice() const { return _price; }

private:
	std::string _code, _name;
	double _price;
};

//---------------------------------------------------------------------------------

// A catalog represents a collection of all of the products available
// at a store.
class Catalog {
public:
	// Create a new catalog.
	//
	// maxProducts is the maximum number of products that can be
	// stored. It must be positive, or else this function throws
	// std::invalid_argument.
	Catalog(int maxProducts)
	{
		// Checks for valid maxProducts. If not valid, throw an exception.
		if (maxProducts <= 0) throw std::invalid_argument("negative or zero value");
		_maxProducts = maxProducts;
		_n = 0;
	}

	// Deallocate memory. 
	~Catalog() {
		for (int i = 0; i < _n; i++) {
			delete _productList.at(i);
			_productList.at(i) = NULL;
		}
	}

	// Accessors.
	int getMaxProducts() const {
		return _maxProducts;
	}

	int getNumProducts() const {
		return _n;
	}

	// Return true when the catalog cannot fit any more products.
	bool isFull() const {
		return _n >= _maxProducts;
	}

	// Add a new product to the catalog with a given code and name.
	//
	// code, name, and price have the same meaning as in a Product. If
	// price is invalid, throw std::invalid_argument.
	//
	// If this catalog is already full, throw overflow_error.
	//
	// Code must be different from all the product codes already in the
	// database. If it's not, throw std::invalid_argument.
	void addProduct(const std::string& code, const std::string& name, double price) {
		// Error Checking for price and if the vector is full.
		if (price <= 0.0) throw std::invalid_argument("invalid price");
		if (isFull()) throw std::overflow_error("overflow");

		// Checks if code already exists. If it exists, throw an exception.
		for (int i = 0; i < _n; i++) {
			if (_productList.at(i)->getCode() == code) throw std::invalid_argument("adding existing code");
		}

		// Create the product and add it to the catalog.
		_productList.push_back(new Product(code, name, price));
		_n++;
	}

	// Find a product by its code.
	//
	// code is a product code.
	//
	// Returns a const reference to the product with the matching code.
	//
	// Throw std::invalid_argument if no product with that code exists
	// in the catalog.
	const Product& findCode(const std::string& code) const {
		// Search if there is already a product with the code. 
		for (int i = 0; i < _n; i++) {
			if (_productList.at(i)->getCode() == code) {
				return *_productList.at(i);
			}
		}

		// If this is reached, no code exists. 
		throw std::invalid_argument("code does not exist");
	}

private:
	std::vector<Product*> _productList;
	int _maxProducts;
	int _n;
};

#endif
