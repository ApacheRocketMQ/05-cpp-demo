#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <thread>
#include <DefaultMQProducer.h>
#include <MQMessage.h>

using namespace rocketmq;
using namespace std;

int main(int argc, char *argv[]) {
    string namesrv_addr = "127.0.0.1:9876";
    string topic = "tigerweili_topic_01";

    if (argc >= 2) {
        namesrv_addr = argv[1];
    }
    string producer_group_name = "tiger_producer_group_01";
    
    DefaultMQProducer producer(producer_group_name);
    producer.setNamesrvAddr(namesrv_addr);
    producer.start();

    MQMessage msg(topic, "*", "Hi RocketMQ"); 
    SendResult sendResult = producer.send(msg, false);
    
    std::cout << namesrv_addr << endl;

    std::cout << sendResult.getMsgId();

    producer.shutdown();

    return 0;
}