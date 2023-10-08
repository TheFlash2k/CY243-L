FROM ubuntu:22.04

RUN apt update
RUN apt install sudo nano vim net-tools iproute2 -y
RUN useradd -m "kali" -s "/bin/bash"
RUN echo "kali:kali" | chpasswd
RUN usermod -aG sudo kali
WORKDIR /home/kali
COPY ./checker/checker /bin/checker
COPY ./README.md /home/kali/README.md
RUN chown kali:kali /home/kali/README.md
RUN chmod 644 /home/kali/README.md
RUN chown root:root /bin/checker
RUN chmod 4755 /bin/checker
ENV HOSTNAME="quiz-1"
USER kali