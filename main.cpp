#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <thread>
#include <DefaultMQProducer.h>
#include <MQMessage.h>
#include <MQMessageListener.h>
#include <DefaultMQPushConsumer.h>

using namespace rocketmq;
using namespace std;

class RocketMQListener : public MessageListenerConcurrently
{
public:
    RocketMQListener() {}
    virtual ~RocketMQListener() {}

    virtual ConsumeStatus consumeMessage(const vector<MQMessageExt> &msgs)
    {
        for (size_t i = 0; i < msgs.size(); ++i)
        {
            cout << "消费消息body: " << msgs[i].getBody() << endl;
        }
        return CONSUME_SUCCESS;
    }
};

int consumer_demo(string namesrv_addr, string topic)
{
    RocketMQListener msglistener;
    string consumer_group_name = "tiger_consumer_group_01";
    DefaultMQPushConsumer consumer(consumer_group_name);

    consumer.setNamesrvAddr(namesrv_addr);
    consumer.subscribe(topic, "*");
    consumer.registerMessageListener(&msglistener);

    try
    {
        consumer.start();
    }
    catch (MQClientException &e)
    {
        cout << e << endl;
    }

    sleep(100000);
    return 0;
}

int producer_demo(string namesrv_addr, string topic)
{
    string producer_group_name = "tiger_producer_group_01";

    DefaultMQProducer producer(producer_group_name);
    producer.setNamesrvAddr(namesrv_addr);
    producer.start();

    MQMessage msg(topic, "*", "Hi RocketMQ");
    SendResult sendResult = producer.send(msg, false);

    cout << "发送消息成功：" << sendResult.getMsgId() << endl;

    producer.shutdown();

    return 0;
}

int main(int argc, char *argv[])
{
    string namesrv_addr = "127.0.0.1:9876";
    if (argc >= 2)
    {
        namesrv_addr = argv[1];
    }

    cout << "namesrv地址:" << namesrv_addr << endl;
    string topic = "tigerweili_topic_01";

    producer_demo(namesrv_addr, topic);

    consumer_demo(namesrv_addr, topic);
}
