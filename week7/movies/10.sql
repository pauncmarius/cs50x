-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0
select distinct people.name
from people
join directors on people.id=directors.person_id
join movies on directors.movie_id = movies.id
join ratings on movies.id=ratings.movie_id
where rating >= 9;
