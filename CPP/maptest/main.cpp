#include <iostream>
#include <string>
#include <map>
#include <vector>

int main()
{
  std::map<std::pair<int,int>, std::pair<int,int> > resolutions;

  resolutions[std::make_pair(640,480)] = std::make_pair(980,480);
  resolutions[std::make_pair(600,480)] = std::make_pair(900,480);

  auto it = resolutions.find(std::make_pair(600,480));
  if (it != resolutions.end())
  {
    std::cout << "Resolution " << (*it).second.first  << "," 
                               << (*it).second.second << std::endl;
  }
  else
  {
    std::cout <<"Resolution was found " << std::endl;
  }
}
