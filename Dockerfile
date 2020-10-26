FROM ubuntu:latest
MAINTAINER Yusuke Tabata <tabata.yusuke@gmail.com>

RUN apt-get update && apt-get -y update
RUN apt-get -y install python3-pip
RUN pip3 install gyp-next
RUN apt-get -y install git
RUN git clone --depth 1 --recursive https://github.com/nlsynth/karuta
WORKDIR karuta
RUN python3 configure
RUN make
RUN make install

ENTRYPOINT bash
