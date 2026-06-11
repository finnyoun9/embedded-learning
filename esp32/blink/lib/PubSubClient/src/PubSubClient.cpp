#include "PubSubClient.h"

#define MQTTCONNECT     1 << 4
#define MQTTPUBLISH     3 << 4
#define MQTTSUBSCRIBE   8 << 4
#define MQTTPINGREQ    12 << 4
#define MQTTPINGRESP   13 << 4
#define MQTTDISCONNECT 14 << 4

#define MQTT_CONN_ACCEPTED     0
#define MQTT_CONN_REFUSED_PROT 1
#define MQTT_CONN_REFUSED_ID   2
#define MQTT_CONN_REFUSED_SERV 3
#define MQTT_CONN_REFUSED_BAD  4
#define MQTT_CONN_REFUSED_AUTH 5

PubSubClient::PubSubClient() : _client(NULL), _domain(NULL), _port(1883),
    _callback(NULL), _lastActivity(0), _connected(false) {}

PubSubClient::PubSubClient(Client& client) : _client(&client), _domain(NULL), _port(1883),
    _callback(NULL), _lastActivity(0), _connected(false) {}

PubSubClient& PubSubClient::setServer(const char* domain, uint16_t port) {
    _domain = domain;
    _port = port;
    return *this;
}

PubSubClient& PubSubClient::setCallback(void (*callback)(char*, uint8_t*, unsigned int)) {
    _callback = callback;
    return *this;
}

uint16_t PubSubClient::writeString(const char* string, uint8_t* buf, uint16_t pos) {
    uint16_t len = strlen(string);
    buf[pos++] = len >> 8;
    buf[pos++] = len & 0xFF;
    memcpy(buf + pos, string, len);
    return pos + len;
}

boolean PubSubClient::readByte(uint8_t* result) {
    uint32_t start = millis();
    while (!_client->available()) {
        if (millis() - start > 15000) return false;
        delay(1);
    }
    *result = _client->read();
    return true;
}

boolean PubSubClient::readByte(uint8_t* result, uint16_t* index) {
    uint32_t start = millis();
    while (!_client->available()) {
        if (millis() - start > 15000) return false;
        delay(1);
    }
    *result = _client->read();
    (*index)++;
    return true;
}

boolean PubSubClient::connectMQTT(const char* id, const char* user, const char* pass,
                                   const char* willTopic, uint8_t willQos, boolean willRetain,
                                   const char* willMessage, boolean cleanSession) {
    if (!_client->connect(_domain, _port)) return false;

    uint8_t buffer[256];
    uint16_t pos = 0;

    // Protocol name
    buffer[pos++] = 0x00;
    buffer[pos++] = 0x04;
    buffer[pos++] = 'M';
    buffer[pos++] = 'Q';
    buffer[pos++] = 'T';
    buffer[pos++] = 'T';
    buffer[pos++] = 0x04; // protocol level

    // Connect flags
    uint8_t flags = 0;
    if (cleanSession) flags |= 0x02;
    if (willTopic != NULL) flags |= 0x04;
    if (user != NULL) flags |= 0x80;
    if (pass != NULL) flags |= 0x40;
    buffer[pos++] = flags;

    // Keepalive
    buffer[pos++] = 0;
    buffer[pos++] = MQTT_KEEPALIVE;

    // Client ID
    pos = writeString(id, buffer, pos);

    if (willTopic != NULL) {
        pos = writeString(willTopic, buffer, pos);
        uint16_t willMsgLen = strlen(willMessage);
        buffer[pos++] = willMsgLen >> 8;
        buffer[pos++] = willMsgLen & 0xFF;
        memcpy(buffer + pos, willMessage, willMsgLen);
        pos += willMsgLen;
    }

    if (user != NULL) pos = writeString(user, buffer, pos);
    if (pass != NULL) pos = writeString(pass, buffer, pos);

    // Write header
    uint8_t header[5];
    header[0] = MQTTCONNECT;
    uint8_t headerSize = 1;
    uint16_t remaining = pos;
    do {
        header[headerSize++] = remaining & 0x7F | (remaining > 127 ? 0x80 : 0);
        remaining >>= 7;
    } while (remaining > 0);

    for (uint8_t i = 0; i < headerSize; i++) _client->write(header[i]);
    _client->write(buffer, pos);

    // Read CONNACK
    uint8_t connack[4];
    for (int i = 0; i < 4; i++) {
        if (!readByte(&connack[i])) return false;
    }

    if (connack[3] != MQTT_CONN_ACCEPTED) return false;

    _connected = true;
    _lastActivity = millis();
    return true;
}

