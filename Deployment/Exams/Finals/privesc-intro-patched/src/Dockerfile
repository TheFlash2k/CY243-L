FROM ubuntu:20.04

RUN apt update
RUN DEBIAN_FRONTEND="noninteractive" apt install -y \
    vim nano git wget curl tmux sudo \
    python3 python3-pip gcc g++ make \
    python3-dev python3-setuptools \
    build-essential libssl-dev libffi-dev openssl \
    openssh-server openssh-client net-tools

RUN rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash vancejoy
RUN echo 'vancejoy:p0sty_g0a73d' | chpasswd
RUN mkdir -p /home/vancejoy/.ssh
RUN ssh-keygen -t rsa -f /home/vancejoy/.ssh/id_rsa -q -P ""
RUN cat /home/vancejoy/.ssh/id_rsa.pub >> /home/vancejoy/.ssh/authorized_keys
RUN chmod 600 /home/vancejoy/.ssh/authorized_keys
RUN chown -R vancejoy:vancejoy /home/vancejoy/.ssh

# Run the SSH service:
RUN sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config

COPY docker-entrypoint.sh /tmp/docker-entrypoint.sh
RUN chmod +x /tmp/docker-entrypoint.sh
ENTRYPOINT [ "/tmp/docker-entrypoint.sh" ]

COPY src.c /opt/
COPY Makefile /opt/