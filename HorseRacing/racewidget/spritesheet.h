#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QPixmap>
#include <QVector>

class SpriteSheet
{
public:
    SpriteSheet();

    QPixmap getSpriteAt(int index) const { return sprites.at(index); }
    int spriteCount() const { return sprites.size(); }
    int spriteWidth() const { return sw; }
    int spriteHeight() const { return sh; }

private:
    QVector<QPixmap> sprites;
    int sw;
    int sh;
};

#endif // SPRITESHEET_H
