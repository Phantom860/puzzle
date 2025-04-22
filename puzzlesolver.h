#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QList>

struct Node {
    QVector<QVector<int>> state;
    QList<QVector<QVector<int>>> path;
};

class PuzzleSolver : public QObject {
    Q_OBJECT
public:
    explicit PuzzleSolver(QObject *parent = nullptr);
    QList<QVector<QVector<int>>> solveBFS(const QVector<QVector<int>> &start, const QVector<QVector<int>> &goal);
    QList<QVector<QVector<int>>> solveWithDFS(QVector<QVector<int>> startState, QVector<QVector<int>> goalState);

    QList<QVector<QVector<int> > > solveWithBestFS(QVector<QVector<int> > startState, QVector<QVector<int> > goalState);
    QList<QVector<QVector<int> > > solveWithBnB(QVector<QVector<int> > startState, QVector<QVector<int> > goalState);
private:
    bool isSolvable(const QVector<QVector<int>> &state);
    QVector<QVector<QVector<int>>> getNeighbors(const QVector<QVector<int>> &state);
    QString stateToString(const QVector<QVector<int>> &state);

    QString hashState(const QVector<QVector<int>>& state) const;
    int getInversionCount(const QVector<QVector<int> > &state) const;
    bool isSolvable(const QVector<QVector<int> > &start, const QVector<QVector<int> > &goal) const;
    int manhattanDistance(const QVector<QVector<int> > &state, const QVector<QVector<int> > &goal) const;
};

#endif // PUZZLESOLVER_H

