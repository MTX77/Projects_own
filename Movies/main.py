import csv
from datetime import datetime 
from collections import namedtuple

Movie = namedtuple("Movie",['id', 'title', 'original_language', 'release_date', 'vote_average',
'popularity', 'adult', 'genres'])

movies_file_name = "movies_fp.csv"
genres_file_name = "movies_fp_genres.csv"

def read_dictionary_genres(genres_file_name):
    with open(genres_file_name, 'r') as csv_file:
        reader = csv.reader(csv_file, delimiter=':')
        next(reader)

        dict_genres = dict()
        for id, genre in reader:
            good_genre = genre.strip(' ').split(', ')

            if id not in dict_genres.keys():
                set_genres = set(good_genre)
                dict_genres[id] = set_genres
            else:
                set_genres = set(good_genre).union(dict_genres[id])
                dict_genres[id] = set_genres

        return dict_genres


def read_movies(movies_file_name, genres_file_name):
    with open(movies_file_name) as csv_file:
        reader = csv.reader(csv_file, delimiter=',')
        next(reader)

        dict_genres = read_dictionary_genres(genres_file_name)
        Movies = list()

        for id, title, original_language, release_date, vote_average, popularity, adult in reader:
            good_date = datetime.strptime(release_date, '%Y-%m-%d').date()
            good_vote = float(vote_average)
            good_popularity = int(popularity)
            good_adult = bool(adult)

            good_genres = set()
            for k, v in dict_genres.items():
                if id == k:
                    good_genres = v
                    my_movie = Movie(id, title, original_language, good_date, good_vote, good_popularity, good_adult, good_genres)
                    Movies.append(my_movie)

    return Movies


def most_frequent_genre(movies):
    dict_genres_frequency = dict()
    for movie in movies:
        for genre in movie.genres:
            if genre not in dict_genres_frequency.keys():
                count = 1
                dict_genres_frequency[genre] = count
            else:
                count = dict_genres_frequency[genre] + 1
                dict_genres_frequency[genre] = count

    max_value = max(dict_genres_frequency.values())
    
    for k, v in dict_genres_frequency.items():
        if v == max_value:
            most_f_genre = k

    return (most_f_genre, max_value)


def top_rated_by_language(movies):
    list_languages = list()
    for movie in movies:
        if movie.original_language not in list_languages:
            list_languages.append(movie.original_language)

        dict_laguages_rank = dict()
    for language in list_languages:
        top_movie = ''
        popularity = 0
        rating = 0
        for movie in movies:
            if language == movie.original_language:

                if movie.popularity > popularity:
                    popularity = movie.popularity
                    top_movie = movie
                    rating = movie.vote_average
                elif movie.popularity == popularity:
                    if movie.vote_average > rating:
                        popularity = movie.popularity
                        top_movie = movie
                        rating = movie.vote_average

        dict_laguages_rank[language] = top_movie
    
    return dict_laguages_rank

                
def media_ratings(movies, my_genres):
    sum = 0
    count = 0
    for movie in movies:
        if my_genres.issubset(movie.genres):
            sum += movie.vote_average
            count += 1

    if count == 0:
        return 0.0
    
    return sum/count


def top_n_by_genre(movies, n):
    list_genres = list()
    for movie in movies:
        for genre in movie.genres:
            if genre not in list_genres:
                list_genres.append(genre)

    dict_top_genres = dict()
    for my_genre in list_genres:
        list_top_movies = list()
        for movie in movies:
            for genre in movie.genres:
                if genre == my_genre:
                    list_top_movies.append(movie)
        list_top_movies = sorted(list_top_movies, key=lambda avg: -avg.vote_average)
        dict_top_genres[my_genre] = list_top_movies[:n]

    return dict_top_genres

def test1(Movies):
    print('Test 1:')
    print('First: ', Movies[0])
    print('Latest: ', Movies[-1])
    print()

def test2(Movies):
    print('Test 2:')
    print('The most frequent genre is: ', most_frequent_genre(Movies))
    print()

def test3(Movies):
    print('Test 3:')
    print('Best in Spanish (es): ', top_rated_by_language(Movies)['es'])
    print()

def test4(Movies, genres):
    print('Test 4:')
    print(genres)
    print(media_ratings(Movies, genres))
    print()

def test5(Movies, n):
    print('Test 5:')
    print('Top 2 Fake:',top_n_by_genre(Movies, n)['Fake'])
    print()
    print('Top 2 Action:',top_n_by_genre(Movies, n)['Action'])



def main():
    Movies = read_movies(movies_file_name, genres_file_name)

    test1(Movies)
    test2(Movies)
    test3(Movies)
    test4(Movies, {'Action', 'Adventure', 'Fake'})
    test4(Movies, {'Action', 'Thriller'})
    test5(Movies, 2)


if __name__ == '__main__':
    main()
