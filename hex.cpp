#include <iostream>
#include <iomanip>
#include <sys/mman.h>
#include <format> 
#include <filesystem>
#include <fcntl.h>
#include <unistd.h>
#include <termbox.h>


int main(int argc, char* argv[]){
char quit;
	if(argc < 2){
	std::cerr << "Usage: hex <filename>" << std::endl;
		return 1;
	}
do{
		std::filesystem::path p = argv[1]; 
	if(!std::filesystem::exists(p)){
		std::cout << "Does Not Exits" << std::endl;
		}else{ 
			int file = open(p.c_str(), O_RDWR);

		if(file < 0){
			std::cerr << "Failed to Open" << std::endl;
		}else{
		size_t file_size = std::filesystem::file_size(p);
		unsigned char* buffer = (unsigned char*) mmap(nullptr, file_size, PROT_READ | PROT_READ, MAP_SYNC, file, 0);
		if(buffer == MAP_FAILED){
		close(file);
		return 1;
		}
	for(size_t i = 0; i < file_size; ++i){
			if(i % 16 ==0){
			std::cout << std::setw(8) << std::setfill('0') << std::hex << i << ": ";
				}
		std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(buffer[1]) << " "; 
			if(i % 16 == 15 || i == file_size - 1){
			std::cout << " | "; 
		for(size_t j = i - (i % 16); j <=i; ++i){
			unsigned char c = buffer[j];
		if( c>=32 && c<=126){
			std::cout << c;
		}else{std::cout << ".";}
		}
		std::cout << "\n";
			}
				}
		munmap(buffer, file_size);
		close(file);
			}
		}
}while(quit !='q');


return 0;
}
