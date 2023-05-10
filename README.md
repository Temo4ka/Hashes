# Хеш-таблица




## Цель работы


    1. Исследовать различные хэш-функции на достоинства и недостатки для кодирования объектов в хэш-таблице.
    2. Изучить способы оптимизации программы методами: ассэмблерной вставки, ассэмблерного варината функции и SIMD оптимизации.


## О структуре


    Хэш-таблица - массив списков, где каждому значению хэша соотвествует отдельный список, в котором хранятся значения захэшированных элементов. Чем меньше размер списков, тем меньше времени будет затраченно на поиски элемента в структуре. Количество элементов в списке зависит от выбранной функции хэширования.
    В моей структуре так же хранятся текущее и максимально возможное количество элементов в таблице и указатель на хэш-функцию
    ![struct HashTable](source/hashtable.png)
    
    
## Ход работы 
    Основополгающей частью хэш-таблицы являеется хэш-функция, поэтому давайте проведём анализ следующих функций:
    1. **DumbHash** - возвращает всегда 1.
    ![DumbHash](source/DumbHash.png)
    2. **FirstByteHash** - возвращает ASCII код первого символа строки.
    ![FirstByteHash](source/FirstByteHash.png)
    3. **StrLenHash** - возвращает длину строки.
    ![StrLenHash](source/StrLenHash.png)
    4. **SumHash** - возвращает сумму всех ASCII кодов символов строки.
    ![SumHash](source/SumHash.png)
    5. **RolHash** - циклический сдвиг хеша влево и xor со значением элемента ключа.
    ![RolHash](source/RolHash.png)
    6. **RorHash** - циклический сдвиг хеша вправо и xor со значением элемента ключа.
    ![RorHash](source/RorHash.png)
