#include <iostream>
#include <sstream>

#include "solutions.hpp"

using namespace std;

std::string Day02_1(std::ifstream& in) {
  constexpr auto kRed = int{12}, kGreen = int{13}, kBlue = int{14};
  string line;
  string token;
  int amount, id, result = 0;
  char separator;
  while (getline(in, line)) {
    stringstream ss(line);
    ss >> token >> id >> separator;
    string sub_game;
    bool possible{true};
    while (getline(ss, sub_game, ';')) {
      stringstream ss(sub_game);
      string draw;
      while (getline(ss, draw, ',')) {
        stringstream ss(draw);
        ss >> amount >> token;
        if ((token == "red" && amount > kRed) || (token == "green" && amount > kGreen) ||
            (token == "blue" && amount > kBlue)) {
          possible = false;
        }
      }
    }
    if (possible) {
      result += id;
    }
  }
  return to_string(result);
};

std::string Day02_2(std::ifstream& in) {
  string line;
  string token;
  int amount, id, result = 0;
  char separator;
  while (getline(in, line)) {
    stringstream ss(line);
    ss >> token >> id >> separator;
    string sub_game;
    auto min_red = int{0}, min_green = int{0}, min_blue = int{0};
    while (getline(ss, sub_game, ';')) {
      stringstream ss(sub_game);
      string draw;
      while (getline(ss, draw, ',')) {
        stringstream ss(draw);
        ss >> amount >> token;
        if (token == "red") {
          min_red = max(min_red, amount);
        } else if (token == "green") {
          min_green = max(min_green, amount);
        } else if (token == "blue") {
          min_blue = max(min_blue, amount);
        }
      }
    }
    result += min_red * min_green * min_blue;
  }
  return to_string(result);
};