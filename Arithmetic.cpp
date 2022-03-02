// Winston Yi
// wyi10

#include<stdio.h>
#include<fstream>
#include<iostream>
#include"BigInteger.h"


int main(int argc, char* argv[]) {
	std::ifstream in;
	std::ofstream out;
	// check command line for correct number of arguments
    if( argc != 3 ){
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return(EXIT_FAILURE);
   	}

   	// open files for reading and writing 
   	in.open(argv[1]);
   	if( !in.is_open() ){
    	  std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
      	return(EXIT_FAILURE);
  	 }

   	out.open(argv[2]);
   	if( !out.is_open() ){
    	  std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
      	return(EXIT_FAILURE);
   	}
    std::string s1;
    std::string s2;
	std::getline(in, s1, '\n');
	std::getline(in, s2); //read in twice becuase s\n \n s2\n format, need to skip delimiters \n
	std::getline(in, s2);
	BigInteger A = s1;
	BigInteger B = s2;
	out << A << std::endl << std::endl;
	out << B << std::endl << std::endl;

	BigInteger C = A+B;
	out << C << std::endl << std::endl;

	BigInteger F = A-B;
	out << F << std::endl << std::endl;

	C = A-A;
	out << C << std::endl << std::endl;

	std::string three = "3";
	std::string two = "2";
	BigInteger Scalar = three;
	C = Scalar*A;
	Scalar = two;
	BigInteger D = Scalar*B;
	BigInteger K = C-D;
	out << K << std::endl << std::endl;

	C = A*B;
	out << C << std::endl << std::endl;

	C = A*A;
	out << C << std::endl << std::endl;
    
	D = B*B;
	out << D << std::endl << std::endl;

	std::string fifteen = "16";
	std::string nine = "9";
	BigInteger Scalar2 = fifteen;
	BigInteger Scalar3 = nine;
	C = C*A*A*Scalar3;
	D = B*B*B*B*B*Scalar2;
	K = C+D;
	out << K << std::endl << std::endl;
	printf("\n");
	return 0;
}


