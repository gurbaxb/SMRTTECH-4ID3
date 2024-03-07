import paho.mqtt.client as mqtt_client

# MQTT broker information 
address = "test.mosquitto.org"
port = 1883
topics = ["4ID3_GroupA/temperature", "4ID3_GroupA/humidity", "4ID3_GroupA/pressure", "4ID3_GroupA/light"]

# Connecting to MQTT broker
def on_connect(mqttc, obj, flags, rc):
    if rc == 0:
        print("Successfully connected to MQTT broker")
        # Subscribe to topics upon succesful connection
        for topic in topics:
            mqttc.subscribe(topic)
        # For unsuccessful connections, print explanation of error message
    else:
        if rc == 1:
            print("rc = 1: Connection to MQTT broker unsuccessful – incorrect protocol")
        elif rc == 2:
            print("rc = 2: Connection to MQTT broker unsuccessful – invalid client identifer")
        elif rc == 3:
            print("rc = 3: Connection to MQTT broker unsuccessful – server unavailable")
        elif rc == 4:
            print("rc = 4: Connection to MQTT broker unsuccessful – incorrect username or password")
        elif rc == 5:
            print("rc = 5: Connection to MQTT broker unsuccessful – authorization refused")

# For receiving messages from MQTT broker
def on_message(mqttc, obj, msg):
    print("Topic: " + (msg.topic))

# For subscribing to client
def on_subscribe(mqttc, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos)) # mid is the message_ID 

# Client information
mqttc = mqtt_client.Client("4ID3 L03 - Group 2 Client")
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.on_subscribe = on_subscribe

# Connect to MQTT broker
mqttc.connect(address, port, 150) # Interval is set to 150 seconds

# Loop forever to maintain connection with broker
mqttc.loop_forever()