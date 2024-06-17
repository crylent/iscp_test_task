import math
import random
import timeit


# Хорошая функция, минусов нет
def is_even(value):
    return value % 2 == 0


# По времени хуже
def is_even_2(value):
    return math.remainder(value, 2) == 0


# По времени плюс-минус так же, по читаемости кода хуже
def is_even_3(value):
    return not value & 1


# Ещё хуже по читаемости...
def is_even_4(value):
    return (value >> 1 << 1) == value


n = 10000
k = 1000
print(timeit.timeit(lambda: is_even(random.randrange(k)), number=n))
print(timeit.timeit(lambda: is_even_2(random.randrange(k)), number=n))
print(timeit.timeit(lambda: is_even_3(random.randrange(k)), number=n))
print(timeit.timeit(lambda: is_even_4(random.randrange(k)), number=n))
