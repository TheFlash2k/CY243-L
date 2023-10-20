FROM php:7.4.3-apache

COPY src/ /var/www/html/
RUN rm /var/www/html/custom-logs.conf

RUN rm /var/log/apache2/access.log /var/log/apache2/error.log
RUN touch /var/log/apache2/access.log /var/log/apache2/error.log
RUN chown www-data:www-data /var/log/apache2/access.log /var/log/apache2/error.log
RUN chmod -R 644 /var/log/apache2/access.log
RUN chmod -R 644 /var/log/apache2/error.log

RUN apt update && apt install cron nano ncat python3 -y
