#pragma once

#pragma execution_character_set("utf-8")
#include <QCoreApplication>
#include <QDebug>
#include <QMetaObject>
#include <QObject>

class BaseWorker : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
};

class SubWorker : public BaseWorker
{
    // 故意不写 Q_OBJECT
public:
    using BaseWorker::BaseWorker;
    void onTriggered() { qDebug() << "[C] SubWorker::onTriggered called"; }
};

// 场景 1：有 Q_OBJECT，但方法未加 Q_INVOKABLE / slots
class WorkerWithMacro : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
    void normalFunc() { qDebug() << "normalFunc called"; }
    Q_INVOKABLE void invokableFunc() { qDebug() << "invokableFunc called"; }
};

// 场景 2：完全没有 Q_OBJECT
class WorkerNoMacro : public QObject
{
public:
    using QObject::QObject;
    void plainFunc() { qDebug() << "[No Q_OBJECT] plainFunc called via functor invokeMethod"; }
};