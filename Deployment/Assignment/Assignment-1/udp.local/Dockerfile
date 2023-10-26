FROM python:alpine

COPY src/main.py /app/main.py
WORKDIR /app
COPY docker-entrypoint.sh /
RUN chmod +x /docker-entrypoint.sh
RUN echo "Setting up the UDP container"
ENTRYPOINT [ "/docker-entrypoint.sh" ]