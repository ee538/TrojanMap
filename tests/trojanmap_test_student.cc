#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

//Test GetLat function
TEST(TrojanMapStudentTest, GetLat) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete
  
  std::string id = "33078887";
  double real = m.GetLat(id);
  double expected = 34.026738;
  EXPECT_EQ(expected, real);
}

//Test GetLon function
TEST(TrojanMapStudentTest, GetLon) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete

  std::string id = "63765376";
  double real = m.GetLon(id);
  double expected = -118.2817732;
  EXPECT_EQ(expected, real);
}


//Test GetName function
TEST(TrojanMapStudentTest, GetName) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete

  std::string id = "614990288";
  std::string real = m.GetName(id);
  std::string expected = "Trojan Grounds Starbucks";
  EXPECT_EQ(expected, real);
}


//Test GetNode function 
TEST(TrojanMapStudentTest, GetNode) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete

  std::string name = "Parking Center";
  Node real = m.GetNode(name);//Node exp("732642214",34.0199998,-118.277186,"Parking Center",{"4012759746"});

  auto expid = "732642214";
  double explat = 34.0199998;
  double explon = -118.277186;
  auto expname = "Parking Center";
  std::vector<std::string> expneighbors = {"4012759746"};

  EXPECT_EQ(expid, real.id);
  EXPECT_EQ(explat, real.lat);
  EXPECT_EQ(explon, real.lon);
  EXPECT_EQ(expname, real.name);
  EXPECT_EQ(expneighbors,real.neighbors);  
}


//Test GetNeighborIDs function
TEST(TrojanMapStudentTest, GetNeighborIDs) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete
  
  auto id = "932378219";
  std::vector<std::string> real = m.GetNeighborIDs(id);
  std::vector<std::string>  expected = {"6226313827", "6814990112", "6226313826"};
  EXPECT_EQ(expected, real);
}


//Test CalculateDistance function
TEST(TrojanMapStudentTest, CalculateDistance) {
  TrojanMap m;
  //m.CreateGraphFromCSVFile();//data complete
  
  Node a;//20400292	34.0273404	-118.2765547
  a.lat = 34.0273404;
  a.lon = -118.2765547;

  Node b;//21098539	34.02549	-118.2915534
  b.lat = 34.02549;
  b.lon = -118.2915534;

  // Node a;//21098539	34.02549	-118.2915534
  // a.lat = 34.02549;
  // a.lon = -118.2915534;

  // Node b;//21098546	34.030993	-118.2647022
  // b.lat = 34.030993;
  // b.lon = -118.2647022;

  double c = m.CalculateDistance(a,b);
  double real = (double)(int)(c * 100000.0)/100000.0; 
  double exp = 0.86882;
  EXPECT_EQ(exp, real);
}


//Test CalculatePathLength function
TEST(TrojanMapStudentTest, CalculatePathLength) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete

  std::vector<std::string> path = {"20400292","21098539","21098546"};
  double c = m.CalculatePathLength(path);
  double real = (double)(int)(c * 100000.0)/100000.0; 
  double exp = 2.45359;//0.86882+1.58476
  EXPECT_EQ(exp, real);
}


//Test Autocomplete function
TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete
  std::vector<std::string> exp_names = {"USC Fisher Museum of Art", "USC Village Gym","USC Parking","USC Village Dining Hall"}; 
  
  // Test the simple case
  auto real_names = m.Autocomplete("USC");
  EXPECT_EQ(real_names, exp_names);
  
  // Test the lower case
  real_names = m.Autocomplete("usc");
  EXPECT_EQ(real_names, exp_names);
 
  // Test the lower and upper case 
  real_names = m.Autocomplete("Usc"); 
  EXPECT_EQ(real_names, exp_names);
}



//Test GetPosition function
TEST(TrojanMapTest, GetPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete

  // Test case 1
  auto name1 = "Massman Theatre";
  std::pair<double, double> real_pair1 =  m.GetPosition(name1);
  std::pair<double, double> exp_pair1(34.0226664,-118.2899311);
  EXPECT_EQ(real_pair1, exp_pair1);
  
  // Test case 2
  auto name2 = "Crosswalk1";
  std::pair<double, double> real_pair2 =  m.GetPosition(name2);
  std::pair<double, double> exp_pair2(34.0302951,-118.2857237);
  EXPECT_EQ(real_pair2, exp_pair2); 

  // Test case 3
  auto name3 = "Astor Motel";
  std::pair<double, double> real_pair3 =  m.GetPosition(name3);
  std::pair<double, double> exp_pair3(34.024536,-118.2755802);
  EXPECT_EQ(real_pair3, exp_pair3);  
}




