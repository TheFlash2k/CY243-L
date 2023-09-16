FROM ubuntu:22.04

RUN apt update
RUN apt install sudo git curl wget net-tools -y
RUN useradd -m "kali" -s "/bin/bash"
RUN echo "kali:kali" | chpasswd
RUN usermod -aG sudo kali
WORKDIR /home/kali
COPY ./README.md README.md
RUN chown kali:kali README.md
COPY ./check.sh /bin/check
# Just giving SETUID perms
RUN chown root:root /bin/check
RUN chmod 4755 /bin/check
USER kali