FROM ubuntu:20.04

RUN apt-get update
RUN DEBIAN_FRONTEND="noninteractive" apt-get install -y \
    build-essential \
    git \
    curl \
    vim \
    nano \
    sudo \
    openssh-server \
    openssh-client \
    net-tools \
    gcc \
    make
RUN rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash cy102l
RUN echo "cy102l:cy102l" | chpasswd
RUN adduser cy102l sudo
RUN mkdir -p /home/cy102l/.ssh
RUN ssh-keygen -t rsa -f /home/cy102l/.ssh/id_rsa -q -P ""
RUN cat /home/cy102l/.ssh/id_rsa.pub >> /home/cy102l/.ssh/authorized_keys
RUN chown -R cy102l:cy102l /home/cy102l/.ssh
RUN chmod 600 /home/cy102l/.ssh
RUN cp /home/cy102l/.bashrc /root/

RUN ln -sf /dev/null /root/.bash_history
RUN ln -sf /dev/null /home/cy102l/.bash_history

RUN sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -i 's/#PubkeyAuthentication yes/PubkeyAuthentication yes/' /etc/ssh/sshd_config

RUN mv $(which curl) /bin/_s
RUN mv $(which wget) /bin/__s
RUN rm $(which apt)
RUN service ssh start