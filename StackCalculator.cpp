#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>

// --- --- --- --- --- --- --- --- 
// Define the stack class
// --- --- --- --- --- --- --- --- 

template<class type>
class Stack
{
public:
	// Default constructor 
	Stack(){
		capacity = 10;
		top = -1;
		array = new type[capacity];
	};

	// Destructor
	~Stack(){
        top = -1;
	    delete[] array;
    };

	// Return top element of stack
	type& Top(){
        if (top < 0) throw "Error: Stack is empty";
	    else return array[top];
    };
	
	void Push(const type& item){
        if (top + 1 == capacity) {
		    capacity *= 2;
		    type* tempArray = new type[capacity];
		    for (int i = 0; i < capacity; i++) {
			    tempArray[i] = array[i];
		    }
		    delete[] array;
		    array = tempArray;
	    }
	    array[++top] = item;
    };
	
	void Pop(){
        if (top < 0) throw "Error: Stack is empty";
	    else top--;
    };
	
	bool IsEmpty() const {
        if (top < 0) return true;
	    else return false;
    };

	void Print() {
		for(int i=0; i<=top; i++) std::cout << array[i] << std::endl;
	};
	
	int Size() { return top+1; }
	
private:
	// Data
	type *array;
	int capacity;
	int top;
};

// --- --- --- --- --- --- --- --- 
// functions for calulation
// --- --- --- --- --- --- --- --- 

Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators

bool isNum(char c) {
	if (c == '0' || c == '1' ||
		c == '2' || c == '3' ||
		c == '4' || c == '5' ||
		c == '6' || c == '7' ||
		c == '8' || c == '9') return true;
	else return false;
}

int priority(char c) {
	switch (c) {
	case '_':
		return 3;
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

double calc(double a, double b, char op) {
	switch (op) {
	case '-':
		return a - b;
	case '+':
		return a + b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
}

//
// Modify Eval() below to evaluate the given expression
//
double Eval(char* in)
{
	double out = 0;
	
	char buf[1000]; // temp buffer
	char lastToken = '#';
	
	double operand;
	int i = 0, bi = 0;
	
	opt.Push('#');
	
	while(in[i] != '\0')
	{		
		char c = in[i];
		
		// Operators
		if(c == '+' || c == '-' ||
		   c == '*' || c == '/' ||
		   c == '(' || c == ')')
		{
			if(bi > 0)
			{
				buf[bi++] = '\0';
				operand = atof(buf);
				bi = 0;
				
				// push operand
				std::cout << "New operand : " << operand << std::endl;
				opr.Push(operand);
			}

			// distinguish whether '-' is binary or unary
			std::cout << "New operator : " << c << std::endl;
			if (c == '-' && i == 0) c = '_';
			if (c == '-') {
				int temp = i - 1;
				while (in[temp] == ' ') temp--;
				if (!isNum(in[temp]) && in[temp] != ')') c = '_';
			}

			// push operator
			if (c == '(') {
				opt.Push(c);
			}// left parenthesis
			else if (c == ')') {						// right parenthesis
				while (opt.Top() != '(') {
					if (opt.Top() == '_') {
						double n = opr.Top(); opr.Pop();
						n *= -1; opt.Pop();
						opr.Push(n);
					}
					else {
						double n1 = opr.Top(); opr.Pop();
						double n2 = opr.Top(); opr.Pop();
						char oldOpt = opt.Top(); opt.Pop();
						opr.Push(calc(n2, n1, oldOpt));
					}
				}
				opt.Pop();
			}
			else if (priority(c) <= priority(opt.Top())) {			// check priority
				while (priority(c) <= priority(opt.Top())) {
					if (opt.Top() == '_') {
						double n = opr.Top(); opr.Pop();
						n *= -1; opt.Pop();
						opr.Push(n);
					}
					else {
						double n1 = opr.Top(); opr.Pop();
						double n2 = opr.Top(); opr.Pop();
						char oldOpt = opt.Top(); opt.Pop();
						opr.Push(calc(n2, n1, oldOpt));
					}
				}
				opt.Push(c);
			}
			else {								// the other
				opt.Push(c);
			}
		}

		// Operands
		else if(isNum(c) || c == '.') {
			buf[bi++] = c;
		}
		else {}
		
		i++;
	}
	
	// push the very last operand if exists
	if(bi > 0)
	{
		buf[bi++] = '\0';
		operand = atof(buf);
		bi = 0;
		
		// push operand
		std::cout << "New operand : " << operand << std::endl;
		opr.Push(operand);
	}

	while (opt.Top() != '#') {
		if (opt.Top() == '_') {
			double n = opr.Top(); opr.Pop();
			n *= -1; opt.Pop();
			opr.Push(n);
		}
		else {
			double n1 = opr.Top(); opr.Pop();
			double n2 = opr.Top(); opr.Pop();
			char oldOpt = opt.Top(); opt.Pop();
			opr.Push(calc(n2, n1, oldOpt));
		}
	}
	
	out = opr.Top(); opr.Pop(); opt.Pop();

	return out;	
}

// --- --- --- --- --- --- --- --- 
// Main
// --- --- --- --- --- --- --- --- 

int main()
{
	// Stack test
	Stack<int> s;
	
	s.Push(23);
	s.Push(102);
	s.Print();
	printf("--\n");
	
	s.Push(345);
	s.Push(77);
	s.Print();
	printf("--\n");
	
	s.Pop();
	s.Push(678);
	s.Push(91011);
	s.Print();
	printf("--\n");
	
	for(int i=0; i<6; i++)
	{
		try {
			s.Pop();
			std::cout << "Pop() is called" << std::endl;
		}
		catch(const char* message)
		{
			std::cout << message << std::endl;
		}		
	}

	// Calculator test
	char str1[] ="-10-((-2+(2+4*3))-12) + 122 * (123 + (120+888) - 300)";
	// The correct result is 101372
	double res1 = Eval(str1);
	std::cout << "Result : " << res1 << std::endl;
	
	
	char str2[] = "1.2 + 2.4 + 3.0*2";
	// The correct result is 9.6
	double res2 = Eval(str2);
	std::cout << "Result : " << res2 << std::endl;
		
	return 0;
}



