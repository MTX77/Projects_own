import players_test

def test1(path):
    print()
    print('Test1:')
    print('Records read: ', len(players_test.read_players(path)))
    print('The first two: ', players_test.read_players(path)[0])
    print(players_test.read_players(path)[1])
    print()
    print('The last two: ', players_test.read_players(path)[-2])
    print(players_test.read_players(path)[-1])
    print()

def test2(players):
    print()
    print('Test2:')
    print('The 4 best players born in 1969 are: ',players_test.best_players(players, '1969', 4))
    print()

def test3(players):
    print()
    print('Test3:')
    print('Players by strokes:')
    for x in players_test.players_per_hits(players):
        print(x)
    print()

def test4(players):
    print()
    print('Test4:')
    print('The average of each senior player with an update date between 2020-03-01 and 2020-05-31 are:')
    print(players_test.average_last_results(players, '2020-03-01', '2020-05-31'))
    print()

def test5(players):
    print()
    print('Test5:')
    print('The best players in each federation are:')
    for k,v in players_test.lower_handicap_player_by_federation(players).items():
        print((k,(v)))
    print()

def test6(players):
    print()
    print('Test6:')
    for x in players_test.comparison_of_best_results_according_to_handicap(players):
        print(x)
    print()  

def main():
    path = 'data.csv'
    players = players_test.read_players(path)

    test1(path)
    test2(players)
    test3(players)
    test4(players)
    test5(players)
    test6(players)

if __name__ == '__main__':
    main()
