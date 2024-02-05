FROM python:3.8.5-slim-buster

RUN pip install flask

COPY ./app/ /app/
COPY docker-entrypoint.sh /
WORKDIR /app

ENTRYPOINT [ "/docker-entrypoint.sh"]