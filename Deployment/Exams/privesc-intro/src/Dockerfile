FROM ubuntu:20.04

RUN apt update
RUN DEBIAN_FRONTEND="noninteractive" apt install -y \
    vim nano git wget curl tmux sudo \
    python3 python3-pip gcc g++ make \
    python3-dev python3-setuptools \
    build-essential libssl-dev libffi-dev openssl \
    openssh-server openssh-client net-tools

RUN rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash the_user
RUN echo 'the_user:%as21k.amu2SAVS51' | chpasswd
RUN mkdir -p /home/the_user/.ssh
RUN ssh-keygen -t rsa -f /home/the_user/.ssh/id_rsa -q -P ""
RUN cat /home/the_user/.ssh/id_rsa.pub >> /home/the_user/.ssh/authorized_keys
RUN chmod 600 /home/the_user/.ssh/authorized_keys
RUN chown -R the_user:the_user /home/the_user/.ssh

# Run the SSH service:
RUN sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config

COPY docker-entrypoint.sh /tmp/docker-entrypoint.sh
RUN chmod +x /tmp/docker-entrypoint.sh
ENTRYPOINT [ "/tmp/docker-entrypoint.sh" ]