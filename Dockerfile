FROM ubuntu:latest as build

USER root

EXPOSE 8081

RUN apt-get update && \
    apt-get install -y \
       g++ \
      libevent-dev \
      cmake

COPY . /app
COPY . /var/www

WORKDIR /app/build

RUN cmake .. && cmake --build .

CMD ./http_static_server