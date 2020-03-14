#include <iostream>
#include <string>
#include <map>
#include <vector>

int main()
{
  std::map<std::pair<int,int>, std::pair<int,int>> resolutions;
  resolutions[std::make_pair(640,480)] = std::make_pair(980,480);

  if (resolutions.find(std::make_pair(640,480)) != resolutions.end())
  {
    std::cout << "Resolution " << resolutions[std::make_pair(640,480)].first  << "," 
                               << resolutions[std::make_pair(640,480)].second << std::endl;
  }
  else
  {
    std::cout <<"Resolution not found " << std::endl;   
  }
}
