#ifndef JERRY_H
#define JERRY_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include "cheese.h"
#include<QTimer>
#include"tom.h"
#include <QGraphicsTextItem>
#include <QMediaPlayer>




class jerry : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int row, column;
    int data[15][15];
    int lives=3;
    bool hasCheese=false;
    bool powerActive;
    QTimer powerTimer;
    cheese *cheesePointer;
    int cheeseCounter=0;
    int tokenCounter=0;
    QGraphicsTextItem livesScreen;
    QGraphicsTextItem modeScreen;
    QGraphicsTextItem tokenScreen;
    QGraphicsTextItem winningText;
    QGraphicsTextItem losingText;
    void homeWithCheese();
    bool insideHome();
    void win();
    void lose();
    QMediaPlayer * sound= new QMediaPlayer();


public:
    jerry(int boardData[15][15],QGraphicsScene* scene);
    void tomCollision();
    void setlives(int n);
    int  getlives();
    void setCheesePointer(cheese *pointer);
    void setRowColumn(int x, int y);
    void setJerryPixmap();
    void setLivesText();
    void setTokenText();
    int  getRow();
    int  getColumn();
    bool getCheeseStatus();
    bool setCheeseStatus(int n);
    cheese* getCheesePointer();
    bool powerStatus();


public slots:
    void keyPressEvent(QKeyEvent* event);
    void deactivate();
};
#endif // JERRY_H


