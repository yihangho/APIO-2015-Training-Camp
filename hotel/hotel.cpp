#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#include <queue>
#define MAX_N 10000
#define MAX_M 100000
#define MAX_H 100
#define TIMELIMIT 600
using namespace std;

typedef pair<int, int> ii;

// Returns a list of hotels accessible from node
vector<int> accessible_hotels(int node, int N, vector<ii> neighbors[], bool has_hotel[]) {
  vector<int> output;
  bool visited[MAX_N + 5] = { 0 };

  priority_queue<ii, vector<ii>, greater<ii> > pq;
  pq.push(make_pair(0, node));

  // Use Dijkstra's Algorithm to greedily visit nodes closest from `node`
  while (!pq.empty()) {
    int current_cost = pq.top().first;
    int current_node = pq.top().second;
    pq.pop();

    if (visited[current_node]) {
      continue;
    }
    visited[current_node] = true;

    if (current_cost > TIMELIMIT) {
      // Since nodes are visited in ascending order of costs, all subsequent
      // nodes are too far too.
      break;
    } else if (has_hotel[current_node]) {
      output.push_back(current_node);
    }

    for (int i = 0; i < neighbors[current_node].size(); i++) {
      int neighbor_cost = neighbors[current_node][i].first;
      int neighbor      = neighbors[current_node][i].second;
      if (!visited[neighbor]) {
        pq.push(make_pair(current_cost + neighbor_cost, neighbor));
      }
    }
  }

  return output;
}

int transport(int N, int M, int cities1[], int cities2[], int costs[], int H, int hotels[]) {
  // neighbors[i] is the list of (cost, immediate_neighbor_of_i) pairs
  vector<ii> neighbors[MAX_N + 5];
  for (int i = 0; i < M; i++) {
    neighbors[cities1[i]].push_back(make_pair(costs[i], cities2[i]));
    neighbors[cities2[i]].push_back(make_pair(costs[i], cities1[i]));
  }

  // is_hotel[i] is true iff i has an hotel or i is the destination
  bool has_hotel[MAX_N + 5] = { 0 };
  for (int i = 0; i < H; i++) {
    has_hotel[hotels[i]] = true;
  }
  has_hotel[N] = true;

  // second_order_map[i] is the list of hotels or ending point accessible from i
  // Note that we are interested in nodes tha has hotel only as we're travelling
  // from hotels to hotels.
  vector<int> nearby_hotels[MAX_N + 5];
  nearby_hotels[1] = accessible_hotels(1, N, neighbors, has_hotel);
  for (int i = 0; i < H; i++) {
    nearby_hotels[hotels[i]] = accessible_hotels(hotels[i], N, neighbors, has_hotel);
  }

  // BFS on second order map to find the shortest path from beginning to the end
  // bfs will contain (node, cost) pairs
  queue<ii> bfs;
  bool visited[MAX_N + 5] = { 0 };

  bfs.push(make_pair(1, 0));
  while (!bfs.empty()) {
    int current_node = bfs.front().first;
    int current_cost = bfs.front().second;
    bfs.pop();

    if (visited[current_node]) {
      continue;
    }
    visited[current_node] = true;

    if (current_node == N) {
      return current_cost - 1;
    }

    // Enqueue all the direct neighbors with cost incremented by 1
    for (int i = 0; i < nearby_hotels[current_node].size(); i++) {
      int next_hotel = nearby_hotels[current_node][i];
      bfs.push(make_pair(next_hotel, current_cost + 1));
    }
  }

  return -1;
}

int main() {
  int N, M, H;
  int cities1[MAX_M + 5], cities2[MAX_M + 5], costs[MAX_M + 5], hotels[MAX_H + 5];

  while (true) {
    scanf("%d", &N); // Number of nodes
    if (N == 0) {
      break;
    }

    scanf("%d", &H); // Number of hotels
    for (int i = 0; i < H; i++) {
      scanf("%d", &hotels[i]);
    }

    scanf("%d", &M); // Number of edges
    for (int i = 0; i < M; i++) {
      scanf("%d %d %d", &cities1[i], &cities2[i], &costs[i]);
    }

    printf("%d\n", transport(N, M, cities1, cities2, costs, H, hotels));
  }

  return 0;
}
