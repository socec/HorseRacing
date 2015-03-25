#include "spritesheet.h"

SpriteSheet::SpriteSheet()
{
    // load sprite sheet
    QPixmap sheet(":/images/muybridge_spritesheet.png", "PNG");

    // used sprite sheet has 4x4 sprites
    sw = sheet.width() / 4;
    sh = sheet.height() / 4;

    // extract sprites
    for(int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++ ) {
            // pick out sprite from the sheet
            QPixmap sprite = sheet.copy(j*sw, i*sh, sw, sh);
            sprites.append(sprite);
        }
}
