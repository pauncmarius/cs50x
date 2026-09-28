# CS50x (Introduction to Computer Science)
Although I already hold a Computer Science degree, I chose to complete CS50x (Harvard/edX) to refresh and reinforce my fundamentals through a rigorous, problem-solving and algorithmic thinking approach. In a field that evolves quickly, going back to solid foundations in data structures, algorithms, memory management, and complexity helps me write cleaner code and understand more deeply the technologies I work with daily (Java/Spring Boot, PySpark, Kotlin). It's also a demonstration of my discipline for continuous self-learning, going beyond what a standard CV can show.

## Week 0 – Scratch
A free-form project built visually in Scratch (no text-based code). 
Minimum requirements: at least 2 sprites, 3 scripts, use of one condition, 
one loop, and one variable, plus a sound. Goal: introduction to 
algorithmic thinking through visual blocks.

## Week 1 – C
First programs written in the C language, focused on basic syntax, 
input/output, and conditional logic:
- **Hello / Mario** – printing text and building a pyramid of characters 
  using nested loops.
- **Cash / Credit** – calculating optimal change (greedy algorithm) and 
  validating a credit card number using the Luhn algorithm.

## Week 2 – Arrays
Introduction to arrays, strings, and character manipulation:
- **Readability** – calculating a text's readability score (Coleman-Liau 
  formula).
- **Caesar / Substitution** – encrypting/decrypting text using classic 
  ciphers (letter shifting, and key-based substitution respectively).

## Week 3 – Algorithms
Focus on search, sorting algorithms, and complexity:
- **Runoff** – simulating a ranked-choice election, successively 
  eliminating the candidate(s) with the fewest votes.
- **Tideman (ranked pairs)** – determining the winner of an election by 
  comparing candidate pairs and building an acyclic graph (avoiding 
  contradictory "locked" cycles).

## Week 4 – Memory
Introduction to pointers, memory allocation, and file I/O in C:
- **Volume** – manipulating a WAV audio file's amplitude by modifying 
  raw byte values directly in the file header/data.
- **Filter** – applying image filters (grayscale, sepia, reflection, 
  box blur) to BMP images through direct pixel/array manipulation.
- **Recover** – recovering JPEG images from a forensic memory image by 
  scanning for file signatures (magic numbers) and reconstructing files 
  byte-by-byte.

## Week 5 – Data Structures
Introduction to dynamic data structures, memory allocation, and recursion:
- **Inheritance** – simulating the inheritance of blood types across a 
  family tree, using structs and recursion to generate and display 
  successive generations of parents.
- **Speller** – implementing a high-performance spell checker, using a 
  data structure of choice (hash table) to load a dictionary and quickly check words in a text, with a focus on optimizing real-world runtime.

## Week 6 – Python
Revisiting earlier problem sets in Python, transitioning from C's low-level 
syntax to a higher-level, more expressive language:
- **Hello** – printing a simple greeting to the user.
- **Mario** – rebuilding the pyramid of characters from Week 1, now using Python's loop and string-formatting constructs.
- **Cash / Credit** – reimplementing the greedy change-making algorithm 
  and/or Luhn's algorithm for credit card validation, this time in Python.
- **Readability** – recalculating the Coleman-Liau readability score, 
  leveraging Python's simpler string and list handling.
- **DNA** – identifying a person from a DNA sample by counting the 
  longest run of consecutive repeats of given STRs (Short Tandem Repeats) in a sequence, and matching the resulting profile against a CSV database of known individuals.

## Week 7 – SQL
Introduction to relational databases and structured queries:
- **Songs** – writing SQL queries against a SQLite database of Spotify's 
  top 100 streamed songs of 2018, exploring joins between artists and 
  songs and analyzing audio features like danceability, energy, and 
  tempo.
- **Movies** – writing SQL queries against an IMDb-based database of 
  movies, directors, actors, and ratings to answer questions involving 
  joins across multiple related tables.
- **Fiftyville** – solving a mystery ("who stole the CS50 duck?") by 
  writing a sequence of SQL queries across various town record tables 
  (crime reports, interviews, bank records, flight logs, phone calls, 
  etc.), progressively narrowing down the thief, their escape city, and 
  their accomplice.

## Week 8 – HTML, CSS, JavaScript
Introduction to front-end web development, building static and interactive pages using the three core web languages:
- **Homepage** – building a personal website with at least four linked HTML pages, using ten or more distinct HTML tags, a custom `styles.css` with at least five selectors and five properties, an integrated Bootstrap component, and a JavaScript-driven interactive feature, all responsive across mobile and desktop.
- **Trivia** – designing a single-page trivia quiz with a multiple-choice section and a free-response section, using JavaScript event listeners to validate answers and dynamically change button/input colors and feedback text based on correctness.

## Week9 - Flask
Introduction to server-side web development using Python, Flask, HTML, CSS, Jinja, and SQL:
- **Birthdays** – building a web application to record and display people’s birthdays. Users can add a name, birth month, and day through a form; the app stores the entries in a SQLite database and displays them in a table. This project introduces Flask routes, form handling, SQL queries, and dynamically rendered HTML templates.
- **Finance** – building a stock-trading simulator where users can register and log in, look up stock prices, buy and sell shares, and view their portfolio and transaction history. The app uses Flask, Jinja templates, and SQLite to manage accounts and transactions. As a personal touch, I added a profile page that lets users change their username and password, with validation checks.

## Week10