#include <bits/stdc++.h>

using namespace std;

const int MAX_TOWNS = 6;

int towns_number;
int roads_number;
int adjacent_matrix_road_cost[MAX_TOWNS][MAX_TOWNS];
vector<int> adjacent_list_roads[MAX_TOWNS];
int residency_cost[6];

long long int shortest_path_cost_in_specific_days[MAX_TOWNS][MAX_TOWNS][MAX_TOWNS]; // family v -> town u in i day
int next_town_for_shortest_path_in_specific_days[MAX_TOWNS][MAX_TOWNS][MAX_TOWNS];  // family v -> town u in i day
long long int meeting_cost_in_specific_town_days[MAX_TOWNS][MAX_TOWNS][MAX_TOWNS][MAX_TOWNS];
// family in town(v) and family in town(u) go to town(z) in i days


void get_inputs() {
    cin >> towns_number >> roads_number;
    for (int i = 1; i <= towns_number; i++) {
        cin >> residency_cost[i];
    }
    for (int i = 1; i <= towns_number; i++) {
        for (int j = 1; j <= towns_number; j++) {
            if (i == j) {
                adjacent_matrix_road_cost[i][j] = residency_cost[i];
                adjacent_list_roads[i].push_back(j);
            } else {
                adjacent_matrix_road_cost[i][j] = -1;
            }
        }
    }
    for (int i = 0; i < roads_number; i++) {
        int s, t, cost;
        cin >> s >> t >> cost;
        adjacent_matrix_road_cost[s][t] = cost + residency_cost[t];
        adjacent_matrix_road_cost[t][s] = cost + residency_cost[s];
        adjacent_list_roads[s].push_back(t);
        adjacent_list_roads[t].push_back(s);
    }
}

void preprocess_shortest_path_cost_in_specific_days() {
    for (int i = 1; i <= towns_number; i++) {
        for (int j = 1; j <= towns_number; j++) {
            for (int z = 0; z <= towns_number; z++) {
                shortest_path_cost_in_specific_days[i][j][z] = -1;
                next_town_for_shortest_path_in_specific_days[i][j][z] = -1;
            }
        }
    }
    for (int i = 1; i <= towns_number; i++) {
        for (int j = 1; j <= towns_number; j++) {
            if (i == j) {
                shortest_path_cost_in_specific_days[i][j][0] = 0;
            } else {
                shortest_path_cost_in_specific_days[i][j][0] = -1;
            }
            next_town_for_shortest_path_in_specific_days[i][j][0] = -1;
        }
    }

    for (int day = 1; day <= towns_number; day++) {
        for (int i = 1; i <= towns_number; i++) {
            for (int j = 1; j <= towns_number; j++) {
                long long int min_cost = INT32_MAX;
                int min_town = -1;
                vector<int> adjacent_list_road = adjacent_list_roads[j];
                for (int adjacent_road : adjacent_list_road) {
                    long long int temp = shortest_path_cost_in_specific_days[i][adjacent_road][day - 1];
                    if (temp != -1 && (temp + adjacent_matrix_road_cost[adjacent_road][j] < min_cost)) {
                        min_cost = temp + adjacent_matrix_road_cost[adjacent_road][j];
                        min_town = adjacent_road;
                    }
                }
                min_cost = min_cost == INT32_MAX ? -1 : min_cost;
                shortest_path_cost_in_specific_days[i][j][day] = min_cost;
                if (min_cost == -1) {
                    next_town_for_shortest_path_in_specific_days[i][j][day] = -1;
                } else {
                    if (next_town_for_shortest_path_in_specific_days[i][min_town][day - 1] == -1) {
                        next_town_for_shortest_path_in_specific_days[i][j][day] = j;
                    } else {
                        next_town_for_shortest_path_in_specific_days[i][j][day] =
                                next_town_for_shortest_path_in_specific_days[i][min_town][day - 1];
                    }
                }
            }
        }
    }
}

void preprocess_meeting_cost_in_specific_town_days() {
    for (int i = 1; i <= towns_number; i++) {
        for (int j = 1; j <= towns_number; j++) {
            for (int z = 1; z <= towns_number; z++) {
                for (int day = 0; day <= towns_number; day++) {
                    long long int temp1 = shortest_path_cost_in_specific_days[i][z][day];
                    long long int temp2 = shortest_path_cost_in_specific_days[j][z][day];
                    if (temp1 == -1 || temp2 == -1) {
                        meeting_cost_in_specific_town_days[i][j][z][day] = -1;
                    } else {
                        meeting_cost_in_specific_town_days[i][j][z][day] = temp1 + temp2;
                    }
                }
            }
        }
    }
}

int main() {
    get_inputs();
    preprocess_shortest_path_cost_in_specific_days();
    preprocess_meeting_cost_in_specific_town_days();
}