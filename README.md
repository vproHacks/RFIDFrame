# RFIDFrame
An RFID Framework that should allow you to interface with MFRC522 devices in python.

# Installation
Use this command `pip install RFIDFrame`

# Using It
There are 2 main parts to utilizing the library.

## Arduino
Get the .ino file from the ESP_CODE Library. Upload this to your ESP device using the arduino software. 

## Python
Load up the file into your project library. It uses Selenium as a dependancy. Import it into your application using this command and there is a sample as to use it as well.

```python
import RFIDFrame as rf

uid_long = rf.RFID.get_uid_long(ip)
```
