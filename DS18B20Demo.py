from machine import Pin,I2C
import ssd1306
import time
import machine
import onewire

dat = machine.Pin(12)		# the device is on GPIO0
i2c = I2C(scl=Pin(5), sda=Pin(4), freq=100000)      #Init i2c
lcd=ssd1306.SSD1306_I2C(128,64,i2c)           #create LCD object,Specify col and row

ds = ds18x20.DS18X20(onewire.OneWire(dat))	   # create the onewire object
roms = ds.scan()			# scan for devices on the bus

try:
  while True:
      ds.convert_temp()
      time.sleep_ms(750)	#The reading temperature needs at least 750ms
      for rom in roms:
          lcd.fill(0)
          lcd.text("temperatures:",10,16) 
          lcd.text(str(ds.read_temp(rom)),24,40)
          lcd.show()  
except KeyboardInterrupt:
          pass


