#include "jerry.h"
#include"power.h"
#include"cheese.h"
#include"token.h"
#include<QTimer>
#include <QDebug>

jerry::jerry(int boardData[15][15],QGraphicsScene* scene)
{
    //jerry: Set Image and position
    row = 7;
    column = 7;
    setJerryPixmap();



    // Set data Array
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            data[i][j] = boardData[i][j];
    connect(&powerTimer,SIGNAL(timeout()),this,SLOT(deactivate()));

    QFont* f = new QFont;
        f->setPointSize(15);
        f->setBold(true);

    setLivesText();                                          // lives text
    livesScreen.setDefaultTextColor(QColor(255, 255, 0, 225));
    livesScreen.setX(50);
    livesScreen.setY(15);
    livesScreen.setFont(*f);
    livesScreen.adjustSize();
    scene->addItem(&livesScreen);

    modeScreen.setPlainText("Mode: Normal");                   // mode text
    modeScreen.setDefaultTextColor(QColor(255, 255, 0, 225));
    modeScreen.setX(500);
    modeScreen.setY(15);
    modeScreen.setFont(*f);
    modeScreen.adjustSize();
    scene->addItem(&modeScreen);

    tokenScreen.setPlainText("Tokens: 0");                   // mode text
    tokenScreen.setDefaultTextColor(QColor(255, 255, 0, 225));
    tokenScreen.setX(250);
    tokenScreen.setY(15);
    tokenScreen.setFont(*f);
    tokenScreen.adjustSize();
    scene->addItem(&tokenScreen);
}
void jerry::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up && data[row - 1][column] >= 0)
    {
       if(hasCheese==true &&  data[row][column] == data[9][7])
        {
          homeWithCheese();
        }
       row--;

    }
    else if (event->key() == Qt::Key_Down && data[row + 1][column] >= 0)
    {
        if(hasCheese==true && data[row][column] == data[5][8] )
         {
           homeWithCheese();
         }
        row++;


    }
    else if (event->key() == Qt::Key_Right && data[row][column + 1] >= 0)
    {
        if(hasCheese==true && data[row][column] == data[7][5] )
         {
           homeWithCheese();
         }
        column++;


    }
    else if (event->key() == Qt::Key_Left && data[row][column - 1] >= 0)
    {
        if(hasCheese==true && data[row][column] == data[7][9] )
         {
           homeWithCheese();
         }
        column--;

    }
    setPos(70 + column * 44, 70 + row * 44);

    QList<QGraphicsItem*> items = collidingItems();
    for (int i = 0; i < items.size(); i++)
    {
        if (typeid(*items[i]) == typeid(cheese))
        {
            if (hasCheese==false)
            {
             if (insideHome()== false)
             {
                scene()->removeItem(items[i]);
                QPixmap jerryCheeseImage("jerrycheeseimage.png");
                jerryCheeseImage = jerryCheeseImage.scaledToWidth(44);
                jerryCheeseImage = jerryCheeseImage.scaledToHeight(44);
                setPixmap(jerryCheeseImage);
                hasCheese=true;
                cheesePointer= dynamic_cast<cheese*>(items[i]);
             }
            }
        }
        if (typeid(*items[i]) == typeid(power))
        {
            scene()->removeItem(items[i]);
            powerTimer.start(5000);
            powerActive = true;
            modeScreen.setPlainText("Mode:Power");

        }
        if (typeid(*items[i]) == typeid(tom))
        {
            if(powerActive==false)
            {
                tomCollision();
            }
        }
        if (typeid(*items[i]) == typeid(token))
        {
            scene()->removeItem(items[i]);
            tokenCounter++;
            setTokenText();
            sound->setMedia(QUrl("qrc:/sounds/coinSound.wav"));
            sound->play();

            if(tokenCounter==3 || tokenCounter==6)
            {
                setlives(getlives()+1);
                setLivesText();
             }


        }

    }
}
void jerry::deactivate()
{
    powerActive = false;
    modeScreen.setPlainText("Mode: Normal");
    powerTimer.stop();
}
void jerry:: homeWithCheese()
{
    if(cheeseCounter==0)
    {
     (*cheesePointer).setPos(70 + 8 * 44, 70 + 8 * 44);
     scene()->addItem(cheesePointer);
     cheeseCounter++;
     hasCheese= false;
     setJerryPixmap();
     sound->setMedia(QUrl("qrc:/sounds/wohoSound.mp3"));;
     sound->play();
    }
    else if(cheeseCounter==1)
    {
        (*cheesePointer).setPos(70 + 8 * 44, 70 + 6 * 44);
        scene()->addItem(cheesePointer);
        cheeseCounter++;
        hasCheese= false;
        setJerryPixmap();
        sound->setMedia(QUrl("qrc:/sounds/wohoSound.mp3"));
        sound->play();
    }
    else if(cheeseCounter==2)
    {
        (*cheesePointer).setPos(70+ 6*44,70+8*44);
        scene()->addItem(cheesePointer);
        cheeseCounter++;
        hasCheese= false;
        setJerryPixmap();
        sound->setMedia(QUrl("qrc:/sounds/wohoSound.mp3"));
        sound->play();
    }
    else if(cheeseCounter==3)
    {
        (*cheesePointer).setPos(70 + 6 * 44, 70 + 6 * 44);
        scene()->addItem(cheesePointer);
        hasCheese= false;
        setJerryPixmap();
        win();
        sound->setMedia(QUrl("qrc:/sounds/wohoSound.mp3"));
        sound->play();
    }
}
bool jerry:: insideHome()
{
    if( data[row][column] == data[8][8] ||  data[row][column] == data[6][6] ||  data[row][column] == data[8][6] ||  data[row][column] == data[6][8] ||data[row][column] == data[7][6] ||data[row][column] == data[8][7] ||data[row][column] == data[6][7]   )
        return true;
    else
        return false;
}
void jerry::setLivesText()
{
    if (lives==3)
         {livesScreen.setPlainText("LIVES= 3");}
    else if(lives==2)
         {livesScreen.setPlainText("LIVES= 2");}
    else if(lives==4)
         {livesScreen.setPlainText("LIVES= 4");}
    else if(lives==5)
         {livesScreen.setPlainText("LIVES= 5");}
    else if(lives==1)
         {livesScreen.setPlainText("LIVES= 1");}
    else if(lives==0)
        {
        livesScreen.setPlainText("LIVES= 0");
        lose();
        }
}
void jerry::win()
{
    QFont* f = new QFont;
    f->setPointSize(60);
    f->setBold(true);
    winningText.setPlainText("YOU WIN!!");
    winningText.setTextWidth(600);
    winningText.setDefaultTextColor(QColor(Qt::white));
    winningText.setX(80);
    winningText.setY(350);
    winningText.setFont(*f);
    winningText.adjustSize();
    scene()->addItem(&winningText);

}
void jerry::lose()
{
    QFont* f = new QFont;
    f->setPointSize(60);
    f->setBold(true);
    losingText.setPlainText("GAME OVER!");
    losingText.setTextWidth(600);
    losingText.setDefaultTextColor(QColor(Qt::white));
    losingText.setX(80);
    losingText.setY(350);
    losingText.setFont(*f);
    losingText.adjustSize();
    scene()->addItem(&losingText);

}
void jerry::tomCollision()
{
    row=7;
    column=7;
    setJerryPixmap();
    lives --;
    setLivesText();

  if(hasCheese==true)
        {
           scene()->addItem(cheesePointer);
           hasCheese=false;
           cheesePointer=NULL;
        }
}
void jerry::setlives(int n)
{
    lives=n;
}
int jerry::getlives()
{
    return lives;
}

