FROM ubuntu:18.04

# コンテナ内の作業用（ワーキング）ディレクトリ（絶対パスの必要）
WORKDIR /work

RUN   apt-get update && \
      apt-get upgrade -y && \
      apt-get install -y \
        build-essential \
        git \
        bzip2 \
        wget && \
      apt-get clean && \
      rm -rf /var/lib/apt/lists/*

RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj

WORKDIR /work/src

ENV PATH "/work/gcc-arm-none-eabi-9-2019-q4-major/bin:$PATH"
