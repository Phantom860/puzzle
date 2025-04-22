#include "puzzlesolver.h"
#include <QQueue>
#include <QSet>
#include <QMap>
#include <QStack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <QPoint>

PuzzleSolver::PuzzleSolver(QObject *parent) : QObject(parent) {}

//solveBFS
QList<QVector<QVector<int>>> PuzzleSolver::solveBFS(const QVector<QVector<int>> &start, const QVector<QVector<int>> &goal) {
    QQueue<Node> queue;
    QSet<QString> visited;

    Node root;
    root.state = start;
    root.path.append(start);
    queue.enqueue(root);
    visited.insert(stateToString(start));

    while (!queue.isEmpty()) {
        Node current = queue.dequeue();

        if (current.state == goal) {
            return current.path;
        }

        for (auto &neighbor : getNeighbors(current.state)) {
            QString key = stateToString(neighbor);
            if (!visited.contains(key)) {
                visited.insert(key);
                Node next;
                next.state = neighbor;
                next.path = current.path;
                next.path.append(neighbor);
                queue.enqueue(next);
            }
        }
    }

    return {};
}

QString PuzzleSolver::stateToString(const QVector<QVector<int>> &state) {
    QString s;
    for (const auto &row : state) {
        for (int val : row) {
            s += QString::number(val);
        }
    }
    return s;
}

QVector<QVector<QVector<int>>> PuzzleSolver::getNeighbors(const QVector<QVector<int>> &state) {
    QVector<QVector<QVector<int>>> neighbors;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    int x, y;

    // 找到空格（0）
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (state[i][j] == 0) {
                x = i; y = j;
            }

    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            QVector<QVector<int>> newState = state;
            std::swap(newState[x][y], newState[nx][ny]);
            neighbors.push_back(newState);
        }
    }

    return neighbors;
}

//solveWithDFS
// 判断逆序数是否一致（拼图是否有解）
int PuzzleSolver::getInversionCount(const QVector<QVector<int>>& state) const {
    QVector<int> flat;
    for (const auto& row : state)
        for (int val : row)
            if (val != 0) flat.append(val);  // 忽略0

    int inv = 0;
    for (int i = 0; i < flat.size(); ++i) {
        for (int j = i + 1; j < flat.size(); ++j) {
            if (flat[i] > flat[j]) ++inv;
        }
    }
    return inv;
}

bool PuzzleSolver::isSolvable(const QVector<QVector<int>>& start, const QVector<QVector<int>>& goal) const {
    return getInversionCount(start) % 2 == getInversionCount(goal) % 2;
}

// 非递归 DFS 实现
QList<QVector<QVector<int>>> PuzzleSolver::solveWithDFS(QVector<QVector<int>> startState, QVector<QVector<int>> goalState) {
    QList<QVector<QVector<int>>> path;

    if (!isSolvable(startState, goalState)) return path;

    QSet<QString> visited;
    QMap<QString, QVector<QVector<int>>> parent;
    QStack<QVector<QVector<int>>> stack;

    stack.push(startState);
    visited.insert(hashState(startState));

    while (!stack.isEmpty()) {
        QVector<QVector<int>> current = stack.pop();

        if (current == goalState) {
            QString hash = hashState(current);
            while (parent.contains(hash)) {
                path.push_front(current);
                current = parent[hash];
                hash = hashState(current);
            }
            path.push_front(startState);
            return path;
        }

        auto neighbors = getNeighbors(current);
        for (const auto& neighbor : neighbors) {
            QString nh = hashState(neighbor);
            if (!visited.contains(nh)) {
                visited.insert(nh);
                parent[nh] = current;
                stack.push(neighbor);
            }
        }
    }

    return {}; // 无解
}

// 哈希状态
QString PuzzleSolver::hashState(const QVector<QVector<int>>& state) const {
    QString result;
    for (const auto& row : state) {
        for (int val : row) {
            result += QString::number(val);
        }
    }
    return result;
}