bool jerry::getCheeseStatus()
{
     return hasCheese;
}
bool jerry::setCheeseStatus(int n)
{
     if (n==0)
         hasCheese=false;
     else if (n==1)
         hasCheese=true;
}
cheese* jerry::getCheesePointer()
{
     return cheesePointer;
}
void jerry::setCheesePointer(cheese *pointer)
{
     cheesePointer=pointer;
}
void jerry:: setRowColumn(int x, int y)
{
     row = x;
     column = y;
}
void jerry::setJerryPixmap()
{
    QPixmap jerryImage("jerry.png");
    jerryImage = jerryImage.scaledToWidth(20);
    jerryImage = jerryImage.scaledToHeight(20);
    setPixmap(jerryImage);
    setPos(70 + column * 44, 70 + row * 44);
}
int jerry::getRow()
{
    return row;
}
int jerry::getColumn()
{
    return column;
}

void jerry::setTokenText()
{
    if (tokenCounter==1)
         {tokenScreen.setPlainText("TOKEN: 1");}
    else if(tokenCounter==2)
         {tokenScreen.setPlainText("TOKEN: 2");}
    else if(tokenCounter==3)
         {tokenScreen.setPlainText("TOKEN: 3");}
    else if(tokenCounter==4)
        {tokenScreen.setPlainText("TOKEN: 4");}
    else if(tokenCounter==5)
         {tokenScreen.setPlainText("TOKEN: 5");}
    else if(tokenCounter==6)
         {tokenScreen.setPlainText("TOKEN: 6");}
}
bool jerry::powerStatus()
{
    return powerActive;
}
