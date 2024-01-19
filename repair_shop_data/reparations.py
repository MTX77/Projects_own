import csv
from collections import namedtuple
from datetime import datetime, timedelta

Repair = namedtuple('Repair', 'ref_number,center,entry_date,repair_date, serial_number, dev_type, problem_description, purchase_date, repair_price')

def read_reparations(path):
    with open(path, 'r', encoding='UTF-8') as csv_file:
        reader = csv.reader(csv_file, delimiter=';')
        next(reader)

        Repairs = list()
        for ref_number,center,entry_date,repair_date, serial_number, dev_type, problem_description, purchase_date, repair_price in reader:
            good_entry = datetime.strptime(entry_date, '%d/%m/%Y').date()
            good_repair = datetime.strptime(repair_date, '%d/%m/%Y').date()
            good_purchase = datetime.strptime(purchase_date, '%d/%m/%Y').date()
            good_price = float(repair_price)

            my_repair = Repair(ref_number,center,good_entry,good_repair, serial_number, dev_type, problem_description, good_purchase, good_price)
            Repairs.append(my_repair)
        
    return Repairs


def calculate_income(repairs, center, dev_type=None):
    income = 0
    my_date = datetime.strptime('1/1/2022', '%d/%m/%Y').date()
    for repair in repairs:
        if repair.center == center:
            entry = repair.entry_date
            purchase = repair.purchase_date
            if dev_type == None:
                if purchase >= my_date:
                    if purchase + timedelta(3*365) < entry:
                        income += repair.repair_price
                else:
                    if purchase + timedelta(2*365) < entry:
                        income += repair.repair_price             
            else:
                if repair.dev_type == dev_type:
                    if purchase >= my_date:
                        if purchase + timedelta(3*365) < entry:
                            income += repair.repair_price
                    else:
                        if purchase + timedelta(2*365) < entry:
                            income += repair.repair_price
    return (center, income)


def longest_repairs(repairs, year, n, center=None):
    dict_repairs_days = dict()
    for repair in repairs:
        if repair.entry_date.year == year:
            if center == None:
                length = (repair.repair_date - repair.entry_date).days
                dict_repairs_days[repair.ref_number] = length
            else:
                if repair.center == center:
                    length = (repair.repair_date - repair.entry_date).days
                    dict_repairs_days[repair.ref_number] = length

    sorted_dict = dict(sorted(dict_repairs_days.items(), key=lambda x: -x[1]))

    my_list = list()
    for k,v in sorted_dict.items():
        my_list.append((k,v))   
    return my_list[:n] 


def fastest_center(repairs, centers):
    dict_centers = dict()
    for repair in repairs:
        if repair.center in centers:
            if repair.center not in dict_centers.keys():
                days = (repair.repair_date - repair.entry_date).days
                count = 1
                dict_centers[repair.center] = days, count
            else:
                days = dict_centers[repair.center][0] + (repair.repair_date - repair.entry_date).days
                count = dict_centers[repair.center][1] + 1
                dict_centers[repair.center] = days, count

    average_days = dict()
    for k,v in dict_centers.items():
        average_days[k] = round(v[0] / v[1], 2)

    sorted_list = sorted(average_days.items(), key=lambda x: x[1])

    return sorted_list[0][0]


def center_experienced_in(repairs, keywords):
    my_words = set()
    for mykeyword in keywords:
            mykeyword = mykeyword.lower()
            my_words.add(mykeyword)

    dict_centers = dict()
    my_center = dict()
    for repair in repairs:
        description = set()
        description = set(repair.problem_description.lower().split())
        for keyword in my_words:
            if keyword in description:
                if keyword not in dict_centers:
                    dict_centers[keyword] = {repair.center: 1}
                elif repair.center not in dict_centers[keyword]:
                    dict_centers[keyword][repair.center] = 1
                else:
                    dict_centers[keyword][repair.center] += 1

# Sort the inner dictionaries by value and keep only the keys
    sorted_dict_centers = {k: [item[0] for item in sorted(v.items(), key=lambda x: -x[1])] for k, v in dict_centers.items()}

    return sorted_dict_centers

def days_between_repairs(repairs):
    repairs = sorted(repairs, key=lambda x: x.entry_date)
    dict_repairs_days = dict()
    for repair in repairs:
        if repair.serial_number not in dict_repairs_days:
            difference = (repair.entry_date - repair.purchase_date).days
            dict_repairs_days[repair.serial_number] = [difference], repair.repair_date
        else:
            difference = (repair.entry_date - dict_repairs_days[repair.serial_number][1]).days
            temp = list(dict_repairs_days[repair.serial_number][0])
            temp.append(difference)
            dict_repairs_days[repair.serial_number] = temp, repair.repair_date
    
    my_dict = dict()
    for k,v in dict_repairs_days.items():
        my_dict[k] = v[0]

    return my_dict
        
    
    