FROM php:7.0-apache

ENV BASE_DIR="/var/www/html"
COPY ./src/ $BASE_DIR/
COPY ./docker-entrypoint.sh /

RUN echo "ServerName localhost" >> "/etc/apache2/apache2.conf"
RUN echo "ServerName webapp.local" >> "/etc/apache2/apache2.conf"
ENTRYPOINT [ "/docker-entrypoint.sh" ]