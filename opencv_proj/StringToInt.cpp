#include<iostream>

using namespace std;


int main(int argc , char** argv){

	cout << "main()...." << endl;


	cout << "argc : " << argc << endl;
	cout << "argv[0]" << argv[0] << endl;
	cout << "argv[1]" << argv[1] << endl;
	cout << "argv[2]" << argv[2] << endl;
	
	int h = stoi(argv[1]);
	int s = stoi(argv[2]);

	cout << " int argv[1] : " <<  h << endl;
	cout << " int argv[2] : " <<  s << endl;

	cout << "argv[2] + argv[1] : " << h+s << endl;
}
