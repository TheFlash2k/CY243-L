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

RUN useradd -ms /bin/bash cy243l
RUN echo "cy243l:cy243l" | chpasswd
RUN adduser cy243l sudo
RUN mkdir -p /home/cy243l/.ssh
RUN ssh-keygen -t rsa -f /home/cy243l/.ssh/id_rsa -q -P ""
RUN cat /home/cy243l/.ssh/id_rsa.pub >> /home/cy243l/.ssh/authorized_keys
RUN chown -R cy243l:cy243l /home/cy243l/.ssh
RUN chmod 600 /home/cy243l/.ssh
RUN cp /home/cy243l/.bashrc /root/

RUN ln -sf /dev/null /root/.bash_history
RUN ln -sf /dev/null /home/cy243l/.bash_history

RUN sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -i 's/#PubkeyAuthentication yes/PubkeyAuthentication yes/' /etc/ssh/sshd_config

RUN mv $(which curl) /bin/_s
RUN mv $(which wget) /bin/__s
RUN rm $(which apt)
RUN service ssh start

COPY checker /usr/bin/checker
RUN chown root:cy243l /usr/bin/checker
RUN chmod 6655 /usr/bin/checker
COPY docker-entrypoint.sh /
COPY README.md /home/cy243l/
RUN chmod 444 /home/cy243l/README.md

ENTRYPOINT ["/docker-entrypoint.sh"]