**Вопрос №3**

На языке Python или С++ предложить алгоритм, который быстрее всего (по процессорным тикам) отсортирует данный ей массив чисел. Массив может быть любого размера со случайным порядком чисел (в том числе и отсортированным). Объяснить, почему вы считаете, что функция соответствует заданным критериям.

---
---

Поразрядная сортировка с разрядностью 2 (`sort_radix2.cpp`) работает быстро, потому что не производит перестановку отдельных элементов и использует побитовые операции. Также я написал и проверил версию с возможностью задать любую разрядность (`sort_anyRadix.cpp`). Эта версия при разрядности 10 работает быстрее, чем при разрядности 2, но если сравнивать с первой версией, то выигрыш из-за увеличения разрядности перекрывается использованием математических операций вместо побитовых. В результате, первая версия работает значительно быстрее.