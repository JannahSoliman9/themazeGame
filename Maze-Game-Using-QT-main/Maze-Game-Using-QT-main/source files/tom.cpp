#include "tom.h"
#include <QtGlobal>
#include <QTimer>
#include "tom.h"
#include "jerry.h"
#include<QDebug>


tom::tom(int boardData[15][15],jerry* jry)
{
    // Set Image
    QPixmap tomImage("tomimage.png");
    tomImage = tomImage.scaledToWidth(44);
    tomImage = tomImage.scaledToHeight(44);
    setPixmap(tomImage);

    jerryPointer=jry;
    // Set Position
    row = 13;
    column = 7;
    setPos(70 + column * 44, 70 + row * 44);
    for (int i = 0; i < 15; i++)
       { for (int j = 0; j < 15; j++)
            data[i][j] = boardData[i][j];
       }

    timerTom.start(200);
    connect(&timerTom,SIGNAL(timeout()),this,SLOT(move()));

    for (int i = 0; i < 93; i++) // initializing matrix to zero
        {
            for (int j = 0; j < 93; j++)
            {
                adjacencyMatrix[i][j] = 0;
            }
        }

    for (int i = 0; i < 15; i++)
       {
           for (int j = 0; j < 15; j++)
           {
               int node = data[i][j];
               if (node != -1 && node != 53 && node != 54 && node != 92 && node != 52) // avoid putting home as adjacent nodes
               {
                   if (i != 0 && data[i-1][j] != -1 && data[i-1][j] != 52 && data[i-1][j] != 53 &&
                           data[i-1][j] != 92 && data[i-1][j] != 54&& data[i-1][j] != 89&& data[i-1][j] != 51&&
                           data[i-1][j] != 1 && data[i-1][j] != 88&& data[i-1][j] != 91) // row up
                   {
                       int x=data[i-1][j];
                       adjacencyMatrix[node][x] = 1;

                   }
                   if (j != 13 && data[i][j+1] != -1 && data[i][j+1] != 52 && data[i][j+1] != 53 && data[i][j+1] != 92 && data[i][j+1] != 54
                           && data[i][j+1] != 89&& data[i][j+1] != 51&& data[i][j+1] != 1 && data[i][j+1] != 88&&data[i][j+1] != 91) // column right
                   {
                     int x= data[i][j+1];
                     if(adjacencyMatrix[x][node] !=1)
                       {
                       adjacencyMatrix[node][data[i][j + 1]] = 1;
                      adjacencyMatrix[x][node]=1;
                       }
                   }
                   if (i != 13 && data[i+1][j] != -1 && data[i+1][j] != 52 && data[i+1][j] != 053 && data[i+1][j] != 92
                           && data[i+1][j] != 54 && data[i+1][j] != 89&& data[i+1][j] != 51&& data[i+1][j] != 1 && data[i+1][j] != 88&& data[i+1][j] != 91) //row down
                   {
                     int x= data[i+1][j];
                     if(adjacencyMatrix[x][node] !=1)
                       {
                         adjacencyMatrix[node][data[i + 1][j]] = 1;
                        adjacencyMatrix[x][node]=1;
                       }
                   }
                   if (j != 0 && data[i][j-1] != -1 && data[i][j-1] != 52 && data[i][j-1] != 53 && data[i][j-1] != 92 && data[i][j-1] != 54
                           && data[i][j-1] != 89&& data[i][j-1] != 51&& data[i][j-1] != 1 && data[i][j-1] != 88&&data[i][j-1] != 91) //column left
                   {
                    int x= data[i][j-1];
                    if(adjacencyMatrix[x][node] !=1)
                       {
                           adjacencyMatrix[node][data[i][j-1]] = 1;
                           adjacencyMatrix[x][node]=1;
                       }
                   }
               }
           }

    }
}


