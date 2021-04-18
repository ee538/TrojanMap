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
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to ChickfilA
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "ChickfilA");
  std::vector<std::string> gt{
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "2613117861", "6817230316", "3642819026", "6817230310", "7811699597", "5565967545", "123318572",
      "6813405206", "6813379482", "544672028", "21306059", "6813379476", "6818390140", "63068610", 
      "6818390143", "7434941012", "4015423966", "5690152766", "6813379440", "6813379466", "21306060",
      "6813379469", "6813379427", "123005255", "6807200376", "6807200380", "6813379451", "6813379463",
      "123327639", "6813379460", "4141790922", "4015423963", "1286136447", "1286136422", "4015423962",
      "6813379494", "63068643", "6813379496", "123241977", "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544",
      "6813405275", "348121996", "348121864", "6813405280", "1472141024", "6813411590", "216155217", 
      "6813411589", "1837212103", "1837212101", "6820935911", "4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  path = m.CalculateShortestPath_Dijkstra("ChickfilA", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


// Test CalculateShortestPath_Dijkstra function 2
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Target", "Popeyes Louisiana Kitchen");
  // Test from Target to Popeyes Louisiana Kitchen
  std::vector<std::string> gt{
      "5237417650", "6813379479", "5237381975", "4399698012", "4399698013", "4399698011", "4399698010", 
      "123044712", "4399698009", "4399698008", "123005253", "6813379513", "6813379517", "6813379521", 
      "123327627", "4399697999", "6813565290", "122719210", "6813379407", "2613117879", "6813379406", 
      "6807905595", "6787803635", "2613117867", "4835551110", "6813565296", "122719205", "6813565294", "4835551232", 
      "4835551104", "4012842272", "4835551103", "123178841", "6813565313", "122814435", "6813565311", "4835551228", 
      "6813513565", "4835551090", "4835551081", "6813513564", "20400292", "5556117120", "5556117115", "4835551064", 
      "4012842277", "6813565326", "123241961", "6813565322", "4835551070", "5695236164"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Popeyes Louisiana Kitchen to Target
  path = m.CalculateShortestPath_Dijkstra("Popeyes Louisiana Kitchen", "Target");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


//Test CalculateShortestPath_Bellman_Ford function

TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to ChickfilA
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "ChickfilA");
  std::vector<std::string> gt{
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "2613117861", "6817230316", "3642819026", "6817230310", "7811699597", "5565967545", "123318572",
      "6813405206", "6813379482", "544672028", "21306059", "6813379476", "6818390140", "63068610", 
      "6818390143", "7434941012", "4015423966", "5690152766", "6813379440", "6813379466", "21306060",
      "6813379469", "6813379427", "123005255", "6807200376", "6807200380", "6813379451", "6813379463",
      "123327639", "6813379460", "4141790922", "4015423963", "1286136447", "1286136422", "4015423962",
      "6813379494", "63068643", "6813379496", "123241977", "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544",
      "6813405275", "348121996", "348121864", "6813405280", "1472141024", "6813411590", "216155217", 
      "6813411589", "1837212103", "1837212101", "6820935911", "4547476733"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to ChickfilA
  path = m.CalculateShortestPath_Bellman_Ford("ChickfilA", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Target", "Popeyes Louisiana Kitchen");
  // Test from Target to Popeyes Louisiana Kitchen
  std::vector<std::string> gt{
      "5237417650", "6813379479", "5237381975", "4399698012", "4399698013", "4399698011", "4399698010", 
      "123044712", "4399698009", "4399698008", "123005253", "6813379513", "6813379517", "6813379521", 
      "123327627", "4399697999", "6813565290", "122719210", "6813379407", "2613117879", "6813379406", 
      "6807905595", "6787803635", "2613117867", "4835551110", "6813565296", "122719205", "6813565294", "4835551232", 
      "4835551104", "4012842272", "4835551103", "123178841", "6813565313", "122814435", "6813565311", "4835551228", 
      "6813513565", "4835551090", "4835551081", "6813513564", "20400292", "5556117120", "5556117115", "4835551064", 
      "4012842277", "6813565326", "123241961", "6813565322", "4835551070", "5695236164"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Popeyes Louisiana Kitchen to Target
  path = m.CalculateShortestPath_Bellman_Ford("Popeyes Louisiana Kitchen", "Target");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
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



// Test TSP function 2
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





//Test IsCyclicUttil funciton
//Test CycleDetection function 
//{-118.299, -118.264, 34.032, 34.011}
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




//Test ReadLocationsFromCSVFile function
//Test ReadDependenciesFromCSVFile function
//Test DeliveringTrojan function
TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Trojan Grounds Starbucks","Ralphs","CVS","ChickfilA","Trader Joe39s"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","ChickfilA"}, {"Ralphs","CVS"}, {"ChickfilA","Trojan Grounds Starbucks"},
                                                        {"CVS","Trojan Grounds Starbucks"},{"Trojan Grounds Starbucks","Trader Joe39s"}};
  auto real = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> exp ={"Ralphs", "CVS", "ChickfilA","Trojan Grounds Starbucks","Trader Joe39s"};
  EXPECT_EQ(real, exp);
}


TEST(TrojanMapTest, TopologicalSort2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
  std::vector<std::vector<std::string>> dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Cardinal Gardens", "Coffee Bean1","CVS"};
  EXPECT_EQ(result, gt);
}