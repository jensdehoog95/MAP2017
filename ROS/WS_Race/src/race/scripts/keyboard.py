#!/usr/bin/env python

import rospy
import curses
from race.msg import drive_param


def keyboard_race():
    # Initializing the keyboard reader
    stdscr = curses.initscr()
    curses.cbreak()
    curses.noecho()
    stdscr.keypad(1)

    # Initializing the ros publisher
    pub = rospy.Publisher('drive_parameters', drive_param, queue_size=10)
    rospy.init_node('keyboard', anonymous=True)

    stdscr.refresh()
    key = ''

    # Initializing steer & throttle variables
    steer = 0.0
    throttle = 0.0

    print_values(stdscr, throttle, steer)

    while not rospy.is_shutdown() and key != ord('q'):
        key = stdscr.getch()
        stdscr.refresh()

        if key == curses.KEY_UP:
            if throttle <= 100.0:
                throttle = throttle + 0.1
        elif key == curses.KEY_DOWN:
            if throttle >= -100.0:
                throttle = throttle - 0.1
        elif key == curses.KEY_LEFT:
            if steer > -100.0:
                steer = steer - 5
        elif key == curses.KEY_RIGHT:
            if steer < 100.0:
                steer = steer + 5
        elif key == curses.KEY_DC or key == curses.KEY_BACKSPACE:
            # Delete key
            throttle = 0.0
            steer = 0.0
        elif key == ord('1'):
            throttle = 1.0
        elif key == ord('2'):
            throttle = 2.0
        elif key == ord('3'):
            throttle = 3.0
        elif key == ord('4'):
            throttle = 4.0
        elif key == ord('5'):
            throttle = 5.0
        elif key == ord('6'):
            throttle = 6.0
        elif key == ord('7'):
            throttle = 7.0
        elif key == ord('8'):
            throttle = 8.0
        elif key == ord('9'):
            throttle = 9.0

        msg = drive_param()

        # Set message parameters
        msg.steer = steer
        msg.throttle = throttle
        print_values(stdscr, throttle, steer)
        pub.publish(msg)

        # If loop is stopped
    curses.endwin()


def print_values(stdscr, throttle, steer):
    stdscr.addstr(3, 20, "Throttle: ")
    stdscr.addstr(3, 30, '%.4f' % throttle)
    stdscr.addstr(4, 20, "Steer: ")
    stdscr.addstr(4, 30, '%.4f' % steer)
    stdscr.addstr(5, 20, "    ")


if __name__ == '__main__':
    try:
        keyboard_race()
    except rospy.ROSInterruptException:
        pass
