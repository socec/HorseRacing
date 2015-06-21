#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QPixmap>
#include <QVector>

/**
 * @brief Sprite sheet used in horse animation.
 */
class SpriteSheet {
public:
    /**
     * @brief Class constructor.
     */
    SpriteSheet();

    /**
     * @brief Returns the sprite at the given index in the spritesheet.
     * @param index - Index of the sprite in the spritesheet.
     * @return Requested sprite as QPixmap.
     */
    QPixmap getSpriteAt(int index) const { return sprites.at(index); }

    /**
     * @brief Returns the number of sprites in the spritesheet.
     * @return Number of sprites.
     */
    int getSpriteCount() const { return sprites.size(); }

    /**
     * @brief Returns the width of a sprite in the spritesheet.
     * @return Sprite width.
     */
    int getSpriteWidth() const { return spriteWidth; }

    /**
     * @brief Returns the height of a sprite in the spritesheet.
     * @return Sprite height.
     */
    int getSpriteHeight() const { return spriteHeight; }

private:
    QVector<QPixmap> sprites;
    int spriteWidth;
    int spriteHeight;
};

#endif // SPRITESHEET_H
