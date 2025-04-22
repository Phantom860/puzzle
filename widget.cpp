#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <algorithm>

#include "puzzlesolver.h"
#include <QElapsedTimer>
#include <QTimer>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始化拼图按钮
    tileButtons = {
        ui->pushButton_1, ui->pushButton_2, ui->pushButton_3,
        ui->pushButton_4, ui->pushButton_5, ui->pushButton_6,
        ui->pushButton_7, ui->pushButton_8, ui->pushButton_9
    };

    // 连接按钮点击信号
    for (QPushButton* button : tileButtons) {
        connect(button, &QPushButton::clicked, this, &Widget::handleTileClick);
    }

    // 初始化游戏
    goalState = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}  // 0表示空白格
    };

    resetGame();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resetGame()
{
    puzzle = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    emptyRow = 2;
    emptyCol = 2;
    steps = 0;
    updatePuzzleUI();
}

void Widget::initializePuzzle()
{
    shufflePuzzle();
    steps = 0;
    ui->timeLabel->setText("Time(s): 0");
    ui->stepsLabel->setText("Steps: 0");
    ui->goalLabel->setText("(No) Goal node");
}

void Widget::shufflePuzzle()
{
    // 随机打乱拼图
    QVector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    std::random_shuffle(nums.begin(), nums.end());

    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        puzzle[row][col] = nums[i];
        if (nums[i] == 0) {
            emptyRow = row;
            emptyCol = col;
        }
    }
    updatePuzzleUI();
}

#include <QPropertyAnimation>

void Widget::updatePuzzleUI(const QPoint &highlight)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int index = i * 3 + j;
            QPushButton *btn = tileButtons[index];

            if (puzzle[i][j] == 0) {
                btn->setText("");
                btn->setStyleSheet("background-color: lightgray;");
            } else {
                btn->setText(QString::number(puzzle[i][j]));

                btn->setStyleSheet("background-color: white;");

                if (highlight == QPoint(i, j)) {
                    tileButtons[index]->setStyleSheet("background-color: red; color: white;");

                    // 动画：放大再还原
                    QPropertyAnimation *anim = new QPropertyAnimation(btn, "geometry");
                    QRect startRect = btn->geometry();
                    QRect bigRect = startRect.adjusted(-5, -5, 5, 5);  // 放大

                    anim->setDuration(300);
                    anim->setKeyValueAt(0, startRect);
                    anim->setKeyValueAt(0.5, bigRect);
                    anim->setKeyValueAt(1, startRect);
                    anim->setEasingCurve(QEasingCurve::OutBack);
                    anim->start(QAbstractAnimation::DeleteWhenStopped);
                }
            }
        }
    }
}


void Widget::updatePuzzleUI() {
    updatePuzzleUI(QPoint(-1, -1));  // 默认无高亮
}

void Widget::handleTileClick()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    int index = tileButtons.indexOf(clickedButton);
    int row = index / 3;
    int col = index % 3;

    // 检查点击的方块是否与空白格相邻
    if ((abs(row - emptyRow) == 1 && col == emptyCol) ||
        (abs(col - emptyCol) == 1 && row == emptyRow)) {
        // 移动方块
        std::swap(puzzle[row][col], puzzle[emptyRow][emptyCol]);
        emptyRow = row;
        emptyCol = col;
        steps++;
        ui->stepsLabel->setText("Steps: " + QString::number(steps));
        updatePuzzleUI();

        // 检查是否完成
        if (checkSolution()) {
            ui->goalLabel->setText("Goal node reached!");
            QMessageBox::information(this, "Congratulations", "You solved the puzzle!");
        }
    }
}

