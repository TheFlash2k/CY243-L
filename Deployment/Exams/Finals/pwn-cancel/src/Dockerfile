FROM theflash2k/pwn-chal

ENV CHAL_NAME=cancel

COPY ${CHAL_NAME} /app/${CHAL_NAME}
RUN apt update && apt install -y gcc-multilib

# For setting up the dynamic flagging.
COPY docker-entrypoint.sh /tmp/docker-entrypoint.sh
RUN chmod +x /tmp/docker-entrypoint.sh
ENTRYPOINT [ "/tmp/docker-entrypoint.sh" ]
