#include<bits/stdc++.h>
using namespace std;

struct State {
    int a, b, c;
};

bool operator<(const State& x, const State& y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

bool visited[11][11][11];
map<State, vector<State>> graph;

void bfs(State start) {
    queue<State> q;
    q.push(start);
    visited[start.a][start.b][start.c] = true;

    while (!q.empty()) {
        State u = q.front(); q.pop();

        vector<State> nextStates;
        if (u.a > 0) {
            if (u.b < 7) nextStates.push_back({ max(0, u.a - (7 - u.b)), min(7, u.b + u.a), u.c });
            if (u.c < 4) nextStates.push_back({ max(0, u.a - (4 - u.c)), u.b, min(4, u.c + u.a) });
        }
        if (u.b > 0) {
            if (u.a < 10) nextStates.push_back({ min(10, u.a + u.b), max(0, u.b - (10 - u.a)), u.c });
            if (u.c < 4) nextStates.push_back({ u.a, max(0, u.b - (4 - u.c)), min(4, u.c + u.b) });
        }
        if (u.c > 0) {
            if (u.a < 10) nextStates.push_back({ min(10, u.a + u.c), u.b, max(0, u.c - (10 - u.a)) });
            if (u.b < 7) nextStates.push_back({ u.a, min(7, u.b + u.c), max(0, u.c - (7 - u.b)) });
        }

        for (auto& v : nextStates) {
            if (!visited[v.a][v.b][v.c]) {
                visited[v.a][v.b][v.c] = true;
                graph[u].push_back(v);
                q.push(v);
            }
        }
    }
}

int main() {
    memset(visited, false, sizeof(visited));
    bfs({0, 7, 4});
    cout << "digraph {\n";
    for (auto& node : graph) {
        for (auto& child : node.second) {
            cout << "  " << node.first.a << node.first.b << node.first.c << " -> " << child.a << child.b << child.c << ";\n";
            cout << "  " << node.first.a << node.first.b << node.first.c << " [label=\"" << node.first.a << "," << node.first.b << "," << node.first.c << "\"];\n";
            cout << "  " << child.a << child.b << child.c << " [label=\"" << child.a << "," << child.b << "," << child.c << "\"];\n";
        }
    }
    cout << "}\n";
    return 0;
}