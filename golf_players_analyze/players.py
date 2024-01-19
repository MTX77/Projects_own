import csv
from datetime import datetime
from typing import *

Player = NamedTuple('Player', [('name',str), ('license',str),('date_birth',datetime),('federation',float),('handicap',str),('date_update',datetime),('senior',bool),('results',List[int])])

def read_players(path: str) -> List[Player]:
    with open(path, 'r', encoding='UTF-8') as csv_file:
        reader = csv.reader(csv_file, delimiter=';')
        next(reader)

        Players = list()
        for name, license, date_birth, federation, handicap, date_update, senior, results in reader:
            birth = datetime.strptime(date_birth, '%d/%m/%Y').date()
            good_handicap = float(handicap)
            update = datetime.strptime(date_update, '%d/%m/%Y %H:%M:%S')
            if senior == 'S':
                good_senior = True
            elif senior == 'N':
                good_senior = False
            my_resoults = results.split(',')
            good_resoults = list()
            for i in my_resoults:
                i = int(i)
                good_resoults.append(i)
            

            my_player = Player(name, license, birth, federation, good_handicap, update, good_senior, good_resoults)
            Players.append(my_player)

    return Players

def best_players(players: List[Player], year: str, n: int) -> List:
    my_year = datetime.strptime(year, '%Y')
    dict_best_players = dict()
    for player in players:
        if player.date_birth.year == my_year.year:
            if player.license not in dict_best_players:
                dict_best_players[player.license] = player.name, player.handicap
    
    sorted_dict = dict(sorted(dict_best_players.items(), key=lambda x: x[1][1]))
    my_list = list()
    for k,v in sorted_dict.items():
        my_list.append((k,v[0],v[1]))

    return my_list[:n]

def players_per_hits(players: List[Player]) -> List:
    dict_strokes_players = dict()
    for player in players:
        for stroke in player.results:
            if stroke not in dict_strokes_players:
                dict_strokes_players[stroke] = {player.license}
            else:
                my_set = dict_strokes_players[stroke]
                my_set.add(player.license)
                dict_strokes_players[stroke] = my_set

    sorted_dict = dict(sorted(dict_strokes_players.items(), key=lambda x: -x[0]))

    my_list = list()
    for k,v in sorted_dict.items():
        my_list.append((k,v))

    return my_list


def average_last_results(players: List[Player], d1: Optional[str]=None, d2: Optional[str]=None) -> List:
    dict_avg_seniors = dict()
    if d1 != None: date1 = datetime.strptime(d1, '%Y-%m-%d').date()
    if d2 != None: date2 = datetime.strptime(d2, '%Y-%m-%d').date()
    for player in players:
        if player.senior == True:
            suma = 0
            count = 0
            for x in player.results:
                suma += x
                count += 1
            avg = suma / count
            if d1 == None and d2 == None:
                dict_avg_seniors[player.license] = avg
            elif d1 == None and player.date_update.date() <= date2:
                dict_avg_seniors[player.license] = avg
            elif player.date_update.date() >= date1 and d2 == None:
                dict_avg_seniors[player.license] = avg
            elif player.date_update.date() >= date1 and player.date_update.date() <= date2:
                dict_avg_seniors[player.license] = avg

    my_list = list()
    for k,v in dict_avg_seniors.items():
        my_list.append((k,v))

    return my_list


def lower_handicap_player_by_federation(players: List[Player]) -> Dict:
    dict_federation_player = dict()
    for player in players:
        if player.federation not in dict_federation_player:
            dict_federation_player[player.federation] = player.name, player.handicap
        else:
            prev_score = dict_federation_player[player.federation][1]
            if player.handicap <= prev_score:
                dict_federation_player[player.federation] = player.name, player.handicap

    return dict_federation_player


def handicap_average(players: List[Player]) -> Dict:
    dict_handicaps = dict()
    for player in players:
        score = min(player.results)
        if player.handicap not in dict_handicaps:
            count = 1
            dict_handicaps[player.handicap] = [score], count
        else:
            count = dict_handicaps[player.handicap][1] + 1
            temp = dict_handicaps[player.handicap][0]
            temp.append(score)
            dict_handicaps[player.handicap] = temp, count

        dict_avg_of_handicaps = dict()
        for k,v in dict_handicaps.items():
            suma = 0
            for value in v[0]:
                suma += value
            dict_avg_of_handicaps[k] = suma / v[1]

    sorted_dict = dict(sorted(dict_avg_of_handicaps.items(), key=lambda x: x[0]))

    return sorted_dict

def difference_handicaps(avg_of_handicaps: Dict) -> List:
    diff_of_handicaps = list()
    prev = list(avg_of_handicaps.items())[0]

    for k in list(avg_of_handicaps.items())[1:]:
        v1 = str(prev[0])
        v2 = str(k[0])
        my_string =  v1 + ' vs ' + v2
        diff_of_handicaps.append((my_string, prev[1] - k[1]))
        prev = k

    return diff_of_handicaps


def comparison_of_best_results_according_to_handicap(players: List[Player]) -> List:
    avg_of_handicaps = handicap_average(players)
    return difference_handicaps(avg_of_handicaps)