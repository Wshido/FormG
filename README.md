<div align="center">

# FormG

**Клиент-серверное приложение для графического отображения ветвящейся (кусочной) функции**

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-6-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)
![PostgreSQL](https://img.shields.io/badge/PostgreSQL-16-4169E1?style=for-the-badge&logo=postgresql&logoColor=white)

[GitHub](https://github.com/Wshido/FormG) &bull; [Wiki](https://github.com/Wshido/FormG/wiki)

Реализовано в рамках дисциплины «Технологии и методы программирования»

</div>

---

## О проекте

Приложение предназначено для построения и визуализации кусочных функций. Клиент подключается к серверу по TCP, передаёт параметры функции, а сервер выполняет вычисления, сохраняет результаты в базу данных и отправляет уведомления по электронной почте.

## Технологический стек

| Компонент | Технология |
|-----------|------------|
| Язык | C++17 |
| Фреймворк | Qt 6 (Widgets, Network, SQL) |
| База данных | PostgreSQL 16 |
| Протокол | TCP, порт 11999 |
| Почта | SMTP через Gmail (SSL, порт 465) |
| Контейнеризация | Docker (Ubuntu 24.04) |
| Тестирование | Qt Test |
| Документация | Doxygen |

## Архитектура

```
┌──────────────┐       TCP        ┌──────────────┐      SQL       ┌──────────────┐
│              │ ──────────────►  │              │ ────────────►  │              │
│    Клиент    │                  │    Сервер    │                │  PostgreSQL  │
│  (Qt Widgets)│ ◄──────────────  │  (Qt 6 Net)  │ ◄────────────  │   Database   │
│              │                  │              │                │              │
└──────────────┘                  └──────┬───────┘                └──────────────┘
                                         │
                                         │ SMTP
                                         ▼
                                  ┌──────────────┐
                                  │   Почтовый   │
                                  │   сервер     │
                                  └──────────────┘
```

Приложение состоит из двух частей:

- **Клиент** (`UI/Timpproject/`) — GUI на Qt Widgets, подключается к серверу по TCP
- **Сервер** (`Server/TCPserver/`) — TCP-сервер на Qt 6 (Network + SQL), обрабатывает запросы клиентов, работает с PostgreSQL и отправляет email через SMTP

## Docker

Контейнеризация серверной части обеспечивает изоляцию окружения, портативность и единообразие среды. Контейнер экспортирует TCP-порт **11999** для приёма клиентских подключений.

Сборка и запуск:

```bash
cd Server/TCPserver/docker
docker-compose up --build
```

Поднимаются два контейнера:
- **PostgreSQL** — порт `5432`
- **TCP-сервер** — порт `11999`

## Структура проекта

```
FormG/
├── UI/
│   └── Timpproject/          # GUI-клиент (Qt Widgets)
│       ├── *.pro             # Проектный файл Qt
│       ├── *.cpp / *.h       # Исходные коды
│       └── *.ui              # UI-формы
├── Server/
│   └── TCPserver/
│       ├── docker/           # Dockerfile + docker-compose.yml
│       ├── tcpserver.*       # TCP-сервер
│       ├── controller.*      # Контроллер
│       ├── serverdb.*        # Работа с БД
│       └── emailservice.*    # Отправка email
├── BD/
│   └── BDbackup.sql          # Резервная копия БД
├── tests/                    # Модульные тесты (Qt Test)
├── docs/                     # Doxygen-документация (HTML)
├── GIT.txt                   # Ссылки на репозиторий
├── otchet.pdf                # Отчёт по проекту
├── .gitignore
└── README.md
```

## Сборка и запуск

### Клиент (локально)

```bash
cd UI/Timpproject
qmake6 Timpproject.pro
make -j$(nproc)
./Timpproject
```

### Сервер (Docker)

```bash
cd Server/TCPserver/docker
docker-compose up --build
```

### Документация

```bash
cd docs
doxygen Doxyfile
# Открыть docs/html/index.html
```

### Тестирование

```bash
cd tests
qmake && make
./tests
```

## Ссылки

- [GitHub репозиторий](https://github.com/Wshido/FormG)
- [Wiki проекта](https://github.com/Wshido/FormG/wiki)
