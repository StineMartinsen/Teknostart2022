# import curses and GPIO
import curses
import RPi.GPIO as GPIO

#set GPIO numbering mode and define output pins
GPIO.setmode(GPIO.BCM)
GPIO.setup(4,GPIO.OUT)
GPIO.setup(5,GPIO.OUT)
GPIO.setup(6,GPIO.OUT)
GPIO.setup(26,GPIO.OUT)

#test
# Get the curses window, turn off echoing of keyboard to screen, turn on
# instant (no waiting) key response, and use special values for cursor keys
screen = curses.initscr()
curses.noecho() 
curses.cbreak()
screen.keypad(True)

try:
        while True:   
            char = screen.getch()
            if char == ord('q'):
                break
            elif char == curses.KEY_UP:
                GPIO.output(4,False)
                GPIO.output(5,True)
                GPIO.output(6,False)
                GPIO.output(26,True)
            elif char == curses.KEY_DOWN:
                GPIO.output(4,True)
                GPIO.output(5,False)
                GPIO.output(6,True)
                GPIO.output(26,False)
            elif char == curses.KEY_RIGHT:
                GPIO.output(4,True)
                GPIO.output(5,False)
                GPIO.output(6,False)
                GPIO.output(26,True)
            elif char == curses.KEY_LEFT:
                GPIO.output(4,False)
                GPIO.output(5,True)
                GPIO.output(6,True)
                GPIO.output(26,False)
            elif char == 10:
                GPIO.output(4,False)
                GPIO.output(5,False)
                GPIO.output(6,False)
                GPIO.output(26,False)
             
finally:
    #Close down curses properly, inc turn echo back on!
    curses.nocbreak(); screen.keypad(0); curses.echo()
    curses.endwin()
    GPIO.cleanup()
    