bool Widget::checkSolution()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] != goalState[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void Widget::playAnimationPath(const QList<QVector<QVector<int>>> &path, int delayMs, const QString &finalMessage)
{
    if (path.isEmpty()) {
        ui->goalLabel->setText("No solution.");
        return;
    }

    int step = 0;
    QTimer *timerAnim = new QTimer(this);
    connect(timerAnim, &QTimer::timeout, this, [=]() mutable {
        if (step >= path.size()) {
            timerAnim->stop();
            timerAnim->deleteLater();
            ui->goalLabel->setText(finalMessage);
            return;
        }

        QPoint changedPos(-1, -1);
        if (step > 0) {
            const auto &prev = path[step - 1];
            const auto &curr = path[step];
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (prev[i][j] != curr[i][j] && curr[i][j] != 0) {
                        changedPos = QPoint(i, j);  // 当前非空、即将出现的位置
                        break;
                    }
                }
            }
        }

        puzzle = path[step];
        updatePuzzleUI(changedPos);  // 传入高亮格子
        step++;
    });
    timerAnim->start(delayMs);
}


// runButton点击事件
void Widget::on_runButton_clicked()
{
    QString algorithm = ui->algorithmCombo->currentText();
    ui->timeLabel->setText("Time(s): 0");
    ui->stepsLabel->setText("Steps: 0");

    // BFS (Breadth-First-Search)
    if (algorithm == "BFS (Breadth-First-Search)") {
        ui->goalLabel->setText("Solving with BFS...");

        PuzzleSolver solver;
        QElapsedTimer timer;
        timer.start();

        QVector<QVector<int>> start = puzzle;
        QList<QVector<QVector<int>>> path = solver.solveBFS(start, goalState);

        qint64 timeUsed = timer.elapsed();
        ui->timeLabel->setText(QString("Time(s): %1").arg(timeUsed / 1000.0));
        ui->stepsLabel->setText(QString("Steps: %1").arg(path.size() - 1));

        playAnimationPath(path, 500, "Solved!");
    }

    //DFS (Depth-First-Search)
    if (algorithm == "DFS (Depth-First-Search)") {
        ui->goalLabel->setText("Solving with DFS...");

        PuzzleSolver solver;
        QElapsedTimer timer;
        timer.start();

        QVector<QVector<int>> start = puzzle;
        QList<QVector<QVector<int>>> path = solver.solveWithDFS(start, goalState);

        qint64 timeUsed = timer.elapsed();
        ui->timeLabel->setText(QString("Time(s): %1").arg(timeUsed / 1000.0));
        ui->stepsLabel->setText(QString("Steps: %1").arg(path.size() - 1));

        if (path.isEmpty()) {
            ui->goalLabel->setText("No solution.");
            return;
        }

        playAnimationPath(path, 500, "Solved!");
    }

    //BFS (Best-First-Search)
    if (algorithm == "BFS (Best-First-Search)") {
        ui->goalLabel->setText("Solving with Best-First Search...");

        PuzzleSolver solver;
        QElapsedTimer timer;
        timer.start();

        QVector<QVector<int>> start = puzzle;
        QList<QVector<QVector<int>>> path = solver.solveWithBestFS(start, goalState);

        qint64 timeUsed = timer.elapsed();
        ui->timeLabel->setText(QString("Time(s): %1").arg(timeUsed / 1000.0));
        ui->stepsLabel->setText(QString("Steps: %1").arg(path.size() - 1));

        if (path.isEmpty()) {
            ui->goalLabel->setText("No solution.");
            return;
        }

        playAnimationPath(path, 500, "Solved!");
    }

    //Brunch-And-Bound
    if (algorithm == "Branch-And-Bound") {
        ui->goalLabel->setText("Solving with Branch and Bound...");

        PuzzleSolver solver;
        QElapsedTimer timer;
        timer.start();

        QVector<QVector<int>> start = puzzle;
        QList<QVector<QVector<int>>> path = solver.solveWithBnB(start, goalState);

        qint64 timeUsed = timer.elapsed();
        ui->timeLabel->setText(QString("Time(s): %1").arg(timeUsed / 1000.0));
        ui->stepsLabel->setText(QString("Steps: %1").arg(path.size() - 1));

        if (path.isEmpty()) {
            ui->goalLabel->setText("No solution.");
            return;
        }

        playAnimationPath(path, 500, "Solved!");
    }

}


void Widget::on_initButton_clicked()
{
    initializePuzzle();
}
