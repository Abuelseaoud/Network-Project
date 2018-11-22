#include <iostream>
#include <fstream>
#include <ctgmath>
#include <stdlib.h>
#include <bitset>
using namespace std;

int  messageSize, polynomialSize, transmittedMessageSize;
unsigned long long int message, polynomial, reminder, receivedMessage, transmittedMessage;
string inputFilePath= "message_generator.txt";
string outputFilePath="transmitted_message.txt";
/*
 generator function description: it simulates the sending process   
 
 1- reads message and polynomial from input file .
 2- divides the message concatenated with number of zeros equal to the order of polynomial by polynomial . 
 3- concatenates message with reminder then write it in the output file .
*/
void generator() 
{
	string S;
	char *End;
	ifstream infile(inputFilePath);
	if (infile.eof())return;
	getline(infile, S);
	messageSize = S.length();
	message = strtoull(S.data(), &End, 2);
	getline(infile, S);
	polynomialSize = S.length();
	polynomial= strtoull(S.data(), &End, 2);
	transmittedMessage = message << (polynomialSize - 1);
	transmittedMessageSize = messageSize + polynomialSize - 1;
	reminder = transmittedMessage >> (transmittedMessageSize - polynomialSize);
	int flag = ((reminder >> (polynomialSize - 1)) & 1) ? 1 : 0;
	for(int i=polynomialSize;i<transmittedMessageSize;i++)
	{
		reminder ^=(polynomial*flag);
		reminder = ((transmittedMessage >> (transmittedMessageSize - i - 1)) & 1) | (reminder << 1);
		flag = ((reminder >> (polynomialSize - 1)) & 1) ? 1 : 0;
	}
	reminder ^= (polynomial*flag);
	transmittedMessage |= reminder;
	infile.close();
	S = bitset <sizeof(unsigned long long int) * 8>(transmittedMessage).to_string();
	S.erase(0, (sizeof(unsigned long long int) * 8) - transmittedMessageSize);
	ofstream outFile(outputFilePath);
	outFile << S;
	outFile.close();

}

int main()
{
	
}