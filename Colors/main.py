#     Program used in combination with a Serial input of 4 Rotary encoders to
#     update colors on a screen. These colors are set with a plot.
#     Array format: [Encoder1, Encoder2, Encoder3, Encoder 4, Difficulty, Red button pressed]

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

import numpy as np
import time
import random
import sys
import matplotlib.pyplot as plt
from ImageSerial import ImageSerial
from enum import Enum
from Database import Database


class Difficulty(Enum):
    EASY = 0
    NORMAL = 1
    HARD = 2


def pick_item(current_list):
    """
    Takes a list of items and picks one item randomly, remove the item and return it.
    :param current_list:
    :return:
    """
    if current_list:  # Check if the list is not empty
        choice = random.choice(current_list)
        current_list.remove(choice)  # Remove the chosen item
        return choice
    else:
        return None  #


def update_image(image_: np.ndarray, pause_time_: int):
    """
    Update the image with the given pause time
    :param image_:
    :param pause_time_:
    :return:
    """
    img_display_ = plt.imshow(image_)
    plt.show(block=False)
    plt.pause(pause_time_)
    return img_display_


def main(port_: str = '/dev/ttyUSB0'):
    print("""Copyright (C) 2024 Joeri Kortenhorst
    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.""")

    # Generate an array of RGB colors
    simple_colors = []
    for i in range(10):
        for j in range(10):
            # Calculate the RGB values based on the grid position
            r = (i * 51) % 256
            g = (j * 51) % 256
            b = ((i + j) * 51) % 256
            # Set the color for each subplot
            simple_colors.append((r / 255, g / 255, b / 255, 1))

    use_db = False
    try:
        db = Database('config.ini')
        use_db = True
        print('Database opened')
    except ValueError:
        print('Config file not found')

    try:
        ser = ImageSerial(port=port_)
        print('Connected to ' + port_)
        while True:
            # Loop start is start of an attempt. Start the timer.
            start_time = time.time()
            print('Timer started.')

            # Randomize the assignment of each Rotary encoder on the AI trainer
            positions = [0, 1, 2, 3]
            position_1 = pick_item(positions)
            position_2 = pick_item(positions)
            position_3 = pick_item(positions)
            position_4 = pick_item(positions)

            # Inform the organizer of the rotary positions
            print(position_1, position_2, position_3, position_4)

            # Get the first array in order to start in the right difficulty mode
            first_read = None
            while not first_read:
                try:
                    first_read = list(ser.loop_once())
                except TypeError:
                    time.sleep(0.05)

            # Set the difficulty, default to EASY
            try:
                mode = Difficulty(first_read[4])
            except ValueError:
                mode = Difficulty.EASY

            # Initialize based on the mode, again default to EASY
            red_button = False
            match mode:
                case Difficulty.EASY:
                    print('Initialize in easy mode.')
                    goal_r, goal_g, goal_b, goal_o = random.choice(simple_colors)
                case Difficulty.NORMAL:
                    print('Initialize in normal mode.')
                    goal_r, goal_g, goal_b, goal_o = random.random(), random.random(), random.random(), random.random()
                case Difficulty.HARD:
                    print('Initialize in hard mode.')
                    goal_r, goal_g, goal_b, goal_o = random.random(), random.random(), random.random(), random.random()
                case default:
                    goal_r, goal_g, goal_b, goal_o, = random.choice(simple_colors)

            # Load your image
            plt.ion()
            figure, ax = plt.subplots(nrows=1, ncols=2, figsize=(16, 9))
            figure.subplots_adjust(left=0, right=1, bottom=0, top=1)

            # Generate offset and a random starting color
            offset1, offset2, offset3, offset4 = random.random(), random.random(), random.random(), random.random()
            r, g, b, o = random.random(), random.random(), random.random(), random.random()

            # Set up the plot
            values = [r, g, b, o]
            img_data = np.full((1, 1, 4), values)
            goal_img = np.full((1, 1, 4), [goal_r, goal_g, goal_b, goal_o])
            ax[0].imshow(goal_img)
            goal_string = f'Doel: RGBA({int(goal_r * 255)}, {int(goal_g * 255)}, {int(goal_b * 255)}, {round(goal_o, 1)})'
            ax[0].set_title(goal_string)
            ax[0].axis('off')
            img_plot = ax[1].imshow(img_data)
            ax[1].axis('off')

            def log(diff: float):
                """
                Logging function for debugging and for the organizer to follow the progress
                :param diff:
                :return:
                """
                elapsed_time = time.time() - start_time
                difference = round(diff, 4)
                rgba_string = (f'RGBA({int(values[position_1] * 255)}, {int(values[position_2] * 255)}, '
                               f'{int(values[position_3] * 255)}, {round(values[position_4], 1)})')
                print(f"{elapsed_time:.2f}s | {difference} | {goal_string} | {rgba_string}")

            def redraw():
                """
                Redraw the figure on the screen and set the title of the figure based on the selected difficulty mode
                The diff equals the score and is the difference between the goal and actual squared. 0 would mean a
                perfect score.
                :return:
                """
                img_plot.set_data(img_data)
                diff = ((goal_r - values[position_1])**2 + (goal_g - values[position_2])**2 +
                        (goal_b - values[position_3])**2 + (goal_o - values[position_4])**2)

                if (mode != Difficulty.HARD) or (mode != Difficulty.EASY and red_button):
                    ax[1].set_title(f'{round(diff, 4)} RGBA({int(values[position_1] * 255)}, '
                                    f'{int(values[position_2] * 255)}, {int(values[position_3] * 255)}, i'
                                    f'{round(values[position_4], 1)})')
                else:
                    ax[1].set_title(None)

                log(diff)
                figure.canvas.draw()
                # Wait a short time to draw the plot
                plt.pause(0.05)

            plt.ioff()

            # Start the actual loop
            while True:
                try:
                    # Collect data from serial in insert into image editor
                    cur_values = list(ser.loop_once())

                    # Check if reset array is received, if yes insert score into the DB and wait untill the red button
                    # is no longer pressed
                    red_button = cur_values[5]
                    if any(i == 255 for i in cur_values) or (red_button and mode != Difficulty.HARD):
                        if use_db and (time.time() - start_time) > 5:
                            db.insert(
                                difference=((goal_r - values[position_1])**2 + (goal_g - values[position_2])**2 +
                                            (goal_b - values[position_3])**2 + (goal_o - values[position_4])**2),
                                elapsed_time=(time.time() - start_time),
                                goal_r=int(goal_r * 255),
                                goal_g=int(goal_g * 255),
                                goal_b=int(goal_b * 255),
                                goal_a=int(goal_o * 255),
                                actual_r=int(values[position_1] * 255),
                                actual_g=int(values[position_2] * 255),
                                actual_b=int(values[position_3] * 255),
                                actual_a=int(values[position_4] * 255)
                            )
                            print('Database updated')

                        plt.close('all')
                        # Read Red button and wait til release to break. Break will restart the round.
                        while cur_values[5]:
                            try:
                                cur_values = list(ser.loop_once())
                            except TypeError:
                                time.sleep(1.00)
                        break

                    # Reaching here means the red button was not pressed, so now the work has to be done.
                    # Read values from serial and convert to between 0 and 1
                    cur_values = [i/100 for i in cur_values]

                    # Apply offset in HARD mode so that the numbers on the trainer don't match the actual position
                    if mode == Difficulty.HARD:
                        cur_values[0] = ((cur_values[0] + offset1) % 1)
                        cur_values[1] = ((cur_values[1] + offset2) % 1)
                        cur_values[2] = ((cur_values[2] + offset3) % 1)
                        cur_values[3] = ((cur_values[3] + offset4) % 1)

                    # Redraw if a change is detected
                    if not np.array_equal(values, cur_values):
                        values = cur_values
                        img_data = np.full((1, 1, 4), [values[position_1], values[position_2],
                                                       values[position_3], values[position_4]])
                        redraw()

                # No Serial value, wait for a short period
                except TypeError:
                    time.sleep(0.05)

            ser.close()

    except AttributeError:
        print("Failed to open Serial at: {}".format(port_))


if __name__ == "__main__":
    if len(sys.argv) == 2:
        main(sys.argv[1])
    else:
        main()
