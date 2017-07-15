#include <QDebug>
#include <QTextStream>

void Debug()
{
    //qInfo is qt5.5+ only.
    qInfo() << "C++ Style Info Message";
    qInfo( "C Style Info Message" );

    qDebug() << "C++ Style Debug Message";
    qDebug( "C Style Debug Message" );

    qWarning() << "C++ Style Warning Message";
    qWarning( "C Style Warning Message" );

    qCritical() << "C++ Style Critical Error Message";
    qCritical( "C Style Critical Error Message" );

    // qFatal does not have a C++ style method.
    qFatal( "C Style Fatal Error Message" );

    qDebug ("message %d, says: %s",'1','2');
}

static inline QDebug operator<<(QDebug dbg, const std::string& str)
{
    dbg.nospace() << QString::fromStdString(str);
    return dbg.space();
}
