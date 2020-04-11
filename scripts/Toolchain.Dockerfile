FROM gcc

RUN apt-get update \
    && apt-get install -y cmake ninja-build python-pip \
    && pip install gcovr

WORKDIR /app
