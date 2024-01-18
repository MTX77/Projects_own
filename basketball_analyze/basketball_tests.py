import basketball
from typing import *

def test1(path: str) -> None:
    print()
    print('Test1')
    print('Total records read:', len(basketball.read_match(path)))
    print('Showing the first three records:\n',basketball.read_match(path)[0])
    print(basketball.read_match(path)[1])
    print(basketball.read_match(path)[2])
    print()


def test2(matches: List) -> None:
    print()
    print('Test2')
    print('Most fouls:', basketball.team_with_most_fouls(matches))
    print()

def test3(matches: List) -> None:
    print()
    print('Test3')
    print('Average_points_per_team test (competition=''Copa del Rey''):\n',basketball.average_points_per_team(matches, 'Copa del Rey'))
    print()

def test4(matches: List) -> None:
    print()
    print('Test4')
    print('Difference_points_scored test (team=''Barcelona''):\n',basketball.difference_points_scored(matches, 'Barcelona'))
    print()

def test5(matches: List) -> None:
    print()
    print('Test5')
    print('Teams and wins:\n',basketball.wins_per_team(matches))
    print()

def test6(matches: List) -> None:
    print()
    print('Test6')
    print('Team test_minimum_victories (n=8): \n',basketball.teams_minimum_wins(matches, 8))
    print()

def test7(matches: List) -> None:
    print()
    print('Test7')
    print('Test of teams_most_wins_per_year (n=8): \n',basketball.teams_most_wins_per_year(matches, 8))
    print()


def main():
    path = 'data.csv'
    matches = basketball.read_match(path)

    test1(path)
    test2(matches)
    test3(matches)
    test4(matches)
    test5(matches)
    test6(matches)
    test7(matches)
    



if __name__ == '__main__':
    main()