boolean PubSubClient::connect(const char* id) {
    return connectMQTT(id, NULL, NULL, NULL, 0, false, NULL, true);
}

boolean PubSubClient::connect(const char* id, const char* user, const char* pass) {
    return connectMQTT(id, user, pass, NULL, 0, false, NULL, true);
}

void PubSubClient::disconnect() {
    uint8_t buffer[2];
    buffer[0] = MQTTDISCONNECT;
    buffer[1] = 0;
    _client->write(buffer, 2);
    _connected = false;
    _client->stop();
}

boolean PubSubClient::connected() {
    return _client && _client->connected() && _connected;
}

int PubSubClient::state() {
    if (!_client) return -4;
    return _client->connected() ? (_connected ? 0 : -3) : -2;
}

boolean PubSubClient::publish(const char* topic, const char* payload) {
    if (!connected()) return false;

    uint8_t buffer[MQTT_MAX_PACKET_SIZE];
    uint16_t pos = 0;
    uint16_t topicLen = strlen(topic);
    uint16_t payloadLen = strlen(payload);

    buffer[0] = MQTTPUBLISH | 0x00;
    uint16_t remaining = 2 + topicLen + payloadLen;
    do {
        buffer[++pos] = remaining & 0x7F | (remaining > 127 ? 0x80 : 0);
        remaining >>= 7;
    } while (remaining > 0);

    buffer[++pos] = topicLen >> 8;
    buffer[++pos] = topicLen & 0xFF;
    memcpy(buffer + (++pos), topic, topicLen);
    pos += topicLen;
    memcpy(buffer + pos, payload, payloadLen);
    pos += payloadLen;

    _client->write(buffer, pos);
    _lastActivity = millis();
    return true;
}

boolean PubSubClient::subscribe(const char* topic) {
    if (!connected()) return false;

    uint8_t buffer[MQTT_MAX_PACKET_SIZE];
    uint16_t packetId = 1;
    uint16_t pos = 0;
    uint16_t topicLen = strlen(topic);

    buffer[0] = MQTTSUBSCRIBE;
    uint16_t remaining = 2 + 2 + topicLen + 1;
    do {
        buffer[++pos] = remaining & 0x7F | (remaining > 127 ? 0x80 : 0);
        remaining >>= 7;
    } while (remaining > 0);

    buffer[++pos] = packetId >> 8;
    buffer[++pos] = packetId & 0xFF;
    buffer[++pos] = topicLen >> 8;
    buffer[++pos] = topicLen & 0xFF;
    memcpy(buffer + (++pos), topic, topicLen);
    pos += topicLen;
    buffer[pos++] = 0; // QoS 0

    _client->write(buffer, pos);
    _lastActivity = millis();
    return true;
}

uint8_t PubSubClient::readPacket() {
    uint8_t buffer[MQTT_MAX_PACKET_SIZE];
    uint16_t pos = 0;

    uint8_t type;
    if (!readByte(&type, &pos)) return 0;

    uint32_t remaining = 0;
    uint8_t shift = 0;
    uint8_t byte;
    do {
        if (!readByte(&byte, &pos) || pos >= MQTT_MAX_PACKET_SIZE) return 0;
        remaining |= (byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);

    for (uint16_t i = 0; i < remaining && pos < MQTT_MAX_PACKET_SIZE; i++) {
        if (!readByte(&buffer[pos++])) return 0;
    }

    uint8_t msgType = type & 0xF0;
    if (msgType == MQTTPUBLISH) {
        processMessage(buffer, pos);
    } else if (msgType == MQTTPINGRESP) {
        _lastActivity = millis();
    }

    return msgType;
}

void PubSubClient::processMessage(uint8_t* buffer, uint16_t length) {
    uint16_t pos = 0;
    uint16_t topicLen = (buffer[pos] << 8) | buffer[pos + 1];
    pos += 2;
    char topic[topicLen + 1];
    memcpy(topic, buffer + pos, topicLen);
    topic[topicLen] = '\0';
    pos += topicLen;

    if (_callback) {
        _callback(topic, buffer + pos, length - pos);
    }
}

boolean PubSubClient::loop() {
    if (!connected()) return false;

    if (_client->available()) {
        readPacket();
        _lastActivity = millis();
        return true;
    }

    if (millis() - _lastActivity > MQTT_KEEPALIVE * 1000UL) {
        uint8_t ping[2] = {MQTTPINGREQ, 0};
        _client->write(ping, 2);
        _lastActivity = millis();
    }

    return false;
}
