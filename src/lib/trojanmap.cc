#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <locale>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
// #include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include <stack>
#include <chrono>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"


#define very_max 999999.9999
//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 * 
 */
void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = Autocomplete(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " << results.first
                << " Longitude: " << results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = CalculateShortestPath_Bellman_Ford(input1, input2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      std::cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Travelling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    std::cout << menu << std::endl << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    getline(std::cin, input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    std::cout << "Calculating ..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto results = TravellingTrojan(locations);
    auto results2= TravellingTrojan_2opt(locations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    CreateAnimation(results.second);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;


     menu = "***************************2-Opt Results***********************************\n";
     std::cout << menu;
     if (results2.second.size() != 0) {
      for (auto x : results2.second[results2.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results2.first << " miles" << std::endl;
      
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }


    auto results3=TravellingTrojan_3opt(locations);
    menu = "***************************3-Opt Results***********************************\n";
     std::cout << menu;
     if (results3.second.size() != 0) {
      for (auto x : results3.second[results3.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results3.first << " miles" << std::endl;
      
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }


    PrintMenu();
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    std::vector<double> square;
    square.push_back(atof(input.c_str()));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results == true)
      std::cout << "there exists cycle in the subgraph " << std::endl;
    else
      std::cout << "there exist no cycle in the subgraph " << std::endl;
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    if (results == true){
      PlotPointsandEdges(cycle_locations,square);
      cycle_locations.clear();

    }
    
    PrintMenu();
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the locations filename:";
    std::cout << menu;
    std::string locations_filename;
    getline(std::cin, locations_filename);
    menu = "Please input the dependencies filename:";
    std::cout << menu;
    std::string dependencies_filename;
    getline(std::cin, dependencies_filename);
    
    // Read location names from CSV file
    std::vector<std::string> location_names;
    if (locations_filename == "") 
      location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    else
      location_names = ReadLocationsFromCSVFile(locations_filename);
    
    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies;
    if (dependencies_filename == "")
      dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}};
    else
      dependencies = ReadDependenciesFromCSVFile(dependencies_filename);

    // std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    // std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    auto start = std::chrono::high_resolution_clock::now();
    auto result = DeliveringTrojan(location_names, dependencies);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Topological Sorting Reults:" << std::endl;
    for (auto x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto x: result) {
      Node node = GetNode(x);
      node_ids.push_back(node.id);
    }
    PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '7':
    break;
  default:
  {
    std::cout << "Please select 1 - 7." << std::endl;
    PrintMenu();
    break;
  }
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/lib/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 * 
 * @param  {std::string} id : location id
 */
void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 * 
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 * 
 * @param  {std::vector<std::string>} location_ids : path
 */
void TrojanMap::PlotPath(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPoints(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    for(auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}


/**
 * CreateAnimation: Create the videos of the progress to get the path
 * 
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> path_progress){
  cv::VideoWriter video("src/lib/output.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
  for(auto location_ids: path_progress) {
    std::string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
              cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
                cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
	video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 * 
 * @param  {double} lat         : latitude 
 * @param  {double} lon         : longitude
 * @return {std::pair<double, double>}  : position on the map
 */
std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(std::string id) {
    return data[id].lat;
}


/**
 * GetLon: Get the longitude of a Node given its id. 
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) { 
    return data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) { 
    return data[id].name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
    return data[id].neighbors;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {Node} a  : node a
 * @param  {Node} b  : node b
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const Node &a, const Node &b) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  double sum = 0;
  int j=1;
  for(int i=0;i<path.size()-1;i++)
  {
    Node node1=data[path[i]];
    Node node2=data[path[j]];
    j++;
    sum += CalculateDistance(node1,node2);
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
  std::map<std::string,Node>::iterator it;
  std::string lower_letter="abcdefghijklmnopqrstuvwxyz";
  std::string upper_letter="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string lower_name=name;
  for(int i=0;i<lower_name.length();i++)
  {
    std::string::size_type pos=upper_letter.find(lower_name[i]);
    if(pos != std::string::npos)
    {
      lower_name[i]=lower_letter[pos];
    }
  }


  for (it = data.begin();it != data.end();it++)
  {
    std::string node_name=GetName(it->first);
    if(node_name=="")
      continue;
    std::string lower_node_name=node_name;
   
    for(int i=0;i<lower_node_name.length();i++)
    {
      std::string::size_type pos=upper_letter.find(lower_node_name[i]);
      if(pos != std::string::npos)
      {
        lower_node_name[i]=lower_letter[pos];
      }
    }
    std::string part_node_name=lower_node_name.substr(0,name.length());
    if(part_node_name==lower_name)
      results.push_back(node_name);



  }
  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  std::map<std::string,Node>::iterator it;
  for(it=data.begin();it !=data.end();it++)
  {
    if(it->second.name==name)
    {
      results=std::make_pair(it->second.lat,it->second.lon);
    }
  }
  return results;
}

/**
 * GetNode: Given a location name, return the node.
 *
 * @param  {std::string} name          : location name
 * @return {Node}  : node
 */
Node TrojanMap::GetNode(std::string name) {
  Node n;
  std::map<std::string,Node>::iterator it;
  for(it=data.begin();it !=data.end();it++)
  {
    if(it->second.name==name)
      return it->second;
  }
  return n;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;
  std::vector<std::string> allNodes;
  std::map<std::string,Node>::iterator it;
  for(it=data.begin();it !=data.end();it++)
  {
    allNodes.push_back(it->first);
  }

  std::vector<int> visited(2237,0);
  std::vector<int> previousNode(2237,-1);
  std::vector<std::vector<double>> weight(2237,std::vector<double>(2237,0));
  for(int i=0;i<2237;i++)
  {
    std::string start_node_id=allNodes[i];
    std::vector<std::string> adjacents=data[start_node_id].neighbors;
    for(int j=0;j<2237;j++)
    {
      std::string end_node_id=allNodes[j];
      if(start_node_id==end_node_id)
      {
        weight[i][j]=0;
        continue;
      }
      std::vector<std::string>::iterator it=std::find(adjacents.begin(),adjacents.end(),end_node_id);
      if(it==adjacents.end())
      {
        weight[i][j]=very_max;
        continue;
      }
      else
      {
        weight[i][j]=CalculateDistance(data[start_node_id],data[end_node_id]);
      }

    }
  }
  std::string start_id=GetNode(location1_name).id;
  std::string end_id=GetNode(location2_name).id;
  std::vector<std::string>::iterator start_it=std::find(allNodes.begin(),allNodes.end(),start_id);
  int v0=start_it-allNodes.begin();
  std::vector<std::string>::iterator end_it=std::find(allNodes.begin(),allNodes.end(),end_id);
  int v1=end_it-allNodes.begin();
  std::vector<double> dist(2237,0);
  for(int i=0;i<2237;i++)
  {
    dist[i]=weight[v0][i];
    if(weight[v0][i]<very_max)
      previousNode[i]=v0;
  }

  visited[v0]=1;
  previousNode[v0]=-1;
  int v;
  double min_cur;

  /* lecture method 
  std::unordered_set<int> isvisited;
  isvisited.insert(v0);
  while(isvisited.size()<2237)
  {
    int u;
    int min=
  }
  */

  
  for(int i=0;i<2236;i++)
  {
     min_cur=very_max;
     for(int j=0;j<2237;j++)
     {
       if(visited[j]==0&&dist[j]<min_cur)
       {
         v=j;
         min_cur=dist[j];
       }
     }
     visited[v]=1;
     for(int j=0;j<2237;j++)
     {
       if(visited[j]==1)
          continue;
       if(dist[v]==very_max||weight[v][j]==very_max)
          continue;
       if(dist[v]+weight[v][j]<dist[j])
       {
         dist[j]=dist[v]+weight[v][j];
         previousNode[j]=v;
       }
     }

  }
  


  if(dist[v1]==very_max)
    return path;
  else
  {
    path.push_back(allNodes[v1]);
    int previous_index=previousNode[v1];
    while(previous_index !=-1)
    {
      path.push_back(allNodes[previous_index]);
      previous_index=previousNode[previous_index];
    }
    std::reverse(path.begin(),path.end());
    return path;

  }
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){
  std::vector<std::string> path;
  std::vector<std::string> allNodes;
  std::map<std::string,Node>::iterator it;
  for(it=data.begin();it !=data.end();it++)
  {
    allNodes.push_back(it->first);
  }
  
  std::vector<std::vector<double>> weight(2237,std::vector<double>(2237,0));
  for(int i=0;i<2237;i++)
  {
    std::string start_node_id=allNodes[i];
    std::vector<std::string> adjacents=data[start_node_id].neighbors;
    for(int j=0;j<2237;j++)
    {
      std::string end_node_id=allNodes[j];
      if(start_node_id==end_node_id)
      {
        weight[i][j]=0;
        continue;
      }
      std::vector<std::string>::iterator it=std::find(adjacents.begin(),adjacents.end(),end_node_id);
      if(it==adjacents.end())
      {
        weight[i][j]=very_max;
        continue;
      }
      else
      {
        weight[i][j]=CalculateDistance(data[start_node_id],data[end_node_id]);
      }

    }

  }

  std::string start_id=GetNode(location1_name).id;
  std::string end_id=GetNode(location2_name).id;
  std::vector<std::string>::iterator start_it=std::find(allNodes.begin(),allNodes.end(),start_id);
  int v0=start_it-allNodes.begin();
  std::vector<std::string>::iterator end_it=std::find(allNodes.begin(),allNodes.end(),end_id);
  int v1=end_it-allNodes.begin();

  

  std::vector<std::vector<double>> d(2237,std::vector<double>(2237));
  std::vector<int> previousNode(2237,-1);

  for(int i=0;i<2237;i++)
  {
    
    for(int v=0;v<2237;v++)
    {
        if(i==0)
        {
          d[0][v]= (v==v0) ? 0:very_max;
          continue;
        }
        d[i][v]=very_max;
        for(std::string u:data[allNodes[v]].neighbors)
        {
          std::vector<std::string>::iterator u_it=std::find(allNodes.begin(),allNodes.end(),u);
          int u_id=u_it-allNodes.begin();
          std::vector<double> comparelist={d[i][v],d[i-1][v],d[i-1][u_id]+weight[u_id][v]};
          d[i][v]= *std::min_element(comparelist.begin(),comparelist.end());

          
          
          if(d[i][v]==d[i-1][u_id]+weight[u_id][v])
            previousNode[v]=u_id;
        }

    }
   
  }


 

  if(d[2236][v1]==very_max)
    return path;

  else{
    path.push_back(allNodes[v1]);
    int previous_index=previousNode[v1];
    while(previous_index !=-1)
    {
      path.push_back(allNodes[previous_index]);
      previous_index=previousNode[previous_index];
    }
    std::reverse(path.begin(),path.end());
    return path;
  }
  


  return path;
}

//Step6 DAG
/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename,std::ios::in);
  std::string line;
  getline(fin,line);
  while(getline(fin,line)){
    line.erase(std::remove(line.begin(),line.end(),','),line.end());
    location_names_from_csv.push_back(line);

  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename,std::ios::in);
  std::string line,word;
  getline(fin,line);
  while(getline(fin,line)){
    std::stringstream s(line);
    std::vector<std::string> temp;
    while(getline(s,word,',')){
      temp.push_back(word);
    }
    dependencies_from_csv.push_back(temp);
  }

  fin.close();

  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */

/*********WAY 1*********/
void TrojanMap::topo(std::string root,std::map<std::string,int> &marks,std::vector<std::string> &top_list, std::map<std::string,std::vector<std::string>> &edge_map){
  marks[root]=1;
  std::vector<std::string> temp=edge_map[root];
  for(const std::string &child : temp)
  {
      if(marks[child]!=1)
      {
        topo(child,marks,top_list,edge_map);
      }
  }
  top_list.push_back(root);

}

std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;
  
  
  std::vector<std::string> root;
  int flag=1;
  for(auto location:locations)
  {
    for(auto x:dependencies)
    {
      if(location==x[1])
        flag=0;
    }
    if(flag==1)
      root.push_back(location);
    
    flag=1;
  }
  
  
  if(root.size()!=1)
    return result;   
  
  std::string start_p=root[0];
  
  std::map<std::string,std::vector<std::string>> edge_map;
  for(auto location:locations)
  {
    for(auto x:dependencies)
    {
      if(location==x[0])
      {
        edge_map[location].push_back(x[1]);
      }
    }
  }

  
  std::map<std::string,int> marks;
  topo(start_p,marks,result,edge_map);
  std::reverse(result.begin(),result.end());
  if(result.size()==locations.size())
    return result;
  else{
    std::vector<std::string> temp;
    return temp;
  }

  return result;

}

/*********WAY 2*********/
// std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
//                                                      std::vector<std::vector<std::string>> &dependencies){
// std::vector<std::string> result;
// int size = locations.size();

                                                  
// while(result.size() != size){

//   for(int i = 0;i < locations.size(); i++){

//     if(std::find(result.begin(), result.end(), locations[i]) == result.end()){
//       result.push_back(locations[i]);
//     }
//     else
//       continue;

//     for(int j = 0;j < dependencies.size(); j++){
//       if(locations[i] == dependencies[j][1] && ( std::find(result.begin(), result.end(),dependencies[j][0]) == result.end() )){
//         result.pop_back(); 
//         break;
//       }
//     }
//   }    

// }  

//   return result;                                                     
// }

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
void TrojanMap::Permute_aux(std::vector<std::string> &nums,std::vector<std::vector<std::string>> &result,std::vector<std::string> curResult){
  if (curResult.size() == nums.size()) {
        result.push_back(curResult);
        return; 
        }
  for (int i = 0; i < nums.size(); i++) {

        if (std::find(curResult.begin(), curResult.end(), nums[i]) != curResult.end()) {
                            continue; 
                            }
// Update curResult
              std::vector<std::string> nextCurResult = curResult;
              nextCurResult.push_back(nums[i]);
// Recursive DFS call
            Permute_aux(nums, result, nextCurResult);
  }
}



std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::vector<std::string>> paths;
  std::vector<std::string> curResult;
  Permute_aux(location_ids,paths,curResult);
  for(int i=0;i<paths.size();i++)
  {
    paths[i].push_back(paths[i][0]);
  }
  double min_len=0;
  int min_index=0;
  
  for(int i=0;i<paths[0].size()-1;i++)
  {
    min_len += CalculateDistance(data[paths[0][i]],data[paths[0][i+1]]);
  }
  for(int i=1;i<paths.size();i++)
  {
    double temp=0;
    for(int j=0;j<paths[0].size()-1;j++)
    {
      temp += CalculateDistance(data[paths[i][j]],data[paths[i][j+1]]);
    }
    if(temp<min_len)
    {
      min_len=temp;
      min_index=i;

    }
  }

  if(min_index != paths.size()-1)
  {
    std::vector<std::string> path_temp=paths[min_index];
    paths[min_index]=paths[paths.size()-1];
    paths[paths.size()-1]=path_temp;
  }

  results.first=min_len;
  results.second=paths;

  return results;
}

void TrojanMap::swap_2Cal(std::vector<std::string> &init_path,int &counter,double &min_len,
std::vector<std::vector<std::string>> &results){
  results.push_back(init_path);
  for(int m=1;m<init_path.size()-2;m++)
  {
    for(int n=m+1;n<init_path.size()-1;n++){
      
        std::vector<std::string> swap_path=init_path;
        std::string temp_node=init_path[m];
        swap_path[m]=swap_path[n];
        swap_path[n]=temp_node;
        double temp_route=0;
        for(int j=0;j<swap_path.size()-1;j++)
        {
          temp_route += CalculateDistance(data[swap_path[j]],data[swap_path[j+1]]);
        }
        if(temp_route<min_len)
        {
          counter=0;
          min_len=temp_route;
          init_path=swap_path;
          return;
        }
        else{
          counter++;
        }
        if(counter==5)
          return;


    }
  }
  
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  
  std::vector<std::vector<std::string>> paths;
  std::vector<std::string> curResult;
  Permute_aux(location_ids,paths,curResult);
  for(int i=0;i<paths.size();i++)
  {
    paths[i].push_back(paths[i][0]);
  }
  
  double min_len=0;
  int counter=0;

  
    std::vector<std::string> init_path=paths[0];
    

    for(int j=0;j<init_path.size()-1;j++)
    {
      min_len += CalculateDistance(data[init_path[j]],data[init_path[j+1]]);
    }
    for(int i=0;i<paths.size();i++)
    {
      if(counter==5)
        break;
      swap_2Cal(init_path,counter,min_len,results.second);
    }
    
    results.first=min_len;

  return results;
}


void TrojanMap::swap_3Cal(std::vector<std::string> &init_path,int &counter,double &min_len,
std::vector<std::vector<std::string>> &results){
            results.push_back(init_path);
            for(int m=1;m<init_path.size()-3;m++)
            {
              for(int n=m+1;n<init_path.size()-2;n++)
              {
                for(int p=n+1;p<init_path.size()-1;p++)
                {
                    std::vector<std::string> swap1_path=init_path;
                    std::string node_m=swap1_path[m];
                    std::string node_n=swap1_path[n];
                    std::string node_p=swap1_path[p];
                    swap1_path[n]=node_m;
                    swap1_path[p]=node_n;
                    swap1_path[m]=node_p;
                    double temp_route=0;
                    for(int j=0;j<swap1_path.size()-1;j++)
                      {
                          temp_route += CalculateDistance(data[swap1_path[j]],data[swap1_path[j+1]]);
                      }
                    
                    if(temp_route>min_len)
                    {
                      counter++;
                      if(counter==5)
                          return;
                      
                    }
                    else{
                      min_len=temp_route;
                      counter=0;
                      init_path=swap1_path;
                      return;
                    }
                    swap1_path=init_path;
                     node_m=swap1_path[m];
                     node_n=swap1_path[n];
                     node_p=swap1_path[p];
                    swap1_path[m]=node_n;
                    swap1_path[n]=node_p;
                    swap1_path[p]=node_m;
                    for(int j=0;j<swap1_path.size()-1;j++)
                      {
                          temp_route += CalculateDistance(data[swap1_path[j]],data[swap1_path[j+1]]);
                      }
                    
                    if(temp_route>min_len)
                    {
                      counter++;
                      if(counter==5)
                          return;
                      
                    }
                    else{
                      min_len=temp_route;
                      counter=0;
                      init_path=swap1_path;
                      return;
                    }
                    


                }
              }
            }
}




std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(
      std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  
  std::vector<std::vector<std::string>> paths;
  std::vector<std::string> curResult;
  Permute_aux(location_ids,paths,curResult);
  for(int i=0;i<paths.size();i++)
  {
    paths[i].push_back(paths[i][0]);
  }
  
  double min_len=0;
  int counter=0;

  
    std::vector<std::string> init_path=paths[0];
    

    for(int j=0;j<init_path.size()-1;j++)
    {
      min_len += CalculateDistance(data[init_path[j]],data[init_path[j+1]]);
    }

    if(init_path.size()<5)
    {
      results.second.push_back(init_path);
      results.first=min_len;
      return results;
    }
    


    for(int i=0;i<paths.size();i++)
    {
      if(counter==5)
        break;
      swap_3Cal(init_path,counter,min_len,results.second);
    }
    
    results.first=min_len;

  return results;
}




/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::IsCyclicUttil(std::string node_id, std::map<std::string,int> &isvisit,std::string parent_id,
const std::vector<double> &square,std::map<std::string,std::string> &father)
{
  isvisit[node_id]=1;
  father[node_id]=parent_id;
  for(auto neighbor:data[node_id].neighbors)
  {
    if((data[neighbor].lon>=square[0])&&(data[neighbor].lon<=square[1])&&(data[neighbor].lat<=square[2])&&(data[neighbor].lat>=square[3]))
    {
      if((isvisit[neighbor]==1)&&(neighbor!=parent_id))
      {
        
        std::string temp=node_id;
        while(temp !=neighbor)
        {
            cycle_locations.push_back(temp);
            temp=father[temp];
        }
        cycle_locations.push_back(neighbor);

        return true;

      }
            

      if(isvisit[neighbor]==0)   
      {
        if(IsCyclicUttil(neighbor,isvisit,node_id,square,father)==true)
          return true;
      }  
    }
    
  }

  return false;

}

bool TrojanMap::CycleDetection(std::vector<double> &square) {
  std::map<std::string,int> isvisit;
  std::map<std::string,Node>::iterator it;
  std::map<std::string,std::string> father;
  for(it=data.begin();it !=data.end();it++)
  {
    if((it->second.lon>=square[0])&&(it->second.lon<=square[1])&&(it->second.lat<=square[2])&&(it->second.lat>=square[3]))
    {
      if(isvisit[it->first]==0)
      {
        if(IsCyclicUttil(it->first,isvisit," ",square,father)==true)
          return true;
      }
    }
  }
  return false;
}