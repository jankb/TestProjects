#include <iostream>
#include <algorithm>
#include <future>
#include <thread>
#include <chrono>
#include <map>




int main()
{
	std::cout << "Starting app." << std::endl;

	std::map<std::string, int> deviceDelayMap;

	deviceDelayMap["device/one"]   = 3000;
	deviceDelayMap["device/two"]   = 100;
	deviceDelayMap["device/three"] = 10;
	deviceDelayMap["device/four"]  = 50;
	deviceDelayMap["device/five"]  = 17000;

	std::vector<std::thread*> threads;

	std::thread applicationLoop([]()
		{
			while (true)
			{
				std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1000));
				printf("*");
			}
		});


	std::for_each(deviceDelayMap.begin(), deviceDelayMap.end(), [&threads](auto deviceDelayPair)
		{
			std::cout << "Creating thread for device " << deviceDelayPair.first << std::endl;
			threads.push_back(new std::thread([=]()
				{ 
					std::cout << " Starting " << deviceDelayPair.first << std::endl;
					std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(deviceDelayPair.second));
					std::cout << "Thread for device " << deviceDelayPair.first << " - started." << std::endl;
				}));
		});

	std::cout << "Done creating threads. Waiting for threads to complete." <<  std::endl;

	std::for_each(threads.begin(), threads.end(), [](std::thread* thread)
		{		
			thread->join();
		});

	std::cout << "All threads completed." << std::endl;
	

	applicationLoop.join();
	return 0;
}
