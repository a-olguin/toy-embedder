# import sys so we can use check stuff with it later
module_two_counter = 0

def module_two_hello():
    global module_two_counter
    module_two_counter += 1
    print("Hola! I'm the second module. I also just incremented a counter :)")

