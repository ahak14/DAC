#include <bits/stdc++.h>

using namespace std;

const int MAX_TOWNS = 100 + 1;

int towns_number;
int roads_number;
int residency_town_cost[6];

int families_town[MAX_TOWNS];
// town of families on time
int min_town_cost;
int meeting_number = 0;
// number of meeting so far
bool did_meet[MAX_TOWNS][MAX_TOWNS];
// did i meet j in j?

void get_inputs() {
    cin >> towns_number >> roads_number;
    for (int i = 1; i <= towns_number; i++) {
        cin >> residency_town_cost[i];
        families_town[i] = i;
    }
}

void find_min_town_cost() {
    int min_cost = INT32_MAX;
    for (int i = 1; i <= towns_number; i++) {
        if (residency_town_cost[i] < min_cost) {
            min_cost = residency_town_cost[i];
            min_town_cost = i;
        }
    }
}

vector<pair<pair<int, int>, pair<int, int> > > handle_a_day(int day) {
    vector<pair<pair<int, int>, pair<int, int> > > day_plan;
    bool fixed_plan[MAX_TOWNS];
    fill(fixed_plan, fixed_plan + MAX_TOWNS, false);
    for (int i = 1; i <= towns_number; i++) {
        if (fixed_plan[i]) {
            continue;
        }
        for (int j = 1; j <= towns_number; j++) {
            if (i == j || fixed_plan[j] || did_meet[i][j]) {
                continue;
            }
            if (families_town[i] != j)
                day_plan.push_back({{1, day}, {i, j}});
            if (families_town[j] != j)
                day_plan.push_back({{1, day}, {j, j}});
            families_town[i] = j;
            families_town[j] = j;
            fixed_plan[i] = true;
            fixed_plan[j] = true;
            did_meet[i][j] = true;
            day_plan.push_back({{2, day}, {i, j}});
            meeting_number++;
            break;
        }
    }
    for (int i = 1; i <= towns_number; i++) {
        if (!fixed_plan[i]) {
            day_plan.push_back({{1, day}, {i, min_town_cost}});
            break;
        }
    }
    return day_plan;
}

vector<pair<pair<int, int>, pair<int, int> > > start() {
    vector<pair<pair<int, int>, pair<int, int> > > plans;
    int max_meeting = towns_number  * (towns_number - 1);
    int day = 0;
    while (meeting_number != max_meeting) {
        day++;
        vector<pair<pair<int, int>, pair<int, int> > > day_plan = handle_a_day(day);
        for (auto plan : day_plan) {
            plans.push_back(plan);
        }
    }
    return plans;
}

int main() {
    get_inputs();
    find_min_town_cost();
    vector<pair<pair<int, int>, pair<int, int> > > plans = start();
    cout << plans.size() << endl;
    for (auto & plan : plans) {
        cout << plan.first.first << " " << plan.first.second << " " << plan.second.first << " " << plan.second.second << endl;
    }
}