FROM ubuntu:22.04

## Honestly, don't ask why i install on different lines.. just... idk.

RUN apt update
RUN apt install sudo nano vim net-tools iproute2 -y
RUN apt install wget curl -y
RUN apt install nmap -y
RUN apt update --fix-missing
RUN apt install python3 python3-pip -y
RUN apt install smbclient -y
RUN apt install tar -y
RUN apt install dirb -y
RUN wget -O /tmp/gobuster.tar.gz https://github.com/OJ/gobuster/releases/download/v3.6.0/gobuster_Linux_x86_64.tar.gz
RUN tar -xvf /tmp/gobuster.tar.gz -C /tmp/
RUN mv /tmp/gobuster /usr/bin/gobuster

RUN apt install iputils-ping -y
RUN apt install nikto -y
RUN apt install ffuf -y

RUN wget -O /tmp/rustscan.deb https://github.com/RustScan/RustScan/releases/download/2.0.1/rustscan_2.0.1_amd64.deb
RUN dpkg -i /tmp/rustscan.deb

RUN apt install git -y
RUN git clone https://gitlab.com/exploit-database/exploitdb /opt/exploit-database
RUN ln -sf /opt/exploit-database/searchsploit /usr/local/bin/searchsploit

RUN apt install perl -y
RUN apt install dnsutils -y
RUN wget -O /usr/bin/enum4linux https://raw.githubusercontent.com/CiscoCXSecurity/enum4linux/master/enum4linux.pl
RUN chmod +x /usr/bin/enum4linux

RUN apt install ncat

RUN useradd -m "kali" -s "/bin/bash"
RUN echo "kali:kali" | chpasswd
RUN usermod -aG sudo kali
WORKDIR /home/kali

COPY docker-entrypoint.sh /docker-entrypoint.sh
RUN chmod +x /docker-entrypoint.sh

RUN wget -O /opt/wordlist.txt https://github.com/daviddias/node-dirbuster/raw/master/lists/directory-list-2.3-medium.txt
RUN wget -O /opt/common.txt https://raw.githubusercontent.com/v0re/dirb/master/wordlists/common.txt
RUN echo "flag.txt" >> /opt/common.txt
RUN echo "flags" >> /opt/common.txt

RUN echo "If you're reading this, you have successfully setup the environment. Now, go ahead and hack the remaining stuff!" > /home/kali/README.txt
RUN echo "Here's the password for the kali user: kali" >> /home/kali/README.txt
RUN echo "Also, Start with webapp.local, then move to share.local and then udp.local\nHowever, you can follow your own structure, whatever you wanna do.\n\nOr Maybe the right order has some hints?? ;)" >> /home/kali/README.txt


ENV HOSTNAME="attacker"
USER kali
# RUN "/docker-entrypoint.sh"
ENTRYPOINT [ "/docker-entrypoint.sh" ]