//BFS (Best-First-Search)
QList<QVector<QVector<int>>> PuzzleSolver::solveWithBestFS(QVector<QVector<int>> startState, QVector<QVector<int>> goalState) {
    QList<QVector<QVector<int>>> path;

    if (!isSolvable(startState, goalState)) return path;

    std::unordered_set<QString> visited;
    std::unordered_map<QString, QVector<QVector<int>>> parent;

    struct StateNode {
        QVector<QVector<int>> state;
        int heuristic;
    };

    // 自定义比较函数：小的 heuristic 优先
    auto cmp = [](const StateNode& a, const StateNode& b) {
        return a.heuristic > b.heuristic;
    };

    std::priority_queue<StateNode, std::vector<StateNode>, decltype(cmp)> openList(cmp);
    openList.push({ startState, manhattanDistance(startState, goalState) });

    visited.insert(hashState(startState));

    while (!openList.empty()) {
        StateNode current = openList.top();
        openList.pop();

        if (current.state == goalState) {
            QString hash = hashState(current.state);
            while (parent.count(hash)) {
                path.push_front(current.state);
                current.state = parent[hash];
                hash = hashState(current.state);
            }
            path.push_front(startState);
            return path;
        }

        auto neighbors = getNeighbors(current.state);
        for (const auto& neighbor : neighbors) {
            QString nh = hashState(neighbor);
            if (!visited.count(nh)) {
                visited.insert(nh);
                parent[nh] = current.state;
                int h = manhattanDistance(neighbor, goalState);
                openList.push({ neighbor, h });
            }
        }
    }

    return {};  // 无解
}

int PuzzleSolver::manhattanDistance(const QVector<QVector<int>>& state, const QVector<QVector<int>>& goal) const {
    QMap<int, QPoint> goalPos;
    for (int i = 0; i < goal.size(); ++i) {
        for (int j = 0; j < goal[i].size(); ++j) {
            goalPos[goal[i][j]] = QPoint(i, j);
        }
    }

    int distance = 0;
    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state[i].size(); ++j) {
            int val = state[i][j];
            if (val == 0) continue;
            QPoint goalP = goalPos[val];
            distance += abs(i - goalP.x()) + abs(j - goalP.y());
        }
    }
    return distance;
}


//(Brunch-And-Bound)
QList<QVector<QVector<int>>> PuzzleSolver::solveWithBnB(QVector<QVector<int>> startState, QVector<QVector<int>> goalState) {
    QList<QVector<QVector<int>>> path;
    if (!isSolvable(startState, goalState)) return path;

    QSet<QString> visited;
    QMap<QString, QVector<QVector<int>>> parent;
    QMap<QString, int> gCost;

    struct StateNode {
        QVector<QVector<int>> state;
        int g; // 当前路径代价
        int h; // 估价函数
        bool operator>(const StateNode& other) const {
            return (g + h) > (other.g + other.h);
        }
    };

    auto cmp = [](const StateNode &a, const StateNode &b) { return a > b; };
    std::priority_queue<StateNode, std::vector<StateNode>, decltype(cmp)> openList(cmp);

    QString startHash = hashState(startState);
    openList.push({ startState, 0, manhattanDistance(startState, goalState) });
    gCost[startHash] = 0;

    while (!openList.empty()) {
        auto current = openList.top();
        openList.pop();

        QString curHash = hashState(current.state);
        if (visited.contains(curHash)) continue;
        visited.insert(curHash);

        if (current.state == goalState) {
            // 回溯路径
            path.push_front(current.state);
            while (parent.contains(curHash)) {
                current.state = parent[curHash];
                curHash = hashState(current.state);
                path.push_front(current.state);
            }
            return path;
        }

        auto neighbors = getNeighbors(current.state);
        for (const auto& neighbor : neighbors) {
            QString nh = hashState(neighbor);
            int newG = current.g + 1;
            if (!gCost.contains(nh) || newG < gCost[nh]) {
                gCost[nh] = newG;
                parent[nh] = current.state;
                int h = manhattanDistance(neighbor, goalState);
                openList.push({ neighbor, newG, h });
            }
        }
    }

    return {}; // 无解
}
