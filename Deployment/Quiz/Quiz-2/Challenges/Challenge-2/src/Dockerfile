FROM ubuntu:20.04

RUN apt update
RUN DEBIAN_FRONTEND="noninteractive" apt install -y \
    vim nano git wget curl tmux sudo \
    python3 python3-pip gcc g++ make \
    python3-dev python3-setuptools \
    build-essential libssl-dev libffi-dev openssl \
    openssh-server openssh-client net-tools

RUN rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash ashfaq
RUN echo "ashfaq:ashfaq" | chpasswd
RUN mkdir -p /home/ashfaq/.ssh
RUN ssh-keygen -t rsa -f /home/ashfaq/.ssh/id_rsa -q -P ""
RUN cat /home/ashfaq/.ssh/id_rsa.pub >> /home/ashfaq/.ssh/authorized_keys
RUN chmod 600 /home/ashfaq/.ssh/authorized_keys
RUN chown -R ashfaq:ashfaq /home/ashfaq/.ssh

# Run the SSH service:
RUN sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config

COPY docker-entrypoint.sh /tmp/docker-entrypoint.sh
RUN chmod +x /tmp/docker-entrypoint.sh
ENTRYPOINT [ "/tmp/docker-entrypoint.sh" ]