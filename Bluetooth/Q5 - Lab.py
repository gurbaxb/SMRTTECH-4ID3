import serial

with serial.Serial('COM10', 9600, timeout=5) as ser:

try:
    while True:
        serial_data = ser.readline()
        
        if data:
            print("The following data is received:", serial_data)
        else:
            print ("Data not received", serial_data)

finally:
    ser.close() 
