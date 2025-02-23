# otus-hw7
Создаем утилиту для парсинга и комплексного логгирования пакетных команд. Стремимся к снижению зависимостей между модулями.

### Разработать программу для пакетной обработки команд.

Команды считываются построчно из стандартного ввода и обрабатываются блоками по N команд. Одна команда - одна строка, конкретное значение роли не играет. Если данные закончились - блок завершается принудительно. Параметр N передается как единственный параметр командной строки в виде целого числа.
Размер блока можно изменить динамически, если перед началом блока и сразу после дать команды `{` и `}` соответственно. Предыдущий пакет при этом принудительно завершается. Такие блоки могут быть включены друг в друга при этом вложенные команды `{` и `}` игнорируются (но не сами блоки). Если данные закончились внутри динамического блока, весь динамический блок игнорируется.
Вместе с выводом в консоль блоки должны сохранятся в отдельные файлы с именами bulk1517223860.log , где 1517223860 - это время получения первой команды из блока. По одному файлу на блок.

- **Требования к реализации**

  Бинарный файл должен называться bulk.
- **Проверка**

  Задание считается выполненным успешно, если после установки пакета и запуска с тестовыми данными вывод соответствует описанию. Данные подаются на стандартный вход построчно с паузой в 1 секунду для визуального контроля. Будет отмечена низкая связанность обработки данных, накопления пачек команд, вывода в консоль и сохранения в файлы.