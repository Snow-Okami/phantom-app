#ifndef CUSTOMEVENTS_H
#define CUSTOMEVENTS_H

#include <QObject>
#include <QWebSocket>
#include <QDebug>
#include <QEvent>

// Login Response event identifier
const QEvent::Type LOGIN_RESPONSE_EVENT = static_cast<QEvent::Type>(QEvent::User + 1);

// Login Response event subclass
class LoginResponseEvent : public QEvent
{
    public:
        LoginResponseEvent(const bool success, const QString response):
            QEvent(LOGIN_RESPONSE_EVENT),
            m_success(success),
            m_response(response)
        {
        }

        bool GetSuccess() const
        {
            return m_success;
        }

        QString GetResponse() const
        {
            return m_response;
        }

    private:
        bool m_success;
        QString m_response;
};

// Define your custom event identifier
const QEvent::Type MY_CUSTOM_EVENT = static_cast<QEvent::Type>(QEvent::User + 1);

// Define your custom event subclass
class MyCustomEvent : public QEvent
{
    public:
        MyCustomEvent(const int customData1, const int customData2):
            QEvent(MY_CUSTOM_EVENT),
            m_customData1(customData1),
            m_customData2(customData2)
        {
        }

        int getCustomData1() const
        {
            return m_customData1;
        }

        int getCustomData2() const
        {
            return m_customData2;
        }

    private:
        int m_customData1;
        int m_customData2;
};

#endif // CUSTOMEVENTS_H