//Test CalculateShortestPath_Dijkstra function
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Ground Zero", "CVS");
  std::vector<std::string> gt{
      "4089614984","4015372469","1732243620","4015372475","4015372476","6813379548","1732243576",
      "4015372477","4015372479","123241977","6813379496","63068643","5690152757","7930461034",
      "4015372481","6813379534","4015372482","4015372483","5690152760","123241965","6813379501","3088548446"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the path
  path = m.CalculateShortestPath_Dijkstra("CVS", "Ground Zero");
  std::reverse(gt.begin(),gt.end()); 
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("ChickfilA", "USC Parking");
  std::vector<std::string> gt{
    "4547476733","6820935911","1837212101","1837212103","6813411589","216155217","6813411590","1472141024","6813405280",
    "348121864","348121996","6813405275","1732243544","6819179749","4015372463","4015372468","4015372474","4015372476",
    "6813379548","1732243576","4015372477","4015372479","123241977","6813379496","63068643","5690152757","7930461034","4015372481",
    "6813379534","4015372482","4015372483","5690152760","123241965","6813379501","6787803628","6285409682","6045067407"}; 

  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  path = m.CalculateShortestPath_Dijkstra("USC Parking", "ChickfilA");
  std::reverse(gt.begin(),gt.end());

  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateShortestPath_Dijkstra3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Martin Luther King Jr Blvd  Coliseum", "John Adams Middle School");
  std::vector<std::string> gt{
      "269633667","6815813004","348123159","348123160","4020099351","348123342","4020099346","348123344","1870795193","122609808",
      "4020099339","216153383","7396914904","1837206582","1837206579","122670276","6819170170","123254978","1732243580","4015477536","6820982894","21302782",
      "6820982898","4012792178","1732243772","123254974","7211629026","7424313391","4012792179","63785567","4012792180","7867482499",
      "21302781","1732340074","123254964","122719192","6817197856","358786623"}; 

  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  path = m.CalculateShortestPath_Dijkstra("John Adams Middle School", "Martin Luther King Jr Blvd  Coliseum");
  std::reverse(gt.begin(),gt.end()); 

  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}






//Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Ground Zero", "CVS");
  std::vector<std::string> gt{
      "4089614984","4015372469","1732243620","4015372475","4015372476","6813379548","1732243576",
      "4015372477","4015372479","123241977","6813379496","63068643","5690152757","7930461034",
      "4015372481","6813379534","4015372482","4015372483","5690152760","123241965","6813379501","3088548446"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to ChickfilA
  path = m.CalculateShortestPath_Bellman_Ford("CVS", "Ground Zero");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("ChickfilA", "USC Parking");
  std::vector<std::string> gt{
      "4547476733","6820935911","1837212101","1837212103","6813411589","216155217","6813411590","1472141024","6813405280",
      "348121864","348121996","6813405275","1732243544","6819179749","4015372463","4015372468","4015372474","4015372476",
      "6813379548","1732243576","4015372477","4015372479","123241977","6813379496","63068643","5690152757","7930461034","4015372481",
      "6813379534","4015372482","4015372483","5690152760","123241965","6813379501","6787803628","6285409682","6045067407"}; 
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  path = m.CalculateShortestPath_Bellman_Ford("USC Parking","ChickfilA");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Martin Luther King Jr Blvd  Coliseum", "John Adams Middle School");
  std::vector<std::string> gt{
      "269633667","6815813004","348123159","348123160","4020099351","348123342","4020099346","348123344","1870795193","122609808",
      "4020099339","216153383","7396914904","1837206582","1837206579","122670276","6819170170","123254978","1732243580","4015477536","6820982894","21302782",
      "6820982898","4012792178","1732243772","123254974","7211629026","7424313391","4012792179","63785567","4012792180","7867482499",
      "21302781","1732340074","123254964","122719192","6817197856","358786623"}; 
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  path = m.CalculateShortestPath_Bellman_Ford("John Adams Middle School", "Martin Luther King Jr Blvd  Coliseum");
  std::reverse(gt.begin(),gt.end()); 
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}





//Test TravellingTrojan function
TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1873056015", "6905329551", "213332060", "1931345270"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1873056015", "213332060", "1931345270", "6905329551", "1873056015"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015405548", "4015203110", "6807439002", "7424270441", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}






//Test CycleDetection function {-118.299, -118.264, 34.032, 34.011}
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();//data complete
  
  // Test case 1
  std::vector<double> square1 = {-118.297, -118.277, 34.022, 34.0201};
  bool real1 = m.CycleDetection(square1);
  EXPECT_EQ(true, real1);

  // Test case 2
  std::vector<double> square2 = {-118.299, -118.277775, 34.032, 34.0291};
  bool real2 = m.CycleDetection(square2);
  EXPECT_EQ(true, real2);

  // Test case 3
  std::vector<double> square3 = {-118.290919, -118.282911, 34.02335, 34.0197};
  bool real3 = m.CycleDetection(square3);
  EXPECT_EQ(false, real3);
}





//Test DeliveringTrojan function
//dependencies1
TEST(TrojanMapTest, TopologicalSort1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Ralphs","CVS","ChickfilA"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","ChickfilA"}, {"ChickfilA","CVS"},{"Ralphs","CVS"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Ralphs","ChickfilA","CVS"};
  EXPECT_EQ(result, gt);
}

//dependencies2
TEST(TrojanMapTest, TopologicalSort2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
  std::vector<std::vector<std::string>> dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Cardinal Gardens", "Coffee Bean1","CVS"};
  EXPECT_EQ(result, gt);
}

// no topo sort
TEST(TrojanMapTest, TopologicalSort3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Ralphs","CVS","ChickfilA"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","ChickfilA"}, {"ChickfilA","CVS"},{"CVS","Ralphs"}};
  auto real = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> exp ={};
  EXPECT_EQ(real, exp);
}