#     Receive array of bytes over Serial and return it

#     Copyright (C) 2024 Joeri Kortenhorst
#
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <https://www.gnu.org/licenses/>.


import serial
import time


class ImageSerial:
    """
    Class for handling serial communication, specifically from the AI trainer. It will read
    a 6 byte array at a time and return it as a byte array.
    :param port: serial port name, default '/dev/ttyUSB0'
    :param baud_rate: serial baud rate, default 9600
    """
    port: str
    baud_rate: int
    serial: serial.Serial

    def __init__(self, port: str = "/dev/ttyACM0", baud_rate: int = 9600):
        self.port = port
        self.baud_rate = baud_rate

        try:
            # Initialize serial connection
            self.serial = serial.Serial(port, baud_rate, timeout=1)

            # Give the serial port some time to establish the connection
            time.sleep(2)

        except serial.SerialException as e:
            print(f"Error opening or communicating through the serial port: {e}")

        except KeyboardInterrupt:
            print("\nProgram exited by user")

    def loop_once(self) -> bytes:
        try:
            if self.serial.in_waiting > 0:
                # return self.serial.readline().decode('utf-8').rstrip()
                return self.serial.read(6)

        except serial.SerialException as e:
            print(f"Error opening or communicating through the serial port: {e}")

        except KeyboardInterrupt:
            print("\nProgram exited by user")

    def loop_forever(self):
        while True:
            print("Received: {}".format(self.loop_once()))

    def close(self):
        # Ensure the serial connection is properly closed
        if 'ser' in locals() or 'ser' in globals():
            self.serial.close()
            print("Serial connection closed")


def main():
    iserial = ImageSerial(port='/dev/ttyUSB0')
    while True:
        try:
            lst = list(iserial.loop_once())
            print(lst)
        except TypeError:
            pass

    iserial.close()


if __name__ == "__main__":
    main()
