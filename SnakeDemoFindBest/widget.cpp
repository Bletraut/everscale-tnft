#include "widget.h"
#include "ui_widget.h"

#include <QString>
#include <QFIle>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene();
    for(int i = 0; i < 50; i++)
    {
        std::vector<QSquare*> vs;
        for(int j = 0; j < 50; j++)
        {
            vs.push_back(new QSquare);
        }
        m_square.push_back(vs);
    }

    m_scene->setSceneRect(0,0,500,500);

    ui->graphicsView->setScene(m_scene);
    for(size_t i = 0; i < 50; i++)
    {
        for(size_t j = 0; j < 50; j++)
        {
            m_scene->addItem(m_square[i][j]);
            m_square[i][j]->setPos((i * 10), (j * 10));
            m_square[i][j]->m_show = true;
        }
    }

    m_corn.x = 0;
    m_corn.y = 0;

    m_keyDownS = new QShortcut(this);
    m_keyDownS->setKey(Qt::Key_S);

    m_keyUpW = new QShortcut(this);
    m_keyUpW->setKey(Qt::Key_W);

    m_keyLeftA = new QShortcut(this);
    m_keyLeftA->setKey(Qt::Key_A);

    m_keyRightD = new QShortcut(this);
    m_keyRightD->setKey(Qt::Key_D);

    connect(m_keyDownS, SIGNAL(activated()), ui->radioButton_down_2, SLOT(click()));
    connect(m_keyUpW, SIGNAL(activated()), ui->radioButton_up_2, SLOT(click()));
    connect(m_keyLeftA, SIGNAL(activated()), ui->radioButton_left_2, SLOT(click()));
    connect(m_keyRightD, SIGNAL(activated()), ui->radioButton_right_2, SLOT(click()));

    m_keyDown = new QShortcut(this);
    m_keyDown->setKey(Qt::Key_Down);

    m_keyUp = new QShortcut(this);
    m_keyUp->setKey(Qt::Key_Up);

    m_keyLeft = new QShortcut(this);
    m_keyLeft->setKey(Qt::Key_Left);

    m_keyRight = new QShortcut(this);
    m_keyRight->setKey(Qt::Key_Right);

    connect(m_keyDown, SIGNAL(activated()), ui->radioButton_down, SLOT(click()));
    connect(m_keyUp, SIGNAL(activated()), ui->radioButton_up, SLOT(click()));
    connect(m_keyLeft, SIGNAL(activated()), ui->radioButton_left, SLOT(click()));
    connect(m_keyRight, SIGNAL(activated()), ui->radioButton_right, SLOT(click()));

    m_train = false;

    m_walls = ui->checkBoxBorder->isChecked();
    QTimer::singleShot(100, this, SLOT(do_step()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeLine(QString str)
{
    ui->textEdit->append(str);
}

void Widget::do_train()
{
    std::vector<uint8_t> firstIn;
    std::vector<uint8_t> secondIn;

    std::vector<uint8_t> firstOut;
    std::vector<uint8_t> secondOut;

    firstOut.push_back(0);
    firstOut.push_back(0);
    firstOut.push_back(0);
    firstOut.push_back(0);

    secondOut = firstOut;

    for(size_t i = 0; i < m_square.size(); i++)
    {
        for(size_t j = 0; j < m_square[i].size(); j++)
        {
            firstIn.push_back(1);
        }
    }

    std::queue<pixel> snake;

    snake = m_snake.m_snake;
    while(!snake.empty())
    {
        if(snake.front().x + (snake.front().y * m_square[0].size()) < firstIn.size())
            firstIn[snake.front().x + (snake.front().y * m_square[0].size())] = 0;
        snake.pop();
    }

    snake = m_snakeEnemy.m_snake;
    while(!snake.empty())
    {
        if(snake.front().x + (snake.front().y * m_square[0].size()) < firstIn.size())
            firstIn[snake.front().x + (snake.front().y * m_square[0].size())] = 0;
       snake.pop();
    }

    firstIn[m_corn.x + (m_corn.y * m_square[0].size())] = 0;

    for(size_t i = 0; i < 256; i++)
    {
        m_bot.doStep(firstIn,firstOut);
        m_botEnemy.doStep(secondIn,secondOut);
    }

    for(size_t i = 0; i < m_square.size(); i++)
    {
        for(size_t j = 0; j < m_square[i].size(); j++)
        {
            if(m_square[i][j]->m_show)
                m_square[i][j]->show();
        }
    }

    snake = m_snake.m_snake;

    while(!snake.empty())
    {
        if(snake.front().y < 50)
            m_square[snake.front().x][snake.front().y]->hide();
        snake.pop();
    }

    snake = m_snakeEnemy.m_snake;

    while(!snake.empty())
    {
       if(snake.front().y < 50)
            m_square[snake.front().x][snake.front().y]->hide();
       snake.pop();
    }

    if(m_corn.y < 50)
        m_square[m_corn.x][m_corn.y]->hide();

    bool b = false;

    if(m_bot.m_reg[0] % 2 == 0)
        b = m_snake.step(&m_snakeEnemy, 0,-1, m_square.size(),m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    else if(m_bot.m_reg[1] % 2 == 0)
        b = m_snake.step(&m_snakeEnemy, 0,1, m_square.size(), m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    else if(m_bot.m_reg[2] % 2 == 0)
        b = m_snake.step(&m_snakeEnemy, -1,0, m_square.size(),m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    else /*if(m_bot.m_reg[3] % 2 == 0)*/
        b = m_snake.step(&m_snakeEnemy, 1,0, m_square.size(), m_square[0].size(), m_corn.x ,m_corn.y, m_walls);

    if(b)
    {
        m_corn.x = std::rand() % m_square.size();
        m_corn.y = std::rand() % m_square[0].size();
    }

    if(m_botEnemy.m_reg[0] % 2 == 0)
        b = m_snakeEnemy.step(&m_snake, 0,-1, m_square.size(),m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    else if(m_botEnemy.m_reg[0] % 2 == 0)
        b = m_snakeEnemy.step(&m_snake, 0,1, m_square.size(), m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    else if(m_botEnemy.m_reg[0] % 2 == 0)
        b = m_snakeEnemy.step(&m_snake, -1,0, m_square.size(),m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    else /*if(m_botEnemy.m_reg[0] % 2 == 0)*/
        b = m_snakeEnemy.step(&m_snake, 1,0, m_square.size(), m_square[0].size(), m_corn.x ,m_corn.y, m_walls);

    if(b)
    {
        m_corn.x = std::rand() % m_square.size();
        m_corn.y = std::rand() % m_square[0].size();
    }

//    ui->textEdit->append(QString::number((int)firstOut[0]) + QString::number((int)firstOut[1]) + QString::number((int)firstOut[2]) + QString::number((int)firstOut[0]));
//    ui->textEdit->append(QString::number(m_bot.m_reg[0]) + QString::number(m_bot.m_reg[1]) + QString::number(m_bot.m_reg[2]) + QString::number(m_bot.m_reg[3]));

//    QString str;
//    str.push_back("Size =");
//    str.push_back(QString::number(m_snake.m_snake.size()));
//    str.push_back(" Die = ");
//    str.push_back(QString::number(m_snake.m_die));

    if(!m_train)
        QTimer::singleShot(100, this, SLOT(do_step()));
    else
    {
        QTimer::singleShot(10, this, SLOT(do_train()));
    }

}

void Widget::do_step()
{
    for(size_t i = 0; i < m_square.size(); i++)
    {
        for(size_t j = 0; j < m_square[i].size(); j++)
        {
            if(m_square[i][j]->m_show)
                m_square[i][j]->show();
        }
    }

    std::queue<pixel> snake;
    snake = m_snake.m_snake;

    while(!snake.empty())
    {
       m_square[snake.front().x][snake.front().y]->hide();
       snake.pop();
    }

    snake = m_snakeEnemy.m_snake;

    while(!snake.empty())
    {
       m_square[snake.front().x][snake.front().y]->hide();
       snake.pop();
    }

    m_square[m_corn.x][m_corn.y]->hide();

    bool b = false;

    if(ui->radioButton_up->isChecked())
        b = m_snake.step(&m_snakeEnemy, 0,-1, m_square.size(),m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    if(ui->radioButton_down->isChecked())
        b = m_snake.step(&m_snakeEnemy, 0,1, m_square.size(), m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    if(ui->radioButton_left->isChecked())
        b = m_snake.step(&m_snakeEnemy, -1,0, m_square.size(),m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    if(ui->radioButton_right->isChecked())
        b = m_snake.step(&m_snakeEnemy, 1,0, m_square.size(), m_square[0].size(), m_corn.x ,m_corn.y, m_walls);

    if(b)
    {
        m_corn.x = std::rand() % m_square.size();
        m_corn.y = std::rand() % m_square[0].size();
    }

    if(ui->radioButton_up_2->isChecked())
        b = m_snakeEnemy.step(&m_snake, 0,-1, m_square.size(),m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    if(ui->radioButton_down_2->isChecked())
        b = m_snakeEnemy.step(&m_snake, 0,1, m_square.size(), m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    if(ui->radioButton_left_2->isChecked())
        b = m_snakeEnemy.step(&m_snake, -1,0, m_square.size(),m_square[0].size(), m_corn.x ,m_corn.y, m_walls);
    if(ui->radioButton_right_2->isChecked())
        b = m_snakeEnemy.step(&m_snake, 1,0, m_square.size(), m_square[0].size(), m_corn.x ,m_corn.y, m_walls);

    if(b)
    {
        m_corn.x = std::rand() % m_square.size();
        m_corn.y = std::rand() % m_square[0].size();
    }

    QString str;
    str.push_back("Size =");
    str.push_back(QString::number(m_snake.m_snake.size()));
    str.push_back(" Die = ");
    str.push_back(QString::number(m_snake.m_die));

    ui->label->setText(str);

    if(!m_train)
        QTimer::singleShot(100, this, SLOT(do_step()));
    else
    {
        QTimer::singleShot(100, this, SLOT(do_train()));
    }
}


void Widget::on_checkBoxBorder_clicked()
{
     m_walls = ui->checkBoxBorder->isChecked();
}

void Widget::on_pushButtonStart_clicked()
{
    ui->pushButtonStart->setEnabled(false);
    m_train = true;
}

void Widget::on_pushButtonStop_clicked()
{
    ui->pushButtonStart->setEnabled(true);
    m_train = false;
}

void Widget::on_pushButtonRand_clicked()
{
    m_bot.randMe();
    m_botEnemy.randMe();
}

void Widget::on_pushButtonSave_clicked()
{
    QFile f("gen1");
    f.open(QIODevice::WriteOnly);
    f.write(reinterpret_cast<char*>(m_bot.m_gen),sizeof(m_bot.m_gen[0]) * 256);
    f.close();

    QFile f1("gen2");
    f1.open(QIODevice::WriteOnly);
    f1.write(reinterpret_cast<char*>(m_botEnemy.m_gen),sizeof(m_botEnemy.m_gen[0]) * 256);
    f1.close();

    ui->textEdit->append("save!!!");

}

void Widget::on_pushButtonLoad_clicked()
{
    GenBot t_b;
    m_bot = t_b;
    m_botEnemy = t_b;

    QFile f("gen1");
    f.open(QIODevice::ReadOnly);
    f.read(reinterpret_cast<char*>(m_bot.m_gen),sizeof(m_bot.m_gen[0]) * 256);
    f.close();

    QFile f1("gen2");
    f1.open(QIODevice::ReadOnly);
    f1.read(reinterpret_cast<char*>(m_botEnemy.m_gen),sizeof(m_botEnemy.m_gen[0]) * 256);
    f1.close();

    ui->textEdit->append("readed!!!");
}
