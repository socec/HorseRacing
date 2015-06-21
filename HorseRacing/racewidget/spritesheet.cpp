#include "spritesheet.h"

SpriteSheet::SpriteSheet() {
    // load sprite sheet
    QPixmap sheet(":/images/muybridge_spritesheet.png", "PNG");

    // used sprite sheet has 4x4 sprites
    spriteWidth = sheet.width() / 4;
    spriteHeight = sheet.height() / 4;

    // extract sprites in correct order, to right then down
    for(int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++ ) {
            QPixmap sprite = sheet.copy(j*spriteWidth, i*spriteHeight, spriteWidth, spriteHeight);
            sprites.append(sprite);
        }
}
