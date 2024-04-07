#include "token.h"

token::token(int i, int j)
{
    // Set Image
    QPixmap powerImage("token.png");
    powerImage = powerImage.scaledToWidth(30);
    powerImage = powerImage.scaledToHeight(30);
    setPixmap(powerImage);

    // Set Position
    setPos(70 + j * 44, 70 + i * 44);

}
