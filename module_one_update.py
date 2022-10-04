# import sys so we can use check stuff with it later
import sys
module_one_counter = 0

def module_one_hello():
    global module_one_counter
    module_one_counter += 1
    print("Heey! I'm the NEW first module. My data is fresh and new and also so are my functions. My counter also just updated...")

