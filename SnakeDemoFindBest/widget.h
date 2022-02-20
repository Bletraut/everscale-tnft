#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

#include "qsquare.h"
#include "qsnake.h"
#include "genbot.h"

#include <QTimer>
#include <QShortcut>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void writeLine(QString str);

private slots:
    void do_train();
    void do_step();
    void on_checkBoxBorder_clicked();
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonRand_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonLoad_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene *m_scene;
    std::vector<std::vector<QSquare*>> m_square;

    QSnake m_snake;
    QSnake m_snakeEnemy;

    GenBot m_bot;
    GenBot m_botEnemy;

    pixel m_corn;

//    QArea m_area;
    bool m_walls;

    QShortcut *m_keyUp;
    QShortcut *m_keyDown;
    QShortcut *m_keyLeft;
    QShortcut *m_keyRight;

    QShortcut *m_keyUpW;
    QShortcut *m_keyDownS;
    QShortcut *m_keyLeftA;
    QShortcut *m_keyRightD;

    bool m_train;
};

#endif // WIDGET_H
