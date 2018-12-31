#include <iostream>
#include <cstdint>
#include <fstream>
#include <algorithm> 
#include   <string>
#include   <string.h>
/*Author: Ali Hassaan Mughal*/
/* I am in this program finding the p and the q variables,  -- 
these  variables form e and f and d and then give me the key value pair for public and the private keys*/
int64_t getD(int64_t variable1s,int64_t variables2s);
bool isPrime(int64_t inputnumbervariable);
void encrypt(const char* __stringone, const char* __stringtwo, int64_t __n, int64_t __e);
void decrypt(const char* __firststring, const char* __second string, int64_t __n, int64_t __d);
using  namespace  std;
int  main(int  argc, char**  argv) // This is the mainly executional function
	{
	int64_t p=0,q=0,e=0,f=0,d=0,n=0;
	if (strcmp(argv[1],"-k") == 0)
	{
	while (!isPrime(p))
	p = (rand())+4096;
	
	while(!isPrime(q))
	q = (rand()%65534)+2;
	
	cout << "P is " << p << " q is " << q;
	
	n  = (p*1) * (q*1);
	
	f = (p-1)*1 * (q-1)*1;
	
	while (__gcd(e , f) != 1)
	e = (rand()%61440) +4096;
	
	cout << " e is" << e << " f is " << f << endl;
	
	d = getD(e,f);
	
	cout << "d is " << d << endl;
	//Public Key Pair
	cout << "The Public Key Pair is (n,e) " << n << " " << e << endl;
	cout << "The Private Key Pair is (n,d) " << n << " " << d << endl;
	}
	//
	else if (strcmp(argv[1],"-e") == 0)
	{
		int64_t n = atoi(argv[2]);
		int64_t e = atoi(argv[3]);
		const char* input = argv[4];
		const char* output = argv[5];
		encrypt(input, output, n,e);
	}
	else if (strcmp(argv[1],"-d") == 0)
	{
		int64_t n = atoi(argv[2]);
		int64_t d = atoi(argv[3]);
		const char* input = argv[4];
		const char* output = argv[5];
		decrypt(input, output, n,d);
	}	
	return 0;
}

bool isPrime(int64_t __numone)
{
	if (__numone ==0 || __numone == 1)
		return 0;
	for (int i=2; i < __numone; i++)
	{
		if (__numone % i == 0){
			return  0; //return false is there is an other factor of the number and hence the number is non __prime
		}
	}
	return true; //return this is the number is __prime
}
// This function returns the modular exponenetatiation of the numbers
int64_t modExp(int64_t basenumber, int64_t expnumber, int64_t mnumber)
{
	int64_t __answervariable = 1;
	for (int iii=0;iii<expnumber;iii++)
	{
		__answervariable *= basenumber;
		__answervariable = __answervariable % mnumber;
	}
	return __answervariable;
}
void keyGen(void){
	
}

void encrypt(const char* inFileName,const char *outFileName, int64_t n, int64_t e)
{
  ifstream input(inFileName,std::ios::out   |   std::ios::binary);     // opening-the-input-file-to-read
  ofstream output(outFileName,std::ios::out   |   std::ios::binary);  //output-part-of-file-to-be-written-to
  int64_t inputlength = 0;
  char c; int charcount = 0;
  int64_t m=0,M=0;
  cout << "The Input File Data" << endl;
  while (input.get(c)){
	   cout << c;
	if (charcount % 3 == 0)
	{
		if (charcount!= 0){
		//cout << m << endl;
			M = modExp(m,e,n);
			output << M << " " << endl;
		}
		m = 0;
		m += c;
	}
	if (charcount % 3 == 1)
	{
		m += 256*c;
	}
	if (charcount % 3 == 2)
	{
		m += 65536*c;
	}
	charcount++;
  }
  if (charcount!= 0){
		//cout << m << endl;
			M = modExp(m,e,n);
			output << M << " " << endl;
		}
  input.close();		 
}
void decrypt(const char *inFileName,const char *outFileName, int64_t n, int64_t d)
{
	ifstream input(inFileName,std::ios::out   |   std::ios::binary);     // opening-the-input-file-to-read
  	ofstream output(outFileName,std::ios::out   |   std::ios::binary);   //output-part-of-file-to-be-written-to
  	int64_t m=0,M=0;
  	string mtemp  = " ";
  	cout << endl << "The Decrypted File Data " << endl;
  	char c; int charcount = 0;
  	while (input.get(c)){
	   if (c == ' ')
	   {
	   	M = atoi(mtemp.c_str());
	   	m = modExp(M,d,n);
	   	//cout << m << endl;
	   	char t1 = 0,t2=0,t3=0;
	   	if (m > 256)
	   	t2 = m / 256;
	   	if (m > 65536)
	   	t3 = m / 65536;
	   	t1 = (m-t1*65536-t2*256);
	   	cout << t1 << t2 << t3;
	   	output << t1 << t2 << t3;
	   	mtemp="";
	   	continue;
	   }
	   mtemp+=c;
	charcount++;
  	}
  	
}
//Returning-the-power-of-a-number-calculated-through-a-for-loop
int64_t power(int64_t basenumber  ,  int __powernumber){
	int __answervariable = 1;
	for (int ijk = 0; ijk < __powernumber; ijk++){
	__answervariable *= basenumber;
	}
	return __answervariable;
}
//This-function-is-used-to-return-the-d-number-of-the-private-key
int64_t getD(int64_t __enumber,int64_t __fnumber)
{
	__enumber = __enumber%__fnumber;
    for (int ijk=1; ijk<__fnumber; ijk++)
       if ((__enumber*ijk) % __fnumber == 1)
          return ijk;	
}
