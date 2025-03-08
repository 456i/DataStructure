#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Ориентированный граф (заданный вручную)
map<int, vector<int>> graph = {
    {1, {2, 4}},   // 1 → 2, 1 → 4
    {2, {3}},      // 2 → 3
    {4, {5}},      // 4 → 5
    {5, {3}},      // 5 → 3
    {3, {}}        // 3 → (нет исходящих рёбер)
};

// Функция для поиска пути с использованием DFS
bool findPath(int current, int end, vector<int>& path, vector<bool>& visited) {
    path.push_back(current);
    if (current == end) return true; // Если дошли до цели, путь найден

    visited[current] = true;
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (findPath(neighbor, end, path, visited)) return true;
        }
    }

    path.pop_back(); // Откатываемся назад, если путь не найден
    return false;
}

int main() {
    int start = 1, end = 3; // Задаём стартовую и конечную вершины
    vector<int> path;
    vector<bool> visited(6, false); // Массив посещённых вершин (макс. вершина = 5)

    if (findPath(start, end, path, visited)) {
        cout << "Path found: ";
        for (int node : path) cout << node << " ";
        cout << endl;
    }
    else {
        cout << "No path exists from " << start << " to " << end << endl;
    }

    return 0;
}