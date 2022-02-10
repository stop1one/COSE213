#include <typeinfo>
#include <iostream>
#include <math.h>

// --- --- --- --- --- --- --- --- 
// Define the class
// --- --- --- --- --- --- --- --- 

class Polynomial;

class Term {
	friend class Polynomial;

private:
	float coef;
	int exp;
};

class Polynomial
{
public:
	// Default constructor p(x) = 0
	Polynomial()
	{
		capacity = 10;
		terms = 0;
		termArray = new Term[capacity];
	};
	
	// Copy constructor
	Polynomial(const Polynomial& source);

	// Destructor
	~Polynomial();

	// Assignment operator
	Polynomial& operator = (const Polynomial& source);

	// Sum of *this and source polynomials
	Polynomial operator+(const Polynomial& source);
	
	// Subtract of source polynomials from *this
	Polynomial operator-(const Polynomial& source);

	// Product of *this and source polynomials
	Polynomial operator*(const Polynomial& source);
	
	// Compute derivative of the current polynomial
	Polynomial Derivative();

	// Return true if left polynomial is identical to right polynomial
	bool operator==(const Polynomial& right);

	// Evaluate polynomial *this at x and return the result
	float Eval(float x);

	// Create a new term. If the term exists, overwrite its coefficient.
	void CreateTerm(const float coef, const int exp);


	// Print polynomial
	void Print()
	{
		if(terms == 0) std::cout << "0" << std::endl;
		else
		{
			for(int i=0; i<terms; i++)
			{
				float c = termArray[i].coef;
				int e = termArray[i].exp;
							
				if(c > 0 && i > 0)
				{
					std::cout << "+";
				}
				
				std::cout << c;
				if(e > 0) std::cout<<"x^"<<e;
			}
			std::cout << std::endl;
		}
	}
	
	int Capacity() const { return capacity; }
	int Terms() const { return terms; }
	Term& GetTerm(int x) const { return termArray[x]; } 

private:
	Term *termArray;
	int capacity; // max # of terms in this polynomial
	int terms;	  // current # of terms in this polynomial
};

// --- --- --- --- --- --- --- --- 
// Define the class function
// --- --- --- --- --- --- --- --- 

// Custom Function
char compare(int a, int b);
float power(float x, int n);

// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
	// ToDo
	this->capacity = source.capacity;
	this->terms = source.terms;
	this->termArray = new Term[capacity];
	for (int i = 0; i < terms; i++) {
		this->termArray[i].coef = source.termArray[i].coef;
		this->termArray[i].exp = source.termArray[i].exp;
	}
}	

// Destructor
Polynomial::~Polynomial()
{
	// ToDo
	delete[] termArray;
}

// Assignment operator
Polynomial& Polynomial::operator = (const Polynomial& source)
{
	// ToDo
	this->capacity = source.capacity;
	this->terms = source.terms;
	this->termArray = new Term[capacity];
	for (int i = 0; i < terms; i++) {
		this->termArray[i].coef = source.termArray[i].coef;
		this->termArray[i].exp = source.termArray[i].exp;
	}
	return *this;
}

 // Sum of *this and source polynomials
 Polynomial Polynomial::operator + (const Polynomial& source)
 {
 	Polynomial c;
	
	int first = 0, second = 0; float newCoef;
 	while (first < terms && second < source.terms) {
 		switch (compare(termArray[first].exp, source.termArray[second].exp)) {
 			case '=':
				newCoef = termArray[first].coef + source.termArray[second].coef;
				c.CreateTerm(newCoef, termArray[first].exp);
				first++; second++; break;
			case '>':
				c.CreateTerm(termArray[first].coef, termArray[first].exp);
				first++; break;
			case '<':
				c.CreateTerm(source.termArray[second].coef, source.termArray[second].exp);
				second++;
 		}
 	}
	for (; first < terms; first++)
		c.CreateTerm(termArray[first].coef, termArray[second].exp);
	for (; second < source.terms; second++)
		c.CreateTerm(source.termArray[second].coef, source.termArray[second].exp);

 	return c;
 }

// Subtract of source polynomials from *this
Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;

	int first = 0, second = 0; float newCoef;
 	while (first < terms && second < source.terms) {
 		switch (compare(termArray[first].exp, source.termArray[second].exp)) {
 			case '=':
				newCoef = termArray[first].coef - source.termArray[second].coef;
				if (newCoef != 0) c.CreateTerm(newCoef, termArray[first].exp);
				first++; second++; break;
			case '>':
				c.CreateTerm(termArray[first].coef, termArray[first].exp);
				first++; break;
			case '<':
				c.CreateTerm((-1)*source.termArray[second].coef, source.termArray[second].exp);
				second++;
 		}
 	}
	for (; first < terms; first++)
		c.CreateTerm(termArray[first].coef, termArray[second].exp);
	for (; second < source.terms; second++)
		c.CreateTerm(source.termArray[second].coef, source.termArray[second].exp);

	return c;
}

