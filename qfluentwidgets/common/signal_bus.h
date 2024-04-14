#pragma once

#include <QtCore/QObject>

class SignalBus : public QObject{
    Q_OBJECT
public:
    static SignalBus* getInstance();

private:
    SignalBus(QObject *parent) : QObject(parent){};
    SignalBus(const SignalBus&) = delete;
    SignalBus& operator=(const SignalBus&) = delete;
    static SignalBus* instance;
signals:
    
    void switchToSampleCard(QString, int);
    void micaEnableChanged(bool);
    void supportSignal();
};


static SignalBus *signalBus = SignalBus::getInstance();