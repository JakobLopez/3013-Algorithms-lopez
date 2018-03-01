```
Name: Jakob Lopez
Date: February 28,2018
Assignment: Program 3
Description:
  Part 1:
    This program randomly generates 10,000 words. 5 different word component files are read into array and then randomly 
    selected at an index to choose a random component. A heurisitic is designed to combine different versions of these 
    word components in order to make a crazy word.
  Part 2:
    The word components are read into an AVL and BS tree. Each word component of the generated crazy word is search 
    for in the trees. A counter variable is placed in both trees so that we can compare the number of comparisons 
    between each tree. This analysis will help us conclude which tree is more practical. Does the overhead of an AVL 
    tree weaken its chances against a slower searching,but much simpler BST? From this program, I have learned that 
    I much prefer the simple BST over the AVL tree.

Files:

| |__generate_words.cpp
| |__BSTree.h
| |__tenthousandwords.txt
| |__word_files
| | |__nouns.txt
| | |__adverbs.txt
| | |__animals.txt
| | |__adjectives.txt
| | |__verbs.txt
| |__README.md
| |__analysis.out
| |__analyze_trees.exe
| |__analyze_trees.cpp
| |__AVLtree.h
```
