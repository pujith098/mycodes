"""
All-in-one Python Concepts Demo
Author: Pujit
"""

# ------------------------
# 1. VARIABLES & DATA TYPES
# ------------------------
integer_val = 10
float_val = 3.14
string_val = "Hello Python"
bool_val = True
list_val = [1, 2, 3]
tuple_val = (4, 5, 6)
set_val = {7, 8, 9}
dict_val = {"name": "Pujit", "age": 24}

print("Data Types:")
print(integer_val, float_val, string_val, bool_val)
print(list_val, tuple_val, set_val, dict_val, "\n")

# ------------------------
# 2. OPERATORS
# ------------------------
a, b = 5, 2
print("Operators:")
print("Addition:", a + b)
print("Division:", a / b)
print("Floor Division:", a // b)
print("Modulus:", a % b)
print("Exponent:", a ** b, "\n")

# ------------------------
# 3. CONDITIONALS
# ------------------------
print("Conditionals:")
if a > b:
    print(f"{a} is greater than {b}")
elif a == b:
    print("They are equal")
else:
    print(f"{a} is less than {b}", "\n")

# ------------------------
# 4. LOOPS
# ------------------------
print("Loops:")
for i in range(3):
    print("For loop i =", i)

count = 0
while count < 3:
    print("While loop count =", count)
    count += 1
print()

# ------------------------
# 5. FUNCTIONS
# ------------------------
def add(x, y=0):
    """Returns sum of x and y (default=0)"""
    return x + y

print("Functions:")
print("add(3,4) =", add(3, 4))
print("add(5) =", add(5), "\n")

# ------------------------
# 6. CLASSES & OBJECTS
# ------------------------
class Person:
    species = "Human"  # class variable

    def __init__(self, name, age):
        self.name = name   # instance variable
        self.age = age

    def greet(self):
        return f"Hi, I'm {self.name} and I'm {self.age} years old."

p1 = Person("Alice", 30)
print("Classes & Objects:")
print(p1.greet(), "\n")

# ------------------------
# 7. INHERITANCE
# ------------------------
class Student(Person):
    def __init__(self, name, age, course):
        super().__init__(name, age)
        self.course = course

    def greet(self):
        return f"I'm {self.name}, studying {self.course}."

s1 = Student("Bob", 20, "Python")
print("Inheritance & Method Overriding:")
print(s1.greet(), "\n")

# ------------------------
# 8. EXCEPTION HANDLING
# ------------------------
print("Exception Handling:")
try:
    result = 10 / 0
except ZeroDivisionError as e:
    print("Error:", e)
finally:
    print("Finally block executed.\n")

# ------------------------
# 9. FILE HANDLING
# ------------------------
print("File Handling:")
with open("sample.txt", "w") as f:
    f.write("Hello File!\nThis is Python.\n")

with open("sample.txt", "r") as f:
    print(f.read())

# ------------------------
# 10. MODULES & IMPORTS
# ------------------------
import math
print("Modules & Imports:")
print("Square root of 16:", math.sqrt(16), "\n")

# ------------------------
# 11. LAMBDA, MAP, FILTER, REDUCE
# ------------------------
from functools import reduce
nums = [1, 2, 3, 4, 5]

print("Lambda / Map / Filter / Reduce:")
print("Squares:", list(map(lambda x: x**2, nums)))
print("Evens:", list(filter(lambda x: x % 2 == 0, nums)))
print("Sum:", reduce(lambda x, y: x + y, nums), "\n")

# ------------------------
# 12. LIST / DICT COMPREHENSIONS
# ------------------------
print("Comprehensions:")
squares = [x**2 for x in range(5)]
even_dict = {x: "even" for x in range(10) if x % 2 == 0}
print(squares)
print(even_dict, "\n")

# ------------------------
# 13. GENERATORS & YIELD
# ------------------------
def my_gen(n):
    for i in range(n):
        yield i*i

print("Generators:")
for val in my_gen(5):
    print(val, end=" ")
print("\n")

# ------------------------
# 14. DECORATORS
# ------------------------
def decorator(func):
    def wrapper(*args, **kwargs):
        print("Before function call")
        res = func(*args, **kwargs)
        print("After function call")
        return res
    return wrapper

@decorator
def say_hello(name):
    print(f"Hello, {name}!")

print("Decorators:")
say_hello("Pujit")
print()

# ------------------------
# 15. MULTITHREADING
# ------------------------
import threading
import time

def worker(name):
    print(f"Thread {name} starting")
    time.sleep(1)
    print(f"Thread {name} finished")

print("Multithreading:")
t1 = threading.Thread(target=worker, args=("A",))
t2 = threading.Thread(target=worker, args=("B",))
t1.start(); t2.start()
t1.join(); t2.join()
print("Both threads completed\n")

# ------------------------
# END
# ------------------------
print("✅ All Python concepts demo complete!")

