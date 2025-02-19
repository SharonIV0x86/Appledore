#include "../include/GraphMatrix.hpp"
#include <iostream>
#include <set>
#include <string>

// Custom edge type for friendship details
class Friendship {
public:
  int sinceYear;
  std::string friendshipType;

  Friendship(int sinceYear = 0, const std::string &friendshipType = "")
      : sinceYear(sinceYear), friendshipType(friendshipType) {}

  bool operator==(const Friendship &other) const {
    return sinceYear == other.sinceYear &&
           friendshipType == other.friendshipType;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const Friendship &friendship) {
    os << "{ Since: " << friendship.sinceYear << ", Type: \""
       << friendship.friendshipType << "\" }";
    return os;
  }
};

int main() {
  // Create a graph to represent a social network
  Appledore::GraphMatrix<std::string, Friendship, Appledore::UndirectedG>
      socialGraph;

  // Add users as vertices
  socialGraph.addVertex("Alice");
  socialGraph.addVertex("Bob");
  socialGraph.addVertex("Charlie");
  socialGraph.addVertex("David");

  // Define some friendships (edges) between users
  Friendship f1{2015, "Best Friends"};
  Friendship f2{2018, "Work Friends"};
  Friendship f3{2020, "College Friends"};

  // Add friendship relationships (edges)
  socialGraph.addEdge("Alice", "Bob", f1); // Alice and Bob are best friends
  socialGraph.addEdge("Alice", "Charlie",
                      f2);                 // Alice and Charlie are work friends
  socialGraph.addEdge("Bob", "David", f3); // Bob and David are college friends
  socialGraph.addEdge("Charlie", "David",
                      f2); // Charlie and David are work friends

  // Get and print all users (vertices)
  std::cout << "Users in the social network: ";
  for (const auto &user : socialGraph.getVertices()) {
    std::cout << user << ", ";
  }
  std::cout << "\n";

  // Get and print neighbors (friends) for "Alice"
  std::cout << "\nFriends of Alice:\n";
  auto friends = socialGraph.getNeighbors("Alice");
  for (const auto &friendName : friends) {
    std::cout << " - " << friendName << "\n";
  }

  // Check if Alice and Bob are friends
  std::cout << "\nAre Alice and Bob friends? ";
  if (socialGraph("Alice", "Bob")) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }

  // Try to get a non-existing friendship (will throw an exception)
  try {
    socialGraph.getEdge(
        "Alice", "David"); // Throws error because there's no direct friendship
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << "\n";
  }
  std::cout << "Total No. of friends Alice has:"
            << socialGraph.totalDegree("Alice");

  return 0;
}
