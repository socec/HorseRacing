#include <spritesheet.h>

SpriteSheet::SpriteSheet(QString filename, int rows, int columns)
{
    // initializing resources in a library
    Q_INIT_RESOURCE(images);

    // load sprite sheet
    QPixmap sheet(":/images/" + filename);

    // get sprite dimensions
    spriteWidth = sheet.width() / columns;
    spriteHeight = sheet.height() / rows;

    // extract sprites, assuming correct order is to right then down
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            QPixmap sprite = sheet.copy(j*spriteWidth, i*spriteHeight, spriteWidth, spriteHeight);
            sprites.append(sprite);
        }
    }
}
