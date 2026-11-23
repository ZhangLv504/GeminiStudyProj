#ifndef GEMINISTUDYPROJ__1_ANYSCDATACHANNEL_H
#define GEMINISTUDYPROJ__1_ANYSCDATACHANNEL_H

#include <QObject>
#include <QObject>
#include <vector>
#include <utility>

// 1. 非模板基类：负责挂载 Q_OBJECT，只发无参通知信号
class AsyncChannelBase : public QObject
{
    Q_OBJECT
public:
    explicit AsyncChannelBase(QObject* parent = nullptr) : QObject(parent) {}

signals:
    void dataReady(); // 仅做事件通知，不耦合具体类型 T

protected:
    // 由子类在合适的时机触发，避免外部随意 emit
    void notifyDataReady()
    {
        emit dataReady();
    }
};


// 2. 模板子类：不加 Q_OBJECT，负责泛型存储与强类型接口
template <typename T>
class AsyncChannel : public AsyncChannelBase
{
public:
    using AsyncChannelBase::AsyncChannelBase;

    void pushData(std::vector<T> data)
    {
        m_buffer.insert(m_buffer.end(),
                        std::make_move_iterator(data.begin()),
                        std::make_move_iterator(data.end()));
        notifyDataReady();
    }

    std::vector<T> takeAll()
    {
        std::vector<T> out;
        out.swap(m_buffer);
        return out;
    }

private:
    std::vector<T> m_buffer;
};

#endif //GEMINISTUDYPROJ__1_ANYSCDATACHANNEL_H
