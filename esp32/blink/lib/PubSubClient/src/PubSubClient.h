#ifndef PubSubClient_h
#define PubSubClient_h

#include <Arduino.h>
#include <Client.h>

#define MQTT_MAX_PACKET_SIZE 256
#define MQTT_KEEPALIVE 15

class PubSubClient {
public:
    PubSubClient();
    PubSubClient(Client& client);

    PubSubClient& setServer(const char* domain, uint16_t port);
    PubSubClient& setCallback(void (*callback)(char*, uint8_t*, unsigned int));

    boolean connect(const char* id);
    boolean connect(const char* id, const char* user, const char* pass);
    void disconnect();
    boolean connected();
    int state();

    boolean publish(const char* topic, const char* payload);
    boolean subscribe(const char* topic);
    boolean loop();

private:
    Client* _client;
    const char* _domain;
    uint16_t _port;
    void (*_callback)(char*, uint8_t*, unsigned int);
    uint32_t _lastActivity;
    boolean _connected;

    boolean connectMQTT(const char* id, const char* user, const char* pass,
                        const char* willTopic, uint8_t willQos, boolean willRetain,
                        const char* willMessage, boolean cleanSession);
    boolean readByte(uint8_t* result);
    boolean readByte(uint8_t* result, uint16_t* index);
    uint16_t writeString(const char* string, uint8_t* buf, uint16_t pos);
    uint8_t readPacket();
    void processMessage(uint8_t* buffer, uint16_t length);
};

#endif
