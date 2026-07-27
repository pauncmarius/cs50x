-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year
select people.id, people.name
from people
join stars on people.id = stars.person_id
join movies on stars.movie_id = movies.id
where year = 2004
order by people.birth asc;

