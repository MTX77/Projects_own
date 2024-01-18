import csv
from datetime import datetime, date
from typing import *
 
Basketball_Match = NamedTuple('Basketball_Match', [('date', date), ('team1', str), ('team2', str), ('competition', str), ('points_eq1', int), ('points_eq2', int), ('fouls_eq1', int), ('fouls_eq2', int)])

def points_to_score(points: str) -> Tuple[int, int]:
    points_vs = points.split('*')
    sum1 = 0
    sum2 = 0
    for x in points_vs:
        good_p = x.split('-')
        sum1 += int(good_p[0])
        sum2 += int(good_p[1])
    return (sum1, sum2)
        

def read_match(path: str) -> List[Basketball_Match]:
    with open(path, 'r', encoding='UTF-8') as csv_file:
        reader = csv.reader(csv_file, delimiter=';')
        next(reader)

        Matches = list()
        for date, team1, team2, competition, points, fouls_eq1, fouls_eq2 in reader:
            good_date = datetime.strptime(date, '%d/%m/%Y').date()
            good_fouls_eq1 = int(fouls_eq1)
            good_fouls_eq2 = int(fouls_eq2)

            points_1_2 = points_to_score(points)

            my_match = Basketball_Match(good_date, team1, team2, competition, points_1_2[0], points_1_2[1], good_fouls_eq1, good_fouls_eq2)
            Matches.append(my_match)
    return Matches        


def team_with_most_fouls(matches: List[Basketball_Match], teams: Optional[Set[str]]=None) -> Tuple[str, int]:
    dict_teams_fouls = dict()
    for match in matches:
        if teams is None:
            if match.team1 not in dict_teams_fouls:
                dict_teams_fouls[match.team1] = match.fouls_eq1
            else:
                dict_teams_fouls[match.team1] += match.fouls_eq1
            if match.team2 not in dict_teams_fouls:
                dict_teams_fouls[match.team2] = match.fouls_eq2
            else:
                dict_teams_fouls[match.team2] += match.fouls_eq2
        else:
            if match.team1 in teams:
                if match.team1 not in dict_teams_fouls:
                    dict_teams_fouls[match.team1] = match.fouls_eq1
                else:
                    dict_teams_fouls[match.team1] += match.fouls_eq1
            if match.team2 in teams:
                if match.team2 not in dict_teams_fouls:
                    dict_teams_fouls[match.team2] = match.fouls_eq2
                else:
                    dict_teams_fouls[match.team2] += match.fouls_eq2
    
    max_val = max(dict_teams_fouls.values())
    my_k =''
    for k,v in dict_teams_fouls.items():
        if v == max_val:
            my_k = k
    return (my_k, max_val)


def average_points_per_team(matches: List[Basketball_Match], competition: str) -> Dict[str, float]:
    dict_points = dict()
    for match in matches:
        if match.competition == competition:
            if match.team1 not in dict_points:
                points = match.points_eq1
                count = 1
                dict_points[match.team1] = points, count
            else:
                points = dict_points[match.team1][0] + match.points_eq1
                count = dict_points[match.team1][1] + 1
                dict_points[match.team1] = points, count
            if match.team2 not in dict_points:
                points = match.points_eq2
                count = 1
                dict_points[match.team2] = points, count
            else:
                points = dict_points[match.team2][0] + match.points_eq2
                count = dict_points[match.team2][1] + 1
                dict_points[match.team2] = points, count

    dict_avg_points = dict()
    for k,v in dict_points.items():
        dict_avg_points[k] = round(v[0] / v[1], 2)

    return dict_avg_points


def difference_points_scored(matches: List[Basketball_Match], team: str) -> List[int]:
    sorted_maches = sorted(matches, key = lambda match: match.date)
    dict_points_team = dict()
    for match in sorted_maches:
        if match.team1 == team:
            if match.team1 not in dict_points_team:
                dict_points_team[match.team1] = [match.points_eq1]
            else:
                temp = dict_points_team[match.team1]
                temp.append(match.points_eq1)
                dict_points_team[match.team1] = temp
        elif match.team2 == team:
            if match.team2 not in dict_points_team:
                dict_points_team[match.team2] = [match.points_eq2]
            else:
                temp = dict_points_team[match.team2]
                temp.append(match.points_eq2)
                dict_points_team[match.team2] = temp

    list_dif_points = list()
    temp_list = list(dict_points_team.values())[0]
    prev = temp_list[0]
    for value in temp_list[1:]:
        dif = value - prev
        list_dif_points.append(dif)
        prev = value

    return list_dif_points

def wins_per_team(matches: List[Basketball_Match]) -> Dict[str, int]:
    dict_team_wins = dict()
    for match in matches:
        if match.points_eq1 > match.points_eq2:
            winner = match.team1
        elif match.points_eq2 > match.points_eq1:
            winner = match.team2

        if winner not in dict_team_wins:
            dict_team_wins[winner] = 1
        else:
            dict_team_wins[winner] += 1

    sorted_dict = dict(sorted(dict_team_wins.items(), key=lambda x: -x[1]))
    
    return sorted_dict


def teams_minimum_wins(matches: List[Basketball_Match], n: int) -> List[str]:
    dict_team_wins = wins_per_team(matches)
    min_wins = list()
    for k,v in dict_team_wins.items():
        if v >= n:
            min_wins.append(k)

    return min_wins

def teams_most_wins_per_year(matches: List[Basketball_Match], n: int) -> Dict[int, List[str]]:
    dict_dates_wins = dict()
    for match in matches:
        if match.date.year not in dict_dates_wins:
            dict_dates_wins[match.date.year] = [match]
        else:
            temp = dict_dates_wins[match.date.year]
            temp.append(match)
            dict_dates_wins[match.date.year] = temp

    my_dict = dict()
    for k,v in dict_dates_wins.items():
        my_dict[k] = teams_minimum_wins(v, n)

    return my_dict