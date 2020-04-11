#include <iostream>
#include <map>
#include <string>
#include <cstdio>

static std::map < int, std::pair<std::string, std::string> >errnoMap;
static std::multimap <int, int> taskSemMap;

int main(int argc, char *argv[])
{
    std::cout << "Starting..." << std::endl;

    int id = 10;


    taskSemMap.insert(std::pair<int,int>(id,22));
    taskSemMap.insert(std::pair<int,int>(id,222));
    taskSemMap.insert(std::pair<int,int>(id,2222));

    taskSemMap.insert(std::pair<int,int>(111,11));
    taskSemMap.insert(std::pair<int,int>(111,111));
    taskSemMap.insert(std::pair<int,int>(111,1111));

    auto range = taskSemMap.equal_range(id);
    for (auto it = range.first; it != range.second; it++)
    {
        std::cout << "sem : 0x" << std::hex <<  it->second << std::endl;

    }

    errnoMap[0] = std::make_pair("No Error", "No error reported");

    printf("Error reported %s, %s\n", errnoMap[0].first.c_str(), errnoMap[0].second.c_str());
    return 0;
}
