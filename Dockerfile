FROM debian:stable-slim AS build

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    make \
    libc6-dev \
    locales \
    fonts-firacode \
    fonts-dejavu \
    fonts-noto \
    && rm -rf /var/lib/apt/lists/*

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen

ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8
ENV TERM=xterm-256color

WORKDIR /app
COPY src/ .

RUN make

FROM debian:stable-slim

RUN apt-get update && apt-get install -y \
    libc6 \
    locales \
    xterm \
    fonts-firacode \
    fonts-dejavu \
    fonts-noto \
    && rm -rf /var/lib/apt/lists/*

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen

ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8
ENV TERM=xterm-256color

WORKDIR /app

COPY --from=build /app/app ./app
COPY --from=build /app/screens ./screens

CMD ["./app"]
