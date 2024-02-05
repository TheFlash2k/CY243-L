FROM ubuntu:20.04

RUN apt update
RUN DEBIAN_FRONTEND="noninteractive" apt install -y \
    vim nano git wget curl tmux sudo \
    python3 python3-pip gcc g++ make \
    python3-dev python3-setuptools \
    build-essential libssl-dev libffi-dev openssl \
    openssh-server openssh-client net-tools cron

RUN rm -rf /var/lib/apt/lists/*

# Add cy243l -> for running /bin/bash /opt/nadeem.sh as Nadeem through sudo
RUN useradd -ms /bin/bash cy243l
RUN echo "cy243l:cy243l" | chpasswd
RUN mkdir -p /home/cy243l/.ssh
RUN ssh-keygen -t rsa -f /home/cy243l/.ssh/id_rsa -q -P ""
RUN cat /home/cy243l/.ssh/id_rsa.pub >> /home/cy243l/.ssh/authorized_keys
RUN chmod 600 /home/cy243l/.ssh/authorized_keys
RUN chown -R cy243l:cy243l /home/cy243l/.ssh
RUN ln -sf /dev/null /home/cy243l/.bash_history

# Add Nadeem -> for SETUID permissions
RUN useradd -ms /bin/bash nadeem
RUN echo "nadeem:n07s0s3cur3p@511s" | chpasswd
RUN mkdir -p /home/nadeem/.ssh
RUN ssh-keygen -t rsa -f /home/nadeem/.ssh/id_rsa -q -P ""
RUN cat /home/nadeem/.ssh/id_rsa.pub >> /home/nadeem/.ssh/authorized_keys
RUN chmod 600 /home/nadeem/.ssh/authorized_keys
RUN chown -R nadeem:nadeem /home/nadeem/.ssh
RUN ln -sf /dev/null /home/nadeem/.bash_history

# Add Bajwa -> For being able to overwrite /etc/passwd
RUN useradd -ms /bin/bash bajwa
RUN echo "bajwa:n07s0s3cur3p@5s11" | chpasswd
RUN mkdir -p /home/bajwa/.ssh
RUN ssh-keygen -t rsa -f /home/bajwa/.ssh/id_rsa -q -P ""
RUN cat /home/bajwa/.ssh/id_rsa.pub >> /home/bajwa/.ssh/authorized_keys
RUN chmod 600 /home/bajwa/.ssh/authorized_keys
RUN chown -R bajwa:bajwa /home/bajwa/.ssh
RUN ln -sf /dev/null /home/bajwa/.bash_history

RUN echo "root:v3ry_s3cur3_r00t_p44sword!" | chpasswd

# Run the SSH service:
RUN sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

COPY docker-entrypoint.sh /tmp/docker-entrypoint.sh
RUN chmod +x /tmp/docker-entrypoint.sh
ENTRYPOINT [ "/tmp/docker-entrypoint.sh" ]

COPY nadeem.sh /opt/