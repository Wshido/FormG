# ---- Build stage ----
FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    g++ \
    qt6-base-dev \
    libpq-dev \
    libssl-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY TCPserver.pro ./
COPY main.cpp ./
COPY tcpserver.h tcpserver.cpp ./
COPY controller.h controller.cpp ./
COPY serverdb.h serverdb.cpp ./
COPY emailservice.h emailservice.cpp ./

RUN qmake6 TCPserver.pro && make -j$(nproc)

# ---- Runtime stage ----
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    libqt6core6t64 \
    libqt6network6t64 \
    libqt6sql6t64 \
    libpq5 \
    libssl3 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/TCPserver ./

EXPOSE 11999

CMD ["./TCPserver"]
