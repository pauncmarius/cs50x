-- Keep a log of any SQL queries you execute as you solve the mystery.

--finding details using the hints
select *
from crime_scene_reports
where day = 28 and month = 7 and street = 'Humphrey Street';
--3 witnesses - bakery : 10:15am, year 2025
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time
--– each of their interview transcripts mentions the bakery.

--searching interviews
select *
from interviews
where day = 28 and month = 7 and year = 2025;
    --1.Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
    --2.I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
    --3.As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief
--say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

--checking security footage from bakery
select *
from bakery_security_logs
where day = 28 and month = 7 and year = 2025 and hour = 10 and minute > 15 and minute <= 25;
/*
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2025 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       | =>
| 261 | 2025 | 7     | 28  | 10   | 18     | exit     | 94KL13X       | =>
| 262 | 2025 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       | =>
| 263 | 2025 | 7     | 28  | 10   | 19     | exit     | 4328GD8       | =>
| 264 | 2025 | 7     | 28  | 10   | 20     | exit     | G412CB7       | =>
| 265 | 2025 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       | =>
| 266 | 2025 | 7     | 28  | 10   | 23     | exit     | 322W7JE       | =>
| 267 | 2025 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       | =>
+-----+------+-------+-----+------+--------+----------+---------------+


*/

--checking atm transactions before theft happened
select *
from atm_transactions
where day = 28 and month = 7 and year =2025 and atm_location = 'Leggett Street';
/*
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2025 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2025 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2025 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2025 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2025 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 275 | 86363979       | 2025 | 7     | 28  | Leggett Street | deposit          | 10     |
| 288 | 25506511       | 2025 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2025 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2025 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
*/

--searching flight and phone calls
select *
from phone_calls
where day = 28 and month = 7 and year = 2025 and duration <60;
/*
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2025 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2025 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2025 | 7     | 28  | 45       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2025 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2025 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2025 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2025 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2025 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2025 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+
*/

select *
from flights
join airports on flights.origin_airport_id = airports.id
where flights.day = 29 and flights.month = 7 and airports.city = 'Fiftyville'
order by flights.hour asc;

/*
+----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-----------------------------+------------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | id | abbreviation |          full_name          |    city    |
+----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-----------------------------+------------+
| 36 | 8                 | 4                      | 2025 | 7     | 29  | 8    | 20     | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
*/

--checking passengers for our flight
select pass
from passengers
where flight_id = 36;

/*
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 7214083635      | 2A   |
| 36        | 1695452385      | 3B   |
| 36        | 5773159633      | 4A   |
| 36        | 1540955065      | 5C   |
| 36        | 8294398571      | 6C   |
| 36        | 1988161715      | 6D   |
| 36        | 9878712108      | 7A   |
| 36        | 8496433585      | 7B   |
+-----------+-----------------+------+
*/

--now after having all details i need to combine the propfs and find the culprit
--i will work on my tables after each query from here
/*
+---------+---------------+
|  name   | license_plate |
+---------+---------------+
| Diana   | 322W7JE       |
| Bruce   | 94KL13X       |
+---------+---------------+
+---------+----------------+
|  name   | account_number |
+---------+----------------+
| Bruce   | 49610011       |
| Diana   | 26013199       |
+---------+----------------+

+---------+----------------+
|  name   |  phone_number  |
+---------+----------------+
| Diana   | (770) 555-1861 |
| Bruce   | (367) 555-5533 |
+---------+----------------+

+--------+-----------------+
|  name  | passport_number |
+--------+-----------------+
| Bruce  | 5773159633      |
+--------+-----------------+
*/
select license_plate
from bakery_security_logs
where day = 28 and month = 7 and year = 2025 and hour = 10 and minute > 15 and minute <= 25;

select name, license_plate
from people
where license_plate in (select license_plate
from bakery_security_logs
where day = 28 and month = 7 and year = 2025 and hour = 10 and minute > 15 and minute <= 25);

select account_number
from atm_transactions
where day = 28 and month = 7 and year =2025 and atm_location = 'Leggett Street' and transaction_type = 'withdraw';

select people.name, bank_accounts.account_number
from people
join bank_accounts on bank_accounts.person_id = people.id
where bank_accounts.account_number in (
    select account_number
    from atm_transactions
    where day = 28 and month = 7 and year =2025 and atm_location = 'Leggett Street' and transaction_type = 'withdraw');
--down to 4 people

select caller
from phone_calls
where day = 28 and month = 7 and year = 2025 and duration <60;

select name, phone_number
from people
where phone_number in (select caller
from phone_calls
where day = 28 and month = 7 and year = 2025 and duration <60);
--down to 2 people

select passport_number
from passengers
where flight_id = 36;

select name, passport_number
from people
where passport_number in (select passport_number
from passengers
where flight_id = 36);

--| Bruce  | 5773159633      | - all matches on him
--lets find where he was going

select destination_airport_id
from flights
where id = 36;

select *
from airports
where id = (select destination_airport_id
from flights
where id = 36);

--| 4  | LGA          | LaGuardia Airport | New York City |
--
--| 233 | (367) 555-5533 | (375) 555-8161 | 2025 | 7     | 28  | 45       |
--now lets see who was he talking to

select *
from people
where phone_number = '(375) 555-8161';

--| 864400 | Robin | (375) 555-8161 | NULL            | 4V16VO0       |
