import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("You need 2 arg!")
        sys.exit(1)

    file_csv = sys.argv[1]
    file_txt = sys.argv[2]

    if not file_csv.endswith(".csv"):
        print("First arg should be .../file.csv!")
        sys.exit(1)

    if not file_txt.endswith(".txt"):
        print("Second arg should be .../file.txt!")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(file_csv) as file:
        database = list(csv.DictReader(file))
    #print(database)

    # TODO: Read DNA sequence file into a variable
    with open(file_txt) as file:
        txt = file.read()
    #print(txt)

    # TODO: Find longest match of each STR in DNA sequence
    list_columns = list(database[0].keys())[1:] #we take first row, extract the keys from list and will pass first key , name

    counts = {}
    for string in list_columns:
        counts[string] = longest_match(txt, string)

    #print(counts)

    # TODO: Check database for matching profiles
    #searching for matching all STR, if one is wrong => no res
    for i in database:
        match = True
        for string in list_columns:
            if int(i[string]) != counts[string]:
                match = False
                break

        if match:
            print(i["name"])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
