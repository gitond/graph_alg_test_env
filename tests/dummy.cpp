#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
/*
std::string exec(const char* cmd){
	std::array<char, 128> buffer;
	std::string result;

	/*auto command autoassigns vartype.
	popen executes a system command inside a c++ program (this case whatever we test)
	the "r" option given to popen sets it into read-only mode*/
/*	auto pipe = popen(cmd, "r");

	if (!pipe) throw std::runtime_error("popen() failed!");

	while(!feof(pipe)){
		if(fgets(buffer.data(), 128, pipe) != nullptr)
			result += buffer.data();
	}

	auto rc = pclose(pipe);

	if (rc != EXIT_SUCCESS) throw std::runtime_error("pclose() had problem with closing pipe");

	return result;
}*/

// This test currently does nothing (and always succeeds), but commented here is a test that checks whether executable output begins with the char 'g'
// NOTE! Since currently (version:0.1.0.1, lastCommitID:6f17564) the testable build (tb) is set to wait for input and this test is set to wait for output just uncommenting this test doesn't work, modifications to main.cpp are needed
int main(){
/*	try{
		if(exec("./tb").at(0) != 'g'){
			std::cout << "Dummytest unsuccessful \n";
			return 1;
		}
	}catch (const std::runtime_error& e){
		std::cout << e.what() << "\n";
		return 1;
	}
*/	std::cout << "Dummytest successful \n";
	return 0;
}