void tom::move()
{
    jerryRow=jerryPointer->getRow();
    jerryColumn=jerryPointer->getColumn();
    jerryPos=data[jerryRow][jerryColumn];
    tomPos=data[row][column];

    if (jerryPos != 89 && jerryPos != 051 && jerryPos != 92 && jerryPos != 54 && jerryPos != 53 && jerryPos != 88 && jerryPos != 1 && jerryPos != 52
            && jerryPos != 91) //tom doesnt move when jerry is in home
      {

                QVector<int> path = Dijkstra(adjacencyMatrix, tomPos, jerryPos);


                if (path.size() >= 2)
                {
                    int movement = path.at(1);
                    // controlling tom's movement and limiting jerry's home

                    if (data[row - 1][column] == movement && data[row - 1][column] != -1 && data[row][column] != 76)
                    {
                        row--;
                    }
                    else if (data[row + 1][column] == movement && data[row + 1][column] != -1 && data[row][column] != 65)
                    {
                       row++;
                    }
                    else if (data[row][column+1] == movement && data[row][column+1] != -1 && data[row][column] != 79)
                    {
                        column++;
                        QPixmap image("tomimage.png");
                        image = image.scaledToWidth(44);
                        image = image.scaledToHeight(44);               //flipping image direction change
                        setPixmap(image);
                        setPos(70 + column * 44, 70 + row * 44);

                    }
                    else if (data[row][column-1] == movement && data[row][column-1] != -1 && data[row][column] != 67)
                    {
                        column--;
                        QPixmap image("tomimage.png");
                        image = image.scaledToWidth(44);
                        image = image.scaledToHeight(44);               //flipping image direction change
                        QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
                        setPixmap(reflectedimage);
                        setPos(70 + column * 44, 70 + row * 44);

                    }
                }
    //}
     setPos(70 + column * 44, 70 + row * 44);
     QList<QGraphicsItem*> items = collidingItems();
        for (int i = 0; i < items.size(); i++)
        {
            if (typeid(*items[i]) == typeid(jerry))  // tom collision with jerry
            {

                jerry* jerrypointer= dynamic_cast<jerry*>(items[i]);
                if(jerryPointer->powerStatus()==false)
                {
                jerrypointer->setlives(jerrypointer->getlives()-1);
                jerrypointer->setLivesText();
                jerrypointer->setRowColumn(7,7);
                jerrypointer->setJerryPixmap();

                if(jerrypointer->getCheeseStatus())
                    {
                       scene()->addItem(jerrypointer->getCheesePointer());
                       jerrypointer->setCheeseStatus(0);
                       jerrypointer->setCheesePointer(NULL);
                        if(jerrypointer->getlives() == 0)
                        {
                            timerTom.stop();
                        }
                }
               }
            }

     }
    }

}

QVector<int> tom::Dijkstra(int Graph[N][N], int tomPos,int jerryPos)
{
    int temp[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Graph[i][j] == 0)
                temp[i][j] = INF;
            else
                temp[i][j] = Graph[i][j];
        }
    }

    bool visited[N];
    int previous[N];
    float cost[N];
    // 1st Row:
    for (int i = 0; i < N; i++)
    {
        if (i == tomPos)
        {
            previous[i] = -1;
            cost[i] = 0;
            visited[i] = true;
        }
        else
        {
            previous[i] = tomPos;
            cost[i] = temp[tomPos][i]; // 0 or 1
            visited[i] = false;
        }
    }

    int count = 1;
    while (count < N)
    {
        // FIND VERTEX TO VISIT WITH LOWEST COST
        int minimum = INF;
        int vertexV;
        for (int i = 0; i < N; i++)
        {
            if (visited[i] == false && cost[i] < minimum)
            {
                minimum = cost[i];
                vertexV = i;
            }
        }
        // Visit the vertex.
        visited[vertexV] = true;

        // Check whether there are shorter paths.
        for (int i = 0; i < N; i++)
        {
            if (visited[i] == false)
            {
                int calcValue = cost[vertexV] + temp[vertexV][i];
                if (calcValue < cost[i])
                {
                    cost[i] = calcValue;
                    previous[i] = vertexV;

                }
            }
        }
        count++;
    }
    // return paths only for efficiency.
    QVector<QVector<int>> paths;
    paths.resize(N);
    int j;
    for (int i = 0; i < N; i++)
    {
        paths[i].push_back(i);
        j = i;
        while (j != tomPos)
        {
                j = previous[j];
                paths[i].insert(paths[i].begin(), j);
        }
    }
    return paths[jerryPos];
}
