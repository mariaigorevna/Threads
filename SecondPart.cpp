/// g++ SecondPart.cpp -std=c++17 -lssl -pthread -lcrypto -lstdc++fs -o laba

#include <iostream>
#include <vector>
#include <filesystem>
#include <thread>
#include <unistd.h>
#include <openssl/md5.h>
#include <fstream>

void print_MD5(std::string hashMe, std::string filePath)
{
	int i;
	MD5_CTX md5Handler;
	unsigned char md5digest[MD5_DIGEST_LENGTH];

	MD5((const unsigned char*)hashMe.c_str(), hashMe.size(), md5digest);
	
	printf("%s: ", filePath.c_str());

	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
		printf("%02x", md5digest[i]);
	}
	printf("\n");
}

int main()
{
	std::string path;
	std::string data, tempBuf;
	std::vector<std::string> vecPaths;		/* Vec with paths */
    std::vector<std::thread> vecThreads;    /* Vec with threads */

	std::cout << "Type directory path: ";
	std::cin >> path;
	for (const auto &entry : std::filesystem::directory_iterator(path)) /* Directory iteration */
	{
		vecPaths.push_back(entry.path());		/* Add all files from dir into vector */
	}

	if (vecPaths.size() == 0)		/* Show error if dir is empty */
	{
		std::cerr << "Error: Empty directory\n";
		return 1;
	}

	for (auto filePath : vecPaths)		/* Iterate to all files in dir */
	{
		data = "";
		std::fstream tmpFile(filePath);
		if (tmpFile.is_open())
		{
			while (getline (tmpFile, tempBuf))
				data += tempBuf + '\n';
			data.pop_back();

			try {
       			vecThreads.emplace_back(print_MD5, data, filePath);
			} catch (const std::exception& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
		}
	}
	
    for (std::thread &threadIter : vecThreads)  /* Iterate to all threads in vector */
    {
        if (threadIter.joinable())
            threadIter.join();                  /* Join if you can */
    }
	
	return 0;
}
