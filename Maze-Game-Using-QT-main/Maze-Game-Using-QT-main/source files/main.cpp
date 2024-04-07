#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <iostream>

#include"cheese.h"
#include"jerry.h"
#include"power.h"
#include"tom.h"
#include"token.h"

using namespace std;

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene scene;

    view.setFixedSize(800, 800);
    view.setWindowTitle("Maze Game");
    QBrush brush(Qt::black);
    view.setBackgroundBrush(brush);

    QFile file("board.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);

    int boardData[15][15];
    QString temp;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }

    QPixmap sandImage("sand.jpg");
    sandImage = sandImage.scaledToWidth(44);
    sandImage = sandImage.scaledToHeight(44);

    QPixmap seaImage("sea.jpg");
    seaImage = seaImage.scaledToWidth(44);
    seaImage = seaImage.scaledToHeight(44);

    QPixmap houseImage("house.png");
    houseImage = houseImage.scaledToWidth(44);
    houseImage = houseImage.scaledToHeight(44);

    QGraphicsPixmapItem boardItems[15][15];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
        {
            // Set Image
            if (boardData[i][j] < 0)
                boardItems[i][j].setPixmap(seaImage);
            else
                boardItems[i][j].setPixmap(sandImage);

            // Set Position
            boardItems[i][j].setPos(70 + j * 44, 70 + i * 44);

            // Add to the Scene
            scene.addItem(&boardItems[i][j]);
        }

    boardItems[7][7].setPixmap(houseImage);
    boardItems[7][7].setPos(70 + 7 * 44, 70 + 7 * 44);
    scene.addItem(&boardItems[7][7]);
    cheese cheese1(1,1);
    cheese cheese2(1,13);
    cheese cheese3(13,1);
    cheese cheese4(13,13);
    scene.addItem(&cheese1);
    scene.addItem(&cheese2);
    scene.addItem(&cheese3);
    scene.addItem(&cheese4);


    jerry jerry1(boardData,&scene);
    scene.addItem(&jerry1);
    jerry1.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    jerry1.setFocus();

    tom tom1(boardData,&jerry1);
    scene.addItem(&tom1);

    power power1(10,6);
    power power2(3,11);
    scene.addItem(&power1);
    scene.addItem(&power2);

    token token1(3,5);
    token token2(13,4);
    token token3(6,13);
    token token4(1,8);
    token token5(8,10);
    token token6(9,1);
    scene.addItem(&token1);
    scene.addItem(&token2);
    scene.addItem(&token3);
    scene.addItem(&token4);
    scene.addItem(&token5);
    scene.addItem(&token6);

    scene.addItem(&power1);
    scene.addItem(&power2);
    view.setScene(&scene);
    view.show();
    return a.exec();

}
