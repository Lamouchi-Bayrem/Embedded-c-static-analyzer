#ifndef FINDING_H
#define FINDING_H
#include <QJsonObject>
#include <QString>
struct Finding {
    QString severity{"Info"}; QString engine; QString rule; QString file;
    int line{0}; int column{0}; QString message; QString status{"Open"};
    QString fingerprint() const;
    QJsonObject toJson() const;
};
inline QString Finding::fingerprint() const { return file+":"+QString::number(line)+":"+QString::number(column)+":"+rule+":"+message.left(80); }
inline QJsonObject Finding::toJson() const { return {{"severity",severity},{"engine",engine},{"rule",rule},{"file",file},{"line",line},{"column",column},{"message",message},{"status",status}}; }
#endif
