#include <iostream>
#include <fstream>
#include <algorithm>

// --- --- --- --- --- --- --- --- 
// Hash Map Data Structure
// --- --- --- --- --- --- --- --- 

// Map element
template <class KeyType, class ValType>
class MapElem
{
public:
	typedef KeyType ktype;
	typedef ValType vtype;
	
	KeyType key;
	ValType val;
	
	MapElem* link = NULL;
};

bool inline operator==(std::string a, std::string b)
{
	if((a).compare(b) == 0) return true;
	return false;
}

//
// Hash Map data structure
//
template <class HashMapElemType> 
class HashMap
{
public:
	typedef typename HashMapElemType::ktype KeyType;
	typedef typename HashMapElemType::vtype ValType;
	
	// constructor
	HashMap(unsigned int c = 1000){
        mapsize = 0;
	    capacity = c;

	    bool* isPrime = new bool[capacity + 1];
	    for (int i = 0; i <= capacity; i++) isPrime[i] = true;
	    isPrime[0] = false; isPrime[1] = false;
	    for (unsigned int i = 2; i * i <= capacity; i++) {
		    if (isPrime[i]) {
			    for (unsigned int j = i * 2; j <= capacity; j += i) {
				    isPrime[j] = false;
			    }
		    }
	    }

	    unsigned int biggestPrime;
	    for (unsigned int i = capacity; i > 0; i--) {
		    if (isPrime[i]) {
			    biggestPrime = i; break;
		    }
	    }

	    divisor = biggestPrime;

	    ht = new HashMapElemType * [capacity];
	    for (int i = 0; i < capacity; i++) {
		    ht[i] = NULL;
	    }
    };
	
	// destructor
	~HashMap(){
        for (unsigned int i = 0; i < capacity; i++) {
		    HashMapElemType* currptr = *(ht + i);
		    HashMapElemType* nextptr = NULL;
		    while (currptr != NULL) {
			    nextptr = currptr->link;
			    delete currptr;
			    currptr = nextptr;
		    }
	    }
	    delete[] ht;
    };
	
	// Modify below functions
	int size() { return mapsize; };
	
	bool isEmpty() { return (mapsize == 0); };
	
	// ToDo
	HashMapElemType* find(const KeyType k){
        unsigned int hashval = hashfunction(k);
	    HashMapElemType* currptr = *(ht + hashval);
	    while (currptr != NULL) {
		    if (currptr->key == k) {
			    return currptr;
		    }
		    currptr = currptr->link;
	    }
	    return NULL;
    };
	
	void insert(const KeyType k, const ValType v){
        unsigned int hv = hashfunction(k);
	    HashMapElemType* currptr = *(ht + hv);
	    HashMapElemType* preptr = NULL;
	    while (currptr != NULL) {
		    if (currptr->key != k) {
			    preptr = currptr;
			    currptr = currptr->link;
		    }
		    else {
    			currptr->val = v;
    			mapsize++;
    			return;
		}
    	}

	    HashMapElemType* newElem = new HashMapElemType;
	    newElem->key = k;
	    newElem->val = v;
	    newElem->link = NULL;
	    if (preptr == NULL) *(ht + hv) = newElem;
	    else preptr->link = newElem;

	    mapsize++;
	    return;
    };
		
	bool remove(const KeyType k){
        unsigned int hashval = hashfunction(k);
	    HashMapElemType* currptr = *(ht + hashval);
	    HashMapElemType* preptr = NULL;
	    while (currptr != NULL) {
		    if (currptr->key == k) {
			    if (preptr == NULL) *(ht + hashval) = currptr->link;
			    else preptr->link = currptr->link;
			    delete currptr;
			    mapsize--;
			    return true;
		    }
		    preptr = currptr;
		    currptr = currptr->link;
	    }
	    mapsize--;
	    return false;
    };
	
	unsigned int hashfunction(const KeyType k){
        unsigned int ret = 0;
	    const int a = 33;

	    for (int i = 0; i < k.length(); i++) {
		    ret += ret * a + k[i];
		    ret %= divisor;
	    }

	    return ret;
    };
	
	void print(){
        for (unsigned int i = 0; i < capacity; i++) {
		    HashMapElemType* currptr = *(ht + i);
		    while (currptr != NULL) {
			    std::cout << currptr->key << ":" << currptr->val << std::endl;
			    currptr = currptr->link;
		    }
	    }
    };
	
private:
	// Hash Table
	HashMapElemType** ht;
	
	unsigned int mapsize, capacity, divisor;
};

// --- --- --- --- --- --- --- --- 
// Main
// --- --- --- --- --- --- --- --- 

HashMap<MapElem<std::string, unsigned int> > hm;

void spellcheck(std::string s)
{
	std::cout << "> " << s;
	// ToDo
	if (hm.find(s) != NULL) std::cout << " is in the dictionary" << std::endl;
	else {
		std::cout << " is NOT in the dictionary" << std::endl;
		std::string* suggestions = new std::string; 
		int suggNum = 0; bool check = false;
		for (int i = 0; i < s.length(); i++) {
			std::string temp = s;
			for (char c = 'a'; c <= 'z'; c++) {
				temp[i] = c;
				if (hm.find(temp) != NULL) {
					if (!check) {
						check = true;
						std::cout << "> " << s << " : ";
					}
					else {
						std::cout << ", ";
					}
					std::cout << temp;
				}
			}
		}
		if (!check) std::cout << "> " << s << " : no suggestion" << std::endl;
		else std::cout << std::endl;
	}
	return;
}

int main()
{
	// load dictionary
	char filename[] = "dictionary.txt";
	std::ifstream ifs(filename, std::ifstream::in);
	std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	std::transform(s.begin(), s.end(),
				   s.begin(), ::tolower);

	std::string token;	
	unsigned int len = s.length();

	for(int i=0; i<len; i++)
	{
		int ascii = s[i];
		
		if(ascii < 97 || ascii > 127) 
		{
			if(token.length() > 0) 
			{
				// ToDo
				// Insert token to hash map
				hm.insert(token, 1);

				token.clear();
			}
			continue;
		}
		token.push_back(s[i]);
	}

	//
	// infinite loop to accept user input word
	//

	while(1)
	{
		std::string s;
		std::cout << "> ";
		std::cin >> s;
		
		if(s.compare("q") == 0) break;	
		
		spellcheck( s );
	}
	
	
	return 0;
}