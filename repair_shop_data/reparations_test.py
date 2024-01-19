import reparations

def test1(Repairs):
    print()
    print('Test1:')
    print('Total number of repairs:', len(Repairs))
    print('These are the first 3 records:\n',Repairs[0])
    print(Repairs[1])
    print(Repairs[2])
    print()

def test2(Repairs):
    print('Test2:')
    print('Revenue in Seville for laptop repair: ',reparations.calculate_income(Repairs, 'Sevilla', 'portátil'))
    print('Revenue in Seville for all types repair:',reparations.calculate_income(Repairs, 'Sevilla'))
    print()

def test3(Repairs):
    print('Test3:')
    print('Longest repair in Seville in 2019: ',reparations.longest_repairs(Repairs, 2019, 1, 'Sevilla'))
    print('The three longest repairs in 2020:',reparations.longest_repairs(Repairs, 2020, 3))
    print()

def test4(Repairs):
    print('Test4:')
    print('Fastest center between Seville, Huelva and Cádiz:',reparations.fastest_center(Repairs, {'Sevilla', 'Cádiz', 'Huelva'}))
    print()

def test5(Repairs):
    print('Test5:')
    print('Ordered list of the centers with the most experience in screens and batteries:',reparations.center_experienced_in(Repairs, {'Batería', 'pantalla'}))
    print()

def test6(Repairs):
    print('Test6:')
    print('Days elapsed between device repairs:',reparations.days_between_repairs(Repairs))
    print()


def main():
    
    path = '_reparaciones.csv'
    Repairs = reparations.read_reparations(path)

    test1(Repairs)
    test2(Repairs)
    test3(Repairs)
    test4(Repairs)
    test5(Repairs)
    test6(Repairs)
    
    




if __name__ == '__main__':
    main()