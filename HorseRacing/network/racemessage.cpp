#include "racemessage.h"

QByteArray RaceMessage::createPositions(const QVector<float>& horsePositions, const float& cameraPosition)
{
    QByteArray message;
    // pack horse data
    for (int i = 0; i < horsePositions.size(); i++)
    {
        message.append("H" + QString::number((double) horsePositions.at(i), 'f', 2));
    }
    // pack camera data
    message.append("C" + QString::number((double) cameraPosition, 'f', 2));
    return message;
}

void RaceMessage::parsePositions(const QByteArray &message, QVector<float>& horsePositions, float& cameraPosition)
{
    // extract camera data
    QStringList split1 = QString::fromUtf8(message).split("C", QString::SkipEmptyParts);
    cameraPosition = split1.at(1).toFloat();
    // extract horses data
    QStringList split2 = split1.at(0).split("H", QString::SkipEmptyParts);
    for (int i = 0; i < split2.size(); i++)
    {
        horsePositions.replace(i, split2.at(i).toFloat());
    }
}
