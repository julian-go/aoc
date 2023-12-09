#include <algorithm>
#include <map>
#include <vector>

#include "solutions.hpp"

using namespace std;

enum class Type {
  kHighCard = 0,
  kOnePair = 1,
  kTwoPair = 2,
  kThreeOfAKind = 3,
  kFullHouse = 4,
  kFourOfAKind = 5,
  kFiveOfAKind = 6
};

using ValueMap = map<char, int>;

static const ValueMap kCardValuePart1 = {{'2', 2},  {'3', 3},  {'4', 4}, {'5', 5},  {'6', 6},
                                         {'7', 7},  {'8', 8},  {'9', 9}, {'T', 10}, {'J', 11},
                                         {'Q', 12}, {'K', 13}, {'A', 14}};

static const ValueMap kCardValuePart2 = {{'J', 1},  {'2', 2},  {'3', 3}, {'4', 4}, {'5', 5},
                                         {'6', 6},  {'7', 7},  {'8', 8}, {'9', 9}, {'T', 10},
                                         {'Q', 11}, {'K', 12}, {'A', 13}};

struct Hand {
  Hand(string c, int b, ValueMap value) : cards{c}, bid{b}, value(value) {
    map<int, int> stats;
    for (const auto& card : cards) {
      if (stats.contains(card)) {
        stats[card]++;
      } else {
        stats[card] = 1;
      }
    }

    if (stats.size() == 5) {
      type = Type::kHighCard;
    } else if (stats.size() == 4) {
      type = Type::kOnePair;
    } else if (stats.size() == 3) {
      bool b = std::find_if(stats.begin(), stats.end(), [](auto p) { return p.second == 3; }) !=
               stats.end();
      if (b) {
        type = Type::kThreeOfAKind;
      } else {
        type = Type::kTwoPair;
      }
    } else if (stats.size() == 2) {
      bool b = std::find_if(stats.begin(), stats.end(), [](auto p) { return p.second == 4; }) !=
               stats.end();
      if (b) {
        type = Type::kFourOfAKind;
      } else {
        type = Type::kFullHouse;
      }
    } else {
      type = Type::kFiveOfAKind;
    }
  }

  void UpgradeJokers() {
    auto num_jokers = std::count(cards.begin(), cards.end(), 'J');
    switch (type) {
      case Type::kHighCard:
        if (num_jokers > 0) {
          type = Type::kOnePair;
        }
        break;
      case Type::kOnePair:
        if (num_jokers > 0) {
          type = Type::kThreeOfAKind;
        }
        break;
      case Type::kTwoPair:
        if (num_jokers > 1) {
          type = Type::kFourOfAKind;
        } else if (num_jokers > 0) {
          type = Type::kFullHouse;
        }
        break;
      case Type::kThreeOfAKind:
        if (num_jokers > 2) {
          type = Type::kFourOfAKind;
        } else if (num_jokers > 1) {
          type = Type::kFiveOfAKind;
        } else if (num_jokers > 0) {
          type = Type::kFourOfAKind;
        }
        break;
      case Type::kFullHouse:
      case Type::kFourOfAKind:
        if (num_jokers > 0) {
          type = Type::kFiveOfAKind;
        }
        break;
      default:
        break;
    }
  }

  Type type;
  string cards;
  int bid;
  ValueMap value;

  bool operator<(const Hand& other) const {
    if (type == other.type) {
      for (int i = 0; i < cards.size(); ++i) {
        if (cards[i] != other.cards[i]) {
          return value.at(cards[i]) < value.at(other.cards[i]);
        }
      }
      return false;
    } else {
      return type < other.type;
    }
  }
};

std::string Day07_1(std::ifstream& in) {
  string cards{};
  int bid{0};
  vector<Hand> hands;
  while (in >> cards >> bid) {
    hands.emplace_back(cards, bid, kCardValuePart1);
  }

  sort(hands.begin(), hands.end());
  int result{0};
  for (int i = 0; i < hands.size(); ++i) {
    result += hands[i].bid * (i + 1);
  }
  return to_string(result);
};

std::string Day07_2(std::ifstream& in) {
  string cards{};
  int bid{0};
  vector<Hand> hands;
  while (in >> cards >> bid) {
    hands.emplace_back(cards, bid, kCardValuePart2);
    hands.back().UpgradeJokers();
  }

  sort(hands.begin(), hands.end());
  int result{0};
  for (int i = 0; i < hands.size(); ++i) {
    result += hands[i].bid * (i + 1);
  }
  return to_string(result);
};