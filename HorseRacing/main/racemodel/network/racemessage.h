#ifndef RACEMESSAGE_H
#define RACEMESSAGE_H

#include <QByteArray>
#include <QVector>

/**
 * @brief Messages shared between server and clients.
 */
class RaceMessage
{
public:
    /**
     * @brief Creates a message with horse and camera positions.
     * @param horsePositions - Current horse positions.
     * @param cameraPosition - Current camera position.
     * @return Created message.
     */
    static QByteArray createPositions(const QVector<float>& horsePositions,
                                      const float& cameraPosition);
    /**
     * @brief Parses the message with horse and camera positions.
     * @param message - Received message.
     * @param horsePositions - Reference to horse positions that will be updated.
     * @param cameraPosition - Reference to camera position that will be updated.
     */
    static void parsePositions(const QByteArray& message,
                               QVector<float>& horsePositions,
                               float& cameraPosition);
};

#endif // RACEMESSAGE_H
