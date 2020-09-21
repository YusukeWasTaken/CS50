SELECT DISTINCT name FROM people JOIN stars on stars.person_id = people.id WHERE movie_id in
(
	SELECT movie_id FROM stars
	JOIN people on stars.person_id = people.id
	WHERE name = "Kevin Bacon" and birth = 1958
)
and name != "Kevin Bacon"