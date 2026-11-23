#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QDebug>

#include "q1MetaAndMoc/AnyscDataChannel.h"
#include "q1MetaAndMoc/Worker.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ////////////////////////////// question1 start //////////////////////////////
    {
        qDebug() << "================== question1 start ==================";
        AsyncChannel<int> channel;
        QObject::connect(&channel, &AsyncChannelBase::dataReady, &channel, [&channel]() {
            auto items = channel.takeAll();
            qDebug() << "Received count:" << items.size() << "first:" << items.front();
        });
        channel.pushData({10, 20, 30});
        qDebug() << "======================================================";

    }

    {
        qDebug() << "======================================================";
        BaseWorker* ptr = new SubWorker(&app);
        // [A] 输出: BaseWorker
        qDebug() << "[A] className:" << ptr->metaObject()->className();
        // [B] 取消下面注释将直接触发 static_assert 编译报错
        // SubWorker* sub = qobject_cast<SubWorker*>(ptr);
        // [C] 正常编译并触发输出
        QObject::connect(ptr, &QObject::objectNameChanged,
                         static_cast<SubWorker*>(ptr), &SubWorker::onTriggered);
        ptr->setObjectName("test");
        // [D] 输出: false
        bool ok = QMetaObject::invokeMethod(ptr, "onTriggered");
        qDebug() << "[D] invokeMethod:" << ok;
        qDebug() << "======================================================";
    }

    {
        qDebug() << "======================================================";
        WorkerWithMacro w1(&app);
        // 1. 输出 false：有 Q_OBJECT 但方法未注册进元对象表
        qDebug() << "string invoke normalFunc:" << QMetaObject::invokeMethod(&w1, "normalFunc");
        // 2. 输出 true：有 Q_OBJECT 且标记了 Q_INVOKABLE
        qDebug() << "string invoke invokableFunc:" << QMetaObject::invokeMethod(&w1, "invokableFunc");

        WorkerNoMacro w2(&app);
        // 3. 输出 true：无 Q_OBJECT，但函数指针重载走纯 C++ 模板，不依赖 moc
        bool ok = QMetaObject::invokeMethod(&w2, &WorkerNoMacro::plainFunc);
        qDebug() << "functor invoke plainFunc:" << ok;
        qDebug() << "================== question1 end ====================";

    }

    ////////////////////////////// question1 end //////////////////////////////



    return app.exec();
}
