# Name: Kyle Johnson
# Class: ETEC2110
# Section: 02
# Assignment Bonus Tank Challenge

# import the things you need here
import math
import random


class Tank_AI(object):
    def __init__(self):
        # required attributes
        self.name = "ICUP"  # your bot name here
        self.house = "Independent"  # your house. Use "Yost", "Witherell", "Lynn", or "Skaggs"
        # your class variables follow
        self.my_angle = 135
        self.fire_countdown = 0

    def make_move(self, your_location, tank_list, bullet_list):
        # pick a new angle every so often
        if (your_location[0] == 20):
            self.my_angle = 90
        if (your_location[1] == 20):
            self.my_angle = 180
        # choose command to return
        if self.fire_countdown <= 0:
            command = ("fire", random.randint(270, 359))
            self.fire_countdown = 15
        else:
            command = ("move", self.my_angle)
            self.fire_countdown -= 1
        # return the selected command
        return command
