FROM php:7.4-apache

COPY ./src/ /var/www/html
WORKDIR /var/www/html
RUN apt-get update
RUN apt-get install -y \
    libpng-dev \
    libjpeg-dev \
    libpq-dev \
    default-mysql-client

RUN docker-php-ext-install -j$(nproc) \
    gd \
    mysqli \
    pdo \
    pdo_mysql \
    pdo_pgsql
    
RUN apt install -y \
    default-mysql-server

RUN apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN mysql_install_db --user=mysql --datadir=/var/lib/mysql --skip-test-db

COPY init.sql /docker-entrypoint-initdb.d/
EXPOSE 80
CMD ["apache2-foreground"]
