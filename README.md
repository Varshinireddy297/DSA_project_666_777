
# Chat Message Search

## About the Project
This project searches for words or patterns in chat messages using two algorithms: Naive String Matching and KMP.

It finds all matching positions, highlights the matched text, and compares both algorithms.

## Features
- Search multiple patterns.
- Find all matching positions.
- Count total matches.
- Highlight matching text.
- Compare Naive and KMP algorithms.
- Display character comparisons.

## Algorithms Used
1. **Naive String Matching:** Checks the pattern at every position in the message.
2. **KMP Algorithm:** Uses the LPS array to avoid unnecessary comparisons.

## Technologies Used
- C++
- Strings
- Vectors
- String Matching Algorithms

## Example
Message:
`ABABABA`
Pattern:
`ABA`
Output:
- Number of matches: 3
- Starting indices: 0, 2, 4
- Highlighted message: `[[ABABABA]]`
## Conclusion
This project helps us understand and compare two string-matching algorithms and their performance.
