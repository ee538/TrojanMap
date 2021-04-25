#include <iostream>
#include "src/lib/trojanmap.h"

int main() {
  TrojanMap x;
  x.CreateGraphFromCSVFile();
  x.PrintMenu(); 
  
  /*std::vector<std::string> input={"123120189", "4011837229", "4011837224", "2514542032", "2514541020", "1931345270", "4015477529", };
  auto result=x.TravellingTrojan(input);
  std::vector<std::string> gt=result.second[result.second.size()-1];
  for(auto x:gt)
  {
    std::cout << x << " ";
  }
  std::cout << std::endl;*/
  
 
  return 0;
}