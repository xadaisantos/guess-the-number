from random import randint

def greetings():
    print("*************************************")
    print("*** Welcome to the guessing game! ***")
    print("*************************************", end="\n\n")

def guessTheNumber():
    start = 0
    stop = 100
    secretNumber = randint(start, stop)
    guess = None
    difficulty = None
    hasWon = False

    greetings()

    difficulty = input("In which difficulty do you want to play? Easy (E), Normal (N) or Hard (H)? ")
    if difficulty[0].upper() == "E":
        difficulty = 15
        print("You've chosen Easy!")
    elif difficulty[0].upper() == "N":
        difficulty = 10
        print("You've chosen Normal!")
    elif difficulty[0].upper() == "H":
        difficulty = 5
        print("You've chosen Hard!")
    else:
        difficulty = 10
        print("Since you didn't type \"E\", \"N\" or \"H\", I've chosen Normal for you.")

    for i in range(difficulty):
        try:
            guess = int(input(f"From {start} to {stop}, what's the number? "))
        except ValueError:
            print('Type a number!')
            continue
            
        if guess > secretNumber:
            print('Less!')
        if guess < secretNumber:
            print('More!')
        if guess == secretNumber:
            hasWon = True
            break

        print("")

    print(f"The number was {secretNumber}!")
    if hasWon:
        print("You've won!")
    else:
        print(f"You've lost!")

guessTheNumber()