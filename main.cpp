#include <bits/stdc++.h>

using namespace std;

int towns_number;
int roads_number;
int adjacent_road_cost[6][6];
int residency_cost[6];

long long int shortest_path_cost[6][6];
int next_town_for_shortest_path[6][6];


void get_inputs() {
    cin >> towns_number >> roads_number;
    for (int i = 1; i <= towns_number; i++) {
        cin >> residency_cost[i];
    }
    for (int i = 1; i <= towns_number; i++) {
        for (int j = 1; j <= towns_number; j++) {
            adjacent_road_cost[i][j] = -1;
        }
    }
    for (int i = 0; i < roads_number; i++) {
        int s, t, cost;
        cin >> s >> t >> cost;
        adjacent_road_cost[s][t] = cost;
        adjacent_road_cost[t][s] = cost;
    }
}

void preprocess_shortest_path_cost() {
    for (int i = 1; i <= towns_number; i++) {
        for (int j = 1; j <= towns_number; j++) {
            if (i == j) {
                shortest_path_cost[i][j] = residency_cost[i];
                next_town_for_shortest_path[i][j] = i;
            } else if (adjacent_road_cost[i][j] != -1) {
                shortest_path_cost[i][j] = adjacent_road_cost[i][j] + residency_cost[j];
                next_town_for_shortest_path[i][j] = j;
            } else {
                shortest_path_cost[i][j] = INT32_MAX;
            }
        }
    }

    for (int i = 1; i <= towns_number; i++) {
        for (int j = 1; j <= towns_number; j++) {
            for (int z = 1; z <= towns_number; z++) {
                if (shortest_path_cost[j][i] + shortest_path_cost[i][z] < shortest_path_cost[j][z]) {
                    shortest_path_cost[j][z] = shortest_path_cost[j][i] + shortest_path_cost[i][z];
                    next_town_for_shortest_path[j][z] = next_town_for_shortest_path[j][i];
                }
            }
        }
    }
}


int main() {
    get_inputs();
    preprocess_shortest_path_cost();

}