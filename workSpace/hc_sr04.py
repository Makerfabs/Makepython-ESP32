from hcsr04 import HCSR04
from machine import Pin,I2C
import ssd1306

i2c = I2C(scl=Pin(5), sda=Pin(4), freq=100000)      #Init i2c
lcd=ssd1306.SSD1306_I2C(128,64,i2c) 

sensor = HCSR04(trigger_pin=13, echo_pin=12,echo_timeout_us=1000000)

try:
  while True:
    distance = sensor.distance_cm()
    print(distance)
    lcd.fill(0)
    lcd.text("Distance:",30,20) 
    lcd.text(str(distance),30,40)
    lcd.show()
except KeyboardInterrupt:
       pass    








