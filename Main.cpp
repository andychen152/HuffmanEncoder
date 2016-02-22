// Huffman Encoding Project

#include <iostream>
#include <exception>
#include <string>
#include <cstdio>
#include "Encoder.h"
#include "Node.h"

using namespace std;

int main()
{

	int defaultCharOccurences[27] = {0};
	freopen("plain.input","r",stdin);     

	try
	{
		while(true)
		{
			char ch;
			cin  >> noskipws >> ch;
			if(cin.eof())
			{
				break;
			}
			if(ch==32)
				defaultCharOccurences[26]++;
			else
				defaultCharOccurences[ch-97]++;
		}
	}
	catch(exception& ex)
	{
		cerr << ex.what() << endl;
	}

	fclose(stdin);
	cin.clear();

	Encoder e;
	e.compressArray(defaultCharOccurences);
	e.heapify();
	e.combineAll();
	e.generateCode();


//	e.print();

	freopen("plain.input","r",stdin);     
	try
	{
		while(true)
		{
			char ch;
			cin  >> noskipws >> ch;
			if(cin.eof())
			{
				break;
			}
			e.addEncode(ch);
		}
	}
	catch(exception& ex)
	{
		cerr << ex.what() << endl;
	}

	cout << e.getEncodedOutput() << endl;

	fclose(stdin);
	cin.clear();	

	e.initializeDecode();
	freopen("encoded.input","r",stdin);     
	try
	{
		while(true)
		{
			char ch;
			cin  >> noskipws >> ch;
			if(cin.eof())
			{
				break;
			}
			e.addDecode(ch);
		}
	}
	catch(exception& ex)
	{
		cerr << ex.what() << endl;
	}

	cout << e.getDecodedOutput() << endl;



	return 0;
}