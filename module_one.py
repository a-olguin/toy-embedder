# import sys so we can use check stuff with it later
import sys
module_one_counter = 0

def module_one_hello():
    global module_one_counter
    module_one_counter += 1
    print("Hiya! I'm the first module. I just incremented a counter btw :)")

