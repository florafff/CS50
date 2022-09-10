import csv
import sys


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage:error")
    database=[]
    # TODO: Read database file into a variable
    with open(sys.argv[1],"r") as file1:
        reader=csv.reader(file1)
        for row in reader:
            database.append(row)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2],"r") as file2:
        DNA_seq=csv.reader(file2)
        for row in DNA_seq:
           String="".join(row)
    count=[]
    for i in range(1,len(database[0])) :
        count.append(str(longest_match(String,database[0][i])))
    flag=0
    for i in database:
        if count==i[1:]:
            print(i[0])
            flag=1
    if(flag==0):
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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
