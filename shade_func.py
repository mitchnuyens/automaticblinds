# shade_func.py

import serial 
import time

def shade():
    """
    The shade() function is designed as a first prototype in the pursuit of designing a completely autonomous window blind.
    It's purpose is to analyze the outside light sources and assess whether the outside world is worthy of the user's viewing.
    If it is dark (sensorValue < 50), the motor will not pull up the blinds.
    If it is bright (sensorValue > 50), the motor will roll up the blinds to reveal the beautiful world outside!
        (edit: assumptions made about user's personal view are not the responsibility of this function. shade() is not responsible for 
            things that can not be unseen once blinds are open.)

    """
    ser = serial.Serial('COM3', 9600)
    time.sleep(2)

    print(' PLEASE START WITH WINDOW CLOSED ')
    print('1. Automatic Function (Light Detection)')
    print('2. Roll shade up')
    print('3. Roll shade down')
    print('4. Show off a little')
    print('5. Quit')
    user_input = input('Enter a numeric option: ')
     
    while(user_input == '1' or '2' or '3' or '4' or '5'):
        if user_input == '1':
            ser.write(b'1') 
            print('> DEVICE IS ASSESSING IF OUTSIDE WORLD IS WORTHY OF YOUR VIEWING')
            time.sleep(2)
            print('>> ARDUINO HAS DECIDED.')
            time.sleep(3)
            user_input = input('Enter a numeric option: ')
        elif user_input == '2':
            ser.write(b'2')
            print('> MANUALLY ROLLING UP IN HERE')
            time.sleep(30)
            user_input = input('Enter a numeric option: ')
        elif user_input == '3':
            ser.write(b'3')
            print('> MANUALLY THROWING SHADE')
            time.sleep(30)
            user_input = input('Enter a numeric option: ')
        elif user_input == '4':
            ser.write(b'4')
            print('> CHECK OUT MY DANCE MOVES')
            time.sleep(5)
            print('> ALRIGHT, ENOUGH OF THAT')
            time.sleep(1)
            user_input = input('Enter a numeric option: ')
        elif user_input == '5':
            ser.write(b'5')
            print('> Function has been terminated. Goodbye.')
            break           
        else
            print('> Input was not recognized. Try again.')
            
    ser.close()
    print('PROGRAM END')