#include "cheese.h"

cheese::cheese(int i, int j)
{
    // Set Image
    QPixmap cheeseImage("cheese.png");
    cheeseImage = cheeseImage.scaledToWidth(44);
    cheeseImage = cheeseImage.scaledToHeight(44);
    setPixmap(cheeseImage);

    // Set Position
    setPos(70 + j * 44, 70 + i * 44);
}

