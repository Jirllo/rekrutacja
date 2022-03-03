# -*- coding: utf-8 -*-

import sys
import os.path
from collections import Counter 
import string

args = sys.argv[1:]

file_name = args[0]
try:
    with open(file_name, 'r') as file:
        collection = Counter()
        line = file.readline()
        while line:
            text = line.lower()
            collection.update(Counter(text))
            line = file.readline()
        
        # print result
        for letter in list(string.ascii_lowercase):
            print(f"{letter}/{letter.upper()} occurs {collection[letter]} times")
        
        
except FileNotFoundError:
    print("File not exist")

