FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    inotify-tools

WORKDIR /app

CMD ["bash", "/app/watch-and-rebuild.sh"]