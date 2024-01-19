import module_f1

def test1(path):
    print()
    print('Test 1:')
    print('Total records read: ',len(module_f1.read_races(path)))
    print('Showing the first two records:\n',module_f1.read_races(path)[0])
    print()
    print(module_f1.read_races(path)[1])
    print()

def test2(Races):
    print()
    print('Test 2:')
    print('The average time in the pits in the city of Barcelona is: ',module_f1.average_time_boxes(Races, 'Barcelona'))
    print()

def test3(Races):
    print()
    print('Test 3:')
    print('The 4 drivers with the lowest average time are: ',module_f1.drivers_shortest_time_average_top_laps(Races, 4))
    print()

def test4(Races):
    print()
    print('Test 4:')
    print('The pit time ratios are:')
    for v in module_f1.ratio_time_boxes_total(Races):
        print(v)
    print()

def test5(Races):
    print()
    print('Test 5:')
    print('Points per year for each of the drivers: ')
    for k,v in module_f1.points_drivers(Races).items():
        print(k,v)
    print()

def test6(Races):
    print()
    print('Test 6:')
    print('The best team in 2022 has been: ',module_f1.best_team_of_any_year(Races, '2022'))
    print()


def main():
    path = '_f1.csv'
    Races = module_f1.read_races(path)

    test1(path)
    test2(Races)
    test3(Races)
    test4(Races)
    test5(Races)
    test6(Races)


if __name__ == '__main__':
    main()