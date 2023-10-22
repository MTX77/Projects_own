import random
from colorama import Fore, Back, Style

MAX_LINES = 4

MIN_BET = 1
MAX_BET = 100

ROWS = 4
COLS = 3

symbols_count = {
    "\U0001F349": 5,
    "\U0001F47D": 3,
    "\U0001F42F": 4,
    "\U0001F984": 4
}

symbol_value = {
    "\U0001F47D": 10,
    "\U0001F42F": 6,
    "\U0001F984": 8,
    "\U0001F349": 5
}

def check_win(columns, lines, bet, values):
    winnings = 0
    winning_lines = []
    for line in range(lines):
        symbol = columns[0][line]
        for column in columns:
            symbol_to_check = column[line]
            if (symbol != symbol_to_check):
                break
        else:
            winnings += values[symbol] * bet
            winning_lines.append(line + 1)

    return winnings, winning_lines
    

def logic(rows, cols, symbols):
    all_symbols = []
    for symbol, symbols_count in symbols.items():
        for _ in range(symbols_count):
            all_symbols.append(symbol)

    columns = []
    for _ in range(cols):
        column = []
        current_symbol = all_symbols[:]

        for _ in range(rows):
            value = random.choice(current_symbol)
            current_symbol.remove(value)
            column.append(value)

        columns.append(column)

    return columns
    
def printing(columns):
    for row in range(len(columns[0])):
        for i, column in enumerate((columns)):
            if (i != len(columns) - 1):
                print(column[row], end=" | ")
            else:
                print(column[row], end="")
        print()


def deposit():
    while (True):
        money = input("What would you like to deposit? $")
        if (money.isdigit()):
            money = int(money)
            if (money > 0):
                break
            else:
                print("Amount must be greater than $0")
        else:
            print("Please, enter a number")

    return money

def lines():
    while (True):
        line = input(f"How many lines would you like to bet on (1-{MAX_LINES})? ")
        if (line.isdigit()):
            line = int(line)
            if (0 < line <= MAX_LINES):
                break
            else:
                print(f"Number of lines must be within (1-{MAX_LINES})")
        else:
            print("Please, enter a valid number")

    return line

def get_bet():
    while (True):
        money = input("How much money would you like to bet? $")
        if (money.isdigit()):
            money = int(money)
            if (MIN_BET <= money <= MAX_BET):
                break
            else:
                print(f"Amount must be within ({MIN_BET}$-{MAX_BET}$)")
        else:
            print("Please, enter a number")

    return money

def game(balance):
    betting_lines = lines()

    while (True):
        bet = get_bet()
        total_bet = betting_lines * bet

        if (total_bet > balance):
            print (f"Not enough funds to place a bet. Your current balance is ${balance}")
        else:
            print("Your total bet is: " + Fore.YELLOW + f"${total_bet}")
            print(Style.RESET_ALL)
            break
    
    columns = logic(ROWS, COLS, symbol_value)
    printing(columns)

    win, winning_lines = check_win(columns, betting_lines, bet, symbol_value)

    if (win > 0):
        print("\nYou won: " + Fore.GREEN + f"${win}")
        print(Style.RESET_ALL, end="")
        print(f"You won on lines: ", *winning_lines)
    else:
        print("\nYou lost: " + Fore.RED + f"${total_bet}")
        print(Style.RESET_ALL, end="")

    return win - total_bet

def main():
    balance = deposit()

    while (True):
        print("\nCurrent balance is: " + Fore.GREEN + f"${balance}")
        print(Style.RESET_ALL)

        balance += game(balance)

        if (balance == 0 ):
            break

        spin = input("Press: Enter - to play or Q - to quit: ")

        if(spin == "q" or spin == "Q"):
            break
    
    if (balance == 0):
        print("You left with: " + Fore.RED + f"${balance}")
    else:
        print("You left with: " + Fore.GREEN + f"${balance}")
    print(Style.RESET_ALL)

main()