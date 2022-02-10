#include "LinkedBinaryTree.h"
#include "SearchTree.h" 
#include "AVLTree.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include <iostream>

using namespace std;

int main()
{
	typedef Entry<int, float> EntryType;

	// Size = 100

	int nElem = 100; //100000000;
	
	int *key = new int[nElem];
	float *val = new float[nElem];
	
	std::srand(std::time(0)); // use current time as seed for random generator
	
	std::cout << "----- Size = 100 -----" << std::endl;

	// Random orders test
	std::cout << "< Random orders test >" << std::endl;

	// initialize
	for (int i = 0; i < nElem; i++)
	{
		key[i] = std::rand();
		val[i] = (float)std::rand() / RAND_MAX * 20000;
	}

	// ST test
	SearchTree<EntryType>	RandomST;

	// ST Insert test
	clock_t TMforRandomST;
	TMforRandomST = clock();
	for (int i = 0; i < nElem; i++)
		RandomST.insert(key[i], val[i]);
	TMforRandomST = clock() - TMforRandomST;
	printf("ST Insert test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomST) / (float)CLOCKS_PER_SEC);

	// ST Find test
	TMforRandomST = clock();
	for (int i = nElem; i < nElem * 2; i++)
		RandomST.find(key[i]);
	TMforRandomST = clock() - TMforRandomST;
	printf("ST Find test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomST) / (float)CLOCKS_PER_SEC);

	// AVL test
	AVLTree<EntryType>	RandomAVL;

	// AVL Insert test
	clock_t TMforRandomAVL;
	TMforRandomAVL = clock();
	for (int i = 0; i < nElem; i++)
		RandomAVL.insert(key[i], val[i]);
	TMforRandomAVL = clock() - TMforRandomAVL;
	printf("AVL Insert test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomAVL) / (float)CLOCKS_PER_SEC);

	// AVL Find test
	TMforRandomAVL = clock();
	for (int i = 0; i < nElem; i++)
		RandomAVL.find(key[i]);
	TMforRandomAVL = clock() - TMforRandomAVL;
	printf("AVL Find test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomAVL) / (float)CLOCKS_PER_SEC);


	// Skewed orders test
	std::cout << std::endl << "< Skewed orders test >" << std::endl;
	
	// initialize
	std::sort(key, key + nElem);
	std::sort(val, val + nElem);

	// ST test
	SearchTree<EntryType>	SkewedST;

	// ST Insert test
	clock_t TMforSkewedST;
	TMforSkewedST = clock();
	for (int i = 0; i < nElem; i++)
		SkewedST.insert(key[i], val[i]);
	TMforSkewedST = clock() - TMforSkewedST;
	printf("ST Insert test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedST) / (float)CLOCKS_PER_SEC);

	// ST Find test
	TMforSkewedST = clock();
	for (int i = 0; i < nElem; i++)
		SkewedST.find(key[i]);
	TMforSkewedST = clock() - TMforSkewedST;
	printf("ST Find test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedST) / (float)CLOCKS_PER_SEC);

	// AVL test
	AVLTree<EntryType>	SkewedAVL;

	// AVL Insert test
	clock_t TMforSkewedAVL;
	TMforSkewedAVL = clock();
	for (int i = 0; i < nElem; i++)
		SkewedAVL.insert(key[i], val[i]);
	TMforSkewedAVL = clock() - TMforSkewedAVL;
	printf("AVL Insert test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedAVL) / (float)CLOCKS_PER_SEC);

	// AVL Find test
	TMforSkewedAVL = clock();
	for (int i = 0; i < nElem; i++)
		SkewedAVL.find(key[i]);
	TMforSkewedAVL = clock() - TMforSkewedAVL;
	printf("AVL Find test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedAVL) / (float)CLOCKS_PER_SEC);
	
	delete[] key;
	delete[] val;

	// Size = 1000

	nElem = 1000; //100000000;

	key = new int[nElem];
	val = new float[nElem];

	std::cout << std::endl << "----- Size = 1000 -----" << std::endl;

	// Random orders test
	std::cout << "< Random orders test >" << std::endl;

	// initialize
	for (int i = 0; i < nElem; i++)
	{
		key[i] = std::rand();
		val[i] = (float)std::rand() / RAND_MAX * 20000;
	}

	// ST test
	SearchTree<EntryType>	RandomST2;

	// ST Insert test
	TMforRandomST = clock();
	for (int i = 0; i < nElem; i++)
		RandomST2.insert(key[i], val[i]);
	TMforRandomST = clock() - TMforRandomST;
	printf("ST Insert test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomST) / (float)CLOCKS_PER_SEC);

	// ST Find test
	for (int i = nElem; i < nElem * 2; i++)
		RandomST2.find(key[i]);
	TMforRandomST = clock() - TMforRandomST;
	printf("ST Find test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomST) / (float)CLOCKS_PER_SEC);

	// AVL test
	AVLTree<EntryType>	RandomAVL2;

	// AVL Insert test
	TMforRandomAVL = clock();
	for (int i = 0; i < nElem; i++)
		RandomAVL2.insert(key[i], val[i]);
	TMforRandomAVL = clock() - TMforRandomAVL;
	printf("AVL Insert test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomAVL) / (float)CLOCKS_PER_SEC);

	// AVL Find test
	TMforRandomAVL = clock();
	for (int i = 0; i < nElem; i++)
		RandomAVL2.find(key[i]);
	TMforRandomAVL = clock() - TMforRandomAVL;
	printf("AVL Find test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomAVL) / (float)CLOCKS_PER_SEC);


	// Skewed orders test
	std::cout << std::endl << "< Skewed orders test >" << std::endl;

	// initialize
	std::sort(key, key + nElem);
	std::sort(val, val + nElem);

	// ST test
	SearchTree<EntryType>	SkewedST2;

	// ST Insert test
	TMforSkewedST = clock();
	for (int i = 0; i < nElem; i++)
		SkewedST2.insert(key[i], val[i]);
	TMforSkewedST = clock() - TMforSkewedST;
	printf("ST Insert test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedST) / (float)CLOCKS_PER_SEC);

	// ST Find test
	TMforSkewedST = clock();
	for (int i = 0; i < nElem; i++)
		SkewedST2.find(key[i]);
	TMforSkewedST = clock() - TMforSkewedST;
	printf("ST Find test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedST) / (float)CLOCKS_PER_SEC);

	// AVL test
	AVLTree<EntryType>	SkewedAVL2;

	// AVL Insert test
	TMforSkewedAVL = clock();
	for (int i = 0; i < nElem; i++)
		SkewedAVL2.insert(key[i], val[i]);
	TMforSkewedAVL = clock() - TMforSkewedAVL;
	printf("AVL Insert test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedAVL) / (float)CLOCKS_PER_SEC);

	// AVL Find test
	TMforSkewedAVL = clock();
	for (int i = 0; i < nElem; i++)
		SkewedAVL2.find(key[i]);
	TMforSkewedAVL = clock() - TMforSkewedAVL;
	printf("AVL Find test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedAVL) / (float)CLOCKS_PER_SEC);

	delete[] key;
	delete[] val;

	// Size = 10000

	nElem = 10000; //100000000;

	key = new int[nElem];
	val = new float[nElem];

	std::cout << std::endl << "----- Size = 10000 -----" << std::endl;

	// Random orders test
	std::cout << "< Random orders test >" << std::endl;

	// initialize
	for (int i = 0; i < nElem; i++)
	{
		key[i] = std::rand();
		val[i] = (float)std::rand() / RAND_MAX * 20000;
	}

	// ST test
	SearchTree<EntryType>	RandomST3;

	// ST Insert test
	TMforRandomST = clock();
	for (int i = 0; i < nElem; i++)
		RandomST3.insert(key[i], val[i]);
	TMforRandomST = clock() - TMforRandomST;
	printf("ST Insert test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomST) / (float)CLOCKS_PER_SEC);

	// ST Find test
	for (int i = nElem; i < nElem * 2; i++)
		RandomST3.find(key[i]);
	TMforRandomST = clock() - TMforRandomST;
	printf("ST Find test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomST) / (float)CLOCKS_PER_SEC);

	// AVL test
	AVLTree<EntryType>	RandomAVL3;

	// AVL Insert test
	TMforRandomAVL = clock();
	for (int i = 0; i < nElem; i++)
		RandomAVL3.insert(key[i], val[i]);
	TMforRandomAVL = clock() - TMforRandomAVL;
	printf("AVL Insert test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomAVL) / (float)CLOCKS_PER_SEC);

	// AVL Find test
	TMforRandomAVL = clock();
	for (int i = 0; i < nElem; i++)
		RandomAVL3.find(key[i]);
	TMforRandomAVL = clock() - TMforRandomAVL;
	printf("AVL Find test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomAVL) / (float)CLOCKS_PER_SEC);


	// Skewed orders test
	std::cout << std::endl << "< Skewed orders test >" << std::endl;

	// initialize
	std::sort(key, key + nElem);
	std::sort(val, val + nElem);

	// ST test
	SearchTree<EntryType>	SkewedST3;

	// ST Insert test
	TMforSkewedST = clock();
	for (int i = 0; i < nElem; i++)
		SkewedST3.insert(key[i], val[i]);
	TMforSkewedST = clock() - TMforSkewedST;
	printf("ST Insert test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedST) / (float)CLOCKS_PER_SEC);

	// ST Find test
	TMforSkewedST = clock();
	for (int i = 0; i < nElem; i++)
		SkewedST3.find(key[i]);
	TMforSkewedST = clock() - TMforSkewedST;
	printf("ST Find test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedST) / (float)CLOCKS_PER_SEC);

	// AVL test
	AVLTree<EntryType>	SkewedAVL3;

	// AVL Insert test
	TMforSkewedAVL = clock();
	for (int i = 0; i < nElem; i++)
		SkewedAVL3.insert(key[i], val[i]);
	TMforSkewedAVL = clock() - TMforSkewedAVL;
	printf("AVL Insert test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedAVL) / (float)CLOCKS_PER_SEC);

	// AVL Find test
	TMforSkewedAVL = clock();
	for (int i = 0; i < nElem; i++)
		SkewedAVL3.find(key[i]);
	TMforSkewedAVL = clock() - TMforSkewedAVL;
	printf("AVL Find test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedAVL) / (float)CLOCKS_PER_SEC);

	delete[] key;
	delete[] val;

	// Size = 100000

	nElem = 100000; //100000000;

	key = new int[nElem];
	val = new float[nElem];

	std::cout << std::endl << "----- Size = 100000 -----" << std::endl;

	// Random orders test
	std::cout << "< Random orders test >" << std::endl;

	// initialize
	for (int i = 0; i < nElem; i++)
	{
		key[i] = std::rand();
		val[i] = (float)std::rand() / RAND_MAX * 20000;
	}

	// ST test
	SearchTree<EntryType>	RandomST4;

	// ST Insert test
	TMforRandomST = clock();
	for (int i = 0; i < nElem; i++)
		RandomST4.insert(key[i], val[i]);
	TMforRandomST = clock() - TMforRandomST;
	printf("ST Insert test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomST) / (float)CLOCKS_PER_SEC);

	// ST Find test
	for (int i = nElem; i < nElem * 2; i++)
		RandomST4.find(key[i]);
	TMforRandomST = clock() - TMforRandomST;
	printf("ST Find test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomST) / (float)CLOCKS_PER_SEC);

	// AVL test
	AVLTree<EntryType>	RandomAVL4;

	// AVL Insert test
	TMforRandomAVL = clock();
	for (int i = 0; i < nElem; i++)
		RandomAVL4.insert(key[i], val[i]);
	TMforRandomAVL = clock() - TMforRandomAVL;
	printf("AVL Insert test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomAVL) / (float)CLOCKS_PER_SEC);

	// AVL Find test
	TMforRandomAVL = clock();
	for (int i = 0; i < nElem; i++)
		RandomAVL4.find(key[i]);
	TMforRandomAVL = clock() - TMforRandomAVL;
	printf("AVL Find test for random orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforRandomAVL) / (float)CLOCKS_PER_SEC);


	// Skewed orders test
	std::cout << std::endl << "< Skewed orders test >" << std::endl;

	// initialize
	std::sort(key, key + nElem);
	std::sort(val, val + nElem);

	// ST test
	SearchTree<EntryType>	SkewedST4;

	// ST Insert test
	TMforSkewedST = clock();
	for (int i = 0; i < nElem; i++)
		SkewedST4.insert(key[i], val[i]);
	TMforSkewedST = clock() - TMforSkewedST;
	printf("ST Insert test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedST) / (float)CLOCKS_PER_SEC);

	// ST Find test
	TMforSkewedST = clock();
	for (int i = 0; i < nElem; i++)
		SkewedST4.find(key[i]);
	TMforSkewedST = clock() - TMforSkewedST;
	printf("ST Find test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedST) / (float)CLOCKS_PER_SEC);

	// AVL test
	AVLTree<EntryType>	SkewedAVL4;

	// AVL Insert test
	TMforSkewedAVL = clock();
	for (int i = 0; i < nElem; i++)
		SkewedAVL4.insert(key[i], val[i]);
	TMforSkewedAVL = clock() - TMforSkewedAVL;
	printf("AVL Insert test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedAVL) / (float)CLOCKS_PER_SEC);

	// AVL Find test
	TMforSkewedAVL = clock();
	for (int i = 0; i < nElem; i++)
		SkewedAVL4.find(key[i]);
	TMforSkewedAVL = clock() - TMforSkewedAVL;
	printf("AVL Find test for skewed orders : \n");
	printf("It took me %f seconds.\n", ((float)TMforSkewedAVL) / (float)CLOCKS_PER_SEC);

	delete[] key;
	delete[] val;

	return 0;
}