#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QPixmap>
#include <QVector>

class SpriteSheet
{
public:
    SpriteSheet();

    QPixmap getSpriteAt(int index) { return sprites.at(index); }
    int spriteCount() { return sprites.size(); }
    int spriteWidth() { return sw; }
    int spriteHeight() { return sh; }

private:
    QVector<QPixmap> sprites;
    int sw;
    int sh;
};

#endif // SPRITESHEET_H
