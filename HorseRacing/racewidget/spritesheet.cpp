#include "spritesheet.h"

SpriteSheet::SpriteSheet()
{
    // load sprite sheet
    QPixmap sheet(":/images/muybridge_spritesheet.png", "PNG");

    // sprite sheet used here has 4x4 sprites
    int spriteRows = 4;
    int spriteColumns = 4;

    spriteWidth = sheet.width() / spriteColumns;
    spriteHeight = sheet.height() / spriteRows;

    // extract sprites in correct order, to right then down
    for (int i = 0; i < spriteRows; i++)
    {
        for (int j = 0; j < spriteColumns; j++)
        {
            QPixmap sprite = sheet.copy(j*spriteWidth, i*spriteHeight, spriteWidth, spriteHeight);
            sprites.append(sprite);
        }
    }
}