// Product of *this and source polynomials
Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;
	
	for (int i = 0; i < terms; i++) {
		Polynomial temp;
		for (int j = 0; j < source.terms; j++) {
			temp.CreateTerm(termArray[i].coef * source.termArray[j].coef, termArray[i].exp + source.termArray[j].exp);
		}
		c = c + temp;
	}
	
	return c;	
}

// Return true if left polynomial is identical to right polynomial
bool Polynomial::operator == (const Polynomial& right)
{
	bool ret;

	ret = true;
	if (terms != right.terms) ret = false;
	else {
		for (int i = 0; i < terms; i++) {
			if (termArray[i].coef != right.termArray[i].coef || termArray[i].exp != termArray[i].exp) {
				ret = false;
				break;
			}
		}
	}

	return ret;
}

// Evaluate polynomial *this at x and return the result
float Polynomial::Eval(float x)
{
	float ret = 0;
	
	for (int i = 0; i < terms; i++) {
		ret += termArray[i].coef * power(x, termArray[i].exp);
	}

	return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;
	
	// ToDo
	for (int i = 0; i < terms; i++) {
		if (termArray[i].exp == 0) break;
		c.CreateTerm(termArray[i].coef * termArray[i].exp, termArray[i].exp - 1);
	}
	
	return c;	

}

// Create a new term. If the term exists, overwrite its coefficient.
void Polynomial::CreateTerm(const float coef, const int exp)
{
	// ToDo
	if (terms == capacity) {				// checking capacity
		capacity *= 2;                      // Array Doubling
		Term* tempTermArray = new Term[capacity];
		for (int j = 0; j < terms; j++) {
			tempTermArray[j].coef = termArray[j].coef;
			tempTermArray[j].exp = termArray[j].exp;
		}
		delete[] termArray;
		termArray = tempTermArray;
	}

	for (int i = 0; i <= terms; i++) {
		if (termArray[i].exp == exp) {				// checking overlap
			if (coef == 0) {						// If coef = 0, delete term
				terms--;
				for (int j = i; j < terms; j++) {
					termArray[j].coef = termArray[j + 1].coef;
					termArray[j].exp = termArray[j + 1].exp;
				}
				return;
			}
			termArray[i].coef = coef;
			if (exp == 0) terms++;
			return;
		}
		else if (exp > termArray[i].exp || i == terms) {			// add terms
			if (coef == 0) return;									// If coef = 0, Not creating term
			
			for (int j = terms; j > i; j--) {		// pushing terms smaller than input term
				termArray[j].coef = termArray[j - 1].coef;
				termArray[j].exp = termArray[j - 1].exp;
			}

			termArray[i].coef = coef;				// term insertion
			termArray[i].exp = exp;
			terms++;
			return;
		}
	}
}

char compare(int a, int b) {
	if (a == b) return '=';
	else if (a > b) return '>';
	else return '<';
}

float power(float x, int n) {
	float ret = 1;
	for (int i = 0; i < n; i++) ret *= x;
	return ret;
}

// --- --- --- --- --- --- --- --- 
// Main
// --- --- --- --- --- --- --- --- 

int main()
{
	Polynomial f, g;
	
	f.CreateTerm(-4, 3);
	f.CreateTerm(2.3, 2);
	f.CreateTerm(-3, 0);
	
	std::cout << "f = ";
	f.Print();
	
	g.CreateTerm(3, 4);
	g.CreateTerm(-8, 0);
	g.CreateTerm(-4, 3);
	
	std::cout << "g = ";
	g.Print();
	
	g.CreateTerm(5, 2);
	std::cout << "g (creating a new term) = ";
	g.Print();
	
	// copy constructor test
	std::cout << "h (created from f) = ";
	Polynomial h = f;
	h.Print();
	
	// assignment operator test
	std::cout << "h (assigned from g) = ";
	h = g;	
	h.Print();
	
	// Add test
	std::cout << "f + g = ";
	h = f + g;	
	h.Print();
	
	// Subtract test
	std::cout << "f - g = ";
	h = f - g;
	h.Print();
	
	// Equal test
	if(f == g)
		std::cout << "f and g are same" << std::endl;
	else
		std::cout << "f and g are different" << std::endl;
	
	// Eval test
	std::cout << "f(3.5) is " << f.Eval(3.5) << std::endl;
		
	// Derivative test
	Polynomial i = f.Derivative(); 
	std::cout << "Derivative of f = ";
	i.Print();
	
	return 0;
}