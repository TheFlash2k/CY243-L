FROM cy102l/basecontainer:latest

COPY checker /usr/bin/checker
RUN chown root:cy102l /usr/bin/checker
RUN chmod 6655 /usr/bin/checker
COPY docker-entrypoint.sh /
COPY README.md /home/cy102l/
RUN chmod 444 /home/cy102l/README.md

RUN useradd -ms /bin/bash ashfaq
RUN echo "ashfaq:ashfaq" | chpasswd

ENTRYPOINT ["/docker-entrypoint.sh"]