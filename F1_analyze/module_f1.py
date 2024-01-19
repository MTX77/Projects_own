import csv
from collections import namedtuple
from datetime import datetime

Race = namedtuple("Race", "name, team, race_date, min_temp, max_speed, duration, fin_pos, city, top_6_laps, box_time, liquid_level")

def read_races(path):
    with open(path, 'r', encoding='UTF-8') as csv_file:
        reader = csv.reader(csv_file, delimiter=';')
        next(reader)

        Races = list()
        for name, team, race_date, min_temp, max_speed, duration, fin_pos, city, top_6_laps, box_time, liquid_level in reader:
            good_date = datetime.strptime(race_date, '%d-%m-%y').date()
            min_temp = int(min_temp)
            max_speed = float(max_speed)
            duration = float(duration)
            fin_pos = int(fin_pos)
            box_time = float(box_time)
            if liquid_level == 'no':
                liquid_level = False
            else:
                liquid_level = True  
            top_6_laps = top_6_laps.strip('[]').split('/ ')

            my_laps = list()
            for lap in top_6_laps:
                if lap == '-':
                    lap = 0
                else:
                    lap = float(lap)
                my_laps.append(lap)

            my_race = Race(name, team, good_date, min_temp, max_speed, duration, fin_pos, city, my_laps, box_time, liquid_level)
            Races.append(my_race)

    return Races


def average_time_boxes(races, city, date=None):
    sum = 0
    count = 0
    for race in races:
        if date == None:
            if race.city == city:
                sum += race.box_time
                count += 1
        else:
            my_date = datetime.strptime(date, '%d-%m-%y').date()
            if race.city == city and race.race_date == my_date:
                sum += race.box_time
                count += 1

    if sum == 0:
        return 0
    else:
        return sum / count
    

def drivers_shortest_time_average_top_laps(races, n):
    dict_top_time = dict()
    for race in races:
        sum = 0
        skip_race = False
        for lap in race.top_6_laps:
            if lap == 0:
                skip_race = True
            else:
                sum += lap
        if skip_race:
            continue
        avg = sum / 6
        if race.name not in dict_top_time:
            dict_top_time[race.name] = race.race_date, avg
        else:
            if avg <= dict_top_time[race.name][1]:
                dict_top_time[race.name] = race.race_date, avg

    sorted_dict = dict(sorted(dict_top_time.items(), key=lambda x: x[1][1]))

    my_list = list()
    for k,v in sorted_dict.items():
        my_list.append((k,v[0]))
    
    return my_list[:n]


def ratio_time_boxes_total(races):
    dict_date_box_time = dict()
    for race in races:
        if race.race_date not in dict_date_box_time:
            dict_date_box_time[race.race_date] = race.box_time
        else:
            dict_date_box_time[race.race_date] += race.box_time

    dict_racers_ratio = dict()
    for race in races:
        total_box_time = 0
        for k,v in dict_date_box_time.items():
            if race.race_date == k:
                total_box_time = v
        if race.name and race.race_date not in dict_racers_ratio:
            ratio = round(race.box_time / total_box_time, 3)
            dict_racers_ratio[race.name, race.race_date] = ratio

    sorted_dict = dict(sorted(dict_racers_ratio.items(), key=lambda x: -x[1]))

    my_list = list()
    for k,v in sorted_dict.items():
        my_list.append((k[0], k[1], v))
    
    return my_list


def my_place(race):
    if race == 1:
        return 50
    elif race == 2:
        return 25
    elif race == 3:
        return 10
    else:
        return 0

def points_drivers(races):
    dict_points = dict()
    for race in races:
        points = my_place(race.fin_pos)
        if race.name not in dict_points:
            dict_points[race.name] = {race.race_date.year: points}
        elif race.race_date.year not in dict_points[race.name]:
            dict_points[race.name][race.race_date.year] = points
        else:
            suma = dict_points[race.name][race.race_date.year] + points
            dict_points[race.name][race.race_date.year] = suma

    sorted_dict = {k: dict(sorted(v.items(), key=lambda x: x[0])) for k,v in dict_points.items()}
    
    my_dict = dict()
    for k,v in sorted_dict.items():
        my_list = list()
        for point in v.values():
            my_list.append(point)
        my_dict[k] = my_list

    return my_dict


def best_team_of_any_year(races, year):
    wins_by_team = dict()
    my_year = datetime.strptime(year, '%Y').year
    for race in races:
        if race.race_date.year == my_year:
            if race.team not in wins_by_team:
                wins_by_team[race.team] = 0
            if race.fin_pos == 1:
                wins_by_team[race.team] += 1
    
    most_wins = sorted(wins_by_team.items(), key=lambda x: -x[1])[0][0]

    return most_wins