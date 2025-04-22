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
                    // tileButtons[index]->setStyleSheet("background-color: red; color: white;");

                    // // 动画：放大再还原
                    // QPropertyAnimation *anim = new QPropertyAnimation(btn, "geometry");
                    // QRect startRect = btn->geometry();
                    // QRect bigRect = startRect.adjusted(-5, -5, 5, 5);  // 放大

                    // anim->setDuration(300);
                    // anim->setKeyValueAt(0, startRect);
                    // anim->setKeyValueAt(0.5, bigRect);
                    // anim->setKeyValueAt(1, startRect);
                    // anim->setEasingCurve(QEasingCurve::OutBack);
                    // anim->start(QAbstractAnimation::DeleteWhenStopped);
                }
            }
        }
    }
}


void Widget::updatePuzzleUI() {
    QFont tileFont;
    tileFont.setPointSize(20);       // 设置字体大小
    tileFont.setBold(true);          // 设置加粗
    tileFont.setFamily("阿里妈妈东方大楷");     // 设置字体（可改为你喜欢的）

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int index = i * 3 + j;
            QPushButton *btn = tileButtons[index];

            btn->setFont(tileFont);

            if (puzzle[i][j] == 0) {
                btn->setText("");
                btn->setStyleSheet("background-color: lightgray;");
            } else {
                btn->setText(QString::number(puzzle[i][j]));
                btn->setStyleSheet("background-color: white;");
            }
        }
    }
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

void Widget::animateTileSlide(int fromRow, int fromCol, int toRow, int toCol, int value)
{
    tileButtons[fromRow * 3 + fromCol]->setText("");
    tileButtons[fromRow * 3 + fromCol]->setStyleSheet("background-color: lightgray;");

    // 获取起始按钮的位置和大小
    QWidget *fromBtn = tileButtons[fromRow * 3 + fromCol];
    QRect startRect = fromBtn->geometry();
    QPoint startGlobal = fromBtn->mapTo(this, QPoint(0, 0));

    QWidget *toBtn = tileButtons[toRow * 3 + toCol];
    QRect endRect = toBtn->geometry();
    QPoint endGlobal = toBtn->mapTo(this, QPoint(0, 0));

    // 创建一个浮动的动画按钮
    QPushButton *floatBtn = new QPushButton(QString::number(value), this);
    floatBtn->setGeometry(QRect(startGlobal, startRect.size()));
    floatBtn->setStyleSheet("background-color: orange; font-weight: bold; border-radius: 10px;");
    floatBtn->show();
    floatBtn->raise();

    // 动画滑动过去
    QPropertyAnimation *anim = new QPropertyAnimation(floatBtn, "pos");
    anim->setDuration(300);
    anim->setStartValue(startGlobal);
    anim->setEndValue(endGlobal);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    connect(anim, &QPropertyAnimation::finished, this, [=]() {
        floatBtn->deleteLater();  // 动画结束删除临时按钮
        updatePuzzleUI();         // 更新真实按钮布局
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::playAnimationPath(const QList<QVector<QVector<int>>> &path, int delayMs, const QString &finalMessage)
{
    if (path.isEmpty()) {
        ui->goalLabel->setText("No solution.");
        return;
    }

    int step = 0;

    // ✅ 正确停止已有动画
    if (animationTimer) {
        animationTimer->stop();
        animationTimer->deleteLater();
        animationTimer = nullptr;
    }

    isAnimating = true;

    // ✅ 使用成员变量 animationTimer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, [=]() mutable {
        if (step >= path.size()) {
            animationTimer->stop();
            animationTimer->deleteLater();
            animationTimer = nullptr;
            isAnimating = false;
            ui->goalLabel->setText(finalMessage);
            return;
        }

        if (step > 0) {
            QVector<QVector<int>> prev = path[step - 1];
            QVector<QVector<int>> curr = path[step];

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (prev[i][j] != 0 && curr[i][j] == 0) {
                        int fromRow = i, fromCol = j;
                        for (int r = 0; r < 3; ++r) {
                            for (int c = 0; c < 3; ++c) {
                                if (curr[r][c] == prev[i][j]) {
                                    animateTileSlide(fromRow, fromCol, r, c, prev[i][j]);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }

        puzzle = path[step];
        step++;
    });

    animationTimer->start(delayMs); // ✅ 用 animationTimer 启动动画
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
    // 停止当前动画
    if (isAnimating) {
        // 如果动画正在进行，停止动画
        isAnimating = false;  // 标记为停止动画
        if (animationTimer) {
            animationTimer->stop();
            animationTimer->deleteLater();
            animationTimer = nullptr;
        }
    }
    initializePuzzle();
}
