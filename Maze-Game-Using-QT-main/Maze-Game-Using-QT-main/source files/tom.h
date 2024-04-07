#ifndef TOM_H
#define TOM_H
#include<QTimer>
#include<vector>
const int INF = 99999;
const int N = 93;

#include <QGraphicsPixmapItem>
class jerry;
class tom :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int row, column;
    int jerryRow, jerryColumn;
    int data[15][15];
    int adjacencyMatrix[93][93];
    jerry * jerryPointer;
    int jerryPos;
    int tomPos;

public:
    tom(int boardData[15][15],jerry* jry);
    QTimer timerTom;
    QVector<int> Dijkstra(int Graph[N][N], int tomPos,int jerryPos);



public slots:
    void move();
};


#endif // TOM_H
