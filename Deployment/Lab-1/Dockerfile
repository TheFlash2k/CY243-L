FROM ubuntu:22.04

RUN apt update
RUN apt install sudo git curl wget net-tools -y
RUN useradd -m "kali"
RUN echo "kali:kali" | chpasswd
RUN usermod -aG sudo kali
USER kali
WORKDIR /home/kali
COPY ./data/README.md README.md
COPY ./data/check.sh /bin/check