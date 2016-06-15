#include <racemessage.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QByteArray RaceMessage::createPositions(const QVector<float>& horsePositions,
                                        const float& cameraPosition)
{
    QJsonObject messageData;

    // pack horse data
    QJsonArray horses;
    for (int i = 0; i < horsePositions.size(); i++)
    {
        horses.append(QJsonValue(horsePositions.at(i)));
    }
    messageData.insert("horses", horses);

    // pack camera data
    QJsonValue camera(cameraPosition);
    messageData.insert("camera", camera);

    QJsonDocument messageDoc(messageData);

    return messageDoc.toBinaryData();
}

void RaceMessage::parsePositions(const QByteArray &message,
                                 QVector<float>& horsePositions,
                                 float& cameraPosition)
{
    QJsonDocument messageDoc = QJsonDocument::fromBinaryData(message);
    QJsonObject messageData = messageDoc.object();

    // extract horses data
    QJsonArray horses = messageData.take("horses").toArray();
    for (int i = 0; i < horsePositions.size(); i++)
    {
        horsePositions.replace(i, (float) horses.at(i).toDouble());
    }
    // extract camera data
    QJsonValue camera = messageData.take("camera");
    cameraPosition = (float) camera.toDouble();
}
