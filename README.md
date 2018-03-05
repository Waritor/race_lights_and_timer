Race Lights and timer

Used Pins on Arduino:
4,5,6 SPI for Race Lights (74HC595 8 Output-pins)
10,11,12 SPI for status register (74HC595) (relais and status lights)

8 chaosbutton (external pulldown)
9 startbutton (external pulldown)

interrupts-pins (fork light barriers)
2 for track 1 (external pullup)
3 for track 2 (external pullup)

I2C (2* LCM1602 (0x3F, 0x27) and 1*4kb Memory(24C04) (0x50))
A4 (SDA)
A5 (SCL)

