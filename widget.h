#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <queue>
#include <unordered_set>
#include <QPropertyAnimation>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void updatePuzzleUI(const QPoint &highlight);
    void animateTileSlide(int fromRow, int fromCol, int toRow, int toCol, int value);
private slots:
    void on_initButton_clicked();
    void on_runButton_clicked();
    void handleTileClick();
    bool checkSolution();

private:
    Ui::Widget *ui;
    QVector<QVector<int>> puzzle;
    QVector<QPushButton*> tileButtons;
    QVector<QVector<int>> goalState;
    QTimer *animationTimer = nullptr;

    int emptyRow, emptyCol;
    int steps;
    bool isAnimating = false;

    void initializePuzzle();
    void updatePuzzleUI();
    void shufflePuzzle();
    void resetGame();
    void playAnimationPath(const QList<QVector<QVector<int>>> &path, int delayMs, const QString &finalMessage);


};

#endif // WIDGET_H
